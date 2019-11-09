#include "MiscAToolBarView.h"
#include "ProjectView.h"

#include "updateassets_png.h"
#include "misca0_png.h"
#include "misca1_png.h"
#include "misca2_png.h"
#include "misca3_png.h"
#include "misca4_png.h"
#include "misca5_png.h"
#include "misca6_png.h"
#include "misca7_png.h"
#include "misca8_png.h"
#include "misca9_png.h"
#include "BitmapCreater.h"
#include "Localization.h"

MiscAToolBarView::MiscAToolBarView(ProjectView *projectView_)
: wxAuiToolBar(projectView_, wxID_ANY, 
			   wxPoint(0, 0), wxSize(960, 16), 
			   wxAUI_TB_DEFAULT_STYLE /*| wxAUI_TB_OVERFLOW/* | wxAUI_TB_VERTICAL*/)
, coordSysComboBox(0)
{
	this->SetForegroundColour(projectView_->GetForegroundColour());
    this->SetBackgroundColour(projectView_->GetBackgroundColour());

	wxBitmap updateassetsPngBitmap		= BitmapCreater::getBitmapFromMemory(updateassets_png, sizeof(updateassets_png));
	wxBitmap miscA0PngBitmap			= BitmapCreater::getBitmapFromMemory(misca0_png, sizeof(misca0_png));
	wxBitmap miscA1PngBitmap			= BitmapCreater::getBitmapFromMemory(misca1_png, sizeof(misca1_png));
	wxBitmap miscA2PngBitmap			= BitmapCreater::getBitmapFromMemory(misca2_png, sizeof(misca2_png));
	wxBitmap miscA3PngBitmap			= BitmapCreater::getBitmapFromMemory(misca3_png, sizeof(misca3_png));
	wxBitmap miscA4PngBitmap			= BitmapCreater::getBitmapFromMemory(misca4_png, sizeof(misca4_png));
	wxBitmap miscA5PngBitmap			= BitmapCreater::getBitmapFromMemory(misca5_png, sizeof(misca5_png));
	wxBitmap miscA6PngBitmap			= BitmapCreater::getBitmapFromMemory(misca6_png, sizeof(misca6_png));
	wxBitmap miscA7PngBitmap			= BitmapCreater::getBitmapFromMemory(misca7_png, sizeof(misca7_png));
	wxBitmap miscA8PngBitmap			= BitmapCreater::getBitmapFromMemory(misca8_png, sizeof(misca8_png));
	wxBitmap miscA9PngBitmap			= BitmapCreater::getBitmapFromMemory(misca9_png, sizeof(misca9_png));
	
	this->SetToolBitmapSize(wxSize(16,16));

	this->AddTool(MenuCommand::MENU_MISC_A_UPDATE_ASSETS	, Localization::getMenuMiscAUpdateAssets()	, updateassetsPngBitmap		, Localization::getMenuMiscAUpdateAssets()	, wxITEM_RADIO);
	this->AddTool(MenuCommand::MENU_MISC_A_0				, Localization::getMenuMiscA0()				, miscA0PngBitmap			, Localization::getMenuMiscA0()				, wxITEM_RADIO);
	this->AddTool(MenuCommand::MENU_MISC_A_1				, Localization::getMenuMiscA1()				, miscA1PngBitmap			, Localization::getMenuMiscA1()				, wxITEM_RADIO);
	this->AddTool(MenuCommand::MENU_MISC_A_2				, Localization::getMenuMiscA2()				, miscA2PngBitmap			, Localization::getMenuMiscA2()				, wxITEM_RADIO);
	this->AddTool(MenuCommand::MENU_MISC_A_3				, Localization::getMenuMiscA3()				, miscA3PngBitmap			, Localization::getMenuMiscA3()				, wxITEM_RADIO);
	this->AddTool(MenuCommand::MENU_MISC_A_4				, Localization::getMenuMiscA4()				, miscA4PngBitmap			, Localization::getMenuMiscA4()				, wxITEM_RADIO);
	this->AddTool(MenuCommand::MENU_MISC_A_5				, Localization::getMenuMiscA5()				, miscA5PngBitmap			, Localization::getMenuMiscA5()				, wxITEM_RADIO);
	this->AddTool(MenuCommand::MENU_MISC_A_6				, Localization::getMenuMiscA6()				, miscA6PngBitmap			, Localization::getMenuMiscA6()				, wxITEM_RADIO);
	this->AddTool(MenuCommand::MENU_MISC_A_7				, Localization::getMenuMiscA7()				, miscA7PngBitmap			, Localization::getMenuMiscA7()				, wxITEM_RADIO);
	this->AddTool(MenuCommand::MENU_MISC_A_8				, Localization::getMenuMiscA8()				, miscA8PngBitmap			, Localization::getMenuMiscA8()				, wxITEM_RADIO);
	this->AddTool(MenuCommand::MENU_MISC_A_9				, Localization::getMenuMiscA9()				, miscA9PngBitmap			, Localization::getMenuMiscA9()				, wxITEM_RADIO);
	
	this->Realize();

	enableUIEvent();
}

MiscAToolBarView::~MiscAToolBarView()
{
}

void MiscAToolBarView::diableUI(unsigned int flags)
{
}

void MiscAToolBarView::enableUI(unsigned int flags)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////
// View request update Model

////////////////////////////////////////////////////////////////////////////////////////////////
// Model request update View
void MiscAToolBarView::notify(int flags, ProjectModelBase &projectModel, const Vector<unsigned char> &buffer)
{
	if(flags & ProjectModelBase::STATE_CHANGED)
	{
		if(projectModel.getCurrentState()=="DebugRun")
		{
			EnableTool(MenuCommand::MENU_MISC_A_UPDATE_ASSETS	, false);
			EnableTool(MenuCommand::MENU_MISC_A_0				, false);
			EnableTool(MenuCommand::MENU_MISC_A_1				, false);
			EnableTool(MenuCommand::MENU_MISC_A_2				, false);
			EnableTool(MenuCommand::MENU_MISC_A_3				, false);
			EnableTool(MenuCommand::MENU_MISC_A_4				, false);
			EnableTool(MenuCommand::MENU_MISC_A_5				, false);
			EnableTool(MenuCommand::MENU_MISC_A_6				, false);
			EnableTool(MenuCommand::MENU_MISC_A_7				, false);
			EnableTool(MenuCommand::MENU_MISC_A_8				, false);
			EnableTool(MenuCommand::MENU_MISC_A_9				, false);

			Refresh();
		}
		else
		{
			EnableTool(MenuCommand::MENU_MISC_A_UPDATE_ASSETS	, true);
			EnableTool(MenuCommand::MENU_MISC_A_0				, true);
			EnableTool(MenuCommand::MENU_MISC_A_1				, true);
			EnableTool(MenuCommand::MENU_MISC_A_2				, true);
			EnableTool(MenuCommand::MENU_MISC_A_3				, true);
			EnableTool(MenuCommand::MENU_MISC_A_4				, true);
			EnableTool(MenuCommand::MENU_MISC_A_5				, true);
			EnableTool(MenuCommand::MENU_MISC_A_6				, true);
			EnableTool(MenuCommand::MENU_MISC_A_7				, true);
			EnableTool(MenuCommand::MENU_MISC_A_8				, true);
			EnableTool(MenuCommand::MENU_MISC_A_9				, true);

			Refresh();
		}
	}
}

void MiscAToolBarView::disableUIEvent()
{
}

void MiscAToolBarView::enableUIEvent()
{
}