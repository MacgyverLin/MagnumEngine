///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _OutputStream_h_
#define _OutputStream_h_

#include "Stage.h"
#include "FileIO.h"
//#include "GZFileIO.h"
#include "EString.h"
#include "ESystem.h"
#include "Array.h"

namespace Magnum
{

/**
* OutputStream. The base class of All OutputStream.
*/
class OutputStream
{
public:
	/**
	* OutputStream Constructor.
	* To Construct the OutputStream.
	*/
	OutputStream() {}

	/**
	* OutputStream Destructor.
	* To Destruct OutputStream
	*/
	virtual ~OutputStream();

	/**
	* read function for bool data
	* @param data, bool, the data is read from the inputstream and return in this data
	*/
	virtual void write(const bool &data);

	/**
	* read function for char data
	* @param data, char, the data is read from the inputstream and return in this data
	*/
	virtual void write(const char &data);

	/**
	* read function for unsigned char data
	* @param data, unsigned char, the data is read from the inputstream and return in this data
	*/
	virtual void write(const unsigned char &data);

	/**
	* read function for short char data
	* @param data, short, the data is read from the inputstream and return in this data
	*/
	virtual void write(const short &data);

	/**
	* read function for unsigned short char data
	* @param data, unsigned short, the data is read from the inputstream and return in this data
	*/
	virtual void write(const unsigned short &data);

	/**
	* read function for int char data
	* @param data, int, the data is read from the inputstream and return in this data
	*/
	virtual void write(const int &data);

	/**
	* read function for unsigned int char data
	* @param data, unsigned int, the data is read from the inputstream and return in this data
	*/
	virtual void write(const unsigned int &data);

	/**
	* read function for long char data
	* @param data, long, the data is read from the inputstream and return in this data
	*/
	virtual void write(const long &data);

	/**
	* read function for unsigned long char data
	* @param data, unsigned long, the data is read from the inputstream and return in this data
	*/
	virtual void write(const unsigned long &data);

	/**
	* read function for float char data
	* @param data, float, the data is read from the inputstream and return in this data
	*/
	virtual void write(const float &data);

	/**
	* read function for double char data
	* @param data, double, the data is read from the inputstream and return in this data
	*/
	virtual void write(const double &data);

	/**
	* read function for String char data
	* @param data, String, the data is read from the inputstream and return in this data
	*/
	virtual void write(const String &str);

	/**
	* write function buffer data
	* @param buffer, void *, the data will be written to the stream.
	* @param size, int, the number of byte to be write to the stream
	* @param reverseOrder, true , for big endian system
	*					   false, for little endian system
	*/
	virtual void writeX(const void *src_, int size, bool reverseOrder=false) = 0;
	/**
	* skip data from buffer
	* @param size, int, the number of byte to be skipped
	*/
	virtual void skip(int size) = 0;
	/**
	* Tell the current read position 
	* @return unsigned int, the current read position 
	*/
	virtual unsigned int tell() const = 0;
	/**
	* Check if the stream is opened
	* @return true, stream is opened, else stream is closed
	*/
	virtual bool opened() const = 0;
	/**
	* Rewind the stream, the stream current read position  will be reset to 0 by this function
	* @return true, stream is opened, else stream is closed
	*/
	virtual void rewind() = 0;

	static bool reverseOrder;
private:
	OutputStream(const OutputStream&);
	OutputStream& operator=(const OutputStream&);
};

/**
* MemOutputStream. The class is a OutputStream for a memory location
*/
class MemOutputStream : public OutputStream
{
public:
	enum
	{
		EXPAND_SIZE = 2048
	};

	/**
	* MemOutputStream Constructor.
	* To Construct the MemOutputStream.
	* @param buffer_ a chunk of memory to be read from
	*/
	MemOutputStream(Vector<unsigned char> &buffer_);

	/**
	* MemOutputStream Destructor.
	* To Destruct MemOutputStream
	*/
	virtual ~MemOutputStream();

	/**
	* write function buffer data
	* @param buffer, void *, the data will be written to the stream.
	* @param size, int, the number of byte to be write to the stream
	* @param reverseOrder, true , for big endian system
	*					   false, for little endian system
	*/
	virtual void writeX(const void *src_, int size, bool reverseOrder=false);

	/**
	* skip data from buffer
	* @param size, int, the number of byte to be skipped
	*/
	virtual unsigned int tell() const;

	/**
	* Tell the current read position 
	* @return unsigned int, the current read position 
	*/
	virtual void skip(int size);

	/**
	* Check if the stream is opened
	* @return true, stream is opened, else stream is closed
	*/
	virtual bool opened() const;

	/**
	* Rewind the stream, the stream current read position  will be reset to 0 by this function
	* @return true, stream is opened, else stream is closed
	*/
	virtual void rewind();
private:
	MemOutputStream(const MemOutputStream&);
	MemOutputStream& operator=(const MemOutputStream&);

	Vector<unsigned char>	&buffer;
	int						position;
};

/**
* FileOutputStream. The class is a OutputStream for a file stream
*/
class FileOutputStream : public OutputStream
{
public:
	/**
	* FileOutputStream Constructor.
	* To Construct the FileOutputStream.
	* @param path_ , filename for the file of FileOutputStream
	*/
	FileOutputStream(const char *path_);

	/**
	* FileOutputStream Destructor.
	* To Destruct FileOutputStream and close the file
	*/
	virtual ~FileOutputStream();

	/**
	* write function buffer data
	* @param buffer, void *, the data will be written to the stream.
	* @param size, int, the number of byte to be write to the stream
	* @param reverseOrder, true , for big endian system
	*					   false, for little endian system
	*/
	virtual void writeX(const void *src_, int size, bool reverseOrder=false);

	/**
	* skip data from buffer
	* @param size, int, the number of byte to be skipped
	*/
	virtual unsigned int tell() const;

	/**
	* Tell the current read position 
	* @return unsigned int, the current read position 
	*/
	virtual void skip(int size);

	/**
	* Check if the stream is opened
	* @return true, stream is opened, else stream is closed
	*/
	virtual bool opened() const;

	/**
	* Rewind the stream, the stream current read position  will be reset to 0 by this function
	* @return true, stream is opened, else stream is closed
	*/
	virtual void rewind();
private:
	FileOutputStream(const FileOutputStream&);
	FileOutputStream& operator=(const FileOutputStream&);

	FileIO file;
};

#if 0
class GZMemOutputStream : public OutputStream
{
public:
	enum
	{
		EXPAND_SIZE = 2048
	};
	GZMemOutputStream(Vector<char> &buffer_);
	virtual ~GZMemOutputStream();

	virtual void writeX(const void *src_, int size, bool reverseOrder=false);
	virtual unsigned int tell() const;
	virtual void skip(int size);
	virtual bool opened() const;
	virtual void rewind();
	void setCompressionLevel(int level=-1);
	int getCompressionLevel() const;
private:
	GZMemOutputStream(const GZMemOutputStream&);
	GZMemOutputStream& operator=(const GZMemOutputStream&);

	Vector<char>	&buffer;
	int				position;
	void			*handle;
	int				level;
};

class GZFileOutputStream : public OutputStream
{
public:
	GZFileOutputStream(const char *path_);
	virtual ~GZFileOutputStream();

	virtual void writeX(const void *src_, int size, bool reverseOrder=false);
	virtual unsigned int tell() const;
	virtual void skip(int size);
	virtual bool opened() const;
	virtual void rewind();
	void setCompressionLevel(int level=-1);
	int getCompressionLevel() const;
private:
	GZFileOutputStream(const GZFileOutputStream&);
	GZFileOutputStream& operator=(const GZFileOutputStream&);

	GZFileIO file;
};
#endif

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

/**
* VectorWrite. A template class for serialization of vector of Type T
*/
template<class T> class VectorWrite
{
public:
	/**
	* VectorWrite Constructor.
	* To VectorWrite the VectorRead.
	* @param vector_ , the vector of class T, the outputstream will fill up this vector_
	*/
	VectorWrite(const Vector<T> &vector_)
	: vector(vector_)
	{
	}

	/**
	* write function.
	* OutputStream will call this function when VectorWrite is serializing
	* @param os , the OutputStream, the OutputStream.
	*/
	void write(OutputStream &os) const
	{
		int length = vector.length();
		os << length;

		for(int i=0; i<vector.length(); i++)
			os << vector[i];
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
	const Vector<T> &vector;
};

/**
* ArrayWrite. A template class for serialization of vector of Type T
*/
template<class T> class ArrayWrite
{
public:
	/**
	* ArrayWrite Constructor.
	* To VectorWrite the VectorRead.
	* @param vector_ , the vector of class T, the outputstream will fill up this vector_
	*/
	ArrayWrite(T* &data_, int size_)
	: data(data_), size(size_)
	{
	}

	/**
	* write function.
	* OutputStream will call this function when ArrayWrite is serializing
	* @param os , the OutputStream, the OutputStream.
	*/
	void write(OutputStream &os)
	{
		os << size;
		for (int i=0; i<size; i++)
		{
			os << data[i];
		}
	}

	/**
	* getSize function.
	* @return int, size of the vector 
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