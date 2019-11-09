///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Stage.h"
using namespace Magnum;

namespace Magnum
{
	long long				Stage::_lastTime									= 0;
	long long				Stage::_newTime										= 0;
	long long				Stage::_timeAdjust									= 0;
	long long				Stage::_lastPolledTime								= 0;
	long long				Stage::_elapsed										= 0;
	float					Stage::_frameRate									= 0;
	long long				Stage::_click										= 0;
	long long				Stage::_gameStartTime								= 0;
	long long				Stage::_frameCountTimer								= 0; 
	int						Stage::_frameCount									= 0;
	unsigned long			Stage::_clicker										= 0;
	int						Stage::_width										= 0;
	int						Stage::_height										= 0;
	char					Stage::_rawAssetRootDirectory[4096];
	char					Stage::_assetRootDirectory[4096];
	char					Stage::_documentDirectory [4096];
	char					Stage::_externalDirectory [4096];
	char					Stage::_initialScene      [4096];
	bool					Stage::_checkMemoryLeakEnabled						= false;
	bool					Stage::_editorMode									= false;
	void					*Stage::_editorProjectView[16];
	int						Stage::_numEditorProjectView						= 0;

	long long				(*Stage::_getCurrentTimeMSFunc)()					= 0;
	void					(*Stage::_printInfoFunc)(const char *buf_)			= 0;
	void					(*Stage::_printDebugFunc)(int i, const char *buf_)	= 0;
	void					(*Stage::_printPanicFunc)(const char *buf_)			= 0;

	char					*Stage::_lastError									= 0;
	bool					Stage::_initiated									= false;
	bool					Stage::_aborting									= false;

	long long Stage::realTime()
	{
		long long current_time = _getCurrentTimeMSFunc();

		return (long long)((double) (current_time-_gameStartTime) );	
	}

	long long Stage::time()
	{
		return _newTime;
	}

	long long Stage::elapsed()
	{
		// hard code for now
		return _elapsed;
	}

	float Stage::frameRate()
	{
		// hard code for now
		return _frameRate;
	}

	bool Stage::initiated()
	{
		return _initiated;
	}
	
	bool Stage::aborting()
	{
		return _aborting;
	}

	void Stage::slice()
	{	
		// set last time
		_lastTime = _newTime;

		_lastPolledTime = realTime();

		_elapsed = _lastTime ? _lastPolledTime - _lastTime : 0;
		
		_frameCountTimer += _elapsed;
		if ( _frameCountTimer >= 1000 )
		{
			_frameRate = _frameCount;
			//debug("%d, %f, %d", _frameCountTimer, _frameRate, _elapsed);
			_frameCount = 0;

			_frameCountTimer -= 1000;
		}
		_frameCount++;

		//if(_suspendState & SUSPEND_PROCESS)
		if(false)
		{
			//Add to freeze values
			_timeAdjust += _elapsed;

			//Nothing happened here
			_elapsed = 0;
		}
		else
		{
			//Store new time
			_newTime = _lastPolledTime;
		}
	}

	void Stage::setStartTime()
	{
		_gameStartTime = _getCurrentTimeMSFunc();
	}

	void Stage::setScreenSize(int width_, int height_)
	{
		_width  = width_;
		_height = height_;
	}

	void Stage::getScreenSize(int &width_, int &height_)
	{
		width_  = _width;
		height_ = _height;
	}

	int Stage::getScreenWidth()
	{
		return _width;
	}

	int Stage::getScreenHeight()
	{
		return _height;
	}
	
	void Stage::setRawAssetRootDirectory(const char *rawAssetRootDirectory_)
	{
		strncpy(_rawAssetRootDirectory, rawAssetRootDirectory_, 4096);
	}

	void Stage::setAssetRootDirectory(const char *assetRootDirectory_)
	{
		strncpy(_assetRootDirectory, assetRootDirectory_, 4096);
	}

	void Stage::setDocumentDirectory(const char *documentDirectory_)
	{
		strncpy(_documentDirectory, documentDirectory_, 4096);
	}

	void Stage::setExternalDirectory(const char *externalDirectory_)
	{
		strncpy(_externalDirectory, externalDirectory_, 4096);
	}

	void Stage::setInitialScene(const char *initialScene_)
	{
		strncpy(_initialScene, initialScene_, 4096);
	}

	void Stage::setGetCurrentTimeMSFunc(long long (*getCurrentTimeMSFunc_)())
	{
		_getCurrentTimeMSFunc	= getCurrentTimeMSFunc_;
	}

	void Stage::setPrintFunc(void (*printInfoFunc_)(const char *buf_),
							 void (*printDebugFunc_)(int i, const char *buf_),
							 void (*printPanicFunc_)(const char *buf_))
	{
		_printInfoFunc			= printInfoFunc_;
		_printDebugFunc			= printDebugFunc_;
		_printPanicFunc			= printPanicFunc_;
	}

	const char *Stage::getRawAssetRootDirectory()
	{
		return _rawAssetRootDirectory;
	}

	const char *Stage::getAssetRootDirectory()
	{
		return _assetRootDirectory;
	}

	const char *Stage::getDocumentDirectory()
	{
		return _documentDirectory;
	}

	const char *Stage::getExternalDirectory()
	{
		return _externalDirectory;
	}

	const char *Stage::getInitialScene()
	{
		return _initialScene;
	}

	void info( const char *a_fmtstr, ...)
	{
#ifdef FINAL
#else
		char buf[4096];
		va_list argptr;
		va_start(argptr, a_fmtstr);

		vsnprintf(buf, 4096, a_fmtstr, argptr);
		
		va_end(argptr);

		Stage::_printInfoFunc(buf);
#endif
	}

	void debug( const char *a_fmtstr, ...)
	{
#ifdef FINAL
#else
		char buf[4096];
		va_list argptr;
		va_start(argptr, a_fmtstr);

		vsnprintf(buf, 4096, a_fmtstr, argptr);
		
		va_end(argptr);

		Stage::_printDebugFunc(0, buf);
#endif
	}

	void panic( const char *a_fmtstr, ...)
	{
#ifdef FINAL
#else
		char buf[4096];
		va_list argptr;
		va_start(argptr, a_fmtstr);

		vsnprintf(buf, 4096, a_fmtstr, argptr);
		
		va_end(argptr);

		Stage::_printPanicFunc(buf);
#endif
	}
};