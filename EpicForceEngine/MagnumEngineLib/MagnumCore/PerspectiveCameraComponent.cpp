///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "PerspectiveCameraComponent.h"
using namespace Magnum;

PerspectiveCameraComponent::PerspectiveCameraComponent(Component::Owner &owner_)
: CameraComponent(owner_)
{
}

PerspectiveCameraComponent::~PerspectiveCameraComponent()
{
}

void PerspectiveCameraComponent::setProjection(float left_, float right_, float bottom_, float top_, float nearPlane_, float farPlane_)
{
	setProjectionPlanes(left_, right_, bottom_, top_, nearPlane_, farPlane_);
}

void PerspectiveCameraComponent::setProjection(float fovy_, float aspect_, float nearPlane_, float farPlane_)
{
	float halfy = Math::Tan(fovy_/2) * nearPlane_;
	float halfx = halfy * aspect_;

	setProjectionPlanes(-halfx, halfx, -halfy, halfy, nearPlane_, farPlane_);
}

void PerspectiveCameraComponent::getProjection(float &left_, float &right_, float &bottom_, float &top_, float &nearPlane_, float &farPlane_) const
{
	getProjectionPlanes(left_, right_, bottom_, top_, nearPlane_, farPlane_);
}

void PerspectiveCameraComponent::getProjection(float &fovy_, float &aspect_, float &nearPlane_, float &farPlane_) const
{
	float l, r, b, t, n, f;
	getProjectionPlanes(l, r, b, t, n, f);

	fovy_       = Math::ATan2(t, n) * 2;

	aspect_     = r / t;

	nearPlane_  = n;

	farPlane_   = f;
}

void PerspectiveCameraComponent::onDebugRender(IComponentDebugRenderer &debugRenderer)
{
	float l, r, b, t, n, f;
	getProjectionPlanes(l, r, b, t, n, f);

	debugRenderer.renderWireFrustum(this->getOwner().getGlobalTransform(),
									ColorRGBA(0.0, 1.0, 1.0, 0.5), 
									l, r, b, t, n, f);
}

void PerspectiveCameraComponent::onValidateProjectionTransform(Matrix4 &projectTransform) const
{
	float l, r, b, t, n, f;
	getProjectionPlanes(l, r, b, t, n, f);

	projectTransform.initPerspectiveOffCenter(l, r, b, t, n, f);
}
