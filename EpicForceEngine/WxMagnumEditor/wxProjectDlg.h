#ifndef _wxProjectDlg_h_
#define _wxProjectDlg_h_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "wxdef.h"
using namespace Magnum;

class wxProjectDlg : public wxDialog
{
public:
	enum
	{
		wxID_OPENOTHER	= 0,
		wxID_OPEN		= 1,
		wxID_BROWSE		= 2,
		wxID_CREATE		= 3,
	};
	wxProjectDlg(const wxString& title, int startPage);
	const wxString &getProjectFolderPath() const;
private:
	void createInitialPages(wxBookCtrlBase *parent);
	int getIconIndex(wxBookCtrlBase* bookCtrl);
	wxPanel *addOpenProjectPage(wxBookCtrlBase *parent);
	wxPanel *addCreateProjectPage(wxBookCtrlBase *parent);
	wxString fixBackslash(const wxString &s);

	bool showProjectFolderPathDlg(wxString &projectFolderPath);
	bool showProjectFilePathDlg(wxString &projectFolderPath);

	void addRecentProject(wxString &path);

	void onButtonClicked(wxCommandEvent &evt);
	void onListItemSelected(wxListEvent &evt);

	int selectListIndex;
	
	wxTextCtrl *newProjectFolderPathCtrl;
	wxListCtrl *recentProjectPathCtrl;

	wxString projectFolderPath;
};

#endif