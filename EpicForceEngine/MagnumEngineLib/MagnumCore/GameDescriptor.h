///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _GameDescriptor_h_
#define _GameDescriptor_h_

namespace Magnum
{

class GameDescriptor
{
public:
	GameDescriptor();
	~GameDescriptor();

	static GameDescriptor &instance();

	bool create(const char *dllFilename);
	void destroy();

	bool isValid() const;
	
	void (*setRawAssetRootDirectory)(const char *rawAssetRootDirectory_);
	void (*setAssetRootDirectory)(const char *assetRootDirectory_);
	void (*setDocumentDirectory)(const char *documentDirectory_);
	void (*setExternalDirectory)(const char *externalDirectory_);
	void (*setInitialScene)(const char *initialScene_);
	void (*setGetCurrentTimeMSFunc)(long long (*getCurrentTimeMSFunc_)());
	void (*setPrintFunc)(void (*printInfoFunc_)(const char *buf_),
						 void (*printDebugFunc_)(int i, const char *buf_),
						 void (*printPanicFunc_)(const char *buf_));
	
	bool (*onInitialize)(int width_, int height_);
	void (*onProcess)();
	void (*onPause)();
	void (*onResume)();
	void (*onTerminate)();
	void (*onMouseDown)(int modifier, int fingerID, float x, float y);
	void (*onMouseUp)(int modifier, int fingerID, float x, float y);
	void (*onMouseMoved)(int modifier, int fingerID, float x, float y);
	void (*onMouseWheel)(int modifier, float x, float y, int axis, int value);
	void (*onGamePadKeyDown)(int keyCode);
	void (*onGamePadKeyUp)(int keyCode);
	void (*onAccelerationUpdate)(float x, float y, float z);
	void (*onGUIEvent)(const unsigned char *buffer, int len);

	////////////////////////////////////////////
	// Editor Specific
	void (*addEditorProjectView)(void *view_);
protected:
private:
	static GameDescriptor *_instance;

	void *hLib;
};

};

#endif