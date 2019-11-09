#ifndef _VisualEffect2FX_h_
#define _VisualEffect2FX_h_

#include "Stage.h"
#include "Platform.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "VisualEffect.h"
#include "tinyxml.h"

namespace EpicForce
{

class VisualEffect2FX
{
public:
	VisualEffect2FX();
	virtual ~VisualEffect2FX();

	bool convert(const char *srcFilename_, const char *dstFilename_);
private:
	bool exportVisualEffect(const char *srcFilename, const char *dstFilename);
	bool writeVisualEffect(const char *dstFilename, String &variable, String &shader, String &effect);
		void getChildren(TiXmlNode *node, const char *type, Vector<TiXmlNode *> &children);
		void getChildren(TiXmlNode *node, Vector<TiXmlNode *> &children);
		String trim(const String &str);
		void tokenize(Vector<String> &tokens, const String &str, const String &delimiters);
		
		bool collectEffect(String &variable, String &shader, String &effect, const char *inputFileName);
			bool collectVertexDesc(String &variable, String &shader, String &effect,TiXmlNode *vertexDescNode);
			bool collectPass(String &variable, String &shader, String &effect,TiXmlNode *passNode);

			String prepareGeneralVariable(const char *type, const char *name, const char *sematic, const char *annotation, const char *values);
			String prepareLightVariable(const char *type, const char *name, const char *sematic, const char *annotation, const char *values);
			String prepareTexture2DVariable(const char *name, const char *sematic, const char *texcoord, 
											const char *minfilter, const char *magfilter, const char *mipfilter,
											const char *wraps, const char *wrapt);
			String prepareTextureCubeVariable(const char *name, const char *sematic, 
											  const char *minfilter, const char *magfilter, const char *mipfilter);
	
			bool collectGeneralVariablesBlock(String &variable, String &shader, String &effect, TiXmlNode *generalVariablesBlockNode);
			bool collectLightVariablesBlock(String &variable, String &shader, String &effect, TiXmlNode *lightVariablesBlockNode);
			bool collectTexture2DVariablesBlock(String &variable, String &shader, String &effect, TiXmlNode *textureVariablesBlockNode);
			bool collectTextureCubeVariablesBlock(String &variable, String &shader, String &effect, TiXmlNode *textureVariablesBlockNode);
			bool collectRenderStatesBlock(String &variable, String &shader, String &effect, TiXmlNode *renderStatesBlockNode);
			bool collectHLSL(String &variable, String &shader, String &effect, TiXmlNode *glslNode);
};

};

#endif
