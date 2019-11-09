#include "ColorSelector1DWndFiller.h"
#include <math.h>
#include <assert.h>

ColorSelector1DWndFiller::ColorSelector1DWndFiller()
: m_width(0)
, m_height(0)
, m_buffer(0)
, lineBuffer(0)
{
	m_nCurMode = modes_hsv_hue;

	additional_components[0] = 0;
	additional_components[1] = 0;
	additional_components[2] = 0;
	additional_components[3] = 0;
}

ColorSelector1DWndFiller::~ColorSelector1DWndFiller()
{
	if(lineBuffer)
		delete [] lineBuffer;
}

void ColorSelector1DWndFiller::construct(int width, int height, unsigned char *buffer)
{
	lineBuffer  = new unsigned char[1*height*4];

	m_width		= width;
	m_height	= height;
	m_buffer	= buffer;
}

void ColorSelector1DWndFiller::setRedMode(float green, float blue)
{
	m_nCurMode = modes_rgb_red;
	
	additional_components[0] = green * max_rgb_red;
	additional_components[1] = blue  * max_rgb_red;

	DoDrawRGB();
	CopyLineBuffer();
}

void ColorSelector1DWndFiller::setGreenMode(float red, float blue)
{
	m_nCurMode = modes_rgb_green;
	additional_components[0] = red   * max_rgb_red;
	additional_components[1] = blue  * max_rgb_red;

	DoDrawRGB();
	CopyLineBuffer();
}

void ColorSelector1DWndFiller::setBlueMode(float red, float green)
{
	m_nCurMode = modes_rgb_blue;
	additional_components[0] = red   * max_rgb_red;
	additional_components[1] = green * max_rgb_red;

	DoDrawRGB();
	CopyLineBuffer();
}

void ColorSelector1DWndFiller::setHueMode(float sat, float val)
{
	m_nCurMode = modes_hsv_hue;
	additional_components[0] = sat   * scale_hsv_sat;
	additional_components[1] = val	 * scale_hsv_value;

	DoDrawHSV_Hue();
	CopyLineBuffer();
}

void ColorSelector1DWndFiller::setSatMode(float hue, float val)
{
	m_nCurMode = modes_hsv_sat;
	additional_components[0] = hue   * 359.9 * scale_hsv_hue;
	additional_components[1] = val	 * scale_hsv_value;

	DoDrawHSV_Sat();
	CopyLineBuffer();
}

void ColorSelector1DWndFiller::setValMode(float hue, float sat)
{
	m_nCurMode = modes_hsv_value;
	additional_components[0] = hue   * 359.9 * scale_hsv_hue;
	additional_components[1] = sat   * scale_hsv_sat;

	DoDrawHSV_Val();
	CopyLineBuffer();
}

void ColorSelector1DWndFiller::DoDrawRGB()
{
	unsigned long start_color, end_color;
	unsigned char c1, c2;
	
	c1 = (unsigned char) ((int) additional_components [0] * 255 / max_rgb);
	c2 = (unsigned char) ((int) additional_components [1] * 255 / max_rgb);
	
	// setup start and end color depending of current mode
	switch (m_nCurMode & modes_mask)
	{
	case	modes_rgb_red:
		start_color = RGB (0, c1, c2);
		end_color	= RGB (255, c1, c2);
		break;
		
	case	modes_rgb_green:
		start_color = RGB (c1, 0, c2);
		end_color	= RGB (c1, 255, c2);
		break;
		
	case	modes_rgb_blue:
		start_color = RGB (c1, c2, 0);
		end_color	= RGB (c1, c2, 255);
		break;
		
	default:
		assert(false);
		return;
	}
	
	GetRGB(lineBuffer, m_height, start_color, end_color);
}

void ColorSelector1DWndFiller::DoDrawHSV_Hue(void)
{
	HSV_HUE(lineBuffer, m_height,
		additional_components [0] / (double) scale_hsv_sat,
		additional_components [1] / (double) scale_hsv_value);
}

void ColorSelector1DWndFiller::DoDrawHSV_Sat(void)
{
	HSV_SAT(lineBuffer, m_height,
		additional_components [0] / (double) scale_hsv_hue,
		additional_components [1] / (double) scale_hsv_value);
}


void ColorSelector1DWndFiller::DoDrawHSV_Val(void)
{
	HSV_VAL(lineBuffer, m_height,
		additional_components [0] / (double) scale_hsv_hue,
		additional_components [1] / (double) scale_hsv_sat);
}

void ColorSelector1DWndFiller::GetRGB(unsigned char *buffer,int samples,unsigned long start, unsigned long end)
{
	int	red, green, blue;
	int	red_adv, green_adv, blue_adv;

	red			= scaled_red (start);
	green		= scaled_green (start);
	blue		= scaled_blue (start);
	red_adv		= (scaled_red (end) - red) / (samples - 1);
	green_adv	= (scaled_green (end) - green) / (samples - 1);
	blue_adv	= (scaled_blue (end) - blue) / (samples - 1);

	while (samples--)
	{
		// set current pixel (in DIB bitmap format is BGR, not RGB!)
		*buffer++ = (unsigned char) (red >> int_extend);
		*buffer++ = (unsigned char) (green >> int_extend);
		*buffer++ = (unsigned char) (blue >> int_extend);

		// advance color values to the next pixel
		red		+= red_adv;
		green	+= green_adv;
		blue	+= blue_adv;
	}
}

void ColorSelector1DWndFiller::HSV_HUE(unsigned char *buffer,int samples,double sat,double val_fp)
{
	// value, but as integer in [0, 255 << int_extend]
	int		val;

	// loop counter
	int		j;

	// coefficients and advances
	int		coef1, coef2, coef3;
	int		coef2_adv, coef3_adv;

	// current position and advance to the next one
	double	pos, pos_adv;

	//
	// hue increments in [0, 360); indirectly
	//	intp changes - 0, 1, 2, 3, 4, 5; indirectly (separate loops)
	//	frac increments in [0, 1) six times; indirectly (coefficients)
	// sat - const, in [0, 1]
	// val - const, in [0, (255 << int_extend)]
	//
	// coef1 => val * (1 - sat)              => const, = val * (1 - sat)
	// coef2 => val * (1 - sat * frac)       => changes from val to val * (1 - sat)
	// coef3 => val * (1 - sat * (1 - frac)) => changes from val * (1 - sat) to val
	//

	// constants
	val = (int) (val_fp * 255) << int_extend;
	coef1 = (int) (val * (1 - sat));

	// prepare
	pos = 0;
	pos_adv = (double) samples / 6.0;

	// hue in [0, 60)
	pos += pos_adv;
	j = (int) pos;
	HSV_SAT_INIT_0 ();
	while (j--) 
	{
		HSV0(buffer);
		
		HSV_SAT_ADV_0();
	}

	pos += pos_adv;
	j = (int) pos - (int) (1 * pos_adv);
	HSV_SAT_INIT_1 ();
	while (j--) 
	{
		HSV1(buffer);
		
		HSV_SAT_ADV_1();
	}

	pos += pos_adv;
	j = (int) pos - (int) (2 * pos_adv);
	HSV_SAT_INIT_2 ();
	while (j--) 
	{
		HSV2(buffer);
		
		HSV_SAT_ADV_2();
	}

	pos += pos_adv;
	j = (int) pos - (int) (3 * pos_adv);
	HSV_SAT_INIT_3 ();
	while (j--) 
	{
		HSV3(buffer);

		HSV_SAT_ADV_3();
	}

	pos += pos_adv;
	j = (int) pos - (int) (4 * pos_adv);
	HSV_SAT_INIT_4 ();
	while (j--) 
	{
		HSV4(buffer);

		HSV_SAT_ADV_4();
	}

	pos += (pos_adv + 0.1);	// + 0.1 because of floating-point math's rounding errors
	j = (int) pos - (int) (5 * pos_adv);
	HSV_SAT_INIT_5 ();
	while (j--) 
	{
		HSV5(buffer);

		HSV_SAT_ADV_5();
	}
}

void ColorSelector1DWndFiller::HSV_SAT(unsigned char *buffer,int samples,double hue,double val_fp)
{
	// value, but as integer in [0, 255 << int_extend]
	int		val;

	// loop counter
	int		j;

	// coefficients and advances
	signed int		coef1, coef2, coef3;
	signed int		coef1_adv, coef2_adv, coef3_adv;

	double	intp, frac;

	//
	// hue - const, in [0, 360)
	//	intp - const in 0, 1, 2, 3, 4, 5
	//	frac - const in [0, 1)
	// sat - increments, in [0, 1]; indirectly (coefficients)
	// val - const, in [0, (255 << int_extend)]
	//
	// coef1 => val * (1 - sat)              => changes from val to 0
	// coef2 => val * (1 - sat * frac)       => changes from val to val * (1 - frac)
	// coef3 => val * (1 - sat * (1 - frac)) => changes from val to val * frac
	//

	// constants
	val = (int) (val_fp * 255) << int_extend;
	frac = modf (hue / 60.0, &intp);

	// prepare
	j = samples;

	coef1 = val;
	coef1_adv = -coef1 / samples;
	coef2 = val;
	coef2_adv = (int) ((1 - frac) * val - coef2) / samples;
	coef3 = val;
	coef3_adv = (int) (frac * val - coef3) / samples;

	switch ((int) intp)
	{
	case	0:
		while (j--) 
		{
			HSV0(buffer);

			HSV_HUE_ADV_0();
		}
		break;
	case	1:
		while (j--) 
		{
			HSV1(buffer);

			HSV_HUE_ADV_1();
		}
		break;
	case	2:
		while (j--) 
		{
			HSV2(buffer);

			HSV_HUE_ADV_2();
		}
		break;
	case	3:
		while (j--) 
		{
			HSV3(buffer);

			HSV_HUE_ADV_3();
		}
		break;
	case	4:
		while (j--)
		{
			HSV4(buffer);

			HSV_HUE_ADV_4();
		}
		break;
	case	5:
		while (j--)
		{
			HSV5(buffer);
			
			HSV_HUE_ADV_5();
		}
		break;
	}
}

void ColorSelector1DWndFiller::HSV_VAL(unsigned char *buffer,int samples,double hue,double sat)
{
	// loop counter
	int		j;

	// coefficients and advances
	signed int		coef1, coef2, coef3;
	signed int		coef1_adv, coef2_adv, coef3_adv;

	int		val, val_adv;
	int		val_max;

	double	intp, frac;

	//
	// hue - const, in [0, 360)
	//	intp - const in 0, 1, 2, 3, 4, 5
	//	frac - const in [0, 1)
	// sat - const, in [0, 1]
	// val - increments, in [0, (255 << int_extend)]; indirectly (coefficients)
	//
	// coef1 => val * (1 - sat)              => changes from 0 to val * (1 - sat)
	// coef2 => val * (1 - sat * frac)       => changes from 0 to val * (1 - sat * frac)
	// coef3 => val * (1 - sat * (1 - frac)) => changes from 0 to val * (1 - sat * (1 - frac))
	//

	// constants
	frac = modf (hue / 60.0, &intp);
	val_max = 255 << int_extend;

	// prepare
	j = samples;

	coef1 = 0;
	coef1_adv = (int) (val_max * (1 - sat)) / samples;
	coef2 = 0;
	coef2_adv = (int) (val_max * (1 - sat * frac)) / samples;
	coef3 = 0;
	coef3_adv = (int) (val_max * (1 - sat * (1 - frac))) / samples;
	val = 0;
	val_adv = val_max / samples;

	/*
	switch ((int) intp)
	{
	case	0:
		while (j--) *buffer++ = HSV_0 (), HSV_HUE_ADV_0 (), val += val_adv;
		break;
	case	1:
		while (j--) *buffer++ = HSV_1 (), HSV_HUE_ADV_1 (), val += val_adv;
		break;
	case	2:
		while (j--) *buffer++ = HSV_2 (), HSV_HUE_ADV_2 (), val += val_adv;
		break;
	case	3:
		while (j--) *buffer++ = HSV_3 (), HSV_HUE_ADV_3 (), val += val_adv;
		break;
	case	4:
		while (j--) *buffer++ = HSV_4 (), HSV_HUE_ADV_4 (), val += val_adv;
		break;
	case	5:
		while (j--) *buffer++ = HSV_5 (), HSV_HUE_ADV_5 (), val += val_adv;
		break;
	}
	*/

	switch ((int) intp)
	{
	case	0:
		while (j--) 
		{
			HSV0(buffer);

			HSV_HUE_ADV_0();

			val += val_adv;
		}
		break;
	case	1:
		while (j--) 
		{
			HSV1(buffer);

			HSV_HUE_ADV_1();

			val += val_adv;
		}
		break;
	case	2:
		while (j--) 
		{
			HSV2(buffer);

			HSV_HUE_ADV_2();

			val += val_adv;
		}
		break;
	case	3:
		while (j--) 
		{
			HSV3(buffer);

			HSV_HUE_ADV_3();

			val += val_adv;
		}
		break;
	case	4:
		while (j--)
		{
			HSV4(buffer);

			HSV_HUE_ADV_4();

			val += val_adv;
		}
		break;
	case	5:
		while (j--)
		{
			HSV5(buffer);
			
			HSV_HUE_ADV_5();

			val += val_adv;
		}
		break;
	}
}

void ColorSelector1DWndFiller::CopyLineBuffer()
{
	unsigned char *dst = m_buffer;

	for(int y=0; y<m_height; y++)
	{
		unsigned char *src = &(lineBuffer[y*3]);
		for(int x=0; x<m_width; x++)
		{
			*dst++ = *(src+0);
			*dst++ = *(src+1);
			*dst++ = *(src+2);
		}
	}
}