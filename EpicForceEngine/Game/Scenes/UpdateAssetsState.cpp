///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "UpdateAssetsState.h"
#include "ProjectModel.h"
using namespace Magnum;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
CheckingRawAssetsState::CheckingRawAssetsState()
: State<ProjectModel>()
{
}

CheckingRawAssetsState::~CheckingRawAssetsState()
{
}

void CheckingRawAssetsState::onEnter(ProjectModel &projectModel)
{
	projectModel.beginCheckRawAssets();
}

void CheckingRawAssetsState::onExit(ProjectModel &projectModel)
{
}

void CheckingRawAssetsState::onUpdate(ProjectModel &projectModel, float dt)
{
	if(!projectModel.isCheckingRawAssets())
	{
		projectModel.changeState("UpdatingAssets");
	}
	else
	{
		debug("CheckingRawAssets");
	}
}

void CheckingRawAssetsState::onPause(ProjectModel &projectModel)
{
}

void CheckingRawAssetsState::onResume(ProjectModel &projectModel)
{
}

void CheckingRawAssetsState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt)
{
}

void CheckingRawAssetsState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt)
{
}

void CheckingRawAssetsState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt)
{
}

void CheckingRawAssetsState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
UpdatingAssetsState::UpdatingAssetsState()
: State<ProjectModel>()
{
}

UpdatingAssetsState::~UpdatingAssetsState()
{
}

void UpdatingAssetsState::onEnter(ProjectModel &projectModel)
{
	projectModel.beginUpdateResources();
}

void UpdatingAssetsState::onExit(ProjectModel &projectModel)
{
}

void UpdatingAssetsState::onUpdate(ProjectModel &projectModel, float dt)
{
	if(!projectModel.isUpdatingResources())
	{
		projectModel.updateResourceImporters();
		projectModel.notifyViews();

		projectModel.changeState("ValidateEntities");
	}
	else
	{
		debug("UpdatingAssets");
	}
}

void UpdatingAssetsState::onPause(ProjectModel &projectModel)
{
}

void UpdatingAssetsState::onResume(ProjectModel &projectModel)
{
}

void UpdatingAssetsState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt)
{
}

void UpdatingAssetsState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt)
{
}

void UpdatingAssetsState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt)
{
}

void UpdatingAssetsState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
ValidateEntitiesState::ValidateEntitiesState()
: State<ProjectModel>()
{
}

ValidateEntitiesState::~ValidateEntitiesState()
{
}

void ValidateEntitiesState::onEnter(ProjectModel &projectModel)
{
	projectModel.beginUpdateEntities();
}

void ValidateEntitiesState::onExit(ProjectModel &projectModel)
{
}

void ValidateEntitiesState::onUpdate(ProjectModel &projectModel, float dt)
{
	if(!projectModel.isUpdatingEntities())
	{
		projectModel.changeState("OperationSelectEntity");
	}
	else
	{
		debug("ValidateEntities");
	}
}

void ValidateEntitiesState::onPause(ProjectModel &projectModel)
{
}

void ValidateEntitiesState::onResume(ProjectModel &projectModel)
{
}

void ValidateEntitiesState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt)
{
}

void ValidateEntitiesState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt)
{
}

void ValidateEntitiesState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt)
{
}

void ValidateEntitiesState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt)
{
}
