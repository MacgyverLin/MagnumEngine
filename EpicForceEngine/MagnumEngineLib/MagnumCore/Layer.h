///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _Layer_h_
#define _Layer_h_

#include "Stage.h"
#include "EMath.h"
#include "EString.h"
#include "InputStream.h"
#include "OutputStream.h"

namespace Magnum
{

class Layer
{
public:
    Layer();
    Layer(unsigned int layer_);

	// assignment
    Layer& operator= (const Layer &other);

    // comparison
    bool operator== (const Layer &other) const;
    bool operator!= (const Layer &other) const;
    bool operator<  (const Layer &other) const;
    bool operator<= (const Layer &other) const;
    bool operator>  (const Layer &other) const;
    bool operator>= (const Layer &other) const;

	void read(InputStream &is);
	void write(OutputStream &os) const;
protected:
private:
    unsigned int layer;


//////////////////////////////////////////////////////////////////////
public:
    // construction
	static void initialize();
    static Array<String> layers;
};

};

#endif
