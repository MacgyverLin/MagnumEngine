#include "GXDepthTestState.h"

GXDepthTestState::GXDepthTestState(const GXDepthTestMode &mode_, bool writeMask_)
{
	set(mode_, writeMask_);
}

void GXDepthTestState::set(const GXDepthTestMode &mode_, bool writeMask_)
{
	this->mode		= mode_;
	this->writeMask = writeMask_;
}

void GXDepthTestState::setMode(const GXDepthTestMode &mode_)
{
	this->mode		= mode_;
}

const GXDepthTestMode &GXDepthTestState::getMode() const
{
	return mode;
}

void GXDepthTestState::setWriteMask(bool writeMask_)
{
	this->writeMask = writeMask_;
}

bool GXDepthTestState::getWriteMask() const
{
	return writeMask;
}