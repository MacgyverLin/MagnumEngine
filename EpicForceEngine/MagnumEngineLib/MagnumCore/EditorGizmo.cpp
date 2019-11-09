///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Stage.h"
#include "EditorGizmo.h"
#include "CameraComponent.h"
#include "Entity.h"
#include "GXDebugRenderer.h"
using namespace Magnum;

EditorGizmo::EditorGizmo(Component::Owner &owner_)
: Graphics3Component(owner_)
, mode(EditorGizmo::DEFAULT)
, coordsys(EditorGizmo::VIEW)
{
}

EditorGizmo::~EditorGizmo()
{
}

void EditorGizmo::setMode(EditorGizmo::Mode mode_, EditorGizmo::CoordSys coordsys_)
{
	mode		= mode_;
	coordsys	= coordsys_;
}

EditorGizmo::Mode EditorGizmo::getMode() const
{
	return mode;
}

EditorGizmo::CoordSys EditorGizmo::getCoordSys() const
{
	return coordsys;
}

void EditorGizmo::render(const Video::Manager::RenderParam &param)
{
	if(!param.cameraComponent.isEditorModeActive())
		return;

	GXDebugRenderer drawer(GXContext::instance(), param.projTransform, param.viewTransform);
	
	renderGizmos(drawer);
	renderGrid(drawer);
	renderSelectedEntity(drawer);
}

void EditorGizmo::getRefTransform(Matrix4 &refTransform, EditorGizmo::CoordSys coordSys)
{
	refTransform	= Matrix4::IDENTITY;
	Entity *entity	= Entity::getSelected();
	if(!entity)
		return;

	Vector3 globalPosition(entity->getGlobalPosition());
	Entity *parent	= (Entity *)entity->getParent();

	if(coordSys==EditorGizmo::LOCAL)
	{
		refTransform = entity->getGlobalTransform();

		refTransform[0][3] = globalPosition[0];
		refTransform[1][3] = globalPosition[1];
		refTransform[2][3] = globalPosition[2];
	}
	else if(coordSys==EditorGizmo::PARENT)
	{
		if(parent)
			refTransform = parent->getGlobalTransform();
		else
			refTransform = Matrix4::IDENTITY;

		refTransform[0][3] = globalPosition[0];
		refTransform[1][3] = globalPosition[1];
		refTransform[2][3] = globalPosition[2];
	}
	else if(coordSys==EditorGizmo::WORLD)
	{
		refTransform = Matrix4::IDENTITY;

		refTransform[0][3] = globalPosition[0];
		refTransform[1][3] = globalPosition[1];
		refTransform[2][3] = globalPosition[2];
	}
	else //if(coordSys==EditorGizmo::VIEW)
	{
		refTransform = getOwner().getGlobalTransform();

		refTransform[0][3] = globalPosition[0];
		refTransform[1][3] = globalPosition[1];
		refTransform[2][3] = globalPosition[2];
	}
}

void EditorGizmo::renderGizmos(GXDebugRenderer drawer)
{
	Entity *entity = Entity::getSelected();
	if(!entity)
		return;

	GXContext::instance().enable(GXEnableMode::Blend);
	GXContext::instance().disable(GXEnableMode::DepthTest);
	GXContext::instance().setBlendStateRgb(GXBlendMode::Add, GXBlendFactor::SrcAlpha, GXBlendFactor::OneMinusSrcAlpha);

	if(mode==DEFAULT) // translate
	{
		renderDefaultGizmos(drawer);
	}
	else if(mode==TRANSLATE) // translate
	{
		renderTranslateGizmos(drawer);
	}
	else if(mode==ROTATE) // rotate
	{
		renderRotateGizmos(drawer);
	}
	else if(mode==SCALE) // scale
	{
		renderScaleGizmos(drawer);
	}

	GXContext::instance().disable(GXEnableMode::Blend);
	GXContext::instance().disable(GXEnableMode::DepthTest);
	GXContext::instance().setBlendStateRgb(GXBlendMode::Add, GXBlendFactor::SrcAlpha, GXBlendFactor::OneMinusSrcAlpha);
}

void EditorGizmo::renderAxis(const Matrix4 &refTransform, GXDebugRenderer drawer, float alpha)
{
	const Vector3 p[] = 
	{
		Vector3::ZERO,
		Vector3::UNIT_X * 5,
		Vector3::ZERO,
		Vector3::UNIT_Y * 5,
		Vector3::ZERO,
		Vector3::UNIT_Z * 5,
	};

	const ColorRGBA c[] = 
	{
		ColorRGBA(1, 0, 0, alpha),
		ColorRGBA(1, 0, 0, alpha),
		ColorRGBA(0, 1, 0, alpha),
		ColorRGBA(0, 1, 0, alpha),
		ColorRGBA(0, 0, 1, alpha),
		ColorRGBA(0, 0, 1, alpha),
	};

	drawer.renderLines(refTransform, p, c, 6);
}

void EditorGizmo::renderDefaultGizmos(GXDebugRenderer drawer)
{
	float alpha = 0.4f;

	Entity *entity = Entity::getSelected();

	Matrix4 offset;
	Matrix4 refTransform;
	getRefTransform(refTransform, getCoordSys());

	renderAxis(refTransform, drawer, alpha);
}

void EditorGizmo::renderTranslateGizmos(GXDebugRenderer drawer)
{
	float alpha = 0.8f;

	Entity *entity = Entity::getSelected();

	Matrix4 offset;
	Matrix4 refTransform;
	getRefTransform(refTransform, getCoordSys());

	renderAxis(refTransform, drawer, alpha);
	offset.initTranslateRotZXYScale(5, 0, 0, -Math::HALF_PI, 0, 0, 1);
	drawer.renderSolidCone(refTransform * offset, ColorRGBA(1, 0, 0, alpha), 0.5, 2, 5);
	offset.initTranslate(0, 5, 0);
	drawer.renderSolidCone(refTransform * offset, ColorRGBA(0, 1, 0, alpha), 0.5, 2, 5);
	offset.initTranslateRotZXYScale(0, 0, 5, 0, Math::HALF_PI, 0, 1);
	drawer.renderSolidCone(refTransform * offset, ColorRGBA(0, 0, 1, alpha), 0.5, 2, 5);
}

void EditorGizmo::renderRotateGizmos(GXDebugRenderer drawer)
{
	float alpha = 0.8f;

	Entity *entity = Entity::getSelected();

	Matrix4 offset;
	Matrix4 refTransform;
	getRefTransform(refTransform, getCoordSys());

	offset.initRotateZ(Math::HALF_PI);
	drawer.renderWireCircle(refTransform * offset, ColorRGBA(1, 0, 0, alpha), 10, 16);
	offset.initRotateZ(0);
	drawer.renderWireCircle(refTransform * offset, ColorRGBA(0, 1, 0, alpha), 10, 16);
	offset.initRotateX(Math::HALF_PI);
	drawer.renderWireCircle(refTransform * offset, ColorRGBA(0, 0, 1, alpha), 10, 16);

	getRefTransform(refTransform, EditorGizmo::VIEW);
	offset.initRotateX(Math::HALF_PI);
	drawer.renderWireCircle(refTransform * offset, ColorRGBA(0.3, 0.3, 0.3, alpha), 10, 16);
	drawer.renderWireCircle(refTransform * offset, ColorRGBA(0.5, 0.5, 0.5, alpha), 12, 16);
}

void EditorGizmo::renderScaleGizmos(GXDebugRenderer drawer)
{
	float alpha = 0.8f;

	Entity *entity = Entity::getSelected();

	Matrix4 offset;
	Matrix4 refTransform;
	getRefTransform(refTransform, getCoordSys());

	renderAxis(refTransform, drawer, alpha);
	offset.initTranslate(5, 0, 0);
	drawer.renderSolidBox(refTransform * offset, ColorRGBA(1, 0, 0, alpha), Vector3(0.5, 0.5, 0.5));
	offset.initTranslate(0, 5, 0);
	drawer.renderSolidBox(refTransform * offset, ColorRGBA(0, 1, 0, alpha), Vector3(0.5, 0.5, 0.5));
	offset.initTranslate(0, 0, 5);
	drawer.renderSolidBox(refTransform * offset, ColorRGBA(0, 0, 1, alpha), Vector3(0.5, 0.5, 0.5));
}

void EditorGizmo::renderSelectedEntity(GXDebugRenderer drawer)
{
	GXContext::instance().enable(GXEnableMode::Blend);
	GXContext::instance().enable(GXEnableMode::DepthTest);
	GXContext::instance().setBlendStateRgb(GXBlendMode::Add, GXBlendFactor::SrcAlpha, GXBlendFactor::OneMinusSrcAlpha);

	Entity *entity = Entity::getSelected();
	if(!entity)
		return;

	entity->debugRender(drawer);

	GXContext::instance().disable(GXEnableMode::Blend);
	GXContext::instance().disable(GXEnableMode::DepthTest);
	GXContext::instance().setBlendStateRgb(GXBlendMode::Add, GXBlendFactor::SrcAlpha, GXBlendFactor::OneMinusSrcAlpha);
}

void EditorGizmo::renderGrid(GXDebugRenderer drawer)
{
	GXContext::instance().enable(GXEnableMode::Blend);
	GXContext::instance().enable(GXEnableMode::DepthTest);
	GXContext::instance().setBlendStateRgb(GXBlendMode::Add, GXBlendFactor::SrcAlpha, GXBlendFactor::OneMinusSrcAlpha);

	drawer.renderGrid(Matrix4::IDENTITY, ColorRGBA(0.3, 0.3, 0.3, 0.5), Vector3(1, 1, 1), Vector3(100, 100, 100), 10);

	GXContext::instance().disable(GXEnableMode::Blend);
	GXContext::instance().disable(GXEnableMode::DepthTest);
	GXContext::instance().setBlendStateRgb(GXBlendMode::Add, GXBlendFactor::SrcAlpha, GXBlendFactor::OneMinusSrcAlpha);
}