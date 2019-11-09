///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "CameraComponent.h"
#include "GXContext.h"
using namespace Magnum;

CameraComponent::CameraComponent(Component::Owner &owner_)
: Component(owner_)
, projectTransform(Matrix4::IDENTITY)
, projectTransformValid(false)
// , renderTargetTexture(0)
, l(-1), r(1), b(-1), t(1), n(1), f(1000)
{
	setOrder(0);
	setTargetLayer(0xffffffff);
	setClearFlags(CLEAR_COLOR | CLEAR_DEPTH);
	setClearColor(ColorRGBA::BLACK);
	setClearDepth(1.0f);
	setClearStencil(0xff);

	setViewport(Vector4(0, 0, 1, 1));

	Video::Manager::instance().cameraComponents.push() = this;
}

CameraComponent::~CameraComponent()
{
	int idx = Video::Manager::instance().cameraComponents.search(this);
	if(idx>=0)
	{
		Video::Manager::instance().cameraComponents.remove(idx);
	}
}

int CameraComponent::compare(const void *left, const void *right)
{
	return (*((const CameraComponent **)left))->getOrder() - (*((const CameraComponent **)right))->getOrder();
}

/*
void CameraComponent::setRenderTargetTexture(RenderTargetTexture *renderTargetTexture_)
{
	renderTargetTexture = renderTargetTexture_;
}

void CameraComponent::appendFilter(BaseFilter *filter_)
{
	filters.push() = filter_;
}

void CameraComponent::insertFilter(int at, BaseFilter *filter_)
{
	filters.insert(at) = filter_;
}

void CameraComponent::removeFilter(BaseFilter *filter_)
{
	int idx = filters.search(filter_);
	if(idx>=0)
		filters.remove(idx);
}

BaseFilter *CameraComponent::getFilter(int i_) const
{
	return filters[i_];
}

int CameraComponent::getNumFilters() const
{
	return filters.length();
}
*/

void CameraComponent::setProjectionPlanes(float left_, float right_, float bottom_, float top_, float nearPlane_, float farPlane_)
{
	l = left_		;
	r = right_		;
	b = bottom_		;
	t = top_		;
	n = nearPlane_	;
	f = farPlane_	;

	inValidateProjectionTransform();
}

void CameraComponent::getProjectionPlanes(float &left_, float &right_, float &bottom_, float &top_, float &nearPlane_, float &farPlane_) const
{
	left_		= l;
	right_		= r;
	bottom_		= b;
	top_		= t;
	nearPlane_	= n;
	farPlane_	= f;
}

const Matrix4 &CameraComponent::getProjectionTransform()
{
	validateProjectionTransform();

	return projectTransform;
}

bool CameraComponent::isLayerMatched(unsigned int layer) const
{
	return (getTargetLayer() & layer)!=0;
}

/*
RenderTargetTexture *CameraComponent::getRenderTargetTexture()
{
	return renderTargetTexture;
}
*/

bool CameraComponent::onConstruct()
{
	return true;
}

void CameraComponent::onStart()
{
}

void CameraComponent::onUpdate(float dt)
{
}

void CameraComponent::onPause()
{
}

void CameraComponent::onResume()
{
}

void CameraComponent::onStop()
{
}

void CameraComponent::onDestruct()
{
}

void CameraComponent::inValidateProjectionTransform()
{
	projectTransformValid = false;
}

void CameraComponent::validateProjectionTransform()
{
	if( projectTransformValid )
		return;

	onValidateProjectionTransform(projectTransform);

	projectTransformValid = true;
}

bool CameraComponent::isProjectionTransformValid() const
{
	return projectTransformValid;
}