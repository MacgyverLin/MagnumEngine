///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Service_h_
#define _Service_h_

#include "Array.h"
#include "List.h"

namespace Magnum
{

/**
* This is interface for the Services
*/
class IService : public Link<IService>
{
public:
	/**
	* IService Constructor.
	* To Construct the IService.
	*/
	IService(const char *name);

	/**
	* IService Destructor.
	* To Destruct IService.
	*/
	virtual ~IService();

public:
	/**
	* Initiate the Services
	* @return true if success, false if failed
	*/
	virtual bool initiate()=0;

	/**
	* Update the Services
	*/
	virtual void process()=0;

	/**
	* Called when the application is pause(e.g system bring the app to background, let the service to release resources)
	*/
	virtual void pause()=0;

	/**
	* Called when the application is resume(e.g system bring back the app from background, let the service to reload resources)
	*/
	virtual void resume()=0;

	/**
	* Terminate the Services, called when the app is terminate.
	*/
	virtual void terminate()=0;

	/**
	* Call when the services needed to be clean up, e.g. during scene transition.
	*/
	virtual void clear()=0;
public:
	char name[15+1];
};

template<typename T> class Service : public IService
{
public:
	Service(const char *name)
	: IService(name)
	{
	}

	virtual ~Service()
	{
	}

	/**
	* Initiate the Services
	* @return true if success, false if failed
	*/
	virtual bool initiate()
	{
		return T::initiate();
	}

	/**
	* Update the Services
	*/
	virtual void process()
	{
		T::process();
	}

	/**
	* Called when the application is pause(e.g system bring the app to background, let the service to release resources)
	*/
	virtual void pause()
	{
		T::pause();
	}

	/**
	* Called when the application is resume(e.g system bring back the app from background, let the service to reload resources)
	*/
	virtual void resume()
	{
		T::resume();
	}

	/**
	* Terminate the Services, called when the app is terminate.
	*/
	virtual void terminate()
	{
		T::terminate();
	}

	/**
	* Call when the services needed to be clean up, e.g. during scene transition.
	*/
	virtual void clear()
	{
		T::clear();
	}
};

class ServiceManager
{
public:
	ServiceManager();
	~ServiceManager();
public:
	static ServiceManager &instance();
	static IService *current();
	static bool processing(IService *service);
	static bool processing(const char *service_name);

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
public:
	List<IService> list;
};

};

#endif
