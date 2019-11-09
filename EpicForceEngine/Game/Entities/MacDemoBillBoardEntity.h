///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _MacDemoBillBoardEntity_h_
#define _MacDemoBillBoardEntity_h_

#include <MagnumEngine.h>
using namespace Magnum;

class MacDemoBillBoardEntity : public Entity
{
public:
	MacDemoBillBoardEntity();
	virtual ~MacDemoBillBoardEntity();

	DECLARE_ENTITY(MacDemoBillBoardEntity);
protected:
private:
	virtual bool onConstruct();
	virtual void onStart();
	virtual void onPause();
	virtual void onResume();
	virtual void onUpdate(float dt);
	virtual void onStop();
	virtual void onDestruct();

	/////////////////////////////////////////////////////
public:
protected:
private:
	BillBoard				billBoard;
	BillBoardRenderer		billBoardRenderer;
};

#endif