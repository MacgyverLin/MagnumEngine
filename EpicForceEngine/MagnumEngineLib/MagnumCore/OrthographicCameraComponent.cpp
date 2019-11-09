///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "OrthographicCameraComponent.h"
using namespace Magnum;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OrthographicCameraComponent::OrthographicCameraComponent(Component::Owner &owner_)
: CameraComponent(owner_)
{
}

OrthographicCameraComponent::~OrthographicCameraComponent()
{
}

void OrthographicCameraComponent::setProjection(float left_, float right_, float bottom_, float top_, float nearPlane_, float farPlane_)
{
	setProjectionPlanes(left_, right_, bottom_, top_, nearPlane_, farPlane_);
}

void OrthographicCameraComponent::getProjection(float &left_, float &right_, float &bottom_, float &top_, float &nearPlane_, float &farPlane_) const
{
	getProjectionPlanes(left_, right_, bottom_, top_, nearPlane_, farPlane_);
}

void OrthographicCameraComponent::onDebugRender(IComponentDebugRenderer &debugRenderer)
{
	float l, r, b, t, n, f;
	getProjectionPlanes(l, r, b, t, n, f);

	Matrix4 transform(this->getOwner().getGlobalTransform());
	
	transform[0][3] = (r+l)/2;
	transform[1][3] = (t+b)/2;
	transform[2][3] = ((-f)+(-n))/2;

	debugRenderer.renderWireBox(transform,
								ColorRGBA(0.0, 1.0, 1.0, 0.5), 
								Vector3((r-l)/2, (t-b)/2, ((-f)-(-n))/2) );
}

void OrthographicCameraComponent::onValidateProjectionTransform(Matrix4 &projectTransform) const
{
	float l, r, b, t, n, f;
	getProjectionPlanes(l, r, b, t, n, f);

	projectTransform.initOrthogonalOffCenter(l, r, b, t, n, f);
}