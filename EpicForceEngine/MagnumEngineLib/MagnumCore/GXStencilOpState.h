#ifndef _GXStencilOp_h_
#define _GXStencilOp_h_

#include "GXDef.h"

namespace Magnum
{

/**
* GXStencilOpState encapsulate a Stencil Operation State of Graphics Device
*/
class GXStencilOpState
{
public:
	GXStencilOpState(const GXStencilOp &failOp_, const GXStencilOp &zFailOp_, const GXStencilOp &zPassOp_);

	bool GXStencilOpState::operator==(const GXStencilOpState &other_)
	{
		return failOp==other_.failOp && zFailOp==other_.zFailOp && zPassOp==other_.zPassOp;
	}

	void set(const GXStencilOp &failOp_, const GXStencilOp &zFailOp_, const GXStencilOp &zPassOp_);

	void setFailOp(const GXStencilOp &failOp_);

	const GXStencilOp &getFailOp() const;

	void setZFailOp(const GXStencilOp &zFailOp_);

	const GXStencilOp &getZFailOp() const;

	void setZPassOp(const GXStencilOp &zPassOp_);

	const GXStencilOp &getZPassOp() const;
private:
	GXStencilOp failOp;
	GXStencilOp zFailOp;
	GXStencilOp zPassOp;
};

};

#endif