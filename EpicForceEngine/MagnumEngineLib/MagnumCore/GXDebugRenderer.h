#ifndef _GXDebugRenderer_h_
#define _GXDebugRenderer_h_

#include "GXContext.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "ColorRGBA.h"
#include "Matrix4.h"
#include "IComponentDebugRenderer.h"
using namespace Magnum;

namespace Magnum
{

/**
* GXColorBuffer encapsulate a the GXDebugRenderer Interface
*/
class GXDebugRenderer : public IComponentDebugRenderer
{
public:
	GXDebugRenderer(GXContext &context_, const Matrix4 &projTransform, const Matrix4 &viewTransform);
	~GXDebugRenderer();

private:
	virtual void renderPrimitive(DrawMode mode, const Matrix4 &transform, const Vector3 *v, const ColorRGBA &color, int count);
	virtual void renderPrimitive(DrawMode mode, const Matrix4 &transform, const Vector3 *v, const ColorRGBA *c, int count);
	
	GXContext &context;
};

};

#endif