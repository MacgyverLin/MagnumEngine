#ifndef _InspectorView_h_
#define _InspectorView_h_

#include "wxdef.h"
#include "Array.h"
#include "EString.h"
#include <MagnumEngine.h>
#include "EntityPanel.h"
using namespace Magnum;

class ProjectView;

class InspectorView : public wxScrolledWindow, public ProjectViewBase
{
friend class ProjectView;
public:
	InspectorView(ProjectView *projectView_);
	virtual ~InspectorView();
protected:
private:
	void createEntityPanel(Entity *entity);
	
	void diableUI(unsigned int flags);
	void enableUI(unsigned int flags);
////////////////////////////////////////////////////////////////////////////////////////////////
// View request update Model
public:
protected:
private:

////////////////////////////////////////////////////////////////////////////////////////////////
// Model request update View
public:
protected:
private:
	virtual void notify(int flags, ProjectModelBase &projectModel, const Vector<unsigned char> &buffer);
	virtual void disableUIEvent();
	virtual void enableUIEvent();

	EntityPanel *entityPanel;
};

#endif