#ifndef _VisualEffect_h_
#define _VisualEffect_h_

#include "Stage.h"
#include "Platform.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "VertexDesc.h"
#include "UniformVariable.h"
#include "RenderStatesBlock.h"

namespace EpicForce
{

class VisualEffect
{
class Resource;
class ResourceImporter;
public:
	class ShaderProgram
	{
	friend class VisualEffect::Resource;
	friend class VisualEffect::ResourceImporter;
	public:
		ShaderProgram();
		virtual ~ShaderProgram();

		ShaderProgram &operator = (const ShaderProgram &other);

		void set(const char *vertexShaderCode_, const char *pixelShaderCode_);

		void read(InputStream &is);
		void write(OutputStream &os) const;
	private:
		String	vertexShaderCode;
		String	pixelShaderCode;

		void	*handle;
	};

	class Pass
	{
	friend class VisualEffect::Resource;
	friend class VisualEffect::ResourceImporter;
	public:
		Pass();
		virtual ~Pass();

		Pass &operator = (const Pass &other);

		const char *getName() const;

		const UniformVariablesBlock	&getGeneralVariablesBlock() const;

		int getNumLightVariables() const;
		const LightVariable &getLightVariable(int i) const;

		int getNumTextureVariables() const;
		const TextureVariable &getTextureVariable(int i) const;

		const RenderStatesBlock &getRenderStatesBlock() const;

		const ShaderProgram &getShaderProgram() const;

		void read(InputStream &is);
		void write(OutputStream &os) const;
	private:
		String						name;

		UniformVariablesBlock		generalVariablesBlock;
		Vector<LightVariable>		lightVariables;
		Vector<TextureVariable>		textureVariables;
		Vector<void	*>				textureHandles;

		RenderStatesBlock			renderStatesBlock;
		ShaderProgram				shaderProgram;		
	};

	class Data
	{
	friend class VisualEffect::Resource;
	friend class VisualEffect::ResourceImporter;
	public:
		Data();
		virtual ~Data();

		Data &operator = (const Data &other);

		int							getVersion() const;
		Platform					getPlatform() const;

		const VertexDesc			&getVertexDesc() const;

		int							getNumPasses() const;
		const Pass					&getPass(int i) const;

		void read(InputStream &is);
		void write(OutputStream &os) const;
	private:
		int							version;
		Platform					platform;

		VertexDesc					vertexDesc;
		Vector<Pass>				passes;
	};

	class ResourceImporter
	{
	public:
		ResourceImporter(const char *path_);
		virtual ~ResourceImporter();

		virtual bool onExportFile(const char *srcFilename_, const char *dstFilename_);
	private:
		bool exportVisualEffect(const char *srcFilename_, const char *dstFilename_);
		bool writeVisualEffect(const char *dstFilename_, VisualEffect::Data &data_);
			void getChildren(TiXmlNode *node, const char *type, Vector<TiXmlNode *> &children);
			void getChildren(TiXmlNode *node, Vector<TiXmlNode *> &children);

			bool collectEffect(const char *inputFileName, VisualEffect::Data &data);
			bool collectVertexDesc(VertexDesc &vertexDesc, TiXmlNode *vertexDescNode);
			bool collectPass(Pass &pass, TiXmlNode *passNode);

			bool collectGeneralVariablesBlock(UniformVariablesBlock &generalVariablesBlock, TiXmlNode *generalVariablesBlockNode);
			bool collectLightVariables(Vector<LightVariable> &lightVariables, TiXmlNode *lightVariablesBlockNode);
			bool collectTextureVariables(Vector<TextureVariable> &textureVariables, TiXmlNode *textureVariablesBlockNode);
			bool collectRenderStatesBlock(VisualEffect::RenderStatesBlock &renderStatesBlock, TiXmlNode *renderStatesBlockNode);
			bool collectShaderProgram(VisualEffect::ShaderProgram &shaderProgram, TiXmlNode *glslNode);
	};

	class Resource
	{
	public:
		Resource(const char *path_);
		virtual ~Resource();
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
	virtual ~VisualEffect();
};

};

#endif
