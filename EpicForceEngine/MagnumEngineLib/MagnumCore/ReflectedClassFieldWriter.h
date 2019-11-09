///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _ReflectedClassFieldWriter_h_
#define _ReflectedClassFieldWriter_h_

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
class ReflectedClassFieldWriter
{
public:
	ReflectedClassFieldWriter(const ReflectClass *reflectClass_)
	: reflectClass(reflectClass_)
	{
	}

	~ReflectedClassFieldWriter()
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

		const ClassDesc::FieldDescList &fieldDescList = classDesc.getFields();

		int numFields = fieldDescList.size();
		os << numFields;

		for(ClassDesc::FieldDescListCItr itr=fieldDescList.begin(); itr!=fieldDescList.end(); itr++)
		{
			int classNameIndex			= itr->getClassIndex();
			String fieldName			= itr->getName();
	
			assert(classNameIndex>=0 && classNameIndex<ClassIndexMap::instance().getNumClasses());
			os << classNameIndex;
			os << fieldName;

			if(!writeFieldDescFuncs[classNameIndex](os, *itr, reflectClass))
				return false;
		}

		return true;
	}
private:
	static bool (*writeFieldDescFuncs[])(OutputStream &os, const FieldDesc &fieldDesc, const ReflectClass *ptr);

	template <class T>
	static bool writeFieldDesc(OutputStream &os, const FieldDesc &fieldDesc, const ReflectClass *ptr)
	{
		T val;

		fieldDesc.get(val, ptr);

		os << val;
		
		return true;
	}

	const ReflectClass *reflectClass;
};

template <class ReflectClass>
bool (*ReflectedClassFieldWriter<ReflectClass>::writeFieldDescFuncs[])(OutputStream &os, const FieldDesc &fieldDesc, const ReflectClass *ptr) =
{
	writeFieldDesc< bool >,
	writeFieldDesc< Vector<bool> >,
	writeFieldDesc< int >,
	writeFieldDesc< Vector<int> >,
	writeFieldDesc< unsigned int >,
	writeFieldDesc< Vector<unsigned int> >,
	writeFieldDesc< float >,
	writeFieldDesc< Vector<float> >,
	writeFieldDesc< double >,
	writeFieldDesc< Vector<double> >,
	writeFieldDesc< String >,
	writeFieldDesc< Vector<String> >,
	writeFieldDesc< ColorRGBA >,
	writeFieldDesc< Vector<ColorRGBA> >,
	writeFieldDesc< Vector2 >,
	writeFieldDesc< Vector<Vector2> >,
	writeFieldDesc< Vector3 >,
	writeFieldDesc< Vector<Vector3> >,
	writeFieldDesc< Vector4 >,
	writeFieldDesc< Vector<Vector4> >,
	writeFieldDesc< IVector2 >,
	writeFieldDesc< Vector<IVector2> >,
	writeFieldDesc< IVector3 >,
	writeFieldDesc< Vector<IVector3> >,
	writeFieldDesc< IVector4 >,
	writeFieldDesc< Vector<IVector4> >,
	writeFieldDesc< ResourcePath >,
	writeFieldDesc< Vector<ResourcePath> >,
	writeFieldDesc< SRTTransform >,
	writeFieldDesc< Vector<SRTTransform> >,
};


}

#endif