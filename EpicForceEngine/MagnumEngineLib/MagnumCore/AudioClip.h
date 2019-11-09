///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _AudioClip_h_
#define _AudioClip_h_

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
* AudioClip.
* AudioClip is the class resposible for audio received
* @see AudioSourceBase
*/
class AudioClip : public AudioSourceBase
{
public:
	class Resource;
	class ResourceImporter;

	class Data
	{
	friend class AudioClip;
	friend class AudioClip::Resource;
	friend class AudioClip::ResourceImporter;
	public:
		Data();
		~Data();

		void read(InputStream &is);
		void write(OutputStream &os) const;
	private:
	};

	/**
	* AudioClip::Resource
	* AudioClip::Resource is the class resposible for audio clip resource
	* @see ResourceAccess
	*/
	class Resource : public ResourceAccess
	{
	friend class AudioClip;
	friend class AudioClip::Resource;
	friend class AudioClip::ResourceImporter;
	public:
		/**
		* AudioClip Resource Constructor.
		* To Construct the AudioClip Resource
		* @param path_, the path of the audio resource.
		*/
		Resource(const char *path_);

		/**
		* AudioClip Resource Destructor.
		* To Destructor the AudioClip Resource
		*/
		virtual ~Resource();

		DECLARE_RESOURCE(AudioClip::Resource, audioclip)
		/**
		* Get the Handle of Audio CLip.
		* @return, the handle of audio clip
		*/
		void *getHandle() const;
	protected:
		virtual unsigned char *onCreate(int length);
		virtual void onLoaded();
		virtual void onDestroy();
	private:
		void					*soundHandle;
		Vector<unsigned char>	buffer;
	};

	#ifdef ENABLE_RESOURCE_IMPORT
	/**
	* AudioClip::ResourceImporter
	* AudioClip::ResourceImporter is the class resposible for audio clip resource
	* @see ResourceAccess
	*/
	class ResourceImporter : public ResourceImport
	{
	friend class AudioClip;
	friend class AudioClip::Resource;
	friend class AudioClip::ResourceImporter;
	public:
		/**
		* AudioClip ResourceImporter Constructor.
		* To Construct the AudioClip ResourceImporter
		* @param path_, the path of the audio resource.
		*/
		ResourceImporter(const char *path_);

		/**
		* AudioClip ResourceImporter Destructor.
		* To Destructor the AudioClip ResourceImporter
		*/
		virtual ~ResourceImporter();

		DECLARE_RESOURCE_IMPORT(AudioClip::ResourceImporter, wav, audioclip)
	
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
	* AudioClip Constructor.
	* To Construct the AudioClip for the owner.
	* @param owner_, the Component::Owner which owns this component.
	*/
	AudioClip(Component::Owner &owner);

	/**
	* AudioClip Destructor.
	* To Destruct AudioClip and remove from its owner.
	*/
	virtual ~AudioClip();

	DECLARE_COMPONENT(AudioClip, AudioSourceBase, false)
////////////////////////////////////////////////////////////////

	PROPERTY(ResourcePath, AudioClipPath);
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
	AudioClip::Resource *resource;
};

};

#endif