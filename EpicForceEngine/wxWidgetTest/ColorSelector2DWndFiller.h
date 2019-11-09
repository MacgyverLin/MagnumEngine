#ifndef _ColorSelector2DWndFiller_h_
#define _ColorSelector2DWndFiller_h_

#include "def.h"

class ColorSelector2DWndFiller
{
public:
	ColorSelector2DWndFiller();
	~ColorSelector2DWndFiller();

	void construct(int width, int height, unsigned char *buffer);

	void setRedMode  (float red);
	void setGreenMode(float green);
	void setBlueMode (float blue);
	void setHueMode  (float hue);
	void setSatMode  (float sat);
	void setValMode  (float val);
private:
	void DoDrawRGB();
	void DoDrawHSV_Hue();
	void DoDrawHSV_Sat();
	void DoDrawHSV_Val();

	void HSV_HUE(unsigned char *buffer, int samples, double sat, double val_fp);
	void HSV_SAT(unsigned char *buffer, int samples, double hue, double val_fp);
	void HSV_VAL(unsigned char *buffer, int samples, double hue, double sat);

	void DoCalculateColors(unsigned long &lefttop,unsigned long &righttop,unsigned long &leftbottom,unsigned long &rightbottom);

	int m_width;
	int m_height;
	unsigned char *m_buffer;
	
	int m_nCurMode;
	int additional_component;
};

#endif