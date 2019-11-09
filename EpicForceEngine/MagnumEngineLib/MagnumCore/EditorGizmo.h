///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _EditorGizmo_h_
#define _EditorGizmo_h_

#include "Stage.h"
#include "Graphics3Component.h"
#include "Vector2.h"
#include "Texture2DFile.h"
#include "VisualEffect.h"
#include "ResourcePath.h"
#include "GXContext.h"
#include "GXDebugRenderer.h"
using namespace Magnum;

namespace Magnum
{

/**
* EditorGizmo.
* EditorGizmo are those mover icon, rotator icon, scaler icon, grid on editor screen
* @see Graphics3Component
*/
class EditorGizmo : public Graphics3Component
{
////////////////////////////////////////////////////////////////
public:
	enum Mode
	{
		DEFAULT		= 0,					/**< Default gizmo only show 3 axis						*/ 
		TRANSLATE	= 1,					/**< Translation gizmo show 3 axis and translate handle	*/ 
		ROTATE		= 2,					/**< Rotation gizmo only show 3 rotation circle handle	*/ 
		SCALE		= 3,					/**< Scale only show 3 axis and scale handle			*/ 
	};

	enum CoordSys
	{
		LOCAL	= 0,						/**< Render Gizmo in Local Space	*/ 
		PARENT	= 1,						/**< Render Gizmo in Parent Space	*/ 
		WORLD	= 2,						/**< Render Gizmo in World Space	*/ 
		VIEW	= 3,						/**< Render Gizmo in View Space		*/ 
	};
////////////////////////////////////////////////////////////////
public:
	/**
	* EditorGizmo Constructor.
	* To Construct the EditorGizmo for the owner.
	* @param owner_, the Component::Owner which owns this component.
	*/
	EditorGizmo(Component::Owner &owner_);

	/**
	* EditorGizmo Destructor.
	* To Destruct the EditorGizmo for the owner.
	*/
	virtual ~EditorGizmo();

	DECLARE_COMPONENT(EditorGizmo, Graphics3Component, false)
////////////////////////////////////////////////////////////////
public:
	/**
	* Set the Gizmo Mode.
	* To Set the Mode and Coordinate System of Gizmo
	* @param mode_, the EditorGizmo::Mode
	* @param coordsys_, the EditorGizmo::CoordSys
	* @see EditorGizmo::Mode, EditorGizmo::CoordSys
	*/
	void setMode(EditorGizmo::Mode mode_, EditorGizmo::CoordSys coordsys_);

	/**
	* Get the Gizmo Mode.
	* To Get the Mode of Gizmo
	* @return the EditorGizmo::Mode
	* @see EditorGizmo::Mode, EditorGizmo::CoordSys
	*/
	EditorGizmo::Mode getMode() const;

	/**
	* Get the Gizmo Coordinate System.
	* To Get the Coordinate System of Gizmo
	* @return the EditorGizmo::CoordSys
	* @see EditorGizmo::Mode, EditorGizmo::CoordSys
	*/
	EditorGizmo::CoordSys getCoordSys() const;

	/**
	* Render the Graphics Object Gizmo.
	* @param param const Video::Manager::RenderParam
	* @see Video::Manager::RenderParam
	*/
	virtual void render(const Video::Manager::RenderParam &param);

	/**
	* Render reference Transform.
	* @param refTransform Matrix4
	* @param coordsys EditorGizmo::CoordSys
	* @see Video::Manager::RenderParam
	*/
	void getRefTransform(Matrix4 &refTransform, EditorGizmo::CoordSys coordsys);
protected:
private:
	void renderGizmos(GXDebugRenderer drawer);
	void renderAxis(const Matrix4 &refTransform, GXDebugRenderer drawer, float alpha);
	void renderDefaultGizmos(GXDebugRenderer drawer);
	void renderTranslateGizmos(GXDebugRenderer drawer);
	void renderRotateGizmos(GXDebugRenderer drawer);
	void renderScaleGizmos(GXDebugRenderer drawer);
	void renderSelectedEntity(GXDebugRenderer drawer);
	void renderGrid(GXDebugRenderer drawer);
public:
protected:
private:
	EditorGizmo::Mode		mode;
	EditorGizmo::CoordSys	coordsys;
};

};

#endif
