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
#include "fmod.hpp"
#include "fmod_errors.h"
using namespace Magnum;

AudioSourceBase::AudioSourceBase(Component::Owner &owner_)
: AudioComponent(owner_)
, channelHandle(0)
, paused(false)
, muteEnabled(false)
, bypassEffectsEnabled(false)
, loopEnabled(false)
, priority(128)
, volume(1)
, pitch(1)
, dopplerLevel(1)
, volumeDecayMode(LogorithmRollOff)
, minDistance(1)
, panLevel(1)
, spread(0)
, maxDistance(500)
{
	Audio::Manager::instance().audioSources.push() = this;
}

AudioSourceBase::~AudioSourceBase()
{
	int idx = Audio::Manager::instance().audioSources.search(this);
	if(idx>=0)
	{
		Audio::Manager::instance().audioSources.remove(idx);
	}
}

void AudioSourceBase::stop()
{
	FMOD_RESULT result;
	FMOD::System *system = (FMOD::System *)(getSystemHandle());
	FMOD::Channel *channel = (FMOD::Channel *)channelHandle;

	if(channel)
	{
		FMOD_RESULT result;
		result = channel->stop();
		channel = 0;
	}
}

void AudioSourceBase::pause()
{
	FMOD_RESULT result;
	FMOD::System *system = (FMOD::System *)(getSystemHandle());
	FMOD::Channel *channel = (FMOD::Channel *)channelHandle;

	paused		= true;
	if(channel)
		channel->setPaused(true);
}

void AudioSourceBase::resume()
{
	FMOD_RESULT result;
	FMOD::System *system = (FMOD::System *)(getSystemHandle());
	FMOD::Channel *channel = (FMOD::Channel *)channelHandle;

	paused		= false;
	if(channel)
		channel->setPaused(false);
}

void AudioSourceBase::setMuteEnable(bool muteEnable_)
{
	FMOD_RESULT result;
	FMOD::System *system = (FMOD::System *)(getSystemHandle());
	FMOD::Channel *channel = (FMOD::Channel *)channelHandle;

	muteEnabled = muteEnable_;

	if(channel)
	{
		channel->setMute(muteEnabled);
	}
}

void AudioSourceBase::setBypassEffectsEnable(bool bypassEffectsEnable_)
{
	FMOD_RESULT result;
	FMOD::System *system = (FMOD::System *)(getSystemHandle());
	FMOD::Channel *channel = (FMOD::Channel *)channelHandle;

	bypassEffectsEnabled = bypassEffectsEnable_;

	if(channel)
	{
		assert(0);
	}
}

void AudioSourceBase::setLoopEnable(bool loopEnable_)
{
	FMOD_RESULT result;
	FMOD::System *system = (FMOD::System *)(getSystemHandle());
	FMOD::Channel *channel = (FMOD::Channel *)channelHandle;

	loopEnabled = loopEnable_;

	if(channel)
	{
		if(loopEnable_)
		{
			//result = channel->setMode(FMOD_LOOP_NORMAL);
			result = channel->setLoopCount(-1);
		}
		else
		{
			//result = channel->setMode(FMOD_LOOP_OFF);
			result = channel->setLoopCount(0);
		}
	}
}

void AudioSourceBase::setPriority(int priority_)
{
	FMOD_RESULT result;
	FMOD::System *system = (FMOD::System *)(getSystemHandle());
	FMOD::Channel *channel = (FMOD::Channel *)channelHandle;

	priority = priority_;

	if(channel)
	{
		channel->setPriority(priority);
	}
}

void AudioSourceBase::setVolume(float volume_)
{
	FMOD_RESULT result;
	FMOD::System *system = (FMOD::System *)(getSystemHandle());
	FMOD::Channel *channel = (FMOD::Channel *)channelHandle;

	volume = volume_;

	if(channel)
	{
		channel->setVolume(volume);
	}
}

void AudioSourceBase::setPitch(float pitch_)
{
	FMOD_RESULT result;
	FMOD::System *system = (FMOD::System *)(getSystemHandle());
	FMOD::Channel *channel = (FMOD::Channel *)channelHandle;

	pitch = pitch_;

	if(channel)
	{
		FMOD::Sound *sound;
		result = channel->getCurrentSound(&sound);

		if(sound)
		{
			float frequency;
			sound->getDefaults(&frequency, 0, 0, 0);
			channel->setFrequency(frequency * pitch);
		}
	}
}

void AudioSourceBase::set3DDopplerLevel(float dopplerLevel_)
{
	FMOD_RESULT result;
	FMOD::System *system = (FMOD::System *)(getSystemHandle());
	FMOD::Channel *channel = (FMOD::Channel *)channelHandle;

	dopplerLevel = dopplerLevel_;

	if(channel)
	{
		channel->set3DDopplerLevel(dopplerLevel_);
	}
}

void AudioSourceBase::set3DVolumeDecayMode(AudioSourceBase::DecayMode volumeDecayMode_)
{
	FMOD_RESULT result;
	FMOD::System *system = (FMOD::System *)(getSystemHandle());
	FMOD::Channel *channel = (FMOD::Channel *)channelHandle;

	volumeDecayMode = volumeDecayMode_;

	if(channel)
	{
		assert(0);
	}
}

void AudioSourceBase::set3DMinDistance(float minDistance_)
{
	FMOD_RESULT result;
	FMOD::System *system = (FMOD::System *)(getSystemHandle());
	FMOD::Channel *channel = (FMOD::Channel *)channelHandle;

	minDistance = minDistance_;

	if(channel)
	{
		channel->set3DMinMaxDistance(minDistance, maxDistance);
	}
}

void AudioSourceBase::set3DPanLevel(float panLevel_)
{
	FMOD_RESULT result;
	FMOD::System *system = (FMOD::System *)(getSystemHandle());
	FMOD::Channel *channel = (FMOD::Channel *)channelHandle;

	panLevel = panLevel_;

	if(channel)
	{
		channel->set3DPanLevel(panLevel);
	}
}

void AudioSourceBase::set3DSpread(float spread_)
{
	FMOD_RESULT result;
	FMOD::System *system = (FMOD::System *)(getSystemHandle());
	FMOD::Channel *channel = (FMOD::Channel *)channelHandle;

	spread = spread_;

	if(channel)
	{
		channel->set3DSpread(spread);
	}
}

void AudioSourceBase::set3DMaxDistance(float maxDistance_)
{
	FMOD_RESULT result;
	FMOD::System *system = (FMOD::System *)(getSystemHandle());
	FMOD::Channel *channel = (FMOD::Channel *)channelHandle;

	maxDistance = maxDistance_;

	if(channel)
	{
		channel->set3DMinMaxDistance(minDistance, maxDistance);
	}
}

bool AudioSourceBase::isPaused() const
{
	return paused;
}

bool AudioSourceBase::isMuteEnabled() const
{
	return muteEnabled;
}

bool AudioSourceBase::isBypassEffectsEnabled() const
{
	return bypassEffectsEnabled;
}

bool AudioSourceBase::isLoopEnabled() const
{
	return loopEnabled;
}

int AudioSourceBase::getPriority() const
{
	return priority;
}

float AudioSourceBase::getVolume() const
{
	return volume;
}

float AudioSourceBase::getPitch() const
{
	return pitch;
}

float AudioSourceBase::get3DDopplerLevel() const
{
	return dopplerLevel;
}

AudioSourceBase::DecayMode AudioSourceBase::get3DVolumeDecayMode() const
{
	return volumeDecayMode;
}

float AudioSourceBase::get3DMinDistance() const
{
	return minDistance;
}

float AudioSourceBase::get3DPanLevel() const
{
	return panLevel;
}

float AudioSourceBase::get3DSpread() const
{
	return spread;
}

float AudioSourceBase::get3DMaxDistance() const
{
	return maxDistance;
}

void *AudioSourceBase::getChannelHandle()
{
	return channelHandle;
}