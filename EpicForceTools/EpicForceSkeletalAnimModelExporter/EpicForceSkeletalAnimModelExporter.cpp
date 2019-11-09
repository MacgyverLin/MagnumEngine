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
//				3DXI file exporter project template
//				For a more in-depth exemple of a 3DXI exporter,
//				please refer to maxsdk\samples\igame\export. 
// AUTHOR:		Jean-Francois Yelle - created Mar.20.2007
//***************************************************************************/

#include "EpicForceSkeletalAnimModelExporter.h"

#include "3dsmaxsdk_preinclude.h"  
#include "IGame/IGame.h" 
#include "IDxMaterial.h"
#include "Stage.h"
#include "Array.h"
#include "Platform.h"
#include <AssetManagement/AssetUser.h>
#include <IFileResolutionManager.h>
#include "SkeletalAnimModel.h"
#include "MaxSkeletalAnimModelBuilder.h"
#include "AnimModelVersion.h"
using namespace EpicForce;

#include <map>
using namespace std;

#define EpicForceSkeletalAnimModelExporter_CLASS_ID	Class_ID(0x8dde1a7f, 0x721de167)

class EpicForceSkeletalAnimModelExporter : public SceneExport 
{
	public:
		
		virtual int				ExtCount();					// Number of extensions supported
		virtual const TCHAR *	Ext(int n);					// Extension #n (i.e. "3DS")
		virtual const TCHAR *	LongDesc();					// Long ASCII description (i.e. "Autodesk 3D Studio File")
		virtual const TCHAR *	ShortDesc();				// Short ASCII description (i.e. "3D Studio")
		virtual const TCHAR *	AuthorName();				// ASCII Author name
		virtual const TCHAR *	CopyrightMessage();			// ASCII Copyright message
		virtual const TCHAR *	OtherMessage1();			// Other message #1
		virtual const TCHAR *	OtherMessage2();			// Other message #2
		virtual unsigned int	Version();					// Version number * 100 (i.e. v3.01 = 301)
		virtual void			ShowAbout(HWND hWnd);		// Show DLL's "About..." box

		virtual BOOL SupportsOptions(int ext, DWORD options);
		virtual int	DoExport(const TCHAR *name,ExpInterface *ei,Interface *i, BOOL suppressPrompts=FALSE, DWORD options=0);

		//Constructor/Destructor 
		EpicForceSkeletalAnimModelExporter();
		virtual ~EpicForceSkeletalAnimModelExporter();

	protected:
		bool infoMessage(const char *a_fmtstr, ...);
		bool warningMessage(const char *a_fmtstr, ...);
		bool errorMessage(const char *a_fmtstr, ...);

		void mergeDoubleSlashes(std::string &str);
		bool getAssetPath(char const *path, String &finalpath);

		bool collectIGameMaterial(IGameMaterial *parentMat, int parentMatID, int level);
		bool collectIGameBitmap(map<String, int> &bitmapsMap, IGameMaterial *material);
		void collectIGameNode(IGameNode *parent);
		bool collecSceneObject(IGameScene *pIgame);
	private:
		static HWND hParams;

	public:
		Vector<String				 >	bitmaps;
		Vector<IGameMaterial		*>	materials;
		Vector<IGameNode			*>	nodes;

		Platform platform;
		float meterPerUnits;
		int framePerKey;
};



class EpicForceSkeletalAnimModelExporterClassDesc : public ClassDesc2 
{
public:
	virtual int IsPublic() 							{ return TRUE; }
	virtual void* Create(BOOL /*loading = FALSE*/) 		{ return new EpicForceSkeletalAnimModelExporter(); }
	virtual const TCHAR *	ClassName() 			{ return GetString(IDS_CLASS_NAME); }
	virtual SClass_ID SuperClassID() 				{ return SCENE_EXPORT_CLASS_ID; }
	virtual Class_ID ClassID() 						{ return EpicForceSkeletalAnimModelExporter_CLASS_ID; }
	virtual const TCHAR* Category() 				{ return GetString(IDS_CATEGORY); }

	virtual const TCHAR* InternalName() 			{ return _T("EpicForceSkeletalAnimModelExporter"); }	// returns fixed parsable name (scripter-visible name)
	virtual HINSTANCE HInstance() 					{ return hInstance; }					// returns owning module handle
	

};


ClassDesc2* GetEpicForceSkeletalAnimModelExporterDesc() { 
	static EpicForceSkeletalAnimModelExporterClassDesc EpicForceSkeletalAnimModelExporterDesc;
	return &EpicForceSkeletalAnimModelExporterDesc; 
}





INT_PTR CALLBACK EpicForceSkeletalAnimModelExporterOptionsDlgProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam) 
{
	static EpicForceSkeletalAnimModelExporter *imp = NULL;
	HWND hCtrl;
	ISpinnerControl *spinner;

	switch(message) 
	{
		case WM_INITDIALOG:
			imp = (EpicForceSkeletalAnimModelExporter *)lParam;
			CenterWindow(hWnd,GetParent(hWnd));

			hCtrl = GetDlgItem(hWnd, IDC_PC); 
			Button_SetCheck(hCtrl, TRUE);
			hCtrl = GetDlgItem(hWnd, IDC_IOS);
			Button_SetCheck(hCtrl, FALSE);
			hCtrl = GetDlgItem(hWnd, IDC_ANDROID);
			Button_SetCheck(hCtrl, FALSE);
			hCtrl = GetDlgItem(hWnd, IDC_PSVITA);
			Button_SetCheck(hCtrl, FALSE);
			hCtrl = GetDlgItem(hWnd, IDC_WIIU);
			Button_SetCheck(hCtrl, FALSE);			

			imp->platform = Platform::PC; 

			spinner = GetISpinner( GetDlgItem(hWnd, IDC_FRAMEPERKEY_SPIN) );
			spinner->SetLimits(1, 5, FALSE);
			spinner->SetValue(3, FALSE);
			spinner->SetScale(1);
			spinner->LinkToEdit( GetDlgItem(hWnd, IDC_FRAMEPERKEY_EDIT), EDITTYPE_INT );
			imp->framePerKey = 3;

			return TRUE;

		case WM_COMMAND:

			if(wParam==IDC_OK)
			{
				hCtrl = GetDlgItem(hWnd, IDC_PC);
				bool exportPC		= Button_GetCheck(hCtrl);
				hCtrl = GetDlgItem(hWnd, IDC_IOS);
				bool exportIOS		= Button_GetCheck(hCtrl);
				hCtrl = GetDlgItem(hWnd, IDC_ANDROID);
				bool exportAndroid	= Button_GetCheck(hCtrl);
				hCtrl = GetDlgItem(hWnd, IDC_PSVITA);
				bool exportPSVita	= Button_GetCheck(hCtrl);
				hCtrl = GetDlgItem(hWnd, IDC_WIIU);
				bool exportWiiU		= Button_GetCheck(hCtrl);


				if(exportPC)
					imp->platform = Platform::PC;
				else if(exportIOS)
					imp->platform = Platform::IOS;
				else if(exportAndroid)
					imp->platform = Platform::ANDROID;
				else if(exportPSVita)
					imp->platform = Platform::PSVITA;
				else if(exportWiiU)
					imp->platform = Platform::WIIU;

				spinner = GetISpinner( GetDlgItem(hWnd, IDC_FRAMEPERKEY_SPIN) );
				imp->framePerKey = spinner->GetIVal();

				EndDialog(hWnd, 0);
				return 1;
			}
			else if (wParam==IDC_CANCEL)
			{
				EndDialog(hWnd, 0);
				return 0;
			}
			else
			{
				return TRUE;
			}

		case WM_CLOSE:
			EndDialog(hWnd, 0);
			return 1;
	}
	return 0;
}


//--- EpicForceSkeletalAnimModelExporter -------------------------------------------------------
EpicForceSkeletalAnimModelExporter::EpicForceSkeletalAnimModelExporter()
{

}

EpicForceSkeletalAnimModelExporter::~EpicForceSkeletalAnimModelExporter() 
{

}

int EpicForceSkeletalAnimModelExporter::ExtCount()
{
	// Returns the number of file name extensions supported by the plug-in.
	return 1;
}

const TCHAR *EpicForceSkeletalAnimModelExporter::Ext(int n)
{		
	return _T("skelanimModel");
}

const TCHAR *EpicForceSkeletalAnimModelExporter::LongDesc()
{
	return _T("EpicForce Skeletal Animation Model");
}
	
const TCHAR *EpicForceSkeletalAnimModelExporter::ShortDesc() 
{			
	return _T("EpicForce Skeletal Animation Model");
}

const TCHAR *EpicForceSkeletalAnimModelExporter::AuthorName()
{			
	return _T("Mac Lin");
}

const TCHAR *EpicForceSkeletalAnimModelExporter::CopyrightMessage() 
{	
	return _T("EpicForce Entertainment Limited");
}

const TCHAR *EpicForceSkeletalAnimModelExporter::OtherMessage1() 
{		
	//TODO: Return Other message #1 if any
	return _T("");
}

const TCHAR *EpicForceSkeletalAnimModelExporter::OtherMessage2() 
{		
	return _T("");
}

unsigned int EpicForceSkeletalAnimModelExporter::Version()
{				
	return 100;
}

void EpicForceSkeletalAnimModelExporter::ShowAbout(HWND hWnd)
{			
	// Optional
}

BOOL EpicForceSkeletalAnimModelExporter::SupportsOptions(int ext, DWORD options)
{
	// TODO Decide which options to support.  Simply return
	// true for each option supported by each Extension 
	// the exporter supports.

	return TRUE;
}

void EpicForceSkeletalAnimModelExporter::mergeDoubleSlashes(std::string &str)
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

bool EpicForceSkeletalAnimModelExporter::getAssetPath(char const *path, String &finalpath)
{
	string temp(IFileResolutionManager::GetInstance()->GetFullFilePath(path, MaxSDK::AssetManagement::kBitmapAsset));

	if(temp.empty())
		return false;

	mergeDoubleSlashes(temp);

	finalpath = temp.c_str();

	return true;
}

bool EpicForceSkeletalAnimModelExporter::collectIGameMaterial(IGameMaterial *parentMat, int parentMatID, int level)
{
	const char *classname = parentMat->GetMaterialClass();

	if( !MaxSkeletalAnimModelBuilder::isValidMaterialClass(classname) )
	{ 
		return MaxSkeletalAnimModelBuilder::errorMessage("Material %s is not a supported, use DXShader or Multi/Sub Material\n", parentMat->GetMaterialName());
	}
	
	if(level>=1 && parentMat->IsMultiType())
	{
		return MaxSkeletalAnimModelBuilder::errorMessage("Error: Material \"%s\" contains more than 1 level of cascaded Multi/Sub Material", classname);
	}

	if(parentMat->IsMultiType())
	{
		for(int i=0; i<parentMat->GetSubMaterialCount(); i++)
		{
			int childMatID			= parentMat->GetMaterialID(i);
			IGameMaterial *childMat = parentMat->GetSubMaterial(i);

			if( !collectIGameMaterial(childMat, childMatID, level+1) )
				return false;
		}
	}
	else
	{
		materials.push() = parentMat;
	}

	return true;
}

bool EpicForceSkeletalAnimModelExporter::collectIGameBitmap(map<String, int> &bitmapsMap, IGameMaterial *material)
{
	if( !MaxSkeletalAnimModelBuilder::isDXShaderMaterialClass(material->GetClassName()) )
		return true;

	/////////////////////////////////////////////////////////////////////////////////////////
	// Effect Parameter
	IGameFX *fx = material->GetIGameFX(); 
	if(!fx)
		return MaxSkeletalAnimModelBuilder::errorMessage("Material .fx file is not set properly\"%s\"'s", material->GetMaterialName());
	// const MaxSDK::AssetManagement::AssetUser &assetUser = fx->GetEffectFile();

	/////////////////////////////////////////////////////////////////////////////////////////
	// Effect Bitmap
	IDxMaterial *idxm = (IDxMaterial *)material->GetMaxMaterial()->GetInterface(IDXMATERIAL_INTERFACE);
	if(!idxm)
		return false;

	// virtual void ReloadDXEffect()=0;
	for(int j=0; j<idxm->GetNumberOfEffectBitmaps(); j++)
	{
		PBBitmap *bitmap				= idxm->GetEffectBitmap(j);
		if(!bitmap)
			return MaxSkeletalAnimModelBuilder::errorMessage("Material \"%s\"'s Bitmap %d is not set properly", material->GetMaterialName(), j);

		BitmapInfo bi					= bitmap->bi;
		MaxSDK::Util::Path path			= bitmap->bi.GetPathEx();
		MaxSDK::Util::Path absolutePath = path.ConvertToAbsolute();
			
		String assetPath;
		if( !getAssetPath(absolutePath.GetCStr(), assetPath) )
			return false;

		map<String, int>::iterator itr = bitmapsMap.find(assetPath);
		if(itr==bitmapsMap.end())
			bitmapsMap.insert(pair<String, int>(assetPath, bitmapsMap.size()));
	}

	return true;
}

void EpicForceSkeletalAnimModelExporter::collectIGameNode(IGameNode *parent)
{
	nodes.push() = parent;

	for(int i=0; i<parent->GetChildCount(); i++)
	{
		IGameNode *child = parent->GetNodeChild(i);

		// we deal with targets in the light/camera section
		if(child->IsTarget())
			continue;

		collectIGameNode(child);
	}
}

bool EpicForceSkeletalAnimModelExporter::collecSceneObject(IGameScene *pIgame)
{
	for(int i=0; i<pIgame->GetRootMaterialCount(); i++) 
	{
		IGameMaterial *igamematerial = pIgame->GetRootMaterial(i); 

		if( !collectIGameMaterial(igamematerial, -1, 0) ) 
		{
			return false;
		}
	}

	map<String, int> bitmapsMap;
	for(int i=0; i<materials.length(); i++)
	{
		if( !collectIGameBitmap(bitmapsMap, materials[i]) )
			return false;
	}

	bitmaps.resize(bitmapsMap.size());
	map<String, int>::iterator itr;
	for(itr=bitmapsMap.begin(); itr!=bitmapsMap.end(); itr++)
	{
		bitmaps[itr->second] = itr->first;
	}

	// collect Nodes;
	for(int i=0; i<pIgame->GetTopLevelNodeCount(); i++)
	{
		IGameNode *igamenode = pIgame->GetTopLevelNode(i);
		//check for selected state - we deal with targets in the light/camera section
		if(igamenode->IsTarget())
			continue; 

		collectIGameNode(igamenode);
	}

	return true;
}

bool EpicForceSkeletalAnimModelExporter::infoMessage(const char *a_fmtstr, ...)
{
	char buf[1024];

	va_list argptr; 
	va_start(argptr, a_fmtstr);

	vsprintf(buf, a_fmtstr, argptr);
	MessageBox(0, buf, "Info", MB_OK);
	
	va_end(argptr);

	return true;
}

bool EpicForceSkeletalAnimModelExporter::warningMessage(const char *a_fmtstr, ...)
{
	char buf[2048];

	va_list argptr; 
	va_start(argptr, a_fmtstr); 
	
	vsprintf(buf, a_fmtstr, argptr);
	MessageBox(0, buf, "Warning", MB_OK);
	
	va_end(argptr); 

	return true;
}

bool EpicForceSkeletalAnimModelExporter::errorMessage(const char *a_fmtstr, ...)
{
	char buf[2048];

	va_list argptr; 
	va_start(argptr, a_fmtstr);

	vsprintf(buf, a_fmtstr, argptr);
	MessageBox(0, buf, "Error", MB_OK);
	
	va_end(argptr);

	return false;
}


int	EpicForceSkeletalAnimModelExporter::DoExport(const TCHAR* path,ExpInterface* ei,Interface* i, BOOL suppressPrompts, DWORD options)
{
	// This is where the file export operation occur.
	if(!suppressPrompts)
		DialogBoxParam(hInstance, 
					   MAKEINTRESOURCE(IDD_PANEL), 
					   GetActiveWindow(), 
					   EpicForceSkeletalAnimModelExporterOptionsDlgProc, (LPARAM)this);

	IGameScene *pIgame = GetIGameInterface();  
	IGameConversionManager *cm = GetConversionManager();
//	cm->SetUserCoordSystem(Whacky);
	cm->SetCoordSystem(IGameConversionManager::IGAME_OGL);
	pIgame->InitialiseIGame(false);
	pIgame->SetStaticFrame(pIgame->GetSceneStartTime());
	meterPerUnits = GetMasterScale(UNITS_METERS); 

	if( !collecSceneObject(pIgame) )
	{
		pIgame->ReleaseIGame();
		return FALSE;
	}

	MaxSkeletalAnimModelBuilder skeletalModelBuilder(ANIMMODEL_VERSION, platform, meterPerUnits,
													 20,
													 bitmaps, materials, nodes,
													 pIgame->GetSceneStartTime()/pIgame->GetSceneTicks(), pIgame->GetSceneEndTime()/pIgame->GetSceneTicks(), 
													 pIgame->GetSceneTicks(), GetFrameRate(), framePerKey);

	SkeletalAnimModel::Data skeletalModelData;
	if(!skeletalModelBuilder.build(skeletalModelData, path))
	{
		pIgame->ReleaseIGame();
		return FALSE;
	}

	{
		FileOutputStream os(path);
		if(!os.opened())
		{
			MaxSkeletalAnimModelBuilder::errorMessage("failed to Open \"%s\" for writing", path);
			pIgame->ReleaseIGame();
			return FALSE;
		}
		os << skeletalModelData;
	}

	/*
	{
		FileInputStream is(path); 
		if(!is.opened())
		{
			MaxSkeletalAnimModelBuilder::errorMessage("failed to Open \"%s\" for writing", name);
			pIgame->ReleaseIGame();
			return FALSE;
		}
		is >> artbkgData;
	}
	*/
		
	pIgame->ReleaseIGame();

	return MaxSkeletalAnimModelBuilder::infoMessage("\"%s\" is Exported Sucessfully", path);
}