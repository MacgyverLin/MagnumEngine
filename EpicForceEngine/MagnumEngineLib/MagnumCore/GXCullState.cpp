#include "GXCullState.h"

GXCullState::GXCullState(const GXCullMode &cullMode_)
{
	set(cullMode_);
}

void GXCullState::set(const GXCullMode &cullMode_)
{
	this->cullMode		= cullMode_;
}

void GXCullState::setMode(const GXCullMode &cullMode_)
{
	this->cullMode		= cullMode_;
}

const GXCullMode &GXCullState::getMode() const
{
	return cullMode;
}