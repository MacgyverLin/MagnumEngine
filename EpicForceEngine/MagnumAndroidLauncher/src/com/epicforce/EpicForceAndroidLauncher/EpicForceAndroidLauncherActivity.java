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

package com.epicforce.EpicForceAndroidLauncher;

import java.io.File;
//import java.io.InputStream;
//import java.io.RandomAccessFile;
//import java.nio.ByteBuffer;
//import java.nio.ByteOrder;
import java.util.List;
import java.util.Locale;

import org.fmod.FMODAudioDevice;
//import java.util.Random;

//import javax.xml.parsers.DocumentBuilder;
//import javax.xml.parsers.DocumentBuilderFactory;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
//import android.app.PendingIntent;
//import android.graphics.Color;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
//import android.os.Messenger;
//import android.provider.Settings;
import android.view.Display;
import android.view.MotionEvent;
import android.view.Surface;
import android.view.View;
import android.view.WindowManager;
import android.view.View.OnTouchListener;
import android.widget.FrameLayout;
import android.widget.SeekBar;
import android.widget.FrameLayout.LayoutParams;
//import android.widget.Button;
//import android.widget.LinearLayout;
//import android.widget.ProgressBar;
//import android.widget.TextView;
//import android.widget.Toast;
//import android.widget.TextView;

//import com.android.vending.expansion.downloader.R;
import com.epicforce.jni.EpicforceJNI;

import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.*;
import android.util.*;
import android.content.pm.PackageManager.NameNotFoundException;
//import android.content.res.AssetManager;

import com.epicforce.jni.EpicforceJNI;

public class EpicForceAndroidLauncherActivity extends Activity 
{
	// private FMODAudioDevice mFMODAudioDevice = new FMODAudioDevice();
	
    private EpicForceAndroidLauncherView mView;
    private static String language;
    
    static
    {
    	System.loadLibrary("fmodex");
    }    
    
	protected boolean initDirectories(boolean development)
	{
		if(development)
		{
			PackageInfo info = null;
			try
			{
	            language = Locale.getDefault().toString();
	            
				info = getPackageManager().getPackageInfo("com.epicforce.EpicForceAndroidLauncher", 0);
				
				EpicforceJNI.setRawAssetRootDirectory(Environment.getExternalStorageDirectory().toString() + "/EpicForce/Game/EpicForceAndroidLauncher/rawAssets/");
				EpicforceJNI.setAssetRootDirectory(Environment.getExternalStorageDirectory().toString() + "/EpicForce/Game/EpicForceAndroidLauncher/device/application/bundle/");
				EpicforceJNI.setDocumentDirectory(Environment.getExternalStorageDirectory().toString() + "/EpicForce/Game/EpicForceAndroidLauncher/device/application/document/");
				EpicforceJNI.setExternalDirectory(Environment.getExternalStorageDirectory().toString() + "/EpicForce/Game/EpicForceAndroidLauncher/device/external/");
				EpicforceJNI.setGetCurrentTimeMSFunc();
				EpicforceJNI.setPrintFunc();
				EpicforceJNI.setInitialScene("PlayMode");
				
				return true;
			}
			catch (NameNotFoundException e)
			{
				Log.e("EpicforceJNI", e.toString());
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	
	SensorManager sensorManager = null;

	// ----------------------------------------------------------------------------------
	boolean accelerationSensorPresent = false;
	Sensor accelerationSensor;
	SensorEventListener accelerationSensorListener = null;
	float gravity_x, gravity_y, gravity_z;
	int width, height;
	
	public void initTouchSensor()
	{
		int currentapiVersion = android.os.Build.VERSION.SDK_INT;

		Display display = this.getWindowManager().getDefaultDisplay();
		width = display.getWidth();
		height = display.getHeight();
		
		mView.setOnTouchListener(new OnTouchListener()
		{
			public boolean onTouch(View v, MotionEvent ev)
			{
				int action = ev.getAction();
				int actionCode = action & MotionEvent.ACTION_MASK;

				if (actionCode == 0 || actionCode == 5) // down or pointer down (BEGIN)
				{
					int pID = action >> MotionEvent.ACTION_POINTER_INDEX_SHIFT;

					EpicforceJNI.onMouseDown(0, pID, 
											 ev.getX()            * 2.0f / width - 1.0f, 
											 (height - ev.getY()) * 2.0f / height - 1.0f);
				}
				else if (actionCode == 2) // moving (MOVE)
				{
					int pID = action >> MotionEvent.ACTION_POINTER_INDEX_SHIFT;

					EpicforceJNI.onMouseMoved(0, pID, 
							 				  ev.getX()            * 2.0f / width - 1.0f, 
							 				  (height - ev.getY()) * 2.0f / height - 1.0f);
				}
				else if (actionCode == 1 || actionCode == 6) // up or pointer (ENDED)
				{
					int pID = action >> MotionEvent.ACTION_POINTER_INDEX_SHIFT;

					EpicforceJNI.onMouseUp(0, pID, 
			 				  			   ev.getX()            * 2.0f / width - 1.0f, 
			 				  			   (height - ev.getY()) * 2.0f / height - 1.0f);
				}
				else if (actionCode == 3) // cancelled because of this app was put to background (CANCELLED)
				{
					int pID = action >> MotionEvent.ACTION_POINTER_INDEX_SHIFT;
					
					EpicforceJNI.onMouseUp(0, pID, 
			 				  			   ev.getX()            * 2.0f / width - 1.0f, 
			 				  			   (height - ev.getY()) * 2.0f / height - 1.0f);
				}

				return true;
			}
		});
	}
	
	/*private static class XAPKFile
	{
		public final boolean mIsMain;
		public final int mFileVersion;
		public final long mFileSize;

		XAPKFile(boolean isMain, int fileVersion, long fileSize)
		{
			mIsMain = isMain;
			mFileVersion = fileVersion;
			mFileSize = fileSize;
		}
	}*/

	public void initAccelerationSensor()
	{
		List<Sensor> sensorList = sensorManager.getSensorList(Sensor.TYPE_ACCELEROMETER);

		gravity_x = 0.0f;
		gravity_y = 0.0f;
		gravity_z = 0.0f;

		if (sensorList.size() > 0)
		{
			accelerationSensorPresent = true;
			accelerationSensor = sensorList.get(0);
		}
		else
		{
			accelerationSensorPresent = false;
		}

		accelerationSensorListener = new SensorEventListener()
		{
			public void onAccuracyChanged(Sensor sensor, int accuracy)
			{
				// Log.d("EpicForce",
				// "accelerationSensorListener onAccuracyChanged: " + sensor +
				// ", accuracy: " + accuracy);
			}

			public void onSensorChanged(SensorEvent event)
			{
				synchronized (this)
				{
					// /////////////////////////////////////////////////////////////
					// acceleration
					float acceleration_x = event.values[0];
					float acceleration_y = event.values[1];
					float acceleration_z = event.values[2];

					// final float alpha = 0.8f;
					// gravity_x = alpha * gravity_x + (1 - alpha) *
					// acceleration_x;
					// gravity_y = alpha * gravity_y + (1 - alpha) *
					// acceleration_y;
					// gravity_z = alpha * gravity_z + (1 - alpha) *
					// acceleration_z;

					// float linear_acceleration_x = acceleration_x;// -
					// gravity_x;
					// float linear_acceleration_y = acceleration_y;// -
					// gravity_y;
					// float linear_acceleration_z = acceleration_z;// -
					// gravity_z;

					// EpicforceJNI.gameAppSetAcc(acceleration_x,
					// acceleration_y, acceleration_z);
					//mView.inputdata.setAcc(acceleration_x, acceleration_y,
							//acceleration_z);
					Display display = (EpicForceAndroidLauncherActivity.this).getWindowManager().getDefaultDisplay();
			        int orientation = display.getRotation();
			        if (orientation == Surface.ROTATION_0)
			        {
			        	EpicforceJNI.onAccelerationUpdate(acceleration_x, acceleration_y, acceleration_z);
			        }
			        else if (orientation == Surface.ROTATION_90)
			        {
			        	EpicforceJNI.onAccelerationUpdate(-acceleration_y, acceleration_x, acceleration_z);
			        }
			        else if (orientation == Surface.ROTATION_180)
			        {
			        	EpicforceJNI.onAccelerationUpdate(-acceleration_x, -acceleration_y, acceleration_z);
			        }
			        else if (orientation == Surface.ROTATION_270)
			        {
			        	EpicforceJNI.onAccelerationUpdate(acceleration_y, -acceleration_x, acceleration_z);
			        }
				}
			}
		};
	}	

    @Override protected void onCreate(Bundle icicle) 
    {
    	initDirectories(true);
		
        super.onCreate(icicle);
        mView = new EpicForceAndroidLauncherView(getApplication());
        setContentView(mView);
        
    	sensorManager = (SensorManager) getSystemService(SENSOR_SERVICE);
		initTouchSensor();
		initAccelerationSensor();
    }
    
	@Override
	protected void onDestroy()
	{
		super.onDestroy();
		
		if (accelerationSensorPresent)
			sensorManager.unregisterListener(accelerationSensorListener);		
	}
    
    @Override
    public void onStart()
    {
    	super.onStart();
    	
    	//mFMODAudioDevice.start();
    }
    
    @Override
    public void onStop()
    {
    	//mFMODAudioDevice.stop();
    	
    	super.onStop();
    }    

    @Override 
    protected void onPause() 
    {
        super.onPause();

        mView.onPause();
    }

    @Override 
    protected void onResume() 
    {
        super.onResume();
        
		if(accelerationSensorPresent)
			sensorManager.registerListener(accelerationSensorListener, accelerationSensor, SensorManager.SENSOR_DELAY_GAME);

        mView.onResume();
    }
}
