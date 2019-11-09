///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "OperationMenuState.h"
#include "ProjectModel.h"
#include "EditorEntity.h"
using namespace Magnum;

///////////////////////////////////////////////////////////////////////////////////////////////////
SelectEntityState::SelectEntityState() : State<ProjectModel>(){}
SelectEntityState::~SelectEntityState(){}
	
void SelectEntityState::onEnter(ProjectModel &projectModel){}
void SelectEntityState::onExit(ProjectModel &projectModel){}
void SelectEntityState::onUpdate(ProjectModel &projectModel, float dt)
{
	EditorEntity *editorEntity	= (EditorEntity *)Entity::findByName("EditorEntity", "EditorEntity");
	if(editorEntity)
	{
		editorEntity->getEditorGizmo().setMode(EditorGizmo::Mode::DEFAULT,
											   (EditorGizmo::CoordSys)projectModel.getCoordinateSystem());
	}
}
void SelectEntityState::onPause(ProjectModel &projectModel){}
void SelectEntityState::onResume(ProjectModel &projectModel){}
void SelectEntityState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt){}
void SelectEntityState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt){}
void SelectEntityState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt){}
void SelectEntityState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////
MoveSelectedState::MoveSelectedState() 
: State<ProjectModel>()
, initMousePosition(Vector2::ZERO)
, refTransform(Matrix4::IDENTITY)
, initGlobalPosition(Vector3::ZERO)
, active(false)
{
}

MoveSelectedState::~MoveSelectedState(){}
	
void MoveSelectedState::onEnter(ProjectModel &projectModel)
{
}

void MoveSelectedState::onExit(ProjectModel &projectModel)
{
}

void MoveSelectedState::onUpdate(ProjectModel &projectModel, float dt)
{
	EditorEntity *editorEntity	= (EditorEntity *)Entity::findByName("EditorEntity", "EditorEntity");
	if(editorEntity)
	{
		editorEntity->getEditorGizmo().setMode(EditorGizmo::Mode::TRANSLATE,
											   (EditorGizmo::CoordSys)projectModel.getCoordinateSystem());
	}
	else
	{
		editorEntity->getEditorGizmo().setMode(EditorGizmo::Mode::DEFAULT,
											   (EditorGizmo::CoordSys)projectModel.getCoordinateSystem());
	}
}

void MoveSelectedState::onPause(ProjectModel &projectModel){}
void MoveSelectedState::onResume(ProjectModel &projectModel){}
void MoveSelectedState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt)
{
	Entity *selected			= projectModel.getSelectedEntity();
	EditorEntity *editorEntity	= (EditorEntity *)Entity::findByName("EditorEntity", "EditorEntity");

	if(evt.event==Input::EVENT_MOUSE_DOWN)
	{
		if(selected)
		{
			active						= true;

			initMousePosition			= evt.position;
			initGlobalPosition			= selected->getGlobalPosition();

			EditorGizmo &editorGizmo	= editorEntity->getEditorGizmo();
			editorGizmo.getRefTransform(refTransform, editorGizmo.getCoordSys());
		}
	}
	else if(evt.event==Input::EVENT_MOUSE_UP)
	{
		if(selected)
			active				= false;
	}
	else if(evt.event==Input::EVENT_MOUSE_MOVE)
	{
		if(selected)
		{
			if(active)
			{
				float factor = 10.0f;
				Vector2 input = evt.position - initMousePosition;
				Vector3 direction;
				if(evt.modifier==Input::TouchpadEvent::Modifier::SHIFT)
				{
					direction.X() = -input.Y() * factor;
					direction.Y() = 0;
					direction.Z() = 0;
				}
				else if(evt.modifier==Input::TouchpadEvent::Modifier::CTRL)
				{
					direction.X() = 0;
					direction.Y() = -input.Y() * factor;
					direction.Z() = 0;
				}
				else if(evt.modifier==Input::TouchpadEvent::Modifier::ALT)
				{
					direction.X() = 0;
					direction.Y() = 0;
					direction.Z() = -input.Y() * factor;
				}
				else
				{
					direction.X() = -input.X() * factor;
					direction.Y() = -input.Y() * factor;
					direction.Z() = 0;
				}

				Vector3 newPos	= initGlobalPosition + refTransform.TimesDirectionVector(direction);
				selected->setGlobalPosition(newPos);

				projectModel.setChanged(ProjectModelBase::SELECTED_ENTITY_TRANSFORM_CHANGED);
				projectModel.notifyViews();
			}
		}
	}
	else if(evt.event==Input::EVENT_MOUSE_WHEEL)
	{
		if(selected)
		{
			debug("%f %f %d %d", evt.position.X(), evt.position.Y(), evt.wheelAxis, evt.wheelRotation);
		}
	}
}

void MoveSelectedState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt){}
void MoveSelectedState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt){}
void MoveSelectedState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////
RotateSelectedState::RotateSelectedState() 
: State<ProjectModel>()
, initMousePosition(Vector2::ZERO)
, refTransform(Matrix4::IDENTITY)
, initGlobalTransform(Matrix4::IDENTITY)
, active(false)
{
}

RotateSelectedState::~RotateSelectedState()
{
}
	
void RotateSelectedState::onEnter(ProjectModel &projectModel)
{
}

void RotateSelectedState::onExit(ProjectModel &projectModel)
{
}

void RotateSelectedState::onUpdate(ProjectModel &projectModel, float dt)
{
	EditorEntity *editorEntity	= (EditorEntity *)Entity::findByName("EditorEntity", "EditorEntity");
	if(editorEntity)
	{
		editorEntity->getEditorGizmo().setMode(EditorGizmo::Mode::ROTATE,
											   (EditorGizmo::CoordSys)projectModel.getCoordinateSystem());
	}
	else
	{
		editorEntity->getEditorGizmo().setMode(EditorGizmo::Mode::DEFAULT,
											   (EditorGizmo::CoordSys)projectModel.getCoordinateSystem());
	}
}

void RotateSelectedState::onPause(ProjectModel &projectModel){}
void RotateSelectedState::onResume(ProjectModel &projectModel){}
void RotateSelectedState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt)
{
	Entity *selected			= projectModel.getSelectedEntity();
	EditorEntity *editorEntity	= (EditorEntity *)Entity::findByName("EditorEntity", "EditorEntity");
	
	if(evt.event==Input::EVENT_MOUSE_DOWN)
	{
		if(selected)
		{
			active						= true;

			initMousePosition			= evt.position;
			initGlobalTransform			= selected->getGlobalTransform();
			EditorGizmo &editorGizmo	= editorEntity->getEditorGizmo();
			editorGizmo.getRefTransform(refTransform, editorGizmo.getCoordSys());
		}
	}
	else if(evt.event==Input::EVENT_MOUSE_UP)
	{
		if(selected)
			active				= false;
	}
	else if(evt.event==Input::EVENT_MOUSE_MOVE)
	{
		if(selected)
		{
			if(active)
			{
				float factor = 10.0f;
				Vector2 input = evt.position - initMousePosition;
				Vector3 direction;
				if(evt.modifier==Input::TouchpadEvent::Modifier::SHIFT)
				{
					direction.X() = -input.Y() * factor;
					direction.Y() = 0;
					direction.Z() = 0;
				}
				else if(evt.modifier==Input::TouchpadEvent::Modifier::CTRL)
				{
					direction.X() = 0;
					direction.Y() = -input.Y() * factor;
					direction.Z() = 0;
				}
				else if(evt.modifier==Input::TouchpadEvent::Modifier::ALT)
				{
					direction.X() = 0;
					direction.Y() = 0;
					direction.Z() = -input.Y() * factor;
				}
				else
				{
					direction.X() = -input.X() * factor;
					direction.Y() = -input.Y() * factor;
					direction.Z() = 0;
				}

				Matrix4 rotX;
				Matrix4 rotY;
				Matrix4 rotZ;
				//rotX.initRotateX(direction.X()*Math::DEG_2_RAD);
				//rotY.initRotateY(direction.Y()*Math::DEG_2_RAD);
				//rotZ.initRotateZ(direction.Z()*Math::DEG_2_RAD);

				rotX.initRotateAxisAngle(Vector3::UNIT_X, direction.X()*Math::DEG_2_RAD);
				rotY.initRotateAxisAngle(Vector3::UNIT_Y, direction.Y()*Math::DEG_2_RAD);
				rotZ.initRotateAxisAngle(Vector3::UNIT_Z, direction.Z()*Math::DEG_2_RAD);

				Matrix4 rotation(rotZ * rotY * rotX);
				rotation.orthonormalize();
				selected->setGlobalTransform(refTransform * rotation * refTransform.Inverse() * initGlobalTransform);

				projectModel.setChanged(ProjectModelBase::SELECTED_ENTITY_TRANSFORM_CHANGED);
				projectModel.notifyViews();
			}
		}
	}
}
void RotateSelectedState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt){}
void RotateSelectedState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt){}
void RotateSelectedState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt){}

///////////////////////////////////////////////////////////////////////////////////////////////////
ScaleSelectedState::ScaleSelectedState()
: State<ProjectModel>()
, initMousePosition(Vector2::ZERO)
, initGlobalTransform(Matrix4::IDENTITY)
, active(false)
{
}

ScaleSelectedState::~ScaleSelectedState()
{
}
	
void ScaleSelectedState::onEnter(ProjectModel &projectModel)
{
}

void ScaleSelectedState::onExit(ProjectModel &projectModel)
{
}
void ScaleSelectedState::onUpdate(ProjectModel &projectModel, float dt)
{
	EditorEntity *editorEntity	= (EditorEntity *)Entity::findByName("EditorEntity", "EditorEntity");
	if(editorEntity)
	{
		editorEntity->getEditorGizmo().setMode(EditorGizmo::Mode::SCALE, EditorGizmo::LOCAL);
	}
	else
	{
		editorEntity->getEditorGizmo().setMode(EditorGizmo::Mode::DEFAULT, EditorGizmo::LOCAL);
	}
}
void ScaleSelectedState::onPause(ProjectModel &projectModel){}
void ScaleSelectedState::onResume(ProjectModel &projectModel){}
void ScaleSelectedState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt)
{
	Entity *selected			= projectModel.getSelectedEntity();
	EditorEntity *editorEntity	= (EditorEntity *)Entity::findByName("EditorEntity", "EditorEntity");
	
	if(evt.event==Input::EVENT_MOUSE_DOWN)
	{
		if(selected)
		{
			active				= true;

			initMousePosition			= evt.position;
			initGlobalTransform			= selected->getGlobalTransform();
			EditorGizmo &editorGizmo	= editorEntity->getEditorGizmo();
			editorGizmo.getRefTransform(refTransform, editorGizmo.getCoordSys());

			refTransform				= initGlobalTransform;
		}
	}
	else if(evt.event==Input::EVENT_MOUSE_UP)
	{
		if(selected)
			active				= false;
	}
	else if(evt.event==Input::EVENT_MOUSE_MOVE)
	{
		if(selected)
		{
			if(active)
			{
				float factor = 1.0f;
				Vector2 input = evt.position - initMousePosition;
				Vector3 direction;
				if(evt.modifier==Input::TouchpadEvent::Modifier::SHIFT)
				{
					direction.X() = 1.0f-input.Y() * factor;
					direction.Y() = 1.0f;
					direction.Z() = 1.0f;
				}
				else if(evt.modifier==Input::TouchpadEvent::Modifier::CTRL)
				{
					direction.X() = 1.0f;
					direction.Y() = 1.0f-input.Y() * factor;
					direction.Z() = 1.0f;
				}
				else if(evt.modifier==Input::TouchpadEvent::Modifier::ALT)
				{
					direction.X() = 1.0f;
					direction.Y() = 1.0f;
					direction.Z() = 1.0f-input.Y() * factor;
				}
				else
				{
					direction.X() = 1.0f-input.X() * factor;
					direction.Y() = 1.0f-input.Y() * factor;
					direction.Z() = 1.0f;
				}

				Matrix4 scaleMat;
				scaleMat.initScale(direction.X(), direction.Y(), direction.Z());

				selected->setGlobalTransform(refTransform * scaleMat * refTransform.Inverse() * initGlobalTransform);

				projectModel.setChanged(ProjectModelBase::SELECTED_ENTITY_TRANSFORM_CHANGED);
				projectModel.notifyViews();
			}
		}
	}
}

void ScaleSelectedState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt){}
void ScaleSelectedState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt){}
void ScaleSelectedState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt){}

///////////////////////////////////////////////////////////////////////////////////////////////////
OperationFrameSelectedState::OperationFrameSelectedState() : State<ProjectModel>(){}
OperationFrameSelectedState::~OperationFrameSelectedState(){}
void OperationFrameSelectedState::onEnter(ProjectModel &projectModel)
{
	projectModel.editFrameSelected();
}
void OperationFrameSelectedState::onExit(ProjectModel &projectModel){}
void OperationFrameSelectedState::onUpdate(ProjectModel &projectModel, float dt)
{
	projectModel.revertToPreviousState();
}
void OperationFrameSelectedState::onPause(ProjectModel &projectModel){}
void OperationFrameSelectedState::onResume(ProjectModel &projectModel){}
void OperationFrameSelectedState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt){}
void OperationFrameSelectedState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt){}
void OperationFrameSelectedState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt){}
void OperationFrameSelectedState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt){}

///////////////////////////////////////////////////////////////////////////////////////////////////
OperationFindState::OperationFindState() : State<ProjectModel>(){}
OperationFindState::~OperationFindState(){}
void OperationFindState::onEnter(ProjectModel &projectModel)
{
	projectModel.editFind();
}
void OperationFindState::onExit(ProjectModel &projectModel){}
void OperationFindState::onUpdate(ProjectModel &projectModel, float dt)
{
	projectModel.revertToPreviousState();
}
void OperationFindState::onPause(ProjectModel &projectModel){}
void OperationFindState::onResume(ProjectModel &projectModel){}
void OperationFindState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt){}
void OperationFindState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt){}
void OperationFindState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt){}
void OperationFindState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt){}

///////////////////////////////////////////////////////////////////////////////////////////////////
OperationSelectAllState::OperationSelectAllState() : State<ProjectModel>(){}
OperationSelectAllState::~OperationSelectAllState(){}
void OperationSelectAllState::onEnter(ProjectModel &projectModel)
{
	projectModel.editSelectAll();
}
void OperationSelectAllState::onExit(ProjectModel &projectModel){}
void OperationSelectAllState::onUpdate(ProjectModel &projectModel, float dt)
{
	projectModel.revertToPreviousState();
}
void OperationSelectAllState::onPause(ProjectModel &projectModel){}
void OperationSelectAllState::onResume(ProjectModel &projectModel){}
void OperationSelectAllState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt){}
void OperationSelectAllState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt){}
void OperationSelectAllState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt){}
void OperationSelectAllState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt){}

///////////////////////////////////////////////////////////////////////////////////////////////////
ZoomState::ZoomState()
: State<ProjectModel>()
, initMousePosition(Vector2::ZERO)
, initRight(0)
, initTop(0)
, initNearPlane(0)
, initFarPlane(0) 
, active(false)
{
}

ZoomState::~ZoomState(){}
	
void ZoomState::onEnter(ProjectModel &projectModel){}
void ZoomState::onExit(ProjectModel &projectModel){}
void ZoomState::onUpdate(ProjectModel &projectModel, float dt)
{
	EditorEntity *editorEntity	= (EditorEntity *)Entity::findByName("EditorEntity", "EditorEntity");
	if(editorEntity)
	{
		editorEntity->getEditorGizmo().setMode(EditorGizmo::Mode::DEFAULT,
											   (EditorGizmo::CoordSys)projectModel.getCoordinateSystem());
	}
}
void ZoomState::onPause(ProjectModel &projectModel){}
void ZoomState::onResume(ProjectModel &projectModel){}
void ZoomState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt)
{
	EditorEntity *editorEntity = (EditorEntity *)Entity::findByName("EditorEntity", "EditorEntity");

	if(evt.event==Input::EVENT_MOUSE_DOWN)
	{
		active				= true;
		initMousePosition	= evt.position;

		float left, right, bottom, top, nearPlane, farPlane;
		editorEntity->getCameraComponent().getProjection(left, right, bottom, top, nearPlane, farPlane);

		initRight			= right;
		initTop				= top;
		initNearPlane		= nearPlane;
		initFarPlane		= farPlane;
	}
	else if(evt.event==Input::EVENT_MOUSE_UP)
	{
		active				= false;
	}
	else if(evt.event==Input::EVENT_MOUSE_MOVE)
	{
		if(active)
		{
			Vector2 diffMousePos	 =	evt.position			- initMousePosition;
			float factor			 =  diffMousePos.Y() * 10;
			if(factor<-0.9)
				factor=-0.9;

			float newRight			 =	initRight * (1.0 + factor);
			float newTop			 =	initTop   * (1.0 + factor);

			editorEntity->getCameraComponent().setProjection(-newRight, newRight, -newTop, newTop, initNearPlane, initFarPlane);
		}
	}
}
void ZoomState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt){}
void ZoomState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt){}
void ZoomState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt){}

///////////////////////////////////////////////////////////////////////////////////////////////////
ZoomExtentState::ZoomExtentState()
: State<ProjectModel>()
, initMousePosition(Vector2::ZERO)
, initCameraPosition(Vector3::ZERO)
, active(false)
{
}

ZoomExtentState::~ZoomExtentState()
{
}
	
void ZoomExtentState::onEnter(ProjectModel &projectModel){}
void ZoomExtentState::onExit(ProjectModel &projectModel){}
void ZoomExtentState::onUpdate(ProjectModel &projectModel, float dt)
{
	EditorEntity *editorEntity	= (EditorEntity *)Entity::findByName("EditorEntity", "EditorEntity");
	if(editorEntity)
	{
		editorEntity->getEditorGizmo().setMode(EditorGizmo::Mode::DEFAULT,
											   (EditorGizmo::CoordSys)projectModel.getCoordinateSystem());
	}
}
void ZoomExtentState::onPause(ProjectModel &projectModel){}
void ZoomExtentState::onResume(ProjectModel &projectModel){}
void ZoomExtentState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt)
{
	EditorEntity *editorEntity = (EditorEntity *)Entity::findByName("EditorEntity", "EditorEntity");

	if(evt.event==Input::EVENT_MOUSE_DOWN)
	{
		active				= true;
		initMousePosition	= evt.position;
		initCameraPosition	= editorEntity->getGlobalPosition();
	}
	else if(evt.event==Input::EVENT_MOUSE_UP)
	{
		active				= false;
	}
	else if(evt.event==Input::EVENT_MOUSE_MOVE)
	{
		if(active)
		{
			Vector2 diffMousePos =	evt.position			- initMousePosition;
			Vector3 newPos		 =	initCameraPosition	+ 
									editorEntity->getGlobalXAxis() * diffMousePos.X() / 1 +
									editorEntity->getGlobalYAxis() * diffMousePos.Y() / 1;
		
			editorEntity->setGlobalPosition(newPos);
		}
	}
}
void ZoomExtentState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt){}
void ZoomExtentState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt){}
void ZoomExtentState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt){}

///////////////////////////////////////////////////////////////////////////////////////////////////
ZoomExtentSelectedState::ZoomExtentSelectedState() 
: State<ProjectModel>()
{
}

ZoomExtentSelectedState::~ZoomExtentSelectedState()
{
}
	
void ZoomExtentSelectedState::onEnter(ProjectModel &projectModel){}
void ZoomExtentSelectedState::onExit(ProjectModel &projectModel){}
void ZoomExtentSelectedState::onUpdate(ProjectModel &projectModel, float dt)
{
	EditorEntity *editorEntity	= (EditorEntity *)Entity::findByName("EditorEntity", "EditorEntity");
	if(editorEntity)
	{
		editorEntity->getEditorGizmo().setMode(EditorGizmo::Mode::DEFAULT,
											   (EditorGizmo::CoordSys)projectModel.getCoordinateSystem());
	}
}
void ZoomExtentSelectedState::onPause(ProjectModel &projectModel){}
void ZoomExtentSelectedState::onResume(ProjectModel &projectModel){}
void ZoomExtentSelectedState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt){}
void ZoomExtentSelectedState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt){}
void ZoomExtentSelectedState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt){}
void ZoomExtentSelectedState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt){}

///////////////////////////////////////////////////////////////////////////////////////////////////
ZoomRegionState::ZoomRegionState() 
: State<ProjectModel>()
, p1(Vector2::ZERO)
, p2(Vector2::ZERO)
, active(false)
{
}

ZoomRegionState::~ZoomRegionState()
{
}
	
void ZoomRegionState::onEnter(ProjectModel &projectModel){}
void ZoomRegionState::onExit(ProjectModel &projectModel){}
void ZoomRegionState::onUpdate(ProjectModel &projectModel, float dt)
{
	EditorEntity *editorEntity	= (EditorEntity *)Entity::findByName("EditorEntity", "EditorEntity");
	if(editorEntity)
	{
		editorEntity->getEditorGizmo().setMode(EditorGizmo::Mode::DEFAULT,
											   (EditorGizmo::CoordSys)projectModel.getCoordinateSystem());
	}
}
void ZoomRegionState::onPause(ProjectModel &projectModel){}
void ZoomRegionState::onResume(ProjectModel &projectModel){}
void ZoomRegionState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt)
{
	EditorEntity *editorEntity = (EditorEntity *)Entity::findByName("EditorEntity", "EditorEntity");

	if(evt.event==Input::EVENT_MOUSE_DOWN)
	{
		float left, right, bottom, top, nearPlane, farPlane;
		editorEntity->getCameraComponent().getProjection(left, right, bottom, top, nearPlane, farPlane);

		float fx = evt.position.X() * 0.5f + 0.5f;
		float fy = evt.position.Y() * 0.5f + 0.5f;
		p1.X() = fx * (right-left  ) + left;
		p1.Y() = fy * (top  -bottom) + bottom;

		active = true;
	}
	else if(evt.event==Input::EVENT_MOUSE_UP)
	{
		if(active)
		{
			float left, right, bottom, top, nearPlane, farPlane;
			editorEntity->getCameraComponent().getProjection(left, right, bottom, top, nearPlane, farPlane);

			float fx = evt.position.X() * 0.5f + 0.5f;
			float fy = evt.position.Y() * 0.5f + 0.5f;
			p2.X() = fx * (right-left  ) + left;
			p2.Y() = fy * (top  -bottom) + bottom;

			float newleft    = Math::Min(p1.X(), p2.X());
			float newRight   = Math::Max(p1.X(), p2.X());
			float newBottom  = Math::Min(p1.Y(), p2.Y());
			float newTop	 = Math::Max(p1.Y(), p2.Y());

			editorEntity->getCameraComponent().setProjection(newleft, newRight, newBottom, newTop, nearPlane, farPlane);

			active				= false;
		}
	}
	else if(evt.event==Input::EVENT_MOUSE_MOVE)
	{
	}
}

void ZoomRegionState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt){}
void ZoomRegionState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt){}
void ZoomRegionState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt){}

///////////////////////////////////////////////////////////////////////////////////////////////////
FovState::FovState()
: State<ProjectModel>()
, initMousePosition(Vector2::ZERO)
, initCameraHalfFOVY(0)
, initAspect(0)
, initNearPlane(0)
, initFarPlane(0) 
, active(false)
{
}

FovState::~FovState()
{
}
	
void FovState::onEnter(ProjectModel &projectModel){}
void FovState::onExit(ProjectModel &projectModel){}
void FovState::onUpdate(ProjectModel &projectModel, float dt)
{
	EditorEntity *editorEntity	= (EditorEntity *)Entity::findByName("EditorEntity", "EditorEntity");
	if(editorEntity)
	{
		editorEntity->getEditorGizmo().setMode(EditorGizmo::Mode::DEFAULT,
											   (EditorGizmo::CoordSys)projectModel.getCoordinateSystem());
	}
}
void FovState::onPause(ProjectModel &projectModel){}
void FovState::onResume(ProjectModel &projectModel){}
void FovState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt)
{
	EditorEntity *editorEntity = (EditorEntity *)Entity::findByName("EditorEntity", "EditorEntity");

	if(evt.event==Input::EVENT_MOUSE_DOWN)
	{
		active				= true;
		initMousePosition	= evt.position;

		float left, right, bottom, top, nearPlane, farPlane;
		editorEntity->getCameraComponent().getProjection(left, right, bottom, top, nearPlane, farPlane);

		initCameraHalfFOVY	= Math::ATan2((top - bottom)/2, nearPlane);
		initAspect			= (right - left) / (top - bottom);
		initNearPlane		= nearPlane;
		initFarPlane		= farPlane;
	}
	else if(evt.event==Input::EVENT_MOUSE_UP)
	{
		active				= false;
	}
	else if(evt.event==Input::EVENT_MOUSE_MOVE)
	{
		if(active)
		{
			Vector2 diffMousePos	 =	evt.position			- initMousePosition;
			float newCameraHalfFOVY	 =	initCameraHalfFOVY + diffMousePos.Y();
			if(newCameraHalfFOVY>Math::DEG_2_RAD*89)
				newCameraHalfFOVY = Math::DEG_2_RAD*89;
			else if(newCameraHalfFOVY<Math::DEG_2_RAD*1)
				newCameraHalfFOVY = Math::DEG_2_RAD*1;

			float newTop			 = Math::Tan(newCameraHalfFOVY) * initNearPlane;
			float newRight			 = newTop * initAspect;

			editorEntity->getCameraComponent().setProjection(-newRight, newRight, -newTop, newTop, initNearPlane, initFarPlane);
		}
	}
}

void FovState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt){}
void FovState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt){}
void FovState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt){}

///////////////////////////////////////////////////////////////////////////////////////////////////
PanState::PanState() : State<ProjectModel>()
, initMousePosition(Vector2::ZERO)
, initCameraPosition(Vector3::ZERO)
, initXAxis(Vector3::ZERO)
, initYAxis(Vector3::ZERO)
, active(false)
{
}

PanState::~PanState()
{
}
	
void PanState::onEnter(ProjectModel &projectModel){}
void PanState::onExit(ProjectModel &projectModel){}
void PanState::onUpdate(ProjectModel &projectModel, float dt)
{
	EditorEntity *editorEntity	= (EditorEntity *)Entity::findByName("EditorEntity", "EditorEntity");
	if(editorEntity)
	{
		editorEntity->getEditorGizmo().setMode(EditorGizmo::Mode::DEFAULT,
											   (EditorGizmo::CoordSys)projectModel.getCoordinateSystem());
	}
}
void PanState::onPause(ProjectModel &projectModel){}
void PanState::onResume(ProjectModel &projectModel){}
void PanState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt)
{
	EditorEntity *editorEntity = (EditorEntity *)Entity::findByName("EditorEntity", "EditorEntity");

	if(evt.event==Input::EVENT_MOUSE_DOWN)
	{
		active				= true;
		initMousePosition	= evt.position;
		initCameraPosition	= editorEntity->getGlobalPosition();
		initXAxis			= editorEntity->getGlobalXAxis();
		initYAxis			= editorEntity->getGlobalYAxis();
	}
	else if(evt.event==Input::EVENT_MOUSE_UP)
	{
		active				= false;
	}
	else if(evt.event==Input::EVENT_MOUSE_MOVE)
	{
		if(active)
		{
			Vector2 diffMousePos	=	evt.position			- initMousePosition;
			Vector2 factor(10.0f, 10.0f);
			/*
			Vector3 factor(Math::FAbs(initCameraPosition.X())/100, 
				           Math::FAbs(initCameraPosition.Y())/100, 
						   Math::FAbs(initCameraPosition.Z())/100);
			*/

			Vector3 newPos			=	initCameraPosition	+ 
										initXAxis * -diffMousePos.X() * factor.X() +
										initYAxis * -diffMousePos.Y() * factor.Y();
		
			editorEntity->setGlobalPosition(newPos);
		}
	}
}

void PanState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt){}
void PanState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt){}
void PanState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt){}

///////////////////////////////////////////////////////////////////////////////////////////////////
OrbitState::OrbitState() 
: State<ProjectModel>()
, initMousePosition(Vector2::ZERO)
, initTransform(Matrix4::IDENTITY)
, initXAxis(Vector3::ZERO)
, initYAxis(Vector3::ZERO)
, initZAxis(Vector3::ZERO)
, initOrbitCenter(Vector3::ZERO)
, orbitSelected(false)
, active(false)
{
}

OrbitState::~OrbitState()
{
}
	
void OrbitState::onEnter(ProjectModel &projectModel){}
void OrbitState::onExit(ProjectModel &projectModel){}
void OrbitState::onUpdate(ProjectModel &projectModel, float dt)
{
	EditorEntity *editorEntity	= (EditorEntity *)Entity::findByName("EditorEntity", "EditorEntity");
	if(editorEntity)
	{
		editorEntity->getEditorGizmo().setMode(EditorGizmo::Mode::DEFAULT,
											   (EditorGizmo::CoordSys)projectModel.getCoordinateSystem());
	}
}
void OrbitState::onPause(ProjectModel &projectModel){}
void OrbitState::onResume(ProjectModel &projectModel){}
void OrbitState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt)
{
	EditorEntity *editorEntity = (EditorEntity *)Entity::findByName("EditorEntity", "EditorEntity");
	
	if(evt.event==Input::EVENT_MOUSE_DOWN)
	{
		active				= true;
		initMousePosition	= evt.position;

		if(orbitSelected)
		{
			Entity *entity = Entity::getSelected();
			if(entity)
				initOrbitCenter = entity->getGlobalPosition();
			else
				initOrbitCenter = Vector3::ZERO;
		}
		else
		{
			initOrbitCenter =  editorEntity->getGlobalPosition();
		}

		initTransform		= editorEntity->getGlobalTransform();
		initXAxis			= editorEntity->getGlobalXAxis();
		initYAxis			= Vector3::UNIT_Y;
		initZAxis			= editorEntity->getGlobalZAxis();
	}
	else if(evt.event==Input::EVENT_MOUSE_UP)
	{
		active				= false;
	}
	else if(evt.event==Input::EVENT_MOUSE_MOVE)
	{
		if(active)
		{
			Vector2 diffMousePos	=	evt.position - initMousePosition;
			Vector2 factor(1.0, 1.0);

			Matrix4 preTranslate;
			preTranslate.initTranslate(-initOrbitCenter.X(), 
									   -initOrbitCenter.Y(), 
									   -initOrbitCenter.Z());

			Matrix4 rotX;
			rotX.initTranslateRotAxisAngleScale(0, 0, 0, initXAxis, diffMousePos.Y() * factor.Y(), 1);

			Matrix4 rotY;
			rotY.initTranslateRotAxisAngleScale(0, 0, 0, initYAxis, diffMousePos.X() * factor.X(), 1);

			Matrix4 rotZ;
			rotZ.initTranslateRotAxisAngleScale(0, 0, 0, initZAxis, 0, 1);

			Matrix4 postTranslate;
			postTranslate.initTranslate(initOrbitCenter.X(),
									    initOrbitCenter.Y(),
										initOrbitCenter.Z());

			Matrix4 mat;
			mat = postTranslate * rotZ  * rotY * rotX * preTranslate * initTransform;

			editorEntity->setGlobalTransform(mat);
		}
	}
}
void OrbitState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt){}
void OrbitState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt){}
void OrbitState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt){}

///////////////////////////////////////////////////////////////////////////////////////////////////
OrbitSelectedState::OrbitSelectedState()
: State<ProjectModel>()
, initMousePosition(Vector2::ZERO)
, initTransform(Matrix4::IDENTITY)
, initXAxis(Vector3::ZERO)
, initYAxis(Vector3::ZERO)
, initZAxis(Vector3::ZERO)
, initOrbitCenter(Vector3::ZERO)
, orbitSelected(true)
, active(false)
{
}

OrbitSelectedState::~OrbitSelectedState()
{
}
	
void OrbitSelectedState::onEnter(ProjectModel &projectModel){}
void OrbitSelectedState::onExit(ProjectModel &projectModel){}
void OrbitSelectedState::onUpdate(ProjectModel &projectModel, float dt)
{
	EditorEntity *editorEntity	= (EditorEntity *)Entity::findByName("EditorEntity", "EditorEntity");
	if(editorEntity)
	{
		editorEntity->getEditorGizmo().setMode(EditorGizmo::Mode::DEFAULT,
											   (EditorGizmo::CoordSys)projectModel.getCoordinateSystem());
	}
}
void OrbitSelectedState::onPause(ProjectModel &projectModel){}
void OrbitSelectedState::onResume(ProjectModel &projectModel){}
void OrbitSelectedState::onTouchpad(ProjectModel &projectModel, const Input::TouchpadEvent &evt)
{
	EditorEntity *editorEntity = (EditorEntity *)Entity::findByName("EditorEntity", "EditorEntity");

	if(evt.event==Input::EVENT_MOUSE_DOWN)
	{
		active				= true;
		initMousePosition	= evt.position;

		if(orbitSelected)
		{
			Entity *entity = Entity::getSelected();
			if(entity)
				initOrbitCenter = entity->getGlobalPosition();
			else
				initOrbitCenter = Vector3::ZERO;
		}
		else
		{
			initOrbitCenter =  editorEntity->getGlobalPosition();
		}

		initTransform		= editorEntity->getGlobalTransform();
		initXAxis			= editorEntity->getGlobalXAxis();
		initYAxis			= Vector3::UNIT_Y;
		initZAxis			= editorEntity->getGlobalZAxis();
	}
	else if(evt.event==Input::EVENT_MOUSE_UP)
	{
		active				= false;
	}
	else if(evt.event==Input::EVENT_MOUSE_MOVE)
	{
		if(active)
		{
			Vector2 diffMousePos	=	evt.position - initMousePosition;
			Vector2 factor(1.0, 1.0);

			Matrix4 preTranslate;
			preTranslate.initTranslate(-initOrbitCenter.X(), 
									   -initOrbitCenter.Y(), 
									   -initOrbitCenter.Z());

			Matrix4 rotX;
			rotX.initTranslateRotAxisAngleScale(0, 0, 0, initXAxis, diffMousePos.Y() * factor.Y(), 1);

			Matrix4 rotY;
			rotY.initTranslateRotAxisAngleScale(0, 0, 0, initYAxis, diffMousePos.X() * factor.X(), 1);

			Matrix4 rotZ;
			rotZ.initTranslateRotAxisAngleScale(0, 0, 0, initZAxis, 0, 1);

			Matrix4 postTranslate;
			postTranslate.initTranslate(initOrbitCenter.X(),
									    initOrbitCenter.Y(),
										initOrbitCenter.Z());

			Matrix4 mat;
			mat = postTranslate * rotZ  * rotY * rotX * preTranslate * initTransform;

			editorEntity->setGlobalTransform(mat);
		}
	}
}

void OrbitSelectedState::onKeypad(ProjectModel &projectModel, const Input::GamepadEvent &evt){}
void OrbitSelectedState::onAccelerator(ProjectModel &projectModel, const Input::AcceleratorEvent &evt){}
void OrbitSelectedState::onGUI(ProjectModel &projectModel, const Input::GUIEvent &evt){}