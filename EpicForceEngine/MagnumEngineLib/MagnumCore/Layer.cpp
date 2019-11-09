///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#include "Layer.h"
using namespace Magnum;

Layer::Layer()
: layer(0)
{
}

Layer::Layer(unsigned int layer_)
: layer(layer_)
{
}

Layer &Layer::operator= (const Layer &other)
{
	layer = other.layer;

	return *this;
}

// comparison
bool Layer::operator== (const Layer &other) const
{
	return layer==other.layer;
}

bool Layer::operator!= (const Layer &other) const
{
	return layer!=other.layer;
}

bool Layer::operator<  (const Layer &other) const
{
	return layer< other.layer;
}

bool Layer::operator<= (const Layer &other) const
{
	return layer<=other.layer;
}

bool Layer::operator>  (const Layer &other) const
{
	return layer> other.layer;
}

bool Layer::operator>= (const Layer &other) const
{
	return layer>=other.layer;
}

void Layer::read(InputStream &is)
{
	is >> layer;
}

void Layer::write(OutputStream &os) const
{
	os << layer;
}

//////////////////////////////////////////////////////////////////////
void Layer::initialize()
{
	for(int i=0; i<layers.length(); i++)
		layers[i].format("Layer%d", i);
}

Array<String> Layer::layers(16, 16);