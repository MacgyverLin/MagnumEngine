#include "wxCollapsePanelCtrl.h"
#include "BitmapCreater.h"
#include "rightarrow_png.h"
#include "downarrow_png.h"

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// ============================================================================
// implementation
// ============================================================================
DEFINE_EVENT_TYPE( wxEVT_COMMAND_COLLAPSEPANEL_CTRL_COLLAPSED_CHANGED )
IMPLEMENT_DYNAMIC_CLASS(wxCollapsePanelCtrlEvent, wxNotifyEvent)
IMPLEMENT_DYNAMIC_CLASS(wxCollapsePanelCtrl, wxControl)

wxCollapsePanelCtrl::wxCollapsePanelCtrl() 
{
	Init(); 
}

wxCollapsePanelCtrl::wxCollapsePanelCtrl(wxWindow *parent,
										 wxWindowID winid,
										 const wxString& label,
										 wxWindow *topLevelWindow,
										 const wxPoint& pos,
										 const wxSize& size,
										 long style,
										 const wxValidator& val,
										 const wxString& name)
{
	Init();

	Create(parent, winid, label, topLevelWindow, pos, size, style, val, name);
}

wxCollapsePanelCtrl::~wxCollapsePanelCtrl()
{
    if (button)
        button->SetContainingSizer(NULL);

    if (staticText)
        staticText->SetContainingSizer(NULL);

    // our sizer is not deleted automatically since we didn't use SetSizer()!
    wxDELETE(sizer);
}

void wxCollapsePanelCtrl::SetTopLevelWindow(wxWindow *topLevelWindow_)
{
	topLevelWindow = topLevelWindow_;
}

wxWindow *wxCollapsePanelCtrl::GetTopLevelWindow()
{
	return topLevelWindow;
}

bool wxCollapsePanelCtrl::Create(wxWindow *parent,
                                 wxWindowID id,
                                 const wxString& label,
								 wxWindow *topLevelWindow_,
                                 const wxPoint& pos,
                                 const wxSize& size,
                                 long style,
                                 const wxValidator& val,
                                 const wxString& name)
{
    if ( !wxControl::Create(parent, id, pos, size, style, val, name) )
        return false;

	topLevelWindow  = topLevelWindow_;

	expandedBitmap	= BitmapCreater::getBitmapFromMemory(downarrow_png, sizeof(downarrow_png) );
	collapsedBitmap = BitmapCreater::getBitmapFromMemory(rightarrow_png, sizeof(rightarrow_png) );

	////////////////////////////////////////////////////////////////////////////////////////
    SetBackgroundColour(parent->GetBackgroundColour());

	////////////////////////////////////////////////////////////////////////////////////////
    // create children and lay them out using a wxBoxSizer
    // (so that we automatically get RTL features)
    button = new wxBitmapButton(this, wxID_ANY, GetButtonBitmap(), 
								wxPoint(0, 0), wxSize(COLLAPSE_BUTTON_SIZE, COLLAPSE_BUTTON_SIZE), wxBORDER_NONE);
	button->SetBackgroundColour(parent->GetBackgroundColour());
	button->SetMinSize(wxSize(COLLAPSE_BUTTON_SIZE, COLLAPSE_BUTTON_SIZE));
	button->SetMaxSize(wxSize(COLLAPSE_BUTTON_SIZE, COLLAPSE_BUTTON_SIZE));

    staticText = new wxStaticText(this, wxID_ANY, label);
	staticText->SetBackgroundColour(parent->GetBackgroundColour());
	staticText->SetMinSize(wxSize(-1, COLLAPSE_BUTTON_SIZE));

    // sizer containing the expand button and possibly a static line
    sizer = new wxBoxSizer(wxHORIZONTAL);
    // on other platforms we put the static line and the button horizontally
    sizer->Add(button, 0, wxLEFT | wxTOP | wxBOTTOM, GetBorder());
    sizer->Add(staticText, 1, wxALIGN_CENTER | wxLEFT | wxRIGHT, GetBorder());

    ////////////////////////////////////////////////////////////////////////////////////////
	// do not set sz as our sizers since we handle the contentPanel window without using sizers
    contentPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
							   wxTAB_TRAVERSAL|wxNO_BORDER, wxT("wxCollapsiblePanePane") );
    contentPanel->SetBackgroundColour(parent->GetBackgroundColour());
    contentPanel->Hide();
    
	////////////////////////////////////////////////////////////////////////////////////////
	this->Connect(wxEVT_SIZE, wxSizeEventHandler(wxCollapsePanelCtrl::OnSize));
	this->Connect(wxID_ANY, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(wxCollapsePanelCtrl::OnButton) );

    return true;
}

void wxCollapsePanelCtrl::Collapse(bool collapse)
{
    // optimization
    if ( IsCollapsed() == collapse )
        return;

    // update our state
    contentPanel->Show(!collapse);

    // NB: this must be done after updating our "state"
	button->SetBitmapLabel(GetButtonBitmap());

    OnStateChange(GetBestSize());
}

void wxCollapsePanelCtrl::SetLabel(const wxString &label_)
{
	staticText->SetLabel(label_);

    Layout();
}

bool wxCollapsePanelCtrl::IsCollapsed() const
{
	return contentPanel==NULL || !contentPanel->IsShown(); 
}

wxWindow *wxCollapsePanelCtrl::GetPane() const
{
	return contentPanel; 
}

wxString wxCollapsePanelCtrl::GetLabel() const
{
	return staticText->GetLabel(); 
}

bool wxCollapsePanelCtrl::Layout()
{
    if (!button || !staticText || !contentPanel || !sizer)
        return false;     // we need to complete the creation first!

    wxSize oursz(GetSize());

    // move & resize the button and the static line
    sizer->SetDimension(0, 0, oursz.GetWidth(), sizer->GetMinSize().GetHeight());
    sizer->Layout();

    if ( !IsCollapsed() )
    {
        // move & resize the container window
        int yoffset = sizer->GetSize().GetHeight() + GetBorder();
        contentPanel->SetSize(0, yoffset,
                        oursz.x, oursz.y - yoffset);

        // this is very important to make the contentPanel window layout show correctly
        contentPanel->Layout();
    }

    return true;
}

wxControl *wxCollapsePanelCtrl::GetControlWidget() const
{
	return (wxControl*)button; 
}

void wxCollapsePanelCtrl::OnStateChange(const wxSize& sz)
{
    // minimal size has priority over the best size so set here our min size
//    SetMinSize(sz);
    SetSize(sz);
	//SetMinSize(sz);

    if (this->HasFlag(wxCP_NO_TLW_RESIZE))
    {
        // the user asked to explicitly handle the resizing itself...
        return;
    }

#if 1
    wxWindow *top = topLevelWindow;
    if(!top)
        return;
#else
    wxTopLevelWindow *top = wxDynamicCast(wxGetTopLevelParent(this), wxTopLevelWindow);
    if(!top)
        return;
#endif

    wxSizer *sizer = top->GetSizer();
    if ( !sizer )
        return;

    const wxSize newBestSize = sizer->ComputeFittingClientSize(top);
    top->SetMinSize(newBestSize);

    // we shouldn't attempt to resize a maximized window, whatever happens
#if 1
	top->SetClientSize(newBestSize);
#else
    if ( !top->IsMaximized() )
        top->SetClientSize(newBestSize);
#endif
}

wxSize wxCollapsePanelCtrl::DoGetBestSize() const
{
    // NB: do not use GetSize() but rather GetMinSize()
    wxSize sz = sizer->GetMinSize();

    // when expanded, we need more vertical space
    if ( !IsCollapsed() )
    {
        sz.SetWidth(wxMax( sz.GetWidth(), contentPanel->GetBestSize().x ));
        sz.SetHeight(sz.y + GetBorder() + contentPanel->GetBestSize().y);
    }

    return sz;
}

const wxBitmap &wxCollapsePanelCtrl::GetButtonBitmap() const
{
	if(IsCollapsed())
		return collapsedBitmap;
	else
		return expandedBitmap;
}

int wxCollapsePanelCtrl::GetBorder() const
{
    wxASSERT(button);
    return button->ConvertDialogToPixels(wxSize(2, 0)).x;
}



//-----------------------------------------------------------------------------
// wxCollapsePanelCtrl - event handlers
//-----------------------------------------------------------------------------
void wxCollapsePanelCtrl::OnButton(wxCommandEvent& evt)
{
    if ( evt.GetEventObject() != button )
    {
        evt.Skip();
        return;
    }

    Collapse(!IsCollapsed());

    // this change was generated by the user - send the event
    wxCollapsePanelCtrlEvent event(wxEVT_COMMAND_COLLAPSEPANEL_CTRL_COLLAPSED_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetCollapsed(IsCollapsed());

    GetEventHandler()->ProcessEvent(event);
}

void wxCollapsePanelCtrl::OnSize(wxSizeEvent& WXUNUSED(event))
{
    Layout();
}

void wxCollapsePanelCtrl::Init()
{
	topLevelWindow  = 0;
    button			= 0;
    staticText		= 0;
	sizer			= 0;

    contentPanel	= 0;    
}