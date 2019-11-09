///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _SkySphere_h_
#define _SkySphere_h_

#include "Stage.h"
#include "Graphics3Component.h"
#include "VisualEffect.h"
#include "Texture2DFile.h"
#include "ResourcePath.h"
using namespace Magnum;

namespace Magnum
{

/**
* SkySphere Rendering Test Graphics Component
* @see Graphics3Component
*/
class SkySphere : public Graphics3Component
{
friend class SkySphereRenderer;
public:
	typedef struct
	{
		float x, y, z;
		float u0, v0;
	}Vertex;

////////////////////////////////////////////////////////////////
	/**
	* SkySphere Constructor.
	* To Construct the SkySphere for the owner.
	* @param owner_, the SkySphere::Owner which owns this component.
	*/
	SkySphere(Component::Owner &owner);

	/**
	* SkySphere Destructor.
	* To Destruct the SkySphere for the owner.
	*/
	virtual ~SkySphere();

	DECLARE_COMPONENT(SkySphere, Graphics3Component, false)

	/**
	* Set the Path of Shader of the SkySphere
	* @param value_, ResourcePath, the Path of Shader of the SkySphere
	*/
	/**
	* Get the Path of Shader of the SkySphere.
	* @return ResourcePath, the Path of Shader of the SkySphere.
	*/
	PROPERTY(ResourcePath, ShaderPath);

	/**
	* Set the Path of Texture of the SkySphere.
	* @param value_, ResourcePath, the Path of Texture of the SkySphere.
	*/
	/**
	* Get the Path of Texture of the SkySphere.
	* @return ResourcePath, the Path of Texture of the SkySphere.
	*/
	PROPERTY(ResourcePath, TexturePath);
////////////////////////////////////////////////////////////////
public:
protected:
private:
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
	virtual void onDebugRender(IComponentDebugRenderer &debugRenderer);
public:
protected:
private:
	VisualEffect	visualEffect;
	Texture2DFile	texture;

	GXVertexBuffer	*vertexBuffer;
	GXIndexBuffer	*indexBuffer;
};

};

#endif
