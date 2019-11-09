///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _EditorEntity_h_
#define _EditorEntity_h_

#include <MagnumEngine.h>
using namespace Magnum;

class EditorEntity : public Entity
{
public:
/////////////////////////////////////////////////////////////
	EditorEntity();
	virtual ~EditorEntity();

	DECLARE_EDITOR_ENTITY(EditorEntity);
/////////////////////////////////////////////////////////////
	EditorCameraComponent &getCameraComponent();
	EditorGizmo &getEditorGizmo();
protected:
private:
	virtual bool onConstruct();
	virtual void onStart();
	virtual void onPause();
	virtual void onResume();
	virtual void onUpdate(float dt);
	virtual void onStop();
	virtual void onDestruct();

	void touchpadEvent(const Input::TouchpadEvent &evt);
	void keypadEvent(const Input::GamepadEvent &evt);
	void acceleratorEvent(const Input::AcceleratorEvent &evt);
/////////////////////////////////////////////////////
public:
protected:
private:
	Input::TouchpadMethod<EditorEntity>		touchpadMethod;
	Input::GamepadMethod<EditorEntity>		keypadMethod;
	Input::AcceleratorMethod<EditorEntity>	acceleratorMethod;

	EditorCameraComponent					cameraComponent;
	EditorGizmoRenderer						editorGizmoRenderer;
	EditorGizmo								editorGizmo;
};

#endif