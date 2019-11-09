///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _SkeletalAnimModelComponent_h_
#define _SkeletalAnimModelComponent_h_

#include "Stage.h"
#include "Platform.h"
#include "Graphics3Component.h"
#include "ResourceImport.h"
#include "ResourceAccess.h"
#include "TextureBase.h"
#include "VisualEffect.h"
#include "SkeletalAnimModel.h"
#include "ResourcePath.h"
using namespace Magnum;

namespace Magnum
{

/**
* SkeletalAnimModelComponent Rendering Graphics Component
* @see Component
*/
class SkeletalAnimModelComponent : public Graphics3Component
{
public:
////////////////////////////////////////////////////////////////
	/**
	* SkeletalAnimModelComponent Constructor.
	* To Construct the SkeletalAnimModelComponent for the owner.
	* @param owner_, the Component::Owner which owns this component.
	*/
	SkeletalAnimModelComponent(Component::Owner &owner);

	/**
	* SkeletalAnimModelComponent Destructor.
	* To Destruct the SkeletalAnimModelComponent for the owner.
	*/
	virtual ~SkeletalAnimModelComponent();

	DECLARE_COMPONENT(SkeletalAnimModelComponent, Graphics3Component, false)
////////////////////////////////////////////////////////////////

	/**
	* Set the Path of Model of the SkeletalAnimModelComponent
	* @param value_, ResourcePath, the Path of Model of the SkeletalAnimModelComponent
	*/
	/**
	* Get the Path of Model of the SkeletalAnimModelComponent.
	* @return ResourcePath, the Path of Model of the SkeletalAnimModelComponent.
	*/
	PROPERTY(ResourcePath, ModelPath);
////////////////////////////////////////////////////////////////
public:
	/**
	* Get the SkeletalAnimModel* of the SkeletalAnimModelComponent.
	* @return SkeletalAnimModel *, the SkeletalAnimModel* of the SkeletalAnimModelComponent.
	*/
	SkeletalAnimModel *getSkeletalAnimModel() const;

	/**
	* Set the SkeletalAnimBase of the SkeletalAnimModelComponent.
	* @param animation_, the SkeletalAnimBase* of the SkeletalAnimModelComponent.
	*/
	void setAnimation(SkeletalAnimBase *animation_);

	/**
	* Get the SkeletalAnimBase* of the SkeletalAnimModelComponent.
	* @return SkeletalAnimBase*, the SkeletalAnimBase* of the SkeletalAnimModelComponent.
	*/
	SkeletalAnimBase *getAnimation() const;

	/**
	* Get the Number of Textures
	* @return int, the Number of Textures
	*/
	int getNumTextures() const;

	/**
	* Set the i-th texture of the Material of the Animation Model
	* @param i, int, index to the Textures
	* @param texture_, TextureBase the i-th texture of the Material of the Animation Model
	*/
	void setTexture(int i, TextureBase *texture_);

	/**
	* Get the i-th texture of the Visual Effect(Material) of the Animation Model
	* @param i, int, index to the Textures
	* @return TextureBase* the i-th texture of the Visual Effect(Material) of the Animation Model
	*/
	TextureBase *getTexture(int i);

	/**
	* Get the Number of Visual Effect(Material)
	* @return int, the Number of Visual Effect(Material)
	*/
	int getNumVisualEffects() const;

	/**
	* Set the i-th Visual Effect(Material) of the Animation Model
	* @param i, int, index to the Visual Effect(Material)
	* @param visualEffect_, VisualEffect the i-th Visual Effect(Material) of Animation Model
	*/
	void setVisualEffect(int i, VisualEffect *visualEffect_);

	/**
	* Get the i-th Visual Effect(Material) of the Animation Model
	* @param i, int, index to the Visual Effect(Material)
	* @return VisualEffect the i-th Visual Effect(Material) of Animation Model
	*/
	VisualEffect *getVisualEffect(int i);
protected:
private:
	bool constructDefaultConfig(const char *path_);

	virtual bool onConstruct();
	virtual void onStart();
	virtual void onUpdate(float dt);
	virtual void onPause();
	virtual void onResume();
	virtual void onStop();
	virtual void onDestruct();

	/**
	* Handle Debuger Rendering Event of the Component
	*/
	virtual void onDebugRender(IComponentDebugRenderer &debugRenderer);
public:
protected:
private:
	SkeletalAnimModel		*skeletalAnimModel;
	Vector<TextureBase  *>	textures;
	Vector<VisualEffect *>	visualEffects;
	
	SkeletalAnimBase		*animation;
};

};

#endif