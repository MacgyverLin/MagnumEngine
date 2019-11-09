///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Collision_h_
#define _Collision_h_

#include "Array.h"
#include "Matrix4.h"
#include "Vector3.h"
#include "Delegate.h"
using namespace Magnum;

namespace Magnum
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

		bool collided;              ///< indicate this_obj and other_obj are collided.
		
		Collision *object0;			///< this_obj  is the (subject) in the Collision::Handler::onCollision
		Vector3 resolvePosition0;   ///< Contact Point of this_obj and other_obj in World Coordinate System
		
		Collision *object1;			///< other_obj is the (object ) in the Collision::Handler::onCollision
		Vector3 resolvePosition1;   ///< Contact Point of this_obj and other_obj in World Coordinate System

		Vector3 contactPoint;       ///< Contact Point of this_obj and other_obj in World Coordinate System
		Vector3 contactNormal;      ///< Contact Normal of this_obj and other_obj in World Coordinate System
		float penetrationDepth;     ///< How much this_obj and other_obj penetrate each other in World Coordinate System
	};

	template <typename U>
	class CallBack : public Delegate1<U, ContactInfo>
	{
	public:
		typedef void (U::*Proc)(const ContactInfo &);

		CallBack(U *who, Proc proc)
		: Delegate1<U, ContactInfo>(who, proc)
		{
		}
		virtual ~CallBack()
		{
		}
		bool operator==(const Proc proc_) const {return Delegate1<U, ContactInfo>::proc==proc_;} 
		Proc &operator=(const Proc proc_){return Delegate1<U, ContactInfo>::proc=proc_;} 
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
	void setCallBack(Functor1<ContactInfo> &cb_);
	void setAttribute(unsigned int attribute_);
	void setCategory(unsigned int category_);
	
	// getter
	Functor1<ContactInfo> &getCallBack();
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
	virtual bool test(float dt, Collision *other_, Collision::ContactInfo &info_){ return false; }; //= 0;
private: //wb made public for cw which has no friend???
	Type type;					///< type(shape) of collision
	unsigned int ID;			///< Collision ID
	unsigned int subID;			///< Collision subID, can be used when a class composed of more than 1 collision
	unsigned int attribute;		///< Now represents the catagory that this collision object can react to
	unsigned int category;		///< catagory of this collision object
	Matrix4 transform;			///< Position/Rotation of Collision Object
	Vector3 velocity;

	// Collision and Collision handler
	Functor1<ContactInfo> *cb;	///< optional collision handler, Collision::onCollision(const ContactInfo &info)
	bool enabled;

////////////////////////////////////////////////////////////////////////////////////
public:
	class Manager
	{
	friend class Collision;
	public:
		Manager();
		virtual ~Manager();
	protected:
	private:
		/**
		* Initiate the Services
		* @return true if success, false if failed
		*/
		bool initiate();

		/**
		* Update the Services
		*/
		void process();

		/**
		* Called when the application is pause(e.g system bring the app to background, let the service to release resources)
		*/
		void pause();

		/**
		* Called when the application is resume(e.g system bring back the app from background, let the service to reload resources)
		*/
		void resume();

		/**
		* Terminate the Services, called when the app is terminate.
		*/
		void terminate();

		/**
		* Call when the services needed to be clean up, e.g. during scene transition.
		*/
		void clear();
	public:
	private:
		Vector<Collision *>				collisions;
	public:
		static Manager					&instance();
	private:
		static Manager					*_instance;
	};
////////////////////////////////////////////////////////////////////////////////////
public:
	struct Service
	{
		/**
		* Initiate the Services
		* @return true if success, false if failed
		*/
		static bool initiate();

		/**
		* Update the Services
		*/
		static void process();

		/**
		* Called when the application is pause(e.g system bring the app to background, let the service to release resources)
		*/
		static void pause();

		/**
		* Called when the application is resume(e.g system bring back the app from background, let the service to reload resources)
		*/
		static void resume();

		/**
		* Terminate the Services, called when the app is terminate.
		*/
		static void terminate();

		/**
		* Call when the services needed to be clean up, e.g. during scene transition.
		*/
		static void clear();
	};
};

};

#endif