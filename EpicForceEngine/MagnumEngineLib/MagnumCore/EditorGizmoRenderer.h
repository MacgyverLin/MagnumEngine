///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _EditorGizmoRenderer_h_
#define _EditorGizmoRenderer_h_

#include "Stage.h"
#include "RendererBase.h"
#include "EditorGizmo.h"
#include "GXContext.h"
#include "GXDebugRenderer.h"
using namespace Magnum;

namespace Magnum
{

/**
* EditorGizmoRenderer.
* EditorGizmoRenderer render EditorGizmo on editor screen. EditorGizmo are those mover icon, rotator icon, scaler icon, grid on editor screen
* @see RendererBase, EditorGizmo
*/
class EditorGizmoRenderer : public RendererBase
{
friend class EditorGizmo;
////////////////////////////////////////////////////////////////
public:
	/**
	* EditorGizmoRenderer Constructor.
	* To Construct the EditorGizmoRenderer for the owner.
	* @param owner_, the Component::Owner which owns this component.
	*/
	EditorGizmoRenderer(Component::Owner &owner_);

	/**
	* EditorGizmoRenderer Destructor.
	* To Destruct EditorGizmoRenderer and remove from its owner.
	*/
	virtual ~EditorGizmoRenderer();

	DECLARE_COMPONENT(EditorGizmoRenderer, RendererBase, false)
////////////////////////////////////////////////////////////////
public:
	/**
	* Get the Order of this renderer.
	* The Renderer will sort all the renderer in acending order. The order is returned by this function.
	*/
	virtual int getOrder() const
	{
		return 0x7fffffff;
	}

	/**
	* add EditorGizmo to the Renderer.
	* @param editorGizmo, an EditorGizmo
	* @see EditorGizmo
	*/
	void add(EditorGizmo &editorGizmo);

	/**
	* remove EditorGizmo from the Renderer.
	* @param editorGizmo, an EditorGizmo
	* @see EditorGizmo
	*/
	void remove(EditorGizmo &editorGizmo);
protected:
private:
	virtual void render(const Video::Manager::RenderParam &param);
public:
protected:
private:
	EditorGizmo *editorGizmo;
};

};

#endif
