///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "GlobalState.h"
#include "ProjectModel.h"
using namespace Magnum;

GlobalState::GlobalState()
: State<ProjectModel>()
{
}

GlobalState::~GlobalState()
{
}

void GlobalState::onEnter(ProjectModel &projectModel)
{
}

void GlobalState::onExit(ProjectModel &projectModel)
{
}

void GlobalState::onUpdate(ProjectModel &projectModel, float dt)
{
}

void GlobalState::onPause(ProjectModel &projectModel)
{
}

void GlobalState::onResume(ProjectModel &projectModel)
{
}

void GlobalState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt)
{
}

void GlobalState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt)
{
}

void GlobalState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt)
{
}

void GlobalState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt)
{
	String command;

	MemInputStream is(&evt.buffer[0], evt.buffer.length());
	is >> command;
	if(command=="ChangeState")
	{
		String nextState;

		is >> nextState;
		if(nextState=="FileProjectNew"  || nextState=="FileProjectOpen")
		{
			String projectPath;
			bool openFileMode;
			is >> projectPath >> openFileMode;

			projectModel.setCurrentProjectPath(projectPath, openFileMode);
			projectModel.changeState(nextState);
		}
		else if(nextState=="FileProjectSave")
		{
			projectModel.changeState(nextState);
		}
		else if(nextState=="FileSceneNew"    || nextState=="FileSceneOpen"   || 
			    nextState=="FileSceneSaveAs" || nextState=="FileSceneDelete")
		{
			String sceneFileName;
			is >> sceneFileName;

			projectModel.setCurrentSceneFileName(sceneFileName);
			projectModel.changeState(nextState);
		}
		else if(nextState=="FileProjectSave")
		{
			projectModel.changeState(nextState);
		}
		else if(nextState=="FilePrefabOpen"  ||	nextState=="FilePrefabSave")
		{
			String prefabFileName;
			is >> prefabFileName;

			projectModel.setPrefabFileName(prefabFileName);
			projectModel.changeState(nextState);
		}
		else /*if(nextState=="EditCut"						||
				nextState=="EditCopy"						||
				nextState=="EditPaste"						||
				nextState=="EditDuplicate"					||
				nextState=="EditDelete"						||
				nextState=="OperationSelectEntity"			||
				nextState=="OperationMoveSelected"			||
				nextState=="OperationRotateSelected"		||
				nextState=="OperationScaleSelected"			||
				nextState=="OperationFrameSelected"			||
				nextState=="OperationFind"					||
				nextState=="OperationSelectAll"				||
				nextState=="OperationZoom"					||
				nextState=="OperationZoomExtent"			||
				nextState=="OperationZoomExtentSelected"	||
				nextState=="OperationZoomRegion"			||
				nextState=="OperationFov"					||
				nextState=="OperationPan"					||
				nextState=="OperationOrbit"					||
				nextState=="OperationOrbitSelected"			||
				nextState=="CheckingRawAssets"				||
				nextState=="DebugRun"						||
				nextState=="DebugStop")
		*/
		{
			projectModel.changeState(nextState);
		}
	}

	if(command=="ChangeCoordSys")
	{
		int coordsys;
		is >> coordsys;

		projectModel.setCoordinateSystem((ProjectModel::CoordSys)coordsys);
	}
}


