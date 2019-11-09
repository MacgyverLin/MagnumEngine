#ifndef _MaxSkeletalAnimModelBuilder_h_
#define _MaxSkeletalAnimModelBuilder_h_

#include "EString.h"
#include "SkeletalAnimModel.h"
#include "MAXRawIndex.h"
// #include "ARTBkgBuilder.h"
#include "IGame/IGame.h"
#include "IGame/IGameObject.h"
#include "IGame/IGameProperty.h"
#include "IGame/IGameControl.h"
#include "IGame/IGameModifier.h"
#include "IGame/IConversionManager.h"
#include "IGame/IGameError.h"
using namespace EpicForce;

namespace EpicForce 
{

class MaxSkeletalAnimModelBuilder 
{
public:
	MaxSkeletalAnimModelBuilder(int version_, const Platform &platform_, float meterPerUnit_,
					    int maxNumBonesPerPatch_,
					    Vector<String> &texturePaths_, Vector<IGameMaterial *> &materials_, Vector<IGameNode *> &nodes_,
					    int startFrame_, int endFrame_, int framePerTick_, int fps_, 
						int framePerKey_);
	virtual ~MaxSkeletalAnimModelBuilder();

	static bool infoMessage(const char *a_fmtstr, ...);
	static bool warningMessage(const char *a_fmtstr, ...);
	static bool errorMessage(const char *a_fmtstr, ...);
	static bool isDXShaderMaterialClass(const char *className);
	static bool isValidMaterialClass(const char *className);

	virtual bool build(SkeletalAnimModel::Data &skeletalModelData, const char *exportDirectory_);

	const char *fixupName(const char *buf);
	static Point3 directionTransform(const Point3 &p, const GMatrix &mat);
	static void convMatrixToVector10(Vector3 &t, Quaternion &q, Vector3 &k, const GMatrix &tm);
	static GMatrix getOffsetMatrix(IGameNode *maxNode);
	int frame2Tick(int frame);
private:
	bool dumpSkin(IGameSkin *skin);
	bool dumpModifier(IGameModifier *modifier);
	
	static Vector3 scaleVector(const Vector3 &in);
	static Matrix4 scaleMatrix(const Matrix4 &in);

	void replaceBlackSlash(String &path);
	bool getEpicForceToolsDirectory(String &toolsDir);
	bool isValidPath(const char *fullPath, const char *toolsDir);
	String getMaterialDirectory(const char *fullPath, const char *toolsDir);
	String getGLFXDirectory(const char *fullPath, const char *toolsDir);
	String getGLFXOutputDirectory(const char *fullPath, const char *toolsDir, const char *exportDirectory);

	void mergeDoubleSlashes(std::string &str);
	bool resolveBitmapPath(char const *path, String &resolvedPath);
	bool makeDirectory(const char *dir_);
	bool copyFile(const char *srcPath, const char *dstPath);
	void getChildren(TiXmlNode *node, const char *type, Vector<TiXmlNode *> &children);
	void getChildren(TiXmlNode *node, Vector<TiXmlNode *> &children);
	
	String getFileName(const char *fullPath);
	String getExtension(const char *fullPath);
	String getDirectory(const char *fullPath);

	int getBitmapIdx(const char *path);
	int getVisualEffectInfoIdx(IGameMaterial *mat);
	int getNodeIdx(IGameNode *node);

	bool buildTexture(SkeletalAnimModel::TextureInfo &textureInfo, const String &info);
	bool buildMaterial(SkeletalAnimModel::VisualEffectInfo &visualEffectInfo, IGameMaterial *maxMaterial);
		bool parseAttributesBlock(AttributesBlock &attributesBlock, TiXmlNode *attributesNode);
		bool parseMaterialUniformVariablesBlock(SkeletalAnimModel::VisualEffectInfo &visualEffectInfo, const String &name, const String &type, const String &defaultValues);
		//int getNumBonesPerVertex(IGameFX *fx);
	bool buildNodes(SkeletalAnimModel::Data &skeletalModelData);
		void allocNodes(SkeletalAnimModel::Data &artbkgData);
		void resetTransformCaches(SkeletalAnimModel::Data &artbkgData);
		bool buildNode(SkeletalAnimModel::Data &skeletalModelData, SkeletalAnimModel::Node &node, IGameNode *iGameNode);
			void buildNodePositionRotationScale(Vector3 &position, Quaternion &quatenion, Vector3 &scale, IGameNode *iGameNode);
		bool buildBone(SkeletalAnimModel::Data &skeletalModelData, SkeletalAnimModel::Bone &bone, 
					   IGameNode *iGameNode, int currentBoneIdx);
		bool buildMesh(SkeletalAnimModel::Data &skeletalModelData, SkeletalAnimModel::Mesh &mesh, 
					   IGameNode *iGameNode, IGameMesh *iGameMeshObj);
			bool getRawIndices(Vector<MAXRawIndex> &maxRawIndices, 
							   IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, const Tab<FaceEx*> &faces, 
							   const SkeletalAnimModel::VisualEffectInfo &visualEffectInfo);
			bool optimizeVBIB(Vector<char> &vbBuffer, Vector<char> &ibBuffer, 
                              int &numOptimizedVertices, int &numOptimizedIndices, 
							  int &stride, Vector<int> &offsets, Vector<int> &sizes,
							  const Vector<MAXRawIndex> &maxRawIndices, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj,
							  const GMatrix &offsetTM, const GMatrix &initSkinTM,
							  const SkeletalAnimModel::VisualEffectInfo &visualEffectInfo);
			void getStrideOffset(int &stride, Vector<int> &offsets, Vector<int> &sizes, 
								 const Vector<GXVertexFormat> &vertexFormat);
			const Matrix4 &getGlobalTransform(Vector<SkeletalAnimModel::Bone> bones, int currentBoneIdx);
		bool buildBoneAnimations(SkeletalAnimModel::Data &skeletalModelData);
			void buildBoneAnimation(SkeletalAnimModel::BoneAnimation &boneAnimation, SkeletalAnimModel::Bone &bone, IGameNode *maxNode);
	
	typedef bool (*IndexGetter)(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner);
	typedef bool (*VertexGetter)(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index);
	
	static IndexGetter indexGetters[];
	static VertexGetter vertexGetters[];

	static bool getPosition0Index(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner);
	static bool getNormalIndex(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner);
	static bool getColor0Index(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner);
	static bool getTexCoord0Index(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner);
	static bool getTexCoord1Index(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner);
	static bool getTexCoord2Index(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner);
	static bool getTexCoord3Index(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner);
	static bool getTexCoord4Index(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner);
	static bool getTexCoord5Index(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner);
	static bool getTexCoord6Index(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner);
	static bool getTexCoord7Index(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner);
	static bool getTangent0Index(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner);
	static bool getBinormal0Index(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner);
	static bool getBone1Index(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner);
	static bool getBone2Index(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner);
	static bool getBone2WeightIndex(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner);
	static bool getBone4Index(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner);
	static bool getBone4WeightIndex(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner);
	static bool getPosition0(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index);
	static bool getNormal(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index);
	static bool getColor0(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index);
	static bool getTexCoord0(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index);
	static bool getTexCoord1(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index);
	static bool getTexCoord2(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index);
	static bool getTexCoord3(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index);
	static bool getTexCoord4(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index);
	static bool getTexCoord5(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index);
	static bool getTexCoord6(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index);
	static bool getTexCoord7(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index);
	static bool getTangent0(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index);
	static bool getBinormal0(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index);
	static bool getBone1IDXs(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index);
	static bool getBone2IDXs(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index);
	static bool getBone2Weights(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index);
	static bool getBone4IDXs(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index);
	static bool getBone4Weights(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index);

	int version;
	const Platform &platform;
	static float meterPerUnits;		
	Vector<String				 >	texturePaths;
	Vector<IGameMaterial		*>	materials;
	Vector<IGameNode			*>	nodes;
	int startFrame;
	int endFrame;
	int framePerTick;
	int fps;
	int framePerKey;
	int maxNumBonesPerPatch;
	String exportDirectory;
	String exportFileName;
	String exportExtension;
	
	Vector<Matrix4> bonesGlobalMat;
	Vector<bool>    bonesGlobalMatValid;
};

};

#endif