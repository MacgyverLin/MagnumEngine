///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Stage.h"
#include "OutputStream.h"
#include <zlib.h>
using namespace Magnum;

bool OutputStream::reverseOrder = false;
	
OutputStream::~OutputStream()
{
}

void OutputStream::write(const bool &data)
{
	unsigned char c;
	if(data)
		c = 1;
	else
		c = 0;
	write(c);
}

void OutputStream::write(const String &str)
{
	int size = str.length();
	write(size);
	writeX(str.text(),size, false);
}

void OutputStream::write(const char &data)
{
	writeX(&data, sizeof(char), reverseOrder);
}

void OutputStream::write(const unsigned char &data)
{
	writeX(&data, sizeof(unsigned char), reverseOrder);
}

void OutputStream::write(const short &data)
{
	writeX(&data, sizeof(short), reverseOrder);
}

void OutputStream::write(const unsigned short &data)
{
	writeX(&data, sizeof(unsigned short), reverseOrder);
}

void OutputStream::write(const int &data)
{
	writeX(&data, sizeof(int), reverseOrder);
}

void OutputStream::write(const unsigned int &data)
{
	writeX(&data, sizeof(unsigned int), reverseOrder);
}

void OutputStream::write(const long &data)
{
	writeX(&data, sizeof(long), reverseOrder);
}

void OutputStream::write(const unsigned long &data)
{
	writeX(&data, sizeof(unsigned long), reverseOrder);
}

void OutputStream::write(const float &data)
{
	writeX(&data, sizeof(float), reverseOrder);
}

void OutputStream::write(const double &data)
{
	writeX(&data, sizeof(double), reverseOrder);
}

///////////////////////////////////////////////////////////////////////////////////////
MemOutputStream::MemOutputStream(Vector<unsigned char> &buffer_)
: buffer(buffer_)
, position(0)
{
}

MemOutputStream::~MemOutputStream()
{
}

void MemOutputStream::writeX(const void *src_, int size, bool reverseOrder)
{
	if(buffer.length() - position < size)
	{
		int expandSize = EXPAND_SIZE;
		if(expandSize<size)
			expandSize=size;
		
		buffer.resize(buffer.length()+expandSize);
	}

	if(reverseOrder)
	{
		char *buf = (char *)src_;
		for(int i=0; i<size; i++)
			buffer[position+i] = buf[position+(size-1-i)];

		position += size;
	}
	else
	{
		System::memcpy(&buffer[position], src_, size);
		position += size;
	}
}

unsigned int MemOutputStream::tell() const
{
	return position;
}

void MemOutputStream::skip(int size)
{
	if(buffer.length() - position < size)
	{
		int expandSize = EXPAND_SIZE;
		if(expandSize<size)
			expandSize=size;
		
		buffer.resize(buffer.length()+expandSize);
	}

	System::memset(&buffer[position], 0, size);
	position += size;
}

bool MemOutputStream::opened() const
{
	return true;
}

void MemOutputStream::rewind()
{
	buffer.clear();
	position = 0;
}

///////////////////////////////////////////////////////////////////////////////////////
FileOutputStream::FileOutputStream(const char *path_) 
: file(path_)
{
	assert( file.open(IO::WRITE) && "Error: cannot open file for writing");
}

FileOutputStream::~FileOutputStream()
{
	file.close();
}

void FileOutputStream::writeX(const void *src_, int size, bool reverseOrder)
{
	if(reverseOrder)
	{
		char *buf = (char *)src_;
		for(int i=0; i<size; i++)
			file.write(&buf[size-1-i], 1);
	}		
	else
	{
		file.write(src_, size);
	}
}

void FileOutputStream::skip(int size)
{
	char c = 0;
	for(int i=0; i<size; i++)
		file.write(&c);
}

unsigned int FileOutputStream::tell() const
{
	return file.tell();
}

bool FileOutputStream::opened() const
{
	return file.live();
}

void FileOutputStream::rewind()
{
	file.seek(IO::BEGIN, 0);
}

#define CHECK_ERR(err, msg) { \
    if (err != Z_OK) { \
        fprintf(stderr, "%s error: %d\n", msg, err); \
        exit(1); \
    } \
}

#if 0
///////////////////////////////////////////////////////////////////////////////////////
GZMemOutputStream::GZMemOutputStream(Vector<char> &buffer_)
: buffer(buffer_)
, position(0)
, handle(0)
, level(Z_DEFAULT_COMPRESSION)
{
	handle = new z_stream();
	z_stream *stream = (z_stream*)handle;
	assert(stream);

    stream->zalloc	= 0;
    stream->zfree	= 0;
    stream->opaque	= (voidpf)0;

	int err;
	err = deflateInit(stream, level);
    CHECK_ERR(err, "deflateInit");
	err = deflateParams(stream, level, Z_FILTERED);
	CHECK_ERR(err, "deflateParams");
}

GZMemOutputStream::~GZMemOutputStream()
{
	z_stream *stream = (z_stream*)handle;
	assert(stream);

	int err = deflate(stream, Z_FINISH);
    if (err != Z_STREAM_END) 
	{
        debug("deflate should report Z_STREAM_END\n");
        assert(0);
    }
    err = deflateEnd(stream);

	delete stream;
	handle = 0;
}

void GZMemOutputStream::writeX(const void *src_, int size, bool reverseOrder)
{
	if(buffer.length() - position < size)
	{
		int expandSize = EXPAND_SIZE;
		if(expandSize<size)
			expandSize=size;
		
		buffer.resize(buffer.length()+expandSize);
	}

	z_stream *stream = (z_stream*)handle;
	assert(stream);

	if(reverseOrder)
	{
		assert(0);
		/*
		char *buf = (char *)src_;
		for(int i=0; i<size; i++)
			buffer[position+i] = buf[position+(size-1-i)];

		position += size;
		*/
	}
	else
	{
		stream->next_out	= (unsigned char *)&buffer[position];
		stream->avail_out	= buffer.length() - position;
		int err = deflate(stream, Z_FINISH);
		CHECK_ERR(err, "deflate");
		if(stream->avail_in != 0) 
		{
			debug("deflate not greedy\n");
			assert(0);
		}
    }
}

unsigned int GZMemOutputStream::tell() const
{
	return position;
}

void GZMemOutputStream::skip(int size)
{
	if(buffer.length() - position < size)
	{
		int expandSize = EXPAND_SIZE;
		if(expandSize<size)
			expandSize=size;
		
		buffer.resize(buffer.length()+expandSize);
	}

	System::memset(&buffer[position], 0, size);
	position += size;
}

bool GZMemOutputStream::opened() const
{
	return true;
}

void GZMemOutputStream::rewind()
{
	buffer.clear();
	position = 0;
}

void GZMemOutputStream::setCompressionLevel(int level_)
{
	level = level_;
}

int GZMemOutputStream::getCompressionLevel() const
{
	return level;
}

///////////////////////////////////////////////////////////////////////////////////////
GZFileOutputStream::GZFileOutputStream(const char *path_) 
: file(path_)
{
	assert( file.open(IO::WRITE) && "Error: cannot open file for writing");
}

GZFileOutputStream::~GZFileOutputStream()
{
	file.close();
}

void GZFileOutputStream::writeX(const void *src_, int size, bool reverseOrder)
{
	if(reverseOrder)
	{
		char *buf = (char *)src_;
		for(int i=0; i<size; i++)
			file.write(&buf[size-1-i], 1);
	}		
	else
	{
		file.write(src_, size);
	}
}

void GZFileOutputStream::skip(int size)
{
	char c = 0;
	for(int i=0; i<size; i++)
		file.write(&c);
}

unsigned int GZFileOutputStream::tell() const
{
	return file.tell();
}

bool GZFileOutputStream::opened() const
{
	return file.live();
}

void GZFileOutputStream::rewind()
{
	file.seek(IO::BEGIN, 0);
}

void GZFileOutputStream::setCompressionLevel(int level)
{
	file.setCompressionLevel(level);
}

int GZFileOutputStream::getCompressionLevel() const
{
	return file.getCompressionLevel();
}
#endif