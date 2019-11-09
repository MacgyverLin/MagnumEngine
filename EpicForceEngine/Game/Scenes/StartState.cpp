///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "StartState.h"
#include "ProjectModel.h"
using namespace Magnum;

//#define QUICK_TEST

StartState::StartState()
: State<ProjectModel>()
{
}

StartState::~StartState()
{
}

void StartState::onEnter(ProjectModel &projectModel)
{
	projectModel.initClassIndexMap();
	projectModel.initEntityCreators();
	Entity::create("EditorEntity", "EditorEntity");

	projectModel.notifyViews();

#ifdef QUICK_TEST
#else
	projectModel.setChanged(ProjectModelBase::PROJECT_DIALOG);
	projectModel.notifyViews();
#endif
}

void StartState::onExit(ProjectModel &projectModel)
{
}

void StartState::onUpdate(ProjectModel &projectModel, float dt)
{
#ifdef QUICK_TEST
	projectModel.changeState("OperationSelectEntity");
#else
	if(projectModel.getOpenFlag())
	{
		projectModel.changeState("FileProjectOpen");
	}
	else
	{
		projectModel.changeState("FileProjectNew");
	}
#endif
}

void StartState::onPause(ProjectModel &projectModel)
{
}

void StartState::onResume(ProjectModel &projectModel)
{
}

void StartState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt)
{
}

void StartState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt)
{
}

void StartState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt)
{
}

void StartState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt)
{
}