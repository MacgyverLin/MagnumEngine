#include "BuildModeToolBarView.h"
#include "ProjectView.h"
#include "win32logo_png.h"
#include "ioslogo_png.h"
#include "androidlogo_png.h"
#include "winmobile_png.h"
#include "ps3logo_png.h"
#include "psplogo_png.h"
#include "psvitalogo_png.h"
#include "wiilogo_png.h"
#include "wiiulogo_png.h"
#include "BitmapCreater.h"
#include "Localization.h"

BuildModeToolBarView::BuildModeToolBarView(ProjectView *projectView_)
: wxAuiToolBar(projectView_, wxID_ANY, 
			   wxPoint(0, 0), wxSize(960, 16), 
			   wxAUI_TB_DEFAULT_STYLE /*| wxAUI_TB_OVERFLOW/* | wxAUI_TB_VERTICAL*/)
{
	this->SetForegroundColour(projectView_->GetForegroundColour());
    this->SetBackgroundColour(projectView_->GetBackgroundColour());

	wxBitmap win32Bitmap		= BitmapCreater::getBitmapFromMemory(win32logo_png		, sizeof(win32logo_png		));
	wxBitmap iosBitmap			= BitmapCreater::getBitmapFromMemory(ioslogo_png		, sizeof(ioslogo_png		));
	wxBitmap androidBitmap		= BitmapCreater::getBitmapFromMemory(androidlogo_png	, sizeof(androidlogo_png	));
	wxBitmap winMobileBitmap	= BitmapCreater::getBitmapFromMemory(winmobile_png		, sizeof(winmobile_png		));
	wxBitmap ps3Bitmap			= BitmapCreater::getBitmapFromMemory(ps3logo_png		, sizeof(ps3logo_png		));
	wxBitmap pspBitmap			= BitmapCreater::getBitmapFromMemory(psplogo_png		, sizeof(psplogo_png		));
	wxBitmap psvitaBitmap		= BitmapCreater::getBitmapFromMemory(psvitalogo_png		, sizeof(psvitalogo_png		));
	wxBitmap wiiBitmap			= BitmapCreater::getBitmapFromMemory(wiilogo_png		, sizeof(wiilogo_png		));
	wxBitmap wiiuBitmap			= BitmapCreater::getBitmapFromMemory(wiiulogo_png		, sizeof(wiiulogo_png		));

	SetToolBitmapSize(wxSize(16,16));
	AddTool(MenuCommand::MENU_BUILD_PLATFORM_WIN32		, Localization::getBuildWIN32()		, win32Bitmap		, Localization::getBuildWIN32()		, wxITEM_RADIO);
	AddTool(MenuCommand::MENU_BUILD_PLATFORM_IOS		, Localization::getBuildIOS()		, iosBitmap			, Localization::getBuildIOS()		, wxITEM_RADIO);
	AddTool(MenuCommand::MENU_BUILD_PLATFORM_ANDROID	, Localization::getBuildANDROID()	, androidBitmap		, Localization::getBuildANDROID()	, wxITEM_RADIO);
	AddTool(MenuCommand::MENU_BUILD_PLATFORM_WINMOBILE	, Localization::getBuildWINMobile()	, winMobileBitmap	, Localization::getBuildWINMobile()	, wxITEM_RADIO);
	AddTool(MenuCommand::MENU_BUILD_PLATFORM_PS3		, Localization::getBuildPS3()		, ps3Bitmap			, Localization::getBuildPS3()		, wxITEM_RADIO);
	AddTool(MenuCommand::MENU_BUILD_PLATFORM_PSP		, Localization::getBuildPSP()		, pspBitmap			, Localization::getBuildPSP()		, wxITEM_RADIO);
	AddTool(MenuCommand::MENU_BUILD_PLATFORM_PSVITA		, Localization::getBuildPSV()		, psvitaBitmap		, Localization::getBuildPSV()		, wxITEM_RADIO);
	AddTool(MenuCommand::MENU_BUILD_PLATFORM_WII		, Localization::getBuildWii()		, wiiBitmap			, Localization::getBuildWii()		, wxITEM_RADIO);
	AddTool(MenuCommand::MENU_BUILD_PLATFORM_WIIU		, Localization::getBuildWiiU()		, wiiuBitmap		, Localization::getBuildWiiU()		, wxITEM_RADIO);
	Realize();

	enableUIEvent();
}

BuildModeToolBarView::~BuildModeToolBarView()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////
// View request update Model

////////////////////////////////////////////////////////////////////////////////////////////////
// Model request update View
void BuildModeToolBarView::notify(int flags, ProjectModelBase &projectModel, const Vector<unsigned char> &buffer)
{
	if(flags & ProjectModelBase::STATE_CHANGED)
	{
		if(projectModel.getCurrentState()=="DebugRun")
		{
			EnableTool(MenuCommand::MENU_BUILD_PLATFORM_WIN32		, false);
			EnableTool(MenuCommand::MENU_BUILD_PLATFORM_IOS			, false);
			EnableTool(MenuCommand::MENU_BUILD_PLATFORM_ANDROID		, false);
			EnableTool(MenuCommand::MENU_BUILD_PLATFORM_WINMOBILE	, false);
			EnableTool(MenuCommand::MENU_BUILD_PLATFORM_PS3			, false);
			EnableTool(MenuCommand::MENU_BUILD_PLATFORM_PSP			, false);
			EnableTool(MenuCommand::MENU_BUILD_PLATFORM_PSVITA		, false);
			EnableTool(MenuCommand::MENU_BUILD_PLATFORM_WII			, false);
			EnableTool(MenuCommand::MENU_BUILD_PLATFORM_WIIU		, false);

			Refresh();
		}
		else
		{
			EnableTool(MenuCommand::MENU_BUILD_PLATFORM_WIN32		, false);// true);
			EnableTool(MenuCommand::MENU_BUILD_PLATFORM_IOS			, false);// true);
			EnableTool(MenuCommand::MENU_BUILD_PLATFORM_ANDROID		, false);// true);
			EnableTool(MenuCommand::MENU_BUILD_PLATFORM_WINMOBILE	, false);// true);
			EnableTool(MenuCommand::MENU_BUILD_PLATFORM_PS3			, false);// true);
			EnableTool(MenuCommand::MENU_BUILD_PLATFORM_PSP			, false);// true);
			EnableTool(MenuCommand::MENU_BUILD_PLATFORM_PSVITA		, false);// true);
			EnableTool(MenuCommand::MENU_BUILD_PLATFORM_WII			, false);// true);
			EnableTool(MenuCommand::MENU_BUILD_PLATFORM_WIIU		, false);// true);
			Refresh();
		}
	}
}

void BuildModeToolBarView::disableUIEvent()
{
}

void BuildModeToolBarView::enableUIEvent()
{
}