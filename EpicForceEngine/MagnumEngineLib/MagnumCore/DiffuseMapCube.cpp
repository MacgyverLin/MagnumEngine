///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Stage.h"
#include "DiffuseMapCube.h"
#include "DiffuseMapCubeRenderer.h"

const DiffuseMapCube::Vertex vertices[] =
{
	{  0.5f,  0.5f,  0.5f,    0.577f,  0.577f,  0.577f,  0.0f, 0.0f },
	{ -0.5f,  0.5f,  0.5f,   -0.577f,  0.577f,  0.577f,  1.0f, 0.0f },
	{  0.5f, -0.5f,  0.5f,    0.577f, -0.577f,  0.577f,  0.0f, 1.0f },
	{ -0.5f, -0.5f,  0.5f,   -0.577f, -0.577f,  0.577f,  1.0f, 1.0f },
																    
	{  0.5f,  0.5f, -0.5f,    0.577f,  0.577f, -0.577f,  0.0f, 0.0f },
	{ -0.5f,  0.5f, -0.5f,   -0.577f,  0.577f, -0.577f,  1.0f, 0.0f },
	{  0.5f, -0.5f, -0.5f,    0.577f, -0.577f, -0.577f,  0.0f, 1.0f },
	{ -0.5f, -0.5f, -0.5f,   -0.577f, -0.577f, -0.577f,  1.0f, 1.0f },
};

const unsigned short indices[] =
{
	0, 1, 2, 
	2, 1, 3, 

	4, 6, 5, 
	5, 6, 7, 

	1, 5, 3, 
	3, 5, 7, 

	4, 0, 6, 
	6, 0, 2, 

	1, 0, 5, 
	5, 0, 4, 

	3, 7, 2, 
	2, 7, 6, 
};

DiffuseMapCube::DiffuseMapCube(Component::Owner &owner_)
: Graphics3Component(owner_)
, vertexBuffer(0)
, indexBuffer(0)
{
	setShaderPath(ResourcePath("default/defaultDiffusemapShader", "vfx"));
	setTexture0Path(ResourcePath("default/defaultDiffusemapTexture", "texture"));
	setExtent(Vector3(0.5, 0.5, 0.5));

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Vector<GXVertexFormat> formats;
	formats.push() = GXVertexFormat::FLOAT3;
	formats.push() = GXVertexFormat::FLOAT3;
	formats.push() = GXVertexFormat::FLOAT2;

	vertexBuffer = new GXVertexBuffer(8, formats);
	vertexBuffer->setVertices(vertices, 8);

	indexBuffer = new GXIndexBuffer(36);
	indexBuffer->setIndices(indices, 36);
}

DiffuseMapCube::~DiffuseMapCube()
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

bool DiffuseMapCube::onConstruct()
{
	if( !visualEffect.construct(getShaderPath().getPath()) )
		return false;
	
	if( !texture0.construct(getTexture0Path().getPath()) )
		return false;

	int handle;
	handle = visualEffect.getTextureHandle("diffuseMapSampler");
	visualEffect.setTexture(handle, &texture0);

	return true;
}

void DiffuseMapCube::onStart()
{
}

void DiffuseMapCube::onUpdate(float dt)
{
}

void DiffuseMapCube::onPause()
{
}

void DiffuseMapCube::onResume()
{
}

void DiffuseMapCube::onStop()
{
}

void DiffuseMapCube::onDestruct()
{
	visualEffect.destruct();
	texture0.destruct();
}

void DiffuseMapCube::onDebugRender(IComponentDebugRenderer &debugRenderer)
{
	debugRenderer.renderWireBox(this->getOwner().getGlobalTransform(),
								ColorRGBA(0.0, 1.0, 1.0, 0.5), 
								getExtent());
}