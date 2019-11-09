///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Stage.h"
#include "ResourceImport.h"
#include "EMath.h"
#include "ESystem.h"
#include "InputStream.h"
#include "OutputStream.h"
using namespace Magnum;

#ifdef ENABLE_RESOURCE_IMPORT

//////////////////////////////////////////////////////////////////////////////////////
ResourceImport::CallBack::CallBack()
{
	ResourceImport::callback = this;
}

ResourceImport::CallBack::~CallBack()
{
	ResourceImport::callback = 0;
}

//////////////////////////////////////////////////////////////////////////////////////
ResourceImport::CallBack *ResourceImport::callback	= 0;

ResourceImport::ResourceImport(const char *name_)
: _name(name_)
, createTime(0)
, lastWriteTime(0)
, lastAccessTime(0)
, refCount(0)
{
	if(ResourceImport::callback)
		ResourceImport::callback->onInstantiateResourceImport(this);
}

ResourceImport::~ResourceImport()
{
	if(ResourceImport::callback)
		ResourceImport::callback->onDeleteResourceImport(this);
}

const char *ResourceImport::name() const
{
	return _name;
}

void ResourceImport::setTime(unsigned long long createTime_, unsigned long long lastWriteTime_, unsigned long long lastAccessTime_)
{
	createTime     = createTime_;
	lastWriteTime  = lastWriteTime_;
	lastAccessTime = lastAccessTime_;
}

void ResourceImport::addReference()
{
	refCount++;
}

int ResourceImport::getRefCount() const
{
	return refCount;
}

void ResourceImport::release()
{
	assert(refCount>0);

	refCount--;
}

bool ResourceImport::defaultExportFileFunc(const char *srcPath, const char *dstPath)
{
#ifdef GZ_RESOURCE

#define BLOCKSIZE 1024*16

	FileInputStream is(srcPath);
	if(!is.opened())
		return false;

	GZFileOutputStream os(dstPath);
	if(!os.opened())
		return false;

	char buffer[BLOCKSIZE];
	int byteToRead = is.length();
	while(byteToRead>0)
	{
		int readLength = BLOCKSIZE;
		if(readLength > byteToRead)
			readLength = byteToRead;

		is.readX(buffer, readLength);
		os.writeX(buffer, readLength);

		byteToRead -= readLength;
	}

	return true;

#undef BLOCKSIZE

#else
	return CopyFileEx(srcPath, dstPath, 0, 0, FALSE, 0 )!=0;
#endif
}

bool ResourceImport::defaultDeleteFileFunc(const char *srcPath)
{
	return DeleteFile(srcPath)!=0;
}

ResourceImport *ResourceImport::get(const char *name_, const char *rawExtension_)
{
	ResourceImport::ICreator *creator = ResourceImport::Factory::instance().find(rawExtension_);
	assert(creator);

	return creator->create(name_);
}

//////////////////////////////////////////////////////////////////////////////////////
ResourceImport::ICreator::ICreator(const char *rawExtension_, const char *expExtension_)
: resourceImporters(0)
{
	assert(rawExtension_!=0 && rawExtension_[0]!=0 && strlen(rawExtension_)<sizeof(rawExtension));
	assert(expExtension_!=0 && expExtension_[0]!=0 && strlen(expExtension_)<sizeof(expExtension));

	assert(!ResourceImport::Factory::instance().creators.full());

	strcpy(rawExtension, rawExtension_);
	strcpy(expExtension, expExtension_);

	ResourceImport::Factory::instance().creators.insert() = this;
}

int ResourceImport::ICreator::getNumResourceImporters() const
{
	return resourceImporters.length();
}

ResourceImport *ResourceImport::ICreator::getResourceImporters(int i)
{
	return resourceImporters[i];
}

const ResourceImport *ResourceImport::ICreator::getResourceImporters(int i) const
{
	return resourceImporters[i];
}

bool ResourceImport::ICreator::initiate()
{
	return true;
}

void ResourceImport::ICreator::process(Vector<System::File> &newFiles, Vector<System::File> &reloadFiles, Vector<System::File> &deleteFiles)
{
	Vector<System::File>	rawFiles;
	Vector<System::File>	expFiles;

	String rawAssetRoot = Stage::getRawAssetRootDirectory();
	String expAssetRoot = Stage::getAssetRootDirectory();

	System::listAssets(rawAssetRoot, rawExtension, rawFiles);
	System::listAssets(expAssetRoot, expExtension, expFiles);

	for(int i=0; i<rawFiles.length(); i++)
	{
		ResourceImport *resourceImporter = ResourceImport::get(rawFiles[i].fileName, rawExtension);
		if(resourceImporter->getRefCount()==0) // create new importer if not existed
		{
			resourceImporter->addReference();
			resourceImporter->setTime(rawFiles[i].createTime, rawFiles[i].lastWriteTime, rawFiles[i].lastAccessTime);
		}
	}

	for(int i=0; i<resourceImporters.length(); i++)
	{
		const char *resourceName = resourceImporters[i]->name();
		String rawPath = String(rawAssetRoot)+String(resourceName)+String(".")+String(rawExtension);
		String expPath = String(expAssetRoot)+String(resourceName)+String(".")+String(expExtension);
		rawPath = rawPath.toLower();
		expPath = expPath.toLower();

		int rawIdx = rawFiles.search(System::File(resourceName));
		int expIdx = expFiles.search(System::File(resourceName));

		if( rawIdx!=-1 ) // has raw file
		{
			if(expIdx!=-1) // has exp file
			{
				if(rawFiles[rawIdx].lastWriteTime > expFiles[expIdx].lastWriteTime)
				{
					////////////////////////////////////////////////////////////////
					// Re-Export becaue Raw Assets is newer than Assets
					debug("re-export %s -> %s", rawPath.text(), expPath.text());

					String dirName = resourceName;
					for(int j=0; j<dirName.length(); j++)
					{
						if(dirName[dirName.length()-1-j]=='/')
						{
							dirName = dirName.extract(0, dirName.length()-1-j);
							break;
						}
					}

					if(dirName!=resourceName)
					{
						String dirPath = String(expAssetRoot)+String(dirName);
						dirPath = dirPath.toLower();
						debug("making Directory =%s", dirPath);
						System::makeDirectory(dirPath);
					}
					else
					{
						debug("no need making Directory");
					}

					resourceImporters[i]->onDeleteFile(expPath);
					resourceImporters[i]->onExportFile(rawPath, expPath);

					////////////////////////////////////////////////////////////////
					System::File &file = reloadFiles.push();
					file.fileName		= resourceName;
					file.extension		= expExtension;
					file.createTime		= 0;
					file.lastWriteTime	= 0;
					file.lastAccessTime	= 0;
				}
				else
				{
					////////////////////////////////////////////////////////////////
					// No Op becaue Raw Assets is older than Assets
					debug("%s is latest, no need export", expPath.text());
				}
			}
			else // no exp file
			{
				////////////////////////////////////////////////////////////////
				// Newly Export
				String dirName = resourceName;
				for(int j=0; j<dirName.length(); j++)
				{
					if(dirName[dirName.length()-1-j]=='/')
					{
						dirName = dirName.extract(0, dirName.length()-1-j);
						break;
					}
				}

				if(dirName!=resourceName)
				{
					String dirPath = String(expAssetRoot)+String(dirName);
					dirPath = dirPath.toLower();
					debug("making Directory =%s", dirPath);
					System::makeDirectory(dirPath);
				}
				else
				{
					debug("no need making Directory");
				}

				resourceImporters[i]->onDeleteFile(expPath);
				resourceImporters[i]->onExportFile(rawPath, expPath);

				////////////////////////////////////////////////////////////////
				System::File &file = newFiles.push();
				file.fileName		= resourceName;
				file.extension		= expExtension;
				file.fileName		= resourceName;
				file.extension		= expExtension;
				file.createTime		= 0;
				file.lastWriteTime	= 0;
				file.lastAccessTime	= 0;

				debug("new export %s -> %s", rawPath.text(), expPath.text());
			}
		}
		else // no raw file
		{
			if(expIdx!=-1) // has exp file 
			{
				debug("delete export %s", expPath.text());
				
				// delete exported assets
				resourceImporters[i]->onDeleteFile(expPath);

				resourceImporters[i]->release();

				////////////////////////////////////////////////////////////////
				System::File &file = deleteFiles.push();
				file.fileName		= resourceName;
				file.extension		= expExtension;
				file.createTime		= 0;
				file.lastWriteTime	= 0;
				file.lastAccessTime	= 0;
			}
			else 
			{
				debug("nothing to do");
			}
		}
	}

	///////////////////////////////////////////////////////////
	// remove resource importer in excess
	for(int i=0; i<resourceImporters.length(); i++)
	{
		if(resourceImporters[i] && resourceImporters[i]->getRefCount()==0)
		{
			if(resourceImporters[i])
			{
				debug("delete resource importer %s", resourceImporters[i]->name());
				delete resourceImporters[i];
				resourceImporters[i] = 0;

				resourceImporters.remove(i);
			}
		}
	}
}

void ResourceImport::ICreator::pause()
{
}

void ResourceImport::ICreator::resume()
{
}

void ResourceImport::ICreator::terminate()
{
	for(int i=0; i<resourceImporters.length(); i++)
	{
		if(resourceImporters[i])
		{
			delete resourceImporters[i];
			resourceImporters[i] = 0;
		}
	}
	resourceImporters.destroy();
}

void ResourceImport::ICreator::clear()
{
	for(int i=0; i<resourceImporters.length(); i++)
	{
		if(resourceImporters[i])
		{
			delete resourceImporters[i];
			resourceImporters[i] = 0;
		}
	}
	resourceImporters.destroy();
}

//////////////////////////////////////////////////////////////////////////////////////
ResourceImport::Factory *ResourceImport::Factory::_instance=0;

ResourceImport::Factory::Factory()
: creators(ResourceImport::MAX_CREATOR, 0)
, _checkRawAssets(false)
{
	assert(_instance==0);
	_instance=this;
}

ResourceImport::Factory::~Factory()
{
}

ResourceImport::Factory &ResourceImport::Factory::instance()
{
	return *_instance;
}

int ResourceImport::Factory::getNumCreators() const
{
	return creators.length();
}

ResourceImport::ICreator *ResourceImport::Factory::getCreator(int i) const
{
	return creators[i];
}

ResourceImport::ICreator *ResourceImport::Factory::find(const char *rawExtension_) const
{
	for(int i=0; i<creators.length(); i++)
	{
		if( strcasecmp(creators[i]->rawExtension, rawExtension_)==0 )
			return creators[i];
	}

	debug("ResourceImport::Factory cannot find creator %s", rawExtension_);
	return 0;
}

void ResourceImport::Factory::beginCheckRawAssets()
{
	_checkRawAssets = true;

	newFiles.destroy();
	reloadFiles.destroy();
	deleteFiles.destroy();
}

void ResourceImport::Factory::endCheckRawAssets()
{
	_checkRawAssets = false;
}

bool ResourceImport::Factory::isCheckingRawAssets() const
{
	return _checkRawAssets;
}

const Vector<System::File> &ResourceImport::Factory::getNewReourceFiles() const
{
	return newFiles;
}

const Vector<System::File> &ResourceImport::Factory::getReloadResourceFiles() const
{
	return reloadFiles;
}

const Vector<System::File> &ResourceImport::Factory::getDeleteReourceFiles() const
{
	return deleteFiles;
}

bool ResourceImport::Factory::initiate()
{
	for(int i=0; i<creators.length(); i++)
	{
		if(!creators[i]->initiate())
			return false;
	}

	return true;
}

void ResourceImport::Factory::process()
{
	if( ResourceImport::Factory::instance().isCheckingRawAssets() )
	{
		debug("ResourceImport::Factory::process()");

		for(int i=0; i<creators.length(); i++)
			creators[i]->process(newFiles, reloadFiles, deleteFiles);

		debug("-------------------------newFiles-------------------------");
		for(int i=0; i<newFiles.length(); i++)
		{
			debug("%s.%s", newFiles[i].fileName, newFiles[i].extension);
		}
		debug("------------------------reloadFiles-----------------------");
		for(int i=0; i<reloadFiles.length(); i++)
		{
			debug("%s.%s", reloadFiles[i].fileName, reloadFiles[i].extension);
		}
		debug("------------------------deleteFiles-----------------------");
		for(int i=0; i<deleteFiles.length(); i++)
		{
			debug("%s.%s", deleteFiles[i].fileName, deleteFiles[i].extension);
		}

		ResourceImport::Factory::instance().endCheckRawAssets();
	}
}

void ResourceImport::Factory::pause()
{
	for(int i=0; i<creators.length(); i++)
	{
		creators[i]->pause();
	}
}

void ResourceImport::Factory::resume()
{
	for(int i=0; i<creators.length(); i++)
	{
		creators[i]->resume();
	}
}

void ResourceImport::Factory::terminate()
{
	for(int i=0; i<creators.length(); i++)
	{
		creators[i]->terminate();
	}

	newFiles.destroy();
	reloadFiles.destroy();
	deleteFiles.destroy();
}

void ResourceImport::Factory::clear()
{
	for(int i=0; i<creators.length(); i++)
	{
		creators[i]->clear();
	}

	newFiles.destroy();
	reloadFiles.destroy();
	deleteFiles.destroy();
}

///////////////////////////////////////////////////////////////
bool ResourceImport::Service::initiate()
{
	return Factory::instance().initiate();
}

void ResourceImport::Service::process()
{
	Factory::instance().process();
}

void ResourceImport::Service::pause()
{
	Factory::instance().pause();
}

void ResourceImport::Service::resume()
{
	Factory::instance().resume();
}

void ResourceImport::Service::terminate()
{
	Factory::instance().terminate();
}

void ResourceImport::Service::clear()
{
	Factory::instance().clear();
}

#endif