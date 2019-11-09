#ifndef _GXDepthTestState_h_
#define _GXDepthTestState_h_

#include "GXDef.h"

namespace Magnum
{

/**
* GXColorBuffer encapsulate a the Depth Test State of Graphics Device
*/
class GXDepthTestState
{
public:
	GXDepthTestState(const GXDepthTestMode &mode_, bool writeMask_);

	bool GXDepthTestState::operator==(const GXDepthTestState &other_)
	{
		return mode==other_.mode && writeMask==other_.writeMask;
	}

	void set(const GXDepthTestMode &mode_, bool writeMask_);

	void setMode(const GXDepthTestMode &mode_);

	const GXDepthTestMode &getMode() const;

	void setWriteMask(bool writeMask_);

	bool getWriteMask() const;
private:
	GXDepthTestMode mode;
	bool			writeMask;
};

};

#endif