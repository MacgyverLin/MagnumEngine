/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.epicforce.jni;

// Wrapper for native library

public class EpicforceJNI 
{
     static 
     {
         System.loadLibrary("EpicForceJNI");
     }
          
     public static native void setRawAssetRootDirectory(String rawAssetRootDirectory);
     public static native void setAssetRootDirectory(String assetRootDirectory);
     public static native void setDocumentDirectory(String documentDirectory);
     public static native void setExternalDirectory(String externalDirectory);
     public static native void setInitialScene(String initialScene);
     public static native void setGetCurrentTimeMSFunc();
     public static native void setPrintFunc();
     public static native boolean onInitialize(int width, int height);
     public static native void onProcess();
     public static native void onPause();
     public static native void onResume();
     public static native void onTerminate();
     public static native void onMouseDown(int modifier, int fingerID, float x, float y);
     public static native void onMouseUp(int modifier, int fingerID, float x, float y);
     public static native void onMouseMoved(int modifier, int fingerID, float x, float y);
     public static native void onWheel(int modifier, float x, float y, int axis, int rotation);
     public static native void onKeyDown(int keyCode);
     public static native void onKeyUp(int keyCode);
     public static native void onAccelerationUpdate(float x, float y, float z);
}