///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Stage.h"
#include "ParticleEmitterRenderer.h"
#include "CameraComponent.h"
#include "ParticleEmitter.h"

ParticleEmitterRenderer::ParticleEmitterRenderer(Component::Owner &owner_)
: RendererBase(owner_)
{
}

ParticleEmitterRenderer::~ParticleEmitterRenderer()
{
}

void ParticleEmitterRenderer::add(ParticleEmitter &particleEmitter)
{
	particleEmitters.push() = &particleEmitter;
}

void ParticleEmitterRenderer::remove(ParticleEmitter &particleEmitter)
{
	int idx = particleEmitters.search(&particleEmitter);
	if(idx>=0)
	{
		particleEmitters.remove(idx);
	}
}

void ParticleEmitterRenderer::render(const Video::Manager::RenderParam &param)
{
	if(particleEmitters.length()==0)
		return;

	//for(int i=0; i<particleEmitters.length(); i++)
		//particleEmitters[i]->update();

	for(int i=0; i<particleEmitters.length(); i++)
	{
		ParticleEmitter &particleEmitter = *particleEmitters[i];

		VisualEffect &visualEffect		= particleEmitter.visualEffect;
		int numUniforms					= visualEffect.getNumUniforms();
		int numAttributes				= visualEffect.getNumAttributes();
		int worldTransformIdx			= visualEffect.getUniformHandle("worldTransform");
		int projViewTransformIdx		= visualEffect.getUniformHandle("projViewTransform");
		int textureIdx					= visualEffect.getTextureHandle("texture");
		
		TextureBase &texture0			= *visualEffect.getTexture(textureIdx);

		Component::Owner &owner = particleEmitter.getOwner();
		unsigned int layer = owner.getLayer();

		bool visible = param.cameraComponent.isLayerMatched(layer) && owner.getActive() && particleEmitter.getEnabled();
		if(visible)
		{
			Video::Manager::getContext().setVertexBuffer(0, particleEmitter.vertexBuffer);
			Video::Manager::getContext().setIndexBuffer(0, 0);

			Matrix4 worldMatrix = param.viewTransformInverse;
			visualEffect.setValue(worldTransformIdx,	worldMatrix);

			Matrix4 projViewMat = param.projViewTransform;
			visualEffect.setValue(projViewTransformIdx,	projViewMat);

			for(int j=0; j<visualEffect.getNumPasses(); j++)
			{
				visualEffect.beginPass(j);

				if(particleEmitter.queueTail-particleEmitter.queueHead>0)
				{
					Video::Manager::getContext().draw
					(
						GXDrawMode::Triangles, 
						particleEmitter.queueHead*NUM_VERTICES_PER_PARTICLE,
						particleEmitter.queueTail*NUM_VERTICES_PER_PARTICLE-particleEmitter.queueHead*NUM_VERTICES_PER_PARTICLE
					);
				}
				else if(particleEmitter.queueTail-particleEmitter.queueHead<0)
				{
					Video::Manager::getContext().draw
					(
						GXDrawMode::Triangles, 
						particleEmitter.queueHead*NUM_VERTICES_PER_PARTICLE,
						particleEmitter.vertices.length()-particleEmitter.queueHead*NUM_VERTICES_PER_PARTICLE
					);

					Video::Manager::getContext().draw
					(
						GXDrawMode::Triangles, 
						0*NUM_VERTICES_PER_PARTICLE,
						particleEmitter.queueTail*NUM_VERTICES_PER_PARTICLE
					);
				}

				visualEffect.endPass(j);
			}
		}
	}

	Video::Manager::getContext().setVertexBuffer(0, 0);
	Video::Manager::getContext().setIndexBuffer(0, 0);
}