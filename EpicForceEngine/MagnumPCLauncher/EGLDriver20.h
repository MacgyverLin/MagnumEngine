///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _EGLDRIVER20_H_
#define _EGLDRIVER20_H_

#include "gldef.h"

#ifdef USE_GLES20

class EGLDriver20
{
public:
	EGLDriver20();
	~EGLDriver20();

	virtual bool Init(HWND hwnd);
	virtual void SwapBuffers();
	virtual void Terminate();
private:
	EGLDisplay			eglDisplay;
	EGLConfig			eglConfig;
	EGLSurface			eglSurface;
	EGLContext			eglContext;
	EGLNativeWindowType	eglWindow;	
};

#else

class EGLDriver20
{
public:
	EGLDriver20();
	~EGLDriver20();

	virtual bool Init(HWND hwnd);
	virtual void SwapBuffers();
	virtual void Terminate();
private:
	HWND		m_hwnd;
	HDC			m_hdc;
	HGLRC		m_hrc;                        // OpenGL Rendering Context 
};

#endif

#endif
