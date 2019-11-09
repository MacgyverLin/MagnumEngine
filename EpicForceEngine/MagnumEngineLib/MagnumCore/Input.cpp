///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Input.h"
#include "Stage.h"
using namespace Magnum;

Vector< Functor1<Input::TouchpadEvent> *>		Input::touchpadMethods;
Vector<Input::TouchpadEvent>					Input::touchpadEvents;

Vector< Functor1<Input::GamepadEvent> *>		Input::gamepadMethods;
Vector<Input::GamepadEvent>						Input::gamepadEvents;

Vector< Functor1<Input::AcceleratorEvent> *>	Input::acceleratorMethods;
Vector<Input::AcceleratorEvent>					Input::acceleratorEvents;

Vector< Functor1<Input::GUIEvent> *>			Input::guiMethods;
Vector<Input::GUIEvent>							Input::guiEvents;

void Input::onMouseEvent(TouchpadEvent::Modifier modifier, Input::Event evt, int fingerID, float x, float y)
{
	Input::TouchpadEvent &touchpadEvent = Input::touchpadEvents.push();

	touchpadEvent.event				= evt;
	touchpadEvent.modifier			= (TouchpadEvent::Modifier)modifier;
	touchpadEvent.fingerID			= fingerID;
	touchpadEvent.position			= Vector2(x, y);

	touchpadEvent.wheelAxis			= 0;
	touchpadEvent.wheelRotation		= 0;
}

void Input::onMouseEvent(TouchpadEvent::Modifier modifier, Input::Event evt, float x, float y, int axis, int rotation)
{
	Input::TouchpadEvent &touchpadEvent = Input::touchpadEvents.push();

	touchpadEvent.event				= evt;
	touchpadEvent.modifier			= (TouchpadEvent::Modifier)modifier;
	touchpadEvent.fingerID			= 0;
	touchpadEvent.position			= Vector2(x, y);

	touchpadEvent.wheelAxis			= axis;
	touchpadEvent.wheelRotation		= rotation;
}

void Input::onKeyEvent(Input::Event evt, int keyCode)
{
	Input::GamepadEvent &gamepadEvent = Input::gamepadEvents.push();

	gamepadEvent.event				= evt;
	gamepadEvent.keyCode			= keyCode;
}

void Input::onAcceleratorEvent(Input::Event evt, float x, float y, float z)
{
	Input::AcceleratorEvent &acceleratorEvent = Input::acceleratorEvents.push();

	acceleratorEvent.event			= evt;
	acceleratorEvent.acceleration	= Vector3(x, y, z);
}

void Input::onGUIEvent(Input::Event evt, const unsigned char *buffer, int len)
{
	Input::GUIEvent &guiEvent		= Input::guiEvents.push();

	guiEvent.event				= evt;
	guiEvent.buffer.resize(len);
	System::memcpy(&guiEvent.buffer[0], buffer, len);
}

///////////////////////////////////////////////////////////////////////////////////
bool Input::Service::initiate()
{
	return true;
}

void Input::Service::process()
{
	for(int i=0; i<touchpadEvents.length(); i++)
	{
		Input::TouchpadEvent &touchpadEvt = Input::touchpadEvents[i];
		for(int j=0; j<touchpadMethods.length(); j++)
		{
			touchpadMethods[j]->invoke(touchpadEvt);
		}
	}

	for(int i=0; i<gamepadEvents.length(); i++)
	{
		Input::GamepadEvent &gamepadEvt = Input::gamepadEvents[i];
		for(int j=0; j<gamepadMethods.length(); j++)
		{
			gamepadMethods[j]->invoke(gamepadEvt);
		}
	}

	for(int i=0; i<acceleratorEvents.length(); i++)
	{
		Input::AcceleratorEvent &acceleratorEvt = Input::acceleratorEvents[i];
		for(int j=0; j<acceleratorMethods.length(); j++)
		{
			acceleratorMethods[j]->invoke(acceleratorEvt);
		}
	}

	for(int i=0; i<guiEvents.length(); i++)
	{
		Input::GUIEvent &guiEvt = Input::guiEvents[i];
		for(int j=0; j<guiMethods.length(); j++)
		{
			guiMethods[j]->invoke(guiEvt);
		}
	}

	touchpadEvents.clear();	
	gamepadEvents.clear();
	acceleratorEvents.clear();
	guiEvents.clear();
}

void Input::Service::pause()
{
}

void Input::Service::resume()
{
}

void Input::Service::terminate()
{
	touchpadMethods.destroy();
	touchpadEvents.destroy();

	gamepadMethods.destroy();
	gamepadEvents.destroy();

	acceleratorMethods.destroy();
	acceleratorEvents.destroy();

	guiMethods.destroy();
	guiEvents.destroy();
}

void Input::Service::clear()
{
	touchpadMethods.destroy();
	touchpadEvents.destroy();

	gamepadMethods.destroy();
	gamepadEvents.destroy();

	acceleratorMethods.destroy();
	acceleratorEvents.destroy();

	guiMethods.destroy();
	guiEvents.destroy();
}