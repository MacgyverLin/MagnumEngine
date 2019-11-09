#include "MAXRawIndex.h"
#include <windows.h>
using namespace EpicForce;

bool MAXRawIndex::operator < (const MAXRawIndex &other) const
{
	/*
	bool less = false;

	if(p < other.p)
	{
		less = true;
	}
	else if(p == other.p)
	{
		if(n < other.n)
		{
			less = true;
		}
		else if(n == other.n)
		{
			int i = 0;
			while(i<9)
			{
				if(t[i] < other.t[i])
				{
					less = true;
					break;
				}
				else if(t[i] == other.t[i])
					i++;
				else
					break;
			};
		}
	}

	return less;
	*/

	bool less = false;

	int i = 0;
	while(i<MAXRawIndex::MaxNumIndices)
	{
		if(indices[i] < other.indices[i])
		{
			less = true;
			break;
		}
		else if(indices[i] == other.indices[i])
			i++;
		else
			break;
	};

	return less;
}

bool MAXRawIndex::operator == (const MAXRawIndex &other) const
{
	return memcmp(this, &other, sizeof(MAXRawIndex)) == 0;
}

bool MAXRawIndex::operator > (const MAXRawIndex &other) const
{
	return memcmp(this, &other, sizeof(MAXRawIndex)) > 0;
}