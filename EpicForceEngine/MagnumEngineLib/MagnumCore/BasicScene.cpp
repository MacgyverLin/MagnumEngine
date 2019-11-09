///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "BasicScene.h"
#include "Entity.h"
using namespace Magnum;

BasicScene::BasicScene()
{
}

BasicScene::~BasicScene()
{
	Entity::Factory::instance().clear();
}

void BasicScene::update(float dt)
{
	Scene::counter++;

	onUpdate(dt);

	Entity::Factory::instance().process(dt);
}