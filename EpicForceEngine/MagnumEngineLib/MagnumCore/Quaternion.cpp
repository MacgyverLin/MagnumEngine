///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Quaternion.h"
using namespace Magnum;

const Quaternion Quaternion::IDENTITY(1.0f,0.0f,0.0f,0.0f);
const Quaternion Quaternion::ZERO(0.0f,0.0f,0.0f,0.0f);
int Quaternion::ms_iNext[3] = { 1, 2, 0 };
