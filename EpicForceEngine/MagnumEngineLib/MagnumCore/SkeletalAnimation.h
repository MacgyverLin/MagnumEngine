///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _SkeletalAnimation_h_
#define _SkeletalAnimation_h_

#include "Stage.h"
#include "Platform.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Array.h"
#include "Matrix4.h"
#include "Vector10.h"
#include "Component.h"
#include "ResourceImport.h"
#include "ResourceAccess.h"
#include "SkeletalAnimBase.h"
#include "SkeletalAnimModel.h"
using namespace Magnum;

namespace Magnum
{

/**
* @brief TCB Spline data driven Animation
*
* This is the animation driven by TCB key. It data file type that this calss uses is *.splineanimv2
*/
class SkeletalAnimation : public SkeletalKeyFrameAnimation
{
public:
	/**
	* @brief Constructor
	*/
	SkeletalAnimation();
	/**
	* @brief Destructor
	*/
	virtual ~SkeletalAnimation();
	/*
	* @brief if not data is not loaded in constructor
	*/
	bool construct(const char *path_);
	/*
	* @brief if not data is
	*/
	void destruct();
//setter
	/**
	* @brief This function set the animation time
	*
	* @param time the time of the animation
	*/
	virtual void setTime(const float &time_);
	/**
	* @brief This function set the animation play back speed
	*
	* @param speed the speed of the animation, set to 1.0 for the same speed as exported data
	*/
	virtual void setSpeed(const float &speed);
	/**
	* @brief This function set the loop behaviour of animation
	*
	* @param lb_     loop behaviour
	*/
	virtual void setLoopBehavior(AnimBase::LoopBehavior lb_);
//getter
	/**
	* @brief This function get the animation time
	*
	* @return     the time of the animation in NUM OF FRAME
	*/
	virtual float getTime() const;
	/**
	* @brief This function get the animation play back speed
	*
	*
	* @return     the speed of the animation is returned
	*/
	virtual float getSpeed() const;
	/**
	* @brief This function get the loop behaviour of animation
	*
	* The loop behaviour of animation
	*
	* @return     loop behaviour
	*/
	virtual AnimBase::LoopBehavior getLoopBehavior() const;
	/**
	* @brief This function get the duration in frame of the animation data.
	*
	* @return     the duration in frame of the animation data
	*/
	virtual float getDuration() const;
	/**
	* @brief This function get the Number of Bones in the animation data.
	*
	* @return     the number of Bones in the animation data.
	*/
	virtual int getNumBones() const;
	/**
	* @brief This function get the Name of Bone in the animation data.
	*
	* @param  i   the idx to bone array;
	* @return     the name of i-th Bone.
	*/
	virtual const char *getBoneName(int boneIdx_) const;
	/**
	* @brief This function try to find the position of Bone of animation data.
	*
	* @param  name_ the name of Bone to find;
	* @return if name_ exists in the bone list, bone index 
	*         if name_ does not exist in the bone list, -1;
	*/
	virtual int getBoneIndex(const char *name_) const;
	/**
	* @brief This function try to find the position of parent of Bone in of animation data.
	*
	* @param  i_   the index of the bone;
	* @return if i-th bones has parent return the index of parent
	*         if i-th bones is already the root bone, return -1
	*/
	virtual int getBoneParentIndex(int boneIdx__) const;
	/**
	* @brief This function get the Vector10 (scale, rotation and translation) of the i-th bone
	*
	* @param  i_   the index of the bone;
	* @param  v_   the variable to received the Vector10 data of i-th bone;
	*/
	virtual void getVector10(int boneIdx_, Vector10 &v_) const;
// operation
	/**
	* @brief This function is implemented thing need to do in each cycle of animation
	*
	* when this function is called, the system time will be record and internal time elapsed is update.
	* getVector10 function use this internal time value to calculate animation
	* 
	*/
	virtual void update();
	/**
	* @brief This function get the playing status of the Animation
	*
	* @return if animation is playing, return true;
	*         if animation is not playing, return false;
	*/
	virtual bool isPlaying() const;
	/**
	* @brief This function start or resume the Animation.
	*
	* After this function is called, the animation will be set at playing state
	*
	* @param  lb_          the behaviour when animation is played to last frame
	* @param  speed_       the speed for the animation
	* @param  starttime_   from which the animation is played
	*
	*/
	virtual void play(AnimBase::LoopBehavior lb_ = AnimBase::LOOP, const float &speed_ = 1, const float &starttime_ = 0);

	/**
	* @brief This function stop the Animation
	*
	* After this function is called, the animation will be set at stop state
	*
	*/
	virtual void stop();
	virtual bool stopped();
	
	/**
	* @brief This function pause the Animation
	*
	* After this function is called, the animation will be set at pause state.
	* We can resume it by calling resume or start
	*
	*/
	virtual void pause();
	virtual void unPause();

	/**
	* @brief This function resets the Animation to its first frame (0 time)
	*/
	virtual void rewind();

	/**
	* @brief This function get the pause status of the Animation
	*
	* @return if animation was paused, return true;
	*         if animation was not paused, return false;
	*/
	virtual bool isPaused() const;
protected:
	SkeletalAnimModel::Resource *resource;
	
	bool _isPlaying;
	bool _isPaused;
	
	float speed;
	AnimBase::LoopBehavior lb;
	float lastTime;
	float time;
	float timedir;
};


}

#endif