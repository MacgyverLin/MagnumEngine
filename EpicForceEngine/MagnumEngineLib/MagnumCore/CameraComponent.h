///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk	z		 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Camera_h_
#define _Camera_h_

#include "Stage.h"
#include "List.h"
#include "Video.h"
#include "ColorRGBA.h"
#include "Matrix4.h"
#include "Component.h"
// #include "RenderTargetTexture.h"
// #include "BaseFilter.h"
#include "String.h"
#include "ColorRGBA.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
using namespace Magnum;

namespace Magnum
{

/**
* CameraComponent.
* CameraComponent is the base class of all CameraComponent component.
* @see Component
*/
class CameraComponent : public Component
{
friend class Video::Manager;
public:
	enum ClearFlag
	{
		CLEAR_NONE		= 0x00,			/**< do not clear */ 
		CLEAR_COLOR		= 0x01,			/**< clear color buffer at each frame by ClearColor */
		CLEAR_DEPTH		= 0x02,			/**< clear depth buffer at each frame by ClearDepth*/ 
		CLEAR_STENCIL	= 0x04,			/**< clear stencil buffer at  each frame by ClearStencil*/
		CLEAR_SKYBOX	= 0x08,			/**< clear color buffer at each frame by SkyBox*/
	};
////////////////////////////////////////////////////////////////
public:
	/**
	* CameraComponent Constructor.
	* To Construct the CameraComponent for the owner.
	* @param owner_, the Component::Owner which owns this component.
	*/
	CameraComponent(Component::Owner &owner_);

	/**
	* CameraComponent Destructor.
	* To Destruct CameraComponent and remove from its owner.
	*/
	virtual ~CameraComponent();

	DECLARE_COMPONENT(CameraComponent, Component, false)

	/**
	* Set the Rendering Order of this Camera
	* @param value_, int, the Rendering Order of this Camera
	*/
	/**
	* Get the Rendering Order of this Camera
	* @return the Rendering Order of this Camera
	*/
	PROPERTY(int, Order);

	/**
	* Set the value of the TargetLayer of this Camera. This camera will only render those Entities with the Layer equal to camera's TargetLayer.
	* @param value_, unsigned int, the value of the TargetLayer of this Camera
	*/
	/**
	* Get the TargetLayer of this Camera
	* @return the TargetLayer of this Camera
	*/
	PROPERTY(unsigned int, TargetLayer);

	/**
	* Set the Clearing Flags of this Camera. ClearFlag can be any one of those specified in CameraComponent::Clearing Flags
	* @param value_, int, the Clearing Flags of this Camera.
	*/
	/**
	* Get the Clearing Flags of this Camera. ClearFlag can be any one of those specified in CameraComponent::Clearing Flags
	* @return int, the Clearing Flags of this Camera.
	*/
	PROPERTY(int, ClearFlags);

	/**
	* Set the Clear Color of this Camera.
	* @param value_, ColorRGBA, the Claring Color of this Camera.
	*/
	/**
	* Get the Clear Color of this Camera.
	* @return ColorRGBA, the Clearing Color of this Camera.
	*/
	PROPERTY(ColorRGBA, ClearColor);

	/**
	* Set the Clear Depth of this Camera.
	* @param value_, float, the Clear Depth of this Camera.
	*/
	/**
	* Get the Clear Depth of this Camera.
	* @return float, the Clear Depth of this Camera.
	*/
	PROPERTY(float, ClearDepth);

	/**
	* Set the Clear Stencil of this Camera.
	* @param value_, unsigned int, the Clear Stencil of this Camera.
	*/
	/**
	* Get the Clear Stencil of this Camera.
	* @return unsigned int, the Clear Stencil of this Camera.
	*/
	PROPERTY(unsigned int, ClearStencil);

	/**
	* Set the Viewport of this Camera.
	* @param value_, Vector4, the x, y, width, height of the view port in screen coordinate.
	*/
	/**
	* Get the Viewport of this Camera.
	* @return Vector4, the x, y, width, height of the view port in screen coordinate.
	*/
	PROPERTY(Vector4, Viewport);
////////////////////////////////////////////////////////////////
	static int compare(const void *left, const  void *right);
public:
	// void setRenderTargetTexture(RenderTargetTexture *renderTargetTexture);

	// void appendFilter(Video::BaseFilter *filter_);

	// void insertFilter(int i, Video::BaseFilter *filter_);

	// void removeFilter(Video::BaseFilter *filter_);

	// Video::BaseFilter *getFilter(int i_) const;

	// int getNumFilters() const;

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
	void setProjectionPlanes(float left_, float right_, float bottom_, float top_, float nearPlane_, float farPlane_);

	/**
	* Get the coordinate of project plane of at the near plane of camera
	* @param left_, float, the left side frustum x coordinate in this camera space is returned thru this parameter
	* @param right_, float, the right side frustum x coordinate in this camera space is returned thru this parameter
	* @param bottom_, float, the bottom side frustum y coordinate in this camera space is returned thru this parameter
	* @param top_, float, the top side frustum y coordinate in this camera space is returned thru this parameter
	* @param nearPlane_, float, the near side frustum z coordinate in this camera space is returned thru this parameter
	* @param farPlane_, float, the far side frustum z coordinate in this camera space is returned thru this parameter
	* @see Redbook of OpenGL Bible for detail of definition of Projection Transform
	*/
	void getProjectionPlanes(float &left_, float &right_, float &bottom_, float &top_, float &nearPlane_, float &farPlane_) const;
	
	/**
	* Get the project transform of this camera
	* @return Matrix4, the projection transform of this camera.
	* @see Redbook of OpenGL Bible for detail of definition of Projection Transform
	*/
	const Matrix4 &getProjectionTransform();

	/**
	* Check if the parameter layer matches TargetLayer to this camera
	* @param layer, unsigned int, the layer to be check
	* @return true: layer matches this camera TargetLayer
	*/
	bool isLayerMatched(unsigned int layer) const;
protected:
	// Video::RenderTargetTexture *getRenderTargetTexture();
	/**
	* Handle Construct Event of the Component
	* @return true if construction is success, return false if fail
	*/
	virtual bool onConstruct();

	/**
	* Handle Start Event of the Component
	*/
	virtual void onStart();

	/**
	* Handle Update Event of the Component
	* @param delta elapse of the game cycle
	*/
	virtual void onUpdate(float dt);

	/**
	* Handle Pause Event of the Component
	*/
	virtual void onPause();

	/**
	* Handle Resume Event of the Component
	*/
	virtual void onResume();

	/**
	* Handle Stop Event of the Component
	*/
	virtual void onStop();

	/**
	* Handle Destruct Event of the Component
	*/
	virtual void onDestruct();

	/**
	* Handle Debuger Rendering Event of the Component
	*/
	virtual void onDebugRender(IComponentDebugRenderer &debugRenderer) = 0;

	/**
	* mark the member variable projectTransformValid is invalide and should be update before next render
	*/
	void inValidateProjectionTransform();

	/**
	* This is a pure virtual function. all sub class should implement this function for their own version of project transform.
	* @param projectTransform, Matrix4, the layer to be check.
	*/
	virtual void onValidateProjectionTransform(Matrix4 &projectTransform) const = 0;
private:
	void validateProjectionTransform();
	bool isProjectionTransformValid() const;
////////////////////////////////////////////////////////////////
public:
protected:
private:
	Matrix4 projectTransform;
	bool projectTransformValid;
	
	float l, r, b, t, n, f;
};

};

#endif
