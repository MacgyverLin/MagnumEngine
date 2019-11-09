#ifndef _GXCullFaceState_h_
#define _GXCullFaceState_h_

#include "GXDef.h"

namespace Magnum
{

/**
* GXColorBuffer encapsulate a the Culling State of Graphics Device
*/
class GXCullState
{
public:
	GXCullState(const GXCullMode &cullFaceDirection_);

	bool GXCullState::operator==(const GXCullState &other_)
	{
		return cullMode==other_.cullMode;
	}

	void set(const GXCullMode &cullFaceDirection_);

	void setMode(const GXCullMode &cullFaceDirection_);

	const GXCullMode &getMode() const;
private:
	GXCullMode		cullMode;
};

};

#endif