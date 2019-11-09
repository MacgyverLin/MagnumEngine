///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Frame3.h"
using namespace Magnum;

Frame3::Frame3()
: parent(0)
, localTransform(Matrix4::IDENTITY)
, globalTransform(Matrix4::IDENTITY)
, validGlobal(false)
//, globalTransformInverse(Matrix4::IDENTITY)
//, validGlobalInverse(false)
{
}

Frame3::~Frame3()
{
}

// init
void Frame3::initZero ()
{
	localTransform.initZero ();

	inValidateGlobal();
	//inValidateGlobalInverse();
}

void Frame3::initIdentity()
{
	localTransform.initIdentity ();

	inValidateGlobal();
	//inValidateGlobalInverse();
}

void Frame3::initTranslate(float x, float y, float z)
{
	localTransform.initTranslate(x, y, z);

	inValidateGlobal();
	//inValidateGlobalInverse();
}

void Frame3::initRotateX(float radian)
{
	localTransform.initRotateX(radian);

	inValidateGlobal();
	//inValidateGlobalInverse();
}

void Frame3::initRotateY(float radian)
{
	localTransform.initRotateY(radian);

	inValidateGlobal();
	//inValidateGlobalInverse();
}

void Frame3::initRotateZ(float radian)
{
	localTransform.initRotateZ(radian);

	inValidateGlobal();
	//inValidateGlobalInverse();
}

void Frame3::initRotateZXY(float z, float x, float y)
{
	localTransform.initRotateZXY(z, x, y);

	inValidateGlobal();
	//inValidateGlobalInverse();
}

void Frame3::initRotateZYX(float z, float y, float x)
{
	localTransform.initRotateZYX(z, y, x);

	inValidateGlobal();
	//inValidateGlobalInverse();
}

void Frame3::initRotateAxisAngle(const Vector3 &axis, float radian)
{
	localTransform.initRotateAxisAngle(axis, radian);

	inValidateGlobal();
	//inValidateGlobalInverse();
}

void Frame3::initScale(float scale)
{
	localTransform.initScale(scale);

	inValidateGlobal();
	//inValidateGlobalInverse();
}

void Frame3::initScale(float x, float y, float z)
{
	localTransform.initScale(x, y, z);

	inValidateGlobal();
	//inValidateGlobalInverse();
}

void Frame3::initTranslateRotZXYScale(float tx, float ty, float tz, float rz, float rx, float ry, float scale)
{
	localTransform.initTranslateRotZXYScale(tx, ty, tz, rz, rx, ry, scale);

	inValidateGlobal();
	//inValidateGlobalInverse();
}

void Frame3::initTranslateRotZYXScale(float tx, float ty, float tz, float rz, float ry, float rx, float scale)
{
	localTransform.initTranslateRotZYXScale(tx, ty, tz, rz, ry, rx, scale);

	inValidateGlobal();
	//inValidateGlobalInverse();
}

void Frame3::initTranslateRotAxisAngleScale(float tx, float ty, float tz, const Vector3 &axis, const float radian, float scale)
{
	localTransform.initTranslateRotAxisAngleScale(tx, ty, tz, axis, radian, scale);

	inValidateGlobal();
	//inValidateGlobalInverse();
}

void Frame3::initTranslateScale(float tx, float ty, float tz, float scale)
{
	localTransform.initTranslateScale(tx, ty, tz, scale);

	inValidateGlobal();
	//inValidateGlobalInverse();
}

void Frame3::initLookAt(const Vector3 &position, const Vector3 &objective, const Vector3 &up)
{
	localTransform.initLookAt(position, objective, up);

	inValidateGlobal();
	//inValidateGlobalInverse();
}

void Frame3::initLookAtScale(const Vector3 &position, const Vector3 &objective, const Vector3 &up, float scale)
{
	localTransform.initLookAtScale(position, objective, up, scale);

	inValidateGlobal();
	//inValidateGlobalInverse();
}

void Frame3::initStandOn(const Vector3 &position, const Vector3 &objective, const Vector3 &up)
{
	localTransform.initStandOn(position, objective, up);

	inValidateGlobal();
	//inValidateGlobalInverse();
}

void Frame3::initStandOnScale(const Vector3 &position, const Vector3 &objective, const Vector3 &up, float scale)
{
	localTransform.initStandOnScale(position, objective, up, scale);

	inValidateGlobal();
	//inValidateGlobalInverse();
}
		 
// setter
void Frame3::setLocalTransform(const Matrix4 &localtransform_)
{
	localTransform = localtransform_;

	inValidateGlobal();
	//inValidateGlobalInverse();
}

void Frame3::setLocalPosition(const Vector3 &localposition_)
{
	localTransform[0][3] = localposition_.X();
	localTransform[1][3] = localposition_.Y();
	localTransform[2][3] = localposition_.Z();

	inValidateGlobal();
	//inValidateGlobalInverse();
}

void Frame3::setGlobalTransform(const Matrix4 &globalTransform_)
{
	//validateGlobal(); // can remove ?, yes can

	if(getParent())
		localTransform = getParent()->getGlobalTransform().Inverse() * globalTransform_;
	else
		localTransform = globalTransform_;

	inValidateGlobal();
	//inValidateGlobalInverse();
}

void Frame3::setGlobalPosition(const Vector3 &globalposition_)
{
	//validateGlobal(); // can remove ?, yes can

	Vector3 localposition;
	if(getParent())
		localposition = getParent()->getGlobalTransform().Inverse() * globalposition_;
	else
		localposition = globalposition_;

	localTransform[0][3] = localposition.X();
	localTransform[1][3] = localposition.Y();
	localTransform[2][3] = localposition.Z();

	inValidateGlobal();
	//inValidateGlobalInverse();
}

// getter
const Matrix4 &Frame3::getLocalTransform() const
{
	return localTransform;
}

Vector3 Frame3::getLocalPosition() const
{
	return Vector3(localTransform[0][3], 
				   localTransform[1][3],
				   localTransform[2][3]);
}

Vector3 Frame3::getLocalXAxis() const
{
	return Vector3(localTransform[0][0], 
				   localTransform[1][0],
				   localTransform[2][0]);
}

Vector3 Frame3::getLocalYAxis() const
{
	return Vector3(localTransform[0][1], 
				   localTransform[1][1],
				   localTransform[2][1]);
}

Vector3 Frame3::getLocalZAxis() const
{
	return Vector3(localTransform[0][2], 
				   localTransform[1][2],
				   localTransform[2][2]);
}

const Matrix4 &Frame3::getGlobalTransform()
{
	validateGlobal();

	return globalTransform;
}

Vector3 Frame3::getGlobalPosition()
{
	validateGlobal();

	return Vector3(globalTransform[0][3], 
				   globalTransform[1][3],
				   globalTransform[2][3]);
}

Vector3 Frame3::getGlobalXAxis()
{
	validateGlobal();

	return Vector3(globalTransform[0][0], 
				   globalTransform[1][0],
				   globalTransform[2][0]);
}

Vector3 Frame3::getGlobalYAxis()
{
	validateGlobal();

	return Vector3(globalTransform[0][1], 
				   globalTransform[1][1],
				   globalTransform[2][1]);
}

Vector3 Frame3::getGlobalZAxis()
{
	validateGlobal();

	return Vector3(globalTransform[0][2], 
				   globalTransform[1][2],
				   globalTransform[2][2]);
}

Matrix4 Frame3::getInverseGlobalTransform()
{
	/*
	validateGlobal();
	validateGlobalInverse();

	return globalTransformInverse;
	*/
	validateGlobal();
	//validateGlobalInverse();

	return globalTransform.Inverse();
}

/*
const Matrix4 &Frame3::getParentGlobalTransform()
{
	if(getParent())
	{
		return getParent()->getGlobalTransform();
	}
	else
		return Matrix4::IDENTITY;
}

Vector3 Frame3::getParentGlobalPosition()
{
	if(getParent())
	{
		Matrix4 mat = getParent()->getGlobalTransform();
		return Vector3(mat[0][3], 
			           mat[1][3], 
					   mat[2][3]);
	}
	else
		return Vector3::ZERO;
}

Vector3 Frame3::getParentGlobalXAxis()
{
	if(getParent())
	{
		Matrix4 mat = getParent()->getGlobalTransform();
		return Vector3(mat[0][0], 
			           mat[1][0], 
					   mat[2][0]);
	}
	else
		return Vector3::UNIT_X;
}

Vector3 Frame3::getParentGlobalYAxis()
{
	if(getParent())
	{
		Matrix4 mat = getParent()->getGlobalTransform();
		return Vector3(mat[0][1], 
			           mat[1][1], 
					   mat[2][1]);
	}
	else
		return Vector3::UNIT_Y;
}

Vector3 Frame3::getParentGlobalZAxis()
{
	if(getParent())
	{
		Matrix4 mat = getParent()->getGlobalTransform();
		return Vector3(mat[0][2], 
			           mat[1][2], 
					   mat[2][2]);
	}
	else
		return Vector3::UNIT_Z;
}
*/

void Frame3::validateGlobal()
{
	if( validGlobal )
		return;

	if(parent)
		globalTransform = parent->getGlobalTransform() * localTransform;
	else
		globalTransform = localTransform;

	validGlobal = true;
}

void Frame3::inValidateGlobal()
{
	validGlobal			= false;
	for (int i=0; i<getNumChildren(); i++)
	{
		getChild(i)->inValidateGlobal();
	}
}

bool Frame3::isValidGlobal()
{
	return validGlobal;
}

/*
void Frame3::validateGlobalInverse()
{
	if( validGlobalInverse )
		return;

	globalTransformInverse = getGlobalTransform().Inverse();

	validGlobalInverse = true;
}

void Frame3::inValidateGlobalInverse()
{
	validGlobalInverse = false;
	for (int i=0; i<children.length(); i++)
	{
		children[i]->inValidateGlobalInverse();
	}
}

bool Frame3::isValidGlobalInverse()
{
	return validGlobalInverse;
}
*/

// setter
void Frame3::addChild(Frame3 *child_)
{
	assert( child_->getParent() == 0 ); // not child already
	
	children.push() = child_;
	child_->parent  = this;
	child_->inValidateGlobal();
	//child_->inValidateGlobalInverse();
}

void Frame3::setChild(Frame3 *child_, int index_)
{
	assert( child_->getParent() == 0 ); // not child already
	assert( index_>=0 && index_<children.length() ); // index in range

	removeChild(index_);

	insertChild(child_, index_);
}

void Frame3::insertChild(Frame3 *child_, int index_)
{
	assert( child_->getParent() == 0 ); // not child already

	children.insert(index_) = child_;
	child_->parent  = this;
	child_->inValidateGlobal();
	//child_->inValidateGlobalInverse();
}

void Frame3::removeAllChildren()
{
	while(children.length()>0)
	{
		removeChild(0);
	};
}

void Frame3::removeChild(int index_)
{
	assert( index_>=0 && index_<children.length() );
	
	removeChild(children[index_]);
}

void Frame3::removeChild(Frame3 *child_)
{
	int idx = children.search(child_);
	if(idx!=-1)
	{
		child_->parent  = 0;
		child_->inValidateGlobal();
		//child_->inValidateGlobalInverse();

		children.remove(idx);
	}
}

// getter
int Frame3::getAllChildren(Vector<Frame3 *> &children_)
{
	for(int i=0; i<children.length(); i++)
	{
		children_.push() = children[i];
	}

	return children.length();
}

Frame3 *Frame3::getChild(int index_) const
{
	assert( index_>=0 && index_<children.length() );

	return children[index_];
}

int Frame3::indexOfChild(Frame3 *child_) const
{
	for(int i=0; i<children.length(); i++)
	{
		if(child_==children[i])
			return i;
	}

	return -1;
}

int Frame3::getNumChildren() const
{
	return children.length();
}

Frame3 *Frame3::getParent()
{
	return parent;
}

const Frame3 *Frame3::getParent() const
{
	return parent;
}

void Frame3::read(InputStream &is)
{
	is >> localTransform;

	inValidateGlobal();
	//inValidateGlobalInverse();
}

void Frame3::write(OutputStream &os) const
{
	os << localTransform;
}