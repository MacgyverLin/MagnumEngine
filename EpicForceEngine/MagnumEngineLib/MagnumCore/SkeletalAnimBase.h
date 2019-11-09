///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _SkeletalAnimBase_h_
#define _SkeletalAnimBase_h_

#include "Vector10.h"
#include "Delegate.h"
#include "AnimBase.h"
using namespace Magnum;

namespace Magnum
{

/**
* @brief Base class For all type of Skeletal Animation
*
* This is the base class for all type of Skeletal Animation. The Animation
* type can be extended by inheritance. 
*/
class SkeletalAnimBase : public AnimBase
{
public:
	/**
	* @brief Constructor
	*/
	SkeletalAnimBase();
	/**
	* @brief Destructor
	*/
	virtual ~SkeletalAnimBase();
//setter
	/**
	* @brief This function set the animation time
	*
	* This function should be implemented by sub class of Animation.
	* @param time the time of the animation
	*/
	virtual void setTime(const float &time_) = 0;
	/**
	* @brief This function set the animation play back speed
	*
	* This function should be implemented by sub class of Animation.
	* @param speed the speed of the animation, set to 1.0 for the same speed as exported data
	*/
	virtual void setSpeed(const float &speed_) = 0;
	/**
	* @brief This function set the loop behaviour of animation
	*
	* This function should be implemented by sub class of Animation.
	* @param lb_     loop behaviour
	*/
	virtual void setLoopBehavior(AnimBase::LoopBehavior lb_) = 0;
//getter
	/**
	* @brief This function set the animation time
	*
	* This function should be implemented by sub class of Animation.
	* @param time the time of the animation
	*/
	virtual float getTime() const = 0;
	/**
	* @brief This function get the animation play back speed
	*
	* This function should be implemented by sub class of Animation.
	* @return     the speed of the animation, 1.0 means the same speed as exported data
	*/
	virtual float getSpeed() const = 0;
	/**
	* @brief This function get the loop behaviour of animation
	*
	* This function should be implemented by sub class of Animation.
	* @return     loop behaviour
	*/
	virtual AnimBase::LoopBehavior getLoopBehavior() const = 0;
	/**
	* @brief This function get the duration of the animation data.
	*
	* This function should be implemented by sub class of Animation.
	* @return     the duration of the animation data
	*/
	virtual float getDuration() const = 0;
//getter
	/**
	* @brief This function get the Number of Bones in the animation data.
	*
	* This function should be implemented by sub class of Animation.
	* @return     the number of Bones in the animation data.
	*/
	virtual int getNumBones() const = 0;
	/**
	* @brief This function get the Name of Bone in the animation data.
	*
	* This function should be implemented by sub class of Animation.
	* @param  i   the idx to bone array;
	* @return     the name of i-th Bone.
	*/
	virtual const char *getBoneName(int boneIdx__) const = 0;
	/**
	* @brief This function try to find the position of Bone of animation data.
	*
	* This function should be implemented by sub class of Animation.
	* @param  name_ the name of Bone to find;
	* @return if name_ exists in the bone list, bone index 
	*         if name_ does not exist in the bone list, -1;
	*/
	virtual int getBoneIndex(const char *name_) const = 0;
	/**
	* @brief This function get the Vector10 (scale, rotation and translation) of the i-th bone
	*
	* This function should be implemented by sub class of Animation.
	* @param  i_   the index of the bone;
	* @param  v_   the variable to received the Vector10 data of i-th bone;
	*/
	virtual int getBoneParentIndex(int boneIdx__) const = 0;
	/**
	* @brief This function get the Vector10 (scale, rotation and translation) of the i-th bone
	*
	* This function should be implemented by sub class of Animation.
	* @param  i_   the index of the bone;
	* @param  v_   the variable to received the Vector10 data of i-th bone;
	*/
	virtual void getVector10(int boneIdx__, Vector10 &v_) const = 0;
	/**
	* @brief This function get the local Transform of of the i-th bone
	*
	* @param  i_   the index of the bone;
	* @param  mat_ the variable to received the local Transform of i-th bone;
	*/
	virtual void getLocalTransform(int boneIdx__, Matrix4 &mat_) const;
	/**
	* @brief This function get the global Transform of of the i-th bone
	*
	* @param  i_   the index of the bone;
	* @param  mat_ the variable to received the global Transform of i-th bone;
	*/
	virtual void getSystemTransform(int boneIdx__, Matrix4 &mat_) const;
// operation
	/**
	* @brief This function is implemented thing need to do in each cycle of animation
	*
	* This function should be implemented by sub class of Animation.
	*/
	virtual void update() = 0;
	/**
	* @brief This function get the playing status of the Animation
	*
	* This function should be implemented by sub class of Animation.
	* @return if animation is playing, return true;
	*         if animation is not playing, return false;
	*/
	virtual bool isPlaying() const = 0;
	/**
	* @brief This function start or resume the Animation.
	*
	* After this function is called, the animation will be set at playing state
	*
	* @param  lb_          the behaviour when animation is played to last frame
	* @param  speed_       the speed for the animation
	* @param  starttime_   from which the animation is played
	*/
	virtual void play(AnimBase::LoopBehavior lb_ = AnimBase::LOOP, const float &speed_ = 1, const float &starttime_ = 0) = 0;
	/**
	* @brief This function stop the Animation
	*
	* After this function is called, the animation will be set at stop state
	*
	* This function should be implemented by sub class of Animation.
	*/
	virtual void stop() = 0;
	/**
	* @brief This function pause the Animation
	*
	* After this function is called, the animation will be set at pause state.
	* We can resume it by calling resume or start
	*
	* This function should be implemented by sub class of Animation.
	*/
	virtual void pause() = 0;
	/**
	* @brief This function rewind the Animation (to its first frame), clears time
	*
	* This function should be implemented by sub class of Animation.
	*/
	virtual void rewind() = 0;
	/**
	* @brief This function get the pause status of the Animation
	*
	* This function should be implemented by sub class of Animation.
	* @return if animation was paused, return true;
	*         if animation was not paused, return false;
	*/
	virtual bool isPaused() const = 0;
protected:
};

/**
* @brief Base class For all type of Skeletal KeyFrame Animation
*
* This is the base class for all type of Skeletal KeyFram eAnimation. The Animation
* type can be extended by inheritance. 
*/
class SkeletalKeyFrameAnimation : public SkeletalAnimBase 
{
public:
	/**
	* @brief Constructor
	*/
	SkeletalKeyFrameAnimation() : SkeletalAnimBase()
	{
	}

	/**
	* @brief Destructor
	*/
	virtual ~SkeletalKeyFrameAnimation()
	{
	}
};

/**
* @brief Base class For all type of Skeletal Procedural Animation
*
* This is the base class for all type of Skeletal Procedural Animation. The Animation
* type can be extended by inheritance. 
*/
class SkeletalProceduralAnimation : public SkeletalAnimBase 
{
public:
	/**
	* @brief Constructor
	*/
	SkeletalProceduralAnimation() : SkeletalAnimBase()
	{
	}

	/**
	* @brief Destructor
	*/
	virtual ~SkeletalProceduralAnimation()
	{
	}
};

}

#endif