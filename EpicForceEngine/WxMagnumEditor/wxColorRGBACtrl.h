#ifndef _wxColorRGBACtrl_h_
#define _wxColorRGBACtrl_h_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "wxdef.h"
#include "ColorRGBA.h"
using namespace Magnum;

class wxColorRGBACtrlEvent : public wxNotifyEvent
{
public:
	wxColorRGBACtrlEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
	: wxNotifyEvent(commandType, winid)
	{
	}

	wxColorRGBACtrlEvent(const wxColorRGBACtrlEvent& event)
	: wxNotifyEvent(event)
	, name(event.name)
	, value(event.value)
	{
	}

	const wxString &GetName() const 
	{ 
		return name; 
	}

	void SetName(const wxString &name_) 
	{
		name = name_;
	}

	const ColorRGBA &GetValue() const 
	{ 
		return value; 
	};

	void SetValue(const ColorRGBA &value_) 
	{
		value = value_;
	}

	wxEvent* Clone() const {return new wxColorRGBACtrlEvent(*this); }
protected:
private:
	wxString name;

	ColorRGBA value;

    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxColorRGBACtrlEvent)
};

typedef void (wxEvtHandler::*wxColorRGBACtrlEventFunction)(wxColorRGBACtrlEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_COLORRGBA_CTRL_VALUE_CHANGED, 1 )
END_DECLARE_EVENT_TYPES()

#define wxColorRGBACtrlEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxColorRGBACtrlEventFunction, &func)

#define wx__DECLARE_COLORRGBA_CTRL_EVT(evt, id, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_COLORRGBA_CTRL_ ## evt, id, wxColorRGBACtrlEventHandler(fn))	

#define EVT_COLORRGBA_CTRL_VALUE_CHANGED(id, fn) wx__DECLARE_COLORRGBA_CTRL_EVT(VALUE_CHANGED, id, fn)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class wxColorRGBACtrl : public wxPanel
{
public:
	wxColorRGBACtrl(wxWindow *parent_, wxWindowID id_,
					const char *label_, const ColorRGBA &value_, 
					const wxPoint& pos_ = wxDefaultPosition,
					const wxSize& size_ = wxDefaultSize,
					long style_ = wxBORDER_NONE);

	wxString GetLabel() const
	{
		return staticText->GetLabel();
	}

	void setValue(const ColorRGBA &value_);
	ColorRGBA getValue() const;
protected:
private:
	void fireEvent();
public:
protected:
private:
	void OnMouseDown(wxMouseEvent &evt);
	//void OnMouseUp(wxMouseEvent &evt);
	//void OnMove(wxMouseEvent &evt);
	void OnPaint(wxPaintEvent &evt);
public:
protected:
private:
	ColorRGBA			value;
	wxStaticText		*staticText;
	wxStaticText		*colorSwatch;
};

#endif