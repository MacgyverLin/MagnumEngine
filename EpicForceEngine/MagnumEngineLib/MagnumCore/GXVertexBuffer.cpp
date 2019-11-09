#include "GXVertexBuffer.h"
#include "GXContext.h"

GXVertexBuffer::GXVertexBuffer(int vertexCount_, const Vector<GXVertexFormat> &formats_, Usage usage_)
: vertexBufferHandle(0)
, vertexCount(vertexCount_)
, formats(formats_)
, usage(usage_)
{
	int oldVertexBufferHandle;
	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &oldVertexBufferHandle);

	prepareFormat();

	glGenBuffers(1, &vertexBufferHandle);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);

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
	glBufferData(GL_ARRAY_BUFFER, vertexCount*stride, 0, flag);
	glBindBuffer(GL_ARRAY_BUFFER, oldVertexBufferHandle);
}

GXVertexBuffer::~GXVertexBuffer()
{
	for(int i=0; i<GXContext::NUM_VERTEXBUFFERS; i++)
	{
		const GXVertexBuffer *vertexBuffer = GXContext::instance().getVertexBuffer(i);
		if(vertexBuffer==this)
		{
			GXContext::instance().setVertexBuffer(i, 0);
		}
	}

	if(vertexBufferHandle)
	{
		glDeleteBuffers(1, &vertexBufferHandle);

		vertexBufferHandle = 0;
	}
}

const Vector<GXVertexFormat> &GXVertexBuffer::getFormats() const
{
	return formats;
}

const Vector<int> &GXVertexBuffer::getOffsets() const
{
	return offsets;
}

int GXVertexBuffer::getVertexCount() const
{
	return vertexCount;
}

int GXVertexBuffer::getStreamCount() const
{
	return formats.length();
}

unsigned int GXVertexBuffer::getVertexHandle() const
{
	return vertexBufferHandle;
}

GXVertexBuffer::Usage GXVertexBuffer::getUsage() const
{
	return usage;
}

void GXVertexBuffer::setVertices(const char *buffer_, int to_, int count_)
{
	assert(to_ + count_ <= vertexCount*stride );

	int oldVertexBufferHandle;
	int oldIndexBufferHandle;
	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &oldVertexBufferHandle);
	glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &oldIndexBufferHandle);
	
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);
	glBufferSubData(GL_ARRAY_BUFFER, to_, count_, buffer_);
	glBindBuffer(GL_ARRAY_BUFFER, oldVertexBufferHandle);

	::checkGLError("setVertices");
}

void GXVertexBuffer::prepareFormat()
{
	offsets.resize(formats.length());

	int offset = 0;
	for(int i=0; i<offsets.length(); i++)
	{
		offsets[i]	= offset;
		offset		+= formats[i].getSize();
	}

	stride = offset;
}