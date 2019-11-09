#include <AssetManagement/AssetUser.h>
#include <IFileResolutionManager.h>
#include "IGame/IGame.h"
#include "IGame/IGameObject.h"
#include "IGame/IGameProperty.h"
#include "IGame/IGameControl.h"
#include "IGame/IGameModifier.h"
#include "IGame/IConversionManager.h"
#include "IGame/IGameError.h"
#include <IGame/IGameFX.h>
#include <IDxMaterial.h>
#include <pbbitmap.h>
#include "Helper.h"
#include "MaxSkeletalAnimModelBuilder.h"
#include "SkeletalAnimModel.h"
#include "VertexIndexOptimizer.h" 
#include "tinyxml.h"
using namespace EpicForce;

float MaxSkeletalAnimModelBuilder::meterPerUnits = 1.0;

void MaxSkeletalAnimModelBuilder::replaceBlackSlash(String &path)
{
	for(int i=0; i<path.length(); i++)
	{
		if(path[i]=='\\')
			path[i] = '/';
	}
}

bool MaxSkeletalAnimModelBuilder::getEpicForceToolsDirectory(String &toolsDir)
{
	const char *toolEnv = getenv("EPICFORCE_TOOLS");
	if(!toolEnv)
		return false;

	toolsDir = toolEnv;
	replaceBlackSlash(toolsDir);

	int i;
	for(i=toolsDir.length()-1; i>=0; i--)
	{
		if( toolsDir[i]!='/' )
			break;
	}

	if(i!=toolsDir.length()-1)
		toolsDir[i+1] = 0;

	toolsDir += "/";

	return true;
}

bool MaxSkeletalAnimModelBuilder::isValidPath(const char *fullPath, const char *toolsDir)
{
	String s1 = toolsDir; s1.toLower();
	String s2 = fullPath; s2.toLower();

	return strnicmp(fullPath, toolsDir, strlen(toolsDir))==0;
}

String MaxSkeletalAnimModelBuilder::getMaterialDirectory(const char *fullPath, const char *toolsDir)
{
	String fxpath = toolsDir + String("fx/");
	int start = fxpath.length();

	const char *filename = strrchr(fullPath, '/')+1;
	const char *ext      = strrchr(fullPath, '.') +1;

	if(filename - fullPath - start==0)
		return "";
	else
		return String(&fullPath[start], filename - fullPath - start);
}

String MaxSkeletalAnimModelBuilder::getGLFXDirectory(const char *fullPath, const char *toolsDir)
{
	return String(toolsDir) + String("glfx/") + getMaterialDirectory(fullPath, toolsDir); 
}

String MaxSkeletalAnimModelBuilder::getGLFXOutputDirectory(const char *fullPath, const char *toolsDir, const char *exportDirectory)
{
	return String(exportDirectory) + String("shaders/") + getMaterialDirectory(fullPath, toolsDir);
}


///////////////////////////////////////////////////////////////////////////////
MaxSkeletalAnimModelBuilder::MaxSkeletalAnimModelBuilder(int version_, const Platform &platform_, float meterPerUnits_,
														 int maxNumBonesPerPatch_,
														 Vector<String> &texturePaths_, Vector<IGameMaterial *> &materials_, Vector<IGameNode *> &nodes_,
														 int startFrame_, int endFrame_, int framePerTick_, int fps_, int framePerKey_)
: version(version_)
, platform(platform_)
, maxNumBonesPerPatch(maxNumBonesPerPatch_)
, texturePaths(texturePaths_)
, materials(materials_)
, nodes(nodes_)
, startFrame(startFrame_)
, endFrame(endFrame_)
, framePerTick(framePerTick_)
, fps(fps_)
, framePerKey(framePerKey_) 
{
	meterPerUnits = meterPerUnits_;
}

MaxSkeletalAnimModelBuilder::~MaxSkeletalAnimModelBuilder()
{
}

bool MaxSkeletalAnimModelBuilder::infoMessage(const char *a_fmtstr, ...)
{
	char buf[1024];

	va_list argptr; 
	va_start(argptr, a_fmtstr);

	vsprintf(buf, a_fmtstr, argptr);
	MessageBox(0, buf, "Info", MB_OK);
	
	va_end(argptr);

	return true;
}

bool MaxSkeletalAnimModelBuilder::warningMessage(const char *a_fmtstr, ...)
{
	char buf[2048];

	va_list argptr; 
	va_start(argptr, a_fmtstr); 
	
	vsprintf(buf, a_fmtstr, argptr);
	MessageBox(0, buf, "Warning", MB_OK);
	
	va_end(argptr); 

	return true;
}

bool MaxSkeletalAnimModelBuilder::errorMessage(const char *a_fmtstr, ...)
{
	char buf[2048];

	va_list argptr; 
	va_start(argptr, a_fmtstr);

	vsprintf(buf, a_fmtstr, argptr);
	MessageBox(0, buf, "Error", MB_OK);
	
	va_end(argptr);

	return false;
}

const char *MaxSkeletalAnimModelBuilder::fixupName(const char *buf)
{
	static char buffer[256];
	char *cPtr;

    strcpy(buffer, buf);
    cPtr = buffer;

    while(*cPtr) 
	{
		if (*cPtr == '"') 
			*cPtr = 39;	// Replace double-quote with single quote.
        else if (*cPtr <= 31) 
			*cPtr = _T('_');	// Replace control characters with underscore
        cPtr++;
    }

	return buffer;
}

Point3 MaxSkeletalAnimModelBuilder::directionTransform(const Point3 &p, const GMatrix &mat)
{
	Point3 rval = p * mat;
	
	rval = rval - Point3(mat[3][0], mat[3][1], mat[3][2]);
	return rval;
}

// This is the Matrix to bring Vertices from ObjectSpace to Local Space
GMatrix MaxSkeletalAnimModelBuilder::getOffsetMatrix(IGameNode *iGameNode)
{
	GMatrix parentWorldTM;
	if( iGameNode->GetNodeParent() )
		parentWorldTM  = iGameNode->GetNodeParent()->GetWorldTM();
	else
		parentWorldTM.SetIdentity();

	GMatrix localTM  = iGameNode->GetLocalTM();
	GMatrix worldTM  = iGameNode->GetWorldTM();
	GMatrix objectTM = iGameNode->GetObjectTM();

	                   // object space -> worldSpace, worldSpace -> localSpace
	GMatrix offsetTM = objectTM * worldTM.Inverse();
	return offsetTM;
}

int MaxSkeletalAnimModelBuilder::frame2Tick(int frame)
{
	return frame * framePerTick;
}

void MaxSkeletalAnimModelBuilder::mergeDoubleSlashes(std::string &str)
{
    std::string::size_type off;
    //  first, turn forward slashes to backward
    while ((off = str.find("/")) != std::string::npos) 
	{
        str.replace(off, 2, "\\");
    }
    //  second, turn double backward slashes to single
    while ((off = str.find("\\\\")) != std::string::npos) 
	{
        str.replace(off, 2, "\\");
    }
}

bool MaxSkeletalAnimModelBuilder::resolveBitmapPath(char const *path, String &resolvedPath)
{
	string temp(IFileResolutionManager::GetInstance()->GetFullFilePath(path, MaxSDK::AssetManagement::kBitmapAsset));

	if(temp.empty())
		return false;

	mergeDoubleSlashes(temp);

	resolvedPath = temp.c_str();
  
	return true;
}

String MaxSkeletalAnimModelBuilder::getDirectory(const char *fullPath)
{
	// const char *str = "D:\\Program Files\\Autodesk\\3ds Max 2012\\Scripts\\Startup\\epicforce\\DXShaderTest.fx";
	const char *filename = strrchr(fullPath, '/')+1;  
	const char *ext      = strrchr(fullPath, '.') +1;

	return String(fullPath, filename - fullPath);
}

String MaxSkeletalAnimModelBuilder::getFileName(const char *fullPath)
{
	// const char *str = "D:\\Program Files\\Autodesk\\3ds Max 2012\\Scripts\\Startup\\epicforce\\DXShaderTest.fx";
	const char *filename = strrchr(fullPath, '/')+1;
	const char *ext      = strrchr(fullPath, '.');

	return String(filename, ext - filename);
}

String MaxSkeletalAnimModelBuilder::getExtension(const char *fullPath)
{
	const char *filename = strrchr(fullPath, '/')+1;
	const char *ext      = strrchr(fullPath, '.')+1;

	// const char *str = "D:\\Program Files\\Autodesk\\3ds Max 2012\\Scripts\\Startup\\epicforce\\DXShaderTest.fx";
	return strrchr(fullPath, '.')+1;
}

bool MaxSkeletalAnimModelBuilder::makeDirectory(const char *dir_) 
{
#if defined(WIN32)
	String dir(dir_);
	Vector<String> intermediateDirs;
	String tem =  "";

	WIN32_FIND_DATA fileinfo;
	HANDLE fFile = FindFirstFile(dir, &fileinfo); 

	if(fileinfo.dwFileAttributes   ==   FILE_ATTRIBUTE_DIRECTORY) 
	{ 
		//   Directory   Exists   close   file   and   return 
		FindClose(fFile); 
		return true; 
	}

	for(int i=0; i<dir.length(); i++) // Parse the supplied String Directory
	{ 
		if(dir[i] != '\\' && dir[i] != '/')		// if the Charachter is not a \   
			tem += dir[i];		// add the character to the Temp String 
		else 
		{ 
			intermediateDirs.push() = tem; // if the Character is a  \   
			tem += "\\";		// Now add the  \ to the temp string 
		} 
		if(i == dir.length()-1) //   If   we   reached   the   end   of   the   String 
			intermediateDirs.push() = tem; 
	} 

	// Close   the   file 
	FindClose(fFile); 

	// Now   lets   cycle   through   the   String   Array   and   create   each   directory   in   turn 
	for(int i=1; i<intermediateDirs.length(); i++) 
	{ 
		debug("intermediateDirs[i]=%s", intermediateDirs[i]);
		bool tt = CreateDirectory(intermediateDirs[i], NULL); 
		// If the Directory exists it will return false 
		if(tt) 
			SetFileAttributes(intermediateDirs[i], FILE_ATTRIBUTE_NORMAL); 
		// If   we   were   successful   we   set   the   attributes   to   normal 
	} 

	// Now   lets   see   if   the   directory   was   successfully   created 
	fFile = FindFirstFile(dir, &fileinfo);
	if(fileinfo.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) 
	{ 
		// Directory   Exists   close   file   and   return 
		FindClose(fFile); 
		return true; 
	} 
	else 
	{ 
		// For   Some   reason   the   Function   Failed     Return   FALSE 
		FindClose(fFile); 
		return false; 
	}

	return true;
#elif defined(__ANDROID__ )
	return true;
#elif ( defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) )
	return true;
#endif
}

bool MaxSkeletalAnimModelBuilder::copyFile(const char *srcPath, const char *dstPath)
{
	return CopyFileEx(srcPath, dstPath, 0, 0, FALSE, 0 )!=0;
}

void MaxSkeletalAnimModelBuilder::getChildren(TiXmlNode *node, const char *type, Vector<TiXmlNode *> &children)
{
	children.clear();
	for(TiXmlNode *childNode = node->FirstChild(type); childNode; childNode = childNode->NextSibling(type) )
	{
		children.push() = childNode;
	}
}

void MaxSkeletalAnimModelBuilder::getChildren(TiXmlNode *node, Vector<TiXmlNode *> &children)
{
	children.clear();
	for(TiXmlNode *childNode = node->FirstChild(); childNode; childNode = childNode->NextSibling() )
	{
		children.push() = childNode;
	}
}

bool MaxSkeletalAnimModelBuilder::isDXShaderMaterialClass(const char *className)
{
	static const char *classNames[] =
	{
		/*
		"EpicForceDiffuse",
		"EpicForceDiffuseGloss",
		"EpicForceDiffuseBump",
		"EpicForceDiffuseEnv",
		"EpicForceDiffuseGlossBump",
		"EpicForceDiffuseGlossEnv",
		"EpicForceDiffuseBumpEnv",
		"EpicForceDiffuseGlossBumpEnv",
		*/
		"DirectX Shader"
	};

	for(int i=0; i<sizeof(classNames)/sizeof(classNames[0]); i++)
	{
		if(String(className)==classNames[i])
			return true;
	}

	return false;
}

bool MaxSkeletalAnimModelBuilder::isValidMaterialClass(const char *className)
{
	static const char *classNames[] =
	{
		/*
		"EpicForceDiffuse",
		"EpicForceDiffuseGloss",
		"EpicForceDiffuseBump",
		"EpicForceDiffuseEnv",
		"EpicForceDiffuseGlossBump",
		"EpicForceDiffuseGlossEnv",
		"EpicForceDiffuseBumpEnv",
		"EpicForceDiffuseGlossBumpEnv",
		*/
		"DirectX Shader",
		"Multi/Sub-Object"
	};

	for(int i=0; i<sizeof(classNames)/sizeof(classNames[0]); i++)
	{
		if(String(className)==classNames[i])
			return true;
	}

	return false;
}


int MaxSkeletalAnimModelBuilder::getBitmapIdx(const char *path)
{
	for(int i=0; i<texturePaths.length(); i++)
	{
		if( texturePaths[i] == path )
			return i;
	}

	return -1;
}

int MaxSkeletalAnimModelBuilder::getVisualEffectInfoIdx(IGameMaterial *mat)
{
	for(int i=0; i<materials.length(); i++)
	{
		if( materials[i] == mat)
		{
			const char *name = materials[i]->GetMaterialName();
			return i;
		}
	}

	return -1;
}

int MaxSkeletalAnimModelBuilder::getNodeIdx(IGameNode *node)
{
	for(int i=0; i<nodes.length(); i++)
	{
		if( nodes[i] == node)
		{
			return i;
		}
	}

	return -1;
}

bool MaxSkeletalAnimModelBuilder::build(SkeletalAnimModel::Data &skeletalModelData, const char *exportPath_)
{
	String exportPath = exportPath_;
	replaceBlackSlash(exportPath);

	exportDirectory	= getDirectory(exportPath.text());
	exportFileName	= getFileName(exportPath.text());
	exportExtension	= getExtension(exportPath.text());

	skeletalModelData.version  = version;
	skeletalModelData.platform = platform;

	skeletalModelData.textureInfos.resize(texturePaths.length());
	for(int i=0; i<skeletalModelData.textureInfos.length(); i++)
	{
		if( !buildTexture(skeletalModelData.textureInfos[i], texturePaths[i]) )
			return false; 
	}

	skeletalModelData.visualEffectInfos.resize(materials.length());
	for(int i=0; i<skeletalModelData.visualEffectInfos.length(); i++) 
	{
		if( !buildMaterial(skeletalModelData.visualEffectInfos[i], materials[i]) )
			return false;
	}

	if( !buildNodes(skeletalModelData) ) 
		return false;

	if( !buildBoneAnimations(skeletalModelData) )
		return false;

	return true;
}

bool MaxSkeletalAnimModelBuilder::buildTexture(SkeletalAnimModel::TextureInfo &textureInfo, const String &fileName_)
{
	String resolvedPath;
	if( !resolveBitmapPath(fileName_.text(), resolvedPath) )
	{
		return errorMessage("Cannot resolve asset file Location %s\n", fileName_.text());
	}
	
	replaceBlackSlash(resolvedPath);

	String fileName			= getFileName(resolvedPath.text());
	String extension		= getExtension(resolvedPath.text());
	textureInfo.filePath	= "textures/" + fileName;

	makeDirectory(exportDirectory + "textures/");
	String writePath	= exportDirectory + "textures/" + fileName + "." + extension;
	replaceBlackSlash(writePath);	writePath = writePath.toLower();

	// write out texture file
	debug("buildTexture: resolvedPath=%s", resolvedPath.text());

	return CopyFileEx(resolvedPath, writePath, 0, 0, FALSE, 0 )!=0;
}
/*
int MaxSkeletalAnimModelBuilder::getNumBonesPerVertex(IGameFX *fx)
{
	for(int j=0; j<fx->GetNumberOfProperties(); j++)
	{ 
		IGameFXProperty *fxprop = fx->GetIGameFXProperty(j);
		String propertiesName					= fxprop->GetPropertyName();

		propertiesName = propertiesName.toLower();

		if(propertiesName=="numbonespervertex") 
		{
			IGameProperty *prop						= fxprop->GetIGameProperty();
			int	numBonesPerVertex;
			prop->GetPropertyValue(numBonesPerVertex);

			return numBonesPerVertex;
		}
	}

	return 0;
}
*/

bool MaxSkeletalAnimModelBuilder::buildMaterial(SkeletalAnimModel::VisualEffectInfo &visualEffectInfo, IGameMaterial *maxMaterial)
{
	const char *classname = maxMaterial->GetMaterialClass(); 

	if( !isValidMaterialClass(classname) )  
	{
		return errorMessage("Material \"%s\" is not supported, use DXShader or Multi/Sub Material\n", maxMaterial->GetMaterialName());
	}

	visualEffectInfo.name						= maxMaterial->GetMaterialName();
	visualEffectInfo.multiSub					= maxMaterial->IsMultiType();

	if( !visualEffectInfo.isMultiSub() )
	{
		/////////////////////////////////////////////////////////////////////////////////////////
		// Effect Parameter
		IGameFX *fx = maxMaterial->GetIGameFX();  
		// const MaxSDK::AssetManagement::AssetUser &assetUser = fx->GetEffectFile();
		if(!fx)
			return errorMessage("Material .fx file is not set properly\"%s\"'s", maxMaterial->GetMaterialName());

		//visualEffectInfo.numBonesPerVertex = getNumBonesPerVertex(fx);

		IDxMaterial *idxm = (IDxMaterial *)maxMaterial->GetMaxMaterial()->GetInterface(IDXMATERIAL_INTERFACE);
		if(!idxm)
			return false;

		const MaxSDK::AssetManagement::AssetUser &assetUser = idxm->GetEffectFile();
		String filePath = assetUser.GetFullFilePath();
		replaceBlackSlash(filePath);

		//////////////////////////////////////////////////////////////////////////////////////////
		String epicForceToolsPath;
		if(!getEpicForceToolsDirectory(epicForceToolsPath))
			return errorMessage("Please set Environment Variable EPICFORCE_TOOLS\n");
		replaceBlackSlash(epicForceToolsPath);

		if( !isValidPath(filePath.text(), epicForceToolsPath) )
			return errorMessage("fx \"%s\" file must be put at EPICFORCE_TOOLS directory\n", filePath.text());

		String fxDirectory				= getDirectory(filePath.text());
		String fxFileName				= getFileName(filePath.text()); 
		String fxExt					= getExtension(filePath.text());

		String glfxDirectory			= getGLFXDirectory(filePath.text(), epicForceToolsPath.text());
		String glfxOutputDirectory		= getGLFXOutputDirectory(filePath.text(), epicForceToolsPath.text(), exportDirectory.text());
		String glfxMaterialDirectory	= getMaterialDirectory(filePath.text(), epicForceToolsPath.text());

		String glfxPath					= glfxDirectory + String(fxFileName) + String(".visualeffect");
		String glfxOutputPath			= glfxOutputDirectory + String(fxFileName) + String(".visualeffect");
		String glfxMaterialPath			= String("shaders/") + glfxMaterialDirectory + String(fxFileName); 

		replaceBlackSlash(glfxPath);			glfxPath.toLower();
		replaceBlackSlash(glfxOutputPath);		glfxOutputPath.toLower();
		replaceBlackSlash(glfxMaterialPath);	glfxMaterialPath.toLower();
		
		//////////////////////////////////////////////////////////////////////////////////////////
		visualEffectInfo.filePath		= glfxMaterialPath;
		
		/////////////////////////////////////////////////////////////////////////////////////////
		// parse visual effect
		TiXmlDocument doc(glfxPath);
		if(!doc.LoadFile())
			return errorMessage("Cannot Open \"%s\" for parsing\n", glfxPath.text()); 

		TiXmlNode *visualEffectNode = doc.FirstChild("VisualEffect");
		if(!visualEffectNode)
			return errorMessage("Failed to parse \"%s\"\n", glfxPath.text());

		TiXmlNode *attributesNode = visualEffectNode->FirstChild("Attributes");
		if(!attributesNode)
			return errorMessage("Failed to parse \"%s\"\n", glfxPath.text());

		if( !parseAttributesBlock(visualEffectInfo.attributesBlock , attributesNode) )
			return errorMessage("Failed to parse AttributesBlock\n");
		 
		/////////////////////////////////////////////////////////////////////////////////////////
		// make output dir and export
		makeDirectory(glfxOutputDirectory); 
		if( !copyFile(glfxPath.text(), glfxOutputPath.text()) )
			return errorMessage("Failed to copy \"%s\" to \"%s\"\n", glfxPath.text(), glfxOutputPath.text());

		//////////////////////////////////////////////////////////////////////////
		#if 0
		String xmlString = "<VisualEffect>\n";
		
		xmlString += "\t<VertexDesc>\n";
		for(int j=0; j<fx->GetNumberOfProperties(); j++)
		{ 
			IGameFXProperty *fxprop = fx->GetIGameFXProperty(j);

			IGameFXProperty::IGameFXPropUsage usage = fxprop->GetPropertyUsage();
			String fxSematic					= fxprop->GetFXSemantic();
			String fxDefaultValue				= fxprop->GetFXDefaultValue();
			String propertiesName				= fxprop->GetPropertyName();
			String propertyType					= fxprop->GetPropertyType();
			IGameNode *node						= fxprop->GetBindingNode();

			if(propertiesName=="vertexDesc") 
			{
				if(propertyType=="string") 
				{
					if( !parseMaterialVertexDescriptor(material, propertiesName, propertyType, fxDefaultValue) )
					{
						return errorMessage("Invalid vertexDesc definition %s\n", propertiesName.text());
					}
				}
				else
				{
					return errorMessage("vStream0Format must be string\n");
				}
			}
		}
		xmlString			 += "\t</VertexDesc>\n";

		//////////////////////////////////////////////////////////////////////////
		xmlString			 += "\t<UniformVariablesBlock>\n";
		for(int j=0; j<fx->GetNumberOfProperties(); j++)
		{ 
			IGameFXProperty *fxprop = fx->GetIGameFXProperty(j);

			IGameFXProperty::IGameFXPropUsage usage = fxprop->GetPropertyUsage();
			String fxSematic					= fxprop->GetFXSemantic();
			String fxDefaultValue				= fxprop->GetFXDefaultValue();
			String propertiesName				= fxprop->GetPropertyName();
			String propertyType					= fxprop->GetPropertyType();
			IGameNode *node						= fxprop->GetBindingNode();

			if(propertiesName!="vertexDesc") 
			{
				if(!parseMaterialUniformVariablesBlock(material, propertiesName, propertyType, fxDefaultValue))
					return errorMessage("Invalid UniformVariablesBlock\n");
			}

			/*
			#if 0
			for(int k=0; k<fxprop->GetNumberOfFXAnnotations(); k++)
			{
				MSTR languageType, key, value;
				bool rval = fxprop->GetFXAnnotation(k, &languageType, &key, &value);
			}

			for(int k=0; k<fxprop->GetNumberofFXPipeStates(); k++)
			{
				MSTR key, value;
				bool rval = fxprop->GetPipeStates(k, &key, &value);
			}
			#endif 
			*/
		}
		xmlString += "\t</UniformVariablesBlock>\n";

		//////////////////////////////////////////////////////////////////////////
		char buffer[4096];

		for(int i=0; i<fx->GetNumberOfTechniques(); i++)
		{
			IGameFXTechnique *technique = fx->GetIGameFXTechnique(i);
			const char *name = technique->GetTechniqueName();

			for(int j=0; j<technique->GetNumberOfPasses(); j++)
			{
				IGameFXPass *pass = technique->GetIGameFXPass(j);
				const char *passName = pass->GetPassName();

				sprintf(buffer, "\t<Pass name=\"%s\">\n", passName);
				xmlString += buffer;
				
				for(int k=0; k<pass->GetNumberOfFXAnnotations(); k++)
				{
					MSTR languageType, key, value;
					bool rval = pass->GetFXAnnotation(k, &languageType, &key, &value);
				}

				xmlString += "\t\t<RenderStatesBlock>\n";

				for(int k=0; k<pass->GetNumberofFXPipeStates(); k++)
				{
					MSTR key, value;
					bool rval = pass->GetPipeStates(k, &key, &value);

					sprintf(buffer, "\t\t\t<RenderState type=\"%s\" value=\"%s\"/>\n", key.data(), value.data());
					xmlString += buffer;
				}
				xmlString += "\t\t</RenderStatesBlock>\n";

				MSTR vsEntryFuncName, vsCode;
				MSTR psEntryFuncName, psCode;
				pass->GetVertexShader(&vsEntryFuncName, &vsCode);
				pass->GetPixelShader(&psEntryFuncName, &psCode);

				xmlString += "\t\t<HLSL>\n";

				xmlString += "\t\t\t<VertexShader>\n";
				// xmlString += vsCode.data();
				xmlString += "\t\t\t</VertexShader>\n";

				xmlString += "\t\t\t<PixelShader>\n";
				// xmlString += psCode.data();
				xmlString += "\t\t\t</PixelShader>\n";

				xmlString += "\t\t</HLSL>\n";

				xmlString += "\t</Pass>\n";
			}

			for(int k=0; k<technique->GetNumberOfFXAnnotations(); k++)
			{
				MSTR languageType, key, value;
				bool rval = technique->GetFXAnnotation(k, &languageType, &key, &value);
			}
		}

		xmlString += "</VisualEffect>\n";

		FILE *fptr = fopen(writePath.text(), "wt");
		if(!fptr)
			return errorMessage("Error in writing %s\n", writePath.text());
		fprintf(fptr, "%s\n", xmlString.text() );
		fclose(fptr);
		#endif

		/////////////////////////////////////////////////////////////////////////////////////////
		// Effect Bitmap
		// virtual PBBitmap * GetSoftwareRenderBitmap() = 0;
		#if 0
		for(int j=0; j<idxm->GetNumberOfLightParams(); j++)
		{
			INode *node								= idxm->GetLightNode(j);
			MCHAR *lightParamName					= idxm->GetLightParameterName(j);
			IDxMaterial::LightSemantics semantic	= idxm->GetLightSemantic(j);
		}
		#endif

		// virtual void ReloadDXEffect()=0;
		visualEffectInfo.textureInfoIndices.resize(idxm->GetNumberOfEffectBitmaps());
		for(int j=0; j<idxm->GetNumberOfEffectBitmaps(); j++) 
		{
			PBBitmap *bitmap		= idxm->GetEffectBitmap(j);
			
			BitmapInfo bi			= bitmap->bi;
			MaxSDK::Util::Path path = bitmap->bi.GetPathEx().ConvertToAbsolute();
			
			String resolvedPath;
			if( !resolveBitmapPath(path.GetCStr(), resolvedPath) )
				return false;

			visualEffectInfo.textureInfoIndices[j]  = getBitmapIdx(resolvedPath);

			//debug("material %s %d\n", finalpath.text(), material.textureIndices[j]);
		}
	}

	//debug("Name=%s"			, material.name.text());
	//debug("isMultiSub=%d"	, material.isMultiSub());
	//debug("FileName=%s"		, material.fileName.text());
	//debug("bitmapIndices:");
	//for(int i=0; i<material.textureIndices.length(); i++)
		//debug("%d, ", material.textureIndices[i]);

	return true;
}

bool MaxSkeletalAnimModelBuilder::parseAttributesBlock(AttributesBlock &attributesBlock, TiXmlNode *attributesNode)
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


bool MaxSkeletalAnimModelBuilder::parseMaterialUniformVariablesBlock(SkeletalAnimModel::VisualEffectInfo &visualEffectInfo, const String &name, const String &type, const String &values)
{
#if 0
	Vector<String> tokens;

	if(type=="bool")
	{
		if( Helper::parseDefaultValues(tokens, values.text() ) ) 
		{
			if(tokens.length()!=1)
			{
				return false;
			}

			UniformVariable<bool> &uniformVar = material.uniformVariablesBlock.boolUniformVariablesArray.uniformVariables.push();
			uniformVar.name = name;
			if(tokens[0]=="true")
				uniformVar.value = true;
			else
				uniformVar.value = false;
		}
		else
		{
			UniformVariable<bool> &uniformVar = material.uniformVariablesBlock.boolUniformVariablesArray.uniformVariables.push();
			uniformVar.name	= name;
			uniformVar.value = true;
		}
	}
	else if(type=="bool2")
	{
		if( Helper::parseDefaultValues(tokens, values.text() ) ) 
		{
			if(tokens.length()!=2)
			{
				return false;
			}

			UniformVariable<BVector2> &uniformVar = material.uniformVariablesBlock.bVector2UniformVariablesArray.uniformVariables.push();
			uniformVar.name = name;
			for(int i=0; i<tokens.length(); i++)
			{
				if(tokens[i]=="true")
					uniformVar.value[i] = 1;
				else
					uniformVar.value[i] = 0;
			}
		}
		else
		{
			UniformVariable<BVector2> &uniformVar = material.uniformVariablesBlock.bVector2UniformVariablesArray.uniformVariables.push();
			uniformVar.name = name;
			for(int i=0; i<tokens.length(); i++)
			{
				uniformVar.value[i] = true;
			}
		}
	}
	else if(type=="bool3")
	{
		if( Helper::parseDefaultValues(tokens, values.text() ) ) 
		{
			if(tokens.length()!=3)
			{
				return false;
			}

			UniformVariable<BVector3> &uniformVar = material.uniformVariablesBlock.bVector3UniformVariablesArray.uniformVariables.push();
			uniformVar.name = name;
			for(int i=0; i<tokens.length(); i++)
			{
				if(tokens[i]=="true")
					uniformVar.value[i] = 1;
				else
					uniformVar.value[i] = 0;
			}
		}
		else
		{
			UniformVariable<BVector3> &uniformVar = material.uniformVariablesBlock.bVector3UniformVariablesArray.uniformVariables.push();
			uniformVar.name = name;
			for(int i=0; i<tokens.length(); i++)
			{
				uniformVar.value[i] = 1;
			}
		}
	}
	else if(type=="bool4")
	{
		if( Helper::parseDefaultValues(tokens, values.text() ) ) 
		{
			if(tokens.length()!=4)
			{
				return false;
			}

			UniformVariable<BVector4> &uniformVar = material.uniformVariablesBlock.bVector4UniformVariablesArray.uniformVariables.push();
			uniformVar.name = name;
			for(int i=0; i<tokens.length(); i++)
			{
				if(tokens[i]=="true")
					uniformVar.value[i] = 1;
				else
					uniformVar.value[i] = 0;
			}
		}
		else
		{
			UniformVariable<BVector4> &uniformVar = material.uniformVariablesBlock.bVector4UniformVariablesArray.uniformVariables.push();
			uniformVar.name = name;
			for(int i=0; i<tokens.length(); i++)
			{
				uniformVar.value[i] = 1;
			}
		}
	}
	else if(type=="int")
	{
		if( Helper::parseDefaultValues(tokens, values.text() ) ) 
		{
			if(tokens.length()!=1)
			{
				return false;
			}

			UniformVariable<int> &uniformVar = material.uniformVariablesBlock.intUniformVariablesArray.uniformVariables.push();
			uniformVar.name	= name;
			uniformVar.value = atoi(tokens[0].text());
		}
		else
		{
			UniformVariable<int> &uniformVar = material.uniformVariablesBlock.intUniformVariablesArray.uniformVariables.push();
			uniformVar.name = name;
			uniformVar.value = 0;
		}
	}
	else if(type=="int2")
	{
		if( Helper::parseDefaultValues(tokens, values.text() ) ) 
		{
			if(tokens.length()!=2)
			{
				return false;
			}

			UniformVariable<IVector2> &uniformVar = material.uniformVariablesBlock.iVector2UniformVariablesArray.uniformVariables.push();
			uniformVar.name = name;
			for(int i=0; i<tokens.length(); i++)
			{
				uniformVar.value[i] = atoi(tokens[i].text());
			}
		}
		else
		{
			UniformVariable<IVector2> &uniformVar = material.uniformVariablesBlock.iVector2UniformVariablesArray.uniformVariables.push();
			uniformVar.name = name;
			for(int i=0; i<tokens.length(); i++)
			{
				uniformVar.value[i] = 0;
			}
		}
	}
	else if(type=="int3")
	{
		if( Helper::parseDefaultValues(tokens, values.text() ) ) 
		{
			if(tokens.length()!=3)
			{
				return false;
			}

			UniformVariable<IVector3> &uniformVar = material.uniformVariablesBlock.iVector3UniformVariablesArray.uniformVariables.push();
			uniformVar.name = name;
			for(int i=0; i<tokens.length(); i++)
			{
				uniformVar.value[i] = atoi(tokens[i].text());
			}
		}
		else
		{
			UniformVariable<IVector3> &uniformVar = material.uniformVariablesBlock.iVector3UniformVariablesArray.uniformVariables.push();
			uniformVar.name = name;
			for(int i=0; i<tokens.length(); i++)
			{
				uniformVar.value[i] = 0;
			}
		}
	}
	else if(type=="int4")
	{
		if( Helper::parseDefaultValues(tokens, values.text() ) ) 
		{
			if(tokens.length()!=4)
			{
				return false;
			}

			UniformVariable<IVector4> &uniformVar = material.uniformVariablesBlock.iVector4UniformVariablesArray.uniformVariables.push();
			uniformVar.name = name;
			for(int i=0; i<tokens.length(); i++)
			{
				uniformVar.value[i] = atoi(tokens[i].text());
			}
		}
		else
		{
			UniformVariable<IVector4> &uniformVar = material.uniformVariablesBlock.iVector4UniformVariablesArray.uniformVariables.push();
			uniformVar.name = name;
			for(int i=0; i<tokens.length(); i++)
			{
				uniformVar.value[i] = 0;
			}
		}
	}
	else if(type=="float")
	{
		if( Helper::parseDefaultValues(tokens, values.text() ) ) 
		{
			if(tokens.length()!=1)
			{
				return false;
			}

			UniformVariable<float> &uniformVar = material.uniformVariablesBlock.floatUniformVariablesArray.uniformVariables.push();
			uniformVar.name = name;
			for(int i=0; i<tokens.length(); i++)
			{
				uniformVar.value = atof(tokens[i].text());
			}
		}
		else
		{
			UniformVariable<float> &uniformVar = material.uniformVariablesBlock.floatUniformVariablesArray.uniformVariables.push();
			uniformVar.name = name;
			for(int i=0; i<tokens.length(); i++)
			{
				uniformVar.value = 0;
			}
		}
	}
	else if(type=="float2")
	{
		if( Helper::parseDefaultValues(tokens, values.text() ) ) 
		{
			if(tokens.length()!=2)
			{
				return false;
			}

			UniformVariable<Vector2> &uniformVar = material.uniformVariablesBlock.vector2UniformVariablesArray.uniformVariables.push();
			uniformVar.name = name;
			for(int i=0; i<tokens.length(); i++)
			{
				uniformVar.value[i] = atof(tokens[i].text());
			}
		}
		else
		{
			UniformVariable<Vector2> &uniformVar = material.uniformVariablesBlock.vector2UniformVariablesArray.uniformVariables.push();
			uniformVar.name = name;
			for(int i=0; i<tokens.length(); i++)
			{
				uniformVar.value[i] = 0;
			}
		}
	}
	else if(type=="float3")
	{
		if( Helper::parseDefaultValues(tokens, values.text() ) ) 
		{
			if(tokens.length()!=3)
			{
				return false;
			}

			UniformVariable<Vector3> &uniformVar = material.uniformVariablesBlock.vector3UniformVariablesArray.uniformVariables.push();
			uniformVar.name = name;
			for(int i=0; i<tokens.length(); i++)
			{
				uniformVar.value[i] = atof(tokens[i].text());
			}
		}
		else
		{
			UniformVariable<Vector3> &uniformVar = material.uniformVariablesBlock.vector3UniformVariablesArray.uniformVariables.push();
			uniformVar.name = name;
			for(int i=0; i<tokens.length(); i++)
			{
				uniformVar.value[i] = 0;
			}
		}
	}
	else if(type=="float4")
	{
		if( Helper::parseDefaultValues(tokens, values.text() ) ) 
		{
			if(tokens.length()!=4)
			{
				return false;
			}

			UniformVariable<Vector4> &uniformVar = material.uniformVariablesBlock.vector4UniformVariablesArray.uniformVariables.push();
			uniformVar.name = name;
			for(int i=0; i<tokens.length(); i++)
			{
				uniformVar.value[i] = atof(tokens[i].text());
			}
		}
		else
		{
			UniformVariable<Vector4> &uniformVar = material.uniformVariablesBlock.vector4UniformVariablesArray.uniformVariables.push();
			uniformVar.name = name;
			for(int i=0; i<tokens.length(); i++)
			{
				uniformVar.value[i] = 0;
			}
		}
	}
	if(type=="float2x2")
	{
		if( Helper::parseDefaultValues(tokens, values.text() ) ) 
		{
			if(tokens.length()!=4)
			{
				return false;
			}

			UniformVariable<Matrix2> &uniformVar = material.uniformVariablesBlock.matrix2UniformVariablesArray.uniformVariables.push();
			uniformVar.name = name;
			float *v = uniformVar.value;
			for(int i=0; i<tokens.length(); i++)
			{
				v[i] = atof(tokens[i].text());
			}
		}
		else
		{
			UniformVariable<Matrix2> &uniformVar = material.uniformVariablesBlock.matrix2UniformVariablesArray.uniformVariables.push();
			uniformVar.name = name;
			float *v = uniformVar.value;
			for(int i=0; i<tokens.length(); i++)
			{
				v[i] = 0;
			}
		}
	}
	else if(type=="float3x3")
	{
		if( Helper::parseDefaultValues(tokens, values.text() ) ) 
		{
			if(tokens.length()!=9)
			{
				return false;
			}

			UniformVariable<Matrix3> &uniformVar = material.uniformVariablesBlock.matrix3UniformVariablesArray.uniformVariables.push();
			uniformVar.name = name;
			float *v = uniformVar.value;
			for(int i=0; i<tokens.length(); i++)
			{
				v[i] = atof(tokens[i].text());
			}
		}
		else
		{
			UniformVariable<Matrix3> &uniformVar = material.uniformVariablesBlock.matrix3UniformVariablesArray.uniformVariables.push();
			uniformVar.name = name;
			float *v = uniformVar.value;
			for(int i=0; i<tokens.length(); i++)
			{
				v[i] = 0;
			}
		}
	}
	else if(type=="float4x4")
	{
		if( Helper::parseDefaultValues(tokens, values.text() ) ) 
		{
			if(tokens.length()!=16)
			{
				return false;
			}

			UniformVariable<Matrix4> &uniformVar = material.uniformVariablesBlock.matrix4UniformVariablesArray.uniformVariables.push();
			uniformVar.name = name;
			float *v = uniformVar.value;
			for(int i=0; i<tokens.length(); i++)
			{
				v[i] = atof(tokens[i].text());
			}
		}
		else
		{
			UniformVariable<Matrix4> &uniformVar = material.uniformVariablesBlock.matrix4UniformVariablesArray.uniformVariables.push();
			uniformVar.name = name;
			float *v = uniformVar.value;
			for(int i=0; i<tokens.length(); i++)
			{
				v[i] = 0;
			}
		}
	}
#endif
	return true;
}

bool MaxSkeletalAnimModelBuilder::buildNodes(SkeletalAnimModel::Data &skeletalModelData)
{
	//////////////////////////////////////////
	// count Nodes
	allocNodes(skeletalModelData);  
	resetTransformCaches(skeletalModelData); 

	int numBones			= 0;
	int numMeshes			= 0;

	//////////////////////////////////////////
	// build bones
	for(int i=0; i<nodes.length(); i++)
	{
		IGameNode *child = nodes[i];

		if(child->IsGroupOwner())
		{
			buildBone(skeletalModelData, skeletalModelData.bones[numBones], child, numBones);
			numBones++;
		}
		else
		{
			IGameObject			*obj  = child->GetIGameObject();
			IGameObject::MaxType	T = obj->GetMaxType();
			//if(obj->IsObjectXRef())
				//AddXMLAttribute(parent,_T("XRefObject"),_T("True"));

			switch(obj->GetIGameType())
			{
				case IGameObject::IGAME_MESH:
				{
					// dummy
					buildBone(skeletalModelData, skeletalModelData.bones[numBones], child, numBones);
					numBones++;
				}
				break;

				case IGameObject::IGAME_UNKNOWN:
				case IGameObject::IGAME_LIGHT:
				case IGameObject::IGAME_SPLINE:
				case IGameObject::IGAME_CAMERA:
				case IGameObject::IGAME_HELPER:
				case IGameObject::IGAME_BONE:
				case IGameObject::IGAME_IKCHAIN:
				case IGameObject::IGAME_XREF:
				default:
				{
					// dummy
					buildBone(skeletalModelData, skeletalModelData.bones[numBones], child, numBones);
					numBones++;
				}
				break;
			}

			child->ReleaseIGameObject();
		}
	}

	//////////////////////////////////////////
	// build mesh
	for(int i=0; i<nodes.length(); i++)
	{
		IGameNode *child = nodes[i];

		if(child->IsGroupOwner())
		{
		}
		else
		{
			IGameObject			*obj  = child->GetIGameObject();
			IGameObject::MaxType	T = obj->GetMaxType();
			//if(obj->IsObjectXRef())
				//AddXMLAttribute(parent,_T("XRefObject"),_T("True"));

			switch(obj->GetIGameType())
			{
				case IGameObject::IGAME_MESH:
				{
					// mesh
					IGameMesh *maxMesh = (IGameMesh*)obj;
					maxMesh->SetCreateOptimizedNormalList(); 
					if(maxMesh->InitializeData() && maxMesh->InitializeBinormalData() )
					{
						if( !buildMesh(skeletalModelData, skeletalModelData.meshes[numMeshes], child, maxMesh) )
							return false;

						//artbkg.meshes[numMeshes].maxNode = (void *)child;
						numMeshes++;
						//DumpMesh(gM,geomData);
					}
					else
					{
						return this->errorMessage("Cannot Generate Tangent Binormal data");
						//AddXMLAttribute(geomData,_T("Error"),_T("BadObject"));
					}
				}
				break;

				case IGameObject::IGAME_UNKNOWN:
				case IGameObject::IGAME_LIGHT:
				case IGameObject::IGAME_SPLINE:
				case IGameObject::IGAME_CAMERA:
				case IGameObject::IGAME_HELPER:
				case IGameObject::IGAME_BONE:
				case IGameObject::IGAME_IKCHAIN:
				case IGameObject::IGAME_XREF:
				default:
				break;
			}

			child->ReleaseIGameObject();
		}
	}

	/*
	for(int i=0; i<artbkg.meshes.length(); i++) 
	{
		IGameNode *maxNode			= (IGameNode *)artbkg.meshes[i].maxNode;
		IGameObject	*maxMesh		= (IGameMesh*)(maxNode->GetIGameObject());
		bool skinned = maxMesh->IsObjectSkinned();
		
		IGameSkin *skin	= maxMesh->GetIGameSkin();
		SkeletalAnimModel::Mesh &mesh = artbkg.meshes[i];
		if(skin)
		{
			for(int j=0; j<skin->GetTotalBoneCount(); j++)
			{
				int localBoneIndex	= j;
				int globalBoneIndex = getNodeIdx(skin->GetIGameBone(j));

				debug("local  bones name = %s", skin->GetIGameBone(localBoneIndex)->GetName()  );
				debug("global bones name = %s", artbkg.bones[globalBoneIndex].name.text() );
			}

			for(int j=0; j<mesh.globalBoneIndices.length(); j++)
			{
				int localBoneIndex  = j;
				int globalBoneIndex = mesh.globalBoneIndices[j];
				
				debug("local  bones name = %s", skin->GetIGameBone(localBoneIndex)->GetName()  );
				debug("global bones name = %s", artbkg.bones[globalBoneIndex].name.text() );
			}
		}

		maxNode->ReleaseIGameObject();
	}
	*/

	return true;
}

void MaxSkeletalAnimModelBuilder::allocNodes(SkeletalAnimModel::Data &skeletalModelData)
{
	int numBones = 0;
	int numMeshes = 0;

	for(int i=0; i<nodes.length(); i++)
	{
		IGameNode *child = nodes[i];

		if(child->IsGroupOwner())
		{
			numBones++;
		}
		else
		{
			IGameObject			*obj  = child->GetIGameObject();
			IGameObject::MaxType	T = obj->GetMaxType();

			switch(obj->GetIGameType())
			{
				case IGameObject::IGAME_MESH:
				{
					numBones++;
				}
				{
					numMeshes++;
				}
				break;

				case IGameObject::IGAME_UNKNOWN:
				case IGameObject::IGAME_LIGHT:
				case IGameObject::IGAME_SPLINE:
				case IGameObject::IGAME_CAMERA:
				case IGameObject::IGAME_HELPER:
				case IGameObject::IGAME_BONE:
				case IGameObject::IGAME_IKCHAIN:
				case IGameObject::IGAME_XREF:
				default:
				{
					numBones++;
				}
				break;
			}

			child->ReleaseIGameObject();
		}
	}

	// resize
	skeletalModelData.bones.resize(numBones);
	skeletalModelData.meshes.resize(numMeshes);
}

void MaxSkeletalAnimModelBuilder::resetTransformCaches(SkeletalAnimModel::Data &skeletalModelData)
{
	bonesGlobalMat.resize(skeletalModelData.bones.length());
	bonesGlobalMatValid.resize(skeletalModelData.bones.length());
	for(int i=0; i<bonesGlobalMatValid.length(); i++)
		bonesGlobalMatValid[i] = false;
}

bool MaxSkeletalAnimModelBuilder::buildNode(SkeletalAnimModel::Data &skeletalModelData, SkeletalAnimModel::Node &node, IGameNode *iGameNode)
{
	node.name				= fixupName( iGameNode->GetName() );
	node.parentIdx			= nodes.search( iGameNode->GetNodeParent() );
	node.userData			= ""; 

	buildNodePositionRotationScale(node.position, node.rotation, node.scale, iGameNode);
	//buildNodePositionAnim(node.posAnim, iGameNode, startFrame, endFrame, step, meterPerUnits);
	//buildNodeRotationAnim(node.rotationAnim, iGameNode, startFrame, endFrame, step);
	//buildNodeScaleAnim(node.scaleAnim, iGameNode, startFrame, endFrame, step);

	return true;
}

void MaxSkeletalAnimModelBuilder::buildNodePositionRotationScale(Vector3 &position, Quaternion &quatenion, Vector3 &scale, IGameNode *iGameNode)
{
	Helper::convertMatrixToVector10(position, quatenion, scale, iGameNode->GetLocalTM( frame2Tick(0) ), meterPerUnits);
}

Vector3 MaxSkeletalAnimModelBuilder::scaleVector(const Vector3 &in)
{
	Vector3 out = in;

	out[0] *= meterPerUnits;
	out[1] *= meterPerUnits;
	out[2] *= meterPerUnits; 

	return out;
}

Matrix4 MaxSkeletalAnimModelBuilder::scaleMatrix(const Matrix4 &in)
{
	Matrix4 out = in;

	out[0][3] *= meterPerUnits;
	out[1][3] *= meterPerUnits;
	out[2][3] *= meterPerUnits;

	return out;
}

bool MaxSkeletalAnimModelBuilder::buildBone(SkeletalAnimModel::Data &skeletalModelData, SkeletalAnimModel::Bone &bone, IGameNode *iGameNode, int currentBoneIdx)
{
	buildNode(skeletalModelData, bone, iGameNode);

	bone.tBindGlobalTransform		= Matrix4::IDENTITY;
	bone.tBindGlobalTransformInv	= Matrix4::IDENTITY;
	bone.t0GlobalTransform			= getGlobalTransform(skeletalModelData.bones, currentBoneIdx);
	bone.t0GlobalTransformInv		= bone.t0GlobalTransform.Inverse();
	
	return true;
}

bool MaxSkeletalAnimModelBuilder::dumpSkin(IGameSkin *skin)
{
	// Get the Skinning type.
	IGameSkin::SkinType   skintype = skin->GetSkinType();

	// Get the number of bones used by the skinning modifiers.
	int totalBoneCount = skin->GetTotalBoneCount();
 	
	// Receive the total number of bones used by the skinning system - this will include bones that are not assigned to any vertex.
	int totalSkinBoneCount = skin->GetTotalSkinBoneCount();

	// Get the original TM for the node with skin.
	GMatrix initSkinMat;
	skin->GetInitSkinTM(initSkinMat);

	debug("Binded-Time Node(with Skin) Tranlation: [%f %f %f]", initSkinMat[3][0], initSkinMat[3][1], initSkinMat[3][2]);

	// Returns the mesh before the skin modifier was added.
	IGameMesh *mesh = skin->GetInitialPose();
	for(int i=0; i<mesh->GetNumberOfVerts(); i++)
	{ 
		Point3 p;
		mesh->GetVertex(i, p);

		debug("Binded-Time Vertices %d: [%f %f %f]", i, p.x, p.y, p.z);
	}
	  
	for(int i=0; i<skin->GetTotalSkinBoneCount(); i++)
	{
		IGameNode *iGameBone = skin->GetIGameBone(i);

		bool rval;
		GMatrix initBoneMat;
		rval = skin->GetInitBoneTM(iGameBone, initBoneMat);

		int	boneIndex = skin->GetBoneIndex(iGameBone);

		debug("%d: %s: boneIndex=%d: [%f %f %f]", i, iGameBone->GetName(), boneIndex, initBoneMat[3][0], initBoneMat[3][1], initBoneMat[3][2]);
	}

	// Get the numbers of vertices effected by this instance of the modifier.
	int numOfSkinnedVerts			= skin->GetNumOfSkinnedVerts();

	for(int i=0; i<numOfSkinnedVerts; i++)
	{
 		// Get Vertex Type.
		IGameSkin::VertexType type = skin->GetVertexType(i); // IGAME_RIGID, IGAME_RIGID_BLENDED, IGAME_UNKNOWN

		// Get the numbers of bones effecting the vertex.
		int numberOfBones				= skin->GetNumberOfBones(i);

		for(int j=0; j<numberOfBones; j++)
		{
			// Get the weight for the bone and vertex index passed in.
			float weight			= skin->GetWeight(i, j);

			// Get the IGameNode equivalent of the bone effecting the vertex.
			IGameNode *iGameBone	= skin->GetIGameBone(i, j);

			// Get the bone TM when skin was added.
			bool rval;
			GMatrix initBoneMat;
			rval = skin->GetInitBoneTM(iGameBone, initBoneMat);

			// use the usedList to define if you want to the search all the bones or just the bones actually effecting a vertex
			int	boneIndex = skin->GetBoneIndex(iGameBone);
	
			// use the usedList to define if you want to the search all the bones or just the bones actually effecting a vertex
			IGameNode *test = skin->GetIGameBone(boneIndex);

			debug("Vertex: %d is binded to %s (index=%d) with weight %f", i, iGameBone->GetName(), boneIndex, weight );
		}
	}

	return true;
}

bool MaxSkeletalAnimModelBuilder::dumpModifier(IGameModifier *modifier)
{
	return true;
}

bool MaxSkeletalAnimModelBuilder::buildMesh(SkeletalAnimModel::Data &skeletalModelData, SkeletalAnimModel::Mesh &mesh, 
									    IGameNode *iGameNode, IGameMesh *maxMeshObj)
{
	/////////////////////////////////////////////////
	//
	IGameMesh *bindPoseMeshObj = 0;

	/////////////////////////////////////////////
	// prepare Matrices
	GMatrix offsetTM = getOffsetMatrix(iGameNode);
	GMatrix initSkinTM;

	///////////////////////////////////////////////////////////////////////
	// calculate Bind Time Bone Transform
	IGameSkin *skin	= maxMeshObj->GetIGameSkin();
	if(skin)
	{
		// output mesh is skinned
		bindPoseMeshObj = skin->GetInitialPose(); 

		////////////////////////////////////
		// fill global bones map
		int usedBoneCount;
		usedBoneCount = skin->GetTotalBoneCount();		// Get the number of bones used by the skinning modifiers.
		usedBoneCount = skin->GetTotalSkinBoneCount();	// Receive the total number of bones used by the skinning system - this will include bones that are not assigned to any vertex.

		if(usedBoneCount>this->maxNumBonesPerPatch)
			return errorMessage("Maximun %d of bones are allowed per Triangle Patch, please check %s", maxNumBonesPerPatch, iGameNode->GetName());

		// dumpSkin(skin);
		mesh.globalBoneIndices.resize(usedBoneCount);
		for(int i=0; i<mesh.globalBoneIndices.length(); i++)
		{
			IGameNode *iGameBone = skin->GetIGameBone(i);

			int	localBoneIndex		= skin->GetBoneIndex(iGameBone);
			int globalBoneIndex		= getNodeIdx(iGameBone);
			mesh.globalBoneIndices[localBoneIndex] = globalBoneIndex;

			//! Get the original TM for the node with skin. 
			//! This provides access to the intial node TM when the skin modifier was applied.
			//  param &intMat  The matrix to receive the intial TM
			skin->GetInitSkinTM(initSkinTM);
			 
			// Get the bone TM when skin was added.
			bool rval;
			GMatrix initBoneMat;
			rval = skin->GetInitBoneTM(iGameBone, initBoneMat);

			// skeletalModelData.bones[globalBoneIndex].hasBindTransform			= true;
			skeletalModelData.bones[globalBoneIndex].tBindGlobalTransform.Set(initBoneMat[0][0], initBoneMat[1][0], initBoneMat[2][0], initBoneMat[3][0], 
																			  initBoneMat[0][1], initBoneMat[1][1], initBoneMat[2][1], initBoneMat[3][1], 
																			  initBoneMat[0][2], initBoneMat[1][2], initBoneMat[2][2], initBoneMat[3][2], 
																			  initBoneMat[0][3], initBoneMat[1][3], initBoneMat[2][3], initBoneMat[3][3]);

			skeletalModelData.bones[globalBoneIndex].tBindGlobalTransform = scaleMatrix(skeletalModelData.bones[globalBoneIndex].tBindGlobalTransform);

			skeletalModelData.bones[globalBoneIndex].tBindGlobalTransformInv	= skeletalModelData.bones[globalBoneIndex].tBindGlobalTransform.Inverse();
		}
	}


	/////////////////////////////////////////////
	mesh.name				= fixupName( iGameNode->GetName() );
	mesh.attachedNodeIdx	= nodes.search( iGameNode );
	mesh.userData			= "";
	
	/////////////////////////////////////////////
	// build up subMatMeshes
	Tab<int> activeMapChannelNums = maxMeshObj->GetActiveMapChannelNum();

	Tab<int> matids = maxMeshObj->GetActiveMatIDs();
	mesh.patches.resize(matids.Count());
	for(int i=0; i<mesh.patches.length(); i++)
	{
		//////////////////////////////////////////////////////////////////
		// get Faces
		Tab<FaceEx*> faces = maxMeshObj->GetFacesFromMatID(matids[i]); 
		assert(faces.Count()!=0 && "Exception: no faces");

		//////////////////////////////////////////////////////////////////
		// get subMaterialIdx
		IGameMaterial *faceMat = maxMeshObj->GetMaterialFromFace(faces[0]);
		mesh.patches[i].visualEffectInfoIdx = getVisualEffectInfoIdx(faceMat);
		if(mesh.patches[i].visualEffectInfoIdx==-1)
			return errorMessage("Invalid material is set, check Mesh \"%s\"", iGameNode->GetName() );

		SkeletalAnimModel::VisualEffectInfo &visualEffectInfo = skeletalModelData.visualEffectInfos[mesh.patches[i].visualEffectInfoIdx];

		//////////////////////////////////////////////////////////////////
		// get Flat and Raw Index from Max
		Vector<MAXRawIndex> maxRawIndices;
		if( !getRawIndices(maxRawIndices, iGameNode, maxMeshObj, bindPoseMeshObj, faces, visualEffectInfo) )
			return false;

		//////////////////////////////////////////////////////////////////
		// get Vertex Offsets and Stride, Optimized the Vertex
		int stride;
		Vector<int> offsets;
		Vector<int> sizes;
		Vector<char> vbBuffer;
		Vector<char> ibBuffer;
		int numOptimizedVertices; 
		int numOptimizedIndices;
		if( !optimizeVBIB(vbBuffer, ibBuffer, 
						  numOptimizedVertices, numOptimizedIndices, 
						  stride, offsets, sizes,
						  maxRawIndices, 
						  iGameNode, maxMeshObj, bindPoseMeshObj,
						  offsetTM, initSkinTM,
						  visualEffectInfo) ) 
			return false;

		//////////////////////////////////////////////////////////////////
		// fill vb and ib
		mesh.patches[i].vb.construct(visualEffectInfo.attributesBlock, numOptimizedVertices, stride);
		memcpy(&mesh.patches[i].vb.buffer[0], &vbBuffer[0], mesh.patches[i].vb.buffer.length());

		mesh.patches[i].ib.construct(numOptimizedIndices, sizeof(unsigned short));
		memcpy(&mesh.patches[i].ib.buffer[0], &ibBuffer[0], mesh.patches[i].ib.buffer.length());
	}

	return true;
}

bool MaxSkeletalAnimModelBuilder::getRawIndices(Vector<MAXRawIndex> &maxRawIndices, 
	                                    IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, const Tab<FaceEx*> &faces, 
										const SkeletalAnimModel::VisualEffectInfo &visualEffectInfo)
{
	maxRawIndices.resize(faces.Count()*3);
	MAXRawIndex *maxRawIndex = &maxRawIndices[0];

	for(int i=0; i<faces.Count(); i++) 
	{
		int face = faces[i]->meshFaceIndex;
	
		for(int j=0; j<3; j++)
		{
			memset(maxRawIndex, 0, sizeof(MAXRawIndex));
			for(int k=0; k<visualEffectInfo.attributesBlock.vertexStreamSources.length(); k++) 
			{
				int vsSource = visualEffectInfo.attributesBlock.vertexStreamSources[k].getValue();
				if( !indexGetters[vsSource](maxRawIndex->indices[k], maxNode, maxMeshObj, bindPoseMeshObj, face, j) )
					return errorMessage("Invalid Stream Source %d", vsSource);
			}

			maxRawIndex++;
		}
	}

	return true;
}

bool MaxSkeletalAnimModelBuilder::optimizeVBIB(Vector<char> &vbBuffer, Vector<char> &ibBuffer, 
									       int &numOptimizedVertices, int &numOptimizedIndices, 
									       int &stride, Vector<int> &offsets, Vector<int> &sizes,
									       const Vector<MAXRawIndex> &maxRawIndices, 
									       IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, 
									       const GMatrix &offsetTM, const GMatrix &initSkinTM,
									       const SkeletalAnimModel::VisualEffectInfo &visualEffectInfo)
{
	Tab<int> activeMapChannelNums = maxMeshObj->GetActiveMapChannelNum();

	/////////////////////////////////////////////////////////////////////////////
	VertexIndexOptimizer vertexIndexOptimizer;
	
	int maxIndex = 0;
	ibBuffer.resize(maxRawIndices.length() * sizeof(unsigned short));
	unsigned short *ibBufPtr = (unsigned short *)(&ibBuffer[0]);
	for(int i=0; i<maxRawIndices.length(); i++)
	{
		*ibBufPtr = vertexIndexOptimizer.add(maxRawIndices[i]);
		if(maxIndex<*ibBufPtr)
			maxIndex = *ibBufPtr;

		ibBufPtr++;
	}

	/////////////////////////////////////////////////////////////////////////////
	vertexIndexOptimizer.build();

	/////////////////////////////////////////////////////////////////////////////
	getStrideOffset(stride, offsets, sizes, visualEffectInfo.attributesBlock.vertexFormats);

	/////////////////////////////////////////////////////////////////////////////
	vbBuffer.resize(vertexIndexOptimizer.getNumOptimzedIndices() * stride);
	char *vbBufPtr =(char *)(&vbBuffer[0]); 
	for(int i=0; i<vertexIndexOptimizer.getNumOptimzedIndices(); i++)
	{
		const MAXRawIndex &gameRawIndex = vertexIndexOptimizer.getOptimzedIndex(i);

		for(int j=0; j<visualEffectInfo.attributesBlock.vertexStreamSources.length(); j++) 
		{
			int vsSource = visualEffectInfo.attributesBlock.vertexStreamSources[j].getValue();
			if( !vertexGetters[vsSource](vbBufPtr, sizes[j], offsetTM, initSkinTM, maxNode, maxMeshObj, bindPoseMeshObj, gameRawIndex.indices[j]) )
				return errorMessage("Invalid Stream Source %d", vsSource);
			
			vbBufPtr += sizes[j];
		}
	}

	/////////////////////////////////////////////////////////////////////////////
	numOptimizedIndices  = maxRawIndices.length();
	numOptimizedVertices = vertexIndexOptimizer.getNumOptimzedIndices();

	return true;
}

void MaxSkeletalAnimModelBuilder::getStrideOffset(int &stride, 
									      Vector<int> &offsets, 
									      Vector<int> &sizes, 
									      const Vector<GXVertexFormat> &vertexFormat)
{
	offsets.resize(vertexFormat.length());
	sizes.resize(vertexFormat.length());

	int offset = 0;
	for(int i=0; i<offsets.length(); i++)
	{
		sizes[i] = vertexFormat[i].getSize();

		offsets[i] = offset;
		
		offset += sizes[i];
	}

	stride = offset;
}

const Matrix4 &MaxSkeletalAnimModelBuilder::getGlobalTransform(Vector<SkeletalAnimModel::Bone> bones, int currentBoneIdx)
{
	if(!bonesGlobalMatValid[currentBoneIdx])
	{
		int parentBoneIdx = bones[currentBoneIdx].getParentIdx();
		if(parentBoneIdx==-1) // no parent global = local
		{
			Matrix4 localMatrix;
			bones[currentBoneIdx].getLocalTransform(localMatrix);

			bonesGlobalMat[currentBoneIdx] = localMatrix;
			
			bonesGlobalMatValid[currentBoneIdx] = true;
		}
		else
		{
			Matrix4 localMatrix;
			bones[currentBoneIdx].getLocalTransform(localMatrix);

			bonesGlobalMat[currentBoneIdx] = bonesGlobalMat[parentBoneIdx] * localMatrix;

			bonesGlobalMatValid[currentBoneIdx] = true;
		}
	}

	return bonesGlobalMat[currentBoneIdx];
}

bool MaxSkeletalAnimModelBuilder::buildBoneAnimations(SkeletalAnimModel::Data &skeletalModelData)
{
	skeletalModelData.animation.startframe	= startFrame;
	skeletalModelData.animation.endframe	= endFrame;
	skeletalModelData.animation.fps			= fps;
	
	skeletalModelData.animation.boneAnimations.resize(nodes.length());
	for(int i=0; i<nodes.length(); i++)
	{
		SkeletalAnimModel::BoneAnimation &boneAnim = skeletalModelData.animation.boneAnimations[i];

		buildBoneAnimation(boneAnim, skeletalModelData.bones[i], nodes[i]);
	}

	return true;
}

void MaxSkeletalAnimModelBuilder::buildBoneAnimation(SkeletalAnimModel::BoneAnimation &boneAnimation, SkeletalAnimModel::Bone &bone, IGameNode *maxNode)
{
	Vector3 t;
	Quaternion q;
	Vector3 k;
	
	boneAnimation.name		= bone.name;
	boneAnimation.parentIdx = bone.parentIdx;

	int numSamples = (endFrame - startFrame) / framePerKey + 1;
	
	boneAnimation.positions.resize(numSamples);
	boneAnimation.rotations.resize(numSamples);
	boneAnimation.scales.resize(numSamples);
	for(int i=0; i<numSamples; i++)
	{
		Helper::convertMatrixToVector10(t, q, k, maxNode->GetLocalTM(frame2Tick(startFrame+i*framePerKey)), meterPerUnits);

		boneAnimation.positions[i]	= t;
		boneAnimation.rotations[i]	= q;
		boneAnimation.scales[i]		= k;
	};

	/*
	EpicForce::Quaternion temp;
	for(int i=0; i<boneAnimation.rotations.length(); i++)
	{
		if(i!=0 && temp.Dot(boneAnimation.rotations[i])<0)
			boneAnimation.rotations[i] = -boneAnimation.rotations[i];

		temp = boneAnimation.rotations[i];
	};
	*/

	for(int i=0; i<boneAnimation.rotations.length(); i++)
	{
		Quaternion q = boneAnimation.rotations[i];
		Vector3 v(q.X(), q.Y(), q.Z());
		if(v.Dot(Vector3::UNIT_Y)<0)
			boneAnimation.rotations[i] = -boneAnimation.rotations[i];
	};
	
	boneAnimation.posKeyInterval   = framePerKey;
	boneAnimation.rotKeyInterval   = framePerKey;
	boneAnimation.scaleKeyInterval = framePerKey;
}


///////////////////////////////////////////////////////////////////
MaxSkeletalAnimModelBuilder::IndexGetter MaxSkeletalAnimModelBuilder::indexGetters[] =
{
	getPosition0Index, getPosition0Index, getPosition0Index, getPosition0Index, 
	getNormalIndex   ,	
	getColor0Index   , getColor0Index   ,
	getTexCoord0Index, getTexCoord1Index, getTexCoord2Index, getTexCoord3Index,
	getTexCoord4Index, getTexCoord5Index, getTexCoord6Index, getTexCoord7Index,
	getTangent0Index , getBinormal0Index,
	getBone1Index	 ,
	getBone2Index	 , getBone2WeightIndex,
	getBone4Index	 , getBone4WeightIndex,
};

MaxSkeletalAnimModelBuilder::VertexGetter MaxSkeletalAnimModelBuilder::vertexGetters[] =
{
	getPosition0, getPosition0, getPosition0, getPosition0, 
	getNormal   ,	
	getColor0   , getColor0   ,
	getTexCoord0, getTexCoord1, getTexCoord2, getTexCoord3,
	getTexCoord4, getTexCoord5,	getTexCoord6, getTexCoord7,
	getTangent0 , getBinormal0,
	getBone1IDXs, 
	getBone2IDXs, getBone2Weights, 
	getBone4IDXs, getBone4Weights, 
};

bool MaxSkeletalAnimModelBuilder::getPosition0Index(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner)
{
	if(maxMeshObj->GetNumberOfVerts()!=0)
	{
		index = maxMeshObj->GetFaceVertex(faceIndex, corner);

		return true;
	}
	else
	{
		index = -1;

		return false;
	}
}

bool MaxSkeletalAnimModelBuilder::getNormalIndex(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner)
{
	if(maxMeshObj->GetNumberOfNormals()!=0)
	{
		index = maxMeshObj->GetFaceVertexNormal(faceIndex, corner);

		return true;
	}
	else
	{
		index = -1;

		return false;
	}
}

bool MaxSkeletalAnimModelBuilder::getColor0Index(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner)
{
	if(maxMeshObj->GetNumberOfMapVerts(0)!=0)
	{
		index = maxMeshObj->GetFaceTextureVertex(faceIndex, corner, 0);

		return true;
	}
	else
	{
		index = -1;

		return false;
	}
}

bool MaxSkeletalAnimModelBuilder::getTexCoord0Index(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner)
{
	if(maxMeshObj->GetNumberOfMapVerts(0+1)!=0)
	{
		index = maxMeshObj->GetFaceTextureVertex(faceIndex, corner, 0+1);

		return true;
	}
	else
	{
		index = -1;

		return false;
	}
}

bool MaxSkeletalAnimModelBuilder::getTexCoord1Index(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner)
{
	if(maxMeshObj->GetNumberOfMapVerts(1+1)!=0)
	{
		index = maxMeshObj->GetFaceTextureVertex(faceIndex, corner, 1+1);

		return true;
	}
	else
	{
		index = -1;

		return false;
	}
}

bool MaxSkeletalAnimModelBuilder::getTexCoord2Index(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner)
{
	if(maxMeshObj->GetNumberOfMapVerts(2+1)!=0)
	{
		index = maxMeshObj->GetFaceTextureVertex(faceIndex, corner, 2+1);

		return true;
	}
	else
	{
		index = -1;

		return false;
	}
}

bool MaxSkeletalAnimModelBuilder::getTexCoord3Index(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner)
{
	if(maxMeshObj->GetNumberOfMapVerts(3+1)!=0)
	{
		index = maxMeshObj->GetFaceTextureVertex(faceIndex, corner, 3+1);

		return true;
	}
	else
	{
		index = -1;

		return false;
	}
}

bool MaxSkeletalAnimModelBuilder::getTexCoord4Index(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner)
{
	if(maxMeshObj->GetNumberOfMapVerts(4+1)!=0)
	{
		index = maxMeshObj->GetFaceTextureVertex(faceIndex, corner, 4+1);

		return true;
	}
	else
	{
		index = -1;

		return false;
	}
}

bool MaxSkeletalAnimModelBuilder::getTexCoord5Index(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner)
{
	if(maxMeshObj->GetNumberOfMapVerts(5+1)!=0)
	{
		index = maxMeshObj->GetFaceTextureVertex(faceIndex, corner, 5+1);

		return true;
	}
	else
	{
		index = -1;

		return false;
	}
}

bool MaxSkeletalAnimModelBuilder::getTexCoord6Index(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner)
{
	if(maxMeshObj->GetNumberOfMapVerts(6+1)!=0)
	{
		index = maxMeshObj->GetFaceTextureVertex(faceIndex, corner, 6+1);

		return true;
	}
	else
	{
		index = -1;

		return false;
	}
}

bool MaxSkeletalAnimModelBuilder::getTexCoord7Index(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner)
{
	if(maxMeshObj->GetNumberOfMapVerts(7+1)!=0)
	{
		index = maxMeshObj->GetFaceTextureVertex(faceIndex, corner, 7+1);

		return true;
	}
	else
	{
		index = -1;

		return false;
	}
}

bool MaxSkeletalAnimModelBuilder::getTangent0Index(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner)
{
	if(maxMeshObj->GetNumberOfTangents(0+1)!=0)
	{
		index = maxMeshObj->GetFaceVertexTangentBinormal(faceIndex, corner, 0+1);

		return true;
	}
	else
	{
		index = -1;

		return false;
	}
}

bool MaxSkeletalAnimModelBuilder::getBinormal0Index(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner)
{
	if(maxMeshObj->GetNumberOfBinormals(0+1)!=0)
	{
		index = maxMeshObj->GetFaceVertexTangentBinormal(faceIndex, corner, 0+1);

		return true;
	}
	else
	{
		index = -1;

		return false;
	}
}

bool MaxSkeletalAnimModelBuilder::getBone1Index(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner)
{
	if( !maxMeshObj->IsObjectSkinned() )
		return MaxSkeletalAnimModelBuilder::errorMessage("The Mesh %s is attached to a 1-Blend Shader.\n But, it has no Skin Modifier attached.\n", maxNode->GetName());

	if(maxMeshObj->GetNumberOfVerts()!=0)
	{
		index = maxMeshObj->GetFaceVertex(faceIndex, corner);

		return true;
	}
	else
	{
		index = -1;

		return false;
	}
}

bool MaxSkeletalAnimModelBuilder::getBone2Index(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner)
{
	if( !maxMeshObj->IsObjectSkinned() )
		return MaxSkeletalAnimModelBuilder::errorMessage("The Mesh %s is attached to a 2-Blend Shader.\n But, it has no Skin Modifier attached.\n", maxNode->GetName());

	if(maxMeshObj->GetNumberOfVerts()!=0)
	{
		index = maxMeshObj->GetFaceVertex(faceIndex, corner);

		return true;
	}
	else
	{
		index = -1;

		return false;
	}
}

bool MaxSkeletalAnimModelBuilder::getBone2WeightIndex(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner)
{
	if( !maxMeshObj->IsObjectSkinned() )
		return MaxSkeletalAnimModelBuilder::errorMessage("The Mesh %s is attached to a 2-Blend Shader.\n But, it has no Skin Modifier attached.\n", maxNode->GetName());

	if(maxMeshObj->GetNumberOfVerts()!=0)
	{
		index = maxMeshObj->GetFaceVertex(faceIndex, corner);

		return true;
	}
	else
	{
		index = -1;

		return false;
	}
}

bool MaxSkeletalAnimModelBuilder::getBone4Index(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner)
{
	if( !maxMeshObj->IsObjectSkinned() )
		return MaxSkeletalAnimModelBuilder::errorMessage("The Mesh %s is attached to a 4-Blend Shader.\n But, it has no Skin Modifier attached.\n", maxNode->GetName());

	if(maxMeshObj->GetNumberOfVerts()!=0)
	{
		index = maxMeshObj->GetFaceVertex(faceIndex, corner);

		return true;
	}
	else
	{
		index = -1;

		return false;
	}
}

bool MaxSkeletalAnimModelBuilder::getBone4WeightIndex(int &index, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int faceIndex, int corner)
{
	if( !maxMeshObj->IsObjectSkinned() )
		return MaxSkeletalAnimModelBuilder::errorMessage("The Mesh %s is attached to a 4-Blend Shader.\n But, it has no Skin Modifier attached.\n", maxNode->GetName());

	if(maxMeshObj->GetNumberOfVerts()!=0)
	{
		index = maxMeshObj->GetFaceVertex(faceIndex, corner);

		return true;
	}
	else
	{
		index = -1;

		return false;
	}
}

///////////////////////////////////////////////////////////////////
bool MaxSkeletalAnimModelBuilder::getPosition0(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index)
{
	if(maxMeshObj->IsObjectSkinned())
	{
		assert(bindPoseMeshObj);
		Point3 p;

		bool rval = bindPoseMeshObj->GetVertex(index, p, true);	// get bind pose vertex at object space
		p = p * initSkinTM;										// transform to world space

		Vector3 sp;
		sp[0] = p.x;
		sp[1] = p.y;
		sp[2] = p.z;
		sp = MaxSkeletalAnimModelBuilder::scaleVector(sp);

		if(rval)
			memcpy(buffer, &sp, size);
		 
		char buffer[1024];
		sprintf(buffer, "%d, %f %f %f\n", index, sp[0], sp[1], sp[2]);
		OutputDebugString(buffer); 

		return rval;
	}
	else
	{
		Point3 p;

		bool rval = maxMeshObj->GetVertex(index, p, true);	// get t0 vertex at object space
		p = p * offsetTM;									// transform to local space

		Vector3 sp;
		sp[0] = p.x;
		sp[1] = p.y;
		sp[2] = p.z;
		sp = MaxSkeletalAnimModelBuilder::scaleVector(sp);

		if(rval)
			memcpy(buffer, &sp, size);

		char buffer[1024];
		sprintf(buffer, "%d, %f %f %f\n", index, sp[0], sp[1], sp[2]);
		OutputDebugString(buffer); 

		return rval;
	}
}

bool MaxSkeletalAnimModelBuilder::getNormal(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index)
{
	if(maxMeshObj->IsObjectSkinned())
	{
		assert(bindPoseMeshObj);
		Point3 p;

		bool rval = bindPoseMeshObj->GetNormal(index, p, true); // get bind pose vertex at object space
		p = directionTransform(p, initSkinTM);
		p.Normalize();

		if(rval)
			memcpy(buffer, &p, size);

		return rval;
	}
	else
	{
		Point3 p;

		bool rval = maxMeshObj->GetNormal(index, p, true);	// get t0 vertex at object space
		p = directionTransform(p, offsetTM);
		p.Normalize();

		if(rval)
			memcpy(buffer, &p, size);

		return rval;
	}
}

bool MaxSkeletalAnimModelBuilder::getColor0(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index)
{
	Point3 p;

	bool rval = maxMeshObj->GetMapVertex(0, index, p);
	if(rval)
		memcpy(buffer, &p, size);

	return rval;
}

bool MaxSkeletalAnimModelBuilder::getTexCoord0(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index)
{
	Point3 p;

	bool rval = maxMeshObj->GetMapVertex(0+1, index, p);
	p.y = 1.0 - p.y;
	if(rval)
		memcpy(buffer, &p, size);

	return rval;
}

bool MaxSkeletalAnimModelBuilder::getTexCoord1(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index)
{
	Point3 p;

	bool rval = maxMeshObj->GetMapVertex(1+1, index, p);
	p.y = 1.0 - p.y;
	if(rval)
		memcpy(buffer, &p, size);

	return rval;
}

bool MaxSkeletalAnimModelBuilder::getTexCoord2(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index)
{
	Point3 p;

	bool rval = maxMeshObj->GetMapVertex(2+1, index, p);
	p.y = 1.0 - p.y;
	if(rval)
		memcpy(buffer, &p, size);

	return rval;
}

bool MaxSkeletalAnimModelBuilder::getTexCoord3(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index)
{
	Point3 p;

	bool rval = maxMeshObj->GetMapVertex(3+1, index, p);
	p.y = 1.0 - p.y;
	if(rval)
		memcpy(buffer, &p, size);

	return rval;
}

bool MaxSkeletalAnimModelBuilder::getTexCoord4(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index)
{
	Point3 p;

	bool rval = maxMeshObj->GetMapVertex(4+1, index, p);
	p.y = 1.0 - p.y;
	if(rval)
		memcpy(buffer, &p, size);

	return rval;
}

bool MaxSkeletalAnimModelBuilder::getTexCoord5(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index)
{
	Point3 p;

	bool rval = maxMeshObj->GetMapVertex(5+1, index, p);
	p.y = 1.0 - p.y;
	if(rval)
		memcpy(buffer, &p, size);

	return rval;
}

bool MaxSkeletalAnimModelBuilder::getTexCoord6(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index)
{
	Point3 p;

	bool rval = maxMeshObj->GetMapVertex(6+1, index, p);
	p.y = 1.0 - p.y;
	if(rval)
		memcpy(buffer, &p, size);

	return rval;
}

bool MaxSkeletalAnimModelBuilder::getTexCoord7(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index)
{
	Point3 p;

	bool rval = maxMeshObj->GetMapVertex(7+1, index, p);
	p.y = 1.0 - p.y;
	if(rval)
		memcpy(buffer, &p, size);

	return rval;
}

bool MaxSkeletalAnimModelBuilder::getTangent0(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index)
{
	Point3 p;

	bool rval = maxMeshObj->GetTangent(index, p, 0+1);
	if(rval)
		memcpy(buffer, &p, size);

	return rval;
}

bool MaxSkeletalAnimModelBuilder::getBinormal0(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index)
{
	Point3 p;

	bool rval = maxMeshObj->GetBinormal(index, p, 0+1);
	if(rval)
		memcpy(buffer, &p, size);

	return rval;
}

bool MaxSkeletalAnimModelBuilder::getBone1IDXs(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index)
{
	if( !maxMeshObj->IsObjectSkinned() )
		return MaxSkeletalAnimModelBuilder::errorMessage("The Mesh %s is attached to a 1-Blend Shader.\n But, it has no Skin Modifier attached.\n", maxNode->GetName());

	IGameSkin *skin = maxMeshObj->GetIGameSkin();

	// Get the numbers of bones effecting the vertex.
	int numberOfBones				= skin->GetNumberOfBones(index);
	if(numberOfBones>1)
	{
		return MaxSkeletalAnimModelBuilder::errorMessage("The Mesh %s is attached to a 1-Blend Shader.\n But it has some vertice attached to more than 1 bone.\n Maximun 1 bone per vertex is allowed", maxNode->GetName());
	}

	if(size!=4)
	{
		return MaxSkeletalAnimModelBuilder::errorMessage("expecting %s BLEND1INDEX as ubyte4 format", maxNode->GetName());
	}

	unsigned char boneIndices[4];
	memset(boneIndices, 0, sizeof(boneIndices[0])*4);
	for(int j=0; j<numberOfBones; j++)
	{
		IGameNode *iGameBone	= skin->GetIGameBone(index, j);
		assert(iGameBone);

		boneIndices[0] = skin->GetBoneIndex(iGameBone);
	}

	memcpy(buffer, &boneIndices[0], size);

	return true;
}

bool MaxSkeletalAnimModelBuilder::getBone2IDXs(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index)
{
	if( !maxMeshObj->IsObjectSkinned() )
		return MaxSkeletalAnimModelBuilder::errorMessage("The Mesh %s is attached to a 2-Blend Shader.\n But, it has no Skin Modifier attached.\n", maxNode->GetName());

	IGameSkin *skin = maxMeshObj->GetIGameSkin();

	// Get the numbers of bones effecting the vertex.
	int numberOfBones				= skin->GetNumberOfBones(index);
	if(numberOfBones>2)
	{
		return MaxSkeletalAnimModelBuilder::errorMessage("The Mesh %s is attached to a 2-Blend Shader.\n But it has some vertice attached to more than 2 bones.\n Maximun 2 bones per vertex is allowed", maxNode->GetName());
	}

	if(size!=4)
	{
		return MaxSkeletalAnimModelBuilder::errorMessage("expecting %s BLEND2INDEX as ubyte4 format", maxNode->GetName());
	}

	unsigned char boneIndices[4];
	memset(boneIndices, 0, sizeof(boneIndices[0])*4);
	for(int j=0; j<numberOfBones; j++)
	{
		IGameNode *iGameBone	= skin->GetIGameBone(index, j);
		assert(iGameBone);

		boneIndices[j] = skin->GetBoneIndex(iGameBone);
	}

	memcpy(buffer, &boneIndices[0], size);

	return true;
}
 
bool MaxSkeletalAnimModelBuilder::getBone2Weights(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index)
{
	if( !maxMeshObj->IsObjectSkinned() )
		return MaxSkeletalAnimModelBuilder::errorMessage("The Mesh %s is attached to a 2-Blend Shader.\n But, it has no Skin Modifier attached.\n", maxNode->GetName());

	IGameSkin *skin = maxMeshObj->GetIGameSkin();

	// Get the numbers of bones effecting the vertex.
	int numberOfBones				= skin->GetNumberOfBones(index);
	if(numberOfBones>2)
	{
		return MaxSkeletalAnimModelBuilder::errorMessage("The Mesh %s is attached to a 2-Blend Shader.\n But it has some vertice attached to more than 2 bones.\n Maximun 2 bones per vertex is allowed", maxNode->GetName());
	}

	if(size!=8)
	{
		return MaxSkeletalAnimModelBuilder::errorMessage("expecting %s BLEND2WEIGHT as float2 format", maxNode->GetName());
	}

	float boneWeights[4];
	memset(boneWeights, 0, sizeof(boneWeights[0])*4);
	for(int j=0; j<numberOfBones; j++)
	{
		// Get the weight for the bone and vertex index passed in.
		boneWeights[j]			= skin->GetWeight(index, j);
	}

	memcpy(buffer, &boneWeights[0], size);

	return true;
}

bool MaxSkeletalAnimModelBuilder::getBone4IDXs(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index)
{
	if( !maxMeshObj->IsObjectSkinned() )
		return MaxSkeletalAnimModelBuilder::errorMessage("The Mesh %s is attached to a 4-Blend Shader.\n But, it has no Skin Modifier attached.\n", maxNode->GetName());

	IGameSkin *skin = maxMeshObj->GetIGameSkin();

	// Get the numbers of bones effecting the vertex.
	int numberOfBones				= skin->GetNumberOfBones(index);
	if(numberOfBones>4)
	{
		return MaxSkeletalAnimModelBuilder::errorMessage("The Mesh %s is attached to a 4-Blend Shader.\n But it has some vertice attached to more than 4 bones.\n Maximun 4 bones per vertex is allowed", maxNode->GetName());
	}

	if(size!=4)
	{
		return MaxSkeletalAnimModelBuilder::errorMessage("expecting %s BLEND4INDEX as ubyte4 format", maxNode->GetName());
	}

	unsigned char boneIndices[4];
	memset(boneIndices, 0, sizeof(boneIndices[0])*4);
	for(int j=0; j<numberOfBones; j++)
	{
		IGameNode *iGameBone	= skin->GetIGameBone(index, j);
		assert(iGameBone);

		boneIndices[j] = skin->GetBoneIndex(iGameBone);
	}

	memcpy(buffer, &boneIndices[0], size);

	return true;
}
 
bool MaxSkeletalAnimModelBuilder::getBone4Weights(char *buffer, int size, const GMatrix &offsetTM, const GMatrix &initSkinTM, IGameNode *maxNode, IGameMesh *maxMeshObj, IGameMesh *bindPoseMeshObj, int index)
{
	if( !maxMeshObj->IsObjectSkinned() )
		return MaxSkeletalAnimModelBuilder::errorMessage("The Mesh %s is attached to a 4-Blend Shader.\n But, it has no Skin Modifier attached.\n", maxNode->GetName());

	IGameSkin *skin = maxMeshObj->GetIGameSkin();

	// Get the numbers of bones effecting the vertex.
	int numberOfBones				= skin->GetNumberOfBones(index);
	if(numberOfBones>4)
	{
		return MaxSkeletalAnimModelBuilder::errorMessage("The Mesh %s is attached to a 4-Blend Shader.\n But it has some vertice attached to more than 4 bones.\n Maximun 4 bones per vertex is allowed", maxNode->GetName());
	}
	
	if(size!=16)
	{
		return MaxSkeletalAnimModelBuilder::errorMessage("expecting %s BLEND4WEIGHT as float4 format", maxNode->GetName());
	}

	float boneWeights[4];
	memset(boneWeights, 0, sizeof(boneWeights[0])*4);
	for(int j=0; j<numberOfBones; j++)
	{
		// Get the weight for the bone and vertex index passed in.
		boneWeights[j]			= skin->GetWeight(index, j);
	}

	memcpy(buffer, &boneWeights[0], size);

	return true;
}
