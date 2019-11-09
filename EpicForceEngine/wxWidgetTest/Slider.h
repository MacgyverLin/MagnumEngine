#ifndef _Slider_h_
#define _Slider_h_

#include "wxdef.h"

class MyPanel : public wxPanel
{
public:
	MyPanel(wxFrame *parent);

	void OnPaint(wxPaintEvent& event);
	void OnScroll(wxScrollEvent& event);

	wxSlider *slider;
	int fill;
};

class Slider : public wxFrame
{
public:
	Slider(const wxString& title);

	MyPanel *panel;
};

const int ID_SLIDER = 100;

#endif