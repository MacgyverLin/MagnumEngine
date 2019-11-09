///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _RenderStatesBlock_h_
#define _RenderStatesBlock_h_

#include "Stage.h"
#include "Platform.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "GXDef.h"

namespace Magnum
{

class RenderStatesBlock
{
public:
	RenderStatesBlock();
	virtual ~RenderStatesBlock();

	bool construct(const char *type, const char *value);

	void read(InputStream &is);
	void write(OutputStream &os) const;

	bool getBoolean(const String &value);
	int getInteger(const String &value);

	bool					blendEnable						; // false						// true, false
	GXBlendMode				blendModeRgb					; // Add						// Add, Subtract, ReverseSubtract
	GXBlendFactor			blendSrcFactorRgb				; // One						// Zero, One, SrcColor, OneMinusSrcColor, SrcAlpha, OneMinusSrcAlpha, DstColor, OneMinusDstColor, DstAlpha, OneMinusDstAlpha, SrcAlphaSaturate
	GXBlendFactor			blendDstFactorRgb				; // Zero						// Zero, One, SrcColor, OneMinusSrcColor, SrcAlpha, OneMinusSrcAlpha, DstColor, OneMinusDstColor, DstAlpha, OneMinusDstAlpha, SrcAlphaSaturate
	GXBlendMode				blendModeAlpha					; // Add						// Add, Subtract, ReverseSubtract
	GXBlendFactor			blendSrcFactorAlpha				; // SrcAlpha					// Zero, One, SrcColor, OneMinusSrcColor, SrcAlpha, OneMinusSrcAlpha, DstColor, OneMinusDstColor, DstAlpha, OneMinusDstAlpha, SrcAlphaSaturate
	GXBlendFactor			blendDstFactorAlpha				; // OneMinusSrcAlpha			// Zero, One, SrcColor, OneMinusSrcColor, SrcAlpha, OneMinusSrcAlpha, DstColor, OneMinusDstColor, DstAlpha, OneMinusDstAlpha, SrcAlphaSaturate

	GXColorMask				colorMask						; // RGBA
		
	bool					cullEnable						; // false						// true, false
	GXCullMode				cullMode						; // CW							// CW, CCW

	bool					depthTestEnable					; // false						// true, false
	bool					depthWriteEnable				; // true						// true, false
	GXDepthTestMode			depthTestMode					; // LEqual						// Always, Never, Equal, NotEequal, Less, Greater, LEqual,	GEqual;

	float					lineWidth						; // 1.0
	float					polygonOffsetFactor				; // 1.0
	float					polygonOffsetUnit				; // 0.0

	GXImageRect				scissor							; // 0, 0, 640, 480

	bool					stencilTestEnable				; // false						// true, false
	GXStencilTestMode		stencilTestModeFront			; // Always						// Always, Never, Equal, NotEequal, Less, Greater, LEqual,	GEqual;
	unsigned int			stencilTestRefFront				; // 0
	unsigned int			stencilTestMaskFront			; // 0xffffffff
	unsigned int			stencilTestWriteMaskFront		; // 0xffffffff
	GXStencilOp				stencilOpFailFront				; // Keep						// Keep, Zero, Replace, Invert, Incr, Decr, IncrWrap, DecrWrap
	GXStencilOp				stencilOpZPassFront				; // Keep						// Keep, Zero, Replace, Invert, Incr, Decr, IncrWrap, DecrWrap
	GXStencilOp				stencilOpZFailFront				; // Keep						// Keep, Zero, Replace, Invert, Incr, Decr, IncrWrap, DecrWrap
	
	GXStencilTestMode		stencilTestModeBack				; // Always						// Always, Never, Equal, NotEequal, Less, Greater, LEqual,	GEqual;
	unsigned int			stencilTestRefBack				; // 0
	unsigned int			stencilTestMaskBack				; // 0xffffffff
	unsigned int			stencilTestWriteMaskBack		; // 0xffffffff
	GXStencilOp				stencilOpFailBack				; // Keep						// Keep, Zero, Replace, Invert, Incr, Decr, IncrWrap, DecrWrap
	GXStencilOp				stencilOpZPassBack				; // Keep						// Keep, Zero, Replace, Invert, Incr, Decr, IncrWrap, DecrWrap
	GXStencilOp				stencilOpZFailBack				; // Keep						// Keep, Zero, Replace, Invert, Incr, Decr, IncrWrap, DecrWrap
															   
	GXImageRect				viewport						; // 0, 0, 640, 480
};

};

#endif
