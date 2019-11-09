///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#include "Stage.h"
#include "FileIO.h"
#if defined(WIN32)
#elif defined(__ANDROID__ )
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#elif ( defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) )
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#endif
using namespace EpicForce;

#define USE_FOPEN

typedef struct
{
#if defined (USE_FOPEN)
	FILE		*handle;
	unsigned int position;
	unsigned int length;
#elif defined(WIN32)
	HANDLE		handle;
	OVERLAPPED	overlapped;
#elif defined(__ANDROID__ )
	int			handle;
#elif ( defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) )
	int			handle;
#endif
}FileDesc;

FileIO::FileIO(const char *path_)
: IO(path_)
, user(0)
{
#if defined (USE_FOPEN)
	user = (void*)(new FileDesc);
	assert(user);

	FileDesc *fd	= ((FileDesc *)user);

	fd->handle		= 0;
	fd->position	= 0;
	fd->length		= 0;
#elif defined(WIN32)
	user = (void*)(new FileDesc);
	assert(user);

	FileDesc *fd	= ((FileDesc *)user);
	
	fd->handle		= INVALID_HANDLE_VALUE;
	fd->position	= 0;
	fd->length		= 0;
#elif defined(__ANDROID__ )
	user = (void*)(new FileDesc);
	assert(user);

	FileDesc *fd	= ((FileDesc *)user);

	fd->handle		= -1;
	fd->position	= 0;
	fd->length		= 0;
#elif ( defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) )
	user = (void*)(new FileDesc);
	assert(user);
    
	FileDesc *fd	= ((FileDesc *)user);
    
	fd->handle		= -1;
	fd->position	= 0;
	fd->length		= 0;
#endif
}

FileIO::~FileIO()
{
	close();

	delete ((FileDesc*)user);
}

bool FileIO::open(AccessMode mode)
{
	IO::open(mode);

#if defined (USE_FOPEN)
	FileDesc *fd = ((FileDesc *)user);
	assert( fd->handle==0 );
    
	if( isReadEnabled() && !isWriteEnabled() )
		fd->handle = ::fopen(path.text(), "rb");
	else if( !isReadEnabled() && isWriteEnabled() )
		fd->handle = ::fopen(path.text(), "wb");
	else if( isReadEnabled() && isWriteEnabled() )
		fd->handle = ::fopen(path.text(), "rb+wb");

	fd->position	= 0;

	::fseek(fd->handle, 0, SEEK_END);
	fd->length		= ::ftell(fd->handle);
	::fseek(fd->handle, 0, SEEK_SET);
#elif defined(WIN32)
	FileDesc *fd = ((FileDesc *)user);
	assert( fd->handle==INVALID_HANDLE_VALUE );

	DWORD dwDesiredAccess = 0;
	if( isReadEnabled() && !isWriteEnabled() )
		dwDesiredAccess |= GENERIC_READ;
	else if( !isReadEnabled() && isWriteEnabled() )
		dwDesiredAccess |= GENERIC_WRITE;
	else if( isReadEnabled() && isWriteEnabled() )
		dwDesiredAccess |= (GENERIC_READ | GENERIC_WRITE);

	DWORD dwCreationDisposition = 0;
	if( isReadEnabled() && !isWriteEnabled() )
		dwCreationDisposition |= OPEN_EXISTING;
	else if( !isReadEnabled() && isWriteEnabled() )
		dwCreationDisposition |= CREATE_ALWAYS;
	else if( isReadEnabled() && isWriteEnabled() )
		dwCreationDisposition |= (OPEN_EXISTING | CREATE_ALWAYS);

	fd->handle = CreateFile(path.text(), dwDesiredAccess, 0, 0, dwCreationDisposition, 
							FILE_ATTRIBUTE_NORMAL, 0);
#elif defined(__ANDROID__ )
	FileDesc *fd = ((FileDesc *)user);
	assert( fd->handle==-1 );
    
	int flag = O_SYNC;
	if( isReadEnabled() && !isWriteEnabled() )
		flag |= O_RDONLY;
	else if( !isReadEnabled() && isWriteEnabled() )
		flag |= (O_WRONLY | O_CREAT);
	else if( isReadEnabled() && isWriteEnabled() )
		flag |= (O_RDWR | O_CREAT);
    
	fd->handle = ::open(path.text(), flag, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
#elif ( defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) )
	FileDesc *fd = ((FileDesc *)user);
	assert( fd->handle==-1 );

	int flag = O_SYNC;
	if( isReadEnabled() && !isWriteEnabled() )
		flag |= O_RDONLY;
	else if( !isReadEnabled() && isWriteEnabled() )
		flag |= (O_WRONLY | O_CREAT);
	else if( isReadEnabled() && isWriteEnabled() )
		flag |= (O_RDWR | O_CREAT);
    
	fd->handle = ::open(path.text(), flag, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
#endif
	return live();
}

bool FileIO::openForAsync(AccessMode mode)
{
	IO::openForAsync(mode);

#if defined (USE_FOPEN)
	FileDesc *fd = ((FileDesc *)user);
	assert( fd->handle==0 );
    
	if( isReadEnabled() && !isWriteEnabled() )
		fd->handle = ::fopen(path.text(), "rb");
	else if( !isReadEnabled() && isWriteEnabled() )
		fd->handle = ::fopen(path.text(), "wb");
	else if( isReadEnabled() && isWriteEnabled() )
		fd->handle = ::fopen(path.text(), "rb+wb");

	if(!fd->handle)
		return false;

	fd->position	= 0;

	::fseek(fd->handle, 0, SEEK_END);
	fd->length		= ::ftell(fd->handle);
	::fseek(fd->handle, 0, SEEK_SET);
#elif defined(WIN32)
	FileDesc *fd = ((FileDesc *)user);
	assert( fd->handle==INVALID_HANDLE_VALUE );

	DWORD dwDesiredAccess = 0;
	if( isReadEnabled() && !isWriteEnabled() )
		dwDesiredAccess |= GENERIC_READ;
	else if( !isReadEnabled() && isWriteEnabled() )
		dwDesiredAccess |= GENERIC_WRITE;
	else if( isReadEnabled() && isWriteEnabled() )
		dwDesiredAccess |= (GENERIC_READ | GENERIC_WRITE);

	DWORD dwCreationDisposition = 0;
	if( isReadEnabled() && !isWriteEnabled() )
		dwCreationDisposition |= OPEN_EXISTING;
	else if( !isReadEnabled() && isWriteEnabled() )
		dwCreationDisposition |= CREATE_ALWAYS;
	else if( isReadEnabled() && isWriteEnabled() )
		dwCreationDisposition |= (OPEN_EXISTING | CREATE_ALWAYS);

	fd->handle = CreateFile(path.text(), dwDesiredAccess, 0, 0, dwCreationDisposition, 
							FILE_FLAG_OVERLAPPED|FILE_FLAG_NO_BUFFERING, 0);
#elif defined(__ANDROID__ )
	FileDesc *fd = ((FileDesc *)user);
	assert( fd->handle==-1 );

	int flag = O_NONBLOCK;
	if( isReadEnabled() && !isWriteEnabled() )
		flag |= O_RDONLY;
	else if( !isReadEnabled() && isWriteEnabled() )
		flag |= (O_WRONLY | O_CREAT);
	else if( isReadEnabled() && isWriteEnabled() )
		flag |= (O_RDWR | O_CREAT);

	fd->handle = ::open(path.text(), flag, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    //int opt = 1;
    //assert(ioctl(fd->handle, FIONBIO, &opt)!=-1);
#if defined(O_NONBLOCK)
    /* Fixme: O_NONBLOCK is defined but broken on SunOS 4.1.x and AIX 3.2.5. */
	int flags = 0;
    if (-1 == (flags = fcntl(fd->handle, F_GETFL, 0)))
        flags = 0;
    
	fcntl(fd->handle, F_SETFL, flags | O_NONBLOCK);
#else
    /* Otherwise, use the old way of doing it */
    flags = 1;
    ioctl(fd->handle, FIONBIO, &flags);
#endif
#elif ( defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) )
	FileDesc *fd = ((FileDesc *)user);
	assert( fd->handle==-1 );
    
	int flag = O_NONBLOCK;
	if( isReadEnabled() && !isWriteEnabled() )
		flag |= O_RDONLY;
	else if( !isReadEnabled() && isWriteEnabled() )
		flag |= (O_WRONLY | O_CREAT);
	else if( isReadEnabled() && isWriteEnabled() )
		flag |= (O_RDWR | O_CREAT);
    
	fd->handle = ::open(path.text(), flag, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    //int opt = 1;
    //assert(ioctl(fd->handle, FIONBIO, &opt)!=-1);
#endif
	return live();
}

bool FileIO::isAsyncFinished()
{
#if defined (USE_FOPEN)
	FileDesc *fd = ((FileDesc *)user);
	assert( fd->handle!=0 );

	return true;
#elif defined(WIN32)
	FileDesc *fd = ((FileDesc *)user);
	assert( fd->handle!=INVALID_HANDLE_VALUE );

	if(asyncMode)
	{
		DWORD numberOfBytesTransferred = 0;
		if( GetOverlappedResult(fd->handle, &fd->overlapped, &numberOfBytesTransferred, FALSE) )
		{
			debug("Info: Async Operation Ended Sucessfully %d\n", numberOfBytesTransferred);
			return true;
		}
		else
		{
			int lastError = GetLastError();
			if( lastError==ERROR_IO_INCOMPLETE ) 
			{
				debug("Info: IO_INCOMPLETE File Reading...%d\n", numberOfBytesTransferred);
				return false;
			}
			else if( lastError==ERROR_IO_PENDING ) 
			{
				debug("Info: IO_PENDING File Reading...%d\n", numberOfBytesTransferred);
				return false;
			}
			else
			{
				debug("Error: Unhandled Error..%d\n", lastError);
				return false;
			}
		}
	}
	else
	{
		return true;
	}
#elif defined(__ANDROID__ )
	FileDesc *fd = ((FileDesc *)user);
	assert( fd->handle!=-1 );

	return true;
#elif ( defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) )
	FileDesc *fd = ((FileDesc *)user);
	assert( fd->handle!=-1 );
    
	return true;  
#endif
}

void FileIO::waitAsyncFinished()
{
#if defined (USE_FOPEN)
	FileDesc *fd = ((FileDesc *)user);
	assert( fd->handle!=0 );
#elif defined(WIN32)
	FileDesc *fd = ((FileDesc *)user);
	assert( fd->handle!=INVALID_HANDLE_VALUE );

	if(asyncMode)
	{
		DWORD numberOfBytesTransferred = 0;
		if( GetOverlappedResult(fd->handle, &fd->overlapped, &numberOfBytesTransferred, TRUE) )
		{
			debug("Info: Async Operation Ended Sucessfully %d\n", numberOfBytesTransferred);
		}
	}
	else
	{
		// sync mode always finished
	}

#elif defined(__ANDROID__ )
	FileDesc *fd = ((FileDesc *)user);
	assert( fd->handle!=-1 );
#elif ( defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) )
	FileDesc *fd = ((FileDesc *)user);
	assert( fd->handle!=-1 );
#endif
}

bool FileIO::close()
{
#if defined (USE_FOPEN)
	FileDesc *fd = ((FileDesc *)user);
	if(fd->handle==0)
		return false;

	fclose(fd->handle);
	fd->handle		= 0;
	fd->position	= 0;
	fd->length		= 0;
#elif defined(WIN32)
	FileDesc *fd = ((FileDesc *)user);
	if( fd->handle==INVALID_HANDLE_VALUE )
		return false;

	CloseHandle(fd->handle);
	fd->handle = INVALID_HANDLE_VALUE;
#elif defined(__ANDROID__ )
	FileDesc *fd = ((FileDesc *)user);
	if(fd->handle==-1)
		return false;

	::close(fd->handle);
	fd->handle = -1;

	//struct stat info;
	//if(stat(path, &info) == 0)
	//{
	//	debug("info.st_mode = %x", info.st_mode);
	//}
#elif ( defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) )
	FileDesc *fd = ((FileDesc *)user);
	if(fd->handle==-1)
		return false;
    
	::close(fd->handle);
	fd->handle = -1;
    
	//struct stat info;
	//if(stat(path, &info) != 0)
//		return false;
//	else
		//return true;
#endif

	return true;
}

bool FileIO::live() const
{
#if defined (USE_FOPEN)
	FileDesc *fd = ((FileDesc *)user);

	return fd->handle != 0;
#elif defined(WIN32)
	FileDesc *fd = ((FileDesc *)user);

	return fd->handle != INVALID_HANDLE_VALUE;
#elif defined(__ANDROID__ )
	FileDesc *fd = ((FileDesc *)user);

	return fd->handle != -1;
#elif ( defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) )
	FileDesc *fd = ((FileDesc *)user);
    
	return fd->handle != -1;
#endif
}

int FileIO::tell() const
{
#if defined (USE_FOPEN)
	FileDesc *fd = ((FileDesc *)user);
	assert(fd->handle!=0);

	return fd->position;
#elif defined(WIN32)
	FileDesc *fd = ((FileDesc *)user);
	assert(fd->handle!=INVALID_HANDLE_VALUE);

	return SetFilePointer(fd->handle, 0, 0, FILE_CURRENT);
#elif defined(__ANDROID__ )
	FileDesc *fd = ((FileDesc *)user);
	assert(fd->handle!=-1);

	return lseek(fd->handle, 0, SEEK_CUR);
#elif ( defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) )
	FileDesc *fd = ((FileDesc *)user);
	assert(fd->handle!=-1);

	return lseek(fd->handle, 0, SEEK_CUR);
#endif
}

int FileIO::seek(SeekDef seek, int offset)
{
#if defined (USE_FOPEN)
	FileDesc *fd = ((FileDesc *)user);
	assert(fd->handle!=0);

	switch(seek)
	{
		default:
		case BEGIN:
		{
			bool rval = ::fseek(fd->handle, offset, SEEK_SET)!=0;
			if(rval)
			{
				fd->position = 0            + offset;
			}
			return rval;
		}

		case CURRENT:
		{
			bool rval = ::fseek(fd->handle, offset, SEEK_CUR)!=0;
			if(rval)
			{
				fd->position = fd->position + offset;
			}
			return rval;
		}

		case END:
		{
			bool rval = ::fseek(fd->handle, offset, SEEK_END)!=0;
			if(rval)
			{
				fd->position = fd->length   - offset;
			}
			return rval;
		}
	};
#elif defined(WIN32)
	FileDesc *fd = ((FileDesc *)user);
	assert(fd->handle!=INVALID_HANDLE_VALUE);

	switch(seek)
	{
		default:
		case BEGIN:
			return SetFilePointer(fd->handle, offset, 0, FILE_BEGIN);

		case CURRENT:
			return SetFilePointer(fd->handle, offset, 0, FILE_CURRENT);

		case END:
			return SetFilePointer(fd->handle, offset, 0, FILE_END);
	};
#elif defined(__ANDROID__ )
	FileDesc *fd = ((FileDesc *)user);
	assert(fd->handle!=-1);

	switch(seek)
	{
		default:
		case BEGIN:
			return lseek(fd->handle, offset, SEEK_SET);

		case CURRENT:
			return lseek(fd->handle, offset, SEEK_CUR);

		case END:
			return lseek(fd->handle, offset, SEEK_END);
	};
#elif ( defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) )
	FileDesc *fd = ((FileDesc *)user);
	assert(fd->handle!=-1);
    
	switch(seek)
	{
		default:
		case BEGIN:
			return lseek(fd->handle, offset, SEEK_SET);
            
		case CURRENT:
			return lseek(fd->handle, offset, SEEK_CUR);
            
		case END:
			return lseek(fd->handle, offset, SEEK_END);
	};
#endif
}

int FileIO::read(void *buf, int size)
{
	assert( isReadEnabled() && "File was not opened in read mode");

#if defined (USE_FOPEN)
	FileDesc *fd = ((FileDesc *)user);
	assert(fd->handle!=0);

	int rval = fread(buf, 1, size, fd->handle);
	fd->position = fd->position + size;
	return rval;
#elif defined(WIN32)
	FileDesc *fd = ((FileDesc *)user);
	assert(fd->handle!=INVALID_HANDLE_VALUE);

	if(!asyncMode)
	{
		DWORD dwReadSize = 0;
		if( ReadFile(fd->handle, buf, size, &dwReadSize, 0) )
			return dwReadSize;
		else
			return -1;
	}
	else
	{
		assert((size % 2048)==0);  // make sure is multiple of 2048
		memset(&fd->overlapped, 0, sizeof(fd->overlapped));
		if(ReadFile(fd->handle, buf, size, 0, &fd->overlapped))
		{
			debug("File Read Sucessfully\n");
			return size;
		}
		else
		{
			int lastError = GetLastError();
			if(lastError == ERROR_IO_PENDING)
			{
				debug("Info: IO Pending..%d\n", lastError);
				return 0;
			}
			else
			{
				debug("Error: Unhandled Error..%d\n", lastError);
				return -1;
			}
		}
	}
#elif defined(__ANDROID__ )
	FileDesc *fd = ((FileDesc *)user);
	assert(fd->handle!=-1);
    
	if(!asyncMode)
	{
        return ::read(fd->handle, buf, size);
	}
	else
	{
        int rval = ::read(fd->handle, buf, size);
        if(rval>0)
        {
            debug("File Read Sucessfully\n");
            return rval;
        }
        else
        {
			int lastError = errno;
			if(lastError == EWOULDBLOCK)
			{
				debug("Info: IO Pending..%d\n", lastError);
				return 0;
			}
			else
			{
				debug("Error: Unhandled Error..%d\n", lastError);
				return -1;
			}
        }
	}
#elif ( defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) )
	FileDesc *fd = ((FileDesc *)user);
	assert(fd->handle!=-1);
    
	if(!asyncMode)
	{
        return ::read(fd->handle, buf, size);
	}
	else
	{
        int rval = ::read(fd->handle, buf, size);
        if(rval>0)
        {
            debug("File Read Sucessfully\n");
            return rval;
        }
        else
        {
			int lastError = errno;
			if(lastError == EWOULDBLOCK)
			{
				debug("Info: IO Pending..%d\n", lastError);
				return 0;
			}
			else
			{
				debug("Error: Unhandled Error..%d\n", lastError);
				return -1;
			}
        }
	}
#endif
}

int FileIO::read(unsigned char *uc)
{
	return read(uc, sizeof(unsigned char));
}

int FileIO::read(char *c)
{
	return read(c, sizeof(char));
}

int FileIO::read(unsigned short *us)
{
	return read(us, sizeof(unsigned short));
}

int FileIO::read(short *s)
{
	return read(s, sizeof(short));
}

int FileIO::read(unsigned int *ui)
{
	return read(ui, sizeof(unsigned int));
}

int FileIO::read(int *i)
{
	return read(i, sizeof(int));
}

int FileIO::read(unsigned long *ul)
{
	return read(ul, sizeof(unsigned long));
}

int FileIO::read(long *l)
{
	return read(l, sizeof(long));
}

int FileIO::read(float *f)
{
	return read(f, sizeof(float));
}

int FileIO::read(double *d)
{
	return read(d, sizeof(double));
}

int FileIO::write(const void *buf, int size)
{
	assert( isWriteEnabled() && "File was not opened in write mode");

#if defined (USE_FOPEN)
	FileDesc *fd = ((FileDesc *)user);
	assert(fd->handle!=0);

	int rval = fwrite(buf, 1, size, fd->handle);
	fd->position = fd->position + size;
	return rval;
#elif defined(WIN32)
	FileDesc *fd = ((FileDesc *)user);
	assert(fd->handle!=INVALID_HANDLE_VALUE);

	if(!asyncMode)
	{
		DWORD dwWriteSize = 0;
		if( WriteFile(fd->handle, buf, size, &dwWriteSize, 0) )
			return dwWriteSize;
		else
			return -1;
	}
	else
	{
		memset(&fd->overlapped, 0, sizeof(fd->overlapped));
		if(WriteFile(fd->handle, buf, size, 0, &fd->overlapped))
		{
			debug("File Write Sucessfully\n");
			return size;
		}
		else
		{
			int lastError = GetLastError();
			if(lastError == ERROR_IO_PENDING)
			{
				debug("Info: IO Pending..%d\n", lastError);
				return 0;
			}
			else
			{
				debug("Error: Unhandled Error..%d\n", lastError);
				return -1;
			}
		}
	}
#elif defined(__ANDROID__ )
	FileDesc *fd = ((FileDesc *)user);
	assert(fd->handle!=-1);
    
	if(!asyncMode)
	{
        return ::write(fd->handle, buf, size);
	}
	else
	{
        int rval = ::write(fd->handle, buf, size);
        if(rval>0)
        {
            debug("File Write Sucessfully\n");
            return rval;
        }
        else
        {
			int lastError = errno;
			if(lastError == EWOULDBLOCK)
			{
				debug("Info: IO Pending..%d\n", lastError);
				return 0;
			}
			else
			{
				debug("Error: Unhandled Error..%d\n", lastError);
				return -1;
			}
        }
	}
#elif ( defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) )
	FileDesc *fd = ((FileDesc *)user);
	assert(fd->handle!=-1);
    
	if(!asyncMode)
	{
        return ::write(fd->handle, buf, size);
	}
	else
	{
        int rval = ::write(fd->handle, buf, size);
        if(rval>0)
        {
            debug("File Write Sucessfully\n");
            return rval;
        }
        else
        {
			int lastError = errno;
			if(lastError == EWOULDBLOCK)
			{
				debug("Info: IO Pending..%d\n", lastError);
				return 0;
			}
			else
			{
				debug("Error: Unhandled Error..%d\n", lastError);
				return -1;
			}
        }
	}
#endif
}

int FileIO::write(const unsigned char *uc)
{
	return write(uc, sizeof(unsigned char));
}

int FileIO::write(const char *c)
{
	return write(c, sizeof(char));
}

int FileIO::write(const unsigned short *us)
{
	return write(us, sizeof(unsigned short));
}

int FileIO::write(const short *s)
{
	return write(s, sizeof(short));
}

int FileIO::write(const unsigned int *ui)
{
	return write(ui, sizeof(unsigned int));
}

int FileIO::write(const int *i)
{
	return write(i, sizeof(int));
}

int FileIO::write(const unsigned long *ul)
{
	return write(ul, sizeof(unsigned long));
}

int FileIO::write(const long *l)
{
	return write(l, sizeof(long));
}

int FileIO::write(const float *f)
{
	return write(f, sizeof(float));
}

int FileIO::write(const double *d)
{
	return write(d, sizeof(double));
}

int FileIO::length() const
{
#if defined (USE_FOPEN)
	FileDesc *fd = ((FileDesc *)user);
	assert(fd->handle!=0);

	return fd->length;
#elif defined(WIN32)
	FileDesc *fd = ((FileDesc *)user);
	assert(fd->handle!=INVALID_HANDLE_VALUE);

	return GetFileSize(fd->handle, 0);
#elif defined(__ANDROID__ )
	FileDesc *fd = ((FileDesc *)user);
	assert(fd->handle!=-1);
	
	struct stat info;
	if(stat(path, &info) != 0)
		return 0;
	else
		return info.st_size;
#elif ( defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) )
	FileDesc *fd = ((FileDesc *)user);
	assert(fd->handle!=-1);
	
	struct stat info;
	if(stat(path, &info) != 0)
		return 0;
	else
		return info.st_size;
#endif
}

bool FileIO::exists(const char *path)
{
#if defined (USE_FOPEN)
	FileIO f(path);
	f.open(IO::READ);

	return f.live();
#elif defined(WIN32)
	FileIO f(path);
	f.open(IO::READ);

	return f.live();
#elif defined(__ANDROID__ )
	struct stat info;
	if(stat(path, &info) != 0)
		return false;
	else
		return true;
#elif ( defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) )
	struct stat info;
	if(stat(path, &info) != 0)
		return false;
	else
		return true;
#endif
}

int FileIO::length(const char *path)
{
#if defined (USE_FOPEN)
	FileIO f(path);
	f.open(IO::READ);
    
	return f.length();
#elif defined(WIN32)
	FileIO f(path);
	f.open(IO::READ);
    
	return f.length();
#elif defined(__ANDROID__ )
	struct stat info;
	if(stat(path, &info) != 0)
		return -1;
	else
		return info.st_size;
#elif ( defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) )
	struct stat info;
	if(stat(path, &info) != 0)
		return -1;
	else
		return info.st_size;
#endif
}

bool FileIO::load(const char *path, void *buf, int size, int offset)
{
	FileIO f(path);
	f.open(IO::READ);
	f.seek(BEGIN, offset);

	return f.read(buf, size);
}