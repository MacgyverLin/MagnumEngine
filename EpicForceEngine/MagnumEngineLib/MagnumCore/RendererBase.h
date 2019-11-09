///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _BaseRenderer_h_
#define _BaseRenderer_h_

#include "Stage.h"
#include "List.h"
#include "Video.h"
#include "ColorRGBA.h"
#include "Matrix4.h"
#include "Component.h"
using namespace Magnum;

namespace Magnum
{

/**
* RendererBase.
* RendererBase is the base class of all Renderer components.
* The Render System will Render each Renderer that matches the Target Layer of the currently rendering camera
* @see Component
*/
class RendererBase : public Component
{
friend class Video;
////////////////////////////////////////////////////////////////
public:
	/**
	* RendererBase Constructor.
	* To Construct the RendererBase for the owner.
	* @param owner_, the Component::Owner which owns this component.
	*/
	RendererBase(Component::Owner &owner_);

	/**
	* RendererBase Destructor.
	* To Destruct RendererBase and remove from its owner.
	*/
	virtual ~RendererBase();

	DECLARE_COMPONENT(RendererBase, Component, false)
////////////////////////////////////////////////////////////////
public:
	/**
	* Get the Order of this renderer. This is a pure virtual function all sub classes must implmented this function
	* The Renderer will sort all the renderer in acending order. The order is returned by this function.
	*/
	virtual int getOrder() const = 0;
protected:
	static int compare(const void *left, const void *right);
private:
	virtual void render(const Video::Manager::RenderParam &param)		= 0;
};

};

#endif
