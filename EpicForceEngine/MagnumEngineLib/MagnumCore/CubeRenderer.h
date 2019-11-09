///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _CubeRenderer_h_
#define _CubeRenderer_h_

#include "Stage.h"
#include "RendererBase.h"
#include "Cube.h"
#include "GXContext.h"
using namespace Magnum;

namespace Magnum
{

/**
* CubeRenderer.
* CubeRenderer render Cube on editor screen.
* @see RendererBase, Cube
*/
class CubeRenderer : public RendererBase
{
friend class Cube;
////////////////////////////////////////////////////////////////
public:
	/**
	* CubeRenderer Constructor.
	* To Construct the CubeRenderer for the owner.
	* @param owner_, the Component::Owner which owns this component.
	*/
	CubeRenderer(Component::Owner &owner_);

	/**
	* CubeRenderer Destructor.
	* To Destruct CubeRenderer and remove from its owner.
	*/
	virtual ~CubeRenderer();

	DECLARE_COMPONENT(CubeRenderer, RendererBase, false)
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
	* add Cube to the Renderer.
	* @param cube, a Cube
	* @see Cube
	*/
	void add(Cube &cube);

	/**
	* remove Cube from the Renderer.
	* @param cube, an Cube
	* @see Cube
	*/
	void remove(Cube &cube);
protected:
private:
	virtual void render(const Video::Manager::RenderParam &param);
public:
protected:
private:
	Vector<Cube *>	cubes;

	float time;
};

};

#endif
