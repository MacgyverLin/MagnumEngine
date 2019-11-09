//
//  ViewController.h
//  EpicForceIOSLauncher
//
//  Created by Macgyver Lin on 21/8/12.
//  Copyright (c) 2012 EpicForce Entertainment Limited. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>

@interface ViewController : GLKViewController <UIAccelerometerDelegate>
{
    UIAccelerometer *accelerometer;
}

@property (nonatomic, retain) UIAccelerometer *accelerometer;

@end
