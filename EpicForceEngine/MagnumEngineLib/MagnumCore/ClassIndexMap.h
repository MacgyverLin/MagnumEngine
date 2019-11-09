///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _ClassIndexMap_h_
#define _ClassIndexMap_h_

#include <typeinfo>
#include <map>
#include <vector>
#include "InputStream.h"
#include "OutputStream.h"
using namespace Magnum;

namespace Magnum
{

class ClassIndexMap
{
public:
	struct ltstr
	{
		bool operator()(const char* s1, const char* s2) const
		{
			return strcmp(s1, s2) < 0;
		}
	};

	ClassIndexMap();
	virtual ~ClassIndexMap();

	static ClassIndexMap &instance();

	void initialize();
	void clear();

	int getNumClasses() const;
	void addClass(const char *name);
	const char *getClassName(int idx) const;
	int getClassIndex(const char *name) const;
protected:
private:
	static ClassIndexMap *_instance;

	std::map<const char *, int, ltstr>	classNameMap;
	std::vector<const char *>			classNames;
};

}

#endif