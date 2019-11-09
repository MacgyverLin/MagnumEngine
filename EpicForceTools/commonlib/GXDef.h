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

	int x;
	int y;
	int width;
	int height;
};


class GXBlendFuncMode
{
public:
	GXBlendFuncMode(unsigned int mode_ = 0)							{ mode = mode_;				}
	operator unsigned int ()										{ return mode;				}
	operator const unsigned int () const							{ return mode;				}

	static const GXBlendFuncMode Add;
	static const GXBlendFuncMode Subtract;
	static const GXBlendFuncMode ReverseSubtract;

	void read(InputStream &is)
	{
		is >> mode;
	}

	void write(OutputStream &os) const
	{
		os << mode;
	}

	bool from(const String &value)
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
private:
	unsigned int mode;
};

class GXBlendFuncFactor
{
public:
	GXBlendFuncFactor(unsigned int factor_ = 0)						{ factor = factor_;			}
	operator unsigned int ()										{ return factor;			}
	operator const unsigned int () const							{ return factor;			}

	static const GXBlendFuncFactor Zero;
	static const GXBlendFuncFactor One;
	static const GXBlendFuncFactor SrcColor;
	static const GXBlendFuncFactor OneMinusSrcColor;
	static const GXBlendFuncFactor SrcAlpha;
	static const GXBlendFuncFactor OneMinusSrcAlpha;
	static const GXBlendFuncFactor DstColor;
	static const GXBlendFuncFactor OneMinusDstColor;
	static const GXBlendFuncFactor DstAlpha;
	static const GXBlendFuncFactor OneMinusDstAlpha;
	static const GXBlendFuncFactor SrcAlphaSaturate;

	void read(InputStream &is)
	{
		is >> factor;
	}

	void write(OutputStream &os) const
	{
		os << factor;
	}

	bool from(const String &value)
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
private:
	unsigned int factor;
};

class GXClearMask
{
public:
	GXClearMask(unsigned int mask_= 0)								{ mask = mask_;				}
	operator unsigned int ()										{ return mask;				}
	operator const unsigned int () const							{ return mask;				}

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
	GXColorMask(unsigned int mask_= 0)								{ mask = mask_;				}
	operator unsigned int ()										{ return mask;				}
	operator const unsigned int () const							{ return mask;				}

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

	bool from(const String &value)
	{
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
	}
private:
	unsigned int mask;
};

class GXCullFaceMode
{
public:
	GXCullFaceMode(unsigned int mode_ = 0)							{ mode = mode_;			}
	operator unsigned int ()										{ return mode;			}
	operator const unsigned int () const							{ return mode;			}

	static const GXCullFaceMode None;
	static const GXCullFaceMode Front;
	static const GXCullFaceMode Back;
	static const GXCullFaceMode FrontAndBack;

	void read(InputStream &is)
	{
		is >> mode;
	}

	void write(OutputStream &os) const
	{
		os << mode;
	}
private:
	unsigned int mode;
};

class GXCullFaceDirection
{
public:
	GXCullFaceDirection(unsigned int dir_ = 0)						{ dir = dir_;			}
	operator unsigned int ()										{ return dir;			}
	operator const unsigned int () const							{ return dir;			}

	static const GXCullFaceDirection CCW;
	static const GXCullFaceDirection CW;

	void read(InputStream &is)
	{
		is >> dir;
	}

	void write(OutputStream &os) const
	{
		os << dir;
	}

	bool from(const String &value)
	{
		if( value == "none" )
		{
			*this = CCW;
			return true;
		}
		if( value == "ccw" )
		{
			*this = CCW;
			return true;
		}
		else if( value == "cw" )
		{
			*this = CW;
			return true;
		}
		else
		{
			return false;
		}
	}
private:
	unsigned int dir;
};

class GXDepthFuncMode
{
public:
	GXDepthFuncMode(unsigned int mode_ = 0)							{ mode = mode_;			}
	operator unsigned int ()										{ return mode;			}
	operator const unsigned int () const							{ return mode;			}

	static const GXDepthFuncMode Always;
	static const GXDepthFuncMode Never;
	static const GXDepthFuncMode Equal;
	static const GXDepthFuncMode NotEequal;
	static const GXDepthFuncMode Less;
	static const GXDepthFuncMode Greater;
	static const GXDepthFuncMode LEqual;
	static const GXDepthFuncMode GEqual;

	void read(InputStream &is)
	{
		is >> mode;
	}

	void write(OutputStream &os) const
	{
		os << mode;
	}

	bool from(const String &value)
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
private:
	unsigned int mode;
};

class GXDrawMode
{
public:
	GXDrawMode(unsigned int mode_ = 0)								{ mode = mode_;			}
	operator unsigned int ()										{ return mode;			}
	operator const unsigned int () const							{ return mode;			}

	static const GXDrawMode Points;
	static const GXDrawMode Lines;
	static const GXDrawMode LineStrip;
	static const GXDrawMode Triangles;
	static const GXDrawMode TriangleStrip;
	static const GXDrawMode TriangleFan;

	void read(InputStream &is)
	{
		is >> mode;
	}

	void write(OutputStream &os) const
	{
		os << mode;
	}
private:
	unsigned int mode;
};

class GXEnableMode
{
public:
	GXEnableMode(unsigned int mode_ = 0)							{ mode = mode_;			}
	operator unsigned int ()										{ return mode;			}
	operator const unsigned int () const							{ return mode;			}

	static const GXEnableMode None;
	static const GXEnableMode ScissorTest;
	static const GXEnableMode CullFace;
	static const GXEnableMode Blend;
	static const GXEnableMode DepthTest;
	static const GXEnableMode PolygonOffsetFill;
	static const GXEnableMode StencilTest;
	static const GXEnableMode Dither;
	static const GXEnableMode All;

	void read(InputStream &is)
	{
		is >> mode;
	}

	void write(OutputStream &os) const
	{
		os << mode;
	}
private:
	unsigned int mode;
};

class GXMultiSampleMode
{
public:
	GXMultiSampleMode(unsigned int mode_= 0)						{ mode = mode_;			}
	operator unsigned int ()										{ return mode;			}
	operator const unsigned int () const							{ return mode;			}

	static const GXMultiSampleMode None;
	static const GXMultiSampleMode Msaa2x;
	static const GXMultiSampleMode Msaa4x;

	void read(InputStream &is)
	{
		is >> mode;
	}

	void write(OutputStream &os) const
	{
		os << mode;
	}
private:
	unsigned int mode;
};

class GXPixelBufferOption
{
public:
	GXPixelBufferOption(unsigned int option_ = 0)						{ option = option_; }
	operator unsigned int ()											{ return option;	}
	operator const unsigned int () const								{ return option;	}

	static const GXPixelBufferOption None;
	static const GXPixelBufferOption Renderable;

	void read(InputStream &is)
	{
		is >> option;
	}

	void write(OutputStream &os) const
	{
		os << option;
	}
private:
	unsigned int option;
};

class GXPixelBufferType
{
public:
	GXPixelBufferType(unsigned int type_ = 0)							{ type = type_;				}
	operator unsigned int ()											{ return type;				}
	operator const unsigned int () const								{ return type;				}

	static const GXPixelBufferType None;
	static const GXPixelBufferType GXTexture2D;
	static const GXPixelBufferType GXTextureCube;
	static const GXPixelBufferType GXColorBuffer;
	static const GXPixelBufferType DepthBuffer;

	void read(InputStream &is)
	{
		is >> type;
	}

	void write(OutputStream &os) const
	{
		os << type;
	}
private:
	unsigned int type;
};

class GXPixelFormat
{
public:
	GXPixelFormat(unsigned int format_ = 0)								{ format = format_;			}
	operator unsigned int ()											{ return format;			}
	operator const unsigned int () const								{ return format;			}

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
		is >> format;
	}

	void write(OutputStream &os) const
	{
		os << format;
	}
private:
	unsigned int format;
};

class GXShaderAttributeType
{
public:
	GXShaderAttributeType(unsigned int numElements_ = 0, unsigned int elementType_ = 0, unsigned int size_ = 0)
	{
		numElements  = numElements_;
		elementType  = elementType_;
		size 		 = size_;
	}

	const unsigned int getNumElements() const							{ return numElements;	}
	const unsigned int getElementType() const							{ return elementType;	}
	const unsigned int getSize() const									{ return size;			}

	static const GXShaderAttributeType None;
	static const GXShaderAttributeType Float;
	static const GXShaderAttributeType Float2;
	static const GXShaderAttributeType Float3;
	static const GXShaderAttributeType Float4;
	static const GXShaderAttributeType Int;
	static const GXShaderAttributeType Int2;
	static const GXShaderAttributeType Int3;
	static const GXShaderAttributeType Int4;
	static const GXShaderAttributeType Bool;
	static const GXShaderAttributeType Bool2;
	static const GXShaderAttributeType Bool3;
	static const GXShaderAttributeType Bool4;
	static const GXShaderAttributeType Float2x2;
	static const GXShaderAttributeType Float3x3;
	static const GXShaderAttributeType Float4x4;

	void read(InputStream &is)
	{
		is >> numElements >> elementType >> size;
	}

	void write(OutputStream &os) const
	{
		os << numElements << elementType << size;
	}
private:
	unsigned int numElements;
	unsigned int elementType;
	unsigned int size;
};

class GXShaderUniformType
{
public:
	GXShaderUniformType(unsigned int numElements_ = 0, unsigned int elementType_ = 0, unsigned int size_ = 0)
	{
		numElements  = numElements_;
		elementType  = elementType_;
		size 		 = size_;
	}
	
	const unsigned int getNumElements() const							{ return numElements;	}
	const unsigned int getElementType() const							{ return elementType;	}
	const unsigned int getSize() const									{ return size;			}

	static const GXShaderUniformType None;
	static const GXShaderUniformType Float;
	static const GXShaderUniformType Float2;
	static const GXShaderUniformType Float3;
	static const GXShaderUniformType Float4;
	static const GXShaderUniformType Int;
	static const GXShaderUniformType Int2;
	static const GXShaderUniformType Int3;
	static const GXShaderUniformType Int4;
	static const GXShaderUniformType Bool;
	static const GXShaderUniformType Bool2;
	static const GXShaderUniformType Bool3;
	static const GXShaderUniformType Bool4;
	static const GXShaderUniformType Float2x2;
	static const GXShaderUniformType Float3x3;
	static const GXShaderUniformType Float4x4;
	static const GXShaderUniformType Sampler2D;
	static const GXShaderUniformType SamplerCube;

	void read(InputStream &is)
	{
		is >> numElements >> elementType >> size;
	}

	void write(OutputStream &os) const
	{
		os << numElements << elementType << size;
	}
private:
	unsigned int numElements;
	unsigned int elementType;
	unsigned int size;
};

class GXStencilFuncMode
{
public:
	GXStencilFuncMode(unsigned int mode_ = 0)							{ mode = mode_;				}
	operator unsigned int ()											{ return mode;				}
	operator const unsigned int () const								{ return mode;				}

	static const GXStencilFuncMode Always;
	static const GXStencilFuncMode Never;
	static const GXStencilFuncMode Equal;
	static const GXStencilFuncMode NotEequal;
	static const GXStencilFuncMode Less;
	static const GXStencilFuncMode Greater;
	static const GXStencilFuncMode LEqual;
	static const GXStencilFuncMode GEqual;

	void read(InputStream &is)
	{
		is >> mode;
	}

	void write(OutputStream &os) const
	{
		os << mode;
	}

	bool from(const String &value)
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
private:
	unsigned int mode;
};

class GXStencilOpMode
{
public:
	GXStencilOpMode(unsigned int mode_ = 0)								{ mode = mode_;			}
	operator unsigned int ()											{ return mode;			}
	operator const unsigned int () const								{ return mode;			}

	static const GXStencilOpMode Keep;
	static const GXStencilOpMode Zero;
	static const GXStencilOpMode Replace;
	static const GXStencilOpMode Invert;
	static const GXStencilOpMode Incr;
	static const GXStencilOpMode Decr;
	static const GXStencilOpMode IncrWrap;
	static const GXStencilOpMode DecrWrap;

	void read(InputStream &is)
	{
		is >> mode;
	}

	void write(OutputStream &os) const
	{
		os << mode;
	}

	bool from(const String &value)
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
private:
	unsigned int mode;
};

class GXTextureCubeFace
{
public:
	GXTextureCubeFace(unsigned int face_ = 0)							{ face = face_;			}
	operator unsigned int ()											{ return face;			}
	operator const unsigned int () const								{ return face;			}

	static const GXTextureCubeFace PositiveX;
	static const GXTextureCubeFace NegativeX;
	static const GXTextureCubeFace PositiveY;
	static const GXTextureCubeFace NegativeY;
	static const GXTextureCubeFace PositiveZ;
	static const GXTextureCubeFace NegativeZ;

	void read(InputStream &is)
	{
		is >> face;
	}

	void write(OutputStream &os) const
	{
		os << face;
	}
private:
	unsigned int face;
};

class GXTextureMinFilterMode
{
public:
	GXTextureMinFilterMode(unsigned int mode_ = 0)						{ mode = mode_;			}
	operator unsigned int ()											{ return mode;			}
	operator const unsigned int () const								{ return mode;			}

	static const GXTextureMinFilterMode Nearest;
	static const GXTextureMinFilterMode Linear;
	static const GXTextureMinFilterMode Nearest_Mipmap_Nearest;
	static const GXTextureMinFilterMode Linear_Mipmap_Nearest;
	static const GXTextureMinFilterMode Nearest_Mipmap_Linear;
	static const GXTextureMinFilterMode Linear_Mipmap_Linear;

	void read(InputStream &is)
	{
		is >> mode;
	}

	void write(OutputStream &os) const
	{
		os << mode;
	}
private:
	unsigned int mode;
};

class GXTextureMagFilterMode
{
public:
	GXTextureMagFilterMode(unsigned int mode_ = 0)						{ mode = mode_;			}
	operator unsigned int ()											{ return mode;			}
	operator const unsigned int () const								{ return mode;			}

	static const GXTextureMagFilterMode Nearest;
	static const GXTextureMagFilterMode Linear;

	void read(InputStream &is)
	{
		is >> mode;
	}

	void write(OutputStream &os) const
	{
		os << mode;
	}
private:
	unsigned int mode;
};

class GXTextureWrapMode
{
public:
	GXTextureWrapMode(unsigned int mode_ = 0)							{ mode = mode_;			}
	operator unsigned int ()											{ return mode;			}
	operator const unsigned int () const								{ return mode;			}

	static const GXTextureWrapMode Repeat;
	static const GXTextureWrapMode ClampToEdge;
	static const GXTextureWrapMode MirroredRepeat;

	void read(InputStream &is)
	{
		is >> mode;
	}

	void write(OutputStream &os) const
	{
		os << mode;
	}
private:
	unsigned int mode;
};

class GXVertexFormat
{
public:
	GXVertexFormat(unsigned int numElements_ = 0, unsigned int elementType_ = 0, bool normalize_ = false, unsigned int size_ = 0)
	{
		numElements  = numElements_;
		elementType  = elementType_;
		normalize	 = normalize_;
		size 		 = size_;
	}

	unsigned int getNumElements() const									{ return numElements;	}
	unsigned int getElementType() const									{ return elementType;	}
	bool getNormalize() const											{ return normalize;		}
	unsigned int getSize() const										{ return size;			}

	static const GXVertexFormat None;
	static const GXVertexFormat Byte;
	static const GXVertexFormat Byte2;
	static const GXVertexFormat Byte3;
	static const GXVertexFormat Byte4;
	static const GXVertexFormat UByte;
	static const GXVertexFormat UByte2;
	static const GXVertexFormat UByte3;
	static const GXVertexFormat UByte4;
	static const GXVertexFormat Short;
	static const GXVertexFormat Short2;
	static const GXVertexFormat Short3;
	static const GXVertexFormat Short4;
	static const GXVertexFormat UShort;
	static const GXVertexFormat UShort2;
	static const GXVertexFormat UShort3;
	static const GXVertexFormat UShort4;
	static const GXVertexFormat Int;
	static const GXVertexFormat Int2;
	static const GXVertexFormat Int3;
	static const GXVertexFormat Int4;
	static const GXVertexFormat UInt;
	static const GXVertexFormat UInt2;
	static const GXVertexFormat UInt3;
	static const GXVertexFormat UInt4;

	static const GXVertexFormat ByteN;
	static const GXVertexFormat Byte2N;
	static const GXVertexFormat Byte3N;
	static const GXVertexFormat Byte4N;
	static const GXVertexFormat UByteN;
	static const GXVertexFormat UByte2N;
	static const GXVertexFormat UByte3N;
	static const GXVertexFormat UByte4N;
	static const GXVertexFormat ShortN;
	static const GXVertexFormat Short2N;
	static const GXVertexFormat Short3N;
	static const GXVertexFormat Short4N;
	static const GXVertexFormat UShortN;
	static const GXVertexFormat UShort2N;
	static const GXVertexFormat UShort3N;
	static const GXVertexFormat UShort4N;
	static const GXVertexFormat IntN;
	static const GXVertexFormat Int2N;
	static const GXVertexFormat Int3N;
	static const GXVertexFormat Int4N;
	static const GXVertexFormat UIntN;
	static const GXVertexFormat UInt2N;
	static const GXVertexFormat UInt3N;
	static const GXVertexFormat UInt4N;

	static const GXVertexFormat Float;
	static const GXVertexFormat Float2;
	static const GXVertexFormat Float3;
	static const GXVertexFormat Float4;
	static const GXVertexFormat Half;
	static const GXVertexFormat Half2;
	static const GXVertexFormat Half3;
	static const GXVertexFormat Half4;

	bool operator == (const GXVertexFormat &other) const
	{
		return	numElements == other.numElements &&
				elementType == other.elementType &&
				normalize   == other.normalize &&
				size        == other.size;
	}
	
	void read(InputStream &is)
	{
		is >> numElements >> elementType >> normalize >> size;
	}

	void write(OutputStream &os) const
	{
		os << numElements << elementType << normalize << size;
	}

	bool from(const char *name)
	{
		String str = name;
		str.toLower();

		if(str=="byte")
		{
			*this = GXVertexFormat::Byte;
			return true;
		}
		else if(str=="byte2")
		{
			*this = GXVertexFormat::Byte2;
			return true;
		}
		else if(str=="byte3")
		{
			*this = GXVertexFormat::Byte3;
			return true;
		}
		else if(str=="byte4")
		{
			*this = GXVertexFormat::Byte4;
			return true;
		}
		else if(str=="ubyte")
		{
			*this = GXVertexFormat::UByte;
			return true;
		}
		else if(str=="ubyte2")
		{
			*this = GXVertexFormat::UByte2;
			return true;
		}
		else if(str=="ubyte3")
		{
			*this = GXVertexFormat::UByte3;
			return true;
		}
		else if(str=="ubyte4")
		{
			*this = GXVertexFormat::UByte4;
			return true;
		}
		else if(str=="short")
		{
			*this = GXVertexFormat::Short;
			return true;
		}
		else if(str=="short2")
		{
			*this = GXVertexFormat::Short2;
			return true;
		}
		else if(str=="short3")
		{
			*this = GXVertexFormat::Short3;
			return true;
		}
		else if(str=="short4")
		{
			*this = GXVertexFormat::Short4;
			return true;
		}
		else if(str=="ushort")
		{
			*this = GXVertexFormat::UShort;
			return true;
		}
		else if(str=="ushort2")
		{
			*this = GXVertexFormat::UShort2;
			return true;
		}
		else if(str=="ushort3")
		{
			*this = GXVertexFormat::UShort3;
			return true;
		}
		else if(str=="ushort4")
		{
			*this = GXVertexFormat::UShort4;
			return true;
		}
		else if(str=="int")
		{
			*this = GXVertexFormat::Int;
			return true;
		}
		else if(str=="int2")
		{
			*this = GXVertexFormat::Int2;
			return true;
		}
		else if(str=="int3")
		{
			*this = GXVertexFormat::Int3;
			return true;
		}
		else if(str=="int4")
		{
			*this = GXVertexFormat::Int4;
			return true;
		}
		else if(str=="uint")
		{
			*this = GXVertexFormat::UInt;
			return true;
		}
		else if(str=="uint2")
		{
			*this = GXVertexFormat::UInt2;
			return true;
		}
		else if(str=="uint3")
		{
			*this = GXVertexFormat::UInt3;
			return true;
		}
		else if(str=="uint4")
		{
			*this = GXVertexFormat::UInt4;
			return true;
		}
		else if(str=="byten")
		{	
			*this = GXVertexFormat::ByteN;
			return true;
		}
		else if(str=="byte2n")
		{
			*this = GXVertexFormat::Byte2N;
			return true;
		}
		else if(str=="byte3n")
		{
			*this = GXVertexFormat::Byte3N;
			return true;
		}
		else if(str=="byte4n")
		{
			*this = GXVertexFormat::Byte4N;
			return true;
		}
		else if(str=="ubyten")
		{
			*this = GXVertexFormat::UByteN;
			return true;
		}
		else if(str=="ubyte2n")
		{
			*this = GXVertexFormat::UByte2N;
			return true;
		}
		else if(str=="ubyte3n")
		{
			*this = GXVertexFormat::UByte3N;
			return true;
		}
		else if(str=="ubyte4n")
		{
			*this = GXVertexFormat::UByte4N;
			return true;
		}
		else if(str=="shortn")
		{
			*this = GXVertexFormat::ShortN;
			return true;
		}
		else if(str=="short2n")
		{
			*this = GXVertexFormat::Short2N;
			return true;
		}
		else if(str=="short3n")
		{
			*this = GXVertexFormat::Short3N;
			return true;
		}
		else if(str=="short4n")
		{
			*this = GXVertexFormat::Short4N;
			return true;
		}
		else if(str=="ushortn")
		{
			*this = GXVertexFormat::UShortN;
			return true;
		}
		else if(str=="ushort2n")
		{
			*this = GXVertexFormat::UShort2N;
			return true;
		}
		else if(str=="ushort3n")
		{
			*this = GXVertexFormat::UShort3N;
			return true;
		}
		else if(str=="ushort4n")
		{
			*this = GXVertexFormat::UShort4N;
			return true;
		}
		else if(str=="intn")
		{
			*this = GXVertexFormat::IntN;
			return true;
		}
		else if(str=="int2n")
		{
			*this = GXVertexFormat::Int2N;
			return true;
		}
		else if(str=="int3n")
		{
			*this = GXVertexFormat::Int3N;
			return true;
		}
		else if(str=="int4n")
		{
			*this = GXVertexFormat::Int4N;
			return true;
		}
		else if(str=="uintn")
		{
			*this = GXVertexFormat::UIntN;
			return true;
		}
		else if(str=="uint2n")
		{
			*this = GXVertexFormat::UInt2N;
			return true;
		}
		else if(str=="uint3n")
		{
			*this = GXVertexFormat::UInt3N;
			return true;
		}
		else if(str=="uint4n")
		{
			*this = GXVertexFormat::UInt4N;
			return true;
		}
		else if(str=="float")
		{
			*this = GXVertexFormat::Float;
			return true;
		}
		else if(str=="float2")
		{
			*this = GXVertexFormat::Float2;
			return true;
		}
		else if(str=="float3")
		{
			*this = GXVertexFormat::Float3;
			return true;
		}
		else if(str=="float4")
		{
			*this = GXVertexFormat::Float4;
			return true;
		}
		else if(str=="half")
		{
			*this = GXVertexFormat::Half;
			return true;
		}
		else if(str=="half2")
		{
			*this = GXVertexFormat::Half2;
			return true;
		}
		else if(str=="half3")
		{
			*this = GXVertexFormat::Half3;
			return true;
		}
		else if(str=="half4")
		{
			*this = GXVertexFormat::Half4;
			return true;
		}
		else
		{
			return false;
		}
	}
private:
	unsigned int numElements;
	unsigned int elementType;
	bool	     normalize;
	unsigned int size;
};

class GXVertexStreamSource
{
public:
	GXVertexStreamSource(unsigned int source_ = 0)
	{
		source  = source_;
	}

	unsigned int getSource() const
	{
		return source;
	}

	bool operator == (const GXVertexStreamSource &other) const
	{
		return this->source == other.source;
	}

	operator int ()
	{
		return source;
	}

	static const GXVertexStreamSource Position;
	static const GXVertexStreamSource Normal;
	static const GXVertexStreamSource Color;
	static const GXVertexStreamSource TexCoord0;
	static const GXVertexStreamSource TexCoord1;
	static const GXVertexStreamSource TexCoord2;
	static const GXVertexStreamSource TexCoord3;
	static const GXVertexStreamSource TexCoord4;
	static const GXVertexStreamSource TexCoord5;
	static const GXVertexStreamSource TexCoord6;
	static const GXVertexStreamSource TexCoord7;
	static const GXVertexStreamSource Tangent;
	static const GXVertexStreamSource Binormal;
	static const GXVertexStreamSource Blend4Index;
	static const GXVertexStreamSource Blend4Weight;
	static const GXVertexStreamSource Blend1Index;

	void read(InputStream &is)
	{
		is >> source;
	}

	void write(OutputStream &os) const
	{
		os << source;
	}

	bool from(const char *name)
	{
		String str = name;
		str.toLower();

		if(str=="position")
		{
			*this = GXVertexStreamSource::Position;
			return true;
		}
		else if(str=="normal")
		{
			*this = GXVertexStreamSource::Normal;
			return true;
		}
		else if(str=="color")
		{
			*this = GXVertexStreamSource::Color;
			return true;
		}
		else if(str=="texcoord0")
		{
			*this = GXVertexStreamSource::TexCoord0;
			return true;
		}
		else if(str=="texcoord1")
		{
			*this = GXVertexStreamSource::TexCoord1;
			return true;
		}
		else if(str=="texcoord2")
		{
			*this = GXVertexStreamSource::TexCoord2;
			return true;
		}
		else if(str=="texcoord3")
		{
			*this = GXVertexStreamSource::TexCoord3;
			return true;
		}
		else if(str=="texcoord4")
		{
			*this = GXVertexStreamSource::TexCoord4;
			return true;
		}
		else if(str=="texcoord5")
		{
			*this = GXVertexStreamSource::TexCoord5;
			return true;
		}
		else if(str=="texcoord6")
		{
			*this = GXVertexStreamSource::TexCoord6;
			return true;
		}
		else if(str=="texcoord7")
		{
			*this = GXVertexStreamSource::TexCoord7;
			return true;
		}
		else if(str=="tangent")
		{
			*this = GXVertexStreamSource::Tangent;
			return true;
		}
		else if(str=="binormal")
		{
			*this = GXVertexStreamSource::Binormal;
			return true;
		}
		else if(str=="blendindex4")
		{
			*this = GXVertexStreamSource::Blend4Index;
			return true;
		}
		else if(str=="blendweight4")
		{
			*this = GXVertexStreamSource::Blend4Weight;
			return true;
		}
		else if(str=="blendindex1")
		{
			*this = GXVertexStreamSource::Blend1Index;
			return true;
		}
		else
			return false;
	}
private:
	unsigned int source;
};

// void checkGLError(const char *name);

};

#endif