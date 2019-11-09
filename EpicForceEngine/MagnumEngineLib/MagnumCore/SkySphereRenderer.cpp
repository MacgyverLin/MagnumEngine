///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Stage.h"
#include "SkySphereRenderer.h"
#include "CameraComponent.h"
using namespace Magnum;

SkySphereRenderer::SkySphereRenderer(Component::Owner &owner_)
: RendererBase(owner_)
{
}

SkySphereRenderer::~SkySphereRenderer()
{
}

void SkySphereRenderer::add(SkySphere &skySphere_)
{
	skySpheres.push() = &skySphere_;
}

void SkySphereRenderer::remove(SkySphere &skySphere_)
{
	int idx = skySpheres.search(&skySphere_);
	if(idx>=0)
	{
		skySpheres.remove(idx);
	}
}

void SkySphereRenderer::render(const Video::Manager::RenderParam &param)
{
	if(skySpheres.length()==0)
		return;

	SkySphere &skySphere			= *skySpheres[0];

	VisualEffect &visualEffect		= skySphere.visualEffect;
	int numUniforms					= visualEffect.getNumUniforms();
	int numAttributes				= visualEffect.getNumAttributes();
	int worldMatIdx					= visualEffect.getUniformHandle("worldMat");
	int viewProjMatIdx				= visualEffect.getUniformHandle("viewProjMat");
	int viewIMatIdx					= visualEffect.getUniformHandle("viewIMat");
	int sizeIdx						= visualEffect.getUniformHandle("size");
	int diffuseMapSamplerIdx		= visualEffect.getTextureHandle("diffuseMapSampler");
	
	TextureBase &diffuseMap			= skySphere.texture;

	Component::Owner &owner			= skySphere.getOwner();
	unsigned int layer				= owner.getLayer();
	
	bool visible =	param.cameraComponent.isLayerMatched(layer) && owner.getActive() && skySpheres[0]->getEnabled();
	if(visible)
	{
		Video::Manager::getContext().setVertexBuffer(0, skySphere.vertexBuffer);
		Video::Manager::getContext().setIndexBuffer(0, skySphere.indexBuffer);

		float l, r, b, t, n, f;
		param.cameraComponent.getProjectionPlanes(l, r, b, t, n, f);
		float size = (n + f) * 0.5f;
		
		visualEffect.setValue(worldMatIdx	, owner.getGlobalTransform());
		visualEffect.setValue(viewProjMatIdx, param.projViewTransform);
		visualEffect.setValue(viewIMatIdx	, param.viewTransformInverse);
		visualEffect.setValue(sizeIdx		, size);
	
		for(int j=0; j<visualEffect.getNumPasses(); j++)
		{
			visualEffect.beginPass(j);
	
			Video::Manager::getContext().draw(GXDrawMode::Triangles, 0, skySphere.indexBuffer->getIndexCount());
	
			visualEffect.endPass(j);
		}
	}
	
	Video::Manager::getContext().setVertexBuffer(0, 0);
	Video::Manager::getContext().setIndexBuffer(0, 0);
}