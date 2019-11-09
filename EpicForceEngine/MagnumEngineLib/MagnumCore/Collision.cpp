///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Collision.h"
using namespace Magnum;

///////////////////////////////////////////////
/**
* @brief The constructor
*/ 
Collision::ContactInfo::ContactInfo()
: collided(false)

, object0(0)
, resolvePosition0(Vector3::ZERO)

, object1(0)
, resolvePosition1(Vector3::ZERO)

, contactPoint(Vector3::ZERO)
, contactNormal(Vector3::ZERO)
, penetrationDepth(0)
{
}

/**
* @brief Reverse the information contained in ContactInfo. 
*
* After reverse, the data of Collision event is described
* from the point of view of other_obj.
*/ 
void Collision::ContactInfo::reverse()
{
	Collision	*tempObject;
	Vector3		tempPosition;
	
	tempObject			= object1;
	object1				= object0;
	object0				= tempObject;
	
	tempPosition		= resolvePosition1;
	resolvePosition1	= resolvePosition0;
	resolvePosition0	= tempPosition;

	contactNormal		*= -1;
}

///////////////////////////////////////////////
/**
* @brief The constructor
*
* @param type_ The Type(Shape) of Collision
*/ 
Collision::Collision(Type type_) 
: type(type_)
, ID(0)
, subID(0)
, attribute(0xffffffff)
, category(0xffffffff)
, transform(Matrix4::IDENTITY)
, velocity(Vector3::ZERO)
, cb(0)
, enabled(true)
{
	Collision::Manager::instance().collisions.push() = this;
}

Collision::~Collision()
{
	int idx = Collision::Manager::instance().collisions.search(this);
	if(idx>=0)
	{
		Collision::Manager::instance().collisions.remove(idx);
	}
}

///////////////////////////////////////////////////
// basic interface
// setter
/**
* @brief set the ID of this Instance of Collision.
*
* @param ID_ ID of this Instance of Collision.
*/ 
void Collision::setID(unsigned int ID_)
{
	ID = ID_;
}

/**
* @brief set the subID of this Instance of Collision.
*
* @param subID_ subID of this Instance of Collision.
*/ 
void Collision::setSubID(unsigned int subID_)
{
	subID = subID_;
}

/**
* @brief set the Position of this Instance of Collision.
*
* If setPhysicsBody(Physics::Body *physicsbody_) is called once with a non-zero physicsbody_,
* The Position of physicsbody_ will be set equal to position_.
*
* @param position_ the Position of this Instance of Collision.
*/
void Collision::setPosition(const Vector3 &position_)
{
	transform[0][3] = position_[0];
	transform[1][3] = position_[1];
	transform[2][3] = position_[2];
}

/**
* @brief set the Position/Rotation of this Instance of Collision.
*
* If setPhysicsBody(Physics::Body *physicsbody_) is called once with a non-zero physicsbody_,
* The Transform of physicsbody_ will be set equal to transform_.
*
* @param transform_ the Position/Rotation of this Instance of Collision.
*/
void Collision::setTransform(const Matrix4 &transform_)
{
	transform = transform_;
}

/**
* @brief set the Velocity of this Instance of Collision.
*
* If setPhysicsBody(Physics::Body *physicsbody_) is called once with a non-zero physicsbody_,
* The Velocity of physicsbody_ will be set equal to velocity_.
*
* @param velocity_ the Velocity of this Instance of Collision.
*/
void Collision::setVelocity(const Vector3 &velocity_)
{
	velocity = velocity_;
}

// getter
/**
* @brief get the ID of this Instance of Collision.
*
* @return unsigned int ID of this Instance of Collision.
*/ 
unsigned int Collision::getID() const
{
	return ID;
}

/**
* @brief get the subID of this Instance of Collision.
*
* @return unsigned int subID of this Instance of Collision.
*/ 
unsigned int Collision::getSubID() const
{
	return subID;
}

/**
* @brief get the Position of this Instance of Collision.
*
* If setPhysicsBody(Physics::Body *physicsbody_) is called once with a non-zero physicsbody_,
* The returned position is the Position of physicsbody_.
*
* @return Vector3 the Position of this Instance of Collision.
*/
Vector3 Collision::getPosition() const
{
	return Vector3(transform[0][3], transform[1][3], transform[2][3]);
}


/**
* @brief get the Position/Rotation of this Instance of Collision.
*
* If setPhysicsBody(Physics::Body *physicsbody_) is called once with a non-zero physicsbody_,
* The returned transform is the Transform of physicsbody_.
*
*  @return Matrix4 the Position/Rotation of this Instance of Collision.
*/
const Matrix4 &Collision::getTransform() const
{
	return transform;
}

/**
* @brief get the Velocity of this Instance of Collision.
*
* If setPhysicsBody(Physics::Body *physicsbody_) is called once with a non-zero physicsbody_,
* The returned velocity is the Velocity of physicsbody_.
*
* @return Vector3 the Velocity of this Instance of Collision.
*/
const Vector3 &Collision::getVelocity() const
{
	return velocity;
}


///////////////////////////////////////////////////////////
// setter
/**
* @brief set the Collision Event Handler
*
* This function is to set the Collision::Handler for handling the collision event
*
* @param handler_ the Collision::Handler
*/
void Collision::setCallBack(Functor1<Collision::ContactInfo> &cb_)
{
	cb = &cb_;
}

/**
* @brief set the Attribute of this Collision Instance
*
* This function is to set the 32-bit Attribute of this Collision Instance.
* Collision Detecion only performs on a pair of Collision Instance if they have at least 1 common bit
* set in their attri_bit. The default value of attri_bit is 0xffffffff 
*
* @param attri_bit_ the Attribute of this Collision
*/
void Collision::setAttribute(unsigned int attribute_)
{
	attribute = attribute_;
}

void Collision::setCategory(unsigned int category_)
{
	category = category_;
}

// getter
/**
* @brief get the Type of this Instance of Collision.
*
* @return Collision::Type the enumerated Type of this Instance of Collision
*/
Collision::Type Collision::getType() const
{
	return type;
}

/**
* @brief get the Collision Event Handler
*
* This function is to get the Collision::Handler for handling the collision event
*
* @return Collision::Handler the Collision handler
*/
Functor1<Collision::ContactInfo> &Collision::getCallBack()
{
	return *cb;
}

/**
* @brief get the Attribute of this Collision Instance
*
* @return unsigned int the Attribute of this Collision Instance
*/
unsigned int Collision::getAttribute() const
{
	return attribute;
}

unsigned int Collision::getCategory() const
{
	return category;
}

bool Collision::getEnabled() const
{
	return enabled;
}

void Collision::setEnabled(bool enabled_)
{
	enabled = enabled_;
}

/**
* @brief preform default Response when this Instance collide with other
*
* When this function is called, the Position of this instance will be changed.
* It will displaced by info.contactNormal * info.penetrationDepth / 2
* This function is supposed to be called during Collision::Handler::onCollision();
* If both the handler of info.this_obj and info.other_obj have called this function, 
* Both info.this_obj and info.other_obj will not intersected
*
* If setPhysicsBody(Physics::Body *physicsbody_) is called once with a non-zero physicsbody_,
* The Physics::Body::defaultImpulseResponse of physicsbody_ will be called as well. 
* physicsbody_ will sync the Position/Rotation, and bounce back, afterward
*
* @param Collision::ContactInfo The information about the collision
*/
void Collision::defaultCollisionResponse(const Collision::ContactInfo &info)
{
	info.object0->setPosition(info.resolvePosition0);
}

///////////////////////////////////////////////////////////
Collision::Manager	*Collision::Manager::_instance = 0;

Collision::Manager::Manager()
{
	assert(_instance==0);

	_instance = this;
}

Collision::Manager::~Manager()
{
	assert(_instance!=0);

	_instance = 0;
}

bool Collision::Manager::initiate()
{
	return true;
}

void Collision::Manager::process()
{
	float dt = (((float)Stage::elapsed())/1000.0f);

	for(int i=0; i<collisions.length(); i++)
	{
		Collision &body0 = *collisions[i];
		if(!body0.getEnabled())
			continue;

		Collision::ContactInfo info;

		for(int j=i+1; j<collisions.length(); j++)
		{
			Collision &body1 = *collisions[j];
			if(!body1.getEnabled())
				continue;

			// only check collision if they shared the same attribte bit.
			if( (body0.getAttribute() & body1.getCategory()) || (body0.getCategory() & body1.getAttribute()) )
			{
				if( body0.test(dt, &body1, info) ) // have method for collision
				{
					//debug("if   info.collided  --- begin ");
					if(info.collided)
					{
						info.object0	= &body0;
						info.object1	= &body1;
						
						// collision handler 0
						if( (body0.getAttribute() & body1.getCategory()) && body0.cb )
							body0.cb->invoke(info);
						
						info.reverse();

						// collision handler 1
						if( (body1.getAttribute() & body0.getCategory()) && body1.cb )
							body1.cb->invoke(info);
					}
				}
				else if( body1.test(dt, &body0, info) ) // have method for collision
				{
					if(info.collided)
					{
						info.object1	= &body1;
						info.object0	= &body0;
						
						// collision handler 1
						if( (body1.getAttribute() & body0.getCategory()) && body1.cb )
							body1.cb->invoke(info);
						
						info.reverse();

						// collision handler 0
						if( (body0.getAttribute() & body1.getCategory()) && body0.cb )
							body0.cb->invoke(info);
					}
				}
			}
		}
	}
}

void Collision::Manager::pause()
{
}

void Collision::Manager::resume()
{
}

void Collision::Manager::terminate()
{
}

void Collision::Manager::clear()
{
	collisions.destroy();
}

Collision::Manager &Collision::Manager::instance()
{
	assert(_instance);

	return *_instance;
}

///////////////////////////////////////////////////////////////////////////////////
bool Collision::Service::initiate()
{
	return Collision::Manager::instance().initiate();
}

void Collision::Service::process()
{
	Collision::Manager::instance().process();
}

void Collision::Service::pause()
{
	Collision::Manager::instance().pause();
}

void Collision::Service::resume()
{
	Collision::Manager::instance().resume();
}

void Collision::Service::terminate()
{
	Collision::Manager::instance().terminate();
}

void Collision::Service::clear()
{
	Collision::Manager::instance().clear();
}