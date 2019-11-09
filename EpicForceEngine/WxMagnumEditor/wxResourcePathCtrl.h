#ifndef _wxResourcePathCtrl_h_
#define _wxResourcePathCtrl_h_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "wxdef.h"
#include "ResourcePath.h"
using namespace Magnum;

class wxResourcePathCtrlEvent : public wxNotifyEvent
{
friend class wxResourcePathCtrlResourceImportDropTarget;
public:
	wxResourcePathCtrlEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
	: wxNotifyEvent(commandType, winid)
	{
	}

	wxResourcePathCtrlEvent(const wxResourcePathCtrlEvent& event)
	: wxNotifyEvent(event)
	, name(event.name)
	, value(event.value)
	{
	}
	
	const wxString &GetName() const 
	{ 
		return name; 
	};

	void SetName(const wxString &name_) 
	{
		name = name_;
	}

	ResourcePath GetValue() const 
	{ 
		return value; 
	};

	void SetValue(const ResourcePath &value_) 
	{
		value = value_;
	}

	wxEvent* Clone() const {return new wxResourcePathCtrlEvent(*this); }
protected:
private:
	wxString name;

	ResourcePath value;

    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxResourcePathCtrlEvent)
};

typedef void (wxEvtHandler::*wxResourcePathCtrlEventFunction)(wxResourcePathCtrlEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_RESOURCEPATH_CTRL_VALUE_CHANGED, 1 )
END_DECLARE_EVENT_TYPES()

#define wxResourcePathCtrlEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxResourcePathCtrlEventFunction, &func)

#define wx__DECLARE_RESOURCEPATH_CTRL_EVT(evt, id, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_RESOURCEPATH_CTRL_ ## evt, id, wxResourcePathCtrlEventHandler(fn))	

#define EVT_RESOURCEPATH_CTRL_VALUE_CHANGED(id, fn) wx__DECLARE_RESOURCEPATH_CTRL_EVT(VALUE_CHANGED, id, fn)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class wxResourcePathCtrl : public wxPanel
{
friend class wxResourcePathCtrlResourceImportDropTarget;
friend class WXMagnumEditorProjectView;
public:
	wxResourcePathCtrl(wxWindow *parent_, wxWindowID id_,
					   const char *label_, const ResourcePath &value_, 
					   const wxPoint& pos_ = wxDefaultPosition,
					   const wxSize& size_ = wxDefaultSize,
					   long style_ = wxBORDER_NONE);

	wxString GetLabel() const
	{
		return staticText->GetLabel();
	}

	void setValue(const ResourcePath &value_);
	ResourcePath getValue() const;
protected:
private:
	void fireEvent();

////////////////////////////////////////////////////////////////////////////////////////////////
// UI Event
public:
protected:
private:
	bool onDropResourceImport(const char *path, const char *extension);
public:
protected:
private:
	ResourcePath		value;
	wxStaticText		*staticText;
	wxStaticText		*textCtrl;
};

#endif