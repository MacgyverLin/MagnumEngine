///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _gldef_h_
#define _gldef_h_

//#define USE_GLES20

#if defined(WIN32)

	#ifdef USE_GLES20

	#include <assert.h>
	#include <EGL/egl.h>
	#include <GLES2/gl2.h>
	#include <GLES2/gl2ext.h>

	#else
	
	#include <assert.h>
	#include <windows.h>
	#include <glew.h>
	#include <wglew.h>
	#include <gl/GL.h>

	#endif

#elif ( defined(__ANDROID__ )  )

    #include <GLES2/gl2.h>
	#include <GLES2/gl2ext.h>

#else

    #include <OpenGLES/ES2/gl.h>
    #include <OpenGLES/ES2/glext.h>

#endif

#endif