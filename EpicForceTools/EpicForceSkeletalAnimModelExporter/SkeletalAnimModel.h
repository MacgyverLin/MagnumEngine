///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited			 //
//																 //
// Author : Mac Lin									             //
// Module : EpicForceEngine										 //
// Date   : 19/Aug/2011											 //
//																 //
///////////////////////////////////////////////////////////////////
#ifndef _SkeletalAnimModel_h_
#define _SkeletalAnimModel_h_

#include "Stage.h"
#include "Platform.h"
#include "InputStream.h"
#include "OutputStream.h"
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
#include "AttributesBlock.h"
#include "UniformsBlock.h"

#ifdef EXPORTER
#else
#include "Component.h"
#include "ResourceImport.h"
#include "ResourceAccess.h"
#include "TextureBase.h"
#include "VisualEffect.h"
#endif

using namespace EpicForce;

namespace EpicForce
{

#ifdef EXPORTER
class SkeletalAnimModel
#else
class SkeletalAnimBase;

class SkeletalAnimModel
#endif
{
public:
	class Resource;
	class ResourceImporter;

public:
	class VertexBuffer
	{
	friend class MaxSkeletalAnimModelBuilder;
	friend class SkeletalAnimModelBuilder;
	friend class SkeletalAnimModelRenderer;
	friend class SkeletalAnimModel;
	public:
		VertexBuffer();
		
		virtual ~VertexBuffer();

		void construct(const AttributesBlock &attributesBlock_, 
			           int count_, int stride_);

		const AttributesBlock &getAttributesBlock() const;

		int getStride() const;

		int getNumVertices() const;

		template <class T>
		const T& get(int i) const
		{
			assert(stride==sizeof(T));

			return ((T*)(&buffer[0]))[i];
		}

		template <class T>
		T& get(int i)
		{
			assert(stride==sizeof(T));

			return ((T*)(&buffer[0]))[i];
		}

		void read(InputStream &is);
		void write(OutputStream &os) const;
	private:
		void				*handle;

		AttributesBlock		attributesBlock;
		int					stride;
		int					count;

		Vector<char>		buffer;
	};

	class IndexBuffer
	{
	friend class MaxSkeletalAnimModelBuilder;
	friend class SkeletalAnimModelBuilder;
	friend class SkeletalAnimModelRenderer;
	friend class SkeletalAnimModel;
	public:
		IndexBuffer();
		
		virtual ~IndexBuffer();

		void construct(int count_, int stride_=sizeof(unsigned short));
		
		int getStride() const;

		int getNumIndices() const;

		template <class T>
		const T& get(int i) const
		{
			assert(stride==sizeof(T));

			return ((T*)(&buffer[0]))[i];
		}

		template <class T>
		T& get(int i)
		{
			assert(stride==sizeof(T));

			return ((T*)(&buffer[0]))[i];
		}

		void read(InputStream &is);
		void write(OutputStream &os) const;
	private:
		void			*handle;

		int				stride;
		int				count;
		Vector<char>	buffer;
	};

	class BoneAnimation
	{
	friend class MaxSkeletalAnimModelBuilder;
	friend class SkeletalAnimModelBuilder;
	friend class SkeletalAnimModelRenderer;
	friend class SkeletalAnimModel;
	public:
		BoneAnimation();
		~BoneAnimation();

		int getNumPositionKeys() const;
		int getNumRotationKeys() const;
		int getNumScaleKeys() const;
		void getPosition(const float &t_, Vector3 &p_) const;
		void getRotation(const float &t_, Quaternion &r_) const;
		void getScale(const float &t_, Vector3 &s_) const;

		void getVector10(const float &t_, Vector10 &v_) const;

		void read(InputStream &is);
		void write(OutputStream &os) const;
	private:
		String name;
		int parentIdx;

		Vector<Vector3> positions;
		float posKeyInterval;

		Vector<Quaternion> rotations;
		float rotKeyInterval;

		Vector<Vector3> scales;
		float scaleKeyInterval;
	};

	class Animation
	{
	friend class MaxSkeletalAnimModelBuilder;
	friend class SkeletalAnimModelBuilder;
	friend class SkeletalAnimModelRenderer;
	friend class SkeletalAnimModel;
	public:
		Animation();
		~Animation();

		int getDuration() const;
		int getFPS() const;
		int getNumBoneAnimations() const;
		const SkeletalAnimModel::BoneAnimation &getBoneAnimation(int boneIdx_) const;

		const char *getBoneName(int boneIdx_) const;
		int getBoneIndex(const char *name_) const;
		int getBoneParentIndex(int boneIdx_) const;
		void getVector10(int boneIdx_, float time, Vector10 &v_) const;

		void read(InputStream &is);
		void write(OutputStream &os) const;
	private:
		int							startframe, endframe, fps;
		Vector<BoneAnimation>		boneAnimations;
	};

	class TextureInfo
	{
	friend class MaxSkeletalAnimModelBuilder;
	friend class SkeletalAnimModelBuilder;
	friend class SkeletalAnimModelRenderer;
	friend class SkeletalAnimModel;
	public:
		enum Format
		{
			TEXTURE_INFO_2D			= 0,
			TEXTURE_INFO_CUBE		= 1,
		};
		TextureInfo();
		virtual ~TextureInfo();

		bool construct();

		const String &getFilePath() const;

		void read(InputStream &is);
		void write(OutputStream &os) const;
	private:
		Format		format;
		String		filePath;
	};

	class VisualEffectInfo
	{
	friend class MaxSkeletalAnimModelBuilder;
	friend class SkeletalAnimModelBuilder;
	friend class SkeletalAnimModelRenderer;
	friend class SkeletalAnimModel;
	public:
		VisualEffectInfo();
		virtual ~VisualEffectInfo();

		bool construct();

		const char *getName() const;
		bool isMultiSub() const;
		const char *getFilePath() const;

		int	getNumBonesPerVertex() const;

		const AttributesBlock &getAttributesBlock() const;
		const UniformsBlock &getUniformsBlock() const;

		int getNumTextureInfoIndices() const;
		int getTextureInfoIndex(int i) const;

		void read(InputStream &is);
		void write(OutputStream &os) const;
	private:
		String								name;
		bool								multiSub;
		String								filePath;

		int									numBonesPerVertex;

		AttributesBlock						attributesBlock;
		UniformsBlock						uniformsBlock;

		Vector<int>							textureInfoIndices;
	};

	class Node
	{
	friend class MaxSkeletalAnimModelBuilder;
	friend class SkeletalAnimModelBuilder;
	friend class SkeletalAnimModelRenderer;
	friend class SkeletalAnimModel;
	public:
		Node();
		virtual ~Node();

		const char *			getName() const;
		int						getParentIdx() const;
		const char *			getUserData() const;

		const Vector3			&getPosition() const;
		const Quaternion		&getRotation() const;
		const Vector3			&getScale() const;

		void					getLocalTransform(Matrix4 &m) const;

		void					read(InputStream &is);
		void					write(OutputStream &os) const;
	private:
		String					name;
		int						parentIdx;
		String					userData;

		Vector3					position;
		Quaternion				rotation;
		Vector3					scale;
	};

	class Bone : public Node
	{
	friend class MaxSkeletalAnimModelBuilder;
	friend class SkeletalAnimModelBuilder;
	friend class SkeletalAnimModelRenderer;
	friend class SkeletalAnimModel;
	public:
		Bone();
		virtual ~Bone();

		const Matrix4 &getTBindGlobalTransform();
		const Matrix4 &getTBindGlobalTransformInv();
		const Matrix4 &getT0GlobalTransform();
		const Matrix4 &getT0GlobalTransformInv();

		void read(InputStream &is);
		void write(OutputStream &os) const;
	private:
		Matrix4 tBindGlobalTransform;
		Matrix4 tBindGlobalTransformInv;
		Matrix4 t0GlobalTransform;
		Matrix4 t0GlobalTransformInv;
	};

	class Mesh
	{
	friend class MaxSkeletalAnimModelBuilder;
	friend class SkeletalAnimModelBuilder;
	friend class SkeletalAnimModelRenderer;
	friend class SkeletalAnimModel;
	public:
		class Patch
		{
		friend class MaxSkeletalAnimModelBuilder;
		friend class SkeletalAnimModelBuilder;
		friend class SkeletalAnimModelRenderer;
		friend class SkeletalAnimModel;
		public:
			Patch();
			virtual ~Patch();

			bool construct();

			int getVisualEffectInfoIdx() const;

			bool isSkinned() const;

			const VertexBuffer &getVertexbuffer() const;

			const IndexBuffer &getIndexBuffer() const;

			void read(InputStream &is);
			void write(OutputStream &os) const;
		private:
			int				visualEffectInfoIdx;

			VertexBuffer	vb;
			IndexBuffer		ib;
		};

		Mesh();
		virtual ~Mesh();

		const char *getName() const;
		int getAttachedNodeIdx() const;
		const char *getUserData() const;

		int getNumGlobalBoneIndices() const;
		int getGlobalBoneIndex(int i);

		int getNumPatches() const;
		const Patch &getPatch(int i) const;

		void read(InputStream &is);
		void write(OutputStream &os) const;
	private:
		String					name;
		int						attachedNodeIdx;
		String					userData;

		Vector<int>				globalBoneIndices;
		Vector<Patch>			patches;
	};

	class Data
	{
	friend class MaxSkeletalAnimModelBuilder;
	friend class SkeletalAnimModelBuilder;
	friend class SkeletalAnimModelRenderer;
	friend class SkeletalAnimModel;
	public:
		Data();
		virtual ~Data();

		int getNumTextureInfos() const;
		const SkeletalAnimModel::TextureInfo *getTextureInfo(int i) const;
	
		int getNumVisualEffectInfos() const;
		const SkeletalAnimModel::VisualEffectInfo *getVisualEffectInfo(int i) const;

		int getNumBones() const;
		const SkeletalAnimModel::Bone *getBone(int i) const;
		const Vector<SkeletalAnimModel::Bone> *getBones() const;

		int getNumMeshes() const;
		const SkeletalAnimModel::Mesh *getMesh(int i) const;

		int getDuration() const;
		int getFPS() const;
		int getNumBoneAnimations() const;
		const SkeletalAnimModel::BoneAnimation *getBoneAnimation(int boneIdx_) const;

		const char *getBoneName(int boneIdx_) const;
		int getBoneIndex(const char *name_) const;
		int getBoneParentIndex(int boneIdx_) const;
		void getVector10(int boneIdx_, float time, Vector10 &v_) const;

		void read(InputStream &is);
		void write(OutputStream &os) const;
	private:
		int version;
		Platform platform;

		////////////////////////////////
		// Appearances
		// Bitmap
		Vector<TextureInfo>			textureInfos;
		// Shaders
		Vector<VisualEffectInfo>	visualEffectInfos;

		////////////////////////////////
		// Nodes
		Vector<Bone>				bones;
		Vector<Mesh>				meshes;

		////////////////////////////////
		// Animation
		Animation					animation;
	};

#ifdef EXPORTER
#else
	class Resource : public ResourceAccess
	{
	friend class SkeletalAnimModel::Resource;
	friend class SkeletalAnimModel::ResourceImporter;
	public:
		Resource(const char *path_);
		virtual ~Resource();

		DECLARE_RESOURCE(SkeletalAnimModel::Resource, skelanimmdl)
		
		int getNumTextureInfos() const;
		const SkeletalAnimModel::TextureInfo *getTextureInfo(int i) const;
	
		int getNumVisualEffectInfos() const;
		const SkeletalAnimModel::VisualEffectInfo *getVisualEffectInfo(int i) const;

		int getNumBones() const;
		const SkeletalAnimModel::Bone *getBone(int i) const;
		const Vector<SkeletalAnimModel::Bone> *getBones() const;

		int getNumMeshes() const;
		const SkeletalAnimModel::Mesh *getMesh(int i) const;

		int getDuration() const;
		int getFPS() const;
		int getNumBoneAnimations() const;
		const SkeletalAnimModel::BoneAnimation *getBoneAnimation(int boneIdx_) const;

		const char *getBoneName(int boneIdx_) const;
		int getBoneIndex(const char *name_) const;
		int getBoneParentIndex(int boneIdx_) const;
		void getVector10(int boneIdx_, float time, Vector10 &v_) const;
	protected:
		virtual unsigned char *onCreate(int length);
		virtual void onLoaded();
		virtual void onDestroy();
	private:
		SkeletalAnimModel::Data			data;

		Vector<unsigned char>		buffer;
	};

	#ifdef ENABLE_RESOURCE_IMPORT
	class ResourceImporter : public ResourceImport
	{
	friend class SkeletalAnimModel::Resource;
	friend class SkeletalAnimModel::ResourceImporter;
	public:
		ResourceImporter(const char *name);
		virtual ~ResourceImporter();

		DECLARE_RESOURCE_IMPORT(SkeletalAnimModel::ResourceImporter, skelanimmodel, skelanimmdl)

		static bool initiate();
		static void terminate();
	protected:
		virtual bool onExportFile(const char *srcFilename_, const char *dstFilename_);
		virtual bool onDeleteFile(const char *srcFilename_);
	private:
		bool exportVisualEffect(const char *srcFilename_, const char *dstFilename_);
		bool writeVisualEffect(const char *dstFilename_, SkeletalAnimModel::Data &data_);
	public:
	};
	#endif

public:
	friend class MaxSkeletalModelBuilder;
	friend class SkeletalModelBuilder;
	friend class SkeletalModelRenderer;
	friend class SkeletalAnimModel;

	SkeletalAnimModel();
	virtual ~SkeletalAnimModel();

	bool construct(const char *path_);
	void destruct();

	int getNumTextureInfos() const;
	const SkeletalAnimModel::TextureInfo *getTextureInfo(int i) const;
	
	int getNumVisualEffectInfos() const;
	const SkeletalAnimModel::VisualEffectInfo *getVisualEffectInfo(int i) const;

	int getNumBones() const;
	const SkeletalAnimModel::Bone *getBone(int i) const;
	const Vector<SkeletalAnimModel::Bone> *getBones() const;

	int getNumMeshes() const;
	const SkeletalAnimModel::Mesh *getMesh(int i) const;

	int getDuration() const;
	int getFPS() const;
	int getNumBoneAnimations() const;
	const SkeletalAnimModel::BoneAnimation *getBoneAnimation(int boneIdx_) const;

	const char *getBoneName(int boneIdx_) const;
	int getBoneIndex(const char *name_) const;
	int getBoneParentIndex(int boneIdx_) const;
	void getVector10(int boneIdx_, float time, Vector10 &v_) const;
private:
	SkeletalAnimModel::Resource *resource;
#endif
};

};

#endif