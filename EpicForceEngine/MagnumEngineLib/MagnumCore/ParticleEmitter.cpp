///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Stage.h"
#include "ParticleEmitter.h"
#include "ParticleEmitterRenderer.h"

ParticleEmitter::ParticleEmitter(Component::Owner &owner_)
: Graphics3Component(owner_)
, currentTime(0)
, queueHead(0)
, queueTail(0)
, newParticleAccum(0)

, vertexBuffer(0)
{
	setShaderPath			(ResourcePath("default/defaultParticleEmitterShader" , "vfx")		);
	setTexturePath			(ResourcePath("default/defaultParticleEmitterTexture", "texture")	);
	setInitialVelocityDelta	(Vector3(0, 0, 0)													);
	setInitialVelocity		(Vector3(0, 0, -10)													);
	setAcceleration			((Vector3(0, 0, -7) - Vector3(0, 0, -10)) / 10.0f					);
	setStartColor			(ColorRGBA(1, 0, 0, 1)												);
	setEndColor				(ColorRGBA(0.01, 1, 0.01, 0)										);
	setTextureColumn		(4																	);
	setTextureRow			(4																	);
	setFramesPerSecond		(4																	);
	setDuration				(10																	);
	setEmissionRate			(5																	);
	setStartSize			(Vector2(10, 10)													);
	setEndSize				(Vector2(60, 60)													);
						   
	setEmitting				(false																);
}

ParticleEmitter::~ParticleEmitter()
{
}

bool ParticleEmitter::onConstruct()
{
	if( !visualEffect.construct(getShaderPath().getPath()) )
		return false;
	
	if( !texture.construct(getTexturePath().getPath()) )
		return false;

	int textureIdx = visualEffect.getTextureHandle("texture");
	visualEffect.setTexture(textureIdx, &texture);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int maxNumParticles = getEmissionRate() * getDuration() * 2.0f;

	vertices.resize(maxNumParticles*NUM_VERTICES_PER_PARTICLE);
	System::memset(&vertices[0], 0, vertices.length());

	Vector<GXVertexFormat> formats;
	formats.push() = GXVertexFormat::UBYTE4N;
	formats.push() = GXVertexFormat::FLOAT4;
	formats.push() = GXVertexFormat::FLOAT3;
	formats.push() = GXVertexFormat::FLOAT3;
	formats.push() = GXVertexFormat::FLOAT4;
	formats.push() = GXVertexFormat::UBYTE4N;
	formats.push() = GXVertexFormat::UBYTE4N;
	vertexBuffer = new GXVertexBuffer(vertices.length(), formats, GXVertexBuffer::DYNAMIC);
	vertexBuffer->setVertices(&vertices[0], vertices.length());

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	currentTime			= 0;
	queueHead			= 0;
	queueTail			= 0;
	newParticleAccum	= 0;

	int handle;
	handle = visualEffect.getUniformHandle("currentTime");
	visualEffect.setValue(handle, currentTime);
	handle = visualEffect.getUniformHandle("invDuration");
	visualEffect.setValue(handle, 1.0f/getDuration());
	handle = visualEffect.getUniformHandle("invTextureRowColumn");
	visualEffect.setValue(handle, Vector2(1.0f/getTextureColumn(), 1.0f/getTextureRow()));
	handle = visualEffect.getUniformHandle("framesPerSecond");
	visualEffect.setValue(handle, getFramesPerSecond());

	return true;
}

void ParticleEmitter::onStart()
{
}

void ParticleEmitter::onUpdate(float dt)
{
	bool emitting = this->getEmitting();
	if(emitting)
	{
		int a = 1;
	}

	if(!Stage::isEditorMode() || this->getOwner().isSelected())
		updateParticles(dt);

	if(Stage::isEditorMode() && !this->getOwner().isSelected() )
	{
		currentTime			= 0;
		queueHead			= 0;
		queueTail			= 0;
		newParticleAccum	= 0;
	}
}

void ParticleEmitter::onPause()
{
}

void ParticleEmitter::onResume()
{
}

void ParticleEmitter::onStop()
{
}

void ParticleEmitter::onDestruct()
{
	if(vertexBuffer)
	{
		delete vertexBuffer;		
		vertexBuffer = 0;
	}

	texture.destruct();
	
	visualEffect.destruct();
}

void ParticleEmitter::onDebugRender(IComponentDebugRenderer &debugRenderer)
{
}

void ParticleEmitter::createParticles(int startIdx, int endIdx, float particleTime, float timePerParticles)
{
	Vector3 initialPosition = getOwner().getGlobalPosition();
	unsigned int startCol	= getStartColor().toInteger();
	unsigned int endCol		= getEndColor().toInteger();

	int idx					= startIdx * NUM_VERTICES_PER_PARTICLE;

	const Matrix4 &transform = this->getOwner().getGlobalTransform();
	Vector3 initialVelocityDelta(transform.TimesDirectionVector(getInitialVelocityDelta()));
	Vector3 initialVelocity(transform.TimesDirectionVector(getInitialVelocity()));
	Vector3 acceleration(transform.TimesDirectionVector(getAcceleration()));

	for(int i=startIdx; i<endIdx; i++)
	{
		Vector3 velocityDelta
		(
			Math::IntervalRandom(-initialVelocityDelta.X(), initialVelocityDelta.X()),
			Math::IntervalRandom(-initialVelocityDelta.Y(), initialVelocityDelta.Y()),
			Math::IntervalRandom(-initialVelocityDelta.Z(), initialVelocityDelta.Z())
		);
		Vector3 velocity(initialVelocity + velocityDelta);
		
		int startFrame   = ((int)(Math::IntervalRandom(0, 1) * getTextureRow() * getTextureColumn()))<<16;

		vertices[idx+0].set(0x0001ffff | startFrame, particleTime, 
						    initialPosition, velocity, acceleration,
							startCol, endCol, getStartSize(), getEndSize());

		vertices[idx+1].set(0x0001ff00 | startFrame, particleTime, 
						    initialPosition, velocity, acceleration,
							startCol, endCol, getStartSize(), getEndSize());

		vertices[idx+2].set(0x000100ff | startFrame, particleTime, 
						    initialPosition, velocity, acceleration,
							startCol, endCol, getStartSize(), getEndSize());

		vertices[idx+3] = vertices[idx+2];

		vertices[idx+4] = vertices[idx+1];

		vertices[idx+5].set(0x00010000 | startFrame, particleTime, 
						    initialPosition, velocity, acceleration,
							startCol, endCol, getStartSize(), getEndSize());

		idx				+= NUM_VERTICES_PER_PARTICLE;
		particleTime	+= timePerParticles;
	}

	vertexBuffer->setVertices(&vertices[0], 
							  startIdx*NUM_VERTICES_PER_PARTICLE,
							  startIdx*NUM_VERTICES_PER_PARTICLE,
		                      (endIdx-startIdx)*NUM_VERTICES_PER_PARTICLE);
}

int ParticleEmitter::destroyParticles(int startIdx, int endIdx)
{
	int idx	= startIdx * NUM_VERTICES_PER_PARTICLE;
	for(int i=startIdx; i<endIdx; i++)
	{
		if(vertices[idx].initialPositionCreateTime.W() + getDuration() >= currentTime)
		{
			return i;
		}

		idx += NUM_VERTICES_PER_PARTICLE;
	}

	return endIdx;
}

void ParticleEmitter::updateParticles(float dt)
{
	if(!getOwner().getActive())
		return ;

	float deltaTime			= dt;
	int maxNumParticles		= vertices.length() / NUM_VERTICES_PER_PARTICLE;
	float timePerParticle	= 1.0f / getEmissionRate();
	currentTime				+= deltaTime;

	///////////////////////////////////////////////////////
	// update
	int handle;
	handle = visualEffect.getUniformHandle("currentTime");
	visualEffect.setValue(handle, currentTime);

	if(getEmitting())
	{
		///////////////////////////////////////////////////////
		// Generate new Particles

		// generate particles
		newParticleAccum += deltaTime * getEmissionRate();
        if(newParticleAccum>maxNumParticles)
            newParticleAccum = maxNumParticles;
            
		int numNewParticles = Math::Floor(newParticleAccum);
		newParticleAccum -= numNewParticles;

		if(numNewParticles)
		{
			int nextQueueTail = queueTail + numNewParticles;
			if(nextQueueTail<maxNumParticles)
			{
				createParticles(queueTail, nextQueueTail, currentTime, timePerParticle);

				queueTail = nextQueueTail;
			}
			else
			{
				int numParticles1		= maxNumParticles - queueTail;
				createParticles(queueTail, maxNumParticles, currentTime, timePerParticle);			

				int numParticles2		= numNewParticles - numParticles1;
				if(numParticles2)
				{
					createParticles(0, numParticles2, currentTime+numParticles1*timePerParticle, timePerParticle);
				}

				queueTail = numParticles2;
			}
		}
	}

	if(queueTail-queueHead>=0)
	{
		int index;
		index = destroyParticles(queueHead, queueTail);

		//debug("1 %d %d %d", queueHead, queueTail, index);
		queueHead = index;
	}
	else
	{
		int index;
		index = destroyParticles(queueHead, maxNumParticles);
		if(index==maxNumParticles)
			index = destroyParticles(0, queueTail);
		
		//debug("2 %d %d %d", queueHead, queueTail, index);
		queueHead = index;
	}
}