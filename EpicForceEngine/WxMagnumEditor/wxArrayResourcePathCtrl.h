#ifndef _wxArrayResourcePathCtrl_h_
#define _wxArrayResourcePathCtrl_h_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "wxdef.h"
#include "wxResourcePathCtrl.h"
#include "wxIntSpinnerCtrl.h"
#include "wxArrayLengthCtrl.h"
#include "wxCollapsePanelCtrl.h"
#include "Array.h"
using namespace Magnum;

class wxArrayResourcePathCtrlEvent : public wxNotifyEvent
{
public:
	wxArrayResourcePathCtrlEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
	: wxNotifyEvent(commandType, winid)
	{
	}

	wxArrayResourcePathCtrlEvent(const wxArrayResourcePathCtrlEvent& event)
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

	const Vector<ResourcePath> &GetValue() const 
	{ 
		return values; 
	};

	void SetValue(const Vector<ResourcePath> &values_) 
	{
		values = values_;
	}

	wxEvent* Clone() const {return new wxArrayResourcePathCtrlEvent(*this); }
protected:
private:
	wxString name;
	Vector<ResourcePath> values;

    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxArrayResourcePathCtrlEvent)
};

typedef void (wxEvtHandler::*wxArrayResourcePathCtrlEventFunction)(wxArrayResourcePathCtrlEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_ARRAY_RESOURCEPATH_CTRL_VALUE_CHANGED , 1 )
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_ARRAY_RESOURCEPATH_CTRL_LENGTH_CHANGED, 2 )
END_DECLARE_EVENT_TYPES()

#define wxArrayResourcePathCtrlEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxArrayResourcePathCtrlEventFunction, &func)

#define wx__DECLARE_ARRAY_RESOURCEPATH_CTRL_EVT(evt, id, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_ARRAY_RESOURCEPATH_CTRL_ ## evt, id, wxArrayResourcePathCtrlEventHandler(fn))	

#define EVT_ARRAY_RESOURCEPATH_CTRL_VALUE_CHANGED(id, fn)  wx__DECLARE_ARRAY_RESOURCEPATH_CTRL_EVT(VALUE_CHANGED, id, fn)
#define EVT_ARRAY_RESOURCEPATH_CTRL_LENGTH_CHANGED(id, fn) wx__DECLARE_ARRAY_RESOURCEPATH_CTRL_EVT(LENGTH_CHANGED, id, fn)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class wxArrayResourcePathCtrl : public wxCollapsePanelCtrl
{
public:
	wxArrayResourcePathCtrl(wxWindow *parent_, wxWindowID id_,
						 const char *caption_,
						 const Vector<ResourcePath> &values_,
						 wxWindow *topLevelWindow_ = 0,
						 const wxPoint& pos_ = wxDefaultPosition,
						 const wxSize& size_ = wxDefaultSize,
						 long style_ = wxCP_DEFAULT_STYLE);

	void setLength(int length_);
	int getLength() const;

	void setValue(int idx, const ResourcePath &value_);
	ResourcePath getValue(int idx) const;
protected:
private:
	void createElementsUI();
	void destroyElementsUI();
	void resizeElementsUI(int newLength);
public:
protected:
private:
	void onLengthChanged(wxArrayLengthCtrlEvent &evt);
	void onResourcePathValueChanged(wxResourcePathCtrlEvent &evt);
public:
protected:
private:
	Vector<ResourcePath>			values;

	wxBoxSizer						*hBox;
	wxFlexGridSizer					*flexSizer;

	wxArrayLengthCtrl				*numElementsSpinner;
	Vector<wxResourcePathCtrl *>	resourcePathCtrls;
};

#endif