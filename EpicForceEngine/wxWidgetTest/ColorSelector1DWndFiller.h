#ifndef _ColorSelector1DWndFiller_h_
#define _ColorSelector1DWndFiller_h_

#include "def.h"

class ColorSelector1DWndFiller
{
public:
	ColorSelector1DWndFiller();
	~ColorSelector1DWndFiller();

	void construct(int width, int height, unsigned char *buffer);

	void setRedMode  (float green, float  blue);
	void setGreenMode(float   red, float  blue);
	void setBlueMode (float   red, float green);
	void setHueMode  (float   sat, float   val);
	void setSatMode  (float   hue, float   val);
	void setValMode  (float   hue, float   sat);
private:
	void DoDrawRGB();
	void DoDrawHSV_Hue();
	void DoDrawHSV_Sat();
	void DoDrawHSV_Val();

	void GetRGB(unsigned char *buffer,int samples,unsigned long start, unsigned long end);
	void HSV_HUE(unsigned char *buffer, int samples, double sat, double val_fp);
	void HSV_SAT(unsigned char *buffer, int samples, double hue, double val_fp);
	void HSV_VAL(unsigned char *buffer, int samples, double hue, double sat);

	void CopyLineBuffer();
	
	int m_width;
	int m_height;
	unsigned char *m_buffer;

	unsigned char *lineBuffer;
		
	int m_nCurMode;
	int	additional_components[4];
};

#endif