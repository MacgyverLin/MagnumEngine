///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Stage.h"

#if defined(WIN32)

#include <wincon.h>
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#elif ( defined(__ANDROID__ )  )
#else // IOS
#endif

using namespace Magnum;

namespace Magnum
{
#if defined(WIN32)
	_CrtMemState s1, s2, s3;

	void Stage::beginCheckMemoryLeak(int breakAtAllocationID)
	{
		if(!_checkMemoryLeakEnabled)
		{
			_CrtMemCheckpoint( &s1 );

			#ifdef _DEBUG
				int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
				flag |= _CRTDBG_LEAK_CHECK_DF; // Turn on leak-checking bit
				_CrtSetDbgFlag(flag);
				

				if(breakAtAllocationID!=-1)
					_CrtSetBreakAlloc(breakAtAllocationID);
			#endif
			_checkMemoryLeakEnabled = true;
		}
	}

	void Stage::dumpMemoryLeak()
	{
		if(_checkMemoryLeakEnabled)
		{
			_CrtMemCheckpoint( &s2 );

			if( _CrtMemDifference( &s3, &s1, &s2) )
			{
				_CrtMemDumpStatistics( &s3 );

				_CrtDumpMemoryLeaks();
				assert(0);
			}
		}
	}

	void Stage::endCheckMemoryLeak()
	{
		if(_checkMemoryLeakEnabled)
		{
			int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
			flag &= ~_CRTDBG_LEAK_CHECK_DF; // Turn on leak-checking bit
			_CrtSetDbgFlag(flag);

			_checkMemoryLeakEnabled = false;
		}
	}

	void Stage::addEditorProjectView(void *view)
	{
		if(_numEditorProjectView+1<16)
		{
			_editorProjectView[_numEditorProjectView] =  view;

			_numEditorProjectView++;
		}
	}

	void *Stage::getEditorProjectView(int i)
	{
		return _editorProjectView[i];
	}

	int Stage::getNumEditorProjectView()
	{
		return _numEditorProjectView;
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
#elif defined(__ANDROID__)
#else // IOS
#endif
}