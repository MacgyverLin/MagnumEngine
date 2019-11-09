///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _SkeletalAnimModelRenderer_h_
#define _SkeletalAnimModelRenderer_h_

#include "Stage.h"
#include "RendererBase.h"
#include "GXContext.h"
#include "SkeletalAnimModelComponent.h"
using namespace Magnum;

namespace Magnum
{

/**
* SkeletalAnimModelRenderer.
* SkeletalAnimModelRenderer render SkeletalAnimModel on editor screen.
* @see RendererBase, SkeletalAnimModelRenderer
*/
class SkeletalAnimModelRenderer : public RendererBase
{
friend class SkeletalAnimModelComponent;
////////////////////////////////////////////////////////////////
public:
	/**
	* SkeletalAnimModelRenderer Constructor.
	* To Construct the SkeletalAnimModelRenderer for the owner.
	* @param owner_, the Component::Owner which owns this component.
	*/
	SkeletalAnimModelRenderer(Component::Owner &owner_);

	/**
	* SkeletalAnimModelRenderer Destructor.
	* To Destruct SkeletalAnimModelRenderer and remove from its owner.
	*/
	virtual ~SkeletalAnimModelRenderer();

	DECLARE_COMPONENT(SkeletalAnimModelRenderer, RendererBase, false)
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
	* add SkeletalAnimModelComponent to the Renderer.
	* @param skeletalAnimModelComponent, a SkeletalAnimModelComponent
	* @see SkeletalAnimModelComponent
	*/
	void add(SkeletalAnimModelComponent &skeletalAnimModelComponent);

	/**
	* remove SkeletalAnimModelComponent from the Renderer.
	* @param skeletalAnimModelComponent, a SkeletalAnimModelComponent
	* @see SkeletalAnimModelComponent
	*/
	void remove(SkeletalAnimModelComponent &skeletalAnimModelComponent);
protected:
private:
	/**
	* Render the SkeletalAnimModelComponent according to view, project described by RenderParam
	* @param param, a Video::Manager::RenderParam
	*/
	virtual void render(const Video::Manager::RenderParam &param);

	/**
	* Update the All Bones Global Transform
	* @param skeletalAnimModelComponent, a SkeletalAnimModelComponent
	* @param param, a Video::Manager::RenderParam
	*/
	void updateBonesGlobalTransform(SkeletalAnimModelComponent &skeletalAnimModelComponent, const Video::Manager::RenderParam &param);

	/**
	* Update a Bone Global Transform at the index to bones array specified by currentBoneIdx
	* @param skeletalAnimModelComponent, a SkeletalAnimModelComponent
	* @param currentBoneIdx, the index to bones array
	* @param param, a Video::Manager::RenderParam
	*/
	void updateBoneGlobalTransform(SkeletalAnimModelComponent &skeletalAnimModelComponent, int currentBoneIdx, const Video::Manager::RenderParam &param);

	void setSemanticUniformVariables(SkeletalAnimModelComponent &skeletalAnimModelComponent , const SkeletalAnimModel::Mesh &mesh, const SkeletalAnimModel::Mesh::Patch &patch, const Video::Manager::RenderParam &param);

	/**
	* Render the model, this function iterate all model in the model and call renderMesh to render the meshes
	* @param skeletalAnimModelComponent, a SkeletalAnimModelComponent
	* @param param, a Video::Manager::RenderParam
	* @see SkeletalAnimModelRenderer::renderMesh
	*/
	void renderModel(SkeletalAnimModelComponent &skeletalAnimModelComponent, const Video::Manager::RenderParam &param);

	/**
	* Render the mesh, this function iterate all patch in the mesh and call renderPatch to render the patches
	* @param skeletalAnimModelComponent, a SkeletalAnimModelComponent
	* @param mesh, a SkeletalAnimModel::Mesh
	* @param param, a Video::Manager::RenderParam
	* @see SkeletalAnimModelRenderer::renderPatch
	*/
	void renderMesh(SkeletalAnimModelComponent &skeletalAnimModelComponent, const SkeletalAnimModel::Mesh &mesh, const Video::Manager::RenderParam &param);

	/**
	* Render the patch
	* @param skeletalAnimModelComponent, a SkeletalAnimModelComponent
	* @param mesh, a SkeletalAnimModel::Mesh
	* @param patch, a SkeletalAnimModel::Patch
	* @param param, a Video::Manager::RenderParam
	*/
	void renderPatch(SkeletalAnimModelComponent &skeletalAnimModelComponent, const SkeletalAnimModel::Mesh &mesh, const SkeletalAnimModel::Mesh::Patch &patch, const Video::Manager::RenderParam &param);
public:
protected:
private:
	Vector<SkeletalAnimModelComponent *>		skeletalAnimModelComponents;

	Vector<Matrix4>								meshBoneMatrices;
	Vector<Matrix4>								skeletalModelBoneMatrices;
	Vector<bool>								skeletalModelBoneMatrixValids;
	Vector<Matrix4>								skeletalModelSkinMatrices;

	Array<Vector3>								lightDirections;
	Array<ColorRGBA>							lightColors;
	Array<float>								angles;
};

};

#endif
