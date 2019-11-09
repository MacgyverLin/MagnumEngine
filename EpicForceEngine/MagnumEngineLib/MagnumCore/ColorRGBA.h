///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _ColorRGBA_h_
#define _ColorRGBA_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"

namespace Magnum
{

class ColorRGB;

class ColorRGBA
{
public:
	ColorRGBA(float r_=0, float g_=0, float b_=0, float a_=0);
	ColorRGBA(const ColorRGBA &rgba);
	ColorRGBA &operator = (const ColorRGB &rgb);
	ColorRGBA &operator = (const ColorRGBA &rgba);
	~ColorRGBA();

	float &R() { return m_afTuple[0]; };
	float &G() { return m_afTuple[1]; };
	float &B() { return m_afTuple[2]; };
	float &A() { return m_afTuple[3]; };

	const float &R() const { return m_afTuple[0]; };
	const float &G() const { return m_afTuple[1]; };
	const float &B() const { return m_afTuple[2]; };
	const float &A() const { return m_afTuple[3]; };

	float &operator [] (int i) { assert(i<4); return m_afTuple[i]; };
	const float &operator [] (int i) const { assert(i<4); return m_afTuple[i]; };

	bool operator == (const ColorRGBA &rgba) const;
	bool operator <  (const ColorRGBA &rgba) const;

	ColorRGBA operator+ (const ColorRGBA& rkC) const;
    ColorRGBA operator* (float fScalar) const;

	unsigned int toInteger() const;

	void read(InputStream &is);
	void write(OutputStream &os) const;

	static const ColorRGBA BLACK;
	static const ColorRGBA BLUE;
	static const ColorRGBA GREEN;
	static const ColorRGBA CYAN;
	static const ColorRGBA RED;
	static const ColorRGBA MANGENTA;
	static const ColorRGBA BROWN;
	static const ColorRGBA GREY;
	static const ColorRGBA BRIGHT_BLUE;
	static const ColorRGBA BRIGHT_GREEN;
	static const ColorRGBA BRIGHT_CYAN;
	static const ColorRGBA BRIGHT_RED;
	static const ColorRGBA BRIGHT_MANGENTA;
	static const ColorRGBA YELLOW;
	static const ColorRGBA WHITE;
private:
	float m_afTuple[4];
};

};

#endif