///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include "GameDescriptor.h"
using namespace Magnum;

GameDescriptor *GameDescriptor::_instance = 0;

GameDescriptor::GameDescriptor()
{
	_instance					= this;

	hLib						= 0;

	setRawAssetRootDirectory	= 0;
	setAssetRootDirectory		= 0;
	setDocumentDirectory		= 0;
	setExternalDirectory		= 0;
	setInitialScene				= 0;
	setGetCurrentTimeMSFunc		= 0;
	setPrintFunc				= 0;
	onInitialize				= 0;
	onProcess					= 0;
	onPause						= 0;
	onResume					= 0;
	onTerminate					= 0;
	onMouseDown					= 0;
	onMouseUp					= 0;
	onMouseMoved				= 0;
	onMouseWheel				= 0;
	onGamePadKeyDown			= 0;
	onGamePadKeyUp				= 0;
	onAccelerationUpdate		= 0;
	onGUIEvent				= 0;

	addEditorProjectView		= 0;
}

GameDescriptor::~GameDescriptor()
{
	_instance					= 0;
}

GameDescriptor &GameDescriptor::instance()
{
	return *_instance;
}

bool GameDescriptor::create(const char *dllFilename)
{
	hLib = (HINSTANCE)LoadLibrary(dllFilename);
	if(hLib==NULL) 
		return false;

	setRawAssetRootDirectory	= (void (*)(const char *))									GetProcAddress((HMODULE)hLib, "gameDescSetRawAssetRootDirectory");
	setAssetRootDirectory		= (void (*)(const char *))									GetProcAddress((HMODULE)hLib, "gameDescSetAssetRootDirectory");
	setDocumentDirectory		= (void (*)(const char *))									GetProcAddress((HMODULE)hLib, "gameDescSetDocumentDirectory");
	setExternalDirectory		= (void (*)(const char *))									GetProcAddress((HMODULE)hLib, "gameDescSetExternalDirectory");
	setInitialScene				= (void (*)(const char *))									GetProcAddress((HMODULE)hLib, "gameDescSetInitialScene");
	setGetCurrentTimeMSFunc		= (void (*)(long long (*)()))								GetProcAddress((HMODULE)hLib, "gameDescSetGetCurrentTimeMSFunc");
	setPrintFunc				= (void (*)(void (*)(const char *buf_),
											void (*)(int i, const char *buf_),
											void (*)(const char *buf_)))					GetProcAddress((HMODULE)hLib, "gameDescSetPrintFunc");

	onInitialize				= (bool (*)(int, int))										GetProcAddress((HMODULE)hLib, "gameDescOnInitialize");
	onProcess					= (void (*)())												GetProcAddress((HMODULE)hLib, "gameDescOnProcess");
	onPause						= (void (*)())												GetProcAddress((HMODULE)hLib, "gameDescOnPause");
	onResume					= (void (*)())												GetProcAddress((HMODULE)hLib, "gameDescOnResume");
	onTerminate					= (void (*)())												GetProcAddress((HMODULE)hLib, "gameDescOnTerminate");
	onMouseDown					= (void (*)(int, int, float, float))						GetProcAddress((HMODULE)hLib, "gameDescOnMouseDown");
	onMouseUp					= (void (*)(int, int, float, float))						GetProcAddress((HMODULE)hLib, "gameDescOnMouseUp");
	onMouseMoved				= (void (*)(int, int, float, float))						GetProcAddress((HMODULE)hLib, "gameDescOnMouseMoved");
	onMouseWheel				= (void (*)(int, float, float, int, int))					GetProcAddress((HMODULE)hLib, "gameDescOnMouseWheel");
	onGamePadKeyDown			= (void (*)(int))											GetProcAddress((HMODULE)hLib, "gameDescOnGamePadKeyDown");
	onGamePadKeyUp				= (void (*)(int))											GetProcAddress((HMODULE)hLib, "gameDescOnGamePadKeyUp");
	onAccelerationUpdate		= (void (*)(float, float, float))							GetProcAddress((HMODULE)hLib, "gameDescOnAccelerationUpdate");
	onGUIEvent					= (void (*)(const unsigned char *, int))					GetProcAddress((HMODULE)hLib, "gameDescOnGUIEvent");
	addEditorProjectView		= (void (*)(void *))										GetProcAddress((HMODULE)hLib, "gameDescAddEditorProjectView");

	if(!isValid())
	{
		FreeLibrary((HMODULE)hLib);
		return false;
	}

	return true;
}

void GameDescriptor::destroy()
{
	if(hLib) 
	{
		FreeLibrary((HMODULE)hLib);
		hLib = 0;
	}
}

bool GameDescriptor::isValid() const
{
	return 	setAssetRootDirectory &&
			setDocumentDirectory &&
			setExternalDirectory &&
			setInitialScene &&
			setGetCurrentTimeMSFunc &&
			setPrintFunc &&

			onInitialize &&
			onProcess &&
			onPause &&
			onResume &&
			onTerminate &&

			onMouseDown &&
			onMouseUp &&
			onMouseMoved &&
			onMouseWheel &&

			onGamePadKeyDown &&
			onGamePadKeyUp &&
			onAccelerationUpdate &&
			onGUIEvent &&

			addEditorProjectView
			;
}