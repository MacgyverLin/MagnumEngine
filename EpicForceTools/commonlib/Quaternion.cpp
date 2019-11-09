///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#include "Quaternion.h"
using namespace EpicForce;

const Quaternion Quaternion::IDENTITY(1.0f,0.0f,0.0f,0.0f);
const Quaternion Quaternion::ZERO(0.0f,0.0f,0.0f,0.0f);
int Quaternion::ms_iNext[3] = { 1, 2, 0 };
