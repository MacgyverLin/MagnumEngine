///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _ParticleEmitterRenderer_h_
#define _ParticleEmitterRenderer_h_

#include "Stage.h"
#include "RendererBase.h"
#include "Cube.h"
#include "GXContext.h"
#include "ParticleEmitter.h"
using namespace Magnum;

namespace Magnum
{

/**
* ParticleEmitterRenderer.
* ParticleEmitterRenderer render ParticleEmitter on editor screen.
* @see RendererBase, DiffuseMapSpecularMapCube
*/
class ParticleEmitterRenderer : public RendererBase
{
friend class ParticleEmitter;
////////////////////////////////////////////////////////////////
public:
	/**
	* ParticleEmitterRenderer Constructor.
	* To Construct the ParticleEmitterRenderer for the owner.
	* @param owner_, the Component::Owner which owns this component.
	*/
	ParticleEmitterRenderer(Component::Owner &owner_);

	/**
	* ParticleEmitterRenderer Destructor.
	* To Destruct ParticleEmitterRenderer and remove from its owner.
	*/
	virtual ~ParticleEmitterRenderer();

	DECLARE_COMPONENT(ParticleEmitterRenderer, RendererBase, false)
////////////////////////////////////////////////////////////////
public:
	/**
	* Get the Order of this renderer.
	* The Renderer will sort all the renderer in acending order. The order is returned by this function.
	*/
	virtual int getOrder() const
	{
		return 0x10000000;
	}

	/**
	* add ParticleEmitter to the Renderer.
	* @param particleEmitter, a ParticleEmitter
	* @see ParticleEmitter
	*/
	void add(ParticleEmitter &particleEmitter);

	/**
	* remove ParticleEmitter from the Renderer.
	* @param particleEmitter, a ParticleEmitter
	* @see ParticleEmitter
	*/
	void remove(ParticleEmitter &particleEmitter);
protected:
private:
	/**
	* Render the ParticleEmitter according to view, project described by RenderParam
	* @param param, a Video::Manager::RenderParam
	*/
	virtual void render(const Video::Manager::RenderParam &param);
public:
protected:
private:
	Vector<ParticleEmitter *>	particleEmitters;
};

};

#endif
