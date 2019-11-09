#include "CycleTest_Scene.h"
static Scene::Creator<CycleTest_Scene> scene_CycleTest("CycleTest", false);

#include "HelloWorld2_Scene.h"
static Scene::Creator<HelloWorld2_Scene> scene_HelloWorld2("HelloWorld2", false);

#include "HelloWorld_Scene.h"
static Scene::Creator<HelloWorld_Scene> scene_HelloWorld("HelloWorld", false);

#include "InputTest_Scene.h"
static Scene::Creator<InputTest_Scene> scene_InputTest("InputTest", false);

#include "TinyXMLTest_Scene.h"
static Scene::Creator<TinyXMLTest_Scene> scene_TinyXMLTest("TinyXMLTest", false);

