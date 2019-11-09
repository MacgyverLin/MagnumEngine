///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "MacDemoCameraEntity.h"
using namespace Magnum;

MacDemoCameraEntity::MacDemoCameraEntity()
: touchpadMethod(this, &MacDemoCameraEntity::touchpadEvent)
, keypadMethod(this, &MacDemoCameraEntity::keypadEvent)
, acceleratorMethod(this, &MacDemoCameraEntity::acceleratorEvent)
, perspCamera(*this)
//, orthoCamera(*this)
//, isMainCamera(false)
{
	perspCamera.setProjection(Math::ONE_PI*45/180, 960.0f/640.0f, 0.1, 3000);
	perspCamera.setTargetLayer(0x01);
	perspCamera.setClearFlags(CameraComponent::CLEAR_COLOR | CameraComponent::CLEAR_DEPTH);

	//orthoCamera.setProjection(-20, 20, -10, 10, 1, 1000);
	//orthoCamera.setTargetLayer(0x01);
	//orthoCamera.setClearFlags(CameraComponent::CLEAR_COLOR | CameraComponent::CLEAR_DEPTH);
}

MacDemoCameraEntity::~MacDemoCameraEntity()
{
}

PerspectiveCameraComponent &MacDemoCameraEntity::getCamera()
{
	return perspCamera;
}

bool MacDemoCameraEntity::onConstruct()
{
	return true;
}

void MacDemoCameraEntity::onStart()
{
}

void MacDemoCameraEntity::onPause()
{
}

void MacDemoCameraEntity::onResume()
{
}

void MacDemoCameraEntity::onUpdate(float dt)
{
}

void MacDemoCameraEntity::onStop()
{
}

void MacDemoCameraEntity::onDestruct()
{
}

void MacDemoCameraEntity::touchpadEvent(const Input::TouchpadEvent &evt)
{
	debug("MacDemoCameraEntity::touchpadEvent(const Input::TouchpadEvent &evt)");
}

void MacDemoCameraEntity::keypadEvent(const Input::GamepadEvent &evt)
{
	debug("MacDemoCameraEntity::keypadEvent(const Input::GamepadEvent &evt)");
}

void MacDemoCameraEntity::acceleratorEvent(const Input::AcceleratorEvent &evt)
{
	debug("MacDemoCameraEntity::acceleratorEvent(const Input::AcceleratorEvent &evt)");
}