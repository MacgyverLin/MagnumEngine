///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _DiffuseMapCube_h_
#define _DiffuseMapCube_h_

#include "Stage.h"
#include "Graphics3Component.h"
#include "Vector2.h"
#include "Texture2DFile.h"
#include "VisualEffect.h"
#include "ResourcePath.h"
using namespace Magnum;

namespace Magnum
{

/**
* DiffuseMapCube Rendering Test Graphics Component
* @see Graphics3Component
*/
class DiffuseMapCube : public Graphics3Component
{
friend class DiffuseMapCubeRenderer;
public:
	typedef struct
	{
		float px, py, pz;
		float nx, ny, nz;
		float u0, v0;
	}Vertex;

////////////////////////////////////////////////////////////////
	/**
	* DiffuseMapCube Constructor.
	* To Construct the DiffuseMapCube for the owner.
	* @param owner_, the DiffuseMapCube::Owner which owns this component.
	*/
	DiffuseMapCube(Component::Owner &owner);

	/**
	* DiffuseMapCube Destructor.
	* To Destruct the DiffuseMapCube for the owner.
	*/
	virtual ~DiffuseMapCube();

	DECLARE_COMPONENT(DiffuseMapCube, Graphics3Component, false)
////////////////////////////////////////////////////////////////
	/**
	* Set the Path of Shader of the DiffuseMapCube
	* @param value_, ResourcePath, the Path of Shader of the DiffuseMapCube
	*/
	/**
	* Get the Path of Shader of the DiffuseMapCube.
	* @return ResourcePath, the Path of Shader of the DiffuseMapCube.
	*/
	PROPERTY(ResourcePath,	ShaderPath);

	/**
	* Set the Path of Texture0 of the DiffuseMapCube.
	* @param value_, ResourcePath, the Path of Texture0 of the DiffuseMapCube.
	*/
	/**
	* Get the Path of Texture0 of the DiffuseMapCube.
	* @return ResourcePath, the Path of Texture0 of the DiffuseMapCube.
	*/
	PROPERTY(ResourcePath,	Texture0Path);

	/**
	* Set the Extent of the DiffuseMapCube.
	* @param value_, Vector3, the Extent of DiffuseMapCube.
	* @see Vector3
	*/
	/**
	* Get the Extent of the DiffuseMapCube.
	* @return , Vector3, the Extent of the DiffuseMapCube.
	* @see Vector3
	*/
	PROPERTY(Vector3     ,	Extent);
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
	Texture2DFile	texture0;

	GXVertexBuffer	*vertexBuffer;
	GXIndexBuffer	*indexBuffer;
};

};

#endif
