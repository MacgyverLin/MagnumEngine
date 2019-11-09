#include "FileToolBarView.h"
#include "ProjectView.h"
#include "Localization.h"

FileToolBarView::FileToolBarView(ProjectView *projectView_)
: wxAuiToolBar(projectView_, wxID_ANY, 
			   wxPoint(0, 0), wxSize(960, 16), 
			   wxAUI_TB_DEFAULT_STYLE /*| wxAUI_TB_OVERFLOW/* | wxAUI_TB_VERTICAL*/)
{
    this->SetForegroundColour(wxColour(  0,   0,   0, 255));
    this->SetBackgroundColour(wxColour(128, 128, 128, 255));

    this->SetToolBitmapSize(wxSize(48,48));
	this->AddTool(MenuCommand::MENU_FILE_SCENE_NEW 		, Localization::getFileSceneNew()		, wxArtProvider::GetBitmap(wxART_NEW)			, Localization::getFileSceneNew()		);
    this->AddTool(MenuCommand::MENU_FILE_SCENE_OPEN		, Localization::getFileSceneOpen()		, wxArtProvider::GetBitmap(wxART_FILE_OPEN)		, Localization::getFileSceneOpen()		);
    this->AddTool(MenuCommand::MENU_FILE_SCENE_SAVE		, Localization::getFileSceneSave()		, wxArtProvider::GetBitmap(wxART_FILE_SAVE)		, Localization::getFileSceneSave()		);
    this->AddTool(MenuCommand::MENU_FILE_SCENE_SAVE_AS	, Localization::getFileSceneSaveAs()	, wxArtProvider::GetBitmap(wxART_FILE_SAVE_AS)	, Localization::getFileSceneSaveAs()	);
    this->AddSeparator();
	this->AddTool(MenuCommand::MENU_FILE_EXIT			, Localization::getFileExit()			, wxArtProvider::GetBitmap(wxART_QUIT)			, Localization::getFileExit()			);
    this->Realize();

	enableUIEvent();
}

FileToolBarView::~FileToolBarView()
{
}

void FileToolBarView::diableUI(unsigned int flags)
{
}

void FileToolBarView::enableUI(unsigned int flags)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////
// View request update Model

////////////////////////////////////////////////////////////////////////////////////////////////
// Model request update View
void FileToolBarView::notify(int flags, ProjectModelBase &projectModel, const Vector<unsigned char> &buffer)
{
	if(flags & ProjectModelBase::STATE_CHANGED)
	{
		if(projectModel.getCurrentState()=="DebugRun")
		{
			EnableTool(MenuCommand::MENU_FILE_SCENE_NEW			, false);
			EnableTool(MenuCommand::MENU_FILE_SCENE_OPEN		, false);
			EnableTool(MenuCommand::MENU_FILE_SCENE_SAVE		, false);
			EnableTool(MenuCommand::MENU_FILE_SCENE_SAVE_AS		, false);
			EnableTool(MenuCommand::MENU_FILE_EXIT				, false);
			Refresh();
		}
		else
		{
			EnableTool(MenuCommand::MENU_FILE_SCENE_NEW			, true);
			EnableTool(MenuCommand::MENU_FILE_SCENE_OPEN		, true);
			EnableTool(MenuCommand::MENU_FILE_SCENE_SAVE		, true);
			EnableTool(MenuCommand::MENU_FILE_SCENE_SAVE_AS		, true);
			EnableTool(MenuCommand::MENU_FILE_EXIT				, true);
			Refresh();
		}
	}
}

void FileToolBarView::disableUIEvent()
{
}

void FileToolBarView::enableUIEvent()
{
}