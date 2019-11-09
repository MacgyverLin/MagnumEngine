///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "FileMenuState.h"
#include "ProjectModel.h"
using namespace Magnum;

///////////////////////////////////////////////////////////////////////////////////////////////////
FileProjectNewState::FileProjectNewState() : State<ProjectModel>()
{
}

FileProjectNewState::~FileProjectNewState()
{
}

void FileProjectNewState::onEnter(ProjectModel &projectModel)
{
	projectModel.fileProjectNew(projectModel.getCurrentProjectPath());
}

void FileProjectNewState::onExit(ProjectModel &projectModel){}

void FileProjectNewState::onUpdate(ProjectModel &projectModel, float dt)
{
	//projectModel.revertToPreviousState();
	projectModel.changeState("CheckingRawAssets");
}

void FileProjectNewState::onPause(ProjectModel &projectModel){}
void FileProjectNewState::onResume(ProjectModel &projectModel){}
void FileProjectNewState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt){}
void FileProjectNewState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt){}
void FileProjectNewState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt){}
void FileProjectNewState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt){}

///////////////////////////////////////////////////////////////////////////////////////////////////
FileProjectOpenState::FileProjectOpenState(){}
FileProjectOpenState::~FileProjectOpenState(){}
	
void FileProjectOpenState::onEnter(ProjectModel &projectModel)
{
	projectModel.fileProjectOpen(projectModel.getCurrentProjectPath());
}

void FileProjectOpenState::onExit(ProjectModel &projectModel){}

void FileProjectOpenState::onUpdate(ProjectModel &projectModel, float dt)
{
	//projectModel.revertToPreviousState();
	projectModel.changeState("CheckingRawAssets");
}

void FileProjectOpenState::onPause(ProjectModel &projectModel){}
void FileProjectOpenState::onResume(ProjectModel &projectModel){}
void FileProjectOpenState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt){}
void FileProjectOpenState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt){}
void FileProjectOpenState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt){}
void FileProjectOpenState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt){}

///////////////////////////////////////////////////////////////////////////////////////////////////
FileProjectSaveState::FileProjectSaveState(){}
FileProjectSaveState::~FileProjectSaveState(){}

void FileProjectSaveState::onEnter(ProjectModel &projectModel)
{
	projectModel.fileProjectSave();
}

void FileProjectSaveState::onExit(ProjectModel &projectModel){}

void FileProjectSaveState::onUpdate(ProjectModel &projectModel, float dt)
{
	projectModel.revertToPreviousState();
}

void FileProjectSaveState::onPause(ProjectModel &projectModel){}
void FileProjectSaveState::onResume(ProjectModel &projectModel){}
void FileProjectSaveState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt){}
void FileProjectSaveState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt){}
void FileProjectSaveState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt){}
void FileProjectSaveState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt){}

///////////////////////////////////////////////////////////////////////////////////////////////////
FileSceneNewState::FileSceneNewState(){}
FileSceneNewState::~FileSceneNewState(){}

void FileSceneNewState::onEnter(ProjectModel &projectModel)
{
	projectModel.fileSceneNew(projectModel.getCurrentSceneFileName());
}

void FileSceneNewState::onExit(ProjectModel &projectModel){}

void FileSceneNewState::onUpdate(ProjectModel &projectModel, float dt)
{
	//projectModel.revertToPreviousState();
	projectModel.changeState("CheckingRawAssets");
}

void FileSceneNewState::onPause(ProjectModel &projectModel){}
void FileSceneNewState::onResume(ProjectModel &projectModel){}
void FileSceneNewState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt){}
void FileSceneNewState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt){}
void FileSceneNewState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt){}
void FileSceneNewState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt){}

///////////////////////////////////////////////////////////////////////////////////////////////////
FileSceneOpenState::FileSceneOpenState(){}
FileSceneOpenState::~FileSceneOpenState(){}

void FileSceneOpenState::onEnter(ProjectModel &projectModel)
{
	projectModel.fileSceneOpen(projectModel.getCurrentSceneFileName());
}

void FileSceneOpenState::onExit(ProjectModel &projectModel){}

void FileSceneOpenState::onUpdate(ProjectModel &projectModel, float dt)
{
	//projectModel.revertToPreviousState();
	projectModel.changeState("CheckingRawAssets");
}

void FileSceneOpenState::onPause(ProjectModel &projectModel){}
void FileSceneOpenState::onResume(ProjectModel &projectModel){}
void FileSceneOpenState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt){}
void FileSceneOpenState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt){}
void FileSceneOpenState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt){}
void FileSceneOpenState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt){}

///////////////////////////////////////////////////////////////////////////////////////////////////
FileSceneSaveState::FileSceneSaveState(){}
FileSceneSaveState::~FileSceneSaveState(){}
	
void FileSceneSaveState::onEnter(ProjectModel &projectModel)
{
	projectModel.fileSceneSave();
}

void FileSceneSaveState::onExit(ProjectModel &projectModel){}

void FileSceneSaveState::onUpdate(ProjectModel &projectModel, float dt)
{
	//projectModel.revertToPreviousState();
	projectModel.changeState("CheckingRawAssets");
}

void FileSceneSaveState::onPause(ProjectModel &projectModel){}
void FileSceneSaveState::onResume(ProjectModel &projectModel){}
void FileSceneSaveState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt){}
void FileSceneSaveState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt){}
void FileSceneSaveState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt){}
void FileSceneSaveState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt){}

///////////////////////////////////////////////////////////////////////////////////////////////////
FileSceneSaveAsState::FileSceneSaveAsState(){}
FileSceneSaveAsState::~FileSceneSaveAsState(){}
	
void FileSceneSaveAsState::onEnter(ProjectModel &projectModel)
{
	projectModel.fileSceneSaveAs(projectModel.getCurrentSceneFileName());
}

void FileSceneSaveAsState::onExit(ProjectModel &projectModel){}

void FileSceneSaveAsState::onUpdate(ProjectModel &projectModel, float dt)
{
	//projectModel.revertToPreviousState();
	projectModel.changeState("CheckingRawAssets");
}

void FileSceneSaveAsState::onPause(ProjectModel &projectModel){}
void FileSceneSaveAsState::onResume(ProjectModel &projectModel){}
void FileSceneSaveAsState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt){}
void FileSceneSaveAsState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt){}
void FileSceneSaveAsState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt){}
void FileSceneSaveAsState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt){}

///////////////////////////////////////////////////////////////////////////////////////////////////
FileSceneDeleteState::FileSceneDeleteState(){}
FileSceneDeleteState::~FileSceneDeleteState(){}
	
void FileSceneDeleteState::onEnter(ProjectModel &projectModel)
{
	projectModel.fileSceneDelete(projectModel.getCurrentSceneFileName());
}

void FileSceneDeleteState::onExit(ProjectModel &projectModel){}

void FileSceneDeleteState::onUpdate(ProjectModel &projectModel, float dt)
{
	//projectModel.revertToPreviousState();
	projectModel.changeState("CheckingRawAssets");
}

void FileSceneDeleteState::onPause(ProjectModel &projectModel){}
void FileSceneDeleteState::onResume(ProjectModel &projectModel){}
void FileSceneDeleteState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt){}
void FileSceneDeleteState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt){}
void FileSceneDeleteState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt){}
void FileSceneDeleteState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt){}

///////////////////////////////////////////////////////////////////////////////////////////////////
FilePrefabOpenState::FilePrefabOpenState(){}
FilePrefabOpenState::~FilePrefabOpenState(){}
	
void FilePrefabOpenState::onEnter(ProjectModel &projectModel)
{
	projectModel.filePrefabLoad(projectModel.getPrefabFileName());
}

void FilePrefabOpenState::onExit(ProjectModel &projectModel){}

void FilePrefabOpenState::onUpdate(ProjectModel &projectModel, float dt)
{
	//projectModel.revertToPreviousState();
	projectModel.changeState("CheckingRawAssets");
}

void FilePrefabOpenState::onPause(ProjectModel &projectModel){}
void FilePrefabOpenState::onResume(ProjectModel &projectModel){}
void FilePrefabOpenState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt){}
void FilePrefabOpenState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt){}
void FilePrefabOpenState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt){}
void FilePrefabOpenState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt){}

///////////////////////////////////////////////////////////////////////////////////////////////////
FilePrefabSaveState::FilePrefabSaveState(){}
FilePrefabSaveState::~FilePrefabSaveState(){}

void FilePrefabSaveState::onEnter(ProjectModel &projectModel)
{
	projectModel.filePrefabSave(projectModel.getPrefabFileName());
}

void FilePrefabSaveState::onExit(ProjectModel &projectModel){}

void FilePrefabSaveState::onUpdate(ProjectModel &projectModel, float dt)
{
	//projectModel.revertToPreviousState();
	projectModel.changeState("CheckingRawAssets");
}

void FilePrefabSaveState::onPause(ProjectModel &projectModel){}
void FilePrefabSaveState::onResume(ProjectModel &projectModel){}
void FilePrefabSaveState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt){}
void FilePrefabSaveState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt){}
void FilePrefabSaveState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt){}
void FilePrefabSaveState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt){}

///////////////////////////////////////////////////////////////////////////////////////////////////
FileExitState::FileExitState(){}
FileExitState::~FileExitState(){}

void FileExitState::onEnter(ProjectModel &projectModel){}
void FileExitState::onExit(ProjectModel &projectModel){}

void FileExitState::onUpdate(ProjectModel &projectModel, float dt)
{
	projectModel.revertToPreviousState();
}

void FileExitState::onPause(ProjectModel &projectModel){}
void FileExitState::onResume(ProjectModel &projectModel){}
void FileExitState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt){}
void FileExitState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt){}
void FileExitState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt){}
void FileExitState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt){}