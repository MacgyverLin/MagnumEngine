///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _PerspectiveCameraComponent_h_
#define _PerspectiveCameraComponent_h_

#include "Stage.h"
#include "CameraComponent.h"
using namespace Magnum;

namespace Magnum
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
* PerspectiveCameraComponent.
* PerspectiveCameraComponent is a base class for all Orthographic Camera
* @see CameraComponent
*/
class PerspectiveCameraComponent : public CameraComponent
{
public:
	/**
	* PerspectiveCameraComponent Constructor.
	* To Construct the PerspectiveCameraComponent for the owner.
	* @param owner_, the Component::Owner which owns this component.
	*/
	PerspectiveCameraComponent(Component::Owner &owner_);

	/**
	* PerspectiveCameraComponent Destructor.
	* To Destruct PerspectiveCameraComponent and remove from its owner.
	*/
	virtual ~PerspectiveCameraComponent();

	DECLARE_COMPONENT(PerspectiveCameraComponent, CameraComponent, false)

	/**
	* Set the Field of View in Y Direction of the camera
	* @param value_, float, the Field of View in Y Direction of the camera
	*/
	/**
	* Get the Field of View in Y Direction of the camera
	* @return float, the Field of View in Y Direction of the camera
	*/
	PROPERTY_CUSTOM_FUNC
	(
		float, Fovy,
		{
			float fovy;
			float aspect;
			float nearPlane;
			float farPlane;
			getProjection(fovy, aspect, nearPlane, farPlane);

			return fovy * Math::RAD_2_DEG;
		}
		,
		{
			float fovy;
			float aspect;
			float nearPlane;
			float farPlane;
			getProjection(fovy, aspect, nearPlane, farPlane);
			setProjection(value * Math::DEG_2_RAD, aspect, nearPlane, farPlane);
		}
	);

	/**
	* Set the Aspect Ratio of the camera
	* @param value_, float, the Aspect Ratio of the camera
	*/
	/**
	* Get the  Aspect Ratio of the camera
	* @return float, the Aspect Ratio of the camera
	*/
	PROPERTY_CUSTOM_FUNC
	(
		float, Aspect,
		{
			float fovy;
			float aspect;
			float nearPlane;
			float farPlane;
			getProjection(fovy, aspect, nearPlane, farPlane);

			return aspect;
		}
		,
		{
			float fovy;
			float aspect;
			float nearPlane;
			float farPlane;
			getProjection(fovy, aspect, nearPlane, farPlane);
			setProjection(fovy, value, nearPlane, farPlane);
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
			float fovy;
			float aspect;
			float nearPlane;
			float farPlane;
			getProjection(fovy, aspect, nearPlane, farPlane);

			return nearPlane;
		},
		{
			float fovy;
			float aspect;
			float nearPlane;
			float farPlane;
			getProjection(fovy, aspect, nearPlane, farPlane);
			setProjection(fovy, aspect, value, farPlane);
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
			float fovy;
			float aspect;
			float nearPlane;
			float farPlane;
			getProjection(fovy, aspect, nearPlane, farPlane);

			return farPlane;
		},
		{
			float fovy;
			float aspect;
			float nearPlane;
			float farPlane;
			getProjection(fovy, aspect, nearPlane, farPlane);
			setProjection(fovy, aspect, nearPlane, value);
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
	* Set the coordinate of project plane of at the near plane of camera
	* @param fovy_, float, the field of view in y direction of the camera
	* @param aspect_, float, the aspect ratio of the camera
	* @param nearPlane_, float, the near side frustum z coordinate in this camera space
	* @param farPlane_, float, the far side frustum z coordinate in this camera space
	* @see Redbook of OpenGL Bible for detail of definition of Projection Transform
	*/
	void setProjection(float fovy_, float aspect_, float nearPlane_, float farPlane_);

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

	/**
	* Get the coordinate of project plane of at the near plane of camera
	* @param fovy_, float, return the field of view in y direction of the camera
	* @param aspect_, float, return the aspect ratio of the camera
	* @param nearPlane_, float, return the near side frustum z coordinate in this camera space
	* @param farPlane_, float, return the far side frustum z coordinate in this camera space
	* @see Redbook of OpenGL Bible for detail of definition of Projection Transform
	*/
	void getProjection(float &fovy_, float &aspect_, float &nearPlane_, float &farPlane_) const;
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