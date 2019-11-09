#ifndef _ResourceImporterView_h_
#define _ResourceImporterView_h_

#include "wxdef.h"
#include "Array.h"
#include "EString.h"
#include "Vector3.h"
#include "PointerTreeItemMap.h"
#include <map>
#include <MagnumEngine.h>
using namespace Magnum;

class ProjectView;

class ResourceImporterView : public wxTreeCtrl, public ProjectViewBase
{
friend class ProjectView;
public:
	ResourceImporterView(ProjectView *projectView_);
	~ResourceImporterView();
protected:
private:
	void diableUI(unsigned int flags);
	void enableUI(unsigned int flags);
////////////////////////////////////////////////////////////////////////////////////////////////
// View request update Model
public:
protected:
private:
	void onBeginDrag(wxTreeEvent &event);

////////////////////////////////////////////////////////////////////////////////////////////////
// Model request update View
public:
protected:
private:
	virtual void notify(int flags, ProjectModelBase &projectModel, const Vector<unsigned char> &buffer);
	virtual void disableUIEvent();
	virtual void enableUIEvent();
////////////////////////////////////////////////////////////
public:
protected:
private:
	PointerTreeItemMap<ResourceImport> pointerTreeItemMap;
};

#endif