///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _AudioSourceBase_h_
#define _AudioSourceBase_h_

#include "Stage.h"
#include "Audio.h"
#include "AudioComponent.h"
using namespace Magnum;

namespace Magnum
{

/**
* AudioSourceBase.
* AudioSourceBase is the base class of all AudioSource component.
* @see AudioComponent
*/
class AudioSourceBase : public AudioComponent
{
friend class Audio::Manager;
public:
	enum DecayMode
	{
		LogorithmRollOff	= 0x00,					/**< Static Audio Level Fall off Logorithmatically	*/ 
		LinearRollOff		= 0x01,					/**< Static Audio Level Fall off Linearly			*/ 
		Custom				= 0x02,					/**< Static Audio Level Fall off Custom define		*/ 
	};

////////////////////////////////////////////////////////////////
	/**
	* AudioSourceBase Constructor.
	* To Construct the AudioSourceBase for the owner.
	* @param owner_, the Component::Owner which owns this component.
	*/
	AudioSourceBase(Component::Owner &owner_);

	/**
	* AudioSourceBase Destructor.
	* To Destruct AudioSourceBase and remove from its owner.
	*/
	virtual ~AudioSourceBase();

////////////////////////////////////////////////////////////////
	DECLARE_COMPONENT(AudioSourceBase, AudioComponent, false)

////////////////////////////////////////////////////////////////
	/**
	* Start playing the audio.
	* @param loop, if true the audio will rewind to beginning.
	*/
	virtual bool play(bool loop) = 0;

	/**
	* Stop playing the audio.
	*/
	void stop();

	/**
	* Pause the audio.
	*/
	void pause();

	/**
	* Resume the audio.
	*/
	void resume();

	/**
	* Mute/Unmute the audio Source
	* @param muteEnable_, if true mute the audio, else unmute
	*/
	void setMuteEnable(bool muteEnable_);

	/**
	* Enable/Disable Effect
	* @param bypassEffectsEnable_, if true Disable the audio Effect, else Enable audio effect
	*/
	void setBypassEffectsEnable(bool bypassEffectsEnable_);

	/**
	* Enable/Disable the looping
	* @param loopEnable_, if true loop the audio, else unloop
	*/
	void setLoopEnable(bool loopEnable_);

	/**
	* Set the priority of the audio. If all audio channels are fully occupied, lower priority will be ignored. 
	* @param priority_, the priority of the Audio
	*/
	void setPriority(int priority_);

	/**
	* Set the volume of the audio source, from 0 to 1
	* @param volume_, the volume of the Audio Source.
	*/
	void setVolume(float volume_);

	/**
	* Set the pitch of the audio source
	* @param pitch_, the pitch of the Audio Source. the frequency of the audio will be scale by the this parameter
	*/
	void setPitch(float pitch_);

	/**
	* Set the doppler Level
	* @param dopplerLevel_, the dopplerLevel of the Audio Source. Adjust the dopper level will scale the effect of velocity
	*/
	void set3DDopplerLevel(float dopplerLevel_);

	/**
	* Set the volume Decay Mode
	* @param volumeDecayMode_, the volumeDecayMode of the Audio Source. either LogorithmRollOff, LinearRollOff or Custom.
	*/
	void set3DVolumeDecayMode(AudioSourceBase::DecayMode volumeDecayMode_);

	/**
	* Set the min Distance
	* @param minDistance_, the minDistance of the Audio Source. It is the minimun distance, that the audio can be heard
	*/
	void set3DMinDistance(float minDistance_);

	/**
	* Set the pan Level
	* @param panLevel_, the panLevel of the Audio Source. From -1 to 1, -1 being left, 1 being right
	*/
	void set3DPanLevel(float panLevel_);

	/**
	* Set the spread
	* @param spread_, the spread of the Audio Source. From -1 to 1, -1 being left, 1 being right
	*/
	void set3DSpread(float spread_);

	/**
	* Set the max Distance
	* @param maxDistance_, the maxDistance of the Audio Source. It is the maximun distance, that the audio can be heard
	*/
	void set3DMaxDistance(float maxDistance_);

	/**
	* Check of audio is Paused.
	* @return, bool, true if audio is being paused, false if audio is not being paused
	*/
	bool isPaused() const;

	/**
	* Check of audio is Muted.
	* @return, bool, true if audio is being muted, false if audio is not being muted
	*/
	bool isMuteEnabled() const;

	/**
	* Check of audio effect is bypassed.
	* @return, bool, true if audio effect is bypassed, false if audio effect is not bypassed.
	*/
	bool isBypassEffectsEnabled() const;

	/**
	* Check of audio is looped.
	* @return, bool, true if audio is being muted, false if audio is not being muted
	*/
	bool isLoopEnabled() const;

	/**
	* Get the priority of the audio. If all audio channels are fully occupied, lower priority will be ignored. 
	* @return int, the priority of the Audio
	*/
	int getPriority() const;

	/**
	* Get the volume of the audio source, from 0 to 1
	* @return float, the volume of the Audio Source.
	*/
	float getVolume() const;

	/**
	* Get the pitch of the audio source
	* @return float, the pitch of the Audio Source. the frequency of the audio will be scale by the this parameter
	*/
	float getPitch() const;

	/**
	* Get the doppler Level
	* @return float, the dopplerLevel of the Audio Source. Adjust the dopper level will scale the effect of velocity
	*/
	float get3DDopplerLevel() const;

	/**
	* Get the volume Decay Mode
	* @return float, the volumeDecayMode of the Audio Source. either LogorithmRollOff, LinearRollOff or Custom.
	*/
	DecayMode get3DVolumeDecayMode() const;

	/**
	* Get the min Distance
	* @return float, the minDistance of the Audio Source. It is the minimun distance, that the audio can be heard
	*/
	float get3DMinDistance() const;

	/**
	* Get the pan Level
	* @return float, the panLevel of the Audio Source. From -1 to 1, -1 being left, 1 being right
	*/
	float get3DPanLevel() const;

	/**
	* Get the spread
	* @return , the spread of the Audio Source. From -1 to 1, -1 being left, 1 being right
	*/
	float get3DSpread() const;

	/**
	* Get the max Distance
	* @return , the maxDistance of the Audio Source. It is the maximun distance, that the audio can be heard
	*/
	float get3DMaxDistance() const;
protected:
	void *getChannelHandle();
	void *channelHandle;
private:
	bool paused;									/**< 	paused, Pause				*/ 
	bool muteEnabled;								/**< 	muteEnable, Mute Enable 	*/ 
	bool bypassEffectsEnabled;						/**< 	effect Bypass			 	*/ 
	bool loopEnabled;								/**< 	loop Enable					*/ 
	int priority;									/**< 	priority					*/ 
	float volume;									/**< 	volume						*/ 
	float pitch;									/**< 	pitch						*/ 

	float dopplerLevel;								/**< 	dopplerLevel				*/ 
	DecayMode volumeDecayMode;						/**< 	pitch						*/ 
	float minDistance;								/**< 	minDistance					*/ 
	float panLevel;									/**< 	panLevel					*/ 
	float spread;									/**< 	spread						*/ 
	float maxDistance;								/**< 	maxDistance					*/ 
////////////////////////////////////////////////////////////////
public:
protected:
private:
};

};

#endif