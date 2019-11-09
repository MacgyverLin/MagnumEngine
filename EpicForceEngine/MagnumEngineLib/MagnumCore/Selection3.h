///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Selection3_h_
#define _Selection3_h_

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

class Selection3
{
public:
	class Bound : public Component
	{
	public:
		Bound(Component::Owner &owner_);
		~Bound();

		DECLARE_COMPONENT(Bound, Component, false)
	////////////////////////////////////////////////////////////////
	public:
		void setOffsetTransform(const Matrix4 &offsetTransform_);
		const Matrix4 &getOffsetTransform() const;

		void setCategory(unsigned int category_);
		unsigned int getCategory() const;

		void setMask(unsigned int mask_);
		unsigned int getMask() const;

		void setUserData(void *userData_);
		void *getUserData() const;

		virtual bool rayCast(const Vector3 &from, const Vector3 &dir) = 0;
		virtual bool sphereCast(const Vector3 &from, float radius, const Vector3 &dir) = 0;

		void getInverseGlobalTransform(Matrix4 &globalTransform);
	protected:
	private:
	///////////////////////////////////////////////////////////////////////////////////
	public:
	protected:
	private:
		unsigned int category;
		unsigned int mask;
		Matrix4 offsetTransform;

		void *userData;
	};

	class Manager
	{
	friend class Selection3;
	friend class RigidBody;
	friend class World;
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
	public:
		static Manager					&instance();
	private:
		static Manager					*_instance;

		Vector<Selection3::Bound *>		bounds;
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
