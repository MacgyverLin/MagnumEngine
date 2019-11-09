///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Audio.h"
#include "AudioClip.h"
#include "fmod.hpp"
#include "fmod_errors.h"
using namespace Magnum;

AudioClip::Data::Data()
{
}

AudioClip::Data::~Data()
{
}

void AudioClip::Data::read(InputStream &is)
{
}

void AudioClip::Data::write(OutputStream &os) const
{
}

//////////////////////////////////////////////////////////////////////////////////////
AudioClip::Resource::Resource(const char *path_)
: ResourceAccess(path_)
, soundHandle(0)
{
}

AudioClip::Resource::~Resource()
{
	onDestroy();
}

unsigned char *AudioClip::Resource::onCreate(int length_)
{
	buffer.resize(length_);

	return &buffer[0];
}

void AudioClip::Resource::onLoaded()
{
	MemInputStream is(&buffer[0], buffer.length());

	FMOD_RESULT result;
	FMOD::System *system = (FMOD::System *)(Audio::Manager::instance().getSystemHandle());

	FMOD_CREATESOUNDEXINFO exinfo;
	System::memset(&exinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
    exinfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
    exinfo.length = buffer.length();

	FMOD::Sound *sound;
	result = system->createSound((char *)&buffer[0], FMOD_HARDWARE | FMOD_LOOP_NORMAL | FMOD_3D | FMOD_OPENMEMORY, &exinfo, &sound);
	assert(result == FMOD_OK);

	soundHandle = sound;

	buffer.destroy();
}

void AudioClip::Resource::onDestroy()
{
	FMOD::Sound *sound = (FMOD::Sound *)soundHandle;
	if(sound)
	{
		sound->release();
		sound			 = 0;
		soundHandle		= 0;
	}

	buffer.destroy();
}

void *AudioClip::Resource::getHandle() const
{
	return soundHandle;
}

///////////////////////////////////////////////////////////////////////////////////
#ifdef ENABLE_RESOURCE_IMPORT
AudioClip::ResourceImporter::ResourceImporter(const char *name)
: ResourceImport(name)
{
}

AudioClip::ResourceImporter::~ResourceImporter()
{
}

bool AudioClip::ResourceImporter::initiate()
{
	return true;
}

void AudioClip::ResourceImporter::terminate()
{
}

bool AudioClip::ResourceImporter::onExportFile(const char *srcFilename_, const char *dstFilename_)
{
	// collect Options
	this->defaultExportFileFunc(srcFilename_, dstFilename_);

	return true;
}

bool AudioClip::ResourceImporter::onDeleteFile(const char *srcFilename_)
{
	return this->defaultDeleteFileFunc(srcFilename_);
}
#endif

///////////////////////////////////////////////////////////////////////////////////
AudioClip::AudioClip(Component::Owner &owner_)
: AudioSourceBase(owner_)
, resource(0)
{
	setAudioClipPath(ResourcePath("default/default", "audioclip"));
}

AudioClip::~AudioClip()
{
}

bool AudioClip::play(bool loop)
{
	FMOD::System	   *system			= (FMOD::System	 	  *)(getSystemHandle()		  );
	FMOD::ChannelGroup *bgmChannelGroup = (FMOD::ChannelGroup *)(getBGMChannelGroupHandle());
	FMOD::ChannelGroup *sfxChannelGroup = (FMOD::ChannelGroup *)(getSFXChannelGroupHandle());

	FMOD_RESULT result;
	result = system->playSound(channelHandle ? FMOD_CHANNEL_REUSE : FMOD_CHANNEL_FREE, 
		                       (FMOD::Sound *)resource->getHandle(), 
							   true, 
							   (FMOD::Channel **)(&channelHandle));
	assert(result==FMOD_OK);
	if(!channelHandle)
		return false;

	FMOD::Channel *channel = (FMOD::Channel *)channelHandle;
	channel->setChannelGroup(sfxChannelGroup);

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

bool AudioClip::onConstruct()
{
	assert(resource==0);

	resource = AudioClip::Resource::get(getAudioClipPath().getPath());
	//resource = AudioClip::Resource::get("default/default");
	if(!resource)
		return false;

	resource->addReference();
	return true;
}

void AudioClip::onStart()
{
	//play(isLoopEnabled());
}

void AudioClip::onUpdate(float dt)
{
}

void AudioClip::onPause()
{
}

void AudioClip::onResume()
{
}

void AudioClip::onStop()
{
}

void AudioClip::onDestruct()
{
	FMOD_RESULT result;
	FMOD::System *system = (FMOD::System *)(getSystemHandle());
	FMOD::Channel *channel = (FMOD::Channel *)channelHandle;
	if(channel)
	{
		channel->stop();
		channel			= 0;
		channelHandle	= 0;
	}

	if(resource)
	{
		resource->release();
		resource = 0;
	}
}

void AudioClip::onDebugRender(IComponentDebugRenderer &debugRenderer)
{
	debugRenderer.renderWireBox(this->getOwner().getGlobalTransform(),
								ColorRGBA(0.0, 0.0, 1.0, 0.5), 
								Vector3(1, 1, 1));
}