///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _ReflectEntity_h_
#define _ReflectEntity_h_

#include <MagnumEngine.h>
using namespace Magnum;

class ReflectEntity : public Entity
{
public:
	ReflectEntity();
	virtual ~ReflectEntity();
	
	DECLARE_ENTITY(ReflectEntity);

	/////////////////////////////////////////////////////////////
	PROPERTY(bool							, prop0);
	PROPERTY(int							, prop1);
	PROPERTY(unsigned int					, prop2);
	PROPERTY(float							, prop3);
	PROPERTY(double							, prop4);
	PROPERTY(String							, prop5);
	PROPERTY(ColorRGBA						, prop6);
	PROPERTY(Vector2						, prop7);
	PROPERTY(Vector3						, prop8);
	PROPERTY(Vector4						, prop9);
	PROPERTY(IVector2						, prop10);
	PROPERTY(IVector3						, prop11);
	PROPERTY(IVector4						, prop12);
	PROPERTY(ResourcePath					, prop13);
	PROPERTY(SRTTransform					, prop14);

	PROPERTY(Vector<bool		>			, vectorProp0);
	PROPERTY(Vector<int			>			, vectorProp1);
	PROPERTY(Vector<unsigned int>			, vectorProp2);
	PROPERTY(Vector<float		>			, vectorProp3);
	PROPERTY(Vector<double		>			, vectorProp4);
	PROPERTY(Vector<String		>			, vectorProp5);
	PROPERTY(Vector<ColorRGBA	>			, vectorProp6);
	PROPERTY(Vector<Vector2		>			, vectorProp7);
	PROPERTY(Vector<Vector3		>			, vectorProp8);
	PROPERTY(Vector<Vector4		>			, vectorProp9);
	PROPERTY(Vector<IVector2	>			, vectorProp10);
	PROPERTY(Vector<IVector3	>			, vectorProp11);
	PROPERTY(Vector<IVector4	>			, vectorProp12);
	PROPERTY(Vector<ResourcePath>			, vectorProp13);
	PROPERTY(Vector<SRTTransform>			, vectorProp14);

	/////////////////////////////////////////////////////////////
	FIELD(public, float							, startTheta);
	FIELD(public, float							, endTheta  );
	FIELD(public, float							, startPhi  );
	FIELD(public, float							, endPhi    );
	FIELD(public, float							, radius    );
	FIELD(public, float							, height    );	
	FIELD(public, int							, slices    );	
	FIELD(public, int							, segments  );	


	FIELD(public, bool							, v0);
	//FIELD(public, char						, v1);
	//FIELD(public, unsigned  char				, v2);
	//FIELD(public, short						, v3);
	//FIELD(public, unsigned short				, v4);
	FIELD(public, int							, v5);
	FIELD(public, unsigned int					, v6);
	FIELD(public, float							, v7);
	FIELD(public, double						, v8);
	FIELD(public, String						, v9);
	FIELD(public, ColorRGBA						, v10);
	FIELD(public, Vector2						, v11);
	FIELD(public, Vector3						, v12);
	FIELD(public, Vector4						, v13);
	FIELD(public, IVector2						, v14);
	FIELD(public, IVector3						, v15);
	FIELD(public, IVector4						, v16);
	FIELD(public, ResourcePath					, v17);

	FIELD(public, Vector<bool>					, vectorValue0);
	//FIELD(public, Vector<char>				, vectorValue1);
	//FIELD(public, Vector<unsigned char>		, vectorValue2);
	//FIELD(public, Vector<short>				, vectorValue3);
	//FIELD(public, Vector<unsigned short>		, vectorValue4);
	FIELD(public, Vector<int>					, vectorValue5);
	FIELD(public, Vector<unsigned int>			, vectorValue6);
	FIELD(public, Vector<float>					, vectorValue7);
	FIELD(public, Vector<double>				, vectorValue8);
	FIELD(public, Vector<String>				, vectorValue9);
	FIELD(public, Vector<ColorRGBA>				, vectorValue10);
	FIELD(public, Vector<Vector2>				, vectorValue11);
	FIELD(public, Vector<Vector3>				, vectorValue12);
	FIELD(public, Vector<Vector4>				, vectorValue13);
	FIELD(public, Vector<IVector2>				, vectorValue14);
	FIELD(public, Vector<IVector3>				, vectorValue15);
	FIELD(public, Vector<IVector4>				, vectorValue16);
	FIELD(public, Vector<ResourcePath>			, vectorValue17);
	
	METHOD(public, bool 			, method0 , (int a, char b));
	METHOD(public, char 			, method1 , (int a, char b));
	METHOD(public, unsigned char	, method2 , (int a, char b));
	METHOD(public, short			, method3 , (int a, char b));
	METHOD(public, unsigned short	, method4 , (int a, char b));
	METHOD(public, int				, method5 , (int a, char b));
	METHOD(public, unsigned int		, method6 , (int a, char b));
	METHOD(public, float			, method7 , (int a, char b));
	METHOD(public, double			, method8 , (int a, char b));
	METHOD(public, const char *		, method9 , (int a, char b));
	METHOD(public, String			, method10, (int a, char b));
protected:
private:
	virtual bool onConstruct();
	virtual void onStart();
	virtual void onPause();
	virtual void onResume();
	virtual void onUpdate(float dt);
	virtual void onStop();
	virtual void onDestruct();

	void touchpadEvent(const Input::TouchpadEvent &evt);
	void keypadEvent(const Input::GamepadEvent &evt);
	void acceleratorEvent(const Input::AcceleratorEvent &evt);
/////////////////////////////////////////////////////
public:
protected:
private:
	Input::TouchpadMethod<ReflectEntity>		touchpadMethod;
	Input::GamepadMethod<ReflectEntity>			keypadMethod;
	Input::AcceleratorMethod<ReflectEntity>		acceleratorMethod;
};

#endif