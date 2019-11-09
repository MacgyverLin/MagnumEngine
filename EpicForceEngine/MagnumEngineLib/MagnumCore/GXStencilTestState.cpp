#include "GXStencilTestState.h"

GXStencilTestState::GXStencilTestState(const GXStencilTestMode &mode_, unsigned int reference_, unsigned int readMask_, unsigned int writeMask_)
{
	set(mode_, reference_, readMask_, writeMask_);
}

void GXStencilTestState::set(const GXStencilTestMode &mode_, unsigned int reference_, unsigned int readMask_, unsigned int writeMask_)
{
	this->mode			= mode_;
	this->reference		= reference_;
	this->readMask		= readMask_;
	this->writeMask		= writeMask_;
}

void GXStencilTestState::setMode(const GXStencilTestMode &mode_)
{
	this->mode = mode_;
}

const GXStencilTestMode &GXStencilTestState::getMode() const
{
	return mode;
}

void GXStencilTestState::setReference(unsigned int reference_)
{
	this->reference = reference_;
}

unsigned int GXStencilTestState::getReference() const
{
	return reference;
}

void GXStencilTestState::setReadMask(unsigned int readMask_)
{
	this->readMask		= readMask_;
}

unsigned int GXStencilTestState::getReadMask() const
{
	return readMask;
}

void GXStencilTestState::setWriteMask(unsigned int writeMask_)
{
	this->writeMask		= writeMask_;
}

unsigned int GXStencilTestState::getWriteMask() const
{
	return writeMask;
}