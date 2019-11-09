///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Stage.h"
#include "ResourceAccess.h"
#include "EMath.h"
#include "ESystem.h"
#include "FileIO.h"
//#include "GZFileIO.h"
using namespace Magnum;

ResourceAccess::ResourceAccess(const char *name_)
: _name(name_)
, file(0)
, refCount(0)
, state(PENDING)
, length(0)
, _valid(true)
#ifdef SIMULATE_ASYNC
, testCounter(0)
#endif
{
}

ResourceAccess::~ResourceAccess()
{
	closeFile();
}

const char *ResourceAccess::name()
{
	return _name;
}

void ResourceAccess::addReference()
{
	refCount++;
}

int ResourceAccess::getRefCount() const
{
	return refCount;
}

void ResourceAccess::release()
{
	assert(refCount>0);

	refCount--;
}

bool ResourceAccess::isLoading() const
{
	return state == LOADING;
}

bool ResourceAccess::isReady() const
{
	return state == READY;
}

void ResourceAccess::invalidate()
{
	_valid = false;
}

void ResourceAccess::validate()
{
	_valid = true;
}

bool ResourceAccess::isValid() const
{
	return _valid;
}

bool ResourceAccess::openFile()
{
	assert(file==0);
	
	String path = Stage::getAssetRootDirectory() + _name.toLower() + "." + extension();
	//String path = Stage::getDocumentDirectory() + name.toLower() + "." + extension();
	//String path = Stage::getExternalDirectory() + _name.toLower() + "." + extension();

#ifdef GZ_RESOURCE
	file = new GZFileIO(path.text());
#else
	file = new FileIO(path.text());
#endif
    if(!file)
	{
		debug("failed to open files %s", path.text());
		return false;
	}

#ifdef SIMULATE_ASYNC
	testCounter = Math::IntervalRandom(0, 10);
	return file->open(IO::READ);
#else
	return file->openForAsync(IO::READ);
#endif
}

void ResourceAccess::closeFile()
{
	if(file)
	{
		file->close();
		delete file;
		file = 0;
	}
}

bool ResourceAccess::isLoadingFinished()
{
#ifdef SIMULATE_ASYNC
	if(testCounter>0)
		testCounter--;

	return testCounter==0;
#else
	if(!file)
		file = file;

	assert(file);

	return file->isAsyncFinished();
#endif
}

bool ResourceAccess::isLoadingTimeOut() const
{
	return false;
}

void ResourceAccess::setPendingState()
{
	state = PENDING;
}

void ResourceAccess::setLoadingState()
{
	if( !openFile() )
	{
		setFailedState();
		return;
	}

	onDestroy();

	length = file->length();
    unsigned char *buffer = onCreate(length);
	if(!buffer)
	{
		setFailedState();
		return;
	}

	int rval = file->read(buffer, length);	

	state = LOADING;
}

void ResourceAccess::setFailedState()
{
	closeFile();

	state = FAILED;
}

void ResourceAccess::setReadyState()
{
	onLoaded();

	closeFile();

	state = READY;
}

ResourceAccess *ResourceAccess::get(const char *name_, const char *extension_, bool asyncLoading)
{
	ResourceAccess::ICreator *creator = ResourceAccess::Factory::instance().find(extension_);
	if(creator)
		return creator->create(name_, asyncLoading);
	else
		return 0;
}

void ResourceAccess::load(const char *directory_, const char *extension)
{
	Vector<System::File>		files;

	String path = Stage::getAssetRootDirectory() + String(directory_);
	if(directory_!="")
		path += "/";

	System::listAssets(path.text(), extension, files);

	for(int i=0; i<files.length(); i++)
	{
		debug("%s %s", files[i].fileName.text(), files[i].extension.text());

		ResourceAccess *resource = ResourceAccess::get(files[i].fileName, files[i].extension, true);
		if(resource)
			resource->addReference();
	}
}

void ResourceAccess::unload(const char *directory_, const char *extension)
{
	Vector<System::File>		files;

	String path = Stage::getAssetRootDirectory() + String(directory_);
	if(directory_!="")
		path += "/";

	System::listAssets(path.text(), extension, files);

	for(int i=0; i<files.length(); i++)
	{
		debug("%s %s", files[i].fileName.text(), files[i].extension.text());

		ResourceAccess *resource = ResourceAccess::get(files[i].fileName, files[i].extension, true);
		if(resource)
			resource->release();
	}
}

//////////////////////////////////////////////////////////////////////////////////////
ResourceAccess::ICreator::ICreator(const char *extension_)
: activeResources(0)
, inactiveResources(0)
{
	assert(extension_!=0 && extension_[0]!=0 && strlen(extension_)<sizeof(extension));
	assert(!ResourceAccess::Factory::instance().creators.full());

	strcpy(extension, extension_);
	
	ResourceAccess::Factory::instance().creators.insert() = this;
}

bool ResourceAccess::ICreator::initiate()
{
	return true;
}

void ResourceAccess::ICreator::process()
{
	int idx = -1;

	for(int i=0; i<activeResources.length(); i++)
	{
		switch(activeResources[i]->state)
		{
			case PENDING:
				activeResources[i]->setLoadingState();
				break;

			case LOADING:
				if(activeResources[i]->isLoadingFinished())
					activeResources[i]->setReadyState();
				else if(activeResources[i]->isLoadingTimeOut())
					activeResources[i]->setFailedState();
				break;

			case FAILED:
				if( activeResources[i]->refCount==0 )
				{
					//resources[i]->setOrphanState();
					inactiveResources.push() = activeResources[i];

					activeResources.remove(i);
				}
				else if( !activeResources[i]->isValid() )
				{
					activeResources[i]->setLoadingState();
					activeResources[i]->validate();
				}
				break;

			case READY:
				if( activeResources[i]->refCount==0 )
				{
					//resources[i]->setOrphanState();
					inactiveResources.push() = activeResources[i];

					activeResources.remove(i);
				}
				else if( !activeResources[i]->isValid() )
				{
					activeResources[i]->setLoadingState();
					activeResources[i]->validate();
				}
				break;
		}
	}

	for(int i=0; i<inactiveResources.length(); i++)
	{
		if(inactiveResources[i])
		{
			delete inactiveResources[i];
			inactiveResources[i] = 0;
		}
	}
	inactiveResources.clear();
}

void ResourceAccess::ICreator::pause()
{
}

void ResourceAccess::ICreator::resume()
{
}

void ResourceAccess::ICreator::terminate()
{
	for(int i=0; i<activeResources.length(); i++)
	{
		if(activeResources[i])
		{
			delete activeResources[i];
			activeResources[i] = 0;
		}
	}
	activeResources.destroy();

	for(int i=0; i<inactiveResources.length(); i++)
	{
		if(inactiveResources[i])
		{
			delete inactiveResources[i];
			inactiveResources[i] = 0;
		}
	}
	inactiveResources.destroy();
}

void ResourceAccess::ICreator::clear()
{
	for(int i=0; i<activeResources.length(); i++)
	{
		if(activeResources[i])
		{
			delete activeResources[i];
			activeResources[i] = 0;
		}
	}
	activeResources.destroy();

	for(int i=0; i<inactiveResources.length(); i++)
	{
		if(inactiveResources[i])
		{
			delete inactiveResources[i];
			inactiveResources[i] = 0;
		}
	}
	inactiveResources.destroy();
}

bool ResourceAccess::ICreator::isLoading() const
{
	for(int i=0; i<activeResources.length(); i++)
	{
		if(activeResources[i]->isLoading())
			return true;
	}

	return false;
}

void ResourceAccess::ICreator::getCount(int &pendingCount, int &loadingCount, int &failedCount, int &readyCount, int &orphanCount) const
{
	for(int i=0; i<activeResources.length(); i++)
	{
		switch(activeResources[i]->state)
		{
			case PENDING:
				pendingCount++;
				break;
			case LOADING:
				loadingCount++;
				break;
			case FAILED:
				failedCount++;
				break;
			case READY:
				readyCount++;
				break;
		}
	}
}

void ResourceAccess::ICreator::getSize(int &pendingSize, int &loadingSize, int &failedSize, int &readySize, int &orphanSize) const
{
	for(int i=0; i<activeResources.length(); i++)
	{
		switch(activeResources[i]->state)
		{
			case PENDING:
				pendingSize		+= activeResources[i]->length;
				break;
			case LOADING:
				loadingSize		+= activeResources[i]->length;
				break;
			case FAILED:
				failedSize		+= activeResources[i]->length;
				break;
			case READY:
				readySize		+= activeResources[i]->length;
				break;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////
ResourceAccess::Factory *ResourceAccess::Factory::_instance=0;

ResourceAccess::Factory::Factory()
: creators(ResourceAccess::MAX_CREATOR, 0)
{
	assert(_instance==0);
	_instance=this;
}

ResourceAccess::Factory::~Factory()
{
}

ResourceAccess::Factory &ResourceAccess::Factory::instance()
{
	return *_instance;
}

ResourceAccess::ICreator *ResourceAccess::Factory::find(const char *extension_) const
{
	for(int i=0; i<creators.length(); i++)
	{
		if(strcasecmp(creators[i]->extension, extension_)==0)
			return creators[i];
	}
	
	debug("ResourceAccess::Factory cannot find creator %s", extension_);
	return 0;
}

void ResourceAccess::Factory::beginUpdateResources(const Vector<System::File> &newReourceFiles_,
												   const Vector<System::File> &reloadResourceFiles_,
												   const Vector<System::File> &deleteReourceFiles_)
{
	newReourceFiles			= newReourceFiles_;
	reloadResourceFiles		= reloadResourceFiles_;
	deleteReourceFiles		= deleteReourceFiles_;

	_updateAssets = true;
}

void ResourceAccess::Factory::endUpdateResources()
{
	_updateAssets = false;
}

bool ResourceAccess::Factory::isUpdatingResources() const
{
	return _updateAssets;
}

bool ResourceAccess::Factory::initiate()
{
	for(int i=0; i<creators.length(); i++)
	{
		if( !creators[i]->initiate() )
			return false;
	}

	return true;
}

void ResourceAccess::Factory::process()
{
	if(ResourceAccess::Factory::instance().isUpdatingResources())
	{
		// update assets
		ResourceAccess::Factory::instance().endUpdateResources();
	}

	for(int i=0; i<creators.length(); i++)
	{
		creators[i]->process();
	}
}

void ResourceAccess::Factory::pause()
{
	for(int i=0; i<creators.length(); i++)
	{
		creators[i]->pause();
	}
}

void ResourceAccess::Factory::resume()
{
	for(int i=0; i<creators.length(); i++)
	{
		creators[i]->resume();
	}
}

void ResourceAccess::Factory::terminate()
{
	for(int i=0; i<creators.length(); i++)
	{
		creators[i]->terminate();
	}

	newReourceFiles.destroy();
	reloadResourceFiles.destroy();
	deleteReourceFiles.destroy();
}

void ResourceAccess::Factory::clear()
{
	for(int i=0; i<creators.length(); i++)
	{
		creators[i]->clear();
	}

	newReourceFiles.destroy();
	reloadResourceFiles.destroy();
	deleteReourceFiles.destroy();
}

bool ResourceAccess::Factory::isLoading() const
{
	for(int i=0; i<creators.length(); i++)
	{
		if( creators[i]->isLoading() )
			return true;
	}

	return false;
}

void ResourceAccess::Factory::getCount(int &pendingCount, int &loadingCount, int &failedCount, int &readyCount, int &orphanCount) const
{
	for(int i=0; i<creators.length(); i++)
	{
		int pendingCountCreator = 0, loadingCountCreator = 0, failedCountCreator = 0, readyCountCreator = 0, orphanCountCreator = 0;
		creators[i]->getCount(pendingCountCreator, loadingCountCreator, failedCountCreator, readyCountCreator, orphanCountCreator);

		pendingCount	+= pendingCountCreator;
		loadingCount	+= loadingCountCreator;
		failedCount		+= failedCountCreator;
		readyCount		+= readyCountCreator;
		orphanCount		+= orphanCountCreator;
	}
}

void ResourceAccess::Factory::getSize(int &pendingSize, int &loadingSize, int &failedSize, int &readySize, int &orphanSize) const
{
	for(int i=0; i<creators.length(); i++)
	{
		int pendingSizeCreator = 0, loadingSizeCreator = 0, failedSizeCreator = 0, readySizeCreator = 0, orphanSizeCreator = 0;
		creators[i]->getSize(pendingSizeCreator, loadingSizeCreator, failedSizeCreator, readySizeCreator, orphanSizeCreator);

		pendingSize		+= pendingSizeCreator;
		loadingSize		+= loadingSizeCreator;
		failedSize		+= failedSizeCreator;
		readySize		+= readySizeCreator;
		orphanSize		+= orphanSizeCreator;
	}
}

///////////////////////////////////////////////////////////////
bool ResourceAccess::Service::isLoading()
{
	return Factory::instance().isLoading();
}

void ResourceAccess::Service::getCount(int &pendingCount, int &loadingCount, int &failedCount, int &readyCount, int &orphanCount)
{
	pendingCount = 0, loadingCount = 0, failedCount = 0, readyCount = 0, orphanCount = 0;
	Factory::instance().getCount(pendingCount, loadingCount, failedCount, readyCount, orphanCount);
}

void ResourceAccess::Service::getSize(int &pendingSize, int &loadingSize, int &failedSize, int &readySize, int &orphanSize)
{
	pendingSize = 0, loadingSize = 0, failedSize = 0, readySize = 0, orphanSize = 0;
	Factory::instance().getSize(pendingSize, loadingSize, failedSize, readySize, orphanSize);
}

///////////////////////////////////////////////////////////////
bool ResourceAccess::Service::initiate()
{
	return Factory::instance().initiate();
}

void ResourceAccess::Service::process()
{
	Factory::instance().process();
}

void ResourceAccess::Service::pause()
{
	Factory::instance().pause();
}

void ResourceAccess::Service::resume()
{
	Factory::instance().resume();
}

void ResourceAccess::Service::terminate()
{
	Factory::instance().terminate();
}

void ResourceAccess::Service::clear()
{
	Factory::instance().clear();
}