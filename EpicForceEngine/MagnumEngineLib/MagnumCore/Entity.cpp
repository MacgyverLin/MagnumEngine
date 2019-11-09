///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Stage.h"
#include "Entity.h"
#include "EMath.h"
#include "ESystem.h"
using namespace Magnum;

//////////////////////////////////////////////////////////////////////////////////////
Entity::Entity()
: Component::Owner()
, creator(0)
{
}

Entity::~Entity()
{
	Entity *parent = (Entity *)getParent();
	if(parent)
		parent->removeChild(this);

	removeAllChildren();

	unselect();

	creator = 0;
}

const char *Entity::getClassPath() const
{
	return creator->getClassPath();
}

void Entity::read(InputStream &is)
{
	Component::Owner::read(is);
}

void Entity::write(OutputStream &os) const
{
	Component::Owner::write(os);
}

Entity *Entity::findByName(const char *classPath_, const char *name_)
{
	return Entity::Factory::instance().findByName(classPath_, name_);
}

Entity *Entity::findByName(const char *name_)
{
	return Entity::Factory::instance().findByName(name_);
}

Entity *Entity::findByTag(const char *classPath_, const char *tag_)
{
	return Entity::Factory::instance().findByTag(classPath_, tag_);
}

Entity *Entity::findByTag(const char *tag_)
{
	return Entity::Factory::instance().findByTag(tag_);
}

Entity *Entity::findByUniqueID(unsigned int uniqueID_)
{
	return Entity::Factory::instance().findByUniqueID(uniqueID_);
}

Entity *Entity::create(const char *classPath_, const char *name_)
{
	Entity *entity = createCore(classPath_, name_);
	if(entity)
	{
		bool ok = entity->construct();
		assert(ok);

		entity->start();
	}

	return entity;
}

void Entity::release(Entity *entity_)
{
	if(entity_)
	{
		entity_->unselect();

		entity_->stop();

		entity_->destruct();

		releaseCore(entity_);
	}
}

Entity *Entity::createCore(const char *classPath_, const char *name_)
{
	Entity::ICreator *creator = Entity::Factory::instance().find(classPath_);
	if(creator)
		return creator->create(name_);
	else
		return 0;
}

void Entity::releaseCore(Entity *entity_)
{
	if(entity_ && entity_->creator)
	{
		entity_->creator->release(entity_);
	}
}

Entity *Entity::getSelected()
{
	return (Entity *)Component::Owner::getSelected();
}

//////////////////////////////////////////////////////////////////////////////////////
Entity::ICreator::ICreator(const char *classPath_)
{
	assert(classPath_!=0 && classPath_[0]!=0 && strlen(classPath_)<sizeof(classPath));
	assert(!Entity::Factory::instance().creators.full());

	strcpy(classPath, classPath_);
	
	Entity::Factory::instance().creators.insert() = this;
}

const char *Entity::ICreator::getClassPath() const
{
	return classPath;
}

int Entity::ICreator::getNumEntities() const
{
	return activeEntities.length();
}

const Entity *Entity::ICreator::getEntity(int i) const
{
	return activeEntities[i];
}

Entity *Entity::ICreator::getEntity(int i)
{
	return activeEntities[i];
}

void Entity::ICreator::deleteActiveEntities()
{
	for(int i=0; i<activeEntities.length(); i++)
	{
		if(activeEntities[i])
		{
			//activeEntities[i]->stop();
			//activeEntities[i]->destruct();

			delete activeEntities[i];
			activeEntities[i] = 0;
		}
	}
}

void Entity::ICreator::deleteInActiveEntities()
{
	for(int i=0; i<inActiveEntities.length(); i++)
	{
		if(inActiveEntities[i])
		{
			//inActiveEntities[i]->stop();
			//inActiveEntities[i]->destruct();

			delete inActiveEntities[i];
			inActiveEntities[i] = 0;
		}
	}
}

void Entity::ICreator::preUpdate(float dt)
{
	for(int i=0; i<activeEntities.length(); i++)
	{
		if(activeEntities[i])
		{
			// activeEntities[i]->start();
			activeEntities[i]->preUpdate(dt);
		}
	}
}

void Entity::ICreator::update(float dt)
{
	for(int i=0; i<activeEntities.length(); i++)
	{
		if(activeEntities[i])
		{
			// activeEntities[i]->start();
			activeEntities[i]->update(dt);
		}
	}
}

void Entity::ICreator::postUpdate(float dt)
{
	for(int i=0; i<activeEntities.length(); i++)
	{
		if(activeEntities[i])
		{
			// activeEntities[i]->start();
			activeEntities[i]->postUpdate(dt);
		}
	}
}

void Entity::ICreator::recycle(float dt)
{
	deleteInActiveEntities();
	inActiveEntities.clear();
}

void Entity::ICreator::pause()
{
	for(int i=0; i<activeEntities.length(); i++)
	{
		if(activeEntities[i])
			activeEntities[i]->pause();
	}

	for(int i=0; i<inActiveEntities.length(); i++)
	{
		if(inActiveEntities[i])
			inActiveEntities[i]->pause();
	}
}

void Entity::ICreator::resume()
{
	for(int i=0; i<activeEntities.length(); i++)
	{
		if(activeEntities[i])
			activeEntities[i]->resume();
	}

	for(int i=0; i<inActiveEntities.length(); i++)
	{
		if(inActiveEntities[i])
			inActiveEntities[i]->resume();
	}
}

void Entity::ICreator::clear()
{
	deleteActiveEntities();
	activeEntities.destroy();

	deleteInActiveEntities();
	inActiveEntities.destroy();
}

//////////////////////////////////////////////////////////////////////////////////////
Entity::Factory *Entity::Factory::_instance=0;

Entity::Factory::Factory()
: creators(Entity::MAX_CREATOR, 0)
, nextUniqueID(1)
{
	assert(!_instance);

	_instance=this;
}

Entity::Factory::~Factory()
{
	assert(_instance);

	_instance = 0;
}

Entity::Factory &Entity::Factory::instance()
{
	return *_instance;
}

void Entity::Factory::process(float dt)
{
	for(int i=0; i<creators.length(); i++)
	{
		creators[i]->preUpdate(dt);
	}

	for(int i=0; i<creators.length(); i++)
	{
		creators[i]->update(dt);
	}

	for(int i=0; i<creators.length(); i++)
	{
		creators[i]->postUpdate(dt);
	}

	for(int i=0; i<creators.length(); i++)
	{
		creators[i]->recycle(dt);
	}
}

void Entity::Factory::pause()
{
	for(int i=0; i<creators.length(); i++)
	{
		creators[i]->pause();
	}
}

void Entity::Factory::resume()
{
	for(int i=0; i<creators.length(); i++)
	{
		creators[i]->resume();
	}
}

void Entity::Factory::clear()
{
	nextUniqueID = 1;

	for(int i=0; i<creators.length(); i++)
	{
		creators[i]->clear();
	}
}

unsigned int Entity::Factory::getNextUniqueID()
{
	return nextUniqueID;
}

Entity *Entity::Factory::findByName(const char *classPath_, const char *name_)
{
	const Entity::ICreator *creator = Entity::Factory::instance().find(classPath_);
	if(creator)
		return creator->findByName(name_);
	else
		return 0;
}

Entity *Entity::Factory::findByName(const char *name_)
{
	for(int i=0; i<Entity::Factory::instance().getNumCreators(); i++)
	{
		const Entity::ICreator *creator = Entity::Factory::instance().getCreator(i);
		
		Entity *entity = creator->findByName(name_);
		if(entity)
			return entity;
	}

	return 0;
}

Entity *Entity::Factory::findByTag(const char *classPath_, const char *tag_)
{
	const Entity::ICreator *creator = Entity::Factory::instance().find(classPath_);
	if(creator)
		return creator->findByTag(tag_);
	else
		return 0;
}

Entity *Entity::Factory::findByTag(const char *tag_)
{
	for(int i=0; i<Entity::Factory::instance().getNumCreators(); i++)
	{
		const Entity::ICreator *creator = Entity::Factory::instance().getCreator(i);
		
		Entity *entity = creator->findByTag(tag_);
		if(entity)
			return entity;
	}

	return 0;
}

Entity *Entity::Factory::findByUniqueID(unsigned int uniqueID_)
{
	for(int i=0; i<Entity::Factory::instance().getNumCreators(); i++)
	{
		const Entity::ICreator *creator = Entity::Factory::instance().getCreator(i);
		
		Entity *entity = creator->findByUniqueID(uniqueID_);
		if(entity)
			return entity;
	}

	return 0;
}

int Entity::Factory::getNumCreators() const
{
	return creators.length();
}

const Entity::ICreator *Entity::Factory::getCreator(int i) const
{
	return creators[i];
}

Entity::ICreator *Entity::Factory::getCreator(int i)
{
	return creators[i];
}

Entity::ICreator *Entity::Factory::find(const char *classPath_)
{
	for(int i=0; i<creators.length(); i++)
	{
		if( strcasecmp(creators[i]->classPath, classPath_)==0 )
		{
			return creators[i];
		}
	}

	return 0;
}