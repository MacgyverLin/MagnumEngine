///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "ReflectEntity.h"
using namespace Magnum;

ReflectEntity::ReflectEntity()
: touchpadMethod(this, &ReflectEntity::touchpadEvent)
, keypadMethod(this, &ReflectEntity::keypadEvent)
, acceleratorMethod(this, &ReflectEntity::acceleratorEvent)
{
	TextureCubeFile::Resource *resource = TextureCubeFile::Resource::get("cubemaptest");
	
	prop0		= true;

	bool a		= prop0;
	int  b		= prop1;

	prop0		= true;
	prop1		= 1;
	prop2		= 2;
	prop3		= 1.1;
	prop4		= 2.2;
	prop5		= "Hello";
	prop6		= ColorRGBA(0.1, 0.2, 0.3, 0.4);
	prop7		= Vector2(1, 2);
	prop8		= Vector3(3, 4, 5);
	prop9		= Vector4(6, 7, 8, 9);
	prop10		= IVector2(10, 11);
	prop11		= IVector3(12, 13, 14);
	prop12		= IVector4(15, 16, 17, 18);
	prop13		= ResourcePath("1", "2");
	prop14		= SRTTransform(Vector3(1, 2, 3), Vector3(4, 5, 6), Vector3(7, 8, 9));

	startTheta = 0;
	endTheta   = 360;
	startPhi   = 0;
	endPhi     = 180;
	radius     = 10;
	height     = 40;
	slices     = 10;
	segments   = 8;

	v0										=	false;
	v5										=	123458;
	v6										=	9876532;
	v7										=	1.123456789;
	v8										=	9.87654321;
	v9										=	"fuck somthing 2";
	v10										=   ColorRGBA(0.1, 0.2, 0.3, 0.4);
	v11										=   Vector2(1, 2);
	v12										=   Vector3(1, 2, 3);
	v13										=   Vector4(1, 2, 3, 4);
	v14										=   IVector2(1, 2);
	v15										=   IVector3(1, 2, 3);
	v16										=   IVector4(1, 2, 3, 4);
	v17										=   ResourcePath("123", "audioclip");

	vectorValue0.push()						=	true;
	vectorValue5.push()						=	2468011;
	vectorValue6.push()						=	9874611;
	vectorValue7.push()						=	1.123456789;
	vectorValue8.push()						=	9.87654321;
	vectorValue9.push()						=	"fuck somthing 2";
	vectorValue10.push()					=   ColorRGBA(0.1, 0.2, 0.3, 0.4);
	vectorValue11.push()					=   Vector2(11, 12);
	vectorValue12.push()					=   Vector3(13, 14, 15);
	vectorValue13.push()					=   Vector4(16, 17, 18, 19);
	vectorValue14.push()					=   IVector2(20, 21);
	vectorValue15.push()					=   IVector3(22, 23, 24);
	vectorValue16.push()					=   IVector4(25, 26, 20, 28);
	vectorValue17.push()					=   ResourcePath("456", "texture");


	vectorValue0.push()						=	false; vectorValue0.push()						=	true;
	vectorValue5.push()						=	1235678;
	vectorValue6.push()						=	981272634;
	vectorValue7.push()						=	10.123456789;
	vectorValue8.push()						=	90.87654321;
	vectorValue9.push()						=	"super fuck somthing 2";
	vectorValue10.push()					=   ColorRGBA(0.2, 0.4, 0.6, 0.8);
	vectorValue11.push()					=   Vector2(29, 30);
	vectorValue12.push()					=   Vector3(31, 32, 33);
	vectorValue13.push()					=   Vector4(34, 35, 36, 37);
	vectorValue14.push()					=   IVector2(38, 39);
	vectorValue15.push()					=   IVector3(40, 41, 42);
	vectorValue16.push()					=   IVector4(43, 44, 45, 46);
	vectorValue17.push()					=   ResourcePath("789", "vfx");


	////////////////////////////////////////////////////////////////////////////////////
	const ClassDesc &classDesc				=	getClassDesc();
	const char *className					=	classDesc.getName();
	const ClassDesc &superClassDesc			=	classDesc.getSuper();
	const char *superClassName				=	superClassDesc.getName();

	////////////////////////////////////////////////////////////////////////////////////
	const MethodDesc &method0  = classDesc.getMethod("method0");
	const MethodDesc &method1  = classDesc.getMethod("method1");
	const MethodDesc &method2  = classDesc.getMethod("method2");
	const MethodDesc &method3  = classDesc.getMethod("method3");
	const MethodDesc &method4  = classDesc.getMethod("method4");
	const MethodDesc &method5  = classDesc.getMethod("method5");
	const MethodDesc &method6  = classDesc.getMethod("method6");
	const MethodDesc &method7  = classDesc.getMethod("method7");
	const MethodDesc &method8  = classDesc.getMethod("method8");
	const MethodDesc &method9  = classDesc.getMethod("method9");
	const MethodDesc &method10 = classDesc.getMethod("method10");

	Entity					*base = this;
	bool					rvalV0;
	char					rvalV1;
	unsigned char			rvalV2;
	short					rvalV3;
	unsigned short			rvalV4;
	int						rvalV5;
	unsigned int			rvalV6;
	float					rvalV7;
	double					rvalV8;
	const char *			rvalV9;
	String					rvalV10;
	method0.invoke(rvalV0, this, 1, '1');
	method1.invoke(rvalV1, this, 1, '1');
	method2.invoke(rvalV2, this, 1, '1');
	method3.invoke(rvalV3, this, 1, '1');
	method4.invoke(rvalV4, this, 1, '1');
	method5.invoke(rvalV5, this, 1, '1');
	method6.invoke(rvalV6, this, 1, '1');
	method7.invoke(rvalV7, this, 1, '1');
	method8.invoke(rvalV8, this, 1, '1');
	method9.invoke(rvalV9, this, 1, '1');
	method10.invoke(rvalV10, this, 1, '1');

	method0.invoke(rvalV0, base, 1, '1');
	method1.invoke(rvalV1, base, 1, '1');
	method2.invoke(rvalV2, base, 1, '1');
	method3.invoke(rvalV3, base, 1, '1');
	method4.invoke(rvalV4, base, 1, '1');
	method5.invoke(rvalV5, base, 1, '1');
	method6.invoke(rvalV6, base, 1, '1');
	method7.invoke(rvalV7, base, 1, '1');
	method8.invoke(rvalV8, base, 1, '1');
	method9.invoke(rvalV9, base, 1, '1');
	method10.invoke(rvalV10, base, 1, '1');
	

	bool rval;
	rval = classDesc.isBase(superClassDesc);
	rval = classDesc.isRelative(superClassDesc);
	rval = classDesc.isSame(superClassDesc);
	rval = classDesc.isSuper(superClassDesc);
	rval = superClassDesc.isBase(classDesc);
	rval = superClassDesc.isRelative(classDesc);
	rval = superClassDesc.isSame(classDesc);
	rval = superClassDesc.isSuper(classDesc);

	const char *accessTypeStrs[] =
	{
		"public",
		"protected",
		"private",
	};

	char					testV1;
	unsigned char			testV2;
	short					testV3;
	unsigned short			testV4;
	int						testV5;
	unsigned int			testV6;
	float					testV7;
	double					testV8;
	const char *			testV9;
	String					testV10;
	
	Vector<char >			testVectorValue1;
	Vector<unsigned char>	testVectorValue2;
	Vector<short>			testVectorValue3;
	Vector<unsigned short>	testVectorValue4;
	Vector<int>				testVectorValue5;
	Vector<unsigned int>	testVectorValue6;
	Vector<float>			testVectorValue7;
	Vector<double>			testVectorValue8;
	Vector<const char *>	testVectorValue9;
	Vector<String>			testVectorValue10;

    const ClassDesc::FieldDescList &fieldDescList				= classDesc.getFields();
	for(ClassDesc::FieldDescListCItr itr=fieldDescList.begin(); itr!=fieldDescList.end(); itr++)
	{
		const ClassDesc &classDesc	 = itr->getClass();

		const ACCESS_TYPE accessType = itr->getAccess();
		int classIndex				 = itr->getClassIndex();
		const char *name			 = itr->getName();

		/*
		get(*itr, testV1, this);
		get(*itr, testV2, this);
		get(*itr, testV3, this);
		get(*itr, testV4, this);
		get(*itr, testV5, this);
		get(*itr, testV6, this);
		get(*itr, testV7, this);
		get(*itr, testV8, this);
		get(*itr, testV9, this);
		get(*itr, testV10, this);

		get(*itr, testVectorValue1, this);
		get(*itr, testVectorValue2, this);
		get(*itr, testVectorValue3, this);
		get(*itr, testVectorValue4, this);
		get(*itr, testVectorValue5, this);
		get(*itr, testVectorValue6, this);
		get(*itr, testVectorValue7, this);
		get(*itr, testVectorValue8, this);
		get(*itr, testVectorValue9, this);
		get(*itr, testVectorValue10, this);
		*/

		/*
		itr->get(testV1, this);
		itr->get(testV2, this);
		itr->get(testV3, this);
		itr->get(testV4, this);
		itr->get(testV5, this);
		itr->get(testV6, this);
		itr->get(testV7, this);
		itr->get(testV8, this);
		itr->get(testV9, this);
		itr->get(testV10, this);
	
		itr->get(testVectorValue1, this);
		itr->get(testVectorValue2, this);
		itr->get(testVectorValue3, this);
		itr->get(testVectorValue4, this);
		itr->get(testVectorValue5, this);
		itr->get(testVectorValue6, this);
		itr->get(testVectorValue7, this);
		itr->get(testVectorValue8, this);
		itr->get(testVectorValue9, this);
		itr->get(testVectorValue10, this);
		*/
		//debug("Class Name=%s: %s %s %s", classDesc.getName(), accessTypeStrs[accessType], type, name);
	}

	const ClassDesc::StaticFieldDescList &staticFieldDescList	= classDesc.getStaticFields();
	for(ClassDesc::StaticFieldDescListCItr itr=staticFieldDescList.begin(); itr!=staticFieldDescList.end(); itr++)
	{
		const ClassDesc &classDesc	 = itr->getClass();

		const ACCESS_TYPE accessType = itr->getAccess();
		int classIndex				 = itr->getClassIndex();
		const char *name			 = itr->getName();

		//debug("Class Name=%s: %s %s %s", classDesc.getName(), accessTypeStrs[accessType], type, name);
	}

    const ClassDesc::MethodDescList &methodDescList				= classDesc.getMethods();
	for(ClassDesc::MethodDescListCItr itr=methodDescList.begin(); itr!=methodDescList.end(); itr++)
	{
		const ClassDesc &classDesc	 = itr->getClass();

		const ACCESS_TYPE accessType = itr->getAccess();
		const char *type			 = itr->getType();
		const char *name			 = itr->getName();
		const char *args			 = itr->getArgs();
		const char *id				 = itr->getId();

		//debug("Class Name=%s: %s %s %s %s %s", classDesc.getName(), accessTypeStrs[accessType], type, name, args, id);
	}

	const ClassDesc::StaticMethodDescList &staticMethodDescList = classDesc.getStaticMethods();
	for(ClassDesc::StaticMethodDescListCItr itr=staticMethodDescList.begin(); itr!=staticMethodDescList.end(); itr++)
	{
		const ClassDesc &classDesc	 = itr->getClass();

		const ACCESS_TYPE accessType = itr->getAccess();
		const char *type			 = itr->getType();
		const char *name			 = itr->getName();
		const char *args			 = itr->getArgs();
		const char *id				 = itr->getId();

		//debug("Class Name=%s: %s %s %s %s %s", classDesc.getName(), accessTypeStrs[accessType], type, name, args, id);
	}

	const ClassDesc::PropertyDescList &propertyDescList			= classDesc.getProperties();
}

ReflectEntity::~ReflectEntity()
{
}

bool ReflectEntity::onConstruct()
{
	return true;
}

void ReflectEntity::onStart()
{
}

void ReflectEntity::onPause()
{
}

void ReflectEntity::onResume()
{
}

void ReflectEntity::onUpdate(float dt)
{
}

void ReflectEntity::onStop()
{
}

void ReflectEntity::onDestruct()
{
}

void ReflectEntity::touchpadEvent(const Input::TouchpadEvent &evt)
{
}

void ReflectEntity::keypadEvent(const Input::GamepadEvent &evt)
{
}

void ReflectEntity::acceleratorEvent(const Input::AcceleratorEvent &evt)
{
}

bool ReflectEntity::method0(int a, char b)
{
	return true;
}

char ReflectEntity::method1(int a, char b)
{
	return 'a';
}

unsigned char ReflectEntity::method2(int a, char b)
{
	return 'aa';
}

short ReflectEntity::method3(int a, char b)
{
	return 1;
}

unsigned short ReflectEntity::method4(int a, char b)
{
	return 2;
}

int	ReflectEntity::method5(int a, char b)
{
	return 3;
}

unsigned int ReflectEntity::method6(int a, char b)
{
	return 4;
}

float ReflectEntity::method7(int a, char b)
{
	return 5.0;
}

double ReflectEntity::method8(int a, char b)
{
	return 6.0;
}

const char *ReflectEntity::method9(int a, char b)
{
	return "test1";
}

String ReflectEntity::method10(int a, char b)
{
	return "test2";
}