#ifndef _wxArrayVector2SpinnerCtrl_h_
#define _wxArrayVector2SpinnerCtrl_h_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "wxdef.h"
#include "wxVector2SpinnerCtrl.h"
#include "wxIntSpinnerCtrl.h"
#include "wxArrayLengthCtrl.h"
#include "wxCollapsePanelCtrl.h"
#include "Array.h"
using namespace Magnum;

class wxArrayVector2SpinnerCtrlEvent : public wxNotifyEvent
{
public:
	wxArrayVector2SpinnerCtrlEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
	: wxNotifyEvent(commandType, winid)
	{
	}

	wxArrayVector2SpinnerCtrlEvent(const wxArrayVector2SpinnerCtrlEvent& event)
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

	const Vector<Vector2> &GetValue() const 
	{ 
		return values; 
	};

	void SetValue(const Vector<Vector2> &values_) 
	{
		values = values_;
	}

	wxEvent* Clone() const {return new wxArrayVector2SpinnerCtrlEvent(*this); }
protected:
private:
	wxString name;
	Vector<Vector2> values;

    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxArrayVector2SpinnerCtrlEvent)
};

typedef void (wxEvtHandler::*wxArrayVector2SpinnerCtrlEventFunction)(wxArrayVector2SpinnerCtrlEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_ARRAY_VECTOR2_SPINNER_CTRL_VALUE_CHANGED , 1 )
END_DECLARE_EVENT_TYPES()

#define wxArrayVector2SpinnerCtrlEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxArrayVector2SpinnerCtrlEventFunction, &func)

#define wx__DECLARE_ARRAY_VECTOR2_SPINNER_CTRL_EVT(evt, id, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_ARRAY_VECTOR2_SPINNER_CTRL_ ## evt, id, wxArrayVector2SpinnerCtrlEventHandler(fn))	

#define EVT_ARRAY_VECTOR2_SPINNER_CTRL_VALUE_CHANGED(id, fn)  wx__DECLARE_ARRAY_VECTOR2_SPINNER_CTRL_EVT(VALUE_CHANGED, id, fn)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class wxArrayVector2SpinnerCtrl : public wxCollapsePanelCtrl
{
public:
	wxArrayVector2SpinnerCtrl(wxWindow *parent_, wxWindowID id_,
						      const char *caption_,
						      const Vector<Vector2> &values_, const Vector2 &minValue_, const Vector2 &maxValue_,
							  wxWindow *topLevelWindow_ = 0,
						      const wxPoint& pos_ = wxDefaultPosition,
						      const wxSize& size_ = wxDefaultSize,
						      long style_ = wxCP_DEFAULT_STYLE);

	void setLength(int length_);
	int getLength() const;

	void setMinValue(const Vector2 &value_);
	Vector2 getMinValue() const;

	void setMaxValue(const Vector2 &value_);
	Vector2 getMaxValue() const;

	void setValue(int idx, const Vector2 &value_);
	Vector2 getValue(int idx) const;
protected:
private:
	void createElementsUI();
	void destroyElementsUI();
	void resizeElementsUI(int newLength);
public:
protected:
private:
	void onLengthChanged(wxArrayLengthCtrlEvent &evt);
	void onVector2ValueChanged(wxVector2SpinnerCtrlEvent &evt);
public:
protected:
private:
	Vector<Vector2>					values;
	Vector2							minValue;
	Vector2							maxValue;

	wxBoxSizer						*hBox;
	wxFlexGridSizer					*flexSizer;

	wxArrayLengthCtrl				*numElementsSpinner;
	Vector<wxVector2SpinnerCtrl *>	vector2Spinners;
};

#endif