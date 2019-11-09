///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Graphics2Component_h_
#define _Graphics2Component_h_

#include "Stage.h"
#include "Component.h"
#include "Vector2.h"
#include "GXContext.h"
#include "GXDebugRenderer.h"
using namespace Magnum;

namespace Magnum
{

/**
* Graphics2Component.
* Graphics2Component is the base classes for all 2D Graphics Item
* @see Component
*/
class Graphics2Component : public Component
{
////////////////////////////////////////////////////////////////
public:
	/**
	* Graphics2Component Constructor.
	* To Construct the Graphics2Component for the owner.
	* @param owner_, the Component::Owner which owns this component.
	*/
	Graphics2Component(Component::Owner &owner_);

	/**
	* Graphics2Component Destructor.
	* To Destruct the Graphics2Component for the owner.
	*/
	virtual ~Graphics2Component();

	DECLARE_COMPONENT(Graphics2Component, Component, false)
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
