#include "GXPolygonOffsetState.h"

GXPolygonOffsetState::GXPolygonOffsetState(float factor_, float units_)
{
	set(factor_, units_);
}

void GXPolygonOffsetState::set(float factor_, float units_)
{
	this->factor	= factor_;
	this->units		= units_;
}

float GXPolygonOffsetState::getFactor() const
{
	return factor;
}

float GXPolygonOffsetState::getUnits() const
{
	return units;
}