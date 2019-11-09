///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _IComponentDebugRenderer_h_
#define _IComponentDebugRenderer_h_

#include "Stage.h"
#include "FileIO.h"
#include "Array.h"
#include "Delegate.h"
#include "Frame3.h"
#include "ColorRGBA.h"
#include "reflection.h"
using namespace agm::reflection;

namespace Magnum
{

class IComponentDebugRenderer
{
public:
	enum DrawMode
	{
		Points				= 0,
		Lines				= 1,
		LineStrip			= 2,
		Triangles			= 3,
		TriangleStrip		= 4,
		TriangleFan			= 5
	};

	IComponentDebugRenderer(const Matrix4 &projTransform, const Matrix4 &viewTransform);
	virtual ~IComponentDebugRenderer();

	const Matrix4 &getProjTransform() const;
	const Matrix4 &getViewTransform() const;

	void renderPoints(const Matrix4 &transform,
					const Vector3 *p, const ColorRGBA &color, int count);
	void renderPoints(const Matrix4 &transform,
					const Vector3 *p, const ColorRGBA *c, int count);
	void renderLines(const Matrix4 &transform,
				   const Vector3 *p, const ColorRGBA &color, int count);
	void renderLines(const Matrix4 &transform,
				   const Vector3 *p, const ColorRGBA *c, int count);
	void renderLineStrip(const Matrix4 &transform,
					   const Vector3 *p, const ColorRGBA &color, int count);
	void renderLineStrip(const Matrix4 &transform,
					   const Vector3 *p, const ColorRGBA *c, int count);
	void renderLineLoop(const Matrix4 &transform,
					  const Vector3 *p, const ColorRGBA &color, int count);
	void renderLineLoop(const Matrix4 &transform,
					  const Vector3 *p, const ColorRGBA *c, int count);
	void renderWireTriangles(const Matrix4 &transform, 
						   const Vector3 *p, const ColorRGBA &color, int count);
	void renderSolidTriangles(const Matrix4 &transform,
							const Vector3 *p, const ColorRGBA &color, int count);
	void renderWireTriangles(const Matrix4 &transform, 
						   const Vector3 *p, const ColorRGBA *c, int count);
	void renderSolidTriangles(const Matrix4 &transform,
							const Vector3 *p, const ColorRGBA *c, int count);
	void renderWireTriangleStrip(const Matrix4 &transform,
								const Vector3 *p, const ColorRGBA &color, int count);
	void renderSolidTriangleStrip(const Matrix4 &transform,
								const Vector3 *p, const ColorRGBA &color, int count);
	void renderWireTriangleStrip(const Matrix4 &transform,
							   const Vector3 *p, const ColorRGBA *c, int count);
	void renderSolidTriangleStrip(const Matrix4 &transform,
								const Vector3 *p, const ColorRGBA *c, int count);
	void renderWireTriangleFan(const Matrix4 &transform,
							  const Vector3 *p, const ColorRGBA &color, int count);
	void renderSolidTriangleFan(const Matrix4 &transform,
							  const Vector3 *p, const ColorRGBA &color, int count);
	void renderWireTriangleFan(const Matrix4 &transform,
							 const Vector3 *p, const ColorRGBA *c, int count);
	void renderSolidTriangleFan(const Matrix4 &transform,
							  const Vector3 *p, const ColorRGBA *c, int count);

	void renderGrid(const Matrix4 &transform, const ColorRGBA &color, const Vector3 &size, const Vector3 &extent, int boldInterval);

	void renderWireCircle(const Matrix4 &transform,
						  const ColorRGBA &color, float radius, int slices, float startTheta = 0, float endTheta = Math::TWO_PI);
	void renderSolidCircle(const Matrix4 &transform,
						   const ColorRGBA &color, float radius, int slices, float startTheta = 0, float endTheta = Math::TWO_PI);

	void renderWireSphere(const Matrix4 &transform,
						const ColorRGBA &color, float radius, int slices, int segments,
						float startTheta = 0, float endTheta = Math::TWO_PI,
						float startPhi = 0, float endPhi = Math::ONE_PI);
	void renderSolidSphere(const Matrix4 &transform,
						const ColorRGBA &color, float radius, int slices, int segments,
						float startTheta = 0, float endTheta = Math::TWO_PI,
						float startPhi = 0, float endPhi = Math::ONE_PI);

	void renderWireCapsule(const Matrix4 &transform,
						 const ColorRGBA &color, float radius, float height, int slices, int segments,
						 float startTheta = 0, float endTheta = Math::TWO_PI);
	void renderSolidCapsule(const Matrix4 &transform,
						 const ColorRGBA &color, float radius, float height, int slices, int segments, 
						 float startTheta = 0, float endTheta = Math::TWO_PI);

	void renderWireCylinder(const Matrix4 &transform,
						   const ColorRGBA &color, float radius, float height, int slices,
						   float startTheta = 0, float endTheta = Math::TWO_PI);
	void renderSolidCylinder(const Matrix4 &transform,
						   const ColorRGBA &color, float radius, float height, int slices, 
						   float startTheta = 0, float endTheta = Math::TWO_PI);

	void renderWireCone(const Matrix4 &transform, 
					  const ColorRGBA &color, float radius, float height, int slices, 
					  float startTheta = 0, float endTheta = Math::TWO_PI);
	void renderSolidCone(const Matrix4 &transform, 
					   const ColorRGBA &color, float radius, float height, int slices, 
					   float startTheta = 0, float endTheta = Math::TWO_PI);

	void renderWireBox(const Matrix4 &transform,
					 const ColorRGBA &color, const Vector3 &extent);
	void renderSolidBox(const Matrix4 &transform,
					 const ColorRGBA &color, const Vector3 &extent);

	void renderWireFrustum(const Matrix4 &transform,
						 const ColorRGBA &color, 
						 float l, float r, float b, float t, float n, float f);
	void renderSolidFrustum(const Matrix4 &transform, 
						  const ColorRGBA &color, 
						  float l, float r, float b, float t, float n, float f);
protected:
	void renderWireCircleCore(const Matrix4 &transform, 
							const ColorRGBA &color, 
							const Vector3 &offset, 
							float radius, int slices,
							float startTheta, float endTheta);


	void renderWireSphereCore(const Matrix4 &transform, 
							const ColorRGBA &color, 
							const Vector3 &offset, 
							float radius, int slices, int segments,
							float startTheta, float endTheta,
							float startPhi, float endPhi);

	void renderWireConeBody(const Matrix4 &transform, 
						  const ColorRGBA &color, const Vector3 &offset, 
						  float r0, float r1, float height, int slices,
						  float startTheta, float endTheta);

	void renderSolidConeCore(const Matrix4 &transform, 
						   const ColorRGBA &color, const Vector3 &offset, 
						   float radius, float height, int slices, float startTheta = 0, float endTheta = Math::TWO_PI);
	void renderSolidSphereCore(const Matrix4 &transform,
							 const ColorRGBA &color, const Vector3 &offset, 
							 float radius, int slices, int segments, 
							 float startTheta = 0, float endTheta = Math::TWO_PI,
							 float startPhi = 0, float endPhi = Math::ONE_PI);
	void renderSolidCylinderBody(const Matrix4 &transform, 
							   const ColorRGBA &color, 
							   const Vector3 &offset, 
							   float r0, float r1, float height, int slices, float startTheta, float endTheta);

	virtual void renderPrimitive(DrawMode mode, const Matrix4 &transform, const Vector3 *v, const ColorRGBA &color, int count) = 0;
	virtual void renderPrimitive(DrawMode mode, const Matrix4 &transform, const Vector3 *v, const ColorRGBA *c, int count) = 0;
private:

public:
protected:
	const Matrix4 &projTransform;
	const Matrix4 &viewTransform;
private:
};

};

#endif
