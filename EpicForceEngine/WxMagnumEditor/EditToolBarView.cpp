#include "EditToolBarView.h"
#include "ProjectView.h"
#include "Localization.h"
#include "BitmapCreater.h"

EditToolBarView::EditToolBarView(ProjectView *projectView_)
: wxAuiToolBar(projectView_, wxID_ANY, 
			   wxPoint(0, 0), wxSize(960, 16), 
			   wxAUI_TB_DEFAULT_STYLE /*| wxAUI_TB_OVERFLOW/* | wxAUI_TB_VERTICAL*/)
{
    this->SetForegroundColour(wxColour(  0,   0,   0, 255));
    this->SetBackgroundColour(wxColour(128, 128, 128, 255));

    this->SetToolBitmapSize(wxSize(16,16));
	this->AddTool(MenuCommand::MENU_EDIT_UNDO			, Localization::getEditUndo()	, wxArtProvider::GetBitmap(wxART_UNDO  ), Localization::getEditUndo()	);
	this->AddTool(MenuCommand::MENU_EDIT_REDO			, Localization::getEditRedo()	, wxArtProvider::GetBitmap(wxART_REDO  ), Localization::getEditRedo()	);
	this->AddSeparator();															 											  						 
	this->AddTool(MenuCommand::MENU_EDIT_CUT			, Localization::getEditCut()	, wxArtProvider::GetBitmap(wxART_CUT   ), Localization::getEditCut()	);
	this->AddTool(MenuCommand::MENU_EDIT_COPY			, Localization::getEditCopy()	, wxArtProvider::GetBitmap(wxART_COPY  ), Localization::getEditCopy()	);
	this->AddTool(MenuCommand::MENU_EDIT_PASTE			, Localization::getEditPaste()	, wxArtProvider::GetBitmap(wxART_PASTE ), Localization::getEditPaste()	);
	this->AddSeparator();																										  						
	this->AddTool(MenuCommand::MENU_EDIT_DELETE			, Localization::getEditDelete()	, wxArtProvider::GetBitmap(wxART_DELETE), Localization::getEditDelete()	);
    this->Realize();

	enableUIEvent();
}

EditToolBarView::~EditToolBarView()
{
}

void EditToolBarView::diableUI(unsigned int flags)
{
}

void EditToolBarView::enableUI(unsigned int flags)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////
// View request update Model

////////////////////////////////////////////////////////////////////////////////////////////////
// Model request update View
void EditToolBarView::notify(int flags, ProjectModelBase &projectModel, const Vector<unsigned char> &buffer)
{
	if(flags & ProjectModelBase::STATE_CHANGED)
	{
		if(projectModel.getCurrentState()=="DebugRun")
		{
			EnableTool(MenuCommand::MENU_EDIT_UNDO  , false);
			EnableTool(MenuCommand::MENU_EDIT_REDO  , false);
			EnableTool(MenuCommand::MENU_EDIT_CUT   , false);
			EnableTool(MenuCommand::MENU_EDIT_COPY  , false);
			EnableTool(MenuCommand::MENU_EDIT_PASTE , false);
			EnableTool(MenuCommand::MENU_EDIT_DELETE, false);
			Refresh();
		}
		else
		{
			EnableTool(MenuCommand::MENU_EDIT_UNDO  , false); // , true);
			EnableTool(MenuCommand::MENU_EDIT_REDO  , false); // , true);
			EnableTool(MenuCommand::MENU_EDIT_CUT   , true);
			EnableTool(MenuCommand::MENU_EDIT_COPY  , true);
			EnableTool(MenuCommand::MENU_EDIT_PASTE , true);
			EnableTool(MenuCommand::MENU_EDIT_DELETE, true);
			Refresh();
		}
	}
}

void EditToolBarView::disableUIEvent()
{
}

void EditToolBarView::enableUIEvent()
{
}