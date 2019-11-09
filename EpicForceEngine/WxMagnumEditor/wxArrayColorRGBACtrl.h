#ifndef _wxArrayColorRGBACtrl_h_
#define _wxArrayColorRGBACtrl_h_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "wxdef.h"
#include "wxColorRGBACtrl.h"
#include "wxIntSpinnerCtrl.h"
#include "wxArrayLengthCtrl.h"
#include "wxCollapsePanelCtrl.h"
#include "Array.h"
using namespace Magnum;

class wxArrayColorRGBACtrlEvent : public wxNotifyEvent
{
public:
	wxArrayColorRGBACtrlEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
	: wxNotifyEvent(commandType, winid)
	{
	}

	wxArrayColorRGBACtrlEvent(const wxArrayColorRGBACtrlEvent& event)
	: wxNotifyEvent(event)
	, name(event.name)
	, values(event.values)
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

	const Vector<ColorRGBA> &GetValue() const 
	{ 
		return values; 
	};

	void SetValue(const Vector<ColorRGBA> &values_) 
	{
		values = values_;
	}

	wxEvent* Clone() const {return new wxArrayColorRGBACtrlEvent(*this); }
protected:
private:
	wxString name;
	Vector<ColorRGBA> values;

    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxArrayColorRGBACtrlEvent)
};

typedef void (wxEvtHandler::*wxArrayColorRGBACtrlEventFunction)(wxArrayColorRGBACtrlEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_ARRAY_COLORRGBA_CTRL_VALUE_CHANGED , 1 )
END_DECLARE_EVENT_TYPES()

#define wxArrayColorRGBACtrlEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxArrayColorRGBACtrlEventFunction, &func)

#define wx__DECLARE_ARRAY_COLORRGBA_CTRL_EVT(evt, id, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_ARRAY_COLORRGBA_CTRL_ ## evt, id, wxArrayColorRGBACtrlEventHandler(fn))	

#define EVT_ARRAY_COLORRGBA_CTRL_VALUE_CHANGED(id, fn)  wx__DECLARE_ARRAY_COLORRGBA_CTRL_EVT(VALUE_CHANGED, id, fn)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class wxArrayColorRGBACtrl : public wxCollapsePanelCtrl
{
public:
	wxArrayColorRGBACtrl(wxWindow *parent_, wxWindowID id_,
						 const char *caption_,
						 const Vector<ColorRGBA> &values_,
						 wxWindow *topLevelWindow_ = 0,
						 const wxPoint& pos_ = wxDefaultPosition,
						 const wxSize& size_ = wxDefaultSize,
						 long style_ = wxCP_DEFAULT_STYLE);

	void setLength(int length_);
	int getLength() const;

	void setValue(int idx, const ColorRGBA &value_);
	ColorRGBA getValue(int idx) const;
protected:
private:
	void createElementsUI();
	void destroyElementsUI();
	void resizeElementsUI(int newLength);
public:
protected:
private:
	void onLengthChanged(wxArrayLengthCtrlEvent &evt);
	void onColorRGBAValueChanged(wxColorRGBACtrlEvent &evt);
public:
protected:
private:
	Vector<ColorRGBA>				values;

	wxBoxSizer						*hBox;
	wxFlexGridSizer					*flexSizer;

	wxArrayLengthCtrl				*numElementsSpinner;
	Vector<wxColorRGBACtrl *>		colorRGBACtrls;
};

#endif