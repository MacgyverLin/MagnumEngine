#include "EntityDragDrop.h"

size_t EntityDragDropDataObject::GetDataSize() const
{
    return getSize();
}

bool EntityDragDropDataObject::GetDataHere(void *buf_) const
{
	memcpy( (char*)buf_, &_operation, getSize() );

    return true;
}

bool EntityDragDropDataObject::SetData(size_t WXUNUSED(len), const void *buf_)
{
	memcpy( &_operation, (char*)buf_, getSize() );

    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
EntityDropTarget::EntityDropTarget()
{
    SetDataObject(new EntityDragDropDataObject());
}

wxDragResult EntityDropTarget::OnData(wxCoord x, wxCoord y, wxDragResult def)
{
    if ( !GetData() )
        return wxDragNone;

    EntityDragDropDataObject *dobj = (EntityDragDropDataObject *)m_dataObject;

	if(dobj->getOperation()==EntityDragDropDataObject::CHANGE_REPARENT)
	{
		wxTreeCtrl *treeCtrl = dobj->getTreeCtrl();
		int flag = 0;
		wxTreeItemId destItem = treeCtrl->HitTest(wxPoint(x, y), flag);
		wxTreeItemId srcItem  = dobj->getItem();
		if(srcItem==destItem)										// if dest is myself, can't be my parent, no response
			return wxDragNone;

		if(isDestMyChildren(treeCtrl, destItem, srcItem))			// if dest is my child, can't be my parent, no response
			return wxDragNone;

		if(isDestMyDirectParent(treeCtrl, destItem, srcItem))		// if dest is my parent already, no response
			return wxDragNone;	

		if(flag & (wxTREE_HITTEST_ONITEMBUTTON | wxTREE_HITTEST_ONITEMICON | wxTREE_HITTEST_ONITEMINDENT | wxTREE_HITTEST_ONITEMLABEL) )
		{
			wxTreeItemId childItem			= dobj->getItem();
			wxTreeItemId oldParentItem		= treeCtrl->GetItemParent(childItem);
			wxTreeItemId newParentItem		= destItem;

			return onChangedParent(newParentItem, oldParentItem, childItem) ? def : wxDragNone;
		}
		else
		{
			wxTreeItemId childItem			= dobj->getItem();
			wxTreeItemId oldParentItem		= treeCtrl->GetItemParent(childItem);
			wxTreeItemId newParentItem		= treeCtrl->GetRootItem();

			return onChangedParent(newParentItem, oldParentItem, childItem) ? def : wxDragNone;
		}
	}
	else if(dobj->getOperation()==EntityDragDropDataObject::CREATE_ENTITY)
	{
		return onCreateEntity(wxPoint(x, y), dobj->getEntityName()) ? def : wxDragNone;
	}
	else
	{
		return wxDragNone;
	}
}

bool EntityDropTarget::isDestMyChildren(wxTreeCtrl *treeCtrl, const wxTreeItemId &destItem, const wxTreeItemId &srcItem)
{
	wxTreeItemIdValue cookie;
	wxTreeItemId search;
	wxTreeItemId child = treeCtrl->GetFirstChild(srcItem, cookie);

	while( child.IsOk() )
	{
		if(destItem==child)
			return true;

		if(isDestMyChildren(treeCtrl, destItem, child))
			return true;

		child = treeCtrl->GetNextChild(srcItem, cookie);
	}

	return false;
}

bool EntityDropTarget::isDestMyDirectParent(wxTreeCtrl *treeCtrl, const wxTreeItemId &destItem, const wxTreeItemId &srcItem)
{
	wxTreeItemId search;
	wxTreeItemId parent = treeCtrl->GetItemParent(srcItem);

	if( !parent.IsOk() )
		return false;

	if(destItem==parent)
		return true;

	return false;
}