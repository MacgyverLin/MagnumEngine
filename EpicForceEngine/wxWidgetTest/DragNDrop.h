#ifndef _DragNDrop_h_
#define _DragNDrop_h_

#include "wxdef.h"

class TextDrop : public wxFrame
{
public:
	TextDrop(const wxString& title);

	void OnSelect(wxCommandEvent& event);
	void OnDragInit(wxListEvent& event);

	wxGenericDirCtrl *m_gdir;
	wxListCtrl *m_lc1;
	wxListCtrl *m_lc2;
};

class MyTextDropTarget : public wxTextDropTarget
{
public:
	MyTextDropTarget(wxListCtrl *owner);

	virtual bool OnDropText(wxCoord x, wxCoord y, const wxString& data);

	wxListCtrl *m_owner;
};

#endif