///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Semantic_h_
#define _Semantic_h_

#include "Stage.h"

namespace Magnum
{

enum Semantic
{
	DIFFUSEMAP										= 0,
	OPACITYMAP										= 1,
	SPECULARMAP										= 2,
	NORMALMAP			 							= 3,
	LIGHTMAP										= 4,
	DISPLACEMENTMAP									= 5,
	REFLECTIONMAP									= 6,
	RENDERCOLORTARGET								= 7,
	RENDERDEPTHSTENCILTARGET						= 8,
	WORLD											= 9,
	WORLDINVERSE									= 10,
	VIEW											= 11,
	VIEWINVERSE										= 12,
	PROJECTION										= 13,
	PROJECTIONINVERSE								= 14,
	WORLDVIEW										= 15,
	WORLDVIEWINVERSE								= 16,
	VIEWPROJ										= 17,
	VIEWPROJINVERSE									= 18,
	WORLDVIEWPROJ									= 19,
	WORLDVIEWPROJINVERSE							= 20,
	VIEWPORTPIXELSIZE								= 21,
	LOCALBBOXMIN									= 22,
	LOCALBBOXMAX									= 23,
	LOCALBBOXSIZE									= 24,
	RECIPLOCALBBOXSIZE								= 25,
	LIGHT0VECTOR									= 26,
	LIGHT0COLOR										= 27,
	LIGHT0ATTENUATION								= 28,
	LIGHT1VECTOR									= 29,
	LIGHT1COLOR										= 30,
	LIGHT1ATTENUATION								= 31,
	LIGHT2VECTOR									= 32,
	LIGHT2COLOR										= 33,
	LIGHT2ATTENUATION								= 34,
	TIME											= 35,
	PERIOD											= 36,
	BONETRANSFORMS									= 37,
	NUM_SEMANTICS
};

};

#endif
