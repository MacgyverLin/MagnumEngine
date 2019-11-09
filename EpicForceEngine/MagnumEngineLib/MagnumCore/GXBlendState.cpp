#include "GXBlendState.h"

GXBlendState::GXBlendState(const GXBlendMode &mode_, const GXBlendFactor &srcFactor_, const GXBlendFactor &dstFactor_)
{
	set(mode_, srcFactor_, dstFactor_);
}

void GXBlendState::set(const GXBlendMode &mode_, const GXBlendFactor &srcFactor_, const GXBlendFactor &dstFactor_)
{
	mode		= mode_;
	srcFactor	= srcFactor_;
	dstFactor	= dstFactor_;
}

void GXBlendState::setMode(const GXBlendMode &mode_)
{
	this->mode		= mode_;
}

const GXBlendMode &GXBlendState::getMode() const
{
	return mode;
}

void GXBlendState::setSrcFactor(const GXBlendFactor &srcFactor_)
{
	this->srcFactor = srcFactor_;
}

const GXBlendFactor &GXBlendState::getSrcFactor() const
{
	return srcFactor;
}

void GXBlendState::setDstFactor(const GXBlendFactor &dstFactor_)
{
	this->dstFactor = dstFactor_;
}

const GXBlendFactor &GXBlendState::getDstFactor() const
{
	return dstFactor;
}