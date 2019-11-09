#include "MiscBToolBarView.h"
#include "ProjectView.h"

#include "updateassets_png.h"
#include "miscb0_png.h"
#include "miscb1_png.h"
#include "miscb2_png.h"
#include "miscb3_png.h"
#include "miscb4_png.h"
#include "miscb5_png.h"
#include "miscb6_png.h"
#include "miscb7_png.h"
#include "miscb8_png.h"
#include "miscb9_png.h"
#include "BitmapCreater.h"
#include "Localization.h"

MiscBToolBarView::MiscBToolBarView(ProjectView *projectView_)
: wxAuiToolBar(projectView_, wxID_ANY, 
			   wxPoint(0, 0), wxSize(960, 16), 
			   wxAUI_TB_DEFAULT_STYLE /*| wxAUI_TB_OVERFLOW/* | wxAUI_TB_VERTICAL*/)
, coordSysComboBox(0)
{
	this->SetForegroundColour(projectView_->GetForegroundColour());
    this->SetBackgroundColour(projectView_->GetBackgroundColour());

	wxBitmap miscB0PngBitmap			= BitmapCreater::getBitmapFromMemory(miscb0_png, sizeof(miscb0_png));
	wxBitmap miscB1PngBitmap			= BitmapCreater::getBitmapFromMemory(miscb1_png, sizeof(miscb1_png));
	wxBitmap miscB2PngBitmap			= BitmapCreater::getBitmapFromMemory(miscb2_png, sizeof(miscb2_png));
	wxBitmap miscB3PngBitmap			= BitmapCreater::getBitmapFromMemory(miscb3_png, sizeof(miscb3_png));
	wxBitmap miscB4PngBitmap			= BitmapCreater::getBitmapFromMemory(miscb4_png, sizeof(miscb4_png));
	wxBitmap miscB5PngBitmap			= BitmapCreater::getBitmapFromMemory(miscb5_png, sizeof(miscb5_png));
	wxBitmap miscB6PngBitmap			= BitmapCreater::getBitmapFromMemory(miscb6_png, sizeof(miscb6_png));
	wxBitmap miscB7PngBitmap			= BitmapCreater::getBitmapFromMemory(miscb7_png, sizeof(miscb7_png));
	wxBitmap miscB8PngBitmap			= BitmapCreater::getBitmapFromMemory(miscb8_png, sizeof(miscb8_png));
	wxBitmap miscB9PngBitmap			= BitmapCreater::getBitmapFromMemory(miscb9_png, sizeof(miscb9_png));
	
	this->SetToolBitmapSize(wxSize(16,16));

	this->AddTool(MenuCommand::MENU_MISC_B_0				, Localization::getMenuMiscB0()				, miscB0PngBitmap			, Localization::getMenuMiscB0()				, wxITEM_RADIO);
	this->AddTool(MenuCommand::MENU_MISC_B_1				, Localization::getMenuMiscB1()				, miscB1PngBitmap			, Localization::getMenuMiscB1()				, wxITEM_RADIO);
	this->AddTool(MenuCommand::MENU_MISC_B_2				, Localization::getMenuMiscB2()				, miscB2PngBitmap			, Localization::getMenuMiscB2()				, wxITEM_RADIO);
	this->AddTool(MenuCommand::MENU_MISC_B_3				, Localization::getMenuMiscB3()				, miscB3PngBitmap			, Localization::getMenuMiscB3()				, wxITEM_RADIO);
	this->AddTool(MenuCommand::MENU_MISC_B_4				, Localization::getMenuMiscB4()				, miscB4PngBitmap			, Localization::getMenuMiscB4()				, wxITEM_RADIO);
	this->AddTool(MenuCommand::MENU_MISC_B_5				, Localization::getMenuMiscB5()				, miscB5PngBitmap			, Localization::getMenuMiscB5()				, wxITEM_RADIO);
	this->AddTool(MenuCommand::MENU_MISC_B_6				, Localization::getMenuMiscB6()				, miscB6PngBitmap			, Localization::getMenuMiscB6()				, wxITEM_RADIO);
	this->AddTool(MenuCommand::MENU_MISC_B_7				, Localization::getMenuMiscB7()				, miscB7PngBitmap			, Localization::getMenuMiscB7()				, wxITEM_RADIO);
	this->AddTool(MenuCommand::MENU_MISC_B_8				, Localization::getMenuMiscB8()				, miscB8PngBitmap			, Localization::getMenuMiscB8()				, wxITEM_RADIO);
	this->AddTool(MenuCommand::MENU_MISC_B_9				, Localization::getMenuMiscB9()				, miscB9PngBitmap			, Localization::getMenuMiscB9()				, wxITEM_RADIO);
	
	this->Realize();

	enableUIEvent();
}

MiscBToolBarView::~MiscBToolBarView()
{
}

void MiscBToolBarView::diableUI(unsigned int flags)
{
}

void MiscBToolBarView::enableUI(unsigned int flags)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////
// View request update Model

////////////////////////////////////////////////////////////////////////////////////////////////
// Model request update View
void MiscBToolBarView::notify(int flags, ProjectModelBase &projectModel, const Vector<unsigned char> &buffer)
{
	if(flags & ProjectModelBase::STATE_CHANGED)
	{
		if(projectModel.getCurrentState()=="DebugRun")
		{
			EnableTool(MenuCommand::MENU_MISC_B_0				, false);
			EnableTool(MenuCommand::MENU_MISC_B_1				, false);
			EnableTool(MenuCommand::MENU_MISC_B_2				, false);
			EnableTool(MenuCommand::MENU_MISC_B_3				, false);
			EnableTool(MenuCommand::MENU_MISC_B_4				, false);
			EnableTool(MenuCommand::MENU_MISC_B_5				, false);
			EnableTool(MenuCommand::MENU_MISC_B_6				, false);
			EnableTool(MenuCommand::MENU_MISC_B_7				, false);
			EnableTool(MenuCommand::MENU_MISC_B_8				, false);
			EnableTool(MenuCommand::MENU_MISC_B_9				, false);

			Refresh();
		}
		else
		{
			EnableTool(MenuCommand::MENU_MISC_B_0				, true);
			EnableTool(MenuCommand::MENU_MISC_B_1				, true);
			EnableTool(MenuCommand::MENU_MISC_B_2				, true);
			EnableTool(MenuCommand::MENU_MISC_B_3				, true);
			EnableTool(MenuCommand::MENU_MISC_B_4				, true);
			EnableTool(MenuCommand::MENU_MISC_B_5				, true);
			EnableTool(MenuCommand::MENU_MISC_B_6				, true);
			EnableTool(MenuCommand::MENU_MISC_B_7				, true);
			EnableTool(MenuCommand::MENU_MISC_B_8				, true);
			EnableTool(MenuCommand::MENU_MISC_B_9				, true);

			Refresh();
		}
	}
}

void MiscBToolBarView::disableUIEvent()
{
}

void MiscBToolBarView::enableUIEvent()
{
}