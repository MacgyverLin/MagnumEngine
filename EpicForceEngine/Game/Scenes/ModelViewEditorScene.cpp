///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "ModelViewEditorScene.h"
using namespace Magnum;

ModelViewEditorScene::ModelViewEditorScene()
: touchpadMethod(this, &ModelViewEditorScene::touchpadEvent, true)
, keypadMethod(this, &ModelViewEditorScene::keypadEvent, true)
, acceleratorMethod(this, &ModelViewEditorScene::acceleratorEvent, true)
, guiMethod(this, &ModelViewEditorScene::guiEvent, true)
{
#if defined(WIN32)
	for(int i=0; i<Stage::getNumEditorProjectView(); i++)
	{
		ProjectViewBase *view = (ProjectViewBase *)(Stage::getEditorProjectView(i));
		projectModel.addView(view);
	}

	projectModel.changeState("Start");
#elif ( defined(__ANDROID__ )  )
#else // IOS
#endif
}

ModelViewEditorScene::~ModelViewEditorScene()
{
}

void ModelViewEditorScene::onConstruct()
{
}

void ModelViewEditorScene::onEnter()
{
}

void ModelViewEditorScene::onExit()
{
}

void ModelViewEditorScene::onUpdate(float dt)
{
#if defined(WIN32)
	projectModel.onUpdate(dt);
#elif ( defined(__ANDROID__ )  )
#else // IOS
#endif
}

void ModelViewEditorScene::onPause()
{
#if defined(WIN32)
	projectModel.onPause();
#elif ( defined(__ANDROID__ )  )
#else // IOS
#endif
}

void ModelViewEditorScene::onResume()
{
#if defined(WIN32)
	projectModel.onResume();
#elif ( defined(__ANDROID__ )  )
#else // IOS
#endif
}

bool ModelViewEditorScene::onTransition(TransitionMode)
{
	return false;
}

void ModelViewEditorScene::touchpadEvent(const Input::TouchpadEvent &evt)
{
#if defined(WIN32)
	projectModel.onTouchpad(evt);
#elif ( defined(__ANDROID__ )  )
#else // IOS
#endif
}

void ModelViewEditorScene::keypadEvent(const Input::GamepadEvent &evt)
{
#if defined(WIN32)
	projectModel.onKeypad(evt);
#elif ( defined(__ANDROID__ )  )
#else // IOS
#endif
}

void ModelViewEditorScene::acceleratorEvent(const Input::AcceleratorEvent &evt)
{
#if defined(WIN32)
	projectModel.onAccelerator(evt);
#elif ( defined(__ANDROID__ )  )
#else // IOS
#endif
}

void ModelViewEditorScene::guiEvent(const Input::GUIEvent &evt)
{
#if defined(WIN32)
	projectModel.onGUI(evt);
#elif ( defined(__ANDROID__ )  )
#else // IOS
#endif
}