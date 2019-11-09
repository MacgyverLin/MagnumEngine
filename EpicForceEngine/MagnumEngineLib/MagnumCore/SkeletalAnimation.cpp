///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "SkeletalAnimation.h"
#include "SkeletalAnimModel.h"
using namespace Magnum;

//////////////////////////////////////////////////////
SkeletalAnimation::SkeletalAnimation() 
: SkeletalKeyFrameAnimation()
, resource(0)
, _isPlaying(false)
, _isPaused(false)
, speed(1.0f)
, lb(LOOP)
, lastTime(0)
, time(0)
, timedir(1)
{
}

SkeletalAnimation::~SkeletalAnimation()
{
}


bool SkeletalAnimation::construct(const char *path_)
{
	assert(resource==0);

	String directory	= System::getDirectory(path_);
	String fileName		= System::getFileName(path_);
	String extension	= System::getExtension(path_);
	String path			= path_;
	// String path = String(directory_) + String("/") + filename_;

	timedir		= 1;
	lastTime	= 0;
	time		= 0;
	lb			= LOOP;
	speed		= 1.0f;
	_isPaused	= false;
	_isPlaying	= false;

	resource = SkeletalAnimModel::Resource::get(path.text());
	if(!resource)
		return false;

	resource->addReference();
	return true;
}

/*
* @brief if not data is
*/
void SkeletalAnimation::destruct()
{
	if(resource)
	{
		resource->release();
		resource = 0;
	}
}

//setter
void SkeletalAnimation::setTime(const float &time_)
{
	assert(resource);

	time		= time_;
	if(time < 0)
		time = 0;
	if(time >= resource->getDuration()-1)
		time = resource->getDuration()-1;
	
	lastTime	= time;
}

void SkeletalAnimation::setSpeed(const float &speed_)
{
	speed = speed_;
}

void SkeletalAnimation::setLoopBehavior(AnimBase::LoopBehavior lb_)
{
	lb = lb_;
}

//getter
float SkeletalAnimation::getTime() const
{
	return time;
}

float SkeletalAnimation::getSpeed() const
{
	return speed;
}

AnimBase::LoopBehavior SkeletalAnimation::getLoopBehavior() const
{
	return lb;
}

float SkeletalAnimation::getDuration() const
{
	assert(resource);
	return resource->getDuration();
}

int SkeletalAnimation::getNumBones() const
{
	assert(resource);
	return resource->getNumBones();
}

const char *SkeletalAnimation::getBoneName(int boneIdx_) const
{
	assert(resource);
	
	return resource->getBoneName(boneIdx_);
}

int SkeletalAnimation::getBoneIndex(const char *name_) const
{
	assert(resource);
	
	return resource->getBoneIndex(name_);
}

int SkeletalAnimation::getBoneParentIndex(int boneIdx_) const
{
	assert(resource);
	
	return resource->getBoneParentIndex(boneIdx_);
}

void SkeletalAnimation::getVector10(int boneIdx_, Vector10 &v_) const
{
	assert(resource);

	resource->getVector10(boneIdx_, time, v_);
}

// operation
void SkeletalAnimation::update()
{
	if(!_isPlaying)
		return;
		
	if(_isPaused)
		return;

	assert(resource);

	// save last time
	lastTime	= time;

	switch(lb)
	{
		case ONESHOT:
			time += Stage::elapsed() * 0.001f * speed * resource->getFPS();
			if(speed >= 0)
			{
				if(time > getDuration())
				{
					invokeCallBack();
					time = 0;

					_isPlaying = false;
				}
			}
			else
			{
				if(time < 0)
				{
					invokeCallBack();
					time = getDuration();

					_isPlaying = false;
				}
			}
		break;
		case CLAMP:
			time += Stage::elapsed() * 0.001f * speed * resource->getFPS();
			if(speed >= 0)
			{
				if(time > getDuration())
				{
					invokeCallBack();
					time = getDuration();

					_isPlaying = false;
				}
			}
			else
			{
				if(time < 0)
				{
					invokeCallBack();
					time = 0;

					_isPlaying = false;
				}
			}
		break;
		case LOOP:
			time += Stage::elapsed() * 0.001f * speed * resource->getFPS();
			if(speed >= 0)
			{
				if(time > getDuration())
				{
					invokeCallBack();
					time = time - getDuration();
				}
			}
			else
			{
				if(time < 0)
				{
					invokeCallBack();
					time = getDuration() + time;
				}
			}
		break;
		case PINGPONG:
			float absspeed = Math::FAbs(speed);
			time += Stage::elapsed() * 0.001f * absspeed * timedir * resource->getFPS();
			if(time > getDuration())
			{
				invokeCallBack();
				time = getDuration() - (time - getDuration());
				timedir = -1;
			}
			else if(time < 0)
			{
				invokeCallBack();
				time = 0 - time;
				timedir = 1;
			}
		break;
	};
}

bool SkeletalAnimation::isPlaying() const
{
	return _isPlaying;
}

void SkeletalAnimation::play(SkeletalAnimBase::LoopBehavior lb_, const float &speed_, const float &starttime_)
{
	lb = lb_;
	speed = speed_;
	_isPlaying = true;
	_isPaused  = false;
	timedir    = 1;

	setTime(starttime_);
}

bool SkeletalAnimation::stopped()
{
	return !(_isPlaying || _isPaused);
}

void SkeletalAnimation::stop()
{
	_isPlaying = false;
	_isPaused  = false;
}

void SkeletalAnimation::pause()
{
	_isPaused  = true;
}

void SkeletalAnimation::unPause()
{
	_isPaused  = false;
}

void SkeletalAnimation::rewind()
{
	time = 0;
}

bool SkeletalAnimation::isPaused() const
{
	return _isPaused;
}