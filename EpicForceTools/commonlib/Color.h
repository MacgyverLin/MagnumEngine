#ifndef _Color_h_
#define _Color_h_

#include "InputStream.h"
#include "OutputStream.h"

namespace EpicForce
{

class Color
{
public:
	Color(unsigned char r_=0, unsigned char g_=0, unsigned char b_=0, unsigned char a_=0);
	Color(const Color &rgba);
	Color& operator = (const Color &rgba);
	~Color();

	unsigned char &R() { return m[0]; };
	unsigned char &G() { return m[1]; };
	unsigned char &B() { return m[2]; };
	unsigned char &A() { return m[3]; };

	const unsigned char &R() const { return m[0]; };
	const unsigned char &G() const { return m[1]; };
	const unsigned char &B() const { return m[2]; };
	const unsigned char &A() const { return m[3]; };

	unsigned char &operator [] (int i) { return m[i]; };
	const unsigned char &operator [] (int i) const{ return m[i]; };

	bool operator == (const Color &rgba) const;
	bool operator <  (const Color &rgba) const;

	Color operator+ (const Color& rkC) const;
    Color operator* (float fScalar) const;

	void read(InputStream &is);
	void write(OutputStream &os);

	static const Color BLACK;
	static const Color WHITE;
	static const Color MAGENTA;
private:
	unsigned char m[4];
};

};

#endif