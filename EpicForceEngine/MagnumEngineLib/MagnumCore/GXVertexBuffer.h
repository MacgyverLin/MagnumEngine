#ifndef _GXVertexBuffer_h_
#define _GXVertexBuffer_h_

#include "GXDef.h"
#include "gldef.h"

namespace Magnum
{

/**
* GXVertexBuffer encapsulate a the Index Buffer of Graphics Device
*/
class GXVertexBuffer
{
friend class GXContext;
private:
	GXVertexBuffer(const GXVertexBuffer &vertexBuffer_);
	GXVertexBuffer &operator = (const GXVertexBuffer &vertexBuffer_);
public:	
	enum Usage
	{
		STATIC,
		DYNAMIC,
		STREAM,
	};
	GXVertexBuffer(int vertexCount_, const Vector<GXVertexFormat> &formats_, Usage usage_ = STATIC);

	virtual ~GXVertexBuffer();

	const Vector<GXVertexFormat> &getFormats() const;

	const Vector<int> &getOffsets() const;

	int getVertexCount() const;

	int getStreamCount() const;

	unsigned int getVertexHandle() const;

	Usage getUsage() const;

	void setVertices(const char *buffer_, int to_, int count_);

	template <class T>
	void setVertices(const T *vertices_, int count_)
	{
		assert(count_<=vertexCount);
		assert( sizeof(T) == stride );

		setVertices(vertices_, 0, 0, count_);
	}

	template <class T>
	void setVertices(const T *vertices_, int to_, int from_, int count_)
	{
		assert(to_  +count_<=vertexCount);
		assert( sizeof(T) == stride );

		int oldVertexBufferHandle;
		int oldIndexBufferHandle;
		glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &oldVertexBufferHandle);
		glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &oldIndexBufferHandle);
	
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);
		glBufferSubData(GL_ARRAY_BUFFER, to_*sizeof(T), count_*sizeof(T), &vertices_[from_]);
		glBindBuffer(GL_ARRAY_BUFFER, oldVertexBufferHandle);

		::checkGLError("setVertices");
	}

	/*
	template <class T>
	void setVertices(int stream, const Vector<T> &vertices)
	{
		assert( getStreamSize(stream)==sizeof(T) );
	}

	template <class T>
	void setVertices(int stream, const Vector<T> &vertices, int to, int from, int count)
	{
		assert( getStreamSize(stream)==sizeof(T) );
	}

	template <class T>
	void setVertices(int stream, const Vector<T> &vertices, int offset, int stride)
	{
		assert( getStreamSize(stream)==sizeof(T) );
	}

	template <class T>
	void setVertices(int stream, const Vector<T> &vertices, GXVertexFormat format, Vector4 trans, Vector4 scale)
	{
		assert( getStreamSize(stream)==sizeof(T) );
	}

	template <class T>
	void setVertices(int stream, const Vector<T> &vertices, GXVertexFormat format, Vector4 trans, Vector4 scale, int offset, int stride, int to, int from, int count)
	{
		assert( getStreamSize(stream)==sizeof(T) );
	}
	*/
private:
	void prepareFormat();
protected:
	unsigned int			vertexBufferHandle;

	int						vertexCount;
	int						GXPrimitiveCount;
	Vector<GXVertexFormat>	formats;
	Vector<int>				offsets;
	int						stride;

	Usage					usage;
};

};

#endif