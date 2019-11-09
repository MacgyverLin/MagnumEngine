#ifndef _Localization_h_
#define _Localization_h_

#include "wxdef.h"

class Localization
{
public:
	enum Langunage
	{
		ENGLISH = 0,
		CHINESE = 1,
	};

	static void setLangunage(Langunage lang);
private:
	static wxString *texts;
public:
	static wxString &getTopWindowTitle					();
	static wxString &getSceneViewTitle					();
	static wxString &getResourceImporterViewTitle		();
	static wxString &getEntityViewCreatorsTitle			();
	static wxString &getDebugViewCreatorsTitle			();
	static wxString &getHierachyViewTitle				();
	static wxString &getInspectorViewCreatorsTitle		();	
	
	//////////////////////////////////////////////////////////////
	static wxString &getFileMenu						();
	static wxString &getFileProject						();
	static wxString &getFileProjectNew					();
	static wxString &getFileProjectNewOpen				();
	static wxString &getFileProjectNewSave				();
	static wxString &getFileScene						();
	static wxString &getFileSceneNew					();
	static wxString &getFileSceneOpen					();
	static wxString &getFileSceneSave					();
	static wxString &getFileSceneSaveAs					();
	static wxString &getFileSceneDelete					();
	static wxString &getFilePrefab						();
	static wxString &getFilePrefabOpen					();
	static wxString &getFilePrefabSave					();
	static wxString &getFileExit						();

	//////////////////////////////////////////////////////////////
	static wxString &getEditMenu						();
	static wxString &getEditUndo						();
	static wxString &getEditRedo						();
	static wxString &getEditCut							();
	static wxString &getEditCopy						();
	static wxString &getEditPaste						();
	static wxString &getEditDuplicate					();
	static wxString &getEditDelete						();
	static wxString &getEditFrameSelected				();
	static wxString &getEditFind						();
	static wxString &getEditSelectAll					();

	//////////////////////////////////////////////////////////////
	static wxString &getBuildMenu						();
	static wxString &getBuildWIN32						();
	static wxString &getBuildIOS						();
	static wxString &getBuildANDROID					();
	static wxString &getBuildWINMobile					();
	static wxString &getBuildPS3						();
	static wxString &getBuildPSP						();
	static wxString &getBuildPSV						();
	static wxString &getBuildWii						();
	static wxString &getBuildWiiU						();

	//////////////////////////////////////////////////////////////
	static wxString &getDebugMenu						();
	static wxString &getDebugRun						();
	static wxString &getDebugStop						();
	static wxString &getDebugPause						();
	static wxString &getDebugStep						();

	//////////////////////////////////////////////////////////////
	static wxString &getHelpMenu						();
	static wxString &getHelpHelp						();
	static wxString &getHelpAbout						();

	//////////////////////////////////////////////////////////////
	static wxString &getOperationMenu					();
	static wxString &getOperationSelection				();

	static wxString &getOperationMoveSelected			();
	static wxString &getOperationRotateSelected			();
	static wxString &getOperationScaleSelected			();

	static wxString &getOperationZoom					();
	static wxString &getOperationZoomExtent				();
	static wxString &getOperationZoomExtentSelected		();
	static wxString &getOperationZoomRegion				();
	static wxString &getOperationFov					();
	static wxString &getOperationPan					();
	static wxString &getOperationOrbit					();
	static wxString &getOperationOrbitSelected			();
	
	//////////////////////////////////////////////////////////////
	static wxString &getMenuMiscA						();
	static wxString &getMenuMiscAUpdateAssets			();
	static wxString &getMenuMiscA0						();
	static wxString &getMenuMiscA1						();
	static wxString &getMenuMiscA2						();
	static wxString &getMenuMiscA3						();
	static wxString &getMenuMiscA4						();
	static wxString &getMenuMiscA5						();
	static wxString &getMenuMiscA6						();
	static wxString &getMenuMiscA7						();
	static wxString &getMenuMiscA8						();
	static wxString &getMenuMiscA9						();

	//////////////////////////////////////////////////////////////
	static wxString &getMenuMiscB						();
	static wxString &getMenuMiscB0						();
	static wxString &getMenuMiscB1						();
	static wxString &getMenuMiscB2						();
	static wxString &getMenuMiscB3						();
	static wxString &getMenuMiscB4						();
	static wxString &getMenuMiscB5						();
	static wxString &getMenuMiscB6						();
	static wxString &getMenuMiscB7						();
	static wxString &getMenuMiscB8						();
	static wxString &getMenuMiscB9						();
	
	//////////////////////////////////////////////////////////////
	static wxString &getStatusBarReady					();

	//////////////////////////////////////////////////////////////
	static wxString &getCoordSysLocal					();
	static wxString &getCoordSysGlobal					();
	static wxString &getCoordSysParent					();
	static wxString &getCoordSysWorld					();
	static wxString &getCoordSysView					();

	//////////////////////////////////////////////////////////////
	static wxString &getAboutString1					();
	static wxString &getAboutString2					();

};

#endif