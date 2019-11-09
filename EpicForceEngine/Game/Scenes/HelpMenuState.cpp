///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "HelpMenuState.h"
#include "ProjectModel.h"
using namespace Magnum;

HelpMenuState::HelpMenuState() : State<ProjectModel>(){}
HelpMenuState::~HelpMenuState(){}
void HelpMenuState::onEnter(ProjectModel &projectModel){}
void HelpMenuState::onExit(ProjectModel &projectModel){}
void HelpMenuState::onUpdate(ProjectModel &projectModel, float dt){}
void HelpMenuState::onPause(ProjectModel &projectModel){}
void HelpMenuState::onResume(ProjectModel &projectModel){}
void HelpMenuState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt){}
void HelpMenuState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt){}
void HelpMenuState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt){}
void HelpMenuState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt){}