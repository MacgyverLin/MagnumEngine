#ifndef _def_h_
#define _def_h_

#define	HSV_LOOP_STEPS(w)	((w) - 1)

#define RGB(r,g,b)          ((unsigned long )(((unsigned char)(r)|((unsigned short)((unsigned char)(g))<<8))|(((unsigned long )(unsigned char)(b))<<16)))
#define LOBYTE(w)           ((unsigned char)(((unsigned long)(w)) & 0xff))
#define GetRValue(rgb)      (LOBYTE(rgb))
#define GetGValue(rgb)      (LOBYTE(((unsigned short)(rgb)) >> 8))
#define GetBValue(rgb)      (LOBYTE((rgb)>>16))

#define	HSV_0()				RGB ((unsigned char) (coef1 >> int_extend),(unsigned char) (coef3 >> int_extend),(unsigned char) (val >> int_extend))
#define	HSV0(buffer)		*buffer++ = ((unsigned char)(  val >> int_extend)),	*buffer++ = ((unsigned char)(coef3 >> int_extend)),	*buffer++ = ((unsigned char)(coef1 >> int_extend))
							
#define	HSV_HUE_ADV_0()		coef1 += coef1_adv,coef3 += coef3_adv

#define	HSV_1()				RGB ((unsigned char) (coef1 >> int_extend),(unsigned char) (val >> int_extend),(unsigned char) (coef2 >> int_extend))
#define	HSV1(buffer)		*buffer++ = ((unsigned char)(coef2 >> int_extend)),	*buffer++ = ((unsigned char)(  val >> int_extend)),	*buffer++ = ((unsigned char)(coef1 >> int_extend))
							
#define	HSV_HUE_ADV_1()		coef1 += coef1_adv,	coef2 += coef2_adv

#define	HSV_2()				RGB ((unsigned char) (coef3 >> int_extend),(unsigned char) (val >> int_extend),(unsigned char) (coef1 >> int_extend))
#define	HSV2(buffer)		*buffer++ = ((unsigned char)(coef1 >> int_extend)),	*buffer++ = ((unsigned char)(  val >> int_extend)),	*buffer++ = ((unsigned char)(coef3 >> int_extend))
							
#define	HSV_HUE_ADV_2()		HSV_HUE_ADV_0()

#define	HSV_3()				RGB ((unsigned char) (val >> int_extend),(unsigned char) (coef2 >> int_extend),(unsigned char) (coef1 >> int_extend))
#define	HSV3(buffer)		*buffer++ = ((unsigned char)(coef1 >> int_extend)),	*buffer++ = ((unsigned char)(coef2 >> int_extend)),	*buffer++ = ((unsigned char)(val   >> int_extend))
							
#define	HSV_HUE_ADV_3()		HSV_HUE_ADV_1()

#define	HSV_4()				RGB ((unsigned char) (val >> int_extend),(unsigned char) (coef1 >> int_extend),(unsigned char) (coef3 >> int_extend))
#define	HSV4(buffer)		*buffer++ = ((unsigned char)(coef3 >> int_extend)),	*buffer++ = ((unsigned char)(coef1 >> int_extend)),	*buffer++ = ((unsigned char)(val   >> int_extend))
							
#define	HSV_HUE_ADV_4()		HSV_HUE_ADV_0()

#define	HSV_5()				RGB ((unsigned char) (coef2 >> int_extend),(unsigned char) (coef1 >> int_extend),(unsigned char) (val >> int_extend))
#define	HSV5(buffer)		*buffer++ = ((unsigned char)(val   >> int_extend)),	*buffer++ = ((unsigned char)(coef1 >> int_extend)),	*buffer++ = ((unsigned char)(coef2 >> int_extend))

#define	HSV_HUE_ADV_5()		HSV_HUE_ADV_1()

// initialize for HSV colorspace in SAT mode, for HUE between 0 and 1 (0 and 60 deg)
#define	HSV_SAT_INIT_0()	coef3 = coef1,	coef3_adv = (int) ((val - coef3) / HSV_LOOP_STEPS (j))

// advance for HSV colorspace in SAT mode, for HUE between 0 and 1 (0 and 60 deg)
#define	HSV_SAT_ADV_0()	    coef3 += coef3_adv

#define	HSV_SAT_INIT_1()	coef2 = val, coef2_adv = (int) ((val * (1.0 - sat) - coef2) / HSV_LOOP_STEPS (j))

#define	HSV_SAT_ADV_1()	    coef2 += coef2_adv

#define	HSV_SAT_INIT_2()	HSV_SAT_INIT_0()
#define	HSV_SAT_ADV_2()		HSV_SAT_ADV_0()

#define	HSV_SAT_INIT_3()	HSV_SAT_INIT_1()
#define	HSV_SAT_ADV_3()		HSV_SAT_ADV_1()

#define	HSV_SAT_INIT_4()	HSV_SAT_INIT_0()
#define	HSV_SAT_ADV_4()		HSV_SAT_ADV_0()

#define	HSV_SAT_INIT_5()	HSV_SAT_INIT_1()
#define	HSV_SAT_ADV_5()		HSV_SAT_ADV_1()

// for HSV colorspace, VAL mode is calculate in a same manner as SAT mode
//	so all macroses simply maps over SAT mode macroses
#define	HSV_VAL_INIT_0()	HSV_SAT_INIT_0()
#define	HSV_VAL_ADV_0()		HSV_SAT_ADV_0()

#define	HSV_VAL_INIT_1()	HSV_SAT_INIT_1()
#define	HSV_VAL_ADV_1()		HSV_SAT_ADV_1()

#define	HSV_VAL_INIT_2()	HSV_SAT_INIT_2()
#define	HSV_VAL_ADV_2()		HSV_SAT_ADV_2()

#define	HSV_VAL_INIT_3()	HSV_SAT_INIT_3()
#define	HSV_VAL_ADV_3()		HSV_SAT_ADV_3()

#define	HSV_VAL_INIT_4()	HSV_SAT_INIT_4()
#define	HSV_VAL_ADV_4()		HSV_SAT_ADV_4()

const int	int_extend = 20;

enum scale_values
{
	scale_rgb = 1,
	scale_rgb_red = scale_rgb,
	scale_rgb_green = scale_rgb,
	scale_rgb_blue = scale_rgb,
	scale_hsv_hue = 10,
	scale_hsv_sat = 1000,
	scale_hsv_value = 1000
};

enum max_values
{
	max_rgb = 255,
	max_rgb_red = max_rgb,
	max_rgb_green = max_rgb,
	max_rgb_blue = max_rgb,
	max_hsv_hue = 3599,
	max_hsv_sat = 1000,
	max_hsv_value = 1000
};

enum modes_visual
{
	modes_rgb_red = 0,
	modes_rgb_green = 1,
	modes_rgb_blue = 2,
	modes_hsv_hue = 3,
	modes_hsv_sat = 4,
	modes_hsv_value = 5,
	modes_max,
	modes_mask = 0x7F,
	modes_reverse = 0x80
};

inline int scaled_red (unsigned long c)
{
	return (GetRValue (c) << int_extend);
}

inline int scaled_green (unsigned long c)
{
	return (GetGValue (c) << int_extend);
}

inline int scaled_blue (unsigned long c)
{
	return (GetBValue (c) << int_extend);
}

#endif