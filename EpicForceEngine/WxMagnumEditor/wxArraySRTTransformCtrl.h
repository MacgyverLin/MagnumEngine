#ifndef _wxArraySRTTransformCtrl_h_
#define _wxArraySRTTransformCtrl_h_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "wxdef.h"
#include "wxSRTTransformCtrl.h"
#include "wxArrayLengthCtrl.h"
#include "wxCollapsePanelCtrl.h"
#include "Array.h"
using namespace Magnum;

class wxArraySRTTransformCtrlEvent : public wxNotifyEvent
{
public:
	wxArraySRTTransformCtrlEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
	: wxNotifyEvent(commandType, winid)
	{
	}

	wxArraySRTTransformCtrlEvent(const wxArraySRTTransformCtrlEvent& event)
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

	const Vector<SRTTransform> &GetValue() const 
	{ 
		return values; 
	};

	void SetValue(const Vector<SRTTransform> &values_) 
	{
		values = values_;
	}

	wxEvent* Clone() const {return new wxArraySRTTransformCtrlEvent(*this); }
protected:
private:
	wxString name;
	Vector<SRTTransform> values;

    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxArraySRTTransformCtrlEvent)
};

typedef void (wxEvtHandler::*wxArraySRTTransformCtrlEventFunction)(wxArraySRTTransformCtrlEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_ARRAY_SRTTRANSFORM_CTRL_VALUE_CHANGED , 1 )
END_DECLARE_EVENT_TYPES()

#define wxArraySRTTransformCtrlEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxArraySRTTransformCtrlEventFunction, &func)

#define wx__DECLARE_ARRAY_SRTTRANSFORM_CTRL_EVT(evt, id, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_ARRAY_SRTTRANSFORM_CTRL_ ## evt, id, wxArraySRTTransformCtrlEventHandler(fn))	
	
#define EVT_ARRAY_SRTTRANSFORM_CTRL_VALUE_CHANGED(id, fn)  wx__DECLARE_ARRAY_SRTTRANSFORM_CTRL_EVT(VALUE_CHANGED, id, fn)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class wxArraySRTTransformCtrl : public wxCollapsePanelCtrl
{
public:
	wxArraySRTTransformCtrl(wxWindow *parent_, wxWindowID id_,
						    const char *caption_,
						    const Vector<SRTTransform> &values_,
							wxWindow *topLevelWindow_ = 0,
						    const wxPoint& pos_ = wxDefaultPosition,
						    const wxSize& size_ = wxDefaultSize,
						    long style_ = wxCP_DEFAULT_STYLE);

	void setLength(int length_);
	int getLength() const;

	void setValue(int idx, const SRTTransform &value_);
	SRTTransform getValue(int idx) const;
protected:
private:
	void createElementsUI();
	void destroyElementsUI();
	void resizeElementsUI(int newLength);
public:
protected:
private:
	void onLengthChanged(wxArrayLengthCtrlEvent &evt);
	void onSRTTransformValueChanged(wxSRTTransformCtrlEvent &evt);
public:
protected:
private:
	Vector<SRTTransform>				values;

	wxBoxSizer							*hBox;
	wxFlexGridSizer					*flexSizer;

	wxArrayLengthCtrl					*numElementsSpinner;
	Vector<wxSRTTransformCtrl *>		srtTransformCtrls;
};

#endif