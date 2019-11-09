#include "ResourceImporterView.h"
#include "ResourceImportDragDrop.h"
#include "ProjectView.h"
#include "ResourceImport.h"

ResourceImporterView::ResourceImporterView(ProjectView *projectView_)
: wxTreeCtrl(projectView_, wxID_ANY,
		     wxDefaultPosition, wxDefaultSize, 
			 wxTR_DEFAULT_STYLE | wxTR_MULTIPLE | wxTR_EDIT_LABELS | wxTR_HIDE_ROOT | wxNO_BORDER)
{
	wxImageList* imglist = new wxImageList(16, 16, true, 2);
	imglist->Add(wxArtProvider::GetBitmap(wxART_FOLDER, wxART_OTHER, wxSize(16,16)));
	imglist->Add(wxArtProvider::GetBitmap(wxART_FOLDER, wxART_OTHER, wxSize(16,16)));
	
    this->SetForegroundColour(wxColour(  0,   0,   0, 255));
    this->SetBackgroundColour(wxColour(128, 128, 128, 255));
	this->Centre();
	this->AssignImageList(imglist);
	
	wxTreeItemId root = this->AddRoot(wxT(""), 0);

	enableUIEvent();
}

ResourceImporterView::~ResourceImporterView()
{
}

void ResourceImporterView::diableUI(unsigned int flags)
{
}

void ResourceImporterView::enableUI(unsigned int flags)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////
// View request update Model
void ResourceImporterView::onBeginDrag(wxTreeEvent &event)
{
	int flag = 0;
	wxTreeItemId hitItem = this->HitTest(event.GetPoint(), flag);

	if(flag & (wxTREE_HITTEST_ONITEMBUTTON | wxTREE_HITTEST_ONITEMICON | wxTREE_HITTEST_ONITEMINDENT | wxTREE_HITTEST_ONITEMLABEL) )
	{
		wxString text = this->GetItemText(hitItem);

		ResourceImport *resourceImport = (ResourceImport *)pointerTreeItemMap.find(hitItem);
		assert(resourceImport);

		ResourceImportDataObject resourceImportDataObject(resourceImport->name(), resourceImport->extension());

		wxDropSource dragSource(this);
		dragSource.SetData(resourceImportDataObject);

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
	else if(flag & wxTREE_HITTEST_NOWHERE )
	{
		event.Veto();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////
// Model request update View
void ResourceImporterView::notify(int flags, ProjectModelBase &projectModel, const Vector<unsigned char> &buffer)
{
	if(flags & ProjectModelBase::RESOURCE_IMPORTERS)
	{
		DeleteAllItems();
		pointerTreeItemMap.clear();
		wxTreeItemId root = this->AddRoot(wxT("Root Node"), 0);

		for(int i=0; i<projectModel.getNumResourceCreators(); i++)
		{
			ResourceImport::ICreator *creator = projectModel.getResourceCreators(i);

			for(int j=0; j<creator->getNumResourceImporters(); j++)
			{
				ResourceImport *resourceImport = creator->getResourceImporters(j);

				wxTreeItemId item = this->AppendItem(GetRootItem(), resourceImport->name(), wxTreeItemIcon_Normal, wxTreeItemIcon_Selected);
				assert(item.IsOk());

				pointerTreeItemMap.add(item, resourceImport);
			}
		}
	}
	if(flags & ProjectModelBase::STATE_CHANGED)
	{
	}
}

void ResourceImporterView::disableUIEvent()
{
	Disconnect(wxEVT_COMMAND_TREE_BEGIN_DRAG, wxTreeEventHandler(ResourceImporterView::onBeginDrag));
}

void ResourceImporterView::enableUIEvent()
{
	Connect(wxEVT_COMMAND_TREE_BEGIN_DRAG, wxTreeEventHandler(ResourceImporterView::onBeginDrag));
}