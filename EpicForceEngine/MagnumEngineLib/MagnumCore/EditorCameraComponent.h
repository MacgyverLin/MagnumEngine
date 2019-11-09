///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _EditorCameraComponent_h_
#define _EditorCameraComponent_h_

#include "Stage.h"
#include "PerspectiveCameraComponent.h"
using namespace Magnum;

namespace Magnum
{

/**
* EditorCameraComponent.
* EditorCameraComponent is a PerspectiveCameraComponent for editor
* @see PerspectiveCameraComponent
*/
class EditorCameraComponent : public PerspectiveCameraComponent
{
public:
	/**
	* EditorCameraComponent Constructor.
	* To Construct the EditorCameraComponent for the owner.
	* @param owner_, the Component::Owner which owns this component.
	*/
	EditorCameraComponent(Component::Owner &owner);

	/**
	* EditorCameraComponent Destructor.
	* To Destruct EditorCameraComponent and remove from its owner.
	*/
	virtual ~EditorCameraComponent();

	DECLARE_COMPONENT(EditorCameraComponent, PerspectiveCameraComponent, true)
////////////////////////////////////////////////////////////////
public:
protected:
private:
	/**
	* Handle Debuger Rendering Event of the Component
	*/
	virtual void onDebugRender(IComponentDebugRenderer &debugRenderer);
////////////////////////////////////////////////////////////////
public:
protected:
private:
};

};

#endif
