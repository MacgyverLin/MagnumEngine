///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "gldef.h"
#include "Video.h"
#include "CameraComponent.h"
#include "RendererBase.h"
#include "GXContext.h"
using namespace Magnum;

///////////////////////////////////////////////////////////////////////////////////
Video::Manager::RenderParam::RenderParam(CameraComponent &cameraComponent_)
: cameraComponent(cameraComponent_)
{
	viewTransform				= cameraComponent.getOwner().getInverseGlobalTransform();
	projTransform				= cameraComponent.getProjectionTransform();
	projViewTransform			= projTransform * viewTransform;

	viewTransformInverse		= viewTransform.Inverse();
	projTransformInverse		= projTransform.Inverse();
	projViewTransformInverse	= projViewTransform.Inverse();
}

///////////////////////////////////////////////////////////////////////////////////
Video::Manager *Video::Manager::_instance = 0;

Video::Manager::Manager()
: locked(true)
, context(0)
//, vertexBuffer(0)
//, indexBuffer(0)
{
	assert(_instance==0);

	_instance = this;
}

Video::Manager::~Manager()
{
	assert(_instance!=0);

	_instance = 0;
}


bool Video::Manager::initiate()
{
	int width, height;
	Stage::getScreenSize(width, height);
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	context = new GXContext(width, height, GXPixelFormat::R8G8B8A8, GXPixelFormat::D24S8, GXMultiSampleMode::None);
	if(!context)
		return false;

	return true;
}

void Video::Manager::process()
{
	locked = false;

	Vector<CameraComponent *> sortedCameraComponents(cameraComponents);
	sortedCameraComponents.sort(CameraComponent::compare);

	Video::Manager::getContext().enable(GXEnableMode::ScissorTest);
	Video::Manager::getContext().setScissor(0, 0, 0.5, 0.5);
	Video::Manager::getContext().setClearColor(0.1f, 0.3f, 0.3f, 0.0f);
	Video::Manager::getContext().clear(GXClearMask::All);
	Video::Manager::getContext().disable(GXEnableMode::ScissorTest);

	renderEditorCameras(sortedCameraComponents);
	renderGameCameras(sortedCameraComponents);

	Video::Manager::getContext().flush();
	Video::Manager::getContext().finish();

	locked = true;
}

void Video::Manager::pause()
{
}

void Video::Manager::resume()
{
}

void Video::Manager::terminate()
{
	renderers.destroy();
	cameraComponents.destroy();

	if(context)
	{
		delete context;
		context = 0;
	}
}

void Video::Manager::clear()
{
	renderers.destroy();
	cameraComponents.destroy();
}

bool Video::Manager::isLocked() const
{
	return locked;
}

Video::Manager &Video::Manager::instance()
{
	assert(_instance);

	return *_instance;
}

GXContext &Video::Manager::getContext()
{
	return *Video::Manager::instance().context;
}

void Video::Manager::beginRender(const CameraComponent &camera, float offsetX, float offsetY, float scaleX, float scaleY)
{
	assert(IS_PROCESSING_VIDEO);

	//if(renderTargetTexture)
		//renderTargetTexture->beginRender();

	if(camera.getClearFlags()==CameraComponent::CLEAR_NONE)
		return;
	else if(camera.getClearFlags()==CameraComponent::CLEAR_SKYBOX)
	{
		// do sky box
		return;
	}
	else 
	{
		GXClearMask mask = GXClearMask::None;
		if(camera.getClearFlags() & CameraComponent::CLEAR_COLOR)
		{
			const ColorRGBA clearColor = camera.getClearColor();
			Video::Manager::getContext().setClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
		
			mask = mask | GXClearMask::Color;
		}
		if(camera.getClearFlags() & CameraComponent::CLEAR_DEPTH)
		{
			float clearDepth = camera.getClearDepth();
			Video::Manager::getContext().setClearDepth(clearDepth);

			mask = mask | GXClearMask::Depth;
		}
		if(camera.getClearFlags() & CameraComponent::CLEAR_STENCIL)
		{
			int clearStencil = Video::Manager::getContext().getClearStencil();
			Video::Manager::getContext().setClearStencil(clearStencil);

			mask = mask | GXClearMask::Stencil;
		}

		if( Stage::isEditorMode() )
		{
			Vector4 viewport(camera.getViewport());
			//float vp_x, vp_y, vp_width, vp_height;
			//camera.getViewport(vp_x, vp_y, vp_width, vp_height);

			float viewportX			= (viewport[0]	* scaleX + offsetX	)	* Stage::getScreenWidth();
			float viewportY			= (viewport[1]	* scaleY + offsetY	)	* Stage::getScreenHeight();
			float viewportWidth		= (viewport[2]	* scaleX			)	* Stage::getScreenWidth();
			float viewportHeight	= (viewport[3]	* scaleY			)	* Stage::getScreenHeight();

			float previewClipX		= (0			* scaleX + offsetX	)	* Stage::getScreenWidth();
			float previewClipY		= (0			* scaleY + offsetY	)	* Stage::getScreenHeight();
			float previewClipWidth	= (1			* scaleX			)	* Stage::getScreenWidth();
			float previewClipHeight	= (1			* scaleY			)	* Stage::getScreenHeight();

			Video::Manager::getContext().setViewport(viewportX, viewportY, viewportWidth, viewportHeight);
			Video::Manager::getContext().enable(GXEnableMode::ScissorTest);
			Video::Manager::getContext().setScissor(previewClipX, previewClipY, previewClipWidth, previewClipHeight);
			Video::Manager::getContext().clear(mask);
			//Video::Manager::getContext().disable(GXEnableMode::ScissorTest);
		}
		else
		{
			Vector4 viewport(camera.getViewport());

			float viewportX			= (viewport[0]	* scaleX + offsetX	)	* Stage::getScreenWidth();
			float viewportY			= (viewport[1]	* scaleY + offsetY	)	* Stage::getScreenHeight();
			float viewportWidth		= (viewport[2]	* scaleX			)	* Stage::getScreenWidth();
			float viewportHeight	= (viewport[3]	* scaleY			)	* Stage::getScreenHeight();

			Video::Manager::getContext().setViewport(viewportX, viewportY, viewportWidth, viewportHeight);
			Video::Manager::getContext().enable(GXEnableMode::ScissorTest);
			Video::Manager::getContext().setScissor(viewportX, viewportY, viewportWidth, viewportHeight);
			Video::Manager::getContext().clear(mask);
			//Video::Manager::getContext().disable(GXEnableMode::ScissorTest);
		}
	}
}

void Video::Manager::renderEditorCameras(const Vector<CameraComponent *> &cameras)
{
	for(int i=0; i<cameras.length(); i++)
	{
		CameraComponent &camera = *cameras[i];

		if(camera.getOwner().getActive() && camera.isEditorModeActive() && Stage::isEditorMode()) // draw editor camera
		{
			Video::Manager::RenderParam param(camera);

			Vector<RendererBase *> sortedRenderers(renderers);
			sortedRenderers.sort(RendererBase::compare);

			beginRender(camera, 0, 0, 1, 1);

			for(int j=0; j<sortedRenderers.length(); j++)
			{
				RendererBase &renderer = *sortedRenderers[j];

				if( renderer.getEnabled() )
				{
					renderer.render(param);
				}
			}

			/*
			if(camera.getRenderTargetTexture())
			{
				for(int i=0; i<camera.filters.length(); i++)
				{
					Video::BaseFilter &filter = *camera.getFilter(i);
					if( filter.getEnabled() )
					{
						filter.prepare(param);
						filter.render(param);
						filter.restore(param);
					}
				}
			}
			*/
			
			renderBox(camera);

			endRender(camera);
		}
	}
}

#include "Scene.h"

void Video::Manager::renderGameCameras(const Vector<CameraComponent *> &cameras)
{
	float offsety = 0;
	for(int i=0; i<cameras.length(); i++)
	{
		CameraComponent &camera = *cameras[i];

		if(camera.getOwner().getActive() && !camera.isEditorModeActive())
		{
			Video::Manager::RenderParam param(camera);

			Vector<RendererBase *> sortedRenderers(renderers);
			sortedRenderers.sort(RendererBase::compare);

			if(Stage::isEditorMode())
				beginRender(camera, 0.8, offsety, 0.2, 0.2);
			else
				beginRender(camera, 0.0, 0.0, 1.0, 1.0);

			for(int j=0; j<sortedRenderers.length(); j++)
			{
				RendererBase &renderer = *sortedRenderers[j];

				if( renderer.getEnabled() )
					renderer.render(param);
			}

			/*
			if(camera.getRenderTargetTexture())
			{
				for(int i=0; i<camera.filters.length(); i++)
				{
					Video::BaseFilter &filter = *camera.getFilter(i);
					if( filter.getEnabled() )
					{
						filter.prepare(param);
						filter.render(param);
						filter.restore(param);
					}
				}
			}
			*/

			if(Stage::isEditorMode())
				renderBox(camera);

			offsety+=0.2;

			endRender(camera);
		}
	}
}

void Video::Manager::renderBox(CameraComponent &cameraBase)
{
	Matrix4 projMat;
	projMat.initOrthogonalOffCenter(0, 1, 0, 1, 1, 100);

	Vector3 pos[] = 
	{
		Vector3(0, 0, -1),
		Vector3(1, 0, -1),
		Vector3(1, 1, -1),
		Vector3(0, 1, -1),
		Vector3(0, 0, -1),
	};

	Video::Manager::getContext().draw(GXDrawMode::LineStrip, projMat, Matrix4::IDENTITY, Matrix4::IDENTITY, &pos[0], ColorRGBA(1, 1, 1, 1), 5);
}

void Video::Manager::endRender(const CameraComponent &camera)
{
	assert(IS_PROCESSING_VIDEO);

	Video::Manager::getContext().flush();

	//if(renderTargetTexture)
		//renderTargetTexture->endRender();
}

void Video::Manager::checkError(const char* op)
{
	for (GLint error = glGetError(); error; error = glGetError())
	{
		debug("after %s() glError (0x%x)\n", op, error);
	}
}

///////////////////////////////////////////////////////////////////////////////////
bool Video::Service::initiate()
{
	return Video::Manager::instance().initiate();
}

void Video::Service::process()
{
	Video::Manager::instance().process();
}

void Video::Service::pause()
{
	Video::Manager::instance().pause();
}

void Video::Service::resume()
{
	Video::Manager::instance().resume();
}

void Video::Service::terminate()
{
	Video::Manager::instance().terminate();
}

void Video::Service::clear()
{
	Video::Manager::instance().clear();
}