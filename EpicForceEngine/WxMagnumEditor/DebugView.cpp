#include "DebugView.h"
#include "ProjectView.h"
#include "ResourceImportDragDrop.h"

////////////////////////////////////////////////////////////////////////////////////////////////
class DebugViewResourceImportDropTarget : public ResourceImportDropTarget
{
public:
	DebugViewResourceImportDropTarget(DebugView *view_)
	: ResourceImportDropTarget("texture")
	, view(view_)
	{
	}

    virtual bool onDropResourceImport(const char *path, const char *extension)
	{
		return view->onDropResourceImport(path, extension);
	}
private:
	DebugView *view;
};

////////////////////////////////////////////////////////////////////////////////////////////////
DebugView::DebugView(ProjectView *projectView_)
: wxTextCtrl(projectView_, wxID_ANY,
			 "",
			 wxDefaultPosition, wxDefaultSize, 
			 wxTE_MULTILINE | wxTE_READONLY | wxNO_BORDER)
{
    this->SetForegroundColour(wxColour(  0,   0,   0, 255));
    this->SetBackgroundColour(wxColour(128, 128, 128, 255));

	DebugViewResourceImportDropTarget *dropTarget = new DebugViewResourceImportDropTarget(this);
	
	this->SetDropTarget(dropTarget);

	enableUIEvent();
}

DebugView::~DebugView()
{
}

void DebugView::diableUI(unsigned int flags)
{
}

void DebugView::enableUI(unsigned int flags)
{
}

void DebugView::clear()
{
	SetValue("");
}

void DebugView::infoPrint(const char *buf)
{
	AppendText(buf);

	this->Fit();
}

void DebugView::debugPrint(int i, const char *buf)
{
	AppendText(buf);

	this->Fit();
}

////////////////////////////////////////////////////////////////////////////////////////////////
// View request update Model
bool DebugView::onDropResourceImport(const char *path, const char *extension)
{
	debugPrint(0, path);
	debugPrint(0, ".");
	debugPrint(0, extension);
	debugPrint(0, "\n");

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// Model request update View
void DebugView::notify(int flags, ProjectModelBase &projectModel, const Vector<unsigned char> &buffer)
{
	if(flags & ProjectModelBase::ENTITIY_CREATORS)
	{
	}
	/*
	if(flags & ProjectModelBase::RESOURCE_IMPORTERS)
	{
		for(int i=0; i<projectModel.getNumResourceCreators(); i++)
		{
			const ResourceImport::ICreator *creator = projectModel.getResourceCreators(i);

			for(int j=0; j<creator->getNumResourceImporters(); j++)
			{
				const ResourceImport *resourceImport = creator->getResourceImporters(j);

				AppendText(resourceImport->name());
				AppendText("\n");
			}
		}
	}
	*/
	if(flags & ProjectModelBase::STATE_CHANGED)
	{
	}
}

void DebugView::disableUIEvent()
{
}

void DebugView::enableUIEvent()
{
}



////////////////////////////////////////////////////////////////////////////////////////////////
/*
void DebugView::clear()
{
	SetValue("");
}

void DebugView::infoPrint(const char *buf)
{
	AppendText(buf);

	this->Fit();
}

void DebugView::debugPrint(int i, const char *buf)
{
	AppendText(buf);

	this->Fit();
}
*/