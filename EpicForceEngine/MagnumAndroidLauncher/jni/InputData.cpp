///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited			 //
//																 //
// Author : Mac Lin									             //
// Module : EpicForceEngine										 //
// Date   : 19/Aug/2011											 //
//																 //
///////////////////////////////////////////////////////////////////
#include "InputData.h"
#include <assert.h>

InputData::InputData()
{
	mouseDownCnt = 0;
	for(int i=0; i<MOUSE_EVENT_CNT; i++)
	{
		mouseDownID[i] = 0;	
		mouseDownX[i]  = 0;	
		mouseDownY[i]  = 0;
	}

	mouseMoveCnt = 0;
	for(int i=0; i<MOUSE_EVENT_CNT; i++)
	{
		mouseMoveID[i] = 0;	
		mouseMoveX[i]  = 0;	
		mouseMoveY[i]  = 0;
	}

	mouseUpCnt = 0;
	for(int i=0; i<MOUSE_EVENT_CNT; i++)
	{
		mouseUpID[i] = 0; 
		mouseUpX[i]  = 0;
		mouseUpY[i]  = 0;
	}

	hasAcc = false;
	accX = 0;
	accY = 0;
	accZ = 0;

	keyDownCount = 0;
	for(int i=0; i<KEY_EVENT_CNT; i++)
	{
		keyDownCode[i] = 0; 
	}

	keyUpCount = 0;
	for(int i=0; i<KEY_EVENT_CNT; i++)
	{
		keyUpCode[i] = 0; 
	}
}

InputData::~InputData()
{
}

void InputData::addMouseDown(int modifier_, int fingerid_, float x_, float y_)
{
	assert(mouseDownCnt+1<MOUSE_EVENT_CNT);

	mouseDownModifier[mouseDownCnt] = modifier_;
	mouseDownID[mouseDownCnt] = fingerid_;
	mouseDownX[mouseDownCnt]  = x_;
	mouseDownY[mouseDownCnt]  = y_;

	mouseDownCnt++;
}

void InputData::addMouseMove(int modifier_, int fingerid_, float x_, float y_)
{
	assert(mouseMoveCnt+1<MOUSE_EVENT_CNT);

	mouseMoveModifier[mouseMoveCnt] = modifier_;
	mouseMoveID[mouseMoveCnt] = fingerid_;
	mouseMoveX[mouseMoveCnt]  = x_;
	mouseMoveY[mouseMoveCnt]  = y_;

	mouseMoveCnt++;
}

void InputData::addMouseUp(int modifier_, int fingerid_, float x_, float y_)
{
	assert(mouseUpCnt+1<MOUSE_EVENT_CNT);

	mouseUpModifier[mouseMoveCnt] = modifier_;
	mouseUpID[mouseUpCnt] = fingerid_;
	mouseUpX[mouseUpCnt]  = x_;
	mouseUpY[mouseUpCnt]  = y_;

	mouseUpCnt++;
}

void InputData::addWheelMotion(int modifier_, int x_, int y_, int axis_, int rotation_)
{
	assert(wheelCnt+1<MOUSE_EVENT_CNT);

	wheelModifier[wheelCnt]			=	modifier_;
	wheelX[wheelCnt]				=	x_;
	wheelY[wheelCnt]				=	y_;
	wheelAxis[wheelCnt]				=	axis_;
	wheelRotation[wheelCnt]			=	rotation_;

	wheelCnt++;
}

void InputData::setAcc(float x_, float y_, float z_)
{
	hasAcc = true;

	accX = x_;
	accY = y_;
	accZ = z_;
}

void InputData::addKeyDown(int keyDownCode_)
{
	assert(keyDownCount+1<KEY_EVENT_CNT);

	keyDownCode[keyDownCount] = keyDownCode_;	

	keyDownCount++;
}

void InputData::addKeyUp(int keyUpCode_)
{
	assert(keyUpCount+1<KEY_EVENT_CNT);

	keyUpCode[keyUpCount] = keyUpCode_;	

	keyUpCount++;
}