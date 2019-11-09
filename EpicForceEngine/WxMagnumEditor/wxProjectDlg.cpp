#include "wxProjectDlg.h"
#include "Config.h"

#define I_WAS_INSERTED_PAGE_NAME        wxT("Inserted")
#define RADIOBUTTONS_PAGE_NAME          wxT("Radiobuttons")
#define VETO_PAGE_NAME                  wxT("Veto")
#define MAXIMIZED_BUTTON_PAGE_NAME      wxT("Maximized button")

wxProjectDlg::wxProjectDlg(const wxString & title, int startPage)
: wxDialog(0, -1, title, wxDefaultPosition, wxSize(640, 400))
, projectFolderPath("")
, selectListIndex(-1)
{
    int flags = wxBK_TOP;// wxBK_BOTTOM; wxBK_LEFT; wxBK_RIGHT;

	wxBookCtrlBase *m_bookCtrl	= new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, flags);

	wxBoxSizer *vBox = new wxBoxSizer(wxVERTICAL);
	SetSizer(vBox);
		vBox->Add(m_bookCtrl, 1, wxGROW | wxALL, 12);

	createInitialPages(m_bookCtrl);

	m_bookCtrl->ChangeSelection(startPage);
}

const wxString &wxProjectDlg::getProjectFolderPath() const
{
	return projectFolderPath;
}

void wxProjectDlg::createInitialPages(wxBookCtrlBase *parent)
{
    wxPanel *panel1 = addOpenProjectPage(parent);
    parent->AddPage(panel1, "Open Project", false, getIconIndex(parent) );

    wxPanel *panel2 = addCreateProjectPage(parent);
    parent->AddPage(panel2, "Create new Project", false, getIconIndex(parent) );
}

wxPanel *wxProjectDlg::addOpenProjectPage(wxBookCtrlBase *parent)
{
	wxPanel *panel = new wxPanel(parent);

	wxStaticText *staticTextCtrl			= new wxStaticText(panel, wxID_ANY, "Select recently opened project:");
	
	recentProjectPathCtrl					= new wxListCtrl(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize,
															 wxLC_REPORT | wxLC_NO_HEADER | wxLC_SINGLE_SEL);
	wxListItem info;
	recentProjectPathCtrl->InsertColumn(0, info);
	recentProjectPathCtrl->SetColumnWidth(0, 320);

	Vector<wxString> recentProjectPaths;
	recentProjectPaths = Config::instance().getRecentProjectPaths();
	for(int i=recentProjectPaths.length()-1; i>=0; i--)
	{
		recentProjectPathCtrl->InsertItem(0, recentProjectPaths[i]);
	}

	wxButton *openOtherButton				= new wxButton(panel, wxID_OPENOTHER, wxT("Open Other..."), wxDefaultPosition, wxDefaultSize);
	wxButton *openButton					= new wxButton(panel, wxID_OPEN, wxT("Open"), wxDefaultPosition, wxDefaultSize);
	
	wxBoxSizer *vBox1 = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *hBox1 = new wxBoxSizer(wxHORIZONTAL);
	panel->SetSizer(vBox1);
		vBox1->Add(-1, 8, 0, wxGROW | (wxLEFT | wxRIGHT | wxBottom), 8);
		vBox1->Add(staticTextCtrl		, 0, wxGROW | (wxLEFT | wxRIGHT | wxBOTTOM), 8);
		vBox1->Add(recentProjectPathCtrl, 1, wxGROW | (wxLEFT | wxRIGHT | wxBOTTOM), 8);
		vBox1->Add(-1, 8, 0, wxGROW | (wxLEFT | wxRIGHT | wxBottom), 8);
		vBox1->Add(hBox1			, 0, wxGROW | (wxLEFT | wxRIGHT | wxBOTTOM), 8);
			hBox1->Add(openOtherButton, 0, wxLEFT);
			hBox1->Add(0, 16, 1);
			hBox1->Add(openButton, 0, wxRIGHT);

	openOtherButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(wxProjectDlg::onButtonClicked)				, 0, this);
	openButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(wxProjectDlg::onButtonClicked)					, 0, this);
	recentProjectPathCtrl->Connect(wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler(wxProjectDlg::onListItemSelected)	, 0, this);
	
	return panel;
}

wxPanel *wxProjectDlg::addCreateProjectPage(wxBookCtrlBase *parent)
{
	wxPanel *panel = new wxPanel(parent);

	wxStaticText	*locationLabel			= new wxStaticText(panel, wxID_ANY, "Project Location:");

	wxStandardPaths &stdPath = wxStandardPaths::Get();
	newProjectFolderPathCtrl				= new wxTextCtrl(panel, wxID_ANY, fixBackslash(stdPath.GetDocumentsDir() + "/MagnumProject/"));
	wxButton		*browseButton			= new wxButton(panel, wxID_BROWSE, wxT("Browser..."));
	wxStaticText	*packageLabel			= new wxStaticText(panel, wxID_ANY, "Import the following packages:");
	wxListCtrl		*listCtrl				= new wxListCtrl(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize,
													 wxLC_REPORT | wxLC_NO_HEADER | wxLC_SINGLE_SEL);
	wxButton *createButton			= new wxButton(panel, wxID_CREATE, wxT("Create"), wxDefaultPosition, wxDefaultSize);
	
	wxBoxSizer *vBox1 = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *hBox1 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *hBox2 = new wxBoxSizer(wxHORIZONTAL);
	panel->SetSizer(vBox1);
		vBox1->Add(-1, 8, 0, wxGROW | (wxLEFT | wxRIGHT | wxBottom), 8);
		vBox1->Add(locationLabel	, 0, wxGROW | (wxLEFT | wxRIGHT | wxBottom), 8);
		vBox1->Add(hBox1			, 0, wxGROW | (wxLEFT | wxRIGHT | wxBottom), 8);
			hBox1->Add(newProjectFolderPathCtrl, 1);
			hBox1->Add(8, -1);
			hBox1->Add(browseButton, 0, wxRIGHT);
		vBox1->Add(-1, 8, 0, wxGROW | (wxLEFT | wxRIGHT | wxBottom), 16);
		vBox1->Add(packageLabel		, 0, wxGROW | (wxLEFT | wxRIGHT | wxBottom), 8);
		vBox1->Add(listCtrl			, 1, wxGROW | (wxLEFT | wxRIGHT | wxBottom), 8);
		vBox1->Add(-1, 8, 0, wxGROW | (wxLEFT | wxRIGHT | wxBottom), 8);
		vBox1->Add(hBox2			, 0, wxGROW | (wxLEFT | wxRIGHT | wxBottom), 8);
			hBox2->Add(-1, 16, 1);
			hBox2->Add(createButton, 0, wxRIGHT);
		vBox1->Add(-1, 8, 0, wxGROW | (wxLEFT | wxRIGHT | wxBottom), 8);

	browseButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(wxProjectDlg::onButtonClicked)		, 0, this);
	createButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(wxProjectDlg::onButtonClicked)		, 0, this);

	return panel;
}

void wxProjectDlg::addRecentProject(wxString &path)
{
	Vector<wxString> recentProjectPaths;
	recentProjectPaths = Config::instance().getRecentProjectPaths();

	for(int i=0; i<recentProjectPaths.length(); i++)
	{
		if(recentProjectPaths[i]==path)
		{
			recentProjectPaths.remove(i);
			break;
		}
	}

	if(recentProjectPaths.length()>=10)
		recentProjectPaths.pop();

	recentProjectPaths.insert(0) = path;

	Config::instance().setRecentProjectPaths(recentProjectPaths);
}

int wxProjectDlg::getIconIndex(wxBookCtrlBase* bookCtrl)
{
    if (bookCtrl && bookCtrl->GetImageList())
    {
       int nImages = bookCtrl->GetImageList()->GetImageCount();
       if (nImages > 0)
       {
           return bookCtrl->GetPageCount() % nImages;
       }
    }

    return -1;
}

wxString wxProjectDlg::fixBackslash(const wxString &s)
{
	wxString rval(s);

	for(int i=0; i<rval.length(); i++)
	{
		if(rval[i] == '\\')
			rval[i] = '/';
	}

	return rval;
}

bool wxProjectDlg::showProjectFolderPathDlg(wxString &projectFolderPath)
{
	wxStandardPaths &stdPath = wxStandardPaths::Get();
	wxDirDialog dirDialog(this, wxT("New Project"), wxEmptyString, 
						  wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition);
	
	if(dirDialog.ShowModal() == wxID_OK)
	{
		projectFolderPath = fixBackslash(dirDialog.GetPath().c_str() + "/");
		return true;
	}
	else
	{
		projectFolderPath = "";
		return false;
	}
}

bool wxProjectDlg::showProjectFilePathDlg(wxString &projectFolderPath)
{
	wxFileDialog openDialog(this, wxT("Open Project"), wxEmptyString, wxEmptyString, 
							wxT("Magnum Project files (*.magnumproj)|*.magnumproj"),
							wxFD_OPEN | wxFD_FILE_MUST_EXIST, wxDefaultPosition);
	
	if(openDialog.ShowModal() == wxID_OK)
	{
		projectFolderPath = fixBackslash(openDialog.GetDirectory().c_str() + "/");
		return true;
	}
	else
	{
		projectFolderPath = "";
		return false;
	}
}

void wxProjectDlg::onButtonClicked(wxCommandEvent& evt)
{
	int rval = evt.GetId();
	if(rval==wxProjectDlg::wxID_OPENOTHER)
	{
		wxString temp;
		if(showProjectFilePathDlg(temp))
		{
			addRecentProject(temp);

			projectFolderPath = temp;
			EndModal(evt.GetId());
		}
	}
	else if(rval==wxProjectDlg::wxID_OPEN)
	{
		if(selectListIndex!=-1)
		{
			wxString temp = recentProjectPathCtrl->GetItemText(selectListIndex);

			addRecentProject(temp);
			
			projectFolderPath = temp;
			EndModal(evt.GetId());
		}
		else
		{
			wxString message;
			message.Printf("Select a project path from the list or open other");
			wxMessageBox(message);
		}
	}
	else if(rval==wxProjectDlg::wxID_BROWSE)
	{
		wxString temp;
		if(showProjectFolderPathDlg(temp))
		{
			newProjectFolderPathCtrl->SetValue(temp);
		}
	}
	else if(rval==wxProjectDlg::wxID_CREATE)
	{
		wxString temp(newProjectFolderPathCtrl->GetValue());
		if(temp!="")
		{
			addRecentProject(temp);

			projectFolderPath = temp;
			EndModal(evt.GetId());
		}
		else
		{
			wxString message;
			message.Printf("%s Valid Path must be selected", temp);
			wxMessageBox(message);
		}
	}
}

void wxProjectDlg::onListItemSelected(wxListEvent &evt)
{
	selectListIndex = evt.GetIndex();
}