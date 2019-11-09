///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _ColorRGB_h_
#define _ColorRGB_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"

namespace Magnum
{

class ColorRGBA;

class ColorRGB
{
public:
	ColorRGB(float r_=0, float g_=0, float b_=0);
	ColorRGB(const ColorRGB &rgb);
	ColorRGB &operator = (const ColorRGB &rgb);
	ColorRGB &operator = (const ColorRGBA &rgba);
	~ColorRGB();

	float &R() { return m_afTuple[0]; };
	float &G() { return m_afTuple[1]; };
	float &B() { return m_afTuple[2]; };

	const float &R() const { return m_afTuple[0]; };
	const float &G() const { return m_afTuple[1]; };
	const float &B() const { return m_afTuple[2]; };

	float &operator [] (int i) { assert(i<3); return m_afTuple[i]; };
	const float &operator [] (int i) const { assert(i<3); return m_afTuple[i]; };

	bool operator == (const ColorRGB &rgba) const;
	bool operator <  (const ColorRGB &rgba) const;

	ColorRGB operator+ (const ColorRGB& rkC) const;
    ColorRGB operator* (float fScalar) const;

	unsigned int toInteger() const;

	void read(InputStream &is);
	void write(OutputStream &os) const;

	static const ColorRGB BLACK;
	static const ColorRGB BLUE;
	static const ColorRGB GREEN;
	static const ColorRGB CYAN;
	static const ColorRGB RED;
	static const ColorRGB MANGENTA;
	static const ColorRGB BROWN;
	static const ColorRGB GREY;
	static const ColorRGB BRIGHT_BLUE;
	static const ColorRGB BRIGHT_GREEN;
	static const ColorRGB BRIGHT_CYAN;
	static const ColorRGB BRIGHT_RED;
	static const ColorRGB BRIGHT_MANGENTA;
	static const ColorRGB YELLOW;
	static const ColorRGB WHITE;
private:
	float m_afTuple[3];
};

};

#endif