///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _AnimBase_h_
#define _AnimBase_h_

#include "Vector10.h"
#include "Delegate.h"
using namespace Magnum;

namespace Magnum
{

/**
* @brief Base class For all type of Skeletal Animation
*
* This is the base class for all type of Skeletal Animation. The Animation
* type can be extended by inheritance. 
*/
class AnimBase
{
public:
	/**
	* @brief This Enum specified the way the animation is played. 
	*/
	enum LoopBehavior
	{
		ONESHOT,	///< play until last frame and stop at first frame
		CLAMP,		///< play until last frame and stop at last frame
		LOOP,		///< play until last frame and rewind to first frame, loop forever until stop or pause
		PINGPONG	///< play until last frame and reverse dir, loop forever until stop or pause
	};

	/**
	* @brief Constructor
	*/
	AnimBase();
	/**
	* @brief Destructor
	*/
	virtual ~AnimBase();
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
	/**
	* @brief This function set the animation call back
	*
	*/
	virtual void setEventCallBack(Functor1<AnimBase *> *cb_);
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
	* @brief This function get the animation call back
	*
	*/
	virtual Functor1<AnimBase *> *getEventCallBack();
	/**
	* @brief This function get the duration of the animation data.
	*
	* This function should be implemented by sub class of Animation.
	* @return     the duration of the animation data
	*/
	virtual float getDuration() const = 0;
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
	/**
	* @brief This function invoke the Animation CallBack
	*
	*/
	void invokeCallBack();
	/**
	* @brief This function retrieve the Animation that Triggered the callback
	*
	* @return the Animation that Triggered the callback
	*/
protected:
	Functor1<AnimBase *> *cb;
};


}

#endif
