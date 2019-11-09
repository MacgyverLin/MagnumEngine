///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "SkeletalAnimModelComponent.h"
#include "SkeletalAnimModelRenderer.h"
#include "Texture2DFile.h"
#include "TextureCubeFile.h"
using namespace Magnum;

SkeletalAnimModelComponent::SkeletalAnimModelComponent(Component::Owner &owner)
: Graphics3Component(owner)
, skeletalAnimModel(0)
, animation(0)
{
	setModelPath(ResourcePath("default/default", "skelanimmdl"));
}

SkeletalAnimModelComponent::~SkeletalAnimModelComponent()
{
}

SkeletalAnimModel *SkeletalAnimModelComponent::getSkeletalAnimModel() const
{
	return skeletalAnimModel;
}

void SkeletalAnimModelComponent::setAnimation(SkeletalAnimBase *animation_)
{
	animation = animation_;
}

SkeletalAnimBase *SkeletalAnimModelComponent::getAnimation() const
{
	return animation;
}

int SkeletalAnimModelComponent::getNumTextures() const
{
	return textures.length();
}

void SkeletalAnimModelComponent::setTexture(int i, TextureBase *texture_)
{
	textures[i] = texture_;
}

TextureBase *SkeletalAnimModelComponent::getTexture(int i)
{
	return textures[i];
}

int SkeletalAnimModelComponent::getNumVisualEffects() const
{
	return visualEffects.length();
}

void SkeletalAnimModelComponent::setVisualEffect(int i, VisualEffect *visualEffect_)
{
	if(i<visualEffects.length())
		visualEffects[i] = visualEffect_;
}

VisualEffect *SkeletalAnimModelComponent::getVisualEffect(int i)
{
	if(i<visualEffects.length())
		return visualEffects[i];
	else
		return 0;
}

bool SkeletalAnimModelComponent::constructDefaultConfig(const char *path_)
{
	String modelPath	= path_;

	String directory	= System::getDirectory(path_);
	String fileName		= System::getFileName(path_);
	String extension	= System::getExtension(path_);
	// String path = String(directory_) + String("/") + filename_;

	skeletalAnimModel	= new SkeletalAnimModel();
	assert(skeletalAnimModel);
	if( !skeletalAnimModel->construct(modelPath) )
		return false;

	int numTextures = skeletalAnimModel->getNumTextureInfos();
	textures.resize(numTextures);
	for(int i=0; i<textures.length(); i++)
	{
		const SkeletalAnimModel::TextureInfo &textureInfo = *(skeletalAnimModel->getTextureInfo(i));
		
		String texturePath(directory + "/" + textureInfo.getFilePath());

		Texture2DFile *texture2d = new Texture2DFile();
		if( !texture2d->construct(texturePath) )
			return false;

		textures[i] = texture2d;
	}

	int numVisualEffectInfos = skeletalAnimModel->getNumVisualEffectInfos();
	visualEffects.resize(numVisualEffectInfos);
	for(int i=0; i<visualEffects.length(); i++)
	{
		const SkeletalAnimModel::VisualEffectInfo &visualEffectInfo = *(skeletalAnimModel->getVisualEffectInfo(i));

		String effectPath(directory + "/" + visualEffectInfo.getFilePath());

		VisualEffect *effect = new VisualEffect();
		if( !effect->construct(effectPath) )
			return false;

		for(int j=0; j<visualEffectInfo.getNumTextureInfoIndices(); j++)
		{
			int idx = visualEffectInfo.getTextureInfoIndex(j);
			effect->setTexture(j, textures[idx]);
		}

		visualEffects[i] = effect;
	}

	return true;
}

bool SkeletalAnimModelComponent::onConstruct()
{
	return constructDefaultConfig(getModelPath().getPath());
}

void SkeletalAnimModelComponent::onStart()
{
}

void SkeletalAnimModelComponent::onUpdate(float dt)
{
}

void SkeletalAnimModelComponent::onPause()
{
}

void SkeletalAnimModelComponent::onResume()
{
}

void SkeletalAnimModelComponent::onStop()
{
}

void SkeletalAnimModelComponent::onDestruct()
{
	if(skeletalAnimModel)
	{
		delete skeletalAnimModel;
		skeletalAnimModel = 0;
	}

	for(int i=0; i<textures.length(); i++)
	{
		if(textures[i])
		{
			delete textures[i];
			textures[i] = 0;
		}
	}
	textures.destroy();

	for(int i=0; i<visualEffects.length(); i++)
	{
		if(visualEffects[i])
		{
			delete visualEffects[i];
			visualEffects[i] = 0;
		}
	}
	visualEffects.destroy();
}

void SkeletalAnimModelComponent::onDebugRender(IComponentDebugRenderer &debugRenderer)
{

}