#ifndef _VertexIndexOptimizer_h_
#define _VertexIndexOptimizer_h_

#include <map>
#include "Array.h"
#include "MAXRawIndex.h"
using namespace EpicForce;
using namespace std;

namespace EpicForce
{

class VertexIndexOptimizer
{
public:
	VertexIndexOptimizer();
	virtual ~VertexIndexOptimizer();
	int add(const MAXRawIndex &v);
		
	void build();
	int getNumOptimzedIndices() const;
	const MAXRawIndex &getOptimzedIndex(int i) const;
private:
	map<MAXRawIndex, int> indicesMap;
	Vector<MAXRawIndex> indices;
};

};

#endif