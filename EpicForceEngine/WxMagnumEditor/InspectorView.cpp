#include "InspectorView.h"
#include "ProjectView.h"
#include "EntityPanel.h"
using namespace Magnum;

InspectorView::InspectorView(ProjectView *projectView_)
: wxScrolledWindow(projectView_, wxID_ANY)
, entityPanel(0)
{
	SetBackgroundColour(wxColor(128, 128, 128, 255));

	wxBoxSizer *vBox	= new wxBoxSizer(wxVERTICAL);
	SetSizer(vBox);
	SetScrollRate(20, 20);
}

InspectorView::~InspectorView()
{
}

void InspectorView::diableUI(unsigned int flags)
{
}

void InspectorView::enableUI(unsigned int flags)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////
// member function
void InspectorView::createEntityPanel(Entity *entity)
{
	EntityPanel *newPanel = 0;
	if(entity)
	{
		//-----------------------------------------------------------------
		// constructror
		newPanel = new EntityPanel(this, entity);
		getModel().addView(newPanel);
	}

	if(entityPanel)
	{
		entityPanel->Hide();

		getModel().removeView(entityPanel);
		delete entityPanel;
		entityPanel = 0;
	}
	
	//-----------------------------------------------------------------	
	entityPanel = newPanel;	
	if(entityPanel)
	{
		wxSizer *sizer = this->GetSizer();
		sizer->Add(entityPanel, 1, wxEXPAND);

		entityPanel->Show();
	}

	FitInside();
	SetScrollRate(20, 20);
}

////////////////////////////////////////////////////////////////////////////////////////////////
// View request update Model

////////////////////////////////////////////////////////////////////////////////////////////////
// Model request update View
void InspectorView::notify(int flags, ProjectModelBase &projectModel, const Vector<unsigned char> &buffer)
{
	if(flags & ProjectModelBase::HIERARCHY_SELECTION_CHANGED)
	{
		Entity *entity = projectModel.getSelectedEntity();

		createEntityPanel(entity);
	}
	if(flags & ProjectModelBase::RESOURCEIMPORT_SELECTION_CHANGED)
	{
	}
	if(flags & ProjectModelBase::STATE_CHANGED)
	{
	}
}

void InspectorView::disableUIEvent()
{
}

void InspectorView::enableUIEvent()
{
}