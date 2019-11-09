#ifndef _GXStencilTestState_h_
#define _GXStencilTestState_h_

#include "GXDef.h"

namespace Magnum
{

/**
* GXStencilTestState encapsulate a Stencil Test State of Graphics Device
*/
class GXStencilTestState
{
public:
	GXStencilTestState(const GXStencilTestMode &mode_, unsigned int reference_, unsigned int readMask_, unsigned int writeMask_);

	bool GXStencilTestState::operator==(const GXStencilTestState &other_)
	{
		return mode==other_.mode && reference==other_.reference && 
			   readMask==other_.readMask && writeMask==other_.writeMask;
	}

	void set(const GXStencilTestMode &mode_, unsigned int reference_, unsigned int readMask_, unsigned int writeMask_);
	
	void setMode(const GXStencilTestMode &mode_);

	const GXStencilTestMode &getMode() const;

	void setReference(unsigned int reference_);

	unsigned int getReference() const;

	void setReadMask(unsigned int readMask_);

	unsigned int getReadMask() const;

	void setWriteMask(unsigned int writeMask_);

	unsigned int getWriteMask() const;
private:
	GXStencilTestMode	mode;
	unsigned int		reference;
	unsigned int		readMask;
	unsigned int		writeMask;
};

};

#endif