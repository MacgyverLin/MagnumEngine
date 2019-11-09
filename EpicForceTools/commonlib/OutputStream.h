///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited			 //
//																 //
// Author : Mac Lin									             //
// Module : EpicForceEngine										 //
// Date   : 19/Aug/2011											 //
//																 //
///////////////////////////////////////////////////////////////////
#ifndef _OutputStream_h_
#define _OutputStream_h_

#include "Stage.h"
#include "FileIO.h"
//#include "GZFileIO.h"
#include "EString.h"
#include "ESystem.h"
#include "Array.h"

namespace EpicForce
{

class OutputStream
{
public:
	OutputStream() {}
	virtual ~OutputStream();
	virtual void write(const bool &data);
	virtual void write(const char &data);
	virtual void write(const unsigned char &data);
	virtual void write(const short &data);
	virtual void write(const unsigned short &data);
	virtual void write(const int &data);
	virtual void write(const unsigned int &data);
	virtual void write(const long &data);
	virtual void write(const unsigned long &data);
	virtual void write(const float &data);
	virtual void write(const double &data);
	virtual void write(const String &str);

	virtual void writeX(const void *src_, int size, bool reverseOrder=false) = 0;
	virtual unsigned int tell() const = 0;
	virtual void skip(int size) = 0;
	virtual bool opened() const = 0;
	virtual void rewind() = 0;

	static bool reverseOrder;
private:
	OutputStream(const OutputStream&);
	OutputStream& operator=(const OutputStream&);
};

class MemOutputStream : public OutputStream
{
public:
	enum
	{
		EXPAND_SIZE = 2048
	};
	MemOutputStream(Vector<unsigned char> &buffer_);
	virtual ~MemOutputStream();

	virtual void writeX(const void *src_, int size, bool reverseOrder=false);
	virtual unsigned int tell() const;
	virtual void skip(int size);
	virtual bool opened() const;
	virtual void rewind();
private:
	MemOutputStream(const MemOutputStream&);
	MemOutputStream& operator=(const MemOutputStream&);

	Vector<unsigned char>	&buffer;
	int						position;
};

class FileOutputStream : public OutputStream
{
public:
	FileOutputStream(const char *path_);
	virtual ~FileOutputStream();

	virtual void writeX(const void *src_, int size, bool reverseOrder=false);
	virtual unsigned int tell() const;
	virtual void skip(int size);
	virtual bool opened() const;
	virtual void rewind();
private:
	FileOutputStream(const FileOutputStream&);
	FileOutputStream& operator=(const FileOutputStream&);

	FileIO file;
};

template<class T> inline OutputStream& operator<<(OutputStream &os, const T &data)
{
	data.write(os);
	return os;
}

inline OutputStream& operator<<(OutputStream &os, const bool &data)
{
	os.write(data);
	return os;
}

inline OutputStream& operator<<(OutputStream &os, const char &data)
{
	os.write(data);
	return os;
}

inline OutputStream& operator<<(OutputStream &os, const unsigned char &data)
{
	os.write(data);
	return os;
}

inline OutputStream& operator<<(OutputStream &os, const short &data)
{
	os.write(data);
	return os;
}

inline OutputStream& operator<<(OutputStream &os, const unsigned short &data)
{
	os.write(data);
	return os;
}

inline OutputStream& operator<<(OutputStream &os, const int &data)
{
	os.write(data);
	return os;
}

inline OutputStream& operator<<(OutputStream &os, const unsigned int &data)
{
	os.write(data);
	return os;
}

inline OutputStream& operator<<(OutputStream &os, const long &data)
{
	os.write(data);
	return os;
}

inline OutputStream& operator<<(OutputStream &os, const unsigned long &data)
{
	os.write(data);
	return os;
}

inline OutputStream& operator<<(OutputStream &os, const float &data)
{
	os.write(data);
	return os;
} 

inline OutputStream& operator<<(OutputStream &os, const double &data)
{
	os.write(data);
	return os;
} 

inline OutputStream& operator<<(OutputStream &os, const String &data)
{
	os.write(data);
	return os;
}

template<class T> inline OutputStream& operator<<(OutputStream &os, const Vector<T> &data)
{
	int len = data.length();
	os << len;
	for(int i=0; i<len; i++)
		os << data[i];

	return os;
}

template<class T> class VectorWrite
{
public:
	VectorWrite(const Vector<T> &vector_)
		: vector(vector_)
	{
	}

	void write(OutputStream &os) const
	{
		int length = vector.length();
		os << length;

		for(int i=0; i<vector.length(); i++)
			os << vector[i];
	}

	int getSize() const
	{
		return vector.length();
	}
private:
	const Vector<T> &vector;
};

template<class T> class ArrayWrite
{
public:
	ArrayWrite(T* &data_, int size_)
		: data(data_), size(size_)
	{
	}

	void write(OutputStream &os)
	{
		os << size;
		for (int i=0; i<size; i++)
		{
			os << data[i];
		}
	}

	int getSize() const
	{
		return size;
	}

private:
	T* &data;
	int size;
};

};

#endif