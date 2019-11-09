///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Texture2DFile_h_
#define _Texture2DFile_h_

#include "Stage.h"
#include "Platform.h"
#include "ResourceAccess.h"
#include "ResourceImport.h"
#include "Texture2DBase.h"
using namespace Magnum;

#ifdef ENABLE_RESOURCE_IMPORT
#include "PVRTexConvert.h"
#endif

namespace Magnum
{

class GXTexture;

/**
* Texture2DFile. This is the 2d texture file class
* @see Texture2DFile
*/
class Texture2DFile : public Texture2DBase
{
public:
	class Resource;
	class ResourceImporter;

	class Data
	{
	friend class Texture2DFile;
	friend class Texture2DFile::Resource;
	friend class Texture2DFile::ResourceImporter;
	public:
		Data();
		~Data();

		void read(InputStream &is);
		void write(OutputStream &os) const;
	private:
		int						version;
		Platform				platform;
		void					*textureHandle;
	};

	/**
	* Texture2DFile::Resource. This is the Resource class of Texture2DFile
	*/
	class Resource : public ResourceAccess
	{
	friend class Texture2DFile;
	friend class Texture2DFile::Resource;
	friend class Texture2DFile::ResourceImporter;
	public:
		/**
		* Texture2DFile::Resource Constructor.
		* To Construct the Texture2DFile::Resource
		* @param, path_, const char *, the path to the texture resource
		*/
		Resource(const char *path_);

		/**
		* Texture2DFile::Resource Destructor.
		* To Destruct the Texture2DFile::Resource
		*/
		virtual ~Resource();

		DECLARE_RESOURCE(Texture2DFile::Resource, texture)
	protected:
		virtual unsigned char *onCreate(int length);
		virtual void onLoaded();
		virtual void onDestroy();
	private:
		/**
		* Get the Handle of the Texture. 
		* @return void *, handle of the texture
		*/
		virtual void *getHandle() const;

		/**
		* Get the Width of the Texture. 
		* @return int, the Width of the Texture.
		*/
		int getWidth() const;

		/**
		* Get the Height of the Texture. 
		* @return int, the Height of the Texture.
		*/
		int getHeight() const;

		/**
		* Get the Mipmap Level Count of the Texture.
		* @return int, the Mipmap Level Count of the Texture.
		*/
		int getLevelCount() const;

		/**
		* Check if texture is renderable. 
		* @return true if the Texture is Renderable.
		*/
		bool isRenderable() const;

		/**
		* Check if texture is power of 2 in both width and height. 
		* @return true if the Texture is power of 2.
		*/
		bool isPowerOfTwo() const;
	private:
		Texture2DFile::Data		data;
		Vector<unsigned char>	buffer;
	};

	#ifdef ENABLE_RESOURCE_IMPORT
	class ResourceImporter : public ResourceImport
	{
	friend class Texture2DFile;
	friend class Texture2DFile::Resource;
	friend class Texture2DFile::ResourceImporter;
	public:
		/**
		* Texture2DFile::ResourceImporter Constructor.
		* To Construct the Texture2DFile::ResourceImporter
		* @param, path_, const char *, the path to the texture resource
		*/
		ResourceImporter(const char *path_);
		/**
		* Texture2DFile::ResourceImporter Destructor.
		* To Destruct the Texture2DFile::ResourceImporter
		*/
		virtual ~ResourceImporter();

		DECLARE_RESOURCE_IMPORT(Texture2DFile::ResourceImporter, tga, texture)
	
		/**
		* To initiate the resource import system.
		*/
		static bool initiate();

		/**
		* To terminate the resource import system.
		*/
		static void terminate();
	protected:
		virtual bool onExportFile(const char *srcFilename_, const char *dstFilename_);
		virtual bool onDeleteFile(const char *srcFilename_);
	private:
		bool exportTexture(const char *srcFilename_, const char *dstFilename_, unsigned int pixelType);
		bool makeRawTexture(Vector<unsigned char> &buf, 
							int &topLevelMipmapWidth, int &topLevelMipmapHeight, int &numberMipMapsLevel,
							const char *srcFilename_, unsigned int pixelType);
		bool writeTexture(const char *dstFilename_, Texture2DFile::Data &data_, void *texture_);
	public:
		PVRTexConvert::PrecisionOption		precision;
		PVRTexConvert::AlphaOption			alpha;
		PVRTexConvert::ChromeOption			chrome;
		PVRTexConvert::CompressOption		compress;
		int									quality;
	};
	#endif

//////////////////////////////////////////////////////////////////
public:
	/**
	* Texture2DFile Constructor.
	* To Construct the Texture2DFile
	*/
	Texture2DFile();

	/**
	* Texture2DFile Constructor.
	* To Destruct the Texture2DFile
	*/
	virtual ~Texture2DFile();

	/**
	* construct the texture from a path and allocate texture resource
	* @param, path_, const char *, the path to the texture resource
	* @return true if construction is success, return false if fail
	*/
	bool construct(const char *path_);

	/**
	* destruct the texture and release of texture resource 
	*/
	void destruct();

	/**
	* Get the Handle of the Texture. 
	* @return void *, handle of the texture
	*/
	virtual void *getHandle() const;
	
	/**
	* Get the Width of the Texture. 
	* @return int, the Width of the Texture.
	*/
	int getWidth() const;
	
	/**
	* Get the Height of the Texture. 
	* @return int, the Height of the Texture.
	*/
	int getHeight() const;
	
	/**
	* Get the Mipmap Level Count of the Texture.
	* @return int, the Mipmap Level Count of the Texture.
	*/
	int getLevelCount() const;
	
	/**
	* Check if texture is renderable. 
	* @return true if the Texture is Renderable.
	*/
	bool isRenderable() const;
	
	/**
	* Check if texture is power of 2 in both width and height. 
	* @return true if the Texture is power of 2.
	*/
	bool isPowerOfTwo() const;
private:
	Texture2DFile::Resource *resource;
};

};

#endif