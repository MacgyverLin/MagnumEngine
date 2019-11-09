///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _SkySphereRenderer_h_
#define _SkySphereRenderer_h_

#include "Stage.h"
#include "RendererBase.h"
#include "BillBoard.h"
#include "GXContext.h"
#include "VisualEffect.h"
#include "GXVertexBuffer.h"
#include "SkySphere.h"
using namespace Magnum;

namespace Magnum
{

/**
* SkySphereRenderer.
* SkySphereRenderer render SkySphere on editor screen.
* @see RendererBase, SkySphere
*/
class SkySphereRenderer : public RendererBase
{
friend class SkySphere;
////////////////////////////////////////////////////////////////
public:
	/**
	* SkySphereRenderer Constructor.
	* To Construct the SkySphereRenderer for the owner.
	* @param owner_, the Component::Owner which owns this component.
	*/
	SkySphereRenderer(Component::Owner &owner_);

	/**
	* SkySphereRenderer Destructor.
	* To Destruct SkySphereRenderer and remove from its owner.
	*/
	virtual ~SkySphereRenderer();

	DECLARE_COMPONENT(SkySphereRenderer, RendererBase, false)
////////////////////////////////////////////////////////////////
public:
	/**
	* Get the Order of this renderer.
	* The Renderer will sort all the renderer in acending order. The order is returned by this function.
	*/
	virtual int getOrder() const
	{
		return 0x00000001;
	}
	/**
	* add SkySphere to the Renderer.
	* @param skySphere_, a SkySphere
	* @see SkySphere
	*/
	void add(SkySphere &skySphere_);

	/**
	* remove SkySphere from the Renderer.
	* @param skySphere_, a SkySphere
	* @see SkySphere
	*/
	void remove(SkySphere &skySphere_);
protected:
private:
	virtual void render(const Video::Manager::RenderParam &param);
public:
protected:
private:
	Vector<SkySphere *>	skySpheres;
};

};

#endif
