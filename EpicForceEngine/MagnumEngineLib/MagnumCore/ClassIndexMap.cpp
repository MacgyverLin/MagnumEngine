#include "ClassIndexMap.h"
#include <assert.h>
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
#include "Rectangle2.h"
using namespace Magnum;

///////////////////////////////////////////////////////////////////////////////////
ClassIndexMap *ClassIndexMap::_instance = 0;

ClassIndexMap &ClassIndexMap::instance()
{
	assert(_instance);

	return *_instance;
}

ClassIndexMap::ClassIndexMap()
{
	assert(_instance == 0);

	_instance = this;
}

ClassIndexMap::~ClassIndexMap()
{
	assert(_instance != 0);

	_instance = 0;
}

void ClassIndexMap::initialize()
{
	addClass(typeid(bool					).name()	);
	addClass(typeid(Vector<bool>			).name()	);
	addClass(typeid(int						).name()	);
	addClass(typeid(Vector<int>				).name()	);
	addClass(typeid(unsigned int			).name()	);
	addClass(typeid(Vector<unsigned int>	).name()	);
	addClass(typeid(float					).name()	);
	addClass(typeid(Vector<float>			).name()	);
	addClass(typeid(double					).name()	);
	addClass(typeid(Vector<double>			).name()	);
	addClass(typeid(String					).name()	);
	addClass(typeid(Vector<String>			).name()	);
	addClass(typeid(ColorRGBA				).name()	);
	addClass(typeid(Vector<ColorRGBA>		).name()	);
	addClass(typeid(Vector2					).name()	);
	addClass(typeid(Vector<Vector2>			).name()	);
	addClass(typeid(Vector3					).name()	);
	addClass(typeid(Vector<Vector3>			).name()	);
	addClass(typeid(Vector4					).name()	);
	addClass(typeid(Vector<Vector4>			).name()	);
	addClass(typeid(IVector2				).name()	);
	addClass(typeid(Vector<IVector2>		).name()	);
	addClass(typeid(IVector3				).name()	);
	addClass(typeid(Vector<IVector3>		).name()	);
	addClass(typeid(IVector4				).name()	);	
	addClass(typeid(Vector<IVector4>		).name()	);
	addClass(typeid(ResourcePath			).name()	);	
	addClass(typeid(Vector<ResourcePath>	).name()	);
	addClass(typeid(SRTTransform			).name()	);	
	addClass(typeid(Vector<SRTTransform>	).name()	);
	addClass(typeid(Rectangle2				).name()	);
	addClass(typeid(Vector<Rectangle2>		).name()	);
}

void ClassIndexMap::clear()
{
	classNameMap.clear();
	classNames.clear();
}

int ClassIndexMap::getNumClasses() const
{
	return classNames.size();
}

void ClassIndexMap::addClass(const char *name)
{
	classNameMap.insert( std::pair<const char *, int>(name, classNameMap.size()) );
	classNames.push_back(name);
}

const char *ClassIndexMap::getClassName(int idx) const
{
	return classNames[idx];
}

int ClassIndexMap::getClassIndex(const char *name) const
{
	std::map<const char *, int, ltstr>::const_iterator itr = classNameMap.find(name);
	if(itr==classNameMap.end())
		return -1;

	return itr->second;
}