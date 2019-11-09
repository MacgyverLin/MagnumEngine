///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _PlayModeScene_h_
#define _PlayModeScene_h_

#include <MagnumEngine.h>
#include <MagnumGame.h>
#include "ProjectModel.h"
using namespace Magnum;

namespace Magnum
{

class PlayModeScene : public BasicScene
{
public:
	PlayModeScene();
	virtual ~PlayModeScene();

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
protected:
private:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void initClassIndexMap();
	void initEntityCreators();

	bool loadSceneGraphCore(const char *path, const Vector3 &offset = Vector3::ZERO);
	bool loadEntities(InputStream &is, const Vector3 &offset = Vector3::ZERO);

	void releaseEntity(Entity *entity, bool updateViews = true);
	void releaseAllEntity();
	
	void collectTopLevelEntity(Vector<Entity *> &topLevelEntities, bool includeEditorEntity = false);
	void collectEntitiesRecursive(Vector<Entity *> &entities, Entity *topLevelEntity, bool includeEditorEntity = false);
	void collectAllEntities(Vector<Entity *> &entities, bool includeEditorEntity = false);
public:
protected:
private:
	Input::TouchpadMethod<PlayModeScene>			touchpadMethod;
	Input::GamepadMethod<PlayModeScene>				keypadMethod;
	Input::AcceleratorMethod<PlayModeScene>			acceleratorMethod;

	ClassIndexMap									classIndexMap;
};

};

#endif