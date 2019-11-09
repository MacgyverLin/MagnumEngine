#ifndef _Widget_h_
#define _Widget_h_

#include "wxdef.h"

class Widget : public wxPanel
{
public:
	Widget(wxPanel *parent, int id );

	wxPanel *m_parent;

	void OnSize(wxSizeEvent& event);
	void OnPaint(wxPaintEvent& event);  
};

#endif