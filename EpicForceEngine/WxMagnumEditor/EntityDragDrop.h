#ifndef _HierarchyDragDrop_h_
#define _HierarchyDragDrop_h_

#include "wxdef.h"
#include "Array.h"
#include "EString.h"
using namespace Magnum;

class EntityDragDropDataObject : public wxDataObjectSimple
{
public:
	enum Operation
	{
		NONE,
		CHANGE_REPARENT,
		CREATE_ENTITY,
	};
    // ctor: you can specify the text here or in SetText(), or override
    // GetText()
    EntityDragDropDataObject()
	: wxDataObjectSimple("EntityDragDrop")
	, _operation(EntityDragDropDataObject::NONE)
    , _hitItem()
	, _treeCtrl(0)
	{
		memset(_entityName, 0, 2048);
	}

    EntityDragDropDataObject(const wxTreeItemId &hitItem_, wxTreeCtrl *treeCtrl_)
	: wxDataObjectSimple("EntityDragDrop")
	, _operation(CHANGE_REPARENT)
    , _hitItem(hitItem_)
	, _treeCtrl(treeCtrl_)
	{
		memset(_entityName, 0, 2048);
	}

    EntityDragDropDataObject(const char *entityName_)
	: wxDataObjectSimple("EntityDragDrop")
	, _operation(CREATE_ENTITY)
    , _hitItem()
	, _treeCtrl(0)
	{
		assert( strlen(entityName_)<2048);

		strncpy(_entityName, entityName_, 2048);
	}

    // virtual functions which you may override if you want to provide text on
    // demand only - otherwise, the trivial default versions will be used
    virtual size_t getSize() const 
	{ 
		return sizeof(_operation) + sizeof(_hitItem) + sizeof(_treeCtrl) + sizeof(_entityName);
	}

	virtual EntityDragDropDataObject::Operation getOperation() const { return _operation; }

    virtual const wxTreeItemId &getItem() const { return _hitItem; }
	virtual wxTreeItemId &getItem() { return _hitItem; }
    
	virtual const wxTreeCtrl *getTreeCtrl() const { return _treeCtrl; }
	virtual wxTreeCtrl *getTreeCtrl() { return _treeCtrl; }

	virtual const char *getEntityName() const { return _entityName; }

    virtual void setItem(const wxTreeItemId &hitItem_) { _hitItem = hitItem_; }
	virtual void setTreeCtrl(wxTreeCtrl *treeCtrl_) { _treeCtrl = treeCtrl_; }
	virtual void setEntityName(const char *entityName_) 
	{
		assert( strlen(entityName_)<2048);

		strncpy(_entityName, entityName_, 2048);
	}

    // implement base class pure virtuals
    // ----------------------------------

    // some platforms have 2 and not 1 format for text data
    virtual size_t GetDataSize() const;
    virtual bool GetDataHere(void *buf) const;
    virtual bool SetData(size_t len, const void *buf);
    // Must provide overloads to avoid hiding them (and warnings about it)
    virtual size_t GetDataSize(const wxDataFormat&) const
    {
        return GetDataSize();
    }
    virtual bool GetDataHere(const wxDataFormat&, void *buf) const
    {
        return GetDataHere(buf);
    }
    virtual bool SetData(const wxDataFormat&, size_t len, const void *buf)
    {
        return SetData(len, buf);
    }

private:
	EntityDragDropDataObject::Operation		_operation;
    wxTreeItemId							_hitItem;
	wxTreeCtrl								*_treeCtrl;
	char									_entityName[2048];

    DECLARE_NO_COPY_CLASS(EntityDragDropDataObject)
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
class EntityDropTarget : public wxDropTarget
{
public:
    EntityDropTarget();

    virtual wxDragResult OnData(wxCoord x, wxCoord y, wxDragResult def);

	virtual bool onCreateEntity(const wxPoint &position, const char *entityClassName)
	{
		return true; 
	};

	virtual bool onChangedParent(const wxTreeItemId &newParentItemId, const wxTreeItemId &oldParentItemId, const wxTreeItemId &childItemId)
	{
		return true; 
	};
private:
	bool isDestMyChildren(wxTreeCtrl *treeCtrl, const wxTreeItemId &destItem, const wxTreeItemId &srcItem);
	bool isDestMyDirectParent(wxTreeCtrl *treeCtrl, const wxTreeItemId &destItem, const wxTreeItemId &srcItem);

	DECLARE_NO_COPY_CLASS(EntityDropTarget)
};

#endif