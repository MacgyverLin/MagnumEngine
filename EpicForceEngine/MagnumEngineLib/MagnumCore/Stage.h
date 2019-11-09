///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Stage_h_
#define _Stage_h_

//#define GZ_RESOURCE

#if defined(WIN32)

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <windows.h>
#include <mmsystem.h>
#define ENABLE_RESOURCE_IMPORT
#define ENABLE_EDITOR

#elif ( defined(__ANDROID__ )  )

#else // IOS

#include "TargetConditionals.h" 

#endif

//#include "new.h"
#include <limits.h>
#include <ctype.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <string.h>

namespace Magnum
{

#ifdef WIN32
#define strcasecmp _stricmp
#define strncasecmp _strnicmp
#endif

class Stage 
{
public:
	////////////////////////////////////
	// Generic
	static long long realTime();
	static long long time();
	static long long elapsed();
	static float frameRate();
	static bool initiated();
	static bool aborting();
	static void slice();	
	static void setStartTime();
	static void setScreenSize(int width_, int height_);
	static void getScreenSize(int &width_, int &height_);
	static int getScreenWidth();
	static int getScreenHeight();
	static void setRawAssetRootDirectory(const char *rawAssetRootDirectory_);
	static void setAssetRootDirectory(const char *assetRootDirectory_);
	static void setDocumentDirectory(const char *documentDirectory_);
	static void setExternalDirectory(const char *externalDirectory_);
	static void setInitialScene(const char *initialScene_);
	static void setGetCurrentTimeMSFunc(long long (*getCurrentTimeMSFunc_)());
	static void setPrintFunc(void (*printInfoFunc_)(const char *buf_),
							 void (*printDebugFunc_)(int i, const char *buf_),
							 void (*printPanicFunc_)(const char *buf_));
	static const char *getRawAssetRootDirectory();
	static const char *getAssetRootDirectory();
	static const char *getDocumentDirectory();
	static const char *getExternalDirectory();
	static const char *getInitialScene();
	static void beginCheckMemoryLeak(int breakAtAllocationID);
	static void dumpMemoryLeak();
	static void endCheckMemoryLeak();
	static void	addEditorProjectView(void *view);
	static void	*getEditorProjectView(int i);
	static int  getNumEditorProjectView();
	static void enableEditorMode();
	static void disableEditorMode();
	static bool isEditorMode();
private:
	static long long		_lastTime;
	static long long		_newTime;
	static long long		_timeAdjust;
	static long long		_lastPolledTime;
	static long long		_elapsed;
	static float			_frameRate;
	static long long		_click;
	static long long		_gameStartTime;
	static long long		_frameCountTimer; 
	static int				_frameCount;
	static unsigned long	_clicker;
	static int				_width;
	static int				_height;
	static char				_rawAssetRootDirectory[4096];
	static char				_assetRootDirectory[4096];
	static char				_documentDirectory[4096];
	static char				_externalDirectory[4096];
	static char				_initialScene[4096];
	static bool				_isEditorModeEnabled;
	static bool				_checkMemoryLeakEnabled;
	static bool				_editorMode;
	static void				*_editorProjectView[16];
	static int				_numEditorProjectView;
public:
	static long long		(*_getCurrentTimeMSFunc)();
	static void				(*_printInfoFunc)(const char *buf_);
	static void				(*_printDebugFunc)(int i, const char *buf_);
	static void				(*_printPanicFunc)(const char *buf_);

	static char				*_lastError;
	static bool				_initiated;
	static bool				_aborting;
	////////////////////////////////////
	// Platform Dependent
	static bool getPlatformExternalDeviceMounted();
public:
};

void info(const char *a_fmtstr, ...);
void debug(const char *a_fmtstr, ...);
void panic(const char *a_fmtstr, ...);

#ifdef assert
#undef assert
#endif

#ifdef FINAL
#define assert(exp)		((void)0)
#else
#define assert(exp)		if(!(exp)){Magnum::panic("assert(%s)\n%s line# %d\n",#exp,__FILE__,__LINE__);}
#endif

};

#endif