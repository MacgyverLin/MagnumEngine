#include "DragNDrop.h"
#include <wx/treectrl.h>
#include <wx/dirctrl.h>
#include <wx/dir.h>
#include <wx/splitter.h>

TextDrop::TextDrop(const wxString& title)
: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(300, 200))
{
	wxSplitterWindow *spl1 = new wxSplitterWindow(this, -1);
	wxSplitterWindow *spl2 = new wxSplitterWindow(spl1, -1);

	m_gdir = new wxGenericDirCtrl(spl1, -1, wxT("/home/"), wxPoint(-1, -1), wxSize(-1, -1), wxDIRCTRL_DIR_ONLY);
	m_lc1 = new wxListCtrl(spl2, -1, wxPoint(-1, -1), wxSize(-1, -1), wxLC_LIST);
	m_lc2 = new wxListCtrl(spl2, -1, wxPoint(-1, -1), wxSize(-1, -1), wxLC_LIST);

	MyTextDropTarget *mdt = new MyTextDropTarget(m_lc2);
	m_lc2->SetDropTarget(mdt);

	Connect(m_lc1->GetId(), wxEVT_COMMAND_LIST_BEGIN_DRAG, wxListEventHandler(TextDrop::OnDragInit));

	wxTreeCtrl *tree = m_gdir->GetTreeCtrl();

	spl1->SplitVertically(m_gdir, spl2);
	spl2->SplitHorizontally(m_lc1, m_lc2);
	Connect(tree->GetId(), wxEVT_COMMAND_TREE_SEL_CHANGED, wxCommandEventHandler(TextDrop::OnSelect));

	Center();
}

void TextDrop::OnSelect(wxCommandEvent& event)
{
	wxString filename;
	wxString path = m_gdir->GetPath();
	wxDir dir(path);

	bool cont = dir.GetFirst(&filename, wxEmptyString, wxDIR_FILES);

	int i = 0;

	m_lc1->ClearAll();
	m_lc2->ClearAll();

	while ( cont )
	{
		m_lc1->InsertItem(i, filename);
		cont = dir.GetNext(&filename);
		i++;
	}
}

void TextDrop::OnDragInit(wxListEvent& event)
{
	wxString text = m_lc1->GetItemText(event.GetIndex());

	wxTextDataObject my_data(text);
	wxDropSource dragSource(m_lc1);
	dragSource.SetData(my_data);
	wxDragResult result = dragSource.DoDragDrop(wxDrag_CopyOnly);
}

/////////////////////////////////////////////////////////////////////////////////////////
MyTextDropTarget::MyTextDropTarget(wxListCtrl *owner)
{
	m_owner = owner;
}

bool MyTextDropTarget::OnDropText(wxCoord x, wxCoord y, const wxString& data)
{
	m_owner->InsertItem(0, data);
	
	return true;
}