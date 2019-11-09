///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#include "Stage.h"
#include "ESystem.h"
using namespace EpicForce;

void System::Memset(void *dst, int val, int size)
{
	::memset(dst, val, size);
}

void System::Memcpy(void *dst, const void *src, int size)
{
	::memcpy(dst, src, size);
}

int System::Memcmp(const void *s1, const void *s2, int size)
{
	return ::memcmp(s1, s2, size);
}

bool System::isDirectory(const char *path)
{
	int length = strlen(path);
    int i = length - 1;

	// exception for directories
    if(path[length] == '.') 
	{
		return true;
	}	
	
    // such as \. and \..
    for(i; i >= 0; i--) 
	{
        if(path[i] == '.') 
			return false; // if we first encounter a . then it's a file
        else if (path[i] == '\\' || path[i] == '/') 
			return true; // if we first encounter a \ it's a dir
    }

	return false;
}

bool System::makeDirectory(const char *dir_) 
{
#if defined(WIN32)
	String dir(dir_);
	Vector<String> intermediateDirs;
	String tem =  "";

	WIN32_FIND_DATA fileinfo;
	HANDLE fFile = FindFirstFile(dir, &fileinfo); 

	if(fileinfo.dwFileAttributes   ==   FILE_ATTRIBUTE_DIRECTORY) 
	{ 
		//   Directory   Exists   close   file   and   return 
		FindClose(fFile); 
		return true; 
	}

	for(int i=0; i<dir.length(); i++) // Parse the supplied String Directory
	{ 
		if(dir[i] != '\\' && dir[i] != '/')		// if the Charachter is not a \   
			tem += dir[i];		// add the character to the Temp String 
		else 
		{ 
			intermediateDirs.push() = tem; // if the Character is a  \   
			tem += "\\";		// Now add the  \ to the temp string 
		} 
		if(i == dir.length()-1) //   If   we   reached   the   end   of   the   String 
			intermediateDirs.push() = tem; 
	} 

	// Close   the   file 
	FindClose(fFile); 

	// Now   lets   cycle   through   the   String   Array   and   create   each   directory   in   turn 
	for(int i=1; i<intermediateDirs.length(); i++) 
	{ 
		debug("intermediateDirs[i]=%s", intermediateDirs[i]);
		bool tt = CreateDirectory(intermediateDirs[i], NULL); 
		// If the Directory exists it will return false 
		if(tt) 
			SetFileAttributes(intermediateDirs[i], FILE_ATTRIBUTE_NORMAL); 
		// If   we   were   successful   we   set   the   attributes   to   normal 
	} 

	// Now   lets   see   if   the   directory   was   successfully   created 
	fFile = FindFirstFile(dir, &fileinfo);
	if(fileinfo.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) 
	{ 
		// Directory   Exists   close   file   and   return 
		FindClose(fFile); 
		return true; 
	} 
	else 
	{ 
		// For   Some   reason   the   Function   Failed     Return   FALSE 
		FindClose(fFile); 
		return false; 
	}

	return true;
#elif defined(__ANDROID__ )
	return true;
#elif ( defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) )
	return true;
#endif
} 

bool System::listDirectories(const String &path, Vector<String> &directories)
{
#if defined(WIN32)
	HANDLE hFind = INVALID_HANDLE_VALUE;     
	WIN32_FIND_DATA ffd;
	directories.push() = path;

	String str = path + "*";
	hFind = FindFirstFile(str.text(), &ffd);

	if(hFind == INVALID_HANDLE_VALUE)
	{          
		return false;
	}

	do
	{       
		if( String(ffd.cFileName)!="." && String(ffd.cFileName)!="..")
		{               
			if( (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !(ffd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) )
			{
				String str = path + ffd.cFileName + "/";
				if( !listDirectories(str.text(), directories) )
					return false;
			}
		}
	}while (FindNextFile(hFind, &ffd) != 0);

	if( GetLastError() != ERROR_NO_MORE_FILES )
	{            
		FindClose(hFind);
		return false;        
	}

	FindClose(hFind);      
	hFind = INVALID_HANDLE_VALUE;

	return true;
#elif defined(__ANDROID__ )
	return true;
#elif ( defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) )
	return true;
#endif
}

bool System::listFiles(const char *rootDir, const String &path, const char *extension, 
					   Vector<System::File> &files)
{
#if defined(WIN32)
	int trimStart  = strlen(rootDir);
	int trimEnd    = strlen(extension)+1;

	HANDLE hFind = INVALID_HANDLE_VALUE;     
	WIN32_FIND_DATA ffd;

	String str = path + "*." + extension;    
	hFind = FindFirstFile(str.text(), &ffd);     
	if(hFind == INVALID_HANDLE_VALUE)
	{          
		return false;
	}

	do
	{       
		if( String(ffd.cFileName)!="." && String(ffd.cFileName)!=".." )
		{               
			if( !(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !(ffd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) )
			{
				System::File &file		= files.push();

				file.fileName			= path + ffd.cFileName;
				file.fileName			= file.fileName.extract(trimStart, file.fileName.length()-trimStart-trimEnd);
				file.extension			= extension;
				file.createTime			= (((unsigned long long)ffd.ftCreationTime.dwHighDateTime  )<<32) | ((unsigned long long)ffd.ftCreationTime.dwLowDateTime   );
				file.lastWriteTime		= (((unsigned long long)ffd.ftLastWriteTime.dwHighDateTime )<<32) | ((unsigned long long)ffd.ftLastWriteTime.dwLowDateTime  );
				file.lastAccessTime		= (((unsigned long long)ffd.ftLastAccessTime.dwHighDateTime)<<32) | ((unsigned long long)ffd.ftLastAccessTime.dwLowDateTime );

				/*
				String filename;
				String extension;

				int pos;
				char *test = ffd.cFileName;
				int len = strlen(test);
				for(pos=0; pos<len; pos++)
				{
					if(test[pos]=='.')
						break;
				}
				
				filename					= test;
				if(pos==len)
				{
					filenames.push()		= filename;
					extensions.push()		= "";
				}
				else
				{
					filenames.push()		= filename.extract(0, pos);
					extensions.push()		= filename.extract(pos+1, len);
				}
				times.push()			= 
					//(((unsigned long long)ffd.ftCreationTime.dwHighDateTime  )<<32) | ((unsigned long long)ffd.ftCreationTime.dwLowDateTime  );
					//(((unsigned long long)ffd.ftLastAccessTime.dwHighDateTime)<<32) | ((unsigned long long)ffd.ftLastAccessTime.dwLowDateTime);
					(((unsigned long long)ffd.ftLastWriteTime.dwHighDateTime )<<32) | ((unsigned long long)ffd.ftLastWriteTime.dwLowDateTime );
				*/
			}
		}
	}while (FindNextFile(hFind, &ffd) != 0);

	if( GetLastError() != ERROR_NO_MORE_FILES )
	{            
		FindClose(hFind);
		return false;        
	}

	FindClose(hFind);      
	hFind = INVALID_HANDLE_VALUE;   

	return true;
#elif defined(__ANDROID__ )
	return true;
#elif ( defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) )
	return true;
#endif
}

bool System::listAssets(const char *rootDir, const char *extension, 
	                    Vector<System::File> &files)
{
#if defined(WIN32)
	Vector<String> assetsDirs;
	if( listDirectories(rootDir, assetsDirs) ) 
	{
		for(int i=0; i<assetsDirs.length(); i++)
		{
			listFiles(rootDir, assetsDirs[i], extension, files);

			//for(int j=0; j<filenames.length(); j++)
			//{
				//debug("%s %d", filenames[j].text(), times[j] );
			//}
		}
	}

	return true;
#elif defined(__ANDROID__ )
	return true;
#elif ( defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) )
	return true;
#endif
}