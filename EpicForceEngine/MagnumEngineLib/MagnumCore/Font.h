///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Font_h_
#define _Font_h_

#include "Stage.h"
#include "Platform.h"
#include "ResourceAccess.h"
#include "ResourceImport.h"
#include "Texture2DBase.h"
#include "Graphics2.h"
#include "GXContext.h"
using namespace Magnum;

#ifdef ENABLE_RESOURCE_IMPORT
#include "PVRTexConvert.h"
#endif

namespace Magnum
{

class GXTexture;

/**
* Font Graphics Object
* @see Texture2DBase
*/
class Font : public Texture2DBase
{
public:
	class Resource;
	class ResourceImporter;

	class Quad : public GXContext::Quad
	{
	friend class Font;
	friend class Font::Resource;
	friend class Font::ResourceImporter;
	public:
		Quad();
		~Quad();

		void read(InputStream &is);
		void write(OutputStream &os) const;

		float pre, post;
	};

	class Data
	{
	friend class Font;
	friend class Font::Resource;
	friend class Font::ResourceImporter;
	public:
		Data();
		~Data();

		int getNumQuads() const;
		const Font::Quad &getQuad(int i) const;

		void read(InputStream &is);
		void write(OutputStream &os) const;
	private:
		int									version;
		Platform							platform;
		
		float								maxHeight;
		Vector<Font::Quad>					quads;

		void								*textureHandle;
	};

	class Resource : public ResourceAccess
	{
	friend class Font;
	friend class Font::Resource;
	friend class Font::ResourceImporter;
	public:
		Resource(const char *path_);
		virtual ~Resource();

		virtual void *getHandle() const;

		/**
		* Get the Font Maximun Height
		* @return int  the Font Maximun Height
		*/
		virtual int getFontMaxHeight() const;

		/**
		* Get the Font Width of character c
		* @return int the Font Width of character c
		*/
		virtual int getFontWidth(char c) const;

		/**
		* Get the Font Height of character c
		* @return int the Font Height of character c
		*/
		virtual int getFontHeight(char c) const;

		/**
		* Get the Width of the Texture
		* @return int the Width of the Texture
		*/
		virtual int getWidth() const;

		/**
		* Get the Height of the Texture
		* @return int the Height of the Texture
		*/
		virtual int getHeight() const;

		/**
		* Get the Mip LevelCount of the Texture
		* @return int the Mip LevelCount of the Texture
		*/
		virtual int getLevelCount() const;

		/**
		* bool chec if the texture is Renderable
		* @return true if the Texture is Renderable, else false
		*/
		virtual bool isRenderable() const;

		/**
		* bool chec if the texture is PowerOfTwo
		* @return true if the Texture is PowerOfTwo, else false
		*/
		virtual bool isPowerOfTwo() const;

		DECLARE_RESOURCE(Font::Resource, fnt)
	protected:
		virtual unsigned char *onCreate(int length);
		virtual void onLoaded();
		virtual void onDestroy();
	private:
		int getNumQuads() const;
		const Font::Quad &getQuad(int i) const;
	private:
		Font::Data		data;
		Vector<unsigned char>	buffer;
	};

	#ifdef ENABLE_RESOURCE_IMPORT
	class ResourceImporter : public ResourceImport
	{
	friend class Font;
	friend class Font::Resource;
	friend class Font::ResourceImporter;
	public:
		ResourceImporter(const char *path_);
		virtual ~ResourceImporter();

		DECLARE_RESOURCE_IMPORT(Font::ResourceImporter, fontzip, fnt)
	
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
		char *_get_line(char *file, char *line);
		bool exportFont(const char *srcFilename_, const char *dstFilename_, unsigned int pixelType);
		bool makeFontInfo(const char *srcFilename_, Vector<Font::Quad> &quads, float &height);
		bool makeFontTexture(Vector<unsigned char> &buf, 
							 int &topLevelMipmapWidth, int &topLevelMipmapHeight, int &numberMipMapsLevel,
							 const char *srcFilename_, unsigned int pixelType);
		bool writeFont(const char *dstFilename_, Vector<Font::Quad> &quads, void *texture_, float fontHeight);
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
	Font();
	virtual ~Font();

	bool construct(const char *path_);
	void destruct();

	virtual void *getHandle() const;

	virtual int getFontMaxHeight() const;
	virtual int getFontWidth(char c) const;
	virtual int getFontHeight(char c) const;

	virtual int getWidth() const;
	virtual int getHeight() const;
	virtual int getLevelCount() const;

	virtual bool isRenderable() const;
	virtual bool isPowerOfTwo() const;

	int getNumQuads() const;
	const Font::Quad &getQuad(int i) const;
private:
	Font::Resource *resource;
};

};

#endif