#ifndef _MiscBToolBarView_h_
#define _MiscBToolBarView_h_

#include "wxdef.h"
#include "Array.h"
#include "EString.h"
#include "MenuCommand.h"
#include "ProjectModelViewBase.h"
using namespace Magnum;

class ProjectView;

class MiscBToolBarView : public wxAuiToolBar, public ProjectViewBase
{
friend class ProjectView;
public:
	MiscBToolBarView(ProjectView *projectView_);
	~MiscBToolBarView();
protected:
private:
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

////////////////////////////////////////////////////////////////////////////////////////////////
public:
protected:
private:
	wxComboBox *coordSysComboBox;
};

#endif