/*
#if defined(WIN32)
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
//#include <GLES2/gl2extimg.h>
#elif ( defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) )
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
//#include <OpenGLES/ES2/glextimg.h>
#elif ( defined(__ANDROID__ )  )
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
//#include <GLES2/gl2extimg.h>
#endif
*/
#include "gl2.h"
#include "gl2ext.h"
#include "GXDef.h"
using namespace EpicForce;

const GXBlendFuncMode				GXBlendFuncMode::Add							(GL_FUNC_ADD				);
const GXBlendFuncMode				GXBlendFuncMode::Subtract						(GL_FUNC_SUBTRACT			);
const GXBlendFuncMode				GXBlendFuncMode::ReverseSubtract				(GL_FUNC_REVERSE_SUBTRACT	);

const GXBlendFuncFactor				GXBlendFuncFactor::Zero							(GL_ZERO					);
const GXBlendFuncFactor				GXBlendFuncFactor::One							(GL_ONE						);
const GXBlendFuncFactor				GXBlendFuncFactor::SrcColor						(GL_SRC_COLOR				);
const GXBlendFuncFactor				GXBlendFuncFactor::OneMinusSrcColor				(GL_ONE_MINUS_SRC_COLOR		);
const GXBlendFuncFactor				GXBlendFuncFactor::SrcAlpha						(GL_SRC_ALPHA				);
const GXBlendFuncFactor				GXBlendFuncFactor::OneMinusSrcAlpha				(GL_ONE_MINUS_SRC_ALPHA		);
const GXBlendFuncFactor				GXBlendFuncFactor::DstColor						(GL_DST_COLOR				);
const GXBlendFuncFactor				GXBlendFuncFactor::OneMinusDstColor				(GL_ONE_MINUS_DST_COLOR		);
const GXBlendFuncFactor				GXBlendFuncFactor::DstAlpha						(GL_DST_ALPHA				);
const GXBlendFuncFactor				GXBlendFuncFactor::OneMinusDstAlpha				(GL_ONE_MINUS_DST_ALPHA		);
const GXBlendFuncFactor				GXBlendFuncFactor::SrcAlphaSaturate				(GL_SRC_ALPHA_SATURATE		);

const GXClearMask					GXClearMask::None								(0);
const GXClearMask					GXClearMask::Color								(GL_COLOR_BUFFER_BIT);
const GXClearMask					GXClearMask::Depth								(GL_DEPTH_BUFFER_BIT);
const GXClearMask					GXClearMask::Stencil							(GL_STENCIL_BUFFER_BIT);
const GXClearMask					GXClearMask::All								(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

const GXColorMask					GXColorMask::None								(0);
const GXColorMask					GXColorMask::R									(1);
const GXColorMask					GXColorMask::G									(2);
const GXColorMask					GXColorMask::B									(4);
const GXColorMask					GXColorMask::A									(8);
const GXColorMask					GXColorMask::Rgb								(7);
const GXColorMask					GXColorMask::Rgba								(15);

const GXCullFaceMode				GXCullFaceMode::None							(0					);
const GXCullFaceMode				GXCullFaceMode::Front							(GL_FRONT			);
const GXCullFaceMode				GXCullFaceMode::Back							(GL_BACK			);
const GXCullFaceMode				GXCullFaceMode::FrontAndBack					(GL_FRONT_AND_BACK	);

const GXCullFaceDirection			GXCullFaceDirection::CCW						(GL_CCW);
const GXCullFaceDirection			GXCullFaceDirection::CW							(GL_CW);

const GXDepthFuncMode				GXDepthFuncMode::Always							(GL_ALWAYS	);
const GXDepthFuncMode				GXDepthFuncMode::Never 							(GL_NEVER	);
const GXDepthFuncMode				GXDepthFuncMode::Equal 							(GL_EQUAL	);
const GXDepthFuncMode				GXDepthFuncMode::NotEequal 						(GL_NOTEQUAL);
const GXDepthFuncMode				GXDepthFuncMode::Less 							(GL_LESS	);
const GXDepthFuncMode				GXDepthFuncMode::Greater 						(GL_GREATER	);
const GXDepthFuncMode				GXDepthFuncMode::LEqual 						(GL_LEQUAL	);
const GXDepthFuncMode				GXDepthFuncMode::GEqual							(GL_GEQUAL	);

const GXDrawMode					GXDrawMode::Points								(GL_POINTS        );
const GXDrawMode					GXDrawMode::Lines								(GL_LINES         );
const GXDrawMode					GXDrawMode::LineStrip							(GL_LINE_STRIP    );
const GXDrawMode					GXDrawMode::Triangles							(GL_TRIANGLES     );
const GXDrawMode					GXDrawMode::TriangleStrip						(GL_TRIANGLE_STRIP);
const GXDrawMode					GXDrawMode::TriangleFan							(GL_TRIANGLE_FAN  );

const GXEnableMode					GXEnableMode::None								(0);
const GXEnableMode					GXEnableMode::ScissorTest						(1);
const GXEnableMode					GXEnableMode::CullFace							(2);
const GXEnableMode					GXEnableMode::Blend								(4);
const GXEnableMode					GXEnableMode::DepthTest							(8);
const GXEnableMode					GXEnableMode::PolygonOffsetFill					(16);
const GXEnableMode					GXEnableMode::StencilTest						(32);
const GXEnableMode					GXEnableMode::Dither							(64);
const GXEnableMode					GXEnableMode::All								(127);

const GXMultiSampleMode				GXMultiSampleMode::None							(0);
const GXMultiSampleMode				GXMultiSampleMode::Msaa2x						(1);
const GXMultiSampleMode				GXMultiSampleMode::Msaa4x						(2);

const GXPixelBufferOption			GXPixelBufferOption::None						(0);
const GXPixelBufferOption			GXPixelBufferOption::Renderable					(1);

const GXPixelBufferType				GXPixelBufferType::None							(0);
const GXPixelBufferType				GXPixelBufferType::GXTexture2D					(GL_TEXTURE_2D			);
const GXPixelBufferType				GXPixelBufferType::GXTextureCube				(GL_TEXTURE_CUBE_MAP	);
const GXPixelBufferType				GXPixelBufferType::GXColorBuffer				(GL_COLOR_ATTACHMENT0	);
const GXPixelBufferType				GXPixelBufferType::DepthBuffer					(GL_DEPTH_ATTACHMENT	);

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

const GXShaderAttributeType			GXShaderAttributeType::None						(0, 0				 ,  0);
const GXShaderAttributeType			GXShaderAttributeType::Float					(1, GL_FLOAT		 ,  4);
const GXShaderAttributeType			GXShaderAttributeType::Float2					(2, GL_FLOAT_VEC2	 ,  8);
const GXShaderAttributeType			GXShaderAttributeType::Float3					(3, GL_FLOAT_VEC3	 , 12);
const GXShaderAttributeType			GXShaderAttributeType::Float4					(4, GL_FLOAT_VEC4	 , 16);
const GXShaderAttributeType			GXShaderAttributeType::Int						(1, GL_INT		     ,  4);
const GXShaderAttributeType			GXShaderAttributeType::Int2						(2, GL_INT_VEC2		 ,  8);
const GXShaderAttributeType			GXShaderAttributeType::Int3						(3, GL_INT_VEC3		 , 12);
const GXShaderAttributeType			GXShaderAttributeType::Int4						(4, GL_INT_VEC4		 , 16);
const GXShaderAttributeType			GXShaderAttributeType::Bool						(1, GL_BOOL			 ,  4);
const GXShaderAttributeType			GXShaderAttributeType::Bool2					(2, GL_BOOL_VEC2	 ,  8);
const GXShaderAttributeType			GXShaderAttributeType::Bool3					(3, GL_BOOL_VEC3	 , 12);
const GXShaderAttributeType			GXShaderAttributeType::Bool4					(4, GL_BOOL_VEC4	 , 16);
const GXShaderAttributeType			GXShaderAttributeType::Float2x2					(1, GL_FLOAT_MAT2	 , 16);
const GXShaderAttributeType			GXShaderAttributeType::Float3x3					(1, GL_FLOAT_MAT3	 , 36);
const GXShaderAttributeType			GXShaderAttributeType::Float4x4					(1, GL_FLOAT_MAT4	 , 48);

const GXShaderUniformType			GXShaderUniformType::None						(0, 0				 ,  0);
const GXShaderUniformType			GXShaderUniformType::Float						(1, GL_FLOAT		 ,  4);
const GXShaderUniformType			GXShaderUniformType::Float2						(2, GL_FLOAT_VEC2	 ,  8);
const GXShaderUniformType			GXShaderUniformType::Float3						(3, GL_FLOAT_VEC3	 , 12);
const GXShaderUniformType			GXShaderUniformType::Float4						(4, GL_FLOAT_VEC4	 , 16);
const GXShaderUniformType			GXShaderUniformType::Int						(1, GL_INT			 ,  4);
const GXShaderUniformType			GXShaderUniformType::Int2						(2, GL_INT_VEC2		 ,  8);
const GXShaderUniformType			GXShaderUniformType::Int3						(3, GL_INT_VEC3		 , 12);
const GXShaderUniformType			GXShaderUniformType::Int4						(4, GL_INT_VEC4		 , 16);
const GXShaderUniformType			GXShaderUniformType::Bool						(1, GL_BOOL			 ,  4);
const GXShaderUniformType			GXShaderUniformType::Bool2						(2, GL_BOOL_VEC2	 ,  8);
const GXShaderUniformType			GXShaderUniformType::Bool3						(3, GL_BOOL_VEC3	 , 12);
const GXShaderUniformType			GXShaderUniformType::Bool4						(4, GL_BOOL_VEC4	 , 16);
const GXShaderUniformType			GXShaderUniformType::Float2x2					(1, GL_FLOAT_MAT2	 , 16);
const GXShaderUniformType			GXShaderUniformType::Float3x3					(1, GL_FLOAT_MAT3	 , 36);
const GXShaderUniformType			GXShaderUniformType::Float4x4					(1, GL_FLOAT_MAT4	 , 64);
const GXShaderUniformType			GXShaderUniformType::Sampler2D					(1, GL_SAMPLER_2D	 ,  4);
const GXShaderUniformType			GXShaderUniformType::SamplerCube				(1, GL_SAMPLER_CUBE  ,  4);

const GXStencilFuncMode				GXStencilFuncMode::Always						(GL_ALWAYS				);
const GXStencilFuncMode				GXStencilFuncMode::Never						(GL_NEVER				);
const GXStencilFuncMode				GXStencilFuncMode::Equal						(GL_EQUAL				);
const GXStencilFuncMode				GXStencilFuncMode::NotEequal					(GL_NOTEQUAL			);
const GXStencilFuncMode				GXStencilFuncMode::Less							(GL_LESS				);
const GXStencilFuncMode				GXStencilFuncMode::Greater						(GL_GREATER				);
const GXStencilFuncMode				GXStencilFuncMode::LEqual						(GL_LEQUAL				);
const GXStencilFuncMode				GXStencilFuncMode::GEqual						(GL_GEQUAL				);

const GXStencilOpMode				GXStencilOpMode::Keep 							(GL_KEEP				);
const GXStencilOpMode				GXStencilOpMode::Zero 							(GL_ZERO				);
const GXStencilOpMode				GXStencilOpMode::Replace 						(GL_REPLACE				);
const GXStencilOpMode				GXStencilOpMode::Invert 						(GL_INVERT				);
const GXStencilOpMode				GXStencilOpMode::Incr 							(GL_INCR				);
const GXStencilOpMode				GXStencilOpMode::Decr 							(GL_DECR				);
const GXStencilOpMode				GXStencilOpMode::IncrWrap 						(GL_INCR_WRAP			);
const GXStencilOpMode				GXStencilOpMode::DecrWrap						(GL_DECR_WRAP			);

const GXTextureCubeFace				GXTextureCubeFace::PositiveX					(GL_TEXTURE_CUBE_MAP_POSITIVE_X);
const GXTextureCubeFace				GXTextureCubeFace::NegativeX					(GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
const GXTextureCubeFace				GXTextureCubeFace::PositiveY					(GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
const GXTextureCubeFace				GXTextureCubeFace::NegativeY					(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
const GXTextureCubeFace				GXTextureCubeFace::PositiveZ					(GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
const GXTextureCubeFace				GXTextureCubeFace::NegativeZ					(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);

const GXTextureMagFilterMode		GXTextureMagFilterMode::Nearest					(GL_NEAREST					);
const GXTextureMagFilterMode		GXTextureMagFilterMode::Linear					(GL_LINEAR					);

const GXTextureMinFilterMode		GXTextureMinFilterMode::Nearest					(GL_NEAREST					);
const GXTextureMinFilterMode		GXTextureMinFilterMode::Linear					(GL_LINEAR					);
const GXTextureMinFilterMode		GXTextureMinFilterMode::Nearest_Mipmap_Nearest	(GL_NEAREST_MIPMAP_NEAREST	);
const GXTextureMinFilterMode		GXTextureMinFilterMode::Linear_Mipmap_Nearest	(GL_LINEAR_MIPMAP_NEAREST	);
const GXTextureMinFilterMode		GXTextureMinFilterMode::Nearest_Mipmap_Linear	(GL_NEAREST_MIPMAP_LINEAR	);
const GXTextureMinFilterMode		GXTextureMinFilterMode::Linear_Mipmap_Linear	(GL_LINEAR_MIPMAP_LINEAR	);

const GXTextureWrapMode				GXTextureWrapMode::Repeat						(GL_REPEAT					);
const GXTextureWrapMode				GXTextureWrapMode::ClampToEdge					(GL_CLAMP_TO_EDGE			);
const GXTextureWrapMode				GXTextureWrapMode::MirroredRepeat				(GL_MIRRORED_REPEAT			);

const GXVertexFormat				GXVertexFormat::None							(0, 0					, false	,  0);
const GXVertexFormat				GXVertexFormat::Byte							(1, GL_BYTE				, false	,  1);
const GXVertexFormat				GXVertexFormat::Byte2							(2, GL_BYTE				, false	,  2);
const GXVertexFormat				GXVertexFormat::Byte3							(3, GL_BYTE				, false	,  3);
const GXVertexFormat				GXVertexFormat::Byte4							(4, GL_BYTE				, false	,  4);
const GXVertexFormat				GXVertexFormat::UByte							(1, GL_UNSIGNED_BYTE	, false	,  1);
const GXVertexFormat				GXVertexFormat::UByte2							(2, GL_UNSIGNED_BYTE	, false	,  2);
const GXVertexFormat				GXVertexFormat::UByte3							(3, GL_UNSIGNED_BYTE	, false	,  3);
const GXVertexFormat				GXVertexFormat::UByte4							(4, GL_UNSIGNED_BYTE	, false	,  4);
const GXVertexFormat				GXVertexFormat::Short							(1, GL_SHORT			, false	,  2);
const GXVertexFormat				GXVertexFormat::Short2							(2, GL_SHORT			, false	,  4);
const GXVertexFormat				GXVertexFormat::Short3							(3, GL_SHORT			, false	,  6);
const GXVertexFormat				GXVertexFormat::Short4							(4, GL_SHORT			, false	,  8);
const GXVertexFormat				GXVertexFormat::UShort							(1, GL_UNSIGNED_SHORT	, false	,  2);
const GXVertexFormat				GXVertexFormat::UShort2							(2, GL_UNSIGNED_SHORT	, false	,  4);
const GXVertexFormat				GXVertexFormat::UShort3							(3, GL_UNSIGNED_SHORT	, false	,  6);
const GXVertexFormat				GXVertexFormat::UShort4							(4, GL_UNSIGNED_SHORT	, false	,  8);
const GXVertexFormat				GXVertexFormat::Int								(1, GL_INT				, false	,  4);
const GXVertexFormat				GXVertexFormat::Int2							(2, GL_INT				, false	,  8);
const GXVertexFormat				GXVertexFormat::Int3							(3, GL_INT				, false	, 12);
const GXVertexFormat				GXVertexFormat::Int4							(4, GL_INT				, false	, 16);
const GXVertexFormat				GXVertexFormat::UInt							(1, GL_UNSIGNED_INT		, false	,  4);
const GXVertexFormat				GXVertexFormat::UInt2							(2, GL_UNSIGNED_INT		, false	,  8);
const GXVertexFormat				GXVertexFormat::UInt3							(3, GL_UNSIGNED_INT		, false	, 12);
const GXVertexFormat				GXVertexFormat::UInt4							(4, GL_UNSIGNED_INT		, false	, 16);
const GXVertexFormat				GXVertexFormat::ByteN							(1, GL_BYTE				,true	,  1);
const GXVertexFormat				GXVertexFormat::Byte2N							(2, GL_BYTE				,true	,  2);
const GXVertexFormat				GXVertexFormat::Byte3N							(3, GL_BYTE				,true	,  3);
const GXVertexFormat				GXVertexFormat::Byte4N							(4, GL_BYTE				,true	,  4);
const GXVertexFormat				GXVertexFormat::UByteN							(1, GL_UNSIGNED_BYTE	,true	,  1);
const GXVertexFormat				GXVertexFormat::UByte2N							(2, GL_UNSIGNED_BYTE	,true	,  2);
const GXVertexFormat				GXVertexFormat::UByte3N							(3, GL_UNSIGNED_BYTE	,true	,  3);
const GXVertexFormat				GXVertexFormat::UByte4N							(4, GL_UNSIGNED_BYTE	,true	,  4);
const GXVertexFormat				GXVertexFormat::ShortN							(1, GL_SHORT			,true	,  2);
const GXVertexFormat				GXVertexFormat::Short2N							(2, GL_SHORT			,true	,  4);
const GXVertexFormat				GXVertexFormat::Short3N							(3, GL_SHORT			,true	,  6);
const GXVertexFormat				GXVertexFormat::Short4N							(4, GL_SHORT			,true	,  8);
const GXVertexFormat				GXVertexFormat::UShortN							(1, GL_UNSIGNED_SHORT	,true	,  2);
const GXVertexFormat				GXVertexFormat::UShort2N						(2, GL_UNSIGNED_SHORT	,true	,  4);
const GXVertexFormat				GXVertexFormat::UShort3N						(3, GL_UNSIGNED_SHORT	,true	,  6);
const GXVertexFormat				GXVertexFormat::UShort4N						(4, GL_UNSIGNED_SHORT	,true	,  8);
const GXVertexFormat				GXVertexFormat::IntN							(1, GL_INT				,true	,  4);
const GXVertexFormat				GXVertexFormat::Int2N							(2, GL_INT				,true	,  8);
const GXVertexFormat				GXVertexFormat::Int3N							(3, GL_INT				,true	, 12);
const GXVertexFormat				GXVertexFormat::Int4N							(4, GL_INT				,true	, 16);
const GXVertexFormat				GXVertexFormat::UIntN							(1, GL_UNSIGNED_INT		,true	,  4);
const GXVertexFormat				GXVertexFormat::UInt2N							(2, GL_UNSIGNED_INT		,true	,  8);
const GXVertexFormat				GXVertexFormat::UInt3N							(3, GL_UNSIGNED_INT		,true	, 12);
const GXVertexFormat				GXVertexFormat::UInt4N							(4, GL_UNSIGNED_INT		,true	, 16);
const GXVertexFormat				GXVertexFormat::Float							(1, GL_FLOAT			,true	,  4);
const GXVertexFormat				GXVertexFormat::Float2							(2, GL_FLOAT			,true	,  8);
const GXVertexFormat				GXVertexFormat::Float3							(3, GL_FLOAT			,true	, 12);
const GXVertexFormat				GXVertexFormat::Float4							(4, GL_FLOAT			,true	, 16);
const GXVertexFormat				GXVertexFormat::Half							(1, GL_HALF_FLOAT_OES	,true	,  4);
const GXVertexFormat				GXVertexFormat::Half2							(2, GL_HALF_FLOAT_OES	,true	,  8);
const GXVertexFormat				GXVertexFormat::Half3							(3, GL_HALF_FLOAT_OES	,true	, 12);
const GXVertexFormat				GXVertexFormat::Half4							(4, GL_HALF_FLOAT_OES	,true	, 16);

const GXVertexStreamSource			GXVertexStreamSource::Position					(0);
const GXVertexStreamSource			GXVertexStreamSource::Normal					(1);
const GXVertexStreamSource			GXVertexStreamSource::Color						(2);
const GXVertexStreamSource			GXVertexStreamSource::TexCoord0					(3);
const GXVertexStreamSource			GXVertexStreamSource::TexCoord1					(4);
const GXVertexStreamSource			GXVertexStreamSource::TexCoord2					(5);
const GXVertexStreamSource			GXVertexStreamSource::TexCoord3					(6);
const GXVertexStreamSource			GXVertexStreamSource::TexCoord4					(7);
const GXVertexStreamSource			GXVertexStreamSource::TexCoord5					(8);
const GXVertexStreamSource			GXVertexStreamSource::TexCoord6					(9);
const GXVertexStreamSource			GXVertexStreamSource::TexCoord7					(10);
const GXVertexStreamSource			GXVertexStreamSource::Tangent					(11);
const GXVertexStreamSource			GXVertexStreamSource::Binormal					(12);
const GXVertexStreamSource			GXVertexStreamSource::Blend4Index				(13);
const GXVertexStreamSource			GXVertexStreamSource::Blend4Weight				(14);
const GXVertexStreamSource			GXVertexStreamSource::Blend1Index				(15);

/*
void EpicForce::checkGLError(const char *name)
{
	int error = glGetError();
	
	if(error)
		debug("%s glGetError(%04x)", name, error);
}
*/