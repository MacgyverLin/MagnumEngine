#ifndef _Helper_h_
#define _Helper_h_

#include "IGame/IGame.h"
#include "IGame/IGameObject.h"
#include "IGame/IGameProperty.h"
#include "IGame/IGameControl.h"
#include "IGame/IGameModifier.h"
#include "IGame/IConversionManager.h"
#include "IGame/IGameError.h"
#include "EString.h"
#include "SkeletalAnimModel.h"

namespace EpicForce
{

class Helper
{
public:
	static String trim(const String &str);
	static void tokenize(Vector<String> &tokens, const String &str, const String &delimiters);
	static void parseValues(Vector<String> &values, const String &str);
	static bool parseDefaultValues(Vector<String> &values, const String &str);

	static void convertMatrixToVector10(Vector3 &t, Quaternion &q, Vector3 &k, const GMatrix &tm, float metersPerUnit);
};

};

#endif