///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _CheckingRawAssetsState_h_
#define _CheckingRawAssetsState_h_

#include "StateMachine.h"
using namespace Magnum;

namespace Magnum
{
	
class ProjectModel;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CheckingRawAssetsState : public State<ProjectModel>
{
public:
	CheckingRawAssetsState();
	virtual ~CheckingRawAssetsState();
	
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
class UpdatingAssetsState : public State<ProjectModel>
{
public:
	UpdatingAssetsState();
	virtual ~UpdatingAssetsState();
	
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ValidateEntitiesState : public State<ProjectModel>
{
public:
	ValidateEntitiesState();
	virtual ~ValidateEntitiesState();
	
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