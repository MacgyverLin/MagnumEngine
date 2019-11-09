///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _ResourcePath_h_
#define _ResourcePath_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "String.h"

namespace Magnum
{

/**
* ResourcePath. The basic data type for Resource Path
*/
class ResourcePath
{
public:
	/**
	* ResourcePath Constructor.
	* To Construct the ResourcePath.
	* @param extension_ the extension of the Path
	*/
	ResourcePath(const char *extension_="default");

	/**
	* ResourcePath Constructor.
	* To Construct the ResourcePath.
	* @param filename_ the name of the Path
	* @param extension_ the extension of the Path
	*/
	ResourcePath(const char *filename_, const char *extension_);

	/**
	* ResourcePath Copy Constructor.
	* @param resourcePath_ the ResourcePath
	*/
	ResourcePath(const ResourcePath &resourcePath_);

	/**
	* ResourcePath assign operator
	* @param resourcePath_ the ResourcePath
	*/
	ResourcePath &operator = (const ResourcePath &resourcePath_);

	/**
	* ResourcePath Destructor.
	* To Destruct ResourcePath
	*/
	~ResourcePath();

	/**
	* Get the filename of the ResourcePath.
	* @return String, the filename of the Path
	*/
	const String &getPath() const;

	/**
	* Set the filename of the ResourcePath.
	* @param path_, String, the filename of the Path
	*/
	void setPath(const String &path_);

	/**
	* Get the extension of the ResourcePath.
	* @return String, the filename of the Path
	*/
	const String &getExtension() const;

	bool operator == (const ResourcePath &rgba) const;
	bool operator <  (const ResourcePath &rgba) const;

	/**
	* read method for Serialization
	* @param is, the InputStream for Serialization
	*/
	void read(InputStream &is);

	/**
	* write method for Serialization
	* @param os, the OutputStream for Serialization
	*/
	void write(OutputStream &os) const;
private:
	String path;
	String extension;
};

};

#endif