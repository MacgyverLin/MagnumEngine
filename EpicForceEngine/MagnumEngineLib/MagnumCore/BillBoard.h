///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _BillBoard_h_
#define _BillBoard_h_

#include "Stage.h"
#include "Graphics3Component.h"
#include "Vector2.h"
#include "Texture2DFile.h"
#include "VisualEffect.h"
#include "ResourcePath.h"
using namespace Magnum;

namespace Magnum
{

/**
* BillBoard
* @see Graphics3Component
*/
class BillBoard : public Graphics3Component
{
friend class BillBoardRenderer;
public:
	enum
	{
		NUM_TEXTURES = 2
	};

	enum Alignment
	{
		CAMERA_Z = 0,
		ROTATE_ABOUT_CAMERA,
		ROTATE_ABOUT_AXIS,
		ROTATE_ABOUT_PIVOT,
	};

	typedef struct
	{
		float x, y, z;
		float r, g, b, a;
		//unsigned char r, g, b, a;
		float u0, v0;
		float u1, v1;
	}Vertex;

////////////////////////////////////////////////////////////////
	/**
	* BillBoard Constructor.
	* To Construct the BillBoard for the owner.
	* @param owner_, the Component::Owner which owns this component.
	*/
	BillBoard(Component::Owner &owner_);

	/**
	* BillBoard Destructor.
	* To Destruct the BillBoard for the owner.
	*/
	virtual ~BillBoard();

	DECLARE_COMPONENT(BillBoard, Graphics3Component, false)
////////////////////////////////////////////////////////////////
	/**
	* Set the Path of Shader of the ParticleEmitter.
	* @param value_, ResourcePath, the Path of Shader of the ParticleEmitter.
	*/
	/**
	* Get the Path of Shader of the ParticleEmitter.
	* @return ResourcePath, the Path of Shader of the ParticleEmitter.
	*/
	PROPERTY(ResourcePath,	ShaderPath);

	/**
	* Set the Path of Texture0 of the ParticleEmitter.
	* @param value_, ResourcePath, the Path of Texture0 of the ParticleEmitter.
	*/
	/**
	* Get the Path of Texture0 of the ParticleEmitter.
	* @return ResourcePath, the Path of Texture0 of the ParticleEmitter.
	*/
	PROPERTY(ResourcePath,	Texture0Path);

	/**
	* Set the Path of Texture1 of the ParticleEmitter.
	* @param value_, ResourcePath, the Path of Texture1 of the ParticleEmitter.
	*/
	/**
	* Get the Path of Texture1 of the ParticleEmitter.
	* @return ResourcePath, the Path of Texture1 of the ParticleEmitter.
	*/
	PROPERTY(ResourcePath,	Texture1Path);

	/**
	* Set the Size of the Particle of the ParticleEmitter.
	* @param value_, Vector2, the Size of the Particle of Texture of the ParticleEmitter.
	*/
	/**
	* Get the Size of the Particle of Texture of the ParticleEmitter.
	* @return Vector2, the Size of the Particle of Texture of the ParticleEmitter.
	*/
	PROPERTY(Vector2     ,	Size);
////////////////////////////////////////////////////////////////
public:
	/**
	* Set the Alignment Mode of the Particle of the ParticleEmitter.
	* @param value_, ParticleEmitter::Alignment, the Alignment Mode of the Particle of the ParticleEmitter.
	* @see ParticleEmitter::Alignment
	*/
	/**
	* Get the Alignment Mode of the Particle of the ParticleEmitter.
	* @return , ParticleEmitter::Alignment, the Alignment Mode of the Particle of the ParticleEmitter.
	* @see ParticleEmitter::Alignment
	*/
	void setAlignmentMode(const Alignment &mode);
	const Alignment &getAlignmentMode() const;

	/**
	* Set the Alignment Axis of the Particle of the ParticleEmitter.
	* @param value_, Vector3, the Alignment Axis of the Particle of the ParticleEmitter.
	* @see Vector3
	*/
	/**
	* Get the Alignment Axis of the Particle of the ParticleEmitter.
	* @return , Vector3, the Alignment Axis of the Particle of the ParticleEmitter.
	* @see Vector3
	*/
	void setAlignmentAxis(const Vector3 &axis);
	const Vector3 &getAlignmentAxis() const;

	/**
	* Set the Rotation Pivot of the Particle of the ParticleEmitter.
	* @param value_, Vector3, the Rotation Pivot of the Particle of the ParticleEmitter.
	* @see Vector3
	*/
	/**
	* Get the Rotation Pivot of the Particle of the ParticleEmitter.
	* @return , Vector3, the Rotation Pivot of the Particle of the ParticleEmitter.
	* @see Vector3
	*/
	void setRotationPivot(const Vector3 &pivot);
	const Vector3 &getRotationPivot() const;
protected:
private:
	void getBillBoardMatrix(Matrix4 &matrix, 
						    const Matrix4 &globalTransform, const Vector3 &globalPosition);

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
public:
protected:
private:
	Alignment mode;
	Vector3 axis;
	Vector3 pivot;

	VisualEffect	visualEffect;
	Texture2DFile	texture0;
	Texture2DFile	texture1;

	GXVertexBuffer	*vertexBuffer;
	GXIndexBuffer	*indexBuffer;
};

};

#endif
