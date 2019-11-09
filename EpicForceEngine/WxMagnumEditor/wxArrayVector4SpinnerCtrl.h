#ifndef _wxArrayVector4SpinnerCtrl_h_
#define _wxArrayVector4SpinnerCtrl_h_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "wxdef.h"
#include "wxVector4SpinnerCtrl.h"
#include "wxIntSpinnerCtrl.h"
#include "wxArrayLengthCtrl.h"
#include "wxCollapsePanelCtrl.h"
#include "Array.h"
using namespace Magnum;

class wxArrayVector4SpinnerCtrlEvent : public wxNotifyEvent
{
public:
	wxArrayVector4SpinnerCtrlEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
	: wxNotifyEvent(commandType, winid)
	{
	}

	wxArrayVector4SpinnerCtrlEvent(const wxArrayVector4SpinnerCtrlEvent& event)
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

	const Vector<Vector4> &GetValue() const 
	{ 
		return values; 
	};

	void SetValue(const Vector<Vector4> &values_) 
	{
		values = values_;
	}

	wxEvent* Clone() const {return new wxArrayVector4SpinnerCtrlEvent(*this); }
protected:
private:
	wxString name;
	Vector<Vector4> values;

    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxArrayVector4SpinnerCtrlEvent)
};

typedef void (wxEvtHandler::*wxArrayVector4SpinnerCtrlEventFunction)(wxArrayVector4SpinnerCtrlEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_ARRAY_VECTOR4_SPINNER_CTRL_VALUE_CHANGED , 1 )
END_DECLARE_EVENT_TYPES()

#define wxArrayVector4SpinnerCtrlEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxArrayVector4SpinnerCtrlEventFunction, &func)

#define wx__DECLARE_ARRAY_VECTOR4_SPINNER_CTRL_EVT(evt, id, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_ARRAY_VECTOR4_SPINNER_CTRL_ ## evt, id, wxArrayVector4SpinnerCtrlEventHandler(fn))	

#define EVT_ARRAY_VECTOR4_SPINNER_CTRL_VALUE_CHANGED(id, fn)  wx__DECLARE_ARRAY_VECTOR4_SPINNER_CTRL_EVT(VALUE_CHANGED, id, fn)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class wxArrayVector4SpinnerCtrl : public wxCollapsePanelCtrl
{
public:
	wxArrayVector4SpinnerCtrl(wxWindow *parent_, wxWindowID id_,
						      const char *caption_,
						      const Vector<Vector4> &values_, const Vector4 &minValue_, const Vector4 &maxValue_,
							  wxWindow *topLevelWindow_ = 0,
						      const wxPoint& pos_ = wxDefaultPosition,
						      const wxSize& size_ = wxDefaultSize,
						      long style_ = wxCP_DEFAULT_STYLE);

	void setLength(int length_);
	int getLength() const;

	void setMinValue(const Vector4 &value_);
	Vector4 getMinValue() const;

	void setMaxValue(const Vector4 &value_);
	Vector4 getMaxValue() const;

	void setValue(int idx, const Vector4 &value_);
	Vector4 getValue(int idx) const;
protected:
private:
	void createElementsUI();
	void destroyElementsUI();
	void resizeElementsUI(int newLength);
public:
protected:
private:
	void onLengthChanged(wxArrayLengthCtrlEvent &evt);
	void onVector4ValueChanged(wxVector4SpinnerCtrlEvent &evt);
public:
protected:
private:
	Vector<Vector4>					values;
	Vector4							minValue;
	Vector4							maxValue;

	wxBoxSizer						*hBox;
	wxFlexGridSizer					*flexSizer;

	wxArrayLengthCtrl				*numElementsSpinner;
	Vector<wxVector4SpinnerCtrl *>	vector4Spinners;
};

#endif