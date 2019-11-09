///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Graphics3Component_h_
#define _Graphics3Component_h_

#include "Stage.h"
#include "Component.h"
#include "GXContext.h"
#include "GXDebugRenderer.h"
using namespace Magnum;

namespace Magnum
{

/**
* Graphics3Component.
* Graphics3Component is the base classes for all 3D Graphics Item
* @see Component
*/
class Graphics3Component : public Component
{
////////////////////////////////////////////////////////////////
public:
	enum Mode
	{
		DEFAULT		= 0,					/**< Default gizmo only show 3 axis						*/ 
		TRANSLATE	= 1,					/**< Translation gizmo show 3 axis and translate handle	*/ 
		ROTATE		= 2,					/**< Rotation gizmo only show 3 rotation circle handle	*/ 
		SCALE		= 3,					/**< Scale only show 3 axis and scale handle			*/ 
	};

	enum CoordSys
	{
		LOCAL	= 0,						/**< Render Gizmo in Local Space	*/ 
		PARENT	= 1,						/**< Render Gizmo in Parent Space	*/ 
		WORLD	= 2,						/**< Render Gizmo in World Space	*/ 
		VIEW	= 3,						/**< Render Gizmo in View Space		*/ 
	};
////////////////////////////////////////////////////////////////
public:
	/**
	* Graphics3Component Constructor.
	* To Construct the Graphics3Component for the owner.
	* @param owner_, the Component::Owner which owns this component.
	*/
	Graphics3Component(Component::Owner &owner_);

	/**
	* Graphics3Component Destructor.
	* To Destruct the Graphics3Component for the owner.
	*/
	virtual ~Graphics3Component();

	DECLARE_COMPONENT(Graphics3Component, Graphics3Component, false)
////////////////////////////////////////////////////////////////
public:
protected:
private:
public:
protected:
private:
};

};

#endif
