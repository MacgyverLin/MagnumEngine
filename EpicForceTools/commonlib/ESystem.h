///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _ESystem_h_
#define _ESystem_h_

#include "Stage.h"
#include "Array.h"
#include "EString.h"

namespace EpicForce
{

class System
{
public:
	class File
	{
	public:
		File()
		{
			fileName		= "";
			extension		= "";
			createTime		= 0;
			lastWriteTime	= 0;
			lastAccessTime	= 0;
		}

		File(const char *fileName_)
		{
			fileName		= fileName_;
			extension		= "";
			createTime		= 0;
			lastWriteTime	= 0;
			lastAccessTime	= 0;
		}

		File(const char *fileName_, const char *extension_, 
			 unsigned long long createTime_, unsigned long long lastWriteTime_, unsigned long long lastAccessTime_)
		{
			fileName		= fileName_;
			extension		= extension_;
			createTime		= createTime_;
			lastWriteTime	= lastWriteTime_;
			lastAccessTime	= lastAccessTime_;
		}

		bool operator < (const File &file)
		{
			return this->fileName < file.fileName;
		}

		bool operator == (const File &file)
		{
			return this->fileName == file.fileName;
		}

		String				fileName;
		String				extension;
		unsigned long long	createTime;
		unsigned long long	lastWriteTime;
		unsigned long long	lastAccessTime;
	};

	static void Memset(void *dst, int val, int size);
	static void Memcpy(void *dst, const void *src, int size);
	static int Memcmp(const void *s1, const void *s2, int size);
	static bool isDirectory(const char *name_);

	static bool makeDirectory(const char *dir_);
	static bool listDirectories(const String &path, Vector<String> &directories);
	static bool listFiles(const char *rootDir, const String &path, const char *extension, Vector<System::File> &files);
	static bool listAssets(const char *rootDir, const char *extension, Vector<System::File> &files);
};

};

#endif

