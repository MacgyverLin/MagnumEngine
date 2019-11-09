///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited			 //
//																 //
// Author : Mac Lin									             //
// Module : EpicForceEngine										 //
// Date   : 19/Aug/2011											 //
//																 //
///////////////////////////////////////////////////////////////////
#ifndef _Graphics2_h_
#define _Graphics2_h_

#include "Component.h"
#include "Vector2.h"
#include "ColorRGBA.h"
#include "Video.h"
#include "GXContext.h"

namespace Magnum
{

class Graphics2 : public Component
{
friend class Video;
public:
	enum BlendMode
	{
		Filter,
		Addictive,
		Subtractive
	};

	Graphics2();
	virtual ~Graphics2();

	void setPosition(const Vector3 &position_);
	const Vector3 &getPosition() const;

	void setScale(const Vector2 &scale_);
	const Vector2 &getScale() const;

	void setColor(const ColorRGBA &color_);
	const ColorRGBA &getColor() const;

	void setRotation(float rotation_);
	float getRotation() const;

	void setBlendMode(Graphics2::BlendMode blendMode_);
	Graphics2::BlendMode getBlendMode() const;
protected:
	void calcWorldTransform(Matrix4 &worldMat_);

	static int compare(const void *left, const void *right);

	virtual void draw(const Video::Manager::RenderParam &param) = 0;
	void setupGXBlendFunc(BlendMode blendMode_);
	void setupGXTexture(int i, GXTexture *texture_);
private:

/////////////////////////////////////////////////////////////////
public:
	Vector3			position;
	Vector2			scale;
	ColorRGBA		color;
	float			rotation;

	BlendMode		blendMode;
protected:
private:
};

};

#endif
