#include "EntityCreatorsView.h"
#include "EntityDragDrop.h"
#include "ProjectView.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
EntityCreatorsView::EntityCreatorsView(ProjectView *projectView_)
: wxListCtrl((wxFrame *)projectView_, wxID_ANY,
		     wxPoint(0, 0), wxSize(320, 240),
			 wxLC_REPORT | wxLC_NO_HEADER | wxNO_BORDER | wxLC_SINGLE_SEL)
{
	wxImageList* imglist = new wxImageList(16, 16, true, 2);
	imglist->Add(wxArtProvider::GetBitmap(wxART_FOLDER, wxART_OTHER, wxSize(16,16)));
	imglist->Add(wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16,16)));

    this->SetForegroundColour(wxColour(  0,   0,   0, 255));
    this->SetBackgroundColour(wxColour(128, 128, 128, 255));
	this->Centre();
	this->AssignImageList(imglist, 0);

	wxListItem info;
	this->InsertColumn(0, info);
	this->SetColumnWidth(0, 320);

	enableUIEvent();
}

EntityCreatorsView::~EntityCreatorsView()
{
}

void EntityCreatorsView::diableUI(unsigned int flags)
{
}

void EntityCreatorsView::enableUI(unsigned int flags)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////
// View request update Model
void EntityCreatorsView::onBeginDrag(wxListEvent &event)
{
	String createName = this->GetItemText(event.GetIndex());
	EntityDragDropDataObject entityDragDropDataObject(createName);

	wxDropSource dragSource(this);
	dragSource.SetData(entityDragDropDataObject);

	wxDragResult result = dragSource.DoDragDrop(wxDrag_CopyOnly);
	switch (result)
	{
		case wxDragError:
			// error prevented the d&d operation from completing
		break;
		case wxDragNone:
			// drag target didn't accept the data
		break;
	    case wxDragCopy: 
			// copy the data
		break;
	    case wxDragMove: 
			// move the data
		break;
		case wxDragLink:
			// operation is a drag-link
		break;
		case wxDragCancel:
			// the operation was cancelled by user (not an error)
	    break;
	};
}

////////////////////////////////////////////////////////////////////////////////////////////////
// Model request update View
void EntityCreatorsView::notify(int flags, ProjectModelBase &projectModel, const Vector<unsigned char> &buffer)
{
	if(flags & ProjectModelBase::ENTITIY_CREATORS)
	{
		DeleteAllItems();

		for(int i=0; i<projectModel.getNumEntityCreators(true); i++)
		{
			Entity::ICreator *creator = projectModel.getEntityCreators(i);
			
			const char *entityCreatorName = creator->getClassPath();

			if( String(entityCreatorName)!="EditorEntity" )
				InsertItem(0, entityCreatorName);
		}
	}
	if(flags & ProjectModelBase::STATE_CHANGED)
	{
	}
}

void EntityCreatorsView::disableUIEvent()
{
	Disconnect(wxEVT_COMMAND_LIST_BEGIN_DRAG, wxListEventHandler(EntityCreatorsView::onBeginDrag));
}

void EntityCreatorsView::enableUIEvent()
{
	Connect(wxEVT_COMMAND_LIST_BEGIN_DRAG, wxListEventHandler(EntityCreatorsView::onBeginDrag));
}