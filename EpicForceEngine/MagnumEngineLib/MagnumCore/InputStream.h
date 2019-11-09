///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _InputStream_h_
#define _InputStream_h_

#include "Stage.h"
#include "FileIO.h"
//#include "GZFileIO.h"
#include "EString.h"
#include "Array.h"

namespace Magnum
{

/**
* InputStream. The base class of All InputStream.
*/
class InputStream
{
public:
	/**
	* InputStream Constructor.
	* To Construct the InputStream.
	*/
	InputStream() {}

	/**
	* InputStream Destructor.
	* To Destruct the InputStream.
	*/
	virtual ~InputStream();

	/**
	* read function for bool data
	* @param data, bool, the data is read from the inputstream and return in this data
	*/
	virtual void read(bool &data);

	/**
	* read function for char data
	* @param data, char, the data is read from the inputstream and return in this data
	*/
	virtual void read(char &data);

	/**
	* read function for unsigned char data
	* @param data, unsigned char, the data is read from the inputstream and return in this data
	*/
	virtual void read(unsigned char &data);

	/**
	* read function for short char data
	* @param data, short, the data is read from the inputstream and return in this data
	*/
	virtual void read(short &data);

	/**
	* read function for unsigned short char data
	* @param data, unsigned short, the data is read from the inputstream and return in this data
	*/
	virtual void read(unsigned short &data);

	/**
	* read function for int char data
	* @param data, int, the data is read from the inputstream and return in this data
	*/
	virtual void read(int &data);

	/**
	* read function for unsigned int char data
	* @param data, unsigned int, the data is read from the inputstream and return in this data
	*/
	virtual void read(unsigned int &data);

	/**
	* read function for long char data
	* @param data, long, the data is read from the inputstream and return in this data
	*/
	virtual void read(long &data);

	/**
	* read function for unsigned long char data
	* @param data, unsigned long, the data is read from the inputstream and return in this data
	*/
	virtual void read(unsigned long &data);

	/**
	* read function for float char data
	* @param data, float, the data is read from the inputstream and return in this data
	*/
	virtual void read(float &data);

	/**
	* read function for double char data
	* @param data, double, the data is read from the inputstream and return in this data
	*/
	virtual void read(double &data);

	/**
	* read function for String char data
	* @param data, String, the data is read from the inputstream and return in this data
	*/
	virtual void read(String &str);

	/**
	* read function buffer data
	* @param buffer, void *, the data is read from the inputstream and fill in this buffer
	* @param size, int, the number of byte to be read from the input steam
	* @param reverseOrder, true , for big endian system
	*					   false, for little endian system
	*/
	virtual void readX(void *buffer, int size, bool reverseOrder=false) = 0;

	/**
	* skip data from buffer
	* @param size, int, the number of byte to be skipped
	*/
	virtual void skip(int size) = 0;

	/**
	* Get the length of buffer data
	* @return unsigned int, the length of InputStream
	*/
	virtual unsigned int length() = 0;

	/**
	* Tell the current read position 
	* @return unsigned int, the current read position 
	*/
	virtual unsigned int tell() = 0;

	/**
	* Check if the stream is opened
	* @return true, stream is opened, else stream is closed
	*/
	virtual bool opened() = 0;

	/**
	* Rewind the stream, the stream current read position  will be reset to 0 by this function
	* @return true, stream is opened, else stream is closed
	*/
	virtual void rewind() = 0;

	static bool reverseOrder;
private:
	InputStream(const InputStream&);
	InputStream& operator=(const InputStream&);
};	//class InputStream

/**
* InputStream. The class is an InputStream for a memory location
*/
class MemInputStream : public InputStream
{
public:
	/**
	* MemInputStream Constructor.
	* To Construct the MemInputStream.
	* @param data_, unsigned char *, a pointer to a memory chunk to read from
	* @param length_, unsigned int, the length of the data trunk
	*/
	MemInputStream(const unsigned char *data_, const unsigned int length_);

	/**
	* MemInputStream Destructor.
	* To Destruct MemInputStream
	*/
	virtual ~MemInputStream();

	/**
	* read function buffer data
	* @param buffer, void *, the data is read from the inputstream and fill in this buffer
	* @param size, int, the number of byte to be read from the input steam
	* @param reverseOrder, true , for big endian system
	*					   false, for little endian system
	*/
	virtual void readX(void *buffer, int size, bool reverseOrder=false);

	/**
	* skip data from buffer
	* @param size, int, the number of byte to be skipped
	*/
	virtual void skip(int size);

	/**
	* Get the length of buffer data
	* @return unsigned int, the length of InputStream
	*/
	virtual unsigned int length();

	/**
	* Tell the current read position 
	* @return unsigned int, the current read position 
	*/
	virtual unsigned int tell();

	/**
	* Check if the stream is opened
	* @return true, stream is opened, else stream is closed
	*/
	virtual bool opened();

	/**
	* Rewind the stream, the stream current read position  will be reset to 0 by this function
	* @return true, stream is opened, else stream is closed
	*/
	virtual void rewind();
private:
	MemInputStream(const MemInputStream&);
	MemInputStream& operator=(const MemInputStream&);

	const unsigned char *data_head;
	const unsigned char *data;
	unsigned int current;
	unsigned int len;
};

/**
* FileInputStream. The class is an InputStream for a file stream
*/
class FileInputStream : public InputStream
{
public:
	/**
	* FileInputStream Constructor.
	* To Construct the FileInputStream.
	* @param path_ , filename for the file of FileInputStream
	*/
	FileInputStream(const char *path_);

	/**
	* FileInputStream Destructor.
	* To Destruct FileInputStream and close the file
	*/
	virtual ~FileInputStream();

	/**
	* read function buffer data
	* @param buffer, void *, the data is read from the inputstream and fill in this buffer
	* @param size, int, the number of byte to be read from the input steam
	* @param reverseOrder, true , for big endian system
	*					   false, for little endian system
	*/
	virtual void readX(void *buffer, int size, bool reverseOrder=false);

	/**
	* skip data from buffer
	* @param size, int, the number of byte to be skipped
	*/
	virtual void skip(int size);

	/**
	* Get the length of buffer data
	* @return unsigned int, the length of InputStream
	*/
	virtual unsigned int length();

	/**
	* Tell the current read position 
	* @return unsigned int, the current read position 
	*/
	virtual unsigned int tell();

	/**
	* Check if the stream is opened
	* @return true, stream is opened, else stream is closed
	*/
	virtual bool opened();

	/**
	* Rewind the stream, the stream current read position  will be reset to 0 by this function
	* @return true, stream is opened, else stream is closed
	*/
	virtual void rewind();
private:
	FileInputStream(const FileInputStream&);
	FileInputStream& operator=(const FileInputStream&);

	FileIO file;
};

#if 0
class GZMemInputStream : public InputStream
{
public:
	GZMemInputStream(const unsigned char *data_, const unsigned int length_);
	virtual ~GZMemInputStream();

	/**
	* read function buffer data
	* @param buffer, void *, the data is read from the inputstream and fill in this buffer
	* @param size, int, the number of byte to be read from the input steam
	* @param reverseOrder, true , for big endian system
	*					   false, for little endian system
	*/
	/**
	* skip data from buffer
	* @param size, int, the number of byte to be skipped
	*/
	/**
	* Get the length of buffer data
	* @return unsigned int, the length of InputStream
	*/
	/**
	* Tell the current read position 
	* @return unsigned int, the current read position 
	*/
	/**
	* Check if the stream is opened
	* @return true, stream is opened, else stream is closed
	*/
	/**
	* Rewind the stream, the stream current read position  will be reset to 0 by this function
	* @return true, stream is opened, else stream is closed
	*/
	virtual void readX(void *buffer, int size, bool reverseOrder=false);
	virtual void skip(int size);
	virtual unsigned int length();
	virtual unsigned int tell();
	virtual bool opened();
	virtual void rewind();
private:
	GZMemInputStream(const GZMemInputStream&);
	GZMemInputStream& operator=(const GZMemInputStream&);

	const unsigned char *data_head;
	const unsigned char *data;
	unsigned int current;
	unsigned int len;
};

class GZFileInputStream : public InputStream
{
public:
	GZFileInputStream(const char *path_);
	virtual ~GZFileInputStream();

	/**
	* read function buffer data
	* @param buffer, void *, the data is read from the inputstream and fill in this buffer
	* @param size, int, the number of byte to be read from the input steam
	* @param reverseOrder, true , for big endian system
	*					   false, for little endian system
	*/
	/**
	* skip data from buffer
	* @param size, int, the number of byte to be skipped
	*/
	/**
	* Get the length of buffer data
	* @return unsigned int, the length of InputStream
	*/
	/**
	* Tell the current read position 
	* @return unsigned int, the current read position 
	*/
	/**
	* Check if the stream is opened
	* @return true, stream is opened, else stream is closed
	*/
	/**
	* Rewind the stream, the stream current read position  will be reset to 0 by this function
	* @return true, stream is opened, else stream is closed
	*/
	virtual void readX(void *buffer, int size, bool reverseOrder=false);
	virtual void skip(int size);
	virtual unsigned int length();
	virtual unsigned int tell();
	virtual bool opened();
	virtual void rewind();
private:
	GZFileInputStream(const GZFileInputStream&);
	GZFileInputStream& operator=(const GZFileInputStream&);

	GZFileIO file;
};
#endif

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

/**
* VectorRead. A template class for serialization of vector of Type T
*/
template<class T> class VectorRead
{
public:
	/**
	* VectorRead Constructor.
	* To Construct the VectorRead.
	* @param vector_ , the vector of class T, the input stream will fill up this vector_
	*/
	VectorRead( Vector<T> &vector_)
		: vector(vector_)
	{
	}

	/**
	* read function.
	* Input Stream will call this function when VectorRead is serializing
	* @param is , the InputStream, the input stream.
	*/
	void read(InputStream &is)
	{
		int length;
		is >> length;

		vector.resize(length);
		for(int i=0; i<vector.length(); i++)
			is >> vector[i];
	}

	/**
	* getSize function.
	* @return int, size of the vector 
	*/
	int getSize() const
	{
		return vector.length();
	}
private:
	Vector<T> &vector;
};

/**
* ArrayRead. A template class for serialization of array of Type T
*/
template<class T> class ArrayRead
{
public:
	/**
	* ArrayRead Constructor.
	* To Construct the ArrayRead.
	* @param data_ , the vector of class T, the input stream will fill up this data_
	*/
	ArrayRead(T* &data_)
		: data(data_)
	{
	}

	/**
	* read function.
	* Input Stream will call this function when ArrayRead is serializing
	* @param is , the InputStream, the input stream.
	*/
	void read(InputStream &is)
	{
		is >> size;
		data = new T[size];
		for (int i=0; i<size; i++)
		{
			is >> data[i];
		}
	}

	/**
	* getSize function.
	* @return int, size of the array 
	*/
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