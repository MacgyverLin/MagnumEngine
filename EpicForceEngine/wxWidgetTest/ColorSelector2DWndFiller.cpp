#include "ColorSelector2DWndFiller.h"
#include <math.h>

ColorSelector2DWndFiller::ColorSelector2DWndFiller()
: m_width(0)
, m_height(0)
, m_buffer(0)
{
	m_nCurMode = modes_hsv_hue;
	additional_component = 0;	
}

ColorSelector2DWndFiller::~ColorSelector2DWndFiller()
{
}

void ColorSelector2DWndFiller::construct(int width, int height, unsigned char *buffer)
{
	m_width		= width;
	m_height	= height;
	m_buffer	= buffer;
}

void ColorSelector2DWndFiller::setRedMode(float red)
{
	m_nCurMode = modes_rgb_red;
	additional_component = red * max_rgb_red; // 0- 255

	DoDrawRGB();
}

void ColorSelector2DWndFiller::setGreenMode(float green)
{
	m_nCurMode = modes_rgb_green;
	additional_component = green * max_rgb_green;// 0- 255

	DoDrawRGB();
}

void ColorSelector2DWndFiller::setBlueMode(float blue)
{
	m_nCurMode = modes_rgb_blue;
	additional_component = blue * max_rgb_blue;// 0- 255

	DoDrawRGB();
}

void ColorSelector2DWndFiller::setHueMode(float hue)
{
	m_nCurMode = modes_hsv_hue;
	additional_component = hue * 359.9 * scale_hsv_hue;// 0- 359

	DoDrawHSV_Hue();
}

void ColorSelector2DWndFiller::setSatMode(float sat)
{
	m_nCurMode = modes_hsv_sat;
	additional_component = sat * scale_hsv_sat; // 0 -1

	DoDrawHSV_Sat();
}

void ColorSelector2DWndFiller::setValMode(float val)
{
	m_nCurMode = modes_hsv_value;
	additional_component = val * scale_hsv_value; // 0 -1

	DoDrawHSV_Val();
}

void ColorSelector2DWndFiller::DoCalculateColors(unsigned long &lefttop,unsigned long &righttop,unsigned long &leftbottom,unsigned long &rightbottom)
{
	unsigned char c = (unsigned char) ((int) additional_component * 255 / max_rgb);
	
	switch (m_nCurMode)
	{
	case	modes_rgb_red:
		lefttop = RGB (c, 255, 0);
		righttop = RGB (c, 255, 255);
		leftbottom = RGB (c, 0, 0);
		rightbottom = RGB (c, 0, 255);
		break;
		
	case	modes_rgb_green:
		lefttop = RGB (255, c, 0);
		righttop = RGB (255, c, 255);
		leftbottom = RGB (0, c, 0);
		rightbottom = RGB (0, c, 255);
		break;
		
	case	modes_rgb_blue:
		lefttop = RGB (0, 255, c);
		righttop = RGB (255, 255, c);
		leftbottom = RGB (0, 0, c);
		rightbottom = RGB (255, 0, c);
		break;
	}
}


void ColorSelector2DWndFiller::DoDrawRGB()
{
	int		i;		// loop counters
	int		j;
	
	int		nSkip;	// number of pixels to skip after current row and before next one
	
	unsigned char *p;		// pointer to first pixel from the blend & a loop pointer
	
	int		blend_width		= m_width;
	int		blend_height	= m_height;
	
	// left side components, extended with int_extend bits
	int		left_red, left_green, left_blue;
	// left side component advance, extended with int_extend bits
	int		left_red_adv, left_green_adv, left_blue_adv;
	int		right_red, right_green, right_blue;
	int		right_red_adv, right_green_adv, right_blue_adv;
	
	// current components, extended with int_extend bits
	int		red, green, blue;
	// advance, extended with int_extend bits
	int		red_adv, green_adv, blue_adv;
	
	unsigned long	lefttop, righttop, leftbottom, rightbottom;
	
	p = m_buffer;
	nSkip = 0;
	
	DoCalculateColors (lefttop, righttop, leftbottom, rightbottom);
	
	left_red = scaled_red (leftbottom);
	left_green = scaled_green (leftbottom);
	left_blue = scaled_blue (leftbottom);
	left_red_adv = (scaled_red (lefttop) - left_red) / (blend_height - 1);
	left_green_adv = (scaled_green (lefttop) - left_green) / (blend_height - 1);
	left_blue_adv = (scaled_blue (lefttop) - left_blue) / (blend_height - 1);
	
	right_red = scaled_red (rightbottom);
	right_green = scaled_green (rightbottom);
	right_blue = scaled_blue (rightbottom);
	right_red_adv = (scaled_red (righttop) - right_red) / (blend_height - 1);
	right_green_adv = (scaled_green (righttop) - right_green) / (blend_height - 1);
	right_blue_adv = (scaled_blue (righttop) - right_blue) / (blend_height - 1);
	
	// outer loop - rows
	i = blend_height;
	while (i--)
	{
		red = left_red;
		green = left_green;
		blue = left_blue;
		red_adv = (right_red - red) / (blend_width - 1);
		green_adv = (right_green - green) / (blend_width - 1);
		blue_adv = (right_blue - blue) / (blend_width - 1);
		
		// inner loop - pixels @ each row
		j = blend_width;
		while (j--)
		{
			// in DIB bitmap values are 0BGR
			/*
			*p++ = RGB (
				blue >> int_extend,
				green >> int_extend,
				red >> int_extend);
			*/
			*p++ = red		>> int_extend;
			*p++ = green	>> int_extend;
			*p++ = blue		>> int_extend;
			
			// advance to the next pixel
			red += red_adv; green += green_adv; blue += blue_adv;
		}
		
		// advance to the next row
		left_red += left_red_adv;
		left_green += left_green_adv;
		left_blue += left_blue_adv;
		right_red += right_red_adv;
		right_green += right_green_adv;
		right_blue += right_blue_adv;
		p += nSkip;
	}
}

void ColorSelector2DWndFiller::DoDrawHSV_Hue()
{
	int		i;				// loop counters
	
	unsigned char *p;		// pointer to first pixel from the blend & a loop pointer
	int		nSkip;			// number of pixels to skip after current row and before next one
	
	int		blend_width		= m_width;
	int		blend_height	= m_height;
	
	double	hue;
	double	val, val_adv;
	
	p		= m_buffer; // pixels on first row
	nSkip	= 0;
	
	// constant
	hue = additional_component / (double) scale_hsv_hue;
	
	// outer loop - rows
	i = blend_height;
	
	// initial and change
	val = 0.0;
	val_adv = 1.0 / HSV_LOOP_STEPS (i);
	
	while (i--)
	{
		HSV_SAT(p, blend_width, hue, val);
		val += val_adv;
		p += (blend_width * 3 + nSkip);
	}
}

void ColorSelector2DWndFiller::DoDrawHSV_Sat(void)
{
	int		i;		// loop counters
	
	int		nSkip;	// number of pixels to skip after current row and before next one
	
	unsigned char	*p;		// pointer to first pixel from the blend & a loop pointer
	
	
	int		blend_width		= m_width;
	int		blend_height	= m_height;
	
	double	sat;
	double	val, val_adv;
	
	p		= m_buffer; // pixels on first row
	nSkip	= 0;
	
	// constant
	sat = additional_component / (double) scale_hsv_sat;
	
	// outer loop - rows
	i = blend_height;
	
	// initial and change
	val = 0.0;
	val_adv = 1.0 / HSV_LOOP_STEPS (i);
	
	while (i--)
	{
		HSV_HUE(p, blend_width, sat, val);
		val += val_adv;
		p += (blend_width * 3 + nSkip);
	}
}

void ColorSelector2DWndFiller::DoDrawHSV_Val(void)
{
	int		i;		// loop counters
	
	int		nSkip;	// number of pixels to skip after current row and before next one
	
	unsigned char	*p;		// pointer to first pixel from the blend & a loop pointer
	
	
	int		blend_width		= m_width;
	int		blend_height	= m_height;
	
	double	sat;
	double	sat_adv;
	double	val;
	
	p		= m_buffer; // pixels on first row
	nSkip	= 0;
	
	// constant
	val = additional_component / (double) scale_hsv_value;
	
	// outer loop - rows
	i = blend_height;
	sat = 0.0;
	sat_adv = 1.0 / HSV_LOOP_STEPS (i);
	
	while (i--)
	{
		HSV_HUE(p, blend_width, sat, val);
		sat += sat_adv;
		p += (blend_width * 3 + nSkip);
	}
}

void ColorSelector2DWndFiller::HSV_HUE(unsigned char *buffer,int samples,double sat,double val_fp)
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

void ColorSelector2DWndFiller::HSV_SAT(unsigned char *buffer,int samples,double hue,double val_fp)
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

void ColorSelector2DWndFiller::HSV_VAL(unsigned char *buffer,int samples,double hue,double sat)
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