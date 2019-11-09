///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "EditMenuState.h"
#include "ProjectModel.h"
using namespace Magnum;

///////////////////////////////////////////////////////////////////////////////////////////////////
EditCutState::EditCutState() : State<ProjectModel>(){}
EditCutState::~EditCutState(){}
void EditCutState::onEnter(ProjectModel &projectModel)
{
	projectModel.editCut();
}
void EditCutState::onExit(ProjectModel &projectModel){}
void EditCutState::onUpdate(ProjectModel &projectModel, float dt)
{
	projectModel.revertToPreviousState();
}
void EditCutState::onPause(ProjectModel &projectModel){}
void EditCutState::onResume(ProjectModel &projectModel){}
void EditCutState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt){}
void EditCutState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt){}
void EditCutState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt){}
void EditCutState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt){}

///////////////////////////////////////////////////////////////////////////////////////////////////
EditCopyState::EditCopyState() : State<ProjectModel>(){}
EditCopyState::~EditCopyState(){}
void EditCopyState::onEnter(ProjectModel &projectModel)
{
	projectModel.editCopy();
}
void EditCopyState::onExit(ProjectModel &projectModel){}
void EditCopyState::onUpdate(ProjectModel &projectModel, float dt)
{
	projectModel.revertToPreviousState();
}
void EditCopyState::onPause(ProjectModel &projectModel){}
void EditCopyState::onResume(ProjectModel &projectModel){}
void EditCopyState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt){}
void EditCopyState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt){}
void EditCopyState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt){}
void EditCopyState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt){}

///////////////////////////////////////////////////////////////////////////////////////////////////
EditPasteState::EditPasteState() : State<ProjectModel>(){}
EditPasteState::~EditPasteState(){}
void EditPasteState::onEnter(ProjectModel &projectModel)
{
	projectModel.editPaste();
}
void EditPasteState::onExit(ProjectModel &projectModel){}
void EditPasteState::onUpdate(ProjectModel &projectModel, float dt)
{
	projectModel.revertToPreviousState();
}
void EditPasteState::onPause(ProjectModel &projectModel){}
void EditPasteState::onResume(ProjectModel &projectModel){}
void EditPasteState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt){}
void EditPasteState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt){}
void EditPasteState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt){}
void EditPasteState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt){}

///////////////////////////////////////////////////////////////////////////////////////////////////
EditDuplicateState::EditDuplicateState() : State<ProjectModel>(){}
EditDuplicateState::~EditDuplicateState(){}
void EditDuplicateState::onEnter(ProjectModel &projectModel)
{
	projectModel.editDuplicate();
}
void EditDuplicateState::onExit(ProjectModel &projectModel){}
void EditDuplicateState::onUpdate(ProjectModel &projectModel, float dt)
{
	projectModel.revertToPreviousState();
}
void EditDuplicateState::onPause(ProjectModel &projectModel){}
void EditDuplicateState::onResume(ProjectModel &projectModel){}
void EditDuplicateState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt){}
void EditDuplicateState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt){}
void EditDuplicateState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt){}
void EditDuplicateState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt){}

///////////////////////////////////////////////////////////////////////////////////////////////////
EditDeleteState::EditDeleteState() : State<ProjectModel>(){}
EditDeleteState::~EditDeleteState(){}
void EditDeleteState::onEnter(ProjectModel &projectModel)
{
	projectModel.editDelete();
}
void EditDeleteState::onExit(ProjectModel &projectModel){}
void EditDeleteState::onUpdate(ProjectModel &projectModel, float dt)
{
	projectModel.revertToPreviousState();
}
void EditDeleteState::onPause(ProjectModel &projectModel){}
void EditDeleteState::onResume(ProjectModel &projectModel){}
void EditDeleteState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt){}
void EditDeleteState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt){}
void EditDeleteState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt){}
void EditDeleteState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt){}