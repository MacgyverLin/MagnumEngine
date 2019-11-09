///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _ProjectModel_h_
#define _ProjectModel_h_

#include <MagnumEngine.h>
#include "ProjectModelFSM.h"
#include "ProjectModelViewBase.h"
using namespace std;
using namespace Magnum;

namespace Magnum
{

#if defined(WIN32)
class ProjectModel : public ProjectModelBase
{
public:
	ProjectModel();
	virtual ~ProjectModel();

	virtual void initClassIndexMap();
	virtual int getNumClassIndices();
	virtual const char *getClass(int i);

	virtual void initEntityCreators();
	virtual int getNumEntityCreators(bool includeEditorActive);
	virtual Entity::ICreator *getEntityCreators(int i);

	virtual void beginCheckRawAssets();
	virtual bool isCheckingRawAssets();
	virtual void beginUpdateResources();
	virtual bool isUpdatingResources();
	virtual void updateResourceImporters();
	virtual void beginUpdateEntities();
	virtual bool isUpdatingEntities();

	virtual int getNumResourceCreators();
	virtual const ResourceImport::ICreator *getResourceCreators(int i) const;
	virtual ResourceImport::ICreator *getResourceCreators(int i);

	virtual Entity *createEntity(const char *classPath, const char *name, const Vector3 &position);
	virtual void addChild(Entity *newParent, Entity *child);
	virtual void removeChild(Entity *oldParent, Entity *child);
	virtual void changeParent(Entity *newParent, Entity *oldParent, Entity *child);

	virtual void setEntityName(Entity *entity, const char *name);

	virtual void releaseEntity(Entity *entity, bool updateViews = true);
	virtual void releaseAllEntity();
	virtual void selectEntity(Entity *entity);

	virtual void updateSelectedEntityName();
	virtual void updateSelectedEntityTransform();
	virtual void updateSelectedEntityValue();

	virtual void collectTopLevelEntity(Vector<Entity *> &topLevelEntities, bool includeEditorEntity = false);
	virtual void collectEntitiesRecursive(Vector<Entity *> &entities, Entity *topLevelEntity, bool includeEditorEntity = false);
	virtual void collectAllEntities(Vector<Entity *> &entities, bool includeEditorEntity = false);

	virtual Entity *getSelectedEntity();

	virtual const char *getCurrentProjectPath();
	virtual bool getOpenFlag();
	virtual void setCurrentProjectPath(const char *currentProjectPath_, bool openProject_);
	virtual const char *getCurrentSceneFileName();
	virtual void setCurrentSceneFileName(const char *currentSceneFileName_);
	virtual const char *getPrefabFileName();
	virtual void setPrefabFileName(const char *prefabFileName_);

	virtual void setCoordinateSystem(ProjectModel::CoordSys coordsys_);
	virtual ProjectModel::CoordSys getCoordinateSystem();
///////////////////////////////////////////////////////////////////////////////////
	bool createEditorEntities();
	bool fileProjectNew(const char *path);
	bool fileProjectOpen(const char *path);
	bool fileProjectSave();
	bool fileSceneNew(const char *file);
	bool fileSceneOpen(const char *file);
	bool fileSceneSave();
	bool fileSceneSaveAs(const char *file);
	bool fileSceneDelete(const char *path);
	bool filePrefabLoad(const char *file);
	bool filePrefabSave(const char *file);
	void fileExit();

	bool editUndo();
	bool editRedo();
	bool editCut();
	bool editCopy();
	bool editPaste();
	bool editDuplicate();
	bool editDelete();
	bool editFrameSelected();
	bool editFind();
	bool editSelectAll();

	bool debugScenePlay();
	bool debugSceneStop();

	bool loadSceneGraphCore(const char *path, const Vector3 &offset = Vector3::ZERO);
	bool loadEntities(InputStream &is, const Vector3 &offset = Vector3::ZERO);
	bool saveSceneGraphCore(const char *path);
	bool saveEntities(OutputStream &os, Vector<Entity *> &entities);
protected:
private:
///////////////////////////////////////////////////////////////////////////////////
public:
	virtual void changeState(const char *name);
	virtual void revertToPreviousState();
	virtual const String &getCurrentState();

	virtual void onUpdate(float dt);
	virtual void onPause();
	virtual void onResume();
	virtual void onTouchpad(const Input::TouchpadEvent &evt);
	virtual void onKeypad(const Input::GamepadEvent &evt);
	virtual void onAccelerator(const Input::AcceleratorEvent &evt);
	virtual void onGUI(const Input::GUIEvent &evt);
protected:
private:

///////////////////////////////////////////////////////////////////////////////////
public:
protected:
private:
	ClassIndexMap			classIndexMap;
	String					projectPath;
	bool					openProject;
	String					currentSceneFileName;
	String					prefabFileName;
	Vector<unsigned char>	clipsBoards;

	CoordSys				coordsys;

	Vector<String>			tags;
	Vector<String>			layers;

	ProjectModelFSM			stateMachine;
};

#elif ( defined(__ANDROID__ )  )
#else // IOS
#endif

}

#endif