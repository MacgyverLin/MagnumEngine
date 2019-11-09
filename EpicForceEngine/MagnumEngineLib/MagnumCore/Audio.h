///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Audio_h_
#define _Audio_h_

#include "Stage.h"
#include "List.h"
#include "EString.h"
#include "Array.h"
#include "ColorRGBA.h"
#include "Matrix4.h"
using namespace Magnum;

namespace Magnum
{

class AudioListenerBase;
class AudioSourceBase;
class AudioComponent;

/**
* Audio Services.
*/
class Audio
{
friend class AudioComponent;
public:
	/**
	* Audio Manager manager the all AudioListener, AudioSource, Volumes, Parameters
	*/
	class Manager
	{
	friend class Audio;
	friend class AudioComponent;
	friend class AudioListenerBase;
	friend class AudioSourceBase;
	public:
		/**
		* Audio::Manager Constructor.
		* To Construct the Audio::Manager.
		*/
		Manager();

		/**
		* Audio::Manager Destructor.
		* To Destruct Audio::Manager.
		*/
		virtual ~Manager();

		/**
		* Set the Master Volume. 
		* @param volume, float which specify the volume from 0-1
		*/
		void setMasterVolume(float volume);

		/**
		* Set the BGM Volume. 
		* @param volume, float which specify the volume from 0-1
		*/
		void setBGMVolume(float volume);

		/**
		* Set the SFX Volume. 
		* @param volume, float which specify the volume from 0-1
		*/
		void setSFXVolume(float volume);

		/**
		* Get the Master Volume. 
		* @return float, the volume from 0-1
		*/
		float getMasterVolume() const;

		/**
		* Get the BGM Volume. 
		* @return float, the volume from 0-1
		*/
		float getBGMVolume() const;

		/**
		* Get the SFX Volume. 
		* @return float, the volume from 0-1
		*/
		float getSFXVolume() const;

		/**
		* Get the handle of the Audio System. 
		* @return void *
		*/
		void *getSystemHandle();
	protected:
	private:
		void *getBGMChannelGroupHandle();
		void *getSFXChannelGroupHandle();

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

		void beginRender(const AudioListenerBase &audioListener_);
		void endRender(const AudioListenerBase &audioListener_);
	public:
	private:
		void							*handle;
		
		Vector<AudioListenerBase *>		audioListeners;
		Vector<AudioSourceBase *>		audioSources;
	public:
		static Manager					&instance();
	private:
		static Manager					*_instance;
	};
////////////////////////////////////////////////////////////////////////////////////
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

};

#endif
