///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "EditorCameraComponent.h"
using namespace Magnum;

EditorCameraComponent::EditorCameraComponent(Component::Owner &owner_)
: PerspectiveCameraComponent(owner_)
{
}

EditorCameraComponent::~EditorCameraComponent()
{
}

void EditorCameraComponent::onDebugRender(IComponentDebugRenderer &debugRenderer)
{
}