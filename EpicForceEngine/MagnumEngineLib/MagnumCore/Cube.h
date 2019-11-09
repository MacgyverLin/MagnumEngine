///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Cube_h_
#define _Cube_h_

#include "Stage.h"
#include "Graphics3Component.h"
#include "Vector2.h"
#include "Vector3.h"
#include "ColorRGBA.h"
#include "Texture2DFile.h"
#include "VisualEffect.h"
#include "ResourcePath.h"
using namespace Magnum;

namespace Magnum
{

/**
* Cube Rendering Test Graphics Component
* @see Graphics3Component
*/
class Cube : public Graphics3Component
{
friend class CubeRenderer;
public:
	typedef struct
	{
		float x, y, z;
		float r, g, b, a;
		// unsigned char r, g, b, a;
		float u0, v0, u1, v1;
	}Vertex;

////////////////////////////////////////////////////////////////
	/**
	* Cube Constructor.
	* To Construct the Cube for the owner.
	* @param owner_, the Component::Owner which owns this component.
	*/
	Cube(Component::Owner &owner);

	/**
	* Cube Destructor.
	* To Destruct the Cube for the owner.
	*/
	virtual ~Cube();

	DECLARE_COMPONENT(Cube, Graphics3Component, false)
////////////////////////////////////////////////////////////////
	/**
	* Set the Path of Shader of the Cube
	* @param value_, ResourcePath, the Path of Shader of the Cube
	*/
	/**
	* Get the Path of Shader of the Cube.
	* @return ResourcePath, the Path of Shader of the Cube.
	*/
	PROPERTY(ResourcePath,	ShaderPath);

	/**
	* Set the Path of Texture0 of the Cube.
	* @param value_, ResourcePath, the Path of Texture0 of the Cube.
	*/
	/**
	* Get the Path of Texture0 of the Cube.
	* @return ResourcePath, the Path of Texture0 of the Cube.
	*/
	PROPERTY(ResourcePath,	Texture0Path);

	/**
	* Set the Path of Texture1 of the Cube.
	* @param value_, ResourcePath, the Path of Texture1 of the Cube.
	*/
	/**
	* Get the Path of Texture1 of the Cube.
	* @return ResourcePath, the Path of Texture1 of the Cube.
	*/
	PROPERTY(ResourcePath,	Texture1Path);

	/**
	* Set the Extent of the Cube.
	* @param value_, Vector3, the Extent of Cube.
	* @see Vector3
	*/
	/**
	* Get the Extent of the Cube.
	* @return , Vector3, the Extent of the Cubes.
	* @see Vector3
	*/
	PROPERTY(Vector3     ,	Extent);
	//PROPERTY(int		 ,	Test1Value);
	//PROPERTY(float		 ,	Test2Value);
	//PROPERTY(Vector2	 ,	Test3Value);
	//PROPERTY(Vector3	 ,	Test4Value);
	//PROPERTY(ColorRGBA	 ,	Test5Value);
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
	Texture2DFile	texture1;

	GXVertexBuffer	*vertexBuffer;
	GXIndexBuffer	*indexBuffer;
};

};

#endif
