///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include <MagnumEngine.h>
using namespace Magnum;
#include "gldef.h"
#ifdef USE_GLES20
#pragma comment(lib, "libEGL.lib")
#pragma comment(lib, "libGLESv2.lib")
#else
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "Opengl32.lib")
#endif

///////////////////////////////////////////////////////////////////////////////////
// Globals
ServiceManager				serviceManager;
Scene::Factory				sceneFactory;
#ifdef ENABLE_RESOURCE_IMPORT
ResourceImport::Factory		resourceImportFactory;
#endif
ResourceAccess::Factory		resourceAccessFactory;
Entity::Factory				entityFactory;
Physics3::Manager			physics3Manager;
Collision::Manager			collisionManager;
Selection3::Manager			selection3Manager;
Video::Manager				videoManager;
Audio::Manager				audioManager;

#ifdef ENABLE_RESOURCE_IMPORT
///////////////////////////////////////////////////////////////////////////////////
// Resources Importer
//ResourceImport::Creator<Font::ResourceImporter>						fontResourceImporterCreator;
//ResourceImport::Creator<SkyMapResourceImporter>					skyMapResourceImporterCreator;
//ResourceImport::Creator<SpriteAnimation::ResourceImporter>		spriteAnimationResourceImporterCreator;
ResourceImport::Creator<MagnumScene::ResourceImporter>				MagnumSceneResourceImporterCreator;
ResourceImport::Creator<MagnumPrefab::ResourceImporter>				MagnumPrefabResourceImporterCreator;
ResourceImport::Creator<Texture2DFile::ResourceImporter>			texture2DFileResourceImporterCreator;
ResourceImport::Creator<TextureCubeFile::ResourceImporter>			textureCubeFileResourceImporterCreator;
ResourceImport::Creator<VisualEffect::ResourceImporter>				visualEffectResourceImporterCreator;
ResourceImport::Creator<SkeletalAnimModel::ResourceImporter>		skeletalAnimModelResourceImporterCreator;
ResourceImport::Creator<AudioClip::ResourceImporter>				audioClipResourceImporterCreator;
ResourceImport::Creator<AudioStream::ResourceImporter>				audioStreamResourceImporterCreator;
ResourceImport::Creator<BVHTriangleMeshShape3::ResourceImporter>	bvhTriangleMeshShape3ImporterCreator;
ResourceImport::Creator<SpriteSheet::ResourceImporter>				spriteSheetImporterCreator;
ResourceImport::Creator<Font::ResourceImporter>						fontImporterCreator;
ResourceImport::Creator<SceneCollision::ResourceImporter>			sceneCollisionImporterCreator;
ResourceImport::Creator<BVHTriangleMeshShape3::ResourceImporter>	bvhtrianglemeshshape3ImporterCreator;
ResourceImport::Creator<HeightFieldShape3::ResourceImporter>		heightfieldshape3ImporterCreator;
#endif

///////////////////////////////////////////////////////////////////////////////////
// Resources
//ResourceAccess::Creator<Font::Resource>								fontResourceCreator;
//Resource::Creator<SkyMapResource>									skyMapResourceCreator;
//Resource::Creator<SpriteAnimationResource>						spriteAnimationResourceCreator;
ResourceAccess::Creator<Texture2DFile::Resource>					texture2DFileResourceCreator;
ResourceAccess::Creator<TextureCubeFile::Resource>					textureCubeFileResourceCreator;
ResourceAccess::Creator<VisualEffect::Resource>						visualEffectResourceCreator;
ResourceAccess::Creator<SkeletalAnimModel::Resource>				skeletalAnimModelResourceCreator;
ResourceAccess::Creator<AudioClip::Resource>						audioClipResourceCreator;
ResourceAccess::Creator<BVHTriangleMeshShape3::Resource>			bvhTriangleMeshShape3Creator;
ResourceAccess::Creator<SpriteSheet::Resource>						spriteSheetCreator;
ResourceAccess::Creator<Font::Resource>								fontCreator;
ResourceAccess::Creator<SceneCollision::Resource>					sceneCollisionCreator;
ResourceAccess::Creator<BVHTriangleMeshShape3::Resource>			bvhtrianglemeshshape3Creator;
ResourceAccess::Creator<HeightFieldShape3::Resource>				heightfieldshape3Creator;

///////////////////////////////////////////////////////////////////////////////////
// Services
Service<Scene::Service>				sceneSrv("Scene");
#ifdef ENABLE_RESOURCE_IMPORT
Service<ResourceImport::Service>	resourceImportSrv("ResourceImport");
#endif
Service<ResourceAccess::Service>	resourceAccessSrv("ResourceAccess");
Service<Input::Service>				inputSrv("Input");
Service<Physics3::Service>			physics3Srv("Physics3");
Service<Collision::Service>			collisionSrv("Collision");
Service<Selection3::Service>		selection3Srv("Selection3");
Service<Video::Service>				videoSrv("Video");
Service<Audio::Service>				audioSrv("Audio");

///////////////////////////////////////////////////////////////////////////////////
// SceneCreators
#include "SceneCreators.h"

///////////////////////////////////////////////////////////////////////////////////
// EntityCreators
#include "EntityCreators.h"

///////////////////////////////////////////////////////////////////////////////////
// GameDescriptor
void setRawAssetRootDirectory(const char *rawAssetRootDirectory_)
{
	Stage::setRawAssetRootDirectory(rawAssetRootDirectory_);
}

void setAssetRootDirectory(const char *assetRootDirectory_)
{
	Stage::setAssetRootDirectory(assetRootDirectory_);
}

void setDocumentDirectory(const char *documentDirectory_)
{
	Stage::setDocumentDirectory(documentDirectory_);
}

void setExternalDirectory(const char *externalDirectory_)
{
	Stage::setExternalDirectory(externalDirectory_);
}

void setInitialScene(const char *initialScene_)
{
	Stage::setInitialScene(initialScene_);
}

void setGetCurrentTimeMSFunc(long long (*getCurrentTimeMSFunc_)())
{
	Stage::setGetCurrentTimeMSFunc(getCurrentTimeMSFunc_);
}

void setPrintFunc(void (*printInfoFunc_)(const char *buf_),
				  void (*printDebugFunc_)(int i, const char *buf_),
				  void (*printPanicFunc_)(const char *buf_))
{
	Stage::setPrintFunc(printInfoFunc_, printDebugFunc_, printPanicFunc_);
}

bool onInitialize(int width_, int height_)
{
	Stage::setStartTime();
	Stage::setScreenSize(width_, height_);
	
	if( !ServiceManager::instance().initiate() )
		return false;

	Stage::beginCheckMemoryLeak(-1);
	Stage::_initiated = true;

	if( !Scene::Factory::instance().find(Stage::getInitialScene()) )
		return false;

	if( !Scene::Factory::instance().pushTransit(Stage::getInitialScene()) )
		return false;

	return true;
}

void onProcess()
{
	Stage::slice();

	serviceManager.process();
}

void onPause()
{
	serviceManager.pause();
}

void onResume()
{
	serviceManager.resume();
}

void onTerminate()
{
	Stage::_aborting = true;

	Stage::endCheckMemoryLeak();

	serviceManager.terminate();

	Stage::_initiated = false;
}

void onMouseDown(int modifier, int fingerID, float x, float y)
{
	Input::onMouseEvent((Input::TouchpadEvent::Modifier)modifier, Input::EVENT_MOUSE_DOWN, fingerID, x, y);
}

void onMouseUp(int modifier, int fingerID, float x, float y)
{
	Input::onMouseEvent((Input::TouchpadEvent::Modifier)modifier, Input::EVENT_MOUSE_UP, fingerID, x, y);
}

void onMouseMoved(int modifier, int fingerID, float x, float y)
{
	Input::onMouseEvent((Input::TouchpadEvent::Modifier)modifier, Input::EVENT_MOUSE_MOVE, fingerID, x, y);
}

void onMouseWheel(int modifier, float x, float y, int axis, int rotation)
{
	Input::onMouseEvent((Input::TouchpadEvent::Modifier)modifier, Input::EVENT_MOUSE_WHEEL, x, y, axis, rotation);
}

void onGamePadKeyDown(int keyCode)
{
	Input::onKeyEvent(Input::EVENT_GAMEPAD_KEY_DOWN, keyCode);
}

void onGamePadKeyUp(int keyCode)
{
	Input::onKeyEvent(Input::EVENT_GAMEPAD_KEY_UP, keyCode);
}

void onAccelerationUpdate(float x, float y, float z)
{
	Input::onAcceleratorEvent(Input::EVENT_ACCELERATOR_UPDATE, x, y, z);
}

void onGUIEvent(const unsigned char *buffer, int len)
{
	Input::onGUIEvent(Input::EVENT_GUI, buffer, len);
}

void addEditorProjectView(void *view_)
{
	Stage::addEditorProjectView(view_);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DLL Entries Point
#if defined(WIN32)
#define DLL_EXPORT extern "C" __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

DLL_EXPORT void gameDescSetRawAssetRootDirectory(const char *rawAssetRootDirectory_)
{
	setRawAssetRootDirectory(rawAssetRootDirectory_);
}

DLL_EXPORT void gameDescSetAssetRootDirectory(const char *assetRootDirectory_)
{
	setAssetRootDirectory(assetRootDirectory_);
}

DLL_EXPORT void gameDescSetDocumentDirectory(const char *documentDirectory_)
{
	setDocumentDirectory(documentDirectory_);
}

DLL_EXPORT void gameDescSetExternalDirectory(const char *externalDirectory_)
{
	setExternalDirectory(externalDirectory_);
}

DLL_EXPORT void gameDescSetInitialScene(const char *initialScene_)
{
	setInitialScene(initialScene_);
}

DLL_EXPORT void gameDescSetGetCurrentTimeMSFunc(long long (*getCurrentTimeMSFunc_)())
{
	setGetCurrentTimeMSFunc(getCurrentTimeMSFunc_);
}

DLL_EXPORT void gameDescSetPrintFunc(void (*printInfoFunc_)(const char *buf_),
									 void (*printDebugFunc_)(int i, const char *buf_),
									 void (*printPanicFunc_)(const char *buf_))
{
	setPrintFunc(printInfoFunc_, printDebugFunc_, printPanicFunc_);
}

DLL_EXPORT bool gameDescOnInitialize(int width_, int height_)
{
	return onInitialize(width_, height_);
}

DLL_EXPORT void gameDescOnProcess()
{
	onProcess();
}

DLL_EXPORT void gameDescOnPause()
{
	onPause();
}

DLL_EXPORT void gameDescOnResume()
{
	onResume();
}

DLL_EXPORT void gameDescOnTerminate()
{
	onTerminate();
}

DLL_EXPORT void gameDescOnMouseDown(int modifier, int fingerID, float x, float y)
{
	onMouseDown(modifier, fingerID, x, y);
}

DLL_EXPORT void gameDescOnMouseUp(int modifier, int fingerID, float x, float y)
{
	onMouseUp(modifier, fingerID, x, y);
}

DLL_EXPORT void gameDescOnMouseMoved(int modifier, int fingerID, float x, float y)
{
	onMouseMoved(modifier, fingerID, x, y);
}

DLL_EXPORT void gameDescOnMouseWheel(int modifier, float x, float y, int axis, int rotation)
{
	onMouseWheel(modifier, x, y, axis, rotation);
}

DLL_EXPORT void gameDescOnGamePadKeyDown(int keyCode)
{
	onGamePadKeyDown(keyCode);
}

DLL_EXPORT void gameDescOnGamePadKeyUp(int keyCode)
{
	onGamePadKeyUp(keyCode);
}

DLL_EXPORT void gameDescOnAccelerationUpdate(float x, float y, float z)
{
	onAccelerationUpdate(x, y, z);
}

DLL_EXPORT void gameDescOnGUIEvent(const unsigned char *buffer, int len)
{
	onGUIEvent(buffer, len);
}

DLL_EXPORT void gameDescAddEditorProjectView(void *view_)
{
	addEditorProjectView(view_);
}