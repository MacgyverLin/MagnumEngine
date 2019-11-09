#ifndef _GXDef_h_
#define _GXDef_h_

#include "Stage.h"
#include "Array.h"
#include "EString.h"
#include "IVector2.h"
#include "IVector3.h"
#include "IVector4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix2.h" 
#include "Matrix3.h"
#include "Matrix4.h"
using namespace EpicForce;

namespace EpicForce
{

class GXImageRect 
{
public:
	GXImageRect()
	{
	}

	GXImageRect(int x_, int y_, int width_, int height_)
	{
		this->x			= x_;
		this->y			= y_;
		this->width		= width_;
		this->height	= height_;
	}

	void read(InputStream &is)
	{
		is >> x >> y >> width >> height;
	}

	void write(OutputStream &os) const
	{
		os << x << y << width << height;
	}

	int x;
	int y;
	int width;
	int height;
};

class GXBlendMode
{
public:
	GXBlendMode(unsigned int order_ = 0)							
	{
		order = order_;				
	}

	operator unsigned int ();
	operator const unsigned int () const;
	unsigned int getValue() const;

	static const GXBlendMode Add;
	static const GXBlendMode Subtract;
	static const GXBlendMode ReverseSubtract;

	bool set(const String &value)
	{
		if(value=="add")
		{
			*this = Add;
			return true;
		}
		else if(value=="subtract")
		{
			*this = Subtract;
			return true;
		}
		else if(value=="reversesubtract")
		{
			*this = ReverseSubtract;
			return true;
		}
		else
		{
			return false;
		}
	}

	void read(InputStream &is)
	{
		is >> order;
	}

	void write(OutputStream &os) const
	{
		os << order;
	}
private:
	unsigned int order;
};

class GXBlendFactor
{
public:
	GXBlendFactor(unsigned int order_ = 0)							
	{
		order = order_;				
	}

	operator unsigned int ();
	operator const unsigned int () const;
	unsigned int getValue() const;

	static const GXBlendFactor Zero;
	static const GXBlendFactor One;
	static const GXBlendFactor SrcColor;
	static const GXBlendFactor OneMinusSrcColor;
	static const GXBlendFactor SrcAlpha;
	static const GXBlendFactor OneMinusSrcAlpha;
	static const GXBlendFactor DstColor;
	static const GXBlendFactor OneMinusDstColor;
	static const GXBlendFactor DstAlpha;
	static const GXBlendFactor OneMinusDstAlpha;
	static const GXBlendFactor SrcAlphaSaturate;

	bool set(const String &value)
	{
		if(value=="zero")
		{
			*this = Zero;
			return true;
		}
		else if(value=="one")
		{
			*this = One;
			return true;
		}
		else if(value=="srccolor")
		{
			*this = SrcColor;
			return true;
		}
		else if(value=="oneminussrccolor")
		{
			*this = OneMinusSrcColor;
			return true;
		}
		else if(value=="srcalpha")
		{
			*this = SrcAlpha;
			return true;
		}
		else if(value=="oneminussrcalpha")
		{
			*this = OneMinusSrcAlpha;
			return true;
		}
		else if(value=="dstcolor")
		{
			*this = DstColor;
			return true;
		}
		else if(value=="oneminusdstcolor")
		{
			*this = OneMinusDstColor;
			return true;
		}
		else if(value=="dstalpha")
		{
			*this = DstAlpha;
			return true;
		}
		else if(value=="oneminusdstalpha")
		{
			*this = OneMinusDstAlpha;
			return true;
		}
		else if(value=="srcalphasaturate")
		{
			*this = SrcAlphaSaturate;
			return true;
		}
		else
		{
			return false;
		}
	}

	void read(InputStream &is)
	{
		is >> order;
	}

	void write(OutputStream &os) const
	{
		os << order;
	}
private:
	unsigned int order;
};

class GXClearMask
{
public:
	GXClearMask(unsigned int mask_ = 0)							
	{
		mask = mask_;				
	}

	operator unsigned int ();
	operator const unsigned int () const;
	unsigned int getValue() const;

	static const GXClearMask None;
	static const GXClearMask Color;
	static const GXClearMask Depth;
	static const GXClearMask Stencil;
	static const GXClearMask All;

	void read(InputStream &is)
	{
		is >> mask;
	}

	void write(OutputStream &os) const
	{
		os << mask;
	}
private:
	unsigned int mask;
};

class GXColorMask
{
public:
	GXColorMask(unsigned int mask_ = 0)							
	{
		mask = mask_;				
	}
	operator unsigned int ();
	operator const unsigned int () const;
	unsigned int getValue() const;

	static const GXColorMask None;
	static const GXColorMask R;
	static const GXColorMask G;
	static const GXColorMask B;
	static const GXColorMask A;
	static const GXColorMask Rgb;
	static const GXColorMask Rgba;

	void read(InputStream &is)
	{
		is >> mask;
	}

	void write(OutputStream &os) const
	{
		os << mask;
	}

	bool set(const String &value)
	{
		this->mask = 0;

		for(int i=0; i<value.length(); i++)
		{
			if(value[i] == 'r')
			{
				this->mask |= R.mask;
			}
			else if(value[i] == 'g')
			{
				this->mask |= G.mask;
			}
			else if(value[i] == 'b')
			{
				this->mask |= B.mask;
			}
			else if(value[i] == 'a')
			{
				this->mask |= A.mask;
			}
			else
			{
				return false;
			}
		}

		return true;

		/*
		int last = 0;

		this->mask = 0;
		for(int i=0; i<=value.length(); i++)
		{
			if(i==value.length() || value[i]=='|')
			{
				String token = value.extract(last, i-last);
				token.trim();

				if(token == "red")
				{
					this->mask |= R.mask;
				}
				else if(token == "green")
				{
					this->mask |= G.mask;
				}
				else if(token == "blue")
				{
					this->mask |= B.mask;
				}
				else if(token == "alpha")
				{
					this->mask |= A.mask;
				}
				else
				{
					return false;
				}

				last = i+1;
			}
		}

		return true;
		*/
	}
private:
	unsigned int mask;
};

class GXCullMode
{
public:
	GXCullMode(unsigned int order_ = 0)							
	{
		order = order_;				
	}
	operator unsigned int ();
	operator const unsigned int () const;
	unsigned int getValue() const;

	static const GXCullMode CW;
	static const GXCullMode CCW;

	bool set(const String &value)
	{
		if( value == "cw" )
		{
			*this = CW;
			return true;
		}
		else if( value == "ccw" )
		{
			*this = CCW;
			return true;
		}
		else
		{
			return false;
		}
	}

	void read(InputStream &is)
	{
		is >> order;
	}

	void write(OutputStream &os) const
	{
		os << order;
	}
private:
	unsigned int order;
};

class GXDepthTestMode
{
public:
	GXDepthTestMode(unsigned int order_ = 0)							
	{
		order = order_;				
	}
	operator unsigned int ();
	operator const unsigned int () const;
	unsigned int getValue() const;

	static const GXDepthTestMode Always;
	static const GXDepthTestMode Never;
	static const GXDepthTestMode Equal;
	static const GXDepthTestMode NotEequal;
	static const GXDepthTestMode Less;
	static const GXDepthTestMode Greater;
	static const GXDepthTestMode LEqual;
	static const GXDepthTestMode GEqual;

	bool set(const String &value)
	{
		if( value == "always" )
		{
			*this = Always;
			return true;
		}
		else if( value == "never" )
		{
			*this = Never;
			return true;
		}
		else if( value == "equal" )
		{
			*this = Equal;
			return true;
		}
		else if( value == "noteequal" )
		{
			*this = NotEequal;
			return true;
		}
		else if( value == "less" )
		{
			*this = Less;
			return true;
		}
		else if( value == "greater" )
		{
			*this = Greater;
			return true;
		}
		else if( value == "lequal" )
		{
			*this = LEqual;
			return true;
		}
		else if( value == "gequal" )
		{
			*this = GEqual;
			return true;
		}
		else
		{
			return false;
		}
	}

	void read(InputStream &is)
	{
		is >> order;
	}

	void write(OutputStream &os) const
	{
		os << order;
	}
private:
	unsigned int order;
};

class GXDrawMode
{
public:
	GXDrawMode(unsigned int order_ = 0)							
	{
		order = order_;				
	}
	operator unsigned int ();
	operator const unsigned int () const;
	unsigned int getValue() const;

	static const GXDrawMode Points;
	static const GXDrawMode Lines;
	static const GXDrawMode LineStrip;
	static const GXDrawMode Triangles;
	static const GXDrawMode TriangleStrip;
	static const GXDrawMode TriangleFan;

	void read(InputStream &is)
	{
		is >> order;
	}

	void write(OutputStream &os) const
	{
		os << order;
	}
private:
	unsigned int order;
};

class GXEnableMode
{
public:
	GXEnableMode(unsigned int order_ = 0)							
	{
		order = order_;				
	}
	operator unsigned int ();
	operator const unsigned int () const;
	unsigned int getValue() const;

	static const GXEnableMode None;
	static const GXEnableMode CullFace;
	static const GXEnableMode ScissorTest;
	static const GXEnableMode Blend;
	static const GXEnableMode DepthTest;
	static const GXEnableMode PolygonOffsetFill;
	static const GXEnableMode StencilTest;
	static const GXEnableMode Dither;
	static const GXEnableMode All;

	void read(InputStream &is)
	{
		is >> order;
	}

	void write(OutputStream &os) const
	{
		os << order;
	}
private:
	unsigned int order;
};

class GXMultiSampleMode
{
public:
	GXMultiSampleMode(unsigned int order_ = 0)							
	{
		order = order_;				
	}
	operator unsigned int ();
	operator const unsigned int () const;
	unsigned int getValue() const;

	static const GXMultiSampleMode None;
	static const GXMultiSampleMode Msaa2x;
	static const GXMultiSampleMode Msaa4x;

	void read(InputStream &is)
	{
		is >> order;
	}

	void write(OutputStream &os) const
	{
		os << order;
	}
private:
	unsigned int order;
};

class GXPixelBufferOption
{
public:
	GXPixelBufferOption(unsigned int order_ = 0)							
	{
		order = order_;				
	}
	operator unsigned int ();
	operator const unsigned int () const;
	unsigned int getValue() const;

	static const GXPixelBufferOption None;
	static const GXPixelBufferOption Renderable;

	void read(InputStream &is)
	{
		is >> order;
	}

	void write(OutputStream &os) const
	{
		os << order;
	}
private:
	unsigned int order;
};

class GXPixelBufferType
{
public:
	GXPixelBufferType(unsigned int order_ = 0)							
	{
		order = order_;				
	}

	operator unsigned int ();
	operator const unsigned int () const;
	unsigned int getValue() const;

	static const GXPixelBufferType None;
	static const GXPixelBufferType GXTexture2D;
	static const GXPixelBufferType GXTextureCube;
	static const GXPixelBufferType GXColorBuffer;
	static const GXPixelBufferType DepthBuffer;

	void read(InputStream &is)
	{
		is >> order;
	}

	void write(OutputStream &os) const
	{
		os << order;
	}
private:
	unsigned int order;
};

class GXPixelFormat
{
public:
	GXPixelFormat(unsigned int order_ = 0)							
	{
		order = order_;				
	}

	operator unsigned int ();
	operator const unsigned int () const;
	unsigned int getValue() const;

	static const GXPixelFormat None			;
	static const GXPixelFormat R8G8B8		;
	static const GXPixelFormat R5G6B5		;
	static const GXPixelFormat RGB_PVRTC2	;
	static const GXPixelFormat RGB_PVRTC4	;
	static const GXPixelFormat RGB_ETC		;
	static const GXPixelFormat R8G8B8A8		;
	static const GXPixelFormat R4G4B4A4		;
	static const GXPixelFormat R5G5B5A1		;
	static const GXPixelFormat R16G16B16A16	;
	static const GXPixelFormat R32G32B32A32	;
	static const GXPixelFormat RGBA_PVRTC2	;
	static const GXPixelFormat RGBA_PVRTC4	;
	static const GXPixelFormat RGBA_ETC		;
	static const GXPixelFormat I8			;
	static const GXPixelFormat A8			;
	static const GXPixelFormat AI8			;
	static const GXPixelFormat D16S8		;
	static const GXPixelFormat D24S8		;

	void read(InputStream &is)
	{
		is >> order;
	}

	void write(OutputStream &os) const
	{
		os << order;
	}
private:
	unsigned int order;
};

class GXShaderAttributeType
{
public:
	GXShaderAttributeType(unsigned int order_ = 0)
	{
		order		 = order_;
	}

	operator unsigned int ();
	operator const unsigned int () const;
	const unsigned int getNumElements() const;
	const unsigned int getElementType() const;
	const unsigned int getSize() const;

	static const GXShaderAttributeType BOOL;
	static const GXShaderAttributeType BVEC2;
	static const GXShaderAttributeType BVEC3;
	static const GXShaderAttributeType BVEC4;
	static const GXShaderAttributeType INT;
	static const GXShaderAttributeType IVEC2;
	static const GXShaderAttributeType IVEC3;
	static const GXShaderAttributeType IVEC4;
	static const GXShaderAttributeType FLOAT;
	static const GXShaderAttributeType VEC2;
	static const GXShaderAttributeType VEC3;
	static const GXShaderAttributeType VEC4;
	static const GXShaderAttributeType MAT2;
	static const GXShaderAttributeType MAT3;
	static const GXShaderAttributeType MAT4;

	bool set(const char *name)
	{
		String str = name;
		str.toLower();

		if(str=="bool")
		{
			*this = GXShaderAttributeType::BOOL;
			return true;
		}
		else if(str=="bvec2")
		{
			*this = GXShaderAttributeType::BVEC2;
			return true;
		}
		else if(str=="bvec3")
		{
			*this = GXShaderAttributeType::BVEC3;
			return true;
		}
		else if(str=="bvec4")
		{
			*this = GXShaderAttributeType::BVEC4;
			return true;
		}
		else if(str=="int")
		{
			*this = GXShaderAttributeType::INT;
			return true;
		}
		else if(str=="ivec2")
		{
			*this = GXShaderAttributeType::IVEC2;
			return true;
		}
		else if(str=="ivec3")
		{
			*this = GXShaderAttributeType::IVEC3;
			return true;
		}
		else if(str=="ivec4")
		{
			*this = GXShaderAttributeType::IVEC4;
			return true;
		}
		else if(str=="float")
		{
			*this = GXShaderAttributeType::FLOAT;
			return true;
		}
		else if(str=="vec2")
		{
			*this = GXShaderAttributeType::VEC2;
			return true;
		}
		else if(str=="vec3")
		{
			*this = GXShaderAttributeType::VEC3;
			return true;
		}
		else if(str=="vec4")
		{
			*this = GXShaderAttributeType::VEC4;
			return true;
		}
		else if(str=="mat2")
		{
			*this = GXShaderAttributeType::MAT2;
			return true;
		}
		else if(str=="mat3")
		{
			*this = GXShaderAttributeType::MAT3;
			return true;
		}
		else if(str=="mat4")
		{
			*this = GXShaderAttributeType::MAT4;
			return true;
		}
		else
			return false;
	}

	void read(InputStream &is)
	{
		is >> order;
	}

	void write(OutputStream &os) const
	{
		os << order;
	}
private:
	unsigned int order;
};

class GXShaderUniformType
{
public:
	GXShaderUniformType(unsigned int order_ = 0)
	{
		order		 = order_;
	}
	
	operator unsigned int ();
	operator const unsigned int () const;
	const unsigned int getNumElements() const;
	const unsigned int getElementType() const;
	const unsigned int getSize() const;

	static const GXShaderUniformType BOOL;
	static const GXShaderUniformType BVEC2;
	static const GXShaderUniformType BVEC3;
	static const GXShaderUniformType BVEC4;
	static const GXShaderUniformType INT;
	static const GXShaderUniformType IVEC2;
	static const GXShaderUniformType IVEC3;
	static const GXShaderUniformType IVEC4;
	static const GXShaderUniformType FLOAT;
	static const GXShaderUniformType VEC2;
	static const GXShaderUniformType VEC3;
	static const GXShaderUniformType VEC4;
	static const GXShaderUniformType MAT2;
	static const GXShaderUniformType MAT3;
	static const GXShaderUniformType MAT4;
	static const GXShaderUniformType SAMPLER2D;
	static const GXShaderUniformType SAMPLERCUBE;

	void read(InputStream &is)
	{
		is >> order;
	}

	void write(OutputStream &os) const
	{
		os << order;
	}
private:
	unsigned int order;
};

class GXStencilTestMode
{
public:
	GXStencilTestMode(unsigned int order_ = 0)							
	{
		order = order_;				
	}

	operator unsigned int ();
	operator const unsigned int () const;
	unsigned int getValue() const;

	static const GXStencilTestMode Always;
	static const GXStencilTestMode Never;
	static const GXStencilTestMode Equal;
	static const GXStencilTestMode NotEequal;
	static const GXStencilTestMode Less;
	static const GXStencilTestMode Greater;
	static const GXStencilTestMode LEqual;
	static const GXStencilTestMode GEqual;

	bool set(const String &value)
	{
		if( value == "always" )
		{
			*this = Always;
			return true;
		}
		else if( value == "never" )
		{
			*this = Never;
			return true;
		}
		else if( value == "equal" )
		{
			*this = Equal;
			return true;
		}
		else if( value == "noteequal" )
		{
			*this = NotEequal;
			return true;
		}
		else if( value == "less" )
		{
			*this = Less;
			return true;
		}
		else if( value == "greater" )
		{
			*this = Greater;
			return true;
		}
		else if( value == "lequal" )
		{
			*this = LEqual;
			return true;
		}
		else if( value == "gequal" )
		{
			*this = GEqual;
			return true;
		}
		else
		{
			return false;
		}
	}

	void read(InputStream &is)
	{
		is >> order;
	}

	void write(OutputStream &os) const
	{
		os << order;
	}
private:
	unsigned int order;
};

class GXStencilOp
{
public:
	GXStencilOp(unsigned int order_ = 0)							
	{
		order = order_;				
	}

	operator unsigned int ();
	operator const unsigned int () const;
	unsigned int getValue() const;

	static const GXStencilOp Keep;
	static const GXStencilOp Zero;
	static const GXStencilOp Replace;
	static const GXStencilOp Invert;
	static const GXStencilOp Incr;
	static const GXStencilOp Decr;
	static const GXStencilOp IncrWrap;
	static const GXStencilOp DecrWrap;

	bool set(const String &value)
	{
		if( value == "keep" )
		{
			*this = Keep;
			return true;
		}
		else if( value == "zero" )
		{
			*this = Zero;
			return true;
		}
		else if( value == "replace" )
		{
			*this = Replace;
			return true;
		}
		else if( value == "invert" )
		{
			*this = Invert;
			return true;
		}
		else if( value == "incr" )
		{
			*this = Incr;
			return true;
		}
		else if( value == "decr" )
		{
			*this = Decr;
			return true;
		}
		else if( value == "incrwrap" )
		{
			*this = IncrWrap;
			return true;
		}
		else if( value == "decrwrap" )
		{
			*this = DecrWrap;
			return true;
		}
		else
		{
			return false;
		}
	}

	void read(InputStream &is)
	{
		is >> order;
	}

	void write(OutputStream &os) const
	{
		os << order;
	}
private:
	unsigned int order;
};

class GXTextureCubeFace
{
public:
	GXTextureCubeFace(unsigned int order_ = 0)							
	{
		order = order_;				
	}

	operator unsigned int ();
	operator const unsigned int () const;
	unsigned int getValue() const;

	static const GXTextureCubeFace PositiveX;
	static const GXTextureCubeFace NegativeX;
	static const GXTextureCubeFace PositiveY;
	static const GXTextureCubeFace NegativeY;
	static const GXTextureCubeFace PositiveZ;
	static const GXTextureCubeFace NegativeZ;

	void read(InputStream &is)
	{
		is >> order;
	}

	void write(OutputStream &os) const
	{
		os << order;
	}
private:
	unsigned int order;
};

class GXTextureMinFilterMode
{
public:
	GXTextureMinFilterMode(unsigned int order_ = 0)							
	{
		order = order_;				
	}

	operator unsigned int ();
	operator const unsigned int () const;
	unsigned int getValue() const;

	static const GXTextureMinFilterMode Nearest;
	static const GXTextureMinFilterMode Linear;
	static const GXTextureMinFilterMode NearestMipmapNearest;
	static const GXTextureMinFilterMode LinearMipmapNearest;
	static const GXTextureMinFilterMode NearestMipmapLinear;
	static const GXTextureMinFilterMode LinearMipmapLinear;

	bool set(const String &value)
	{
		if( value == "nearest" )
		{
			*this = Nearest;
			return true;
		}
		else if( value == "linear" )
		{
			*this = Linear;
			return true;
		}
		else if( value == "nearestmipmapnearest" )
		{
			*this = NearestMipmapNearest;
			return true;
		}
		else if( value == "linearmipmapnearest" )
		{
			*this = LinearMipmapNearest;
			return true;
		}
		else if( value == "nearestmipmaplinear" )
		{
			*this = NearestMipmapLinear;
			return true;
		}
		else if( value == "linearmipmaplinear" )
		{
			*this = LinearMipmapLinear;
			return true;
		}
		else
		{
			return false;
		}
	}

	void read(InputStream &is)
	{
		is >> order;
	}

	void write(OutputStream &os) const
	{
		os << order;
	}
private:
	unsigned int order;
};

class GXTextureMagFilterMode
{
public:
	GXTextureMagFilterMode(unsigned int order_ = 0)							
	{
		order = order_;				
	}

	operator unsigned int ();
	operator const unsigned int () const;
	unsigned int getValue() const;

	static const GXTextureMagFilterMode Nearest;
	static const GXTextureMagFilterMode Linear;

	bool set(const String &value)
	{
		if( value == "nearest" )
		{
			*this = Nearest;
			return true;
		}
		else if( value == "linear" )
		{
			*this = Linear;
			return true;
		}
		else
		{
			return false;
		}
	}

	void read(InputStream &is)
	{
		is >> order;
	}

	void write(OutputStream &os) const
	{
		os << order;
	}
private:
	unsigned int order;
};

class GXTextureWrapMode
{
public:
	GXTextureWrapMode(unsigned int order_ = 0)							
	{
		order = order_;				
	}

	operator unsigned int ();
	operator const unsigned int () const;
	unsigned int getValue() const;

	static const GXTextureWrapMode Repeat;
	static const GXTextureWrapMode ClampToEdge;
	static const GXTextureWrapMode MirroredRepeat;

	bool set(const String &value)
	{
		if( value == "repeat" )
		{
			*this = Repeat;
			return true;
		}
		else if( value == "clamptoedge" )
		{
			*this = ClampToEdge;
			return true;
		}
		else if( value == "mirroredrepeat" )
		{
			*this = MirroredRepeat;
			return true;
		}
		else
		{
			return false;
		}
	}

	void read(InputStream &is)
	{
		is >> order;
	}

	void write(OutputStream &os) const
	{
		os << order;
	}
private:
	unsigned int order;
};

class GXVertexFormat
{
public:
	GXVertexFormat(unsigned int order_ = 0)							
	{
		order = order_;				
	}

	operator unsigned int ();
	operator const unsigned int () const;

	const unsigned int getNumElements() const;
	const unsigned int getElementType() const;
	const bool getNormalize() const;
	const unsigned int getSize() const;

	static const GXVertexFormat BYTE;
	static const GXVertexFormat BYTE2;
	static const GXVertexFormat BYTE3;
	static const GXVertexFormat BYTE4;
	static const GXVertexFormat UBYTE;
	static const GXVertexFormat UBYTE2;
	static const GXVertexFormat UBYTE3;
	static const GXVertexFormat UBYTE4;
	static const GXVertexFormat SHORT;
	static const GXVertexFormat SHORT2;
	static const GXVertexFormat SHORT3;
	static const GXVertexFormat SHORT4;
	static const GXVertexFormat USHORT;
	static const GXVertexFormat USHORT2;
	static const GXVertexFormat USHORT3;
	static const GXVertexFormat USHORT4;
	static const GXVertexFormat INT;
	static const GXVertexFormat INT2;
	static const GXVertexFormat INT3;
	static const GXVertexFormat INT4;
	static const GXVertexFormat UINT;
	static const GXVertexFormat UINT2;
	static const GXVertexFormat UINT3;
	static const GXVertexFormat UINT4;
	static const GXVertexFormat BYTEN;
	static const GXVertexFormat BYTE2N;
	static const GXVertexFormat BYTE3N;
	static const GXVertexFormat BYTE4N;
	static const GXVertexFormat UBYTEN;
	static const GXVertexFormat UBYTE2N;
	static const GXVertexFormat UBYTE3N;
	static const GXVertexFormat UBYTE4N;
	static const GXVertexFormat SHORTN;
	static const GXVertexFormat SHORT2N;
	static const GXVertexFormat SHORT3N;
	static const GXVertexFormat SHORT4N;
	static const GXVertexFormat USHORTN;
	static const GXVertexFormat USHORT2N;
	static const GXVertexFormat USHORT3N;
	static const GXVertexFormat USHORT4N;
	static const GXVertexFormat INTN;
	static const GXVertexFormat INT2N;
	static const GXVertexFormat INT3N;
	static const GXVertexFormat INT4N;
	static const GXVertexFormat UINTN;
	static const GXVertexFormat UINT2N;
	static const GXVertexFormat UINT3N;
	static const GXVertexFormat UINT4N;
	static const GXVertexFormat FLOAT;
	static const GXVertexFormat FLOAT2;
	static const GXVertexFormat FLOAT3;
	static const GXVertexFormat FLOAT4;
	static const GXVertexFormat HALF;
	static const GXVertexFormat HALF2;
	static const GXVertexFormat HALF3;
	static const GXVertexFormat HALF4;

	bool operator == (const GXVertexFormat &other) const
	{
		return	order == other.order;
	}

	bool set(const char *name)
	{
		String str = name;
		str.toLower();

		if(str=="byte")
		{
			*this = GXVertexFormat::BYTE;
			return true;
		}
		else if(str=="byte2")
		{
			*this = GXVertexFormat::BYTE2;
			return true;
		}
		else if(str=="byte3")
		{
			*this = GXVertexFormat::BYTE3;
			return true;
		}
		else if(str=="byte4")
		{
			*this = GXVertexFormat::BYTE4;
			return true;
		}
		else if(str=="ubyte")
		{
			*this = GXVertexFormat::UBYTE;
			return true;
		}
		else if(str=="ubyte2")
		{
			*this = GXVertexFormat::UBYTE2;
			return true;
		}
		else if(str=="ubyte3")
		{
			*this = GXVertexFormat::UBYTE3;
			return true;
		}
		else if(str=="ubyte4")
		{
			*this = GXVertexFormat::UBYTE4;
			return true;
		}
		else if(str=="short")
		{
			*this = GXVertexFormat::SHORT;
			return true;
		}
		else if(str=="short2")
		{
			*this = GXVertexFormat::SHORT2;
			return true;
		}
		else if(str=="short3")
		{
			*this = GXVertexFormat::SHORT3;
			return true;
		}
		else if(str=="short4")
		{
			*this = GXVertexFormat::SHORT4;
			return true;
		}
		else if(str=="ushort")
		{
			*this = GXVertexFormat::USHORT;
			return true;
		}
		else if(str=="ushort2")
		{
			*this = GXVertexFormat::USHORT2;
			return true;
		}
		else if(str=="ushort3")
		{
			*this = GXVertexFormat::USHORT3;
			return true;
		}
		else if(str=="ushort4")
		{
			*this = GXVertexFormat::USHORT4;
			return true;
		}
		else if(str=="int")
		{
			*this = GXVertexFormat::INT;
			return true;
		}
		else if(str=="int2")
		{
			*this = GXVertexFormat::INT2;
			return true;
		}
		else if(str=="int3")
		{
			*this = GXVertexFormat::INT3;
			return true;
		}
		else if(str=="int4")
		{
			*this = GXVertexFormat::INT4;
			return true;
		}
		else if(str=="uint")
		{
			*this = GXVertexFormat::UINT;
			return true;
		}
		else if(str=="uint2")
		{
			*this = GXVertexFormat::UINT2;
			return true;
		}
		else if(str=="uint3")
		{
			*this = GXVertexFormat::UINT3;
			return true;
		}
		else if(str=="uint4")
		{
			*this = GXVertexFormat::UINT4;
			return true;
		}
		else if(str=="byten")
		{	
			*this = GXVertexFormat::BYTEN;
			return true;
		}
		else if(str=="byte2n")
		{
			*this = GXVertexFormat::BYTE2N;
			return true;
		}
		else if(str=="byte3n")
		{
			*this = GXVertexFormat::BYTE3N;
			return true;
		}
		else if(str=="byte4n")
		{
			*this = GXVertexFormat::BYTE4N;
			return true;
		}
		else if(str=="ubyten")
		{
			*this = GXVertexFormat::UBYTEN;
			return true;
		}
		else if(str=="ubyte2n")
		{
			*this = GXVertexFormat::UBYTE2N;
			return true;
		}
		else if(str=="ubyte3n")
		{
			*this = GXVertexFormat::UBYTE3N;
			return true;
		}
		else if(str=="ubyte4n")
		{
			*this = GXVertexFormat::UBYTE4N;
			return true;
		}
		else if(str=="shortn")
		{
			*this = GXVertexFormat::SHORTN;
			return true;
		}
		else if(str=="short2n")
		{
			*this = GXVertexFormat::SHORT2N;
			return true;
		}
		else if(str=="short3n")
		{
			*this = GXVertexFormat::SHORT3N;
			return true;
		}
		else if(str=="short4n")
		{
			*this = GXVertexFormat::SHORT4N;
			return true;
		}
		else if(str=="ushortn")
		{
			*this = GXVertexFormat::USHORTN;
			return true;
		}
		else if(str=="ushort2n")
		{
			*this = GXVertexFormat::USHORT2N;
			return true;
		}
		else if(str=="ushort3n")
		{
			*this = GXVertexFormat::USHORT3N;
			return true;
		}
		else if(str=="ushort4n")
		{
			*this = GXVertexFormat::USHORT4N;
			return true;
		}
		else if(str=="intn")
		{
			*this = GXVertexFormat::INTN;
			return true;
		}
		else if(str=="int2n")
		{
			*this = GXVertexFormat::INT2N;
			return true;
		}
		else if(str=="int3n")
		{
			*this = GXVertexFormat::INT3N;
			return true;
		}
		else if(str=="int4n")
		{
			*this = GXVertexFormat::INT4N;
			return true;
		}
		else if(str=="uintn")
		{
			*this = GXVertexFormat::UINTN;
			return true;
		}
		else if(str=="uint2n")
		{
			*this = GXVertexFormat::UINT2N;
			return true;
		}
		else if(str=="uint3n")
		{
			*this = GXVertexFormat::UINT3N;
			return true;
		}
		else if(str=="uint4n")
		{
			*this = GXVertexFormat::UINT4N;
			return true;
		}
		else if(str=="float")
		{
			*this = GXVertexFormat::FLOAT;
			return true;
		}
		else if(str=="float2")
		{
			*this = GXVertexFormat::FLOAT2;
			return true;
		}
		else if(str=="float3")
		{
			*this = GXVertexFormat::FLOAT3;
			return true;
		}
		else if(str=="float4")
		{
			*this = GXVertexFormat::FLOAT4;
			return true;
		}
		else if(str=="half")
		{
			*this = GXVertexFormat::HALF;
			return true;
		}
		else if(str=="half2")
		{
			*this = GXVertexFormat::HALF2;
			return true;
		}
		else if(str=="half3")
		{
			*this = GXVertexFormat::HALF3;
			return true;
		}
		else if(str=="half4")
		{
			*this = GXVertexFormat::HALF4;
			return true;
		}
		else
		{
			return false;
		}
	}
	
	void read(InputStream &is)
	{
		is >> order;
	}

	void write(OutputStream &os) const
	{
		os << order;
	}
private:
	unsigned int order;
};

class GXVertexStreamSource
{
public:
	GXVertexStreamSource(unsigned int order_ = 0)							
	{
		order = order_;				
	}

	operator unsigned int ();
	operator const unsigned int () const;
	unsigned int getValue() const;

	bool operator == (const GXVertexStreamSource &other) const
	{
		return order == other.order;
	}

	static const GXVertexStreamSource POSITION0;
	static const GXVertexStreamSource POSITION1;
	static const GXVertexStreamSource POSITION2;
	static const GXVertexStreamSource POSITION3;
	static const GXVertexStreamSource NORMAL;
	static const GXVertexStreamSource COLOR0;
	static const GXVertexStreamSource COLOR1;
	static const GXVertexStreamSource TEXCOORD0;
	static const GXVertexStreamSource TEXCOORD1;
	static const GXVertexStreamSource TEXCOORD2;
	static const GXVertexStreamSource TEXCOORD3;
	static const GXVertexStreamSource TEXCOORD4;
	static const GXVertexStreamSource TEXCOORD5;
	static const GXVertexStreamSource TEXCOORD6;
	static const GXVertexStreamSource TEXCOORD7;
	static const GXVertexStreamSource TANGENT;
	static const GXVertexStreamSource BINORMAL;
	static const GXVertexStreamSource BLEND1INDEX;
	static const GXVertexStreamSource BLEND2INDEX;
	static const GXVertexStreamSource BLEND2WEIGHT;
	static const GXVertexStreamSource BLEND4INDEX;
	static const GXVertexStreamSource BLEND4WEIGHT;

	bool set(const char *name)
	{
		String str = name;
		str.toLower();

		if(str=="position0")
		{
			*this = GXVertexStreamSource::POSITION0;
			return true;
		}
		else if(str=="position1")
		{
			*this = GXVertexStreamSource::POSITION1;
			return true;
		}
		else if(str=="position2")
		{
			*this = GXVertexStreamSource::POSITION2;
			return true;
		}
		else if(str=="position3")
		{
			*this = GXVertexStreamSource::POSITION3;
			return true;
		}
		else if(str=="normal")
		{
			*this = GXVertexStreamSource::NORMAL;
			return true;
		}
		else if(str=="color0")
		{
			*this = GXVertexStreamSource::COLOR0;
			return true;
		}
		else if(str=="color1")
		{
			*this = GXVertexStreamSource::COLOR1;
			return true;
		}
		else if(str=="texcoord0")
		{
			*this = GXVertexStreamSource::TEXCOORD0;
			return true;
		}
		else if(str=="texcoord1")
		{
			*this = GXVertexStreamSource::TEXCOORD1;
			return true;
		}
		else if(str=="texcoord2")
		{
			*this = GXVertexStreamSource::TEXCOORD2;
			return true;
		}
		else if(str=="texcoord3")
		{
			*this = GXVertexStreamSource::TEXCOORD3;
			return true;
		}
		else if(str=="texcoord4")
		{
			*this = GXVertexStreamSource::TEXCOORD4;
			return true;
		}
		else if(str=="texcoord5")
		{
			*this = GXVertexStreamSource::TEXCOORD5;
			return true;
		}
		else if(str=="texcoord6")
		{
			*this = GXVertexStreamSource::TEXCOORD6;
			return true;
		}
		else if(str=="texcoord7")
		{
			*this = GXVertexStreamSource::TEXCOORD7;
			return true;
		}
		else if(str=="tangent")
		{
			*this = GXVertexStreamSource::TANGENT;
			return true;
		} 
		else if(str=="binormal")
		{
			*this = GXVertexStreamSource::BINORMAL;
			return true;
		}
		else if(str=="blend1index")
		{
			*this = GXVertexStreamSource::BLEND1INDEX;
			return true;
		}
		else if(str=="blend2index")
		{
			*this = GXVertexStreamSource::BLEND2INDEX;
			return true;
		}
		else if(str=="blend2weight")
		{
			*this = GXVertexStreamSource::BLEND2WEIGHT;
			return true;
		}
		else if(str=="blend4index")
		{
			*this = GXVertexStreamSource::BLEND4INDEX;
			return true;
		}
		else if(str=="blend4weight")
		{
			*this = GXVertexStreamSource::BLEND4WEIGHT;
			return true;
		}
		else
			return false;
	}

	void read(InputStream &is)
	{
		is >> order;
	}

	void write(OutputStream &os) const
	{
		os << order;
	}
private:
	unsigned int order;
};

#ifdef EXPORTER
#else
void checkGLError(const char *name);
#endif

};

#endif