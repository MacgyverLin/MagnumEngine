///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Scene_h_
#define _Scene_h_

#include "Array.h"
#include "Delegate.h"
#include "Entity.h"

namespace Magnum
{

class Scene
{
public:
	static int counter;
	enum TransitionMode
	{
		NONE,	
		EXITING,	
		ENTERING
	};

	Scene();
	virtual ~Scene();

	static bool is(const char *name);						//	returns true if name matches (ignore case) current scene 
	static const char *next();								//	returns next scene name or 0 is no scene has been activated
	static const char *name();								//	returns current scene name
	static void transit(const char *name);					//	notifies scene service to activate a scene, scene is not loadded until the scene service is processing
	static void pushTransit(const char *name);				//	notifies scene service to activate a scene, scene is not loadded until the scene service is processing
	static void popTransit();								//	notifies scene service to activate a scene, scene is not loadded until the scene service is processing
	static bool transitioning();							//	true before enter() and after exit()
	static bool running();									//	true after enter() and before exit();
	static bool loaded();									//	true after contruct() and before destructor is called
protected:
	virtual void onConstruct();								//	called after all constructors
	virtual void onEnter();									//	called after enter transition is done
	virtual void onExit();									//	called before exit transition starts
	virtual void onUpdate(float dt);						//	called each cycle while scene is up and running
	virtual void onPause();									//	called when about to paused
	virtual void onResume();								//	called when about to resume
	virtual bool onTransition(TransitionMode);				//	called while transitioning returning false stops transition mode
private:
	virtual void construct();
	virtual void enter();
	virtual void exit();
	virtual void update(float dt);
	virtual void pause();
	virtual void resume();
	virtual bool transition(TransitionMode);
public: 
	#define NAME_MAX (63)
public:
	class ICreator
	{
	public:
		ICreator(const char *name_, bool overlay=true);
		virtual Scene *create()=0;

		char name[NAME_MAX+1];
		int hits;
		int index;
		bool overlay;
	};

	template<typename T> class Creator : public ICreator
	{
	public:
		Creator(const char *name, bool overlay=true)
		: ICreator(name, overlay)
		{
		}

		virtual Scene *create()
		{
			return new T();
		}
	};

public:

	enum
	{
		MAX_NUM_SCENES = 150
	};

	class Factory
	{
	public:
		Factory();
		~Factory();
		static Factory &instance();

		ICreator *current()					{	return _current;	}
		ICreator *next()					{	return _next;		}
		Scene *scene()						{	return _scene;		}
		ICreator *find(const char *name);
		ICreator *transit(const char *name);
		ICreator *pushTransit(const char *name);
		ICreator *popTransit();
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
		typedef Array<ICreator *> Scenes;
		Scenes scenes;
		static bool overlay;
	private:
		ICreator *_current;
		ICreator *_next;
		Stack<ICreator *, MAX_NUM_SCENES> sceneStacks;
		Scene *_scene;
	}; 

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