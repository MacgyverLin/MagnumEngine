#include "GXDebugRenderer.h"
using namespace Magnum;

GXDebugRenderer::GXDebugRenderer(GXContext &context_, const Matrix4 &projTransform_, const Matrix4 &viewTransform_)
: IComponentDebugRenderer(projTransform_, viewTransform_)
, context(context_)
{
}

GXDebugRenderer::~GXDebugRenderer()
{
}

void GXDebugRenderer::renderPrimitive(DrawMode mode, const Matrix4 &worldTransform, const Vector3 *v, const ColorRGBA &c, int count)
{
	context.draw(mode, projTransform, viewTransform, worldTransform, v, c, count);
}

void GXDebugRenderer::renderPrimitive(DrawMode mode, const Matrix4 &worldTransform, const Vector3 *v, const ColorRGBA *c, int count)
{
	context.draw(mode, projTransform, viewTransform, worldTransform, v, c, count);
}