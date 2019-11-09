//**************************************************************************/
// Copyright (c) 1998-2007 Autodesk, Inc.
// All rights reserved.
// 
// These coded instructions, statements, and computer programs contain
// unpublished proprietary information written by Autodesk, Inc., and are
// protected by Federal copyright law. They may not be disclosed to third
// parties or copied or duplicated in any form, in whole or in part, without
// the prior written consent of Autodesk, Inc.
//**************************************************************************/
// DESCRIPTION: Appwizard generated plugin
// AUTHOR: 
//***************************************************************************/

#include "EpicForceSceneCollisionExporter.h"
#include "SceneCollision.h"
#include "Array.h"
using namespace EpicForce;

namespace EpicForce
{

class SceneCollisionBuilder
{
public:
	SceneCollisionBuilder();
	~SceneCollisionBuilder();

	bool build(SceneCollision::Data &data, INode *rootNode, float meterPerUnits_);
	static bool errorMessage(const char *a_fmtstr, ...);
private:
	bool TMNegParity(Matrix3 &m);
	TriObject* GetTriObjectFromNode(INode *node, TimeValue t, int &deleteIt);

	bool collectNode(SceneCollision::Data &data, INode* node);
	bool collectCollision(SceneCollision::Data &data, INode* node);
	bool collectBrush(SceneCollision::Data &data, INode* node);
	bool collectHeightField(SceneCollision::Data &data, INode* node);

	float meterPerUnits;
};

SceneCollisionBuilder::SceneCollisionBuilder()
{
}

SceneCollisionBuilder::~SceneCollisionBuilder()
{
}

bool SceneCollisionBuilder::errorMessage(const char *a_fmtstr, ...)
{
	char buf[2048];

	va_list argptr; 
	va_start(argptr, a_fmtstr);

	vsprintf(buf, a_fmtstr, argptr);
	MessageBox(0, buf, "Error", MB_OK);
	
	va_end(argptr);

	return false;
}

bool SceneCollisionBuilder::build(SceneCollision::Data &data, INode *rootNode, float meterPerUnits_)
{
	meterPerUnits = meterPerUnits_;

	if( !collectNode(data, rootNode) )
	{
		MessageBox(0, "Export Failed", "Info", MB_OK);
		return FALSE;
	}

	return TRUE;
}

bool SceneCollisionBuilder::TMNegParity(Matrix3 &m)
{
	return (DotProd(CrossProd(m.GetRow(0),m.GetRow(1)),m.GetRow(2))<0.0) ? true : false;
}

TriObject* SceneCollisionBuilder::GetTriObjectFromNode(INode *node, TimeValue t, int &deleteIt)
{
	deleteIt = FALSE;
	Object *obj = node->EvalWorldState(t).obj;
	if (obj->CanConvertToType(Class_ID(TRIOBJ_CLASS_ID, 0))) 
	{ 
		TriObject *tri = (TriObject *) obj->ConvertToType(t, Class_ID(TRIOBJ_CLASS_ID, 0));
		// Note that the TriObject should only be deleted
		// if the pointer to it is not equal to the object
		// pointer that called ConvertToType()
		if (obj != tri) 
			deleteIt = TRUE;
		return tri;
	}
	else 
	{
		return 0;
	}
}

bool SceneCollisionBuilder::collectNode(SceneCollision::Data &data, INode* node)
{
	// The ObjectState is a 'thing' that flows down the pipeline containing
	// all information about the object. By calling EvalWorldState() we tell
	// max to eveluate the object at end of the pipeline.
	ObjectState os = node->EvalWorldState(0); 
	// The obj member of ObjectState is the actual object we will export.
	if (os.obj) 
	{
		// We look at the super class ID to determine the type of the object.
		switch(os.obj->SuperClassID()) 
		{
			case GEOMOBJECT_CLASS_ID:
				// exportGeometry(node, curNode);
				if( !collectCollision(data, node) )
					return false;
			break;
			case CAMERA_CLASS_ID:
				//exportCamera(node, curNode);
			break;
			case LIGHT_CLASS_ID:
				//exportLight(node, curNode);
			break;
			case SHAPE_CLASS_ID:
				//exportShape(node, curNode);
			break;
			case HELPER_CLASS_ID:
				//exportHelper(node, curNode);
			break;
		}
	}
	
	// For each child of this node, we recurse into ourselves 
	// and increment the counter until no more children are found.
	for (int c = 0; c < node->NumberOfChildren(); c++) 
	{
		if( !collectNode(data, node->GetChildNode(c)) )
			return false;
	}

	return true;
}

bool SceneCollisionBuilder::collectCollision(SceneCollision::Data &data, INode* node)
{
	if(node->IsNodeHidden())
		return true;

	ObjectState os = node->EvalWorldState(0);
	if (!os.obj)
	{
		MessageBox(0, "Error in Exporting Collision", "Error", MB_OK);
		return false;
	}

	// Targets are actually geomobjects, but we will export them
	// from the camera and light objects, so we skip them here.
	if (os.obj->ClassID() == Class_ID(TARGET_CLASS_ID, 0))
	{
		return true;
	}

	TSTR typeString;
	node->GetUserPropString("TYPE", typeString);
	//fprintf(txtfptr, "GEOMOBJECT_CLASS_ID: %s, TYPE %s, USERBUF %s\n", 
		//node->GetName(), (char*)userstring, (char*)userbuf);
	//virtual node->GetUserPropBuffer(const TSTR &buf)
	//virtual node->GetUserPropString(const TSTR &key, int &val)
	//virtual BOOL  GetUserPropInt (const TSTR &key, int &val)=0 
	//virtual BOOL  GetUserPropFloat (const TSTR &key, float &val)=0 
	//virtual BOOL  GetUserPropBool (const TSTR &key, BOOL &b)=0 

	if(typeString==TSTR("BRUSH") )
		return collectBrush(data, node);
	else if(typeString==TSTR("HEIGHT_FIELD") )
		return collectHeightField(data, node);
	else
		return true;
}

bool SceneCollisionBuilder::collectBrush(SceneCollision::Data &data, INode* node)
{
	Matrix3 tm    = node->GetObjTMAfterWSM(0);
	BOOL negScale = TMNegParity(tm);
	int vx1, vx2, vx3;
	// Order of the vertices. Get 'em counter clockwise if the objects is
	// negatively scaled.
	if (negScale) 
	{
		vx1 = 2;
		vx2 = 1;
		vx3 = 0;
	}
	else 
	{
		vx1 = 0;
		vx2 = 1;
		vx3 = 2;
	}

	BOOL needDel;
	TriObject* tri = GetTriObjectFromNode(node, 0, needDel);
	if (!tri) 
	{
		MessageBox(0, "Error in Exporting PolyList", "Error", MB_OK);
		return false;
	}
	
	Mesh* mesh = &tri->GetMesh();
	mesh->buildNormals();

	SceneCollision::Brush &brush = data.brushList.brushes.push();
	brush.name = node->GetName();
	for (int i=0; i<mesh->getNumFaces(); i++)
	{
		Point3 v1 = (tm * mesh->verts[mesh->faces[i].v[vx1]]) * Point3(meterPerUnits, meterPerUnits, meterPerUnits);
		Point3 v2 = (tm * mesh->verts[mesh->faces[i].v[vx2]]) * Point3(meterPerUnits, meterPerUnits, meterPerUnits);
		Point3 v3 = (tm * mesh->verts[mesh->faces[i].v[vx3]]) * Point3(meterPerUnits, meterPerUnits, meterPerUnits);
		
		Plane3 plane(Vector3(v1.x, v1.z, -v1.y), Vector3(v2.x, v2.z, -v2.y), Vector3(v3.x, v3.z, -v3.y) ) ;
		brush.add(plane);
	}

	if(needDel)
	{
		delete tri;
	}

	return true;
}

bool SceneCollisionBuilder::collectHeightField(SceneCollision::Data &data, INode* node)
{
	Matrix3 tm    = node->GetObjTMAfterWSM(0);
	BOOL negScale = TMNegParity(tm);
	int vx1, vx2, vx3;
	// Order of the vertices. Get 'em counter clockwise if the objects is
	// negatively scaled.
	if (negScale) 
	{
		vx1 = 2;
		vx2 = 1;
		vx3 = 0;
	}
	else 
	{
		vx1 = 0;
		vx2 = 1;
		vx3 = 2;
	}

	BOOL needDel;
	TriObject* tri = GetTriObjectFromNode(node, 0, needDel);
	if (!tri) 
	{
		MessageBox(0, "Error in Exporting Height Field", "Error", MB_OK);
		return false;
	}
	
	Mesh* mesh = &tri->GetMesh();
	mesh->buildNormals();
	
	Box3 box = mesh->getBoundingBox(&tm);
	Point3 min = box.Min() * Point3(meterPerUnits, meterPerUnits, meterPerUnits); 
	Point3 max = box.Max() * Point3(meterPerUnits, meterPerUnits, meterPerUnits);
	Point3 v00 = (tm * mesh->verts[0]) * Point3(meterPerUnits, meterPerUnits, meterPerUnits);
	Point3 v01 = (tm * mesh->verts[1]) * Point3(meterPerUnits, meterPerUnits, meterPerUnits);
	float gridSizeX = fabs(v00.x - v01.x);
	float xmin =  min.x, xmax =  max.x;
	int numGridX = ((xmax - xmin) / gridSizeX) + 0.5f;
	 
	Point3 v10 = (tm * mesh->verts[numGridX+1]) * Point3(meterPerUnits, meterPerUnits, meterPerUnits);
	float gridSizeZ = fabs(v00.y - v10.y);
	float zmin = -max.y, zmax = -min.y; 
	int numGridZ = ((zmax - zmin) / gridSizeZ) + 0.5f; 
	Vector<float> height; 
	height.resize( (numGridX+1)*(numGridZ+1) );
	for (int z=0; z<numGridZ+1; z++)
	{
		for (int x=0; x<numGridX+1; x++)
		{
			int i1 = (numGridZ-z) * (numGridX+1) + x;
			int i2 =            z * (numGridX+1) + x;
			Point3 v = (tm * mesh->verts[i1]) * Point3(meterPerUnits, meterPerUnits, meterPerUnits);
			height[i2] = v.z;
		}
	}

	SceneCollision::HeightField &heightfield = data.heightFieldList.heightFields.push();
	heightfield.name = node->GetName();
	heightfield.init(xmin, xmax, zmin, zmax, 
					 numGridX, numGridZ,
		             gridSizeX, gridSizeZ, 
					 height);

	if (needDel) 
	{
		delete tri;
	}

	return true;
}

};


#define EpicForceSceneCollisionExporter_CLASS_ID	Class_ID(0x922592d1, 0x6a421b97)

class EpicForceSceneCollisionExporter : public SceneExport {
	public:
		
		static HWND hParams;
		
		int				ExtCount();					// Number of extensions supported
		const TCHAR *	Ext(int n);					// Extension #n (i.e. "3DS")
		const TCHAR *	LongDesc();					// Long ASCII description (i.e. "Autodesk 3D Studio File")
		const TCHAR *	ShortDesc();				// Short ASCII description (i.e. "3D Studio")
		const TCHAR *	AuthorName();				// ASCII Author name
		const TCHAR *	CopyrightMessage();			// ASCII Copyright message
		const TCHAR *	OtherMessage1();			// Other message #1
		const TCHAR *	OtherMessage2();			// Other message #2
		unsigned int	Version();					// Version number * 100 (i.e. v3.01 = 301)
		void			ShowAbout(HWND hWnd);		// Show DLL's "About..." box

		static DWORD WINAPI progressCBFunc(LPVOID arg);

		BOOL SupportsOptions(int ext, DWORD options);
		int				DoExport(const TCHAR *name,ExpInterface *ei,Interface *i, BOOL suppressPrompts=FALSE, DWORD options=0);

		//Constructor/Destructor
		EpicForceSceneCollisionExporter();
		~EpicForceSceneCollisionExporter();		

		int totalNumOfNode;
		Interface *ip;
public:
};



class EpicForceSceneCollisionExporterClassDesc : public ClassDesc2 
{
public:
	virtual int IsPublic() 							{ return TRUE; }
	virtual void* Create(BOOL /*loading = FALSE*/) 		{ return new EpicForceSceneCollisionExporter(); }
	virtual const TCHAR *	ClassName() 			{ return GetString(IDS_CLASS_NAME); }
	virtual SClass_ID SuperClassID() 				{ return SCENE_EXPORT_CLASS_ID; }
	virtual Class_ID ClassID() 						{ return EpicForceSceneCollisionExporter_CLASS_ID; }
	virtual const TCHAR* Category() 				{ return GetString(IDS_CATEGORY); }

	virtual const TCHAR* InternalName() 			{ return _T("EpicForceSceneCollisionExporter"); }	// returns fixed parsable name (scripter-visible name)
	virtual HINSTANCE HInstance() 					{ return hInstance; }					// returns owning module handle
	

};


ClassDesc2* GetEpicForceSceneCollisionExporterDesc() { 
	static EpicForceSceneCollisionExporterClassDesc EpicForceSceneCollisionExporterDesc;
	return &EpicForceSceneCollisionExporterDesc; 
}





INT_PTR CALLBACK EpicForceSceneCollisionExporterOptionsDlgProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam) {
	static EpicForceSceneCollisionExporter *imp = NULL;

	switch(message) {
		case WM_INITDIALOG:
			imp = (EpicForceSceneCollisionExporter *)lParam;
			CenterWindow(hWnd,GetParent(hWnd));
			return TRUE;

		case WM_CLOSE:
			EndDialog(hWnd, 0);
			return 1;
	}
	return 0;
}


//--- EpicForceSceneCollisionExporter -------------------------------------------------------
EpicForceSceneCollisionExporter::EpicForceSceneCollisionExporter()
: totalNumOfNode(0)
, ip(0)
{
}

EpicForceSceneCollisionExporter::~EpicForceSceneCollisionExporter() 
{

}

int EpicForceSceneCollisionExporter::ExtCount()
{
	// Returns the number of file name extensions supported by the plug-in.
	return 1;
}

const TCHAR *EpicForceSceneCollisionExporter::Ext(int n)
{		
	return _T("scenecollision");
}

const TCHAR *EpicForceSceneCollisionExporter::LongDesc()
{
	return _T("EpicForce Scene Collision");
}
	
const TCHAR *EpicForceSceneCollisionExporter::ShortDesc() 
{			
	return _T("EpicForce Scene Collision");
}

const TCHAR *EpicForceSceneCollisionExporter::AuthorName()
{			
	return _T("Mac Lin");
}

const TCHAR *EpicForceSceneCollisionExporter::CopyrightMessage() 
{	
	return _T("EpicForce Entertainment Limited");
}

const TCHAR *EpicForceSceneCollisionExporter::OtherMessage1() 
{		
	return _T("asd");
}

const TCHAR *EpicForceSceneCollisionExporter::OtherMessage2() 
{		
	return _T("asd");
}

unsigned int EpicForceSceneCollisionExporter::Version()
{				
	return 100;
}

void EpicForceSceneCollisionExporter::ShowAbout(HWND hWnd)
{			
	// Optional
}

BOOL EpicForceSceneCollisionExporter::SupportsOptions(int ext, DWORD options)
{
	// #pragma message(TODO("Decide which options to support.  Simply return true for each option supported by each Extension the exporter supports."))
	return TRUE;
}

// Dummy function for progress bar
DWORD WINAPI EpicForceSceneCollisionExporter::progressCBFunc(LPVOID arg)
{
	return(0);
}

int	EpicForceSceneCollisionExporter::DoExport(const TCHAR *path, ExpInterface *ei,Interface *i, BOOL suppressPrompts, DWORD options)
{
	// #pragma message(TODO("Implement the actual file Export here and"))
	DialogBoxParam(hInstance, 
				   MAKEINTRESOURCE(IDD_PANEL), 
				   GetActiveWindow(), 
				   EpicForceSceneCollisionExporterOptionsDlgProc, (LPARAM)this);

	float meterPerUnits = GetMasterScale(UNITS_METERS); 
	// save Interface Pointer
	ip = i;

	// Startup the progress bar.
	ip->ProgressStart("Exporting", TRUE, progressCBFunc, NULL);
	
	SceneCollision::Data data;
	SceneCollisionBuilder builder;
	if( !builder.build(data, ip->GetRootNode(), meterPerUnits) )
		return FALSE;

	FileOutputStream os(path); 
	if(!os.opened())
	{
		SceneCollisionBuilder::errorMessage("failed to Open \"%s\" for writing", path);
		return FALSE;
	}
	os << data;

	// We're done. Finish the progress bar.
	ip->ProgressEnd();

	return TRUE;
}