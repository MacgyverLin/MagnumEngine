///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _VisualEffect_h_
#define _VisualEffect_h_

#include "Stage.h"
#include "Platform.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "GXShaderProgram.h"
#include "GXTexture.h"
#include "Stage.h"
#include "Platform.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Component.h"
#include "ResourceImport.h"
#include "ResourceAccess.h"
#include "GXDef.h"
#include "BVector2.h"
#include "BVector3.h"
#include "BVector4.h"
#include "IVector2.h"
#include "IVector3.h"
#include "IVector4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix2.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "Vector10.h"
#include "ColorRGBA.h"
#include "ResourceImport.h"
#include "ResourceAccess.h"
#include "TextureBase.h"
#include "AttributesBlock.h"
#include "RenderStatesBlock.h"
#include "UniformsBlock.h"
#include "TextureUniformsBlock.h"
#include "ShaderProgramBlock.h"
#ifdef ENABLE_RESOURCE_IMPORT
#include "tinyxml.h"
#endif
#include "Semantic.h"

namespace Magnum
{

/**
* VisualEffect. This is the VisualEffect(Material) for rendering effect
* @see VisualEffect
*/
class VisualEffect
{
public:
	class Resource;
	class ResourceImporter; 

	class Pass
	{
	friend class VisualEffect;
	friend class VisualEffect::Resource;
	friend class VisualEffect::ResourceImporter;
	public:
		Pass();
		virtual ~Pass();

		Pass &operator = (const Pass &other);

		const char *getName() const;
		RenderStatesBlock &getRenderStatesBlock();
		ShaderProgramBlock &getShaderProgramBlock();

		int getNumGlobalUniformIndices() const;
		int getGlobalUniformIndices(int i) const;

		void read(InputStream &is);
		void write(OutputStream &os) const;
	private:
		String						name;
		RenderStatesBlock			renderStatesBlock;
		ShaderProgramBlock			shaderProgramBlock;

		Vector<int>					globalUniformIndices;
		Vector<int>					globalTextureIndices;
	};

	class Data
	{
	friend class VisualEffect;
	friend class VisualEffect::Resource;
	friend class VisualEffect::ResourceImporter;
	public:
		Data();
		~Data();
	
		Data &operator = (const Data &other);

		int								getVersion() const;
		Platform						getPlatform() const;

		int								getOrder() const;
		int								getZsort() const;

		int								getNumAttributes() const;
		const GXShaderAttributeType		&getAttributeType(int i) const;
		const GXVertexStreamSource		&getVertexStreamSource(int i) const;

		int								getNumUniforms() const;
		bool							isUniformSemanticExists(Semantic semantic) const;

		int								getNumTextures() const;
		bool							isTextureSemanticExists(Semantic semantic) const;

		int								getUniformHandle(const char *name) const;
		int								getUniformHandleBySemantic(const char *sematic) const;
		int								getUniformHandleBySemantic(Semantic semantic) const;

		int								getTextureHandle(const char *name) const;
		int								getTextureHandleBySemantic(const char *sematic) const;
		int								getTextureHandleBySemantic(Semantic semantic) const;

		template <class T>
		void							setValue(int handle, const T &values_, int count_ = 1, int offset_ = 0)
		{
			if(handle>=0 && handle<uniformsBlock.getNumUniforms())
				uniformsBlock.getUniform(handle).setValue(values_, count_, offset_);
		}
	 
		template <class T>
		void							getValue(int handle, T &values_, int count_ = 1, int offset_ = 0)
		{
			if(handle>=0 && handle<uniformsBlock.getNumUniforms())
				uniformsBlock.getUniform(handle).getValue(values_, count_, offset_);
		}

		TextureBase						*getTexture(int handle);
		void							setTexture(int handle, TextureBase *texture);

		void							beginPass(int i);
		void							endPass(int i);
		
		void							applyShader(int i);
		void							applyTexture(int i);
		void							applyRenderState(int i);
		void							applyShaderConstant(int i);
		void							restoreShader(int i);
		void							restoreTexture(int i);
		void							restoreRenderState(int i);
		void							restoreShaderConstant(int i);	

		int								getNumPasses() const;
		Pass							&getPass(int i);
										
		void							read(InputStream &is);
		void							write(OutputStream &os) const;
	private:
		bool							buildTextureBlock();
		bool							linkSemanticIndices();
		bool							linkShaderInfo();

		int								version;
		Platform						platform;

		int								order;
		int								zsort;

		AttributesBlock					attributesBlock;

		UniformsBlock					uniformsBlock;
		Vector<int>						uniformIndicesBySemantic;

		TextureUniformsBlock			textureUniformsBlock;
		Vector<int>						textureIndicesBySemantic;

		Vector<Pass>					passes;
	};

	#ifdef ENABLE_RESOURCE_IMPORT
	class ResourceImporter : public ResourceImport
	{
	friend class VisualEffect;
	friend class VisualEffect::Resource;
	friend class VisualEffect::ResourceImporter;
	public:
		ResourceImporter(const char *path_);
		virtual ~ResourceImporter();

		DECLARE_RESOURCE_IMPORT(VisualEffect::ResourceImporter, visualeffect, vfx)

		static bool initiate();
		static void terminate();

		virtual bool onExportFile(const char *srcFilename_, const char *dstFilename_);
		virtual bool onDeleteFile(const char *srcFilename_);
	private:
		bool exportVisualEffect(const char *srcFilename_, const char *dstFilename_);
		bool writeVisualEffect(const char *dstFilename_, VisualEffect::Data &data_);
			void getChildren(TiXmlNode *node, const char *type, Vector<TiXmlNode *> &children);
			void getChildren(TiXmlNode *node, Vector<TiXmlNode *> &children);
			String trim(const String &str);
			void tokenize(Vector<String> &tokens, const String &str, const String &delimiters);
			void parseValues(Vector<String> &values, const String &str);
			bool parseDefaultValues(Vector<String> &values, const String &str);

			bool collectEffect(const char *inputFileName, VisualEffect::Data &data);
				bool collectAttributesBlock(VisualEffect::Data &data, AttributesBlock &attributesBlock, TiXmlNode *attributesNode);
				bool collectUniformsBlock(VisualEffect::Data &data, UniformsBlock &uniformsBlock, TiXmlNode *uniformVariablesBlockNode);
					bool parseUniformVariable(VisualEffect::Data &data, GXUniform &uniform, int uniformIdx, int &textureIdx, 
											  const char *type, const char *name, int arraySize, const char *semantic, const char *initializer,
											  const char *minfilter, const char *magfilter, const char *wraps, const char *wrapt);
					bool parseUniformIndicesBySemantic(VisualEffect::Data &data, int uniformIdx, const char *semantic);
					bool parseTextureUniformIndicesBySemantic(VisualEffect::Data &data, int textureIdx, const char *semantic);
				bool collectPass(VisualEffect::Data &data, UniformsBlock &uniformsBlock, Pass &pass, TiXmlNode *passNode);
					bool collectRenderStatesBlock(VisualEffect::Data &data, UniformsBlock &uniformsBlock, RenderStatesBlock &renderStatesBlock, TiXmlNode *renderStatesBlockNode);
					bool collectShaderProgramBlock(VisualEffect::Data &data, UniformsBlock &uniformsBlock, VisualEffect::ShaderProgramBlock &shaderProgramBlock, TiXmlNode *vertexShaderNode, TiXmlNode *pixelShaderNode);
	};
	#endif

	class Resource : public ResourceAccess
	{
	friend class VisualEffect;
	friend class VisualEffect::Resource;
	friend class VisualEffect::ResourceImporter;
	public:
		Resource(const char *path_);
		virtual ~Resource();

		DECLARE_RESOURCE(VisualEffect::Resource, vfx)
	protected:
		virtual unsigned char *onCreate(int length);
		virtual void onLoaded();
		virtual void onDestroy();
	private:
		VisualEffect::Data			data;

		Vector<unsigned char>		buffer;
	};
public:
	VisualEffect();
	~VisualEffect();

	bool construct(const char *path_);
	void destruct();

	int							getVersion() const;
	Platform					getPlatform() const;

	int							getNumAttributes() const;
	const GXShaderAttributeType &getAttributeType(int i) const;
	const GXVertexStreamSource	&getVertexStreamSource(int i) const;

	int							getNumUniforms() const;
	bool						isUniformSemanticExists(Semantic semantic) const;

	int							getNumTextures() const;
	bool						isTextureSemanticExists(Semantic semantic) const;

	int							getUniformHandle(const char *name) const;
	int							getUniformHandleBySemantic(const char *semantic) const;
	int							getUniformHandleBySemantic(Semantic semantic) const;

	int							getTextureHandle(const char *name) const;
	int							getTextureHandleBySemantic(const char *semantic) const;
	int							getTextureHandleBySemantic(Semantic semantic) const;

	template <class T>
	void						setValue(int handle, const T &values_, int count_= 1, int offset_ = 0)
	{
		if(data)
			data->setValue(handle, values_, count_, offset_);
	}
	
	template <class T>
	void						getValue(int handle, T &values_, int count_ = 1, int offset_ = 0)
	{
		if(data)
			data->getValue(handle, values_, count_, offset_);
	}

	void						setTexture(int handle, TextureBase *texture);

	TextureBase					*getTexture(int handle);
	
	void						beginPass(int i);
	void						endPass(int i);

	void						applyShader(int i);
	void						applyTexture(int i);
	void						applyRenderState(int i);
	void						applyShaderConstant(int i);
	void						restoreShader(int i);
	void						restoreTexture(int i);
	void						restoreRenderState(int i);
	void						restoreShaderConstant(int i);

	int							getNumPasses() const;
	Pass						&getPass(int i);
private:
	VisualEffect::Resource		*resource;
	VisualEffect::Data			*data;
};

};

#endif
