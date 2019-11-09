///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Stage.h"
#include "BillBoardRenderer.h"
#include "CameraComponent.h"
using namespace Magnum;

BillBoardRenderer::BillBoardRenderer(Component::Owner &owner_)
: RendererBase(owner_)
{
}

BillBoardRenderer::~BillBoardRenderer()
{
}

void BillBoardRenderer::add(BillBoard &billBoard)
{
	billBoards.push() = &billBoard;
}

void BillBoardRenderer::remove(BillBoard &billBoard)
{
	int idx = billBoards.search(&billBoard);
	if(idx>=0)
	{
		billBoards.remove(idx);
	}
}

void BillBoardRenderer::render(const Video::Manager::RenderParam &param)
{
	if(billBoards.length()==0)
		return;

	for(int i=0; i<billBoards.length(); i++)
	{
		BillBoard &billboard = *billBoards[i];

		VisualEffect &visualEffect		= billboard.visualEffect;
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

		Component::Owner &owner = billboard.getOwner();
		unsigned int layer = owner.getLayer();

		bool visible = param.cameraComponent.isLayerMatched(layer) && owner.getActive() && billboard.getEnabled();
		if(visible)
		{
			Video::Manager::getContext().setVertexBuffer(0, billboard.vertexBuffer);
			Video::Manager::getContext().setIndexBuffer(0, billboard.indexBuffer);

			const Vector3 &position  = billboard.getOwner().getGlobalPosition();
		
			Matrix4 billboardMatrix;
			billboard.getBillBoardMatrix(billboardMatrix, 
										 param.cameraComponent.getOwner().getGlobalTransform(), 
										 param.cameraComponent.getOwner().getGlobalPosition());

			Matrix4 projViewModelMat;
			projViewModelMat = param.projViewTransform * billboardMatrix;

			visualEffect.setValue(projViewModelTransformIdx	, projViewModelMat					);
			visualEffect.setValue(texture0TransformIdx		, Matrix2(2, 0, 0, 2)				);
			visualEffect.setValue(texCoord0OffsetIdx		, Vector2::ZERO						);
			visualEffect.setValue(texCoord0ScaleIdx			, Vector2(2, 2)						);
			visualEffect.setValue(colorConstantIdx			, Vector4(1.0f, 1.0f, 1.0f, 1.0f)	);

			for(int j=0; j<visualEffect.getNumPasses(); j++)
			{
				visualEffect.beginPass(j);

				Video::Manager::getContext().draw(GXDrawMode::Triangles, 0, 6);

				visualEffect.endPass(j);
			}
		}
	}

	Video::Manager::getContext().setVertexBuffer(0, 0);
	Video::Manager::getContext().setIndexBuffer(0, 0);
}