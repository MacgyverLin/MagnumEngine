///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Stage.h"
#include "DiffuseMapCubeRenderer.h"
#include "CameraComponent.h"

DiffuseMapCubeRenderer::DiffuseMapCubeRenderer(Component::Owner &owner_)
: RendererBase(owner_)
, lightDirections(3)
, lightColors(3)
, angles(3)
, time(0)
{
	for(int i=0; i<3; i++)
	{
		angles[i] = Math::ONE_PI * i / 3;

		lightColors[i] = ColorRGBA::WHITE;
	}
}

DiffuseMapCubeRenderer::~DiffuseMapCubeRenderer()
{
}

void DiffuseMapCubeRenderer::add(DiffuseMapCube &cube)
{
	cubes.push() = &cube;
}

void DiffuseMapCubeRenderer::remove(DiffuseMapCube &cube)
{
	int idx = cubes.search(&cube);
	if(idx>=0)
	{
		cubes.remove(idx);
	}
}

void DiffuseMapCubeRenderer::render(const Video::Manager::RenderParam &param)
{
	for(int i=0; i<3; i++)
	{
		lightDirections[i].X() = 0.6 * Math::Cos(angles[i]);
		lightDirections[i].Y() = 0.0;
		lightDirections[i].Z() = 0.6 * Math::Sin(angles[i]);
		angles[i] += 0.3 * Math::DEG_2_RAD;
	}

	time += ((float)Stage::elapsed()) / 1000.0f;

	if(cubes.length()==0)
		return;

	for(int i=0; i<cubes.length(); i++)
	{
		DiffuseMapCube &cube = *cubes[i];

		VisualEffect &visualEffect		= cube.visualEffect;
		int numUniforms					= visualEffect.getNumUniforms();
		int numAttributes				= visualEffect.getNumAttributes();
		int ambientLightColorIdx		= visualEffect.getUniformHandle("ambientLightColor");
		int dirLightDirIdx				= visualEffect.getUniformHandle("dirLightDir");
		int dirLightColorIdx			= visualEffect.getUniformHandle("dirLightColor");
		int worldMatIdx					= visualEffect.getUniformHandle("worldMat");
		int viewMatIdx					= visualEffect.getUniformHandle("viewMat");
		int worldViewMatIdx				= visualEffect.getUniformHandle("worldViewMat");
		int viewProjMatIdx				= visualEffect.getUniformHandle("viewProjMat");
		int diffuseMapSamplerIdx		= visualEffect.getTextureHandle("diffuseMapSampler");

		TextureBase &texture0			= *visualEffect.getTexture(diffuseMapSamplerIdx);

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

			Matrix4 worldMat;
			worldMat = owner.getGlobalTransform() * cubeSizeMat;

			Matrix4 viewWorldMat;
			viewWorldMat = param.viewTransform * worldMat;

			visualEffect.setValue(ambientLightColorIdx	, Vector4(0.3f, 0.3f, 0.3f, 1.0f)	);
			visualEffect.setValue(dirLightDirIdx		, lightDirections[0]				);
			visualEffect.setValue(dirLightColorIdx		, Vector4(0.7f, 0.7f, 0.7f, 1.0f)	);
			visualEffect.setValue(worldMatIdx			, worldMat							);
			visualEffect.setValue(viewMatIdx			, param.viewTransform				);
			visualEffect.setValue(worldViewMatIdx		, viewWorldMat						);
			visualEffect.setValue(viewProjMatIdx		, param.projViewTransform			);

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