///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Stage.h"
#include "CubeRenderer.h"
#include "CameraComponent.h"

CubeRenderer::CubeRenderer(Component::Owner &owner_)
: RendererBase(owner_)
{
}

CubeRenderer::~CubeRenderer()
{
}

void CubeRenderer::add(Cube &cube)
{
	cubes.push() = &cube;
}

void CubeRenderer::remove(Cube &cube)
{
	int idx = cubes.search(&cube);
	if(idx>=0)
	{
		cubes.remove(idx);
	}
}

void CubeRenderer::render(const Video::Manager::RenderParam &param)
{
	if(cubes.length()==0)
		return;

	for(int i=0; i<cubes.length(); i++)
	{
		Cube &cube = *cubes[i];

		VisualEffect &visualEffect		= cube.visualEffect;
		int numUniforms					= visualEffect.getNumUniforms();
		int numAttributes				= visualEffect.getNumAttributes();
		int projViewModelTransformIdx	= visualEffect.getUniformHandle("projViewModelTransform");
		int texCoord0OffsetIdx			= visualEffect.getUniformHandle("texCoord0Offset");
		int texCoord0ScaleIdx			= visualEffect.getUniformHandle("texCoord0Scale");
		int texture0TransformIdx		= visualEffect.getUniformHandle("texture0Transform");
		int colorConstantIdx			= visualEffect.getUniformHandle("colorConstant");
		int textureIdx0					= visualEffect.getTextureHandle("texture0");
		int textureIdx1					= visualEffect.getTextureHandle("texture1");

		TextureBase &texture2D_0		= *visualEffect.getTexture(textureIdx0);
		TextureBase &texture2D_1		= *visualEffect.getTexture(textureIdx1);
		
		Component::Owner &owner = cube.getOwner();
		unsigned int layer = owner.getLayer();

		bool visible = param.cameraComponent.isLayerMatched(layer) && owner.getActive() && cube.getEnabled();
		if(visible)
		{
			Video::Manager::getContext().setVertexBuffer(0, cube.vertexBuffer);
			Video::Manager::getContext().setIndexBuffer(0, cube.indexBuffer);

			Vector3 extent(cube.getExtent());
		
			Matrix4 cubeSizeMat;
			cubeSizeMat.initScale(2*extent.X(), 2*extent.Y(), 2*extent.Z());

			Matrix4 projViewModelMat;
			projViewModelMat = param.projViewTransform * owner.getGlobalTransform() * cubeSizeMat;

			visualEffect.setValue(projViewModelTransformIdx	, projViewModelMat					);
			visualEffect.setValue(texture0TransformIdx		, Matrix2::IDENTITY					);
			visualEffect.setValue(texCoord0OffsetIdx		, Vector2::ZERO						);
			visualEffect.setValue(texCoord0ScaleIdx			, Vector2(1, 1)						);
			visualEffect.setValue(colorConstantIdx			, Vector4(1.0f, 1.0f, 1.0f, 1.0f)	);

			for(int j=0; j<visualEffect.getNumPasses(); j++)
			{
				visualEffect.beginPass(j);

				Video::Manager::getContext().draw(GXDrawMode::Triangles, 0, 36);

				visualEffect.endPass(j);
			}
		}
	}

	Video::Manager::getContext().setVertexBuffer(0, 0);
	Video::Manager::getContext().setIndexBuffer(0, 0);
}