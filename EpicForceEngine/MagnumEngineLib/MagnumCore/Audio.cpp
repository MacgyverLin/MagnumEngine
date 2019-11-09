///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Audio.h"
#include "AudioSourceBase.h"
#include "AudioListenerBase.h"
#include "fmod.hpp"
#include "fmod_errors.h"
using namespace Magnum;

///////////////////////////////////////////////////////////////////////////////////
Audio::Manager *Audio::Manager::_instance = 0;

namespace Magnum
{

/**
* AudioDesc. The Imple class for Audio Service by using FMOD Sound Engine
*/
class AudioDesc
{
public:
	AudioDesc()
	: system(0)
	, masterChannelGroup(0)
	, bgmChannelGroup(0)
	, sfxChannelGroup(0)
	{
	}

	~AudioDesc()
	{
	}

	bool initiate()
	{
		FMOD_RESULT      result;
		unsigned int     version;
		int              key, numdrivers;
		FMOD_SPEAKERMODE speakermode;
		FMOD_CAPS        caps;
		char             name[256];

		//	Create a System object and initialize.
		result = FMOD::System_Create(&system);
		if(result != FMOD_OK)
			return false;
    
		result = system->getVersion(&version);
		if(result != FMOD_OK)
			return false;
		if(version < FMOD_VERSION)
		{
			debug("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
			return false;
		}
    
		result = system->getNumDrivers(&numdrivers);
		if(result != FMOD_OK)
			return false;

		if (numdrivers == 0)
		{
			result = system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
			if(result != FMOD_OK)
				return false;
		}
		else
		{
			result = system->getDriverCaps(0, &caps, 0, &speakermode);
			if(result != FMOD_OK)
				return false;

			result = system->setSpeakerMode(speakermode);       // Set the user selected speaker mode.
			if(result != FMOD_OK)
				return false;

			if(caps & FMOD_CAPS_HARDWARE_EMULATED)             // The user has the 'Acceleration' slider set to off!  This is really bad for latency!.
			{                                                  // You might want to warn the user about this.
				result = system->setDSPBufferSize(1024, 10);
				if(result != FMOD_OK)
					return false;
			}

			result = system->getDriverInfo(0, name, 256, 0);
			if(result != FMOD_OK)
				return false;

			if (strstr(name, "SigmaTel"))   // Sigmatel sound devices crackle for some reason if the format is PCM 16bit.  PCM floating point output seems to solve it.
			{
				result = system->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0,0, FMOD_DSP_RESAMPLER_LINEAR);
				if(result != FMOD_OK)
					return false;
			}
		}

		result = system->init(100, FMOD_INIT_NORMAL, 0);
		if (result == FMOD_ERR_OUTPUT_CREATEBUFFER)         // Ok, the speaker mode selected isn't supported by this soundcard.  Switch it back to stereo...
		{
			result = system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
			if(result != FMOD_OK)
				return false;
            
			result = system->init(100, FMOD_INIT_NORMAL, 0); // ... and re-init.
			if(result != FMOD_OK)
				return false;
		}

		float distancefactor = 1.0f;						// 1.0 unit per meter
		//	Set the distance units. (meters/feet etc).
		result = system->set3DSettings(1.0, distancefactor, 1.0f);
		if(result != FMOD_OK)
			return false;

		result = system->createChannelGroup("BGM", &bgmChannelGroup);
		if(result != FMOD_OK)
			return false;
		
		result = system->createChannelGroup("SFX", &sfxChannelGroup);
		if(result != FMOD_OK)
			return false;

		result = system->getMasterChannelGroup(&masterChannelGroup);
		if(result != FMOD_OK)
			return false;

		result = masterChannelGroup->addGroup(bgmChannelGroup);
		if(result != FMOD_OK)
			return false;

		result = masterChannelGroup->addGroup(sfxChannelGroup);
		if(result != FMOD_OK)
			return false;

		return true;
	}

	void process(float dt)
	{
		FMOD_RESULT      result;

        result = system->update();
	}

	void pause()
	{
	}

	void resume()
	{
	}

	void terminate()
	{
		FMOD_RESULT      result;

		if(bgmChannelGroup)
		{
			result = bgmChannelGroup->release();
			assert(result == FMOD_OK);

			bgmChannelGroup = 0;
		}

		if(sfxChannelGroup)
		{
			result = sfxChannelGroup->release();
			assert(result == FMOD_OK);

			sfxChannelGroup = 0;
		}

		if(system)
		{
			result = system->close();
			assert(result == FMOD_OK);

			result = system->release();
			assert(result == FMOD_OK);

			system = 0;
		}
	}

	void clear()
	{
	}

    FMOD::System		*system;
	FMOD::ChannelGroup	*masterChannelGroup;
	FMOD::ChannelGroup	*bgmChannelGroup;
	FMOD::ChannelGroup	*sfxChannelGroup;
};

};

Audio::Manager::Manager()
: handle(0)
{
	assert(_instance==0);

	_instance = this;

	handle = (void *)(new AudioDesc());
	assert(handle);

	AudioDesc *ad = (AudioDesc *)handle;
}

Audio::Manager::~Manager()
{
	assert(_instance!=0);

	AudioDesc *ad = (AudioDesc *)handle;
	assert(ad);

	delete ad;
	handle = 0;

	_instance = 0;
}

void Audio::Manager::setMasterVolume(float volume)
{
	AudioDesc *ad = (AudioDesc *)handle;
	assert(ad);

	ad->masterChannelGroup->setVolume(volume);
}

float Audio::Manager::getMasterVolume() const
{
	AudioDesc *ad = (AudioDesc *)handle;
	assert(ad);

	float volume;
	ad->masterChannelGroup->getVolume(&volume);

	return volume;
}

void Audio::Manager::setBGMVolume(float volume)
{
	AudioDesc *ad = (AudioDesc *)handle;
	assert(ad);

	ad->bgmChannelGroup->setVolume(volume);
}

void Audio::Manager::setSFXVolume(float volume)
{
	AudioDesc *ad = (AudioDesc *)handle;
	assert(ad);

	ad->sfxChannelGroup->setVolume(volume);
}

float Audio::Manager::getBGMVolume() const
{
	AudioDesc *ad = (AudioDesc *)handle;
	assert(ad);

	float volume;
	ad->bgmChannelGroup->getVolume(&volume);

	return volume;
}

float Audio::Manager::getSFXVolume() const
{
	AudioDesc *ad = (AudioDesc *)handle;
	assert(ad);

	float volume;
	ad->sfxChannelGroup->getVolume(&volume);

	return volume;
}

void *Audio::Manager::getSystemHandle()
{
	AudioDesc *ad = (AudioDesc *)handle;
	assert(ad);

	return ad->system;
}

void *Audio::Manager::getBGMChannelGroupHandle()
{
	AudioDesc *ad = (AudioDesc *)handle;
	assert(ad);

	return ad->bgmChannelGroup;
}

void *Audio::Manager::getSFXChannelGroupHandle()
{
	AudioDesc *ad = (AudioDesc *)handle;
	assert(ad);

	return ad->sfxChannelGroup;
}

bool Audio::Manager::initiate()
{
	AudioDesc *ad = (AudioDesc *)handle;
	assert(ad);

	return ad->initiate();
}

void Audio::Manager::process()
{
	if(!Stage::isEditorMode())
	{
		AudioDesc *ad = (AudioDesc *)handle;
		assert(ad);

		float dt = (((float)Stage::elapsed())/1000.0f);

		FMOD_RESULT result;
		FMOD::System *system				= (FMOD::System *)(getSystemHandle());
		FMOD::ChannelGroup *bgmChannelGroup = (FMOD::ChannelGroup *)(getBGMChannelGroupHandle());
		FMOD::ChannelGroup *sfxChannelGroup = (FMOD::ChannelGroup *)(getSFXChannelGroupHandle());

		///////////////////////////////////////////////////
		// find and update Listener, if any
		AudioListenerBase *firstListener = 0;
		for(int i=0; i<audioListeners.length(); i++)
		{
			firstListener = audioListeners[i];
			break;
		}
	
		if(firstListener && firstListener->getEnabled() && firstListener->getOwner().getActive())
		{
			// has at least 1 active listner

			Component::Owner &owner = firstListener->getOwner();
			Vector3 pos		=  owner.getGlobalPosition();
			Vector3 forward = -owner.getGlobalZAxis();
			Vector3 up	    =  owner.getGlobalYAxis();
			Vector3 vel		= Vector3::ZERO;

			result = system->set3DListenerAttributes(0,  
													 (const FMOD_VECTOR *)(&pos)    , (const FMOD_VECTOR *)(&vel),
													 (const FMOD_VECTOR *)(&forward), (const FMOD_VECTOR *)(&up) );
			assert(result==FMOD_OK);

			ad->masterChannelGroup->setMute(false);
		}
		else
		{
			// no active listner
			ad->masterChannelGroup->setMute(true);
		}
	
		///////////////////////////////////////////////////
		// find and update all sources
		for(int i=0; i<audioSources.length(); i++)
		{
			if(audioSources[i]->getEnabled() && audioSources[i]->getOwner().getActive())
			{
				FMOD::Channel *channel = (FMOD::Channel *)audioSources[i]->getChannelHandle();

				Component::Owner &owner = audioSources[i]->getOwner();

				Vector3 pos = owner.getGlobalPosition();
				Vector3 vel = Vector3::ZERO;
				result = channel->set3DAttributes((const FMOD_VECTOR *)&pos, (const FMOD_VECTOR *)&vel);

				if(channel)
					result = channel->setMute(false);
			}
			else
			{
				FMOD::Channel *channel = (FMOD::Channel *)audioSources[i]->getChannelHandle();

				if(channel)
					result = channel->setMute(true);
			}
		}

		ad->process(dt);
	}
}

void Audio::Manager::pause()
{
	AudioDesc *ad = (AudioDesc *)handle;
	assert(ad);

	ad->pause();
}

void Audio::Manager::resume()
{
	AudioDesc *ad = (AudioDesc *)handle;
	assert(ad);

	ad->resume();
}

void Audio::Manager::terminate()
{
	AudioDesc *ad = (AudioDesc *)handle;
	assert(ad);

	audioSources.destroy();

	ad->terminate();
}

void Audio::Manager::clear()
{
	AudioDesc *ad = (AudioDesc *)handle;
	assert(ad);

	audioSources.destroy();

	ad->clear();
}

Audio::Manager &Audio::Manager::instance()
{
	assert(_instance);

	return *_instance;
}

void Audio::Manager::beginRender(const AudioListenerBase &audioListener_)
{
	AudioDesc *ad = (AudioDesc *)handle;
	assert(ad);
}

void Audio::Manager::endRender(const AudioListenerBase &audioListener_)
{
	AudioDesc *ad = (AudioDesc *)handle;
	assert(ad);
}

///////////////////////////////////////////////////////////////////////////////////
bool Audio::Service::initiate()
{
	return Audio::Manager::instance().initiate();
}

void Audio::Service::process()
{
	Audio::Manager::instance().process();
}

void Audio::Service::pause()
{
	Audio::Manager::instance().pause();
}

void Audio::Service::resume()
{
	Audio::Manager::instance().resume();
}

void Audio::Service::terminate()
{
	Audio::Manager::instance().terminate();
}

void Audio::Service::clear()
{
	Audio::Manager::instance().clear();
}