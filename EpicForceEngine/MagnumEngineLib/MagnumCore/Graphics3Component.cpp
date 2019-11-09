///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Stage.h"
#include "CameraComponent.h"
#include "GXDebugRenderer.h"
#include "Graphics3Component.h"
#include "Entity.h"
using namespace Magnum;

Graphics3Component::Graphics3Component(Component::Owner &owner_)
: Component(owner_)
{
}

Graphics3Component::~Graphics3Component()
{
}