///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "EGLDriver20.h"

#ifdef USE_GLES20

EGLDriver20::EGLDriver20()
{
	eglDisplay = 0;
	eglConfig = 0;
	eglSurface = 0;
	eglContext = 0;
	eglWindow = 0;
}

EGLDriver20::~EGLDriver20()
{
}

bool EGLDriver20::Init(HWND hwnd)
{
	eglWindow = hwnd;

	HDC	hdc = GetDC(hwnd);
	if (!hdc)
	{
		return false;
	}

	eglDisplay = eglGetDisplay(hdc);

	EGLint majorVersion, minorVersion;
	if(!eglInitialize(eglDisplay, &majorVersion, &minorVersion))
	{
		//debug("PVRShell: Unable to initialise EGL\n");
		//debug("PVRShell: EGL Error (%s)\n", StringFrom_eglGetError());
		return false;
	}

	if(!eglBindAPI(EGL_OPENGL_ES_API))
	{
		//debug("PVRShell: Failed to bind OpenGL ES API\n");
		return false;
	}

	const EGLint pi32ConfigAttribs[] =
	{
		EGL_LEVEL,				0,
		EGL_SURFACE_TYPE,		EGL_WINDOW_BIT,
		EGL_RENDERABLE_TYPE,	EGL_OPENGL_ES2_BIT,
		EGL_NATIVE_RENDERABLE,	EGL_FALSE,
		EGL_RED_SIZE,			8,
		EGL_GREEN_SIZE,			8,
		EGL_BLUE_SIZE,			8,
		EGL_ALPHA_SIZE,			8,
		EGL_DEPTH_SIZE,			24,
		EGL_STENCIL_SIZE,		8,
		EGL_NONE
	};

	
	int iConfigs;
	if (!eglChooseConfig(eglDisplay, pi32ConfigAttribs, &eglConfig, 1, &iConfigs) || (iConfigs != 1))
	{
		return false;
	}

	EGLint ai32ContextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
	eglContext = eglCreateContext(eglDisplay, eglConfig, 0, ai32ContextAttribs);

	
	eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, eglWindow, NULL);
    if(eglSurface == EGL_NO_SURFACE)
    {
        eglGetError(); // Clear error
        eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, NULL, NULL);
	}

	if(eglGetError() != EGL_SUCCESS)
	{
		return false;
	}

	eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);
	if (eglGetError() != EGL_SUCCESS)
	{
		return false;
	}

	return true;
}


void EGLDriver20::SwapBuffers()
{
	eglSwapBuffers(eglDisplay, eglSurface);
}

void EGLDriver20::Terminate()
{
	//glDeleteProgram(uiProgramObject);
	//glDeleteShader(uiFragShader);
	//glDeleteShader(uiVertShader);

	eglMakeCurrent(eglDisplay, NULL, NULL, NULL);
	assert(eglGetError() == EGL_SUCCESS);
	eglTerminate(eglDisplay);
	assert(eglGetError() == EGL_SUCCESS);
}

#else

EGLDriver20::EGLDriver20()
: m_hwnd(0)
, m_hdc(0)
{
}

EGLDriver20::~EGLDriver20()
{
}

bool EGLDriver20::Init(HWND hwnd)
{
	m_hwnd = hwnd;
	m_hdc = GetDC(m_hwnd);
	if(!m_hdc)
	{
		return false;
	}

	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize  = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion   = 1;
	pfd.dwFlags    = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;
 
	int nPixelFormat = ChoosePixelFormat(m_hdc, &pfd);
	if (nPixelFormat == 0) 
		return false;
 
	BOOL bResult = SetPixelFormat(m_hdc, nPixelFormat, &pfd);
 
	if (!bResult) 
		return false; 
 
	HGLRC tempContext = wglCreateContext(m_hdc);
	wglMakeCurrent(m_hdc, tempContext);
 
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		return false;
	}
 
	int attribs[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 1,
		WGL_CONTEXT_FLAGS_ARB, 0,
		0
	};
 
	if(wglewIsSupported("WGL_ARB_create_context") == 1)
	{
		m_hrc = wglCreateContextAttribsARB(m_hdc, 0, attribs);
		wglMakeCurrent(NULL,NULL);
		wglDeleteContext(tempContext);
		wglMakeCurrent(m_hdc, m_hrc);
	}
	else
	{	//It's not possible to make a GL 3.x context. Use the old style context (GL 2.1 and before)
		m_hrc = tempContext;
	}
 
	//Checking GL version
	const unsigned char *GLVersionString = glGetString(GL_VERSION);
 
	//Or better yet, use the GL3 way to get the version number
	int OpenGLVersion[2];
	glGetIntegerv(GL_MAJOR_VERSION, &OpenGLVersion[0]);
	glGetIntegerv(GL_MINOR_VERSION, &OpenGLVersion[1]);
 
	if(!m_hrc)
		return false;
 
	return true;

}

void EGLDriver20::SwapBuffers()
{
	::SwapBuffers(m_hdc);
}

void EGLDriver20::Terminate()
{
	wglMakeCurrent(0, 0);
	if(m_hrc)
	{
		wglDeleteContext(m_hrc);
		m_hrc = 0;
	}
}

#endif