#include "Color.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "assert.h"
using namespace EpicForce;

const Color Color::BLACK(0x00, 0x00, 0x00, 0xff);
const Color Color::WHITE(0xff, 0xff, 0xff, 0xff);
const Color Color::MAGENTA(0xff, 0x7f, 0xff, 0x00);

Color::Color(unsigned char r_, unsigned char g_, unsigned char b_, unsigned char a_) 
{
	m[0] = r_;
	m[1] = g_;
	m[2] = b_;
	m[3] = a_;
}

Color::Color(const Color &rgba_)
{
	*this = rgba_;
}

Color& Color::operator = (const Color &rgba)
{
	m[0] = rgba.m[0];
	m[1] = rgba.m[1];
	m[2] = rgba.m[2];
	m[3] = rgba.m[3];

	return *this;
}

Color::~Color()
{
}

bool Color::operator == (const Color &rgba) const
{
	return 	m[0] == rgba.m[0] &&
			m[1] == rgba.m[1] &&
			m[2] == rgba.m[2]
			;//&& a == rgba.a;
}

bool Color::operator < (const Color &rgba) const
{
	return memcmp(m, rgba.m, sizeof(m[0])*3) < 0;
}

Color Color::operator+ (const Color& rkC) const
{
	return Color(m[0]+rkC.m[0], m[1]+rkC.m[1], m[2]+rkC.m[2], m[3]);
}

Color Color::operator* (float fScalar) const
{
	return Color(m[0]*fScalar, m[1]*fScalar, m[2]*fScalar, m[3]);
}

void Color::read(InputStream &is)
{
	is >> m[0] >> m[1] >> m[2] >> m[3];
}

void Color::write(OutputStream &os)
{
	os << m[0] << m[1] << m[2] << m[3];
}
