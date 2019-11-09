#ifndef _GXBlendState_h_
#define _GXBlendState_h_

#include "GXDef.h"

namespace Magnum
{

/**
* GXBlendState encapsulate a Blending State of Graphics Device
*/
class GXBlendState
{
public:
	GXBlendState(const GXBlendMode &mode_, const GXBlendFactor &srcFactor_, const GXBlendFactor &dstFactor_);

	bool GXBlendState::operator==(const GXBlendState &other_)
	{
		return mode==other_.mode && srcFactor==other_.srcFactor && dstFactor==other_.dstFactor;
	}
	
	void set(const GXBlendMode &mode_, const GXBlendFactor &srcFactor_, const GXBlendFactor &dstFactor_);
	
	void setMode(const GXBlendMode &mode_);
	
	const GXBlendMode &getMode() const;

	void setSrcFactor(const GXBlendFactor &srcFactor_);

	const GXBlendFactor &getSrcFactor() const;

	void setDstFactor(const GXBlendFactor &dstFactor_);

	const GXBlendFactor &getDstFactor() const;
private:
	GXBlendMode		mode;
	GXBlendFactor	srcFactor;
	GXBlendFactor	dstFactor;
};

};

#endif