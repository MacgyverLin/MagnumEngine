///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "BuildMenuState.h"
#include "ProjectModel.h"
using namespace Magnum;

BuildMenuState::BuildMenuState()
: State<ProjectModel>()
{
}

BuildMenuState::~BuildMenuState()
{
}

void BuildMenuState::onEnter(ProjectModel &projectModel)
{
}

void BuildMenuState::onExit(ProjectModel &projectModel)
{
}

void BuildMenuState::onUpdate(ProjectModel &projectModel, float dt)
{
}

void BuildMenuState::onPause(ProjectModel &projectModel)
{
}

void BuildMenuState::onResume(ProjectModel &projectModel)
{
}

void BuildMenuState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt)
{
}

void BuildMenuState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt)
{
}

void BuildMenuState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt)
{
}

void BuildMenuState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt)
{
}