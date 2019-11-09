///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "PlayModeScene.h"
//#include "ZipFile.h"
using namespace Magnum;

PlayModeScene::PlayModeScene()
: touchpadMethod(this, &PlayModeScene::touchpadEvent, true)
, keypadMethod(this, &PlayModeScene::keypadEvent, true)
, acceleratorMethod(this, &PlayModeScene::acceleratorEvent, true)
{
	/*
	{
		ZipFile zipFile;

		String zippath(Stage::getRawAssetRootDirectory());
		zippath += "1.zip";
		bool rval = zipFile.open(zippath.text());

		Vector<String> fileList;
		zipFile.getFilesList(fileList);

		for(int i=0; i<fileList.length(); i++)
		{
			if(System::isDirectory(fileList[i]))
				debug("Directory: %s", fileList[i]);
			else
				debug("File     : %s", fileList[i]);
		}

		int a = 1;
	}
	*/
	
	debug("step 1");
	initClassIndexMap();

	debug("step 2");
	initEntityCreators();

	debug("step 3");
	releaseAllEntity();
	//Entity::Factory::instance().clear();

	debug("step 4");
	Stage::disableEditorMode();
	
	debug("step 5");
	String path(Stage::getAssetRootDirectory());
	path += "scenes/default.magnumscene";

	loadSceneGraphCore(path);
}

PlayModeScene::~PlayModeScene()
{
}

void PlayModeScene::onConstruct()
{
}

void PlayModeScene::onEnter()
{
}

void PlayModeScene::onExit()
{
}

void PlayModeScene::onUpdate(float dt)
{
}

void PlayModeScene::onPause()
{
}

void PlayModeScene::onResume()
{
}

bool PlayModeScene::onTransition(TransitionMode)
{
	return false;
}

void PlayModeScene::touchpadEvent(const Input::TouchpadEvent &evt)
{
}

void PlayModeScene::keypadEvent(const Input::GamepadEvent &evt)
{
}

void PlayModeScene::acceleratorEvent(const Input::AcceleratorEvent &evt)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PlayModeScene::initClassIndexMap()
{
	classIndexMap.clear();
	classIndexMap.initialize();
}

void PlayModeScene::initEntityCreators()
{
}

bool PlayModeScene::loadSceneGraphCore(const char *path, const Vector3 &offset)
{
	FileInputStream is(path);
	if(!is.opened())
		return false;

	bool rval = loadEntities(is, offset);

	return rval;
}

bool PlayModeScene::loadEntities(InputStream &is, const Vector3 &offset)
{
	Vector<int>			parentIndices;
	Vector<Entity *>	entities;

	int numEntities;
	is >> numEntities;

	parentIndices.resize(numEntities);
	entities.resize(numEntities);
	for(int i=0; i<entities.length(); i++)
	{
		String				classPath;

		is >> parentIndices[i];
		is >> classPath;

		entities[i] = Entity::createCore(classPath, "");
		assert(entities[i]);
		EntityPropertyReader entityFieldReader(*entities[i]);
		is >> entityFieldReader;
	}

	for(int i=0; i<entities.length(); i++)
	{
		if(parentIndices[i]>=0)
		{
			entities[parentIndices[i]]->addChild(entities[i]);
		}
		else
		{
			Vector3 pos = entities[i]->getGlobalPosition();
			entities[i]->setGlobalPosition(pos + offset);
		}
	}

	for(int i=0; i<entities.length(); i++)
	{
		entities[i]->construct();
	}

	for(int i=0; i<entities.length(); i++)
	{
		entities[i]->start();
	}

	return true;
}

void PlayModeScene::releaseEntity(Entity *entity, bool updateViews)
{
	if(entity)
	{
		Vector<Entity *> entities;
		collectEntitiesRecursive(entities, entity, true);

		for(int i=0; i<entities.length(); i++)
		{
			entities[i]->unselect();
			entities[i]->stop();
		}

		for(int i=0; i<entities.length(); i++)
		{
			entities[i]->destruct();
		}

		for(int i=0; i<entities.length(); i++)
		{
			Entity::releaseCore(entities[i]);
		}

		Entity::Factory::instance().process(0);
	}
}

void PlayModeScene::releaseAllEntity()
{
	Vector<Entity *> topLevelEntities;
	collectTopLevelEntity(topLevelEntities, true);

	for(int i=0; i<topLevelEntities.length(); i++)
	{
		releaseEntity(topLevelEntities[i], false);
	}
}

void PlayModeScene::collectTopLevelEntity(Vector<Entity *> &topLevelEntities, bool includeEditorEntity)
{
	for(int i=0; i<Entity::Factory::instance().getNumCreators(); i++)
	{
		const Entity::ICreator *creator = Entity::Factory::instance().getCreator(i);

		for(int j=0; j<creator->getNumEntities(); j++)
		{
			const Entity *entity = creator->getEntity(j);
			if( (!entity->isEditorModeActive() || includeEditorEntity) && !entity->getParent())
				topLevelEntities.push() = (Entity *)entity;
		}
	}
}

void PlayModeScene::collectEntitiesRecursive(Vector<Entity *> &entities, Entity *entity, bool includeEditorEntity)
{
	if( !entity->isEditorModeActive() || includeEditorEntity )
		entities.push() = entity;

	for(int i=0; i<entity->getNumChildren(); i++)
	{
		Entity *childEntity = (Entity *)(entity->getChild(i));

		collectEntitiesRecursive(entities, childEntity, includeEditorEntity);
	}
}

void PlayModeScene::collectAllEntities(Vector<Entity *> &entities, bool includeEditorEntity)
{
	Vector<Entity *> topLevelEntities;
	collectTopLevelEntity(topLevelEntities, includeEditorEntity);

	for(int i=0; i<topLevelEntities.length(); i++)
	{
		collectEntitiesRecursive(entities, topLevelEntities[i], includeEditorEntity);
	}
}