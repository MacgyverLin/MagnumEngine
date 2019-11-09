#ifndef _MAXRawIndex_h_
#define _MAXRawIndex_h_

#include "Vector3.h"
#include "Vector4.h"
#include "IGame/IGame.h"
#include "IGame/IGameObject.h"
#include "IGame/IGameProperty.h"
#include "IGame/IGameControl.h"
#include "IGame/IGameModifier.h"
#include "IGame/IConversionManager.h"
#include "IGame/IGameError.h"

namespace EpicForce
{

class MAXRawIndex
{
public:
	enum
	{
		MaxNumIndices = 16
	};
	int indices[MaxNumIndices];

	bool operator < (const MAXRawIndex &other) const;
	bool operator == (const MAXRawIndex &other) const;
	bool operator > (const MAXRawIndex &other) const;
};

};

#endif