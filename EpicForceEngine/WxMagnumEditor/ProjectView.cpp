#include "ProjectView.h"
#include "Localization.h"
#include "EGLDriver20.h"
#include "wxProjectDlg.h"
using namespace Magnum;

GameDescriptor					gameDesc;
EGLDriver20						*eglDriver			= 0;
bool							lButtonDown			= false;
bool							mButtonDown			= false;
bool							rButtonDown			= false;
float							accX				= 0.0f;
float							accY				= 0.0f;
float							accZ				= 0.0f;
bool							isPaused			= false;
HWND							lastFocusedHWND		= NULL;
HWND							focusedHWND			= NULL;
InputData						inputData;

ProjectView	*ProjectView::_instance = 0;

ProjectView::ProjectView(const wxString& title)
: wxFrame(NULL, wxID_ANY, title, wxPoint(0, 0), wxSize(1600, 1024))
, viewWidth(640)
, viewHeight(480)
{
	assert(_instance==0);
	_instance =  this;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Localization::setLangunage((Localization::Langunage)(Config::instance().getLanguage()));

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	initUI();
	Center();
	
	m_mgr.SetFlags(wxAUI_MGR_ALLOW_FLOATING | wxAUI_MGR_TRANSPARENT_HINT | wxAUI_MGR_HINT_FADE | wxAUI_MGR_NO_VENETIAN_BLINDS_FADE | 
				   wxAUI_MGR_TRANSPARENT_DRAG | wxAUI_MGR_LIVE_RESIZE);

    m_mgr.Update();
}

ProjectView::~ProjectView()
{
    m_mgr.UnInit();

	assert(_instance!=0);

	_instance = 0;
}

void ProjectView::diableUI(unsigned int flags)
{
}

void ProjectView::enableUI(unsigned int flags)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////
// member function
ProjectView &ProjectView::instance()
{
	return *_instance;
}

bool ProjectView::initStage(int width, int height, int editorWidth, int editorHeight)
{
	viewWidth  = width;
	viewHeight = height;

	//////////////////////////////////////////////////////
	// initialize Game Entry Point
	if(!gameDesc.create("game.dll"))
		return false;
	
	/////////////////////////////////////////////////////
	// initialize Apps
	this->SetSize(editorWidth, editorHeight);

	/////////////////////////////////////////////////////
	// initialize Video
	eglDriver = new EGLDriver20();
	eglDriver->Init((HWND)sceneView->GetHWND());
	if(!eglDriver)
		return false;

	/////////////////////////////////////////////////////
	// initialize Engine
	wxStandardPaths &stdPath = wxStandardPaths::Get();
	String projectRootDir( fixBackslash(stdPath.GetDocumentsDir()) + "/" );

	gameDesc.setRawAssetRootDirectory(projectRootDir + "rawassets/");
	gameDesc.setAssetRootDirectory(projectRootDir + "device/application/bundle/");
	gameDesc.setDocumentDirectory(projectRootDir + "device/application/document/");
	gameDesc.setExternalDirectory(projectRootDir + "device/external/");
	gameDesc.setGetCurrentTimeMSFunc(getCurrentTimeMSFunc_);
	gameDesc.setPrintFunc(infoPrintFunc, debugPrintFunc, panicPrintFunc);
	gameDesc.setInitialScene("ModelViewEditor");
	gameDesc.addEditorProjectView((ProjectViewBase *)this);
	gameDesc.addEditorProjectView((ProjectViewBase *)resourceImporterView);
	gameDesc.addEditorProjectView((ProjectViewBase *)entityCreatorsView);
	gameDesc.addEditorProjectView((ProjectViewBase *)debugView);
	gameDesc.addEditorProjectView((ProjectViewBase *)sceneView);
	gameDesc.addEditorProjectView((ProjectViewBase *)fileToolBarView);
	gameDesc.addEditorProjectView((ProjectViewBase *)editToolBarView);
	gameDesc.addEditorProjectView((ProjectViewBase *)operationModeToolBarView);
	gameDesc.addEditorProjectView((ProjectViewBase *)playModeToolBarView);
	gameDesc.addEditorProjectView((ProjectViewBase *)buildModeToolBarView);
	gameDesc.addEditorProjectView((ProjectViewBase *)miscAToolBarView);
	gameDesc.addEditorProjectView((ProjectViewBase *)miscBToolBarView);
	gameDesc.addEditorProjectView((ProjectViewBase *)hierarchyView);
	gameDesc.addEditorProjectView((ProjectViewBase *)inspectorView);

	if( !gameDesc.onInitialize(width, height) )
		return false;

	return true;
}

bool ProjectView::processStage()
{
	updateKeyBoard();
	updateJoyPad();

	for(int i=0; i<inputData.mouseDownCnt; i++)
		gameDesc.onMouseDown(inputData.mouseDownModifier[i], inputData.mouseDownID[i], inputData.mouseDownX[i], inputData.mouseDownY[i]);
	inputData.mouseDownCnt	= 0;
	
	for(int i=0; i<inputData.mouseMoveCnt; i++)
		gameDesc.onMouseMoved(inputData.mouseMoveModifier[i], inputData.mouseDownID[i], inputData.mouseMoveX[i], inputData.mouseMoveY[i]);
	inputData.mouseMoveCnt	= 0;
	
	for(int i=0; i<inputData.mouseUpCnt; i++)
		gameDesc.onMouseUp(inputData.mouseUpModifier[i], inputData.mouseDownID[i], inputData.mouseUpX[i], inputData.mouseUpY[i]);
	inputData.mouseUpCnt	= 0;

	for(int i=0; i<inputData.wheelCnt; i++)
		gameDesc.onMouseWheel(inputData.wheelModifier[i], inputData.wheelX[i], inputData.wheelY[i], inputData.wheelAxis[i], inputData.wheelRotation[i]);
	inputData.wheelCnt	= 0;
	
	for(int i=0; i<inputData.keyDownCount; i++)
		gameDesc.onGamePadKeyDown(inputData.keyDownCode[i]);
	inputData.keyDownCount	= 0;
	
	for(int i=0; i<inputData.keyUpCount; i++)
		gameDesc.onGamePadKeyUp(inputData.keyUpCode[i]);
	inputData.keyUpCount	= 0;
	
	if(inputData.hasAcc)
		gameDesc.onAccelerationUpdate(inputData.accX, inputData.accY, inputData.accZ);
	inputData.hasAcc = false;
	
	gameDesc.onProcess();
		
	if(eglDriver)
		eglDriver->SwapBuffers();

	return true;
}

void ProjectView::terminateStage()
{
	/////////////////////////////////////////////////////
	// terminate Engine
	gameDesc.onTerminate();

	/////////////////////////////////////////////////////
	// terminate Video
	if(eglDriver)
	{
		eglDriver->Terminate();

		delete eglDriver;
		eglDriver = 0;
	}

	//////////////////////////////////////////////////////
	// terminate Launcher Entry Point

	/////////////////////////////////////////////////////
	// terminate entry point
	gameDesc.destroy();
}

void ProjectView::initUI()
{
	m_mgr.SetManagedWindow(this);
	m_mgr.GetArtProvider()->SetColor(wxAUI_DOCKART_BACKGROUND_COLOUR				, wxColor(255, 255, 255));
	m_mgr.GetArtProvider()->SetColor(wxAUI_DOCKART_SASH_COLOUR						, wxColor(147, 147, 147));
	m_mgr.GetArtProvider()->SetColor(wxAUI_DOCKART_BORDER_COLOUR					, wxColor( 81,  81,  81));
	m_mgr.GetArtProvider()->SetColor(wxAUI_DOCKART_INACTIVE_CAPTION_COLOUR			, wxColor(128, 128, 128));
	m_mgr.GetArtProvider()->SetColor(wxAUI_DOCKART_INACTIVE_CAPTION_GRADIENT_COLOUR , wxColor( 73,  73,  73));
	m_mgr.GetArtProvider()->SetColor(wxAUI_DOCKART_INACTIVE_CAPTION_TEXT_COLOUR     , wxColor(  0,   0,   0));
	m_mgr.GetArtProvider()->SetColor(wxAUI_DOCKART_ACTIVE_CAPTION_COLOUR			, wxColor(128, 128, 128));
	m_mgr.GetArtProvider()->SetColor(wxAUI_DOCKART_ACTIVE_CAPTION_GRADIENT_COLOUR   , wxColor( 73,  73,  73));
	m_mgr.GetArtProvider()->SetColor(wxAUI_DOCKART_ACTIVE_CAPTION_TEXT_COLOUR       , wxColor(  0,   0,   0));

	initMenuBar();

	sceneView = new SceneView(this);
	m_mgr.AddPane(sceneView, 
				  wxAuiPaneInfo().Name(wxT("SceneView")).Caption(Localization::getSceneViewTitle()).
				  BestSize(wxSize(960, 640)).
				  Position(0).Row(0).Centre().Layer(0).
				  CloseButton(false));

	inspectorView = new InspectorView(this);
	m_mgr.AddPane(inspectorView, 
	wxAuiPaneInfo().Name(wxT("InspectorView")).Caption(Localization::getInspectorViewCreatorsTitle()).
				  BestSize(wxSize(400, 640)).
				  Position(0).Row(0).Right().Layer(1).
				  CloseButton(false));

	resourceImporterView = new ResourceImporterView(this);
	m_mgr.AddPane(resourceImporterView, 
	wxAuiPaneInfo().Name(wxT("ResourceImporterView")).Caption(Localization::getResourceImporterViewTitle()).
				  BestSize(wxSize(640, 240)).
				  Position(0).Row(0).Bottom().Layer(2).
				  CloseButton(false));

	entityCreatorsView = new EntityCreatorsView(this);
	m_mgr.AddPane(entityCreatorsView, 
				  wxAuiPaneInfo().Name(wxT("EntityCreatorsView")).Caption(Localization::getEntityViewCreatorsTitle()).
				  BestSize(wxSize(320, 240)).
				  Position(1).Row(0).Bottom().Layer(2).
				  CloseButton(false));
	
	debugView = new DebugView(this);
	m_mgr.AddPane(debugView, 
	wxAuiPaneInfo().Name(wxT("DebugView")).Caption(Localization::getDebugViewCreatorsTitle()).
				  BestSize(wxSize(320, 240)).
				  Position(2).Row(0).Bottom().Layer(2).
				  CloseButton(false));

	fileToolBarView = new FileToolBarView(this);
    m_mgr.AddPane(fileToolBarView, 
				  wxAuiPaneInfo().Name(wxT("FileToolBarView")).Caption(wxT("File")).ToolbarPane().
				  Position(0).Row(0).Top().Layer(2).
				  CloseButton(false));

	editToolBarView = new EditToolBarView(this);
    m_mgr.AddPane(editToolBarView, 
				  wxAuiPaneInfo().Name(wxT("EditToolBarView")).Caption(wxT("Edit")).ToolbarPane().
				  Position(1).Row(0).Top().Layer(2).
				  CloseButton(false));

	operationModeToolBarView = new OperationModeToolBarView(this);
    m_mgr.AddPane(operationModeToolBarView, 
				  wxAuiPaneInfo().Name(wxT("OperationModeToolBarView")).Caption(wxT("Operation Mode")).ToolbarPane().
				  Position(2).Row(0).Top().Layer(2).
				  CloseButton(false));

	playModeToolBarView = new PlayModeToolBarView(this);
    m_mgr.AddPane(playModeToolBarView, 
				  wxAuiPaneInfo().Name(wxT("PlayModeToolBarView")).Caption(wxT("Play Mode")).ToolbarPane().
				  Position(3).Row(0).Top().Layer(2).
				  CloseButton(false));

	buildModeToolBarView = new BuildModeToolBarView(this);
    m_mgr.AddPane(buildModeToolBarView, 
				  wxAuiPaneInfo().Name(wxT("BuildModeToolBarView")).Caption(wxT("Build Mode")).ToolbarPane().
				  Position(4).Row(0).Top().Layer(2).
				  CloseButton(false));

	miscAToolBarView = new MiscAToolBarView(this);
    m_mgr.AddPane(miscAToolBarView, 
				  wxAuiPaneInfo().Name(wxT("MiscAToolBarView")).Caption(wxT("Miscellaneous A")).ToolbarPane().
				  Position(0).Row(0).Left().Layer(2).
				  CloseButton(false));

	miscBToolBarView = new MiscBToolBarView(this);
    m_mgr.AddPane(miscBToolBarView, 
				  wxAuiPaneInfo().Name(wxT("MiscBToolBarView")).Caption(wxT("Miscellaneous B")).ToolbarPane().
				  Position(1).Row(0).Left().Layer(2).
				  CloseButton(false));

	hierarchyView = new HierarchyView(this);
	m_mgr.AddPane(hierarchyView, 
				  wxAuiPaneInfo().Name(wxT("HierarchyView")).Caption(Localization::getHierachyViewTitle()).
				  BestSize(wxSize(320, 640)).
				  Position(0).Row(0).Right().Layer(2).
				  CloseButton(false).Right());

    CreateStatusBar();
	GetStatusBar()->SetStatusText(Localization::getStatusBarReady());
}

void ProjectView::initMenuBar()
{
    SetForegroundColour(wxColour(  0,   0,   0, 255));
    SetBackgroundColour(wxColour(128, 128, 128, 255));

	wxMenu *fileMenu = new wxMenu;
	wxMenu *fileProjectMenu = new wxMenu;
	wxMenu *fileSceneMenu = new wxMenu;
	wxMenu *filePrefabMenu = new wxMenu;
	fileMenu->AppendSubMenu(fileProjectMenu, Localization::getFileProject()														);
		fileProjectMenu->Append(MenuCommand::MENU_FILE_PROJECT_NEW 		, Localization::getFileProjectNew()						);
		fileProjectMenu->Append(MenuCommand::MENU_FILE_PROJECT_OPEN		, Localization::getFileProjectNewOpen()					);
		fileProjectMenu->Append(MenuCommand::MENU_FILE_PROJECT_SAVE		, Localization::getFileProjectNewSave()					);
	fileMenu->AppendSubMenu(fileSceneMenu, Localization::getFileScene()															);
		fileSceneMenu->Append(MenuCommand::MENU_FILE_SCENE_NEW 			, Localization::getFileSceneNew()						);
		fileSceneMenu->Append(MenuCommand::MENU_FILE_SCENE_OPEN			, Localization::getFileSceneOpen()						);
		fileSceneMenu->Append(MenuCommand::MENU_FILE_SCENE_SAVE			, Localization::getFileSceneSave()						);
		fileSceneMenu->Append(MenuCommand::MENU_FILE_SCENE_SAVE_AS		, Localization::getFileSceneSaveAs()					);
		fileSceneMenu->Append(MenuCommand::MENU_FILE_SCENE_DELETE		, Localization::getFileSceneDelete()					);
	fileMenu->AppendSubMenu(filePrefabMenu, Localization::getFilePrefab()														);
		filePrefabMenu->Append(MenuCommand::MENU_FILE_OPEN_PREFAB		, Localization::getFilePrefabOpen()						);
		filePrefabMenu->Append(MenuCommand::MENU_FILE_SAVE_PREFAB		, Localization::getFilePrefabSave()						);
	fileMenu->AppendSeparator();
	fileMenu->Append(MenuCommand::MENU_FILE_EXIT , Localization::getFileExit()													);

	wxMenu *editMenu = new wxMenu;
	wxMenu *editDeleteMenu = new wxMenu;
	editMenu->Append(MenuCommand::MENU_EDIT_UNDO			, Localization::getEditUndo()										);
	editMenu->Append(MenuCommand::MENU_EDIT_REDO			, Localization::getEditRedo()										);
	editMenu->AppendSeparator();											
	editMenu->Append(MenuCommand::MENU_EDIT_CUT				, Localization::getEditCut()										);
	editMenu->Append(MenuCommand::MENU_EDIT_COPY			, Localization::getEditCopy()										);
	editMenu->Append(MenuCommand::MENU_EDIT_PASTE			, Localization::getEditPaste()										);
	editMenu->AppendSeparator();											
	editMenu->Append(MenuCommand::MENU_EDIT_DUPLICATE		, Localization::getEditDuplicate()									);
	editMenu->Append(MenuCommand::MENU_EDIT_DELETE			, Localization::getEditDelete()										);

	wxMenu *operationMenu = new wxMenu;
	operationMenu->Append(MenuCommand::MENU_OPERATION_SELECTION				, Localization::getOperationSelection()				);
	operationMenu->Append(MenuCommand::MENU_OPERATION_MOVE_SELECTED			, Localization::getOperationMoveSelected()			);	
	operationMenu->Append(MenuCommand::MENU_OPERATION_ROTATE_SELECTED		, Localization::getOperationRotateSelected()		);
	operationMenu->Append(MenuCommand::MENU_OPERATION_SCALE_SELECTED		, Localization::getOperationScaleSelected()			);
	operationMenu->AppendSeparator();
	operationMenu->Append(MenuCommand::MENU_OPERATION_FRAME_SELECTED		, Localization::getEditFrameSelected()				);
	operationMenu->Append(MenuCommand::MENU_OPERATION_FIND					, Localization::getEditFind()						);
	operationMenu->Append(MenuCommand::MENU_OPERATION_SELECT_ALL			, Localization::getEditSelectAll()					);
	operationMenu->Append(MenuCommand::MENU_OPERATION_ZOOM					, Localization::getOperationZoom()					);
	operationMenu->Append(MenuCommand::MENU_OPERATION_ZOOM_EXTENT			, Localization::getOperationZoomExtent()			);
	operationMenu->Append(MenuCommand::MENU_OPERATION_ZOOM_EXTENT_SELECTED	, Localization::getOperationZoomExtentSelected()	);
	operationMenu->Append(MenuCommand::MENU_OPERATION_ZOOM_REGION			, Localization::getOperationZoomRegion()			);
	operationMenu->Append(MenuCommand::MENU_OPERATION_FOV					, Localization::getOperationFov()					);
	operationMenu->Append(MenuCommand::MENU_OPERATION_PAN					, Localization::getOperationPan()					);
	operationMenu->Append(MenuCommand::MENU_OPERATION_ORBIT					, Localization::getOperationOrbit()					);
	operationMenu->Append(MenuCommand::MENU_OPERATION_ORBIT_SELECTED		, Localization::getOperationOrbitSelected()			);

	wxMenu *miscAMenu = new wxMenu;
	miscAMenu->Append(MenuCommand::MENU_MISC_A_UPDATE_ASSETS					, Localization::getMenuMiscAUpdateAssets()			);
	miscAMenu->Append(MenuCommand::MENU_MISC_A_0								, Localization::getMenuMiscA0			()			);	
	miscAMenu->Append(MenuCommand::MENU_MISC_A_1								, Localization::getMenuMiscA1			()			);
	miscAMenu->Append(MenuCommand::MENU_MISC_A_2								, Localization::getMenuMiscA2			()			);
	miscAMenu->Append(MenuCommand::MENU_MISC_A_3								, Localization::getMenuMiscA3			()			);
	miscAMenu->Append(MenuCommand::MENU_MISC_A_4								, Localization::getMenuMiscA4			()			);
	miscAMenu->Append(MenuCommand::MENU_MISC_A_5								, Localization::getMenuMiscA5			()			);
	miscAMenu->Append(MenuCommand::MENU_MISC_A_6								, Localization::getMenuMiscA6			()			);
	miscAMenu->Append(MenuCommand::MENU_MISC_A_7								, Localization::getMenuMiscA7			()			);
	miscAMenu->Append(MenuCommand::MENU_MISC_A_8								, Localization::getMenuMiscA8			()			);
	miscAMenu->Append(MenuCommand::MENU_MISC_A_9								, Localization::getMenuMiscA9			()			);

	wxMenu *miscBMenu = new wxMenu;
	miscBMenu->Append(MenuCommand::MENU_MISC_B_0								, Localization::getMenuMiscB0			()			);	
	miscBMenu->Append(MenuCommand::MENU_MISC_B_1								, Localization::getMenuMiscB1			()			);
	miscBMenu->Append(MenuCommand::MENU_MISC_B_2								, Localization::getMenuMiscB2			()			);
	miscBMenu->Append(MenuCommand::MENU_MISC_B_3								, Localization::getMenuMiscB3			()			);
	miscBMenu->Append(MenuCommand::MENU_MISC_B_4								, Localization::getMenuMiscB4			()			);
	miscBMenu->Append(MenuCommand::MENU_MISC_B_5								, Localization::getMenuMiscB5			()			);
	miscBMenu->Append(MenuCommand::MENU_MISC_B_6								, Localization::getMenuMiscB6			()			);
	miscBMenu->Append(MenuCommand::MENU_MISC_B_7								, Localization::getMenuMiscB7			()			);
	miscBMenu->Append(MenuCommand::MENU_MISC_B_8								, Localization::getMenuMiscB8			()			);
	miscBMenu->Append(MenuCommand::MENU_MISC_B_9								, Localization::getMenuMiscB9			()			);

	wxMenu *debugMenu = new wxMenu;
	debugMenu->Append(MenuCommand::MENU_DEBUG_RUN  , Localization::getDebugRun()												);
	debugMenu->AppendSeparator();
	debugMenu->Append(MenuCommand::MENU_DEBUG_STOP , Localization::getDebugStop()												);
	debugMenu->Append(MenuCommand::MENU_DEBUG_PAUSE, Localization::getDebugPause()												);
	debugMenu->Append(MenuCommand::MENU_DEBUG_STEP , Localization::getDebugStep()												);

	wxMenu *buildMenu = new wxMenu;
	buildMenu->Append(MenuCommand::MENU_BUILD_PLATFORM_WIN32	, Localization::getBuildWIN32()									);
	buildMenu->AppendSeparator();
	buildMenu->Append(MenuCommand::MENU_BUILD_PLATFORM_IOS		, Localization::getBuildIOS()									);
	buildMenu->Append(MenuCommand::MENU_BUILD_PLATFORM_ANDROID	, Localization::getBuildANDROID()								);
	buildMenu->Append(MenuCommand::MENU_BUILD_PLATFORM_WINMOBILE, Localization::getBuildWINMobile()								);
	buildMenu->AppendSeparator();
	buildMenu->Append(MenuCommand::MENU_BUILD_PLATFORM_PS3		, Localization::getBuildPS3()									);
	buildMenu->Append(MenuCommand::MENU_BUILD_PLATFORM_PSP		, Localization::getBuildPSP()									);
	buildMenu->Append(MenuCommand::MENU_BUILD_PLATFORM_PSVITA	, Localization::getBuildPSV()									);
	buildMenu->AppendSeparator();
	buildMenu->Append(MenuCommand::MENU_BUILD_PLATFORM_WII		, Localization::getBuildWii()									);
	buildMenu->Append(MenuCommand::MENU_BUILD_PLATFORM_WIIU		, Localization::getBuildWiiU()									);

	wxMenu *helpMenu = new wxMenu;
	helpMenu->Append(MenuCommand::MENU_HELP_HELP , Localization::getHelpHelp()													);
	helpMenu->Append(MenuCommand::MENU_HELP_ABOUT, Localization::getHelpAbout()													);
																								
	wxMenuBar *menuBar = new wxMenuBar();
	menuBar->Append(fileMenu		, Localization::getFileMenu()																);
	menuBar->Append(editMenu		, Localization::getEditMenu()																);
	menuBar->Append(operationMenu	, Localization::getOperationMenu()															);
	menuBar->Append(debugMenu		, Localization::getDebugMenu()																);
	menuBar->Append(buildMenu		, Localization::getBuildMenu()																);	
	menuBar->Append(miscAMenu		, Localization::getMenuMiscA()																);	
	menuBar->Append(miscBMenu		, Localization::getMenuMiscB()																);	
	menuBar->Append(helpMenu		, Localization::getHelpMenu()																);

    SetMenuBar(menuBar);
}

//////////////////////////////////////////////////////////////////////////////////////
int keyCodes[] =
{
	VK_F9, VK_F10, VK_F11, VK_F12,		// KEY_HOME,		KEY_BACK,		KEY_MENU,		KEY_SEARCH,
	VK_F1,  VK_F2,  VK_F3,  VK_F4,		// KEY_SPECIAL0,	KEY_SPECIAL1,	KEY_SPECIAL2,	KEY_SPECIAL3,
	VK_F5,  VK_F6,  VK_F7,  VK_F8,		// KEY_SPECIAL4,	KEY_SPECIAL5,	KEY_SPECIAL6,	KEY_SPECIAL7,
	'W', 'S', 'A', 'D',					// KEYPAD0_UP,		KEYPAD0_DOWN,	KEYPAD0_LEFT,	KEYPAD0_RIGHT,
	'Z', 'X',							// KEYPAD0_SELECT,	KEYPAD0_START,
	'J', 'N', 'B', 'H',					// KEYPAD0_BUTTON0,	KEYPAD0_BUTTON1,KEYPAD0_BUTTON2,KEYPAD0_BUTTON3,
	'Y', 'G', 'V',						// KEYPAD0_L1,		KEYPAD0_L2,		KEYPAD0_L3,
	'O', 'K', 'M',						// KEYPAD0_R1,		KEYPAD0_R2,		KEYPAD0_R2,
};

int lastKeyStatus[] =
{
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 
	0, 0, 0, 0,
	0, 0, 0, 
	0, 0, 0, 
};

void ProjectView::updateKeyBoard()
{
	for(int i=0; i<sizeof(keyCodes)/sizeof(keyCodes[0]); i++)
	{
		int keyStatus = ::GetAsyncKeyState(keyCodes[i]);
		if( (keyStatus & 0x8000) ^ (lastKeyStatus[i] & 0x8000) )
		{
			if(keyStatus & 0x8000)
			{
				inputData.addKeyDown(i);
				//::OutputDebugString("inputData.addKeyDown\n");
			}
			else
			{
				inputData.addKeyUp(i);
				//::OutputDebugString("inputData.addKeyUp\n");
			}
		}
		lastKeyStatus[i] = keyStatus;
	}
}

//////////////////////////////////////////////////////////////////////////////////////
unsigned int lastJoypadButtonStatus[16] =
{
	0x00000000,	0x00000000,	0x00000000,	0x00000000,
	0x00000000,	0x00000000,	0x00000000,	0x00000000,
	0x00000000,	0x00000000,	0x00000000,	0x00000000,
	0x00000000,	0x00000000,	0x00000000,	0x00000000,
};

int joypadKeyCodes[] =
{
	8, 9,							// KEYPAD0_SELECT,	KEYPAD0_START,
	0, 1, 2, 3,						// KEYPAD0_BUTTON0,	KEYPAD0_BUTTON1,KEYPAD0_BUTTON2,KEYPAD0_BUTTON3,
	6, 4, 10,						// KEYPAD0_L1,		KEYPAD0_L2,		KEYPAD0_L3,
	7, 5, 11,						// KEYPAD0_R1,		KEYPAD0_R2,		KEYPAD0_R2,
};

unsigned int lastJoypadPOVStatus = 0x00000000;

int joypadPovKeyCodes[] =
{
	Input::KEYPAD0_UP,
	Input::KEYPAD0_RIGHT,
	Input::KEYPAD0_DOWN,
	Input::KEYPAD0_LEFT,
};

unsigned int getJoypadPOVStatus(unsigned int povValue)
{
	int value1 = (povValue / 9000);
	int value2 = (povValue - 9000 * value1) / 4500;
	
	int rval   = (1<<value1);
	if(value2!=0)
		rval |= (2<<value1);

	return rval;
}

void ProjectView::updateJoyPad()
{
	int numJoypads = joyGetNumDevs();
	for(int i=0; i<numJoypads && i<1; i++)
	{
		JOYINFOEX joyInfoEx;
		memset(&joyInfoEx, 0, sizeof(joyInfoEx));
		joyInfoEx.dwSize = sizeof(JOYINFOEX);
		joyInfoEx.dwFlags = JOY_RETURNALL;

		MMRESULT result = joyGetPosEx(i, &joyInfoEx);
		if(result==JOYERR_NOERROR)
		{
			int x = joyInfoEx.dwXpos;
			int y = joyInfoEx.dwYpos;
			int z = joyInfoEx.dwZpos;
			int r = joyInfoEx.dwRpos;			
			unsigned int joypadButtonStatus = joyInfoEx.dwButtons;
			unsigned int joypadButtonDelta = joypadButtonStatus ^ lastJoypadButtonStatus[i];

			//char buf[4096];
			//sprintf(buf, "%d %d %d %d\n", x, y, z, r);
			//::OutputDebugStringA(buf);
			//sprintf(buf, "%d\n", joyInfoEx.dwPOV);
			//::OutputDebugStringA(buf);
			/////////////////////////////////////////////////////////////////////////////////////////
			for(int j=0; j<sizeof(joypadKeyCodes)/sizeof(joypadKeyCodes[0]); j++)
			{
				unsigned int bit = (1<<joypadKeyCodes[j]);
				if(joypadButtonDelta & bit)
				{
					if(joypadButtonStatus & bit)
					{				
						inputData.addKeyDown(j + Input::KEYPAD0_SELECT);
					}
					else
					{
						inputData.addKeyUp(j + Input::KEYPAD0_SELECT);
					}
				}
			}

			lastJoypadButtonStatus[i]	= joypadButtonStatus;
			
			/////////////////////////////////////////////////////////////////////////////////////////
			unsigned int joypadPOVStatus = 0;
			if(joyInfoEx.dwPOV!=65535)
				joypadPOVStatus = getJoypadPOVStatus(joyInfoEx.dwPOV);
			unsigned int joypadPOVDelta = joypadPOVStatus ^ lastJoypadPOVStatus;

			for(int j=0; j<sizeof(joypadPovKeyCodes)/sizeof(joypadPovKeyCodes[0]); j++)
			{
				unsigned int bit = (1<<j);
				if(joypadPOVDelta & bit)
				{
					if(joypadPOVStatus & bit)
					{				
						inputData.addKeyDown(joypadPovKeyCodes[j]);
					}
					else
					{
						inputData.addKeyUp(joypadPovKeyCodes[j]);
					}
				}
			}

			lastJoypadPOVStatus			= joypadPOVStatus;
		}
		else
		{
			lastJoypadButtonStatus[i] = 0;
		}
	}
}

void ProjectView::addMouseUp(int modifier, int id, float x, float y)
{
	inputData.addMouseUp(modifier, id, x * 2.0f / viewWidth - 1.0f, (viewHeight - y) * 2.0f / viewHeight - 1.0f);
}

void ProjectView::addMouseDown(int modifier, int id, float x, float y)
{
	inputData.addMouseDown(modifier, id, x * 2.0f / viewWidth - 1.0f, (viewHeight - y) * 2.0f / viewHeight - 1.0f);
}

void ProjectView::addMouseMove(int modifier, int id, float x, float y)
{
	inputData.addMouseMove(modifier, id, x * 2.0f / viewWidth - 1.0f, (viewHeight - y) * 2.0f / viewHeight - 1.0f);
}

void ProjectView::addWheelMotion(int modifier, float x, float y, int axis, int rotation)
{
	inputData.addWheelMotion(modifier, x, y, axis, rotation);
}

const ClassIndexMap	&ProjectView::getClassIndexMap() const
{
	return classIndexMap;
}

String ProjectView::fixBackslash(const wxString &s)
{
	String rval(s);

	for(int i=0; i<rval.length(); i++)
	{
		if(rval[i] == '\\')
			rval[i] = '/';
	}

	return rval;
}

long long ProjectView::getCurrentTimeMSFunc_()
{
	return timeGetTime();
	return GetTickCount();
}

void ProjectView::infoPrintFunc(const char *buf_)
{
	ProjectView::instance().debugView->infoPrint("Info  : ");
	ProjectView::instance().debugView->infoPrint(buf_);
	ProjectView::instance().debugView->infoPrint("\n");
	//OutputDebugStringA(buf_);
	//OutputDebugStringA("\n");
}

void ProjectView::debugPrintFunc(int i, const char *buf_)
{
	ProjectView::instance().debugView->debugPrint(i, "Debug : ");
	ProjectView::instance().debugView->debugPrint(i, buf_);
	ProjectView::instance().debugView->debugPrint(i, "\n");
	//OutputDebugStringA(buf_);
	//OutputDebugStringA("\n");
}

void ProjectView::panicPrintFunc(const char *buf_)
{
	/*
	wxMessageDialog *dialog = new wxMessageDialog(NULL, buf_, wxT("Exclamation"), wxOK | wxICON_EXCLAMATION);

	if(dialog)
	{
		dialog->ShowModal();
		delete dialog;
	}

	ProjectView::instance().Close();
	*/

	OutputDebugStringA(buf_);
	OutputDebugStringA("\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////
// View request update Model
void ProjectView::onSize(wxSizeEvent &evt)
{
	m_mgr.Update();
}

void ProjectView::onMouseEnter(wxMouseEvent &evt)
{
	::OutputDebugStringA("onMouseEnter\n");
}

void ProjectView::onMouseLeave(wxMouseEvent &evt)
{
	::OutputDebugStringA("onMouseLeave\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////
void ProjectView::onMenuSelected(wxCommandEvent &evt)
{
	switch(evt.GetId())
	{
		case MenuCommand::MENU_FILE_PROJECT_NEW:
		case MenuCommand::MENU_FILE_PROJECT_OPEN:
		case MenuCommand::MENU_FILE_PROJECT_SAVE:
		case MenuCommand::MENU_FILE_SCENE_NEW:
		case MenuCommand::MENU_FILE_SCENE_OPEN:
		case MenuCommand::MENU_FILE_SCENE_SAVE:
		case MenuCommand::MENU_FILE_SCENE_SAVE_AS:
		case MenuCommand::MENU_FILE_SCENE_DELETE:
		case MenuCommand::MENU_FILE_OPEN_PREFAB:
		case MenuCommand::MENU_FILE_SAVE_PREFAB:
		case MenuCommand::MENU_FILE_EXIT:
			onFileMenuSelected(evt);
			break;

		case MenuCommand::MENU_EDIT_UNDO:
		case MenuCommand::MENU_EDIT_REDO:
		case MenuCommand::MENU_EDIT_CUT:
		case MenuCommand::MENU_EDIT_COPY:
		case MenuCommand::MENU_EDIT_PASTE:
		case MenuCommand::MENU_EDIT_DUPLICATE:
		case MenuCommand::MENU_EDIT_DELETE:
			onEditMenuSelected(evt);
			break;

		case MenuCommand::MENU_OPERATION_SELECTION:
		case MenuCommand::MENU_OPERATION_MOVE_SELECTED:
		case MenuCommand::MENU_OPERATION_ROTATE_SELECTED:
		case MenuCommand::MENU_OPERATION_SCALE_SELECTED:
		case MenuCommand::MENU_OPERATION_FRAME_SELECTED:
		case MenuCommand::MENU_OPERATION_FIND:
		case MenuCommand::MENU_OPERATION_SELECT_ALL:
		case MenuCommand::MENU_OPERATION_ZOOM:
		case MenuCommand::MENU_OPERATION_ZOOM_EXTENT:
		case MenuCommand::MENU_OPERATION_ZOOM_EXTENT_SELECTED:
		case MenuCommand::MENU_OPERATION_ZOOM_REGION:
		case MenuCommand::MENU_OPERATION_FOV:
		case MenuCommand::MENU_OPERATION_PAN:
		case MenuCommand::MENU_OPERATION_ORBIT:
		case MenuCommand::MENU_OPERATION_ORBIT_SELECTED:
			onOpsMenuSelected(evt);
			break;

		case MenuCommand::MENU_DEBUG_RUN:
		case MenuCommand::MENU_DEBUG_STOP:
		case MenuCommand::MENU_DEBUG_PAUSE:
		case MenuCommand::MENU_DEBUG_STEP:		
			onDebugRunMenuSelected(evt);
			break;

		case MenuCommand::MENU_BUILD_PLATFORM_WIN32:
		case MenuCommand::MENU_BUILD_PLATFORM_IOS:
		case MenuCommand::MENU_BUILD_PLATFORM_ANDROID:
		case MenuCommand::MENU_BUILD_PLATFORM_WINMOBILE:
		case MenuCommand::MENU_BUILD_PLATFORM_PS3:
		case MenuCommand::MENU_BUILD_PLATFORM_PSP:
		case MenuCommand::MENU_BUILD_PLATFORM_PSVITA:
		case MenuCommand::MENU_BUILD_PLATFORM_WII:
		case MenuCommand::MENU_BUILD_PLATFORM_WIIU:
			onBuildMenuSelected(evt);
			break;

		case MenuCommand::MENU_MISC_A_UPDATE_ASSETS:
		case MenuCommand::MENU_MISC_A_0:
		case MenuCommand::MENU_MISC_A_1:
		case MenuCommand::MENU_MISC_A_2:
		case MenuCommand::MENU_MISC_A_3:
		case MenuCommand::MENU_MISC_A_4:
		case MenuCommand::MENU_MISC_A_5:
		case MenuCommand::MENU_MISC_A_6:
		case MenuCommand::MENU_MISC_A_7:
		case MenuCommand::MENU_MISC_A_8:
		case MenuCommand::MENU_MISC_A_9:
			onMiscAMenuSelected(evt);
			break;

		case MenuCommand::MENU_MISC_B_0:
		case MenuCommand::MENU_MISC_B_1:
		case MenuCommand::MENU_MISC_B_2:
		case MenuCommand::MENU_MISC_B_3:
		case MenuCommand::MENU_MISC_B_4:
		case MenuCommand::MENU_MISC_B_5:
		case MenuCommand::MENU_MISC_B_6:
		case MenuCommand::MENU_MISC_B_7:
		case MenuCommand::MENU_MISC_B_8:
		case MenuCommand::MENU_MISC_B_9:
			onMiscBMenuSelected(evt);
			break;

		case MenuCommand::MENU_HELP_HELP:
		case MenuCommand::MENU_HELP_ABOUT:
			onHelpMenuSelected(evt);
			break;
	};
}

void ProjectView::onFileMenuSelected(wxCommandEvent &evt)
{
	switch(evt.GetId())
	{
		case MenuCommand::MENU_FILE_PROJECT_NEW:
		{
			wxProjectDlg projectDlg("Project", 1);
			int rval = projectDlg.ShowModal();
			if(rval==wxProjectDlg::wxID_OPENOTHER || rval==wxProjectDlg::wxID_OPEN)
			{
				Vector<unsigned char> buffer;
				MemOutputStream os(buffer);
				os << String("ChangeState") << String("FileProjectOpen") << String(projectDlg.getProjectFolderPath()) << true;
				GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
				/*
				ProjectModelBase &model = getModel();
				model.setCurrentProjectPath(projectDlg.getProjectFolderPath(), true);
				model.changeState("FileProjectOpen");
				*/
			}
			else if(rval==wxProjectDlg::wxID_CREATE)
			{
				Vector<unsigned char> buffer;
				MemOutputStream os(buffer);
				os << String("ChangeState") << String("FileProjectNew") << String(projectDlg.getProjectFolderPath()) << false;
				GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
				/*
				ProjectModelBase &model = getModel();
				model.setCurrentProjectPath(projectDlg.getProjectFolderPath(), false);
				model.changeState("FileProjectNew");
				*/
			}
		}
		break;
		case MenuCommand::MENU_FILE_PROJECT_OPEN:
		{
			wxProjectDlg projectDlg("Project", 0);
			int rval = projectDlg.ShowModal();
			if(rval==wxProjectDlg::wxID_OPENOTHER || rval==wxProjectDlg::wxID_OPEN)
			{
				Vector<unsigned char> buffer;
				MemOutputStream os(buffer);
				os << String("ChangeState") << String("FileProjectOpen") << String(projectDlg.getProjectFolderPath()) << true;
				GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
				/*
				ProjectModelBase &model = getModel();
				model.setCurrentProjectPath(projectDlg.getProjectFolderPath(), true);
				model.changeState("FileProjectOpen");
				*/
			}
			else if(rval==wxProjectDlg::wxID_CREATE)
			{
				Vector<unsigned char> buffer;
				MemOutputStream os(buffer);
				os << String("ChangeState") << String("FileProjectNew") << String(projectDlg.getProjectFolderPath()) << false;
				GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
				/*
				ProjectModelBase &model = getModel();
				model.setCurrentProjectPath(projectDlg.getProjectFolderPath(), false);
				model.changeState("FileProjectNew");
				*/
			}
		}
		break;
		case MenuCommand::MENU_FILE_PROJECT_SAVE:
		{
			Vector<unsigned char> buffer;
			MemOutputStream os(buffer);
			os << String("ChangeState") << String("FileProjectSave");
			GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
			/*
			ProjectModelBase &model = getModel();
			model.changeState("FileProjectSave");
			*/
		}
		break;
		case MenuCommand::MENU_FILE_SCENE_NEW:
		{
			ProjectModelBase &model = getModel();

			wxString projectDir(fixBackslash(model.getCurrentProjectPath()	));
			wxString sceneDir(fixBackslash(projectDir + "rawassets/scenes/" 	));

			wxFileDialog openDialog(this, wxT("New Scene"), sceneDir, wxEmptyString, 
									wxT("Magnum Scene files (*.MagnumScene)|*.MagnumScene"),
									wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition);
 
			// Creates a "open file" dialog with 4 file types
			if(openDialog.ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
			{
				wxString dialogPath(fixBackslash(openDialog.GetPath()			));
				wxString dialogDir(fixBackslash(openDialog.GetDirectory() + "/"	));
				String dialogFile(fixBackslash(openDialog.GetFilename()			));

				if(sceneDir.IsSameAs(dialogDir, false))
				{
					Vector<unsigned char> buffer;
					MemOutputStream os(buffer);
					os << String("ChangeState") << String("FileSceneNew") << String(dialogFile);
					GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
					/*
					model.setCurrentSceneFileName(dialogFile);
					model.changeState("FileSceneNew");
					*/
				}	
				else
				{
					wxString message;
					message.Printf("Scene file must be inside %s Directory", sceneDir);
					wxMessageBox(message, "Error");
				}	
			}
		}
		break;
		case MenuCommand::MENU_FILE_SCENE_OPEN:
		{
			ProjectModelBase &model = getModel();
			wxString projectDir		= fixBackslash(model.getCurrentProjectPath()	);
			wxString sceneDir		= fixBackslash(projectDir + "rawassets/scenes/" 	);

			wxFileDialog openDialog(this, wxT("Open Scene"), sceneDir, wxEmptyString, 
									wxT("Magnum Scene files (*.MagnumScene)|*.MagnumScene"),
									wxFD_OPEN | wxFD_FILE_MUST_EXIST, wxDefaultPosition);
 
			// Creates a "open file" dialog with 4 file types
			if(openDialog.ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
			{
				wxString dialogPath		= fixBackslash(openDialog.GetPath()					);
				wxString dialogDir		= fixBackslash(openDialog.GetDirectory() + "/"		);
				String dialogFile		= fixBackslash(openDialog.GetFilename()				);

				if(sceneDir.IsSameAs(dialogDir, false))
				{
					Vector<unsigned char> buffer;
					MemOutputStream os(buffer);
					os << String("ChangeState") << String("FileSceneOpen") << String(dialogFile);
					GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
					/*
					model.setCurrentSceneFileName(dialogFile);
					model.changeState("FileSceneOpen");
					*/
				}
				else
				{
					wxString message;
					message.Printf("Scene file must be inside %s Directory", sceneDir);
					wxMessageBox(message, "Error");
				}			
			}
		}
		break;
		case MenuCommand::MENU_FILE_SCENE_SAVE:
		{
			Vector<unsigned char> buffer;
			MemOutputStream os(buffer);
			os << String("ChangeState") << String("FileSceneSave");
			GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
			/*
			ProjectModelBase &model = getModel();
			model.changeState("FileSceneSave");
			*/
		}
		break;
		case MenuCommand::MENU_FILE_SCENE_SAVE_AS:
		{
			ProjectModelBase &model = getModel();
			wxString projectDir		= fixBackslash(model.getCurrentProjectPath()	);
			wxString sceneDir		= fixBackslash(projectDir + "rawassets/scenes/" 	);

			wxFileDialog saveDialog(this, wxT("Save Scene"), sceneDir, wxEmptyString,
									wxT("Magnum Scene files (*.MagnumScene)|*.MagnumScene"),
									wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition);
 
			// Creates a Save Dialog with 4 file types
			if(saveDialog.ShowModal() == wxID_OK) // If the user clicked "OK"
			{
				wxString dialogPath		= fixBackslash(saveDialog.GetPath()					);
				wxString dialogDir		= fixBackslash(saveDialog.GetDirectory() + "/"		);
				String dialogFile		= fixBackslash(saveDialog.GetFilename()				);

				if(sceneDir.IsSameAs(dialogDir, false))
				{
					Vector<unsigned char> buffer;
					MemOutputStream os(buffer);
					os << String("ChangeState") << String("FileSceneSaveAs") << String(dialogFile);
					GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
					/*
					model.setCurrentSceneFileName(dialogFile);
					model.changeState("FileSceneSaveAs");
					*/
				}
				else
				{
					wxString message;
					message.Printf("Scene file must be inside %s Directory", sceneDir);
					wxMessageBox(message, "Error");
				}
			}

		}
		break;
		case MenuCommand::MENU_FILE_SCENE_DELETE:
		{
			ProjectModelBase &model = getModel();
			wxString projectDir		= fixBackslash(model.getCurrentProjectPath()	);
			wxString sceneDir		= fixBackslash(projectDir + "rawassets/scenes/" 	);

			wxFileDialog openDialog(this, _("Select file to delete"), sceneDir, wxEmptyString, 
									_("Magnum Scene files (*.MagnumScene)|*.MagnumScene"),
									wxFD_OPEN | wxFD_FILE_MUST_EXIST, wxDefaultPosition);
 
			// Creates a "open file" dialog with 4 file types
			if(openDialog.ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
			{
				wxString dialogPath		= fixBackslash(openDialog.GetPath()					);
				wxString dialogDir		= fixBackslash(openDialog.GetDirectory() + "/"		);
				String dialogFile		= fixBackslash(openDialog.GetFilename()				);

				if(sceneDir.IsSameAs(dialogDir, false))
				{
					Vector<unsigned char> buffer;
					MemOutputStream os(buffer);
					os << String("ChangeState") << String("FileSceneDelete") << String(dialogFile);
					GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
					/*
					model.setCurrentSceneFileName(dialogFile);
					model.changeState("FileSceneDelete");
					*/
				}
				else
				{
					wxString message;
					message.Printf("Scene file must be inside %s Directory", sceneDir);
					wxMessageBox(message, "Error");
				}
			}
		}
		break;
		case MenuCommand::MENU_FILE_OPEN_PREFAB:
		{
			ProjectModelBase &model = getModel();
			wxString projectDir		= fixBackslash(model.getCurrentProjectPath()	);
			wxString prefabDir		= fixBackslash(projectDir + "rawassets/prefabs/" 	);

			wxFileDialog openDialog(this, wxT("Open Prefab"), prefabDir, wxEmptyString, 
									wxT("Magnum Prefab files (*.magnumPrefab)|*.magnumPrefab"),
									wxFD_OPEN | wxFD_FILE_MUST_EXIST, wxDefaultPosition);
 
			// Creates a "open file" dialog with 4 file types
			if(openDialog.ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
			{
				wxString dialogPath		= fixBackslash(openDialog.GetPath()					);
				wxString dialogDir		= fixBackslash(openDialog.GetDirectory() + "/"		);
				String dialogFile		= fixBackslash(openDialog.GetFilename()				);

				if(prefabDir.IsSameAs(dialogDir, false))
				{
					Vector<unsigned char> buffer;
					MemOutputStream os(buffer);
					os << String("ChangeState") << String("FilePrefabOpen") << String(dialogFile);
					GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
					/*
					model.setPrefabFileName(dialogFile);
					model.changeState("FilePrefabOpen");
					*/
				}
				else
				{
					wxString message;
					message.Printf("Prefab file must be inside %s Directory", prefabDir);
					wxMessageBox(message, "Error");
				}
			}
		}
		break;
		case MenuCommand::MENU_FILE_SAVE_PREFAB:
		{
			ProjectModelBase &model = getModel();
			wxString projectDir		= fixBackslash(model.getCurrentProjectPath()	);
			wxString prefabDir		= fixBackslash(projectDir + "rawassets/prefabs/"	);

			wxFileDialog saveDialog(this, wxT("Save Prefab"), prefabDir, wxEmptyString,
									wxT("Magnum Prefab files (*.magnumPrefab)|*.magnumPrefab"),
									wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition);
 
			// Creates a Save Dialog with 4 file types
			if(saveDialog.ShowModal() == wxID_OK) // If the user clicked "OK"
			{
				wxString dialogPath		= fixBackslash(saveDialog.GetPath()					);
				wxString dialogDir		= fixBackslash(saveDialog.GetDirectory() + "/"		);
				String dialogFile		= fixBackslash(saveDialog.GetFilename()				);

				if(prefabDir.IsSameAs(dialogDir, false))
				{
					Vector<unsigned char> buffer;
					MemOutputStream os(buffer);
					os << String("ChangeState") << String("FilePrefabSave") << String(dialogFile);
					GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
					/*
					model.setPrefabFileName(dialogFile);
					model.changeState("FilePrefabSave");
					*/
				}
				else
				{
					wxString message;
					message.Printf("Prefab file must be inside %s Directory", prefabDir); 
					wxMessageBox(message, "Error");
				}
			}
		}
		break;
		case MenuCommand::MENU_FILE_EXIT:
		{
			Vector<unsigned char> buffer;
			MemOutputStream os(buffer);
			os << String("ChangeState") << String("FileExit");
			GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
			/*
			ProjectModelBase &model = getModel();
			model.changeState("FileExit");
			*/

			Close();
		}
		break;
	};
}

void ProjectView::onEditMenuSelected(wxCommandEvent &evt)
{
	switch(evt.GetId())
	{
		case MenuCommand::MENU_EDIT_UNDO:
		break;
		case MenuCommand::MENU_EDIT_REDO:
		break;
		case MenuCommand::MENU_EDIT_CUT:
		{
			Vector<unsigned char> buffer;
			MemOutputStream os(buffer);
			os << String("ChangeState") << String("EditCut");
			GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
			/*
			ProjectModelBase &model = getModel();
			model.changeState("EditCut");
			*/
		}
		break;
		case MenuCommand::MENU_EDIT_COPY:
		{
			Vector<unsigned char> buffer;
			MemOutputStream os(buffer);
			os << String("ChangeState") << String("EditCopy");
			GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
			/*
			ProjectModelBase &model = getModel();
			model.changeState("EditCopy");
			*/
		}
		break;
		case MenuCommand::MENU_EDIT_PASTE:
		{
			Vector<unsigned char> buffer;
			MemOutputStream os(buffer);
			os << String("ChangeState") << String("EditPaste");
			GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
			/*
			ProjectModelBase &model = getModel();
			model.changeState("EditPaste");
			*/
		}
		break;
		case MenuCommand::MENU_EDIT_DUPLICATE:
		{
			Vector<unsigned char> buffer;
			MemOutputStream os(buffer);
			os << String("ChangeState") << String("EditDuplicate");
			GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
			/*
			ProjectModelBase &model = getModel();
			model.changeState("EditDuplicate");
			*/
		}
		break;
		case MenuCommand::MENU_EDIT_DELETE:
		{
			Vector<unsigned char> buffer;
			MemOutputStream os(buffer);
			os << String("ChangeState") << String("EditDelete");
			GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
			/*
			ProjectModelBase &model = getModel();
			model.changeState("EditDelete");
			*/
		}
		break;
	};
}

void ProjectView::onOpsMenuSelected(wxCommandEvent &evt)
{
	switch(evt.GetId())
	{
		case MenuCommand::MENU_OPERATION_SELECTION:
		{
			Vector<unsigned char> buffer;
			MemOutputStream os(buffer);
			os << String("ChangeState") << String("OperationSelectEntity");
			GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
			/*
			ProjectModelBase &model = getModel();
			model.changeState("OperationSelectEntity");
			*/
		}
		break;
		case MenuCommand::MENU_OPERATION_MOVE_SELECTED:
		{
			Vector<unsigned char> buffer;
			MemOutputStream os(buffer);
			os << String("ChangeState") << String("OperationMoveSelected");
			GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
			/*
			ProjectModelBase &model = getModel();
			model.changeState("OperationMoveSelected");
			*/
		}
		break;
		case MenuCommand::MENU_OPERATION_ROTATE_SELECTED:
		{
			Vector<unsigned char> buffer;
			MemOutputStream os(buffer);
			os << String("ChangeState") << String("OperationRotateSelected");
			GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
			/*
			ProjectModelBase &model = getModel();
			model.changeState("OperationRotateSelected");
			*/
		}
		break;
		case MenuCommand::MENU_OPERATION_SCALE_SELECTED:
		{
			Vector<unsigned char> buffer;
			MemOutputStream os(buffer);
			os << String("ChangeState") << String("OperationScaleSelected");
			GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
			/*
			ProjectModelBase &model = getModel();
			model.changeState("OperationScaleSelected");
			*/
		}
		break;

		case MenuCommand::MENU_OPERATION_FRAME_SELECTED:
		{
			Vector<unsigned char> buffer;
			MemOutputStream os(buffer);
			os << String("ChangeState") << String("OperationFrameSelected");
			GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
			/*
			ProjectModelBase &model = getModel();
			model.changeState("OperationFrameSelected");
			*/
		}
		break;
		case MenuCommand::MENU_OPERATION_FIND:
		{
			Vector<unsigned char> buffer;
			MemOutputStream os(buffer);
			os << String("ChangeState") << String("OperationFind");
			GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
			/*
			ProjectModelBase &model = getModel();
			model.changeState("OperationFind");
			*/
		}
		break;
		case MenuCommand::MENU_OPERATION_SELECT_ALL:
		{
			Vector<unsigned char> buffer;
			MemOutputStream os(buffer);
			os << String("ChangeState") << String("OperationSelectAll");
			GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
			/*
			ProjectModelBase &model = getModel();
			model.changeState("OperationSelectAll");
			*/
		}
		break;

		case MenuCommand::MENU_OPERATION_ZOOM:
		{
			Vector<unsigned char> buffer;
			MemOutputStream os(buffer);
			os << String("ChangeState") << String("OperationZoom");
			GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
			/*
			ProjectModelBase &model = getModel();
			model.changeState("OperationZoom");
			*/
		}
		break;
		case MenuCommand::MENU_OPERATION_ZOOM_EXTENT:
		{
			Vector<unsigned char> buffer;
			MemOutputStream os(buffer);
			os << String("ChangeState") << String("OperationZoomExtent");
			GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
			/*
			ProjectModelBase &model = getModel();
			model.changeState("OperationZoomExtent");
			*/
		}
		break;
		case MenuCommand::MENU_OPERATION_ZOOM_EXTENT_SELECTED:
		{
			Vector<unsigned char> buffer;
			MemOutputStream os(buffer);
			os << String("ChangeState") << String("OperationZoomExtentSelected");
			GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
			/*
			ProjectModelBase &model = getModel();
			model.changeState("OperationZoomExtentSelected");
			*/
		}
		break;
		case MenuCommand::MENU_OPERATION_ZOOM_REGION:
		{
			Vector<unsigned char> buffer;
			MemOutputStream os(buffer);
			os << String("ChangeState") << String("OperationZoomRegion");
			GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
			/*
			ProjectModelBase &model = getModel();
			model.changeState("OperationZoomRegion");
			*/
		}
		break;
		case MenuCommand::MENU_OPERATION_FOV:
		{
			Vector<unsigned char> buffer;
			MemOutputStream os(buffer);
			os << String("ChangeState") << String("OperationFov");
			GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
			/*
			ProjectModelBase &model = getModel();
			model.changeState("OperationFov");
			*/
		}
		break;
		case MenuCommand::MENU_OPERATION_PAN:
		{
			Vector<unsigned char> buffer;
			MemOutputStream os(buffer);
			os << String("ChangeState") << String("OperationPan");
			GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
			/*
			ProjectModelBase &model = getModel();
			model.changeState("OperationPan");
			*/
		}
		break;
		case MenuCommand::MENU_OPERATION_ORBIT:
		{
			Vector<unsigned char> buffer;
			MemOutputStream os(buffer);
			os << String("ChangeState") << String("OperationOrbit");
			GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
			/*
			ProjectModelBase &model = getModel();
			model.changeState("OperationOrbit");
			*/
		}
		break;
		case MenuCommand::MENU_OPERATION_ORBIT_SELECTED:
		{
			Vector<unsigned char> buffer;
			MemOutputStream os(buffer);
			os << String("ChangeState") << String("OperationOrbitSelected");
			GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
			/*
			ProjectModelBase &model = getModel();
			model.changeState("OperationOrbitSelected");
			*/
		};
		break;
	};
}

void ProjectView::onDebugRunMenuSelected(wxCommandEvent &evt)
{
	switch(evt.GetId())
	{
		case MenuCommand::MENU_DEBUG_RUN:
		{
			Vector<unsigned char> buffer;
			MemOutputStream os(buffer);
			os << String("ChangeState") << String("DebugRun");
			GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
			/*
			ProjectModelBase &model = getModel();
			model.changeState("DebugRun");
			*/
		}
		break;
		case MenuCommand::MENU_DEBUG_STOP:
		{
			Vector<unsigned char> buffer;
			MemOutputStream os(buffer);
			os << String("ChangeState") << String("DebugStop");
			GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
			/*
			ProjectModelBase &model = getModel();
			model.changeState("DebugStop");
			*/
		}
		break;
		case MenuCommand::MENU_DEBUG_PAUSE:
		{
		}
		break;
		case MenuCommand::MENU_DEBUG_STEP:
		{
		}
		break;
	};
}

void ProjectView::onBuildMenuSelected(wxCommandEvent &evt)
{
	switch(evt.GetId())
	{
		case MenuCommand::MENU_BUILD_PLATFORM_WIN32:
		case MenuCommand::MENU_BUILD_PLATFORM_IOS:
		case MenuCommand::MENU_BUILD_PLATFORM_ANDROID:
		case MenuCommand::MENU_BUILD_PLATFORM_WINMOBILE:
		case MenuCommand::MENU_BUILD_PLATFORM_PS3:
		case MenuCommand::MENU_BUILD_PLATFORM_PSP:
		case MenuCommand::MENU_BUILD_PLATFORM_PSVITA:
		case MenuCommand::MENU_BUILD_PLATFORM_WII:
		case MenuCommand::MENU_BUILD_PLATFORM_WIIU:
		break;
	};
}

void ProjectView::onMiscAMenuSelected(wxCommandEvent &evt)
{
	switch(evt.GetId())
	{
		case MenuCommand::MENU_MISC_A_UPDATE_ASSETS:
		{
			Vector<unsigned char> buffer;
			MemOutputStream os(buffer);
			os << String("ChangeState") << String("CheckingRawAssets");
			GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
			/*
			ProjectModelBase &model = getModel();
			model.changeState("CheckingRawAssets");
			*/
		}
		break;
		case MenuCommand::MENU_MISC_A_0:
		break;
		case MenuCommand::MENU_MISC_A_1:
		break;
		case MenuCommand::MENU_MISC_A_2:
		break;
		case MenuCommand::MENU_MISC_A_3:
		break;
		case MenuCommand::MENU_MISC_A_4:
		break;
		case MenuCommand::MENU_MISC_A_5:
		break;
		case MenuCommand::MENU_MISC_A_6:
		break;
		case MenuCommand::MENU_MISC_A_7:
		break;
		case MenuCommand::MENU_MISC_A_8:
		break;
		case MenuCommand::MENU_MISC_A_9:
		break;
	};
}

void ProjectView::onMiscBMenuSelected(wxCommandEvent &evt)
{
	switch(evt.GetId())
	{
		case MenuCommand::MENU_MISC_B_0:
		break;
		case MenuCommand::MENU_MISC_B_1:
		break;
		case MenuCommand::MENU_MISC_B_2:
		break;
		case MenuCommand::MENU_MISC_B_3:
		break;
		case MenuCommand::MENU_MISC_B_4:
		break;
		case MenuCommand::MENU_MISC_B_5:
		break;
		case MenuCommand::MENU_MISC_B_6:
		break;
		case MenuCommand::MENU_MISC_B_7:
		break;
		case MenuCommand::MENU_MISC_B_8:
		break;
		case MenuCommand::MENU_MISC_B_9:
		break;
	};
}

#include <windows.h>
void ProjectView::onHelpMenuSelected(wxCommandEvent &evt)
{
	switch(evt.GetId())
	{
		case MenuCommand::MENU_HELP_HELP:
			ShellExecute(0, _("open"), _("http://www.google.com"), 0, 0, SW_SHOWNORMAL);
		break;
		case MenuCommand::MENU_HELP_ABOUT:
			wxMessageBox(Localization::getAboutString1(), Localization::getAboutString2(), wxOK, this);
		break;
	};
}

////////////////////////////////////////////////////////////////////////////////////////////////
// Model request update View
void ProjectView::notify(int flags, ProjectModelBase &projectModel, const Vector<unsigned char> &buffer)
{
	if(flags & ProjectModelBase::CLASSIDXMAP)
	{
		classIndexMap.clear();
		for(int i=0; i<projectModel.getNumClassIndices(); i++)
		{
			const char *className = projectModel.getClass(i);
			
			classIndexMap.addClass(className);
		}
	}
	if(flags & ProjectModelBase::STATE_CHANGED)
	{
		wxMenuBar *menuBar = this->GetMenuBar();

		if(projectModel.getCurrentState()=="DebugRun")
		{
			menuBar->Enable(MenuCommand::MENU_FILE_PROJECT_NEW				, false);
			menuBar->Enable(MenuCommand::MENU_FILE_PROJECT_OPEN				, false);
			menuBar->Enable(MenuCommand::MENU_FILE_PROJECT_SAVE				, false);

			menuBar->Enable(MenuCommand::MENU_FILE_SCENE_NEW				, false);
			menuBar->Enable(MenuCommand::MENU_FILE_SCENE_OPEN				, false);
			menuBar->Enable(MenuCommand::MENU_FILE_SCENE_SAVE				, false);
			menuBar->Enable(MenuCommand::MENU_FILE_SCENE_SAVE_AS			, false);
			menuBar->Enable(MenuCommand::MENU_FILE_SCENE_DELETE				, false);
			menuBar->Enable(MenuCommand::MENU_FILE_OPEN_PREFAB				, false);
			menuBar->Enable(MenuCommand::MENU_FILE_SAVE_PREFAB				, false);
			menuBar->Enable(MenuCommand::MENU_FILE_EXIT						, false);
		}
		else
		{
			menuBar->Enable(MenuCommand::MENU_FILE_PROJECT_NEW				, true);
			menuBar->Enable(MenuCommand::MENU_FILE_PROJECT_OPEN				, true);
			menuBar->Enable(MenuCommand::MENU_FILE_PROJECT_SAVE				, true);

			menuBar->Enable(MenuCommand::MENU_FILE_SCENE_NEW				, true);
			menuBar->Enable(MenuCommand::MENU_FILE_SCENE_OPEN				, true);
			menuBar->Enable(MenuCommand::MENU_FILE_SCENE_SAVE				, true);
			menuBar->Enable(MenuCommand::MENU_FILE_SCENE_SAVE_AS			, true);
			menuBar->Enable(MenuCommand::MENU_FILE_SCENE_DELETE				, true);
			menuBar->Enable(MenuCommand::MENU_FILE_OPEN_PREFAB				, true);
			menuBar->Enable(MenuCommand::MENU_FILE_SAVE_PREFAB				, true);
			menuBar->Enable(MenuCommand::MENU_FILE_EXIT						, true);
		}

		if(projectModel.getCurrentState()=="DebugRun")
		{
			menuBar->Enable(MenuCommand::MENU_EDIT_UNDO						, false);
			menuBar->Enable(MenuCommand::MENU_EDIT_REDO						, false);
			menuBar->Enable(MenuCommand::MENU_EDIT_CUT						, false);
			menuBar->Enable(MenuCommand::MENU_EDIT_COPY						, false);
			menuBar->Enable(MenuCommand::MENU_EDIT_PASTE					, false);
			menuBar->Enable(MenuCommand::MENU_EDIT_DELETE					, false);
		}
		else
		{
			menuBar->Enable(MenuCommand::MENU_EDIT_UNDO						, false); // , true);
			menuBar->Enable(MenuCommand::MENU_EDIT_REDO						, false); // , true);
			menuBar->Enable(MenuCommand::MENU_EDIT_CUT						, true);
			menuBar->Enable(MenuCommand::MENU_EDIT_COPY						, true);
			menuBar->Enable(MenuCommand::MENU_EDIT_PASTE					, true);
			menuBar->Enable(MenuCommand::MENU_EDIT_DELETE					, true);
		}

		/////////////////////////////////////////////////////
		// Ops menu
		if(projectModel.getCurrentState()=="DebugRun")
		{
			menuBar->Enable(MenuCommand::MENU_OPERATION_SELECTION			, false);
			menuBar->Enable(MenuCommand::MENU_OPERATION_MOVE_SELECTED		, false);
			menuBar->Enable(MenuCommand::MENU_OPERATION_ROTATE_SELECTED		, false);
			menuBar->Enable(MenuCommand::MENU_OPERATION_SCALE_SELECTED		, false);

			menuBar->Enable(MenuCommand::MENU_OPERATION_ZOOM				, false);
			menuBar->Enable(MenuCommand::MENU_OPERATION_ZOOM_EXTENT			, false);
			menuBar->Enable(MenuCommand::MENU_OPERATION_ZOOM_EXTENT_SELECTED, false);
			menuBar->Enable(MenuCommand::MENU_OPERATION_ZOOM_REGION			, false);
			menuBar->Enable(MenuCommand::MENU_OPERATION_FOV					, false);
			menuBar->Enable(MenuCommand::MENU_OPERATION_PAN					, false);
			menuBar->Enable(MenuCommand::MENU_OPERATION_ORBIT				, false);
			menuBar->Enable(MenuCommand::MENU_OPERATION_ORBIT_SELECTED		, false);
		}
		else
		{
			menuBar->Enable(MenuCommand::MENU_OPERATION_SELECTION			, true);
			menuBar->Enable(MenuCommand::MENU_OPERATION_MOVE_SELECTED		, true);
			menuBar->Enable(MenuCommand::MENU_OPERATION_ROTATE_SELECTED		, true);
			menuBar->Enable(MenuCommand::MENU_OPERATION_SCALE_SELECTED		, true);

			menuBar->Enable(MenuCommand::MENU_OPERATION_ZOOM				, true);
			menuBar->Enable(MenuCommand::MENU_OPERATION_ZOOM_EXTENT			, true);
			menuBar->Enable(MenuCommand::MENU_OPERATION_ZOOM_EXTENT_SELECTED, true);
			menuBar->Enable(MenuCommand::MENU_OPERATION_ZOOM_REGION			, true);
			menuBar->Enable(MenuCommand::MENU_OPERATION_FOV					, true);
			menuBar->Enable(MenuCommand::MENU_OPERATION_PAN					, true);
			menuBar->Enable(MenuCommand::MENU_OPERATION_ORBIT				, true);
			menuBar->Enable(MenuCommand::MENU_OPERATION_ORBIT_SELECTED		, true);
		}

		/////////////////////////////////////////////////////
		// Debug menu
		if(projectModel.getCurrentState()=="DebugRun")
		{
			menuBar->Enable(MenuCommand::MENU_DEBUG_RUN						, false);
			menuBar->Enable(MenuCommand::MENU_DEBUG_STOP					, true );
			menuBar->Enable(MenuCommand::MENU_DEBUG_PAUSE					, true );
			menuBar->Enable(MenuCommand::MENU_DEBUG_STEP					, true );
		}
		else
		{
			menuBar->Enable(MenuCommand::MENU_DEBUG_RUN						, true );
			menuBar->Enable(MenuCommand::MENU_DEBUG_STOP					, false);
			menuBar->Enable(MenuCommand::MENU_DEBUG_PAUSE					, false);
			menuBar->Enable(MenuCommand::MENU_DEBUG_STEP					, false);
		}

		/////////////////////////////////////////////////////
		// Excutable menu
		if(projectModel.getCurrentState()=="DebugRun")
		{
			menuBar->Enable(MenuCommand::MENU_BUILD_PLATFORM_WIN32			, false);
			menuBar->Enable(MenuCommand::MENU_BUILD_PLATFORM_IOS			, false);
			menuBar->Enable(MenuCommand::MENU_BUILD_PLATFORM_ANDROID		, false);
			menuBar->Enable(MenuCommand::MENU_BUILD_PLATFORM_WINMOBILE		, false);
			menuBar->Enable(MenuCommand::MENU_BUILD_PLATFORM_PS3			, false);
			menuBar->Enable(MenuCommand::MENU_BUILD_PLATFORM_PSP			, false);
			menuBar->Enable(MenuCommand::MENU_BUILD_PLATFORM_PSVITA			, false);
			menuBar->Enable(MenuCommand::MENU_BUILD_PLATFORM_WII			, false);
			menuBar->Enable(MenuCommand::MENU_BUILD_PLATFORM_WIIU			, false);
		}
		else
		{
			menuBar->Enable(MenuCommand::MENU_BUILD_PLATFORM_WIN32			, false); // , true);
			menuBar->Enable(MenuCommand::MENU_BUILD_PLATFORM_IOS			, false); // , true);
			menuBar->Enable(MenuCommand::MENU_BUILD_PLATFORM_ANDROID		, false); // , true);
			menuBar->Enable(MenuCommand::MENU_BUILD_PLATFORM_WINMOBILE		, false); // , true);
			menuBar->Enable(MenuCommand::MENU_BUILD_PLATFORM_PS3			, false); // , true);
			menuBar->Enable(MenuCommand::MENU_BUILD_PLATFORM_PSP			, false); // , true);
			menuBar->Enable(MenuCommand::MENU_BUILD_PLATFORM_PSVITA			, false); // , true);
			menuBar->Enable(MenuCommand::MENU_BUILD_PLATFORM_WII			, false); // , true);
			menuBar->Enable(MenuCommand::MENU_BUILD_PLATFORM_WIIU			, false); // , true);
		}

		/////////////////////////////////////////////////////
		// Misc A menu
		if(projectModel.getCurrentState()=="DebugRun")
		{
			menuBar->Enable(MenuCommand::MENU_MISC_A_UPDATE_ASSETS	, false);
			menuBar->Enable(MenuCommand::MENU_MISC_A_0				, false);
			menuBar->Enable(MenuCommand::MENU_MISC_A_1				, false);
			menuBar->Enable(MenuCommand::MENU_MISC_A_2				, false);
			menuBar->Enable(MenuCommand::MENU_MISC_A_3				, false);
			menuBar->Enable(MenuCommand::MENU_MISC_A_4				, false);
			menuBar->Enable(MenuCommand::MENU_MISC_A_5				, false);
			menuBar->Enable(MenuCommand::MENU_MISC_A_6				, false);
			menuBar->Enable(MenuCommand::MENU_MISC_A_7				, false);
			menuBar->Enable(MenuCommand::MENU_MISC_A_8				, false);
			menuBar->Enable(MenuCommand::MENU_MISC_A_9				, false);
		}
		else
		{
			menuBar->Enable(MenuCommand::MENU_MISC_A_UPDATE_ASSETS	, true);
			menuBar->Enable(MenuCommand::MENU_MISC_A_0				, true);
			menuBar->Enable(MenuCommand::MENU_MISC_A_1				, true);
			menuBar->Enable(MenuCommand::MENU_MISC_A_2				, true);
			menuBar->Enable(MenuCommand::MENU_MISC_A_3				, true);
			menuBar->Enable(MenuCommand::MENU_MISC_A_4				, true);
			menuBar->Enable(MenuCommand::MENU_MISC_A_5				, true);
			menuBar->Enable(MenuCommand::MENU_MISC_A_6				, true);
			menuBar->Enable(MenuCommand::MENU_MISC_A_7				, true);
			menuBar->Enable(MenuCommand::MENU_MISC_A_8				, true);
			menuBar->Enable(MenuCommand::MENU_MISC_A_9				, true);
		}

		/////////////////////////////////////////////////////
		// Misc B menu
		if(projectModel.getCurrentState()=="DebugRun")
		{
			menuBar->Enable(MenuCommand::MENU_MISC_B_0				, false);
			menuBar->Enable(MenuCommand::MENU_MISC_B_1				, false);
			menuBar->Enable(MenuCommand::MENU_MISC_B_2				, false);
			menuBar->Enable(MenuCommand::MENU_MISC_B_3				, false);
			menuBar->Enable(MenuCommand::MENU_MISC_B_4				, false);
			menuBar->Enable(MenuCommand::MENU_MISC_B_5				, false);
			menuBar->Enable(MenuCommand::MENU_MISC_B_6				, false);
			menuBar->Enable(MenuCommand::MENU_MISC_B_7				, false);
			menuBar->Enable(MenuCommand::MENU_MISC_B_8				, false);
			menuBar->Enable(MenuCommand::MENU_MISC_B_9				, false);
		}
		else
		{
			menuBar->Enable(MenuCommand::MENU_MISC_B_0				, true);
			menuBar->Enable(MenuCommand::MENU_MISC_B_1				, true);
			menuBar->Enable(MenuCommand::MENU_MISC_B_2				, true);
			menuBar->Enable(MenuCommand::MENU_MISC_B_3				, true);
			menuBar->Enable(MenuCommand::MENU_MISC_B_4				, true);
			menuBar->Enable(MenuCommand::MENU_MISC_B_5				, true);
			menuBar->Enable(MenuCommand::MENU_MISC_B_6				, true);
			menuBar->Enable(MenuCommand::MENU_MISC_B_7				, true);
			menuBar->Enable(MenuCommand::MENU_MISC_B_8				, true);
			menuBar->Enable(MenuCommand::MENU_MISC_B_9				, true);
		}

		/////////////////////////////////////////////////////
		// Help menu
		if(projectModel.getCurrentState()=="DebugRun")
		{
			menuBar->Enable(MenuCommand::MENU_HELP_HELP						, true);
			menuBar->Enable(MenuCommand::MENU_HELP_ABOUT					, true);
		}
		else
		{
			menuBar->Enable(MenuCommand::MENU_HELP_HELP						, true);
			menuBar->Enable(MenuCommand::MENU_HELP_ABOUT					, true);
		}

		menuBar->Refresh();
	}
	if(flags & ProjectModelBase::PROJECT_DIALOG)
	{
		wxProjectDlg projectDlg("Project", 0);
		int rval = projectDlg.ShowModal();
		if(rval==wxProjectDlg::wxID_OPENOTHER)
		{
			getModel().setCurrentProjectPath(projectDlg.getProjectFolderPath(), true);
		}
		else if(rval==wxProjectDlg::wxID_OPEN)
		{
			getModel().setCurrentProjectPath(projectDlg.getProjectFolderPath(), true);
		}
		else if(rval==wxProjectDlg::wxID_CREATE)
		{
			getModel().setCurrentProjectPath(projectDlg.getProjectFolderPath(), false);
		}
	}
	if(flags & ProjectModelBase::SCENE_CHANGED)
	{
		wxString title = Localization::getTopWindowTitle();
		title += " (Build 0001) ";
		title += this->getModel().getCurrentProjectPath();
		title += " - ";
		title += this->getModel().getCurrentSceneFileName();

		this->SetTitle(title);
	}
}

void ProjectView::disableUIEvent()
{
	Disconnect(wxEVT_COMMAND_MENU_SELECTED	, wxCommandEventHandler(ProjectView::onMenuSelected), 0, this);
	Disconnect(wxEVT_SIZE					, wxSizeEventHandler(ProjectView::onSize)			, 0, this);
	Disconnect(wxEVT_SIZE					, wxSizeEventHandler(ProjectView::onSize)			, 0, this);

	Disconnect(wxEVT_ENTER_WINDOW 			, wxMouseEventHandler(ProjectView::onMouseEnter)	, 0, this);
	Disconnect(wxEVT_LEAVE_WINDOW 			, wxMouseEventHandler(ProjectView::onMouseLeave)	, 0, this);	
}

void ProjectView::enableUIEvent()
{
	Connect(wxEVT_COMMAND_MENU_SELECTED	, wxCommandEventHandler(ProjectView::onMenuSelected), 0, this);
	Connect(wxEVT_SIZE					, wxSizeEventHandler(ProjectView::onSize)			, 0, this);

	Connect(wxEVT_ENTER_WINDOW 			, wxMouseEventHandler(ProjectView::onMouseEnter)	, 0, this);
	Connect(wxEVT_LEAVE_WINDOW 			, wxMouseEventHandler(ProjectView::onMouseLeave)	, 0, this);
}