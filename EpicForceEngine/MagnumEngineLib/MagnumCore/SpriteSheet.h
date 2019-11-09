///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _SpriteSheet_h_
#define _SpriteSheet_h_

#include "Stage.h"
#include "Component.h"
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

class SpriteSheet : public Texture2DBase
{
public:
	class Resource;
	class ResourceImporter;

	class Quad : public GXContext::Quad
	{
	friend class SpriteSheet;
	friend class SpriteSheet::Resource;
	friend class SpriteSheet::ResourceImporter;
	public:
		Quad();
		~Quad();

		void read(InputStream &is);
		void write(OutputStream &os) const;
	};

	class Sequence
	{
	friend class SpriteSheet;
	friend class SpriteSheet::Resource;
	friend class SpriteSheet::ResourceImporter;
	public:
		Sequence();
		~Sequence();

		const String &getName() const;
		int getNumFrames() const;
		int getStartIndex() const;
		int getEndIndex() const;

		void read(InputStream &is);
		void write(OutputStream &os) const;
	private:
		String name;
		int startIndex;
		int endIndex;
	};

	class Data
	{
	friend class SpriteSheet;
	friend class SpriteSheet::Resource;
	friend class SpriteSheet::ResourceImporter;
	public:
		Data();
		~Data();

		int getNumQuads() const;
		const SpriteSheet::Quad &getQuad(int i) const;
		int getNumSequences() const;
		const SpriteSheet::Sequence &getSequence(int i) const;

		void read(InputStream &is);
		void write(OutputStream &os) const;
	private:
		int									version;
		Platform							platform;
		Vector<SpriteSheet::Quad>			quads;
		Vector<SpriteSheet::Sequence>		sequences;

		void								*textureHandle;
	};

	class Resource : public ResourceAccess
	{
	friend class SpriteSheet;
	friend class SpriteSheet::Resource;
	friend class SpriteSheet::ResourceImporter;
	public:
		Resource(const char *path_);
		virtual ~Resource();

		virtual void *getHandle() const;

		virtual int getWidth() const;
		virtual int getHeight() const;
		virtual int getLevelCount() const;

		virtual bool isRenderable() const;
		virtual bool isPowerOfTwo() const;

		DECLARE_RESOURCE(SpriteSheet::Resource, spritesheet)
	protected:
		virtual unsigned char *onCreate(int length);
		virtual void onLoaded();
		virtual void onDestroy();
	private:
		int getNumQuads() const;
		const SpriteSheet::Quad &getQuad(int i) const;
		int getNumSequences() const;
		const SpriteSheet::Sequence &getSequence(int i) const;
	private:
		SpriteSheet::Data		data;

		Vector<unsigned char>	buffer;
	};

	#ifdef ENABLE_RESOURCE_IMPORT
	class ResourceImporter : public ResourceImport
	{
	friend class SpriteSheet;
	friend class SpriteSheet::Resource;
	friend class SpriteSheet::ResourceImporter;
	public:
		class QuadBuffer
		{
		public:
			QuadBuffer()
			{
			}

			QuadBuffer &operator = (QuadBuffer &quadBuffer)
			{
				filename	= quadBuffer.filename	;
				imagename	= quadBuffer.imagename	;
				idx			= quadBuffer.idx		;
				u0			= quadBuffer.u0			;
				v0			= quadBuffer.v0			;
				u1			= quadBuffer.u1			;
				v1			= quadBuffer.v1			;
				width		= quadBuffer.width		;
				height		= quadBuffer.height		;

				return *this;
			}

			String filename;
			unsigned int imagename;
			int idx;
			float u0, v0;
			float u1, v1;
			float width;
			float height;
		};

		ResourceImporter(const char *path_);
		virtual ~ResourceImporter();

		DECLARE_RESOURCE_IMPORT(SpriteSheet::ResourceImporter, spritesheetzip, spritesheet)
	
		static bool initiate();
		static void terminate();

		static int compareQuadBufs(const void *q1, const void *q2);
		static int compareString(const void *left, const void *right);
	protected:
		virtual bool onExportFile(const char *srcFilename_, const char *dstFilename_);
		virtual bool onDeleteFile(const char *srcFilename_);
	private:
		bool exportSpriteSheet(const char *srcFilename_, const char *dstFilename_, unsigned int pixelType);
		bool makeSpriteTexture(Vector<unsigned char> &textureBuf, 
							   Vector<SpriteSheet::Quad> &rects, 
							   Vector<SpriteSheet::Sequence> &sequences, 
							   int &topLevelMipmapWidth, int &topLevelMipmapHeight, 
							   const char *srcFilename_, unsigned int pixelType);
			bool getSequence(const char *srcFilename_, Vector<SpriteSheet::Sequence> &sequences);
			bool getQuadBuffers(const char *srcFilename_, 
							    SpriteSheet::Sequence &sequence,
								Vector<SpriteSheet::ResourceImporter::QuadBuffer> &quadBuffers);
			void drawBitmap(Vector<unsigned char> &textureBuf, QuadBuffer &quadBuf, int xOffset, int yOffset, int width, int height);
		bool writeSpriteSheet(const char *dstFilename_, 
								  Vector<SpriteSheet::Quad> &quads, 
								  Vector<SpriteSheet::Sequence> &sequences, 
								  void *texture);
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
	SpriteSheet();
	virtual ~SpriteSheet();
public:
	bool construct(const char *path_);
	void destruct();

	virtual void *getHandle() const;

	virtual int getWidth() const;
	virtual int getHeight() const;
	virtual int getLevelCount() const;

	virtual bool isRenderable() const;
	virtual bool isPowerOfTwo() const;

	int getNumQuads() const;
	const SpriteSheet::Quad &getQuad(int i) const;
	int getNumSequences() const;
	const SpriteSheet::Sequence &getSequence(int i) const;
private:
	SpriteSheet::Resource *resource;
};

};

#endif