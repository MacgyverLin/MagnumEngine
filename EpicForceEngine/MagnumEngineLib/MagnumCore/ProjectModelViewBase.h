#ifndef _ProjectModelViewBase_h_
#define _ProjectModelViewBase_h_

#include "Stage.h"
#include "Array.h"
#include "ResourceImport.h"
#include "Entity.h"
#include "Input.h"
using namespace Magnum;

namespace Magnum
{

#if defined(WIN32)

class ProjectViewBase;

class ProjectModelBase
{
public:
	enum CoordSys
	{
		LOCAL	= 0, 
		PARENT	= 1, 
		WORLD	= 2,
		VIEW	= 3, 
	};
	enum ChangeFlag
	{
		NONE								= 0x00000000,
		
		SCENE_CHANGED						= 0x00000001,

		STATE_CHANGED						= 0x00000002,

		CLASSIDXMAP							= 0x00000004,
		ENTITIY_CREATORS					= 0x00000008,
		RESOURCE_IMPORTERS					= 0x00000010,
		HIERARCHY_SELECTION_CHANGED			= 0x00000020,
		HIERARCHY_VIEW						= 0x00000040,

		SELECTED_ENTITY_NAME_CHANGED		= 0x00000080,
		SELECTED_ENTITY_TRANSFORM_CHANGED	= 0x00000100,
		SELECTED_ENTITY_PROPERTIES_CHANGED	= 0x00000200,

		RESOURCEIMPORT_SELECTION_CHANGED	= 0x00000400,

		COORDSYS_CHANGED					= 0x00000800,

		PROJECT_DIALOG						= 0x00001000,
		
		ALL									= 0xffffffff,
	};

	ProjectModelBase();
	~ProjectModelBase();

	virtual void initClassIndexMap() = 0;
	virtual int getNumClassIndices() = 0;
	virtual const char *getClass(int i) = 0;

	virtual void initEntityCreators() = 0;
	virtual int getNumEntityCreators(bool includeEditorActive) = 0;
	virtual Entity::ICreator *getEntityCreators(int i) = 0;

	virtual void beginCheckRawAssets() = 0;
	virtual bool isCheckingRawAssets() = 0;
	virtual void beginUpdateResources() = 0;
	virtual bool isUpdatingResources() = 0;
	virtual void beginUpdateEntities() = 0;
	virtual bool isUpdatingEntities() = 0;
	virtual void updateResourceImporters() = 0;

	virtual int getNumResourceCreators() = 0;
	virtual const ResourceImport::ICreator *getResourceCreators(int i) const = 0;
	virtual ResourceImport::ICreator *getResourceCreators(int i) = 0;

	virtual Entity *createEntity(const char *classPath, const char *name, const Vector3 &position) = 0;
	virtual void addChild(Entity *newParent, Entity *child) = 0;
	virtual void removeChild(Entity *oldParent, Entity *child) = 0;
	virtual void changeParent(Entity *newParent, Entity *oldParent, Entity *child) = 0;

	virtual void setEntityName(Entity *entity, const char *name) = 0;

	virtual void releaseEntity(Entity *entity, bool updateViews = true) = 0;
	virtual void releaseAllEntity() = 0;
	virtual void selectEntity(Entity *entity) = 0;

	virtual void updateSelectedEntityName() = 0;
	virtual void updateSelectedEntityTransform() = 0;
	virtual void updateSelectedEntityValue() = 0;

	virtual void collectTopLevelEntity(Vector<Entity *> &topLevelEntities, bool includeEditorEntity = false) = 0;
	virtual void collectEntitiesRecursive(Vector<Entity *> &entities, Entity *topLevelEntity, bool includeEditorEntity = false) = 0;
	virtual void collectAllEntities(Vector<Entity *> &entities, bool includeEditorEntity = false) = 0;

	virtual Entity *getSelectedEntity() = 0;

	virtual const char *getCurrentProjectPath() = 0;
	virtual bool getOpenFlag() = 0;
	virtual void setCurrentProjectPath(const char *currentProjectPath_, bool open) = 0;
	virtual const char *getCurrentSceneFileName() = 0;
	virtual void setCurrentSceneFileName(const char *currentSceneFileName_) = 0;
	virtual const char *getPrefabFileName() = 0;
	virtual void setPrefabFileName(const char *prefabFileName_) = 0;

	virtual void setCoordinateSystem(CoordSys coordsys) = 0;
	virtual CoordSys getCoordinateSystem() = 0;
///////////////////////////////////////////////////////////////////////////////////
public:
	virtual void changeState(const char *name) = 0;
	virtual void revertToPreviousState() = 0;
	virtual const String &getCurrentState() = 0;
protected:
private:
///////////////////////////////////////////////////////////////////////////////////
public:
	void addView(ProjectViewBase *view);
	int getNumViews() const;
	void removeView(ProjectViewBase *view);

	bool hasChanged(int flags);
	void notifyViews();

	void notifyViews(const Vector<unsigned char> &buffer);
	void setChanged(int flags);
protected:
	void clearChanged(int flags);
private:
	int flags;

	Vector<ProjectViewBase *> views;
};

////////////////////////////////////////////////////////////////////////////////////
class ProjectViewBase
{
friend class ProjectModelBase;
public:
	ProjectViewBase();
	~ProjectViewBase();

	ProjectModelBase &getModel();
protected:
	virtual void notify(int flags, ProjectModelBase &projectModel, const Vector<unsigned char> &buffer) = 0;
	virtual void disableUIEvent() = 0;
	virtual void enableUIEvent() = 0;
private:
	ProjectModelBase *model;
};

#elif ( defined(__ANDROID__ )  )
#else // IOS
#endif


};

#endif