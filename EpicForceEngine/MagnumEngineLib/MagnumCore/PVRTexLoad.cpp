///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Stage.h"
#include "PVRTexLoad.h"

const unsigned int PVRTEX_MIPMAP			= (1<<8);		// has mip map levels
const unsigned int PVRTEX_TWIDDLE			= (1<<9);		// is twiddled
const unsigned int PVRTEX_BUMPMAP			= (1<<10);		// has normals encoded for a bump map
const unsigned int PVRTEX_TILING			= (1<<11);		// is bordered for tiled pvr
const unsigned int PVRTEX_CUBEMAP			= (1<<12);		// is a cubemap/skybox
const unsigned int PVRTEX_FALSEMIPCOL		= (1<<13);		// are there false coloured MIP levels
const unsigned int PVRTEX_VOLUME			= (1<<14);		// is this a volume texture
const unsigned int PVRTEX_ALPHA				= (1<<15);		// v2.1 is there transparency info in the texture
const unsigned int PVRTEX_VERTICAL_FLIP		= (1<<16);		// v2.1 is the texture vertically flipped

const unsigned int PVRTEX_PIXELTYPE			= 0xff;			// pixel type is always in the last 16bits of the flags
const unsigned int PVRTEX_IDENTIFIER		= 0x21525650;	// the pvr identifier is the characters 'P','V','R'

const unsigned int PVRTEX_V1_HEADER_SIZE	= 44;			// old header size was 44 for identification purposes

const unsigned int PVRTC2_MIN_TEXWIDTH		= 16;
const unsigned int PVRTC2_MIN_TEXHEIGHT		= 8;
const unsigned int PVRTC4_MIN_TEXWIDTH		= 8;
const unsigned int PVRTC4_MIN_TEXHEIGHT		= 8;
const unsigned int ETC_MIN_TEXWIDTH			= 4;
const unsigned int ETC_MIN_TEXHEIGHT		= 4;
const unsigned int DXT_MIN_TEXWIDTH			= 4;
const unsigned int DXT_MIN_TEXHEIGHT		= 4;

#define PT_INDEX (2)	// The Punch-through index

#define BLK_Y_SIZE 	(4) // always 4 for all 2D block types

#define BLK_X_MAX	(8)	// Max X dimension for blocks

#define BLK_X_2BPP	(8) // dimensions for the two formats
#define BLK_X_4BPP	(4)

#define WRAP_COORD(Val, Size) ((Val) & ((Size)-1))

#define POWER_OF_2(X)   util_number_is_power_2(X)

/*
	Define an expression to either wrap or clamp large or small vals to the
	legal coordinate range
*/
#define LIMIT_COORD(Val, Size, AssumeImageTiles) \
      ((AssumeImageTiles)? WRAP_COORD((Val), (Size)): PVRT_CLAMP((Val), 0, (Size)-1))

#define PVRT_MIN(a,b)            (((a) < (b)) ? (a) : (b))
#define PVRT_MAX(a,b)            (((a) > (b)) ? (a) : (b))
#define PVRT_CLAMP(x, l, h)      (PVRT_MIN((h), PVRT_MAX((x), (l))))
#define FREE(X)		{ if(X) { free(X); (X) = 0; } }

bool IsGLExtensionSupported(const char *extension)
{
	// The recommended technique for querying OpenGL extensions;
	// from http://opengl.org/resources/features/OGLextensions/
	const GLubyte *extensions = NULL;
	const GLubyte *start;
	GLubyte *where, *terminator;

	/* Extension names should not have spaces. */
	where = (GLubyte *) strchr(extension, ' ');
	if (where || *extension == '\0')
		return 0;

	extensions = glGetString(GL_EXTENSIONS);

	/* It takes a bit of care to be fool-proof about parsing the
	OpenGL extensions string. Don't be fooled by sub-strings, etc. */
	start = extensions;
	for (;;) {
		where = (GLubyte *) strstr((const char *) start, extension);
		if (!where)
			break;
		terminator = where + strlen(extension);
		if (where == start || *(where - 1) == ' ')
			if (*terminator == ' ' || *terminator == '\0')
				return true;
		start = terminator;
	}

	return false;
}

int util_number_is_power_2( unsigned  input )
{
  unsigned minus1;

  if( !input ) return 0;

  minus1 = input - 1;
  return ( (input | minus1) == (input ^ minus1) ) ? 1 : 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	// Uses 64 bits pre block
	unsigned int PackedData[2];
}AMTC_BLOCK_STRUCT;

static void Unpack5554Colour(const AMTC_BLOCK_STRUCT *pBlock,
							 int   ABColours[2][4])
{
	unsigned int RawBits[2];

	int i;

	// Extract A and B
	RawBits[0] = pBlock->PackedData[1] & (0xFFFE); // 15 bits (shifted up by one)
	RawBits[1] = pBlock->PackedData[1] >> 16;	   // 16 bits

	// step through both colours
	for(i = 0; i < 2; i++)
	{
		// If completely opaque
		if(RawBits[i] & (1<<15))
		{
			// Extract R and G (both 5 bit)
			ABColours[i][0] = (RawBits[i] >> 10) & 0x1F;
			ABColours[i][1] = (RawBits[i] >>  5) & 0x1F;

			/*
				The precision of Blue depends on  A or B. If A then we need to
				replicate the top bit to get 5 bits in total
			*/
			ABColours[i][2] = RawBits[i] & 0x1F;
			if(i==0)
			{
				ABColours[0][2] |= ABColours[0][2] >> 4;
			}

			// set 4bit alpha fully on...
			ABColours[i][3] = 0xF;
		}
		else // Else if colour has variable translucency
		{
			/*
				Extract R and G (both 4 bit).
				(Leave a space on the end for the replication of bits
			*/
			ABColours[i][0] = (RawBits[i] >>  (8-1)) & 0x1E;
			ABColours[i][1] = (RawBits[i] >>  (4-1)) & 0x1E;

			// replicate bits to truly expand to 5 bits
			ABColours[i][0] |= ABColours[i][0] >> 4;
			ABColours[i][1] |= ABColours[i][1] >> 4;

			// grab the 3(+padding) or 4 bits of blue and add an extra padding bit
			ABColours[i][2] = (RawBits[i] & 0xF) << 1;

			/*
				expand from 3 to 5 bits if this is from colour A, or 4 to 5 bits if from
				colour B
			*/
			if(i==0)
			{
				ABColours[0][2] |= ABColours[0][2] >> 3;
			}
			else
			{
				ABColours[0][2] |= ABColours[0][2] >> 4;
			}

			// Set the alpha bits to be 3 + a zero on the end
			ABColours[i][3] = (RawBits[i] >> 11) & 0xE;
		}
	}
}

static void	UnpackModulations(const AMTC_BLOCK_STRUCT *pBlock,
							  const int Do2bitMode,
							  int ModulationVals[8][16],
							  int ModulationModes[8][16],
							  int StartX,
							  int StartY)
{
	int BlockModMode;
	unsigned int ModulationBits;

	int x, y;

	BlockModMode= pBlock->PackedData[1] & 1;
	ModulationBits	= pBlock->PackedData[0];

	// if it's in an interpolated mode
	if(Do2bitMode && BlockModMode)
	{
		/*
			run through all the pixels in the block. Note we can now treat all the
			"stored" values as if they have 2bits (even when they didn't!)
		*/
		for(y = 0; y < BLK_Y_SIZE; y++)
		{
			for(x = 0; x < BLK_X_2BPP; x++)
			{
				ModulationModes[y+StartY][x+StartX] = BlockModMode;

				// if this is a stored value...
				if(((x^y)&1) == 0)
				{
					ModulationVals[y+StartY][x+StartX] = ModulationBits & 3;
					ModulationBits >>= 2;
				}
			}
		}
	}
	else if(Do2bitMode) // else if direct encoded 2bit mode - i.e. 1 mode bit per pixel
	{
		for(y = 0; y < BLK_Y_SIZE; y++)
		{
			for(x = 0; x < BLK_X_2BPP; x++)
			{
				ModulationModes[y+StartY][x+StartX] = BlockModMode;

				// double the bits so 0=> 00, and 1=>11
				if(ModulationBits & 1)
				{
					ModulationVals[y+StartY][x+StartX] = 0x3;
				}
				else
				{
					ModulationVals[y+StartY][x+StartX] = 0x0;
				}
				ModulationBits >>= 1;
			}
		}
	}
	else // else its the 4bpp mode so each value has 2 bits
	{
		for(y = 0; y < BLK_Y_SIZE; y++)
		{
			for(x = 0; x < BLK_X_4BPP; x++)
			{
				ModulationModes[y+StartY][x+StartX] = BlockModMode;

				ModulationVals[y+StartY][x+StartX] = ModulationBits & 3;
				ModulationBits >>= 2;
			}
		}
	}

	// make sure nothing is left over
	assert(ModulationBits==0);
}

static int DisableTwiddlingRoutine = 0;

static unsigned int TwiddleUV(unsigned int YSize, unsigned int XSize, unsigned int YPos, unsigned int XPos)
{
	unsigned int Twiddled;

	unsigned int MinDimension;
	unsigned int MaxValue;

	unsigned int SrcBitPos;
	unsigned int DstBitPos;

	int ShiftCount;

	assert(YPos < YSize);
	assert(XPos < XSize);

	assert(POWER_OF_2(YSize));
	assert(POWER_OF_2(XSize));

	if(YSize < XSize)
	{
		MinDimension = YSize;
		MaxValue	 = XPos;
	}
	else
	{
		MinDimension = XSize;
		MaxValue	 = YPos;
	}

	// Nasty hack to disable twiddling
	if(DisableTwiddlingRoutine)
		return (YPos* XSize + XPos);

	// Step through all the bits in the "minimum" dimension
	SrcBitPos = 1;
	DstBitPos = 1;
	Twiddled  = 0;
	ShiftCount = 0;

	while(SrcBitPos < MinDimension)
	{
		if(YPos & SrcBitPos)
		{
			Twiddled |= DstBitPos;
		}

		if(XPos & SrcBitPos)
		{
			Twiddled |= (DstBitPos << 1);
		}


		SrcBitPos <<= 1;
		DstBitPos <<= 2;
		ShiftCount += 1;

	}

	// prepend any unused bits
	MaxValue >>= ShiftCount;

	Twiddled |=  (MaxValue << (2*ShiftCount));

	return Twiddled;
}

static void InterpolateColours(const int ColourP[4],
						  const int ColourQ[4],
						  const int ColourR[4],
						  const int ColourS[4],
						  const int Do2bitMode,
						  const int x,
						  const int y,
						  int Result[4])
{
	int u, v, uscale;
	int k;

	int tmp1, tmp2;

	int P[4], Q[4], R[4], S[4];

	// Copy the colours
	for(k = 0; k < 4; k++)
	{
		P[k] = ColourP[k];
		Q[k] = ColourQ[k];
		R[k] = ColourR[k];
		S[k] = ColourS[k];
	}

	// put the x and y values into the right range
	v = (y & 0x3) | ((~y & 0x2) << 1);

	if(Do2bitMode)
		u = (x & 0x7) | ((~x & 0x4) << 1);
	else
		u = (x & 0x3) | ((~x & 0x2) << 1);

	// get the u and v scale amounts
	v  = v - BLK_Y_SIZE/2;

	if(Do2bitMode)
	{
		u = u - BLK_X_2BPP/2;
		uscale = 8;
	}
	else
	{
		u = u - BLK_X_4BPP/2;
		uscale = 4;
	}

	for(k = 0; k < 4; k++)
	{
		tmp1 = P[k] * uscale + u * (Q[k] - P[k]);
		tmp2 = R[k] * uscale + u * (S[k] - R[k]);

		tmp1 = tmp1 * 4 + v * (tmp2 - tmp1);

		Result[k] = tmp1;
	}

	// Lop off the appropriate number of bits to get us to 8 bit precision
	if(Do2bitMode)
	{
		// do RGB
		for(k = 0; k < 3; k++)
		{
			Result[k] >>= 2;
		}

		Result[3] >>= 1;
	}
	else
	{
		// do RGB  (A is ok)
		for(k = 0; k < 3; k++)
		{
			Result[k] >>= 1;
		}
	}

	// sanity check
	for(k = 0; k < 4; k++)
	{
		assert(Result[k] < 256);
	}


	/*
		Convert from 5554 to 8888

		do RGB 5.3 => 8
	*/
	for(k = 0; k < 3; k++)
	{
		Result[k] += Result[k] >> 5;
	}

	Result[3] += Result[3] >> 4;

	// 2nd sanity check
	for(k = 0; k < 4; k++)
	{
		assert(Result[k] < 256);
	}

}

static void GetModulationValue(int x,
							   int y,
							   const int Do2bitMode,
							   const int ModulationVals[8][16],
							   const int ModulationModes[8][16],
							   int *Mod,
							   int *DoPT)
{
	static const int RepVals0[4] = {0, 3, 5, 8};
	static const int RepVals1[4] = {0, 4, 4, 8};

	int ModVal;

	// Map X and Y into the local 2x2 block
	y = (y & 0x3) | ((~y & 0x2) << 1);

	if(Do2bitMode)
		x = (x & 0x7) | ((~x & 0x4) << 1);
	else
		x = (x & 0x3) | ((~x & 0x2) << 1);

	// assume no PT for now
	*DoPT = 0;

	// extract the modulation value. If a simple encoding
	if(ModulationModes[y][x]==0)
	{
		ModVal = RepVals0[ModulationVals[y][x]];
	}
	else if(Do2bitMode)
	{
		// if this is a stored value
		if(((x^y)&1)==0)
			ModVal = RepVals0[ModulationVals[y][x]];
		else if(ModulationModes[y][x] == 1) // else average from the neighbours if H&V interpolation..
		{
			ModVal = (RepVals0[ModulationVals[y-1][x]] +
					  RepVals0[ModulationVals[y+1][x]] +
					  RepVals0[ModulationVals[y][x-1]] +
					  RepVals0[ModulationVals[y][x+1]] + 2) / 4;
		}
		else if(ModulationModes[y][x] == 2) // else if H-Only
		{
			ModVal = (RepVals0[ModulationVals[y][x-1]] +
					  RepVals0[ModulationVals[y][x+1]] + 1) / 2;
		}
		else // else it's V-Only
		{
			ModVal = (RepVals0[ModulationVals[y-1][x]] +
					  RepVals0[ModulationVals[y+1][x]] + 1) / 2;
		}
	}
	else // else it's 4BPP and PT encoding
	{
		ModVal = RepVals1[ModulationVals[y][x]];

		*DoPT = ModulationVals[y][x] == PT_INDEX;
	}

	*Mod =ModVal;
}

static void Decompress(AMTC_BLOCK_STRUCT *pCompressedData,
				const int Do2bitMode,
				const int XDim,
				const int YDim,
				const int AssumeImageTiles,
				unsigned char* pResultImage)
{
	int x, y;
	int i, j;

	int BlkX, BlkY;
	int BlkXp1, BlkYp1;
	int XBlockSize;
	int BlkXDim, BlkYDim;

	int StartX, StartY;

	int ModulationVals[8][16];
	int ModulationModes[8][16];

	int Mod, DoPT;

	unsigned int uPosition;

	// local neighbourhood of blocks
	AMTC_BLOCK_STRUCT *pBlocks[2][2];

	AMTC_BLOCK_STRUCT *pPrevious[2][2] = {{NULL, NULL}, {NULL, NULL}};

	// Low precision colours extracted from the blocks
	struct
	{
		int Reps[2][4];
	}Colours5554[2][2];

	// Interpolated A and B colours for the pixel
	int ASig[4], BSig[4];

	int Result[4];

	if(Do2bitMode)
		XBlockSize = BLK_X_2BPP;
	else
		XBlockSize = BLK_X_4BPP;

	// For MBX don't allow the sizes to get too small
	BlkXDim = PVRT_MAX(2, XDim / XBlockSize);
	BlkYDim = PVRT_MAX(2, YDim / BLK_Y_SIZE);

	/*
		Step through the pixels of the image decompressing each one in turn

		Note that this is a hideously inefficient way to do this!
	*/
	for(y = 0; y < YDim; y++)
	{
		for(x = 0; x < XDim; x++)
		{
			// map this pixel to the top left neighbourhood of blocks
			BlkX = (x - XBlockSize/2);
			BlkY = (y - BLK_Y_SIZE/2);

			BlkX = LIMIT_COORD(BlkX, XDim, AssumeImageTiles);
			BlkY = LIMIT_COORD(BlkY, YDim, AssumeImageTiles);


			BlkX /= XBlockSize;
			BlkY /= BLK_Y_SIZE;

			// compute the positions of the other 3 blocks
			BlkXp1 = LIMIT_COORD(BlkX+1, BlkXDim, AssumeImageTiles);
			BlkYp1 = LIMIT_COORD(BlkY+1, BlkYDim, AssumeImageTiles);

			// Map to block memory locations
			pBlocks[0][0] = pCompressedData +TwiddleUV(BlkYDim, BlkXDim, BlkY, BlkX);
			pBlocks[0][1] = pCompressedData +TwiddleUV(BlkYDim, BlkXDim, BlkY, BlkXp1);
			pBlocks[1][0] = pCompressedData +TwiddleUV(BlkYDim, BlkXDim, BlkYp1, BlkX);
			pBlocks[1][1] = pCompressedData +TwiddleUV(BlkYDim, BlkXDim, BlkYp1, BlkXp1);


			/*
				extract the colours and the modulation information IF the previous values
				have changed.
			*/
			if(memcmp(pPrevious, pBlocks, 4*sizeof(void*)) != 0)
			{
				StartY = 0;
				for(i = 0; i < 2; i++)
				{
					StartX = 0;
					for(j = 0; j < 2; j++)
					{
						Unpack5554Colour(pBlocks[i][j], Colours5554[i][j].Reps);

						UnpackModulations(pBlocks[i][j],
										  Do2bitMode,
										  ModulationVals,
										  ModulationModes,
										  StartX, StartY);

						StartX += XBlockSize;
					}

					StartY += BLK_Y_SIZE;
				}

				// make a copy of the new pointers
				memcpy(pPrevious, pBlocks, 4*sizeof(void*));
			}

			// decompress the pixel.  First compute the interpolated A and B signals
			InterpolateColours(Colours5554[0][0].Reps[0],
							   Colours5554[0][1].Reps[0],
							   Colours5554[1][0].Reps[0],
							   Colours5554[1][1].Reps[0],
							   Do2bitMode, x, y,
							   ASig);

			InterpolateColours(Colours5554[0][0].Reps[1],
							   Colours5554[0][1].Reps[1],
							   Colours5554[1][0].Reps[1],
							   Colours5554[1][1].Reps[1],
							   Do2bitMode, x, y,
							   BSig);

			GetModulationValue(x,y, Do2bitMode, (const int (*)[16])ModulationVals, (const int (*)[16])ModulationModes,
							   &Mod, &DoPT);

			// compute the modulated colour
			for(i = 0; i < 4; i++)
			{
				Result[i] = ASig[i] * 8 + Mod * (BSig[i] - ASig[i]);
				Result[i] >>= 3;
			}

			if(DoPT)
				Result[3] = 0;

			// Store the result in the output image
			uPosition = (x+y*XDim)<<2;
			pResultImage[uPosition+0] = (unsigned char)Result[0];
			pResultImage[uPosition+1] = (unsigned char)Result[1];
			pResultImage[uPosition+2] = (unsigned char)Result[2];
			pResultImage[uPosition+3] = (unsigned char)Result[3];
		}
	}
}

void PVRTDecompressPVRTC(const void *pCompressedData,
				const int Do2bitMode,
				const int XDim,
				const int YDim,
				unsigned char* pResultImage)
{
	Decompress((AMTC_BLOCK_STRUCT*)pCompressedData,Do2bitMode,XDim,YDim,1,pResultImage);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define _CLAMP_(X,Xmin,Xmax) (  (X)<(Xmax) ?  (  (X)<(Xmin)?(Xmin):(X)  )  : (Xmax)    )

/*****************************************************************************
Constants
******************************************************************************/
unsigned int ETC_FLIP =  0x01000000;
unsigned int ETC_DIFF = 0x02000000;
const int mod[8][4]={{2, 8,-2,-8},
					{5, 17, -5, -17},
					{9, 29, -9, -29},
					{13, 42, -13, -42},
					{18, 60, -18, -60},
					{24, 80, -24, -80},
					{33, 106, -33, -106},
					{47, 183, -47, -183}};

unsigned long modifyPixel(int red, int green, int blue, int x, int y, unsigned long modBlock, int modTable)
{
	int index = x*4+y, pixelMod;
	unsigned long mostSig = modBlock<<1;

	if (index<8)
		pixelMod = mod[modTable][((modBlock>>(index+24))&0x1)+((mostSig>>(index+8))&0x2)];
	else
		pixelMod = mod[modTable][((modBlock>>(index+8))&0x1)+((mostSig>>(index-8))&0x2)];

	red = _CLAMP_(red+pixelMod,0,255);
	green = _CLAMP_(green+pixelMod,0,255);
	blue = _CLAMP_(blue+pixelMod,0,255);

	return ((red<<16) + (green<<8) + blue)|0xff000000;
}

int ETCTextureDecompress(const void * const pSrcData, const int &x, const int &y, const void *pDestData,const int &/*nMode*/)
{
	unsigned long blockTop, blockBot, *input = (unsigned long*)pSrcData, *output;
	unsigned char red1, green1, blue1, red2, green2, blue2;
	bool bFlip, bDiff;
	int modtable1,modtable2;

	for(int i=0;i<y;i+=4)
	{
		for(int m=0;m<x;m+=4)
		{
				blockTop = *(input++);
				blockBot = *(input++);

			output = (unsigned long*)pDestData + i*x +m;

			// check flipbit
			bFlip = (blockTop & ETC_FLIP) != 0;
			bDiff = (blockTop & ETC_DIFF) != 0;

			if(bDiff)
			{	// differential mode 5 colour bits + 3 difference bits
				// get base colour for subblock 1
				blue1 = (unsigned char)((blockTop&0xf80000)>>16);
				green1 = (unsigned char)((blockTop&0xf800)>>8);
				red1 = (unsigned char)(blockTop&0xf8);

				// get differential colour for subblock 2
				signed char blues = (signed char)(blue1>>3) + ((signed char) ((blockTop & 0x70000) >> 11)>>5);
				signed char greens = (signed char)(green1>>3) + ((signed char)((blockTop & 0x700) >>3)>>5);
				signed char reds = (signed char)(red1>>3) + ((signed char)((blockTop & 0x7)<<5)>>5);

				blue2 = (unsigned char)blues;
				green2 = (unsigned char)greens;
				red2 = (unsigned char)reds;

				red1 = red1 +(red1>>5);	// copy bits to lower sig
				green1 = green1 + (green1>>5);	// copy bits to lower sig
				blue1 = blue1 + (blue1>>5);	// copy bits to lower sig

				red2 = (red2<<3) +(red2>>2);	// copy bits to lower sig
				green2 = (green2<<3) + (green2>>2);	// copy bits to lower sig
				blue2 = (blue2<<3) + (blue2>>2);	// copy bits to lower sig
			}
			else
			{	// individual mode 4 + 4 colour bits
				// get base colour for subblock 1
				blue1 = (unsigned char)((blockTop&0xf00000)>>16);
				blue1 = blue1 +(blue1>>4);	// copy bits to lower sig
				green1 = (unsigned char)((blockTop&0xf000)>>8);
				green1 = green1 + (green1>>4);	// copy bits to lower sig
				red1 = (unsigned char)(blockTop&0xf0);
				red1 = red1 + (red1>>4);	// copy bits to lower sig

				// get base colour for subblock 2
				blue2 = (unsigned char)((blockTop&0xf0000)>>12);
				blue2 = blue2 +(blue2>>4);	// copy bits to lower sig
				green2 = (unsigned char)((blockTop&0xf00)>>4);
				green2 = green2 + (green2>>4);	// copy bits to lower sig
				red2 = (unsigned char)((blockTop&0xf)<<4);
				red2 = red2 + (red2>>4);	// copy bits to lower sig
			}
			// get the modtables for each subblock
			modtable1 = (blockTop>>29)&0x7;
			modtable2 = (blockTop>>26)&0x7;

			if(!bFlip)
			{	// 2 2x4 blocks side by side

				for(int j=0;j<4;j++)	// vertical
				{
					for(int k=0;k<2;k++)	// horizontal
					{
						*(output+j*x+k) = modifyPixel(red1,green1,blue1,k,j,blockBot,modtable1);
						*(output+j*x+k+2) = modifyPixel(red2,green2,blue2,k+2,j,blockBot,modtable2);
					}
				}

			}
			else
			{	// 2 4x2 blocks on top of each other
				for(int j=0;j<2;j++)
				{
					for(int k=0;k<4;k++)
					{
						*(output+j*x+k) = modifyPixel(red1,green1,blue1,k,j,blockBot,modtable1);
						*(output+(j+2)*x+k) = modifyPixel(red2,green2,blue2,k,j+2,blockBot,modtable2);
					}
				}
			}
		}
	}

	return x*y/2;
}

int PVRTDecompressETC(const void * const pSrcData,
						 const unsigned int &x,
						 const unsigned int &y,
						 void *pDestData,
						 const int &nMode)
{
	int i32read;

	if(x<ETC_MIN_TEXWIDTH || y<ETC_MIN_TEXHEIGHT)
	{	// decompress into a buffer big enough to take the minimum size
		char* pTempBuffer =	(char*)malloc(PVRT_MAX(x,ETC_MIN_TEXWIDTH)*PVRT_MAX(y,ETC_MIN_TEXHEIGHT)*4);
		i32read = ETCTextureDecompress(pSrcData,PVRT_MAX(x,ETC_MIN_TEXWIDTH),PVRT_MAX(y,ETC_MIN_TEXHEIGHT),pTempBuffer,nMode);

		for(unsigned int i=0;i<y;i++)
		{	// copy from larger temp buffer to output data
			memcpy((char*)(pDestData)+i*x*4,pTempBuffer+PVRT_MAX(x,ETC_MIN_TEXWIDTH)*4*i,x*4);
		}

		if(pTempBuffer) free(pTempBuffer);
	}
	else	// decompress larger MIP levels straight into the output data
		i32read = ETCTextureDecompress(pSrcData,x,y,pDestData,nMode);

	// swap r and b channels
	unsigned char* pSwap = (unsigned char*)pDestData, swap;

	for(unsigned int i=0;i<y;i++)
		for(unsigned int j=0;j<x;j++)
		{
			swap = pSwap[0];
			pSwap[0] = pSwap[2];
			pSwap[2] = swap;
			pSwap+=4;
		}

	return i32read;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int PVRTTextureLoadFromPointer(const void* pointer, bool bAllowDecompress, 
									    int &width, int &height, GXPixelFormat &format, int &levelCount)
{
	unsigned int nLoadFromLevel = 0;

	PVR_Texture_Header *psPVRHeader = (PVR_Texture_Header*)pointer;
	unsigned int u32NumSurfs;

	// perform checks for old PVR psPVRHeader
	if(psPVRHeader->dwHeaderSize!=sizeof(PVR_Texture_Header))
	{	// Header V1
		if(psPVRHeader->dwHeaderSize==PVRTEX_V1_HEADER_SIZE)
		{	// react to old psPVRHeader: i.e. fill in numsurfs as this is missing from old header
			debug("PVRTTextureLoadFromPointer warning: this is an old pvr - you can use PVRTexTool to update its header.\n");
			if(psPVRHeader->dwpfFlags&PVRTEX_CUBEMAP)
				u32NumSurfs = 6;
			else
				u32NumSurfs = 1;
		}
		else
		{	// not a pvr at all
			debug("PVRTTextureLoadFromPointer failed: not a valid pvr.\n");
			return 0;
		}
	}
	else
	{	// Header V2
		if(psPVRHeader->dwNumSurfs<1)
		{	// encoded with old version of PVRTexTool before zero numsurfs bug found.
			if(psPVRHeader->dwpfFlags & PVRTEX_CUBEMAP)
				u32NumSurfs = 6;
			else
				u32NumSurfs = 1;
		}
		else
		{
			u32NumSurfs = psPVRHeader->dwNumSurfs;
		}
	}

	GLuint textureName				= 0;
	GLenum eTextureFormat			= 0;
	GLenum eTextureInternalFormat	= 0;	// often this is the same as textureFormat, but not for BGRA8888 on the iPhone, for instance
	GLenum eTextureType				= 0;
	GLenum eTarget;

#ifdef USE_GLES20

	bool bIsPVRTCSupported = IsGLExtensionSupported("GL_IMG_texture_compression_pvrtc");
#ifndef TARGET_OS_IPHONE
	bool bIsBGRA8888Supported  = IsGLExtensionSupported("GL_IMG_texture_format_BGRA8888");
#else
	bool bIsBGRA8888Supported  = false;
#endif
	bool bIsFloat16Supported = IsGLExtensionSupported("GL_OES_texture_half_float");
	bool bIsFloat32Supported = IsGLExtensionSupported("GL_OES_texture_float");
#ifndef TARGET_OS_IPHONE
	bool bIsETCSupported = IsGLExtensionSupported("GL_OES_compressed_ETC1_RGB8_texture");
#else
	bool bIsETCSupported = false;
#endif
	bool bIsCompressedFormatSupported = false, bIsCompressedFormat = false;

#else

	bool bIsPVRTCSupported = false;
#ifndef TARGET_OS_IPHONE
	bool bIsBGRA8888Supported  = IsGLExtensionSupported("GL_IMG_texture_format_BGRA8888");
#else
	bool bIsBGRA8888Supported  = false;
#endif
	bool bIsFloat16Supported = false;
	bool bIsFloat32Supported = false;
#ifndef TARGET_OS_IPHONE
	bool bIsETCSupported = IsGLExtensionSupported("GL_OES_compressed_ETC1_RGB8_texture");
#else
	bool bIsETCSupported = false;
#endif
	bool bIsCompressedFormatSupported = false, bIsCompressedFormat = false;

#endif

	/* Only accept untwiddled data UNLESS texture format is PVRTC */
	if ( ((psPVRHeader->dwpfFlags & PVRTEX_TWIDDLE) == PVRTEX_TWIDDLE)
		&& ((psPVRHeader->dwpfFlags & PVRTEX_PIXELTYPE)!=OGL_PVRTC2)
		&& ((psPVRHeader->dwpfFlags & PVRTEX_PIXELTYPE)!=OGL_PVRTC4) )
	{
		// We need to load untwiddled textures -- GL will twiddle for us.
		debug("PVRTTextureLoadFromPointer failed: texture should be untwiddled.\n");
		return 0;
	}

	width		= psPVRHeader->dwWidth;
	height		= psPVRHeader->dwHeight;
		
	PixelType ePixelType = (PixelType)(psPVRHeader->dwpfFlags & PVRTEX_PIXELTYPE);
	switch(ePixelType)
	{
	case OGL_RGBA_4444:
		eTextureFormat	= eTextureInternalFormat = GL_RGBA;
		eTextureType	= GL_UNSIGNED_SHORT_4_4_4_4;
		
		format			= GXPixelFormat::R4G4B4A4;
		break;

	case OGL_RGBA_5551:
		eTextureFormat	= eTextureInternalFormat = GL_RGBA;
		eTextureType	= GL_UNSIGNED_SHORT_5_5_5_1;

		format			= GXPixelFormat::R5G5B5A1;
		break;

	case OGL_RGBA_8888:
		eTextureFormat	= eTextureInternalFormat = GL_RGBA;
		eTextureType	= GL_UNSIGNED_BYTE;

		format			= GXPixelFormat::R8G8B8A8;
		break;

		/* New OGL Specific Formats Added */

	case OGL_RGB_565:
		eTextureFormat	= eTextureInternalFormat = GL_RGB;
		eTextureType	= GL_UNSIGNED_SHORT_5_6_5;

		format			= GXPixelFormat::R5G6B5;

		break;

	case OGL_RGB_555:
		debug("PVRTTextureLoadFromPointer failed: pixel type OGL_RGB_555 not supported.\n");
		return 0;

	case OGL_RGB_888:
		eTextureFormat	= eTextureInternalFormat = GL_RGB;
		eTextureType	= GL_UNSIGNED_BYTE;

		format			= GXPixelFormat::R8G8B8;
		break;

	case OGL_I_8:
		eTextureFormat	= eTextureInternalFormat = GL_LUMINANCE;
		eTextureType	= GL_UNSIGNED_BYTE;

		format			= GXPixelFormat::I8;
		break;

	case OGL_AI_88:
		eTextureFormat	= eTextureInternalFormat = GL_LUMINANCE_ALPHA;
		eTextureType	= GL_UNSIGNED_BYTE;

		format			= GXPixelFormat::AI8;
		break;

	case MGLPT_PVRTC2:
	case OGL_PVRTC2:
		if(bIsPVRTCSupported)
		{
#ifdef USE_GLES20
			bIsCompressedFormatSupported = bIsCompressedFormat = true;
			eTextureFormat = psPVRHeader->dwAlphaBitMask==0 ? GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG : GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG ;	// PVRTC2

			format		   = psPVRHeader->dwAlphaBitMask==0 ? GXPixelFormat::RGB_PVRTC2 : GXPixelFormat::RGBA_PVRTC2;
#else
			assert(0);
#endif
		}
		else
		{
			if(bAllowDecompress)
			{
				bIsCompressedFormatSupported	= false;
				bIsCompressedFormat				= true;
				eTextureFormat					= eTextureInternalFormat = GL_RGBA;
				eTextureType					= GL_UNSIGNED_BYTE;

				format							= GXPixelFormat::R8G8B8A8;

				debug("PVRTTextureLoadFromPointer warning: PVRTC2 not supported. Converting to RGBA8888 instead.\n");
			}
			else
			{
				debug("PVRTTextureLoadFromPointer error: PVRTC2 not supported.\n");
				return 0;
			}
		}
		break;

	case MGLPT_PVRTC4:
	case OGL_PVRTC4:
		if(bIsPVRTCSupported)
		{
#ifdef USE_GLES20
			bIsCompressedFormatSupported = bIsCompressedFormat = true;
			eTextureFormat = psPVRHeader->dwAlphaBitMask==0 ? GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG : GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG ;	// PVRTC4

			format		   = psPVRHeader->dwAlphaBitMask==0 ? GXPixelFormat::RGB_PVRTC4 : GXPixelFormat::RGBA_PVRTC4;
#else
			assert(0);
#endif
		}
		else
		{
			if(bAllowDecompress)
			{
				bIsCompressedFormatSupported	= false;
				bIsCompressedFormat				= true;
				eTextureFormat					= eTextureInternalFormat = GL_RGBA;
				eTextureType					= GL_UNSIGNED_BYTE;

				format							= GXPixelFormat::R8G8B8A8;
				
				debug("PVRTTextureLoadFromPointer warning: PVRTC4 not supported. Converting to RGBA8888 instead.\n");
			}
			else
			{
				debug("PVRTTextureLoadFromPointer error: PVRTC4 not supported.\n");
				return 0;
			}
		}
		break;
	case OGL_A_8:
		eTextureFormat	= eTextureInternalFormat = GL_ALPHA;
		eTextureType	= GL_UNSIGNED_BYTE;

		format			= GXPixelFormat::A8;
		break;
		/*
	case OGL_BGRA_8888:
		if(bIsBGRA8888Supported)
		{
		eTextureType = GL_UNSIGNED_BYTE;
		#ifndef __APPLE__
		eTextureFormat = eTextureInternalFormat = GL_BGRA;
		#else
		eTextureFormat = GL_BGRA;
		eTextureInternalFormat = GL_RGBA;
		#endif
		}
		else
		{
		// debug("PVRTTextureLoadFromPointer failed: Unable to load GL_BGRA texture as extension GL_IMG_texture_format_BGRA8888 is unsupported.\n");
		return 0;
		}
		break;
		*/
	case D3D_ABGR_16161616F:
		if(bIsFloat16Supported)
		{
#ifdef USE_GLES20
			eTextureFormat	= eTextureInternalFormat =  GL_RGBA;
			eTextureType	= GL_HALF_FLOAT_OES;

			format			= GXPixelFormat::R16G16B16A16;
#else
			assert(0);
#endif
		}
		break;
	case D3D_ABGR_32323232F:
		if(bIsFloat32Supported)
		{
			eTextureFormat	= eTextureInternalFormat =  GL_RGBA ;
			eTextureType	= GL_FLOAT;

			format			= GXPixelFormat::R32G32B32A32;
		}
		break;

	case ETC_RGB_4BPP:
		// if(bIsETCSupported)
        if(false)
		{
            /*
			bIsCompressedFormatSupported = bIsCompressedFormat = true;
			eTextureFormat				 = GL_ETC1_RGB8_OES;

			format						 = GXPixelFormat::RGB_ETC;
            */
		}
		else
		{
			if(bAllowDecompress)
			{
				bIsCompressedFormatSupported	= false;
				bIsCompressedFormat				= true;
				eTextureFormat					= GL_RGBA;
				eTextureType					= GL_UNSIGNED_BYTE;

				format							= GXPixelFormat::R8G8B8A8;
				
				debug("PVRTTextureLoadFromPointer warning: ETC not supported. Converting to RGBA8888 instead.\n");
			}
			else
			{
				debug("PVRTTextureLoadFromPointer error: ETC not supported.\n");
				return 0;
			}
		}
		break;

	default:											// NOT SUPPORTED
		debug("PVRTTextureLoadFromPointer failed: pixel type not supported.\n");
		return 0;
	}


	// load the texture up
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);				// Never have row-aligned in psPVRHeaders

	glGenTextures(1, &textureName);

	//  check that this data is cube map data or not.
	int oldTextureHandle;
	if(psPVRHeader->dwpfFlags & PVRTEX_CUBEMAP)
	{
		eTarget = GL_TEXTURE_CUBE_MAP;

		glGetIntegerv(GL_TEXTURE_BINDING_CUBE_MAP, &oldTextureHandle);
	}
	else
	{
		eTarget = GL_TEXTURE_2D;

		glGetIntegerv(GL_TEXTURE_BINDING_2D		 , &oldTextureHandle);
	}

	glBindTexture(eTarget, textureName);

	if(glGetError())
	{
		debug("PVRTTextureLoadFromPointer failed: glBindTexture() failed.\n");
		return 0;
	}

	for(unsigned int i=0; i<u32NumSurfs; i++)
	{
		char	*theTexturePtr = (char*)(psPVRHeader) + psPVRHeader->dwHeaderSize + psPVRHeader->dwTextureDataSize * i;
		char	*theTextureToLoad = 0;
		unsigned int		nSizeX= psPVRHeader->dwWidth, nSizeY = psPVRHeader->dwHeight;
		unsigned int		CompressedImageSize = 0;
		int		nMIPMapLevel;
		int		nTextureLevelsNeeded = (psPVRHeader->dwpfFlags & PVRTEX_MIPMAP)? psPVRHeader->dwMipMapCount : 0;
		levelCount	= nTextureLevelsNeeded;

		for(nMIPMapLevel = 0; nMIPMapLevel <= nTextureLevelsNeeded; nSizeX=PVRT_MAX(nSizeX/2, (unsigned int)1), nSizeY=PVRT_MAX(nSizeY/2, (unsigned int)1), nMIPMapLevel++)
		{
			theTextureToLoad = theTexturePtr;

			// Load the Texture

			// If the texture is PVRTC or ETC then use GLCompressedTexImage2D
			if(bIsCompressedFormat)
			{
				/* Calculate how many bytes this MIP level occupies */
				if ((psPVRHeader->dwpfFlags & PVRTEX_PIXELTYPE)==OGL_PVRTC2)
				{
					CompressedImageSize = ( PVRT_MAX(nSizeX, PVRTC2_MIN_TEXWIDTH) * PVRT_MAX(nSizeY, PVRTC2_MIN_TEXHEIGHT) * psPVRHeader->dwBitCount) / 8;
				}
				else if ((psPVRHeader->dwpfFlags & PVRTEX_PIXELTYPE)==OGL_PVRTC4)
				{
					CompressedImageSize = ( PVRT_MAX(nSizeX, PVRTC4_MIN_TEXWIDTH) * PVRT_MAX(nSizeY, PVRTC4_MIN_TEXHEIGHT) * psPVRHeader->dwBitCount) / 8;
				}
				else
				{// ETC
					CompressedImageSize = ( PVRT_MAX(nSizeX, ETC_MIN_TEXWIDTH) * PVRT_MAX(nSizeY, ETC_MIN_TEXHEIGHT) * psPVRHeader->dwBitCount) / 8;
				}

				if(((signed int)nMIPMapLevel - (signed int)nLoadFromLevel) >= 0)
				{
					if(bIsCompressedFormatSupported)
					{
						if(psPVRHeader->dwpfFlags&PVRTEX_CUBEMAP)
						{
							// Load compressed texture data at selected MIP level
							glCompressedTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, nMIPMapLevel-nLoadFromLevel, eTextureFormat, nSizeX, nSizeY, 0,
												   CompressedImageSize, theTextureToLoad);
						}
						else
						{
							// Load compressed texture data at selected MIP level
							glCompressedTexImage2D(GL_TEXTURE_2D, nMIPMapLevel-nLoadFromLevel, eTextureFormat, nSizeX, nSizeY, 0,
											       CompressedImageSize, theTextureToLoad);
						}
					}
					else
					{
						// Convert PVRTC to 32-bit
						unsigned char *u8TempTexture = (unsigned char*)malloc(nSizeX*nSizeY*4);
						if ((psPVRHeader->dwpfFlags & PVRTEX_PIXELTYPE)==OGL_PVRTC2)
						{
							PVRTDecompressPVRTC(theTextureToLoad, 1, nSizeX, nSizeY, u8TempTexture);
						}
						else if((psPVRHeader->dwpfFlags & PVRTEX_PIXELTYPE)==OGL_PVRTC4)
						{
							PVRTDecompressPVRTC(theTextureToLoad, 0, nSizeX, nSizeY, u8TempTexture);
						}
						else
						{	// ETC
							PVRTDecompressETC(theTextureToLoad, nSizeX, nSizeY, u8TempTexture, 0);
						}

						if(psPVRHeader->dwpfFlags&PVRTEX_CUBEMAP)
						{
							// Load compressed cubemap data at selected MIP level
							// Upload the texture as 32-bits

							glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,nMIPMapLevel-nLoadFromLevel,GL_RGBA, nSizeX,nSizeY,0, GL_RGBA,GL_UNSIGNED_BYTE,u8TempTexture);

							FREE(u8TempTexture);
						}
						else
						{
							// Load compressed 2D data at selected MIP level
							// Upload the texture as 32-bits

							glTexImage2D(GL_TEXTURE_2D,nMIPMapLevel-nLoadFromLevel,GL_RGBA, nSizeX,nSizeY,0, GL_RGBA,GL_UNSIGNED_BYTE,u8TempTexture);

							FREE(u8TempTexture);
						}
					}
				}
			}
			else
			{
				if(((signed int)nMIPMapLevel - (signed int)nLoadFromLevel) >= 0)
				{
					if(psPVRHeader->dwpfFlags & PVRTEX_CUBEMAP)
					{
						// Load uncompressed texture data at selected MIP level
						glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,nMIPMapLevel-nLoadFromLevel,eTextureInternalFormat,nSizeX,nSizeY, 0, eTextureFormat,eTextureType,theTextureToLoad);
					}
					else
					{
						// Load uncompressed texture data at selected MIP level
						glTexImage2D(GL_TEXTURE_2D,nMIPMapLevel-nLoadFromLevel,eTextureInternalFormat,nSizeX,nSizeY,0,eTextureFormat,eTextureType,theTextureToLoad);
					}
				}
			}
			
			if(glGetError())
			{
				debug("PVRTTextureLoadFromPointer failed: glTexImage2D() failed.\n");
				return 0;
			}

			// offset the texture pointer by one mip-map level

			/* PVRTC case */
			if ( bIsCompressedFormat )
			{
				theTexturePtr += CompressedImageSize;
			}
			else
			{
				/* New formula that takes into account bit counts inferior to 8 (e.g. 1 bpp) */
				theTexturePtr += (nSizeX * nSizeY * psPVRHeader->dwBitCount + 7) / 8;
			}
		}
	}

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(eTarget, oldTextureHandle);

	/*
	if(psTextureHeader)
	{
		*(PVR_Texture_Header*)psTextureHeader = *psPVRHeader;
		((PVR_Texture_Header*)psTextureHeader)->dwPVR = PVRTEX_IDENTIFIER;
		((PVR_Texture_Header*)psTextureHeader)->dwNumSurfs = u32NumSurfs;
	}

	if(eTextureType==GL_FLOAT || eTextureType==GL_HALF_FLOAT_OES)
	{
		if(!psPVRHeader->dwMipMapCount)
		{	// Texture filter modes are limited to these for float textures
			glTexParameteri(eTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(eTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}
		else
		{
			glTexParameteri(eTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
			glTexParameteri(eTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}
	}
	else
	{
		if(!psPVRHeader->dwMipMapCount)
		{
			glTexParameteri(eTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(eTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		else
		{
			glTexParameteri(eTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			glTexParameteri(eTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
	}

	if(
		(psPVRHeader->dwWidth & (psPVRHeader->dwWidth - 1)) |
		(psPVRHeader->dwHeight & (psPVRHeader->dwHeight - 1)))
	{
		// NPOT textures requires the wrap mode to be set explicitly to
		// GL_CLAMP_TO_EDGE or the texture will be inconsistent.
		glTexParameteri(eTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(eTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	*/

	return textureName;
}