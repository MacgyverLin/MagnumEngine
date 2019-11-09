///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "VisualEffect.h"
#include "GXShaderProgram.h"
#ifdef ENABLE_RESOURCE_IMPORT
#include "tinyxml.h"
#include <string>
#endif
#include "Video.h"
#include "GXContext.h"
using namespace Magnum;

static const char *defaultSemantics[] =
{
	"DIFFUSEMAP",
	"OPACITYMAP",
	"SPECULARMAP",
	"NORMALMAP",
	"LIGHTMAP",
	"DISPLACEMENTMAP",
	"REFLECTIONMAP",
	"RENDERCOLORTARGET",
	"RENDERDEPTHSTENCILTARGET",
	"WORLD",
	"WORLDINVERSE",
	"VIEW",
	"VIEWINVERSE",
	"PROJECTION",
	"PROJECTIONINVERSE",
	"WORLDVIEW",
	"WORLDVIEWINVERSE",
	"VIEWPROJ",
	"VIEWPROJINVERSE",
	"WORLDVIEWPROJ",
	"WORLDVIEWPROJINVERSE",
	"VIEWPORTPIXELSIZE",
	"LOCALBBOXMIN",
	"LOCALBBOXMAX",
	"LOCALBBOXSIZE",
	"RECIPLOCALBBOXSIZE",
	"LIGHT0VECTOR",
	"LIGHT0COLOR",
	"LIGHT0ATTENUATION",
	"LIGHT1VECTOR",
	"LIGHT1COLOR",
	"LIGHT1ATTENUATION",
	"LIGHT2VECTOR",
	"LIGHT2COLOR",
	"LIGHT2ATTENUATION",
	"TIME",
	"PERIOD",
	"BONETRANSFORMS",
};

/////////////////////////////////////////////////////////////////////////////////////////////
VisualEffect::Pass::Pass()
{
}

VisualEffect::Pass::~Pass()
{
}

VisualEffect::Pass &VisualEffect::Pass::operator = (const VisualEffect::Pass &other)
{
	this->name					= other.name;
	this->renderStatesBlock		= other.renderStatesBlock;
	this->shaderProgramBlock	= other.shaderProgramBlock;

	this->globalUniformIndices	= other.globalUniformIndices;
	this->globalTextureIndices	= other.globalTextureIndices;

	return *this;
}

const char *VisualEffect::Pass::getName() const
{
	return name.text();
}

RenderStatesBlock &VisualEffect::Pass::getRenderStatesBlock()
{
	return renderStatesBlock;
}

ShaderProgramBlock &VisualEffect::Pass::getShaderProgramBlock()
{
	return shaderProgramBlock;
}

int VisualEffect::Pass::getNumGlobalUniformIndices() const
{
	return globalUniformIndices.length();
}

int VisualEffect::Pass::getGlobalUniformIndices(int i) const
{
	return globalUniformIndices[i];
}

void VisualEffect::Pass::read(InputStream &is)
{
	is >> name;
	is >> renderStatesBlock;
	is >> shaderProgramBlock;

	VectorRead<int> globalUniformIndicesVectorRead(globalUniformIndices);
	is >> globalUniformIndicesVectorRead;

	VectorRead<int> globalTextureIndicesVectorRead(globalTextureIndices);
	is >> globalTextureIndicesVectorRead;
}

void VisualEffect::Pass::write(OutputStream &os) const
{
	os << name;
	os << renderStatesBlock;
	os << shaderProgramBlock;

	VectorWrite<int> globalUniformIndicesVectorWrite(globalUniformIndices);
	os << globalUniformIndicesVectorWrite;

	VectorWrite<int> globalTextureIndicesVectorWrite(globalTextureIndices);
	os << globalTextureIndicesVectorWrite;
}

/////////////////////////////////////////////////////////////////////////////////////////////
VisualEffect::Data::Data()
{
}

VisualEffect::Data::~Data()
{
}
	
VisualEffect::Data &VisualEffect::Data::operator = (const VisualEffect::Data &other)
{
	this->version					= other.version;
	this->platform					= other.platform;

	this->order						= other.order;
	this->zsort						= other.zsort;

	this->attributesBlock			= other.attributesBlock;
	
	this->uniformsBlock				= other.uniformsBlock;
	this->uniformIndicesBySemantic	= other.uniformIndicesBySemantic;

	this->textureUniformsBlock		= other.textureUniformsBlock;
	this->textureIndicesBySemantic	= other.textureIndicesBySemantic;

	this->passes					= other.passes;

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

int	VisualEffect::Data::getOrder() const
{
	return order;
}

int VisualEffect::Data::getZsort() const
{
	return zsort;
}

int VisualEffect::Data::getNumAttributes() const
{
	return attributesBlock.getNumAttributes();
}

const GXShaderAttributeType &VisualEffect::Data::getAttributeType(int i) const
{
	return attributesBlock.getAttributeType(i);
}

const GXVertexStreamSource	&VisualEffect::Data::getVertexStreamSource(int i) const
{
	return attributesBlock.getVertexStreamSource(i);
}

int VisualEffect::Data::getNumUniforms() const
{
	return uniformsBlock.getNumUniforms();
}

bool VisualEffect::Data::isUniformSemanticExists(Semantic semantic) const
{
	return uniformIndicesBySemantic[semantic]!=-1;
}

int VisualEffect::Data::getNumTextures() const
{
	return textureUniformsBlock.getNumTextures();
}

bool VisualEffect::Data::isTextureSemanticExists(Semantic semantic) const
{
	return textureIndicesBySemantic[semantic]!=-1;
}

int VisualEffect::Data::getUniformHandle(const char *name) const
{
	return uniformsBlock.getUniformHandle(name);
}

int	VisualEffect::Data::getUniformHandleBySemantic(const char *semantic) const
{
	return uniformsBlock.getUniformHandleBySemantic(semantic);
}

int VisualEffect::Data::getUniformHandleBySemantic(Semantic semantic) const
{
	return uniformIndicesBySemantic[semantic];
}

int VisualEffect::Data::getTextureHandle(const char *name) const
{
	return textureUniformsBlock.getTextureHandle(name);
}

int VisualEffect::Data::getTextureHandleBySemantic(const char *semantic) const
{
	return textureUniformsBlock.getTextureHandleBySemantic(semantic);
}

int VisualEffect::Data::getTextureHandleBySemantic(Semantic semantic) const
{
	return textureIndicesBySemantic[semantic];
}

void VisualEffect::Data::setTexture(int handle, TextureBase *texture_)
{
	textureUniformsBlock.setTexture(handle, texture_);
}

TextureBase	*VisualEffect::Data::getTexture(int handle)
{
	return textureUniformsBlock.getTexture(handle);
}

void VisualEffect::Data::beginPass(int i)
{
	applyShader(i);
	applyTexture(i);
	applyRenderState(i);
	applyShaderConstant(i);
}

void VisualEffect::Data::endPass(int i)
{
	restoreShaderConstant(i);	
	restoreRenderState(i);
	restoreTexture(i);
	restoreShader(i);
}

void VisualEffect::Data::applyShader(int i)
{
	Pass &pass = passes[i];

	//////////////////////////////////////////////////////////
	// SS
	GXShaderProgram &shaderProgram = *((GXShaderProgram *)pass.shaderProgramBlock.handle);
	Video::Manager::getContext().setShaderProgram(&shaderProgram);
}

void VisualEffect::Data::applyTexture(int i)
{
	Pass &pass = passes[i];

	//////////////////////////////////////////////////////////
	// TS
	GXShaderProgram &shaderProgram = *((GXShaderProgram *)pass.shaderProgramBlock.handle);
	
	int textureIdx = 0;
	for(int i=0; i<shaderProgram.getUniformCount(); i++)
	{
		const GXShaderUniformType &type = shaderProgram.getUniformType(i);
		// const char *name = shaderProgram.getUniformName(i);

		if(type==GXShaderUniformType::SAMPLER2D || type==GXShaderUniformType::SAMPLERCUBE)
		{
			int globalTextureIndex = pass.globalTextureIndices[textureIdx];
			TextureBase *textureBase = textureUniformsBlock.getTexture(globalTextureIndex);

			GXTexture *texture = (GXTexture *)textureBase->getHandle();
			texture->setFilter(textureUniformsBlock.getMagFilters(globalTextureIndex),
							   textureUniformsBlock.getMinFilters(globalTextureIndex) );
			texture->setWrap(textureUniformsBlock.getWrapS(globalTextureIndex),
							 textureUniformsBlock.getWrapT(globalTextureIndex));

			Video::Manager::getContext().setTexture(textureIdx, (GXTexture *)textureBase->getHandle() );

			textureIdx++;
		}
	}
}

void VisualEffect::Data::applyRenderState(int i)
{
	Pass &pass = passes[i];

	//////////////////////////////////////////////////////////
	// RS
	RenderStatesBlock &rsBlock = pass.renderStatesBlock;

	GXEnableMode mode = 0;
	if(pass.renderStatesBlock.cullEnable)
		mode = mode | GXEnableMode::CullFace;
	if(pass.renderStatesBlock.blendEnable)
		mode = mode | GXEnableMode::Blend;
	if(pass.renderStatesBlock.stencilTestEnable)
		mode = mode | GXEnableMode::StencilTest;
	if(pass.renderStatesBlock.depthTestEnable)
		mode = mode | GXEnableMode::DepthTest;

	Video::Manager::getContext().enable(mode);

	Video::Manager::getContext().setBlendStateRgb  (rsBlock.blendModeRgb  , rsBlock.blendSrcFactorRgb  , rsBlock.blendDstFactorRgb  );
	Video::Manager::getContext().setBlendStateAlpha(rsBlock.blendModeAlpha, rsBlock.blendSrcFactorAlpha, rsBlock.blendDstFactorAlpha);
	Video::Manager::getContext().setColorMask(rsBlock.colorMask);
	Video::Manager::getContext().setCullState(rsBlock.cullMode);
	Video::Manager::getContext().setDepthTestState(rsBlock.depthTestMode, rsBlock.depthWriteEnable);
	Video::Manager::getContext().setLineWidth(rsBlock.lineWidth);
	Video::Manager::getContext().setPolygonOffsetState(rsBlock.polygonOffsetFactor, rsBlock.polygonOffsetUnit);
	// Video::Manager::getContext().setScissor(rsBlock.scissor);
	Video::Manager::getContext().setStencilTestStateFront(rsBlock.stencilTestModeFront, rsBlock.stencilTestRefFront, 
													      rsBlock.stencilTestMaskFront, rsBlock.stencilTestWriteMaskFront);
	Video::Manager::getContext().setStencilOpStateFront(rsBlock.stencilOpFailFront, 
														rsBlock.stencilOpZFailFront, 
														rsBlock.stencilOpZPassFront);
	Video::Manager::getContext().setStencilTestStateBack(rsBlock.stencilTestModeBack, rsBlock.stencilTestRefBack, 
													     rsBlock.stencilTestMaskBack, rsBlock.stencilTestWriteMaskBack);
	Video::Manager::getContext().setStencilOpStateBack(rsBlock.stencilOpFailBack, 
													   rsBlock.stencilOpZFailBack, 
													   rsBlock.stencilOpZPassBack);
	// Video::Manager::getContext().setViewport(rsBlock.viewport);
}

void VisualEffect::Data::applyShaderConstant(int i)
{
	Pass &pass = passes[i];
	GXShaderProgram &shaderProgram = *((GXShaderProgram *)pass.shaderProgramBlock.handle);

	//////////////////////////////////////////////////////////
	// Constant
	int textureIdx = 0;

	for(int i=0; i<shaderProgram.getUniformCount(); i++)
	{
		const GXShaderUniformType &type = shaderProgram.getUniformType(i);
		// const char *name = shaderProgram.getUniformName(i);

		if( type==GXShaderUniformType::SAMPLER2D || type==GXShaderUniformType::SAMPLERCUBE )
		{
			shaderProgram.setUniformValue(i, textureIdx);
			textureIdx++;
		}
		else
		{
			int globalUniformIndex = pass.globalUniformIndices[i];
			GXUniform &uniform = uniformsBlock.getUniform(globalUniformIndex);

			shaderProgram.copyUniformValue(i, uniform);
		}
	}
}

void VisualEffect::Data::restoreShader(int i)
{
	//////////////////////////////////////////////////////////
	// SS
	Video::Manager::getContext().setShaderProgram(0);
}

void VisualEffect::Data::restoreTexture(int i)
{
	//////////////////////////////////////////////////////////
	// TS
	for(int i=0; i<GXContext::NUM_TEXTURES; i++)
	{
		Video::Manager::getContext().setTexture(i, 0);
	}
}

void VisualEffect::Data::restoreRenderState(int i)
{
	//////////////////////////////////////////////////////////
	// RS
	Video::Manager::getContext().disable(GXEnableMode::All);
	Video::Manager::getContext().enable(GXEnableMode::Dither);

	Video::Manager::getContext().setBlendStateRgb(GXBlendMode::Add, GXBlendFactor::One, GXBlendFactor::Zero);
	Video::Manager::getContext().setBlendStateAlpha(GXBlendMode::Add, GXBlendFactor::SrcAlpha, GXBlendFactor::OneMinusSrcAlpha);
	Video::Manager::getContext().setColorMask(GXColorMask::Rgba);
	Video::Manager::getContext().setCullState(GXCullMode::CW);
	Video::Manager::getContext().setDepthTestState(GXDepthTestMode::LEqual, true);
	Video::Manager::getContext().setLineWidth(1.0);
	Video::Manager::getContext().setPolygonOffsetState(1.0, 1.0);
	// Video::Manager::getContext().setScissor(rsBlock.scissor);
	Video::Manager::getContext().setStencilTestStateFront(GXStencilTestMode::Always, 0, 0xffffffff, 0xffffffff);
	Video::Manager::getContext().setStencilOpStateFront(GXStencilOp::Keep, GXStencilOp::Keep, GXStencilOp::Keep);
	Video::Manager::getContext().setStencilTestStateBack(GXStencilTestMode::Always, 0, 0xffffffff, 0xffffffff);
	Video::Manager::getContext().setStencilOpStateBack(GXStencilOp::Keep, GXStencilOp::Keep, GXStencilOp::Keep);
	// Video::Manager::getContext().setViewport(rsBlock.viewport);
}

void VisualEffect::Data::restoreShaderConstant(int i)
{
	//////////////////////////////////////////////////////////
	// Constant
}

int	VisualEffect::Data::getNumPasses() const
{
	return passes.length();
}

VisualEffect::Pass &VisualEffect::Data::getPass(int i)
{
	return passes[i];
}
									
void VisualEffect::Data::read(InputStream &is)
{
	is >> version;
	is >> platform;

	is >> order;
	is >> zsort;

	is >> attributesBlock;

	is >> uniformsBlock;
	VectorRead<int> uniformSemanticIndicesRead(uniformIndicesBySemantic);
	is >> uniformSemanticIndicesRead;

	is >> textureUniformsBlock;
	VectorRead<int> textureIndicesBySemanticRead(textureIndicesBySemantic);
	is >> textureIndicesBySemanticRead;

	VectorRead<Pass> passesVectorRead(passes);
	is >> passesVectorRead;
}

void VisualEffect::Data::write(OutputStream &os) const
{
	os << version;
	os << platform;

	os << order;
	os << zsort;

	os << attributesBlock;

	os << uniformsBlock;
	VectorWrite<int> uniformSemanticIndicesWrite(uniformIndicesBySemantic);
	os << uniformSemanticIndicesWrite;

	os << textureUniformsBlock;
	VectorWrite<int> textureIndicesBySemanticWrite(textureIndicesBySemantic);
	os << textureIndicesBySemanticWrite;

	VectorWrite<Pass> passesVectorWrite(passes);
	os << passesVectorWrite;
}

bool VisualEffect::Data::buildTextureBlock()
{
	return true;

	int idx = 0;
	for(int i=0; i<uniformsBlock.getNumUniforms(); i++)
	{
		const GXShaderUniformType &type = uniformsBlock.getUniform(i).getType();
		const char *name				= uniformsBlock.getUniform(i).getName();
		const char *semantic			= uniformsBlock.getUniform(i).getSemantic();

		if(type==GXShaderUniformType::SAMPLER2D || type==GXShaderUniformType::SAMPLERCUBE)
		{
			const char *name = uniformsBlock.getUniform(i).getName();

			textureUniformsBlock.names.push()		= name;
			textureUniformsBlock.semantics.push()	= semantic;
			textureUniformsBlock.textures.push()	= 0;

			//debug("%s %d %x", textureUniformsBlock.names.back().text(), idx++, textureUniformsBlock.textures.back());
		}
	}

	return true;
}

bool VisualEffect::Data::linkSemanticIndices()
{
	return true;
	
	uniformIndicesBySemantic.resize(NUM_SEMANTICS);
	for(int i=0; i<NUM_SEMANTICS; i++)
	{
		uniformIndicesBySemantic[i] = -1;
		for(int j=0; j<uniformsBlock.uniforms.length(); j++)
		{
			const char *name			= uniformsBlock.uniforms[j].getName();
			const char *uniformSemantic = uniformsBlock.uniforms[j].getSemantic();

			if( strcasecmp(defaultSemantics[i], uniformSemantic)==0 )
			{
				uniformIndicesBySemantic[i] = j;
			}
		}
	}

	textureIndicesBySemantic.resize(NUM_SEMANTICS);
	for(int i=0; i<NUM_SEMANTICS; i++)
	{
		textureIndicesBySemantic[i] = -1;
		for(int j=0; j<textureUniformsBlock.getNumTextures(); j++)
		{
			const char *name			= textureUniformsBlock.names[j];
			const char *textureSemantic = textureUniformsBlock.semantics[j];

			if( strcasecmp(defaultSemantics[i], textureSemantic)==0 )
			{
				textureIndicesBySemantic[i] = j;
				break;
			}			
		}
	}

	return true;
}

bool VisualEffect::Data::linkShaderInfo()
{
	for(int i=0; i<passes.length(); i++)
	{
		VisualEffect::Pass &pass = passes[i];

		GXShaderProgram *shaderProgram = (GXShaderProgram *)pass.shaderProgramBlock.handle;
		assert(shaderProgram);

		// build global Uniform Indices
		for(int j=0; j<shaderProgram->getUniformCount(); j++)
		{
			const char *name	 = shaderProgram->getUniformName(j);
			const char *semantic = shaderProgram->getUniformSemantic(j);
			const GXShaderUniformType &type = shaderProgram->getUniformType(j);

			int handle = uniformsBlock.getUniformHandle(name);
			assert(handle>=0);

			pass.globalUniformIndices.push() = handle;
		}
	}

	for(int i=0; i<passes.length(); i++)
	{
		VisualEffect::Pass &pass = passes[i];

		GXShaderProgram *shaderProgram = (GXShaderProgram *)pass.shaderProgramBlock.handle;
		assert(shaderProgram);

		// build global Texture Indices
		for(int j=0; j<shaderProgram->getUniformCount(); j++)
		{
			const char *name	 = shaderProgram->getUniformName(j);
			const char *semantic = shaderProgram->getUniformSemantic(j);
			const GXShaderUniformType &type = shaderProgram->getUniformType(j);

			if(type==GXShaderUniformType::SAMPLER2D || type==GXShaderUniformType::SAMPLERCUBE)
			{
				for(int k=0; k<textureUniformsBlock.names.length(); k++)
				{
					if(textureUniformsBlock.names[k]==name)
					{
						pass.globalTextureIndices.push() = k;
					}
				}
			}
		}
	}

	return true;
}


///////////////////////////////////////////////////////////////////////////////////
#ifdef ENABLE_RESOURCE_IMPORT
VisualEffect::ResourceImporter::ResourceImporter(const char *path_)
: ResourceImport(path_)
{
}

VisualEffect::ResourceImporter::~ResourceImporter()
{
}

bool VisualEffect::ResourceImporter::initiate()
{
	return true;
}

void VisualEffect::ResourceImporter::terminate()
{
}

bool VisualEffect::ResourceImporter::onExportFile(const char *srcFilename_, const char *dstFilename_)
{
	// collect Options

	// export
	return exportVisualEffect(srcFilename_, dstFilename_);

	//onDeleteFile(dstFilename_);
}

bool VisualEffect::ResourceImporter::onDeleteFile(const char *srcFilename_)
{
	return this->defaultDeleteFileFunc(srcFilename_);
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

bool VisualEffect::ResourceImporter::writeVisualEffect(const char *dstFilename_, VisualEffect::Data &data)
{
#ifdef GZ_RESOURCE
	GZFileOutputStream os(dstFilename_);
#else
	FileOutputStream os(dstFilename_);
#endif
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

String VisualEffect::ResourceImporter::trim(const String &str)
{
	std::string s = str.text();

	int start = s.find_first_not_of(" ");
	int end   = s.find_last_not_of(" ");

	return String(s.substr(start, end-start+1).c_str());
}

void VisualEffect::ResourceImporter::tokenize(Vector<String> &tokens, const String &str, const String &delimiters)
{
	std::string s = str.text();

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

void VisualEffect::ResourceImporter::parseValues(Vector<String> &values, const String &str)
{
	values.clear();

	tokenize(values, str.text(), ",;");
}

bool VisualEffect::ResourceImporter::parseDefaultValues(Vector<String> &values, const String &str)
{
	std::string s = str.text();

	int start = s.find_first_of("({");
	start += 1;

	int end   = s.find_last_of(")}");

	parseValues(values, s.substr(start, end-start).c_str() );

	return values.length()!=0;
}

bool VisualEffect::ResourceImporter::collectEffect(const char *inputFileName, VisualEffect::Data &data)
{
	TiXmlDocument doc(inputFileName);
	if(doc.LoadFile())
	{
		TiXmlNode *visualEffectNode = doc.FirstChild("VisualEffect");

		TiXmlElement *visualEffectNodeAttributes = visualEffectNode->ToElement();
		if(!visualEffectNodeAttributes)
			return false;

		const char *orderStr = visualEffectNodeAttributes->Attribute("order");
		if(!orderStr)
			orderStr = "1";

		const char *zsortStr = visualEffectNodeAttributes->Attribute("zsort");
		if(!zsortStr)
			zsortStr = "false";

		data.order			= atoi(orderStr);
		if( strcasecmp(zsortStr, "true")==0 )
			data.zsort			= true;
		else
			data.zsort			= false;

		TiXmlNode *attributesNode = visualEffectNode->FirstChild("Attributes");
		if(!attributesNode)
			return false;

		TiXmlNode *uniformsNode = visualEffectNode->FirstChild("Uniforms");
		if(!uniformsNode)
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
		
		if( !collectAttributesBlock(data, data.attributesBlock, attributesNode) )
			return false;

		if( !collectUniformsBlock(data, data.uniformsBlock, uniformsNode) )
			return false;

		Vector<TiXmlNode *> passNodes;
		getChildren(techniqueNode, "Pass", passNodes);
		data.passes.resize(passNodes.length());
		for(int i=0; i<data.passes.length(); i++)
		{
			if(!collectPass(data, data.uniformsBlock, data.passes[i], passNodes[i]))
				return false;
		}

		if( !data.buildTextureBlock() )
			return false;

		if( !data.linkSemanticIndices() )
			return false;
	}

	return true;
}

bool VisualEffect::ResourceImporter::collectAttributesBlock(VisualEffect::Data &data, AttributesBlock &attributesBlock, TiXmlNode *attributesNode)
{
	Vector<TiXmlNode *> attributeNodes;
	getChildren(attributesNode, attributeNodes);
	
	attributesBlock.attributeTypes.resize(attributeNodes.length());
	attributesBlock.vertexFormats.resize(attributeNodes.length());
	attributesBlock.attributeNames.resize(attributeNodes.length());
	attributesBlock.vertexStreamSources.resize(attributeNodes.length());
	for(int i=0; i<attributeNodes.length(); i++)
	{
		TiXmlElement *descNodeAttributes = attributeNodes[i]->ToElement();
		if(!descNodeAttributes)
			return false;

		const char *type = descNodeAttributes->Attribute("type");
		if(!type)
			return false;

		const char *format = descNodeAttributes->Attribute("format");
		if(!format)
			return false;

		const char *name = descNodeAttributes->Attribute("name");
		if(!name)
			return false;

		const char *semantic = descNodeAttributes->Attribute("semantic");
		if(!semantic)
			return false;

		if( !attributesBlock.attributeTypes[i].set(type) )
			return false;

		if( !attributesBlock.vertexFormats[i].set(format) )
			return false;

		attributesBlock.attributeNames[i] = name;

		if( !attributesBlock.vertexStreamSources[i].set(semantic) )
			return false;
	}

	return true;
}

bool VisualEffect::ResourceImporter::collectUniformsBlock(VisualEffect::Data &data, UniformsBlock &uniformsBlock, TiXmlNode *uniformsBlockNode)
{
	///////////////////////////////////////////////////////////////////////////////////////////////////
	data.uniformIndicesBySemantic.resize(NUM_SEMANTICS);
	data.textureIndicesBySemantic.resize(NUM_SEMANTICS);

	int textureIdx = 0;
	for(int i=0; i<NUM_SEMANTICS; i++)
	{
		data.uniformIndicesBySemantic[i] = -1;
		data.textureIndicesBySemantic[i] = -1;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////
	Vector<TiXmlNode *> uniformsNodes;
	getChildren(uniformsBlockNode, uniformsNodes);

	uniformsBlock.uniforms.resize(uniformsNodes.length());
	for(int i=0; i<uniformsNodes.length(); i++)
	{
		TiXmlElement *uniformsNodeAttributes = uniformsNodes[i]->ToElement();
		if(!uniformsNodeAttributes)
			return false;

		const char *precision		= uniformsNodeAttributes->Attribute("precision");
		if(!precision)
			return false;

		const char *format			= uniformsNodeAttributes->Attribute("format");
		if(!format)
			return false;

		const char *name			= uniformsNodeAttributes->Attribute("name");
		if(!name)
			return false;

		const char *arraysize		= uniformsNodeAttributes->Attribute("arraysize");
		if(!arraysize)
			arraysize = "1";

		const char *semantic		= uniformsNodeAttributes->Attribute("semantic");
		if(!semantic)
			semantic = "";

		const char *initializer		= uniformsNodeAttributes->Attribute("initializer");
		if(!initializer)
			initializer = "";

		const char *minfilter		= uniformsNodeAttributes->Attribute("minfilter");
		if(!minfilter)
			minfilter = "linear";

		const char *magfilter		= uniformsNodeAttributes->Attribute("magfilter");
		if(!magfilter)
			magfilter = "linear";

		const char *wraps			= uniformsNodeAttributes->Attribute("wraps");
		if(!wraps)
			wraps = "repeat";

		const char *wrapt			= uniformsNodeAttributes->Attribute("wrapt");
		if(!wrapt)
			wrapt = "repeat";

		if( !parseUniformVariable(data, uniformsBlock.uniforms[i], i, textureIdx, 
			                      format, name, atoi(arraysize), semantic, initializer,
			                      minfilter, magfilter, wraps, wrapt) )
			return false;
	}

	return true;
}

bool VisualEffect::ResourceImporter::parseUniformVariable(VisualEffect::Data &data, GXUniform &uniform, int uniformIdx, int &textureIdx, 
														  const char *type, const char *name, int arraySize, const char *semantic, const char *initializer, 
	                                                      const char *minfilter, const char *magfilter, const char *wraps, const char *wrapt)
{
	Vector<String> tokens;
	String typeStr = type;

	if(typeStr=="bool")
	{
		Vector<bool> values;
		values.resize(arraySize);

		if( parseDefaultValues(tokens, initializer) )
		{
			if(tokens.length()!=arraySize*1)
			{
				return false;
			}

			int idx = 0;
			for(int i=0; i<values.length(); i++)
			{
				values[i] = tokens[idx++]=="true" ? true : false;
			}
		}
		else
		{
			for(int i=0; i<values.length(); i++)
			{
				values[i] = true;
			}
		}

		uniform.construct(-1, GXShaderUniformType::BOOL, name, arraySize, semantic);
		uniform.setValue(values[0], values.length());

		if( !parseUniformIndicesBySemantic(data, uniformIdx, semantic) )
			return false;
		
		return true;
	}
	else if(typeStr=="bvec2")
	{
		Vector<BVector2> values;
		values.resize(arraySize);

		if( parseDefaultValues(tokens, initializer) )
		{
			if(tokens.length()!=arraySize*2)
			{
				return false;
			}

			int idx = 0;
			for(int i=0; i<values.length(); i++)
			{
				values[i][0] = tokens[idx++]=="true" ? true : false;
				values[i][1] = tokens[idx++]=="true" ? true : false;
			}
		}
		else
		{
			for(int i=0; i<values.length(); i++)
			{
				values[i][0] = true;
				values[i][1] = true;
			}
		}

		uniform.construct(-1, GXShaderUniformType::BVEC2, name, arraySize, semantic);
		uniform.setValue(values[0], values.length());

		if( !parseUniformIndicesBySemantic(data, uniformIdx, semantic) )
			return false;

		return true;
	}
	else if(typeStr=="bvec3")
	{
		Vector<BVector3> values;
		values.resize(arraySize);

		if( parseDefaultValues(tokens, initializer) )
		{
			if(tokens.length()!=arraySize*3)
			{
				return false;
			}

			int idx = 0;
			for(int i=0; i<values.length(); i++)
			{
				values[i][0] = tokens[idx++]=="true" ? true : false;
				values[i][1] = tokens[idx++]=="true" ? true : false;
				values[i][2] = tokens[idx++]=="true" ? true : false;
			}
		}
		else
		{
			for(int i=0; i<values.length(); i++)
			{
				values[i][0] = true;
				values[i][1] = true;
				values[i][2] = true;
			}
		}

		uniform.construct(-1, GXShaderUniformType::BVEC3, name, arraySize, semantic);
		uniform.setValue(values[0], values.length());

		if( !parseUniformIndicesBySemantic(data, uniformIdx, semantic) )
			return false;

		return true;
	}
	else if(typeStr=="bvec4")
	{
		Vector<BVector4> values;
		values.resize(arraySize);

		if( parseDefaultValues(tokens, initializer) )
		{
			if(tokens.length()!=arraySize*4)
			{
				return false;
			}

			int idx = 0;
			for(int i=0; i<values.length(); i++)
			{
				values[i][0] = tokens[idx++]=="true" ? true : false;
				values[i][1] = tokens[idx++]=="true" ? true : false;
				values[i][2] = tokens[idx++]=="true" ? true : false;
				values[i][3] = tokens[idx++]=="true" ? true : false;
			}
		}
		else
		{
			for(int i=0; i<values.length(); i++)
			{
				values[i][0] = true;
				values[i][1] = true;
				values[i][2] = true;
				values[i][3] = true;
			}
		}

		uniform.construct(-1, GXShaderUniformType::BVEC4, name, arraySize, semantic);
		uniform.setValue(values[0], values.length());

		if( !parseUniformIndicesBySemantic(data, uniformIdx, semantic) )
			return false;

		return true;
	}
	else if(typeStr=="int")
	{
		Vector<int> values;
		values.resize(arraySize);

		if( parseDefaultValues(tokens, initializer) )
		{
			if(tokens.length()!=arraySize*1)
			{
				return false;
			}

			int idx = 0;
			for(int i=0; i<values.length(); i++)
			{
				values[i] = atoi(tokens[idx++]);
			}
		}
		else
		{
			for(int i=0; i<values.length(); i++)
			{
				values[i] = 0;
			}
		}

		uniform.construct(-1, GXShaderUniformType::INT, name, arraySize, semantic);
		uniform.setValue(values[0], values.length());

		if( !parseUniformIndicesBySemantic(data, uniformIdx, semantic) )
			return false;

		return true;
	}
	else if(typeStr=="ivec2")
	{
		Vector<IVector2> values;
		values.resize(arraySize);

		if( parseDefaultValues(tokens, initializer) )
		{
			if(tokens.length()!=arraySize*2)
			{
				return false;
			}

			int idx = 0;
			for(int i=0; i<values.length(); i++)
			{
				values[i][0] = atoi(tokens[idx++]);
				values[i][1] = atoi(tokens[idx++]);
			}
		}
		else
		{
			for(int i=0; i<values.length(); i++)
			{
				values[i][0] = 0;
				values[i][1] = 0;
			}
		}

		uniform.construct(-1, GXShaderUniformType::IVEC2, name, arraySize, semantic);
		uniform.setValue(values[0], values.length());

		if( !parseUniformIndicesBySemantic(data, uniformIdx, semantic) )
			return false;

		return true;
	}
	else if(typeStr=="ivec3")
	{
		Vector<IVector3> values;
		values.resize(arraySize);

		if( parseDefaultValues(tokens, initializer) )
		{
			if(tokens.length()!=arraySize*3)
			{
				return false;
			}

			int idx = 0;
			for(int i=0; i<values.length(); i++)
			{
				values[i][0] = atoi(tokens[idx++]);
				values[i][1] = atoi(tokens[idx++]);
				values[i][2] = atoi(tokens[idx++]);
			}
		}
		else
		{
			for(int i=0; i<values.length(); i++)
			{
				values[i][0] = 0;
				values[i][1] = 0;
				values[i][2] = 0;
			}
		}

		uniform.construct(-1, GXShaderUniformType::IVEC3, name, arraySize, semantic);
		uniform.setValue(values[0], values.length());

		if( !parseUniformIndicesBySemantic(data, uniformIdx, semantic) )
			return false;

		return true;
	}
	else if(typeStr=="ivec4")
	{
		Vector<IVector4> values;
		values.resize(arraySize);

		if( parseDefaultValues(tokens, initializer) )
		{
			if(tokens.length()!=arraySize*4)
			{
				return false;
			}

			int idx = 0;
			for(int i=0; i<values.length(); i++)
			{
				values[i][0] = atoi(tokens[idx++]);
				values[i][1] = atoi(tokens[idx++]);
				values[i][2] = atoi(tokens[idx++]);
				values[i][3] = atoi(tokens[idx++]);
			}
		}
		else
		{
			for(int i=0; i<values.length(); i++)
			{
				values[i][0] = 0;
				values[i][1] = 0;
				values[i][2] = 0;
				values[i][3] = 0;
			}
		}

		uniform.construct(-1, GXShaderUniformType::IVEC4, name, arraySize, semantic);
		uniform.setValue(values[0], values.length());

		if( !parseUniformIndicesBySemantic(data, uniformIdx, semantic) )
			return false;

		return true;
	}
	else if(typeStr=="float")
	{
		Vector<float> values;
		values.resize(arraySize);

		if( parseDefaultValues(tokens, initializer) )
		{
			if(tokens.length()!=arraySize*1)
			{
				return false;
			}

			int idx = 0;
			for(int i=0; i<values.length(); i++)
			{
				values[i] = atof(tokens[idx++]);
			}
		}
		else
		{
			for(int i=0; i<values.length(); i++)
			{
				values[i] = 0.0f;
			}
		}

		uniform.construct(-1, GXShaderUniformType::FLOAT, name, arraySize, semantic);
		uniform.setValue(values[0], values.length());

		if( !parseUniformIndicesBySemantic(data, uniformIdx, semantic) )
			return false;

		return true;
	}
	else if(typeStr=="vec2")
	{
		Vector<Vector2> values;
		values.resize(arraySize);

		if( parseDefaultValues(tokens, initializer) )
		{
			if(tokens.length()!=arraySize*2)
			{
				return false;
			}

			int idx = 0;
			for(int i=0; i<values.length(); i++)
			{
				values[i][0] = atof(tokens[idx++]);
				values[i][1] = atof(tokens[idx++]);
			}
		}
		else
		{
			for(int i=0; i<values.length(); i++)
			{
				values[i][0] = 0.0f;
				values[i][1] = 0.0f;
			}
		}

		uniform.construct(-1, GXShaderUniformType::VEC2, name, arraySize, semantic);
		uniform.setValue(values[0], values.length());

		if( !parseUniformIndicesBySemantic(data, uniformIdx, semantic) )
			return false;

		return true;
	}
	else if(typeStr=="vec3")
	{
		Vector<Vector3> values;
		values.resize(arraySize);

		if( parseDefaultValues(tokens, initializer) )
		{
			if(tokens.length()!=arraySize*3)
			{
				return false;
			}

			int idx = 0;
			for(int i=0; i<values.length(); i++)
			{
				values[i][0] = atof(tokens[idx++]);
				values[i][1] = atof(tokens[idx++]);
				values[i][2] = atof(tokens[idx++]);
			}
		}
		else
		{
			for(int i=0; i<values.length(); i++)
			{
				values[i][0] = 0.0f;
				values[i][1] = 0.0f;
				values[i][2] = 0.0f;
			}
		}

		uniform.construct(-1, GXShaderUniformType::VEC3, name, arraySize, semantic);
		uniform.setValue(values[0], values.length());

		if( !parseUniformIndicesBySemantic(data, uniformIdx, semantic) )
			return false;

		return true;
	}
	else if(typeStr=="vec4")
	{
		Vector<Vector4> values;
		values.resize(arraySize);

		if( parseDefaultValues(tokens, initializer) )
		{
			if(tokens.length()!=arraySize*4)
			{
				return false;
			}

			int idx = 0;
			for(int i=0; i<values.length(); i++)
			{
				values[i][0] = atof(tokens[idx++]);
				values[i][1] = atof(tokens[idx++]);
				values[i][2] = atof(tokens[idx++]);
				values[i][3] = atof(tokens[idx++]);
			}
		}
		else
		{
			for(int i=0; i<values.length(); i++)
			{
				values[i][0] = 0.0f;
				values[i][1] = 0.0f;
				values[i][2] = 0.0f;
				values[i][3] = 0.0f;
			}
		}

		uniform.construct(-1, GXShaderUniformType::VEC4, name, arraySize, semantic);
		uniform.setValue(values[0], values.length());

		if( !parseUniformIndicesBySemantic(data, uniformIdx, semantic) )
			return false;

		return true;
	}
	else if(typeStr=="mat2")
	{
		Vector<Matrix2> values;
		values.resize(arraySize);

		if( parseDefaultValues(tokens, initializer) )
		{
			if(tokens.length()!=arraySize*(2*2))
			{
				return false;
			}

			int idx = 0;
			for(int i=0; i<values.length(); i++)
			{
				values[i][0][0] = atof(tokens[idx++]);	values[i][0][1] = atof(tokens[idx++]);
				values[i][1][0] = atof(tokens[idx++]);	values[i][1][1] = atof(tokens[idx++]);
			}
		}
		else
		{
			for(int i=0; i<values.length(); i++)
			{
				values[i] = Matrix2::ZERO;
			}
		}

		uniform.construct(-1, GXShaderUniformType::MAT2, name, arraySize, semantic);
		uniform.setValue(values[0], values.length());

		if( !parseUniformIndicesBySemantic(data, uniformIdx, semantic) )
			return false;

		return true;
	}
	else if(typeStr=="mat3")
	{
		Vector<Matrix3> values;
		values.resize(arraySize);

		if( parseDefaultValues(tokens, initializer) )
		{
			if(tokens.length()!=arraySize*(3*3))
			{
				return false;
			}

			int idx = 0;
			for(int i=0; i<values.length(); i++)
			{
				values[i][0][0] = atof(tokens[idx++]);	values[i][0][1] = atof(tokens[idx++]); values[i][0][2] = atof(tokens[idx++]);
				values[i][1][0] = atof(tokens[idx++]);	values[i][1][1] = atof(tokens[idx++]); values[i][1][2] = atof(tokens[idx++]);
				values[i][2][0] = atof(tokens[idx++]);	values[i][2][1] = atof(tokens[idx++]); values[i][2][2] = atof(tokens[idx++]);
			}
		}
		else
		{
			for(int i=0; i<values.length(); i++)
			{
				values[i] = Matrix3::ZERO;
			}
		}

		uniform.construct(-1, GXShaderUniformType::MAT3, name, arraySize, semantic);
		uniform.setValue(values[0], values.length());

		if( !parseUniformIndicesBySemantic(data, uniformIdx, semantic) )
			return false;

		return true;
	}
	else if(typeStr=="mat4")
	{
		Vector<Matrix4> values;
		values.resize(arraySize);

		if( parseDefaultValues(tokens, initializer) )
		{
			if(tokens.length()!=arraySize*(4*4))
			{
				return false;
			}

			int idx = 0;
			for(int i=0; i<values.length(); i++)
			{
				values[i][0][0] = atof(tokens[idx++]);	values[i][0][1] = atof(tokens[idx++]); values[i][0][2] = atof(tokens[idx++]); values[i][0][3] = atof(tokens[idx++]);
				values[i][1][0] = atof(tokens[idx++]);	values[i][1][1] = atof(tokens[idx++]); values[i][1][2] = atof(tokens[idx++]); values[i][1][3] = atof(tokens[idx++]);
				values[i][2][0] = atof(tokens[idx++]);	values[i][2][1] = atof(tokens[idx++]); values[i][2][2] = atof(tokens[idx++]); values[i][2][3] = atof(tokens[idx++]);
				values[i][3][0] = atof(tokens[idx++]);	values[i][3][1] = atof(tokens[idx++]); values[i][3][2] = atof(tokens[idx++]); values[i][3][3] = atof(tokens[idx++]);
			}
		}
		else
		{
			for(int i=0; i<values.length(); i++)
			{
				values[i] = Matrix4::ZERO;
			}
		} 

		uniform.construct(-1, GXShaderUniformType::MAT4, name, arraySize, semantic);
		uniform.setValue(values[0], values.length());

		if( !parseUniformIndicesBySemantic(data, uniformIdx, semantic) )
			return false;

		return true;
	}
	else if(typeStr=="sampler2d")
	{
		Vector<int> values;
		values.resize(arraySize);

		if( parseDefaultValues(tokens, initializer) )
		{
			if(tokens.length()!=arraySize*1)
			{
				return false;
			}

			int idx = 0;
			for(int i=0; i<values.length(); i++)
			{
				values[i] = atoi(tokens[idx++]);
			}
		}
		else
		{
			for(int i=0; i<values.length(); i++)
			{
				values[i] = 0;
			}
		}

		uniform.construct(-1, GXShaderUniformType::SAMPLER2D, name, arraySize, semantic);
		uniform.setValue(values[0], values.length());

		if( !parseTextureUniformIndicesBySemantic(data, textureIdx, semantic) )
			return false;

		data.textureUniformsBlock.names.push()						= name;
		data.textureUniformsBlock.semantics.push()					= semantic;
		data.textureUniformsBlock.textures.push()					= 0;
		data.textureUniformsBlock.minFilters.push().set(String(minfilter).toLower().text());
		data.textureUniformsBlock.magFilters.push().set(String(magfilter).toLower().text());
		data.textureUniformsBlock.wrapSs.push().set(String(wraps).toLower().text());
		data.textureUniformsBlock.wrapTs.push().set(String(wrapt).toLower().text());

		textureIdx++;

		return true;
	}
	else if(typeStr=="samplercube")
	{
		Vector<int> values;
		values.resize(arraySize);

		if( parseDefaultValues(tokens, initializer) )
		{
			if(tokens.length()!=arraySize*1)
			{
				return false;
			}

			int idx = 0;
			for(int i=0; i<values.length(); i++)
			{
				values[i] = atoi(tokens[idx++]);
			}
		}
		else
		{
			for(int i=0; i<values.length(); i++)
			{
				values[i] = 0;
			}
		}

		uniform.construct(-1, GXShaderUniformType::SAMPLERCUBE, name, arraySize, semantic);
		uniform.setValue(values[0], values.length());

		if( !parseTextureUniformIndicesBySemantic(data, textureIdx, semantic) )
			return false;

		data.textureUniformsBlock.names.push()						= name;
		data.textureUniformsBlock.semantics.push()					= semantic;
		data.textureUniformsBlock.textures.push()					= 0;
		data.textureUniformsBlock.minFilters.push().set(String(minfilter).toLower().text());
		data.textureUniformsBlock.magFilters.push().set(String(magfilter).toLower().text());
		data.textureUniformsBlock.wrapSs.push().set(String(wraps).toLower().text());
		data.textureUniformsBlock.wrapTs.push().set(String(wrapt).toLower().text());

		textureIdx++;

		return true;
	}
	else
	{
		return false;
	}

	return true;
}

bool VisualEffect::ResourceImporter::parseUniformIndicesBySemantic(VisualEffect::Data &data, int uniformIdx, const char *semantic)
{
	for(int i=0; i<NUM_SEMANTICS; i++)
	{
		if( strcasecmp(defaultSemantics[i], semantic)==0 )
		{
			data.uniformIndicesBySemantic[i] = uniformIdx;
		}
	}

	return true;
}

bool VisualEffect::ResourceImporter::parseTextureUniformIndicesBySemantic(VisualEffect::Data &data, int textureIdx, const char *semantic)
{
	for(int i=0; i<NUM_SEMANTICS; i++)
	{
		if( strcasecmp(defaultSemantics[i], semantic)==0 )
		{
			data.textureIndicesBySemantic[i] = textureIdx;
		}
	}

	return true;
}

bool VisualEffect::ResourceImporter::collectPass(VisualEffect::Data &data, UniformsBlock &uniformsBlock, Pass &pass, TiXmlNode *passNode)
{
	TiXmlNode *renderStatesBlockNode = passNode->FirstChild("RenderStates");
	if(!renderStatesBlockNode)
		return false;

	TiXmlElement *passNodeAttributes = passNode->ToElement();
	if(!passNodeAttributes)
		return false;

	const char *passNodeName = passNodeAttributes->Attribute("name");
	if(!passNodeName)
		return false;

	TiXmlNode *vertexShaderNode = passNode->FirstChild("VertexShader");
	if(!vertexShaderNode)
		return false;

	TiXmlNode *pixelShaderNode = passNode->FirstChild("PixelShader");
	if(!pixelShaderNode)
		return false;

	pass.name = passNodeName;
	
	if( !collectRenderStatesBlock(data, uniformsBlock, pass.renderStatesBlock, renderStatesBlockNode) )
		return false;

	if( !collectShaderProgramBlock(data, uniformsBlock, pass.shaderProgramBlock, vertexShaderNode, pixelShaderNode) )
		return false;
	
	return true;
}

bool VisualEffect::ResourceImporter::collectRenderStatesBlock(VisualEffect::Data &data, UniformsBlock &uniformsBlock, RenderStatesBlock &renderStatesBlock, TiXmlNode *renderStatesBlockNode)
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

		if( !renderStatesBlock.construct(renderStateType, renderStateValue) )
			return false;
	}

	return true;
}

bool VisualEffect::ResourceImporter::collectShaderProgramBlock(VisualEffect::Data &data, UniformsBlock &uniformsBlock, ShaderProgramBlock &shaderProgramBlock, TiXmlNode *vertexShaderNode, TiXmlNode *pixelShaderNode)
{
	TiXmlNode *vertexShaderTextNode = vertexShaderNode->FirstChild();
	if(!vertexShaderTextNode)
		return false;

	TiXmlNode *pixelShaderTextNode = pixelShaderNode->FirstChild();
	if(!pixelShaderTextNode)
		return false;

	const char *vertexShaderCode = vertexShaderTextNode->Value();
	if(!vertexShaderCode)
		return false;

	const char *pixelShaderCode = pixelShaderTextNode->Value();
	if(!pixelShaderCode)
		return false;

	shaderProgramBlock.vertexShaderCode = vertexShaderCode;

	shaderProgramBlock.pixelShaderCode  = pixelShaderCode;

	return true;
}
#endif

///////////////////////////////////////////////////////////////////////////////////
VisualEffect::Resource::Resource(const char *path_)
: ResourceAccess(path_)
{
}	

VisualEffect::Resource::~Resource()
{
	onDestroy();
}

unsigned char *VisualEffect::Resource::onCreate(int length_)
{
	buffer.resize(length_);

	return &buffer[0];
}

void VisualEffect::Resource::onLoaded()
{
	MemInputStream is(&buffer[0], buffer.length());

	is >> data;

	for(int i=0; i<data.passes.length(); i++)
	{
		Pass &pass = data.passes[i];

		String str = name();

		GXShaderProgram *shaderProgram = new GXShaderProgram
		(
			pass.shaderProgramBlock.vertexShaderCode.text(), pass.shaderProgramBlock.vertexShaderCode.length(),
			pass.shaderProgramBlock.pixelShaderCode.text() , pass.shaderProgramBlock.pixelShaderCode.length(),
			data.attributesBlock.attributeNames
		);
		assert(shaderProgram);

		data.passes[i].shaderProgramBlock.handle = (int)shaderProgram;
	}

	data.linkShaderInfo();

	buffer.destroy();
}

void VisualEffect::Resource::onDestroy()
{
	for(int i=0; i<data.passes.length(); i++)
	{
		Pass &pass = data.passes[i];

		GXShaderProgram *shaderProgram = (GXShaderProgram *)data.passes[i].shaderProgramBlock.handle;
		if(shaderProgram)
		{
			delete shaderProgram;
		}
	}

	buffer.destroy();
}

///////////////////////////////////////////////////////////////////////////////////
VisualEffect::VisualEffect() 
: resource(0)
, data(0)
{
}

VisualEffect::~VisualEffect()
{
	destruct();
}
		
bool VisualEffect::construct(const char *path_)
{
	assert(resource==0);
	assert(data==0);

	resource = VisualEffect::Resource::get(path_);
	if(!resource)
		return false;
	resource->addReference();

	data = new VisualEffect::Data();
	*data = resource->data;

	return true;
}

void VisualEffect::destruct()
{
	if(data)
	{
		delete data;
		data = 0;
	}
	if(resource)
	{
		resource->release();
		resource = 0;
	}
}

int	VisualEffect::getVersion() const
{
	if(data)
		return data->getVersion();
	else
		return 0;
}

Platform VisualEffect::getPlatform() const
{
	if(data)
		return data->getPlatform();
	else
		return 0;
}

int VisualEffect::getNumAttributes() const
{
	if(data)
		return data->getNumAttributes();
	else
		return 0;
}

const GXShaderAttributeType &VisualEffect::getAttributeType(int i) const
{
	if(data)
		return data->getAttributeType(i);
	else
		return GXShaderAttributeType::VEC3;
}

const GXVertexStreamSource	&VisualEffect::getVertexStreamSource(int i) const
{
	if(data)
		return data->getVertexStreamSource(i);
	else
		return GXVertexStreamSource::POSITION0;
}

int VisualEffect::getNumUniforms() const
{
	if(data)
		return data->getNumUniforms();
	else
		return 0;
}

bool VisualEffect::isUniformSemanticExists(Semantic semantic) const
{
	if(data)
		return data->isUniformSemanticExists(semantic);
	else
		return false;
}

int	VisualEffect::getNumTextures() const
{
	if(data)
		return data->getNumTextures();
	else
		return 0;
}

bool VisualEffect::isTextureSemanticExists(Semantic semantic) const
{
	if(data)
		return data->isTextureSemanticExists(semantic);
	else
		return -1;
}

int VisualEffect::getUniformHandle(const char *name) const
{
	if(data)
		return data->getUniformHandle(name);
	else
		return -1;
}

int VisualEffect::getUniformHandleBySemantic(const char *semantic) const
{
	if(data)
		return data->getUniformHandleBySemantic(semantic);
	else
		return -1;
}

int VisualEffect::getUniformHandleBySemantic(Semantic semantic) const
{
	if(data)
		return data->getUniformHandleBySemantic(semantic);
	else
		return -1;
}

int	VisualEffect::getTextureHandle(const char *name) const
{
	if(data)
		return data->getTextureHandle(name);
	else
		return -1;
}

int	VisualEffect::getTextureHandleBySemantic(const char *semantic) const
{
	if(data)
		return data->getTextureHandleBySemantic(semantic);
	else
		return -1;
}

int VisualEffect::getTextureHandleBySemantic(Semantic semantic) const
{
	if(data)
		return data->getTextureHandleBySemantic(semantic);
	else
		return -1;
}

void VisualEffect::setTexture(int handle, TextureBase *texture)
{
	if(data)
		data->setTexture(handle, texture);
}

TextureBase	*VisualEffect::getTexture(int handle)
{
	if(data)
		return data->getTexture(handle);
	else
		return 0;
}

void VisualEffect::beginPass(int i)
{
	if(data)
		data->beginPass(i);
}

void VisualEffect::endPass(int i)
{
	if(data)
		data->endPass(i);
}

void VisualEffect::applyShader(int i)
{
	if(data)
		data->applyShader(i);
}

void VisualEffect::applyTexture(int i)
{
	if(data)
		data->applyTexture(i);
}

void VisualEffect::applyRenderState(int i)
{
	if(data)
		data->applyRenderState(i);
}

void VisualEffect::applyShaderConstant(int i)
{
	if(data)
		data->applyShaderConstant(i);
}

void VisualEffect::restoreShader(int i)
{
	if(data)
		data->restoreShader(i);
}

void VisualEffect::restoreTexture(int i)
{
	if(data)
		data->restoreTexture(i);
}

void VisualEffect::restoreRenderState(int i)
{
	if(data)
		data->restoreRenderState(i);
}

void VisualEffect::restoreShaderConstant(int i)
{
	if(data)
		data->restoreShaderConstant(i);
}

int VisualEffect::getNumPasses() const
{
	if(data)
		return data->getNumPasses();
	else
		return 0;
}