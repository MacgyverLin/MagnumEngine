///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _ReflectedClassFieldReader_h_
#define _ReflectedClassFieldReader_h_

#include "Stage.h"
#include "Entity.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "ClassIndexMap.h"
#include "String.h"
#include "ColorRGBA.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "IVector2.h"
#include "IVector3.h"
#include "IVector4.h"
#include "ResourcePath.h"
#include "SRTTransform.h"
using namespace Magnum;

namespace Magnum
{

template<class ReflectClass>
class ReflectedClassFieldReader
{
public:
	ReflectedClassFieldReader(ReflectClass *reflectClass_)
	: reflectClass(reflectClass_)
	{
	}

	~ReflectedClassFieldReader()
	{
	}
	
	ReflectClass *getReflectClass()
	{
		return reflectClass;
	}

	bool read(InputStream &is)
	{
		const ClassDesc &classDesc	= reflectClass->getClassDesc();

		return readClass(is, classDesc);
	}

	bool readClass(InputStream &is, const ClassDesc &classDesc) const
	{
		if(classDesc.hasSuper())
		{
			if(!readClass(is, classDesc.getSuper()))
				return false;
		}

		String className;
		is >> className;

		const ClassDesc::FieldDescList &fieldDescList = classDesc.getFields();

		int numFields;
		is >> numFields;
		assert(numFields==fieldDescList.size());
		for(ClassDesc::FieldDescListCItr itr=fieldDescList.begin(); itr!=fieldDescList.end(); itr++)
		{
			int classNameIndex			= itr->getClassIndex();
			String fieldName			= itr->getName();
	
			assert(classNameIndex>=0 && classNameIndex<ClassIndexMap::instance().getNumClasses());
			is >> classNameIndex;
			is >> fieldName;

			if(!readFieldDescFuncs[classNameIndex](is, *itr, reflectClass))
				return false;
		}

		return true;
	}
private:
	static bool (*readFieldDescFuncs[])(InputStream &is, const FieldDesc &fieldDesc, ReflectClass *ptr);

	template <class T>
	static bool readFieldDesc(InputStream &is, const FieldDesc &fieldDesc, ReflectClass *ptr)
	{
		T val;
		is >> val;

		try
		{
			fieldDesc.set(ptr, val);
			return true;
		}
		catch(...)
		{
			return false;
		}
	}

	ReflectClass *reflectClass;
};

template <class ReflectClass>
bool (*ReflectedClassFieldReader<ReflectClass>::readFieldDescFuncs[])(InputStream &is, const FieldDesc &fieldDesc, ReflectClass *ptr) =
{
	readFieldDesc< bool >,
	readFieldDesc< Vector<bool> >,
	readFieldDesc< int >,
	readFieldDesc< Vector<int> >,
	readFieldDesc< unsigned int >,
	readFieldDesc< Vector<unsigned int> >,
	readFieldDesc< float >,
	readFieldDesc< Vector<float> >,
	readFieldDesc< double >,
	readFieldDesc< Vector<double> >,
	readFieldDesc< String >,
	readFieldDesc< Vector<String> >,
	readFieldDesc< ColorRGBA >,
	readFieldDesc< Vector<ColorRGBA> >,
	readFieldDesc< Vector2 >,
	readFieldDesc< Vector<Vector2> >,
	readFieldDesc< Vector3 >,
	readFieldDesc< Vector<Vector3> >,
	readFieldDesc< Vector4 >,
	readFieldDesc< Vector<Vector4> >,
	readFieldDesc< IVector2 >,
	readFieldDesc< Vector<IVector2> >,
	readFieldDesc< IVector3 >,
	readFieldDesc< Vector<IVector3> >,
	readFieldDesc< IVector4 >,
	readFieldDesc< Vector<IVector4> >,
	readFieldDesc< ResourcePath >,
	readFieldDesc< Vector<ResourcePath> >,
	readFieldDesc< SRTTransform >,
	readFieldDesc< Vector<SRTTransform> >,
};

}

#endif
