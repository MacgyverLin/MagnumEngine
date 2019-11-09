#include "SceneView.h"
#include "EntityDragDrop.h"
#include "ProjectView.h"

class SceneViewEntityDropTarget : public EntityDropTarget
{
public:
	SceneViewEntityDropTarget(SceneView *view_)
	: view(view_)
	{
	}

	virtual bool onCreateEntity(const wxPoint &position, const char *entityClassName)
	{
		view->onCreateEntity(position, entityClassName);

		return true;
	}
private:
	SceneView *view;
};

///////////////////////////////////////////////////////////////////////////////////////
SceneView::SceneView(ProjectView *projectView_)
: wxScrolledWindow(projectView_, wxID_ANY,
				   wxDefaultPosition, wxDefaultSize, 
				   wxBORDER_DEFAULT)
, projectView(projectView_)
{
	SceneViewEntityDropTarget *dropTarget = new SceneViewEntityDropTarget(this);
	
	this->SetDropTarget(dropTarget);

	enableUIEvent();
}

SceneView::~SceneView()
{
}

void SceneView::diableUI(unsigned int flags)
{
}

void SceneView::enableUI(unsigned int flags)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////
// View request update Model
void SceneView::onCreateEntity(const wxPoint &position, const char *entityClassName)
{
	ProjectModelBase &model = this->getModel();

	Entity *entity = model.createEntity(entityClassName, 0, Vector3::ZERO);
}

void SceneView::onMouseDown(wxMouseEvent& evt)
{
	int modifier = Input::TouchpadEvent::NONE;
	if(evt.AltDown())
		modifier |= Input::TouchpadEvent::ALT;
	if(evt.ControlDown())
		modifier |= Input::TouchpadEvent::CTRL;
	if(evt.ShiftDown())
		modifier |= Input::TouchpadEvent::SHIFT;

	wxSize size = GetSize();

	if(evt.ButtonDown())
	{
		if(!HasCapture())
		{
			CaptureMouse();

			if( evt.Button(wxMOUSE_BTN_LEFT) )
			{
				projectView->addMouseDown(modifier, 0, evt.GetX(), evt.GetY());
			}
			else if( evt.Button(wxMOUSE_BTN_MIDDLE) )
			{
				projectView->addMouseDown(modifier, 1, evt.GetX(), evt.GetY());
			}
			else if( evt.Button(wxMOUSE_BTN_RIGHT) )
			{
				projectView->addMouseDown(modifier, 2, evt.GetX(), evt.GetY());
			}
		}
	}
}

void SceneView::onMouseUp(wxMouseEvent& evt)
{
	int modifier = Input::TouchpadEvent::NONE;
	if(evt.AltDown())
		modifier |= Input::TouchpadEvent::ALT;
	if(evt.ControlDown())
		modifier |= Input::TouchpadEvent::CTRL;
	if(evt.ShiftDown())
		modifier |= Input::TouchpadEvent::SHIFT;

	if(evt.ButtonUp())
	{
		if(HasCapture())
		{
			ReleaseMouse();

			if( evt.Button(wxMOUSE_BTN_LEFT) )
			{
				projectView->addMouseUp(modifier, 0, evt.GetX(), evt.GetY());
			}
			else if( evt.Button(wxMOUSE_BTN_MIDDLE) )
			{
				projectView->addMouseUp(modifier, 1, evt.GetX(), evt.GetY());
			}
			else if( evt.Button(wxMOUSE_BTN_RIGHT) )
			{
				projectView->addMouseUp(modifier, 2, evt.GetX(), evt.GetY());
			}
		}
	}
}

void SceneView::onMouseMotion(wxMouseEvent& evt)
{
	int modifier = Input::TouchpadEvent::NONE;
	if(evt.AltDown())
		modifier |= Input::TouchpadEvent::ALT;
	if(evt.ControlDown())
		modifier |= Input::TouchpadEvent::CTRL;
	if(evt.ShiftDown())
		modifier |= Input::TouchpadEvent::SHIFT;

	//char buf[1024];
	//sprintf(buf, "modifier=%d\n", modifier);
	//::OutputDebugStringA(buf);

	wxSize size = GetSize();

	if(evt.Dragging())
	{
		if( evt.ButtonIsDown(wxMOUSE_BTN_LEFT) )
		{
			projectView->addMouseMove(modifier, 0, evt.GetX(), evt.GetY());
		}
		else if( evt.ButtonIsDown(wxMOUSE_BTN_MIDDLE) )
		{
			projectView->addMouseMove(modifier, 1, evt.GetX(), evt.GetY());
		}
		else if( evt.ButtonIsDown(wxMOUSE_BTN_RIGHT) )
		{
			projectView->addMouseMove(modifier, 2, evt.GetX(), evt.GetY());
		}
	}
}

void SceneView::onMouseWheel(wxMouseEvent& evt)
{
	int modifier = Input::TouchpadEvent::NONE;
	if(evt.AltDown())
		modifier |= Input::TouchpadEvent::ALT;
	if(evt.ControlDown())
		modifier |= Input::TouchpadEvent::CTRL;
	if(evt.ShiftDown())
		modifier |= Input::TouchpadEvent::SHIFT;

	wxSize size = GetSize();

	projectView->addWheelMotion(modifier, evt.GetX(), size.y - evt.GetY(), 
		(evt.GetWheelAxis()==wxMOUSE_WHEEL_VERTICAL) ? 0:1, evt.GetWheelRotation());
}

void SceneView::onMouseCaptureLost(wxMouseCaptureLostEvent& evt)
{
	if(HasCapture())
	{
		ReleaseMouse();
	}
}

void SceneView::onFocusEvent(wxFocusEvent &evt)
{
	if(evt.GetWindow()==this)
	{
		::OutputDebugStringA("gain focus\n");
	}
	else
	{
		::OutputDebugStringA("lost focus\n");
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////
// Model request update View
void SceneView::notify(int flags, ProjectModelBase &projectModel, const Vector<unsigned char> &buffer)
{
	if(flags & ProjectModelBase::ENTITIY_CREATORS)
	{
	}
	if(flags & ProjectModelBase::STATE_CHANGED)
	{
	}
}

void SceneView::disableUIEvent()
{
	Disconnect(wxEVT_LEFT_DOWN			, wxMouseEventHandler(SceneView::onMouseDown)					);
	Disconnect(wxEVT_MIDDLE_DOWN		, wxMouseEventHandler(SceneView::onMouseDown)					);
	Disconnect(wxEVT_RIGHT_DOWN			, wxMouseEventHandler(SceneView::onMouseDown)					);
	Disconnect(wxEVT_LEFT_UP			, wxMouseEventHandler(SceneView::onMouseUp)						);
	Disconnect(wxEVT_MIDDLE_UP			, wxMouseEventHandler(SceneView::onMouseUp)						);
	Disconnect(wxEVT_RIGHT_UP			, wxMouseEventHandler(SceneView::onMouseUp)						);
	Disconnect(wxEVT_MOTION				, wxMouseEventHandler(SceneView::onMouseMotion)					);
	Disconnect(wxEVT_MOUSEWHEEL			, wxMouseEventHandler(SceneView::onMouseWheel)					);
	Disconnect(wxEVT_MOUSE_CAPTURE_LOST	, wxMouseCaptureLostEventHandler(SceneView::onMouseCaptureLost)	);
	Disconnect(wxEVT_SET_FOCUS			, wxFocusEventHandler(SceneView::onFocusEvent)					);
	Disconnect(wxEVT_KILL_FOCUS			, wxFocusEventHandler(SceneView::onFocusEvent)					);
}

void SceneView::enableUIEvent()
{
	Connect(wxEVT_LEFT_DOWN				, wxMouseEventHandler(SceneView::onMouseDown)					);
	Connect(wxEVT_MIDDLE_DOWN			, wxMouseEventHandler(SceneView::onMouseDown)					);
	Connect(wxEVT_RIGHT_DOWN			, wxMouseEventHandler(SceneView::onMouseDown)					);
	Connect(wxEVT_LEFT_UP				, wxMouseEventHandler(SceneView::onMouseUp)						);
	Connect(wxEVT_MIDDLE_UP				, wxMouseEventHandler(SceneView::onMouseUp)						);
	Connect(wxEVT_RIGHT_UP				, wxMouseEventHandler(SceneView::onMouseUp)						);
	Connect(wxEVT_MOTION				, wxMouseEventHandler(SceneView::onMouseMotion)					);
	Connect(wxEVT_MOUSEWHEEL			, wxMouseEventHandler(SceneView::onMouseWheel)					);
	Connect(wxEVT_MOUSE_CAPTURE_LOST	, wxMouseCaptureLostEventHandler(SceneView::onMouseCaptureLost)	);
	Connect(wxEVT_SET_FOCUS				, wxFocusEventHandler(SceneView::onFocusEvent)					);
	Connect(wxEVT_KILL_FOCUS			, wxFocusEventHandler(SceneView::onFocusEvent)					);
}