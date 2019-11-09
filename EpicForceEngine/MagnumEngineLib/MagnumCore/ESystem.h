///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _ESystem_h_
#define _ESystem_h_

#include "Stage.h"
#include "Array.h"
#include "EString.h"

namespace Magnum
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


	static char *strcpy(char *dest, const char *src);
	static char *strncpy(char *dest, const char *src, int count);
	static int strcmp(const char *str1, const char *str2);
	static int stricmp(const char *str1, const char *str2);
	static int strncmp(const char *str1, const char *str2, int maxcount);
	static int strnicmp(const char *str1, const char *str2, int maxcount);

	static void memset(void *dst, int val, int size);
	static void memcpy(void *dst, const void *src, int size);
	static int memcmp(const void *s1, const void *s2, int size);

	static String getDirectory(const char *fullPath);
	static String getFileName(const char *fullPath);
	static String getExtension(const char *fullPath);

	static bool isDirectory(const char *name_);

	static bool makeDirectory(const char *dir_);
	static bool listDirectories(const String &path, Vector<String> &directories);
	static bool listFiles(const char *rootDir, const String &path, const char *extension, Vector<System::File> &files);
	static bool listAssets(const char *rootDir, const char *extension, Vector<System::File> &files);
};

};

#endif

