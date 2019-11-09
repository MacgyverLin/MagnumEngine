///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _BuildMenuState_h_
#define _BuildMenuState_h_

#include "StateMachine.h"
using namespace Magnum;

namespace Magnum
{
	
class ProjectModel;

class BuildMenuState : public State<ProjectModel>
{
public:
	BuildMenuState();
	virtual ~BuildMenuState();
	
	virtual void onEnter(ProjectModel &projectModel);
	virtual void onExit(ProjectModel &projectModel);

	virtual void onUpdate(ProjectModel &projectModel, float dt);
	virtual void onPause(ProjectModel &projectModel);
	virtual void onResume(ProjectModel &projectModel);
	virtual void onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt);
	virtual void onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt);
	virtual void onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt);
	virtual void onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt);
protected:
private:
};

};

#endif