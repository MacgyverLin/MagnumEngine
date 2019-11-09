///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#include "VisualEffect2FX.h"
using namespace EpicForce;

///////////////////////////////////////////////////////////////////
VisualEffect2FX::VisualEffect2FX()
{
}

VisualEffect2FX::~VisualEffect2FX()
{
}

bool VisualEffect2FX::convert(const char *srcFilename_, const char *dstFilename_)
{
	// collect Options

	// export
	exportVisualEffect(srcFilename_, dstFilename_);

	return true;
}

bool VisualEffect2FX::exportVisualEffect(const char *srcFilename, const char *dstFilename)
{
	String variable;
	String shader;
	String effect;

	if( !collectEffect(variable, shader, effect, srcFilename) )
		return false;

	if( !writeVisualEffect(dstFilename, variable, shader, effect) )
		return false;

	return true;
}

bool VisualEffect2FX::writeVisualEffect(const char *dstFilename, String &variable, String &shader, String &effect)
{
	FILE *fptr = fopen(dstFilename, "wt");
	if(!fptr)
		return false;

	fprintf(fptr, "%s", variable.text()		);
	fprintf(fptr, "%s", shader.text()		);
	fprintf(fptr, "%s", effect.text()	);

	fclose(fptr);

	return true;
}

void VisualEffect2FX::getChildren(TiXmlNode *node, const char *type, Vector<TiXmlNode *> &children)
{
	children.clear();
	for(TiXmlNode *childNode = node->FirstChild(type); childNode; childNode = childNode->NextSibling(type) )
	{
		children.push() = childNode;
	}
}

void VisualEffect2FX::getChildren(TiXmlNode *node, Vector<TiXmlNode *> &children)
{
	children.clear();
	for(TiXmlNode *childNode = node->FirstChild(); childNode; childNode = childNode->NextSibling() )
	{
		children.push() = childNode;
	}
}

bool VisualEffect2FX::collectEffect(String &variable, String &shader, String &effect, const char *inputFileName)
{
	TiXmlDocument doc(inputFileName);
	if(doc.LoadFile())
	{
		TiXmlNode *visualEffectNode = doc.FirstChild("VisualEffect");

		TiXmlNode *vertexDescNode = visualEffectNode->FirstChild("VertexDesc");
		if(!vertexDescNode)
			return false;

		TiXmlNode *UniformVariablesNode = visualEffectNode->FirstChild("UniformVariables");
		if(!UniformVariablesNode)
			return false;

		TiXmlNode *techniqueNode = visualEffectNode->FirstChild("Technique");
		if(!techniqueNode)
			return false;

		TiXmlElement *techniqueNodeAttributes = techniqueNode->ToElement();
		if(!techniqueNodeAttributes)
			return false;

		const char *techniqueNodeName = techniqueNodeAttributes->Attribute("name");
		if(!techniqueNodeName)
			return false;

		if( !collectVertexDesc(variable, shader, effect, vertexDescNode) )
			return false;

		if( !collectGeneralVariablesBlock(variable, shader, effect, UniformVariablesNode) )
			return false;

		if( !collectLightVariablesBlock(variable, shader, effect, UniformVariablesNode) )
			return false;
	
		if( !collectTexture2DVariablesBlock(variable, shader, effect, UniformVariablesNode) )
			return false;

		if( !collectTextureCubeVariablesBlock(variable, shader, effect, UniformVariablesNode) )
			return false;

		effect += "technique " + String(techniqueNodeName) + "\n";
		effect += "{\n";

		Vector<TiXmlNode *> passNodes;
		getChildren(techniqueNode, "Pass", passNodes);
		for(int i=0; i<passNodes.length(); i++)
		{
			if(!collectPass(variable, shader, effect, passNodes[i]))
				return false;
		}

		effect += "}\n";

		return true;
	}
	else
	{
		return false;
	}
}

bool VisualEffect2FX::collectVertexDesc(String &variable, String &shader, String &effect, TiXmlNode *vertexDescNode)
{
	Vector<TiXmlNode *> descNodes;
	getChildren(vertexDescNode, "Desc", descNodes);
	
	variable += "string vertexDesc = \"";
	
	for(int i=0; i<descNodes.length(); i++)
	{
		TiXmlElement *descNodeAttributes = descNodes[i]->ToElement();
		if(!descNodeAttributes)
			return false;

		const char *vertexStreamSourceName = descNodeAttributes->Attribute("source");
		if(!vertexStreamSourceName)
			return false;

		const char *vertexFormatName = descNodeAttributes->Attribute("format");
		if(!vertexFormatName)
			return false;

		variable += String(vertexStreamSourceName).toLower() + String(",");
		variable += String(vertexFormatName).toLower();

		if(i!=descNodes.length()-1)
			variable += ",";
	}

	variable += "\";\n\n";

	return true;
}

bool VisualEffect2FX::collectPass(String &variable, String &shader, String &effect, TiXmlNode *passNode)
{
	TiXmlNode *renderStatesBlockNode = passNode->FirstChild("RenderStatesBlock");
	if(!renderStatesBlockNode)
		return false;

	TiXmlNode *hlslNode = passNode->FirstChild("HLSL");
	if(!hlslNode)
		return false;

	TiXmlElement *passNodeAttributes = passNode->ToElement();
	if(!passNodeAttributes)
		return false;

	const char *passNodeName = passNodeAttributes->Attribute("name");
	if(!passNodeName)
		return false;

	effect += "\tpass " + String(passNodeName) + String("\n");
	effect += String("\t{\n");

	if( !collectRenderStatesBlock(variable, shader, effect, renderStatesBlockNode) )
		return false;

	if( !collectHLSL(variable, shader, effect, hlslNode) )
		return false;

	effect += String("\t}\n");
	
	return true;
}

String VisualEffect2FX::prepareGeneralVariable(const char *type, const char *name, const char *sematic, const char *annotation, const char *values)
{
	String variable;

	variable += String(type) + " " + String(name);

	if(String(sematic)!="")
		variable += String(" : ") + sematic;

	if(String(annotation)!="")
		variable += String("\n<\n\t") + annotation + String("\n>");

	if(String(values)!="")
		variable += String(" = {") + values + String("};\n\n");
	else
		variable += ";\n\n";

	return variable;
}

String VisualEffect2FX::prepareLightVariable(const char *type, const char *name, const char *sematic, const char *annotation, const char *values)
{
	return prepareGeneralVariable(type, name, sematic, annotation, values);
}

String VisualEffect2FX::prepareTexture2DVariable(const char *name, const char *sematic, const char *texcoord, 
												   const char *minfilter, const char *magfilter, const char *mipfilter,
												   const char *wraps, const char *wrapt)
{
	String variable;

	variable += String("texture ") + String(name);
	if(String(sematic)!="")
		variable += String(" : ") + sematic + String("\n");

	int textureCoord   = atoi(texcoord);
	int mappingChannel = textureCoord + 1;

	char textureCoordBuf[10];
	sprintf(textureCoordBuf, "%d", textureCoord);
	char mappingChannelBuf[10];
	sprintf(mappingChannelBuf, "%d", mappingChannel);

	variable += String("<\n");
	variable += String("\tstring name		= \"\";\n");
	variable += String("\tstring UIName		= \"")	+ name			+ String(" Texture\";\n");
	variable += String("\tstring type		= \"2D\";\n");
	variable += String("\tint Texcoord		= ")	+ textureCoordBuf	+ String(";\n");
	variable += String("\tint MapChannel	= ")	+ mappingChannelBuf	+ String(";\n");
	variable += String(">;\n\n");


	variable += String("sampler ") + String(name) + "Sampler = sampler_state\n";
	variable += String("{\n");
	variable += String("\tTexture		= (") + name		+ String(");\n");
	variable += String("\tMinFilter		= ") + minfilter	+ String(";\n");
	variable += String("\tMagFilter		= ") + magfilter	+ String(";\n");
	variable += String("\tMipFilter		= ") + mipfilter	+ String(";\n");
	variable += String("\tADDRESSU		= ") + wraps		+ String(";\n");
	variable += String("\tADDRESSV		= ") + wrapt		+ String(";\n");
	variable += String("};\n\n");

	return variable;
}

String VisualEffect2FX::prepareTextureCubeVariable(const char *name, const char *sematic, 
												     const char *minfilter, const char *magfilter, const char *mipfilter)
{
	String variable;

	variable += String("texture ") + String(name);
	if(String(sematic)!="")
		variable += String(" : ") + sematic + String("\n");

	variable += String("<\n");
	variable += String("\tstring name		= \"\";\n");
	variable += String("\tstring UIName		= \"")	+ name			+ String(" Texture\";\n");
	variable += String("\tstring type		= \"Cube\";\n");
	variable += String(">;\n\n");

	variable += String("samplerCUBE ") + String(name) + "Sampler = sampler_state\n";
	variable += String("{\n");
	variable += String("\tTexture		= (") + name		+ String(");\n");
	variable += String("\tMinFilter		= ") + minfilter	+ String(";\n");
	variable += String("\tMagFilter		= ") + magfilter	+ String(";\n");
	variable += String("\tMipFilter		= ") + mipfilter	+ String(";\n");
	variable += String("};\n\n");

	return variable;
}

#include <string>
using namespace std;
String VisualEffect2FX::trim(const String &str)
{
	string s = str.text();

	int start = s.find_first_not_of(" ");
	int end   = s.find_last_not_of(" ");

	return String(s.substr(start, end-start+1).c_str());
}

void VisualEffect2FX::tokenize(Vector<String> &tokens, const String &str, const String &delimiters)
{
	string s = str.text();

	tokens.clear();

	// skip delimiters at beginning.
	int lastPos = s.find_first_not_of(delimiters, 0);
	
	// find first "non-delimiter".
	int pos = s.find_first_of(delimiters, lastPos);

	while( pos!=-1 || lastPos!=-1 )
	{
		// found a token, add it to the vector.
		tokens.push() = s.substr(lastPos, pos - lastPos).c_str();

		tokens.back() = trim(tokens.back());
	
		// skip delimiters.  Note the "not_of"
		lastPos = s.find_first_not_of(delimiters, pos);
	
		// find next "non-delimiter"
		pos = s.find_first_of(delimiters, lastPos);
	}
}

bool VisualEffect2FX::collectGeneralVariablesBlock(String &variable, String &shader, String &effect, TiXmlNode *generalVariablesBlockNode)
{
	Vector<TiXmlNode *> generalVariablesNodes;
	getChildren(generalVariablesBlockNode, "General", generalVariablesNodes);

	for(int i=0; i<generalVariablesNodes.length(); i++)
	{
		TiXmlElement *generalVariablesNodeAttributes = generalVariablesNodes[i]->ToElement();
		if(!generalVariablesNodeAttributes)
			return false;

		const char *generalVariableType = generalVariablesNodeAttributes->Attribute("type");
		if(!generalVariableType)
			return false;

		const char *generalVariableName = generalVariablesNodeAttributes->Attribute("name");
		if(!generalVariableName)
			return false;

		const char *generalVariableValues = generalVariablesNodeAttributes->Attribute("default");
		if(!generalVariableValues)
			generalVariableValues = "";

		const char *generalVariableSematic = generalVariablesNodeAttributes->Attribute("sematic");
		if(!generalVariableSematic)
			generalVariableSematic = "";

		const char *generalVariableAnnotation = generalVariablesNodeAttributes->Attribute("annotation");
		if(!generalVariableAnnotation)
			generalVariableAnnotation = "";

		variable += prepareGeneralVariable(generalVariableType, generalVariableName, generalVariableSematic, generalVariableAnnotation, generalVariableValues);
	}

	return true;
}

bool VisualEffect2FX::collectLightVariablesBlock(String &variable, String &shader, String &effect, TiXmlNode *lightVariablesBlockNode)
{
	Vector<TiXmlNode *> lightVariablesNodes;
	getChildren(lightVariablesBlockNode, "Light", lightVariablesNodes);

	for(int i=0; i<lightVariablesNodes.length(); i++)
	{
		TiXmlElement *lightVariablesNodeAttributes = lightVariablesNodes[i]->ToElement();
		if(!lightVariablesNodeAttributes)
			return false;

		const char *lightVariableType = lightVariablesNodeAttributes->Attribute("type");
		if(!lightVariableType)
			return false;

		const char *lightVariableName = lightVariablesNodeAttributes->Attribute("name");
		if(!lightVariableName)
			return false;

		const char *lightVariableColor = lightVariablesNodeAttributes->Attribute("color");
		if(!lightVariableColor)
			return false;

		const char *lightVariableAnnotation = lightVariablesNodeAttributes->Attribute("annotation");
		if(!lightVariableAnnotation)
			lightVariableAnnotation = "";

		if(String(lightVariableType)=="directional")
		{
			const char *lightVariableDirection = lightVariablesNodeAttributes->Attribute("direction");
			if(!lightVariableDirection)
				return false;

			String dirLightVariableDirectionName = String(lightVariableName) + "Direction";
			String dirLightVariableColorName	 = String(lightVariableName) + "Color";

			variable += prepareLightVariable("float3", dirLightVariableDirectionName.text(), "DIRECTION" , "", 
									  lightVariableDirection);

			variable += prepareLightVariable("float4", dirLightVariableColorName.text(),	  "LIGHTCOLOR", "", 
									  lightVariableColor);
			/*
			if( !lightVariablesBlock.set("float3", dirLightVariableDirectionName.text(), lightVariableDirection, "") )
				return false;

			if( !lightVariablesBlock.set("float4", dirLightVariableColorName.text(), lightVariableColor, "") )
				return false;
			*/
		}
		else if(String(lightVariableType)=="omni")
		{
			const char *lightVariablePosition = lightVariablesNodeAttributes->Attribute("position");
			if(!lightVariablePosition)
				return false;

			const char *lightVariableAtteunation = lightVariablesNodeAttributes->Attribute("atteunation");
			if(!lightVariableAtteunation)
				return false;

			String pointLightVariablePositionName		 = String(lightVariableName) + "Position";
			String pointLightVariableColorName			 = String(lightVariableName) + "Color";
			String pointLightVariableAtteunationName	 = String(lightVariableName) + "Atteunation";

			variable += prepareLightVariable("float3", pointLightVariablePositionName.text(),		"POSITION" , "", 
											 lightVariablePosition);

			variable += prepareLightVariable("float4", pointLightVariableColorName.text(),			"LIGHTCOLOR", "", 
											 lightVariableColor);

			variable += prepareLightVariable("float4", pointLightVariableAtteunationName.text(),	"LIGHTATTENUATION", "", 
											 lightVariableAtteunation);
			/*
			if( !lightVariablesBlock.set("float3", pointLightVariablePositionName.text(), lightVariablePosition, "") )
				return false;

			if( !lightVariablesBlock.set("float4", pointLightVariableColorName.text(), lightVariableColor, "") )
				return false;

			if( !lightVariablesBlock.set("float4", pointLightVariableAtteunationName.text(), lightVariableAtteunation, "") )
				return false;
			*/
		}
		else if(String(lightVariableType)=="spot")
		{
			const char *lightVariablePosition = lightVariablesNodeAttributes->Attribute("position");
			if(!lightVariablePosition)
				return false;

			const char *lightVariableAtteunation= lightVariablesNodeAttributes->Attribute("atteunation");
			if(!lightVariableAtteunation)
				return false;

			const char *lightVariableHotspot = lightVariablesNodeAttributes->Attribute("hotspot");
			if(!lightVariableHotspot)
				return false;

			const char *lightVariableFalloff = lightVariablesNodeAttributes->Attribute("falloff");
			if(!lightVariableFalloff)
				return false;

			String spotLightVariablePositionName		 = String(lightVariableName) + "Position";
			String spotLightVariableColorName			 = String(lightVariableName) + "Color";
			String spotLightVariableAtteunationName		 = String(lightVariableName) + "Atteunation";
			String spotLightVariableHotSpotName			 = String(lightVariableName) + "HotSpot";
			String spotLightVariableFallOffName			 = String(lightVariableName) + "FallOff";

			variable += prepareLightVariable("float3", spotLightVariablePositionName.text(),		"POSITION" , "", 
											 lightVariablePosition);

			variable += prepareLightVariable("float4", spotLightVariableColorName.text(),			"LIGHTCOLOR", "", 
											 lightVariableColor);

			variable += prepareLightVariable("float4", spotLightVariableAtteunationName.text(),	"LIGHTATTENUATION", "", 
											 lightVariableAtteunation);

			variable += prepareLightVariable("float", spotLightVariableHotSpotName.text(),	"LIGHTHOTSPOT", "", 
											 lightVariableHotspot);

			variable += prepareLightVariable("float", spotLightVariableFallOffName.text(),	"LIGHTFALLOFF", "", 
											 lightVariableFalloff);
			/*
			if( !lightVariablesBlock.set("float3", spotLightVariablePositionName.text(), lightVariablePosition, "") )
				return false;

			if( !lightVariablesBlock.set("float4", spotLightVariableColorName.text(), lightVariableColor, "") )
				return false;

			if( !lightVariablesBlock.set("float4", spotLightVariableAtteunationName.text(), lightVariableAtteunation, "") )
				return false;

			if( !lightVariablesBlock.set("float", spotLightVariableHotSpotName.text(), lightVariableHotspot, "") )
				return false;

			if( !lightVariablesBlock.set("float", spotLightVariableFallOffName.text(), lightVariableFalloff, "") )
				return false;
			*/
		}
	}

	return true;
}

bool VisualEffect2FX::collectTexture2DVariablesBlock(String &variable, String &shader, String &effect, TiXmlNode *textureVariablesBlockNode)
{
	Vector<TiXmlNode *> textureVariablesNodes;
	getChildren(textureVariablesBlockNode, "Sampler2D", textureVariablesNodes);

	for(int i=0; i<textureVariablesNodes.length(); i++)
	{
		TiXmlElement *textureVariablesNodeAttributes = textureVariablesNodes[i]->ToElement();
		if(!textureVariablesNodeAttributes)
			return false;

		const char *textureVariableName = textureVariablesNodeAttributes->Attribute("name");
		if(!textureVariableName)
			return false;

		const char *textureVariableTexCoord = textureVariablesNodeAttributes->Attribute("texcoord");
		if(!textureVariableTexCoord)
			return false;

		const char *textureVariableMinFilter = textureVariablesNodeAttributes->Attribute("minfilter");
		if(!textureVariableMinFilter)
			return false;

		const char *textureVariableMagFilter = textureVariablesNodeAttributes->Attribute("magfilter");
		if(!textureVariableMagFilter)
			return false;

		const char *textureVariableMipFilter = textureVariablesNodeAttributes->Attribute("mipfilter");
		if(!textureVariableMipFilter)
			return false;

		const char *textureVariableWrapS = textureVariablesNodeAttributes->Attribute("wraps");
		if(!textureVariableMipFilter)
			return false;

		const char *textureVariableWrapT = textureVariablesNodeAttributes->Attribute("wrapt");
		if(!textureVariableMipFilter)
			return false;

		const char *textureVariableSematic = textureVariablesNodeAttributes->Attribute("sematic");
		if(!textureVariableSematic)
			textureVariableSematic = "";

		variable += prepareTexture2DVariable(textureVariableName,  textureVariableSematic, 
										     textureVariableTexCoord,  
										     textureVariableMinFilter, textureVariableMagFilter,textureVariableMipFilter,
										     textureVariableWrapS, textureVariableWrapT);
	}

	return true;
}

bool VisualEffect2FX::collectTextureCubeVariablesBlock(String &variable, String &shader, String &effect, TiXmlNode *textureVariablesBlockNode)
{
	Vector<TiXmlNode *> textureVariablesNodes;
	getChildren(textureVariablesBlockNode, "SamplerCube", textureVariablesNodes);

	for(int i=0; i<textureVariablesNodes.length(); i++)
	{
		TiXmlElement *textureVariablesNodeAttributes = textureVariablesNodes[i]->ToElement();
		if(!textureVariablesNodeAttributes)
			return false;

		const char *textureVariableName = textureVariablesNodeAttributes->Attribute("name");
		if(!textureVariableName)
			return false;

		const char *textureVariableMinFilter = textureVariablesNodeAttributes->Attribute("minfilter");
		if(!textureVariableMinFilter)
			return false;

		const char *textureVariableMagFilter = textureVariablesNodeAttributes->Attribute("magfilter");
		if(!textureVariableMagFilter)
			return false;

		const char *textureVariableMipFilter = textureVariablesNodeAttributes->Attribute("mipfilter");
		if(!textureVariableMipFilter)
			return false;

		const char *textureVariableSematic = textureVariablesNodeAttributes->Attribute("sematic");
		if(!textureVariableSematic)
			textureVariableSematic = "";

		variable += prepareTextureCubeVariable(textureVariableName,  textureVariableSematic, 
										       textureVariableMinFilter, textureVariableMagFilter,textureVariableMipFilter);
	}

	return true;
}

bool VisualEffect2FX::collectRenderStatesBlock(String &variable, String &shader, String &effect, TiXmlNode *renderStatesBlockNode)
{
	Vector<TiXmlNode *> renderStateNodes;
	getChildren(renderStatesBlockNode, "RenderState", renderStateNodes);
	
	for(int i=0; i<renderStateNodes.length(); i++)
	{
		TiXmlElement *renderStateNodeAttributes = renderStateNodes[i]->ToElement();
		if(!renderStateNodeAttributes)
			return false;

		const char *renderStateType = renderStateNodeAttributes->Attribute("type");
		if(!renderStateType)
			return false;

		const char *renderStateValue = renderStateNodeAttributes->Attribute("value");
		if(!renderStateValue)
			return false;

		effect += "\t\t";
		effect += renderStateType;
		effect += " = ";
		effect += renderStateValue;
		effect += ";\n";
	}

	effect += "\n";

	return true;
}

bool VisualEffect2FX::collectHLSL(String &variable, String &shader, String &effect, TiXmlNode *hlslNode)
{
	TiXmlNode *vsCodeNode = hlslNode->FirstChild("VertexShader");
	TiXmlNode *psCodeNode = hlslNode->FirstChild("PixelShader");

	if(!vsCodeNode || !vsCodeNode->ToElement() || !vsCodeNode->FirstChild())
		return false;
	if(!psCodeNode || !psCodeNode->ToElement() || !psCodeNode->FirstChild())
		return false;

	TiXmlElement *vsCodeNodeAttributes = vsCodeNode->ToElement();
	TiXmlElement *psCodeNodeAttributes = psCodeNode->ToElement();
	TiXmlNode *vsCodeTextNode = vsCodeNode->FirstChild();
	TiXmlNode *psCodeTextNode = psCodeNode->FirstChild();

	const char *vsEntryPointName = vsCodeNodeAttributes->Attribute("entrypoint");
	if(!vsEntryPointName)
		return false;

	const char *psEntryPointName = psCodeNodeAttributes->Attribute("entrypoint");
	if(!psEntryPointName)
		return false;

	effect += String("\t\tVertexShader = compile vs_3_0 ") + vsEntryPointName + String("();\n");
	effect += String("\t\tPixelShader  = compile ps_3_0 ") + psEntryPointName + String("();\n");

	shader += vsCodeTextNode->Value();
	shader += psCodeTextNode->Value();
	shader += String("\n\n");
}