#ifndef _StateMachine_h_
#define _StateMachine_h_

#include "Array.h"
#include "Input.h"
#include "State.h"
#include <map>
using namespace std;
using namespace Magnum;

namespace Magnum
{

template<class Actor>
class StateMachine
{
public:
	StateMachine(Actor &actor_)
	: actor(actor_)
	, globalState(0)
	, currentState(0)
	, previousState(0)
	{
	}

	virtual ~StateMachine()
	{
	}

	void onUpdate(Actor &actor, float dt)
	{
		if(globalState)
			globalState->onUpdate(actor, dt);

		if(currentState)
			currentState->onUpdate(actor, dt);
	}

	void onPause()
	{
		if(globalState)
			globalState->onPause(actor);

		if(currentState)
			currentState->onPause(actor);
	}

	void onResume()
	{
		if(globalState)
			globalState->onResume(actor);

		if(currentState)
			currentState->onResume(actor);
	}

	void onTouchpad(Actor &actor, const Input::TouchpadEvent &evt)
	{
		if(globalState)
			globalState->onTouchpad(actor, evt);

		if(currentState)
			currentState->onTouchpad(actor, evt);
	}

	void onKeypad(Actor &actor, const Input::GamepadEvent &evt)
	{
		if(globalState)
			globalState->onKeypad(actor, evt);

		if(currentState)
			currentState->onKeypad(actor, evt);
	}

	void onAccelerator(Actor &actor, const Input::AcceleratorEvent &evt)
	{
		if(globalState)
			globalState->onAccelerator(actor, evt);

		if(currentState)
			currentState->onAccelerator(actor, evt);
	}

	void onGUI(Actor &actor, const Input::GUIEvent &evt)
	{
		if(globalState)
			globalState->onGUI(actor, evt);

		if(currentState)
			currentState->onGUI(actor, evt);
	}

	void changeState(const char *name)
	{
		previousState = currentState;

		if(globalState)
			globalState->onExit(actor);
		if(currentState)
			currentState->onExit(actor);

		currentState = getState(name);
		assert(currentState!=0);

		if(globalState)
			globalState->onEnter(actor);
		if(currentState)
			currentState->onEnter(actor);
	}

	void revertToPreviousState()
	{
		if(currentState)
			currentState->onExit(actor);

		currentState = previousState;
		assert(currentState!=0);

		if(currentState)
			currentState->onEnter(actor);
	}

	const String &getCurrentState() const
	{
		for(StateMapCItr itr=states.begin(); itr!=states.end(); itr++)
		{
			if(currentState==itr->second)
				return itr->first;
		}

		return 0;
	}
protected:
	void setGlobalState(State<Actor> *state)
	{
		globalState = state;
	}

	void addState(const char *name, State<Actor> *state)
	{
		states.insert(pair<String, State<Actor> *>(name, state));
	}

	void removeState(const char *name)
	{
		StateMapCItr itr = states.find(name);

		if(itr!=states.end())
		{
			states.erase(itr);
		}
	}

	State<Actor> *getState(const char *name)
	{
		StateMapCItr itr = states.find(name);

		if(itr!=states.end())
			return itr->second;
		else
			return 0;
	}
private:
	typedef typename std::map<String, State<Actor> *> StateMap;
	typedef typename std::map<String, State<Actor> *>::iterator StateMapItr;
	typedef typename std::map<String, State<Actor> *>::const_iterator StateMapCItr;

	State<Actor>				*globalState;
	map<String, State<Actor> *> states;

	State<Actor>				*currentState;
	State<Actor>				*previousState;

	Actor &actor;
};

};

#endif