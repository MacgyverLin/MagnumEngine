///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _BasicScene_h_
#define _BasicScene_h_

#include "Scene.h"
using namespace Magnum;

namespace Magnum
{

class BasicScene : public Scene
{
public:
	BasicScene();
	virtual ~BasicScene();

protected:
	virtual void update(float dt);
private:
////////////////////////////////////////////
public:
protected:
private:
};

};

#endif