///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Stage.h"
#include "BillBoard.h"
#include "BillBoardRenderer.h"
using namespace Magnum;

const BillBoard::Vertex vertices[] =
{
	{  0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 0.0f, 0.0f },
	{ -0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 0.0f, 1.0f, 0.0f },
	{  0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f, 1.0f },
	{ -0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f, 1.0f },
};

const unsigned short indices[] =
{
	0, 1, 2, 
	2, 1, 3, 
};

BillBoard::BillBoard(Component::Owner &owner_)
: Graphics3Component(owner_)

, mode(BillBoard::CAMERA_Z)
, axis(Vector3::UNIT_Y)
, pivot(Vector3::ZERO)

, vertexBuffer(0)
, indexBuffer(0)
{
	setShaderPath(ResourcePath("default/defaultBillBoardShader", "vfx") );
	setTexture0Path(ResourcePath("default/defaultBillBoardTexture0", "texture") );
	setTexture1Path(ResourcePath("default/defaultBillBoardTexture1", "texture") );
	setSize(Vector2(1, 1));


	///////////////////////////////////////////////////////////
	Vector<GXVertexFormat> formats;
	formats.push() = GXVertexFormat::FLOAT3;
	formats.push() = GXVertexFormat::FLOAT4;
	//formats.push() = GXVertexFormat::BYTE4N;
	formats.push() = GXVertexFormat::FLOAT2;
	formats.push() = GXVertexFormat::FLOAT2;

	vertexBuffer = new GXVertexBuffer(4, formats);
	vertexBuffer->setVertices<Vertex>(&vertices[0], 4);
	
	indexBuffer = new GXIndexBuffer(6);
	indexBuffer->setIndices(indices, 6);
}

BillBoard::~BillBoard()
{
	if(vertexBuffer)
	{
		delete vertexBuffer;		
		vertexBuffer	= 0;
	}
	if(indexBuffer)
	{
		delete indexBuffer;		
		indexBuffer	= 0;
	}
}

void BillBoard::setAlignmentMode(const BillBoard::Alignment &mode_)
{
	mode = mode_;
}

const BillBoard::Alignment &BillBoard::getAlignmentMode() const
{
	return mode;
}

void BillBoard::setAlignmentAxis(const Vector3 &axis_)
{
	axis = axis_;
}

const Vector3 &BillBoard::getAlignmentAxis() const
{
	return axis;
}

void BillBoard::setRotationPivot(const Vector3 &pivot_)
{
	pivot = pivot_;
}

const Vector3 &BillBoard::getRotationPivot() const
{
	return pivot;
}

void BillBoard::getBillBoardMatrix(Matrix4 &matrix, 
								   const Matrix4 &globalTransform, const Vector3 &globalPosition)
{
	if(mode==BillBoard::CAMERA_Z)
	{
		const Vector3 &billboardPosition    = getOwner().getGlobalPosition();
		const Matrix4 &transform			= globalTransform;

		matrix.Set(transform[0][0], transform[0][1], transform[0][2], billboardPosition[0],
				   transform[1][0], transform[1][1], transform[1][2], billboardPosition[1],
				   transform[2][0], transform[2][1], transform[2][2], billboardPosition[2],
				   transform[3][0], transform[3][1], transform[3][2],					 1);
	}
	else if(mode==BillBoard::ROTATE_ABOUT_CAMERA)
	{
		const Vector3 &billboardPosition  = getOwner().getGlobalPosition();
		const Vector3 &cameraPosition     = globalPosition;

		matrix.initLookAt(billboardPosition, cameraPosition, Vector3::UNIT_Y);
	}
	else if(mode==BillBoard::ROTATE_ABOUT_AXIS)
	{
		const Vector3 &billboardPosition	= getOwner().getGlobalPosition();
		const Vector3 &alignmentAxis		= getAlignmentAxis();
		const Vector3 &cameraPosition		= globalPosition;

		Vector3 yaxis = alignmentAxis						 ; yaxis.Normalize();
		Vector3 zaxis = billboardPosition - cameraPosition   ; zaxis.Normalize();
		Vector3 xaxis = yaxis.Cross(zaxis);					 ; xaxis.Normalize(); 	

		matrix.Set(xaxis[0], yaxis[0], zaxis[0], billboardPosition[0],
				   xaxis[1], yaxis[1], zaxis[1], billboardPosition[1],
				   xaxis[2], yaxis[2], zaxis[2], billboardPosition[2],
				          0,        0,        0,                   1);
	}
	else if(mode==BillBoard::ROTATE_ABOUT_PIVOT)
	{
		const Vector3 &billboardPosition  = getOwner().getGlobalPosition();
		const Vector3 &cameraPosition     = globalPosition;

		matrix.initLookAt(billboardPosition, pivot, Vector3::UNIT_Y);
	}

	Vector2 size(getSize());
	matrix[0][0] *= size.X(); matrix[0][1] *= size.Y();
	matrix[1][0] *= size.X(); matrix[1][1] *= size.Y();
	matrix[2][0] *= size.X(); matrix[2][1] *= size.Y();
}

bool BillBoard::onConstruct()
{
	if( !visualEffect.construct(getShaderPath().getPath()) )
		return false;
	
	if( !texture0.construct(getTexture0Path().getPath()) )
		return false;

	if( !texture1.construct(getTexture1Path().getPath()) )
		return false;

	int handle;
	handle = visualEffect.getTextureHandle("texture0");
	visualEffect.setTexture(handle, &texture0);
	handle = visualEffect.getTextureHandle("texture1");
	visualEffect.setTexture(handle, &texture1);

	return true;
}

void BillBoard::onStart()
{
}

void BillBoard::onUpdate(float dt)
{
}

void BillBoard::onPause()
{
}

void BillBoard::onResume()
{
}

void BillBoard::onStop()
{
}

void BillBoard::onDestruct()
{
	visualEffect.destruct();
	texture0.destruct();
	texture1.destruct();
}

void BillBoard::onDebugRender(IComponentDebugRenderer &debugRenderer)
{
	debugRenderer.renderWireBox(this->getOwner().getGlobalTransform(),
								ColorRGBA(0.0, 1.0, 1.0, 0.5), 
								Vector3(getSize().X(), getSize().Y(), 0));
}