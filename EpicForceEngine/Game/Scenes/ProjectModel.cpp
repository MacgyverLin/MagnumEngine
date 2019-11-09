///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "ProjectModel.h"
#include "StartState.h"
#include "UpdateAssetsState.h"
#include "OperationMenuState.h"

#include "EntityPropertyReader.h"
#include "EntityPropertyWriter.h"
using namespace Magnum;

///////////////////////////////////////////////////////////////////////////////////
//
// EditorProjectModel
//
///////////////////////////////////////////////////////////////////////////////////
#if defined(WIN32)
ProjectModel::ProjectModel()
: ProjectModelBase()
, stateMachine(*this)
, projectPath("")
, currentSceneFileName("")
, prefabFileName("")
, coordsys(ProjectModelBase::LOCAL)
{
	Stage::enableEditorMode();
}

ProjectModel::~ProjectModel()
{
	releaseAllEntity();
}

void ProjectModel::initClassIndexMap()
{
	classIndexMap.clear();
	classIndexMap.initialize();

	setChanged(ProjectModelBase::CLASSIDXMAP);
}

int ProjectModel::getNumClassIndices()
{
	return classIndexMap.getNumClasses();
}

const char *ProjectModel::getClass(int i)
{
	return classIndexMap.getClassName(i);
}

void ProjectModel::initEntityCreators()
{
	setChanged(ProjectModelBase::ENTITIY_CREATORS);
}

int ProjectModel::getNumEntityCreators(bool includeEditorActive)
{
	return Entity::Factory::instance().getNumCreators();
}

Entity::ICreator *ProjectModel::getEntityCreators(int i)
{
	return Entity::Factory::instance().getCreator(i);
}

void ProjectModel::beginCheckRawAssets()
{
	ResourceImport::Factory::instance().beginCheckRawAssets();
}

bool ProjectModel::isCheckingRawAssets()
{
	return ResourceImport::Factory::instance().isCheckingRawAssets();
}

void ProjectModel::beginUpdateResources()
{
	const Vector<System::File> &newResourceFiles    = ResourceImport::Factory::instance().getNewReourceFiles();
	const Vector<System::File> &reloadResourceFiles = ResourceImport::Factory::instance().getReloadResourceFiles();
	const Vector<System::File> &deleteResourceFiles = ResourceImport::Factory::instance().getDeleteReourceFiles();

	ResourceAccess::Factory::instance().beginUpdateResources(newResourceFiles, reloadResourceFiles, deleteResourceFiles);
}

bool ProjectModel::isUpdatingResources()
{
	return ResourceAccess::Factory::instance().isUpdatingResources();
}

void ProjectModel::updateResourceImporters()
{
	setChanged(ProjectModelBase::RESOURCE_IMPORTERS);
}

void ProjectModel::beginUpdateEntities()
{
}

bool ProjectModel::isUpdatingEntities()
{
	return false;
}

int ProjectModel::getNumResourceCreators()
{
	return ResourceImport::Factory::instance().getNumCreators();
}

const ResourceImport::ICreator *ProjectModel::getResourceCreators(int i) const
{
	return ResourceImport::Factory::instance().getCreator(i);		
}

ResourceImport::ICreator *ProjectModel::getResourceCreators(int i)
{
	return ResourceImport::Factory::instance().getCreator(i);		
}

Entity *ProjectModel::createEntity(const char *classPath, const char *name, const Vector3 &position)
{
	String entityName;
	if(name)
		entityName = name;
	else
		entityName.format("%s%04d", classPath, Entity::Factory::instance().getNextUniqueID());

	Entity *child = Entity::createCore(classPath, entityName);
	assert(child);
	child->setLocalPosition(position);

	child->construct();
	child->start();

	child->select();

	this->setChanged(HIERARCHY_VIEW | HIERARCHY_SELECTION_CHANGED);
	this->notifyViews();

	return child;
}

void ProjectModel::addChild(Entity *newParent, Entity *child)
{
	if(newParent)
	{
		const Matrix4 &globalMat = child->getGlobalTransform();

		newParent->addChild(child);

		child->setGlobalTransform(globalMat);

		child->select();

		this->setChanged(HIERARCHY_VIEW | HIERARCHY_SELECTION_CHANGED);
		this->notifyViews();
	}
}

void ProjectModel::removeChild(Entity *oldParent, Entity *child)
{
	if(oldParent)
	{
		const Matrix4 &globalMat = child->getGlobalTransform(); 

		oldParent->removeChild(child);

		child->setGlobalTransform(globalMat);

		child->select();

		this->setChanged(HIERARCHY_VIEW | HIERARCHY_SELECTION_CHANGED);
		this->notifyViews();
	}
}

void ProjectModel::changeParent(Entity *newParent, Entity *oldParent, Entity *child)
{
	if(oldParent)
	{
		const Matrix4 &globalMat = child->getGlobalTransform(); 

		oldParent->removeChild(child);

		child->setGlobalTransform(globalMat);
	}

	if(newParent)
	{
		const Matrix4 &globalMat = child->getGlobalTransform();

		newParent->addChild(child);

		child->setGlobalTransform(globalMat);
	}

	child->select();

	this->setChanged(HIERARCHY_VIEW | HIERARCHY_SELECTION_CHANGED);
	this->notifyViews();
}

void ProjectModel::setEntityName(Entity *entity, const char *name)
{
	if(entity)
	{
		entity->setName(name);

		this->setChanged(SELECTED_ENTITY_NAME_CHANGED);
		this->notifyViews();
	}
}

void ProjectModel::releaseEntity(Entity *entity, bool updateViews)
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

		if(updateViews)
		{
			this->setChanged(HIERARCHY_VIEW | HIERARCHY_SELECTION_CHANGED);
			this->notifyViews();
		}
	}
}

void ProjectModel::releaseAllEntity()
{
	Vector<Entity *> topLevelEntities;
	collectTopLevelEntity(topLevelEntities, true);

	for(int i=0; i<topLevelEntities.length(); i++)
	{
		releaseEntity(topLevelEntities[i], false);
	}

	this->setChanged(HIERARCHY_VIEW | HIERARCHY_SELECTION_CHANGED);
	this->notifyViews();
}

void ProjectModel::selectEntity(Entity *entity)
{
	//if(selected!=entity)
	{
		//selected = entity;
		entity->select();

		this->setChanged(HIERARCHY_SELECTION_CHANGED);
		this->notifyViews();
	}
}

void ProjectModel::updateSelectedEntityName()
{
	Entity *selected = Entity::getSelected();
	if(selected)
	{
		String entityName = selected->getName();

		selected->stop();
		selected->destruct();

		selected->setName(entityName);

		selected->construct();
		selected->start();

		this->setChanged(SELECTED_ENTITY_NAME_CHANGED);
		this->notifyViews();
	}
}

void ProjectModel::updateSelectedEntityTransform()
{
	Entity *selected = Entity::getSelected();
	if(selected)
	{
		SRTTransform srtTransform = selected->getTransform();

		selected->stop();
		selected->destruct();

		selected->setLocalTransform(srtTransform.toMatrix4());

		selected->construct();
		selected->start();

		//this->setChanged(SELECTED_ENTITY_TRANSFORM_CHANGED);
		//this->notifyViews();
	}
}

void ProjectModel::updateSelectedEntityValue()
{
	Entity *selected = Entity::getSelected();
	if(selected)
	{
		Vector<unsigned char > buffer;
		MemOutputStream os(buffer);
		EntityPropertyWriter entityPropertyWriter(*selected);
		os << entityPropertyWriter;

		selected->stop();
		selected->destruct();

		MemInputStream is(&buffer[0], buffer.length());
		EntityPropertyReader entityPropertyReader(*selected);
		is >> entityPropertyReader;

		selected->construct();
		selected->start();

		this->setChanged(SELECTED_ENTITY_PROPERTIES_CHANGED);
		this->notifyViews();
	}
}

void ProjectModel::collectTopLevelEntity(Vector<Entity *> &topLevelEntities, bool includeEditorEntity)
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

void ProjectModel::collectEntitiesRecursive(Vector<Entity *> &entities, Entity *entity, bool includeEditorEntity)
{
	if( !entity->isEditorModeActive() || includeEditorEntity )
		entities.push() = entity;

	for(int i=0; i<entity->getNumChildren(); i++)
	{
		Entity *childEntity = (Entity *)(entity->getChild(i));

		collectEntitiesRecursive(entities, childEntity, includeEditorEntity);
	}
}

void ProjectModel::collectAllEntities(Vector<Entity *> &entities, bool includeEditorEntity)
{
	Vector<Entity *> topLevelEntities;
	collectTopLevelEntity(topLevelEntities, includeEditorEntity);

	for(int i=0; i<topLevelEntities.length(); i++)
	{
		collectEntitiesRecursive(entities, topLevelEntities[i], includeEditorEntity);
	}
}

Entity *ProjectModel::getSelectedEntity()
{
	return Entity::getSelected();
}

const char *ProjectModel::getCurrentProjectPath()
{
	return projectPath.text();
}

bool ProjectModel::getOpenFlag()
{
	return openProject;
}

void ProjectModel::setCurrentProjectPath(const char *projectPath_, bool openProject_)
{
	projectPath = projectPath_;
	openProject = openProject_;
}

const char *ProjectModel::getCurrentSceneFileName()
{
	return currentSceneFileName;
}

void ProjectModel::setCurrentSceneFileName(const char *currentSceneFileName_)
{
	currentSceneFileName = currentSceneFileName_;
}

const char *ProjectModel::getPrefabFileName()
{
	return prefabFileName;
}

void ProjectModel::setPrefabFileName(const char *prefabFileName_)
{
	prefabFileName = prefabFileName_;
}

void ProjectModel::setCoordinateSystem(ProjectModel::CoordSys coordsys_)
{
	coordsys = coordsys_;

	setChanged(COORDSYS_CHANGED);
	notifyViews();
}

ProjectModel::CoordSys ProjectModel::getCoordinateSystem()
{
	return coordsys;
}

bool ProjectModel::createEditorEntities()
{
	Entity *child = Entity::createCore("EditorEntity", "EditorEntity");
	assert(child);

	child->construct();
	child->start();

	return true;
}

bool ProjectModel::fileProjectNew(const char *path)
{
	Stage::enableEditorMode();

	projectPath		= path;
	currentSceneFileName	= "default.magnumscene";

	for(int i=0; i<tags.length(); i++)
		tags[i].format("Tag%d", i);

	for(int i=0; i<layers.length(); i++)
		layers[i].format("Layer%d", i);
	
	System::makeDirectory(projectPath);
	System::makeDirectory(projectPath + String("rawassets/scenes/")				);
	System::makeDirectory(projectPath + String("rawassets/prefabs/")			);
	System::makeDirectory(projectPath + String("settings/")						);
	System::makeDirectory(projectPath + String("device/application/bundle/")	);
	System::makeDirectory(projectPath + String("device/application/document/")	);
	System::makeDirectory(projectPath + String("device/external/")				);

	Stage::setRawAssetRootDirectory(projectPath + "rawassets/");
	Stage::setAssetRootDirectory(projectPath + "device/application/bundle/");
	Stage::setDocumentDirectory(projectPath + "device/application/document/");
	Stage::setExternalDirectory(projectPath + "device/external/");

	if( !fileSceneNew(currentSceneFileName) )
		return false;

	if( !fileProjectSave() )
		return false;

	return fileProjectOpen(path);
}

bool ProjectModel::fileProjectOpen(const char *path)
{
	Stage::enableEditorMode();

	FileInputStream is(String(path) + "project.magnumproj");
	if(!is.opened())
		return false;

	is >> currentSceneFileName;

	int len;
	is >> len;
	tags.resize(len);
	for(int i=0; i<tags.length(); i++)
		is >> tags[i];

	is >> len;
	layers.resize(len);
	for(int i=0; i<layers.length(); i++)
		is >> layers[i];

	projectPath = path;

	Stage::setRawAssetRootDirectory(projectPath + "rawassets/");
	Stage::setAssetRootDirectory(projectPath + "device/application/bundle/");
	Stage::setDocumentDirectory(projectPath + "device/application/document/");
	Stage::setExternalDirectory(projectPath + "device/external/");

	return fileSceneOpen(currentSceneFileName);
}

bool ProjectModel::fileProjectSave()
{
	Stage::enableEditorMode();

	FileOutputStream os(projectPath + "project.magnumproj");
	if(!os.opened())
		return false;

	os << currentSceneFileName;

	os << tags.length();
	for(int i=0; i<tags.length(); i++)
		os << tags[i];

	os << layers.length();
	for(int i=0; i<layers.length(); i++)
		os << layers[i];

	return fileSceneSave();
}

bool ProjectModel::fileSceneNew(const char *file)
{
	releaseAllEntity();
	//Entity::Factory::instance().clear();

	Stage::enableEditorMode();
	createEditorEntities();

	currentSceneFileName = file;

	setChanged(SCENE_CHANGED);
	notifyViews();
	
	return fileSceneSaveAs(file);
}

bool ProjectModel::fileSceneOpen(const char *file)
{
	releaseAllEntity();
	//Entity::Factory::instance().clear();

	Stage::enableEditorMode();
	createEditorEntities();

	String path(projectPath + String("rawassets/scenes/") + file);
	currentSceneFileName = file;

	setChanged(SCENE_CHANGED);
	notifyViews();
	
	return loadSceneGraphCore(path);
}

bool ProjectModel::fileSceneSave()
{
	return fileSceneSaveAs(currentSceneFileName);
}

bool ProjectModel::fileSceneSaveAs(const char *file)
{
	Stage::enableEditorMode();

	String path(projectPath + String("rawassets/scenes/") + file);
	currentSceneFileName = file;

	setChanged(SCENE_CHANGED);
	notifyViews();

	return saveSceneGraphCore(path);
}

bool ProjectModel::fileSceneDelete(const char *path)
{
	int a = 1;
	return true;
}

bool ProjectModel::filePrefabLoad(const char *file)
{
	Stage::enableEditorMode();

	String path(projectPath + String("rawassets/prefabs/") + file);
	
	return loadSceneGraphCore(path, Vector3(0, 0, -40));
}

bool ProjectModel::filePrefabSave(const char *file)
{
	Stage::enableEditorMode();

	String path(projectPath + String("rawassets/prefabs/") + file);

	return saveSceneGraphCore(path);
}

void ProjectModel::fileExit()
{
	releaseAllEntity();
}

bool ProjectModel::editUndo()
{
	return true;
}

bool ProjectModel::editRedo()
{
	return true;
}

bool ProjectModel::editCut()
{
	Entity *selectedEntity = getSelectedEntity();
	//if(!selectedEntity || selectedEntity->getParent()!=0)
	if(!selectedEntity)
		return false;

	if(!editCopy())
		return false;
	
	releaseEntity(selectedEntity);

	return true;
}

bool ProjectModel::editCopy()
{
	Entity *selectedEntity = getSelectedEntity();
	//if(!selectedEntity || selectedEntity->getParent()!=0)
	if(!selectedEntity)
		return false;

	Vector<Entity *> entities;
	collectEntitiesRecursive(entities, selectedEntity, false);

	Vector<unsigned char> tempBuffers;
	MemOutputStream os(tempBuffers);
	if(!saveEntities(os, entities))
		return false;

	clipsBoards = tempBuffers;

	return true;
}

bool ProjectModel::editPaste()
{
	if(clipsBoards.length()==0)
		return false;

	MemInputStream is(&clipsBoards[0], clipsBoards.length());
	if(!loadEntities(is, Vector3(0, 0, 20)))
		return false;

	setChanged(ProjectModelBase::SELECTED_ENTITY_PROPERTIES_CHANGED | ProjectModelBase::HIERARCHY_VIEW);
	notifyViews();

	return true;
}

bool ProjectModel::editDuplicate()
{
	if(!editCopy())
		return false;

	if(!editPaste())
		return false;

	return true;
}

bool ProjectModel::editDelete()
{
	Entity *selectedEntity = getSelectedEntity();
	//if(!selectedEntity || selectedEntity->getParent()!=0)
	if(!selectedEntity)
		return false;

	releaseEntity(selectedEntity);

	return true;
}

bool ProjectModel::editFrameSelected()
{
	return true;
}

bool ProjectModel::editFind()
{
	return true;
}

bool ProjectModel::editSelectAll()
{
	return true;
}

bool ProjectModel::debugScenePlay()
{
	if(saveSceneGraphCore("temp.scene"))
	{
		releaseAllEntity();
		//Entity::Factory::instance().clear();

		Stage::disableEditorMode();
		return loadSceneGraphCore("temp.scene");
	}
	else
		return false;
}

bool ProjectModel::debugSceneStop()
{
	releaseAllEntity();
	//Entity::Factory::instance().clear();

	Stage::enableEditorMode();
	createEditorEntities();
	if(loadSceneGraphCore("temp.scene"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ProjectModel::loadSceneGraphCore(const char *path, const Vector3 &offset)
{
	FileInputStream is(path);
	if(!is.opened())
		return false;

	loadEntities(is, offset);

	setChanged(ProjectModelBase::ENTITIY_CREATORS | ProjectModelBase::RESOURCE_IMPORTERS | ProjectModelBase::HIERARCHY_VIEW);
	notifyViews();

	return true;
}

bool ProjectModel::loadEntities(InputStream &is, const Vector3 &offset)
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

bool ProjectModel::saveSceneGraphCore(const char *path)
{
	FileOutputStream os(path);
	if(!os.opened())
		return false;

	Vector<Entity *> entities;
	collectAllEntities(entities);

	saveEntities(os, entities);

	return true;
}

bool ProjectModel::saveEntities(OutputStream &os, Vector<Entity *> &entities)
{
	std::map<const Entity *, int> parentIndicesMap;

	int numEntities = entities.length();
	os << numEntities;
	for(int i=0; i<entities.length(); i++)
	{
		assert(entities[i]);

		parentIndicesMap.insert(std::pair<const Entity *, int>(entities[i], i));

		int parentIdx = -1;
		const Entity *parent = (const Entity *)entities[i]->getParent();
		if(parent)
		{
			std::map<const Entity *, int>::iterator itr = parentIndicesMap.find(parent);
			
			// if has parent, but not in save list
			if(itr==parentIndicesMap.end())
			{
				parentIdx = -1;
			}
			else
			{
				parentIdx = itr->second;
			}
		}

		String classPath(entities[i]->getClassPath());
		
		EntityPropertyWriter entityPropertyWriter(*entities[i]);
		os << parentIdx;
		os << classPath;
		os << entityPropertyWriter;
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////
void ProjectModel::changeState(const char *name)
{
	stateMachine.changeState(name);

	this->setChanged(ProjectModelBase::STATE_CHANGED);
	this->notifyViews();
}

void ProjectModel::revertToPreviousState()
{
	stateMachine.revertToPreviousState();

	this->setChanged(ProjectModelBase::STATE_CHANGED);
	this->notifyViews();
}

const String &ProjectModel::getCurrentState()
{
	return stateMachine.getCurrentState();
}

void ProjectModel::onUpdate(float dt)
{
	stateMachine.onUpdate(*this, dt);
}

void ProjectModel::onPause()
{
	stateMachine.onPause();
}

void ProjectModel::onResume()
{
	stateMachine.onResume();
}

void ProjectModel::onTouchpad(const Input::TouchpadEvent &evt)
{
	stateMachine.onTouchpad(*this, evt);
}

void ProjectModel::onKeypad(const Input::GamepadEvent &evt)
{
	stateMachine.onKeypad(*this, evt);
}

void ProjectModel::onAccelerator(const Input::AcceleratorEvent &evt)
{
	stateMachine.onAccelerator(*this, evt);
}

void ProjectModel::onGUI(const Input::GUIEvent &evt)
{
	stateMachine.onGUI(*this, evt);
}

#elif ( defined(__ANDROID__ )  )
#else // IOS
#endif