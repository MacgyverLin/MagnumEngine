///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Stage.h"
#include "InputStream.h"
#include <zlib.h>
using namespace Magnum;

bool InputStream::reverseOrder = false;

InputStream::~InputStream()
{
}

void InputStream::read(bool &data)
{
	unsigned char c;
	read(c);
	data=(c!=0);
}

void InputStream::read(String &str)
{
	int size;
	read(size);
//	assert(size<512);
	if(!size)
		str="";
	else
	{ 
		str.grow(size);
		readX(str.buffer(),size, false);
		str.reset(size);
	}
}

void InputStream::read(char &data)
{
	readX(&data, sizeof(char), reverseOrder);
}

void InputStream::read(unsigned char &data)
{
	readX(&data, sizeof(unsigned char), reverseOrder);
}

void InputStream::read(short &data)
{
	readX(&data, sizeof(short), reverseOrder);
}

void InputStream::read(unsigned short &data)
{
	readX(&data, sizeof(unsigned short), reverseOrder);
}

void InputStream::read(int &data)
{
	readX(&data, sizeof(int), reverseOrder);
}

void InputStream::read(unsigned int &data)
{
	readX(&data, sizeof(unsigned int), reverseOrder);
}

void InputStream::read(long &data)
{
	readX(&data, sizeof(long), reverseOrder);
}

void InputStream::read(unsigned long &data)
{
	readX(&data, sizeof(unsigned long), reverseOrder);
}

void InputStream::read(float &data)
{
	readX(&data, sizeof(float), reverseOrder);
}

void InputStream::read(double &data)
{
	readX(&data, sizeof(double), reverseOrder);
}

//void InputStream::read(fix &data)
//{
//	//readX(&data, sizeof(fix));
//	float f;
//	readX(&f, sizeof(float));
//	data = f;
//}

///////////////////////////////////////////////////////////////////////////////////////
MemInputStream::MemInputStream(const unsigned char *data_, const unsigned int len_)
: data_head(data_)
, data(data_)
, len(len_)
, current(0)
{
}

MemInputStream::~MemInputStream()
{
}

void MemInputStream::readX(void *buffer, int size, bool reverseOrder)
{
	memcpy(buffer, data, size);
	data    += size;
	current += size;
}

void MemInputStream::skip(int size)
{
	data    += size;
	current += size;
}

unsigned int MemInputStream::length()
{
	return len;
}

unsigned int MemInputStream::tell()
{
	return current;
}

bool MemInputStream::opened()
{
	return true;
}

void MemInputStream::rewind()
{
	data = data_head;
	current = 0;
}

///////////////////////////////////////////////////////////////////////////////////////
FileInputStream::FileInputStream(const char *path_) 
: file(path_)
{
	file.open(IO::READ);
}

FileInputStream::~FileInputStream()
{
	file.close();
}

void FileInputStream::readX(void *buffer, int size, bool reverseOrder)
{
	if(reverseOrder)
	{
		char *buf = (char *)buffer;
		for(int i=0; i<size; i++)
			file.read(&buf[size-1-i], 1);
	}		
	else
	{
		file.read(buffer, size);
	}
}

void FileInputStream::skip(int size)
{
	file.seek(IO::CURRENT, size);
}

unsigned int FileInputStream::length()
{
	return file.length();
}

unsigned int FileInputStream::tell()
{
	assert(0 && "TODO");
	return 0;
}

bool FileInputStream::opened()
{
	return file.live();
}

void FileInputStream::rewind()
{
	file.seek(IO::BEGIN, 0);
}

///////////////////////////////////////////////////////////////////////////////////////
#if 0
GZMemInputStream::GZMemInputStream(const unsigned char *data_, const unsigned int len_)
: data_head(data_)
, data(data_)
, len(len_)
, current(0)
{
}

GZMemInputStream::~GZMemInputStream()
{
}

void GZMemInputStream::readX(void *buffer, int size, bool reverseOrder)
{
	memcpy(buffer, data, size);
	data    += size;
	current += size;
}

void GZMemInputStream::skip(int size)
{
	data    += size;
	current += size;
}

unsigned int GZMemInputStream::length()
{
	return len;
}

unsigned int GZMemInputStream::tell()
{
	return current;
}

bool GZMemInputStream::opened()
{
	return true;
}

void GZMemInputStream::rewind()
{
	data	= data_head;
	current = 0;
}

///////////////////////////////////////////////////////////////////////////////////////
GZFileInputStream::GZFileInputStream(const char *path_) 
: file(path_)
{
	assert( file.open(IO::READ) && "Error: cannot open file for reading");
}

GZFileInputStream::~GZFileInputStream()
{
	file.close();
}

void GZFileInputStream::readX(void *buffer, int size, bool reverseOrder)
{
	if(reverseOrder)
	{
		char *buf = (char *)buffer;
		for(int i=0; i<size; i++)
			file.read(&buf[size-1-i], 1);
	}		
	else
	{
		file.read(buffer, size);
	}
}

void GZFileInputStream::skip(int size)
{
	file.seek(IO::CURRENT, size);
}

unsigned int GZFileInputStream::length()
{
	return file.length();
}

unsigned int GZFileInputStream::tell()
{
	assert(0 && "TODO");
	return 0;
}

bool GZFileInputStream::opened()
{
	return file.live();
}

void GZFileInputStream::rewind()
{
	file.seek(IO::BEGIN, 0);
}
#endif