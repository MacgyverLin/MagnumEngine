#ifndef _wxCollapsePanelCtrl_h_
#define _wxCollapsePanelCtrl_h_

#include "wxdef.h"

// ----------------------------------------------------------------------------
// event types and macros
// ----------------------------------------------------------------------------
class wxCollapsePanelCtrlEvent : public wxNotifyEvent
{
public:
	wxCollapsePanelCtrlEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
	: wxNotifyEvent(commandType, winid)
	{
	}

	wxCollapsePanelCtrlEvent(const wxCollapsePanelCtrlEvent& event)
	: wxNotifyEvent(event)
	, m_bCollapsed(event.m_bCollapsed)
	{
	}

    bool GetCollapsed() const 
	{
		return m_bCollapsed; 
	}

    void SetCollapsed(bool c) 
	{
		m_bCollapsed = c; 
	}
	
    // default copy ctor, assignment operator and dtor are ok
    virtual wxEvent *Clone() const 
	{ 
		return new wxCollapsePanelCtrlEvent(*this); 
	}
private:
    bool m_bCollapsed;

    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxCollapsePanelCtrlEvent)
};

// ----------------------------------------------------------------------------
// event types and macros
// ----------------------------------------------------------------------------
typedef void (wxEvtHandler::*wxCollapsePanelCtrlEventFunction)(wxCollapsePanelCtrlEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_COLLAPSEPANEL_CTRL_COLLAPSED_CHANGED , 1 )
END_DECLARE_EVENT_TYPES()

#define wxCollapsePanelCtrlEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxCollapsePanelCtrlEventFunction, &func)

#define wx__DECLARE_COLLAPSEPANEL_CTRL_EVT(evt, id, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_COLLAPSEPANEL_CTRL_ ## evt, id, wxCollapsePanelCtrlEventHandler(fn))	

#define EVT_COLLAPSEPANEL_CTRL_VALUE_CHANGED(id, fn) wx__DECLARE_COLLAPSEPANEL_CTRL_EVT(VALUE_CHANGED, id, fn)

#define wxCP_DEFAULT_STYLE          (wxTAB_TRAVERSAL | wxNO_BORDER)
#define wxCP_NO_TLW_RESIZE          (0x0002)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ----------------------------------------------------------------------------
// wxCollapsePanelCtrl
// ----------------------------------------------------------------------------

class WXDLLIMPEXP_CORE wxCollapsePanelCtrl : public wxControl
{
public:
    wxCollapsePanelCtrl();

    wxCollapsePanelCtrl(wxWindow *parent,
                        wxWindowID winid,
                        const wxString& label,
						wxWindow *topLevelWindow = 0,
                        const wxPoint& pos = wxDefaultPosition,
                        const wxSize& size = wxDefaultSize,
                        long style = wxCP_DEFAULT_STYLE,
                        const wxValidator& val = wxDefaultValidator,
                        const wxString& name = "wxCollapsePanelCtrlEvent");

    virtual ~wxCollapsePanelCtrl();

	void SetTopLevelWindow(wxWindow *topLevelWindow_);
	wxWindow *GetTopLevelWindow();

    bool Create(wxWindow *parent,
                wxWindowID winid,
                const wxString& label,
				wxWindow *topLevelWindow_,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = wxCP_DEFAULT_STYLE,
                const wxValidator& val = wxDefaultValidator,
                const wxString& name = "wxCollapsePanelCtrlEvent");
    
    virtual void Collapse(bool collapse = true);

    virtual void SetLabel(const wxString &label);

    virtual bool IsCollapsed() const;

    virtual wxWindow *GetPane() const;

    virtual wxString GetLabel() const;

    virtual bool Layout();
	
    // for the generic collapsible pane only:
    wxControl *GetControlWidget() const;

    // implementation only, don't use
    void OnStateChange(const wxSize& sizeNew);
private:
    // overridden methods
    virtual wxSize DoGetBestSize() const;

    const wxBitmap &GetButtonBitmap() const;

    int GetBorder() const;

	wxWindow		*topLevelWindow;

	wxBitmap		expandedBitmap;
	wxBitmap		collapsedBitmap;

    wxBitmapButton	*button;
    wxStaticText	*staticText;
	wxSizer			*sizer;

    wxWindow		*contentPanel;

    void Init();

    // event handlers
    void OnButton(wxCommandEvent &ev);
    void OnSize(wxSizeEvent &ev);

    DECLARE_DYNAMIC_CLASS(wxCollapsePanelCtrl)
    //DECLARE_EVENT_TABLE()
};

#endif