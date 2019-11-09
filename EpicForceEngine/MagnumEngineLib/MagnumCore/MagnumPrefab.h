///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _MagnumPrefab_h_
#define _MagnumPrefab_h_

#include "Stage.h"
#include "Platform.h"
#include "ResourceAccess.h"
#include "ResourceImport.h"
using namespace Magnum;

namespace Magnum
{

class MagnumPrefab
{
public:
	class Resource;
	class ResourceImporter;

	class Data
	{
	friend class MagnumPrefab;
	friend class MagnumPrefab::Resource;
	friend class MagnumPrefab::ResourceImporter;
	public:
		Data();
		~Data();

		const unsigned char *getBuffer() const;

		void read(InputStream &is);
		void write(OutputStream &os) const;
	private:
		int						version;
		Platform				platform;
		Vector<unsigned char>	buffer;
	};

	class Resource : public ResourceAccess
	{
	friend class MagnumPrefab;
	friend class MagnumPrefab::Resource;
	friend class MagnumPrefab::ResourceImporter;
	public:
		Resource(const char *path_);
		virtual ~Resource();

		const unsigned char *getBuffer() const;

		DECLARE_RESOURCE(MagnumPrefab::Resource, MagnumPrefab)
	protected:
		virtual unsigned char *onCreate(int length);
		virtual void onLoaded();
		virtual void onDestroy();
	private:
	/////////////////////////////////////////////////////////
	public:
	protected:
	private:
		MagnumPrefab::Data			data;
		Vector<unsigned char>	buffer;
	};

	#ifdef ENABLE_RESOURCE_IMPORT
	class ResourceImporter : public ResourceImport
	{
	friend class MagnumPrefab;
	friend class MagnumPrefab::Resource;
	friend class MagnumPrefab::ResourceImporter;
	public:
		ResourceImporter(const char *path_);
		virtual ~ResourceImporter();

		DECLARE_RESOURCE_IMPORT(MagnumPrefab::ResourceImporter, MagnumPrefab, MagnumPrefab)
	
		static bool initiate();
		static void terminate();
	protected:
		virtual bool onExportFile(const char *srcFilename_, const char *dstFilename_);
		virtual bool onDeleteFile(const char *srcFilename_);
	private:
	public:
	};
	#endif

//////////////////////////////////////////////////////////////////
public:
	MagnumPrefab();
	virtual ~MagnumPrefab();

	bool construct(const char *path_);
	void destruct();

	const unsigned char *getBuffer() const;
private:
	MagnumPrefab::Resource *resource;
};

};

#endif