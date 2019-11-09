#include "HierarchyView.h"
#include "EntityDragDrop.h"
#include "ProjectView.h"

////////////////////////////////////////////////////////////////////////////////////////////////
class HierarchyViewEntityDropTarget : public EntityDropTarget
{
public:
	HierarchyViewEntityDropTarget(HierarchyView *view_)
	: view(view_)
	{
	}

	virtual bool onCreateEntity(const wxPoint &position, const char *entityClassName)
	{
		view->onCreateEntity(position, entityClassName);

		return true;
	}

	virtual bool onChangedParent(const wxTreeItemId &newParentItemId, const wxTreeItemId &oldParentItemId,
								 const wxTreeItemId &childItemId)
	{
		view->onChangedParent(newParentItemId, oldParentItemId, childItemId);

		return true;
	}
private:
	HierarchyView *view;
};

////////////////////////////////////////////////////////////////////////////////////////////
HierarchyView::HierarchyView(ProjectView *projectView_)
: wxTreeCtrl(projectView_, wxID_ANY,
			  wxDefaultPosition, wxDefaultSize, 
			  wxTR_TWIST_BUTTONS | wxTR_DEFAULT_STYLE | wxTR_HIDE_ROOT | /*wxTR_MULTIPLE |*/
			  wxNO_BORDER | wxTR_EDIT_LABELS)
{
	////////////////////////////////////////////////
	// initialize
	wxImageList* imglist = new wxImageList(16, 16, true, 2);
	imglist->Add(wxArtProvider::GetBitmap(wxART_FOLDER, wxART_OTHER, wxSize(16,16)));
	imglist->Add(wxArtProvider::GetBitmap(wxART_FOLDER_OPEN, wxART_OTHER, wxSize(16,16)));
	imglist->Add(wxArtProvider::GetBitmap(wxART_GO_BACK, wxART_OTHER, wxSize(16,16)));
		
    this->SetForegroundColour(wxColour(  0,   0,   0, 255));
    this->SetBackgroundColour(wxColour(128, 128, 128, 255));
	this->SetMinSize(wxSize(320, 640));
	this->Centre();
	this->AssignImageList(imglist);
	this->AddRoot(wxT("Scene Root"), 1);
	
	////////////////////////////////////////////////
	// event
	HierarchyViewEntityDropTarget *dropTarget = new HierarchyViewEntityDropTarget(this);
	this->SetDropTarget(dropTarget);

	enableUIEvent();
}

HierarchyView::~HierarchyView()
{
}

void HierarchyView::diableUI(unsigned int flags)
{
}

void HierarchyView::enableUI(unsigned int flags)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////
// member function
void HierarchyView::createItemRecursive(const wxTreeItemId &parentItemId, Entity *entity)
{
	wxTreeItemId itemId = this->AppendItem(parentItemId, entity->getName().text(), wxTreeItemIcon_Normal, wxTreeItemIcon_Selected);
	assert(itemId.IsOk());
	pointerTreeItemMap.add(itemId, entity);

	for(int i=0; i<entity->getNumChildren(); i++)
	{
		Entity *child = (Entity *)entity->getChild(i);

		createItemRecursive(itemId, child);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////
// View request update Model
void HierarchyView::onCreateEntity(const wxPoint &position, const char *entityClassName)
{
	ProjectModelBase &model = this->getModel();
	Entity *entity = model.createEntity(entityClassName, 0, Vector3::ZERO);

	//wxTreeItemId item = this->AppendItem(GetRootItem(), entity->getName(), wxTreeItemIcon_Normal, wxTreeItemIcon_Selected);
	//assert(item.IsOk());
	//pointerTreeItemMap.add(item, entity);
}

void HierarchyView::onChangedParent(const wxTreeItemId &newParentItemId, const wxTreeItemId &oldParentItemId,
									const wxTreeItemId &childItemId)
{
	Entity *newParentEntity	= pointerTreeItemMap.find(newParentItemId);
	Entity *oldParentEntity	= pointerTreeItemMap.find(oldParentItemId);
	Entity *childEntity		= pointerTreeItemMap.find(childItemId);

	//wxTreeItemId nodeItemIdCopy = moveItem(newParentItemId, childItemId);
	//ExpandAllChildren(nodeItemIdCopy);
	ProjectModelBase &model = this->getModel();
	model.changeParent(newParentEntity, oldParentEntity, childEntity);
}

void HierarchyView::onMenu(wxTreeEvent &event)
{
	wxMenu menu; 
	
	menu.Append(wxID_OPEN, wxT("Open")); 
	PopupMenu(&menu, wxDefaultPosition); 
}

void HierarchyView::onBeginLabelEdit(wxTreeEvent &event)
{
}

void HierarchyView::onEndLabelEdit(wxTreeEvent &evt)
{
	wxTreeItemId selectedItem = this->GetSelection();
	if(selectedItem.IsOk())
	{
		wxString oldName	= this->GetItemText(selectedItem);
		wxString newName	= evt.GetLabel();
		if(!evt.IsEditCancelled() && newName!="")
		{
			Entity *entity					= pointerTreeItemMap.find(selectedItem);
			assert(entity);

			ProjectModelBase &model			= getModel();
			model.setEntityName(entity, newName.c_str());
		}
	}
}

void HierarchyView::onDeleteItem(wxTreeEvent &evt)
{
}

void HierarchyView::onItemSelChanged(wxTreeEvent &evt)
{
	wxTreeItemId oldSelectedItem		= evt.GetOldItem();
	wxTreeItemId newSelectedItem		= evt.GetItem();
	if(newSelectedItem.IsOk())
	{
		Entity *oldSelectEntity		= pointerTreeItemMap.find(oldSelectedItem);
		Entity *newSelectEntity		= pointerTreeItemMap.find(newSelectedItem);
		
		if(oldSelectEntity!=newSelectEntity)
		{
			ProjectModelBase &model			= getModel();
			model.selectEntity(newSelectEntity);
		}
	}
}

void HierarchyView::onItemRightClicked(wxTreeEvent &event)
{
}

void HierarchyView::onKeyDown(wxTreeEvent &event)
{
	switch(event.GetKeyCode())
	{
		case WXK_DELETE:
		{
			wxTreeItemId selectedItem = this->GetSelection();
			
			if(selectedItem.IsOk())
			{
				Entity *entity					= pointerTreeItemMap.find(selectedItem);
				assert(entity);

				ProjectModelBase &model			= getModel();
				model.releaseEntity(entity);
			}
		}
		break;
	};
}

void HierarchyView::onBeginDrag(wxTreeEvent &event)
{
	int flag = 0;
	wxTreeItemId hitItem = this->HitTest(event.GetPoint(), flag);

	if(flag & (wxTREE_HITTEST_ONITEMBUTTON | wxTREE_HITTEST_ONITEMICON | wxTREE_HITTEST_ONITEMINDENT | wxTREE_HITTEST_ONITEMLABEL) )
	{
		wxString text = this->GetItemText(hitItem);

		EntityDragDropDataObject entityDragDropDataObject(hitItem, this);

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
	else if(flag & wxTREE_HITTEST_NOWHERE )
	{
		event.Veto();
	}
}

void HierarchyView::onEndDrag(wxTreeEvent &evt)
{
}

void HierarchyView::onSize(wxSizeEvent &evt)
{
	this->Fit();
}

////////////////////////////////////////////////////////////////////////////////////////////////
// Model request update View
void HierarchyView::notify(int flags, ProjectModelBase &projectModel, const Vector<unsigned char> &buffer)
{
	if(flags & ProjectModelBase::HIERARCHY_VIEW)
	{
		DeleteAllItems();
		pointerTreeItemMap.clear();
		wxTreeItemId root = this->AddRoot(wxT("Root Node"), 0);

		Vector<Entity *> topLevelEntities;
		projectModel.collectTopLevelEntity(topLevelEntities, false);

		for(int i=0; i<topLevelEntities.length(); i++)
			createItemRecursive(this->GetRootItem(), topLevelEntities[i]);

		this->Refresh();
	}
	if(flags & ProjectModelBase::SELECTED_ENTITY_NAME_CHANGED)
	{
		Entity *selectedEntity	= projectModel.getSelectedEntity();
		if(selectedEntity)
		{
			wxTreeItemId selectedEntityItemID	= pointerTreeItemMap.find(selectedEntity);
			assert(selectedEntityItemID.IsOk());

			this->SetItemText(selectedEntityItemID, wxString(selectedEntity->getName()));

			this->Refresh();
		}
	}
	if(flags & ProjectModelBase::HIERARCHY_SELECTION_CHANGED)
	{
		Entity *newSelectedEntity				= projectModel.getSelectedEntity();
		if(newSelectedEntity)
		{
			wxTreeItemId selectedEntityItemID	= pointerTreeItemMap.find(newSelectedEntity);
			assert(selectedEntityItemID.IsOk());

			this->SelectItem(selectedEntityItemID);

			this->Refresh();
		}
	}
	if(flags & ProjectModelBase::STATE_CHANGED)
	{
	}
}

void HierarchyView::disableUIEvent()
{
	this->Disconnect(wxEVT_COMMAND_TREE_ITEM_MENU			, wxTreeEventHandler(HierarchyView::onMenu					)	);
	this->Disconnect(wxEVT_COMMAND_TREE_BEGIN_LABEL_EDIT	, wxTreeEventHandler(HierarchyView::onBeginLabelEdit		)	);
	this->Disconnect(wxEVT_COMMAND_TREE_END_LABEL_EDIT		, wxTreeEventHandler(HierarchyView::onEndLabelEdit			)	);
	this->Disconnect(wxEVT_COMMAND_TREE_DELETE_ITEM			, wxTreeEventHandler(HierarchyView::onDeleteItem			)	);
	this->Disconnect(wxEVT_COMMAND_TREE_SEL_CHANGED			, wxTreeEventHandler(HierarchyView::onItemSelChanged		)	);
	this->Disconnect(wxEVT_COMMAND_TREE_ITEM_RIGHT_CLICK	, wxTreeEventHandler(HierarchyView::onItemRightClicked		)	);
	this->Disconnect(wxEVT_COMMAND_TREE_KEY_DOWN			, wxTreeEventHandler(HierarchyView::onKeyDown				)	);
	this->Disconnect(wxEVT_COMMAND_TREE_BEGIN_DRAG			, wxTreeEventHandler(HierarchyView::onBeginDrag				)	);
	this->Disconnect(wxEVT_COMMAND_TREE_END_DRAG			, wxTreeEventHandler(HierarchyView::onEndDrag				)	);

	this->Disconnect(wxEVT_SIZE								, wxSizeEventHandler(HierarchyView::onSize					)	);
}

void HierarchyView::enableUIEvent()
{
	this->Connect(wxEVT_COMMAND_TREE_ITEM_MENU				, wxTreeEventHandler(HierarchyView::onMenu					)	);
	this->Connect(wxEVT_COMMAND_TREE_BEGIN_LABEL_EDIT		, wxTreeEventHandler(HierarchyView::onBeginLabelEdit		)	);
	this->Connect(wxEVT_COMMAND_TREE_END_LABEL_EDIT			, wxTreeEventHandler(HierarchyView::onEndLabelEdit			)	);
	this->Connect(wxEVT_COMMAND_TREE_DELETE_ITEM			, wxTreeEventHandler(HierarchyView::onDeleteItem			)	);
	this->Connect(wxEVT_COMMAND_TREE_SEL_CHANGED			, wxTreeEventHandler(HierarchyView::onItemSelChanged		)	);
	this->Connect(wxEVT_COMMAND_TREE_ITEM_RIGHT_CLICK		, wxTreeEventHandler(HierarchyView::onItemRightClicked		)	);
	this->Connect(wxEVT_COMMAND_TREE_KEY_DOWN				, wxTreeEventHandler(HierarchyView::onKeyDown				)	);
	this->Connect(wxEVT_COMMAND_TREE_BEGIN_DRAG				, wxTreeEventHandler(HierarchyView::onBeginDrag				)	);
	this->Connect(wxEVT_COMMAND_TREE_END_DRAG				, wxTreeEventHandler(HierarchyView::onEndDrag				)	);

	this->Connect(wxEVT_SIZE								 , wxSizeEventHandler(HierarchyView::onSize					)	);
}