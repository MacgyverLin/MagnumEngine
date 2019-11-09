///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Physics3_h_
#define _Physics3_h_

#include "Stage.h"
#include "List.h"
#include "EString.h"
#include "Array.h"
#include "Matrix4.h"
#include "AABB3.h"
#include "ColorRGBA.h"
#include "ColorRGB.h"
#include "Component.h"
#include "Quaternion.h"
#include "Shape3.h"
using namespace Magnum;

namespace Magnum
{

#define CAST_BTVECTOR3(x)		( (btVector3		&)(x) )
#define CONST_CAST_BTVECTOR3(x)	( (const btVector3	&)(x) )

#define CAST_VECTOR3(x)			( (Vector3			&)(x) )
#define CONST_CAST_VECTOR3(x)	( (const Vector3	&)(x) )
#define CAST_COLORRGB(x)		( (ColorRGB			&)(x) )
#define CONST_CAST_COLORRGB(x)	( (const ColorRGB	&)(x) )

/**
* Physics3 Services.
*/
class Physics3
{
public:
	class RigidBody;
	class World;
	class Manager;
	
	/**
	* CollisionFilter.
	* CollisionFilter defines the group the rigidbody belongs to filter out the collision by ising maskBits
	*/
	class CollisionFilter
	{
	public:
		/**
		* CollisionFilter Constructor.
		* To Construct the CollisionFilter
		*/
		CollisionFilter()
		{
			groupBits		= 0x0001;
			maskBits		= 0xffff;
		}

		unsigned short groupBits;				/**< group Bits */ 
		unsigned short maskBits;				/**< mask Bits to selected which group to collide with. */
	};


	/**
	* Material.
	* Material describe the friction, restitution, density, isSensor properties of the Rigidbody.
	* Physics simulation use these to properties to define the collision response
	*/
	class Material
	{
	public:
		/**
		* Material Constructor.
		* To Construct the Material
		*/
		Material()
		{
			friction	= 0.9f;		
			restitution = 0.0f;		
			density		= 1.0f;		
			isSensor	= false;	
		}

		float					friction;		/**< friction parameter */ 
		float					restitution;	/**< resititution rebounce parameter. */ 
		float					density;		/**< density parameter*/ 
		bool					isSensor;		/**< collision response */
	};
	

	/**
	* RigidBody Component.
	* RigidBody Component is a base component for handling Physics simulation.
	* Developer can specified Mass, Shape, Position, Velocity, Force, AngularPosition, AngularVelocity, Torque for Rigidbody
	* Static, Kinematic, Dynamic Rigidbody is supported.
	*/
	class RigidBody : public Component
	{
	friend class World;
	friend class Manager;
	public:
		enum Type
		{
			STATIC		=  0,	/**< Static RigidBody.		*/ 
			KINEMATIC		,	/**< Kinematic RigidBody.	*/ 
			DYNAMIC			,	/**< Dynamic RigidBody.		*/ 
		};
	////////////////////////////////////////////////////////////////
	public:
		/**
		* RigidBody Constructor.
		* To Construct the Rigidbody for the owner.
		*/
		RigidBody(Component::Owner &owner_);

		/**
		* RigidBody Destructor.
		* To Destruct RigidBody and remove from its owner.
		*/
		~RigidBody();

		DECLARE_COMPONENT(RigidBody, Component, false)
	////////////////////////////////////////////////////////////////
	public:
		/**
		* Set the Transform of the RigidBody.
		* @param transform_, Matrix4 which specify the position, rotation, scale of rigidbody.
		*/
		void setTransform(const Matrix4 &transform_);

		/**
		* Get the Transform of the RigidBody.
		* @param transform_, Matrix4 which receive the position, rotation, scale of rigidbody.
		*/
		void getTransform(Matrix4 &transform_) const;

		/**
		* Set the Position of the RigidBody.
		* @param position_, Vector3 which specify the position of rigidbody.
		*/
		void setPosition(const Vector3 &position_);

		/**
		* Get the Position of the RigidBody.
		* @return Vector3, the position of rigidbody.
		*/
		const Vector3 &getPosition() const;

		/**
		* Set the Angular Position of the RigidBody.
		* @param axis_, Vector3 which specify the axis of angular position.
		* @param angle_, float which specify the degree (in radian) rotate around the axis.
		*/
		void setAngularPosition(const Vector3 &axis_, float angle_);

		/**
		* Set the Angular Position of the RigidBody.
		* @param angularPosition_, Quaternion which specify the rotation and axis of rotation.
		*/
		void setAngularPosition(const Quaternion &angularPosition_);

		/**
		* Get the Angular Position of the RigidBody.
		* @return Quaternion, the angular position of rigidbody.
		*/
		Quaternion getAngularPosition() const;

		/**
		* Set the Velocity of the RigidBody.
		* @param velocity_, Vector3 which specify the velocity of rigidbody.
		*/
		void setLinearVelocity(const Vector3 &velocity_);

		/**
		* Get the Velocity of the RigidBody.
		* @return Vector3, the velocity of rigidbody.
		*/
		const Vector3 &getLinearVelocity() const;

		/**
		* Set the Angular Velocity of the RigidBody.
		* @param angularVel_, Vector3 which specify the axis of rotation with its length represent the angle (in radian).
		*/
		void setAngularVelocity(const Vector3 &angularVel_);

		/**
		* Get the Angular Velocity of the RigidBody.
		* @return Vector3, the angular velocity of rigidbody. which represent axis of rotation and
		* its length represent the angle of rotation (in radian).
		*/
		const Vector3 &getAngularVelocity() const;

		/**
		* Set the Linear Factor of the RigidBody.
		* @param factor_, Vector3 which specify the linear factor of rigidbody. Linear Factor scales the amount of linear 
		* motion along each axis.
		*/
		void setLinearFactor(const Vector3 &factor_);

		/**
		* Get the Linear Factor of the RigidBody.
		* @return Vector3, the linear factor of rigidbody. 
		* @see setLinearFactor()
		*/
		const Vector3 &getLinearFactor() const;

		/**
		* Set the Angular Factor of the RigidBody.
		* @param factor_, Vector3 which specify the angular factor of rigidbody. 
		* Angular Factor scales the amount of rotation motion along each axis.
		*/
		void setAngularFactor(const Vector3 &factor_);

		/**
		* Get the Angular Factor of the RigidBody.
		* @return Vector3, the angular factor of rigidbody. 
		* @see setAngularFactor()
		*/
		const Vector3 &getAngularFactor() const;

		/**
		* Apply a Force of the RigidBody at specific point around its center of mass.
		* @param force_, Vector3 which specify the force direction and magnitude.
		* @param point_, Vector3 which specify the point the force act on the Rigidbody. 
		*/
		void applyForce(const Vector3 &force_, const Vector3 &point_);

		/**
		* Apply a Force of the RigidBody at center of its center of mass.
		* @param force_, Vector3 which specify the force direction and magnitude.
		*/
		void applyForceToCenter(const Vector3 &force_);

		/**
		* Apply a Torque(Rotational Force) of the RigidBody at center of mass.
		* @param torque_, Vector3 which specify the torque direction and magnitude.
		*/
		void applyTorque(const Vector3 &torque_);

		/**
		* Apply a LinearImpulse (Delta Velocity) of the RigidBody at specific point around its center of mass.
		* @param impulse_, Vector3 which specify the impulse direction and magnitude.
		* @param point_, Vector3 which specify the point the impulse act on the Rigidbody. 
		*/
		void applyLinearImpulse(const Vector3 &impulse_, const Vector3 &point_);

		/**
		* Apply a LinearImpulse (Delta Velocity) of the RigidBody at its center of mass.
		* @param impulse_, Vector3 which specify the impulse direction and magnitude.
		*/
		void applyLinearImpulseToCenter(const Vector3 &impulse_);

		/**
		* Apply a AngularImpulse (Delta Angular Velocity) of the RigidBody at its center of mass.
		* @param angularImpulse_, Vector3 which specify the impulse direction and magnitude.
		*/
		void applyAngularImpulse(const Vector3 &angularImpulse_);

		/**
		* Get the Mass of the RigidBody.
		* @return float, the mass of rigidbody. 
		*/
		float getMass() const;

		/**
		* Get the Moment of Inertia of the RigidBody.
		* @return Vector3, the Moment of Inertia of rigidbody. 
		*/
 
		Vector3 getInertia() const;

		/**
		* Convert a Position in Local Space of the RigidBody to a corresponding Position in the World Space.
		* @param localPoint_, Vector3 which input the position in Local Space to be converted.
		* @return Vector3, the corresponding position in World Space. 
		*/
		Vector3 getWorldPoint(const Vector3 &localPoint_) const;

		/**
		* Convert a Directional Vector in Local Space of the RigidBody to a corresponding Direction in the World Space.
		* @param localVector_, Vector3 which input the direction in Local Space to be converted.
		* @return Vector3, the corresponding direction in World Space. 
		*/
		Vector3 getWorldVector(const Vector3 &localVector_) const;

		/**
		* Convert a Position in World Space of the RigidBody to a corresponding Position in the Local Space.
		* @param worldPoint_, Vector3 which input the position in World Space to be converted.
		* @return Vector3, the corresponding position in Local Space. 
		*/
		Vector3 getLocalPoint(const Vector3 &worldPoint_) const;

		/**
		* Convert a Directional Vector in World Space of the RigidBody to a corresponding Direction in the Local Space.
		* @param worldVector_, Vector3 which input the direction in World Space to be converted.
		* @return Vector3, the corresponding direction in World Space. 
		*/
		Vector3 getLocalVector(const Vector3 &worldVector_) const;

		/**
		* Get the Linear Velocity of specific point in World Space on the Rigidbody.
		* @param worldPoint_, Vector3 which specify the point in World Space.
		* @return Vector3, the Velocity of specific point in World Space on the Rigidbody. 
		*/
		Vector3 getLinearVelocityFromWorldPoint(const Vector3 &worldPoint_) const;

		/**
		* Get the Linear Velocity of specific point in Local Space on the Rigidbody.
		* @param localPoint_, Vector3 which specify the point in Local Space.
		* @return Vector3, the Velocity of specific point in Local Space on the Rigidbody. 
		*/
		Vector3 getLinearVelocityFromLocalPoint(const Vector3 &localPoint_) const;

		/**
		* Set the Linear Damping Factor of the RigidBody. The Linear Damping is a reduction of linear velocity due to the
		* loss of kinetic energy for some reason(e.g. friction, sound)
		* @param linearDamping_, float which specify the linear Damping factor of the RigidBody. 
		*/
		void setLinearDamping(float linearDamping_);

		/**
		* Get the Linear Damping Factor of the RigidBody. The Linear Damping is a reduction of linear velocity due to the
		* loss of kinetic energy for some reason(e.g. friction, sound)
		* @return float, the linear damping factor of the RigidBody. 
		*/
		float getLinearDamping() const;
	
		/**
		* Set the Angular Damping Factor of the RigidBody. The Angular Damping is a reduction of angular velocity due to the
		* loss of kinetic energy for some reason(e.g. friction, sound)
		* @param angularDamping_, float which specify the angular Damping factor of the RigidBody. 
		*/
		void setAngularDamping(float angularDamping_);

		/**
		* Get the Angular Damping Factor of the RigidBody. The Angular Damping is a reduction of lienar velocity due to the
		* loss of kinetic energy for some reason(e.g. friction, sound)
		* @return float, the angular damping factor of the RigidBody. 
		*/
		float getAngularDamping() const;
	
		/**
		* Set the RigidBody Type. RigidBody can be STATIC, DYNAMIC, KINEMATIC
		* @param type_, Physics3::RigidBody::Type, the type of rigidbody. 
		*/
		void setType(Physics3::RigidBody::Type type_);

		/**
		* Get the RigidBody Type. RigidBody can be STATIC, DYNAMIC, KINEMATIC
		* @return type_, Physics3::RigidBody::Type, the type of rigidbody. 
		*/
		Physics3::RigidBody::Type getType() const;

		/**
		* Set the Material of RigidBody.
		* @param material_, the material of rigidbody. 
		* @see Physics3::Material
		*/
		void setMaterial(const Physics3::Material &material_);

		/**
		* Get the Material RigidBody.
		* @return Physics3::Material, the material of rigidbody. 
		* @see Physics3::Material
		*/
		Physics3::Material getMaterial() const;

		/**
		* Set the CollisionFilter of RigidBody.
		* @param collisionFilter_, the collision Filter of rigidbody. 
		* @see Physics3::CollisionFilter
		*/
		void setCollisionFilter(const Physics3::CollisionFilter &collisionFilter_);

		/**
		* Get the Physics3::CollisionFilter RigidBody.
		* @return Physics3::CollisionFilter, the collision Filter of rigidbody. 
		* @see Physics3::CollisionFilter
		*/
		Physics3::CollisionFilter getCollisionFilter() const;

		/**
		* Set whether or not the Rigidbody use continuous collision detection(bullet). 
		* Continuous Collision Detection need more calculation, Only use on fast or small rigidbody only. 
		* @param flag,  true rigid is bullet. 
		*				false rigid is not a bullet. 
		*/
		void setBullet(bool flag);

		/**
		* Check whether or not the Rigidbody use continuous collision detection(bullet). 
		* Continuous Collision Detection need more calculation, Only use on fast or small rigidbody only. 
		* @return true  : is bullet. 
		*	      false : not a bullet. 
		*/
		bool isBullet() const;

		/**
		* Set whether or not the Rigidbody is allowed to enter to sleep mode while isolated. 
		* Isolated and Steady rigid body will go to sleep and will not participate in physics calculation. save CPU
		* @param flag,  true: allow to enter sleep mode. 
		*				false not allow to enter sleep mode. 
		*/
		void setSleepingAllowed(bool flag);

		/**
		* Check whether or not the Rigidbody is allowed to enter to sleep mode while isolated. 
		* Isolated and Steady rigid body will go to sleep and will not participate in physics calculation. save CPU
		* @return  true : allow to enter sleep mode. 
		*		   false: not allow to enter sleep mode. 
		*/
		bool isSleepingAllowed() const;

		/**
		* Set Rigidbody to awake state. 
		* Rigid Body in Awake State will participate into physics calculation and will enter Sleep State if it become Steady.
		* @param flag,  true: allow to enter sleep mode. 
		*				false not allow to enter sleep mode. 
		*/
		void setAwake(bool flag);

		/**
		* Check if Rigidbody is in awake state. 
		* Rigid Body in Awake will participate into physics calculation and will enter Sleep State if it become Steady.
		* @return flag,  true : in awake state
		*				 false: not in awake state
		*/
		bool isAwake() const;

		/**
		* Set Rigidbody to active state. 
		* Rigid Body in Active State will participate into physics calculation.
		* @param flag, true : in active state
		*			   false: not in active state
		*/
		void setActive(bool flag);

		/**
		* Check if Rigidbody to active state. 
		* Rigid Body in Active State will participate into physics calculation.
		* @return  true : in active state
		*		   false: not in active state
		*/
		bool isActive() const;

		/**
		* Set the CallBack Function for collision event between rigidbodies. 
		* @param collisionCB_, Functor : the Collision CallBack Function
		*/
		void setCollisionCallBack(Functor *collisionCB_);

		/**
		* Get the CallBack Function for collision event between rigidbodies. 
		* @return Functor : the CallBack Function
		*/
		Functor *getCollisionCallBack() const;
	
		/**
		* Set the CallBack Function for destruction event of the joint connected on the rigidbody. 
		* @param destructionCB_, Functor : the Destruction CallBack Function
		*/
		void setDestuctionCallBack(Functor *destructionCB_);

		/**
		* Get the CallBack Function for  destruction event of the joint connected on the rigidbody.
		* @return Functor : the CallBack Function
		*/
		Functor *getDestuctionCallBack() const;

		/**
		* Set the pointer for custom user data. 
		* @param userData_: the User Pointer
		*/
		void setUserData(void *userData_);

		/**
		* Get the pointer for custom user data. 
		* @return the User Pointer
		*/
		void *getUserData() const;
	protected:
		/**
		* Construct the RigidBody 
		* @param type_: the Type of RigidBody
		* @param shape_: the Shape3 of rigidbody
		* @param material_: the Material of RigidBody
		* @param collisionFilter_: the Physics3::CollisionFilter
		* @see Physics3::RigidBody::Type
		* @see Shape3
		* @see Physics3::Material
		* @see Physics3::CollisionFilter
		*/
		bool constructRigidBody(Physics3::RigidBody::Type type_,
								const Shape3 *shape_, 
								const Physics3::Material &material_, 
								const Physics3::CollisionFilter &collisionFilter_);

		/**
		* Update the rigidbody and the owner. 
		* @param dt, the delta of the game cycle
		*/
		void updateRigidBody(float dt);

		/**
		* Destruct the rigidbody. 
		*/
		void destructRigidBody();
	private:
		/**
		* calculate the mass and moment of inertia according to the shape and density
		* @param density, the density of the shape
		* @param mass, the result of the mass of the shape is returned here
		* @param localInertia, the result of the moment of inertia of the shape is returned here
		*/
		void calculateMass(float density_, float &mass_, Vector3 &localInertia_) const;

		/**
		* helper function for calculate Mass Properties based on type of rigidbody
		*/
		void updateMassProps();

		/**
		* helper function for update Collision Flags, calculate activation state based on type of rigidbody
		*/
		void updateCollisionFlags();

		/**
		* helper function for updating Activation State, calculate activation state based on type of rigidbody
		*/
		void updateActivationState();

		void *getHandle();

		/**
		* Handle Debuger Rendering Event of the Component
		*/
		virtual void onDebugRender(IComponentDebugRenderer &debugRenderer)
		{
		}
	///////////////////////////////////////////////////////////////////////////////////
	public:
	protected:
	private:
		void *handle;
	};

	class Vehicle : public Component
	{
	friend class World;
	friend class Manager;
	////////////////////////////////////////////////////////////////
	public:
		class Params
		{
		public:
			Params();

			Vector3									bodyHalfSize;
			Vector3									bodyGroundOffset;		

			float									suspensionStiffness;
			float									suspensionCompression;
			float									suspensionDamping;
			float									suspensionRestLength;
			float									maxSuspensionTravelCm;
			float									maxSuspensionForce;

			float									frictionSlip;
			float									rollInfluence;

			float									wheelRadius;
			float									wheelWidth;
			float									wheelFriction;

			float									connectionHeight;
		};

		class WheelInfo
		{
		public:
			//set by raycaster
			Vector3	contactNormalWS;	/**< contact Normal				*/ 
			Vector3	contactPointWS;		/**< raycast Hit Point			*/ 
			float	suspensionLength;	/**< suspension length			*/
			Vector3	hardPointWS;		/**< raycast starting point		*/ 
			Vector3	wheelDirectionWS;	/**< direction in worldspace	*/ 
			Vector3	wheelAxleWS;		/**< axle in worldspace			*/ 
			bool	isInContact;
			// void*	groundObject;	/**< friction parameter			*/ 

			Matrix4		worldTransform;	/**< world Transform			*/ 
		};

		/**
		* Vehicle Constructor.
		* To Construct the Vehicle for the owner.
		* @param owener_, the owner of this component
		*/
		Vehicle(Component::Owner &owner_);


		/**
		* Vehicle Destructor.
		* To Destruct the Vehicle for the owner.
		*/
		~Vehicle();

		DECLARE_COMPONENT(Vehicle, Component, false)
	////////////////////////////////////////////////////////////////
		PROPERTY(Vector3, BodyHalfSize);
		PROPERTY(Vector3, BodyGroundOffset);
		PROPERTY(float, SuspensionStiffness);
		PROPERTY(float, SuspensionCompression);
		PROPERTY(float, SuspensionDamping);
		PROPERTY(float, SuspensionRestLength);
		PROPERTY(float, MaxSuspensionTravelCm);
		PROPERTY(float, MaxSuspensionForce);
		PROPERTY(float, FrictionSlip);
		PROPERTY(float, RollInfluence);
		PROPERTY(float, WheelRadius);
		PROPERTY(float, WheelWidth);
		PROPERTY(float, WheelFriction);
		PROPERTY(float, ConnectionHeight);
	public:
		void setParams(Physics3::Vehicle::Params &params);
		const Physics3::Vehicle::Params getParams() const;

		/**
		* Set the Transform of the RigidBody.
		* @param transform_, Matrix4 which specify the position, rotation, scale of rigidbody.
		*/
		void setTransform(const Matrix4 &transform_);

		/**
		* Get the Transform of the RigidBody.
		* @param transform_, Matrix4 which receive the position, rotation, scale of rigidbody.
		*/
		void getTransform(Matrix4 &transform_) const;

		/**
		* Set the Position of the RigidBody.
		* @param position_, Vector3 which specify the position of rigidbody.
		*/
		void setPosition(const Vector3 &position_);

		/**
		* Get the Position of the RigidBody.
		* @return Vector3, the position of rigidbody.
		*/
		const Vector3 &getPosition() const;

		/**
		* Set the Angular Position of the RigidBody.
		* @param axis_, Vector3 which specify the axis of angular position.
		* @param angle_, float which specify the degree (in radian) rotate around the axis.
		*/
		void setAngularPosition(const Vector3 &axis_, float angle_);

		/**
		* Set the Angular Position of the RigidBody.
		* @param angularPosition_, Quaternion which specify the rotation and axis of rotation.
		*/
		void setAngularPosition(const Quaternion &angularPosition_);

		/**
		* Get the Angular Position of the RigidBody.
		* @return Quaternion, the angular position of rigidbody.
		*/
		Quaternion getAngularPosition() const;

		/**
		* Set the Velocity of the RigidBody.
		* @param velocity_, Vector3 which specify the velocity of rigidbody.
		*/
		void setLinearVelocity(const Vector3 &velocity_);

		/**
		* Get the Velocity of the RigidBody.
		* @return Vector3, the velocity of rigidbody.
		*/
		const Vector3 &getLinearVelocity() const;

		/**
		* Set the Angular Velocity of the RigidBody.
		* @param angularVel_, Vector3 which specify the axis of rotation with its length represent the angle (in radian).
		*/
		void setAngularVelocity(const Vector3 &angularVel_);

		/**
		* Get the Angular Velocity of the RigidBody.
		* @return Vector3, the angular velocity of rigidbody. which represent axis of rotation and
		* its length represent the angle of rotation (in radian).
		*/
		const Vector3 &getAngularVelocity() const;

		/**
		* Set the Linear Factor of the RigidBody.
		* @param factor_, Vector3 which specify the linear factor of rigidbody. Linear Factor scales the amount of linear 
		* motion along each axis.
		*/
		void setLinearFactor(const Vector3 &factor_);

		/**
		* Get the Linear Factor of the RigidBody.
		* @return Vector3, the linear factor of rigidbody. 
		* @see setLinearFactor()
		*/
		const Vector3 &getLinearFactor() const;

		/**
		* Set the Angular Factor of the RigidBody.
		* @param factor_, Vector3 which specify the angular factor of rigidbody. 
		* Angular Factor scales the amount of rotation motion along each axis.
		*/
		void setAngularFactor(const Vector3 &factor_);

		/**
		* Get the Angular Factor of the RigidBody.
		* @return Vector3, the angular factor of rigidbody. 
		* @see setAngularFactor()
		*/
		const Vector3 &getAngularFactor() const;

		/**
		* Apply a Force of the RigidBody at specific point around its center of mass.
		* @param force_, Vector3 which specify the force direction and magnitude.
		* @param point_, Vector3 which specify the point the force act on the Rigidbody. 
		*/
		void applyForce(const Vector3 &force_, const Vector3 &point_);

		/**
		* Apply a Force of the RigidBody at center of its center of mass.
		* @param force_, Vector3 which specify the force direction and magnitude.
		*/
		void applyForceToCenter(const Vector3 &force_);

		/**
		* Apply a Torque(Rotational Force) of the RigidBody at center of mass.
		* @param torque_, Vector3 which specify the torque direction and magnitude.
		*/
		void applyTorque(const Vector3 &torque_);

		/**
		* Apply a LinearImpulse (Delta Velocity) of the RigidBody at specific point around its center of mass.
		* @param impulse_, Vector3 which specify the impulse direction and magnitude.
		* @param point_, Vector3 which specify the point the impulse act on the Rigidbody. 
		*/
		void applyLinearImpulse(const Vector3 &impulse_, const Vector3 &point_);

		/**
		* Apply a LinearImpulse (Delta Velocity) of the RigidBody at its center of mass.
		* @param impulse_, Vector3 which specify the impulse direction and magnitude.
		*/
		void applyLinearImpulseToCenter(const Vector3 &impulse_);

		/**
		* Apply a AngularImpulse (Delta Angular Velocity) of the RigidBody at its center of mass.
		* @param angularImpulse_, Vector3 which specify the impulse direction and magnitude.
		*/
		void applyAngularImpulse(const Vector3 &angularImpulse_);

		/**
		* Get the Mass of the RigidBody.
		* @return float, the mass of rigidbody. 
		*/
		float getMass() const;

		/**
		* Get the Moment of Inertia of the RigidBody.
		* @return Vector3, the Moment of Inertia of rigidbody. 
		*/
		Vector3 getInertia() const;

		/**
		* Convert a Position in Local Space of the RigidBody to a corresponding Position in the World Space.
		* @param localPoint_, Vector3 which input the position in Local Space to be converted.
		* @return Vector3, the corresponding position in World Space. 
		*/
		Vector3 getWorldPoint(const Vector3 &localPoint_) const;

		/**
		* Convert a Directional Vector in Local Space of the RigidBody to a corresponding Direction in the World Space.
		* @param localVector_, Vector3 which input the direction in Local Space to be converted.
		* @return Vector3, the corresponding direction in World Space. 
		*/
		Vector3 getWorldVector(const Vector3 &localVector_) const;

		/**
		* Convert a Position in World Space of the RigidBody to a corresponding Position in the Local Space.
		* @param worldPoint_, Vector3 which input the position in World Space to be converted.
		* @return Vector3, the corresponding position in Local Space. 
		*/
		Vector3 getLocalPoint(const Vector3 &worldPoint_) const;

		/**
		* Convert a Directional Vector in World Space of the RigidBody to a corresponding Direction in the Local Space.
		* @param worldVector_, Vector3 which input the direction in World Space to be converted.
		* @return Vector3, the corresponding direction in World Space. 
		*/
		Vector3 getLocalVector(const Vector3 &worldVector_) const;

		/**
		* Get the Linear Velocity of specific point in World Space on the Rigidbody.
		* @param worldPoint_, Vector3 which specify the point in World Space.
		* @return Vector3, the Velocity of specific point in World Space on the Rigidbody. 
		*/
		Vector3 getLinearVelocityFromWorldPoint(const Vector3 &worldPoint_) const;

		/**
		* Get the Linear Velocity of specific point in Local Space on the Rigidbody.
		* @param localPoint_, Vector3 which specify the point in Local Space.
		* @return Vector3, the Velocity of specific point in Local Space on the Rigidbody. 
		*/
		Vector3 getLinearVelocityFromLocalPoint(const Vector3 &localPoint_) const;

		/**
		* Set the Linear Damping Factor of the RigidBody. The Linear Damping is a reduction of linear velocity due to the
		* loss of kinetic energy for some reason(e.g. friction, sound)
		* @param linearDamping_, float which specify the linear Damping factor of the RigidBody. 
		*/
		void setLinearDamping(float linearDamping_);

		/**
		* Get the Linear Damping Factor of the RigidBody. The Linear Damping is a reduction of linear velocity due to the
		* loss of kinetic energy for some reason(e.g. friction, sound)
		* @return float, the linear damping factor of the RigidBody. 
		*/
		float getLinearDamping() const;
	
		/**
		* Set the Angular Damping Factor of the RigidBody. The Angular Damping is a reduction of angular velocity due to the
		* loss of kinetic energy for some reason(e.g. friction, sound)
		* @param angularDamping_, float which specify the angular Damping factor of the RigidBody. 
		*/
		void setAngularDamping(float angularDamping_);

		/**
		* Get the Angular Damping Factor of the RigidBody. The Angular Damping is a reduction of lienar velocity due to the
		* loss of kinetic energy for some reason(e.g. friction, sound)
		* @return float, the angular damping factor of the RigidBody. 
		*/
		float getAngularDamping() const;

		/**
		* Set the Material of RigidBody.
		* @param material_, the material of rigidbody. 
		* @see Physics3::Material
		*/
		void setMaterial(const Physics3::Material &material_);

		/**
		* Get the Material RigidBody.
		* @return Physics3::Material, the material of rigidbody. 
		* @see Physics3::Material
		*/
		Physics3::Material getMaterial() const;

		/**
		* Set the CollisionFilter of RigidBody.
		* @param collisionFilter_, the collision Filter of rigidbody. 
		* @see Physics3::CollisionFilter
		*/
		void setCollisionFilter(const Physics3::CollisionFilter &collisionFilter_);

		/**
		* Get the Physics3::CollisionFilter RigidBody.
		* @return Physics3::CollisionFilter, the collision Filter of rigidbody. 
		* @see Physics3::CollisionFilter
		*/
		Physics3::CollisionFilter getCollisionFilter() const;

		/**
		* Set whether or not the Rigidbody use continuous collision detection(bullet). 
		* Continuous Collision Detection need more calculation, Only use on fast or small rigidbody only. 
		* @param flag,  true rigid is bullet. 
		*				false rigid is not a bullet. 
		*/
		void setBullet(bool flag);

		/**
		* Check whether or not the Rigidbody use continuous collision detection(bullet). 
		* Continuous Collision Detection need more calculation, Only use on fast or small rigidbody only. 
		* @return true  : is bullet. 
		*	      false : not a bullet. 
		*/
		bool isBullet() const;

		/**
		* Set whether or not the Rigidbody is allowed to enter to sleep mode while isolated. 
		* Isolated and Steady rigid body will go to sleep and will not participate in physics calculation. save CPU
		* @param flag,  true: allow to enter sleep mode. 
		*				false not allow to enter sleep mode. 
		*/
		void setSleepingAllowed(bool flag);

		/**
		* Check whether or not the Rigidbody is allowed to enter to sleep mode while isolated. 
		* Isolated and Steady rigid body will go to sleep and will not participate in physics calculation. save CPU
		* @return  true : allow to enter sleep mode. 
		*		   false: not allow to enter sleep mode. 
		*/
		bool isSleepingAllowed() const;

		/**
		* Set Rigidbody to awake state. 
		* Rigid Body in Awake State will participate into physics calculation and will enter Sleep State if it become Steady.
		* @param flag,  true: allow to enter sleep mode. 
		*				false not allow to enter sleep mode. 
		*/
		void setAwake(bool flag);

		/**
		* Check if Rigidbody is in awake state. 
		* Rigid Body in Awake will participate into physics calculation and will enter Sleep State if it become Steady.
		* @return flag,  true : in awake state
		*				 false: not in awake state
		*/
		bool isAwake() const;

		/**
		* Set Rigidbody to active state. 
		* Rigid Body in Active State will participate into physics calculation.
		* @param flag, true : in active state
		*			   false: not in active state
		*/
		void setActive(bool flag);

		/**
		* Check if Rigidbody to active state. 
		* Rigid Body in Active State will participate into physics calculation.
		* @return  true : in active state
		*		   false: not in active state
		*/
		bool isActive() const;

		/**
		* Set the CallBack Function for collision event between rigidbodies. 
		* @param collisionCB_, Functor : the Collision CallBack Function
		*/
		void setCollisionCallBack(Functor *collisionCB_);

		/**
		* Get the CallBack Function for collision event between rigidbodies. 
		* @return Functor : the CallBack Function
		*/
		Functor *getCollisionCallBack() const;
	
		/**
		* Set the CallBack Function for destruction event of the joint connected on the rigidbody. 
		* @param destructionCB_, Functor : the Destruction CallBack Function
		*/
		void setDestuctionCallBack(Functor *destructionCB_);

		/**
		* Get the CallBack Function for  destruction event of the joint connected on the rigidbody.
		* @return Functor : the CallBack Function
		*/
		Functor *getDestuctionCallBack() const;

		/**
		* Set the pointer for custom user data. 
		* @param userData_: the User Pointer
		*/
		void setUserData(void *userData_);

		/**
		* Get the pointer for custom user data. 
		* @return the User Pointer
		*/
		void *getUserData() const;

		/**
		* Set the steering, -1 for full left, 0 for middle, 1 for full right 
		* @param steering_: the Steering value
		*/
		void setSteering(float steering_);

		/**
		* Set the Engine Force on the wheel 
		* @param force_: the Forward Engine Force
		*/
		void applyEngineForce(float force_);

		/**
		* Set the Brack Force on the wheel 
		* @param force_: the Brack Force
		*/
		void setBrakeForce(float force_);
		
		/**
		* Get the Speed of the vehicle 
		* @return float: the Speed of the vehicle 
		*/
		float getSpeed() const;

		/**
		* Get the Number of Wheels 
		* @return int: the Number of Wheels 
		*/
		int getNumWheels() const;

		/**
		* Get the World Transform of the car body 
		* @param Matrix4, retunr the World Transform of the car body 
		*/
		void getChassisWorldTransform(Matrix4 &worldTransform) const;

		/**
		* Get the Wheel Info of particular wheel
		* @return Physics3::Vehicle::WheelInfo, Wheel Info of wheel index by i 
		*/
		Physics3::Vehicle::WheelInfo getWheelInfo(int i);
	protected:
		/**
		* Construct the RigidBody 
		* @param material_: the Material of RigidBody
		* @param collisionFilter_: the Physics3::CollisionFilter
		* @see Physics3::Material
		* @see Physics3::CollisionFilter
		*/
		bool constructRigidBody(const Physics3::Material &material_, 
								const Physics3::CollisionFilter &collisionFilter_);

		/**
		* Update the rigidbody and the owner. 
		* @param dt, the delta of the game cycle
		*/
		void updateRigidBody(float dt);

		/**
		* Destruct the rigidbody. 
		*/
		void destructRigidBody();
	private:
		/**
		* calculate the mass and moment of inertia according to the shape and density
		* @param density, the density of the shape
		* @param mass, the result of the mass of the shape is returned here
		* @param localInertia, the result of the moment of inertia of the shape is returned here
		*/
		void calculateMass(float density_, float &mass_, Vector3 &localInertia_) const;

		/**
		* helper function for calculate Mass Properties based on type of rigidbody
		*/
		void updateMassProps();

		/**
		* helper function for update Collision Flags, calculate activation state based on type of rigidbody
		*/
		void updateCollisionFlags();

		/**
		* helper function for updating Activation State, calculate activation state based on type of rigidbody
		*/
		void updateActivationState();

		void *getHandle();

		/**
		* Handle Debuger Rendering Event of the Component
		*/
		virtual void onDebugRender(IComponentDebugRenderer &debugRenderer);
	///////////////////////////////////////////////////////////////////////////////////
	public:
	protected:
	private:
		void *handle;
	};

	class RayCastResult
	{
	public:
		RayCastResult()
		{
			hasHit = false;
		}

		bool			hasHit;							/**< return if the cast result hit something */ 
		Vector3			rayFromWorld;					/**< start point of the ray at world space */ 
		Vector3			rayToWorld;						/**< end point of the ray at world space */ 
		Vector<Vector3>	hitNormalWorlds;				/**< contact normal */ 
		Vector<Vector3>	hitPointWorlds;					/**< contact point */ 
		Vector<float>	hitFractions;					/**< the t value of the intersection point */ 

		Vector<const void *> hitCollisionObjects;		/**< the Collided Objects */ 
	};

	class ConvexCastResult
	{
	public:
		ConvexCastResult()
		{
			hasHit = false;
		}

		bool			hasHit;							/**< return if the cast result hit something */ 
		Vector3			convexFromWorld;				/**< start point of the ray at world space */ 
		Vector3			convexToWorld;					/**< end point of the ray at world space */ 
		Vector<Vector3>	hitNormalWorlds;				/**< contact normal */ 
		Vector<Vector3>	hitPointWorlds;					/**< contact point */ 
		Vector<float>	hitFractions;					/**< the t value of the intersection point */

		Vector<const void *> hitCollisionObjects;		/**< the Collided Objects */ 
	};

	class World
	{
	friend class RigidBody;
	friend class Vehicle;
	friend class Manager;
	public:
		World();
		virtual ~World();

		/// Register a destruction listener. The listener is owned by you and must
		/// remain in scope.
		// void SetDestructionListener(b2DestructionListener* listener);

		/// Register a contact filter to provide specific control over collision.
		/// Otherwise the default filter is used (b2_defaultFilter). The listener is
		/// owned by you and must remain in scope. 
		// void SetContactFilter(b2ContactFilter* filter);

		/// Register a contact event listener. The listener is owned by you and must
		/// remain in scope.
		// void SetContactListener(b2ContactListener* listener);

		/// Register a routine for debug drawing. The debug draw functions are called
		/// inside with b2World2::DrawDebugData method. The debug draw object is owned
		/// by you and must remain in scope.
		// void setDebugDrawer(Physics3::DebugDrawer *debugDrawer_);

		/// Take a time step. This performs collision detection, integration,
		/// and constraint solution.
		/// @param timeStep the amount of time to simulate, this should not vary.
		/// @param velocityIterations for the velocity constraint solver.
		/// @param positionIterations for the position constraint solver.
		void process(float dt);

		/// Manually clear the force buffer on all bodies. By default, forces are cleared automatically
		/// after each call to Step. The default behavior is modified by calling SetAutoClearForces.
		/// The purpose of this function is to support sub-stepping. Sub-stepping is often used to maintain
		/// a fixed sized time step under a variable frame-rate.
		/// When you perform sub-stepping you will disable auto clearing of forces and instead call
		/// ClearForces after all sub-steps are complete in one pass of your game loop.
		/// @see SetAutoClearForces
		void clearForces();

		/// Call this to draw shapes and other debug draw data.
		void drawDebugData();

		/// Query the World2 for all fixtures that potentially overlap the
		/// provided AABB.
		/// @param callback a user implemented callback class.
		/// @param aabb the query box.
		void testPoint(const Vector3 &p, unsigned short group, unsigned short mask, Physics3::RayCastResult &result, bool closestOnly) const;

		/// Ray-cast the World2 for all fixtures in the path of the ray. Your callback
		/// controls whether you get the closest point, any point, or n-points.
		/// The ray-cast ignores shapes that contain the starting point.
		/// @param callback a user implemented callback class.
		/// @param point1 the ray starting point
		/// @param point2 the ray ending point
		void testRayCast(const Vector3 &p, const Vector3 &direction, unsigned short group, unsigned short mask, Physics3::RayCastResult &result, bool closestOnly) const;

		/// Ray-cast the World2 for all fixtures in the path of the ray. Your callback
		/// controls whether you get the closest point, any point, or n-points.
		/// The ray-cast ignores shapes that contain the starting point.
		/// @param callback a user implemented callback class.
		/// @param point1 the ray starting point
		/// @param point2 the ray ending point
		void testSphere(const Vector3 &p, float radius, unsigned short group, unsigned short mask, Physics3::ConvexCastResult &result, bool closestOnly) const;

		/// Ray-cast the World2 for all fixtures in the path of the ray. Your callback
		/// controls whether you get the closest point, any point, or n-points.
		/// The ray-cast ignores shapes that contain the starting point.
		/// @param callback a user implemented callback class.
		/// @param point1 the ray starting point
		/// @param point2 the ray ending point
		void testSphereCast(const Vector3 &p, const Vector3 &direction, float radius, unsigned short group, unsigned short mask, Physics3::ConvexCastResult &result, bool closestOnly) const;

		/// Get the World2 joint list. With the returned joint, use b2Joint::GetNext to get
		/// the next joint in the World2 list. A NULL joint indicates the end of the list.
		/// @return the head of the World2 joint list.
		// const b2Joint* GetJointList() const;

		/// Get the World2 contact list. With the returned contact, use b2Contact::GetNext to get
		/// the next contact in the World2 list. A NULL contact indicates the end of the list.
		/// @return the head of the World2 contact list.
		/// @warning contacts are created and destroyed in the middle of a time step.
		/// Use b2ContactListener to avoid missing contacts.
		// const b2Contact *GetContactList() const;

		/// Enable/disable sleep.
		void setAllowSleepingEnable(bool flag);
		bool isAllowSleepingEnabled() const;

		/// Enable/disable warm starting. For testing.
		void setWarmStartingEnable(bool flag);
		bool isWarmStartingEnabled() const;

		/// Enable/disable continuous physics. For testing.
		void setContinuousPhysicsEnable(bool flag);
		bool isContinuousPhysicsEnabled() const;

		/// Set flag to control automatic clearing of forces after each time step.
		void setAutoClearForcesEnable(bool flag);
		bool isAutoClearForcesEnabled() const;

		/// Enable/disable single stepped continuous physics. For testing.
		void setSubSteppingEnable(bool flag);
		bool isSubSteppingEnabled() const;

		/// Get the number of broad-phase proxies.
		int getProxyCount() const;

		/// Get the number of bodies.
		int getBodyCount() const;

		/// Get the number of joints.
		int getJointCount() const;

		/// Get the number of contacts (each may have 0 or more contact points).
		int getContactCount() const;

		/// Get the quality metric of the dynamic tree. The smaller the better.
		/// The minimum is 1.
		float getOptimizationQuality() const;

		/// Change the global gravity vector.
		void setGravity(const Vector3 &gravity);

		/// Get the global gravity vector.
		Vector3 getGravity() const;

		/// Is the World2 locked (in the middle of a time step).
		//bool isLocked() const;

		/// Get the contact manager for testing.
		//const b2ContactManager& GetContactManager() const;

		/// Get the current profile.
		//const b2Profile& GetProfile() const;

		/// Dump the World2 into the log file.
		/// @warning this should be called outside of a time step.
		//void dump();

		void *getHandle();
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

		void *handle;
	};

	class Manager
	{
	friend class Physics3;
	friend class RigidBody;
	friend class Vehicle;
	friend class World;
	public:
		Manager();
		virtual ~Manager();

		Physics3::World &getWorld(int i);
		const Physics3::World &getWorld(int i) const;
		int getNumWorlds() const;
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

		Vector<World> worlds;
	public:
	private:
	public:
		static Manager					&instance();
	private:
		static Manager					*_instance;
	};

////////////////////////////////////////////////////////////////////////////////////
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
