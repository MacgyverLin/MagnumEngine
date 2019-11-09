///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Frame3_h_
#define _Frame3_h_

#include "Stage.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "Array.h"
using namespace Magnum;

namespace Magnum
{

/**
* Frame3 is a base class for describing tree structure of the scene graph.
* It provides tree function such as add, remove, query, child
* global and local transform.
* convient function for initialing the transforms
*/
class Frame3
{
friend class EntityReader;
friend class EntityWriter;
public:
	/**
	* Frame3 Constructor.
	* To Construct the Frame3 for the owner.
	*/
	Frame3();

	/**
	* Frame3 Destructor.
	* To Destruct Frame3 and remove from its owner.
	*/
	virtual ~Frame3();

// init
	/**
	* Set all element of of the local transform as 0
	*/
    void initZero();

	/**
	* Set the Frame3's local transform as identity
	*/
	void initIdentity();

	/**
	* Set the Frame3's local transform translation
	* @param x, float, x translation
	* @param y, float, y translation
	* @param z, float, z translation
	*/
	void initTranslate(float x, float y, float z);

	/**
	* Set the Frame3's local transform rotation around X Axis
	* @param x, float, rotation in radian
	*/
	void initRotateX(float x);

	/**
	* Set the Frame3's local transform rotation around Y Axis
	* @param y, float, rotation in radian
	*/
	void initRotateY(float y);

	/**
	* Set the Frame3's local transform rotation around Z Axis
	* @param z, float, rotation in radian
	*/
	void initRotateZ(float z);

	/**
	* Set the Frame3's local transform rotation around Y Axis, X Axis, Z Axis consecutively
	* @param z, float, rotation around Z Axis in radian
	* @param x, float, rotation around X Axis in radian
	* @param y, float, rotation around Y Axis in radian
	*/
	void initRotateZXY(float z, float x, float y);

	/**
	* Set the Frame3's local transform rotation around Z Axis, Y Axis, X Axis consecutively
	* @param z, float, rotation around Z Axis in radian
	* @param y, float, rotation around Y Axis in radian
	* @param x, float, rotation around X Axis in radian
	*/
	void initRotateZYX(float z, float y, float x);

	/**
	* Set the Frame3's local transform rotation about an axis and an angle in radian
	* @param axis, Vector3, a unit vector for axis of rotation
	* @param angle, float, rotation around the axis in radian
	*/
	void initRotateAxisAngle(const Vector3 &axis, float radian);

	/**
	* Set the Frame3's local transform for uniform scale
	* @param scale, float, the scale 
	*/
	void initScale(float scale);

	/**
	* Set the Frame3's local transform for non-uniform scale
	* @param x, float, the scale of x direction
	* @param y, float, the scale of y direction 
	* @param z, float, the scale of z direction
	*/
	void initScale(float x, float y, float z);

	/**
	* Set the Frame3's local transform. First by scale, then rotation around Z Axis, X Axis, Y Axis consecutively, then translate 
	* @param tx, float, translation in X direction
	* @param ty, float, translation in Y direction
	* @param tz, float, translation in Z direction
	* @param rz, float, rotation around Z Axis in radian
	* @param rx, float, rotation around X Axis in radian
	* @param ry, float, rotation around Y Axis in radian
	* @param scale, float, the uniform scale in all direction
	*/
	void initTranslateRotZXYScale(float tx, float ty, float tz, float rz, float rx, float ry, float scale);

	/**
	* Set the Frame3's local transform. First by scale, then rotation around Z Axis, Y Axis, X Axis consecutively, then translate 
	* @param tx, float, translation in X direction
	* @param ty, float, translation in Y direction
	* @param tz, float, translation in Z direction
	* @param rz, float, rotation around Z Axis in radian
	* @param ry, float, rotation around Y Axis in radian
	* @param rx, float, rotation around X Axis in radian
	* @param scale, float, the uniform scale in all direction
	*/
	void initTranslateRotZYXScale(float tx, float ty, float tz, float rz, float ry, float rx, float scale);

	/**
	* Set the Frame3's local transform. First by scale, then rotate about an axis and an angle in radian, then translate 
	* @param tx, float, translation in X direction
	* @param ty, float, translation in Y direction
	* @param tz, float, translation in Z direction
	* @param axis, Vector3, a unit vector for axis of rotation
	* @param angle, float, rotation around the axis in radian
	* @param scale, float, the uniform scale in all direction
	*/
	void initTranslateRotAxisAngleScale(float tx, float ty, float tz, const Vector3 &axis, const float angle, float scale);
	
	/**
	* Set the Frame3's local transform. First by scale, then translate
	* @param tx, float, translation in X direction
	* @param ty, float, translation in Y direction
	* @param tz, float, translation in Z direction
	* @param scale, float, the uniform scale in all direction
	*/
	void initTranslateScale(float tx, float ty, float tz, float scale);

	/**
	* Set the Frame3's local transform. Look At objective from position, head point up
	* @param position, Vector3, Observer's position
	* @param target, Vector3, Observer's target
	* @param up, Vector3, upward direction
	*/
	void initLookAt(const Vector3 &position, const Vector3 &target, const Vector3 &up);

	/**
	* Set the Frame3's local transform. Look At objective from position, head point up, then uniformly scale
	* @param position, Vector3, Observer's position
	* @param target, Vector3, Observer's target
	* @param up, Vector3, upward direction
	* @param scale, float, the uniform scale
	*/
	void initLookAtScale(const Vector3 &position, const Vector3 &target, const Vector3 &up, float scale);

	/**
	* Set the Frame3's local transform. Stand on a surface with normal vector up. Look At objective from position
	* @param position, Vector3, Observer's position
	* @param target, Vector3, Observer's target
	* @param up, Vector3, upward direction the Observer stand on
	*/
	void initStandOn(const Vector3 &position, const Vector3 &target, const Vector3 &up);

	/**
	* Set the Frame3's local transform. Stand on a surface with normal vector up. Look At objective from position, then uniformly scale
	* @param position, Vector3, Observer's position
	* @param target, Vector3, Observer's target
	* @param up, Vector3, upward direction the Observer stand on
	* @param scale, float, the uniform scale
	*/
	void initStandOnScale(const Vector3 &position, const Vector3 &objective, const Vector3 &up, float scale);
// setter

	/**
	* Set the Frame3's local transform by directly setting the Local Transform Matrix
	* @param localtransform_, Matrix4, the local transform
	*/
	void setLocalTransform(const Matrix4 &localtransform_);

	/**
	* Set the Frame3's local transform by directly setting the Local Position
	* @param localposition_, Vector3, the local position
	*/
	void setLocalPosition(const Vector3 &localposition_);

	/**
	* Set the Frame3's local transform by directly setting the a Global Transform Matrix 
	* @param globaltransform_, Matrix4, the global transform
	*/
	void setGlobalTransform(const Matrix4 &globaltransform_);

	/**
	* Set the Frame3's local transform by directly setting the a Global Position
	* @param globalposition_, Vector3, the global position
	*/
	void setGlobalPosition(const Vector3 &globalposition_);
// getter

	/**
	* Get the Frame3's local transform
	* @return const Matrix4 &, the global transform
	*/
	const Matrix4 &getLocalTransform() const;	

	/**
	* Get the Frame3's local position
	* @return Vector3, the local position
	*/
	Vector3 getLocalPosition() const;

	/**
	* Get the Frame3's local x axis
	* @return Vector3, the local x axis
	*/
	Vector3 getLocalXAxis() const;

	/**
	* Get the Frame3's local y axis
	* @return Vector3, the local y axis
	*/
	Vector3 getLocalYAxis() const;

	/**
	* Get the Frame3's local z axis
	* @return Vector3, the local z axis
	*/
	Vector3 getLocalZAxis() const;

	/**
	* Get the Frame3's global transform
	* @return const Matrix4 &, the global transform
	*/
	const Matrix4 &getGlobalTransform();

	/**
	* Get the Frame3's global position
	* @return Vector3, the global position
	*/
	Vector3 getGlobalPosition();

	/**
	* Get the Frame3's local x axis
	* @return Vector3, the local x axis
	*/
	Vector3 getGlobalXAxis();

	/**
	* Get the Frame3's local y axis
	* @return Vector3, the local y axis
	*/
	Vector3 getGlobalYAxis();

	/**
	* Get the Frame3's local z axis
	* @return Vector3, the local z axis
	*/
	Vector3 getGlobalZAxis();

	/**
	* Get the Frame3's inverse transform
	* @return Matrix4, the inverse transform
	*/
	Matrix4 getInverseGlobalTransform();

	/*
	const Matrix4 &getParentGlobalTransform();
	Vector3 getParentGlobalPosition();
	Vector3 getParentGlobalXAxis();
	Vector3 getParentGlobalYAxis();
	Vector3 getParentGlobalZAxis();
	*/

	// setter
	/**
	* add a child to this Frame3's children list
	* @param child_, the child to be added
	*/
	void addChild(Frame3 *child_);

	/**
	* set i-th child for this Frame3's  
	* @param child_, the child to be set to
	* @param index_, the index_ position
	*/
	void setChild(Frame3 *child_, int index_);

	/**
	* insert a child to this Frame3's at index_
	* @param child_, the child to be set to
	* @param index_, the index_ position
	*/
	void insertChild(Frame3 *child_, int index_);

	/**
	* remove all children from this Frame3
	*/
	void removeAllChildren();

	/**
	* remove child at index_
	*/
	void removeChild(int index_);

	/**
	* remove child_
	*/
	void removeChild(Frame3 *child_);

	// getter
	/**
	* get all children from this Frame3
	*/
	int getAllChildren(Vector<Frame3 *> &children_);

	/**
	* Get a child of this frame at index_
	* @param index_, the index_ position
	* @return Frame3 *, the i-th child
	*/
	Frame3 *getChild(int index_) const;

	/**
	* Get an index of child
	* @param child_, Frame3 *
	* @return int, the index of child. if child is not in children list, return -1
	*/
	int indexOfChild(Frame3 *child_) const;

	/**
	* Get the number of children
	* @return int, the number of children
	*/
	int getNumChildren() const;

	/**
	* Get a the parent of this frame
	* @return Frame3 *, this frame's parent. if this frame has no parent, return 0
	*/
	Frame3 *getParent();

	/**
	* Get a the parent of this frame
	* @return const Frame3 *, this frame's parent. if this frame has no parent, return 0
	*/
	const Frame3 *getParent() const;

	/**
	* read method for Serialization
	* @param is, the InputStream for Serialization
	*/
	void read(InputStream &is);

	/**
	* write method for Serialization
	* @param os, the OutputStream for Serialization
	*/
	void write(OutputStream &os) const;
protected:
	void validateGlobal();
	void inValidateGlobal();
	bool isValidGlobal();

	//void validateGlobalInverse();
	//void inValidateGlobalInverse();
	//bool isValidGlobalInverse();
private:
	Frame3 *parent;
	Vector<Frame3 *> children;

	Matrix4 localTransform;
	Matrix4 globalTransform;
	bool validGlobal;

	//Matrix4 globalTransformInverse;
	//bool validGlobalInverse;
};

}

#endif