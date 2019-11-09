///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited			 //
//																 //
// Author : Mac Lin									             //
// Module : EpicForceEngine										 //
// Date   : 19/Aug/2011											 //
//																 //
///////////////////////////////////////////////////////////////////
#ifndef _InputStream_h_
#define _InputStream_h_

#include "Stage.h"
#include "FileIO.h"
#include "EString.h"
#include "Array.h"

namespace EpicForce
{

class InputStream
{
public:
	InputStream() {}
	virtual ~InputStream();
	virtual void read(bool &data);
	virtual void read(char &data);
	virtual void read(unsigned char &data);
	virtual void read(short &data);
	virtual void read(unsigned short &data);
	virtual void read(int &data);
	virtual void read(unsigned int &data);
	virtual void read(long &data);
	virtual void read(unsigned long &data);
	virtual void read(float &data);
	virtual void read(double &data);
	virtual void read(String &str);

	virtual void readX(void *buffer, int size, bool reverseOrder=false) = 0;
	virtual void skip(int size) = 0;
	virtual unsigned int length() = 0;
	virtual unsigned int tell() = 0;
	virtual bool opened() = 0;
	virtual void rewind() = 0;

	static bool reverseOrder;
private:
	InputStream(const InputStream&);
	InputStream& operator=(const InputStream&);
};	//class InputStream

class MemInputStream : public InputStream
{
public:
	MemInputStream(const unsigned char *data_, const unsigned int length_);
	virtual ~MemInputStream();

	virtual void readX(void *buffer, int size, bool reverseOrder=false);
	virtual void skip(int size);
	virtual unsigned int length();
	virtual unsigned int tell();
	virtual bool opened();
	virtual void rewind();
private:
	MemInputStream(const MemInputStream&);
	MemInputStream& operator=(const MemInputStream&);

	const unsigned char *data_head;
	const unsigned char *data;
	unsigned int current;
	unsigned int len;
};

class FileInputStream : public InputStream
{
public:
	FileInputStream(const char *path_);
	virtual ~FileInputStream();

	virtual void readX(void *buffer, int size, bool reverseOrder=false);
	virtual void skip(int size);
	virtual unsigned int length();
	virtual unsigned int tell();
	virtual bool opened();
	virtual void rewind();
private:
	FileInputStream(const FileInputStream&);
	FileInputStream& operator=(const FileInputStream&);

	FileIO file;
};	//class FileInputStream

template<class T> inline InputStream& operator>>(InputStream &is, T &data)
{
	data.read(is);
	return is;
}

inline InputStream& operator>>(InputStream &is, bool &data)
{
	is.read(data);
	return is;
}

inline InputStream& operator>>(InputStream &is, char &data)
{
	is.read(data);
	return is;
}

inline InputStream& operator>>(InputStream &is, unsigned char &data)
{
	is.read(data);
	return is;
}

inline InputStream& operator>>(InputStream &is, short &data)
{
	is.read(data);
	return is;
}

inline InputStream& operator>>(InputStream &is, unsigned short &data)
{
	is.read(data);
	return is;
}

inline InputStream& operator>>(InputStream &is, int &data)
{
	is.read(data);
	return is;
}

inline InputStream& operator>>(InputStream &is, unsigned int &data)
{
	is.read(data);
	return is;
}

inline InputStream& operator>>(InputStream &is, long &data)
{
	is.read(data);
	return is;
}

inline InputStream& operator>>(InputStream &is, unsigned long &data)
{
	is.read(data);
	return is;
}

inline InputStream& operator>>(InputStream &is, float &data)
{
	is.read(data);
	return is;
} 

inline InputStream& operator>>(InputStream &is, double &data)
{
	is.read(data);
	return is;
} 

inline InputStream& operator>>(InputStream &is, String &data)
{
	is.read(data);
	return is;
}

template<class T> inline InputStream& operator>>(InputStream &is, Vector<T> &data)
{
	int len;
	is >> len;
	data.resize(len);

	for(int i=0; i<len; i++)
		is >> data[i];

	return is;
}

template<class T> class VectorRead
{
public:
	VectorRead( Vector<T> &vector_)
		: vector(vector_)
	{
	}

	void read(InputStream &is)
	{
		int length;
		is >> length;

		vector.resize(length);
		for(int i=0; i<vector.length(); i++)
			is >> vector[i];
	}

	int getSize() const
	{
		return vector.length();
	}

private:
	Vector<T> &vector;
};

template<class T> class ArrayRead
{
public:
	ArrayRead(T* &data_)
		: data(data_)
	{
	}

	void read(InputStream &is)
	{
		is >> size;
		data = new T[size];
		for (int i=0; i<size; i++)
		{
			is >> data[i];
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