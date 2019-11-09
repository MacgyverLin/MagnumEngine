#ifndef _State_h_
#define _State_h_

#include "Array.h"
#include "Input.h"
#include <map>
using namespace std;
using namespace Magnum;

namespace Magnum
{

template<class Actor>
class State
{
public:
	State()
	{
	}
	virtual ~State()
	{
	}

	virtual void onEnter(Actor &actor) = 0;
	virtual void onExit(Actor &actor) = 0;

	virtual void onPause(Actor &actor) = 0;
	virtual void onResume(Actor &actor) = 0;
	virtual void onUpdate(Actor &actor, float dt) = 0;
	virtual void onTouchpad(Actor &actor, const Input::TouchpadEvent &evt) = 0;
	virtual void onKeypad(Actor &actor, const Input::GamepadEvent &evt) = 0;
	virtual void onAccelerator(Actor &actor, const Input::AcceleratorEvent &evt) = 0;
	virtual void onGUI(Actor &actor, const Input::GUIEvent &evt) = 0;
};

};

#endif