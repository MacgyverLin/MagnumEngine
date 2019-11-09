///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Scene.h"
#include "Stage.h"
#include "Service.h"
using namespace Magnum;

int Scene::counter = 0;

static int scene_count=0;
static Scene::TransitionMode transition_mode=Scene::NONE;
static bool scene_loaded=false;

Scene::ICreator::ICreator(const char *name_, bool overlay_)
: hits(0)
, index(scene_count++)
, overlay(overlay_)
{
	assert(strlen(name_)<sizeof(name));
	memset(name,0,sizeof(name));
	strncpy(name,name_,sizeof(name)-1);
	assert(!Scene::Factory::instance().scenes.full());
	Scene::Factory::instance().scenes.insert()=this;
}

bool Scene::is(const char *name_)
{
	return strcasecmp(name(), name_)==0;
}

const char *Scene::name()
{
	return Scene::Factory::instance().current()->name;
}
	
const char *Scene::next()
{
	if(!Scene::Factory::instance().next() ) return 0;
	return Scene::Factory::instance().next()->name;
}

void Scene::transit(const char *name)
{
	Scene::Factory::instance().transit(name);
}

void Scene::pushTransit(const char *name)
{
	Scene::Factory::instance().pushTransit(name);
}

void Scene::popTransit()
{
	Scene::Factory::instance().popTransit();
}

bool Scene::transitioning()
{
	return !scene_loaded || transition_mode!=NONE;
}

bool Scene::running()
{
	return scene_loaded && transition_mode==NONE;
}

bool Scene::loaded()
{
	return scene_loaded;
}

void Scene::onConstruct()
{
}

void Scene::onEnter()
{
}

void Scene::onExit()
{
}

void Scene::onUpdate(float dt)
{
}

void Scene::onPause()
{
}

void Scene::onResume()
{
}

bool Scene::onTransition(TransitionMode mode)
{
	return false;
}

void Scene::construct()
{
	onConstruct();
}

void Scene::enter()
{
	onEnter();
}

void Scene::exit()
{
	onExit();
}

void Scene::update(float dt)
{
	onUpdate(dt);
}

void Scene::pause()
{
	onPause();
}

void Scene::resume()
{
	onResume();
}

bool Scene::transition(TransitionMode mode)
{
	return onTransition(mode);
}

Scene::~Scene()
{
}

Scene::Scene()
{
}

bool Scene::Factory::overlay			=	true;
Scene::Factory *SceneFactory_instance	=	0;

Scene::Factory::Factory()
: _next(0)
, _current(0)
, _scene(0)
, scenes(MAX_NUM_SCENES, 0)
{
	assert(SceneFactory_instance==0);

	SceneFactory_instance=this;
}

Scene::Factory::~Factory()
{
}

Scene::Factory &Scene::Factory::instance()
{
	return *SceneFactory_instance;
}

Scene::ICreator *Scene::Factory::find(const char *name)
{
	if(name)
	{
		for(int i=0;i<scenes.length();i++)
		{
			if( strcasecmp(scenes[i]->name,name)==0 )
				return scenes[i];
		}
	}

	return 0;
}

Scene::ICreator *Scene::Factory::transit(const char *name)
{
	_next = find(name);

	if(_next==0)
	{
		debug("Scene %s not available.",name);
		return 0;
	}

	sceneStacks.top() = _current;

	return _next;
}

Scene::ICreator *Scene::Factory::pushTransit(const char *name)
{
	_next = find(name);

	if(_next==0)
	{
		debug("Scene %s not available.",name);
		return 0;
	}

	sceneStacks.push() = _current;

	return _next;
}

Scene::ICreator *Scene::Factory::popTransit()
{
	if(sceneStacks.length()==1)
	{
		debug("Only 1 Scene in Stack, Cannot pop Scene");
		return 0;
	}

	_next = sceneStacks.pop();

	if(_next==0)
	{
		debug("Scene %s not available.",name);
		return 0;
	}

	return _next;
}

void Scene::Factory::process()
{ 	
	float dt = ((float)Stage::elapsed()) / 1000.0f;

	if(transition_mode==Scene::ENTERING)
	{
		if(_scene->transition(transition_mode))
			return;
		else
		{
			transition_mode=Scene::NONE;
			_scene->enter();
			return;
		}
	}

	if(!_next) 
	{
		if(_scene)
		{
			_scene->update(dt);
		}
		return;
	}

	if(_scene)
	{
		if(transition_mode==Scene::EXITING)
		{
			if(_scene->transition(transition_mode))
				return;
		}

		if(transition_mode==NONE)
		{
			transition_mode=Scene::EXITING;
			_scene->exit();
			if(_scene->transition(transition_mode))
				return;
		}
	
		ICreator *_prior=_current;
		debug("Scene: %s destructing...",_prior->name);
		unsigned long time=Stage::realTime();
		scene_loaded=false;
		
		delete _scene;
		ServiceManager::instance().clear();
		debug("Scene: %s destructed in %d ms",_prior->name, Stage::realTime()-time);

		//Stage::dumpMemoryLeak();
	}
	
	_current	=	_next;
	_next		=	0;

	unsigned long time=Stage::realTime();

	debug("Scene: %s constructing...\n",_current->name);
	// printSystem();
	_scene=_current->create();
	_scene->construct();

	scene_loaded=true;

	time=Stage::realTime()-time;
	debug("Scene: %s loaded in %d.%2.2d seconds",_current->name,time/1000,(time%1000)/10);
	// MemoryReport();

	transition_mode=Scene::ENTERING;
}

void Scene::Factory::pause()
{
	if(_scene)
	{
		_scene->pause();
	}
}

void Scene::Factory::resume()
{
	if(_scene)
	{
		_scene->resume();
	}
}

void Scene::Factory::terminate()
{
	if(_scene)
	{
		delete _scene;
		_scene = 0;
	}
}

///////////////////////////////////////////////////////////////////////////////////
bool Scene::Service::initiate()
{
	return true;
}

void Scene::Service::process()
{ 
	Scene::Factory::instance().process();
}

void Scene::Service::pause()
{
	Scene::Factory::instance().pause();
}

void Scene::Service::resume()
{
	Scene::Factory::instance().resume();
}

void Scene::Service::terminate()
{
	Scene::Factory::instance().terminate();
}

void Scene::Service::clear()
{
}