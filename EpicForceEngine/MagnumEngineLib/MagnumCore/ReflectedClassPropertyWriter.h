///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _ReflectedClassPropertyWriter_h_
#define _ReflectedClassPropertyWriter_h_

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
class ReflectedClassPropertyWriter
{
public:
	ReflectedClassPropertyWriter(const ReflectClass *reflectClass_)
	: reflectClass(reflectClass_)
	{
	}

	~ReflectedClassPropertyWriter()
	{
	}
	
	ReflectClass *getReflectClass()
	{
		return reflectClass;
	}

	bool write(OutputStream &os) const
	{
		const ClassDesc &classDesc	= reflectClass->getClassDesc();

		return writeClass(os, classDesc);
	}

	bool writeClass(OutputStream &os, const ClassDesc &classDesc) const
	{
		if(classDesc.hasSuper())
		{
			if(!writeClass(os, classDesc.getSuper()))
				return false;
		}

		String className(classDesc.getName());
		os << className;

		const ClassDesc::PropertyDescList &propertyList = classDesc.getProperties();

		int numProperties = propertyList.size();
		os << numProperties;

		for(ClassDesc::PropertyDescListCItr itr=propertyList.begin(); itr!=propertyList.end(); itr++)
		{
			int classNameIndex			= itr->getClassIndex();
			String propertyName			= itr->getName();
	
			assert(classNameIndex>=0 && classNameIndex<ClassIndexMap::instance().getNumClasses());
			os << classNameIndex;
			os << propertyName;

			if(!writePropertyDescFuncs[classNameIndex](os, *itr, reflectClass))
				return false;
		}

		return true;
	}
private:
	static bool (*writePropertyDescFuncs[])(OutputStream &os, const PropertyDesc &propertyDesc, const ReflectClass *ptr);

	template <class T>
	static bool writePropertyDesc(OutputStream &os, const PropertyDesc &propertyDesc, const ReflectClass *ptr)
	{
		T val;

		propertyDesc.get(val, ptr);

		os << val;

		return true;
	}

	const ReflectClass *reflectClass;
};

template <class ReflectClass>
bool (*ReflectedClassPropertyWriter<ReflectClass>::writePropertyDescFuncs[])(OutputStream &os, const PropertyDesc &propertyDesc, const ReflectClass *ptr) =
{
	writePropertyDesc< bool >,
	writePropertyDesc< Vector<bool> >,
	writePropertyDesc< int >,
	writePropertyDesc< Vector<int> >,
	writePropertyDesc< unsigned int >,
	writePropertyDesc< Vector<unsigned int> >,
	writePropertyDesc< float >,
	writePropertyDesc< Vector<float> >,
	writePropertyDesc< double >,
	writePropertyDesc< Vector<double> >,
	writePropertyDesc< String >,
	writePropertyDesc< Vector<String> >,
	writePropertyDesc< ColorRGBA >,
	writePropertyDesc< Vector<ColorRGBA> >,
	writePropertyDesc< Vector2 >,
	writePropertyDesc< Vector<Vector2> >,
	writePropertyDesc< Vector3 >,
	writePropertyDesc< Vector<Vector3> >,
	writePropertyDesc< Vector4 >,
	writePropertyDesc< Vector<Vector4> >,
	writePropertyDesc< IVector2 >,
	writePropertyDesc< Vector<IVector2> >,
	writePropertyDesc< IVector3 >,
	writePropertyDesc< Vector<IVector3> >,
	writePropertyDesc< IVector4 >,
	writePropertyDesc< Vector<IVector4> >,
	writePropertyDesc< ResourcePath >,
	writePropertyDesc< Vector<ResourcePath> >,
	writePropertyDesc< SRTTransform >,
	writePropertyDesc< Vector<SRTTransform> >,
};


}

#endif
