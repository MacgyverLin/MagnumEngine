///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _ReflectedClassPropertyReader_h_
#define _ReflectedClassPropertyReader_h_

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
class ReflectedClassPropertyReader
{
public:
	ReflectedClassPropertyReader(ReflectClass *reflectClass_)
	: reflectClass(reflectClass_)
	{
	}

	~ReflectedClassPropertyReader()
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
			if(!readClass(is, classDesc.getSuper()) )
				return false;
		}

		String className;
		is >> className;

		const ClassDesc::PropertyDescList &propertyList = classDesc.getProperties();

		int numProperties;
		is >> numProperties;
		assert(numProperties==propertyList.size());
		for(ClassDesc::PropertyDescListCItr itr=propertyList.begin(); itr!=propertyList.end(); itr++)
		{
			int classNameIndex			= itr->getClassIndex();
			String propertyName			= itr->getName();
	
			assert(classNameIndex>=0 && classNameIndex<ClassIndexMap::instance().getNumClasses());
			is >> classNameIndex;
			is >> propertyName;

			if(!readPropertyDescFuncs[classNameIndex](is, *itr, reflectClass))
				return false;
		}

		return true;
	}
private:
	static bool (*readPropertyDescFuncs[])(InputStream &is, const PropertyDesc &propertyDesc, ReflectClass *ptr);

	template <class T>
	static bool readPropertyDesc(InputStream &is, const PropertyDesc &propertyDesc, ReflectClass *ptr)
	{
		T val;
		is >> val;

		try
		{
			propertyDesc.set(ptr, val);
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
bool (*ReflectedClassPropertyReader<ReflectClass>::readPropertyDescFuncs[])(InputStream &is, const PropertyDesc &propertyDesc, ReflectClass *ptr) =
{
	readPropertyDesc< bool >,
	readPropertyDesc< Vector<bool> >,
	readPropertyDesc< int >,
	readPropertyDesc< Vector<int> >,
	readPropertyDesc< unsigned int >,
	readPropertyDesc< Vector<unsigned int> >,
	readPropertyDesc< float >,
	readPropertyDesc< Vector<float> >,
	readPropertyDesc< double >,
	readPropertyDesc< Vector<double> >,
	readPropertyDesc< String >,
	readPropertyDesc< Vector<String> >,
	readPropertyDesc< ColorRGBA >,
	readPropertyDesc< Vector<ColorRGBA> >,
	readPropertyDesc< Vector2 >,
	readPropertyDesc< Vector<Vector2> >,
	readPropertyDesc< Vector3 >,
	readPropertyDesc< Vector<Vector3> >,
	readPropertyDesc< Vector4 >,
	readPropertyDesc< Vector<Vector4> >,
	readPropertyDesc< IVector2 >,
	readPropertyDesc< Vector<IVector2> >,
	readPropertyDesc< IVector3 >,
	readPropertyDesc< Vector<IVector3> >,
	readPropertyDesc< IVector4 >,
	readPropertyDesc< Vector<IVector4> >,
	readPropertyDesc< ResourcePath >,
	readPropertyDesc< Vector<ResourcePath> >,
	readPropertyDesc< SRTTransform >,
	readPropertyDesc< Vector<SRTTransform> >,
};

}

#endif
