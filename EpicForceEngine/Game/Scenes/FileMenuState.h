///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _FileMenuState_h_
#define _FileMenuState_h_

#include "StateMachine.h"
using namespace Magnum;

namespace Magnum
{
	
class ProjectModel;

///////////////////////////////////////////////////////////////////////////////////////////////////
class FileProjectNewState : public State<ProjectModel>
{
public:
	FileProjectNewState();
	virtual ~FileProjectNewState();
	
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

///////////////////////////////////////////////////////////////////////////////////////////////////
class FileProjectOpenState : public State<ProjectModel>
{
public:
	FileProjectOpenState();
	virtual ~FileProjectOpenState();
	
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

///////////////////////////////////////////////////////////////////////////////////////////////////
class FileProjectSaveState : public State<ProjectModel>
{
public:
	FileProjectSaveState();
	virtual ~FileProjectSaveState();
	
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

///////////////////////////////////////////////////////////////////////////////////////////////////
class FileSceneNewState : public State<ProjectModel>
{
public:
	FileSceneNewState();
	virtual ~FileSceneNewState();
	
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

///////////////////////////////////////////////////////////////////////////////////////////////////
class FileSceneOpenState : public State<ProjectModel>
{
public:
	FileSceneOpenState();
	virtual ~FileSceneOpenState();
	
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

///////////////////////////////////////////////////////////////////////////////////////////////////
class FileSceneSaveState : public State<ProjectModel>
{
public:
	FileSceneSaveState();
	virtual ~FileSceneSaveState();
	
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

///////////////////////////////////////////////////////////////////////////////////////////////////
class FileSceneSaveAsState : public State<ProjectModel>
{
public:
	FileSceneSaveAsState();
	virtual ~FileSceneSaveAsState();
	
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

///////////////////////////////////////////////////////////////////////////////////////////////////
class FileSceneDeleteState : public State<ProjectModel>
{
public:
	FileSceneDeleteState();
	virtual ~FileSceneDeleteState();
	
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

///////////////////////////////////////////////////////////////////////////////////////////////////
class FilePrefabOpenState : public State<ProjectModel>
{
public:
	FilePrefabOpenState();
	virtual ~FilePrefabOpenState();
	
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

///////////////////////////////////////////////////////////////////////////////////////////////////
class FilePrefabSaveState : public State<ProjectModel>
{
public:
	FilePrefabSaveState();
	virtual ~FilePrefabSaveState();
	
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

class FileExitState : public State<ProjectModel>
{
public:
	FileExitState();
	virtual ~FileExitState();
	
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