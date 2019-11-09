///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#include "Stage.h"
using namespace EpicForce;

namespace EpicForce
{
	Stage::SuspendProcess	Stage::_suspendState			= SUSPEND_OFF;
	long long				Stage::_lastTime				= 0;
	long long				Stage::_newTime					= 0;
	long long				Stage::_timeAdjust				= 0;
	long long				Stage::_lastPolledTime			= 0;
	long long				Stage::_elapsed					= 0;
	float					Stage::_rate					= 0;
	long long				Stage::_click					= 0;
	long long				Stage::_gameStartTime			= 0;
	long long				Stage::_frameCountTimer			= 0; 
	int						Stage::_frameCount				= 0;
	unsigned long			Stage::_clicker					= 0;
	int						Stage::_width					= 0;
	int						Stage::_height					= 0;
	char					*Stage::_lastError				= 0;
	bool					Stage::_initiated				= false;
	bool					Stage::_aborting				= false;
	bool					Stage::_checkMemoryLeakEnabled	= false;

	long long Stage::clock()
	{
		long long current_time = getPlatformCurrentTimeMS();

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
		//Set last time
		_lastTime = _newTime;

		_lastPolledTime = clock();

		_elapsed = _lastTime ? _lastPolledTime - _lastTime : 0;
		
		_frameCountTimer += _elapsed;
		if ( _frameCountTimer >= 1000 )
		{
			_rate = _frameCount;
			//debug("%d, %f, %d", _frameCountTimer, _rate, _elapsed);
			_frameCount = 0;

			_frameCountTimer -= 1000;
		}
		_frameCount++;

		if(_suspendState & SUSPEND_PROCESS)
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

	float Stage::rate()
	{
		// hard code for now
		return _rate;
	}

	void Stage::setGameStartTime()
	{
		_gameStartTime = getPlatformCurrentTimeMS();
	}

	void Stage::setGameResolution(int width_, int height_)
	{
		_width  = width_;
		_height = height_;
	}

	void debug( const char *a_fmtstr, ...)
	{
		char buf[2048];
		va_list argptr;
		va_start(argptr, a_fmtstr);

#ifdef FINAL
#else
		vsnprintf(buf, 2048, a_fmtstr, argptr);
		Stage::printlnPlatform("DEBUG  : ");
		Stage::printlnPlatform(buf);
		Stage::printlnPlatform("\n");
#endif
		va_end(argptr);
	}

	void print(const char *a_fmtstr, ...)
	{
		char buf[2048];
		va_list argptr;
		va_start(argptr, a_fmtstr);

#ifdef FINAL
#else
		vsnprintf(buf, 2048, a_fmtstr, argptr);
		Stage::printlnPlatform(buf);
#endif

		va_end(argptr);
	}

	void abort(const char *a_fmtstr, ...)
	{
		char buf[2048];
		va_list argptr;
		va_start(argptr, a_fmtstr);

#ifdef FINAL
#else
		vsnprintf(buf, 2048, a_fmtstr, argptr);
		Stage::printlnPlatform("ABORT!!: ");
		Stage::printlnPlatform(buf);
		Stage::printlnPlatform("\n");
#endif
		va_end(argptr);
		exit(-1);
	}

	void panic(const char *a_fmtstr, ...)
	{
		char buf[2048];
		va_list argptr;
		va_start(argptr, a_fmtstr);
#ifdef FINAL
#else
		vsnprintf(buf, 2048, a_fmtstr, argptr);
		Stage::printlnPlatform("PANIC!!: ");
		Stage::printlnPlatform(buf);
		Stage::printlnPlatform("\n");
#endif
		va_end(argptr); 
		exit(-1);
	}

	//----------------------------------------------------------------
	int Stage::getScreenWidth()
	{
		return 640;
	}

	//----------------------------------------------------------------
	int Stage::getScreenHeight()
	{
		return 480;
	}

	long long Stage::getPlatformCurrentTimeMS()
	{
		return 0;
	}

	//----------------------------------------------------------------
	void Stage::printlnPlatform(const char *buf_)
	{
		OutputDebugStringA(buf_);
		// printf(buf_);
	}
};