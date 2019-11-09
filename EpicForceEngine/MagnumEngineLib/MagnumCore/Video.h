///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Video_h_
#define _Video_h_

#include "Stage.h"
#include "List.h"
#include "EString.h"
#include "Array.h"
#include "ColorRGBA.h"
#include "Matrix4.h"

using namespace Magnum;

namespace Magnum
{

#define IS_PROCESSING_VIDEO (!Video::Manager::instance().isLocked())

class GXContext;
class CameraComponent;
class RendererBase;
class GXVertexBuffer;
class GXIndexBuffer;

/**
* Video Services
*/
class Video
{
public:
	/**
	* Video::Manager manage the all CameraComponent, RendererBase, and Graphics Context
	*/
	class Manager
	{
	friend class CameraComponent;
	friend class RendererBase;
	public:
		/**
		* Video::Manager::RenderParam provide neccessary data for rendering each camera pass
		* Mp = Projection transform
		* Mv = View transform
		* Mm = Model transform
		*/
		class RenderParam
		{
		public:
			RenderParam(CameraComponent &camera_);

			CameraComponent &cameraComponent;			/**< the current Rendering Camera */ 
			Matrix4 viewTransform;						/**< the Mv of the current Rendering Camera */ 
			Matrix4 projTransform;						/**< the Mp of the current Rendering Camera */ 
			Matrix4 projViewTransform;					/**< the Mp * Mv of the current Rendering Camera */ 

			Matrix4 viewTransformInverse;				/**< the Inverse of Mv of the current Rendering Camera */ 
			Matrix4 projTransformInverse;				/**< the Inverse of Mp of the current Rendering Camera */ 
			Matrix4 projViewTransformInverse;			/**< the Inverse of Mp * Mv of the current Rendering Camera */ 
		};

		Manager();
		virtual ~Manager();

		/**
		* Initiate the Services
		* @return true if success, false if failed
		*/
		bool initiate();

		/**
		* Update the Services
		*/
		void process();

		/**
		* Called when the application is pause(e.g system bring the app to background, let the service to release resources)
		*/
		void pause();

		/**
		* Called when the application is resume(e.g system bring back the app from background, let the service to reload resources)
		*/
		void resume();

		/**
		* Terminate the Services, called when the app is terminate.
		*/
		void terminate();

		/**
		* Call when the services needed to be clean up, e.g. during scene transition.
		*/
		void clear();

		/**
		* check if the Rendering is in process(locked)
		* @return true if locked, false if not locked
		*/
		bool isLocked() const;
		static void checkError(const char* op);
	protected:
	private:
		/**
		* Begin Rendering the Object for CameraComponent camera, with offset, and scale 
		* @param camera, CameraComponent which specify the camera
		* @param offsetX, the Screen Offset X of the viewport
		* @param offsetY, the Screen Offset Y of the viewport
		* @param scaleX, the Screen Scale X of the viewport
		* @param scaleT, the Screen Scale Y of the viewport
		*/
		void beginRender(const CameraComponent &camera, float offsetX, float offsetY, float scaleX, float scaleY);
		
		/**
		* Do rendering for editor Cameras 
		* @param cameraBasesSorted, const Vector<CameraComponent *> which specify the editor camera
		*/
		void renderEditorCameras(const Vector<CameraComponent *> &cameraBasesSorted);

		/**
		* Do rendering for Game Cameras 
		* @param cameraBasesSorted, const Vector<CameraComponent *> which specify the editor camera
		*/
		void renderGameCameras(const Vector<CameraComponent *> &cameraBasesSorted);

		/**
		* Do rendering for Physics BoundBox 
		* @param cameraBase, CameraComponent * which specify the physics camera
		*/
		void renderBox(CameraComponent &cameraBase);

		/**
		* End Rendering the Object for CameraComponent camera
		*/
		void endRender(const CameraComponent &camera);
	public:
	private:
		bool locked;

		GXContext						*context;
		Vector<CameraComponent*>		cameraComponents;
		Vector<RendererBase*>			renderers;
	public:
		static Manager					&instance();
		static GXContext				&getContext();
	private:
		static Manager					*_instance;
	};
protected:
private:

public:
////////////////////////////////////////////////////////////////////////////////////
	struct Service
	{
		/**
		* Initiate the Services
		* @return true if success, false if failed
		*/
		static bool initiate();

		/**
		* Update the Services
		*/
		static void process();

		/**
		* Called when the application is pause(e.g system bring the app to background, let the service to release resources)
		*/
		static void pause();

		/**
		* Called when the application is resume(e.g system bring back the app from background, let the service to reload resources)
		*/
		static void resume();

		/**
		* Terminate the Services, called when the app is terminate.
		*/
		static void terminate();

		/**
		* Call when the services needed to be clean up, e.g. during scene transition.
		*/
		static void clear();
	};
};

};

#endif
