///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _FileIO_h_
#define _FileIO_h_

#include "EString.h"
#include "IO.h"

namespace Magnum
{
	class FileIO : public IO
	{
	public:
		FileIO(const char *path_);
		virtual ~FileIO();

		virtual bool open(AccessMode mode);
		virtual bool openForAsync(AccessMode mode);
		virtual bool isAsyncFinished();
		virtual void waitAsyncFinished();
		virtual bool close();
		virtual bool live() const;

		virtual int tell() const;
		virtual int seek(SeekDef from, int offset = 0);

		virtual int read(void *buf, int size);
		virtual int read(unsigned char *uc);
		virtual int read(char *c);
		virtual int read(unsigned short *us);
		virtual int read(short *s);
		virtual int read(unsigned int *ui);
		virtual int read(int *i);
		virtual int read(unsigned long *ui);
		virtual int read(long *i);
		virtual int read(float *f);
		virtual int read(double *d);

		virtual int write(const void *buf, int size);
		virtual int write(const unsigned char *uc);
		virtual int write(const char *c);
		virtual int write(const unsigned short *us);
		virtual int write(const short *s);
		virtual int write(const unsigned int *ui);
		virtual int write(const int *i);
		virtual int write(const unsigned long *ui);
		virtual int write(const long *i);
		virtual int write(const float *f);
		virtual int write(const double *d);

		virtual int length() const;

		static bool exists(const char *path);
		static int length(const char *path);
		static bool load(const char *path, void *data, int size, int offset);
	private: 
		void *user;
	};
}

#endif