///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#include "ESystem.h"
#include "ColorRGB.h"
#include "ColorRGBA.h"
using namespace EpicForce;

const ColorRGBA ColorRGBA::BLACK		  (0.0f, 0.0f, 0.0f, 1.0f);
const ColorRGBA ColorRGBA::BLUE			  (0.0f, 0.0f, 0.5f, 1.0f);
const ColorRGBA ColorRGBA::GREEN	  	  (0.0f, 0.5f, 0.0f, 1.0f);
const ColorRGBA ColorRGBA::CYAN			  (0.0f, 0.5f, 0.5f, 1.0f);
const ColorRGBA ColorRGBA::RED			  (0.5f, 0.0f, 0.0f, 1.0f);
const ColorRGBA ColorRGBA::MANGENTA		  (0.5f, 0.0f, 0.5f, 1.0f);
const ColorRGBA ColorRGBA::BROWN		  (0.5f, 0.5f, 0.0f, 1.0f);
const ColorRGBA ColorRGBA::GREY			  (0.5f, 0.5f, 0.5f, 1.0f);
const ColorRGBA ColorRGBA::BRIGHT_BLUE    (0.0f, 0.0f, 1.0f, 1.0f);
const ColorRGBA ColorRGBA::BRIGHT_GREEN   (0.0f, 1.0f, 0.0f, 1.0f);
const ColorRGBA ColorRGBA::BRIGHT_CYAN    (0.0f, 1.0f, 1.0f, 1.0f);
const ColorRGBA ColorRGBA::BRIGHT_RED     (1.0f, 0.0f, 0.0f, 1.0f);
const ColorRGBA ColorRGBA::BRIGHT_MANGENTA(1.0f, 0.0f, 1.0f, 1.0f);
const ColorRGBA ColorRGBA::YELLOW         (1.0f, 1.0f, 0.0f, 1.0f);
const ColorRGBA ColorRGBA::WHITE          (1.0f, 1.0f, 1.0f, 1.0f);

ColorRGBA::ColorRGBA(float r_, float g_, float b_, float a_) 
{
	m_afTuple[0] = r_;
	m_afTuple[1] = g_;
	m_afTuple[2] = b_;
	m_afTuple[3] = a_;
}

ColorRGBA::ColorRGBA(const ColorRGBA &rgba_)
{
	*this = rgba_;
}

ColorRGBA &ColorRGBA::operator = (const ColorRGB &rgb)
{
	m_afTuple[0] = rgb[0];
	m_afTuple[1] = rgb[1];
	m_afTuple[2] = rgb[2];
	m_afTuple[3] = 1.0f;

	return *this;
}

ColorRGBA &ColorRGBA::operator = (const ColorRGBA &rgba)
{
	m_afTuple[0] = rgba[0];
	m_afTuple[1] = rgba[1];
	m_afTuple[2] = rgba[2];
	m_afTuple[3] = rgba[3];

	return *this;
}

ColorRGBA::~ColorRGBA()
{
}

bool ColorRGBA::operator == (const ColorRGBA &rgba) const
{
	return System::Memcmp( (const void *)(m_afTuple), (const void *)(rgba.m_afTuple), sizeof(m_afTuple[0])*3) == 0;
}

bool ColorRGBA::operator < (const ColorRGBA &rgba) const
{
	return System::Memcmp( (const void *)(m_afTuple), (const void *)(rgba.m_afTuple), sizeof(m_afTuple[0])*3) < 0;
}

ColorRGBA ColorRGBA::operator+ (const ColorRGBA& rkC) const
{
	return ColorRGBA(m_afTuple[0]+rkC.m_afTuple[0], m_afTuple[1]+rkC.m_afTuple[1], m_afTuple[2]+rkC.m_afTuple[2], m_afTuple[3]);
}

ColorRGBA ColorRGBA::operator* (float fScalar) const
{
	return ColorRGBA(m_afTuple[0]*fScalar, m_afTuple[1]*fScalar, m_afTuple[2]*fScalar, m_afTuple[3]);
}

void ColorRGBA::read(InputStream &is)
{
	is >> m_afTuple[0] >> m_afTuple[1] >> m_afTuple[2] >> m_afTuple[3];
}

void ColorRGBA::write(OutputStream &os) const
{
	os << m_afTuple[0] << m_afTuple[1] << m_afTuple[2] << m_afTuple[3];
}
