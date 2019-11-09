///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "EditorGizmoRenderer.h"
#include "EditorGizmo.h"
#include "CameraComponent.h"
using namespace Magnum;

EditorGizmoRenderer::EditorGizmoRenderer(Component::Owner &owner_)
: RendererBase(owner_)
, editorGizmo(0)
{
}

EditorGizmoRenderer::~EditorGizmoRenderer()
{
}

void EditorGizmoRenderer::add(EditorGizmo &editorGizmo_)
{
	editorGizmo = &editorGizmo_;
}

void EditorGizmoRenderer::remove(EditorGizmo &editorGizmo_)
{
	editorGizmo = 0;
}

void EditorGizmoRenderer::render(const Video::Manager::RenderParam &param)
{
	if(!param.cameraComponent.isEditorModeActive())
		return;

	if(editorGizmo)
		editorGizmo->render(param);
}