///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "SkeletalAnimModel.h"
#ifdef EXPORTER
#else
#include "VisualEffect.h"
#include "Texture2DFile.h"
#include "GXVertexBuffer.h"
#include "GXIndexBuffer.h"
#include "SkeletalAnimModelRenderer.h"
#include "SkeletalAnimBase.h"
#endif
using namespace Magnum;

//////////////////////////////////////////////////////////////////
SkeletalAnimModel::VertexBuffer::VertexBuffer()
: handle(0)
, stride(0)
, count(0)
{
}

SkeletalAnimModel::VertexBuffer::~VertexBuffer()
{
#ifdef EXPORTER
#else
	if(handle)
	{
		GXVertexBuffer *vertexBuffer = (GXVertexBuffer *)handle;
		delete vertexBuffer;

		handle = 0;
	}
#endif
}

void SkeletalAnimModel::VertexBuffer::construct(const AttributesBlock &attributesBlock_, int count_, int stride_)
{
	attributesBlock		= attributesBlock_;
	stride				= stride_;
	count				= count_;

	buffer.resize(stride * count);
}

const AttributesBlock &SkeletalAnimModel::VertexBuffer::getAttributesBlock() const
{
	return attributesBlock;
}

int SkeletalAnimModel::VertexBuffer::getStride() const
{
	return stride;
}

int SkeletalAnimModel::VertexBuffer::getNumVertices() const
{
	return count;
}

void SkeletalAnimModel::VertexBuffer::read(InputStream &is)
{
	is >> attributesBlock;

	is >> stride;
	is >> count; 

	int numBytes;
	is >> numBytes;
	if(numBytes)
	{
		buffer.resize(numBytes);
		is.readX(&buffer[0], buffer.length());
	}
#ifdef EXPORTER
#else
	GXVertexBuffer *vertexBuffer = new GXVertexBuffer(count, attributesBlock.vertexFormats);
	vertexBuffer->setVertices(&buffer[0], 0, buffer.length());
	handle = (void *)vertexBuffer;
	buffer.destroy();
#endif
}

void SkeletalAnimModel::VertexBuffer::write(OutputStream &os) const
{
	os << attributesBlock;

	os << stride;
	os << count;

	int numBytes = buffer.length();
	os << numBytes;
	if(numBytes)
		os.writeX(&buffer[0], buffer.length());
}

//////////////////////////////////////////////////////////////////
SkeletalAnimModel::IndexBuffer::IndexBuffer()
: handle(0)
, stride(0)
, count(0)
{
}

SkeletalAnimModel::IndexBuffer::~IndexBuffer()
{
#ifdef EXPORTER
#else
	if(handle)
	{
		GXIndexBuffer *indexBuffer = (GXIndexBuffer *)handle;
		delete indexBuffer;

		handle = 0;
	}
#endif
}

void SkeletalAnimModel::IndexBuffer::construct(int count_, int stride_)
{
	stride = stride_;
	count  = count_; 

	buffer.resize(stride * count);
}

int SkeletalAnimModel::IndexBuffer::getStride() const
{
	return stride;
}

int SkeletalAnimModel::IndexBuffer::getNumIndices() const
{
	return count;
}

void SkeletalAnimModel::IndexBuffer::read(InputStream &is)
{
	is >> stride;
	is >> count;

	int numBytes;
	is >> numBytes;
	if(numBytes)
	{
		buffer.resize(numBytes);
		is.readX(&buffer[0], buffer.length());
	}
#ifdef EXPORTER
#else
	GXIndexBuffer *indexBuffer = new GXIndexBuffer(count);
	indexBuffer->setIndices(&buffer[0], 0, buffer.length());
	handle = (void *)indexBuffer;
	buffer.destroy();
#endif
}

void SkeletalAnimModel::IndexBuffer::write(OutputStream &os) const
{
	os << stride;
	os << count;

	int numBytes = buffer.length();
	os << numBytes;
	if(numBytes)
	{
		os.writeX(&buffer[0], buffer.length());
	}
}

//////////////////////////////////////////////////////////////////
SkeletalAnimModel::BoneAnimation::BoneAnimation()
{
}

SkeletalAnimModel::BoneAnimation::~BoneAnimation()
{
}

int SkeletalAnimModel::BoneAnimation::getNumPositionKeys() const
{
	return positions.length();
}

int SkeletalAnimModel::BoneAnimation::getNumRotationKeys() const
{
	return rotations.length();
}

int SkeletalAnimModel::BoneAnimation::getNumScaleKeys() const
{
	return scales.length();
}

void SkeletalAnimModel::BoneAnimation::getPosition(const float &t_, Vector3 &p_) const
{
	int idx = t_ / posKeyInterval;
	if(idx<0)
	{
		p_ = positions[0];
	}
	else if(idx>=positions.length()-1)
	{
		p_ = positions[positions.length()-1];
	}
	else
	{
		float u = t_ / posKeyInterval - idx;
		p_ = positions[idx]*(1-u) + positions[idx+1]*u;
	}
}

void SkeletalAnimModel::BoneAnimation::getRotation(const float &t_, Quaternion &r_) const
{
	int idx = t_ / rotKeyInterval;
	if(idx<0)
	{
		idx = 0;
		r_[0] = rotations[idx  ][0];
		r_[1] = rotations[idx  ][1];
		r_[2] = rotations[idx  ][2];
		r_[3] = rotations[idx  ][3];
	}
	else if(idx>=rotations.length()-1)
	{
		idx = rotations.length()-1;
		r_[0] = rotations[idx  ][0];
		r_[1] = rotations[idx  ][1];
		r_[2] = rotations[idx  ][2];
		r_[3] = rotations[idx  ][3];
	}
	else
	{
		Quaternion q0;
		q0[0] =	rotations[idx  ][0];
		q0[1] =	rotations[idx  ][1];
		q0[2] =	rotations[idx  ][2];
		q0[3] =	rotations[idx  ][3];

		Quaternion q1;
		q1[0] =	rotations[idx+1][0];
		q1[1] =	rotations[idx+1][1];
		q1[2] =	rotations[idx+1][2];
		q1[3] =	rotations[idx+1][3];

		float u = t_ / rotKeyInterval - idx;
		r_ = q0*(1-u) + q1*u;
		r_.Normalize();
	}
	/*
	int idx = t_ / (*rotKeyInterval);
	if(idx<0)
	{
		idx = 0;
		r_ = Mayhem::Quaternion(rotations[idx  ][0].v/4096.0f, 
								rotations[idx  ][1].v/4096.0f,
								rotations[idx  ][2].v/4096.0f,
								rotations[idx  ][3].v/4096.0f);
	}
	else if(idx>=(*numRotKeys)-1)
	{
		idx = (*numRotKeys)-1;
		r_ = Mayhem::Quaternion(rotations[idx  ][0].v/4096.0f, 
								rotations[idx  ][1].v/4096.0f,
								rotations[idx  ][2].v/4096.0f,
								rotations[idx  ][3].v/4096.0f);
	}
	else
	{
		Mayhem::Quaternion q0(	rotations[idx  ][0].v/4096.0f, 
								rotations[idx  ][1].v/4096.0f,
								rotations[idx  ][2].v/4096.0f,
								rotations[idx  ][3].v/4096.0f);
		Mayhem::Quaternion q1(	rotations[idx+1][0].v/4096.0f, 
								rotations[idx+1][1].v/4096.0f,
								rotations[idx+1][2].v/4096.0f,
								rotations[idx+1][3].v/4096.0f);

		float u = t_ / (*rotKeyInterval) - idx;
		r_ = q0*(1-u) + q1*u;
		r_.Normalize();
	}
	*/
}

void SkeletalAnimModel::BoneAnimation::getScale(const float &t_, Vector3 &s_) const
{
	int idx = t_ / scaleKeyInterval;
	if(idx<0)
	{
		s_ = scales[0];
	}
	else if(idx>= scales.length()-1)
	{
		s_ = scales[scales.length()-1];
	}
	else
	{
		float u = t_ / scaleKeyInterval - idx;
		s_ = scales[idx]*(1-u) + scales[idx+1]*u;
	}
}

void SkeletalAnimModel::BoneAnimation::getVector10(const float &t_, Vector10 &v_) const
{
	getPosition(t_, v_.t);
	getRotation(t_, v_.q);
	getScale(t_, v_.k);
}

void SkeletalAnimModel::BoneAnimation::read(InputStream &is)
{
	is >> name;
	is >> parentIdx;

	VectorRead<Vector3> positionsVertorRead(positions);
	is >> positionsVertorRead;
	is >> posKeyInterval;

	VectorRead<Quaternion> rotationsVertorRead(rotations);
	is >> rotationsVertorRead;
	is >> rotKeyInterval;

	VectorRead<Vector3> scalesVertorRead(scales);
	is >> scalesVertorRead;
	is >> scaleKeyInterval;
}

void SkeletalAnimModel::BoneAnimation::write(OutputStream &os) const
{
	os << name;
	os << parentIdx;

	VectorWrite<Vector3> positionsVertorWrite(positions);
	os << positionsVertorWrite;
	os << posKeyInterval;

	VectorWrite<Quaternion> rotationsVertorWrite(rotations);
	os << rotationsVertorWrite;
	os << rotKeyInterval;

	VectorWrite<Vector3> scalesVertorWrite(scales);
	os << scalesVertorWrite;
	os << scaleKeyInterval;
}

//////////////////////////////////////////////////////////////////
SkeletalAnimModel::Animation::Animation()
{
}

SkeletalAnimModel::Animation::~Animation()
{
}

int SkeletalAnimModel::Animation::getDuration() const
{
	return endframe - startframe + 1;
}

int SkeletalAnimModel::Animation::getFPS() const
{
	return fps;
}

int SkeletalAnimModel::Animation::getNumBoneAnimations() const
{
	return boneAnimations.length();
}

const SkeletalAnimModel::BoneAnimation &SkeletalAnimModel::Animation::getBoneAnimation(int boneIdx_) const
{
	return boneAnimations[boneIdx_];
}

const char *SkeletalAnimModel::Animation::getBoneName(int boneIdx_) const
{
	return boneAnimations[boneIdx_].name.text();
}

int SkeletalAnimModel::Animation::getBoneIndex(const char *name_) const
{
	for(int i=0; i<boneAnimations.length(); i++)
	{
		if(boneAnimations[i].name==name_)
		{
			return i;
		}
	}

	return -1;
}

int SkeletalAnimModel::Animation::getBoneParentIndex(int boneIdx_) const
{
	return boneAnimations[boneIdx_].parentIdx;
}

void SkeletalAnimModel::Animation::getVector10(int boneIdx_, float time, Vector10 &v_) const
{
	boneAnimations[boneIdx_].getVector10(time, v_);
}

void SkeletalAnimModel::Animation::read(InputStream &is)
{
	is >> startframe >> endframe >> fps;

	VectorRead<BoneAnimation> boneAnimationsVertorRead(boneAnimations);
	is >> boneAnimationsVertorRead;
}

void SkeletalAnimModel::Animation::write(OutputStream &os) const
{
	os << startframe << endframe << fps;

	VectorWrite<BoneAnimation> boneAnimationsVertorWrite(boneAnimations);
	os << boneAnimationsVertorWrite;
}

//////////////////////////////////////////////////////////////////
SkeletalAnimModel::TextureInfo::TextureInfo()
{
}

SkeletalAnimModel::TextureInfo::~TextureInfo()
{
}

const String &SkeletalAnimModel::TextureInfo::getFilePath() const
{
	return filePath;
}

void SkeletalAnimModel::TextureInfo::read(InputStream &is)
{
	int temp;
	is >> temp; 
	format = (SkeletalAnimModel::TextureInfo::Format)temp;

	is >> filePath;
}

void SkeletalAnimModel::TextureInfo::write(OutputStream &os) const
{
	int temp;
	temp = (int)format;

	os << temp;
	os << filePath;
}

///////////////////////////////////////////////////////////////////////////////////////
SkeletalAnimModel::Mesh::Patch::Patch()
: visualEffectInfoIdx(-1)
{
}

SkeletalAnimModel::Mesh::Patch::~Patch()
{
}

int SkeletalAnimModel::Mesh::Patch::getVisualEffectInfoIdx() const
{
	return visualEffectInfoIdx;
}

const SkeletalAnimModel::VertexBuffer &SkeletalAnimModel::Mesh::Patch::getVertexbuffer() const
{
	return vb;
}

const SkeletalAnimModel::IndexBuffer &SkeletalAnimModel::Mesh::Patch::getIndexBuffer() const
{
	return ib;
}

void SkeletalAnimModel::Mesh::Patch::read(InputStream &is)
{
	is >> visualEffectInfoIdx;

	is >> vb;
	is >> ib;
}

void SkeletalAnimModel::Mesh::Patch::write(OutputStream &os) const
{
	os << visualEffectInfoIdx; 

	os << vb;
	os << ib;
}

//////////////////////////////////////////////////////////////////
SkeletalAnimModel::VisualEffectInfo::VisualEffectInfo()
{
}

SkeletalAnimModel::VisualEffectInfo::~VisualEffectInfo()
{
}

const char *SkeletalAnimModel::VisualEffectInfo::getName() const
{
	return name.text();
}

bool SkeletalAnimModel::VisualEffectInfo::isMultiSub() const
{
	return multiSub;
}

const char *SkeletalAnimModel::VisualEffectInfo::getFilePath() const
{
	return filePath.text();
}

int	SkeletalAnimModel::VisualEffectInfo::getNumBonesPerVertex() const
{
	return numBonesPerVertex;
}

const AttributesBlock &SkeletalAnimModel::VisualEffectInfo::getAttributesBlock() const
{
	return attributesBlock;
}

const UniformsBlock &SkeletalAnimModel::VisualEffectInfo::getUniformsBlock() const
{
	return uniformsBlock;
}

int SkeletalAnimModel::VisualEffectInfo::getNumTextureInfoIndices() const
{
	return textureInfoIndices.length();
}

int SkeletalAnimModel::VisualEffectInfo::getTextureInfoIndex(int i) const
{
	return textureInfoIndices[i];
}

void SkeletalAnimModel::VisualEffectInfo::read(InputStream &is)
{
	is >> name;
	is >> multiSub;
	is >> filePath;

	is >> numBonesPerVertex;
	is >> attributesBlock;
	is >> uniformsBlock;
	
	VectorRead<int> textureIndicesVertorRead(textureInfoIndices);
	is >> textureIndicesVertorRead;
}

void SkeletalAnimModel::VisualEffectInfo::write(OutputStream &os) const
{
	os << name;
	os << multiSub;
	os << filePath;

	os << numBonesPerVertex;
	os << attributesBlock;
	os << uniformsBlock;
	
	VectorWrite<int> textureIndicesVertorWrite(textureInfoIndices);
	os << textureIndicesVertorWrite;
}

//////////////////////////////////////////////////
SkeletalAnimModel::Node::Node()
: parentIdx(-1)
{
}

SkeletalAnimModel::Node::~Node()
{
}

const char *SkeletalAnimModel::Node::getName() const
{
	return name.text();
}

int	SkeletalAnimModel::Node::getParentIdx() const
{
	return parentIdx;
}

const char *SkeletalAnimModel::Node::getUserData() const
{
	return userData.text();
}

const Vector3 &SkeletalAnimModel::Node::getPosition() const
{
	return position;
}

const Quaternion &SkeletalAnimModel::Node::getRotation() const
{
	return rotation;
}

const Vector3 &SkeletalAnimModel::Node::getScale() const
{
	return scale;	
}

void SkeletalAnimModel::Node::getLocalTransform(Matrix4 &m) const
{
	Vector10 v;
	v.t = position;
	v.q = rotation;
	v.k = scale;

	v.ToMatrix4(m);
}

void SkeletalAnimModel::Node::read(InputStream &is)
{
	is >> name; 
	is >> parentIdx;
	is >> userData;

	is >> position;
	is >> rotation;
	is >> scale;
}

void SkeletalAnimModel::Node::write(OutputStream &os) const
{
	os << name;
	os << parentIdx;
	os << userData;

	os << position;
	os << rotation;
	os << scale;
}

/////////////////////////////////////////////////////////
SkeletalAnimModel::Bone::Bone()
: tBindGlobalTransform(Matrix4::IDENTITY)
, tBindGlobalTransformInv(Matrix4::IDENTITY)
, t0GlobalTransform(Matrix4::IDENTITY)
, t0GlobalTransformInv(Matrix4::IDENTITY)
{
}

SkeletalAnimModel::Bone::~Bone()
{
}

const Matrix4 &SkeletalAnimModel::Bone::getTBindGlobalTransform()
{
	return tBindGlobalTransform;
}

const Matrix4 &SkeletalAnimModel::Bone::getTBindGlobalTransformInv()
{
	return tBindGlobalTransformInv;
}

const Matrix4 &SkeletalAnimModel::Bone::getT0GlobalTransform()
{
	return t0GlobalTransform;
}

const Matrix4 &SkeletalAnimModel::Bone::getT0GlobalTransformInv()
{
	return t0GlobalTransformInv;
}

void SkeletalAnimModel::Bone::read(InputStream &is)
{
	SkeletalAnimModel::Node::read(is);

	is >> tBindGlobalTransform;
	is >> tBindGlobalTransformInv;
	is >> t0GlobalTransform;
	is >> t0GlobalTransformInv;
}

void SkeletalAnimModel::Bone::write(OutputStream &os) const
{
	SkeletalAnimModel::Node::write(os);

	os << tBindGlobalTransform;
	os << tBindGlobalTransformInv;
	os << t0GlobalTransform;
	os << t0GlobalTransformInv;
}

///////////////////////////////////////////////////////////////
SkeletalAnimModel::Mesh::Mesh()
: attachedNodeIdx(-1)
{
}

SkeletalAnimModel::Mesh::~Mesh()
{
}

const char *SkeletalAnimModel::Mesh::getName() const
{
	return name.text();
}

int SkeletalAnimModel::Mesh::getAttachedNodeIdx() const
{
	return attachedNodeIdx;
}

const char *SkeletalAnimModel::Mesh::getUserData() const
{
	return userData.text();
}

int SkeletalAnimModel::Mesh::getNumGlobalBoneIndices() const
{
	return globalBoneIndices.length();
}

int SkeletalAnimModel::Mesh::getGlobalBoneIndex(int i)
{
	return globalBoneIndices[i];
}

int SkeletalAnimModel::Mesh::getNumPatches() const
{
	return patches.length();
}

const SkeletalAnimModel::Mesh::Patch &SkeletalAnimModel::Mesh::getPatch(int i) const
{
	return patches[i];
}

void SkeletalAnimModel::Mesh::read(InputStream &is)
{
	is >> name;
	is >> attachedNodeIdx;
	is >> userData;

	VectorRead<int> globalBoneIndicesVectorRead(globalBoneIndices);
	is >> globalBoneIndicesVectorRead;

	VectorRead<Patch> patchesVectorRead(patches);
	is >> patchesVectorRead;
}

void SkeletalAnimModel::Mesh::write(OutputStream &os) const
{
	os << name;
	os << attachedNodeIdx;
	os << userData;

	VectorWrite<int> globalBoneIndicesVectorWrite(globalBoneIndices);
	os << globalBoneIndicesVectorWrite;

	VectorWrite<Patch> patchesVectorWrite(patches);
	os << patchesVectorWrite;
}

////////////////////////////////////////////////////////
SkeletalAnimModel::Data::Data()
{
}

SkeletalAnimModel::Data::~Data()
{
}

int SkeletalAnimModel::Data::getNumTextureInfos() const
{
	return textureInfos.length();
}

const SkeletalAnimModel::TextureInfo *SkeletalAnimModel::Data::getTextureInfo(int i) const
{
	return &textureInfos[i];
}

int SkeletalAnimModel::Data::getNumVisualEffectInfos() const
{
	return visualEffectInfos.length();
}

const SkeletalAnimModel::VisualEffectInfo *SkeletalAnimModel::Data::getVisualEffectInfo(int i) const
{
	return &visualEffectInfos[i];
}

int SkeletalAnimModel::Data::getNumBones() const
{
	return bones.length();
}

const SkeletalAnimModel::Bone *SkeletalAnimModel::Data::getBone(int i) const
{
	return &bones[i];
}

const Vector<SkeletalAnimModel::Bone> *SkeletalAnimModel::Data::getBones() const
{
	return &bones;
}
	
int SkeletalAnimModel::Data::getNumMeshes() const
{
	return meshes.length();
}

const SkeletalAnimModel::Mesh *SkeletalAnimModel::Data::getMesh(int i) const
{
	return &meshes[i];
}

int SkeletalAnimModel::Data::getDuration() const
{
	return animation.getDuration();
}

int SkeletalAnimModel::Data::getFPS() const
{
	return animation.getFPS();
}

int SkeletalAnimModel::Data::getNumBoneAnimations() const
{
	return animation.getNumBoneAnimations();
}

const SkeletalAnimModel::BoneAnimation *SkeletalAnimModel::Data::getBoneAnimation(int boneIdx_) const
{
	return &animation.getBoneAnimation(boneIdx_);
}

const char *SkeletalAnimModel::Data::getBoneName(int boneIdx_) const
{
	return animation.getBoneName(boneIdx_);
}

int SkeletalAnimModel::Data::getBoneIndex(const char *name_) const
{
	return animation.getBoneIndex(name_);
}

int SkeletalAnimModel::Data::getBoneParentIndex(int boneIdx_) const
{
	return animation.getBoneParentIndex(boneIdx_);
}

void SkeletalAnimModel::Data::getVector10(int boneIdx_, float time, Vector10 &v_) const
{
	return animation.getVector10(boneIdx_, time, v_);
}

void SkeletalAnimModel::Data::read(InputStream &is)
{
	is >> version;
	is >> platform;

	VectorRead<TextureInfo>  textureInfosVectorRead(textureInfos);
	is >> textureInfosVectorRead;

	VectorRead<VisualEffectInfo> visualEffectInfosVectorRead(visualEffectInfos);
	is >> visualEffectInfosVectorRead;

	VectorRead<Bone> bonesVectorRead(bones);
	is >> bonesVectorRead;

	VectorRead<Mesh> meshesVectorRead(meshes);
	is >> meshesVectorRead;

	is >> animation;
}

void SkeletalAnimModel::Data::write(OutputStream &os) const
{
	os << version;
	os << platform;

	VectorWrite<TextureInfo>  textureInfosVectorWrite(textureInfos);
	os << textureInfosVectorWrite;

	VectorWrite<VisualEffectInfo> visualEffectInfosVectorWrite(visualEffectInfos);
	os << visualEffectInfosVectorWrite;

	VectorWrite<Bone> bonesVectorWrite(bones);
	os << bonesVectorWrite;

	VectorWrite<Mesh> meshesVectorWrite(meshes);
	os << meshesVectorWrite;

	os << animation;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef EXPORTER
#else
SkeletalAnimModel::Resource::Resource(const char *path_)
: ResourceAccess(path_)
{
}

SkeletalAnimModel::Resource::~Resource()
{
	onDestroy();
}

int SkeletalAnimModel::Resource::getNumTextureInfos() const
{
	return data.getNumTextureInfos();
}

const SkeletalAnimModel::TextureInfo *SkeletalAnimModel::Resource::getTextureInfo(int i) const
{
	return data.getTextureInfo(i);
}

int SkeletalAnimModel::Resource::getNumVisualEffectInfos() const
{
	return data.getNumVisualEffectInfos();
}

const SkeletalAnimModel::VisualEffectInfo *SkeletalAnimModel::Resource::getVisualEffectInfo(int i) const
{
	return data.getVisualEffectInfo(i);
}

int SkeletalAnimModel::Resource::getNumBones() const
{
	return data.getNumBones();
}

const SkeletalAnimModel::Bone *SkeletalAnimModel::Resource::getBone(int i) const
{
	return data.getBone(i);
}

const Vector<SkeletalAnimModel::Bone> *SkeletalAnimModel::Resource::getBones() const
{
	return data.getBones();
}

int SkeletalAnimModel::Resource::getNumMeshes() const
{
	return data.getNumMeshes();
}

const SkeletalAnimModel::Mesh *SkeletalAnimModel::Resource::getMesh(int i) const
{
	return data.getMesh(i);
}

int SkeletalAnimModel::Resource::getDuration() const
{
	return data.getDuration();
}

int SkeletalAnimModel::Resource::getFPS() const
{
	return data.getFPS();
}

int SkeletalAnimModel::Resource::getNumBoneAnimations() const
{
	return data.getNumBoneAnimations();
}

const SkeletalAnimModel::BoneAnimation *SkeletalAnimModel::Resource::getBoneAnimation(int boneIdx_) const
{
	return data.getBoneAnimation(boneIdx_);
}

const char *SkeletalAnimModel::Resource::getBoneName(int boneIdx_) const
{
	return data.getBoneName(boneIdx_);
}

int SkeletalAnimModel::Resource::getBoneIndex(const char *name_) const
{
	return data.getBoneIndex(name_);
}

int SkeletalAnimModel::Resource::getBoneParentIndex(int boneIdx_) const
{
	return data.getBoneParentIndex(boneIdx_);
}

void SkeletalAnimModel::Resource::getVector10(int boneIdx_, float time, Vector10 &v_) const
{
	data.getVector10(boneIdx_, time, v_);
}

unsigned char *SkeletalAnimModel::Resource::onCreate(int length_)
{
	buffer.resize(length_);

	return &buffer[0];
}

void SkeletalAnimModel::Resource::onLoaded()
{
	MemInputStream is(&buffer[0], buffer.length());

	is >> data;

	buffer.destroy();
}

void SkeletalAnimModel::Resource::onDestroy()
{
	buffer.destroy();
}

///////////////////////////////////////////////////////////////////////////////////
#ifdef ENABLE_RESOURCE_IMPORT
SkeletalAnimModel::ResourceImporter::ResourceImporter(const char *name)
: ResourceImport(name)
{
}

SkeletalAnimModel::ResourceImporter::~ResourceImporter()
{
}

bool SkeletalAnimModel::ResourceImporter::initiate()
{
	return true;
}

void SkeletalAnimModel::ResourceImporter::terminate()
{
}

bool SkeletalAnimModel::ResourceImporter::onExportFile(const char *srcFilename_, const char *dstFilename_)
{
	// collect Options
	this->defaultExportFileFunc(srcFilename_, dstFilename_);

	return true;
}

bool SkeletalAnimModel::ResourceImporter::onDeleteFile(const char *srcFilename_)
{
	return this->defaultDeleteFileFunc(srcFilename_);
}
#endif

///////////////////////////////////////////////////////////////////////////////////
SkeletalAnimModel::SkeletalAnimModel()
: resource(0)
{
}

SkeletalAnimModel::~SkeletalAnimModel()
{
	destruct();
}

bool SkeletalAnimModel::construct(const char *path_)
{
	assert(resource==0);

	String directory	= System::getDirectory(path_);
	String fileName		= System::getFileName(path_);
	String extension	= System::getExtension(path_);
	String path			= path_;
	// String path = String(directory_) + String("/") + filename_;

	resource = SkeletalAnimModel::Resource::get(path.text());
	if(!resource)
		return false;

	resource->addReference();

	return true;
}

void SkeletalAnimModel::destruct()
{
	if(resource)
	{
		resource->release();
		resource = 0;
	}
}

int SkeletalAnimModel::getNumTextureInfos() const
{
	if(resource)
		return resource->getNumTextureInfos();
	else
		return 0;
}

const SkeletalAnimModel::TextureInfo *SkeletalAnimModel::getTextureInfo(int i) const
{
	if(resource && i>=0 && i<resource->getNumTextureInfos() )
		return resource->getTextureInfo(i);
	else
		return 0;
}

int SkeletalAnimModel::getNumVisualEffectInfos() const
{
	if(resource)
		return resource->getNumVisualEffectInfos();
	else
		return 0;
}

const SkeletalAnimModel::VisualEffectInfo *SkeletalAnimModel::getVisualEffectInfo(int i) const
{
	if(resource && i>=0 && i<resource->getNumVisualEffectInfos() )
		return resource->getVisualEffectInfo(i);
	else
		return 0;
}

int SkeletalAnimModel::getNumBones() const
{
	if(resource)
		return resource->getNumBones();
	else
		return 0;
}

const SkeletalAnimModel::Bone *SkeletalAnimModel::getBone(int i) const
{
	if(resource && i>=0 && i<resource->getNumBones() )
		return resource->getBone(i);
	else
		return 0;
}

const Vector<SkeletalAnimModel::Bone> *SkeletalAnimModel::getBones() const
{
	if(resource)
		return resource->getBones();
	else
		return 0;
}

int SkeletalAnimModel::getNumMeshes() const
{
	if(resource)
		return resource->getNumMeshes();
	else
		return 0;
}

const SkeletalAnimModel::Mesh *SkeletalAnimModel::getMesh(int i) const
{
	if(resource && i>=0 && i<resource->getNumMeshes() )
		return resource->getMesh(i);
	else
		return 0;
}

int SkeletalAnimModel::getDuration() const
{
	if(resource)
		return resource->getDuration();
	else
		return 1;
}

int SkeletalAnimModel::getFPS() const
{
	if(resource)
		return resource->getFPS();
	else
		return 30;
}

int SkeletalAnimModel::getNumBoneAnimations() const
{
	if(resource)
		return resource->getNumBoneAnimations();
	else
		return 0;
}

const SkeletalAnimModel::BoneAnimation *SkeletalAnimModel::getBoneAnimation(int boneIdx_) const
{
	if(resource)
		return resource->getBoneAnimation(boneIdx_);
	else
		return 0;
}

const char *SkeletalAnimModel::getBoneName(int boneIdx_) const
{
	if(resource)
		return resource->getBoneName(boneIdx_);
	else
		return 0;
}

int SkeletalAnimModel::getBoneIndex(const char *name_) const
{
	if(resource)
		return resource->getBoneIndex(name_);
	else
		return 0;
}

int SkeletalAnimModel::getBoneParentIndex(int boneIdx_) const
{
	if(resource)
		return resource->getBoneParentIndex(boneIdx_);
	else
		return 0;
}

void SkeletalAnimModel::getVector10(int boneIdx_, float time, Vector10 &v_) const
{
	if(resource)
		return resource->getVector10(boneIdx_, time, v_);
}

#endif