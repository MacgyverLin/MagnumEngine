///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _ResourceAccess_h_
#define _ResourceAccess_h_

#include "IO.h"
#include "Array.h"
#include "Delegate.h"
#include "ESystem.h"

namespace Magnum
{

#define DECLARE_RESOURCE(className, extName) \
static className *get(const char *path_)			{	return (className *)ResourceAccess::get(path_, extensionTag());		} \
static const char *extensionTag()					{	return #extName;													} \
virtual const char *extension() const				{	return extensionTag();												}

// #define SIMULATE_ASYNC

class ResourceAccess
{
	friend class Factory;
	friend class ICreator;

	ResourceAccess(const ResourceAccess &resource); // no copy
	ResourceAccess &operator = (const ResourceAccess &resource); // no assign
public:
	enum
	{
		MAX_CREATOR = 50,
		MAX_NAME	= 64
	};

	enum State
	{
		PENDING = 0,
		LOADING,
		FAILED,
		READY,
	};

	/**
	* ResourceAccess Constructor.
	* To Construct the ResourceAccess for the owner.
	*/
	ResourceAccess(const char *name_);

	/**
	* ResourceAccess Destructor.
	* To Destruct ResourceAccess and remove from its owner.
	*/
	virtual ~ResourceAccess();

	/**
	* Get the Name.
	* @return , const char *name of the resource.
	*/
	const char *name();

	/**
	* Increase Reference Count of the resource by 1
	* This function increase reference count to the resource and keep managed by the Resource Manager.
	*/
	void addReference();
	/**
	* Decrease Reference Count of the resource by 1
	* This function decrease reference count to the resource. If the reference count reach zero, the resource will be release by Resource Services
	* @see addReference
	*/
	void release();

	/**
	* Get the Reference Count of the resource
	* @return int, the how many time the resource is reference.
	*/
	int getRefCount() const;

	/**
	* Check if the Resource is Loading
	*/
	bool isLoading() const;

	/**
	* Increase Reference Count of the resource by 1
	* This function increase reference count to the resource and keep managed by the Resource Manager.
	*/
	bool isReady() const;
protected:
	virtual const char *extension()  const		= 0;
	virtual unsigned char *onCreate(int length) = 0;
	virtual void onLoaded()						= 0;
	virtual void onDestroy()					= 0;
private:
	void invalidate();
	void validate();
	bool isValid() const;

	bool openFile();
	void closeFile();
	bool isLoadingFinished();
	bool isLoadingTimeOut() const;

	void setPendingState();
	void setLoadingState();
	void setFailedState();
	void setReadyState();

	String	_name;

	IO		*file;
	int		refCount;
	State	state;
	int		length;

	bool	_valid;

#ifdef SIMULATE_ASYNC
	int		testCounter;
#endif
public:
	static ResourceAccess *get(const char *name_, const char *extension_, bool asyncLoading=false);

	static void load(const char *directory_, const char *extension = "*");
	static void unload(const char *directory_, const char *extension = "*");
private:
///////////////////////////////////////////////////////////////////////////////////////////////
//
public:
	class ICreator
	{
	friend class Factory;
	friend class ResourceAccess;
	public:
		ICreator(const char *extension_);
		virtual ResourceAccess *create(const char *name_, bool asyncLoading = false) = 0;
	private:
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
		bool isLoading() const;
		void getCount(int &pendingCount, int &loadingCount, int &failedCount, int &readyCount, int &orphanCount) const;
		void getSize(int &pendingSize, int &loadingSize, int &failedSize, int &readySize, int &orphanSize) const;
	protected:
		Vector<ResourceAccess *> activeResources;
		Vector<ResourceAccess *> inactiveResources;

		char extension[MAX_NAME+1];
	};

	template<typename T> class Creator : public ICreator
	{
	friend class Factory;
	friend class ResourceAccess;
	public:
		Creator() 
		: ICreator(T::extensionTag())
		{
		}
	private:
		ResourceAccess *find(const char *name_) const
		{
			for(int i=0; i<activeResources.length(); i++)
			{
				if( strcasecmp(activeResources[i]->_name, name_)==0 )
					return activeResources[i];
			}

			return 0;
		}

		virtual ResourceAccess *create(const char *name_, bool asyncLoading)
		{
			ResourceAccess *resource = find(name_);
			if(resource)
				return resource;
			resource = new T(name_);
			assert(resource);

			if(asyncLoading)
			{
				resource->setPendingState();
			}
			else
			{
				resource->setLoadingState();
				if( resource->isLoading() )
				{
					bool done = false;
					while(!done)
					{
						// debug("sync loading");
						if(resource->isLoadingFinished())
						{
							resource->setReadyState();
							done = true;
						}
						if(resource->isLoadingTimeOut())
						{
							resource->setFailedState();
							done = true;
						}
					}
				}
			}

			activeResources.push() = resource;

			return resource;
		}
	};

	class Factory
	{
	friend class ResourceAccess;
	friend class ICreator;
	public:
		Factory();
		~Factory();

		void beginUpdateResources(const Vector<System::File> &newReourceFiles, 
							      const Vector<System::File> &reloadResourceFiles, 
							      const Vector<System::File> &deleteReourceFiles);
		void endUpdateResources();
		bool isUpdatingResources() const;

		static Factory &instance();
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
		
		bool isLoading() const;
		void getCount(int &pendingCount, int &loadingCount, int &failedCount, int &readyCount, int &orphanCount) const;
		void getSize(int &pendingSize, int &loadingSize, int &failedSize, int &readySize, int &orphanSize) const;
	private:
		static Factory *_instance;

		bool _updateAssets;
		Vector<System::File> newReourceFiles;
		Vector<System::File> reloadResourceFiles;
		Vector<System::File> deleteReourceFiles;

		Array<ICreator *> creators;
	};
public:
	struct Service
	{
		static bool isLoading();
		static void getCount(int &pendingCount, int &loadingCount, int &failedCount, int &readyCount, int &orphanCount);
		static void getSize(int &pendingSize, int &loadingSize, int &failedSize, int &readySize, int &orphanSize);

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
