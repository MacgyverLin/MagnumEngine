#ifndef _GXContext_h_
#define _GXContext_h_

#include "GXDef.h"
#include "GXBlendState.h"
#include "GXColorBuffer.h"
#include "GXCullState.h"
#include "GXDepthTestState.h"
#include "GXFrameBuffer.h"
#include "GXPixelBuffer.h"
#include "GXPolygonOffsetState.h"
#include "GXPrimitive.h"
#include "GXRenderTarget.h"
#include "GXShaderProgram.h"
#include "GXStencilTestState.h"
#include "GXStencilOpState.h"
#include "GXTexture.h"
#include "GXTexture2D.h"
#include "GXTextureCube.h"
#include "GXVertexBuffer.h"
#include "GXIndexBuffer.h"
#include "Graphics2.h"
#include "Singleton.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "ColorRGBA.h"
using namespace Magnum;

namespace Magnum
{

/**
* GXColorBuffer encapsulate a the Context of Graphics Device
*/
class GXContext : public Singleton<GXContext>
{
private:
	GXContext(const GXContext &context_);
	GXContext &operator = (const GXContext &context_);
public:
	class Quad
	{
	public:
		Quad();
		~Quad();

		float u0, v0;
		float u1, v1;
		float width, height;
	};

	enum
	{
		NUM_VERTEXBUFFERS	= 4,
		NUM_INDEXBUFFERS	= 4,
		NUM_TEXTURES		= 8,
	};

	enum GraphicsUpdate
	{
		None				= 0x00000000,
		BlendFunc			= 0x00000001,
		ClearColor			= 0x00000002,
		ClearDepth			= 0x00000004,
		ClearStencil		= 0x00000008,
		ColorMask			= 0x00000010,
		CullFace			= 0x00000020,	
		DepthFunc			= 0x00000040,
		DepthRange			= 0x00000080,
		Enable				= 0x00000100,
		FrameBuffer			= 0x00000200,
		LineWidth			= 0x00000400,
		PolygonOffset		= 0x00000800,
		Scissor				= 0x00001000,
		ShaderProgram		= 0x00002000,
		StencilFunc			= 0x00004000,
		StencilOp			= 0x00008000,	
		Texture0			= 0x00010000,
		TextureN			= 0x00020000,
		VertexBuffer0		= 0x00040000,
		VertexBufferN		= 0x00080000,
		IndexBuffer0		= 0x00100000,
		IndexBufferN		= 0x00200000,
		Viewport			= 0x00400000,
	};

	GXContext(int width_, int height_,
		      GXPixelFormat colorFormat_,
			  GXPixelFormat depthFormat_,
			  GXMultiSampleMode multiSampleMode_);
	
	virtual ~GXContext();

	const GXFrameBuffer *getScreen() const;
	
	void flush();

	void finish();
	
	void clear();
	
	void clear(GXClearMask mask_);

	// flat primitives
	void draw(GXDrawMode mode_, const Matrix4 &projTransform_, const Matrix4 &viewTransform_, const Matrix4 &worldTransform_, 
			  const Vector3 *vertices_, const ColorRGBA &color_, int count_);
	
	// flat texture primitives
	void draw(GXDrawMode mode_, const Matrix4 &projTransform_, const Matrix4 &viewTransform_, const Matrix4 &worldTransform_, 
			  const Vector3 *vertices_, const ColorRGBA &color_, const Vector2 *texcoords_, int count_);

	// gourand primitives
	void draw(GXDrawMode mode_, const Matrix4 &projTransform_, const Matrix4 &viewTransform_, const Matrix4 &worldTransform_, 
			  const Vector3 *vertices_, const ColorRGBA *colors_, int count_);

	// gourand texture primitives
	void draw(GXDrawMode mode_, const Matrix4 &projTransform_, const Matrix4 &viewTransform_, const Matrix4 &worldTransform_, 
			  const Vector3 *vertices_, const ColorRGBA *colors_, const Vector2 *texcoords_, int count_);

	// quad
	void drawQuad(const Matrix4 &projTransform_, const Matrix4 &viewTransform_, const Matrix4 &worldTransform_, 
				  const float *vertices_, const ColorRGBA *colors_, const float *texcoords_,
				  int count_);

	void drawQuad(const Matrix4 &projTransform_, const Matrix4 &viewTransform_, const Matrix4 &worldTransform_, 
				  float xOffset_, float yOffset_, const ColorRGBA &color_,
				  const Quad &quad_);

	void draw(GXDrawMode mode_, int first_, int count_);
	
	void draw(GXDrawMode mode_, int first_, int count_, int repeat_);
	
	void draw(const Vector<GXPrimitive> &primitives_);
	
	void draw(const Vector<GXPrimitive> &primitives_, int first_, int count_);
	
	void readPixels(Vector<unsigned char> &pixels_, GXPixelFormat format_, int sx_, int sy_, int sw_, int sh_);
	
	void readPixels(GXTexture2D *texture_, int level_, int dx_, int dy_, int sx_, int sy_, int sw_, int sh_);
	
	void readPixels(GXTextureCube *texture_, int level_, GXTextureCubeFace cubeFace_, int dx_, int dy_, int sx_, int sy_, int sw_, int sh_);
	
	const GXShaderProgram *getShaderProgram() const;

	void setShaderProgram(GXShaderProgram *program_);

	const GXVertexBuffer *getVertexBuffer(int index_) const;
	
	void setVertexBuffer(int index_, GXVertexBuffer *buffer_);

	const GXIndexBuffer *getIndexBuffer(int index_) const;

	void setIndexBuffer(int index_, GXIndexBuffer *buffer_);
	
	const GXTexture *getTexture(int index_);
	
	void setTexture(int index_, GXTexture *texture_);

	GXFrameBuffer *getFrameBuffer() const;
	
	void setFrameBuffer(GXFrameBuffer *buffer_);

	bool isEnabled(GXEnableMode mode_) const;

	void enable(GXEnableMode mode_, bool status_);
	
	void enable(GXEnableMode mode_);
	
	void disable(GXEnableMode mode_);
	
	const GXImageRect &getScissor() const;

	void setScissor(const GXImageRect &scissor_);

	void setScissor(int x_, int y_, int w_, int h_);
	
	const GXImageRect &getViewport() const;

	void setViewport(const GXImageRect &viewport_);
	
	void setViewport(int x_, int y_, int w_, int h_);
	
	const Vector2 &getDepthRange() const;

	void setDepthRange(const Vector2 &depthRange_);
	
	void setDepthRange(float min_, float max_);

	const Vector4 &getClearColor() const;

	void setClearColor(const Vector4 &clearColor_);
	
	void setClearColor(float r_, float g_, float b_, float a_);
	
	void setClearColor(int r_, int g_, int b_, int a_);
	
	float getClearDepth() const;

	void setClearDepth(float clearDepth_);

	int getClearStencil() const;

	void setClearStencil(int clearStencil_);
	
	const GXCullState &getCullState() const;
	
	void setCullState(const GXCullState &cullFace_);
	
	void setCullState(const GXCullMode &cullMode_);
	
	const GXBlendState &getBlendState() const;

	void setBlendState(const GXBlendState &blendState_);
	
	void setBlendState(const GXBlendMode &mode_, const GXBlendFactor &srcFactor_, const GXBlendFactor &dstFactor_);
	
	const GXBlendState &getBlendStateRgb() const;

	void setBlendStateRgb(const GXBlendState &blendState_);

	void setBlendStateRgb(const GXBlendMode &mode_, const GXBlendFactor &srcFactor_, const GXBlendFactor &dstFactor_);
	
	const GXBlendState &getBlendStateAlpha() const;

	void setBlendStateAlpha(const GXBlendState &blendState_);

	void setBlendStateAlpha(const GXBlendMode &mode_, const GXBlendFactor &srcFactor_, const GXBlendFactor &dstFactor_);

	const GXDepthTestState &getDepthTestState() const;

	void setDepthTestState(const GXDepthTestState &depthTestState_);
	
	void setDepthTestState(const GXDepthTestMode &mode_, bool writeMask_);
	
	const GXPolygonOffsetState &getPolygonOffsetState() const;
	
	void setPolygonOffsetState(const GXPolygonOffsetState &polygonOffsetState_);

	void setPolygonOffsetState(float factor_, float units_);

	const GXStencilTestState &getStencilTestState() const;

	void setStencilTestState(const GXStencilTestState &func_);
	
	void setStencilTestState(const GXStencilTestMode &mode_, unsigned int reference_, unsigned int readMask_, unsigned int writeMask_);

	const GXStencilOpState &getStencilOpState() const;

	void setStencilOpState(const GXStencilOpState &op_);

	void setStencilOpState(const GXStencilOp &failOp_, const GXStencilOp &zFailOp_, const GXStencilOp &zPassOp_);

	const GXStencilTestState &getStencilTestStateFront() const;

	void setStencilTestStateFront(const GXStencilTestState &func_);
	
	void setStencilTestStateFront(const GXStencilTestMode &mode_, unsigned int reference_, unsigned int readMask_, unsigned int writeMask_);

	const GXStencilOpState &getStencilOpStateFront() const;

	void setStencilOpStateFront(const GXStencilOpState &op_);

	void setStencilOpStateFront(const GXStencilOp &failOp_, const GXStencilOp &zFailOp_, const GXStencilOp &zPassOp_);

	const GXStencilTestState &getStencilTestStateBack() const;

	void setStencilTestStateBack(const GXStencilTestState &func_);
	
	void setStencilTestStateBack(const GXStencilTestMode &mode_, unsigned int reference_, unsigned int readMask_, unsigned int writeMask_);

	const GXStencilOpState &getStencilOpStateBack() const;

	void setStencilOpStateBack(const GXStencilOpState &op_);

	void setStencilOpStateBack(const GXStencilOp &failOp_, const GXStencilOp &zFailOp_, const GXStencilOp &zPassOp_);

	const GXColorMask &getColorMask() const;
	
	void setColorMask(const GXColorMask &colorMask_);
	
	float getLineWidth() const;

	void setLineWidth(float lineWidth_);

	void notifyUpdate(GraphicsUpdate update_);

	void checkUpdate();
private:
	void update();
	void updateTexture(int i_, GXTexture *texture_);
	void updateVertexBuffer(int i_, GXVertexBuffer *vertexBuffer_);
	void updateIndexBuffer(int i_, GXIndexBuffer *indexBuffer_);
private:
	GXShaderProgram				*shaderProgram;
	Array<GXVertexBuffer		*> vertexBuffers;
	Array<GXIndexBuffer			*> indexBuffers;
	Array<GXTexture				*> textures;
	GXFrameBuffer				*frameBuffer;
	// static ImageSize[] screenSizes;
	GXFrameBuffer				*screen;
	// GraphicsCaps caps;

	unsigned int			notifyUpdateBits;
	
	// GraphicsState state;	
	GXBlendState			blendStateAlpha;
	GXBlendState			blendStateRgb;
	Vector4					clearColor;
	float					clearDepth;
	int						clearStencil;
	GXColorMask				colorMask;
	GXCullState				cullState;
	GXDepthTestState		depthTestState;
	Vector2					depthRange;
	GXEnableMode			enableMode;
	float					lineWidth;
	GXPolygonOffsetState	polygonOffsetState;
	GXImageRect				scissor;
	GXStencilTestState		stencilTestStateFront;
	GXStencilOpState		stencilOpStateFront;
	GXStencilTestState		stencilTestStateBack;
	GXStencilOpState		stencilOpStateBack;
	GXImageRect				viewport;
	// int[] handles = new int[16];

	/////////////////////////////////////////////
	// dor primitive draw
	GXShaderProgram *flatShader;
	GXShaderProgram *flatTexShader;
	GXShaderProgram *smoothShader;
	GXShaderProgram *smoothTexShader;
	GXShaderProgram *quadShader;
};

};

#endif