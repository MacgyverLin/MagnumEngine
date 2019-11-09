///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Input_h_
#define _Input_h_

#include "Array.h"
#include "List.h"
#include "Delegate.h"
#include "Vector2.h"
#include "Vector3.h"

namespace Magnum
{
 
/**
* Input Services.
*/
class Input
{  	
	Input();
	virtual ~Input();
public:
	enum Event
	{
		EVENT_MOUSE_UP = 0,
		EVENT_MOUSE_DOWN,
		EVENT_MOUSE_MOVE,
		EVENT_MOUSE_WHEEL,
		EVENT_GAMEPAD_KEY_UP,
		EVENT_GAMEPAD_KEY_DOWN,
		EVENT_ACCELERATOR_UPDATE,
		EVENT_GUI,
		EVENT_NUM_EVENT
	};

	enum KeyCode
	{
		KEY_HOME			 = 0,
		KEY_BACK,
		KEY_MENU,
		KEY_SEARCH,

		KEY_SPECIAL0,
		KEY_SPECIAL1,
		KEY_SPECIAL2,
		KEY_SPECIAL3,
		KEY_SPECIAL4,
		KEY_SPECIAL5,
		KEY_SPECIAL6,
		KEY_SPECIAL7,

		KEYPAD0_UP,
		KEYPAD0_DOWN,
		KEYPAD0_LEFT,
		KEYPAD0_RIGHT,
		KEYPAD0_SELECT,
		KEYPAD0_START,
		KEYPAD0_BUTTON0,
		KEYPAD0_BUTTON1,
		KEYPAD0_BUTTON2,
		KEYPAD0_BUTTON3,
		KEYPAD0_L1,
		KEYPAD0_L2,
		KEYPAD0_L3,
		KEYPAD0_R1,
		KEYPAD0_R2,
		KEYPAD0_R3,

		KEYPAD1_UP,
		KEYPAD1_DOWN,
		KEYPAD1_LEFT,
		KEYPAD1_RIGHT,
		KEYPAD1_SELECT,
		KEYPAD1_START,
		KEYPAD1_BUTTON0,
		KEYPAD1_BUTTON1,
		KEYPAD1_BUTTON2,
		KEYPAD1_BUTTON3,
		KEYPAD1_L1,
		KEYPAD1_L2,
		KEYPAD1_L3,
		KEYPAD1_R1,
		KEYPAD1_R2,
		KEYPAD1_R3,

		KEYPAD2_UP,
		KEYPAD2_DOWN,
		KEYPAD2_LEFT,
		KEYPAD2_RIGHT,
		KEYPAD2_SELECT,
		KEYPAD2_START,
		KEYPAD2_BUTTON0,
		KEYPAD2_BUTTON1,
		KEYPAD2_BUTTON2,
		KEYPAD2_BUTTON3,
		KEYPAD2_L1,
		KEYPAD2_L2,
		KEYPAD2_L3,
		KEYPAD2_R1,
		KEYPAD2_R2,
		KEYPAD2_R3,

		KEYPAD3_UP,
		KEYPAD3_DOWN,
		KEYPAD3_LEFT,
		KEYPAD3_RIGHT,
		KEYPAD3_SELECT,
		KEYPAD3_START,
		KEYPAD3_BUTTON0,
		KEYPAD3_BUTTON1,
		KEYPAD3_BUTTON2,
		KEYPAD3_BUTTON3,
		KEYPAD3_L1,
		KEYPAD3_L2,
		KEYPAD3_L3,
		KEYPAD3_R1,
		KEYPAD3_R2,
		KEYPAD3_R3,

		NUM_KEYS
	};
public:
	template <typename U, typename P1>
	class InputDelegate1 : public Functor1<P1>
	{
		typedef void (U::*MemFunc)(const P1 &);

		U *who;
		MemFunc func;
	public:
		InputDelegate1(U *who_, MemFunc func_, bool editorModeActive_)
		: who(who_)
		, func(func_)
		, editorModeActive(editorModeActive_)
		{
			assert(who);
		}
	
		bool operator==(const MemFunc func_) const
		{
			return func == func_;
		}

		bool operator!=(const MemFunc func_) const
		{
			return func != func_;
		}

		InputDelegate1<U, P1> *clone() const
		{
			return new InputDelegate1<U, P1>(*this);
		}

		void operator=(const MemFunc func_)
		{
			func = func_;
		}

		virtual void invoke(const P1 &v1)
		{
			assert(who);
			if(func && (!Stage::isEditorMode() || editorModeActive) )
				(who->*func)(v1);
		}
	private:
		bool editorModeActive;
	};
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	class TouchpadEvent
	{
	public:
		enum Modifier
		{
			NONE	= 0x00,
			ALT		= 0x01,
			CTRL	= 0x02,
			SHIFT	= 0x04,
		};

		bool isAltDown() const
		{
			return (modifier & ALT)!=0;
		}

		bool isCtrlDown() const
		{
			return (modifier & CTRL)!=0;
		}

		bool isShiftDown() const
		{
			return (modifier & SHIFT)!=0;
		}

		Input::Event				event;
		TouchpadEvent::Modifier		modifier;
		int							fingerID;
		Vector2						position;
		int							wheelAxis;
		int							wheelRotation;
	};
	template <typename U>
	class TouchpadMethod : public InputDelegate1<U, TouchpadEvent>
	{
	public:
		typedef void (U::*Proc)(const TouchpadEvent &);

		TouchpadMethod(U *who, Proc proc, bool editorMode=false)
		: InputDelegate1<U, TouchpadEvent>(who, proc, editorMode)
		{
			//debug("TouchpadMethod new");
			touchpadMethods.push() = this;
		}
		virtual ~TouchpadMethod()
		{
			//debug("TouchpadMethod delete");
			int idx = touchpadMethods.search(this);
			if(idx>=0)
			{
				touchpadMethods.remove(idx);
			}
		}
		bool operator==(const Proc proc_) const {return InputDelegate1<U, TouchpadEvent>::proc==proc_;} 
		Proc &operator=(const Proc proc_){return InputDelegate1<U, TouchpadEvent>::proc=proc_;} 
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	class GamepadEvent
	{
	public:
		Input::Event	event;
		int				keyCode;
	};
	template <typename U>
	class GamepadMethod : public InputDelegate1<U, GamepadEvent>
	{
	public:
		typedef void (U::*Proc)(const GamepadEvent &);

		GamepadMethod(U *who, Proc proc, bool editorMode=false)
		: InputDelegate1<U, GamepadEvent>(who, proc, editorMode)
		{
			//debug("GamepadMethod new");
			gamepadMethods.push() = this;
		}
		virtual ~GamepadMethod()
		{
			//debug("GamepadMethod delete");
			int idx = gamepadMethods.search(this);
			if(idx>=0)
			{
				gamepadMethods.remove(idx);
			}
		}
		bool operator==(const Proc proc_) const {return InputDelegate1<U, GamepadEvent>::proc==proc_;} 
		Proc &operator=(const Proc proc_){return InputDelegate1<U, GamepadEvent>::proc=proc_;} 
	};

	//////////////////////////////////////////////////////////////////////////////////////////////
	class AcceleratorEvent
	{
	public:
		Input::Event	event;
		Vector3			acceleration;
	};
	template <typename U>
	class AcceleratorMethod : public InputDelegate1<U, AcceleratorEvent>
	{
	public:
		typedef void (U::*Proc)(const AcceleratorEvent &);

		AcceleratorMethod(U *who, Proc proc, bool editorMode=false)
		: InputDelegate1<U, AcceleratorEvent>(who, proc, editorMode)
		{
			//debug("AcceleratorMethod new");
			acceleratorMethods.push() = this;
		}
		virtual ~AcceleratorMethod()
		{
			//debug("AcceleratorMethod delete");
			int idx = acceleratorMethods.search(this);
			if(idx>=0)
			{
				acceleratorMethods.remove(idx);
			}
		}
		bool operator==(const Proc proc_) const {return InputDelegate1<U, AcceleratorEvent>::proc==proc_;} 
		Proc &operator=(const Proc proc_){return InputDelegate1<U, AcceleratorEvent>::proc=proc_;} 
	};
	
	//////////////////////////////////////////////////////////////////////////////////////////////
	class GUIEvent
	{
	public:
		enum Command
		{
			ChangeState		= 0x00000000,
			ChangeCoorSys	= 0x00000001
		};
		Input::Event				event;
		Input::GUIEvent::Command	command;

		String nextState;
		bool openProject;
		
		int	coordSys;

		Vector<unsigned char>	buffer;
	};
	template <typename U>
	class GUIMethod : public InputDelegate1<U, GUIEvent>
	{
	public:
		typedef void (U::*Proc)(const GUIEvent &);

		GUIMethod(U *who, Proc proc, bool editorMode=false)
		: InputDelegate1<U, GUIEvent>(who, proc, editorMode)
		{
			guiMethods.push() = this;
		}
		virtual ~GUIMethod()
		{
			int idx = guiMethods.search(this);
			if(idx>=0)
			{
				guiMethods.remove(idx);
			}
		}
		bool operator==(const Proc proc_) const {return InputDelegate1<U, GUIEvent>::proc==proc_;} 
		Proc &operator=(const Proc proc_){return InputDelegate1<U, GUIEvent>::proc=proc_;} 
	};

	static void onMouseEvent(TouchpadEvent::Modifier modifier, Input::Event evt, int fingerID, float x, float y);
	static void onMouseEvent(TouchpadEvent::Modifier modifier, Input::Event evt, float x, float y, int axis, int rotation);
	static void onKeyEvent(Input::Event evt, int keyCode);
	static void onAcceleratorEvent(Input::Event evt, float x, float y, float z);
	static void onGUIEvent(Input::Event evt, const unsigned char *buffer, int len);
private:
	static Vector<Functor1<TouchpadEvent> *>		touchpadMethods;
	static Vector<TouchpadEvent>					touchpadEvents;

	static Vector<Functor1<GamepadEvent> *>			gamepadMethods;
	static Vector<GamepadEvent>						gamepadEvents;

	static Vector<Functor1<AcceleratorEvent> *>		acceleratorMethods;
	static Vector<AcceleratorEvent>					acceleratorEvents;

	static Vector<Functor1<GUIEvent> *>				guiMethods;
	static Vector<GUIEvent>							guiEvents;
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

}

#endif