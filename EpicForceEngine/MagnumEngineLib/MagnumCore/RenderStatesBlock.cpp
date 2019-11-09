///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "RenderStatesBlock.h"
using namespace Magnum;

RenderStatesBlock::RenderStatesBlock()
: blendEnable					(false)										// true, false
, blendModeRgb					(GXBlendMode::Add)							// Add, Subtract, ReverseSubtract
, blendSrcFactorRgb				(GXBlendFactor::One)						// Zero, One, SrcColor, OneMinusSrcColor, SrcAlpha, OneMinusSrcAlpha, DstColor, OneMinusDstColor, DstAlpha, OneMinusDstAlpha, SrcAlphaSaturate
, blendDstFactorRgb				(GXBlendFactor::Zero)						// Zero, One, SrcColor, OneMinusSrcColor, SrcAlpha, OneMinusSrcAlpha, DstColor, OneMinusDstColor, DstAlpha, OneMinusDstAlpha, SrcAlphaSaturate
, blendModeAlpha				(GXBlendMode::Add)							// Add, Subtract, ReverseSubtract
, blendSrcFactorAlpha			(GXBlendFactor::SrcAlpha)					// Zero, One, SrcColor, OneMinusSrcColor, SrcAlpha, OneMinusSrcAlpha, DstColor, OneMinusDstColor, DstAlpha, OneMinusDstAlpha, SrcAlphaSaturate
, blendDstFactorAlpha			(GXBlendFactor::OneMinusSrcAlpha)			// Zero, One, SrcColor, OneMinusSrcColor, SrcAlpha, OneMinusSrcAlpha, DstColor, OneMinusDstColor, DstAlpha, OneMinusDstAlpha, SrcAlphaSaturate

, colorMask						(GXColorMask::Rgba)

, cullEnable					(false)										// true, false
, cullMode						(GXCullMode::CW)							// CW, CCW

, depthTestEnable				(false)										// true, false
, depthWriteEnable				(true)										// true, false
, depthTestMode					(GXDepthTestMode::LEqual)					// Always, Never, Equal, NotEequal, Less, Greater, LEqual,	GEqual;

, lineWidth						(1.0)
, polygonOffsetFactor			(1.0)
, polygonOffsetUnit				(0.0)

, scissor						(0, 0, 640, 480)

, stencilTestEnable				(false)										// true, false
, stencilTestModeFront			(GXStencilTestMode::Always)					// Always, Never, Equal, NotEequal, Less, Greater, LEqual,	GEqual;
, stencilTestRefFront			(0)
, stencilTestMaskFront			(0xffffffff)
, stencilTestWriteMaskFront		(0xffffffff)
, stencilOpFailFront			(GXStencilOp::Keep)							// Keep, Zero, Replace, Invert, Incr, Decr, IncrWrap, DecrWrap
, stencilOpZPassFront			(GXStencilOp::Keep)							// Keep, Zero, Replace, Invert, Incr, Decr, IncrWrap, DecrWrap
, stencilOpZFailFront			(GXStencilOp::Keep)							// Keep, Zero, Replace, Invert, Incr, Decr, IncrWrap, DecrWrap

, stencilTestModeBack			(GXStencilTestMode::Always)					// Always, Never, Equal, NotEequal, Less, Greater, LEqual,	GEqual;
, stencilTestRefBack			(0)
, stencilTestMaskBack			(0xffffffff)
, stencilTestWriteMaskBack		(0xffffffff)
, stencilOpFailBack				(GXStencilOp::Keep)							// Keep, Zero, Replace, Invert, Incr, Decr, IncrWrap, DecrWrap
, stencilOpZPassBack			(GXStencilOp::Keep)							// Keep, Zero, Replace, Invert, Incr, Decr, IncrWrap, DecrWrap
, stencilOpZFailBack			(GXStencilOp::Keep)							// Keep, Zero, Replace, Invert, Incr, Decr, IncrWrap, DecrWrap

, viewport						(0, 0, 640, 480)
{
}

RenderStatesBlock::~RenderStatesBlock()
{
}

bool RenderStatesBlock::construct(const char *type_, const char *value_)
{
	String type		= type_;
	String value	= value_;
	type.toLower();
	value.toLower();

	if(type=="blendenable")
	{
		blendEnable = getBoolean(value);
		return true;
	}
	else if(type=="blendmodergb")
	{
		return blendModeRgb.set(value);
	}
	else if(type=="blendsrcfactorrgb")
	{
		return blendSrcFactorRgb.set(value);
	}
	else if(type=="blenddstfactorrgb")
	{
		return blendDstFactorRgb.set(value);
	}
	else if(type=="blendmodealpha")
	{
		return blendModeAlpha.set(value);
	}
	else if(type=="blendsrcfactoralpha")
	{
		return blendSrcFactorAlpha.set(value);
	}
	else if(type=="blenddstfactoralpha")
	{
		return blendDstFactorAlpha.set(value);
	}
	else if(type=="blendmode")
	{
		blendModeRgb.set(value);
		return blendModeAlpha.set(value);
	}
	else if(type=="blendsrcfactor")
	{
		blendSrcFactorRgb.set(value);
		return blendSrcFactorAlpha.set(value);
	}
	else if(type=="blenddstfactor")
	{
		blendDstFactorRgb.set(value);
		return blendDstFactorAlpha.set(value);
	}
	else if(type=="colormask")
	{
		return colorMask.set(value);
	}
	else if(type=="cullenable")
	{
		cullEnable = getBoolean(value);
		return true;
	}
	else if(type=="cullmode")
	{
		return cullMode.set(value);
	}
	else if(type=="depthtestenable")
	{
		depthTestEnable = getBoolean(value);
		return true;
	}
	else if(type=="depthwriteenable")
	{
		depthWriteEnable = getBoolean(value);
		return true;
	}
	else if(type=="depthtestmode")
	{
		return depthTestMode.set(value);
	}
	else if(type=="linewidth")
	{
		lineWidth = atof(value);
		return true;
	}
	else if(type=="polygonoffsetfactor")
	{
		polygonOffsetFactor = atof(value);
		return true;
	}
	else if(type=="polygonoffsetunit")
	{
		polygonOffsetUnit = atof(value);
		return true;
	}
	else if(type=="scissor")
	{
		return true;
	}
	else if(type=="stenciltestenable")
	{
		stencilTestEnable = getBoolean(value);
		return true;
	}
	else if(type=="stenciltestmodefront")
	{
		return stencilTestModeFront.set(value);
	}
	else if(type=="stenciltestreffront")
	{
		stencilTestRefFront = getInteger(value);
		return true;
	}
	else if(type=="stenciltestmaskfront")
	{
		stencilTestMaskFront = getInteger(value);
		return true;
	}
	else if(type=="stenciltestwritemaskfront")
	{
		stencilTestWriteMaskFront = getInteger(value);
		return true;
	}
	else if(type=="stencilopfailfront")
	{
		return stencilOpFailFront.set(value);
	}
	else if(type=="stencilopzpassfront")
	{
		return stencilOpZPassFront.set(value);
	}
	else if(type=="stencilopzfailfront")
	{
		return stencilOpZFailFront.set(value);
	}
	else if(type=="stenciltestmodeback")
	{
		return stencilTestModeBack.set(value);
	}
	else if(type=="stenciltestrefback")
	{
		stencilTestRefBack = getInteger(value);
		return true;
	}
	else if(type=="stenciltestmaskback")
	{
		stencilTestMaskBack = getInteger(value);
		return true;
	}
	else if(type=="stenciltestwritemaskback")
	{
		stencilTestWriteMaskBack = getInteger(value);
		return true;
	}
	else if(type=="stencilopfailback")
	{
		return stencilOpFailBack.set(value);
	}
	else if(type=="stencilopzpassback")
	{
		return stencilOpZPassBack.set(value);
	}
	else if(type=="stencilopzfailback")
	{
		return stencilOpZFailBack.set(value);
	}
	else if(type=="stenciltestmode")
	{
		stencilTestModeFront.set(value);
		return stencilTestModeBack.set(value);
	}
	else if(type=="stenciltestref")
	{
		stencilTestRefFront = getInteger(value);
		stencilTestRefBack  = getInteger(value);
		return true;
	}
	else if(type=="stenciltestmask")
	{
		stencilTestMaskFront = getInteger(value);
		stencilTestMaskBack  = getInteger(value);
		return true;
	}
	else if(type=="stenciltestwritemask")
	{
		stencilTestWriteMaskFront = getInteger(value);
		stencilTestWriteMaskBack  = getInteger(value);
		return true;
	}
	else if(type=="stencilopfail")
	{
		stencilOpFailFront.set(value);
		return stencilOpFailBack.set(value);
	}
	else if(type=="stencilopzpass")
	{
		stencilOpZPassFront.set(value);
		return stencilOpZPassBack.set(value);
	}
	else if(type=="stencilopzfail")
	{
		stencilOpZFailFront.set(value);
		return stencilOpZFailBack.set(value);
	}
	else if(type=="viewport")
	{
		return true;
	}
	else
		return false;
}

void RenderStatesBlock::read(InputStream &is)
{
	is >> blendEnable					; // false						// true, false
	is >> blendModeRgb					; // Add						// Add, Subtract, ReverseSubtract
	is >> blendSrcFactorRgb				; // One						// Zero, One, SrcColor, OneMinusSrcColor, SrcAlpha, OneMinusSrcAlpha, DstColor, OneMinusDstColor, DstAlpha, OneMinusDstAlpha, SrcAlphaSaturate
	is >> blendDstFactorRgb				; // Zero						// Zero, One, SrcColor, OneMinusSrcColor, SrcAlpha, OneMinusSrcAlpha, DstColor, OneMinusDstColor, DstAlpha, OneMinusDstAlpha, SrcAlphaSaturate
	is >> blendModeAlpha				; // Add						// Add, Subtract, ReverseSubtract
	is >> blendSrcFactorAlpha			; // SrcAlpha					// Zero, One, SrcColor, OneMinusSrcColor, SrcAlpha, OneMinusSrcAlpha, DstColor, OneMinusDstColor, DstAlpha, OneMinusDstAlpha, SrcAlphaSaturate
	is >> blendDstFactorAlpha			; // OneMinusSrcAlpha			// Zero, One, SrcColor, OneMinusSrcColor, SrcAlpha, OneMinusSrcAlpha, DstColor, OneMinusDstColor, DstAlpha, OneMinusDstAlpha, SrcAlphaSaturate

	is >> colorMask						; // RGBA

	is >> cullEnable					; // false						// true, false
	is >> cullMode						; // CW							// CW, CCW

	is >> depthTestEnable				; // false						// true, false
	is >> depthWriteEnable				; // true						// true, false
	is >> depthTestMode					; // LEqual						// Always, Never, Equal, NotEequal, Less, Greater, LEqual,	GEqual;

	is >> lineWidth						; // 1.0
	is >> polygonOffsetFactor			; // 1.0
	is >> polygonOffsetUnit				; // 0.0

	is >> scissor						; // 0, 0, 640, 480

	is >> stencilTestEnable				; // false						// true, false
	is >> stencilTestModeFront			; // Always						// Always, Never, Equal, NotEequal, Less, Greater, LEqual,	GEqual;
	is >> stencilTestRefFront			; // 0
	is >> stencilTestMaskFront			; // 0xffffffff
	is >> stencilTestWriteMaskFront		; // 0xffffffff
	is >> stencilOpFailFront			; // Keep						// Keep, Zero, Replace, Invert, Incr, Decr, IncrWrap, DecrWrap
	is >> stencilOpZPassFront			; // Keep						// Keep, Zero, Replace, Invert, Incr, Decr, IncrWrap, DecrWrap
	is >> stencilOpZFailFront			; // Keep						// Keep, Zero, Replace, Invert, Incr, Decr, IncrWrap, DecrWrap

	is >> stencilTestModeBack			; // Always						// Always, Never, Equal, NotEequal, Less, Greater, LEqual,	GEqual;
	is >> stencilTestRefBack			; // 0
	is >> stencilTestMaskBack			; // 0xffffffff
	is >> stencilTestWriteMaskBack		; // 0xffffffff
	is >> stencilOpFailBack				; // Keep						// Keep, Zero, Replace, Invert, Incr, Decr, IncrWrap, DecrWrap
	is >> stencilOpZPassBack			; // Keep						// Keep, Zero, Replace, Invert, Incr, Decr, IncrWrap, DecrWrap
	is >> stencilOpZFailBack			; // Keep						// Keep, Zero, Replace, Invert, Incr, Decr, IncrWrap, DecrWrap
   
	is >> viewport						; // 0, 0, 640, 480
}

void RenderStatesBlock::write(OutputStream &os) const
{
	os << blendEnable					; // false						// true, false
	os << blendModeRgb					; // Add						// Add, Subtract, ReverseSubtract
	os << blendSrcFactorRgb				; // One						// Zero, One, SrcColor, OneMinusSrcColor, SrcAlpha, OneMinusSrcAlpha, DstColor, OneMinusDstColor, DstAlpha, OneMinusDstAlpha, SrcAlphaSaturate
	os << blendDstFactorRgb				; // Zero						// Zero, One, SrcColor, OneMinusSrcColor, SrcAlpha, OneMinusSrcAlpha, DstColor, OneMinusDstColor, DstAlpha, OneMinusDstAlpha, SrcAlphaSaturate
	os << blendModeAlpha				; // Add						// Add, Subtract, ReverseSubtract
	os << blendSrcFactorAlpha			; // SrcAlpha					// Zero, One, SrcColor, OneMinusSrcColor, SrcAlpha, OneMinusSrcAlpha, DstColor, OneMinusDstColor, DstAlpha, OneMinusDstAlpha, SrcAlphaSaturate
	os << blendDstFactorAlpha			; // OneMinusSrcAlpha			// Zero, One, SrcColor, OneMinusSrcColor, SrcAlpha, OneMinusSrcAlpha, DstColor, OneMinusDstColor, DstAlpha, OneMinusDstAlpha, SrcAlphaSaturate

	os << colorMask						; // RGBA

	os << cullEnable					; // false						// true, false
	os << cullMode						; // CW							// CW, CCW

	os << depthTestEnable				; // false						// true, false
	os << depthWriteEnable				; // true						// true, false
	os << depthTestMode					; // LEqual						// Always, Never, Equal, NotEequal, Less, Greater, LEqual,	GEqual;

	os << lineWidth						; // 1.0
	os << polygonOffsetFactor			; // 1.0
	os << polygonOffsetUnit				; // 0.0

	os << scissor						; // 0, 0, 640, 480

	os << stencilTestEnable				; // false						// true, false
	os << stencilTestModeFront			; // Always						// Always, Never, Equal, NotEequal, Less, Greater, LEqual,	GEqual;
	os << stencilTestRefFront			; // 0
	os << stencilTestMaskFront			; // 0xffffffff
	os << stencilTestWriteMaskFront		; // 0xffffffff
	os << stencilOpFailFront			; // Keep						// Keep, Zero, Replace, Invert, Incr, Decr, IncrWrap, DecrWrap
	os << stencilOpZPassFront			; // Keep						// Keep, Zero, Replace, Invert, Incr, Decr, IncrWrap, DecrWrap
	os << stencilOpZFailFront			; // Keep						// Keep, Zero, Replace, Invert, Incr, Decr, IncrWrap, DecrWrap

	os << stencilTestModeBack			; // Always						// Always, Never, Equal, NotEequal, Less, Greater, LEqual,	GEqual;
	os << stencilTestRefBack			; // 0
	os << stencilTestMaskBack			; // 0xffffffff
	os << stencilTestWriteMaskBack		; // 0xffffffff
	os << stencilOpFailBack				; // Keep						// Keep, Zero, Replace, Invert, Incr, Decr, IncrWrap, DecrWrap
	os << stencilOpZPassBack			; // Keep						// Keep, Zero, Replace, Invert, Incr, Decr, IncrWrap, DecrWrap
	os << stencilOpZFailBack			; // Keep						// Keep, Zero, Replace, Invert, Incr, Decr, IncrWrap, DecrWrap

	os << viewport						; // 0, 0, 640, 480
}

bool RenderStatesBlock::getBoolean(const String &value)
{
	if(value=="true")
		return true;
	else
		return false;
}

int RenderStatesBlock::getInteger(const String &value)
{
	if(value.length()>=2 && value[0]=='0' && value[1]=='x')
	{
		return strtoul(value.text(), 0, 16);
	}
	else
	{
		return atoi(value.text());
	}
}