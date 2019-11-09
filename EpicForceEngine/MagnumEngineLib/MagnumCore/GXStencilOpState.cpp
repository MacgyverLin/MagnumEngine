#include "GXStencilOpState.h"

GXStencilOpState::GXStencilOpState(const GXStencilOp &failOp_, const GXStencilOp &zFailOp_, const GXStencilOp &zPassOp_)
{
	set(failOp_, zFailOp_, zPassOp_);
}

void GXStencilOpState::set(const GXStencilOp &failOp_, const GXStencilOp &zFailOp_, const GXStencilOp &zPassOp_)
{
	this->failOp	= failOp_;
	this->zFailOp	= zFailOp_;
	this->zPassOp	= zPassOp_;
}

void GXStencilOpState::setFailOp(const GXStencilOp &failOp_)
{
	this->failOp	= failOp_;
}

const GXStencilOp &GXStencilOpState::getFailOp() const
{
	return this->failOp;
}

void GXStencilOpState::setZFailOp(const GXStencilOp &zFailOp_)
{
	this->zFailOp = zFailOp_;
}

const GXStencilOp &GXStencilOpState::getZFailOp() const
{
	return this->zFailOp;
}

void GXStencilOpState::setZPassOp(const GXStencilOp &zPassOp_)
{
	this->zPassOp	= zPassOp_;
}

const GXStencilOp &GXStencilOpState::getZPassOp() const
{
	return this->zPassOp;
}