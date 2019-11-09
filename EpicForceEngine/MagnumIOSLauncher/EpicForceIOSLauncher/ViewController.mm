//
//  ViewController.m
//  EpicForceIOSLauncher
//
//  Created by Macgyver Lin on 21/8/12.
//  Copyright (c) 2012 EpicForce Entertainment Limited. All rights reserved.
//

#import "ViewController.h"
@interface ViewController () 
{
}
@property (strong, nonatomic) EAGLContext *context;

@end

@implementation ViewController

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc. that aren't in use.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone)
    {
        return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
    }
    else
    {
        return YES;
    }
}

#include "TouchTracker.h"
#include "InputData.h"
#include <time.h>
#include <sys/time.h>

static InputData inputData;
static TouchTracker touchTracker;

//////////////////////////////////////////////////////////////
//----------------------------------------------------------------
long long getCurrentTimeMSFunc()
{
    struct timeval now;
    int rv = gettimeofday(&now, NULL);
    if (rv)
        return rv;
    
    long long tv_sec  = now.tv_sec;
    long long tv_nsec = now.tv_usec * 1000;
    
    return tv_sec * 1000 + tv_nsec / 1000000;
}

//----------------------------------------------------------------
void infoPrintFunc(const char *buf_)
{
    fprintf(stderr, "%s", buf_);
    //[body release];
}

//----------------------------------------------------------------
void debugPrintFunc(int i, const char *buf_)
{
    fprintf(stderr, "%s", buf_);
    //[body release];
}

//----------------------------------------------------------------
void panicPrintFunc(const char *buf_)
{
    fprintf(stderr, "%s", buf_);
    //[body release];
}

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

int width, height;

/////////////////////////////////////////////////////////////////////////
- (void)viewDidLoad
{
    [super viewDidLoad];
    
    ////////////////////////////////////////////////////////////
    // graphics
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];

    if (!self.context)
    {
        NSLog(@"Failed to create ES context");
    }
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableColorFormat    = GLKViewDrawableColorFormatRGBA8888; // GLKViewDrawableColorFormatRGB565
    view.drawableDepthFormat    = GLKViewDrawableDepthFormat24;
    view.drawableStencilFormat  = GLKViewDrawableStencilFormat8;
    view.contentScaleFactor     = 2; // retina       
    
    self.preferredFramesPerSecond = 60;
    
    width                   = view.bounds.size.width *2;
    height                  = view.bounds.size.height*2;
    height                  = view.bounds.size.width *2;
    width                   = view.bounds.size.height*2;
    
    ////////////////////////////////////////////////////////////
    // touch
    
    ////////////////////////////////////////////////////////////
    // accelerator
    self.accelerometer = [UIAccelerometer sharedAccelerometer];
    self.accelerometer.updateInterval = 1.0f / 15.0f;
    self.accelerometer.delegate = self;
    
    //[self setupGL];
    
    ////////////////////////////////////////////////////////////
    // engine
    // Get bundle directory
    NSString *bundleDirNS = [NSString stringWithFormat:@"%@/device/application/bundle/", [[NSBundle mainBundle] resourcePath] ];
    
    // Get documents directory
    NSArray *arrayPaths =
    NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,
                                        NSUserDomainMask,
                                        YES);
    
    NSString *documentDirNS = [NSString stringWithFormat:@"%@/device/application/document/", [arrayPaths objectAtIndex:0]];
    NSString *externalDirNS = [NSString stringWithFormat:@"%@/device/application/external/", [arrayPaths objectAtIndex:0]];

	setRawAssetRootDirectory("../rawAssets/");
	setAssetRootDirectory([bundleDirNS UTF8String]);
	setDocumentDirectory([documentDirNS UTF8String]);
	setExternalDirectory([externalDirNS UTF8String]);
	setGetCurrentTimeMSFunc(getCurrentTimeMSFunc);
	setPrintFunc(infoPrintFunc, debugPrintFunc, panicPrintFunc);
	setInitialScene("PlayMode");

	onInitialize(width, height);
}

- (void)viewDidUnload
{    
    [super viewDidUnload];
    
    ////////////////////////////////////////////////////////////
    // engine
    onTerminate();
    
    ////////////////////////////////////////////////////////////
    // accelerator
    
    ////////////////////////////////////////////////////////////
    // touch

    ////////////////////////////////////////////////////////////
    // InputData
    
    ////////////////////////////////////////////////////////////
    // graphics    
    // [self shutDownGL];
    
    if ([EAGLContext currentContext] == self.context)
    {
        [EAGLContext setCurrentContext:nil];
    }
	self.context = nil;
}

- (void)update
{
    /*
    float aspect = fabsf(self.view.bounds.size.width / self.view.bounds.size.height);
    GLKMatrix4 projectionMatrix = GLKMatrix4MakePerspective(GLKMathDegreesToRadians(65.0f), aspect, 0.1f, 100.0f);
    
    self.effect.transform.projectionMatrix = projectionMatrix;
    
    GLKMatrix4 baseModelViewMatrix = GLKMatrix4MakeTranslation(0.0f, 0.0f, -4.0f);
    baseModelViewMatrix = GLKMatrix4Rotate(baseModelViewMatrix, _rotation, 0.0f, 1.0f, 0.0f);
    
    // Compute the model view matrix for the object rendered with GLKit
    GLKMatrix4 modelViewMatrix = GLKMatrix4MakeTranslation(0.0f, 0.0f, -1.5f);
    modelViewMatrix = GLKMatrix4Rotate(modelViewMatrix, _rotation, 1.0f, 1.0f, 1.0f);
    modelViewMatrix = GLKMatrix4Multiply(baseModelViewMatrix, modelViewMatrix);
    
    self.effect.transform.modelviewMatrix = modelViewMatrix;
    
    // Compute the model view matrix for the object rendered with ES2
    modelViewMatrix = GLKMatrix4MakeTranslation(0.0f, 0.0f, 1.5f);
    modelViewMatrix = GLKMatrix4Rotate(modelViewMatrix, _rotation, 1.0f, 1.0f, 1.0f);
    modelViewMatrix = GLKMatrix4Multiply(baseModelViewMatrix, modelViewMatrix);
    
    _normalMatrix = GLKMatrix3InvertAndTranspose(GLKMatrix4GetMatrix3(modelViewMatrix), NULL);
    
    _modelViewProjectionMatrix = GLKMatrix4Multiply(projectionMatrix, modelViewMatrix);
    
    _rotation += self.timeSinceLastUpdate * 0.5f;
    */
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    /*
    glClearColor(0.65f, 0.65f, 0.65f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glBindVertexArrayOES(_vertexArray);
    
    // Render the object with GLKit
    [self.effect prepareToDraw];
    
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    // Render the object again with ES2
    glUseProgram(_program);
    
    glUniformMatrix4fv(uniforms[UNIFORM_MODELVIEWPROJECTION_MATRIX], 1, 0, _modelViewProjectionMatrix.m);
    glUniformMatrix3fv(uniforms[UNIFORM_NORMAL_MATRIX], 1, 0, _normalMatrix.m);
    
    glDrawArrays(GL_TRIANGLES, 0, 36);
    */
    
    ////////////////////////////////////////////////////////////
    // engine
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
}

- (void)accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration
{
	if(self.paused)
		return;

    // +x right, -x left
    // +y up   , -y down
    // +z back , -z front
    // printf("%f %f %f", acceleration.x, acceleration.y, acceleration.z);
    
    ///////////////////////////////////////////////////////////////
	// pressure
    // set current pressure value
    // touchTracker.handleTouchUpdate(acceleration.x, acceleration.y, acceleration.z);
    
    ///////////////////////////////////////////////////////////////
	// acceleration

    // setAcceleratorValue(0, linear_acceleration_x, linear_acceleration_y, linear_acceleration_z);
    ////////////////////////////////////////////////////////////
    // engine
    inputData.setAcc(acceleration.x, acceleration.y, acceleration.z);
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
	if(self.paused)
		return;
    
    NSUInteger touchCount = [touches count];
    NSUInteger tapCount = [[touches anyObject] tapCount];
    
    for(int i=0; i<touchCount; i++)
    {
        UITouch *touch = [[touches allObjects] objectAtIndex:i];
        CGPoint pt = [touch locationInView:self.view];
        
        pt.x *= 2;
        pt.y *= 2;
        
        touchTracker.handleTouchBegin(inputData, (int)(__bridge void*)touch,
                                      pt.x            * 2.0f / width  - 1.0f,
                                      (height - pt.y) * 2.0f / height - 1.0f,
                                      touch.timestamp);
    }
}

- (void) touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
	if(self.paused)
		return;
    
    NSUInteger touchCount = [touches count];
    NSUInteger tapCount = [[touches anyObject] tapCount];
    
    for(int i=0; i<touchCount; i++)
    {
        UITouch *touch = [[touches allObjects] objectAtIndex:i];
        CGPoint pt = [touch locationInView:self.view];
        
        pt.x *= 2;
        pt.y *= 2;
        
        touchTracker.handleTouchMoved(inputData, (int)(__bridge void*)touch,
                                      pt.x            * 2.0f / width  - 1.0f,
                                      (height - pt.y) * 2.0f / height - 1.0f,
                                      touch.timestamp);
    }
}

- (void) touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	if(self.paused)
		return;
    
    NSUInteger touchCount = [touches count];
    NSUInteger tapCount = [[touches anyObject] tapCount];
    
    for(int i=0; i<touchCount; i++)
    {
        UITouch *touch = [[touches allObjects] objectAtIndex:i];
        CGPoint pt = [touch locationInView:self.view];
        
        pt.x *= 2;
        pt.y *= 2;
        
        touchTracker.handleTouchEnded(inputData, (int)(__bridge void*)touch,
                                      pt.x            * 2.0f / width  - 1.0f,
                                      (height - pt.y) * 2.0f / height - 1.0f,
                                      touch.timestamp);
    }
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
	if(self.paused)
		return;
    
    NSUInteger touchCount = [touches count];
    NSUInteger tapCount = [[touches anyObject] tapCount];
    
    for(int i=0; i<touchCount; i++)
    {
        UITouch *touch = [[touches allObjects] objectAtIndex:i];
        CGPoint pt = [touch locationInView:self.view];
        
        pt.x *= 2;
        pt.y *= 2;
        
        touchTracker.handleTouchEnded(inputData, (int)(__bridge void*)touch,
                                      pt.x            * 2.0f / width  - 1.0f,
                                      (height - pt.y) * 2.0f / height - 1.0f,
                                      touch.timestamp);
    }
}


@end
