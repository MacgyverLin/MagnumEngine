#include "VertexIndexOptimizer.h"
using namespace EpicForce;

VertexIndexOptimizer::VertexIndexOptimizer()
{
}

VertexIndexOptimizer::~VertexIndexOptimizer()
{
}

int VertexIndexOptimizer::add(const MAXRawIndex &v)
{
	map<MAXRawIndex, int>::iterator itr = indicesMap.find(v);
	if( itr!=indicesMap.end() )
		return itr->second;
	else
	{
		int idx = indicesMap.size();
		indicesMap.insert( pair<MAXRawIndex, int>(v, indicesMap.size()) );
		return idx;
	}
}

void VertexIndexOptimizer::build()
{
	indices.resize(indicesMap.size());

	map<MAXRawIndex, int>::iterator itr;
	for(itr=indicesMap.begin(); itr!=indicesMap.end(); itr++)
	{
		indices[itr->second] = itr->first;
	}
}

int VertexIndexOptimizer::getNumOptimzedIndices() const
{
	return indices.length();
}

const MAXRawIndex &VertexIndexOptimizer::getOptimzedIndex(int i) const
{
	return indices[i];
}