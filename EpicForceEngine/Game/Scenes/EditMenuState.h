///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _EditMenuState_h_
#define _EditMenuState_h_

#include "StateMachine.h"
using namespace Magnum;

namespace Magnum
{
	
class ProjectModel;

class EditCutState : public State<ProjectModel>
{
public:
	EditCutState();
	virtual ~EditCutState();
	
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

class EditCopyState : public State<ProjectModel>
{
public:
	EditCopyState();
	virtual ~EditCopyState();
	
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

class EditPasteState : public State<ProjectModel>
{
public:
	EditPasteState();
	virtual ~EditPasteState();
	
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

class EditDuplicateState : public State<ProjectModel>
{
public:
	EditDuplicateState();
	virtual ~EditDuplicateState();
	
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

class EditDeleteState : public State<ProjectModel>
{
public:
	EditDeleteState();
	virtual ~EditDeleteState();
	
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