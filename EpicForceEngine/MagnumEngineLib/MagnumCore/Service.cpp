///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Stage.h"
#include "Service.h"
using namespace Magnum;

IService::IService(const char *name_)
: Link<IService>(*this)
{  
	memset(name,0,sizeof(name));
	strncpy(name,name_,sizeof(name)-1);
	ServiceManager::instance().list.insert(*this);
}

IService::~IService()
{
}

///////////////////////////////////////////////////////
static ServiceManager *_instance=0;
static IService *current_service=0;

ServiceManager::ServiceManager()
{
	_instance=this;
}

ServiceManager::~ServiceManager()
{
}

ServiceManager &ServiceManager::instance()
{
	return *_instance;
}

IService *ServiceManager::current()
{
	return current_service;
}

bool ServiceManager::processing(IService *service)
{
	return current_service==service;
}

bool ServiceManager::processing(const char *service_name)
{
	if(!current_service)
		return false;
	
	return strcasecmp(current_service->name, service_name)==0;
}

bool ServiceManager::initiate()
{
	info("\nInitiating services...\n");

	for(Link<IService> *s=list.first();s;s=s->next())
	{
		IService &service=*(IService *)s;
		info("Service: %s...\n",service.name);

		if( !service.initiate() )
		{
			Stage::_lastError = "Service: Error in Initialiing Service";
			return false;
		}
	}

	info("All Services initiate!\n\n");

	return true;
}

void ServiceManager::process()
{
	for(Link<IService> *s=list.first();s;s=s->next())
	{
		current_service=s->owner();

		current_service->process();
	}
}

void ServiceManager::pause()
{
	for(Link<IService> *s=list.first();s;s=s->next())
	{
		((IService *)s)->pause();
	}
}

void ServiceManager::resume()
{
	for(Link<IService> *s=list.first();s;s=s->next())
	{
		((IService *)s)->resume();
	}
}

void ServiceManager::terminate()
{
	for(Link<IService> *s=list.first();s;s=s->next())
	{
		((IService *)s)->terminate();
	}

	//info("All Services terminated!\n\n");
}

void ServiceManager::clear()
{
	for(Link<IService> *s=list.first();s;s=s->next())
	{
		((IService *)s)->clear();
	}
}