///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Stage.h"
#include "Component.h"
using namespace Magnum;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Component::Owner *Component::Owner::selected = 0;

Component::Owner::Owner()
: Frame3()
, _uniqueID(0)
, _Name("GameObject")
, _Active(true)
, _Tag(" ")
, _Layer(0x01)
, _Static(false)
{
}

Component::Owner::~Owner()
{
	unselect();
}

/*
void Component::Owner::setName(const char *name_)
{
	_name = name_;

	onNameChanged(this);
}

const char *Component::Owner::getName() const
{
	return _name;
}
*/
unsigned int Component::Owner::getUniqueID() const
{
	return _uniqueID;
}
/*
void Component::Owner::setTag(const char *tag_)
{
	_tag = tag_;
}

const char *Component::Owner::getTag() const
{
	return _tag;
}

void Component::Owner::setLayer(unsigned int layer_)
{
	_layer = layer_;
}

unsigned int Component::Owner::getLayer() const
{
	return _layer;
}

void Component::Owner::activate()
{
	_active = true;
}

void Component::Owner::deactivate()
{
	_active = false;
}

bool Component::Owner::isActive() const
{
	return _active;
}
*/

int Component::Owner::getNumComponents() const
{
	return _components.length();
}

Component *Component::Owner::getComponent(int i)
{
	return _components[i];
}

const Component *Component::Owner::getComponent(int i) const
{
	return _components[i];
}

Component *Component::Owner::getComponent(const char *name_)
{
	int idx = getComponentIdx(name_);
	if(idx)
		return _components[idx];
	else
		return 0;
}

const Component *Component::Owner::getComponent(const char *name_) const
{
	int idx = getComponentIdx(name_);
	if(idx)
		return _components[idx];
	else
		return 0;
}

bool Component::Owner::isEditorModeActive() const
{
	return false;
}

void Component::Owner::select()
{
	selected = this;
}

void Component::Owner::unselect()
{
	if(selected==this)
	{
		selected = 0;
	}
}

bool Component::Owner::isSelected() const
{
	return selected==this;
}

Component::Owner *Component::Owner::getSelected()
{
	return selected;
}

bool Component::Owner::construct()
{
	for(int i=0; i<_components.length(); i++)
	{
		if( !_components[i]->construct() )
			return false;
	}
	
	return onConstruct();
}

void Component::Owner::start()
{
	for(int i=0; i<_components.length(); i++)
	{
		_components[i]->start();
	}

	if(!Stage::isEditorMode() || isEditorModeActive())
	{
		onStart();
	}
}

void Component::Owner::preUpdate(float dt)
{
	for(int i=0; i<_components.length(); i++)
	{
		_components[i]->preUpdate(dt);
	}

	if(!Stage::isEditorMode() || isEditorModeActive())
	{
		onPreUpdate(dt);
	}
}

void Component::Owner::update(float dt)
{
	for(int i=0; i<_components.length(); i++)
	{
		_components[i]->update(dt);
	}

	if(!Stage::isEditorMode() || isEditorModeActive())
	{
		onUpdate(dt);
	}
}

void Component::Owner::postUpdate(float dt)
{
	for(int i=0; i<_components.length(); i++)
	{
		_components[i]->postUpdate(dt);
	}

	if(!Stage::isEditorMode() || isEditorModeActive())
	{
		onPostUpdate(dt);
	}
}

void Component::Owner::pause()
{
	for(int i=0; i<_components.length(); i++)
	{
		_components[i]->pause();
	}

	if(!Stage::isEditorMode() || isEditorModeActive())
	{
		onPause();
	}
}

void Component::Owner::resume()
{
	for(int i=0; i<_components.length(); i++)
	{
		_components[i]->resume();
	}

	if(!Stage::isEditorMode() || isEditorModeActive())
	{
		onResume();
	}
}

void Component::Owner::stop()
{
	if(!Stage::isEditorMode() || isEditorModeActive())
	{
		onStop();
	}

	for(int i=0; i<_components.length(); i++)
	{
		_components[i]->stop();
	}
}

void Component::Owner::destruct()
{
	onDestruct();

	for(int i=0; i<_components.length(); i++)
	{
		_components[i]->destruct();
	}
}

void Component::Owner::debugRender(IComponentDebugRenderer &debugRenderer)
{
	onDebugRender(debugRenderer);

	for(int i=0; i<getNumComponents(); i++)
	{
		Component *component = getComponent(i);
		if(component->getEnabled())
		{
			component->debugRender(debugRenderer);
		}
	}
}

void Component::Owner::read(InputStream &is)
{
	Frame3::read(is);

	is >> _Name;

	is >> _Tag;
	is >> _Layer;

	is >> _Active;
}

void Component::Owner::write(OutputStream &os) const
{
	Frame3::write(os);

	os << _Name;

	os << _Tag;
	os << _Layer;

	os << _Active;
}

void Component::Owner::setUniqueID(unsigned int uniqueID_)
{
	_uniqueID = uniqueID_;
}

int Component::Owner::getComponentIdx(const char *name_) const
{
	for(int i=0; i<_components.length(); i++)
	{
		if(_components[i]->Name.get()==name_)
			return i;
	}

	return -1;
}

//////////////////////////////////////////////////////////////////////////////////////
Component::Component(Component::Owner &owner_)
: _owner(owner_)
{
	setEnabled(true);
	setName("Component");

	_owner._components.push() = this;
}

Component::~Component()
{
	int idx = _owner._components.search(this);
	if(idx>=0)
	{
		_owner._components.remove(idx);
	}
}

Component::Owner &Component::getOwner()
{
	return _owner;
}

const Component::Owner &Component::getOwner() const
{
	return _owner;
}

bool Component::construct()
{
	return onConstruct();
}

void Component::start()
{
	if(!Stage::isEditorMode() || isEditorModeActive())
		onStart();
}

void Component::preUpdate(float dt)
{
	if(!Stage::isEditorMode() || isEditorModeActive())
		onPreUpdate(dt);
}

void Component::update(float dt)
{
	if(!Stage::isEditorMode() || isEditorModeActive())
		onUpdate(dt);
}

void Component::postUpdate(float dt)
{
	if(!Stage::isEditorMode() || isEditorModeActive())
		onPostUpdate(dt);
}

void Component::pause()
{
	if(!Stage::isEditorMode() || isEditorModeActive())
		onPause();
}

void Component::resume()
{
	if(!Stage::isEditorMode() || isEditorModeActive())
		onResume();
}

void Component::stop()
{
	if(!Stage::isEditorMode() || isEditorModeActive())
		onStop();
}

void Component::destruct()
{
	onDestruct();
}

void Component::debugRender(IComponentDebugRenderer &debugRenderer)
{
	onDebugRender(debugRenderer);
}