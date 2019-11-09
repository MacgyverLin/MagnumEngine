///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#include "Stage.h"

#if defined(WIN32)

#include <wincon.h>
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#elif ( defined(__ANDROID__ )  )

#include <android/log.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#else // IOS



#endif

using namespace EpicForce;

namespace EpicForce
{
#if defined(WIN32)
#elif defined(__ANDROID__)
	void Stage::beginCheckMemoryLeak(int breakAtAllocationID)
	{
	}

	void Stage::dumpMemoryLeak()
	{
	}

	void Stage::endCheckMemoryLeak()
	{
	}

	void Stage::addEditorProjectView(void *view)
	{
	}

	void *Stage::getEditorProjectView(int i)
	{
		return 0;
	}

	int Stage::getNumEditorProjectView()
	{
		return 0;
	}
	
	void Stage::enableEditorMode()
	{
		_editorMode = true;
	}

	void Stage::disableEditorMode()
	{
		_editorMode = false;
	}

	bool Stage::isEditorMode()
	{
		return _editorMode;
	}

	bool Stage::getPlatformExternalDeviceMounted()
	{
		return true;
	}
#else // IOS
#endif
}
