#ifndef _EntityPanel_h_
#define _EntityPanel_h_

#include "wxdef.h"
#include "wxCollapsePanelCtrl.h"
#include "wxBoolCtrl.h"
#include "wxArrayBoolCtrl.h"
#include "wxIntSpinnerCtrl.h"
#include "wxArrayIntSpinnerCtrl.h"
#include "wxUIntSpinnerCtrl.h"
#include "wxArrayUIntSpinnerCtrl.h"
#include "wxFloatSpinnerCtrl.h"
#include "wxArrayFloatSpinnerCtrl.h"
#include "wxDoubleSpinnerCtrl.h"
#include "wxArrayDoubleSpinnerCtrl.h"
#include "wxColorRGBACtrl.h"
#include "wxArrayColorRGBACtrl.h"
#include "wxStringCtrl.h"
#include "wxArrayStringCtrl.h"
#include "wxIVector2SpinnerCtrl.h"
#include "wxArrayIVector2SpinnerCtrl.h"
#include "wxIVector3SpinnerCtrl.h"
#include "wxArrayIVector3SpinnerCtrl.h"
#include "wxIVector4SpinnerCtrl.h"
#include "wxArrayIVector4SpinnerCtrl.h"
#include "wxVector2SpinnerCtrl.h"
#include "wxArrayVector2SpinnerCtrl.h"
#include "wxVector3SpinnerCtrl.h"
#include "wxArrayVector3SpinnerCtrl.h"
#include "wxVector4SpinnerCtrl.h"
#include "wxArrayVector4SpinnerCtrl.h"
#include "wxResourcePathCtrl.h"
#include "wxArrayResourcePathCtrl.h"
#include "wxLabelCtrl.h"
#include "ReflectedClassPropertyPanel.h"
#include <MagnumEngine.h>
using namespace Magnum;

class ProjectView;

class EntityPanel : public wxPanel, public ProjectViewBase
{
friend class ProjectView;
public:
	EntityPanel(wxScrolledWindow *parent_, Entity *entity_);
	virtual ~EntityPanel();
protected:
private:
	void updateEntityNameUI();
	void updateEntityTransformUI();
	void updateUI();
	void createUI();
	void destroyUI();

	void diableUI(unsigned int flags);
	void enableUI(unsigned int flags);
////////////////////////////////////////////////////////////////////////////////////////////////
// View request update Model
public:
protected:
private:
	void onSize(ReflectedClassPropertyPanelEvent &evt);
	void onCollapsePanelChanged(ReflectedClassPropertyPanelEvent &evt);
	void onNameChanged(ReflectedClassPropertyPanelEvent &evt);
	void onTransformChanged(ReflectedClassPropertyPanelEvent &evt);
	void onValueChanged(ReflectedClassPropertyPanelEvent &evt);
////////////////////////////////////////////////////////////////////////////////////////////////
// Model request update View
public:
protected:
private:
	virtual void notify(int flags, ProjectModelBase &projectModel, const Vector<unsigned char> &buffer);
	virtual void disableUIEvent();
	virtual void enableUIEvent();
public:
protected:
private:
	wxScrolledWindow *parent;
	
	Entity *entity;

	ReflectedClassPropertyPanel<Entity> *entitySubPanel;
	Vector<ReflectedClassPropertyPanel<Component> *> componentSubPanels;
};

#endif