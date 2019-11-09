#ifndef _GXIndexBuffer_h_
#define _GXIndexBuffer_h_

#include "GXDef.h"

namespace Magnum
{

/**
* GXIndexBuffer encapsulate a the Index Buffer of Graphics Device
*/
class GXIndexBuffer
{
friend class GXContext;
private:
	GXIndexBuffer(const GXIndexBuffer &indexBuffer_);
	GXIndexBuffer &operator = (const GXIndexBuffer &indexBuffer_);
public:
	enum Usage
	{
		STATIC,
		DYNAMIC,
		STREAM,
	};
	GXIndexBuffer(int indexCount_, Usage usage_ = STATIC);

	virtual ~GXIndexBuffer();

	int getIndexCount() const;

	unsigned int getIndexHandle() const;

	Usage getUsage() const;

	void setIndices(const char *buffer, int to_, int count_);

	void setIndices(const unsigned short *indices_, int count_);
	
	void setIndices(const unsigned short *indices_, int to_, int from_, int count_);
private:
protected:
	unsigned int			indexBufferHandle;

	int						indexCount;

	Usage					usage;
};

};

#endif