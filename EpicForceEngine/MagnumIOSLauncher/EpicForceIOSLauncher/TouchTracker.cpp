#include "TouchTracker.h"
#include <math.h>

//////////////////////////////////////////////////////////////
TouchEntry::TouchEntry(int ID, float pressure, float x, float y, float time)
{
    this->ID = ID;
    this->pressure = pressure;
    this->x = x;
    this->y = y;
    this->time = time;
    
    this->afterTouchCount = 0;
}

TouchTracker::TouchTracker()
{
    averageAccel = 0;
    currentAccel = 0;
    
    for(int i=0; i<5; i++)
        touches.push_back(new TouchEntry(-10000, 0, 0, 0, 0) );
    
    gravity_x   = 0.0f;
    gravity_y   = 0.0f;
    gravity_z   = 0.0f;
    pressure    = 0;
    
    for (int i = 0; i < NUM_SAMPLES; i++)
        pressureValues[i] = 0;
    currentPressureValueIndex = 1;
}

TouchTracker::~TouchTracker()
{
    averageAccel = 0;
    currentAccel = 0;
    
    for(int i=0; i<5; i++)
    {
        if(touches[i])
        {
            delete touches[i];
        }
    }
    
    for (int i = 0; i < NUM_SAMPLES; i++)
        pressureValues[i] = 0;
    
    currentPressureValueIndex = 1;
}

void TouchTracker::handleTouchBegin(InputData &inputData, int ID, float x, float y, float time)
{
    int idx = findTouchID(-10000);
    
    if(idx!=-1)
    {
        float pressure = fabs(averageAccel - currentAccel);
        
        TouchEntry *t = touches[idx];
        
        t->ID 		= ID;
        t->pressure = pressure;
        t->x 		= x;
        t->y 		= y;
        t->time 	= time;
        t->afterTouchCount = KNumberOfPressureSamples;
        
        //setPointerValue(idx, pressure, x, y);
        
        ////////////////////////////////////////////////////////////
        // engine
        inputData.addMouseDown(0, idx, x, y);
        //printf("addMouseDown  %d %f %f\n", idx, x, y);
    }
}

void TouchTracker::handleTouchMoved(InputData &inputData, int ID, float x, float y, float time)
{
    int idx = findTouchID(ID);
    
    if(idx!=-1)
    {
        TouchEntry *t = touches[idx];
        
        t->x 		= x;
        t->y 		= y;
        
        //setPointerValue(idx, t->pressure, t->x, t->y);
        ////////////////////////////////////////////////////////////
        // engine
        inputData.addMouseMove(0, idx, x, y);
        //printf("addMouseMove  %d %f %f\n", idx, x, y);
    }
}

void TouchTracker::handleTouchEnded(InputData &inputData, int ID, float x, float y, float time)
{
    int idx = findTouchID(ID);
    
    if(idx!=-1)
    {
        TouchEntry *t = touches[idx];
        
        t->ID		= -10000;
        t->x 		= x;
        t->y 		= y;
        
        //setPointerValue(idx, 0, t->x, t->y);
        ////////////////////////////////////////////////////////////
        // engine
        inputData.addMouseUp(0, idx, x, y);
        //printf("addMouseUp  %d %f %f\n", idx, x, y);
    }
}

void TouchTracker::handleTouchUpdate(InputData &inputData, float accel_x, float accel_y, float accel_z)
{
    // set current pressure value
    pressureValues[currentPressureValueIndex % NUM_SAMPLES] = accel_z;
    
    // calculate average pressure
    float total = 0.0f;
    for (int i = 0; i < NUM_SAMPLES; i++)
        total += pressureValues[i];
    
    averageAccel = total / NUM_SAMPLES;
    currentAccel = pressureValues[(currentPressureValueIndex) % NUM_SAMPLES];
    currentPressureValueIndex++;
    if (currentPressureValueIndex > NUM_SAMPLES)
        currentPressureValueIndex = 0;
    
    int idx = -1;
    for (int i = 0; i < touches.size(); i++)
    {
        TouchEntry *thisTouch = touches[i];
        idx++;
        
        if (thisTouch->afterTouchCount > 0)
        {
            float diff = fabs(currentAccel - averageAccel);
            if(thisTouch->pressure < diff)
            {
                thisTouch->pressure = diff;
                
                //setPointerValue(idx, thisTouch->pressure, thisTouch->x, thisTouch->y);
            }
            
            thisTouch->afterTouchCount--;
        }
    }
    
    float value_x = accel_x;
    float value_y = accel_y;
    float value_z = accel_z;
    
    float alpha = 0.8f;
    gravity_x = alpha * gravity_x + (1 - alpha) * value_x;
    gravity_y = alpha * gravity_y + (1 - alpha) * value_y;
    gravity_z = alpha * gravity_z + (1 - alpha) * value_z;
    
    float linear_acceleration_x = value_x - gravity_x;
    float linear_acceleration_y = value_y - gravity_y;
    float linear_acceleration_z = value_z - gravity_z;
}

int TouchTracker::getNumTouches()
{
    return touches.size();
}

int TouchTracker::findTouchID(int ID)
{
    int idx = -1;
    
    for(int i=0; i<touches.size(); i++)
    {
        TouchEntry *thisTouch = touches[i];
        
        if(thisTouch->ID == ID)
        {
            return i;
        }
    }
    
    return -1;
}