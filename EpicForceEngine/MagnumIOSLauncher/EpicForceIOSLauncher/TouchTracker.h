#ifndef _TouchTracker_h_
#define _TouchTracker_h_

#include "InputData.h"
#include <vector>

#define CPBPressureNone         0.0f
#define CPBPressureLight        0.1f
#define CPBPressureMedium       0.3f
#define CPBPressureHard         0.8f
#define CPBPressureInfinite     2.0f
#define KNumberOfPressureSamples    3

class TouchEntry
{
public:
    TouchEntry(int ID, float pressure, float x, float y, float time);
    
    int ID;
    float pressure;
    float x;
    float y;
    float time;
    int afterTouchCount;
};

#define NUM_SAMPLES (30)

class TouchTracker
{
public:
    TouchTracker();
    ~TouchTracker();
    
    void handleTouchBegin(InputData &inputData, int ID, float x, float y, float time);
    void handleTouchMoved(InputData &inputData, int ID, float x, float y, float time);
    void handleTouchEnded(InputData &inputData, int ID, float x, float y, float time);
    void handleTouchUpdate(InputData &inputData, float accel_x, float accel_y, float accel_z);
    int getNumTouches();
    
    int findTouchID(int ID);
    
    float averageAccel;
    float currentAccel;
    std::vector<TouchEntry *> touches;
    
    float gravity_x, gravity_y, gravity_z;
    float pressure;
    float pressureValues[NUM_SAMPLES];
    unsigned int currentPressureValueIndex;
};

#endif