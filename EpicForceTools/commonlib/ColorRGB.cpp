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

const ColorRGB ColorRGB::BLACK			(0.0f, 0.0f, 0.0f);
const ColorRGB ColorRGB::BLUE			(0.0f, 0.0f, 0.5f);
const ColorRGB ColorRGB::GREEN	  		(0.0f, 0.5f, 0.0f);
const ColorRGB ColorRGB::CYAN			(0.0f, 0.5f, 0.5f);
const ColorRGB ColorRGB::RED			(0.5f, 0.0f, 0.0f);
const ColorRGB ColorRGB::MANGENTA		(0.5f, 0.0f, 0.5f);
const ColorRGB ColorRGB::BROWN			(0.5f, 0.5f, 0.0f);
const ColorRGB ColorRGB::GREY			(0.5f, 0.5f, 0.5f);
const ColorRGB ColorRGB::BRIGHT_BLUE    (0.0f, 0.0f, 1.0f);
const ColorRGB ColorRGB::BRIGHT_GREEN   (0.0f, 1.0f, 0.0f);
const ColorRGB ColorRGB::BRIGHT_CYAN    (0.0f, 1.0f, 1.0f);
const ColorRGB ColorRGB::BRIGHT_RED     (1.0f, 0.0f, 0.0f);
const ColorRGB ColorRGB::BRIGHT_MANGENTA(1.0f, 0.0f, 1.0f);
const ColorRGB ColorRGB::YELLOW         (1.0f, 1.0f, 0.0f);
const ColorRGB ColorRGB::WHITE          (1.0f, 1.0f, 1.0f);

ColorRGB::ColorRGB(float r_, float g_, float b_) 
{
	m_afTuple[0] = r_;
	m_afTuple[1] = g_;
	m_afTuple[2] = b_;
}

ColorRGB::ColorRGB(const ColorRGB &rgb_)
{
	*this = rgb_;
}

ColorRGB &ColorRGB::operator = (const ColorRGB &rgb)
{
	m_afTuple[0] = rgb.m_afTuple[0];
	m_afTuple[1] = rgb.m_afTuple[1];
	m_afTuple[2] = rgb.m_afTuple[2];

	return *this;
}

ColorRGB &ColorRGB::operator = (const ColorRGBA &rgba)
{
	m_afTuple[0] = rgba[0];
	m_afTuple[1] = rgba[1];
	m_afTuple[2] = rgba[2];

	return *this;
}

ColorRGB::~ColorRGB()
{
}

bool ColorRGB::operator == (const ColorRGB &rgb) const
{
	return System::Memcmp( (const void *)(m_afTuple), (const void *)(rgb.m_afTuple), sizeof(m_afTuple[0])*3) == 0;
}

bool ColorRGB::operator < (const ColorRGB &rgb) const
{
	return System::Memcmp( (const void *)(m_afTuple), (const void *)(rgb.m_afTuple), sizeof(m_afTuple[0])*3) < 0;
}

ColorRGB ColorRGB::operator+ (const ColorRGB& rkC) const
{
	return ColorRGB(m_afTuple[0]+rkC.m_afTuple[0], m_afTuple[1]+rkC.m_afTuple[1], m_afTuple[2]+rkC.m_afTuple[2]);
}

ColorRGB ColorRGB::operator* (float fScalar) const
{
	return ColorRGB(m_afTuple[0]*fScalar, m_afTuple[1]*fScalar, m_afTuple[2]*fScalar);
}

void ColorRGB::read(InputStream &is)
{
	is >> m_afTuple[0] >> m_afTuple[1] >> m_afTuple[2];
}

void ColorRGB::write(OutputStream &os) const
{
	os << m_afTuple[0] << m_afTuple[1] << m_afTuple[2];
}
