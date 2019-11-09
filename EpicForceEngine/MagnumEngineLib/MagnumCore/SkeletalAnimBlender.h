///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _SkeletalAnimBlender_h_
#define _SkeletalAnimBlender_h_

#include "Array.h"
#include "SkeletalAnimBase.h"
using namespace Magnum;

namespace Magnum
{

/**
* SkeletalAnimWeights. This is a class which describe the blend weight and animation 
*/
class SkeletalAnimWeights
{
public:
	/**
	* SkeletalAnimWeights Constructor.
	* To Construct the SkeletalAnimWeights
	*/
	SkeletalAnimWeights();

	/**
	* SkeletalAnimWeights Destructor.
	* To Destruct the SkeletalAnimWeights
	*/
	~SkeletalAnimWeights();
//setter

	/**
	* Set the Animation to blend
	* @param anim_, SkeletalAnimBase *, the Animation to blend
	*/
	inline void setAnimation(SkeletalAnimBase *anim_){ anim = anim_; };

	/**
	* Set the num of blend weights, this usually the same as the number of bone in Animation
	* @param numWeights_, the num of blend weights
	*/
	inline void setNumWeights(int numWeights_){ weights.resize(numWeights_); };

	/**
	* Set the blend weight of the i-th bone of animation
	* @param boneIdx_, the num of blend weights
	* @param weight_, the blend weights
	*/
	inline void setWeight(int boneIdx_, const float &weight_) 
	{ 
		weights[boneIdx_] = weight_; 
	};

	/**
	* Set the weight of the all bone of animation
	* @param weight_, the blend weights to be set
	*/
	inline void setWeights(const float &weight_)
	{ 
		for(int i=0; i<weights.length(); i++)
			weights[i] = weight_; 
	};
//getter

	/**
	* Get the Animation to blend
	* @return SkeletalAnimBase *, the Animation to blend
	*/
	inline SkeletalAnimBase *getAnimation() const { return anim; };

	/**
	* Get the num of blend weights, this usually the same as the number of bone in Animation
	* @return numWeights_, the num of blend weights
	*/
	inline void getNumWeights() const { weights.length(); };

	/**
	* Get the num of weight of the i-th bone of the animation
	* @param boneIdx_, the num of blend weights
	* @param weight_, the blend weight is return here
	*/
	inline void getWeight(int boneIdx_, float &weight_) const { weight_ = weights[boneIdx_]; };
private:
	SkeletalAnimBase *anim;
	Vector<float> weights;
};

/**
* @brief Animation blender
*
* This is the class to handle the blend operation of character animation
*/
class SkeletalAnimBlender : public SkeletalProceduralAnimation
{
public:
	/**
	* @brief Constructor
	*/
	SkeletalAnimBlender();
	/**
	* @brief Destructor
	*/
	virtual ~SkeletalAnimBlender();
	/**
	* @brief This function initialized the blender with the information of the animation
	* 
	* This function initialized the blender with the information of the animation
	* Internally, it copy the all bones name, and bones parent.
	* These data helps user to specify what part of the animation that he want to manipulated
	* e.g. setting weight
	* After this function is called, we can only add animation 
	* with the same skeletal structure of skelanim_
	* @param skelanim_ the animation that data is to copy from
	*/
	void initSkeleton(const SkeletalAnimBase *skelanim_);
	/**
	* @brief This function initialized the blender with the information of the animation
	* 
	* This function initialized the blender with the information of the animation
	* Internally, it copy the all bones name, and bones parent.
	* These data helps user to specify what part of the animation that he want to manipulated
	* e.g. setting weight
	* After this function is called, we can only add animation 
	* with the same skeletal structure of skelanim_
	* @param skelanim_ the animation that data is to copy from
	*/
	// void initSkeleton(const SkeletalObject3v2 *skelobj_);
//setter
	/**
	* @brief This function set the animation time
	*
	* After this function is called, all child animation's setTime function is called
	*
	* @param time the time of the animation
	*/
	virtual void setTime(const float &time_);
	/**
	* @brief This function set the animation play back speed
	*
	* After this function is called, all child animation's setSpeed is called
	*
	* @param speed the speed of the animation, set to 1.0 for the same speed as exported data
	*/
	virtual void setSpeed(const float &speed);
	/**
	* @brief This function set the loop behaviour
	*
	* After this function is called, all child animation's setLoopBehavior is called
	*
	* @param lb_ the loop behaviour of the animation
	*/
	virtual void setLoopBehavior(AnimBase::LoopBehavior lb_);
	/**
	* @brief This function add animation as child of this blender
	*
	* After this function is called, the skelanim_ will become child of this blender and
	* the blender will include skelanim_ into calculation. By default, this function will set
	* the weight of bones to 1.
	*
	* @param skelanim_ the animation to set
	*/	
	bool addAnimation(SkeletalAnimBase *skelanim_);
	/**
	* @brief This function remove animation from the child animation list
	*
	* After this function is called, the skelanim_ will be removed from the child animation list.
	* the influence of the skelanim_ will be removed afterward
	*
	* @param skelanim_ the animation to set
	*/
	bool removeAnimation(SkeletalAnimBase *skelanim_);
	/**
	* @brief This function remove all animation from the child animation list
	*
	* After this function is called, the skelanim_ will be removed from the child animation list.
	* the influence of the skelanim_ will be removed afterward
	*
	* @param skelanim_ the animation to set
	*/
	bool removeAllAnimation();
	/**
	* @brief This function set the weight of boneIdx_-th bone of animIdx_-th animation
	*
	* This function will start at boneIdx_-th bone and set the weight 
	* if affectChildBone_ is set to true, all its descedent weight will also be set
	*
	* @param  animIdx_	      	the index to child animation
	* @param  boneIdx_		    the index to bone to begin with
	* @param  weight_		    the weight to set
	* @param  affectChildBone_  set to true if needed to recusively set child bone
	*/
	void setBlendWeights(int animIdx_, int boneIdx_, const float &weight_, bool affectChild_ = true);
	/**
	* @brief This function set the weight of specifed bones of animIdx_-th animation
	*
	* This function call void setBlendWeights(int animIdx_, int boneIdx_, const fix &weight_, bool affectChildBone_ = true);
	* for each boneIndices_[i], i = 0 to boneIndices_.length()
	*
	* @param  animIdx_	      	the index to child animation
	* @param  boneIndices_      the array of indices to bone to begin with
	* @param  weight_		    the weight to set
	* @param  affectChildBone_  set to true if needed to recusively set child bone
	*/
	void setBlendWeights(int animIdx_, const Vector<int> &boneIndices_, const float &weight_, bool affectChild_ = true);
	/**
	* @brief This function set the weight of boneIdx_-th bone of animIdx_-th animation
	*
	* This function will start at bone named as boneName_ and set the weight 
	* if affectChildBone_ is set to true, all its descedent weight will also be set
	*
	* @param  animIdx_	      	the index to child animation
	* @param  boneName_		    the name of the bone to begin with
	* @param  weight_		    the weight to set
	* @param  affectChildBone_  set to true if needed to recusively set child bone
	*/
	void setBlendWeights(SkeletalAnimBase *skelanim_, const char *boneName_, const float &weight_, bool affectChild_ = true);
	/**
	* @brief This function set the weight of specifed bones of animIdx_-th animation
	*
	* This function call void setBlendWeights(SkeletalAnimBase *skelanim_, const char *boneName_, const fix &weight_, bool affectChildBone_ = true);
	* for each bonesName_[i], i = 0 to bonesName_.length()
	*
	* @param  animIdx_	      	the index to child animation
	* @param  bonesName_        the array of bone to begin with
	* @param  weight_		    the weight to set
	* @param  affectChildBone_  set to true if needed to recusively set child bone
	*/
	void setBlendWeights(SkeletalAnimBase *skelanim_, const Vector<const char *> &bonesName_, const float &weight_, bool affectChild_ = true);
	/**
	* @brief This function set the weight of all bones of animIdx_-th animation
	*
	* This function call void setBlendWeights(SkeletalAnimBase *skelanim_, const char *boneName_, const fix &weight_, bool affectChildBone_ = true);
	* for each bonesName_[i], i = 0 to bonesName_.length()
	*
	* @param  animIdx_	      	the index to child animation
	* @param  weight_		    the weight to set
	*/
	void setAllBlendWeights(int animIdx_, const float &weight_);
	/**
	* @brief This function set the weight of specifed bones of animIdx_-th animation
	*
	* This function call void setBlendWeights(SkeletalAnimBase *skelanim_, const char *boneName_, const fix &weight_, bool affectChildBone_ = true);
	* for each bonesName_[i], i = 0 to bonesName_.length()
	*
	* @param  animIdx_	      	the index to child animation
	* @param  weight_		    the weight to set
	*/
	void setAllBlendWeights(SkeletalAnimBase *skelanim_, const float &weight_);
//getter
	/**
	* @brief This function get the animation time
	*
	* @return     the time of the child 0 is returned
	*/
	virtual float getTime() const;
	/**
	* @brief This function get the animation play back speed
	*
	* The speed of child 0 is returned
	*
	* @return     the speed of the child 0 is returned
	*/
	virtual float getSpeed() const;
	/**
	* @brief This function get the loop behaviour of animation
	*
	* The loop behaviour of child 0 is returned
	*
	* @return     loop behaviour
	*/
	virtual AnimBase::LoopBehavior getLoopBehavior() const;
	/**
	* @brief This function get the duration of the animation data.
	*
	* The long duration amongst all child is returned
	*
	* @return     the duration of the animation data
	*/
	virtual float getDuration() const;
	/**
	* @brief This function get the Number of Bones in the animation data.
	*
	* The number of bones returned by this function is equal to the animation set during initSkeleton.
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
	virtual int getBoneParentIndex(int boneIdx_) const;
	/**
	* @brief This function get the Vector10 (scale, rotation and translation) of the i-th bone
	*
	* The function returned the blended animation data of the i-th bone
	*
	* @param  i_   the index of the bone;
	* @param  v_   the variable to received the Vector10 data of i-th bone;
	*/
	virtual void getVector10(int boneIdx_, Vector10 &v_) const;
	/**
	* @brief This function return the number of animation child in the blender
	*
	* @return the number child animation
	*/
	int getNumAnimation() const;
	/**
	* @brief This function return the i-th child animation in this blender
	*
	* @return SkeletalAnimBase* pointer to i-th child animation 
	*/
	SkeletalAnimBase *getAnimation(int animIdx_) const;
	/**
	* @brief This function try to find the position of animation in this blender
	*
	* @param  skelanim_   the pointer to SkeletalAnimBase to find
	* @return if skelanim_ exists in child list, the index to the arrya is returned
	*         if skelanim_ does not exist in child list, return -1
	*/
	int getAnimationIndex(SkeletalAnimBase *skelanim_) const;
	/**
	* @brief This function get the weight of boneIdx_-th bones of animIdx_-th animation
	*
	* @param  animIdx_   the index to child animation
	* @param  boneIdx_   the index to bone
	* @param  weight_    the variable to receive the returned weight
	*/
	void getBlendWeight(int animIdx_, int boneIdx_, float &weight_) const;
	/**
	* @brief This function get the weights of bones specified by boneIndices_ of animIdx_-th animation
	*
	* @param  animIdx_       the index to child animation
	* @param  boneIndices_   the array of indices to bones chain
	* @param  weight_        the array to receive the returned weights
	*/
	void getBlendWeights(int animIdx_, const Vector<int> &boneIndices_, Vector<float> &weights_) const;
	/**
	* @brief This function collect the bone indices starting from boneidx_-th bones and all it descedents
	*
	* @param  boneIdx_       the index to starting bone
	* @param  boneIndices_   the array of indices to bones chain
	*/
	void getBonesChainIndices(int boneIdx_, Vector<int> &boneIndices_) const;
// operation
	/**
	* @brief This function is implemented thing need to do in each cycle of animation
	*
	* this function will call all its childen's cycle function
	* 
	*/
	virtual void update();
	/**
	* @brief This function get the playing status of the Animation
	*
	* @return true  if at least one of its child animation is playing, 
	*         false if all child animation is not playing;
	*/
	virtual bool isPlaying() const;
	/**
	* @brief This function start or resume the Animation.
	*
	* This function will call all its childen's start function.
	*
	* @param  lb_          the behaviour when animation is played to last frame
	* @param  speed_       the speed for the animation
	* @param  starttime_   from which the animation is played
	*/
	virtual void play(AnimBase::LoopBehavior lb_ = AnimBase::LOOP, const float &speed_ = 1, const float &starttime_ = 0);
	/**
	* @brief This function stop the Animation
	*
	* This function will call all its childen's stop function.
	*
	*/
	virtual void stop();

	/**
	* @brief This function pause the Animation
	*
	* This function will call all its childen's pause function.
	*
	*/
	virtual void pause();

	/**
	* @brief This function rewind the Animation (to its first frame), clears time
	*
	* This function will call all its childen's rewind function.
	*/
	virtual void rewind();

	/**
	* @brief This function get the pause status of the Animation
	*
	* @return true if all child animations were paused
	*         false if at least one of the child aniamtion is not paused
	*/
	virtual bool isPaused() const;
private:
	Vector<String>  boneNames;
	Vector<short>	parentIndices;

	Vector<SkeletalAnimWeights>	skelAnimWeights;
};

}

#endif