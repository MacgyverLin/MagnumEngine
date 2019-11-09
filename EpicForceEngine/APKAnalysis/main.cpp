#include <Windows.h>
#include "wxdef.h"

///////////////////////////////////////////////////////////////////////////////////////////////
class WXMagnumEditorApp : public wxApp
{
public:
    bool OnInit();
    void OnIdle(wxIdleEvent& evt);
	int OnExit();
private:
	void initPNGHandler();
	const char *getSceneName();
};

IMPLEMENT_APP(WXMagnumEditorApp)

#define WIDTH  960
#define HEIGHT 640
#define EDITOR_WIDTH  1600
#define EDITOR_HEIGHT 1024

bool WXMagnumEditorApp::OnInit()
{
	initPNGHandler();



    projectView = new ProjectView(Localization::getTopWindowTitle());
	SetTopWindow(projectView);

	if( projectView->initStage(WIDTH, HEIGHT, EDITOR_WIDTH, EDITOR_HEIGHT) )
	{
		projectView->Show();

		this->Connect(wxEVT_IDLE, wxIdleEventHandler(WXMagnumEditorApp::OnIdle));
		return true;
	}
	else
	{
		return false;
	}

    return true;
}

void WXMagnumEditorApp::OnIdle(wxIdleEvent& evt)
{
	if(projectView)
	{	
		if(!evt.MoreRequested())
		{
			projectView->processStage();
			
			evt.RequestMore();
		}
	}
}

int WXMagnumEditorApp::OnExit()
{
	this->Disconnect( wxEVT_IDLE, wxIdleEventHandler(WXMagnumEditorApp::OnIdle) );

	if(projectView)
		projectView->terminateStage();

	return 0;
}

void WXMagnumEditorApp::initPNGHandler()
{
	wxImage::AddHandler(new wxPNGHandler);
}


	/*
	wxBitmap bitmap = BitmapCreater::getBitmapFromMemory(splash_png				, sizeof(splash_png			));
	wxSplashScreen* splash = new wxSplashScreen(bitmap,
			wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_TIMEOUT,
			3000, NULL, -1, wxDefaultPosition, wxDefaultSize,
			wxBORDER|wxSTAY_ON_TOP);
	*/