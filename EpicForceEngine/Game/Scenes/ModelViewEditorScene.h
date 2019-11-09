///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _ModelViewEditorScene_h_
#define _ModelViewEditorScene_h_

#include <MagnumEngine.h>
#include <MagnumGame.h>
#include "ProjectModel.h"
using namespace Magnum;

class ModelViewEditorScene : public BasicScene
{
public:
	ModelViewEditorScene();
	virtual ~ModelViewEditorScene();

	virtual void onConstruct();								//	called after all constructors
	virtual void onEnter();									//	called after enter transition is done
	virtual void onExit();									//	called before exit transition starts
	virtual void onUpdate(float dt);						//	called each cycle while scene is up and running
	virtual void onPause();									//	called when about to paused
	virtual void onResume();								//	called when about to resume
	virtual bool onTransition(TransitionMode);				//	called while transitioning returning false stops transition mode

	void touchpadEvent(const Input::TouchpadEvent &evt);
	void keypadEvent(const Input::GamepadEvent &evt);
	void acceleratorEvent(const Input::AcceleratorEvent &evt);
	void guiEvent(const Input::GUIEvent &evt);
protected:
private:

public:
protected:
private:
	Input::TouchpadMethod<ModelViewEditorScene>				touchpadMethod;
	Input::GamepadMethod<ModelViewEditorScene>				keypadMethod;
	Input::AcceleratorMethod<ModelViewEditorScene>			acceleratorMethod;
	Input::GUIMethod<ModelViewEditorScene>					guiMethod;

#if defined(WIN32)
	ProjectModel											projectModel;
#elif ( defined(__ANDROID__ )  )
#else // IOS
#endif
};

#endif