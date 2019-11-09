#ifndef _DebugView_h_
#define _DebugView_h_

#include "wxdef.h"
#include <MagnumEngine.h>
using namespace Magnum;

class ProjectView;

class DebugView : public wxTextCtrl, public ProjectViewBase
{
friend class DebugViewResourceImportDropTarget;
friend class ProjectView;
public:
	DebugView(ProjectView *projectView_);
	~DebugView();
protected:
private:
	void diableUI(unsigned int flags);
	void enableUI(unsigned int flags);

	void clear();
	void infoPrint(const char *buf);
	void debugPrint(int i, const char *buf);
////////////////////////////////////////////////////////////////////////////////////////////////
// View request update Model
public:
protected:
private:
	bool onDropResourceImport(const char *path, const char *extension);

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