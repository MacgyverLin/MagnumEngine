#include <windows.h>
#include <IL\il.h>
#include <IL\ilu.h>
#include "Array.h"
#include "EString.h"
#include "ColorRGBA.h"
#include "Vector3.h"
#include "Vector2.h"
#include "ImageFile.h"
using namespace EpicForce;

bool loadImages(Vector<ImageFile> &imageFiles, const char *prefix, const char *ext)
{
	const char *postfix[] =
	{
		"_rt",
		"_ft",
		"_lf",
		"_bk",
		"_up",
		"_dn",
	};

	imageFiles.resize(6);

	int width = -1, height = -1;
	for(int i=0; i<imageFiles.length(); i++)
	{
		String filename = String(prefix) + String(postfix[i]) + "." + String(ext);

		if( !imageFiles[i].load(filename) )
			return false;

		if(width!=-1 && height!=-1)
		{
			int newWidth  = imageFiles[i].getWidth();
			int newHeight = imageFiles[i].getHeight();

			if(width!=newWidth || height!=newHeight)
				return false;
		}

		width  = imageFiles[i].getWidth();
		height = imageFiles[i].getHeight();
	}

	return true;
}

// rt, lf, up, dn, bk, ft
int getMajorAxis(const Vector3 &dir)
{
	float maxAxisLength = -1;
	int index = 0;
	for(int i=0; i<3; i++)
	{
		if( maxAxisLength < Math::FAbs(dir[i]) )
		{
			maxAxisLength = Math::FAbs(dir[i]);
			index = i;
		}
	}

	if(index==0)
	{
		if(dir[index]>0)
			return 0; // rt
		else
			return 2; // lt
	}
	else if(index==1)
	{
		if(dir[index]>0)
			return 5; // up
		else
			return 4; // dn
	}
	else if(index==2)
	{
		if(dir[index]>0)
			return 1; // ft
		else
			return 3; // bk
	}

	return index;
}

/*
Vector2 getPixelCoord(int index, const Vector3 &dir, int width, int height)
{
	Vector2 rval;

	float t;
	switch(index)
	{
		case 0: // rt
			t = 1.0f / dir.X();
			rval = Vector2( dir.Z()*t*0.5+0.5, -dir.Y()*t*0.5+0.5);
			break;

		case 1: // ft
			t = 1.0f / dir.Z();
			rval = Vector2(-dir.X()*t*0.5+0.5, -dir.Y()*t*0.5+0.5);
			break;

		case 2: // lt
			t = 1.0f / dir.X();
			rval = Vector2( dir.Z()*t*0.5+0.5,  dir.Y()*t*0.5+0.5);
			break;

		case 3: // bk
			t = 1.0f / dir.Z();
			rval = Vector2(-dir.X()*t*0.5+0.5,  dir.Y()*t*0.5+0.5);
			break;
								   					  	   				
		case 4: // up
			t = 1.0f / dir.Y();
			rval = Vector2(-dir.Z()*t*0.5+0.5,  dir.X()*t*0.5+0.5);
			break;

		default:
		case 5: // dn
			t = 1.0f / dir.Y();
			rval = Vector2( dir.Z()*t*0.5+0.5,  dir.X()*t*0.5+0.5);
			break;
	}

	rval.X() *= width -1;
	rval.Y() *= height-1;

	return rval;
}
*/

Vector2 getPixelCoord(int index, const Vector3 &dir, int width, int height)
{
	Vector2 rval;

	float t;
	switch(index)
	{
		case 0: // rt
			t = 1.0f / dir.X();
			rval = Vector2( dir.Z()*t*0.5+0.5,  dir.Y()*t*0.5+0.5);
			break;

		case 2: // lt
			t = 1.0f / dir.X();
			rval = Vector2( dir.Z()*t*0.5+0.5, -dir.Y()*t*0.5+0.5);
			break;
								   					  	   				
		case 4: // up
			t = 1.0f / dir.Y();
			rval = Vector2(-dir.Z()*t*0.5+0.5, -dir.X()*t*0.5+0.5);
			break;

		case 5: // dn
			t = 1.0f / dir.Y();
			rval = Vector2( dir.Z()*t*0.5+0.5,  dir.X()*t*0.5+0.5);
			break;

		case 1: // ft
			t = 1.0f / dir.Z();
			rval = Vector2(-dir.X()*t*0.5+0.5,  dir.Y()*t*0.5+0.5);
			break;

		default:
		case 3: // bk
			t = 1.0f / dir.Z();
			rval = Vector2(-dir.X()*t*0.5+0.5, -dir.Y()*t*0.5+0.5);
			break;
	}

	rval.X() *= width -1;
	rval.Y() *= height-1;

	return rval;
}

Color getColor(const Vector3 &dir, const Vector<ImageFile> &inputFiles)
{
	int idx = getMajorAxis(dir);
	Vector2 coord = getPixelCoord(idx, dir, inputFiles[0].getWidth(), inputFiles[0].getHeight());
	
	int x, y;
	x = coord.X();
	y = coord.Y();

	return inputFiles[idx].getColor(x, y);
}

void convertCube2Sphere(ImageFile &outputFile, const Vector<ImageFile> &inputFiles)
{
	for(int y=0; y<outputFile.getHeight(); y++)
	{
		for(int x=0; x<outputFile.getWidth(); x++)
		{
			float phi   = ((float)y) / outputFile.getHeight() * Math::ONE_PI - Math::ONE_PI / 2.0f;
			float theta = ((float)x) / outputFile.getWidth()  * Math::TWO_PI;

			Vector3 dir;
			dir.X() = Math::Cos(phi) * Math::Cos(theta);
			dir.Y() = Math::Sin(phi);
			dir.Z() = Math::Cos(phi) * Math::Sin(theta);

			outputFile.setColor(x, y, getColor(dir, inputFiles) );
		}
	}
}

int main(int argc, char **argv)
{
	if(argc!=2)
	{
		printf("Usage CubeMapTool -m\n");

		return -1;
	}

	ilInit();
		
	Vector<ImageFile>		inputFiles;
	ImageFile				outputFile;

	const char *path	    = argv[1];
	const char *ext			= strstr(path, ".")+1;
	String prefix(path, ext-path-1);

	if( !loadImages(inputFiles, prefix.text(), ext) )
		return false;

	int outputWidth  = 4 * inputFiles[0].getWidth();
	int outputHeight = 2 * inputFiles[0].getHeight();
	outputFile.init(outputWidth, outputHeight, 32);

	convertCube2Sphere(outputFile, inputFiles);

	remove(path);
	outputFile.save(path); 

	
	ilShutDown();

	return 0;
}