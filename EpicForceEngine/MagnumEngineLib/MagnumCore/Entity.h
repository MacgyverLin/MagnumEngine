///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Entity_h_
#define _Entity_h_

// #define WRITE_ENTITY_FIELD_ONLY

#include "FileIO.h"
#include "Array.h"
#include "Delegate.h"
#include "Component.h"
#include "Frame3.h"
#include "reflection.h"
using namespace agm::reflection;

namespace Magnum
{

#define DECLARE_ENTITY_CORE(T) \
static T *findByName(const char *name_) \
{ \
	return (T *)Entity::findByName(#T, name_); \
} \
static T *findByTag(const char *tag_) \
{ \
	return (T *)Entity::findByTag(#T, tag_); \
} \
static T *findByUniqueID(unsigned int uniqueID_) \
{ \
	return (T *)Entity::findByUniqueID(uniqueID_); \
} \
static T *create(const char *name_) \
{ \
	return (T *)Entity::create(#T, name_); \
} \
CLASS(T, Entity);

#define DECLARE_ENTITY(T) DECLARE_ENTITY_CORE(T) \
virtual bool isEditorModeActive() const \
{ \
	return false; \
}

#define DECLARE_EDITOR_ENTITY(T) DECLARE_ENTITY_CORE(T) \
virtual bool isEditorModeActive() const \
{ \
	return true; \
}

/**
* Entity is the container for all component and provide message servce, game object life cycle 
* It is the most important class in the engine and all the game entity and game entity interaction
* is constructed thru this class.
*/
class Entity : public Component::Owner
{
friend class EntityFieldReader;
friend class EntityFieldWriter;
friend class EntityPropertyReader;
friend class EntityPropertyWriter;
friend class Factory;
friend class ICreator;
friend class CallBack;
friend class ProjectModel;
friend class PlayModeScene;
public:
	enum
	{
		MAX_CREATOR		= 512,
		MAX_CLASSPATH	= 1024
	};

	class ICreator;
/////////////////////////////////////////////////////////////
private:
	Entity(const Entity &entity); // no copy
	Entity &operator = (const Entity &entity); // no assign
public:
	/**
	* Entity Constructor
	* To Construct the Entity
	*/
	Entity();

	/**
	* Entity Destructor
	* To Destructor the Entity
	*/
	virtual ~Entity();

	/////////////////////////////////////////////////////////////
	CLASS(Entity, Component::Owner);

	/////////////////////////////////////////////////////////////
public:
	/**
	* Get the Class Name of the Entity
	* @return const char *, Get the Path of the Class Name
	*/
	const char *getClassPath() const;

	/**
	* read method for Serialization
	* @param is, the InputStream for Serialization
	*/
	void read(InputStream &is);

	/**
	* write method for Serialization
	* @param os, the OutputStream for Serialization
	*/
	void write(OutputStream &os) const;
protected:
private:
public:
	/**
	* Create the Entity by specifying a class path and provide a name as identifier
	* @param classPath_, const char *, the class path
	* @param name_, const char *, the name
	*/
	static Entity *create(const char *classPath_, const char *name_);

	/**
	* Release the Entity and 
	* @param entity_, Entity *, release the entity and put it inactive list, if Entity refer count is zero and it is in inactive list, the Entity will be destructed.
	*/
	static void release(Entity *entity_);

	/**
	* Find the Entity by specifying a class path and provide a name as identifier
	* @param classPath_, const char *, the class path
	* @param name_, const char *, the name
	*/
	static Entity *findByName(const char *classPath_, const char *name_);

	/**
	* Find all Entities with specifying a its name
	* @param name_, const char *, the name
	*/
	static Entity *findByName(const char *name_);

	/**
	* Find the Entity by specifying a class path and its tag
	* @param classPath_, const char *, the class path
	* @param name_, const char *, the name
	*/
	static Entity *findByTag(const char *classPath_, const char *tag_);

	/**
	* Find the Entity by specifying its tag
	* @param name_, const char *, the name
	*/
	static Entity *findByTag(const char *tag_);

	/**
	* Find the Entity by specifying its unique ID
	* @param uniqueID_, unsigned int, the unique ID
	*/
	static Entity *findByUniqueID(unsigned int uniqueID_);

	/**
	* Get the currently selected Entity
	* @return Entity *, the currently selected Entity
	*/
	static Entity *getSelected();
private:
	static Entity *createCore(const char *classPath_, const char *name_);
	static void releaseCore(Entity *entity_);

	Entity::ICreator *creator;
///////////////////////////////////////////////////////////////////////////////////////////////
public:
	/**
	* ICreator.
	* ICreator is the entity creator interface. Provide basic function e.g. finding Entity and also manage the life cycle of
	* the entities of its class
	*/
	class ICreator
	{
	friend class Factory;
	friend class Entity;
	public:
		/**
		* ICreator Constructor
		* To Construct the ICreator of certain Class
		* @param classPath_, the class path of the creator
		*/
		ICreator(const char *classPath_);

		/**
		* Find all Entities with specifying a its name
		* @param name_, const char *, the name
		*/
		virtual Entity *findByName(const char *name_) const
		{
			for(int i=0; i<activeEntities.length(); i++)
			{
				if( strcasecmp(activeEntities[i]->getName(), name_)==0  )
					return activeEntities[i];
			}

			return 0;
		}

		/**
		* Find the Entity by specifying its tag
		* @param name_, const char *, the name
		*/
		virtual Entity *findByTag(const char *tag_) const
		{
			for(int i=0; i<activeEntities.length(); i++)
			{
				if( strcasecmp(activeEntities[i]->getTag(), tag_)==0  )
					return activeEntities[i];
			}

			return 0;
		}

		/**
		* Find the Entity by specifying its unique ID
		* @param uniqueID_, unsigned int, the unique ID
		*/
		virtual Entity *findByUniqueID(unsigned int uniqueID_) const
		{
			for(int i=0; i<activeEntities.length(); i++)
			{
				if( activeEntities[i]->getUniqueID() == uniqueID_)
					return activeEntities[i];
			}

			return 0;
		}

		virtual Entity *create(const char *name_)	= 0;
		virtual void release(Entity *entity_)		= 0;

		/**
		* Get the Class Path of this creator
		* @return , const char *, the ClassPath
		*/
		const char *getClassPath() const;
		
		/**
		* Get the Number of Entities of this Entity Creator
		* @return , int, the Number of Entities of this Entity Creator
		*/
		int getNumEntities() const;

		/**
		* Get the const Entity* indexed at i
		* @return , const Entity *, the Entity* indexed at i
		*/
		const Entity *getEntity(int i) const;

		/**
		* Get the Entity* indexed at i
		* @return, Entity *, the Entity* indexed at i
		*/
		Entity *getEntity(int i);
	private:
		/**
		* delete the active entities and clear the active list (this function is used by EntityFactory clear)
		* @see Entity::Factory
		*/
		void deleteActiveEntities();

		/**
		* delete the inactive entities and clear the inactive list
		*/
		void deleteInActiveEntities();

		/**
		* PreUpdate the Creator, it do preUpdate for itself and preUpdate the all entities for its class
		* @param dt, float, the time elapse of last game cycle
		*/
		virtual void preUpdate(float dt);

		/**
		* Update the Creator, it do update for itself and Update the all entities for its class
		* @param dt, float, the time elapse of last game cycle
		*/
		virtual void update(float dt);

		/**
		* PostUpdate the Creator, it do postUpdate for itself and postUpdate the all entities for its class
		* @param dt, float, the time elapse of last game cycle
		*/
		virtual void postUpdate(float dt);

		/**
		* Recycle the Creator, it do recycle the all inactive entities for its class
		* @param dt, float, the time elapse of last game cycle
		*/
		virtual void recycle(float dt);

		/**
		* Pause the Creator, it do pause for itself and pause the all entities for its class
		*/
		virtual void pause();

		/**
		* Resume the Creator, it do resume for itself and resume the all entities for its class
		*/
		virtual void resume();

		/**
		* Clear the Creator, it do update for itself and clear the all entities for its class
		*/
		virtual void clear();
	protected:
		Vector<Entity *> activeEntities;
		Vector<Entity *> inActiveEntities;

		char classPath[MAX_CLASSPATH+1];
	};

	/**
	* Creator template
	* Creator template is the entity creator. Provide basic function e.g. finding Entity and also manage the life cycle of
	* the entities of its class
	*/
	template<typename T> class Creator : public ICreator
	{
	friend class Factory;
	friend class Entity;
	public:
		/**
		* Creator Constructor
		* To Construct the Creator of certain Class
		* @param classPath_, the class path of the creator
		*/
		Creator(const char *classPath_)
		: ICreator(classPath_)
		{
		}
	private:
		virtual Entity *create(const char *name_)
		{
			Entity *entity;
			//entity = find(name_);
			//if(entity)
				//return entity;
			
			assert(Entity::Factory::instance().nextUniqueID < Math::MAX_INT);

			entity = new T();
			assert(entity);
			entity->setName(name_);
			entity->setUniqueID(Entity::Factory::instance().nextUniqueID++);
			entity->creator = this;

			activeEntities.push() = entity;

			return entity;
		}

		virtual void release(Entity *entity_)
		{
			int activeIdx = activeEntities.search(entity_);

			if(activeIdx>=0)
			{
				inActiveEntities.push() = activeEntities[activeIdx];

				activeEntities.remove(activeIdx);
			}
		}
	};

	/**
	* Factory template
	* Factory template is the entity creator factory. Provide basic function e.g. finding Entity and also manage the life cycle of
	* the entities of its class
	*/
	class Factory
	{
	friend class Entity;
	friend class ICreator;
	public:
		Factory();
		~Factory();

		static Factory &instance();

		/**
		* Update the Factory, it do update for itself and update the all of the creators
		* @param dt, float, the time elapse of last game cycle
		*/
		void process(float dt);

		/**
		* Pause the Factory, it do pause for itself and pause the all of the creators
		*/
		void pause();

		/**
		* Resume the Factory, it do resume for itself and resume the all of the creators
		*/
		void resume();

		/**
		* Clear the Factory, it do clear for itself and clear the all of the creators
		*/
		void clear();

		/**
		* Get the Unique ID for creation of entity
		*/
		unsigned int getNextUniqueID();

		/**
		* Find the Entity by specifying a class path and provide a name as identifier
		* @param classPath_, const char *, the class path
		* @param name_, const char *, the name
		*/
		Entity *findByName(const char *entityClassPath, const char *name_);

		/**
		* Find all Entities with specifying a its name
		* @param name_, const char *, the name
		*/
		Entity *findByName(const char *name_);

		/**
		* Find the Entity by specifying a class path and its tag
		* @param classPath_, const char *, the class path
		* @param name_, const char *, the name
		*/
		Entity *findByTag(const char *entityClassPath, const char *name_);

		/**
		* Find the Entity by specifying its tag
		* @param name_, const char *, the name
		*/
		Entity *findByTag(const char *name_);

		/**
		* Find the Entity by specifying its unique ID
		* @param uniqueID_, unsigned int, the unique ID
		*/
		Entity *findByUniqueID(unsigned int uniqueID_);

		/**
		* Get the Number of Creators
		* @return, int, the Number of Creators
		*/
		int getNumCreators() const;

		/**
		* Get the Creators
		* @param i, int, the index to the creators
		* @return, const ICreator *, the Creators at index i
		*/
		const ICreator *getCreator(int i) const;

		/**
		* Get the Creators
		* @param i, int, the index to the creators
		* @return, ICreator *, the Creators at index i
		*/
		ICreator *getCreator(int i);
	private:
		ICreator *find(const char *classPath_);

		static Factory *_instance;

		unsigned int nextUniqueID;
		Array<ICreator *> creators;
	};
/*
public:
	struct Service
	{
		static bool initiate();
		static void process();
		static void pause();
		static void resume();
		static void terminate();
		static void clear();
	};
*/
};

}

#endif