///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Stage.h"
#include "SkeletalAnimModelRenderer.h"
#include "CameraComponent.h"
#include "VisualEffect.h"
#include "SkeletalAnimBase.h"
using namespace Magnum;

SkeletalAnimModelRenderer::SkeletalAnimModelRenderer(Component::Owner &owner_)
: RendererBase(owner_)
, lightDirections(3)
, lightColors(3)
, angles(3)
{
	for(int i=0; i<3; i++)
	{
		angles[i] = Math::ONE_PI * i / 3;

		lightColors[i] = ColorRGBA::WHITE;
	}


	///////////////////////////////////////////////////
	meshBoneMatrices.resize(100);
	skeletalModelBoneMatrices.resize(100);
	skeletalModelBoneMatrixValids.resize(100);
	
	skeletalModelSkinMatrices.resize(100);
}

SkeletalAnimModelRenderer::~SkeletalAnimModelRenderer()
{
}

void SkeletalAnimModelRenderer::add(SkeletalAnimModelComponent &skeletalAnimModelComponent)
{
	skeletalAnimModelComponents.push() = &skeletalAnimModelComponent;
}

void SkeletalAnimModelRenderer::remove(SkeletalAnimModelComponent &skeletalAnimModelComponent)
{
	int idx = skeletalAnimModelComponents.search(&skeletalAnimModelComponent);
	if(idx>=0)
	{
		skeletalAnimModelComponents.remove(idx);
	}
}

void SkeletalAnimModelRenderer::render(const Video::Manager::RenderParam &param)
{
	for(int i=0; i<3; i++)
	{
		lightDirections[i].X() = 1;
		lightDirections[i].Y() = 1;
		lightDirections[i].Z() = 1;

		lightDirections[i].Normalize();
	}

	if(skeletalAnimModelComponents.length())
	{
		for(int i=0; i<skeletalAnimModelComponents.length(); i++)
		{
			SkeletalAnimModelComponent &skeletalAnimModelComponent = *skeletalAnimModelComponents[i];

			Component::Owner &owner = skeletalAnimModelComponent.getOwner();
			unsigned int layer = owner.getLayer();

			bool visible =	param.cameraComponent.isLayerMatched(layer) && owner.getActive() && 
							skeletalAnimModelComponent.getEnabled() && skeletalAnimModelComponent.getSkeletalAnimModel();
			if(visible)
			{
				updateBonesGlobalTransform(skeletalAnimModelComponent, param);

				renderModel(skeletalAnimModelComponent, param);
			}
		}
	}

	Video::Manager::getContext().setVertexBuffer(0, 0);
	Video::Manager::getContext().setIndexBuffer(0, 0);
}

void SkeletalAnimModelRenderer::updateBonesGlobalTransform(SkeletalAnimModelComponent &skeletalAnimModelComponent, const Video::Manager::RenderParam &param)
{
	SkeletalAnimModel &skeletalAnimModel = *skeletalAnimModelComponent.getSkeletalAnimModel();

	skeletalModelBoneMatrices.resize(skeletalAnimModel.getNumBones());
	skeletalModelBoneMatrixValids.resize(skeletalAnimModel.getNumBones());

	for(int i=0; i<skeletalAnimModel.getNumBones(); i++)
	{
		skeletalModelBoneMatrixValids[i] =  false;
	}

	for(int i=0; i<skeletalAnimModel.getNumBones(); i++)
	{
		updateBoneGlobalTransform(skeletalAnimModelComponent, i, param);
	}

	for(int i=0; i<skeletalAnimModel.getNumBones(); i++)
	{
		const SkeletalAnimModel::Bone &bone = *(skeletalAnimModel.getBone(i));

		skeletalModelSkinMatrices[i] = skeletalModelBoneMatrices[i] * bone.tBindGlobalTransformInv;		
	}
}

void SkeletalAnimModelRenderer::updateBoneGlobalTransform(SkeletalAnimModelComponent &skeletalAnimModelComponent, int currentBoneIdx, const Video::Manager::RenderParam &param)
{
	if(!skeletalModelBoneMatrixValids[currentBoneIdx])
	{
		SkeletalAnimModel &skeletalAnimModel = *skeletalAnimModelComponent.getSkeletalAnimModel();

		const SkeletalAnimModel::Bone &bone = *(skeletalAnimModel.getBone(currentBoneIdx));
		Matrix4 localMatrix;

		SkeletalAnimBase *animation = skeletalAnimModelComponent.getAnimation();
		if(animation)
		{
			Vector10 v;
			animation->getVector10(currentBoneIdx, v);
			v.ToMatrix4(localMatrix);
			// Vector10 v;
			// skeletalModel.getBoneAnimation(currentBoneIdx).getVector10(frame, v);
			// v.ToMatrix4(localMatrix);
		}
		else
		{
			bone.getLocalTransform(localMatrix);
		}


		int parentBoneIdx = bone.getParentIdx();
		if(parentBoneIdx==-1) // no parent, global = local
		{
			skeletalModelBoneMatrices[currentBoneIdx] = skeletalAnimModelComponent.getOwner().getGlobalTransform() * localMatrix;
			// skeletalModelBoneMatrices[currentBoneIdx] = param.projViewTransform * skeletalModel.getOwner().getGlobalTransform() * localMatrix;
		}
		else
		{
			skeletalModelBoneMatrices[currentBoneIdx] = skeletalModelBoneMatrices[parentBoneIdx] * localMatrix;
		}

		skeletalModelBoneMatrixValids[currentBoneIdx] = true;
	}
}


void SkeletalAnimModelRenderer::setSemanticUniformVariables(SkeletalAnimModelComponent &skeletalAnimModelComponent, const SkeletalAnimModel::Mesh &mesh, const SkeletalAnimModel::Mesh::Patch &patch, const Video::Manager::RenderParam &param)
{
	SkeletalAnimModel &skeletalAnimModel = *skeletalAnimModelComponent.getSkeletalAnimModel();

	int visualEffectInfoIdx = patch.getVisualEffectInfoIdx();
	VisualEffect *visualEffect = skeletalAnimModelComponent.getVisualEffect(visualEffectInfoIdx);
	if(!visualEffect)
		return;

	int handle = -1;
	const SkeletalAnimModel::VisualEffectInfo &info = *(skeletalAnimModel.getVisualEffectInfo(patch.getVisualEffectInfoIdx()));
	const Matrix4 &worldTransform		= skeletalModelBoneMatrices[mesh.attachedNodeIdx];
	Matrix4 worldTransformInverse		= worldTransform.Inverse();

	if(info.getNumBonesPerVertex()!=0)
	{
		handle = visualEffect->getUniformHandleBySemantic(BONETRANSFORMS);
		if( handle!=-1 )
		{
			visualEffect->setValue(handle, meshBoneMatrices[0], mesh.getNumGlobalBoneIndices());
		}
	}
	
	if( (handle = visualEffect->getUniformHandleBySemantic(WORLD)) !=-1 )
	{
		visualEffect->setValue(handle, worldTransform);
	}
	if( (handle = visualEffect->getUniformHandleBySemantic(WORLDINVERSE)) !=-1 )
	{
		visualEffect->setValue(handle, worldTransformInverse);
	}
	if( (handle = visualEffect->getUniformHandleBySemantic(VIEW)) !=-1 )
	{
		visualEffect->setValue(handle, param.viewTransform);
	}
	if( (handle = visualEffect->getUniformHandleBySemantic(VIEWINVERSE)) !=-1 )
	{
		visualEffect->setValue(handle, param.viewTransformInverse);
	}
	if( (handle = visualEffect->getUniformHandleBySemantic(PROJECTION)) !=-1 )
	{
		visualEffect->setValue(handle, param.projTransform);
	}
	if( (handle = visualEffect->getUniformHandleBySemantic(PROJECTIONINVERSE)) !=-1 )
	{
		visualEffect->setValue(handle, param.projTransformInverse);
	}
	if( (handle = visualEffect->getUniformHandleBySemantic(WORLDVIEW)) !=-1 )
	{
		visualEffect->setValue(handle, param.viewTransform * worldTransform);
	}
	if( (handle = visualEffect->getUniformHandleBySemantic(WORLDVIEWINVERSE)) !=-1 )
	{
		// Matrix4 mat1 = worldTransformInverse * param.viewTransformInverse;
		visualEffect->setValue(handle, worldTransformInverse * param.viewTransformInverse);
	}
	if( (handle = visualEffect->getUniformHandleBySemantic(VIEWPROJ)) !=-1 )
	{
		visualEffect->setValue(handle, param.projViewTransform);
	}
	if( (handle = visualEffect->getUniformHandleBySemantic(VIEWPROJINVERSE)) !=-1 )
	{
		visualEffect->setValue(handle, param.projViewTransformInverse);
	}
	if( (handle = visualEffect->getUniformHandleBySemantic(WORLDVIEWPROJ)) !=-1 )
	{
		visualEffect->setValue(handle, param.projViewTransform * worldTransform);
	}
	if( (handle = visualEffect->getUniformHandleBySemantic(WORLDVIEWPROJINVERSE)) !=-1 )
	{
		visualEffect->setValue(handle, worldTransformInverse * param.projViewTransformInverse);
	}
	if( (handle = visualEffect->getUniformHandleBySemantic(VIEWPORTPIXELSIZE)) !=-1 )
	{
		visualEffect->setValue(handle, 1.0f);
	}
	if( (handle = visualEffect->getUniformHandleBySemantic(LOCALBBOXMIN)) !=-1 )
	{
		// TODO:
		// visualEffect->getUniform(handle).setValue(Vector3(-0.5f, -0.5f, -0.5f));
	}
	if( (handle = visualEffect->getUniformHandleBySemantic(LOCALBBOXMAX)) !=-1 )
	{
		// TODO:
		// visualEffect->getUniform(handle).setValue(Vector3( 0.5f,  0.5f,  0.5f));
	}
	if( (handle = visualEffect->getUniformHandleBySemantic(LOCALBBOXSIZE)) !=-1 )
	{
		// TODO:
		// visualEffect->getUniform(handle).setValue(Vector3(1.0f, 1.0f, 1.0f));
	}
	if( (handle = visualEffect->getUniformHandleBySemantic(RECIPLOCALBBOXSIZE)) !=-1 )
	{
		// TODO:
		// visualEffect->getUniform(handle).setValue(Vector3(1.0f, 1.0f, 1.0f));
	}
	if( (handle = visualEffect->getUniformHandleBySemantic(LIGHT0VECTOR)) !=-1 )
	{
		// TODO:
		visualEffect->setValue(handle, lightDirections[0]);
	}
	if( (handle = visualEffect->getUniformHandleBySemantic(LIGHT0COLOR)) !=-1 )
	{
		// TODO:
		visualEffect->setValue(handle, lightColors[0]);
	}
	if( (handle = visualEffect->getUniformHandleBySemantic(LIGHT0ATTENUATION)) !=-1 )
	{
		// TODO:
	}
	if( (handle = visualEffect->getUniformHandleBySemantic(LIGHT1VECTOR)) !=-1 )
	{
		// TODO:
		visualEffect->setValue(handle, lightDirections[0]);
	}
	if( (handle = visualEffect->getUniformHandleBySemantic(LIGHT1COLOR)) !=-1 )
	{
		// TODO:
		visualEffect->setValue(handle, lightColors[0]);
	}
	if( (handle = visualEffect->getUniformHandleBySemantic(LIGHT1ATTENUATION)) !=-1 )
	{
		// TODO:
	}
	if( (handle = visualEffect->getUniformHandleBySemantic(LIGHT2VECTOR)) !=-1 )
	{
		// TODO:
		visualEffect->setValue(handle, lightDirections[0]);
	}
	if( (handle = visualEffect->getUniformHandleBySemantic(LIGHT2COLOR)) !=-1 )
	{
		// TODO:
		visualEffect->setValue(handle, lightColors[0]);
	}
	if( (handle = visualEffect->getUniformHandleBySemantic(LIGHT2ATTENUATION)) !=-1 )
	{
		// TODO:
	}
	if( (handle = visualEffect->getUniformHandleBySemantic(TIME)) !=-1 )
	{
		// TODO:
		visualEffect->setValue(handle, 0);
	}
	if( (handle = visualEffect->getUniformHandleBySemantic(PERIOD)) !=-1 )
	{
		// TODO:
		visualEffect->setValue(handle, 0);
	}
	/*
	if( visualEffect->isTextureSemanticExists(VisualEffect::Semantic(DIFFUSEMAP)) )
	{
	}
	if( visualEffect->isTextureSemanticExists(VisualEffect::Semantic(OPACITYMAP)) )
	{
	}
	if( visualEffect->isTextureSemanticExists(VisualEffect::Semantic(SPECULARMAP)) )
	{
	}
	if( visualEffect->isTextureSemanticExists(VisualEffect::Semantic(NORMALMAP)) )
	{
	}
	if( visualEffect->isTextureSemanticExists(VisualEffect::Semantic(LIGHTMAP)) )
	{
	}
	if( visualEffect->isTextureSemanticExists(VisualEffect::Semantic(DISPLACEMENTMAP)) )
	{
	}
	if( visualEffect->isTextureSemanticExists(VisualEffect::Semantic(REFLECTIONMAP)) )
	{
	}
	if( visualEffect->isTextureSemanticExists(VisualEffect::Semantic(RENDERCOLORTARGET)) )
	{
	}
	if( visualEffect->isTextureSemanticExists(VisualEffect::Semantic(RENDERDEPTHSTENCILTARGET)) )
	{
	}*/
}

void SkeletalAnimModelRenderer::renderModel(SkeletalAnimModelComponent &skeletalAnimModelComponent, const Video::Manager::RenderParam &param)
{
	SkeletalAnimModel &skeletalAnimModel = *skeletalAnimModelComponent.getSkeletalAnimModel();

	for(int i=0; i<skeletalAnimModel.getNumMeshes(); i++)
	{
		const SkeletalAnimModel::Mesh &mesh = *(skeletalAnimModel.getMesh(i));

		renderMesh(skeletalAnimModelComponent, mesh, param);
	}
}

void SkeletalAnimModelRenderer::renderMesh(SkeletalAnimModelComponent &skeletalAnimModelComponent, const SkeletalAnimModel::Mesh &mesh, const Video::Manager::RenderParam &param)
{
	SkeletalAnimModel &skeletalAnimModel = *(skeletalAnimModelComponent.getSkeletalAnimModel());

	for(int i=0; i<mesh.globalBoneIndices.length(); i++)
	{
		meshBoneMatrices[i] = skeletalModelSkinMatrices[mesh.globalBoneIndices[i]];
	}

	for(int i=0; i<mesh.getNumPatches(); i++)
	{
		const SkeletalAnimModel::Mesh::Patch &patch = mesh.getPatch(i);

		renderPatch(skeletalAnimModelComponent, mesh, patch, param);
	}
}

void SkeletalAnimModelRenderer::renderPatch(SkeletalAnimModelComponent &skeletalAnimModelComponent, const SkeletalAnimModel::Mesh &mesh, const SkeletalAnimModel::Mesh::Patch &patch, const Video::Manager::RenderParam &param)
{
	SkeletalAnimModel &skeletalAnimModel = *skeletalAnimModelComponent.getSkeletalAnimModel();

	int visualEffectInfoIdx = patch.getVisualEffectInfoIdx();
	VisualEffect *visualEffect = skeletalAnimModelComponent.getVisualEffect(visualEffectInfoIdx);
	if(!visualEffect)
		return;

	for(int i=0; i<visualEffect->getNumPasses(); i++)
	{
		setSemanticUniformVariables(skeletalAnimModelComponent, mesh, patch, param);

		//visualEffect->beginPass(i);
		visualEffect->applyShader(i);
		visualEffect->applyTexture(i);
		visualEffect->applyRenderState(i);
		visualEffect->applyShaderConstant(i);

		Video::Manager::getContext().setVertexBuffer(0, (GXVertexBuffer *)patch.vb.handle);
		Video::Manager::getContext().setIndexBuffer(0, (GXIndexBuffer *)patch.ib.handle);

		Video::Manager::getContext().draw(GXDrawMode::Triangles, 0, patch.ib.count);

		visualEffect->restoreShaderConstant(i);
		visualEffect->restoreRenderState(i);
		visualEffect->restoreTexture(i);
		visualEffect->restoreShader(i);
		//visualEffect->endPass(i);
	}
}