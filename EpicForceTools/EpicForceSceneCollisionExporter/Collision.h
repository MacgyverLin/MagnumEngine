///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited			 //
//																 //
// Author : Mac Lin									             //
// Module : EpicForceEngine										 //
// Date   : 19/Aug/2011											 //
//																 //
///////////////////////////////////////////////////////////////////
#ifndef _Collision_h_
#define _Collision_h_

#include "Array.h"
#include "Matrix4.h"
#include "Vector3.h"
using namespace EpicForce;

namespace EpicForce
{

/**
* @brief Base class For all type of Collision Object
*
* This is the base class for all type of Collision Object. The collision
* type can be extended by inheritance. If setPhysicsBody(Physics::Body *physicsbody) is called with a   
* valid physicsbody pointer, the Transform of the Collision is controlled by that of physicsbody.
* Otherwise, its Transform is controlled by Collision::setTransform(const Matrix4 &transform_);
*/
class Collision
{
public:

	/**
	* @brief Contains information about the collision. 
	* This information is to be passed to Collsion::Handler
	*/
	class ContactInfo
	{
	public:
		ContactInfo();
		
		void reverse();

		Vector3 inputPosition;
		Vector3 inputVelocity;
		float inputRadius;

		Vector3 outputPosition;
		Vector3 *outputNormal;
		Vector3 outputVelocity;
		bool outputStartOut;
		bool outputAllSolid;
		float outputFraction;
		int outputID;
		
		bool collided;              ///< indicate this_obj and other_obj are collided.
		Collision *thisObj;			///< this_obj  is the (subject) in the Collision::Handler::onCollision
		const Collision *otherObj;	///< other_obj is the (object ) in the Collision::Handler::onCollision
		Vector3 contactPoint;       ///< Contact Point of this_obj and other_obj in World Coordinate System
		Vector3 contactNormal;      ///< Contact Normal of this_obj and other_obj in World Coordinate System
		float penetrationDepth;       ///< How much this_obj and other_obj penetrate each other in World Coordinate System
	};

	/**
	* @brief This is the Collision Handler to report the event of Collision.
	*/
	class Handler
	{
	friend class Collision;
	public:
		Handler();
		virtual ~Handler();
	//protected: //wb made public for cw which has no friend???
		/**
		* @brief This is a pure virtual function. The function is a Collision Event Call Back to be implemented by its sub class.
		*
		* @param info The Information about the collision event, detail see Collision::ContactInfo
		*/ 
		virtual void onCollision(const ContactInfo &info) {} //= 0;
	};

	/**
	* @brief enum supported Collision Shape(Type)
	*
	* enum supported Collision Shape(Type)
	*/
	enum Type
	{
		CT_SPHERE3 = 0,
		CT_SCENE,
		CT_NUM_COLLISION
	};

	Collision(Type type_);
	virtual ~Collision();

	///////////////////////////////////////////////////
	// basic interface
	// setter
	void setID(unsigned int ID_);
	void setSubID(unsigned int SubID_);
	void setPosition(const Vector3 &position_);
	void setTransform(const Matrix4 &transform_);
	void setVelocity(const Vector3 &velocity_);

	// getter	
	unsigned int getID() const;
	unsigned int getSubID() const;
	Vector3 getPosition() const;
	const Matrix4 &getTransform() const;
	const Vector3 &getVelocity() const;
	///////////////////////////////////////////////////

	///////////////////////////////////////////////////
	// Collision Specific
	// setter
	Type getType() const;
	void setHandler(Handler *handler_);
	void setAttribute(unsigned int attribute_);
	void setCategory(unsigned int category_);
	
	// getter	
	Handler *getHandler() const;
	unsigned int getAttribute() const;
	unsigned int getCategory() const;
	bool		 getEnabled() const;
	void		 setEnabled(bool enabled_);

	/**
	* @brief This is a pure virtual function. The function checks if a point, defined in world space, is inside the collision shape
	*
	* @param world_point the coordinates, defined in world space, to be checked against the collider
	*
	* @return true  if world_point is inside collision
	*         false if world_point is not inside collision
	*/ 
	virtual bool isInside(const Vector3 &world_point) {return false;} //= 0;

	void defaultCollisionResponse(const ContactInfo &info);
	///////////////////////////////////////////////////
//protected: //wb made public for cw which has no friend???
	/**
	* @brief This is a pure virtual function. The function is a core function for calculate collision
	*
	* This function should be implemented by sub class of Collision. It should get the type of
	* other_ in the parameter and perform collision calculation with all possible type of other_
	* enummerated by Collision::Type
	*
	* @param other the other collision instance to be checked with
	* @param collided_ set by this function, true if collision occurs, false other wise
	* @param contactPoint_ set by this function, the calculated Contact Point of the Collided surface 
	* @param contactNormal_ set by this function, the calculated Contact Normal of the Collided surface 
	* @param penetrationDepth_ set by this function, the depth in which this instance penetrate with the other.
	*
	* @return true  if collision detection is calculated
	*         false if collision detection is not calculated, i.e. no implemnetation
	*/
	virtual bool test(Collision *other_, Collision::ContactInfo &info_){ return false; }; //= 0;
private: //wb made public for cw which has no friend???
	Type type;                ///< type(shape) of collision
	unsigned int ID;          ///< Collision ID
	unsigned int subID;       ///< Collision subID, can be used when a class composed of more than 1 collision
	unsigned int attribute;   ///< Now represents the catagory that this collision object can react to
	unsigned int category;	  ///< catagory of this collision object
	Matrix4 transform;        ///< Position/Rotation of Collision Object
	Vector3 velocity;

	// Collision and Collision handler
	Handler		   *handler;             ///< optional collision handler, Collision::onCollision(const ContactInfo &info)
	bool			enabled;

////////////////////////////////////////////////////////////////////
public:
	class Manager
	{
	friend class Collision;
	public:
		Manager();
		virtual ~Manager();
	protected:
	private:
		bool initiate();
		void process();
		void pause();
		void resume();
		void terminate();
		void clear();
	public:
	private:
		Vector<Collision *>				collisions;
	public:
		static Manager					&instance();
	private:
		static Manager					*_instance;
	};
////////////////////////////////////////////////////////////////////
public:
	struct Service
	{
		static bool initiate();
		static void process();
		static void pause();
		static void resume();
		static void terminate();
		static void clear();
	};
};

};

#endif