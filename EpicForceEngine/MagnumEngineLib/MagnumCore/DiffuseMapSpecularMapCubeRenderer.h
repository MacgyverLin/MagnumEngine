///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _DiffuseMapSpecularMapCubeRenderer_h_
#define _DiffuseMapSpecularMapCubeRenderer_h_

#include "Stage.h"
#include "RendererBase.h"
#include "DiffuseMapSpecularMapCube.h"
#include "GXContext.h"
using namespace Magnum;

namespace Magnum
{

/**
* DiffuseMapSpecularMapCubeRenderer.
* DiffuseMapSpecularMapCubeRenderer render DiffuseMapSpecularMapCube on editor screen.
* @see RendererBase, DiffuseMapSpecularMapCube
*/
class DiffuseMapSpecularMapCubeRenderer : public RendererBase
{
friend class DiffuseMapSpecularMapCube;
////////////////////////////////////////////////////////////////
public:
	/**
	* DiffuseMapSpecularMapCubeRenderer Constructor.
	* To Construct the DiffuseMapSpecularMapCubeRenderer for the owner.
	* @param owner_, the Component::Owner which owns this component.
	*/
	DiffuseMapSpecularMapCubeRenderer(Component::Owner &owner_);

	/**
	* DiffuseMapSpecularMapCubeRenderer Destructor.
	* To Destruct DiffuseMapSpecularMapCubeRenderer and remove from its owner.
	*/
	virtual ~DiffuseMapSpecularMapCubeRenderer();

	DECLARE_COMPONENT(DiffuseMapSpecularMapCubeRenderer, RendererBase, false)
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
	* add DiffuseMapSpecularMapCube to the Renderer.
	* @param cube, a DiffuseMapSpecularMapCube
	* @see DiffuseMapSpecularMapCube
	*/
	void add(DiffuseMapSpecularMapCube &cube);

	/**
	* remove DiffuseMapSpecularMapCube from the Renderer.
	* @param cube, a DiffuseMapSpecularMapCube
	* @see DiffuseMapSpecularMapCube
	*/
	void remove(DiffuseMapSpecularMapCube &cube);
protected:
private:
	virtual void render(const Video::Manager::RenderParam &param);

public:
protected:
private:
	Vector<DiffuseMapSpecularMapCube *>	cubes;

	Array<Vector3>				lightDirections;
	Array<ColorRGBA>			lightColors;
	Array<float>				angles;

	float						time;
};

};

#endif
