///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _Stage_h_
#define _Stage_h_

#if defined(WIN32)

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <windows.h>
#include <mmsystem.h>
#define ENABLE_RESOURCE_IMPORT

#elif ( defined(__ANDROID__ )  )
#elif // IOS
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

namespace EpicForce
{

#ifdef WIN32
#define strcasecmp stricmp
#define strncasecmp strnicmp
#endif

class Stage 
{
public:
	////////////////////////////////////
	// Generic
	static long long clock();
	static long long time();
	static long long elapsed();
	static bool initiated();
	static bool aborting();
	static void slice();
	static float rate();
	static void setGameStartTime();
	static void setGameResolution(int width_, int height_);
	static void beginCheckMemoryLeak(int breakAtAllocationID);
	static void dumpMemoryLeak();
	static void endCheckMemoryLeak();
	typedef enum
	{
		SUSPEND_OFF			=1	,	//Off state
		SUSPEND_BEGIN			,	//Begin suspension
		SUSPEND_PROCESS		=4	,	//Process suspension
		SUSPEND_DVD_ERROR	=8
	}SuspendProcess;
private:
	static SuspendProcess	_suspendState;
	static long long		_lastTime;
	static long long		_newTime;
	static long long		_timeAdjust;
	static long long		_lastPolledTime;
	static long long		_elapsed;
	static float			_rate;
	static long long		_click;
	static long long		_gameStartTime;
	static long long		_frameCountTimer; 
	static int				_frameCount;
	static unsigned long	_clicker;
	static int				_width;
	static int				_height;
	static bool				_checkMemoryLeakEnabled;
public:
	static char				*_lastError;
	static bool				_initiated;
	static bool				_aborting;
	////////////////////////////////////
	// Platform Dependent
	static const char *getPlatformBundleDirectory();
	static const char *getPlatformDocumentDirectory();
	static const char *getPlatformExternalDeviceDirectory();
	static bool getPlatformExternalDeviceMounted();
	//----------------------------------------------------------------
	static long long getPlatformCurrentTimeMS();
	//----------------------------------------------------------------
	static void printlnPlatform(const char *buf_);

	//----------------------------------------------------------------
	static int getScreenWidth();
	static int getScreenHeight();
public:
	////////////////////////////////////
	// Game Dependent
	typedef enum
	{
		ROTATE_0   = 0,
		ROTATE_90  = 1,
		ROTATE_180 = 3,
		ROTATE_270 = 4
	}Orientation;

	static Orientation getGameOrientation();
};

void debug(const char *a_fmtstr, ...);
void print(const char *a_fmtstr, ...);
void abort(const char *a_fmtstr, ...);
void panic(const char *a_fmtstr, ...);

#ifdef assert
#undef assert
#endif

#ifdef FINAL
#define assert(exp)		((void)0)
#else
#define assert(exp)		if(!(exp)){EpicForce::panic("assert(%s)\n%s line# %d\n",#exp,__FILE__,__LINE__);}
#endif

};

#endif