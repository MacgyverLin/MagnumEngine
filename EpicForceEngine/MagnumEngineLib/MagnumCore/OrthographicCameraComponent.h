///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _OrthographicCameraComponent_h_
#define _OrthographicCameraComponent_h_

#include "Stage.h"
#include "CameraComponent.h"
using namespace Magnum;

namespace Magnum
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
* OrthographicCameraComponent.
* OrthographicCameraComponent is a base class for all Orthographic Camera
* @see CameraComponent
*/
class OrthographicCameraComponent : public CameraComponent
{
public:
	/**
	* OrthographicCameraComponent Constructor.
	* To Construct the OrthographicCameraComponent for the owner.
	* @param owner_, the Component::Owner which owns this component.
	*/
	OrthographicCameraComponent(Component::Owner &owner_);

	/**
	* OrthographicCameraComponent Destructor.
	* To Destruct OrthographicCameraComponent and remove from its owner.
	*/
	virtual ~OrthographicCameraComponent();

	DECLARE_COMPONENT(OrthographicCameraComponent, CameraComponent, false)

	/**
	* Set the Width of the near plane of the camera
	* @param value_, float, the Width of the near plane of the camera
	*/
	/**
	* Get the Width of the near plane of the camera
	* @return float, the Width of the near plane of the camera
	*/
	PROPERTY_CUSTOM_FUNC
	(
		float, Width,
		{
			float l;
			float r;
			float b;
			float t;
			float n;
			float f;
			getProjectionPlanes(l, r, b, t, n, f);

			return r*2;
		}
		,
		{
			float l;
			float r;
			float b;
			float t;
			float n;
			float f;
			getProjectionPlanes(l, r, b, t, n, f);
			setProjectionPlanes(-value/2, value/2, b, t, n, f);
		}
	);

	/**
	* Set the Height of the near plane of the camera
	* @param value_, float, the Height of the near plane of the camera
	*/
	/**
	* Get the Height of the near plane of the camera
	* @return float, the Height of the near plane of the camera
	*/
	PROPERTY_CUSTOM_FUNC
	(
		float, Height,
		{
			float l;
			float r;
			float b;
			float t;
			float n;
			float f;
			getProjectionPlanes(l, r, b, t, n, f);

			return t*2;
		}
		,
		{
			float l;
			float r;
			float b;
			float t;
			float n;
			float f;
			getProjectionPlanes(l, r, b, t, n, f);
			setProjectionPlanes(l, r, -value/2, value/2, n, f);
		}
	);

	/**
	* Set the Near Plane of the camera
	* @param value_, float, the Near Plane of the camera
	*/
	/**
	* Get the Near Plane of the camera
	* @return float, the Near Plane of the camera
	*/
	PROPERTY_CUSTOM_FUNC
	(
		float, NearPlane,
		{
			float l;
			float r;
			float b;
			float t;
			float n;
			float f;
			getProjectionPlanes(l, r, b, t, n, f);

			return n;
		},
		{
			float l;
			float r;
			float b;
			float t;
			float n;
			float f;
			getProjectionPlanes(l, r, b, t, n, f);
			setProjectionPlanes(l, r, b, t, value, f);
		}
	);

	/**
	* Set the Far Plane of the camera
	* @param value_, float, the Far Plane of the camera
	*/
	/**
	* Get the Far Plane of the camera
	* @return float, the Far Plane of the camera
	*/
	PROPERTY_CUSTOM_FUNC
	(
		float, FarPlane,
		{
			float l;
			float r;
			float b;
			float t;
			float n;
			float f;
			getProjectionPlanes(l, r, b, t, n, f);

			return f;
		},
		{
			float l;
			float r;
			float b;
			float t;
			float n;
			float f;
			getProjectionPlanes(l, r, b, t, n, f);
			setProjectionPlanes(l, r, b, t, n, value);
		}
	);
////////////////////////////////////////////////////////////////
public:
	/**
	* Set the coordinate of project plane of at the near plane of camera
	* @param left_, float, the left side frustum x coordinate in this camera space
	* @param right_, float, the right side frustum x coordinate in this camera space
	* @param bottom_, float, the bottom side frustum y coordinate in this camera space
	* @param top_, float, the top side frustum y coordinate in this camera space
	* @param nearPlane_, float, the near side frustum z coordinate in this camera space
	* @param farPlane_, float, the far side frustum z coordinate in this camera space
	* @see Redbook of OpenGL Bible for detail of definition of Projection Transform
	*/
	void setProjection(float left_, float right_, float bottom_, float top_, float nearPlane_, float farPlane_);

	/**
	* Get the coordinate of project plane of at the near plane of camera
	* @param left_, float, return the left side frustum x coordinate in this camera space
	* @param right_, float, return the right side frustum x coordinate in this camera space
	* @param bottom_, float, return the bottom side frustum y coordinate in this camera space
	* @param top_, float, return the top side frustum y coordinate in this camera space
	* @param nearPlane_, float, return the near side frustum z coordinate in this camera space
	* @param farPlane_, float, return the far side frustum z coordinate in this camera space
	* @see Redbook of OpenGL Bible for detail of definition of Projection Transform
	*/
	void getProjection(float &left_, float &right_, float &bottom_, float &top_, float &nearPlane_, float &farPlane_) const;
protected:
	/**
	* Handle Debuger Rendering Event of the Component
	*/
	virtual void onDebugRender(IComponentDebugRenderer &debugRenderer);
private:
	virtual void onValidateProjectionTransform(Matrix4 &projectTransform) const;
////////////////////////////////////////////////////////////////
public:
protected:
private:
};

};


#endif