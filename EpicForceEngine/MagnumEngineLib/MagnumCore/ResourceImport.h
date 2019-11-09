///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _ResourceImport_h_
#define _ResourceImport_h_

#include "FileIO.h"
#include "Array.h"
#include "Delegate.h"
#include "ESystem.h"

#ifdef ENABLE_RESOURCE_IMPORT

namespace Magnum
{

#define DECLARE_RESOURCE_IMPORT(importerClassName, rawAssetExtName, assetExtName) \
static importerClassName *get(const char *name_)		{	return (importerClassName *)ResourceImport::get(name_, rawExtensionTag());		} \
static const char *rawExtensionTag()					{	return #rawAssetExtName;														} \
virtual const char *rawExtension() const				{	return rawExtensionTag();														} \
static const char *extensionTag()						{	return #assetExtName;															} \
virtual const char *extension() const					{	return extensionTag();															}

class ResourceImport
{
	friend class Factory;
	friend class ICreator;
public:
	class CallBack
	{
	public:
		CallBack();
		virtual ~CallBack();

		virtual void onInstantiateResourceImport(ResourceImport *entity_) = 0;
		virtual void onDeleteResourceImport(ResourceImport *entity_) = 0;
	};

	enum
	{
		MAX_CREATOR = 50,
		MAX_NAME	= 64
	};

	ResourceImport(const char *name_);
	virtual ~ResourceImport();

	const char *name() const ;
	virtual const char *rawExtension() const	= 0;
	virtual const char *extension() const		= 0;

	void setTime(unsigned long long	createTime_, unsigned long long lastWriteTime_, unsigned long long lastAccessTime_);

	void addReference();
	int getRefCount() const;
	void release();
protected:
	virtual bool onExportFile(const char *srcPath, const char *dstPath) = 0;
	virtual bool onDeleteFile(const char *srcPath) = 0;
protected:
	virtual bool defaultExportFileFunc(const char *srcPath, const char *dstPath);
	virtual bool defaultDeleteFileFunc(const char *srcPath);

	String	_name;

	unsigned long long	createTime;
	unsigned long long	lastWriteTime;
	unsigned long long	lastAccessTime;
	int					refCount;
public:
	static ResourceImport *get(const char *name_, const char *rawExtension_);
private:
	static ResourceImport::CallBack *callback;
///////////////////////////////////////////////////////////////////////////////////////////////
//
public:
	class ICreator
	{
	friend class Factory;
	friend class ResourceImport;
	public:
		ICreator(const char *rawExtension_, const char *expExtension_);
		virtual ResourceImport *create(const char *name_) = 0;

		int getNumResourceImporters() const;
		const ResourceImport *getResourceImporters(int i) const;
		ResourceImport *getResourceImporters(int i);
	protected:
		virtual bool initiate()		= 0;
		virtual void process(Vector<System::File> &newFiles, Vector<System::File> &reloadFiles, Vector<System::File> &deleteFiles);
		virtual void pause();
		virtual void resume();
		virtual void terminate()	= 0;
		virtual void clear();
	private:
	protected:
		Vector<ResourceImport *> resourceImporters;

		char rawExtension[27+1];
		char expExtension[27+1];
	};

	template<typename T> class Creator : public ICreator
	{
	friend class Factory;
	friend class ResourceImport;
	public:
		Creator() 
		: ICreator(T::rawExtensionTag(), T::extensionTag())
		{
		}
	private:
		ResourceImport *find(const char *name_) const
		{
			for(int i=0; i<resourceImporters.length(); i++)
			{
				if( strcasecmp(resourceImporters[i]->_name, name_)==0 )
					return resourceImporters[i];
			}

			return 0;
		}

		virtual ResourceImport *create(const char *name_)
		{
			ResourceImport *resourceImporter = find(name_);
			if(resourceImporter)
				return resourceImporter;

			resourceImporter = new T(name_);
			assert(resourceImporter);

			resourceImporters.push() = resourceImporter;

			return resourceImporter;
		}

		virtual bool initiate()
		{
			return T::initiate();
		}

		virtual void terminate()
		{
			return T::terminate();
		}
	};

	class Factory
	{
	friend class ResourceImport;
	friend class ICreator;
	public:
		Factory();
		~Factory();

		void beginCheckRawAssets();
		void endCheckRawAssets();
		bool isCheckingRawAssets() const;
		
		const Vector<System::File> &getNewReourceFiles() const;
		const Vector<System::File> &getReloadResourceFiles() const;
		const Vector<System::File> &getDeleteReourceFiles() const;

		static Factory &instance();

		int getNumCreators() const;
		ResourceImport::ICreator *getCreator(int i) const;
	private:
		ICreator *find(const char *extension_) const;

		/**
		* Initiate the Services
		* @return true if success, false if failed
		*/
		bool initiate();

		/**
		* Update the Services
		*/
		void process();

		/**
		* Called when the application is pause(e.g system bring the app to background, let the service to release resources)
		*/
		void pause();

		/**
		* Called when the application is resume(e.g system bring back the app from background, let the service to reload resources)
		*/
		void resume();

		/**
		* Terminate the Services, called when the app is terminate.
		*/
		void terminate();

		/**
		* Call when the services needed to be clean up, e.g. during scene transition.
		*/
		void clear();
	private:
		static Factory *_instance;

		bool _checkRawAssets;
		Vector<System::File> newFiles;
		Vector<System::File> reloadFiles;
		Vector<System::File> deleteFiles;

		Array<ICreator *> creators;
	};
public:
	struct Service
	{
		/**
		* Initiate the Services
		* @return true if success, false if failed
		*/
		static bool initiate();

		/**
		* Update the Services
		*/
		static void process();

		/**
		* Called when the application is pause(e.g system bring the app to background, let the service to release resources)
		*/
		static void pause();

		/**
		* Called when the application is resume(e.g system bring back the app from background, let the service to reload resources)
		*/
		static void resume();

		/**
		* Terminate the Services, called when the app is terminate.
		*/
		static void terminate();

		/**
		* Call when the services needed to be clean up, e.g. during scene transition.
		*/
		static void clear();
	};
};

}

#endif

#endif
