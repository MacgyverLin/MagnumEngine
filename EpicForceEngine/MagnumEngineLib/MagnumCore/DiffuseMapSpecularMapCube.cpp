///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Stage.h"
#include "DiffuseMapSpecularMapCube.h"
#include "DiffuseMapSpecularMapCubeRenderer.h"

const DiffuseMapSpecularMapCube::Vertex vertices[] =
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

DiffuseMapSpecularMapCube::DiffuseMapSpecularMapCube(Component::Owner &owner_)
: Graphics3Component(owner_)
, vertexBuffer(0)
, indexBuffer(0)
{
	setShaderPath(ResourcePath("default/defaultDiffuseMapSpecularShader", "vfx"));
	setTexture0Path(ResourcePath("default/defaultDiffuseMapSpecularTexture0", "texture"));
	setTexture1Path(ResourcePath("default/defaultDiffuseMapSpecularTexture1", "texture"));
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

DiffuseMapSpecularMapCube::~DiffuseMapSpecularMapCube()
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

bool DiffuseMapSpecularMapCube::onConstruct()
{
	if( !visualEffect.construct(getShaderPath().getPath()) )
		return false;
	
	if( !texture0.construct(getTexture0Path().getPath()) )
		return false;

	if( !texture1.construct(getTexture1Path().getPath()) )
		return false;

	int handle;
	handle = visualEffect.getTextureHandle("diffuseMapSampler");
	visualEffect.setTexture(handle, &texture0);
	handle = visualEffect.getTextureHandle("glossMapSampler");
	visualEffect.setTexture(handle, &texture1);

	return true;
}

void DiffuseMapSpecularMapCube::onStart()
{
}

void DiffuseMapSpecularMapCube::onUpdate(float dt)
{
}

void DiffuseMapSpecularMapCube::onPause()
{
}

void DiffuseMapSpecularMapCube::onResume()
{
}

void DiffuseMapSpecularMapCube::onStop()
{
}

void DiffuseMapSpecularMapCube::onDestruct()
{
	visualEffect.destruct();
	texture0.destruct();
	texture1.destruct();
}

void DiffuseMapSpecularMapCube::onDebugRender(IComponentDebugRenderer &debugRenderer)
{
	debugRenderer.renderWireBox(this->getOwner().getGlobalTransform(),
								ColorRGBA(0.0, 1.0, 1.0, 0.5), 
								getExtent());
}