///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Audio.h"
#include "AudioStream.h"
#include "fmod.hpp"
#include "fmod_errors.h"
using namespace Magnum;

///////////////////////////////////////////////////////////////////////////////////
#ifdef ENABLE_RESOURCE_IMPORT
AudioStream::ResourceImporter::ResourceImporter(const char *name)
: ResourceImport(name)
{
}

AudioStream::ResourceImporter::~ResourceImporter()
{
}

bool AudioStream::ResourceImporter::initiate()
{
	return true;
}

void AudioStream::ResourceImporter::terminate()
{
}

bool AudioStream::ResourceImporter::onExportFile(const char *srcFilename_, const char *dstFilename_)
{
	// collect Options
	this->defaultExportFileFunc(srcFilename_, dstFilename_);

	return true;
}

bool AudioStream::ResourceImporter::onDeleteFile(const char *srcFilename_)
{
	return this->defaultDeleteFileFunc(srcFilename_);
}
#endif

///////////////////////////////////////////////////////////////////////////////////
AudioStream::AudioStream(Component::Owner &owner_)
: AudioSourceBase(owner_)
, soundHandle(0)
{
	setAudioStreamPath(ResourcePath("demo/26-a-fresh-youngster", "audiostream"));
}

AudioStream::~AudioStream()
{
}

bool AudioStream::play(bool loop)
{
	FMOD::System	   *system			= (FMOD::System	 	  *)(getSystemHandle()		  );
	FMOD::ChannelGroup *bgmChannelGroup = (FMOD::ChannelGroup *)(getBGMChannelGroupHandle());
	FMOD::ChannelGroup *sfxChannelGroup = (FMOD::ChannelGroup *)(getSFXChannelGroupHandle());

	FMOD_RESULT result;
	result = system->playSound(channelHandle ? FMOD_CHANNEL_REUSE : FMOD_CHANNEL_FREE, 
		                       (FMOD::Sound *)soundHandle, 
							   true, 
							   (FMOD::Channel **)(&channelHandle));
	assert(result==FMOD_OK);
	if(!channelHandle)
		return false;

	FMOD::Channel *channel = (FMOD::Channel *)channelHandle;
	channel->setChannelGroup(bgmChannelGroup);

	if(isPaused())
		pause();
	else
		resume();

	setMuteEnable(isMuteEnabled());
	// setBypassEffectsEnable(bypassEffectsEnabled);
	setLoopEnable(loop);
	setPriority(getPriority());
	setVolume(getVolume());
	setPitch(getPitch());
	set3DDopplerLevel(get3DDopplerLevel());
	//set3DVolumeDecayMode(get3DVolumeDecayMode());
	set3DMinDistance(get3DMinDistance());
	set3DPanLevel(get3DPanLevel());
	set3DSpread(get3DSpread());
	set3DMaxDistance(get3DMaxDistance());

	return true;
}

bool AudioStream::onConstruct()
{
	FMOD_RESULT result;
	FMOD::System *system   = (FMOD::System  *)(getSystemHandle());
	FMOD::Channel *channel = (FMOD::Channel *)channelHandle;
	FMOD::Sound   *sound   = (FMOD::Sound   *)soundHandle;
	
	if(channel)
	{
		result			= channel->stop();
		channel			= 0;
		channelHandle	= 0;
	}
	if(sound)
	{
		result			= sound->release();
		sound			= 0;
		soundHandle		= 0;
	}

	String path = String(Stage::getAssetRootDirectory()) + getAudioStreamPath().getPath() + "." + getAudioStreamPath().getExtension();
	//String path = String(Stage::getAssetRootDirectory()) + "demo/26-a-fresh-youngster.audiostream";

	///////////////////////////////////////////////
	result = system->createStream(path, FMOD_HARDWARE | FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound);
	if(result != FMOD_OK)
		return false;
	
	soundHandle = sound;
	
	return soundHandle!=0;
}

void AudioStream::onStart()
{
	// play(isLoopEnabled());
}

void AudioStream::onUpdate(float dt)
{
}

void AudioStream::onPause()
{
}

void AudioStream::onResume()
{
}

void AudioStream::onStop()
{
}

void AudioStream::onDestruct()
{
	FMOD_RESULT result;
	FMOD::System *system   = (FMOD::System  *)(getSystemHandle());
	FMOD::Channel *channel = (FMOD::Channel *)channelHandle;
	FMOD::Sound   *sound   = (FMOD::Sound   *)soundHandle;
	
	if(channel)
	{
		result			= channel->stop();
		channel			= 0;
		channelHandle	= 0;
	}
	if(sound)
	{
		result			= sound->release();
		sound			= 0;
		soundHandle		= 0;
	}
}

void AudioStream::onDebugRender(IComponentDebugRenderer &debugRenderer)
{
	debugRenderer.renderWireBox(this->getOwner().getGlobalTransform(),
								ColorRGBA(0.0, 0.0, 1.0, 0.5), 
								Vector3(1, 1, 1));
}