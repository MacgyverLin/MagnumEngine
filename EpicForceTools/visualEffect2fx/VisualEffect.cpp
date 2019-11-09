///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#include "VisualEffect.h"
#include "tinyxml.h"
using namespace EpicForce;

///////////////////////////////////////////////////////////////////
VisualEffect::ShaderProgram::ShaderProgram()
: handle(0)
{
}

VisualEffect::ShaderProgram::~ShaderProgram()
{
}

VisualEffect::ShaderProgram &VisualEffect::ShaderProgram::operator = (const VisualEffect::ShaderProgram &other)
{
	vertexShaderCode	= other.vertexShaderCode;
	pixelShaderCode		= other.pixelShaderCode;
	handle				= other.handle;

	return *this;
}

void VisualEffect::ShaderProgram::set(const char *vertexShaderCode_, const char *pixelShaderCode_)
{
	vertexShaderCode	= vertexShaderCode_;
	pixelShaderCode		= pixelShaderCode_;
}

void VisualEffect::ShaderProgram::read(InputStream &is)
{
	is >> vertexShaderCode;
	is >> pixelShaderCode;
}

void VisualEffect::ShaderProgram::write(OutputStream &os) const
{
	os << vertexShaderCode;
	os << pixelShaderCode;
}

VisualEffect::Pass::Pass()
{
}

VisualEffect::Pass::~Pass()
{
}

VisualEffect::Pass &VisualEffect::Pass::operator = (const VisualEffect::Pass &other)
{
	this->name						= other.name;

	this->generalVariablesBlock		= other.generalVariablesBlock;
	this->lightVariables			= other.lightVariables;
	
	this->textureVariables			= other.textureVariables;
	this->textureHandles			= other.textureHandles;

	this->renderStatesBlock			= other.renderStatesBlock;

	this->shaderProgram				= other.shaderProgram;

	return *this;
}

const char *VisualEffect::Pass::getName() const
{
	return name;
}

const UniformVariablesBlock	&VisualEffect::Pass::getGeneralVariablesBlock() const
{
	return generalVariablesBlock;
}

int VisualEffect::Pass::getNumLightVariables() const
{
	return lightVariables.length();
}

const LightVariable &VisualEffect::Pass::getLightVariable(int i) const
{
	return lightVariables[i];
}

int VisualEffect::Pass::getNumTextureVariables() const
{
	return textureVariables.length();
}

const TextureVariable &VisualEffect::Pass::getTextureVariable(int i) const
{
	return textureVariables[i];
}

const RenderStatesBlock &VisualEffect::Pass::getRenderStatesBlock() const
{
	return renderStatesBlock;
}

const VisualEffect::ShaderProgram &VisualEffect::Pass::getShaderProgram() const
{
	return shaderProgram;
}

void VisualEffect::Pass::read(InputStream &is)
{
	is >> name;

	is >> generalVariablesBlock;

	int numLightVariables;
	is >> numLightVariables;
	lightVariables.resize(numLightVariables);
	for(int i=0; i<lightVariables.length(); i++)
		is >> lightVariables[i];

	int numTextureVariables;
	is >> numTextureVariables;
	textureVariables.resize(numTextureVariables);
	for(int i=0; i<textureVariables.length(); i++)
		is >> textureVariables[i];

	is >> renderStatesBlock;

	is >> shaderProgram;
}

void VisualEffect::Pass::write(OutputStream &os) const
{
	os << name;

	os << generalVariablesBlock;

	int numLightVariables = lightVariables.length();
	os << numLightVariables;
	for(int i=0; i<lightVariables.length(); i++)
		os << lightVariables[i];
	
	int numTextureVariables = textureVariables.length();
	os << numTextureVariables;
	for(int i=0; i<textureVariables.length(); i++)
		os << textureVariables[i];

	os << renderStatesBlock;

	os << shaderProgram;
}

///////////////////////////////////////////////////////////////////
VisualEffect::Data::Data()
{
}

VisualEffect::Data::~Data()
{
}

VisualEffect::Data &VisualEffect::Data::operator = (const VisualEffect::Data &other)
{
	this->version			= other.version;
	this->platform			= other.platform;
	
	this->vertexDesc		= other.vertexDesc;
	this->passes			= other.passes;

	return *this;
}

int VisualEffect::Data::getVersion() const
{
	return version;
}

Platform VisualEffect::Data::getPlatform() const
{
	return platform;
}

const VertexDesc &VisualEffect::Data::getVertexDesc() const
{
	return vertexDesc;
}

int VisualEffect::Data::getNumPasses() const
{
	return passes.length();
}

const VisualEffect::Pass &VisualEffect::Data::getPass(int i) const
{
	return passes[i];
}

void VisualEffect::Data::read(InputStream &is)
{
	is >> version;
	is >> platform;

	is >> vertexDesc;

	int numPasses;
	is >> numPasses;
	passes.resize(numPasses);
	for(int i=0; i<passes.length(); i++)
	{
		is >> passes[i];
	}
}

void VisualEffect::Data::write(OutputStream &os) const
{
	os << version;
	os << platform;
	
	os << vertexDesc;

	int numPasses = passes.length();
	os << numPasses;
	for(int i=0; i<passes.length(); i++)
	{
		os << passes[i];
	}
}

///////////////////////////////////////////////////////////////////
VisualEffect::ResourceImporter::ResourceImporter(const char *name)
{
}

VisualEffect::ResourceImporter::~ResourceImporter()
{
}

bool VisualEffect::ResourceImporter::onExportFile(const char *srcFilename_, const char *dstFilename_)
{
	// collect Options

	// export
	exportVisualEffect(srcFilename_, dstFilename_);

	return true;
}

bool VisualEffect::ResourceImporter::exportVisualEffect(const char *srcFilename_, const char *dstFilename_)
{
	VisualEffect::Data data;

	data.version		= 1;
	data.platform		= Platform::PC;

	if( !collectEffect(srcFilename_, data) )
		return false;

	if( !writeVisualEffect(dstFilename_, data) )
		return false;

	return true;
}

bool VisualEffect::ResourceImporter::writeVisualEffect(const char *dstFilename, VisualEffect::Data &data)
{
	FileOutputStream os(dstFilename);
	if(!os.opened())
		return false;

	os << data;

	return true;
}

void VisualEffect::ResourceImporter::getChildren(TiXmlNode *node, const char *type, Vector<TiXmlNode *> &children)
{
	children.clear();
	for(TiXmlNode *childNode = node->FirstChild(type); childNode; childNode = childNode->NextSibling(type) )
	{
		children.push() = childNode;
	}
}

void VisualEffect::ResourceImporter::getChildren(TiXmlNode *node, Vector<TiXmlNode *> &children)
{
	children.clear();
	for(TiXmlNode *childNode = node->FirstChild(); childNode; childNode = childNode->NextSibling() )
	{
		children.push() = childNode;
	}
}

bool VisualEffect::ResourceImporter::collectEffect(const char *inputFileName, VisualEffect::Data &data)
{
	TiXmlDocument doc(inputFileName);
	if(doc.LoadFile())
	{
		TiXmlNode *visualEffectNode = doc.FirstChild("VisualEffect");

		TiXmlNode *vertexDescNode = visualEffectNode->FirstChild("VertexDesc");
		if(!vertexDescNode)
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

		if( !collectVertexDesc(data.vertexDesc, vertexDescNode) )
			return false;

		Vector<TiXmlNode *> passNodes;
		getChildren(techniqueNode, "Pass", passNodes);
		data.passes.resize(passNodes.length());

		for(int i=0; i<data.passes.length(); i++)
		{
			if(!collectPass(data.passes[i], passNodes[i]))
				return false;
		}
	}

	return true;
}

bool VisualEffect::ResourceImporter::collectVertexDesc(VertexDesc &vertexDesc, TiXmlNode *vertexDescNode)
{
	Vector<TiXmlNode *> descNodes;
	getChildren(vertexDescNode, "Desc", descNodes);
	
	vertexDesc.vertexFormats.resize(descNodes.length());
	vertexDesc.vertexStreamSources.resize(descNodes.length());
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

		if( !vertexDesc.vertexStreamSources[i].from(vertexStreamSourceName) )
			return false;

		if( !vertexDesc.vertexFormats[i].from(vertexFormatName) )
			return false;
	}

	return true;
}

bool VisualEffect::ResourceImporter::collectPass(Pass &pass, TiXmlNode *passNode)
{
	TiXmlNode *uniformVariablesBlockNode = passNode->FirstChild("UniformVariablesBlock");
	if(!uniformVariablesBlockNode)
		return false;

	TiXmlNode *renderStatesBlockNode = passNode->FirstChild("RenderStatesBlock");
	if(!renderStatesBlockNode)
		return false;

	TiXmlNode *shaderProgramNode = passNode->FirstChild("HLSL");
	if(!shaderProgramNode)
		return false;

	TiXmlElement *passNodeAttributes = passNode->ToElement();
	if(!passNodeAttributes)
		return false;

	const char *passNodeName = passNodeAttributes->Attribute("name");
	if(!passNodeName)
		return false;

	pass.name = passNodeName;
	
	if( !collectGeneralVariablesBlock(pass.generalVariablesBlock, uniformVariablesBlockNode) )
		return false;
	
	if( !collectLightVariables(pass.lightVariables, uniformVariablesBlockNode) )
		return false;
	
	if( !collectTextureVariables(pass.textureVariables, uniformVariablesBlockNode) )
		return false;

	if( !collectRenderStatesBlock(pass.renderStatesBlock, renderStatesBlockNode) )
		return false;

	if( !collectShaderProgram(pass.shaderProgram, shaderProgramNode) )
		return false;
	
	return true;
}

bool VisualEffect::ResourceImporter::collectGeneralVariablesBlock(UniformVariablesBlock &generalVariablesBlock, TiXmlNode *generalVariablesBlockNode)
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

		const char *generalVariableSematics = generalVariablesNodeAttributes->Attribute("sematic");
		if(!generalVariableSematics)
			generalVariableSematics = "";

		if( !generalVariablesBlock.set(generalVariableType, generalVariableName, generalVariableValues, generalVariableSematics) )
			return false;
	}

	return true;
}

bool VisualEffect::ResourceImporter::collectLightVariables(Vector<LightVariable> &lightVariables, TiXmlNode *lightVariablesBlockNode)
{
	Vector<TiXmlNode *> lightVariablesNodes;
	getChildren(lightVariablesBlockNode, "Light", lightVariablesNodes);
	
	lightVariables.resize(lightVariablesNodes.length());
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

		const char *lightVariableSematic = lightVariablesNodeAttributes->Attribute("sematic");
		if(!lightVariableSematic)
			lightVariableSematic = "";

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
			/*
			if( !lightVariables[i].set("float3", dirLightVariableDirectionName.text(), lightVariableDirection, "") )
				return false;

			if( !lightVariables[i].set("float4", dirLightVariableColorName.text(), lightVariableColor, "") )
				return false;
			*/
		}
		else if(String(lightVariableType)=="point")
		{
			const char *lightVariablePosition = lightVariablesNodeAttributes->Attribute("position");
			if(!lightVariablePosition)
				return false;

			const char *lightVariableAtteunation = lightVariablesNodeAttributes->Attribute("atteunation");
			if(!lightVariableAtteunation)
				return false;

			String pointLightVariablePositionName		 = String(lightVariableName) + "Position";
			String pointLightVariableColorName			= String(lightVariableName) + "Color";
			String pointLightVariableAtteunationName	 = String(lightVariableName) + "Atteunation";
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

bool VisualEffect::ResourceImporter::collectTextureVariables(Vector<TextureVariable> &textureVariables, TiXmlNode *textureVariablesBlockNode)
{
	Vector<TiXmlNode *> textureVariablesNodes;
	getChildren(textureVariablesBlockNode, "Sampler2D", textureVariablesNodes);
	
	textureVariables.resize(textureVariablesNodes.length());

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

		const char *textureVariableSematics = textureVariablesNodeAttributes->Attribute("sematic");
		if(!textureVariableSematics)
			textureVariableSematics = "";

		textureVariables[i].set(textureVariableName, 0, 0);
	}

	return true;
}

bool VisualEffect::ResourceImporter::collectRenderStatesBlock(RenderStatesBlock &renderStatesBlock, TiXmlNode *renderStatesBlockNode)
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

		renderStatesBlock.set(renderStateType, renderStateValue);
	}

	return true;
}

bool VisualEffect::ResourceImporter::collectShaderProgram(VisualEffect::ShaderProgram &shaderProgram, TiXmlNode *shaderProgramNode)
{
	TiXmlNode *vsCodeNode = shaderProgramNode->FirstChild("VertexShader");
	TiXmlNode *psCodeNode = shaderProgramNode->FirstChild("PixelShader");

	if(!vsCodeNode)
		return false;

	if(!psCodeNode)
		return false;

	TiXmlNode *vsCodeTextNode = vsCodeNode->FirstChild();
	TiXmlNode *psCodeTextNode = psCodeNode->FirstChild();

	if(!vsCodeTextNode)
		return false;

	if(!psCodeTextNode)
		return false;

	shaderProgram.vertexShaderCode = vsCodeTextNode->Value();
	shaderProgram.pixelShaderCode  = psCodeTextNode->Value();
}

///////////////////////////////////////////////////////////////////
VisualEffect::VisualEffect() 
{
}

VisualEffect::~VisualEffect()
{
}