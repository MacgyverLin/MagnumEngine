#ifndef _ReflectedClassPropertyPanel_h_
#define _ReflectedClassPropertyPanel_h_

#include "wxdef.h"
#include "Entity.h"
#include "ClassIndexMap.h"
#include "InputStream.h"
#include "OutputStream.h"

#include "wxLabelCtrl.h"
#include "wxCollapsePanelCtrl.h"

#include "wxBoolCtrl.h"
#include "wxArrayBoolCtrl.h"
#include "wxIntSpinnerCtrl.h"
#include "wxArrayIntSpinnerCtrl.h"
#include "wxUIntSpinnerCtrl.h"
#include "wxArrayUIntSpinnerCtrl.h"
#include "wxFloatSpinnerCtrl.h"
#include "wxArrayFloatSpinnerCtrl.h"
#include "wxDoubleSpinnerCtrl.h"
#include "wxArrayDoubleSpinnerCtrl.h"
#include "wxColorRGBACtrl.h"
#include "wxArrayColorRGBACtrl.h"
#include "wxStringCtrl.h"
#include "wxArrayStringCtrl.h"
#include "wxIVector2SpinnerCtrl.h"
#include "wxArrayIVector2SpinnerCtrl.h"
#include "wxIVector3SpinnerCtrl.h"
#include "wxArrayIVector3SpinnerCtrl.h"
#include "wxIVector4SpinnerCtrl.h"
#include "wxArrayIVector4SpinnerCtrl.h"
#include "wxVector2SpinnerCtrl.h"
#include "wxArrayVector2SpinnerCtrl.h"
#include "wxVector3SpinnerCtrl.h"
#include "wxArrayVector3SpinnerCtrl.h"
#include "wxVector4SpinnerCtrl.h"
#include "wxArrayVector4SpinnerCtrl.h"
#include "wxResourcePathCtrl.h"
#include "wxArrayResourcePathCtrl.h"
#include "wxSRTTransformCtrl.h"
#include "wxArraySRTTransformCtrl.h"
using namespace Magnum;

// ----------------------------------------------------------------------------
// event types and macros
// ----------------------------------------------------------------------------
class ReflectedClassPropertyPanelEvent : public wxNotifyEvent
{
public:
	ReflectedClassPropertyPanelEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
	: wxNotifyEvent(commandType, winid)
	, nameChanged(false)
	, transformChanged(false)
	, valueChanged(false)
	, m_bCollapsed(false)
	{
	}

	ReflectedClassPropertyPanelEvent(const ReflectedClassPropertyPanelEvent& event)
	: wxNotifyEvent(event)
	, m_bCollapsed(event.m_bCollapsed)
	, m_size(event.m_size)
	, nameChanged(event.nameChanged)
	, transformChanged(event.transformChanged)
	, valueChanged(event.valueChanged)
	{
	}

    bool GetNameChanged() const 
	{
		return nameChanged; 
	}

    void SetNameChanged(bool c) 
	{
		nameChanged = c; 
	}

    bool GetTransformChanged() const 
	{
		return transformChanged; 
	}

    void SetTransformChanged(bool c) 
	{
		transformChanged = c; 
	}

    bool GetValueChanged() const 
	{
		return valueChanged; 
	}

    void SetValueChanged(bool c) 
	{
		valueChanged = c; 
	}

    bool GetCollapsed() const 
	{
		return m_bCollapsed; 
	}

    void SetCollapsed(bool c) 
	{
		m_bCollapsed = c; 
	}

    wxSize GetSize() const 
	{
		return m_size; 
	}

    void SetSize(wxSize size) 
	{
		m_size = size; 
	}
	
    // default copy ctor, assignment operator and dtor are ok
    virtual wxEvent *Clone() const 
	{ 
		return new ReflectedClassPropertyPanelEvent(*this); 
	}
private:
	bool nameChanged;
	bool transformChanged;
	bool valueChanged;

    bool m_bCollapsed;
	wxSize m_size;

    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(ReflectedClassPropertyPanelEvent)
};

// ----------------------------------------------------------------------------
// event types and macros
// ----------------------------------------------------------------------------
typedef void (wxEvtHandler::*wxReflectedClassPropertyPanelEventFunction)(ReflectedClassPropertyPanelEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_REFLECTED_CLASS_PROPERTY_PANEL_COLLAPSED_CHANGED , 1 )
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_REFLECTED_CLASS_PROPERTY_PANEL_SIZE_CHANGED      , 2 )
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_REFLECTED_CLASS_PROPERTY_PANEL_NAME_CHANGED      , 3 )
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_REFLECTED_CLASS_PROPERTY_PANEL_TRANSFORM_CHANGED , 4 )
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_REFLECTED_CLASS_PROPERTY_PANEL_VALUE_CHANGED     , 5 )
END_DECLARE_EVENT_TYPES()

#define wxReflectedClassPropertyPanelEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxReflectedClassPropertyPanelEventFunction, &func)
	
#define wx__DECLARE_REFLECTED_CLASS_PROPERTY_PANEL_EVT(evt, id, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_REFLECTED_CLASS_PROPERTY_PANEL_ ## evt, id, wxReflectedClassPropertyPanelEventHandler(fn))	

#define EVT_REFLECTED_CLASS_PROPERTY_PANEL_COLLAPSED_CHANGED	(id, fn) wx__DECLARE_REFLECTED_CLASS_PROPERTY_PANEL_EVT(COLLAPSED_CHANGED, id, fn)
#define EVT_REFLECTED_CLASS_PROPERTY_PANEL_SIZE_CHANGED			(id, fn) wx__DECLARE_REFLECTED_CLASS_PROPERTY_PANEL_EVT(SIZE_CHANGED, id, fn)
#define EVT_REFLECTED_CLASS_PROPERTY_PANEL_NAME_CHANGED			(id, fn) wx__DECLARE_REFLECTED_CLASS_PROPERTY_PANEL_EVT(NAME_CHANGED, id, fn)
#define EVT_REFLECTED_CLASS_PROPERTY_PANEL_TRANSFORM_CHANGED	(id, fn) wx__DECLARE_REFLECTED_CLASS_PROPERTY_PANEL_EVT(TRANSFORM_CHANGED, id, fn)
#define EVT_REFLECTED_CLASS_PROPERTY_PANEL_VALUE_CHANGED		(id, fn) wx__DECLARE_REFLECTED_CLASS_PROPERTY_PANEL_EVT(VALUE_CHANGED, id, fn)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class ReflectClass>
class ReflectedClassPropertyPanel : public wxCollapsePanelCtrl
{
public:
	ReflectedClassPropertyPanel(wxWindow *instance, wxWindow *&parentWnd, wxSizer *&parentSizer, ReflectClass *reflectClass_)
	: wxCollapsePanelCtrl(parentWnd, wxID_ANY, "", instance)
	, reflectClass(reflectClass_)
	{
		/////////////////////////////////////////////////////////////////////////////////////////
		parentSizer->Add(this, 1, wxEXPAND);
		this->SetBackgroundColour(instance->GetParent()->GetBackgroundColour());
		this->SetForegroundColour(instance->GetParent()->GetForegroundColour());
		this->Connect(wxEVT_COMMAND_COLLAPSEPANEL_CTRL_COLLAPSED_CHANGED, wxCollapsePanelCtrlEventHandler(ReflectedClassPropertyPanel<ReflectClass>::onCollapsePanelChanged), 0, this);
	
		wxWindow *subPanel = this->GetPane();
		subPanel->SetBackgroundColour(instance->GetParent()->GetBackgroundColour());
		subPanel->Connect(wxEVT_SIZE, wxSizeEventHandler(ReflectedClassPropertyPanel<ReflectClass>::onSize), 0, this);
	
		wxBoxSizer *vBox			= new wxBoxSizer(wxVERTICAL);
		subPanelSizer				= new wxFlexGridSizer(1); subPanelSizer->AddGrowableCol(0);
		subPanel->SetSizer(vBox);
			vBox->Add(subPanelSizer, 1, wxEXPAND);

		const ClassDesc &classDesc	= reflectClass->getClassDesc();
		this->SetLabel(classDesc.getName());

		/////////////////////////////////////////////////////////////////////////////////////////
		std::vector<const PropertyDesc *> propertyDescs;
		classDesc.getProperties(propertyDescs, true);

		controls.resize(propertyDescs.size());
		for(unsigned int i=0; i<propertyDescs.size(); i++)
		{
			controls[i] = createPropertyDescUI(instance, this, subPanel, subPanelSizer, *propertyDescs[i], reflectClass);
		}

		this->Collapse(false);

		parentWnd	= subPanel;
		parentSizer	= subPanelSizer;
	}

	~ReflectedClassPropertyPanel()
	{
	}

	template<class T>
	void update(const char *name, const T &value)
	{
		const ClassDesc &classDesc	= reflectClass->getClassDesc();

		std::vector<const PropertyDesc *> propertyDescs;
		classDesc.getProperties(propertyDescs, true);

		for(unsigned int i=0; i<propertyDescs.size(); i++)
		{
			if( strcmp(propertyDescs[i]->getName(), name)==0 )
				updatePropertyDescUI(controls[i], *propertyDescs[i], reflectClass);
		}
	}

	void update()
	{
		const ClassDesc &classDesc	= reflectClass->getClassDesc();

		std::vector<const PropertyDesc *> propertyDescs;
		classDesc.getProperties(propertyDescs, true);

		for(unsigned int i=0; i<propertyDescs.size(); i++)
		{
			updatePropertyDescUI(controls[i], *propertyDescs[i], reflectClass);
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const ReflectClass *getReflectClass()
	{
		return reflectClass;
	}

	void onCollapsePanelChanged(wxCollapsePanelCtrlEvent &evt)
	{
		//parent->FitInside();
		//parent->SetScrollRate(20, 20);

		ReflectedClassPropertyPanelEvent event(wxEVT_COMMAND_REFLECTED_CLASS_PROPERTY_PANEL_COLLAPSED_CHANGED, GetId());
		event.SetEventObject(this);
		event.SetCollapsed(evt.GetCollapsed());

		GetEventHandler()->ProcessEvent( event );
	}

	void onSize(wxSizeEvent &evt)
	{
		//parent->FitInside();
		//parent->SetScrollRate(20, 20);

		ReflectedClassPropertyPanelEvent event(wxEVT_COMMAND_REFLECTED_CLASS_PROPERTY_PANEL_SIZE_CHANGED, GetId());
		event.SetEventObject(this);
		event.SetSize(evt.GetSize());

		GetEventHandler()->ProcessEvent( event );
	}
protected:
private:
	template<class GUIEvent>
	void onGUIValueChanged(GUIEvent &evt)
	{
		setReflectedClassValue(reflectClass, evt.GetName(), evt.GetValue());

		if(evt.GetName()=="Name")
		{
			ReflectedClassPropertyPanelEvent event(wxEVT_COMMAND_REFLECTED_CLASS_PROPERTY_PANEL_NAME_CHANGED, GetId());
			event.SetEventObject(this);
			event.SetNameChanged(true);
			GetEventHandler()->ProcessEvent( event );
		}
		else if(evt.GetName()=="Transform")
		{
			ReflectedClassPropertyPanelEvent event(wxEVT_COMMAND_REFLECTED_CLASS_PROPERTY_PANEL_TRANSFORM_CHANGED, GetId());
			event.SetEventObject(this);
			event.SetTransformChanged(true);
			GetEventHandler()->ProcessEvent( event );
		}
		else
		{
			ReflectedClassPropertyPanelEvent event(wxEVT_COMMAND_REFLECTED_CLASS_PROPERTY_PANEL_VALUE_CHANGED, GetId());
			event.SetEventObject(this);
			event.SetValueChanged(true);
			GetEventHandler()->ProcessEvent( event );
		}
	}

	template<class T>	
	bool setReflectedClassValue(ReflectClass *ptr, const char *name, const T &value)
	{
		const ClassDesc &classDesc	= ptr->getClassDesc();

		try
		{
			const PropertyDesc &propertyDesc	= classDesc.getProperty(name);
			propertyDesc.set(ptr, value);
			return true;
		}
		catch(...)
		{
			return false;
		}
	}

	wxWindow *createPropertyDescUI(wxWindow *topPanel, ReflectedClassPropertyPanel<ReflectClass> *instance, wxWindow *parentWnd, wxSizer *parentSizer, const PropertyDesc &propertyDesc, ReflectClass *ptr) const
	{
		//int classNameIndex			= propertyDesc.getClassIndexMap::instance().getClassIndex(propertyDesc.getType());
		int classNameIndex			= propertyDesc.getClassIndex();
	
		assert(classNameIndex>=0 && classNameIndex<ClassIndexMap::instance().getNumClasses());

		return propertyDescCreateUIFuncs[classNameIndex](topPanel, instance, parentWnd, parentSizer, propertyDesc, ptr);
	}

	void updatePropertyDescUI(wxWindow *ctrl, const PropertyDesc &propertyDesc, ReflectClass *ptr)
	{
		//int classNameIndex			= ClassIndexMap::instance().getClassIndex(propertyDesc.getType());
		int classNameIndex			= propertyDesc.getClassIndex();
	
		assert(classNameIndex>=0 && classNameIndex<ClassIndexMap::instance().getNumClasses());

		return propertyDescUpdateUIFuncs[classNameIndex](ctrl, propertyDesc, ptr);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	static wxWindow *(*propertyDescCreateUIFuncs[])(wxWindow *topPanel, ReflectedClassPropertyPanel<ReflectClass> *instance, wxWindow *parentWnd, wxSizer *parentSizer, const PropertyDesc &propertyDesc, ReflectClass *ptr);

	static wxWindow *createBool				(wxWindow *topPanel, ReflectedClassPropertyPanel<ReflectClass> *instance, wxWindow *parentWnd, wxSizer *parentSizer, const PropertyDesc &propertyDesc, ReflectClass *ptr)
	{
		bool val;
		propertyDesc.get(val, ptr);
	
		wxBoolCtrl *ctrl = new wxBoolCtrl(parentWnd, wxID_ANY, 
										  propertyDesc.getName(), 
										  val);

		wxBoxSizer *hBox = new wxBoxSizer(wxHORIZONTAL);
		parentSizer->Add(hBox, 0, wxRIGHT | wxBOTTOM | wxEXPAND, 4);
			hBox->Add(COLLAPSE_BUTTON_SIZE*1.5, COLLAPSE_BUTTON_SIZE, 0);
			hBox->Add(ctrl, 1, wxEXPAND);

		ctrl->Connect(wxEVT_COMMAND_BOOL_CTRL_VALUE_CHANGED, wxBoolCtrlEventHandler(onGUIValueChanged<wxBoolCtrlEvent>), 0, instance);

		return ctrl;
	}

	static wxWindow *createVectorBool		(wxWindow *topPanel, ReflectedClassPropertyPanel<ReflectClass> *instance, wxWindow *parentWnd, wxSizer *parentSizer, const PropertyDesc &propertyDesc, ReflectClass *ptr)
	{
		Vector<bool> val;
		propertyDesc.get(val, ptr);
	
		wxArrayBoolCtrl *ctrl = new wxArrayBoolCtrl(parentWnd, wxID_ANY,
													propertyDesc.getName(),
													val, 
													topPanel);

		parentSizer->Add(ctrl, 0, wxRIGHT | wxBOTTOM | wxEXPAND, 4);

		ctrl->Connect(wxEVT_COMMAND_ARRAY_BOOL_CTRL_VALUE_CHANGED , wxArrayBoolCtrlEventHandler(onGUIValueChanged<wxArrayBoolCtrlEvent> ), 0, instance);

		return ctrl;
	}

	static wxWindow *createInt				(wxWindow *topPanel, ReflectedClassPropertyPanel<ReflectClass> *instance, wxWindow *parentWnd, wxSizer *parentSizer, const PropertyDesc &propertyDesc, ReflectClass *ptr)
	{
		int val;
		propertyDesc.get(val, ptr);
	
		wxIntSpinnerCtrl *ctrl = new wxIntSpinnerCtrl(parentWnd, wxID_ANY,
													  propertyDesc.getName(),
													  val, INT_MIN, INT_MAX);

		wxBoxSizer *hBox = new wxBoxSizer(wxHORIZONTAL);
		parentSizer->Add(hBox, 0, wxRIGHT | wxBOTTOM | wxEXPAND, 4);
			hBox->Add(COLLAPSE_BUTTON_SIZE*1.5, COLLAPSE_BUTTON_SIZE, 0);
			hBox->Add(ctrl, 1, wxEXPAND);

		ctrl->Connect(wxEVT_COMMAND_INT_SPINNER_CTRL_VALUE_CHANGED, wxIntSpinnerCtrlEventHandler(onGUIValueChanged<wxIntSpinnerCtrlEvent>), 0, instance);

		return ctrl;
	}
	
	static wxWindow *createVectorInt			(wxWindow *topPanel, ReflectedClassPropertyPanel<ReflectClass> *instance, wxWindow *parentWnd, wxSizer *parentSizer, const PropertyDesc &propertyDesc, ReflectClass *ptr)
	{
		Vector<int> val;
		propertyDesc.get(val, ptr);

		wxArrayIntSpinnerCtrl *ctrl = new wxArrayIntSpinnerCtrl(parentWnd, wxID_ANY, 
																propertyDesc.getName(),
																val, INT_MIN, INT_MAX,
																topPanel);

		parentSizer->Add(ctrl, 0, wxRIGHT | wxBOTTOM | wxEXPAND, 4);

		ctrl->Connect(wxEVT_COMMAND_ARRAY_INT_SPINNER_CTRL_VALUE_CHANGED , wxArrayIntSpinnerCtrlEventHandler(onGUIValueChanged<wxArrayIntSpinnerCtrlEvent> ), 0, instance);

		return ctrl;
	}

	static wxWindow *createUInt				(wxWindow *topPanel, ReflectedClassPropertyPanel<ReflectClass> *instance, wxWindow *parentWnd, wxSizer *parentSizer, const PropertyDesc &propertyDesc, ReflectClass *ptr)
	{
		unsigned int val;
		propertyDesc.get(val, ptr);
	
		wxUIntSpinnerCtrl *ctrl = new wxUIntSpinnerCtrl(parentWnd, wxID_ANY, 
														propertyDesc.getName(),
														val, 0, 4294967295);

		wxBoxSizer *hBox = new wxBoxSizer(wxHORIZONTAL);
		parentSizer->Add(hBox, 0, wxRIGHT | wxBOTTOM | wxEXPAND, 4);
			hBox->Add(COLLAPSE_BUTTON_SIZE*1.5, COLLAPSE_BUTTON_SIZE, 0);
			hBox->Add(ctrl, 1, wxEXPAND);

		ctrl->Connect(wxEVT_COMMAND_UINT_SPINNER_CTRL_VALUE_CHANGED, wxUIntSpinnerCtrlEventHandler(onGUIValueChanged<wxUIntSpinnerCtrlEvent>), 0, instance);

		return ctrl;
	}

	static wxWindow *createVectorUInt		(wxWindow *topPanel, ReflectedClassPropertyPanel<ReflectClass> *instance, wxWindow *parentWnd, wxSizer *parentSizer, const PropertyDesc &propertyDesc, ReflectClass *ptr)
	{
		Vector<unsigned int> val;
		propertyDesc.get(val, ptr);
	
		wxArrayUIntSpinnerCtrl *ctrl = new wxArrayUIntSpinnerCtrl(parentWnd, wxID_ANY,
																  propertyDesc.getName(),
																  val, 0, UINT_MAX,
																  topPanel);

		parentSizer->Add(ctrl, 0, wxRIGHT | wxBOTTOM | wxEXPAND, 4);

		ctrl->Connect(wxEVT_COMMAND_ARRAY_UINT_SPINNER_CTRL_VALUE_CHANGED , wxArrayUIntSpinnerCtrlEventHandler(onGUIValueChanged<wxArrayUIntSpinnerCtrlEvent> ), 0, instance);

		return ctrl;
	}

	static wxWindow *createFloat				(wxWindow *topPanel, ReflectedClassPropertyPanel<ReflectClass> *instance, wxWindow *parentWnd, wxSizer *parentSizer, const PropertyDesc &propertyDesc, ReflectClass *ptr)
	{
		float val;
		propertyDesc.get(val, ptr);
	
		wxFloatSpinnerCtrl *ctrl = new wxFloatSpinnerCtrl(parentWnd, wxID_ANY, 
														  propertyDesc.getName(),
														  val, Math::MIN_REAL, Math::MAX_REAL);

		wxBoxSizer *hBox = new wxBoxSizer(wxHORIZONTAL);
		parentSizer->Add(hBox, 0, wxRIGHT | wxBOTTOM | wxEXPAND, 4);
			hBox->Add(COLLAPSE_BUTTON_SIZE*1.5, COLLAPSE_BUTTON_SIZE, 0);
			hBox->Add(ctrl, 1, wxEXPAND);

		ctrl->Connect(wxEVT_COMMAND_FLOAT_SPINNER_CTRL_VALUE_CHANGED, wxFloatSpinnerCtrlEventHandler(onGUIValueChanged<wxFloatSpinnerCtrlEvent>), 0, instance);

		return ctrl;
	}

	static wxWindow *createVectorFloat		(wxWindow *topPanel, ReflectedClassPropertyPanel<ReflectClass> *instance, wxWindow *parentWnd, wxSizer *parentSizer, const PropertyDesc &propertyDesc, ReflectClass *ptr)
	{
		Vector<float> val;
		propertyDesc.get(val, ptr);

		wxArrayFloatSpinnerCtrl *ctrl = new wxArrayFloatSpinnerCtrl(parentWnd, wxID_ANY, 
																	propertyDesc.getName(),
																	val, Math::MIN_REAL, Math::MAX_REAL,
																	topPanel);

		parentSizer->Add(ctrl, 0, wxRIGHT | wxBOTTOM | wxEXPAND, 4);

		ctrl->Connect(wxEVT_COMMAND_ARRAY_FLOAT_SPINNER_CTRL_VALUE_CHANGED , wxArrayFloatSpinnerCtrlEventHandler(onGUIValueChanged<wxArrayFloatSpinnerCtrlEvent> ), 0, instance);

		return ctrl;
	}

	static wxWindow *createDouble			(wxWindow *topPanel, ReflectedClassPropertyPanel<ReflectClass> *instance, wxWindow *parentWnd, wxSizer *parentSizer, const PropertyDesc &propertyDesc, ReflectClass *ptr)
	{
		double val;
		propertyDesc.get(val, ptr);
	
		wxDoubleSpinnerCtrl *ctrl = new wxDoubleSpinnerCtrl(parentWnd, wxID_ANY,
															propertyDesc.getName(),
															val, Math::MIN_REAL, Math::MAX_REAL);

		wxBoxSizer *hBox = new wxBoxSizer(wxHORIZONTAL);
		parentSizer->Add(hBox, 0, wxRIGHT | wxBOTTOM | wxEXPAND, 4);
			hBox->Add(COLLAPSE_BUTTON_SIZE*1.5, COLLAPSE_BUTTON_SIZE, 0);
			hBox->Add(ctrl, 1, wxEXPAND);

		ctrl->Connect(wxEVT_COMMAND_DOUBLE_SPINNER_CTRL_VALUE_CHANGED, wxDoubleSpinnerCtrlEventHandler(onGUIValueChanged<wxDoubleSpinnerCtrlEvent>), 0, instance);

		return ctrl;
	}
	
	static wxWindow *createVectorDouble		(wxWindow *topPanel, ReflectedClassPropertyPanel<ReflectClass> *instance, wxWindow *parentWnd, wxSizer *parentSizer, const PropertyDesc &propertyDesc, ReflectClass *ptr)
	{
		Vector<double> val;
		propertyDesc.get(val, ptr);
	
		wxArrayDoubleSpinnerCtrl *ctrl = new wxArrayDoubleSpinnerCtrl(parentWnd, wxID_ANY, 
																	  propertyDesc.getName(),
																	  val, Math::MIN_REAL, Math::MAX_REAL,
																	  topPanel);

		parentSizer->Add(ctrl, 0, wxRIGHT | wxBOTTOM | wxEXPAND, 4);

		ctrl->Connect(wxEVT_COMMAND_ARRAY_DOUBLE_SPINNER_CTRL_VALUE_CHANGED , wxArrayDoubleSpinnerCtrlEventHandler(onGUIValueChanged<wxArrayDoubleSpinnerCtrlEvent> ), 0, instance);

		return ctrl;
	}

	static wxWindow *createString			(wxWindow *topPanel, ReflectedClassPropertyPanel<ReflectClass> *instance, wxWindow *parentWnd, wxSizer *parentSizer, const PropertyDesc &propertyDesc, ReflectClass *ptr)
	{
		String val;
		propertyDesc.get(val, ptr);
	
		wxStringCtrl *ctrl = new wxStringCtrl(parentWnd, wxID_ANY, 
											  propertyDesc.getName(),
											  val);

		wxBoxSizer *hBox = new wxBoxSizer(wxHORIZONTAL);
		parentSizer->Add(hBox, 0, wxRIGHT | wxBOTTOM | wxEXPAND, 4);
			hBox->Add(COLLAPSE_BUTTON_SIZE*1.5, COLLAPSE_BUTTON_SIZE, 0);
			hBox->Add(ctrl, 1, wxEXPAND);

		ctrl->Connect(wxEVT_COMMAND_STRING_CTRL_VALUE_CHANGED, wxStringCtrlEventHandler(onGUIValueChanged<wxStringCtrlEvent>), 0, instance);

		return ctrl;
	}

	static wxWindow *createVectorString		(wxWindow *topPanel, ReflectedClassPropertyPanel<ReflectClass> *instance, wxWindow *parentWnd, wxSizer *parentSizer, const PropertyDesc &propertyDesc, ReflectClass *ptr)
	{
		Vector<String> val;
		propertyDesc.get(val, ptr);

		wxArrayStringCtrl *ctrl = new wxArrayStringCtrl(parentWnd, wxID_ANY, 
														propertyDesc.getName(),
														val, 
														topPanel);

		parentSizer->Add(ctrl, 0, wxRIGHT | wxBOTTOM | wxEXPAND, 4);

		ctrl->Connect(wxEVT_COMMAND_ARRAY_STRING_CTRL_VALUE_CHANGED , wxArrayStringCtrlEventHandler(onGUIValueChanged<wxArrayStringCtrlEvent> ), 0, instance);

		return ctrl;
	}

	static wxWindow *createColorRGBA			(wxWindow *topPanel, ReflectedClassPropertyPanel<ReflectClass> *instance, wxWindow *parentWnd, wxSizer *parentSizer, const PropertyDesc &propertyDesc, ReflectClass *ptr)
	{
		ColorRGBA val;
		propertyDesc.get(val, ptr);
	
		wxColorRGBACtrl *ctrl = new wxColorRGBACtrl(parentWnd, wxID_ANY, 
													propertyDesc.getName(),
													val);

		wxBoxSizer *hBox = new wxBoxSizer(wxHORIZONTAL);
		parentSizer->Add(hBox, 0, wxRIGHT | wxBOTTOM | wxEXPAND, 4);
			hBox->Add(COLLAPSE_BUTTON_SIZE*1.5, COLLAPSE_BUTTON_SIZE, 0);
			hBox->Add(ctrl, 1, wxEXPAND);

		ctrl->Connect(wxEVT_COMMAND_COLORRGBA_CTRL_VALUE_CHANGED, wxColorRGBACtrlEventHandler(onGUIValueChanged<wxColorRGBACtrlEvent>), 0, instance);

		return ctrl;
	}

	static wxWindow *createVectorColorRGBA	(wxWindow *topPanel, ReflectedClassPropertyPanel<ReflectClass> *instance, wxWindow *parentWnd, wxSizer *parentSizer, const PropertyDesc &propertyDesc, ReflectClass *ptr)
	{
		Vector<ColorRGBA> val;
		propertyDesc.get(val, ptr);

		wxArrayColorRGBACtrl *ctrl = new wxArrayColorRGBACtrl(parentWnd, wxID_ANY, 
															  propertyDesc.getName(),
															  val,
															  topPanel);

		parentSizer->Add(ctrl, 0, wxRIGHT | wxBOTTOM | wxEXPAND, 4);

		ctrl->Connect(wxEVT_COMMAND_ARRAY_COLORRGBA_CTRL_VALUE_CHANGED , wxArrayColorRGBACtrlEventHandler(onGUIValueChanged<wxArrayColorRGBACtrlEvent> ), 0, instance);

		return ctrl;
	}

	static wxWindow *createVector2			(wxWindow *topPanel, ReflectedClassPropertyPanel<ReflectClass> *instance, wxWindow *parentWnd, wxSizer *parentSizer, const PropertyDesc &propertyDesc, ReflectClass *ptr)
	{
		Vector2 val;
		propertyDesc.get(val, ptr);
	
		wxVector2SpinnerCtrl *ctrl = new wxVector2SpinnerCtrl(parentWnd, wxID_ANY, 
															  propertyDesc.getName(), true,
															  val, Vector2(Math::MIN_REAL, Math::MIN_REAL), Vector2(Math::MAX_REAL, Math::MAX_REAL),
															  topPanel);

		parentSizer->Add(ctrl, 0, wxRIGHT | wxBOTTOM | wxEXPAND, 4);

		ctrl->Connect(wxEVT_COMMAND_VECTOR2_SPINNER_CTRL_VALUE_CHANGED, wxVector2SpinnerCtrlEventHandler(onGUIValueChanged<wxVector2SpinnerCtrlEvent>), 0, instance);

		return ctrl;
	}

	static wxWindow *createVectorVector2		(wxWindow *topPanel, ReflectedClassPropertyPanel<ReflectClass> *instance, wxWindow *parentWnd, wxSizer *parentSizer, const PropertyDesc &propertyDesc, ReflectClass *ptr)
	{
		Vector<Vector2> val;
		propertyDesc.get(val, ptr);

		wxArrayVector2SpinnerCtrl *ctrl = new wxArrayVector2SpinnerCtrl(parentWnd, wxID_ANY, 
																		propertyDesc.getName(),
																		val, Vector2(Math::MIN_REAL, Math::MIN_REAL), Vector2(Math::MAX_REAL, Math::MAX_REAL),
																		topPanel);

		parentSizer->Add(ctrl, 0, wxRIGHT | wxBOTTOM | wxEXPAND, 4);

		ctrl->Connect(wxEVT_COMMAND_ARRAY_VECTOR2_SPINNER_CTRL_VALUE_CHANGED , wxArrayVector2SpinnerCtrlEventHandler(onGUIValueChanged<wxArrayVector2SpinnerCtrlEvent> ), 0, instance);

		return ctrl;
	}

	static wxWindow *createVector3			(wxWindow *topPanel, ReflectedClassPropertyPanel<ReflectClass> *instance, wxWindow *parentWnd, wxSizer *parentSizer, const PropertyDesc &propertyDesc, ReflectClass *ptr)
	{
		Vector3 val;
		propertyDesc.get(val, ptr);
	
		wxVector3SpinnerCtrl *ctrl = new wxVector3SpinnerCtrl(parentWnd, wxID_ANY,
															  propertyDesc.getName(), true,
															  val, Vector3(Math::MIN_REAL, Math::MIN_REAL, Math::MIN_REAL), Vector3(Math::MAX_REAL, Math::MAX_REAL, Math::MAX_REAL),
															  topPanel);

		parentSizer->Add(ctrl, 0, wxRIGHT | wxBOTTOM | wxEXPAND, 4);

		ctrl->Connect(wxEVT_COMMAND_VECTOR3_SPINNER_CTRL_VALUE_CHANGED, wxVector3SpinnerCtrlEventHandler(onGUIValueChanged<wxVector3SpinnerCtrlEvent>), 0, instance);

		return ctrl;
	}

	static wxWindow *createVectorVector3		(wxWindow *topPanel, ReflectedClassPropertyPanel<ReflectClass> *instance, wxWindow *parentWnd, wxSizer *parentSizer, const PropertyDesc &propertyDesc, ReflectClass *ptr)
	{
		Vector<Vector3> val;
		propertyDesc.get(val, ptr);
		
		wxArrayVector3SpinnerCtrl *ctrl = new wxArrayVector3SpinnerCtrl(parentWnd, wxID_ANY, 
																		propertyDesc.getName(),
																		val, Vector3(Math::MIN_REAL, Math::MIN_REAL, Math::MIN_REAL), Vector3(Math::MAX_REAL, Math::MAX_REAL, Math::MAX_REAL),
																		topPanel);

		parentSizer->Add(ctrl, 0, wxRIGHT | wxBOTTOM | wxEXPAND, 4);

		ctrl->Connect(wxEVT_COMMAND_ARRAY_VECTOR3_SPINNER_CTRL_VALUE_CHANGED , wxArrayVector3SpinnerCtrlEventHandler(onGUIValueChanged<wxArrayVector3SpinnerCtrlEvent> ), 0, instance);

		return ctrl;
	}

	static wxWindow *createVector4			(wxWindow *topPanel, ReflectedClassPropertyPanel<ReflectClass> *instance, wxWindow *parentWnd, wxSizer *parentSizer, const PropertyDesc &propertyDesc, ReflectClass *ptr)
	{
		Vector4 val;
		propertyDesc.get(val, ptr);
	
		wxVector4SpinnerCtrl *ctrl = new wxVector4SpinnerCtrl(parentWnd, wxID_ANY,
															  propertyDesc.getName(), true,
															  val, Vector4(Math::MIN_REAL, Math::MIN_REAL, Math::MIN_REAL, Math::MIN_REAL), Vector4(Math::MAX_REAL, Math::MAX_REAL, Math::MAX_REAL, Math::MAX_REAL),
															  topPanel);

		parentSizer->Add(ctrl, 0, wxRIGHT | wxBOTTOM | wxEXPAND, 4);

		ctrl->Connect(wxEVT_COMMAND_VECTOR4_SPINNER_CTRL_VALUE_CHANGED, wxVector4SpinnerCtrlEventHandler(onGUIValueChanged<wxVector4SpinnerCtrlEvent>), 0, instance);

		return ctrl;
	}

	static wxWindow *createVectorVector4		(wxWindow *topPanel, ReflectedClassPropertyPanel<ReflectClass> *instance, wxWindow *parentWnd, wxSizer *parentSizer, const PropertyDesc &propertyDesc, ReflectClass *ptr)
	{
		Vector<Vector4> val;
		propertyDesc.get(val, ptr);
	
		wxArrayVector4SpinnerCtrl *ctrl = new wxArrayVector4SpinnerCtrl(parentWnd, wxID_ANY, 
																		propertyDesc.getName(),
																		val, Vector4(Math::MIN_REAL, Math::MIN_REAL, Math::MIN_REAL, Math::MIN_REAL), Vector4(Math::MAX_REAL, Math::MAX_REAL, Math::MAX_REAL, Math::MAX_REAL),
																		topPanel);

		parentSizer->Add(ctrl, 0, wxRIGHT | wxBOTTOM | wxEXPAND, 4);

		ctrl->Connect(wxEVT_COMMAND_ARRAY_VECTOR4_SPINNER_CTRL_VALUE_CHANGED, wxArrayVector4SpinnerCtrlEventHandler(onGUIValueChanged<wxArrayVector4SpinnerCtrlEvent> ), 0, instance);

		return ctrl;
	}

	static wxWindow *createIVector2			(wxWindow *topPanel, ReflectedClassPropertyPanel<ReflectClass> *instance, wxWindow *parentWnd, wxSizer *parentSizer, const PropertyDesc &propertyDesc, ReflectClass *ptr)
	{
		IVector2 val;
		propertyDesc.get(val, ptr);
	
		wxIVector2SpinnerCtrl *ctrl = new wxIVector2SpinnerCtrl(parentWnd, wxID_ANY, 
																propertyDesc.getName(), true,
																val, IVector2(INT_MIN, INT_MIN), IVector2(INT_MAX, INT_MAX),
																topPanel);

		parentSizer->Add(ctrl, 0, wxRIGHT | wxBOTTOM | wxEXPAND, 4);

		ctrl->Connect(wxEVT_COMMAND_IVECTOR2_SPINNER_CTRL_VALUE_CHANGED, wxIVector2SpinnerCtrlEventHandler(onGUIValueChanged<wxIVector2SpinnerCtrlEvent>), 0, instance);

		return ctrl;
	}

	static wxWindow *createVectorIVector2	(wxWindow *topPanel, ReflectedClassPropertyPanel<ReflectClass> *instance, wxWindow *parentWnd, wxSizer *parentSizer, const PropertyDesc &propertyDesc, ReflectClass *ptr)
	{
		Vector<IVector2> val;
		propertyDesc.get(val, ptr);

		wxArrayIVector2SpinnerCtrl *ctrl = new wxArrayIVector2SpinnerCtrl(parentWnd, wxID_ANY, 
																		  propertyDesc.getName(),
																		  val, IVector2(INT_MIN, INT_MIN), IVector2(INT_MAX, INT_MAX),
																		  topPanel);

		parentSizer->Add(ctrl, 0, wxRIGHT | wxBOTTOM | wxEXPAND, 4);

		ctrl->Connect(wxEVT_COMMAND_ARRAY_IVECTOR2_SPINNER_CTRL_VALUE_CHANGED, wxArrayIVector2SpinnerCtrlEventHandler(onGUIValueChanged<wxArrayIVector2SpinnerCtrlEvent> ), 0, instance);

		return ctrl;
	}

	static wxWindow *createIVector3			(wxWindow *topPanel, ReflectedClassPropertyPanel<ReflectClass> *instance, wxWindow *parentWnd, wxSizer *parentSizer, const PropertyDesc &propertyDesc, ReflectClass *ptr)
	{
		IVector3 val;
		propertyDesc.get(val, ptr);
	
		wxIVector3SpinnerCtrl *ctrl = new wxIVector3SpinnerCtrl(parentWnd, wxID_ANY, 
																propertyDesc.getName(),true,
																val, IVector3(INT_MIN, INT_MIN, INT_MIN), IVector3(INT_MAX, INT_MAX, INT_MAX),
																topPanel);

		parentSizer->Add(ctrl, 0, wxRIGHT | wxBOTTOM | wxEXPAND, 4);

		ctrl->Connect(wxEVT_COMMAND_IVECTOR3_SPINNER_CTRL_VALUE_CHANGED, wxIVector3SpinnerCtrlEventHandler(onGUIValueChanged<wxIVector3SpinnerCtrlEvent>), 0, instance);

		return ctrl;
	}

	static wxWindow *createVectorIVector3	(wxWindow *topPanel, ReflectedClassPropertyPanel<ReflectClass> *instance, wxWindow *parentWnd, wxSizer *parentSizer, const PropertyDesc &propertyDesc, ReflectClass *ptr)
	{
		Vector<IVector3> val;
		propertyDesc.get(val, ptr);

		wxArrayIVector3SpinnerCtrl *ctrl = new wxArrayIVector3SpinnerCtrl(parentWnd, wxID_ANY, 
																		  propertyDesc.getName(),
																		  val, IVector3(INT_MIN, INT_MIN, INT_MIN), IVector3(INT_MAX, INT_MAX, INT_MAX),
																		  topPanel);

		parentSizer->Add(ctrl, 0, wxRIGHT | wxBOTTOM | wxEXPAND, 4);

		ctrl->Connect(wxEVT_COMMAND_ARRAY_IVECTOR3_SPINNER_CTRL_VALUE_CHANGED, wxArrayIVector3SpinnerCtrlEventHandler(onGUIValueChanged<wxArrayIVector3SpinnerCtrlEvent> ), 0, instance);

		return ctrl;
	}

	static wxWindow *createIVector4			(wxWindow *topPanel, ReflectedClassPropertyPanel<ReflectClass> *instance, wxWindow *parentWnd, wxSizer *parentSizer, const PropertyDesc &propertyDesc, ReflectClass *ptr)
	{
		IVector4 val;
		propertyDesc.get(val, ptr);
	
		wxIVector4SpinnerCtrl *ctrl = new wxIVector4SpinnerCtrl(parentWnd, wxID_ANY, 
																propertyDesc.getName(), true,
																val, IVector4(INT_MIN, INT_MIN, INT_MIN, INT_MIN), IVector4(INT_MAX, INT_MAX, INT_MAX, INT_MAX),
																topPanel);

		parentSizer->Add(ctrl, 0, wxRIGHT | wxBOTTOM | wxEXPAND, 4);

		ctrl->Connect(wxEVT_COMMAND_IVECTOR4_SPINNER_CTRL_VALUE_CHANGED, wxIVector4SpinnerCtrlEventHandler(onGUIValueChanged<wxIVector4SpinnerCtrlEvent>), 0, instance);

		return ctrl;
	}

	static wxWindow *createVectorIVector4	(wxWindow *topPanel, ReflectedClassPropertyPanel<ReflectClass> *instance, wxWindow *parentWnd, wxSizer *parentSizer, const PropertyDesc &propertyDesc, ReflectClass *ptr)
	{
		Vector<IVector4> val;
		propertyDesc.get(val, ptr);

		wxArrayIVector4SpinnerCtrl *ctrl = new wxArrayIVector4SpinnerCtrl(parentWnd, wxID_ANY, 
																		  propertyDesc.getName(),
																		  val, IVector4(INT_MIN, INT_MIN, INT_MIN, INT_MIN), IVector4(INT_MAX, INT_MAX, INT_MAX, INT_MAX),
																		  topPanel);

		parentSizer->Add(ctrl, 0, wxRIGHT | wxBOTTOM | wxEXPAND, 4);

		ctrl->Connect(wxEVT_COMMAND_ARRAY_IVECTOR4_SPINNER_CTRL_VALUE_CHANGED , wxArrayIVector4SpinnerCtrlEventHandler(onGUIValueChanged<wxArrayIVector4SpinnerCtrlEvent> ), 0, instance);

		return ctrl;
	}

	static wxWindow *createResourcePath		(wxWindow *topPanel, ReflectedClassPropertyPanel<ReflectClass> *instance, wxWindow *parentWnd, wxSizer *parentSizer, const PropertyDesc &propertyDesc, ReflectClass *ptr)
	{
		ResourcePath val;
		propertyDesc.get(val, ptr);
	
		wxResourcePathCtrl *ctrl = new wxResourcePathCtrl(parentWnd, wxID_ANY, 
														  propertyDesc.getName(),
														  val);

		wxBoxSizer *hBox = new wxBoxSizer(wxHORIZONTAL);
		parentSizer->Add(hBox, 0, wxRIGHT | wxBOTTOM | wxEXPAND, 4);
			hBox->Add(COLLAPSE_BUTTON_SIZE*1.5, COLLAPSE_BUTTON_SIZE, 0);
			hBox->Add(ctrl, 1, wxEXPAND);

		ctrl->Connect(wxEVT_COMMAND_RESOURCEPATH_CTRL_VALUE_CHANGED, wxResourcePathCtrlEventHandler(onGUIValueChanged<wxResourcePathCtrlEvent>), 0, instance);

		return ctrl;
	}

	static wxWindow *createVectorResourcePath(wxWindow *topPanel, ReflectedClassPropertyPanel<ReflectClass> *instance, wxWindow *parentWnd, wxSizer *parentSizer, const PropertyDesc &propertyDesc, ReflectClass *ptr)
	{
		Vector<ResourcePath> val;
		propertyDesc.get(val, ptr);

		wxArrayResourcePathCtrl *ctrl = new wxArrayResourcePathCtrl(parentWnd, wxID_ANY, 
																	propertyDesc.getName(),
																	val, 
																	topPanel);

		parentSizer->Add(ctrl, 0, wxRIGHT | wxBOTTOM | wxEXPAND, 4);

		ctrl->Connect(wxEVT_COMMAND_ARRAY_RESOURCEPATH_CTRL_VALUE_CHANGED , wxArrayResourcePathCtrlEventHandler(onGUIValueChanged<wxArrayResourcePathCtrlEvent> ), 0, instance);

		return ctrl;
	}

	static wxWindow *createSRTTransform		(wxWindow *topPanel, ReflectedClassPropertyPanel<ReflectClass> *instance, wxWindow *parentWnd, wxSizer *parentSizer, const PropertyDesc &propertyDesc, ReflectClass *ptr)
	{
		SRTTransform val;
		propertyDesc.get(val, ptr);
	
		wxSRTTransformCtrl *ctrl = new wxSRTTransformCtrl(parentWnd, wxID_ANY, 
														  propertyDesc.getName(), 
														  val, topPanel);

		parentSizer->Add(ctrl, 0, wxRIGHT | wxBOTTOM | wxEXPAND, 4);

		ctrl->Connect(wxEVT_COMMAND_SRTTRANSFORM_CTRL_VALUE_CHANGED, wxSRTTransformCtrlEventHandler(onGUIValueChanged<wxSRTTransformCtrlEvent>), 0, instance);

		return ctrl;
	}

	static wxWindow *createVectorSRTTransform(wxWindow *topPanel, ReflectedClassPropertyPanel<ReflectClass> *instance, wxWindow *parentWnd, wxSizer *parentSizer, const PropertyDesc &propertyDesc, ReflectClass *ptr)
	{
		Vector<SRTTransform> val;
		propertyDesc.get(val, ptr);

		wxArraySRTTransformCtrl *ctrl = new wxArraySRTTransformCtrl(parentWnd, wxID_ANY, 
																	propertyDesc.getName(),
																	val, 
																	topPanel);
		parentSizer->Add(ctrl, 0, wxRIGHT | wxBOTTOM | wxEXPAND, 4);

		ctrl->Connect(wxEVT_COMMAND_ARRAY_SRTTRANSFORM_CTRL_VALUE_CHANGED , wxArraySRTTransformCtrlEventHandler(onGUIValueChanged<wxArraySRTTransformCtrlEvent> ), 0, instance);

		return ctrl;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	static void (*propertyDescUpdateUIFuncs[])(wxWindow *ctrl, const PropertyDesc &propertyDesc, ReflectClass *ptr);

	template<class T, class GUIType>
	static void updateCtrl(wxWindow *ctrl, const PropertyDesc &propertyDesc, ReflectClass *ptr)
	{
		T val;
		propertyDesc.get(val, ptr);
	
		GUIType *control = (GUIType *)ctrl;
		control->setValue(val);
	}

	template<class T, class GUIType>
	static void updateVectorCtrl(wxWindow *ctrl, const PropertyDesc &propertyDesc, ReflectClass *ptr)
	{
		Vector<T> val;
		propertyDesc.get(val, ptr);
	
		GUIType *control = (GUIType *)ctrl;
		control->setLength(val.length());
		for(int i=0; i<val.length(); i++)
			control->setValue(i, val[i]);
	}
public:
protected:
private:
	ReflectClass	*reflectClass;
	wxFlexGridSizer	*subPanelSizer;
	Vector<wxWindow *> controls;
};

template <class ReflectClass>
wxWindow *(*ReflectedClassPropertyPanel<ReflectClass>::propertyDescCreateUIFuncs[])(wxWindow *topPanel, ReflectedClassPropertyPanel<ReflectClass> *instance, wxWindow *parentWnd, wxSizer *parentSizer, const PropertyDesc &propertyDesc, ReflectClass *ptr) =
{
	createBool					,
	createVectorBool			,
	createInt					,
	createVectorInt				,
	createUInt					,
	createVectorUInt			,
	createFloat					,
	createVectorFloat			,
	createDouble				,
	createVectorDouble			,
	createString				,
	createVectorString			,
	createColorRGBA				,
	createVectorColorRGBA		,
	createVector2				,
	createVectorVector2			,
	createVector3				,
	createVectorVector3			,
	createVector4				,
	createVectorVector4			,
	createIVector2				,
	createVectorIVector2		,
	createIVector3				,
	createVectorIVector3		,
	createIVector4				,
	createVectorIVector4		,
	createResourcePath			,
	createVectorResourcePath	,
	createSRTTransform			,
	createVectorSRTTransform	,
};

template <class ReflectClass>
void (*ReflectedClassPropertyPanel<ReflectClass>::propertyDescUpdateUIFuncs[])(wxWindow *ctrl, const PropertyDesc &propertyDesc, ReflectClass *ptr) =
{
	updateCtrl<bool					, wxBoolCtrl					> ,
	updateVectorCtrl<bool			, wxArrayBoolCtrl				> ,
	updateCtrl<int					, wxIntSpinnerCtrl				> ,
	updateVectorCtrl<int			, wxArrayIntSpinnerCtrl			> ,
	updateCtrl<unsigned int			, wxUIntSpinnerCtrl				> ,
	updateVectorCtrl<unsigned int	, wxArrayUIntSpinnerCtrl		> ,
	updateCtrl<float				, wxFloatSpinnerCtrl			> ,
	updateVectorCtrl<float			, wxArrayFloatSpinnerCtrl		> ,
	updateCtrl<double				, wxDoubleSpinnerCtrl			> ,
	updateVectorCtrl<double			, wxArrayDoubleSpinnerCtrl		> ,
	updateCtrl<String				, wxStringCtrl					> ,
	updateVectorCtrl<String			, wxArrayStringCtrl				> ,
	updateCtrl<ColorRGBA			, wxColorRGBACtrl				> ,
	updateVectorCtrl<ColorRGBA		, wxArrayColorRGBACtrl			> ,
	updateCtrl<Vector2				, wxVector2SpinnerCtrl			> ,
	updateVectorCtrl<Vector2		, wxArrayVector2SpinnerCtrl		> ,
	updateCtrl<Vector3				, wxVector3SpinnerCtrl			> ,
	updateVectorCtrl<Vector3		, wxArrayVector3SpinnerCtrl		> ,
	updateCtrl<Vector4				, wxVector4SpinnerCtrl			> ,
	updateVectorCtrl<Vector4		, wxArrayVector4SpinnerCtrl		> ,
	updateCtrl<IVector2				, wxIVector2SpinnerCtrl			> ,
	updateVectorCtrl<IVector2		, wxArrayIVector2SpinnerCtrl	> ,
	updateCtrl<IVector3				, wxIVector3SpinnerCtrl			> ,
	updateVectorCtrl<IVector3		, wxArrayIVector3SpinnerCtrl	> ,
	updateCtrl<IVector4				, wxIVector4SpinnerCtrl			> ,
	updateVectorCtrl<IVector4		, wxArrayIVector4SpinnerCtrl	> ,
	updateCtrl<ResourcePath			, wxResourcePathCtrl			> ,
	updateVectorCtrl<ResourcePath	, wxArrayResourcePathCtrl		> ,
	updateCtrl<SRTTransform			, wxSRTTransformCtrl			> ,
	updateVectorCtrl<SRTTransform	, wxArraySRTTransformCtrl		> ,
};

































#endif