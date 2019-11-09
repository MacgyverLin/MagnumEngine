#include <windows.h>
#include <sys/stat.h>
#include "tinystr.h"
#include "tinyxml.h"
#include <vector>
#include <string>
using namespace std;

#define SCENE_SUFFIX  "Scene.cpp"
#define ENTITY_SUFFIX "Entity.cpp"
#define EXPORT_DIR    "EntryPoint"

void collectCPP(vector<string> &sceneFiles, const char *inputFileName, const char *suffix)
{
	TiXmlDocument doc(inputFileName);
	if(doc.LoadFile())
	{
		TiXmlNode *project = doc.FirstChild("Project");

		for(TiXmlNode *itemGroup = project->FirstChild("ItemGroup"); itemGroup; itemGroup = itemGroup->NextSibling() )
		{
			for(TiXmlNode *clCompile = itemGroup->FirstChild("ClCompile"); clCompile; clCompile = clCompile->NextSibling() )
			{
				TiXmlNode *excludedFromBuild = clCompile->FirstChild("ExcludedFromBuild");
				if(excludedFromBuild)
					continue;
				
				TiXmlElement *element = clCompile->ToElement();
				const char *filename = element->Attribute("Include");
				if(!filename)
					continue;

				if( stricmp( &filename[strlen(filename)-strlen(suffix)], suffix)==0 )
				{
					// printf("%s\n", filename);
					sceneFiles.push_back(filename);
				}
			}
		}
	}
}

const char *getFileName(char *buffer, const char *filename, const char *suffix)
{
	int pos = strlen(filename)-strlen(suffix);
	strncpy(buffer, filename, pos);
	buffer[pos] = 0;

	return buffer;
}

void toLowerName(char *lowerBuffer, const char *filename)
{
	int len = strlen(filename);
	for(int i=0; i<len; i++)
	{
		lowerBuffer[i] = tolower(filename[i]);
	}
	lowerBuffer[len] = 0;
}

void writeSceneCreatorHeader(vector<string> &cppFiles, const char *dir, const char *name)
{
	CreateDirectory(dir, 0);

	char path[2048];
	sprintf(path, "%s/%sCreators.h", dir, name);

	char suffix[2048];
	sprintf(suffix, "%s.cpp", name);

	char lowerName[2048];
	toLowerName(lowerName, name);

	FILE *fptr = fopen(path, "wt");
	if(fptr)
	{
		for(int i=0; i<cppFiles.size(); i++)
		{
			const char *prefix = strchr(getFileName(path, cppFiles[i].c_str(), suffix), '\\')+1;

			fprintf(fptr, "#include \"%s%s.h\"\n", prefix, name);
			fprintf(fptr, "static %s::Creator<%s%s> %s%s(\"%s\", false);\n\n", 
				name, prefix, name, lowerName, prefix, prefix);
		}

		fclose(fptr);
	}
}

void writeEntityCreatorHeader(vector<string> &cppFiles, const char *dir, const char *name)
{
	CreateDirectory(dir, 0);

	char path[2048];
	sprintf(path, "%s/%sCreators.h", dir, name);

	char suffix[2048];
	sprintf(suffix, "%s.cpp", name);

	char lowerName[2048];
	toLowerName(lowerName, name);

	FILE *fptr = fopen(path, "wt");
	if(fptr)
	{
		for(int i=0; i<cppFiles.size(); i++)
		{
			const char *prefix = strchr(getFileName(path, cppFiles[i].c_str(), suffix), '\\')+1;

			fprintf(fptr, "#include \"%s%s.h\"\n", prefix, name);
			fprintf(fptr, "static %s::Creator<%s%s> %s%s(\"%s%s\");\n\n", 
				name, prefix, name, lowerName, prefix, prefix, name);
		}

		fclose(fptr);
	}
}

void writeMagnumGameHeader(vector<string> &cppFiles, const char *dir, const char *name)
{
	CreateDirectory(dir, 0);

	char path[2048];
	sprintf(path, "%s/MagnumGame.h", dir, name);

	char suffix[2048];
	sprintf(suffix, "%s.cpp", name);

	char lowerName[2048];
	toLowerName(lowerName, name);

	FILE *fptr = fopen(path, "wt");
	if(fptr)
	{
		fprintf(fptr, "#ifndef _MagnumGame_h_\n");
		fprintf(fptr, "#define _MagnumGame_h_\n");
		fprintf(fptr, "\n");

		for(int i=0; i<cppFiles.size(); i++)
		{
			const char *prefix = strchr(getFileName(path, cppFiles[i].c_str(), suffix), '\\')+1;

			fprintf(fptr, "#include \"%s%s.h\"\n", prefix, name);
		}
		fprintf(fptr, "\n");

		fprintf(fptr, "#endif");

		fclose(fptr);
	}
}

int main(int argc, char **argv)
{
	if(argc!=2)
	{
		printf("Usage prebuilt myproject.vcxproj");
		return -1;
	}

	vector<string> sceneFiles;
	collectCPP(sceneFiles, argv[1], SCENE_SUFFIX);
	writeSceneCreatorHeader(sceneFiles, EXPORT_DIR, "Scene");

	vector<string> entityFiles;
	collectCPP(entityFiles, argv[1], ENTITY_SUFFIX);
	writeEntityCreatorHeader(entityFiles, EXPORT_DIR, "Entity");

	writeMagnumGameHeader(entityFiles, EXPORT_DIR, "Entity");

	return 0;
}