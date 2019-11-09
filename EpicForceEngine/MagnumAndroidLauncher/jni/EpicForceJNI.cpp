#include <jni.h>
#include <android/log.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define  LOG_TAG    "EpicForceJNI"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#include <android/log.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

long long getCurrentTimeMSFunc()
{
	struct timespec time; 
	clock_gettime(CLOCK_MONOTONIC, &time); 

	return time.tv_sec * 1000.0f + ((float)time.tv_nsec) / 1000.0f / 1000.0f; // in ms
}

void printInfoFunc(const char *buf_)
{
	__android_log_print(ANDROID_LOG_INFO, "EpicForceJNI",  buf_);
}

void printDebugFunc(int i, const char *buf_)
{
	__android_log_print(ANDROID_LOG_INFO, "EpicForceJNI",  buf_);
}

void printPanicFunc(const char *buf_)
{
	__android_log_print(ANDROID_LOG_INFO, "EpicForceJNI",  buf_);
}

#if 0
static void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s\n", name, v);
}

static void checkGlError(const char* op) {
    for (GLint error = glGetError(); error; error
            = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}

static const char gVertexShader[] = 
    "attribute vec4 vPosition;\n"
    "void main() {\n"
    "  gl_Position = vPosition;\n"
    "}\n";

static const char gFragmentShader[] = 
    "precision mediump float;\n"
    "void main() {\n"
    "  gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);\n"
    "}\n";

GLuint loadShader(GLenum shaderType, const char* pSource) {
    GLuint shader = glCreateShader(shaderType);
    if (shader) {
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char* buf = (char*) malloc(infoLen);
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    LOGE("Could not compile shader %d:\n%s\n",
                            shaderType, buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}

GLuint createProgram(const char* pVertexSource, const char* pFragmentSource) {
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
    if (!vertexShader) {
        return 0;
    }

    GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
    if (!pixelShader) {
        return 0;
    }

    GLuint program = glCreateProgram();
    if (program) {
        glAttachShader(program, vertexShader);
        checkGlError("glAttachShader");
        glAttachShader(program, pixelShader);
        checkGlError("glAttachShader");
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char* buf = (char*) malloc(bufLength);
                if (buf) {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    LOGE("Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}

GLuint gProgram;
GLuint gvPositionHandle;

bool setupGraphics(int w, int h)
{
    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);

    LOGI("setupGraphics(%d, %d)", w, h);
    gProgram = createProgram(gVertexShader, gFragmentShader);
    if (!gProgram) {
        LOGE("Could not create program.");
        return false;
    }
    gvPositionHandle = glGetAttribLocation(gProgram, "vPosition");
    checkGlError("glGetAttribLocation");
    LOGI("glGetAttribLocation(\"vPosition\") = %d\n",
            gvPositionHandle);

    glViewport(0, 0, w, h);
    checkGlError("glViewport");
    return true;
}

const GLfloat gTriangleVertices[] = { 0.0f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f };

void renderFrame() 
{
    static float grey;
    grey += 0.01f;
    if (grey > 1.0f) 
	{
        grey = 0.0f;
    }
    glClearColor(grey, grey, grey, 1.0f);
    checkGlError("glClearColor");
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    checkGlError("glClear");

    glUseProgram(gProgram);
    checkGlError("glUseProgram");

    glVertexAttribPointer(gvPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, gTriangleVertices);
    checkGlError("glVertexAttribPointer");
    glEnableVertexAttribArray(gvPositionHandle);
    checkGlError("glEnableVertexAttribArray");
    glDrawArrays(GL_TRIANGLES, 0, 3);
    checkGlError("glDrawArrays");
}
#endif

extern void setRawAssetRootDirectory(const char *rawAssetRootDirectory_);
extern void setAssetRootDirectory(const char *assetRootDirectory_);
extern void setDocumentDirectory(const char *documentDirectory_);
extern void setExternalDirectory(const char *externalDirectory_);
extern void setInitialScene(const char *initialScene_);
extern void setGetCurrentTimeMSFunc(long long (*getCurrentTimeMSFunc_)());
extern void setPrintFunc(void (*printInfoFunc_)(const char *buf_),
						 void (*printDebugFunc_)(int i, const char *buf_),
						 void (*printPanicFunc_)(const char *buf_));
extern bool onInitialize(int width_, int height_);
extern void onProcess();
extern void onPause();
extern void onResume();
extern void onTerminate();
extern void onMouseDown(int modifier, int fingerID, float x, float y);
extern void onMouseUp(int modifier, int fingerID, float x, float y);
extern void onMouseMoved(int modifier, int fingerID, float x, float y);
extern void onMouseWheel(int modifier, float x, float y, int axis, int rotation);
extern void onGamePadKeyDown(int keyCode);
extern void onGamePadKeyUp(int keyCode);
extern void onAccelerationUpdate(float x, float y, float z);
extern void onGUIEvent(const unsigned char *buffer, int len);
extern void addEditorProjectView(void *view_);

extern "C" 
{
	JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_setRawAssetRootDirectory(JNIEnv *env, jobject obj, jstring rawAssetRootDirectory_);
	JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_setAssetRootDirectory(JNIEnv *env, jobject obj, jstring assetRootDirectory_);
	JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_setDocumentDirectory(JNIEnv *env, jobject obj, jstring documentDirectory_);
	JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_setExternalDirectory(JNIEnv *env, jobject obj, jstring externalDirectory_);
	JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_setInitialScene(JNIEnv *env, jobject obj, jstring initialScene_);
	JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_setGetCurrentTimeMSFunc(JNIEnv *env, jobject obj);
	JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_setPrintFunc(JNIEnv *env, jobject obj);
    JNIEXPORT jboolean JNICALL Java_com_epicforce_jni_EpicforceJNI_onInitialize(JNIEnv *env, jobject obj, jint width_, jint height_);
    JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_onProcess(JNIEnv *env, jobject obj);
	JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_onPause(JNIEnv *env, jobject obj);
	JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_onResume(JNIEnv *env, jobject obj);
	JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_onTerminate(JNIEnv *env, jobject obj);
	JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_onMouseDown(JNIEnv *env, jobject obj, jint modifier_, jint fingerID_, jfloat x_, jfloat y_);
	JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_onMouseUp(JNIEnv *env, jobject obj, jint modifier_, jint fingerID_, jfloat x_, jfloat y_);
	JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_onMouseMoved(JNIEnv *env, jobject obj, jint modifier_, jint fingerID_, jfloat x_, jfloat y_);
	JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_onWheel(JNIEnv *env, jobject obj, jint modifier, jfloat x_, jfloat y_, jint axis_, jint rotation_);
	JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_onKeyDown(JNIEnv *env, jobject obj, jint keyCode_);
	JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_onKeyUp(JNIEnv *env, jobject obj, jint keyCode_);
	JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_onAccelerationUpdate(JNIEnv *env, jobject obj, jfloat x_, jfloat y_, jfloat z_);
};

#include "InputData.h"
InputData inputData;

JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_setRawAssetRootDirectory(JNIEnv *env, jobject obj, jstring rawAssetRootDirectory_)
{
	const char *rawAssetRootDirectoryStr = env->GetStringUTFChars(rawAssetRootDirectory_, false );
	
	LOGI("assetRootDirectory=%s\n", rawAssetRootDirectoryStr);
	setRawAssetRootDirectory(rawAssetRootDirectoryStr);
	
	env->ReleaseStringUTFChars(rawAssetRootDirectory_, rawAssetRootDirectoryStr);
}

JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_setAssetRootDirectory(JNIEnv *env, jobject obj, jstring assetRootDirectory_)
{
	const char *assetRootDirectoryStr = env->GetStringUTFChars(assetRootDirectory_, false );
	
	LOGI("assetRootDirectory=%s\n", assetRootDirectoryStr);
	setAssetRootDirectory(assetRootDirectoryStr);
	
	env->ReleaseStringUTFChars(assetRootDirectory_, assetRootDirectoryStr);
}

JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_setDocumentDirectory(JNIEnv *env, jobject obj, jstring documentDirectory_)
{
	const char *documentDirectoryStr = env->GetStringUTFChars(documentDirectory_, false );
	
	LOGI("setDocumentDirectory=%s\n", documentDirectoryStr);
	setDocumentDirectory(documentDirectoryStr);
	
	env->ReleaseStringUTFChars(documentDirectory_, documentDirectoryStr);
}

JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_setExternalDirectory(JNIEnv *env, jobject obj, jstring externalDirectory_)
{
	const char *externalDirectoryStr = env->GetStringUTFChars(externalDirectory_, false );
	
	LOGI("setExternalDirectory=%s\n", externalDirectoryStr);
	setExternalDirectory(externalDirectoryStr);
	
	env->ReleaseStringUTFChars(externalDirectory_, externalDirectoryStr);
}

JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_setInitialScene(JNIEnv *env, jobject obj, jstring initialScene_)
{
	const char *initialSceneStr = env->GetStringUTFChars(initialScene_, false );
	
	LOGI("initialSceneStr=%s\n", initialSceneStr);
	setInitialScene(initialSceneStr);

	env->ReleaseStringUTFChars(initialScene_, initialSceneStr);
}

JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_setGetCurrentTimeMSFunc(JNIEnv *env, jobject obj)
{
	setGetCurrentTimeMSFunc(getCurrentTimeMSFunc);
}

JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_setPrintFunc(JNIEnv *env, jobject obj)
{
	setPrintFunc(printInfoFunc, printDebugFunc, printPanicFunc);
}

JNIEXPORT jboolean JNICALL Java_com_epicforce_jni_EpicforceJNI_onInitialize(JNIEnv *env, jobject obj, jint width_, jint height_)
{
    //setupGraphics(width_, height_);
	LOGI("fuck width=%d, height=%d\n", width_, height_);

	return onInitialize(width_, height_);
}

JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_onProcess(JNIEnv *env, jobject obj)
{
	for(int i=0; i<inputData.mouseDownCnt; i++)
		onMouseDown(inputData.mouseDownModifier[i], inputData.mouseDownID[i], inputData.mouseDownX[i], inputData.mouseDownY[i]);
	inputData.mouseDownCnt	= 0;
	
	for(int i=0; i<inputData.mouseMoveCnt; i++)
		onMouseMoved(inputData.mouseDownModifier[i], inputData.mouseDownID[i], inputData.mouseMoveX[i], inputData.mouseMoveY[i]);
	inputData.mouseMoveCnt	= 0;
	
	for(int i=0; i<inputData.mouseUpCnt; i++)
		onMouseUp(inputData.mouseDownModifier[i], inputData.mouseDownID[i], inputData.mouseUpX[i], inputData.mouseUpY[i]);
	inputData.mouseUpCnt	= 0;
	
	for(int i=0; i<inputData.wheelCnt; i++)
		onMouseWheel(inputData.wheelModifier[i], inputData.wheelX[i], inputData.wheelY[i], inputData.wheelAxis[i], inputData.wheelRotation[i]);
	inputData.wheelCnt	= 0;
	
	for(int i=0; i<inputData.keyDownCount; i++)
		onGamePadKeyDown(inputData.keyDownCode[i]);
	inputData.keyDownCount	= 0;
	
	for(int i=0; i<inputData.keyUpCount; i++)
		onGamePadKeyUp(inputData.keyUpCode[i]);
	inputData.keyUpCount	= 0;
	
	if(inputData.hasAcc)
		onAccelerationUpdate(inputData.accX, inputData.accY, inputData.accZ);
	inputData.hasAcc = false;

	onProcess();
    //renderFrame();
}

JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_onPause(JNIEnv *env, jobject obj)
{
	onPause();
}

JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_onResume(JNIEnv *env, jobject obj)
{
	onResume();
}

JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_onTerminate(JNIEnv *env, jobject obj)
{
	onTerminate();
}

JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_onMouseDown(JNIEnv *env, jobject obj, jint modifier_, jint fingerID_, jfloat x_, jfloat y_)
{
	inputData.addMouseDown(modifier_, fingerID_, x_, y_);
}

JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_onMouseUp(JNIEnv *env, jobject obj, jint modifier_, jint fingerID_, jfloat x_, jfloat y_)
{
	inputData.addMouseUp(modifier_, fingerID_, x_, y_);
}

JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_onMouseMoved(JNIEnv *env, jobject obj, jint modifier_, jint fingerID_, jfloat x_, jfloat y_)
{
	inputData.addMouseMove(modifier_, fingerID_, x_, y_);
}

JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_onWheel(JNIEnv *env, jobject obj, jint modifier_, jfloat x_, jfloat y_, jint axis_, jint rotation_)
{
	inputData.addWheelMotion(modifier_, x_, y_, axis_, rotation_);
}

JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_onKeyDown(JNIEnv *env, jobject obj, jint keyCode_)
{
	inputData.addKeyDown(keyCode_);
}

JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_onKeyUp(JNIEnv *env, jobject obj, jint keyCode_)
{
	inputData.addKeyUp(keyCode_);
}

JNIEXPORT void JNICALL Java_com_epicforce_jni_EpicforceJNI_onAccelerationUpdate(JNIEnv *env, jobject obj, jfloat x_, jfloat y_, jfloat z_)
{
	inputData.setAcc(x_, y_, z_);
}
