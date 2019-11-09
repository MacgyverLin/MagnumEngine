#include "PlayModeToolBarView.h"
#include "ProjectView.h"
#include "runbutton_png.h"
#include "stopbutton_png.h"
#include "stepbutton_png.h"
#include "pausebutton_png.h"
#include "BitmapCreater.h"
#include "Localization.h"

PlayModeToolBarView::PlayModeToolBarView(ProjectView *projectView_)
: wxAuiToolBar(projectView_, wxID_ANY, 
			   wxPoint(0, 0), wxSize(960, 16), 
			   wxAUI_TB_DEFAULT_STYLE /*| wxAUI_TB_OVERFLOW/* | wxAUI_TB_VERTICAL*/)
{
	this->SetForegroundColour(projectView_->GetForegroundColour());
    this->SetBackgroundColour(projectView_->GetBackgroundColour());

	wxBitmap runBitmap						= BitmapCreater::getBitmapFromMemory(runbutton_png				, sizeof(runbutton_png			));
	wxBitmap stopBitmap						= BitmapCreater::getBitmapFromMemory(stopbutton_png				, sizeof(stopbutton_png			));
	wxBitmap pauseBitmap					= BitmapCreater::getBitmapFromMemory(pausebutton_png			, sizeof(pausebutton_png		));
	wxBitmap stepBitmap						= BitmapCreater::getBitmapFromMemory(stepbutton_png				, sizeof(stepbutton_png			));

	this->SetToolBitmapSize(wxSize(16,16));
	this->AddTool(MenuCommand::MENU_DEBUG_RUN	, Localization::getDebugRun()	, runBitmap		, Localization::getDebugRun()	, wxITEM_RADIO);
	this->AddTool(MenuCommand::MENU_DEBUG_STOP	, Localization::getDebugStop()	, stopBitmap	, Localization::getDebugStop()	, wxITEM_RADIO);
	this->AddTool(MenuCommand::MENU_DEBUG_PAUSE	, Localization::getDebugPause()	, pauseBitmap	, Localization::getDebugPause()	, wxITEM_RADIO);
	this->AddTool(MenuCommand::MENU_DEBUG_STEP	, Localization::getDebugStep()	, stepBitmap	, Localization::getDebugStep()	, wxITEM_RADIO);
	this->Realize();

	enableUIEvent();
}

PlayModeToolBarView::~PlayModeToolBarView()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////
// View request update Model

////////////////////////////////////////////////////////////////////////////////////////////////
// Model request update View
void PlayModeToolBarView::notify(int flags, ProjectModelBase &projectModel, const Vector<unsigned char> &buffer)
{
	if(flags & ProjectModelBase::STATE_CHANGED)
	{
		if(projectModel.getCurrentState()=="DebugRun")
		{
			EnableTool(MenuCommand::MENU_DEBUG_RUN  , false);
			EnableTool(MenuCommand::MENU_DEBUG_STOP , true );
			EnableTool(MenuCommand::MENU_DEBUG_PAUSE, true );
			EnableTool(MenuCommand::MENU_DEBUG_STEP , true );
			Refresh();
		}
		else
		{
			EnableTool(MenuCommand::MENU_DEBUG_RUN  , true );
			EnableTool(MenuCommand::MENU_DEBUG_STOP , false);
			EnableTool(MenuCommand::MENU_DEBUG_PAUSE, false);
			EnableTool(MenuCommand::MENU_DEBUG_STEP , false);
			Refresh();
		}
	}
}

void PlayModeToolBarView::disableUIEvent()
{
}

void PlayModeToolBarView::enableUIEvent()
{
}