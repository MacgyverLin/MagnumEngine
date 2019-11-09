///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _ParticleEmitter_h_
#define _ParticleEmitter_h_

#include "Stage.h"
#include "Graphics3Component.h"
#include "Vector2.h"
#include "Texture2DFile.h"
#include "VisualEffect.h"
#include "ResourcePath.h"
using namespace Magnum;

namespace Magnum
{

#define NUM_VERTICES_PER_PARTICLE (6)

/**
* ParticleEmitter
* @see Graphics3Component
*/
class ParticleEmitter : public Graphics3Component
{
friend class ParticleEmitterRenderer;
public:
	class Vertex
	{
	public:
		void set(unsigned int startFrameUV_, float currentTime_, 
				 const Vector3 &initialPosition_, const Vector3 &initialVelocity_, const Vector3 &acceleration_, 
				 unsigned int startColor_, unsigned int endColor_,
				 const Vector2 &startSize_, const Vector2 &endSize_)
		{
			startFrameUV  = startFrameUV_;

			initialPositionCreateTime.X() = initialPosition_.X();
			initialPositionCreateTime.Y() = initialPosition_.Y();
			initialPositionCreateTime.Z() = initialPosition_.Z();
			initialPositionCreateTime.W() = currentTime_;

			initialVelocity = initialVelocity_;
			acceleration    = acceleration_;

			startSizeEndSize.X() = startSize_.X();
			startSizeEndSize.Y() = startSize_.Y();
			startSizeEndSize.Z() = endSize_.X();
			startSizeEndSize.W() = endSize_.Y();

			startColor		= startColor_;
			endColor		= endColor_;
		}

		unsigned int startFrameUV;

		Vector4 initialPositionCreateTime;
		Vector3 initialVelocity;
		Vector3 acceleration;
		Vector4 startSizeEndSize;
		unsigned int startColor;
		unsigned int endColor;
	};

////////////////////////////////////////////////////////////////
	/**
	* ParticleEmitter Constructor.
	* To Construct the ParticleEmitter for the owner.
	* @param owner_, the Component::Owner which owns this component.
	*/
	ParticleEmitter(Component::Owner &owner);

	/**
	* ParticleEmitter Destructor.
	* To Destruct the ParticleEmitter for the owner.
	*/
	virtual ~ParticleEmitter();

	DECLARE_COMPONENT(ParticleEmitter, Graphics3Component, true)
////////////////////////////////////////////////////////////////

	/**
	* Set the Path of Shader of the ParticleEmitter.
	* @param value_, ResourcePath the Path of Shader of the ParticleEmitter.
	*/
	/**
	* Get the Path of Shader of the ParticleEmitter.
	* @return ResourcePath the Path of Shader of the ParticleEmitter.
	*/
	PROPERTY(ResourcePath	, ShaderPath);

	/**
	* Set the Path of Texture of the ParticleEmitter.
	* @param value_, ResourcePath the Path of Texture of the ParticleEmitter.
	*/
	/**
	* Get the Path of Texture of the ParticleEmitter.
	* @return ResourcePath the Path of Texture of the ParticleEmitter.
	*/
	PROPERTY(ResourcePath	, TexturePath);

	/**
	* Set the Initial Delta Velocity of the ParticleEmitter.
	* @param value_, Vector3 the Initial Delta Velocity of the ParticleEmitter.
	*/
	/**
	* Get the Initial Delta Velocity of the ParticleEmitter.
	* @return value_, Vector3 the Initial Delta Velocity of the ParticleEmitter.
	*/
	PROPERTY(Vector3		, InitialVelocityDelta);

	/**
	* Set the Initial Velocity of the ParticleEmitter.
	* @param value_, Vector3 the Initial Velocity of the ParticleEmitter.
	*/
	/**
	* Get the Initial Velocity of the ParticleEmitter.
	* @return value_, Vector3 the Initial Velocity of the ParticleEmitter.
	*/
	PROPERTY(Vector3		, InitialVelocity);

	/**
	* Set the Acceleration of the ParticleEmitter.
	* @param value_, Vector3 the Acceleration of the ParticleEmitter.
	*/
	/**
	* Get the Acceleration of the ParticleEmitter.
	* @return value_, Vector3 the Acceleration of the ParticleEmitter.
	*/
	PROPERTY(Vector3		, Acceleration);

	/**
	* Set the StartColor of the ParticleEmitter.
	* @param value_, ColorRGBA the StartColor of the ParticleEmitter.
	*/
	/**
	* Get the StartColor of the ParticleEmitter.
	* @return value_, ColorRGBA the StartColor of the ParticleEmitter.
	*/
	PROPERTY(ColorRGBA		, StartColor);

	/**
	* Set the EndColor of the ParticleEmitter.
	* @param value_, ColorRGBA the EndColor of the ParticleEmitter.
	*/
	/**
	* Get the EndColor of the ParticleEmitter.
	* @return value_, ColorRGBA the EndColor of the ParticleEmitter.
	*/
	PROPERTY(ColorRGBA		, EndColor);

	/**
	* Set the Number of Column of Texture of the ParticleEmitter.
	* @param value_, int the Number of Column of Texture of the ParticleEmitter.
	*/
	/**
	* Get the Number of Column of Texture of the ParticleEmitter.
	* @return value_, int the Number of Column of Texture of the ParticleEmitter.
	*/
	PROPERTY(int			, TextureColumn);

	/**
	* Set the Number of Row of Texture of the ParticleEmitter.
	* @param value_, int the Number of Row of Texture of the ParticleEmitter.
	*/
	/**
	* Get the Number of Row of Texture of the ParticleEmitter.
	* @return value_, int the Number of Row of Texture of the ParticleEmitter.
	*/
	PROPERTY(int			, TextureRow);

	/**
	* Set the Number of Frames Per Second of the ParticleEmitter.
	* @param value_, float the Number of Frames Per Second of the ParticleEmitter.
	*/
	/**
	* Get the Number of Frames Per Second of the ParticleEmitter.
	* @return value_, float the Number of Frames Per Second of the ParticleEmitter.
	*/
	PROPERTY(float			, FramesPerSecond);

	/**
	* Set the Duration of the ParticleEmitter.
	* @param value_, float the Duration of the ParticleEmitter.
	*/
	/**
	* Get the Duration of the ParticleEmitter.
	* @return value_, float the Duration of the ParticleEmitter.
	*/
	PROPERTY(float			, Duration);

	/**
	* Set the Emission Rate of the ParticleEmitter.
	* @param value_, float the Emission Rate of the ParticleEmitter.
	*/
	/**
	* Get the Emission Rate of the ParticleEmitter.
	* @return value_, float the Emission Rate of the ParticleEmitter.
	*/
	PROPERTY(float			, EmissionRate);

	/**
	* Set the Start Size of the ParticleEmitter.
	* @param value_, Vector2 the Start Size of the ParticleEmitter.
	*/
	/**
	* Get the Start Size of the ParticleEmitter.
	* @return value_, Vector2 the Start Size of the ParticleEmitter.
	*/
	PROPERTY(Vector2		, StartSize);

	/**
	* Set the End Size of the ParticleEmitter.
	* @param value_, Vector2 the End Size of the ParticleEmitter.
	*/
	/**
	* Get the End Size of the ParticleEmitter.
	* @return value_, Vector2 the End Size of the ParticleEmitter.
	*/
	PROPERTY(Vector2		, EndSize);

	/**
	* Set if the ParticleEmitter is Emitting
	* @param value_, true if the ParticleEmitter is Emitting else not Emitting
	*/
	/**
	* Get if the ParticleEmitter is Emitting
	* @return value_, true if the ParticleEmitter is Emitting else not Emitting
	*/
	PROPERTY(bool			, Emitting);
////////////////////////////////////////////////////////////////
public:
	/**
	* Handle Construct Event of the Component
	* @return true if construction is success, return false if fail
	*/
	virtual bool onConstruct();

	/**
	* Handle Start Event of the Component
	*/
	virtual void onStart();

	/**
	* Handle Update Event of the Component
	* @param delta elapse of the game cycle
	*/
	virtual void onUpdate(float dt);

	/**
	* Handle Pause Event of the Component
	*/
	virtual void onPause();

	/**
	* Handle Resume Event of the Component
	*/
	virtual void onResume();

	/**
	* Handle Stop Event of the Component
	*/
	virtual void onStop();

	/**
	* Handle Destruct Event of the Component
	*/
	virtual void onDestruct();

	/**
	* Handle Debuger Rendering Event of the Component
	*/
	virtual void onDebugRender(IComponentDebugRenderer &debugRenderer);
protected:
private:
	void updateParticles(float dt);
	void createParticles(int startIdx, int endIdx, float firstParticleTime, float deltaTimePerParticles);
	int destroyParticles(int startIdx, int endIdx);
public:
protected:
private:
	///////////////////////////////////////////////////////////////
	VisualEffect	visualEffect;
	Texture2DFile	texture;

	///////////////////////////////////////////////////////////////
	float			currentTime;
	int				queueHead;
	int				queueTail;
	float			newParticleAccum;

	Vector<Vertex>	vertices;
	GXVertexBuffer	*vertexBuffer;
};

};

#endif
