#include "EpicForceBaseScene.h"
static Scene::Creator<EpicForceBaseScene> sceneEpicForceBase("EpicForceBase", false);

#include "CycleTestScene.h"
static Scene::Creator<CycleTestScene> sceneCycleTest("CycleTest", false);

#include "EntityTestScene.h"
static Scene::Creator<EntityTestScene> sceneEntityTest("EntityTest", false);

#include "HelloWorld2Scene.h"
static Scene::Creator<HelloWorld2Scene> sceneHelloWorld2("HelloWorld2", false);

#include "HelloWorldScene.h"
static Scene::Creator<HelloWorldScene> sceneHelloWorld("HelloWorld", false);

#include "InputTestScene.h"
static Scene::Creator<InputTestScene> sceneInputTest("InputTest", false);

#include "RendererLayerTestScene.h"
static Scene::Creator<RendererLayerTestScene> sceneRendererLayerTest("RendererLayerTest", false);

#include "ResourceTestScene.h"
static Scene::Creator<ResourceTestScene> sceneResourceTest("ResourceTest", false);

