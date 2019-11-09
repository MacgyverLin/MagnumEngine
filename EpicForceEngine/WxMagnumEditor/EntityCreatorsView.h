#ifndef _EntityCreatorsView_h_
#define _EntityCreatorsView_h_

#include "wxdef.h"
#include <MagnumEngine.h>
using namespace Magnum;

class ProjectView;

//////////////////////////////////////////////////////////////////////////////////////////////////
class EntityCreatorsView : public wxListCtrl, public ProjectViewBase
{
friend class ProjectView;
public:
	EntityCreatorsView(ProjectView *projectView_);
	~EntityCreatorsView();
protected:
private:
	void diableUI(unsigned int flags);
	void enableUI(unsigned int flags);

////////////////////////////////////////////////////////////////////////////////////////////////
// View request update Model
public:
protected:
private:
	void onBeginDrag(wxListEvent &event);

////////////////////////////////////////////////////////////////////////////////////////////////
// Model request update View
public:
protected:
private:
	virtual void notify(int flags, ProjectModelBase &projectModel, const Vector<unsigned char> &buffer);
	virtual void disableUIEvent();
	virtual void enableUIEvent();
};

#endif