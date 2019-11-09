///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _TextureCubeFile_h_
#define _TextureCubeFile_h_

#include "Stage.h"
#include "Platform.h"
#include "ResourceAccess.h"
#include "ResourceImport.h"
#include "TextureCubeBase.h"
using namespace Magnum;

#ifdef ENABLE_RESOURCE_IMPORT
#include "PVRTexConvert.h"
#endif

namespace Magnum
{

class GXTexture;

/**
* TextureCubeFile. This is the cubemap texture file class
* @see TextureCubeFile
*/
class TextureCubeFile : public TextureCubeBase
{
public:
	class Resource;
	class ResourceImporter;

	class Data
	{
	friend class TextureCubeFile;
	friend class TextureCubeFile::Resource;
	friend class TextureCubeFile::ResourceImporter;
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
	* TextureCubeFile::Resource. This is the Resource class of TextureCubeFile
	*/
	class Resource : public ResourceAccess
	{
	friend class TextureCubeFile;
	friend class TextureCubeFile::Resource;
	friend class TextureCubeFile::ResourceImporter;
	public:
		/**
		* TextureCubeFile::Resource Constructor.
		* To Construct the TextureCubeFile::Resource
		* @param, path_, const char *, the path to the texture resource
		*/
		Resource(const char *path_);

		/**
		* TextureCubeFile::Resource Destructor.
		* To Destruct the TextureCubeFile::Resource
		*/
		virtual ~Resource();

		DECLARE_RESOURCE(TextureCubeFile::Resource, textureCube)
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
		Data					data;
		Vector<unsigned char>	buffer;
	};

	#ifdef ENABLE_RESOURCE_IMPORT
	class ResourceImporter : public ResourceImport
	{
	friend class TextureCubeFile;
	friend class TextureCubeFile::Resource;
	friend class TextureCubeFile::ResourceImporter;
	public:
		/**
		* TextureCubeFile::ResourceImporter Constructor.
		* To Construct the Texture2DFile::ResourceImporter
		* @param, path_, const char *, the path to the texture resource
		*/
		ResourceImporter(const char *path_);

		/**
		* TextureCubeFile::ResourceImporter Destructor.
		* To Destruct the Texture2DFile::ResourceImporter
		*/
		virtual ~ResourceImporter();

		DECLARE_RESOURCE_IMPORT(TextureCubeFile::ResourceImporter, dds, textureCube)
	
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
		bool writeTexture(const char *dstFilename_, TextureCubeFile::Data &data_, void *texture_);
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
	* TextureCubeFile Constructor.
	* To Construct the TextureCubeFile
	*/
	TextureCubeFile();

	/**
	* TextureCubeFile Constructor.
	* To Destruct the TextureCubeFile
	*/
	virtual ~TextureCubeFile();

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
	Resource *resource;
};

};

#endif