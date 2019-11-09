///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _DiffuseMapCubeRenderer_h_
#define _DiffuseMapCubeRenderer_h_

#include "Stage.h"
#include "RendererBase.h"
#include "DiffuseMapCube.h"
#include "GXContext.h"
using namespace Magnum;

namespace Magnum
{

/**
* DiffuseMapCubeRenderer.
* DiffuseMapCubeRenderer render DiffuseMapCube on editor screen.
* @see RendererBase, DiffuseMapCube
*/
class DiffuseMapCubeRenderer : public RendererBase
{
friend class DiffuseMapCube;
////////////////////////////////////////////////////////////////
public:
	/**
	* CubeRenderer Constructor.
	* To Construct the CubeRenderer for the owner.
	* @param owner_, the Component::Owner which owns this component.
	*/
	DiffuseMapCubeRenderer(Component::Owner &owner_);

	/**
	* CubeRenderer Destructor.
	* To Destruct CubeRenderer and remove from its owner.
	*/
	virtual ~DiffuseMapCubeRenderer();

	DECLARE_COMPONENT(DiffuseMapCubeRenderer, RendererBase, false)
////////////////////////////////////////////////////////////////
public:
	/**
	* Get the Order of this renderer.
	* The Renderer will sort all the renderer in acending order. The order is returned by this function.
	*/
	virtual int getOrder() const
	{
		return 0x00000002;
	}

	/**
	* add DiffuseMapCube to the Renderer.
	* @param cube, a DiffuseMapCube
	* @see DiffuseMapCube
	*/
	void add(DiffuseMapCube &cube);

	/**
	* remove DiffuseMapCube from the Renderer.
	* @param cube, a DiffuseMapCube
	* @see DiffuseMapCube
	*/
	void remove(DiffuseMapCube &cube);
protected:
private:
	virtual void render(const Video::Manager::RenderParam &param);
public:
protected:
private:
	Vector<DiffuseMapCube *>	cubes;

	Array<Vector3>				lightDirections;
	Array<ColorRGBA>			lightColors;
	Array<float>				angles;

	float						time;
};

};

#endif
