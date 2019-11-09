///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited			 //
//																 //
// Author : Mac Lin									             //
// Module : EpicForceEngine										 //
// Date   : 19/Aug/2011											 //
//																 //
///////////////////////////////////////////////////////////////////
#include "Graphics2.h"
using namespace Magnum;

///////////////////////////////////////////////////////////////////
Graphics2::Graphics2()
: Component()
, position(0, 0, 0)
, scale(1, 1)
, color(1, 1, 1, 1)
, rotation(0)
, blendMode(Filter)
{
}

Graphics2::~Graphics2()
{
}

void Graphics2::setPosition(const Vector3 &position_)
{
	position = position_;
}

const Vector3 &Graphics2::getPosition() const
{
	return position;
}

void Graphics2::setScale(const Vector2 &scale_)
{
	scale = scale_;
}

const Vector2 &Graphics2::getScale() const
{
	return scale;
}

void Graphics2::setColor(const ColorRGBA &color_)
{
	color = color_;
}

const ColorRGBA &Graphics2::getColor() const
{
	return color;
}

void Graphics2::setRotation(float rotation_)
{
	rotation = rotation_;
}

float Graphics2::getRotation() const
{
	return rotation;
}

void Graphics2::setBlendMode(Graphics2::BlendMode blendMode_)
{
	blendMode = blendMode_;
}

Graphics2::BlendMode Graphics2::getBlendMode() const
{
	return blendMode;
}

void Graphics2::calcWorldTransform(Matrix4 &worldMat_)
{
	float *m = worldMat_;
	float cosine = Math::Cos(rotation);
	float sine   = Math::Sin(rotation);
	float sx     = scale.X();
	float sy     = scale.Y();

	m[ 0] = cosine*sx; m[ 1] =  -sine*sy; m[ 2] = 0.0f; m[ 3] = position.X(); 
	m[ 4] =   sine*sx; m[ 5] = cosine*sy; m[ 6] = 0.0f; m[ 7] = position.Y(); 
	m[ 8] =      0.0f; m[ 9] =      0.0f; m[10] = 1.0f; m[11] = 0.0f; 
	m[12] =      0.0f; m[13] =      0.0f; m[14] = 0.0f; m[15] = 1.0f; 
}

int Graphics2::compare(const void *left, const void *right)
{
	return (*((const Graphics2 **)left))->position.Z() - (*((const Graphics2 **)right))->position.Z();
}

void Graphics2::setupGXBlendFunc(BlendMode blendMode_)
{
	switch(blendMode_)
	{
		case BlendMode::Filter:
			GXContext::instance().setBlendStateRgb
			(
				GXBlendMode::Add, 
				GXBlendFactor::SrcAlpha, 
				GXBlendFactor::OneMinusSrcAlpha 
			);
			GXContext::instance().setBlendStateAlpha
			(
				GXBlendMode::Add, 
				GXBlendFactor::SrcAlpha, 
				GXBlendFactor::OneMinusSrcAlpha 
			);
			break;
		case BlendMode::Addictive:
			GXContext::instance().setBlendStateRgb
			(
				GXBlendMode::Add, 
				GXBlendFactor::SrcAlpha, 
				GXBlendFactor::One 
			);
			GXContext::instance().setBlendStateAlpha
			(
				GXBlendMode::Add, 
				GXBlendFactor::SrcAlpha, 
				GXBlendFactor::One 
			);
			break;
		case BlendMode::Subtractive:
			GXContext::instance().setBlendStateRgb
			(
				GXBlendMode::ReverseSubtract, 
				GXBlendFactor::SrcAlpha, 
				GXBlendFactor::One 
			);
			GXContext::instance().setBlendStateAlpha
			(
				GXBlendMode::Add, 
				GXBlendFactor::SrcAlpha, 
				GXBlendFactor::One 
			);
			break;
	}
}



void Graphics2::setupGXTexture(int i, GXTexture *texture_)
{
	GXContext::instance().setTexture(i, texture_);
}