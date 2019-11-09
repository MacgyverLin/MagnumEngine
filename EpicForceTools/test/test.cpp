#include "stdafx.h"
#include <string>
using namespace std;

string getDirectory(const char *fullPath)
{
	// const char *str = "D:\\Program Files\\Autodesk\\3ds Max 2012\\Scripts\\Startup\\epicforce\\DXShaderTest.fx";
	const char *filename = strrchr(fullPath, '\\')+1;
	const char *ext      = strrchr(fullPath, '.') +1;

	return string(fullPath, filename - fullPath);
}

string getFileName(const char *fullPath)
{
	// const char *str = "D:\\Program Files\\Autodesk\\3ds Max 2012\\Scripts\\Startup\\epicforce\\DXShaderTest.fx";
	const char *filename = strrchr(fullPath, '\\')+1;
	const char *ext      = strrchr(fullPath, '.');

	return string(filename, ext - filename);
}

string getExtension(const char *fullPath)
{
	const char *filename = strrchr(fullPath, '\\')+1;
	const char *ext      = strrchr(fullPath, '.')+1;

	// const char *str = "D:\\Program Files\\Autodesk\\3ds Max 2012\\Scripts\\Startup\\epicforce\\DXShaderTest.fx";
	return strrchr(fullPath, '.')+1;
}

bool getEpicForceToolsDirectory(string &toolsDir)
{
	const char *toolEnv = getenv("EPICFORCE_TOOLS");
	//const char *toolEnv = "c:\\EpicForceTools//";
	if(!toolEnv)
		return false;

	toolsDir = toolEnv;

	int i;
	for(i=toolsDir.length()-1; i>=0; i--)
	{
		if( !(toolsDir[i]=='\\' || toolsDir[i]=='/') )
			break;
	}

	if(i!=toolsDir.length()-1)
		toolsDir[i+1] = 0;

	return true;
}

bool isValidPath(const char *fullPath, const char *toolsDir)
{
	string s1 = toolsDir;// s1.toLower();
	string s2 = fullPath;// s2.toLower();

	if(s1.length()!=s2.length())
		return false;

	return (s1==s2);
}

string getMaterialDirectory(const char *fullPath, const char *toolsDir)
{
	string fxpath = toolsDir + string("\\fx\\");
	int start = fxpath.length();

	const char *filename = strrchr(fullPath, '\\')+1;
	const char *ext      = strrchr(fullPath, '.') +1;

	return string(&fullPath[start], filename - fullPath - start);
}

string getGLFXDirectory(const char *fullPath, const char *toolsDir)
{
	return string(toolsDir) + string("\\glfx\\") + getMaterialDirectory(fullPath, toolsDir);
}

string getGLFXOutputDirectory(const char *fullPath, const char *toolsDir, const char *exportDirectory)
{
	return string(exportDirectory) + string("\\Shaders\\") + getMaterialDirectory(fullPath, toolsDir);
}

int _tmain(int argc, _TCHAR* argv[])
{
	string epicForceToolsPath;
	bool r = getEpicForceToolsDirectory(epicForceToolsPath);

	const char *test0= "c:\\EpicForceTools\\fx\\DiffuseMap.fx";
	const char *test1= "c:\\EpicForceTools\\fx\\1Blend\\DiffuseMap.fx";
	const char *test4= "c:\\EpicForceTools\\fx\\4Blend\\DiffuseMap.fx";

	string filename0 = getFileName(test0);
	string filename1 = getFileName(test1);
	string filename4 = getFileName(test4);

	string glfxDirectory;
	string glfxOutputDirectory;
	string glfxMaterialDirectory;

	bool valid0 = isValidPath(test0, epicForceToolsPath.c_str()); 
	bool valid1 = isValidPath(test1, epicForceToolsPath.c_str());
	bool valid4 = isValidPath(test4, epicForceToolsPath.c_str());

	glfxDirectory			= getGLFXDirectory(test0, epicForceToolsPath.c_str()) + string(filename0) + ".visualeffect";
	glfxOutputDirectory		= getGLFXOutputDirectory(test0, epicForceToolsPath.c_str(), "c:\\test1") + string(filename0) + ".visualeffect";
	glfxMaterialDirectory	= getMaterialDirectory(test0, epicForceToolsPath.c_str()) + string(filename0);

	glfxDirectory			= getGLFXDirectory(test1, epicForceToolsPath.c_str()) + string(filename1) + ".visualeffect";
	glfxOutputDirectory		= getGLFXOutputDirectory(test1, epicForceToolsPath.c_str(), "c:\\test1") + string(filename1) + ".visualeffect";
	glfxMaterialDirectory	= getMaterialDirectory(test1, epicForceToolsPath.c_str()) + string(filename1);

	glfxDirectory			= getGLFXDirectory(test4, epicForceToolsPath.c_str()) + string(filename4) + ".visualeffect";
	glfxOutputDirectory		= getGLFXOutputDirectory(test4, epicForceToolsPath.c_str(), "c:\\test1") + string(filename4) + ".visualeffect";
	glfxMaterialDirectory	= getMaterialDirectory(test4, epicForceToolsPath.c_str()) + string(filename4);

	return 0;
}

