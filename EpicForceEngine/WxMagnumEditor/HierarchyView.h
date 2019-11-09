#ifndef _HierarchyView_h_
#define _HierarchyView_h_

#include "wxdef.h"
#include "Array.h"
#include "EString.h"
#include "Vector3.h"
#include "Entity.h"
#include "PointerTreeItemMap.h"
#include <map>
#include <MagnumEngine.h>
using namespace Magnum;

class ProjectView;

////////////////////////////////////////////////////////////////////////////////////////////////
class HierarchyView : public wxTreeCtrl, public ProjectViewBase
{
friend class HierarchyViewEntityDropTarget;
friend class ProjectView;
public:
	HierarchyView(ProjectView *projectView_);
	~HierarchyView();
protected:
private:
	void createItemRecursive(const wxTreeItemId &parentItemId, Entity *entity);

	void diableUI(unsigned int flags);
	void enableUI(unsigned int flags);
////////////////////////////////////////////////////////////////////////////////////////////////
// View request update Model
public:
protected:
private:
	void onCreateEntity(const wxPoint &position, const char *entityClassName);
	void onChangedParent(const wxTreeItemId &newParentItemId, const wxTreeItemId &oldParentItemId,
						 const wxTreeItemId &childItemId);
	
	void onMenu(wxTreeEvent &event);
	void onBeginLabelEdit(wxTreeEvent &event);
	void onEndLabelEdit(wxTreeEvent &event);
	void onDeleteItem(wxTreeEvent &event);
	void onItemSelChanged(wxTreeEvent &event);
	void onItemRightClicked(wxTreeEvent &event);
	void onKeyDown(wxTreeEvent &event);
	void onBeginDrag(wxTreeEvent &event);
	void onEndDrag(wxTreeEvent &event);

	void onSize(wxSizeEvent &event);
////////////////////////////////////////////////////////////////////////////////////////////////
// Model request update View
public:
protected:
private:
	virtual void notify(int flags, ProjectModelBase &projectModel, const Vector<unsigned char> &buffer);
	virtual void disableUIEvent();
	virtual void enableUIEvent();
////////////////////////////////////////////////////////////////////////////////////////////////
public:
protected:
private:
	PointerTreeItemMap<Entity> pointerTreeItemMap;
};

#endif