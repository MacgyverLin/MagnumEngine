#ifndef _GXPolygonOffset_h_
#define _GXPolygonOffset_h_

#include "GXDef.h"

namespace Magnum
{

/**
* GXColorBuffer encapsulate a the Polygon Offset State of Graphics Device
*/
class GXPolygonOffsetState
{
public:
	GXPolygonOffsetState(float factor_, float units_);

	bool GXPolygonOffsetState::operator==(const GXPolygonOffsetState &other_)
	{
		return factor==other_.factor && units==other_.units;
	}
	
	void set(float factor_, float units_);

	float getFactor() const;

	float getUnits() const;
private:
	float factor;
	float units;
};

};

#endif