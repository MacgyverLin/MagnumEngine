#include "GXIndexBuffer.h"
#include "GXContext.h"
#include "gldef.h"

GXIndexBuffer::GXIndexBuffer(int indexCount_, Usage usage_)
: indexBufferHandle(0)
, indexCount(indexCount_)
, usage(usage_)
{
	int oldIndexBufferHandle;
	glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &oldIndexBufferHandle);

	glGenBuffers(1, &indexBufferHandle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferHandle);

	int flag;
	switch(usage)
	{
		default:
		case STATIC:
			flag = GL_STATIC_DRAW;
			break;
		case DYNAMIC:
			flag = GL_DYNAMIC_DRAW;
			break;
		case STREAM:
			flag = GL_STREAM_DRAW;
			break;
	};
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount*sizeof(unsigned short), 0, flag);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, oldIndexBufferHandle);
}

GXIndexBuffer::~GXIndexBuffer()
{
	for(int i=0; i<GXContext::NUM_INDEXBUFFERS; i++)
	{
		const GXIndexBuffer *indexBuffer = GXContext::instance().getIndexBuffer(i);
		if(indexBuffer==this)
		{
			GXContext::instance().setIndexBuffer(i, 0);
		}
	}

	if(indexBufferHandle)
	{
		glDeleteBuffers(1, &indexBufferHandle);

		indexBufferHandle = 0;
	}
}

int GXIndexBuffer::getIndexCount() const
{
	return indexCount;
}

unsigned int GXIndexBuffer::getIndexHandle() const
{
	return indexBufferHandle;
}

GXIndexBuffer::Usage GXIndexBuffer::getUsage() const
{
	return usage;
}

void GXIndexBuffer::setIndices(const char *buffer_, int to_, int count_)
{
	assert(to_ + count_ <= indexCount*sizeof(short) );

	int oldVertexBufferHandle;
	int oldIndexBufferHandle;
	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &oldVertexBufferHandle);
	glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &oldIndexBufferHandle);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferHandle);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, to_, count_, buffer_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, oldIndexBufferHandle);
}

void GXIndexBuffer::setIndices(const unsigned short *indices_, int count_)
{
	assert(count_<=indexCount);

	setIndices(indices_, 0, 0, count_);
}

void GXIndexBuffer::setIndices(const unsigned short *indices_, int to_, int from_, int count_)
{
	assert(to_  +count_<=indexCount);

	int oldVertexBufferHandle;
	int oldIndexBufferHandle;
	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &oldVertexBufferHandle);
	glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &oldIndexBufferHandle);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferHandle);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, to_*sizeof(unsigned short), count_*sizeof(unsigned short), &indices_[from_]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, oldIndexBufferHandle);
}