#include "Stage.h"

#ifdef EXPORTER
#include "gl2.h"
#include "gl2ext.h"
#else
#if defined(WIN32)
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
//#include <GLES2/gl2extimg.h>
#elif ( defined(__ANDROID__ )  )
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h> 
//#include <GLES2/gl2extimg.h>
#else // IOS
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
//#include <OpenGLES/ES2/glextimg.h>
#endif
#endif

#include "GXDef.h"
using namespace EpicForce;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const GXBlendMode				GXBlendMode::Add							(0);
const GXBlendMode				GXBlendMode::Subtract						(1);
const GXBlendMode				GXBlendMode::ReverseSubtract				(2);

static const unsigned int blendFuncModes[] =
{
	GL_FUNC_ADD					,
	GL_FUNC_SUBTRACT			,							
	GL_FUNC_REVERSE_SUBTRACT	,
};

unsigned int GXBlendMode::getValue() const
{
	return blendFuncModes[order];
}

GXBlendMode::operator unsigned int ()
{
	return order;
}

GXBlendMode::operator const unsigned int () const
{
	return order;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const GXBlendFactor				GXBlendFactor::Zero							(0);
const GXBlendFactor				GXBlendFactor::One							(1);
const GXBlendFactor				GXBlendFactor::SrcColor						(2);
const GXBlendFactor				GXBlendFactor::OneMinusSrcColor				(3);
const GXBlendFactor				GXBlendFactor::SrcAlpha						(4);
const GXBlendFactor				GXBlendFactor::OneMinusSrcAlpha				(5);
const GXBlendFactor				GXBlendFactor::DstColor						(6);
const GXBlendFactor				GXBlendFactor::OneMinusDstColor				(7);
const GXBlendFactor				GXBlendFactor::DstAlpha						(8);
const GXBlendFactor				GXBlendFactor::OneMinusDstAlpha				(9);
const GXBlendFactor				GXBlendFactor::SrcAlphaSaturate				(10);

static const unsigned int blendFuncFactors[] =
{
	GL_ZERO						,
	GL_ONE						,							
	GL_SRC_COLOR				,
	GL_ONE_MINUS_SRC_COLOR		,
	GL_SRC_ALPHA				,
	GL_ONE_MINUS_SRC_ALPHA		,
	GL_DST_COLOR				,
	GL_ONE_MINUS_DST_COLOR		,
	GL_DST_ALPHA				,
	GL_ONE_MINUS_DST_ALPHA		,
	GL_SRC_ALPHA_SATURATE		,
};

unsigned int GXBlendFactor::getValue() const
{
	return blendFuncFactors[order];
}

GXBlendFactor::operator unsigned int ()
{
	return order;
}

GXBlendFactor::operator const unsigned int () const
{
	return order;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const GXClearMask					GXClearMask::None								(0);
const GXClearMask					GXClearMask::Color								(1);
const GXClearMask					GXClearMask::Depth								(2);
const GXClearMask					GXClearMask::Stencil							(4);
const GXClearMask					GXClearMask::All								(7);

static const unsigned int clearMasks[] =
{
	0,
	GL_COLOR_BUFFER_BIT,
	                      GL_DEPTH_BUFFER_BIT						 ,
	GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT						 ,
	                                            GL_STENCIL_BUFFER_BIT,
	GL_COLOR_BUFFER_BIT	|						GL_STENCIL_BUFFER_BIT,
						  GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT,
	GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT
};

unsigned int GXClearMask::getValue() const
{
	return clearMasks[mask];
}

GXClearMask::operator unsigned int ()
{
	return mask;
}

GXClearMask::operator const unsigned int () const
{
	return mask;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const GXColorMask					GXColorMask::None								(0);
const GXColorMask					GXColorMask::R									(1);
const GXColorMask					GXColorMask::G									(2);
const GXColorMask					GXColorMask::B									(4);
const GXColorMask					GXColorMask::A									(8);
const GXColorMask					GXColorMask::Rgb								(7);
const GXColorMask					GXColorMask::Rgba								(15);

static const unsigned int colorMasks[] =
{
	0,
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	10,
	11,
	12,
	13,
	14,
	15
};

unsigned int GXColorMask::getValue() const
{
	return colorMasks[mask];
}

GXColorMask::operator unsigned int ()
{
	return mask;
}

GXColorMask::operator const unsigned int () const
{
	return mask;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const GXCullMode				GXCullMode::CW							(0);
const GXCullMode				GXCullMode::CCW						(1);

static const unsigned int cullFaceModes[] =
{
	GL_CW,
	GL_CCW,
};

unsigned int GXCullMode::getValue() const
{
	return cullFaceModes[order];
}

GXCullMode::operator unsigned int ()
{
	return order;
}

GXCullMode::operator const unsigned int () const
{
	return order;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const GXDepthTestMode				GXDepthTestMode::Always							(0);
const GXDepthTestMode				GXDepthTestMode::Never 							(1);
const GXDepthTestMode				GXDepthTestMode::Equal 							(2);
const GXDepthTestMode				GXDepthTestMode::NotEequal 						(3);
const GXDepthTestMode				GXDepthTestMode::Less 							(4);
const GXDepthTestMode				GXDepthTestMode::Greater 						(5);
const GXDepthTestMode				GXDepthTestMode::LEqual 						(6);
const GXDepthTestMode				GXDepthTestMode::GEqual							(7);

static const unsigned int depthFuncModes[] =
{
	GL_ALWAYS	,
	GL_NEVER	,
	GL_EQUAL	,
	GL_NOTEQUAL	,
	GL_LESS		,
	GL_GREATER	,
	GL_LEQUAL	,	
	GL_GEQUAL	
};

unsigned int GXDepthTestMode::getValue() const
{
	return depthFuncModes[order];
}

GXDepthTestMode::operator unsigned int ()
{
	return order;
}


GXDepthTestMode::operator const unsigned int () const
{
	return order;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const GXDrawMode					GXDrawMode::Points								(0);
const GXDrawMode					GXDrawMode::Lines								(1);
const GXDrawMode					GXDrawMode::LineStrip							(2);
const GXDrawMode					GXDrawMode::Triangles							(3);
const GXDrawMode					GXDrawMode::TriangleStrip						(4);
const GXDrawMode					GXDrawMode::TriangleFan							(5);

static const unsigned int drawModes[] =
{
	GL_POINTS,
	GL_LINES,
	GL_LINE_STRIP,
	GL_TRIANGLES,
	GL_TRIANGLE_STRIP,
	GL_TRIANGLE_FAN,
};

unsigned int GXDrawMode::getValue() const
{
	return drawModes[order];
}

GXDrawMode::operator unsigned int ()
{
	return order;
}

GXDrawMode::operator const unsigned int () const
{
	return order;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const GXEnableMode					GXEnableMode::None								(0 );
const GXEnableMode					GXEnableMode::CullFace							(1 );
const GXEnableMode					GXEnableMode::ScissorTest						(2 );
const GXEnableMode					GXEnableMode::Blend								(4 );
const GXEnableMode					GXEnableMode::DepthTest							(8 );
const GXEnableMode					GXEnableMode::PolygonOffsetFill					(16);
const GXEnableMode					GXEnableMode::StencilTest						(32);
const GXEnableMode					GXEnableMode::Dither							(64);
const GXEnableMode					GXEnableMode::All								(127);

unsigned int GXEnableMode::getValue() const
{
	return order;
}

GXEnableMode::operator unsigned int ()
{
	return order;
}

GXEnableMode::operator const unsigned int () const
{
	return order;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const GXMultiSampleMode				GXMultiSampleMode::None							(0);
const GXMultiSampleMode				GXMultiSampleMode::Msaa2x						(1);
const GXMultiSampleMode				GXMultiSampleMode::Msaa4x						(2);

static const unsigned int multiSampleModes[] =
{
	0,
	1,
	2,
};

unsigned int GXMultiSampleMode::getValue() const
{
	return multiSampleModes[order];
}

GXMultiSampleMode::operator unsigned int ()
{
	return order;
}

GXMultiSampleMode::operator const unsigned int () const
{
	return order;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const GXPixelBufferOption			GXPixelBufferOption::None						(0);
const GXPixelBufferOption			GXPixelBufferOption::Renderable					(1);

static const unsigned int pixelBufferOptions[] =
{
	0,
	1,
};

unsigned int GXPixelBufferOption::getValue() const
{
	return pixelBufferOptions[order];
}

GXPixelBufferOption::operator unsigned int ()
{
	return order;
}

GXPixelBufferOption::operator const unsigned int () const
{
	return order;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const GXPixelBufferType				GXPixelBufferType::None							(0);
const GXPixelBufferType				GXPixelBufferType::GXTexture2D					(1);
const GXPixelBufferType				GXPixelBufferType::GXTextureCube				(2);
const GXPixelBufferType				GXPixelBufferType::GXColorBuffer				(3);
const GXPixelBufferType				GXPixelBufferType::DepthBuffer					(4);

static const unsigned int pixelBufferTypes[] =
{
	0,
	GL_TEXTURE_2D,
	GL_TEXTURE_CUBE_MAP,
	GL_COLOR_ATTACHMENT0,	
	GL_DEPTH_ATTACHMENT,
};

unsigned int GXPixelBufferType::getValue() const
{
	return pixelBufferTypes[order];
}

GXPixelBufferType::operator unsigned int ()
{
	return order;
}

GXPixelBufferType::operator const unsigned int () const
{
	return order;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const GXPixelFormat					GXPixelFormat::None								(0);
const GXPixelFormat					GXPixelFormat::R8G8B8							(1);
const GXPixelFormat					GXPixelFormat::R5G6B5							(2);
const GXPixelFormat					GXPixelFormat::RGB_PVRTC2						(3);
const GXPixelFormat					GXPixelFormat::RGB_PVRTC4						(4);
const GXPixelFormat					GXPixelFormat::RGB_ETC							(5);
const GXPixelFormat					GXPixelFormat::R8G8B8A8							(6);
const GXPixelFormat					GXPixelFormat::R4G4B4A4							(7);
const GXPixelFormat					GXPixelFormat::R5G5B5A1							(8);
const GXPixelFormat					GXPixelFormat::R16G16B16A16						(9);
const GXPixelFormat					GXPixelFormat::R32G32B32A32						(10);
const GXPixelFormat					GXPixelFormat::RGBA_PVRTC2						(11);
const GXPixelFormat					GXPixelFormat::RGBA_PVRTC4						(12);
const GXPixelFormat					GXPixelFormat::RGBA_ETC							(13);
const GXPixelFormat					GXPixelFormat::I8								(14);
const GXPixelFormat					GXPixelFormat::A8								(15);
const GXPixelFormat					GXPixelFormat::AI8								(16);
const GXPixelFormat					GXPixelFormat::D16S8							(17);
const GXPixelFormat					GXPixelFormat::D24S8							(18);

static const unsigned int pixelFormats[] =
{
	0,
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	10,
	11,
	12,
	13,
	14,
	15,
	16,
	17,
	18
};

unsigned int GXPixelFormat::getValue() const
{
	return pixelFormats[order];
}

GXPixelFormat::operator unsigned int ()
{
	return order;
}

GXPixelFormat::operator const unsigned int () const
{
	return order;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const GXShaderAttributeType			GXShaderAttributeType::BOOL 					( 0);
const GXShaderAttributeType			GXShaderAttributeType::BVEC2 					( 1);
const GXShaderAttributeType			GXShaderAttributeType::BVEC3 					( 2);
const GXShaderAttributeType			GXShaderAttributeType::BVEC4 					( 3);
const GXShaderAttributeType			GXShaderAttributeType::INT 						( 4);
const GXShaderAttributeType			GXShaderAttributeType::IVEC2 					( 5);
const GXShaderAttributeType			GXShaderAttributeType::IVEC3 					( 6);
const GXShaderAttributeType			GXShaderAttributeType::IVEC4 					( 7);
const GXShaderAttributeType			GXShaderAttributeType::FLOAT 					( 8);
const GXShaderAttributeType			GXShaderAttributeType::VEC2 					( 9);
const GXShaderAttributeType			GXShaderAttributeType::VEC3 					(10);
const GXShaderAttributeType			GXShaderAttributeType::VEC4 					(11);
const GXShaderAttributeType			GXShaderAttributeType::MAT2 					(12);
const GXShaderAttributeType			GXShaderAttributeType::MAT3 					(13);
const GXShaderAttributeType			GXShaderAttributeType::MAT4 					(14);

static const unsigned int attributeTypeValues[] =
{
	1, GL_BOOL			,  4, 0,
	2, GL_BOOL_VEC2		,  8, 0,
	3, GL_BOOL_VEC3		, 12, 0,
	4, GL_BOOL_VEC4		, 16, 0,
	1, GL_INT		    ,  4, 0,
	2, GL_INT_VEC2		,  8, 0,
	3, GL_INT_VEC3		, 12, 0,
	4, GL_INT_VEC4		, 16, 0,
	1, GL_FLOAT			,  4, 0,
	2, GL_FLOAT_VEC2	,  8, 0,
	3, GL_FLOAT_VEC3	, 12, 0,
	4, GL_FLOAT_VEC4	, 16, 0,
	1, GL_FLOAT_MAT2	, 16, 0,
	1, GL_FLOAT_MAT3	, 36, 0,
	1, GL_FLOAT_MAT4	, 48, 0,
};

GXShaderAttributeType::operator unsigned int ()
{
	return order;
}

GXShaderAttributeType::operator const unsigned int () const
{
	return order;
}

const unsigned int GXShaderAttributeType::getNumElements() const
{
	return attributeTypeValues[(order<<2)+0];
}

const unsigned int GXShaderAttributeType::getElementType() const
{
	return attributeTypeValues[(order<<2)+1];
}

const unsigned int GXShaderAttributeType::getSize() const
{
	return attributeTypeValues[(order<<2)+2];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const GXShaderUniformType			GXShaderUniformType::BOOL 						( 0);
const GXShaderUniformType			GXShaderUniformType::BVEC2 						( 1);
const GXShaderUniformType			GXShaderUniformType::BVEC3 						( 2);
const GXShaderUniformType			GXShaderUniformType::BVEC4 						( 3);
const GXShaderUniformType			GXShaderUniformType::INT 						( 4);
const GXShaderUniformType			GXShaderUniformType::IVEC2 						( 5);
const GXShaderUniformType			GXShaderUniformType::IVEC3 						( 6);
const GXShaderUniformType			GXShaderUniformType::IVEC4 						( 7);
const GXShaderUniformType			GXShaderUniformType::FLOAT 						( 8);
const GXShaderUniformType			GXShaderUniformType::VEC2 						( 9);
const GXShaderUniformType			GXShaderUniformType::VEC3 						(10);
const GXShaderUniformType			GXShaderUniformType::VEC4 						(11);
const GXShaderUniformType			GXShaderUniformType::MAT2 						(12);
const GXShaderUniformType			GXShaderUniformType::MAT3 						(13);
const GXShaderUniformType			GXShaderUniformType::MAT4 						(14);
const GXShaderUniformType			GXShaderUniformType::SAMPLER2D 					(15);
const GXShaderUniformType			GXShaderUniformType::SAMPLERCUBE 				(16);

static const unsigned int uniformTypeValues[] =
{
	1, GL_BOOL				,  4, 0,
	2, GL_BOOL_VEC2			,  8, 0,
	3, GL_BOOL_VEC3			, 12, 0,
	4, GL_BOOL_VEC4			, 16, 0,
	1, GL_INT				,  4, 0,
	2, GL_INT_VEC2			,  8, 0,
	3, GL_INT_VEC3			, 12, 0,
	4, GL_INT_VEC4			, 16, 0,
	1, GL_FLOAT				,  4, 0,
	2, GL_FLOAT_VEC2		,  8, 0,
	3, GL_FLOAT_VEC3		, 12, 0,
	4, GL_FLOAT_VEC4		, 16, 0,
	1, GL_FLOAT_MAT2		, 16, 0,
	1, GL_FLOAT_MAT3		, 36, 0,
	1, GL_FLOAT_MAT4		, 64, 0,
	1, GL_SAMPLER_2D		,  4, 0,
	1, GL_SAMPLER_CUBE		,  4, 0,
};

GXShaderUniformType::operator unsigned int ()
{
	return order;
}

GXShaderUniformType::operator const unsigned int () const
{
	return order;
}

const unsigned int GXShaderUniformType::getNumElements() const
{
	return uniformTypeValues[(order<<2)+0];
}

const unsigned int GXShaderUniformType::getElementType() const
{
	return uniformTypeValues[(order<<2)+1];
}

const unsigned int GXShaderUniformType::getSize() const
{
	return uniformTypeValues[(order<<2)+2];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const GXStencilTestMode				GXStencilTestMode::Always						(0);
const GXStencilTestMode				GXStencilTestMode::Never						(1);
const GXStencilTestMode				GXStencilTestMode::Equal						(2);
const GXStencilTestMode				GXStencilTestMode::NotEequal					(3);
const GXStencilTestMode				GXStencilTestMode::Less							(4);
const GXStencilTestMode				GXStencilTestMode::Greater						(5);
const GXStencilTestMode				GXStencilTestMode::LEqual						(6);
const GXStencilTestMode				GXStencilTestMode::GEqual						(7);

static const unsigned int stencilFuncModes[] =
{
	GL_ALWAYS,
	GL_NEVER,
	GL_EQUAL,
	GL_NOTEQUAL,
	GL_LESS,
	GL_GREATER,
	GL_LEQUAL,
	GL_GEQUAL	
};

unsigned int GXStencilTestMode::getValue() const
{
	return stencilFuncModes[order];
}

GXStencilTestMode::operator unsigned int ()
{
	return order;
}

GXStencilTestMode::operator const unsigned int () const
{
	return order;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const GXStencilOp				GXStencilOp::Keep 							(0);
const GXStencilOp				GXStencilOp::Zero 							(1);
const GXStencilOp				GXStencilOp::Replace 						(2);
const GXStencilOp				GXStencilOp::Invert 						(3);
const GXStencilOp				GXStencilOp::Incr 							(4);
const GXStencilOp				GXStencilOp::Decr 							(5);
const GXStencilOp				GXStencilOp::IncrWrap 						(6);
const GXStencilOp				GXStencilOp::DecrWrap						(7);

static const unsigned int stencilOpModes[] =
{
	GL_KEEP		,
	GL_ZERO		,
	GL_REPLACE	,	
	GL_INVERT	,	
	GL_INCR		,
	GL_DECR		,
	GL_INCR_WRAP,	
	GL_DECR_WRAP
};

unsigned int GXStencilOp::getValue() const
{
	return stencilOpModes[order];
}

GXStencilOp::operator unsigned int ()
{
	return order;
}

GXStencilOp::operator const unsigned int () const
{
	return order;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const GXTextureCubeFace				GXTextureCubeFace::PositiveX					(0);
const GXTextureCubeFace				GXTextureCubeFace::NegativeX					(1);
const GXTextureCubeFace				GXTextureCubeFace::PositiveY					(2);
const GXTextureCubeFace				GXTextureCubeFace::NegativeY					(3);
const GXTextureCubeFace				GXTextureCubeFace::PositiveZ					(4);
const GXTextureCubeFace				GXTextureCubeFace::NegativeZ					(5);

static const unsigned int textureCubeFaces[] =
{
	GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Y,	
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,	
	GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
};

unsigned int GXTextureCubeFace::getValue() const
{
	return textureCubeFaces[order];
}

GXTextureCubeFace::operator unsigned int ()
{
	return order;
}

GXTextureCubeFace::operator const unsigned int () const
{
	return order;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const GXTextureMagFilterMode		GXTextureMagFilterMode::Nearest					(0);
const GXTextureMagFilterMode		GXTextureMagFilterMode::Linear					(1);

static const unsigned int textureMagFilterModes[] =
{
	GL_NEAREST,
	GL_LINEAR
};

unsigned int GXTextureMagFilterMode::getValue() const
{
	return textureMagFilterModes[order];
}

GXTextureMagFilterMode::operator unsigned int ()
{
	return order;
}

GXTextureMagFilterMode::operator const unsigned int () const
{
	return order;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const GXTextureMinFilterMode		GXTextureMinFilterMode::Nearest					(0);
const GXTextureMinFilterMode		GXTextureMinFilterMode::Linear					(1);
const GXTextureMinFilterMode		GXTextureMinFilterMode::NearestMipmapNearest	(2);
const GXTextureMinFilterMode		GXTextureMinFilterMode::LinearMipmapNearest		(3);
const GXTextureMinFilterMode		GXTextureMinFilterMode::NearestMipmapLinear		(4);
const GXTextureMinFilterMode		GXTextureMinFilterMode::LinearMipmapLinear		(5);

static const unsigned int textureMinFilterModes[] =
{
	GL_NEAREST,
	GL_LINEAR,
	GL_NEAREST_MIPMAP_NEAREST,
	GL_LINEAR_MIPMAP_NEAREST,
	GL_NEAREST_MIPMAP_LINEAR,
	GL_LINEAR_MIPMAP_LINEAR,
};

unsigned int GXTextureMinFilterMode::getValue() const
{
	return textureMinFilterModes[order];
}

GXTextureMinFilterMode::operator unsigned int ()
{
	return order;
}

GXTextureMinFilterMode::operator const unsigned int () const
{
	return order;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const GXTextureWrapMode				GXTextureWrapMode::Repeat						(0);
const GXTextureWrapMode				GXTextureWrapMode::ClampToEdge					(1);
const GXTextureWrapMode				GXTextureWrapMode::MirroredRepeat				(2);

static const unsigned int textureWrapModes[] =
{
	GL_REPEAT,
	GL_CLAMP_TO_EDGE,
	GL_MIRRORED_REPEAT
};

unsigned int GXTextureWrapMode::getValue() const
{
	return textureWrapModes[order];
}

GXTextureWrapMode::operator unsigned int ()
{
	return order;
}

GXTextureWrapMode::operator const unsigned int () const
{
	return order;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const GXVertexFormat				GXVertexFormat::BYTE							(0);
const GXVertexFormat				GXVertexFormat::BYTE2							(1);
const GXVertexFormat				GXVertexFormat::BYTE3							(2);
const GXVertexFormat				GXVertexFormat::BYTE4							(3);
const GXVertexFormat				GXVertexFormat::UBYTE							(4);
const GXVertexFormat				GXVertexFormat::UBYTE2							(5);
const GXVertexFormat				GXVertexFormat::UBYTE3							(6);
const GXVertexFormat				GXVertexFormat::UBYTE4							(7);
const GXVertexFormat				GXVertexFormat::SHORT							(8);
const GXVertexFormat				GXVertexFormat::SHORT2							(9);
const GXVertexFormat				GXVertexFormat::SHORT3							(10);
const GXVertexFormat				GXVertexFormat::SHORT4							(11);
const GXVertexFormat				GXVertexFormat::USHORT							(12);
const GXVertexFormat				GXVertexFormat::USHORT2							(13);
const GXVertexFormat				GXVertexFormat::USHORT3							(14);
const GXVertexFormat				GXVertexFormat::USHORT4							(15);
const GXVertexFormat				GXVertexFormat::INT								(16);
const GXVertexFormat				GXVertexFormat::INT2							(17);
const GXVertexFormat				GXVertexFormat::INT3							(18);
const GXVertexFormat				GXVertexFormat::INT4							(19);
const GXVertexFormat				GXVertexFormat::UINT							(20);
const GXVertexFormat				GXVertexFormat::UINT2							(21);
const GXVertexFormat				GXVertexFormat::UINT3							(22);
const GXVertexFormat				GXVertexFormat::UINT4							(23);
const GXVertexFormat				GXVertexFormat::BYTEN							(24);
const GXVertexFormat				GXVertexFormat::BYTE2N							(25);
const GXVertexFormat				GXVertexFormat::BYTE3N							(26);
const GXVertexFormat				GXVertexFormat::BYTE4N							(27);
const GXVertexFormat				GXVertexFormat::UBYTEN							(28);
const GXVertexFormat				GXVertexFormat::UBYTE2N							(29);
const GXVertexFormat				GXVertexFormat::UBYTE3N							(30);
const GXVertexFormat				GXVertexFormat::UBYTE4N							(31);
const GXVertexFormat				GXVertexFormat::SHORTN							(32);
const GXVertexFormat				GXVertexFormat::SHORT2N							(33);
const GXVertexFormat				GXVertexFormat::SHORT3N							(34);
const GXVertexFormat				GXVertexFormat::SHORT4N							(35);
const GXVertexFormat				GXVertexFormat::USHORTN							(36);
const GXVertexFormat				GXVertexFormat::USHORT2N						(37);
const GXVertexFormat				GXVertexFormat::USHORT3N						(38);
const GXVertexFormat				GXVertexFormat::USHORT4N						(39);
const GXVertexFormat				GXVertexFormat::INTN							(40);
const GXVertexFormat				GXVertexFormat::INT2N							(41);
const GXVertexFormat				GXVertexFormat::INT3N							(42);
const GXVertexFormat				GXVertexFormat::INT4N							(43);
const GXVertexFormat				GXVertexFormat::UINTN							(44);
const GXVertexFormat				GXVertexFormat::UINT2N							(45);
const GXVertexFormat				GXVertexFormat::UINT3N							(46);
const GXVertexFormat				GXVertexFormat::UINT4N							(47);
const GXVertexFormat				GXVertexFormat::FLOAT							(48);
const GXVertexFormat				GXVertexFormat::FLOAT2							(49);
const GXVertexFormat				GXVertexFormat::FLOAT3							(50);
const GXVertexFormat				GXVertexFormat::FLOAT4							(51);
const GXVertexFormat				GXVertexFormat::HALF							(52);
const GXVertexFormat				GXVertexFormat::HALF2							(53);
const GXVertexFormat				GXVertexFormat::HALF3							(54);
const GXVertexFormat				GXVertexFormat::HALF4							(55);

static const unsigned int vertexFormats[] =
{
	1, GL_BYTE				, false	,  1,
	2, GL_BYTE				, false	,  2,
	3, GL_BYTE				, false	,  3,
	4, GL_BYTE				, false	,  4,
	1, GL_UNSIGNED_BYTE		, false	,  1,
	2, GL_UNSIGNED_BYTE		, false	,  2,
	3, GL_UNSIGNED_BYTE		, false	,  3,
	4, GL_UNSIGNED_BYTE		, false	,  4,
	1, GL_SHORT				, false	,  2,
	2, GL_SHORT				, false	,  4,
	3, GL_SHORT				, false	,  6,
	4, GL_SHORT				, false	,  8,
	1, GL_UNSIGNED_SHORT	, false	,  2,
	2, GL_UNSIGNED_SHORT	, false	,  4,
	3, GL_UNSIGNED_SHORT	, false	,  6,
	4, GL_UNSIGNED_SHORT	, false	,  8,
	1, GL_INT				, false	,  4,
	2, GL_INT				, false	,  8,
	3, GL_INT				, false	, 12,
	4, GL_INT				, false	, 16,
	1, GL_UNSIGNED_INT		, false	,  4,
	2, GL_UNSIGNED_INT		, false	,  8,
	3, GL_UNSIGNED_INT		, false	, 12,
	4, GL_UNSIGNED_INT		, false	, 16,
	1, GL_BYTE				, true	,  1,
	2, GL_BYTE				, true	,  2,
	3, GL_BYTE				, true	,  3,
	4, GL_BYTE				, true	,  4,
	1, GL_UNSIGNED_BYTE		, true	,  1,
	2, GL_UNSIGNED_BYTE		, true	,  2,
	3, GL_UNSIGNED_BYTE		, true	,  3,
	4, GL_UNSIGNED_BYTE		, true	,  4,
	1, GL_SHORT				, true	,  2,
	2, GL_SHORT				, true	,  4,
	3, GL_SHORT				, true	,  6,
	4, GL_SHORT				, true	,  8,
	1, GL_UNSIGNED_SHORT	, true	,  2,
	2, GL_UNSIGNED_SHORT	, true	,  4,
	3, GL_UNSIGNED_SHORT	, true	,  6,
	4, GL_UNSIGNED_SHORT	, true	,  8,
	1, GL_INT				, true	,  4,
	2, GL_INT				, true	,  8,
	3, GL_INT				, true	, 12,
	4, GL_INT				, true	, 16,
	1, GL_UNSIGNED_INT		, true	,  4,
	2, GL_UNSIGNED_INT		, true	,  8,
	3, GL_UNSIGNED_INT		, true	, 12,
	4, GL_UNSIGNED_INT		, true	, 16,
	1, GL_FLOAT				, true	,  4,
	2, GL_FLOAT				, true	,  8,
	3, GL_FLOAT				, true	, 12,
	4, GL_FLOAT				, true	, 16,
	1, GL_HALF_FLOAT_OES	, true	,  4,
	2, GL_HALF_FLOAT_OES	, true	,  8,
	3, GL_HALF_FLOAT_OES	, true	, 12,
	4, GL_HALF_FLOAT_OES	, true	, 16,
};

const unsigned int GXVertexFormat::getNumElements() const
{
	return vertexFormats[(order<<2)+0];
}

const unsigned int GXVertexFormat::getElementType() const
{
	return vertexFormats[(order<<2)+1];
}

const bool GXVertexFormat::getNormalize() const
{
	return vertexFormats[(order<<2)+2];
}

const unsigned int GXVertexFormat::getSize() const
{
	return vertexFormats[(order<<2)+3];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const GXVertexStreamSource			GXVertexStreamSource::POSITION0					(0);
const GXVertexStreamSource			GXVertexStreamSource::POSITION1					(1);
const GXVertexStreamSource			GXVertexStreamSource::POSITION2					(2);
const GXVertexStreamSource			GXVertexStreamSource::POSITION3					(3);
const GXVertexStreamSource			GXVertexStreamSource::NORMAL					(4);
const GXVertexStreamSource			GXVertexStreamSource::COLOR0					(5);
const GXVertexStreamSource			GXVertexStreamSource::COLOR1					(6);
const GXVertexStreamSource			GXVertexStreamSource::TEXCOORD0					(7);
const GXVertexStreamSource			GXVertexStreamSource::TEXCOORD1					(8);
const GXVertexStreamSource			GXVertexStreamSource::TEXCOORD2					(9);
const GXVertexStreamSource			GXVertexStreamSource::TEXCOORD3					(10);
const GXVertexStreamSource			GXVertexStreamSource::TEXCOORD4					(11);
const GXVertexStreamSource			GXVertexStreamSource::TEXCOORD5					(12);
const GXVertexStreamSource			GXVertexStreamSource::TEXCOORD6					(13);
const GXVertexStreamSource			GXVertexStreamSource::TEXCOORD7					(14);
const GXVertexStreamSource			GXVertexStreamSource::TANGENT					(15);
const GXVertexStreamSource			GXVertexStreamSource::BINORMAL					(16);
const GXVertexStreamSource			GXVertexStreamSource::BLEND1INDEX				(17);
const GXVertexStreamSource			GXVertexStreamSource::BLEND2INDEX				(18);
const GXVertexStreamSource			GXVertexStreamSource::BLEND2WEIGHT				(19);
const GXVertexStreamSource			GXVertexStreamSource::BLEND4INDEX				(20);
const GXVertexStreamSource			GXVertexStreamSource::BLEND4WEIGHT				(21);

static const unsigned int vertexStreamSources[] =
{
	0,
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	10,
	11,
	12,
	13,
	14,
	15,
	16,
	17,
	18,
	19,
	20,
	21,
};

unsigned int GXVertexStreamSource::getValue() const
{
	return vertexStreamSources[order];
}

GXVertexStreamSource::operator unsigned int ()
{
	return order;
}

GXVertexStreamSource::operator const unsigned int () const
{
	return order;
}

#ifdef EXPORTER
#else
void EpicForce::checkGLError(const char *name)
{
	int error = glGetError();
	
	if(error)
		debug("%s glGetError 0x%04x", name, error);
}
#endif