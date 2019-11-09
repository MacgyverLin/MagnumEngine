///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _AudioStream_h_
#define _AudioStream_h_

#include "Stage.h"
#include "List.h"
#include "EString.h"
#include "Array.h"
#include "ColorRGBA.h"
#include "Matrix4.h"
#include "AudioSourceBase.h"
#include "ResourceAccess.h"
#include "ResourceImport.h"
#include "ResourcePath.h"
using namespace Magnum;

namespace Magnum
{

/**
* AudioStream.
* AudioStream is the class resposible for audio received
* @see AudioSourceBase
*/
class AudioStream : public AudioSourceBase
{
public:
	class ResourceImporter;

	#ifdef ENABLE_RESOURCE_IMPORT
	class ResourceImporter : public ResourceImport
	{
	friend class AudioStream;
	friend class AudioStream::ResourceImporter;
	public:
		/**
		* AudioStream ResourceImporter Constructor.
		* To Construct the AudioStream ResourceImporter for the owner.
		* @param path_, the path of the audio resource.
		*/
		ResourceImporter(const char *path_);

		/**
		* AudioStream ResourceImporter Destructor.
		* To Destructor the AudioStream ResourceImporter and remove from its owner.
		*/
		virtual ~ResourceImporter();

		DECLARE_RESOURCE_IMPORT(AudioStream::ResourceImporter, mp3, audiostream)
	
		/**
		* To initiate the resource import system.
		*/
		static bool initiate();

		/**
		* To terminate the resource import system.
		*/
		static void terminate();
	protected:
		virtual bool onExportFile(const char *srcFilename_, const char *dstFilename_);
		virtual bool onDeleteFile(const char *srcFilename_);
	private:
	public:
	};
	#endif
public:

//////////////////////////////////////////////////////////////
	/**
	* AudioStream Constructor.
	* To Construct the AudioStream for the owner.
	* @param owner_, the Component::Owner which owns this component.
	*/
	AudioStream(Component::Owner &owner);

	/**
	* AudioStream Destructor.
	* To Destruct AudioStream and remove from its owner.
	*/
	virtual ~AudioStream();

////////////////////////////////////////////////////////////////
	DECLARE_COMPONENT(AudioStream, AudioSourceBase, false)

	PROPERTY(ResourcePath, AudioStreamPath);
////////////////////////////////////////////////////////////////
public:
	/**
	* Start playing the audio.
	* @param loop, if true the audio will rewind to beginning.
	*/
	virtual bool play(bool loop);
protected:
private:
	/**
	* Handle Construct Event of the Component
	* @return true if construction is success, return false if fail
	*/
	virtual bool onConstruct();

	/**
	* Handle Start Event of the Component
	*/
	virtual void onStart();

	/**
	* Handle Update Event of the Component
	* @param delta elapse of the game cycle
	*/
	virtual void onUpdate(float dt);

	/**
	* Handle Pause Event of the Component
	*/
	virtual void onPause();

	/**
	* Handle Resume Event of the Component
	*/
	virtual void onResume();

	/**
	* Handle Stop Event of the Component
	*/
	virtual void onStop();

	/**
	* Handle Destruct Event of the Component
	*/
	virtual void onDestruct();

	/**
	* Handle Debuger Rendering Event of the Component
	*/
	virtual void onDebugRender(IComponentDebugRenderer &debugRenderer);
public:
protected:
private:
	void *soundHandle;
};

};

#endif