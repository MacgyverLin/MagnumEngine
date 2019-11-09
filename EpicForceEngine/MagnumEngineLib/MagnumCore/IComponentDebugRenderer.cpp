///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "IComponentDebugRenderer.h"
using namespace Magnum;

IComponentDebugRenderer::IComponentDebugRenderer(const Matrix4 &projTransform_, const Matrix4 &viewTransform_)
: projTransform(projTransform_)
, viewTransform(viewTransform_)
{
}

IComponentDebugRenderer::~IComponentDebugRenderer()
{
}

const Matrix4 &IComponentDebugRenderer::getProjTransform() const
{
	return projTransform;
}

const Matrix4 &IComponentDebugRenderer::getViewTransform() const
{
	return viewTransform;
}

void IComponentDebugRenderer::renderPoints(const Matrix4 &transform,
									       const Vector3 *p, const ColorRGBA &color, int count)
{
	renderPrimitive(IComponentDebugRenderer::Points, transform, p, color, count);
}

void IComponentDebugRenderer::renderPoints(const Matrix4 &transform, 
	                                    const Vector3 *p, const ColorRGBA *c, int count)
{
	renderPrimitive(IComponentDebugRenderer::Points, transform, p, c, count);
}

void IComponentDebugRenderer::renderLines(const Matrix4 &transform, 
	                                   const Vector3 *p, const ColorRGBA &color, int count)
{
	renderPrimitive(IComponentDebugRenderer::Lines, transform, p, color, count);
}

void IComponentDebugRenderer::renderLines(const Matrix4 &transform, 
									   const Vector3 *p, const ColorRGBA *c, int count)
{
	renderPrimitive(IComponentDebugRenderer::Lines, transform, p, c, count);
}

void IComponentDebugRenderer::renderLineStrip(const Matrix4 &transform, 
	                                       const Vector3 *p, const ColorRGBA &color, int count)
{
	renderPrimitive(IComponentDebugRenderer::LineStrip, transform, p, color, count);
}

void IComponentDebugRenderer::renderLineStrip(const Matrix4 &transform, 
										   const Vector3 *p, const ColorRGBA *c, int count)
{
	renderPrimitive(IComponentDebugRenderer::LineStrip, transform, p, c, count);
}

void IComponentDebugRenderer::renderLineLoop(const Matrix4 &transform, 
										  const Vector3 *p, const ColorRGBA &color, int count)
{
	renderPrimitive(IComponentDebugRenderer::LineStrip, transform, p, color, count);

	Vector3 pLoop[] =
	{
		p[0],
		p[count-1]
	};
	renderPrimitive(IComponentDebugRenderer::Lines, transform, pLoop, color, 2);
}

void IComponentDebugRenderer::renderLineLoop(const Matrix4 &transform, 
										  const Vector3 *p, const ColorRGBA *c, int count)
{
	renderPrimitive(IComponentDebugRenderer::LineStrip, transform, p, c, count);

	Vector3 pLoop[] =
	{
		p[0],
		p[count-1]
	};
	ColorRGBA cLoop[] =
	{
		c[0],
		c[count-1]
	};
	renderPrimitive(IComponentDebugRenderer::Lines, transform, pLoop, cLoop, 2);
}

void IComponentDebugRenderer::renderWireTriangles(const Matrix4 &transform, 
											   const Vector3 *p, const ColorRGBA &color, int count)
{
	for(int i=0; i<count; i+=3)
	{
		Vector3 temp[] =
		{
			p[i+0],
			p[i+1],
			p[i+2],
			p[i+0],
		};
		renderPrimitive(IComponentDebugRenderer::LineStrip, transform, temp, color, 4);
	}
}

void IComponentDebugRenderer::renderWireTriangles(const Matrix4 &transform, const Vector3 *p, const ColorRGBA *c, int count)
{
	for(int i=0; i<count; i+=3)
	{
		Vector3 tempP[] =
		{
			p[i+0],
			p[i+1],
			p[i+2],
			p[i+0],
		};

		ColorRGBA tempC[] =
		{
			c[i+0],
			c[i+1],
			c[i+2],
			c[i+0],
		};
		renderPrimitive(IComponentDebugRenderer::LineStrip, transform, tempP, tempC, 4);
	}
}

void IComponentDebugRenderer::renderWireTriangleStrip(const Matrix4 &transform, 
												   const Vector3 *p, const ColorRGBA &color, int count)
{
	for(int i=0; i<count-2; i++)
	{
		Vector3 temp[] =
		{
			p[i+0],
			p[i+1],
			p[i+2],
			p[i+0],
		};
		renderPrimitive(IComponentDebugRenderer::LineStrip, transform, temp, color, 4);
	}
}

void IComponentDebugRenderer::renderWireTriangleStrip(const Matrix4 &transform, const Vector3 *p, const ColorRGBA *c, int count)
{
	for(int i=0; i<count-2; i++)
	{
		Vector3 tempP[] =
		{
			p[i+0],
			p[i+1],
			p[i+2],
			p[i+0],
		};

		ColorRGBA tempC[] =
		{
			c[i+0],
			c[i+1],
			c[i+2],
			c[i+0],
		};
		renderPrimitive(IComponentDebugRenderer::LineStrip, transform, tempP, tempC, 4);
	}
}

void IComponentDebugRenderer::renderWireTriangleFan(const Matrix4 &transform, 
												 const Vector3 *p, const ColorRGBA &color, int count)
{
	for(int i=0; i<count-2; i++)
	{
		Vector3 tempP[] =
		{
			p[0],
			p[i+1],
			p[i+2],
			p[0],
		};

		renderPrimitive(IComponentDebugRenderer::LineStrip, transform, tempP, color, 4);
	}
}

void IComponentDebugRenderer::renderWireTriangleFan(const Matrix4 &transform, const Vector3 *p, const ColorRGBA *c, int count)
{
	for(int i=0; i<count-2; i++)
	{
		Vector3 tempP[] =
		{
			p[0],
			p[i+1],
			p[i+2],
			p[0],
		};

		ColorRGBA tempC[] =
		{
			c[0],
			c[i+1],
			c[i+2],
			c[0],
		};
		renderPrimitive(IComponentDebugRenderer::LineStrip, transform, tempP, tempC, 4);
	}
}

void IComponentDebugRenderer::renderSolidTriangles(const Matrix4 &transform, 
										        const Vector3 *p, const ColorRGBA &color, int count)
{
	renderPrimitive(IComponentDebugRenderer::Triangles, transform, p, color, count);
}

void IComponentDebugRenderer::renderSolidTriangles(const Matrix4 &transform, 
										        const Vector3 *p, const ColorRGBA *c, int count)
{
	renderPrimitive(IComponentDebugRenderer::Triangles, transform, p, c, count);
}

void IComponentDebugRenderer::renderSolidTriangleStrip(const Matrix4 &transform, 
													const Vector3 *p, const ColorRGBA &color, int count)
{
	renderPrimitive(IComponentDebugRenderer::TriangleStrip, transform, p, color, count);
}

void IComponentDebugRenderer::renderSolidTriangleStrip(const Matrix4 &transform, 
													const Vector3 *p, const ColorRGBA *c, int count)
{
	renderPrimitive(IComponentDebugRenderer::TriangleStrip, transform, p, c, count);
}

void IComponentDebugRenderer::renderSolidTriangleFan(const Matrix4 &transform, 
												  const Vector3 *p, const ColorRGBA &color, int count)
{
	renderPrimitive(IComponentDebugRenderer::TriangleFan, transform, p, color, count);
}

void IComponentDebugRenderer::renderSolidTriangleFan(const Matrix4 &transform, 
												  const Vector3 *p, const ColorRGBA *c, int count)
{
	renderPrimitive(IComponentDebugRenderer::TriangleFan, transform, p, c, count);
}

void IComponentDebugRenderer::renderGrid(const Matrix4 &transform, const ColorRGBA &color, const Vector3 &size, const Vector3 &extent,  int boldInterval)
{
	Vector3 v[2];
	int xCount = extent.X() * 2 / size.X();
	for(int x=0; x<xCount; x++)
	{
		v[0].X() = x * size.X() - extent.X();
		v[0].Y() = 0;
		v[0].Z() = -extent.Z();

		v[1].X() = v[0].X();
		v[1].Y() = v[0].Y();
		v[1].Z() = extent.Z();

		if(x % boldInterval)
			renderLines(transform, v, color, 2);
		else
			renderLines(transform, v, ColorRGBA(color.R()*2, color.G()*2, color.B()*2, color.A()), 2);			
	}

	int zCount = extent.Z() * 2 / size.Z();
	for(int z=0; z<zCount; z++)
	{
		v[0].X() = -extent.X();
		v[0].Y() = 0;
		v[0].Z() = z * size.Z() - extent.Z();

		v[1].X() = extent.X();
		v[1].Y() = v[0].Y();
		v[1].Z() = v[0].Z();

		if(z % boldInterval)
			renderLines(transform, v, color, 2);
		else
			renderLines(transform, v, ColorRGBA(color.R()*2, color.G()*2, color.B()*2, color.A()), 2);			
	}
}

void IComponentDebugRenderer::renderWireCircle(const Matrix4 &transform, 
	                                        const ColorRGBA &color, float radius, int slices,
											float startTheta, float endTheta)
{
	renderWireCircleCore(transform, color, 
					   Vector3::ZERO, 
					   radius, slices,
					   startTheta, endTheta);
}

void IComponentDebugRenderer::renderSolidCircle(const Matrix4 &transform,
											 const ColorRGBA &color, float radius, int slices, 
											 float startTheta, float endTheta)
{
	// renderSolidConeCore(transform, color, Vector3::ZERO, radius, 0, slices, startTheta, endTheta);
	renderSolidCylinderBody(transform, color, 
						  Vector3::ZERO,
						  radius, 0,
						  0, slices, startTheta, endTheta);
}

void IComponentDebugRenderer::renderWireSphere(const Matrix4 &transform, 
										    const ColorRGBA &color, float radius, int slices, int segments,
											float startTheta, float endTheta,
											float startPhi, float endPhi)
{
	renderWireSphereCore(transform, color, 
					   Vector3::ZERO,
					   radius, slices, segments,
					   startTheta, endTheta,
					   startPhi, endPhi);
}

void IComponentDebugRenderer::renderSolidSphere(const Matrix4 &transform, 
											 const ColorRGBA &color, float radius, int slices, int segments,
											 float startTheta, float endTheta,
											 float startPhi, float endPhi)
{
	renderSolidSphereCore(transform, color, Vector3::ZERO, radius, slices, segments, startTheta, endTheta, startPhi, endPhi);
}

void IComponentDebugRenderer::renderWireCapsule(const Matrix4 &transform, 
										     const ColorRGBA &color, float radius, float height, int slices, int segments,
											 float startTheta, float endTheta)
{
	renderWireSphereCore(transform, color, Vector3(0, height, 0), radius, slices, segments/2, startTheta, endTheta,              0, Math::ONE_PI/2);
	renderWireSphereCore(transform, color, Vector3(0,	  0, 0), radius, slices, segments/2, startTheta, endTheta, Math::ONE_PI/2, Math::ONE_PI  );

	renderWireConeBody(transform, color, Vector3(0, 0, 0), radius, radius, height, slices, startTheta, endTheta);
}

void IComponentDebugRenderer::renderSolidCapsule(const Matrix4 &transform, 
											  const ColorRGBA &color, float radius, float height, int slices, int segments, 
											  float startTheta, float endTheta)
{
	renderSolidCylinderBody(transform, color, Vector3::ZERO, radius, radius, height, slices, startTheta, endTheta);

	renderSolidSphereCore(transform, color, Vector3(0, height, 0), radius, slices, segments/2, startTheta, endTheta,              0, Math::ONE_PI/2);
	renderSolidSphereCore(transform, color, Vector3::ZERO        , radius, slices, segments/2, startTheta, endTheta, Math::ONE_PI/2, Math::ONE_PI  );
}

void IComponentDebugRenderer::renderWireCylinder(const Matrix4 &transform,
											  const ColorRGBA &color, float radius, float height, int slices, 
											  float startTheta, float endTheta)
{
	renderWireCircleCore(transform, color, Vector3::ZERO, radius, slices, startTheta, endTheta);
	renderWireCircleCore(transform, color, Vector3(0, height, 0), radius, slices, startTheta, endTheta);
	
	renderWireConeBody(transform, color, Vector3(0, 0, 0), radius, radius, height, slices, startTheta, endTheta);
}

void IComponentDebugRenderer::renderSolidCylinder(const Matrix4 &transform,
											   const ColorRGBA &color, float radius, float height, int slices, 
											   float startTheta, float endTheta)
{
	renderSolidCylinderBody(transform, color, Vector3::ZERO, radius, radius, height, slices, startTheta, endTheta);

	renderSolidCylinderBody(transform, color, 
						  Vector3::ZERO,
						  radius, 0,
						  0, slices, startTheta, endTheta);

	renderSolidCylinderBody(transform, color, 
						  Vector3(0, height, 0),
						  radius, 0,
						  0, slices, startTheta, endTheta);

	//renderSolidConeCore(transform, color, Vector3(0,      0, 0), radius,  0, slices, startTheta, endTheta);
	//renderSolidConeCore(transform, color, Vector3(0, height, 0), radius,  0, slices, startTheta, endTheta);
}

void IComponentDebugRenderer::renderWireCone(const Matrix4 &transform, 
										  const ColorRGBA &color, float radius, float height, int slices, 
										  float startTheta, float endTheta)
{
	renderWireCircleCore(transform, color, Vector3::ZERO, radius, slices, startTheta, endTheta);
	renderWireConeBody(transform, color, Vector3(0, 0, 0), radius, 0, height, slices, startTheta, endTheta);
}

void IComponentDebugRenderer::renderSolidCone(const Matrix4 &transform, 
										   const ColorRGBA &color, float radius, float height, int slices, 
										   float startTheta, float endTheta)
{
	//renderSolidConeCore(transform, color, Vector3::ZERO, radius, height, slices, startTheta, endTheta);
	//renderSolidConeCore(transform, color, Vector3::ZERO, radius,      0, slices, startTheta, endTheta);

	renderSolidCylinderBody(transform, color, 
						  Vector3::ZERO,
						  radius, 0,
						  height, slices, startTheta, endTheta);

	renderSolidCylinderBody(transform, color, 
						  Vector3::ZERO,
						  radius, 0,
						  0, slices, startTheta, endTheta);
}

void IComponentDebugRenderer::renderWireBox(const Matrix4 &transform, 
										 const ColorRGBA &color, const Vector3 &extent)
{
	Vector3 v0(-extent[0], -extent[1], -extent[2]);
	Vector3 v1( extent[0], -extent[1], -extent[2]);
	Vector3 v2( extent[0],  extent[1], -extent[2]);
	Vector3 v3(-extent[0],  extent[1], -extent[2]);

	Vector3 v4(-extent[0], -extent[1],  extent[2]);
	Vector3 v5( extent[0], -extent[1],  extent[2]);
	Vector3 v6( extent[0],  extent[1],  extent[2]);
	Vector3 v7(-extent[0],  extent[1],  extent[2]);

	Vector3 vertices[] = 
	{
		v0, v1, 
		v1, v2,
		v2,	v3,
		v3,	v0,

		v4, v5, 
		v5, v6,
		v6,	v7,
		v7,	v4,

		v0, v4, 
		v1, v5,
		v2,	v6,
		v3,	v7,
	};
	
	renderLines(transform, &vertices[0], color, 24);
}

void IComponentDebugRenderer::renderSolidBox(const Matrix4 &transform, 
										 const ColorRGBA &color, const Vector3 &extent)
{
	Vector3 v0(-extent[0], -extent[1], -extent[2]);
	Vector3 v1( extent[0], -extent[1], -extent[2]);
	Vector3 v2(-extent[0],  extent[1], -extent[2]);
	Vector3 v3( extent[0],  extent[1], -extent[2]);

	Vector3 v4( extent[0], -extent[1],  extent[2]);
	Vector3 v5(-extent[0], -extent[1],  extent[2]);
	Vector3 v6( extent[0],  extent[1],  extent[2]);
	Vector3 v7(-extent[0],  extent[1],  extent[2]);

	Vector3 vertices[] = 
	{
		v0, v1, v2, v3, 
		v4, v5, v6, v7, 

		v1, v4, v3, v6, 
		v5, v0, v7, v2, 

		v0, v5, v1, v4, 
		v7, v2, v6, v3, 
	};
	
	for(int i=0; i<sizeof(vertices)/sizeof(vertices[0]); i+=4)
		renderPrimitive(IComponentDebugRenderer::TriangleStrip, transform, &vertices[i], color, 4);
}

void IComponentDebugRenderer::renderWireFrustum(const Matrix4 &transform,
											 const ColorRGBA &color, 
											 float l, float r, float b, float t, float n, float f)
{
	Vector3 v0(l, b, -n);
	Vector3 v1(r, b, -n);
	Vector3 v2(r, t, -n);
	Vector3 v3(l, t, -n);

	float ratio = f / n;
	Vector3 v4(l*ratio, b*ratio, -f);
	Vector3 v5(r*ratio, b*ratio, -f);
	Vector3 v6(r*ratio, t*ratio, -f);
	Vector3 v7(l*ratio, t*ratio, -f);

	Vector3 vertices[] = 
	{
		v0, v1, 
		v1, v2,
		v2,	v3,
		v3,	v0,

		v4, v5, 
		v5, v6,
		v6,	v7,
		v7,	v4,

		v0, v4, 
		v1, v5,
		v2,	v6,
		v3,	v7,
	};
	
	renderLines(transform, &vertices[0], color, 24);
}

void IComponentDebugRenderer::renderSolidFrustum(const Matrix4 &transform, 
											  const ColorRGBA &color, 
											  float l, float r, float b, float t, float n, float f)
{
	Vector3 v0(l, b, -n);
	Vector3 v1(r, b, -n);
	Vector3 v2(r, t, -n);
	Vector3 v3(l, t, -n);

	float ratio = f / n;
	Vector3 v4(r*ratio, b*ratio, -f);
	Vector3 v5(l*ratio, b*ratio, -f);
	Vector3 v6(l*ratio, t*ratio, -f);
	Vector3 v7(r*ratio, t*ratio, -f);

	Vector3 vertices[] = 
	{
		v0, v1, v2, v3, 
		v4, v5, v6, v7, 

		v1, v4, v3, v6, 
		v5, v0, v7, v2, 

		v0, v5, v1, v4, 
		v7, v2, v6, v3, 
	};
	
	for(int i=0; i<sizeof(vertices)/sizeof(vertices[0]); i+=4)
		renderPrimitive(IComponentDebugRenderer::TriangleStrip, transform, &vertices[i], color, 4);
}


void IComponentDebugRenderer::renderWireCircleCore(const Matrix4 &transform, 
	                                            const ColorRGBA &color, 
												const Vector3 &offset, 
												float radius, int slices,
												float startTheta, float endTheta)
{
	Vector<Vector3> vertices;
	vertices.resize( (slices+1) );

	int vertexIdx	= 0;
	float dAng		= (endTheta - startTheta) / slices;
	float ang		= startTheta;

	for(int sli=0; sli<slices+1; sli++)
	{
		vertices[vertexIdx][0] = radius * Math::Cos(ang) + offset[0];
		vertices[vertexIdx][1] = 0 + offset[1];
		vertices[vertexIdx][2] = radius * Math::Sin(ang) + offset[2];
		vertexIdx++;

		ang += dAng;
	}

	renderPrimitive(IComponentDebugRenderer::LineStrip, transform, &vertices[0], color, vertexIdx);
}

void IComponentDebugRenderer::renderWireSphereCore(const Matrix4 &transform, 
										        const ColorRGBA &color, 
												const Vector3 &offset, 
												float radius, int slices, int segments,
											    float startTheta, float endTheta,
											    float startPhi, float endPhi)
{
	int vertexIdx	= 0;
	float dPhi		= (endPhi - startPhi)     / segments;
	float dAng		= (endTheta - startTheta) / slices;
	float phi0		= startPhi;
	float phi1		= startPhi + dPhi;
	for(int seg=0; seg<segments; seg++)
	{
		float r0	= radius * Math::Sin(phi0);
		float y0 	= radius * Math::Cos(phi0);
		float r1	= radius * Math::Sin(phi1);
		float y1 	= radius * Math::Cos(phi1);

		renderWireCircleCore(transform, color, 
						   offset + Vector3(0, y0, 0),
						   r0, slices,
						   startTheta, endTheta);

		renderWireConeBody(transform, color, 
						 offset + Vector3(0, y0, 0), 
						 r0, r1, y1-y0, slices,
						 startTheta, endTheta);

		phi0		+= dPhi;
		phi1		+= dPhi;
	}
}

void IComponentDebugRenderer::renderWireConeBody(const Matrix4 &transform, 
	                                             const ColorRGBA &color, 
												 const Vector3 &offset, 
												 float r0, float r1, float height, int slices,
												 float startTheta, float endTheta)
{
	Vector<Vector3> vertices;
	vertices.resize( (slices+1) * 2);

	int vertexIdx	= 0;
	float dAng		= (endTheta - startTheta) / slices;
	float ang		= startTheta;

	for(int sli=0; sli<slices+1; sli++)
	{
		vertices[vertexIdx][0] = r0 * Math::Cos(ang) + offset[0];
		vertices[vertexIdx][1] = 0 + offset[1];
		vertices[vertexIdx][2] = r0 * Math::Sin(ang) + offset[2];
		vertexIdx++;

		vertices[vertexIdx][0] = r1 * Math::Cos(ang) + offset[0];
		vertices[vertexIdx][1] = 0 + offset[1] + height;
		vertices[vertexIdx][2] = r1 * Math::Sin(ang) + offset[2];
		vertexIdx++;

		ang += dAng;
	}

	renderPrimitive(IComponentDebugRenderer::Lines, transform, &vertices[0], color, vertexIdx);
}

void IComponentDebugRenderer::renderSolidConeCore(const Matrix4 &transform, 
											   const ColorRGBA &color, const Vector3 &offset, 
										       float radius, float height, int slices, float startTheta, float endTheta)
{
	Vector<Vector3> vertices;
	vertices.resize( (slices+1) + 1 );

	int vertexIdx	= 0;
	float dAng		= (endTheta - startTheta) / slices;
	float ang		= startTheta;

	vertices[vertexIdx][0] = offset[0];
	vertices[vertexIdx][1] = height + offset[1];
	vertices[vertexIdx][2] = offset[2];
	vertexIdx++;
	
	for(int sli=0; sli<slices+1; sli++)
	{
		vertices[vertexIdx][0] = radius * Math::Cos(ang) + offset[0];
		vertices[vertexIdx][1] = offset[1];
		vertices[vertexIdx][2] = radius * Math::Sin(ang) + offset[2];
		vertexIdx++;

		ang += dAng;
	}

	renderPrimitive(IComponentDebugRenderer::TriangleFan, transform, &vertices[0], color, vertexIdx);
}

void IComponentDebugRenderer::renderSolidSphereCore(const Matrix4 &transform, 
											     const ColorRGBA &color, 
												 const Vector3 &offset, float radius, int slices, int segments, 
												 float startTheta, float endTheta,
												 float startPhi, float endPhi)
{
	Vector<Vector3> vertices;
	vertices.resize( ((slices+1) * 2) * (segments) );
	
	int vertexIdx	= 0;
	float dPhi		= (endPhi - startPhi)     / segments;
	float dAng		= (endTheta - startTheta) / slices;
	float phi0		= startPhi;
	float phi1		= startPhi + dPhi;
	for(int seg=0; seg<segments; seg++)
	{
		float r0	= radius * Math::Sin(phi0);
		float y0 	= radius * Math::Cos(phi0);
		float r1	= radius * Math::Sin(phi1);
		float y1 	= radius * Math::Cos(phi1);

		float ang = startTheta;
		for(int sli=0; sli<slices+1; sli++)
		{
			vertices[vertexIdx][0] = r0 * Math::Cos(ang) + offset[0];
			vertices[vertexIdx][1] = y0					 + offset[1];	
			vertices[vertexIdx][2] = r0 * Math::Sin(ang) + offset[2];
			vertexIdx++;

			vertices[vertexIdx][0] = r1 * Math::Cos(ang) + offset[0];
			vertices[vertexIdx][1] = y1					 + offset[1];	
			vertices[vertexIdx][2] = r1 * Math::Sin(ang) + offset[2];
			vertexIdx++;

			ang += dAng;
		}

		phi0		+= dPhi;
		phi1		+= dPhi;
	}

	renderPrimitive(IComponentDebugRenderer::TriangleStrip, transform, &vertices[0], color, vertexIdx);
}

void IComponentDebugRenderer::renderSolidCylinderBody(const Matrix4 &transform, 
											       const ColorRGBA &color, 
												   const Vector3 &offset, 
												   float r0, float r1, float height, int slices, float startTheta, float endTheta)
{
	Vector<Vector3> vertices;
	vertices.resize( ((slices+1) * 2) );
	
	int vertexIdx	= 0;
	float dAng		= (endTheta - startTheta) / slices;
	float ang = startTheta;

	for(int sli=0; sli<slices+1; sli++)
	{
		vertices[vertexIdx][0] = r0 * Math::Cos(ang) + offset[0];
		vertices[vertexIdx][1] = 0 + offset[1];
		vertices[vertexIdx][2] = r0 * Math::Sin(ang) + offset[2];
		vertexIdx++;

		vertices[vertexIdx][0] = r1 * Math::Cos(ang) + offset[0];
		vertices[vertexIdx][1] = height + offset[1];
		vertices[vertexIdx][2] = r1 * Math::Sin(ang) + offset[2];
		vertexIdx++;

		ang += dAng;
	}

	renderPrimitive(IComponentDebugRenderer::TriangleStrip, transform, &vertices[0], color, vertexIdx);
}