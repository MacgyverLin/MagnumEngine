#ifndef _SceneView_h_
#define _SceneView_h_

#include "wxdef.h"
#include <MagnumEngine.h>
using namespace Magnum;

class ProjectView;

class SceneView : public wxScrolledWindow, public ProjectViewBase
{
friend class SceneViewEntityDropTarget;
friend class ProjectView;
public:
	SceneView(ProjectView *projectView_);
	~SceneView();

	void updateFocus();
protected:
private:
	void diableUI(unsigned int flags);
	void enableUI(unsigned int flags);
////////////////////////////////////////////////////////////////////////////////////////////////
// View request update Model
public:
protected:
private:
	void onCreateEntity(const wxPoint &position, const char *entityClassName);
	void onMouseDown(wxMouseEvent& evt);
	void onMouseUp(wxMouseEvent& evt);
	void onMouseMotion(wxMouseEvent& evt);
	void onMouseWheel(wxMouseEvent& evt);

	void onMouseCaptureLost(wxMouseCaptureLostEvent& evt);
	void onFocusEvent(wxFocusEvent &evt);
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
	ProjectView *projectView;
};

#endif