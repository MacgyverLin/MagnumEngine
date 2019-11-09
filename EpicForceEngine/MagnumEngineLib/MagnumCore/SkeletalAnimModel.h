///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
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

using namespace Magnum;

namespace Magnum
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
		/**
		* AudioClip Resource Constructor.
		* To Construct the AudioClip Resource
		* @param path_, the path of the audio resource.
		*/
		Resource(const char *path_);

		/**
		* AudioClip Resource Destructor.
		* To Destructor the AudioClip Resource
		*/
		virtual ~Resource();

		DECLARE_RESOURCE(SkeletalAnimModel::Resource, skelanimmdl)
		
		/**
		* Get the number of Texture Infomations in the Skeletal Anim Model.
		* @return int, the number of Texture Infomations in the Skeletal Anim Model.
		*/
		int getNumTextureInfos() const;

		/**
		* Get the i-th Texture Infomation in the Skeletal Anim Model.
		* @param i, int the index to the Texture Infomation to be returned
		* @return SkeletalAnimModel::TextureInfo *, the i-th Texture Infomation in the Skeletal Anim Model.
		*/
		const SkeletalAnimModel::TextureInfo *getTextureInfo(int i) const;
	
		/**
		* Get the number of VisualEffectInfos in the Skeletal Anim Model.
		* @return int, the number of VisualEffectInfos in the Skeletal Anim Model.
		*/
		int getNumVisualEffectInfos() const;

		/**
		* Get the i-th VisualEffect Infomation in the Skeletal Anim Model.
		* @param i, int the index to the VisualEffect to be returned
		* @return SkeletalAnimModel::VisualEffect *, the i-th VisualEffect Infomation in the Skeletal Anim Model.
		*/
		const SkeletalAnimModel::VisualEffectInfo *getVisualEffectInfo(int i) const;

		/**
		* Get the number of Bones in the Skeletal Anim Model.
		* @return int, the number of Bones in the Skeletal Anim Model.
		*/
		int getNumBones() const;
		/**
		* Get the i-th Bone in the Skeletal Anim Model.
		* @param i, int the index to the bone to be returned
		* @return SkeletalAnimModel::Bone*, the i-th Bone in the Skeletal Anim Model.
		*/
		const SkeletalAnimModel::Bone *getBone(int i) const;

		/**
		* Get all Bone in the Skeletal Anim Model.
		* @return Vector<SkeletalAnimModel::Bone> *, all Bone in the Skeletal Anim Model.
		*/
		const Vector<SkeletalAnimModel::Bone> *getBones() const;

		/**
		* Get the number of Meshes in the Skeletal Anim Model.
		* @return int, the number of Meshes in the Skeletal Anim Model.
		*/
		int getNumMeshes() const;
		/**
		* Get the i-th Mesh in the Skeletal Anim Model.
		* @param i, int the index to the Mesh to be returned
		* @return SkeletalAnimModel::Mesh*, the i-th Mesh in the Skeletal Anim Model.
		*/
		const SkeletalAnimModel::Mesh *getMesh(int i) const;

		/**
		* Get the number frames of Animation.
		* @return int, the number of frames of Animation.
		*/
		int getDuration() const;

		/**
		* Get the Frame Per Seconds of Animation.
		* @return int, the Frame Per Secondsof Animation.
		*/
		int getFPS() const;

		/**
		* Get the Number of Bones of Animation.
		* @return int, the Number of Bones of Animation.
		*/
		int getNumBoneAnimations() const;

		const SkeletalAnimModel::BoneAnimation *getBoneAnimation(int boneIdx_) const;

		/**
		* Get the Name of the i-th Bone in the Skeletal Anim Model.
		* @param i, int, the index to the bone
		* @return const char *, the name of i-th Bone in the Skeletal Anim Model.
		*/
		const char *getBoneName(int boneIdx_) const;

		/**
		* Get the index of the bone by the name of the bone
		* @param name_, const char *, the name of the bone
		* @return int, index of the bone, return -1 if none of the bones's name is name_
		*/
		int getBoneIndex(const char *name_) const;

		/**
		* Get the index of the parent of the i-th bone.
		* @param i_, int, the index to the bone.
		* @return int, the index to the parent of the i-th bone.
		*/
		int getBoneParentIndex(int i_) const;

		/**
		* Get the position, rotation, scale of the i-th bone at time
		* @param i_, int, the index to the bone.
		* @param time_, float, the time of the position, rotation, scale to be sample
		* @return Vector10, the position, rotation, scale of the i-th bone at time
		*/
		void getVector10(int i_, float time_, Vector10 &v_) const;
	protected:
		virtual unsigned char *onCreate(int length);
		virtual void onLoaded();
		virtual void onDestroy();
	private:
		SkeletalAnimModel::Data		data;

		Vector<unsigned char>		buffer;
	};

	#ifdef ENABLE_RESOURCE_IMPORT
	class ResourceImporter : public ResourceImport
	{
	friend class SkeletalAnimModel::Resource;
	friend class SkeletalAnimModel::ResourceImporter;
	public:
		/**
		* SkeletalAnimModel ResourceImporter Constructor.
		* To Construct the SkeletalAnimModel ResourceImporter
		* @param path_, the path of the SkeletalAnimModel resource.
		*/
		ResourceImporter(const char *name);

		/**
		* SkeletalAnimModel ResourceImporter Destructor.
		* To Destructor the SkeletalAnimModel ResourceImporter
		*/
		virtual ~ResourceImporter();

		DECLARE_RESOURCE_IMPORT(SkeletalAnimModel::ResourceImporter, skelanimmodel, skelanimmdl)

		/**
		* To initiate the resource import system.
		*/
		static bool initiate();

		/**
		* To terminate the resource import system.
		*/
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

	/**
	* Get the number of Texture Infomations in the Skeletal Anim Model.
	* @return int, the number of Texture Infomations in the Skeletal Anim Model.
	*/
	int getNumTextureInfos() const;

	/**
	* Get the i-th Texture Infomation in the Skeletal Anim Model.
	* @param i, int the index to the Texture Infomation to be returned
	* @return SkeletalAnimModel::TextureInfo *, the i-th Texture Infomation in the Skeletal Anim Model.
	*/
	const SkeletalAnimModel::TextureInfo *getTextureInfo(int i) const;
	
	/**
	* Get the number of VisualEffectInfos in the Skeletal Anim Model.
	* @return int, the number of VisualEffectInfos in the Skeletal Anim Model.
	*/
	int getNumVisualEffectInfos() const;

	/**
	* Get the i-th VisualEffect Infomation in the Skeletal Anim Model.
	* @param i, int the index to the VisualEffect to be returned
	* @return SkeletalAnimModel::VisualEffect *, the i-th VisualEffect Infomation in the Skeletal Anim Model.
	*/
	const SkeletalAnimModel::VisualEffectInfo *getVisualEffectInfo(int i) const;

	/**
	* Get the number of Bones in the Skeletal Anim Model.
	* @return int, the number of Bones in the Skeletal Anim Model.
	*/
	int getNumBones() const;

	/**
	* Get the i-th Bone in the Skeletal Anim Model.
	* @param i, int the index to the bone to be returned
	* @return SkeletalAnimModel::Bone*, the i-th Bone in the Skeletal Anim Model.
	*/
	const SkeletalAnimModel::Bone *getBone(int i) const;

	/**
	* Get all Bone in the Skeletal Anim Model.
	* @return Vector<SkeletalAnimModel::Bone> *, all Bone in the Skeletal Anim Model.
	*/
	const Vector<SkeletalAnimModel::Bone> *getBones() const;

	/**
	* Get the number of Meshes in the Skeletal Anim Model.
	* @return int, the number of Meshes in the Skeletal Anim Model.
	*/
	int getNumMeshes() const;

	/**
	* Get the i-th Mesh in the Skeletal Anim Model.
	* @param i, int the index to the Mesh to be returned
	* @return SkeletalAnimModel::Mesh*, the i-th Mesh in the Skeletal Anim Model.
	*/
	const SkeletalAnimModel::Mesh *getMesh(int i) const;

	/**
	* Get the number frames of Animation.
	* @return int, the number of frames of Animation.
	*/
	int getDuration() const;

	/**
	* Get the Frame Per Seconds of Animation.
	* @return int, the Frame Per Secondsof Animation.
	*/
	int getFPS() const;

	/**
	* Get the Number of Bones of Animation.
	* @return int, the Number of Bones of Animation.
	*/
	int getNumBoneAnimations() const;
	const SkeletalAnimModel::BoneAnimation *getBoneAnimation(int boneIdx_) const;

	/**
	* Get the Name of the i-th Bone in the Skeletal Anim Model.
	* @param i, int, the index to the bone
	* @return const char *, the name of i-th Bone in the Skeletal Anim Model.
	*/
	const char *getBoneName(int boneIdx_) const;

	/**
	* Get the index of the bone by the name of the bone
	* @param name_, const char *, the name of the bone
	* @return int, index of the bone, return -1 if none of the bones's name is name_
	*/
	int getBoneIndex(const char *name_) const;

	/**
	* Get the index of the parent of the i-th bone.
	* @param i_, int, the index to the bone.
	* @return int, the index to the parent of the i-th bone.
	*/
	int getBoneParentIndex(int boneIdx_) const;

	/**
	* Get the position, rotation, scale of the i-th bone at time
	* @param i_, int, the index to the bone.
	* @param time_, float, the time of the position, rotation, scale to be sample
	* @return Vector10, the position, rotation, scale of the i-th bone at time
	*/
	void getVector10(int boneIdx_, float time, Vector10 &v_) const;
private:
	SkeletalAnimModel::Resource *resource;
#endif
};

};


#endif