///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited			 //
//																 //
// Author : Mac Lin									             //
// Module : EpicForceEngine										 //
// Date   : 19/Aug/2011											 //
//																 //
///////////////////////////////////////////////////////////////////
#ifndef _InputData_h_
#define _InputData_h_

#define MOUSE_EVENT_CNT		10
#define KEY_EVENT_CNT		64
class InputData
{
public:
	InputData();
	~InputData();

	void addMouseDown(int modifier_, int fingerid_, float x_, float y_);
	void addMouseMove(int modifier_, int fingerid_, float x_, float y_);
	void addMouseUp(int modifier_, int fingerid_, float x_, float y_);
	void addWheelMotion(int modifier_, int x_, int y_, int axis_, int rotation_);
    
	void setAcc(float x_, float y_, float z_);

	void addKeyDown(int keyDownCode_);
	void addKeyUp(int keyUpCode_);
	   
    

	int mouseDownCnt;
	int mouseDownID[MOUSE_EVENT_CNT];
	int mouseDownModifier[MOUSE_EVENT_CNT];
	float mouseDownX[MOUSE_EVENT_CNT];
	float mouseDownY[MOUSE_EVENT_CNT];

	int mouseMoveCnt;
	int mouseMoveID[MOUSE_EVENT_CNT];
	int mouseMoveModifier[MOUSE_EVENT_CNT];
	float mouseMoveX[MOUSE_EVENT_CNT];
	float mouseMoveY[MOUSE_EVENT_CNT];

	int mouseUpCnt;
	int mouseUpID[MOUSE_EVENT_CNT];
	int mouseUpModifier[MOUSE_EVENT_CNT];
	float mouseUpX[MOUSE_EVENT_CNT];
	float mouseUpY[MOUSE_EVENT_CNT];

	int wheelCnt;
	int wheelModifier[MOUSE_EVENT_CNT];
	float wheelX[MOUSE_EVENT_CNT];
	float wheelY[MOUSE_EVENT_CNT];
	float wheelAxis[MOUSE_EVENT_CNT];
	float wheelRotation[MOUSE_EVENT_CNT];

	bool hasAcc;
	float accX, accY, accZ;

	int keyDownCount;
	int keyDownCode[KEY_EVENT_CNT];

	int keyUpCount;
	int keyUpCode[KEY_EVENT_CNT];
};

#endif