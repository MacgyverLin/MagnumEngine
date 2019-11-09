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

#include "EpicForcePhysicsExporter.h"

#define EpicForcePhysicsExporter_CLASS_ID	Class_ID(0x4ae67415, 0x7660586e)

class EpicForcePhysicsExporter : public SceneExport {
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
		EpicForcePhysicsExporter();
		~EpicForcePhysicsExporter();		

		int totalNumOfNode;
		Interface *ip;
public:
};



class EpicForcePhysicsExporterClassDesc : public ClassDesc2 
{
public:
	virtual int IsPublic() 							{ return TRUE; }
	virtual void* Create(BOOL /*loading = FALSE*/) 		{ return new EpicForcePhysicsExporter(); }
	virtual const TCHAR *	ClassName() 			{ return GetString(IDS_CLASS_NAME); }
	virtual SClass_ID SuperClassID() 				{ return SCENE_EXPORT_CLASS_ID; }
	virtual Class_ID ClassID() 						{ return EpicForcePhysicsExporter_CLASS_ID; }
	virtual const TCHAR* Category() 				{ return GetString(IDS_CATEGORY); }

	virtual const TCHAR* InternalName() 			{ return _T("EpicForcePhysicsExporter"); }	// returns fixed parsable name (scripter-visible name)
	virtual HINSTANCE HInstance() 					{ return hInstance; }					// returns owning module handle
	

};


ClassDesc2* GetEpicForcePhysicsExporterDesc() { 
	static EpicForcePhysicsExporterClassDesc EpicForcePhysicsExporterDesc;
	return &EpicForcePhysicsExporterDesc; 
}





INT_PTR CALLBACK EpicForcePhysicsExporterOptionsDlgProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam) {
	static EpicForcePhysicsExporter *imp = NULL;

	switch(message) {
		case WM_INITDIALOG:
			imp = (EpicForcePhysicsExporter *)lParam;
			CenterWindow(hWnd,GetParent(hWnd));
			return TRUE;

		case WM_COMMAND:

			if(wParam==IDC_OK)
			{
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


//--- EpicForcePhysicsExporter -------------------------------------------------------
EpicForcePhysicsExporter::EpicForcePhysicsExporter()
: totalNumOfNode(0)
, ip(0)
{
}

EpicForcePhysicsExporter::~EpicForcePhysicsExporter() 
{

}

int EpicForcePhysicsExporter::ExtCount()
{
	// Returns the number of file name extensions supported by the plug-in.
	return 1;
}

const TCHAR *EpicForcePhysicsExporter::Ext(int n)
{		
	return _T("physics");
}

const TCHAR *EpicForcePhysicsExporter::LongDesc()
{
	return _T("EpicForce Physics");
}
	
const TCHAR *EpicForcePhysicsExporter::ShortDesc() 
{			
	return _T("EpicForce Physics");
}

const TCHAR *EpicForcePhysicsExporter::AuthorName()
{			
	return _T("Mac Lin");
}

const TCHAR *EpicForcePhysicsExporter::CopyrightMessage() 
{	
	return _T("EpicForce Entertainment Limited");
}

const TCHAR *EpicForcePhysicsExporter::OtherMessage1() 
{		
	return _T("asd");
}

const TCHAR *EpicForcePhysicsExporter::OtherMessage2() 
{		
	return _T("asd");
}

unsigned int EpicForcePhysicsExporter::Version()
{				
	return 100;
}

void EpicForcePhysicsExporter::ShowAbout(HWND hWnd)
{			
	// Optional
}

BOOL EpicForcePhysicsExporter::SupportsOptions(int ext, DWORD options)
{
	// #pragma message(TODO("Decide which options to support.  Simply return true for each option supported by each Extension the exporter supports."))
	return TRUE;
}

// Dummy function for progress bar
DWORD WINAPI EpicForcePhysicsExporter::progressCBFunc(LPVOID arg)
{
	return(0);
}

int	EpicForcePhysicsExporter::DoExport(const TCHAR *path, ExpInterface *ei,Interface *i, BOOL suppressPrompts, DWORD options)
{
	// #pragma message(TODO("Implement the actual file Export here and"))
	DialogBoxParam(hInstance, 
				   MAKEINTRESOURCE(IDD_PANEL), 
				   GetActiveWindow(), 
				   EpicForcePhysicsExporterOptionsDlgProc, (LPARAM)this);

	float meterPerUnits = GetMasterScale(UNITS_METERS); 
	// save Interface Pointer
	ip = i;

	// Startup the progress bar.
	ip->ProgressStart("Exporting", TRUE, progressCBFunc, NULL);
	
	// We're done. Finish the progress bar.
	ip->ProgressEnd();

	return TRUE;
}