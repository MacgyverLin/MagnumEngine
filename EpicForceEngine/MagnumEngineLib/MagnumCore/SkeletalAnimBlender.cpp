///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "SkeletalAnimBlender.h"
#include "Stage.h"
//#include "SkeletalObject3v2.h"
//#include "SplineAnimationv2.h"
using namespace Magnum;

////////////////////////////////////////////////////
SkeletalAnimWeights::SkeletalAnimWeights() : anim(0)
{
}

SkeletalAnimWeights::~SkeletalAnimWeights()
{
}

////////////////////////////////////////////////////
SkeletalAnimBlender::SkeletalAnimBlender()
{
}

SkeletalAnimBlender::~SkeletalAnimBlender()
{
}

void SkeletalAnimBlender::initSkeleton(const SkeletalAnimBase *skelanim_)
{
	boneNames.resize(skelanim_->getNumBones());
	parentIndices.resize(skelanim_->getNumBones());

	for(int i=0; i<skelanim_->getNumBones(); i++)
	{
		boneNames[i]	 = skelanim_->getBoneName(i);
		parentIndices[i] = skelanim_->getBoneParentIndex(i);
	}
}

/*
void SkeletalAnimBlender::initSkeleton(const SkeletalObject3v2 *skelobj_)
{
	boneNames.resize(skelobj_->getNumBones());
	parentIndices.resize(skelobj_->getNumBones());

	for(int i=0; i<skelobj_->getNumBones(); i++)
	{
		boneNames[i]	 = skelobj_->getBoneName(i);
		parentIndices[i] = skelobj_->getBoneParentIdx(i);
	}
}
*/

//setter
void SkeletalAnimBlender::setTime(const float &time)
{
	for(int i=0; i<skelAnimWeights.length(); i++)
	{
		assert(skelAnimWeights[i].getAnimation());
		skelAnimWeights[i].getAnimation()->setTime(time);
	}
}

void SkeletalAnimBlender::setSpeed(const float &speed)
{
	for(int i=0; i<skelAnimWeights.length(); i++)
	{
		assert(skelAnimWeights[i].getAnimation());
		skelAnimWeights[i].getAnimation()->setSpeed(speed);
	}
}

void SkeletalAnimBlender::setLoopBehavior(AnimBase::LoopBehavior lb_)
{
	for(int i=0; i<skelAnimWeights.length(); i++)
	{
		assert(skelAnimWeights[i].getAnimation());
		skelAnimWeights[i].getAnimation()->setLoopBehavior(lb_);
	}
}

bool SkeletalAnimBlender::addAnimation(SkeletalAnimBase *skelanim_)
{
	assert(skelanim_);

	int numbone1 = skelanim_->getNumBones();
	int numbone2 = getNumBones();
	assert(skelanim_->getNumBones()==getNumBones());

	
	for(int i=0; i<skelAnimWeights.length(); i++)
	{
		if( skelAnimWeights[i].getAnimation()==skelanim_ )
		{
			return false;
		}
	}

	SkeletalAnimWeights &animweights = skelAnimWeights.push();
	animweights.setAnimation(skelanim_);
	animweights.setNumWeights(getNumBones());
	animweights.setWeights(1);
	//debug("added");

	return true;
}

bool SkeletalAnimBlender::removeAnimation(SkeletalAnimBase *skelanim_)
{
	for(int i=0; i<skelAnimWeights.length(); i++)
	{
		if( skelAnimWeights[i].getAnimation()==skelanim_ )
		{
			//debug("removed %d", i);
			skelAnimWeights.remove(i);
			return true;
		}
	}

	return false;
}

bool SkeletalAnimBlender::removeAllAnimation()
{
	skelAnimWeights.clear();

	return true;
}

void SkeletalAnimBlender::setBlendWeights(int animIdx_, int boneIdx_, const float &weight_, bool affectChild_)
{
	if( !(animIdx_>=0 && boneIdx_>=0) )
		return;
 
	if(affectChild_)
	{
		Vector<int> boneIndices;
		getBonesChainIndices(boneIdx_, boneIndices);
		for(int i=0; i<boneIndices.length(); i++)
			skelAnimWeights[animIdx_].setWeight(boneIndices[i], weight_);	
	}
	else
	{
		skelAnimWeights[animIdx_].setWeight(boneIdx_, weight_);
	}
}

void SkeletalAnimBlender::setBlendWeights(int animIdx_, const Vector<int> &boneIndices_, const float &weight_, bool affectChild_)
{
	for(int i=0; i<boneIndices_.length(); i++)
		setBlendWeights(animIdx_, boneIndices_[i], weight_, affectChild_);
}

void SkeletalAnimBlender::setBlendWeights(SkeletalAnimBase *skelanim_, const char *boneName_, const float &weight_, bool affectChild_)
{
	int animIdx = getAnimationIndex(skelanim_);
	int boneIdx = getBoneIndex(boneName_);

	setBlendWeights(animIdx, boneIdx, weight_, affectChild_);
}

void SkeletalAnimBlender::setBlendWeights(SkeletalAnimBase *skelanim_, const Vector<const char *> &boneNames_, const float &weight_, bool affectChild_)
{
	for(int i=0; i<boneNames_.length(); i++)
		setBlendWeights(skelanim_, boneNames_[i], weight_, affectChild_);
}

void SkeletalAnimBlender::setAllBlendWeights(int animIdx_, const float &weight_)
{
	skelAnimWeights[animIdx_].setWeights(weight_);
}

void SkeletalAnimBlender::setAllBlendWeights(SkeletalAnimBase *skelanim_, const float &weight_)
{
	int animIdx = getAnimationIndex(skelanim_);

	setAllBlendWeights(animIdx, weight_);
}

//getter
float SkeletalAnimBlender::getTime() const
{
	float time = 0;
	if(skelAnimWeights.length()!=0)
		time = skelAnimWeights[0].getAnimation()->getTime();

	return time;
}

float SkeletalAnimBlender::getSpeed() const
{
	float speed = 0;
	if(skelAnimWeights.length()!=0)
		speed = skelAnimWeights[0].getAnimation()->getSpeed();

	return speed;
}

AnimBase::LoopBehavior SkeletalAnimBlender::getLoopBehavior() const
{
	AnimBase::LoopBehavior lb = AnimBase::LOOP;

	if(skelAnimWeights.length()!=0)
		lb = skelAnimWeights[0].getAnimation()->getLoopBehavior();

	return lb;
}

float SkeletalAnimBlender::getDuration() const
{
	float maxduration = 0;
	for(int i=0; i<skelAnimWeights.length(); i++)
	{
		if( maxduration < skelAnimWeights[i].getAnimation()->getDuration() )
			maxduration = skelAnimWeights[i].getAnimation()->getDuration();
	}

	return maxduration;
}

int SkeletalAnimBlender::getNumBones() const
{
	return boneNames.length();
}

const char *SkeletalAnimBlender::getBoneName(int boneIdx_) const
{
	return boneNames[boneIdx_];
}

int SkeletalAnimBlender::getBoneIndex(const char *name_) const
{
	for(int i=0; i<boneNames.length(); i++)
	{
		if( strcasecmp(boneNames[i], name_) == 0 )
			return i;
	}

	return -1;
}

int SkeletalAnimBlender::getBoneParentIndex(int boneIdx_) const
{
	return parentIndices[boneIdx_];
}

void SkeletalAnimBlender::getVector10(int boneIdx_, Vector10 &v_) const
{
	//validate();
	assert(skelAnimWeights.length()!=0);

	Vector10 vtemp;

	if(skelAnimWeights.length()==1)
	{
		skelAnimWeights[0].getAnimation()->getVector10(boneIdx_, v_);
	}
	else
	{
		float totalweight = 0;
		for(int i=0; i<skelAnimWeights.length(); i++)
		{
			float w;
			skelAnimWeights[i].getWeight(boneIdx_, w);

			if(w>Math::ZERO_TOLERANCE)
				totalweight += w;
		}
		float invtotalweight = 1.0f / totalweight;
		
		v_ = Vector10::ZERO;
		for(int i=0; i<skelAnimWeights.length(); i++)
		{
			float w;
			skelAnimWeights[i].getWeight(boneIdx_, w);
			if(w>Math::ZERO_TOLERANCE)
			{
				skelAnimWeights[i].getAnimation()->getVector10(boneIdx_, vtemp);
				if(vtemp.q.Dot(v_.q)<0 && i!=0)
					vtemp.q = -vtemp.q;

				vtemp *= w * invtotalweight;

				v_ += vtemp;
			}
		}

		float invLength = Math::FastInvSqrt( v_.q[0]*v_.q[0]+v_.q[1]*v_.q[1]+v_.q[2]*v_.q[2]+v_.q[3]*v_.q[3] );
		v_.q *= invLength;
		//v_.q.Normalize();
	}
}

int SkeletalAnimBlender::getNumAnimation() const
{
	return skelAnimWeights.length();
}

SkeletalAnimBase *SkeletalAnimBlender::getAnimation(int animIdx_) const
{
	return skelAnimWeights[animIdx_].getAnimation();
}

int SkeletalAnimBlender::getAnimationIndex(SkeletalAnimBase *skelanim_) const
{
	for(int i=0; i<skelAnimWeights.length(); i++)
	{
		if(skelAnimWeights[i].getAnimation()==skelanim_)
			return i;
	}

	return -1;
}

void SkeletalAnimBlender::getBlendWeight(int animIdx_, int boneIdx_, float &weight) const
{
	skelAnimWeights[animIdx_].getWeight(boneIdx_, weight);
}

void SkeletalAnimBlender::getBlendWeights(int animIdx_, const Vector<int> &boneIndices_, Vector<float> &weights_) const
{
	weights_.resize(boneIndices_.length());

	for(int i=0; i<boneIndices_.length(); i++)
		skelAnimWeights[animIdx_].getWeight(boneIndices_[i], weights_[i]);
}

void SkeletalAnimBlender::getBonesChainIndices(int idx_, Vector<int> &boneIndices_) const
{
	if(idx_ < 0)
		return ;

	boneIndices_.push() = idx_;
	for(int i=0; i<parentIndices.length(); i++)
	{
		if( parentIndices[i] == idx_ )
		{
			getBonesChainIndices(i, boneIndices_);
		}
	}
}

// operation
void SkeletalAnimBlender::update()
{
	for(int i=0; i<skelAnimWeights.length(); i++)
	{
		assert(skelAnimWeights[i].getAnimation() || !"Weights have no animations"); // Potter 6/08 for easier debugging
		skelAnimWeights[i].getAnimation()->update();
	}
}

bool SkeletalAnimBlender::isPlaying() const
{
	for(int i=0; i<skelAnimWeights.length(); i++)
	{
		if( skelAnimWeights[i].getAnimation()->isPlaying() )
			return true;
	}

	return false;
}

void SkeletalAnimBlender::play(SkeletalAnimBlender::LoopBehavior lb_, const float &speed_, const float &starttime_)
{
	for(int i=0; i<skelAnimWeights.length(); i++)
		skelAnimWeights[i].getAnimation()->play(lb_, speed_, starttime_);
}

void SkeletalAnimBlender::stop()
{
	for(int i=0; i<skelAnimWeights.length(); i++)
		skelAnimWeights[i].getAnimation()->stop();
}

void SkeletalAnimBlender::pause()
{
	for(int i=0; i<skelAnimWeights.length(); i++)
		skelAnimWeights[i].getAnimation()->pause();
}

void SkeletalAnimBlender::rewind()
{
	for(int i=0; i<skelAnimWeights.length(); i++)
		skelAnimWeights[i].getAnimation()->rewind();
}

bool SkeletalAnimBlender::isPaused() const
{
	for(int i=0; i<skelAnimWeights.length(); i++)
	{
		if( !skelAnimWeights[i].getAnimation()->isPaused() )
			return true;
	}

	return false;
}