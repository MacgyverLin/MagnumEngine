///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Physics3.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"

using namespace Magnum;

namespace Magnum
{

#define CAST_BTVECTOR3(x)		( (btVector3		&)(x) )
#define CONST_CAST_BTVECTOR3(x)	( (const btVector3	&)(x) )

#define CAST_VECTOR3(x)			( (Vector3			&)(x) )
#define CONST_CAST_VECTOR3(x)	( (const Vector3	&)(x) )
#define CAST_COLORRGB(x)		( (ColorRGB			&)(x) )
#define CONST_CAST_COLORRGB(x)	( (const ColorRGB	&)(x) )

Physics3::Manager *Physics3::Manager::_instance = 0;

//////////////////////////////////////////////////////////////////
static bool customMaterialCombinerCallback(btManifoldPoint &cp,	
										   const btCollisionObjectWrapper *colObj0Wrap, int partId0, int index0,
										   const btCollisionObjectWrapper *colObj1Wrap, int partId1, int index1)
{
	void *ptr0 = colObj0Wrap->getCollisionObject()->getUserPointer();
	if(ptr0)
	{
		((void (*)())ptr0)();
	}

	void *ptr1 = colObj1Wrap->getCollisionObject()->getUserPointer();
	if(ptr1)
	{
		((void (*)())ptr1)();
	}

	return true;
}

class WorldDesc
{
public:
	WorldDesc(const Vector3 &worldMin, const Vector3 &worldMax)
	: collisionConfiguration(0)
	, dispatcher(0)	
	, overlappingPairCache(0)
	, constraintSolver(0)	
	, dynamicsWorld(0)		
	{
		gContactAddedCallback		= customMaterialCombinerCallback;
	
		collisionConfiguration		= new btDefaultCollisionConfiguration();
		dispatcher					= new btCollisionDispatcher(collisionConfiguration);
		overlappingPairCache		= new btAxisSweep3(CAST_BTVECTOR3(worldMin), CAST_BTVECTOR3(worldMax));
		constraintSolver			= new btSequentialImpulseConstraintSolver();
		dynamicsWorld				= new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, constraintSolver, collisionConfiguration);
	}

	~WorldDesc()
	{
		if(dynamicsWorld)
		{
			delete dynamicsWorld;		   
			dynamicsWorld				= 0;
		}
		if(dispatcher)
		{
			delete dispatcher;			   
			dispatcher					= 0;
		}
		if(overlappingPairCache)
		{
			delete overlappingPairCache;   
			overlappingPairCache		= 0;
		}
		if(constraintSolver)
		{
			delete constraintSolver;	   
			constraintSolver			= 0;
		}
		if(collisionConfiguration)
		{
			delete collisionConfiguration; 
			collisionConfiguration		= 0;
		}
	}

	btDefaultCollisionConfiguration				*collisionConfiguration;
	btCollisionDispatcher						*dispatcher;
	btAxisSweep3								*overlappingPairCache;
	btSequentialImpulseConstraintSolver			*constraintSolver;
	btDiscreteDynamicsWorld						*dynamicsWorld;
};

class RigidBodyDesc
{
public:
	RigidBodyDesc()
	: type(Physics3::RigidBody::DYNAMIC)
	, mass(0)
	, localInertia(Vector3::ZERO)
	, shape(0)
	, material()
	, collisionFilter()
	, body(0)
	, collisionCB(0)
	, destructionCB(0)
	, userData(0)
	{
	}

	~RigidBodyDesc()
	{
	}

	Physics3::RigidBody::Type				type;

	float									mass;
	Vector3									localInertia;
	const Shape3							*shape;
	Physics3::Material						material;
	Physics3::CollisionFilter				collisionFilter;

	btRigidBody								*body;
	
	Functor									*collisionCB;
	Functor									*destructionCB;
	void									*userData;
};

ATTRIBUTE_ALIGNED16(struct)	btMagnumMotionState : public btMotionState
{
	BT_DECLARE_ALIGNED_ALLOCATOR();
public:
	btMagnumMotionState(const btTransform &startTrans = btTransform::getIdentity())
	: m_graphicsWorldTrans(startTrans)
	, m_startWorldTrans(startTrans)
	{
	}

	///synchronizes world transform from user to physics
	virtual void getWorldTransform(btTransform& centerOfMassWorldTrans ) const 
	{
		// centerOfMassWorldTrans = m_centerOfMassOffset.inverse() * m_graphicsWorldTrans;
		centerOfMassWorldTrans = m_graphicsWorldTrans;
	}

	///synchronizes world transform from physics to user
	///Bullet only calls the update of worldtransform for active objects
	virtual void setWorldTransform(const btTransform& centerOfMassWorldTrans)
	{
		// m_graphicsWorldTrans = centerOfMassWorldTrans * m_centerOfMassOffset;
		m_graphicsWorldTrans = centerOfMassWorldTrans;
	}

	btTransform m_graphicsWorldTrans;
	btTransform m_startWorldTrans;
};

void fillBTTransform(const Matrix4 &transform, btTransform &btTransform)
{
	btMatrix3x3 &basis = btTransform.getBasis();
	btVector3 &origin  = btTransform.getOrigin();

	basis[0][0] = transform[0][0]; basis[0][1] = transform[0][1]; basis[0][2] = transform[0][2]; origin[0] = transform[0][3]; 
	basis[1][0] = transform[1][0]; basis[1][1] = transform[1][1]; basis[1][2] = transform[1][2]; origin[1] = transform[1][3];
	basis[2][0] = transform[2][0]; basis[2][1] = transform[2][1]; basis[2][2] = transform[2][2]; origin[2] = transform[2][3];
}

void fillMatrix4(const btTransform &btTransform, Matrix4 &transform)
{
	const btMatrix3x3 &basis = btTransform.getBasis();
	const btVector3 &origin  = btTransform.getOrigin();

	transform[0][0] = basis[0][0]; transform[0][1] = basis[0][1]; transform[0][2] = basis[0][2]; transform[0][3]   = origin[0];
	transform[1][0] = basis[1][0]; transform[1][1] = basis[1][1]; transform[1][2] = basis[1][2]; transform[1][3]   = origin[1];
	transform[2][0] = basis[2][0]; transform[2][1] = basis[2][1]; transform[2][2] = basis[2][2]; transform[2][3]   = origin[2];
	transform[3][0] =           0; transform[3][1] =           0; transform[3][2] =           0; transform[3][3]   =         1;
}

Physics3::RigidBody::RigidBody(Component::Owner &owner_)
: Component(owner_)
, handle(0)
{
}

Physics3::RigidBody::~RigidBody()
{
}

void Physics3::RigidBody::setTransform(const Matrix4 &transform_)
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);
	btMagnumMotionState *ms = (btMagnumMotionState *)rb->body->getMotionState();

	fillBTTransform(transform_, ms->m_graphicsWorldTrans);
}

void Physics3::RigidBody::getTransform(Matrix4 &transform_) const
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);
	btMagnumMotionState *ms = (btMagnumMotionState *)rb->body->getMotionState();

	fillMatrix4(ms->m_graphicsWorldTrans, transform_);
}

void Physics3::RigidBody::setPosition(const Vector3 &position_)
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);
	btMagnumMotionState *ms = (btMagnumMotionState *)rb->body->getMotionState();


	btTransform &tr = ms->m_graphicsWorldTrans;
	tr.setOrigin(btVector3(position_.X(), position_.Y(), position_.Z()));
}

const Vector3 &Physics3::RigidBody::getPosition() const
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);
	btMagnumMotionState *ms = (btMagnumMotionState *)rb->body->getMotionState();


	btTransform &tr = ms->m_graphicsWorldTrans;
	return CONST_CAST_VECTOR3(tr.getOrigin());
}

void Physics3::RigidBody::setAngularPosition(const Vector3 &axis_, float angle_)
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);
	btMagnumMotionState *ms = (btMagnumMotionState *)rb->body->getMotionState();


	btTransform &tr = ms->m_graphicsWorldTrans;
	tr.setRotation(btQuaternion(btVector3(axis_.X(), axis_.Y(), axis_.Z()), angle_));
}

void Physics3::RigidBody::setAngularPosition(const Quaternion &angularPosition_)
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);
	btMagnumMotionState *ms = (btMagnumMotionState *)rb->body->getMotionState();


	btTransform &tr = ms->m_graphicsWorldTrans;
	tr.setRotation(btQuaternion(angularPosition_.X(), angularPosition_.Y(), angularPosition_.Z(), angularPosition_.W()));
}

Quaternion Physics3::RigidBody::getAngularPosition() const
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);
	btMagnumMotionState *ms = (btMagnumMotionState *)rb->body->getMotionState();

	btQuaternion &q = ms->m_graphicsWorldTrans.getRotation();
	return Quaternion(q.w(), q.x(), q.y(), q.z());
}

void Physics3::RigidBody::setLinearVelocity(const Vector3 &velocity_)
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	rb->body->setLinearVelocity(CONST_CAST_BTVECTOR3(velocity_));
}

const Vector3 &Physics3::RigidBody::getLinearVelocity() const
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	return CONST_CAST_VECTOR3(rb->body->getLinearVelocity());
}

void Physics3::RigidBody::setAngularVelocity(const Vector3 &angularVel_)
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	rb->body->setAngularVelocity(CONST_CAST_BTVECTOR3(angularVel_));
}

const Vector3 &Physics3::RigidBody::getAngularVelocity() const
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	return CONST_CAST_VECTOR3(rb->body->getAngularVelocity());
}

void Physics3::RigidBody::setLinearFactor(const Vector3 &factor_)
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	rb->body->setLinearFactor(CONST_CAST_BTVECTOR3(factor_));
}

const Vector3 &Physics3::RigidBody::getLinearFactor() const
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	return CONST_CAST_VECTOR3(rb->body->getLinearFactor());
}

void Physics3::RigidBody::setAngularFactor(const Vector3 &factor_)
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	rb->body->setAngularFactor(CONST_CAST_BTVECTOR3(factor_));
}

const Vector3 &Physics3::RigidBody::getAngularFactor() const
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	return CONST_CAST_VECTOR3(rb->body->getAngularFactor());
}

void Physics3::RigidBody::applyForce(const Vector3 &force_, const Vector3 &relative_position_)
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	return rb->body->applyForce(CAST_BTVECTOR3(force_), CAST_BTVECTOR3(relative_position_));
}

void Physics3::RigidBody::applyForceToCenter(const Vector3 &force_)
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	return rb->body->applyCentralForce(CAST_BTVECTOR3(force_));
}

void Physics3::RigidBody::applyTorque(const Vector3 &torque_)
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	return rb->body->applyTorque(CAST_BTVECTOR3(torque_));
}

void Physics3::RigidBody::applyLinearImpulse(const Vector3 &impulse_, const Vector3 &relative_position_)
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	return rb->body->applyImpulse(CAST_BTVECTOR3(impulse_), CAST_BTVECTOR3(relative_position_));
}

void Physics3::RigidBody::applyLinearImpulseToCenter(const Vector3 &impulse_)
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	return rb->body->applyCentralImpulse(CAST_BTVECTOR3(impulse_));
}

void Physics3::RigidBody::applyAngularImpulse(const Vector3 &angularImpulse_)
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	return rb->body->applyTorqueImpulse(CAST_BTVECTOR3(angularImpulse_));
}

float Physics3::RigidBody::getMass() const
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	return rb->mass;
}

Vector3 Physics3::RigidBody::getInertia() const
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	return rb->localInertia;
}

Vector3 Physics3::RigidBody::getWorldPoint(const Vector3 &localPoint_) const
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	btVector3 localPoint = CAST_BTVECTOR3(localPoint_);
	btVector3 worldPoint = rb->body->getCenterOfMassTransform() * localPoint;

	return CAST_VECTOR3(worldPoint);
}

Vector3 Physics3::RigidBody::getWorldVector(const Vector3 &localVector_) const
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	btVector3 localVector = CAST_BTVECTOR3(localVector_);
	btVector3 worldVector = rb->body->getCenterOfMassTransform().getBasis() * localVector;

	return CAST_VECTOR3(worldVector);
}

Vector3 Physics3::RigidBody::getLocalPoint(const Vector3 &worldPoint_) const
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	btVector3 worldPoint = CAST_BTVECTOR3(worldPoint_);
	btVector3 localPoint = rb->body->getCenterOfMassTransform().inverse() * worldPoint;

	return CAST_VECTOR3(localPoint);
}

Vector3 Physics3::RigidBody::getLocalVector(const Vector3 &worldVector_) const
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	btVector3 worldVector = CAST_BTVECTOR3(worldVector_);
	btVector3 localVector = rb->body->getCenterOfMassTransform().getBasis().inverse() * worldVector;

	return CAST_VECTOR3(localVector);
}

Vector3 Physics3::RigidBody::getLinearVelocityFromWorldPoint(const Vector3 &worldPoint_) const
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	btVector3 worldPoint = CAST_BTVECTOR3(worldPoint_);
	btVector3 localPoint = rb->body->getCenterOfMassTransform().inverse() * worldPoint;

	btVector3 vel = rb->body->getLinearVelocity() + rb->body->getAngularVelocity().cross(localPoint);

	return CAST_VECTOR3(vel);
}

Vector3 Physics3::RigidBody::getLinearVelocityFromLocalPoint(const Vector3 &localPoint_) const
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	btVector3 localPoint = CAST_BTVECTOR3(localPoint_);
	btVector3 vel = rb->body->getLinearVelocity() + rb->body->getAngularVelocity().cross(localPoint);

	return CAST_VECTOR3(vel);
}

void Physics3::RigidBody::setLinearDamping(float linearDamping_)
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	rb->body->setDamping(linearDamping_, getAngularDamping());
}

float Physics3::RigidBody::getLinearDamping() const
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	return rb->body->getLinearDamping();
}

void Physics3::RigidBody::setAngularDamping(float angularDamping_)
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	rb->body->setDamping(getLinearDamping(), angularDamping_);
}

float Physics3::RigidBody::getAngularDamping() const
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	return rb->body->getAngularDamping();
}

void Physics3::RigidBody::setType(Physics3::RigidBody::Type type_)
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	rb->type		= type_;

	// set Mass
	// set Sensor
	updateMassProps();
	updateCollisionFlags();
	updateActivationState();
}

Physics3::RigidBody::Type Physics3::RigidBody::getType() const
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	return rb->type;
}

void Physics3::RigidBody::setMaterial(const Physics3::Material &material_)
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	rb->material			= material_;

	// friction
	// resititution
	rb->body->setFriction(rb->material.friction);
	rb->body->setRestitution(rb->material.restitution);

	// set Mass
	// set Sensor
	updateMassProps();
	updateCollisionFlags();
	updateActivationState();
}

Physics3::Material Physics3::RigidBody::getMaterial() const
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	return rb->material;
}

void Physics3::RigidBody::setCollisionFilter(const Physics3::CollisionFilter &collisionFilter_)
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	rb->collisionFilter		= collisionFilter_;

	rb->body->getBroadphaseProxy()->m_collisionFilterGroup	= rb->collisionFilter.groupBits;
	rb->body->getBroadphaseProxy()->m_collisionFilterMask	= rb->collisionFilter.maskBits;

	// set Mass
	// set Sensor
	updateMassProps();
	updateCollisionFlags();
	updateActivationState();
}

Physics3::CollisionFilter Physics3::RigidBody::getCollisionFilter() const
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	return rb->collisionFilter;
}

void Physics3::RigidBody::setBullet(bool flag)
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	assert(0);
}

bool Physics3::RigidBody::isBullet() const
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	assert(0);

	return false;
}

void Physics3::RigidBody::setSleepingAllowed(bool flag)
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	assert(0);
}

bool Physics3::RigidBody::isSleepingAllowed() const
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	assert(0);

	return false;
}

void Physics3::RigidBody::setAwake(bool flag)
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	assert(0);
}

bool Physics3::RigidBody::isAwake() const
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	assert(0);

	return false;
}

void Physics3::RigidBody::setActive(bool flag)
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	assert(0);
}

bool Physics3::RigidBody::isActive() const
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	assert(0);

	return false;
}

void Physics3::RigidBody::setCollisionCallBack(Functor *collisionCB_)
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	rb->collisionCB = collisionCB_;
}

Functor *Physics3::RigidBody::getCollisionCallBack() const
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	return rb->collisionCB;
}

void Physics3::RigidBody::setDestuctionCallBack(Functor *destructionCB_)
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	rb->destructionCB = destructionCB_;
}

Functor *Physics3::RigidBody::getDestuctionCallBack() const
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	return rb->destructionCB;
}

void Physics3::RigidBody::setUserData(void *userData_)
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	rb->userData = userData_;
}

void *Physics3::RigidBody::getUserData() const
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	return rb->userData;
}

bool Physics3::RigidBody::constructRigidBody(Physics3::RigidBody::Type type_,
											 const Shape3 *shape_, 
											 const Physics3::Material &material_, 
											 const Physics3::CollisionFilter &collisionFilter_)
{
	WorldDesc		  &wdDesc	= *((WorldDesc *)Physics3::Manager::instance().getWorld(0).handle);

	RigidBodyDesc *rb = new RigidBodyDesc();
	handle = (void *)rb;
	assert(handle);
	rb->shape					= shape_;
	rb->type					= type_;
	rb->material				= material_;
	rb->collisionFilter			= collisionFilter_;
	rb->collisionCB				= 0;
	rb->destructionCB			= 0;
	rb->userData				= 0;

	/*
	Vector3 velocity(0.0, 0.0, 0.0);
	if(rb->type==Physics3::RigidBody::STATIC)
	{
		velocity = Vector3(0.0, 10.0, 0.0);

		rb->type = Physics3::RigidBody::DYNAMIC;
	}
	*/


	
	calculateMass(rb->material.density, rb->mass, rb->localInertia);

	btTransform transform;
	transform.setIdentity();
	btMagnumMotionState *motionState = new btMagnumMotionState(transform);
	if(!motionState)
		return false;

	btCollisionShape *btshape		 = (btCollisionShape *)(rb->shape->getHandle());
	if(!btshape)
		return false;

	rb->body = new btRigidBody(rb->mass, motionState, btshape, CONST_CAST_BTVECTOR3(rb->localInertia) );
	if(!rb->body)
		return false;

	rb->body->setFriction(rb->material.friction);
	rb->body->setRestitution(rb->material.restitution);
	rb->body->setUserPointer(this);
	
	wdDesc.dynamicsWorld->addRigidBody(rb->body, rb->collisionFilter.groupBits, rb->collisionFilter.maskBits);

	updateCollisionFlags();
	updateActivationState();
	updateMassProps();

	// setLinearVelocity(velocity);

	return true;
}

void Physics3::RigidBody::updateRigidBody(float dt)
{
	Matrix4 transform;
	
	getTransform(transform);
	getOwner().setGlobalTransform(transform);
}

void Physics3::RigidBody::destructRigidBody()
{
	WorldDesc		  &wdDesc	= *((WorldDesc *)Physics3::Manager::instance().getWorld(0).handle);

	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);
	btRigidBody   *body	  = rb->body;

	if(rb)
	{
		if(body)
		{
			btMagnumMotionState *motionState = (btMagnumMotionState *)body->getMotionState();
			if(motionState)
			{
				delete motionState;
				motionState = 0;
			}

			wdDesc.dynamicsWorld->removeCollisionObject(body);
			delete body;
			body= 0;
		}

		delete rb;
		rb = 0;
		handle = 0;
	}
}

void Physics3::RigidBody::calculateMass(float density_, float &mass_, Vector3 &localInertia_) const
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	rb->shape->getMassProp(density_, mass_, localInertia_);
}

void Physics3::RigidBody::updateMassProps()
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	calculateMass(rb->material.density, rb->mass, rb->localInertia);
	
	if(rb->type==Physics3::RigidBody::STATIC)
	{
		rb->body->setMassProps(0			, CONST_CAST_BTVECTOR3(Vector3::ZERO) );
	}
	else if(rb->type==Physics3::RigidBody::KINEMATIC)
	{
		rb->body->setMassProps(0			, CONST_CAST_BTVECTOR3(Vector3::ZERO) );
	}
	else
	{
		rb->body->setMassProps(rb->mass		, CONST_CAST_BTVECTOR3(rb->localInertia)  );
	}
}

void Physics3::RigidBody::updateCollisionFlags()
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	int collisionFlags = 0;
	// int collisionFlags = CF_CUSTOM_MATERIAL_CALLBACK;
	switch(rb->type)
	{
		case Physics3::RigidBody::STATIC:
			collisionFlags	|= btCollisionObject::CF_STATIC_OBJECT;
			break;

		case Physics3::RigidBody::KINEMATIC:
			collisionFlags  |= btCollisionObject::CF_KINEMATIC_OBJECT;
			break;

		case Physics3::RigidBody::DYNAMIC:
			collisionFlags  |= 0;
			break;
	};
	
	if(rb->material.isSensor)
		collisionFlags |= btCollisionObject::CF_NO_CONTACT_RESPONSE;

	rb->body->setCollisionFlags(collisionFlags);
}

void Physics3::RigidBody::updateActivationState()
{
	RigidBodyDesc *rb = (RigidBodyDesc *)handle;
	assert(rb);

	if(rb->type==Physics3::RigidBody::STATIC)
	{
		rb->body->setActivationState(WANTS_DEACTIVATION);
	}
	else if(rb->type==Physics3::RigidBody::KINEMATIC)
	{
		rb->body->setActivationState(DISABLE_DEACTIVATION);
	}
	else
	{
		rb->body->setActivationState(ACTIVE_TAG);
	}
}

void *Physics3::RigidBody::getHandle()
{
	return handle;
}

/////////////////////////////////////////////////////////////
Physics3::World::World()
: handle(0)
{
}

Physics3::World::~World()
{
}

/// Register a destruction listener. The listener is owned by you and must
/// remain in scope.
// void Physics3::World::setDestructionListener(b2DestructionListener* listener);

/// Register a contact filter to provide specific control over collision.
/// Otherwise the default filter is used (b2_defaultFilter). The listener is
/// owned by you and must remain in scope. 
// void Physics3::World::setContactFilter(b2ContactFilter* filter);

/// Register a contact event listener. The listener is owned by you and must
/// remain in scope.
// void Physics3::World::setContactListener(b2ContactListener* listener);

/// Register a routine for debug drawing. The debug draw functions are called
/// inside with b2World2::DrawDebugData method. The debug draw object is owned
/// by you and must remain in scope.
// void Physics3::World::setDebugDrawer(Physics3::DebugDrawer *debugDrawer_);

/// Manually clear the force buffer on all bodies. By default, forces are cleared automatically
/// after each call to Step. The default behavior is modified by calling SetAutoClearForces.
/// The purpose of this function is to support sub-stepping. Sub-stepping is often used to maintain
/// a fixed sized time step under a variable frame-rate.
/// When you perform sub-stepping you will disable auto clearing of forces and instead call
/// ClearForces after all sub-steps are complete in one pass of your game loop.
/// @see SetAutoClearForces
void Physics3::World::clearForces()
{
	WorldDesc *wd = (WorldDesc *)handle;
	assert(wd);

	wd->dynamicsWorld->clearForces();
}


/// Call this to draw shapes and other debug draw data.
void Physics3::World::drawDebugData()
{
	WorldDesc *wd = (WorldDesc *)handle;
	assert(wd);

	wd->dynamicsWorld->debugDrawWorld();
}


/// Query the World2 for all fixtures that potentially overlap the
/// provided AABB.
/// @param callback a user implemented callback class.
/// @param aabb the query box.
void Physics3::World::testPoint(const Vector3 &p, 
							    unsigned short group, unsigned short mask, 
								Physics3::RayCastResult &result, bool closestOnly) const
{
	testRayCast(p, Vector3::ZERO, group, mask, result, closestOnly);
}

/// Ray-cast the World2 for all fixtures in the path of the ray. Your callback
/// controls whether you get the closest point, any point, or n-points.
/// The ray-cast ignores shapes that contain the starting point.
/// @param callback a user implemented callback class.
/// @param point1 the ray starting point
/// @param point2 the ray ending point
void Physics3::World::testRayCast(const Vector3 &p, const Vector3 &direction, 
								  unsigned short group, unsigned short mask, 
								  Physics3::RayCastResult &result, bool closestOnly) const
{
	WorldDesc *wd = (WorldDesc *)handle;
	assert(wd);

	if(closestOnly)
	{
		btVector3 from = CAST_BTVECTOR3(p);
		btVector3 to   = CAST_BTVECTOR3(p+direction);

		btCollisionWorld::ClosestRayResultCallback resultCallback(from, to);
		resultCallback.m_collisionFilterGroup = 1;
		resultCallback.m_collisionFilterMask  = 1;
		wd->dynamicsWorld->rayTest(from, to, resultCallback);

		result.hasHit						= resultCallback.hasHit();
		result.rayFromWorld					= CAST_VECTOR3(resultCallback.m_rayFromWorld);
		result.rayToWorld					= CAST_VECTOR3(resultCallback.m_rayToWorld);
		if(result.hasHit)
		{
			result.hitNormalWorlds.push()		= CAST_VECTOR3(resultCallback.m_hitNormalWorld);
			result.hitPointWorlds.push()		= CAST_VECTOR3(resultCallback.m_hitPointWorld);
			result.hitFractions.push()			= resultCallback.m_closestHitFraction;
			result.hitCollisionObjects.push()	= resultCallback.m_collisionObject->getUserPointer();
		}
	}
	else
	{
		btVector3 from = CAST_BTVECTOR3(p);
		btVector3 to   = CAST_BTVECTOR3(p+direction);

		btCollisionWorld::AllHitsRayResultCallback resultCallback(from, to);
		wd->dynamicsWorld->rayTest(from, to, resultCallback);

		result.hasHit						= resultCallback.hasHit();
		result.rayFromWorld					= CAST_VECTOR3(resultCallback.m_rayFromWorld);
		result.rayToWorld					= CAST_VECTOR3(resultCallback.m_rayToWorld);
		if(result.hasHit)
		{
			result.hitNormalWorlds.resize(resultCallback.m_collisionObjects.size());
			result.hitPointWorlds.resize(resultCallback.m_collisionObjects.size());
			result.hitFractions.resize(resultCallback.m_collisionObjects.size());
			result.hitCollisionObjects.resize(resultCallback.m_collisionObjects.size());
			for(int i=0; i<resultCallback.m_collisionObjects.size(); i++)
			{
				result.hitNormalWorlds[i]		= CAST_VECTOR3(resultCallback.m_hitNormalWorld[i]);
				result.hitPointWorlds[i]		= CAST_VECTOR3(resultCallback.m_hitPointWorld[i]);
				result.hitFractions[i]			= resultCallback.m_hitFractions[i];
				result.hitCollisionObjects[i]	= resultCallback.m_collisionObjects[i]->getUserPointer();
			}
		}
	}
}

/// Ray-cast the World2 for all fixtures in the path of the ray. Your callback
/// controls whether you get the closest point, any point, or n-points.
/// The ray-cast ignores shapes that contain the starting point.
/// @param callback a user implemented callback class.
/// @param point1 the ray starting point
/// @param point2 the ray ending point
void Physics3::World::testSphere(const Vector3 &p, 
							     float radius, 
								 unsigned short group, unsigned short mask, 
								 Physics3::ConvexCastResult &result, bool closestOnly) const
{
	testSphereCast(p, Vector3::ZERO, radius, group, mask, result, closestOnly);
}

/// Ray-cast the World2 for all fixtures in the path of the ray. Your callback
/// controls whether you get the closest point, any point, or n-points.
/// The ray-cast ignores shapes that contain the starting point.
/// @param callback a user implemented callback class.
/// @param point1 the ray starting point
/// @param point2 the ray ending point
void Physics3::World::testSphereCast(const Vector3 &p, const Vector3 &direction, 
								     float radius,
									 unsigned short group, unsigned short mask, 
									 Physics3::ConvexCastResult &result, bool closestOnly) const
{
	WorldDesc *wd = (WorldDesc *)handle;
	assert(wd);

	if(closestOnly)
	{
		btTransform from;
		from.setIdentity();
		from.setOrigin(CAST_BTVECTOR3(p));
		btTransform to;
		to.setIdentity();
		to.setOrigin(CAST_BTVECTOR3(p+direction));

		btCollisionWorld::ClosestConvexResultCallback resultCallback(from.getOrigin(), to.getOrigin());
		btSphereShape shape(radius);
		wd->dynamicsWorld->convexSweepTest(&shape, from, to, resultCallback);

		result.hasHit						= resultCallback.hasHit();
		result.convexFromWorld				= CAST_VECTOR3(resultCallback.m_convexFromWorld);
		result.convexToWorld				= CAST_VECTOR3(resultCallback.m_convexToWorld);
		if(result.hasHit)
		{
			result.hitNormalWorlds.push()		= CAST_VECTOR3(resultCallback.m_hitNormalWorld);
			result.hitPointWorlds.push()		= CAST_VECTOR3(resultCallback.m_hitPointWorld);
			result.hitFractions.push()			= resultCallback.m_closestHitFraction;
			result.hitCollisionObjects.push()	= resultCallback.m_hitCollisionObject->getUserPointer();
		}
	}
	else
	{
		btTransform from;
		from.setIdentity();
		from.setOrigin(CAST_BTVECTOR3(p));
		btTransform to;
		to.setIdentity();
		to.setOrigin(CAST_BTVECTOR3(p+direction));

		btCollisionWorld::ClosestConvexResultCallback resultCallback(from.getOrigin(), to.getOrigin());
		btSphereShape shape(radius);
		wd->dynamicsWorld->convexSweepTest(&shape, from, to, resultCallback);

		result.hasHit						= resultCallback.hasHit();
		result.convexFromWorld				= CAST_VECTOR3(resultCallback.m_convexFromWorld);
		result.convexToWorld				= CAST_VECTOR3(resultCallback.m_convexToWorld);
		if(result.hasHit)
		{
			result.hitNormalWorlds.push()		= CAST_VECTOR3(resultCallback.m_hitNormalWorld);
			result.hitPointWorlds.push()		= CAST_VECTOR3(resultCallback.m_hitPointWorld);
			result.hitFractions.push()			= resultCallback.m_closestHitFraction;
			result.hitCollisionObjects.push()	= resultCallback.m_hitCollisionObject->getUserPointer();
		}
	}
}

/// Get the World2 joint list. With the returned joint, use b2Joint::GetNext to get
/// the next joint in the World2 list. A NULL joint indicates the end of the list.
/// @return the head of the World2 joint list.
// const b2Joint *Physics3::World::getJointList() const;

/// Get the World2 contact list. With the returned contact, use b2Contact::GetNext to get
/// the next contact in the World2 list. A NULL contact indicates the end of the list.
/// @return the head of the World2 contact list.
/// @warning contacts are created and destroyed in the middle of a time step.
/// Use b2ContactListener to avoid missing contacts.
// const b2Contact *Physics3::World::getContactList() const;

/// Enable/disable sleep.
void Physics3::World::setAllowSleepingEnable(bool flag)
{
	WorldDesc *wd = (WorldDesc *)handle;
	assert(wd);

	assert(0);
}

bool Physics3::World::isAllowSleepingEnabled() const
{
	WorldDesc *wd = (WorldDesc *)handle;
	assert(wd);

	assert(0);

	return true;
}

/// Enable/disable warm starting. For testing.
void Physics3::World::setWarmStartingEnable(bool flag)
{
	WorldDesc *wd = (WorldDesc *)handle;
	assert(wd);

	assert(0);
}

bool Physics3::World::isWarmStartingEnabled() const
{
	WorldDesc *wd = (WorldDesc *)handle;
	assert(wd);

	assert(0);

	return true;
}

/// Enable/disable continuous physics. For testing.
void Physics3::World::setContinuousPhysicsEnable(bool flag)
{
	WorldDesc *wd = (WorldDesc *)handle;
	assert(wd);

	assert(0);
}

bool Physics3::World::isContinuousPhysicsEnabled() const
{
	WorldDesc *wd = (WorldDesc *)handle;
	assert(wd);

	assert(0);

	return true;
}

/// Set flag to control automatic clearing of forces after each time step.
void Physics3::World::setAutoClearForcesEnable(bool flag)
{
	WorldDesc *wd = (WorldDesc *)handle;
	assert(wd);

	assert(0);
}

bool Physics3::World::isAutoClearForcesEnabled() const
{
	WorldDesc *wd = (WorldDesc *)handle;
	assert(wd);

	assert(0);

	return true;
}

/// Enable/disable single stepped continuous physics. For testing.
void Physics3::World::setSubSteppingEnable(bool flag)
{
	WorldDesc *wd = (WorldDesc *)handle;
	assert(wd);

	assert(0);
}

bool Physics3::World::isSubSteppingEnabled() const
{
	WorldDesc *wd = (WorldDesc *)handle;
	assert(wd);

	assert(0);

	return true;
}

/// Get the number of broad-phase proxies.
int Physics3::World::getProxyCount() const
{
	WorldDesc *wd = (WorldDesc *)handle;
	assert(wd);

	assert(0);

	return 0;
}

/// Get the number of bodies.
int Physics3::World::getBodyCount() const
{
	WorldDesc *wd = (WorldDesc *)handle;
	assert(wd);

	return wd->dynamicsWorld->getNumCollisionObjects();
}

/// Get the number of joints.
int Physics3::World::getJointCount() const
{
	WorldDesc *wd = (WorldDesc *)handle;
	assert(wd);

	return wd->dynamicsWorld->getNumConstraints();
}

/// Get the number of contacts (each may have 0 or more contact points).
int Physics3::World::getContactCount() const
{
	WorldDesc *wd = (WorldDesc *)handle;
	assert(wd);

	assert(0);

	return 0;
}

/// Get the quality metric of the dynamic tree. The smaller the better.
/// The minimum is 1.
float Physics3::World::getOptimizationQuality() const
{
	WorldDesc *wd = (WorldDesc *)handle;
	assert(wd);

	assert(0);

	return 0;
}

/// Change the global gravity vector.
void Physics3::World::setGravity(const Vector3 &gravity)
{
	WorldDesc *wd = (WorldDesc *)handle;
	assert(wd);

	wd->dynamicsWorld->setGravity(CAST_BTVECTOR3(gravity));
}

/// Get the global gravity vector.
Vector3 Physics3::World::getGravity() const
{
	WorldDesc *wd = (WorldDesc *)handle;
	assert(wd);

	return CAST_VECTOR3(wd->dynamicsWorld->getGravity());
}

/// Is the World2 locked (in the middle of a time step).
//bool Physics3::World::isLocked() const;

/// Get the contact manager for testing.
//const b2ContactManager& Physics3::World::getContactManager() const;

/// Get the current profile.
//const b2Profile& Physics3::World::getProfile() const;

/// Dump the World2 into the log file.
/// @warning this should be called outside of a time step.
//void Physics3::World::dump();

void *Physics3::World::getHandle()
{
	return handle;
}

bool Physics3::World::initiate()
{
	assert(handle == 0);

	WorldDesc *wd = new WorldDesc(Vector3(-9999,-500,-9999), Vector3( 9999, 500, 9999));
	handle = (void *)wd;
	assert(handle);

	wd->dynamicsWorld->setGravity(btVector3(0, -9.8, 0));

	return handle!=0;
}

void Physics3::World::process(float dt)
{
	WorldDesc *wd = (WorldDesc *)handle;
	assert(wd);

	wd->dynamicsWorld->stepSimulation(dt);
}

void Physics3::World::pause()
{
	WorldDesc *wd = (WorldDesc *)handle;
	assert(wd);
}

void Physics3::World::resume()
{
	WorldDesc *wd = (WorldDesc *)handle;
	assert(wd);
}

void Physics3::World::terminate()
{
	WorldDesc *wd = (WorldDesc *)handle;
	assert(wd);

	delete wd;
	handle = 0;
}

void Physics3::World::clear()
{
	WorldDesc *wd = (WorldDesc *)handle;
	assert(wd);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Physics3::Manager::Manager()
{
	assert(_instance==0);

	_instance = this;
}

Physics3::Manager::~Manager()
{
	assert(_instance);

	_instance = 0;
}

Physics3::World &Physics3::Manager::getWorld(int i)
{
	return worlds[i];
}

const Physics3::World &Physics3::Manager::getWorld(int i) const
{
	return worlds[i];
}

int Physics3::Manager::getNumWorlds() const
{
	return worlds.length();
}

bool Physics3::Manager::initiate()
{
	worlds.resize(1);

	for(int i=0; i<worlds.length(); i++)
	{
		if(!worlds[i].initiate())
			return false;
	}
	
	return true;
}

void Physics3::Manager::process()
{
	float dt = ((float)Stage::elapsed()) / 1000.0f;

	for(int i=0; i<worlds.length(); i++)
	{
		worlds[i].process(dt);
	}
}

void Physics3::Manager::pause()
{
	for(int i=0; i<worlds.length(); i++)
	{
		worlds[i].pause();
	}
}

void Physics3::Manager::resume()
{
	for(int i=0; i<worlds.length(); i++)
	{
		worlds[i].resume();
	}
}

void Physics3::Manager::terminate()
{
	for(int i=0; i<worlds.length(); i++)
	{
		worlds[i].terminate();
	}
}

void Physics3::Manager::clear()
{
	for(int i=0; i<worlds.length(); i++)
	{
		worlds[i].clear();
	}
}

Physics3::Manager &Physics3::Manager::instance()
{
	return *_instance;
}

////////////////////////////////////////////////////////////////////////////////////
bool Physics3::Service::initiate()
{
	return Physics3::Manager::instance().initiate();
}

void Physics3::Service::process()
{
	Physics3::Manager::instance().process();
}

void Physics3::Service::pause()
{
	Physics3::Manager::instance().pause();
}

void Physics3::Service::resume()
{
	Physics3::Manager::instance().resume();
}

void Physics3::Service::terminate()
{
	Physics3::Manager::instance().terminate();
}

void Physics3::Service::clear()
{
	Physics3::Manager::instance().clear();
}

};