///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Stage.h"
#include "Cube.h"
#include "CubeRenderer.h"

const Cube::Vertex vertices[] =
{
	{  0.5f,  0.5f,  0.5f,   0.0f,0.0f,0.0f,1.0f,  0.0f, 0.0f, 0.0f, 0.0f },
	{ -0.5f,  0.5f,  0.5f,   0.0f,0.0f,1.0f,1.0f,  1.0f, 0.0f, 1.0f, 0.0f },
	{  0.5f, -0.5f,  0.5f,   0.0f,1.0f,1.0f,1.0f,  0.0f, 1.0f, 0.0f, 1.0f },
	{ -0.5f, -0.5f,  0.5f,   1.0f,0.0f,0.0f,1.0f,  1.0f, 1.0f, 1.0f, 1.0f },

	{  0.5f,  0.5f, -0.5f,   1.0f,0.0f,1.0f,1.0f,  0.0f, 0.0f, 0.0f, 0.0f },
	{ -0.5f,  0.5f, -0.5f,   1.0f,1.0f,0.5f,1.0f,  1.0f, 0.0f, 1.0f, 0.0f },
	{  0.5f, -0.5f, -0.5f,   1.0f,1.0f,1.0f,1.0f,  0.0f, 1.0f, 0.0f, 1.0f },
	{ -0.5f, -0.5f, -0.5f,   0.5f,0.5f,0.5f,1.0f,  1.0f, 1.0f, 1.0f, 1.0f },
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

Cube::Cube(Component::Owner &owner_)
: Graphics3Component(owner_)
, vertexBuffer(0)
, indexBuffer(0)
{
	setShaderPath(ResourcePath("default/defaultCubeShader", "vfx"));
	setTexture0Path(ResourcePath("default/defaultCubeTexture0", "texture"));
	setTexture1Path(ResourcePath("default/defaultCubeTexture1", "texture"));
	setExtent(Vector3(0.5, 0.5, 0.5));
	/*
	setTest1Value(1);
	setTest2Value(2.0);
	setTest3Value(Vector2(1.1f, 2.2f));
	setTest4Value(Vector3(1.1f, 2.2f, 3.3f));
	setTest5Value(ColorRGBA(0.1f, 0.2f, 0.3f, 1.0f));
	*/
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Vector<GXVertexFormat> formats;
	formats.push() = GXVertexFormat::FLOAT3;
	formats.push() = GXVertexFormat::FLOAT4;
	//formats.push() = GXVertexFormat::BYTE4N;
	formats.push() = GXVertexFormat::FLOAT2;
	formats.push() = GXVertexFormat::FLOAT2;

	vertexBuffer = new GXVertexBuffer(8, formats);
	vertexBuffer->setVertices(vertices, 8);

	indexBuffer = new GXIndexBuffer(36);
	indexBuffer->setIndices(indices, 36);
}

Cube::~Cube()
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

bool Cube::onConstruct()
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

void Cube::onStart()
{
}

void Cube::onUpdate(float dt)
{
}

void Cube::onPause()
{
}

void Cube::onResume()
{
}

void Cube::onStop()
{
}

void Cube::onDestruct()
{
	visualEffect.destruct();
	texture0.destruct();
	texture1.destruct();
}

void Cube::onDebugRender(IComponentDebugRenderer &debugRenderer)
{
	debugRenderer.renderWireBox(this->getOwner().getGlobalTransform(),
								ColorRGBA(0.0, 1.0, 1.0, 0.5), 
								getExtent());
}