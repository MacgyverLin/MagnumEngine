///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _IO_h_
#define _IO_h_

#include "EString.h"

namespace EpicForce
{
	class IO
	{
	public:
		enum SeekDef
		{
			BEGIN	=	0,
			CURRENT		,
			END
		};

		enum AccessMode
		{
			READ	= 0x01,
			WRITE	= 0x02
		};

		IO(const char *path_);
		virtual ~IO();

		virtual bool open(AccessMode mode);
		virtual bool openForAsync(AccessMode mode);
		virtual bool isAsyncFinished()					= 0;
		virtual void waitAsyncFinished()				= 0;
		virtual bool close()							= 0;
		virtual bool live() const						= 0;

		virtual int tell() const						= 0;
		virtual int seek(SeekDef from, int offset = 0)	= 0;

		virtual int read(void *buf, int size)			= 0;
		virtual int read(unsigned char *uc)				= 0;
		virtual int read(char *c)						= 0;
		virtual int read(unsigned short *us)			= 0;
		virtual int read(short *s)						= 0;
		virtual int read(unsigned int *ui)				= 0;
		virtual int read(int *i)						= 0;
		virtual int read(unsigned long *ui)				= 0;
		virtual int read(long *i)						= 0;
		virtual int read(float *f)						= 0;
		virtual int read(double *d)						= 0;

		virtual int write(const void *buf, int size)		= 0;
		virtual int write(const unsigned char *uc)			= 0;
		virtual int write(const char *c)					= 0;
		virtual int write(const unsigned short *us)			= 0;
		virtual int write(const short *s)					= 0;
		virtual int write(const unsigned int *ui)			= 0;
		virtual int write(const int *i)						= 0;
		virtual int write(const unsigned long *ui)			= 0;
		virtual int write(const long *i)					= 0;
		virtual int write(const float *f)					= 0;
		virtual int write(const double *d)					= 0;

		virtual int length() const							= 0;

		bool isReadEnabled() const;
		bool isWriteEnabled() const;
		const char *getPath() const;
	private:

	protected: 
		String path;
		AccessMode accessMode;
		bool asyncMode;
	};
}

#endif