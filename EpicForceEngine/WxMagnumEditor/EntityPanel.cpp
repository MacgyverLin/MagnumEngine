#include "EntityPanel.h"
#include "ProjectView.h"

////////////////////////////////////////////////////////////////////////////////////////////////
EntityPanel::EntityPanel(wxScrolledWindow *parent_, Entity *entity_)
: wxPanel(parent_, wxID_ANY)
, parent(parent_)
, entity(entity_)
, entitySubPanel(0)
{
	SetBackgroundColour(parent->GetBackgroundColour());
	SetForegroundColour(parent->GetForegroundColour());

	wxFlexGridSizer *flexSizer	= new wxFlexGridSizer(1); flexSizer->AddGrowableCol(0);
	SetSizer(flexSizer);

	Hide();

	createUI();

	enableUIEvent();	
}

EntityPanel::~EntityPanel()
{
}

void EntityPanel::createUI()
{
	wxWindow *parentWnd;
	wxSizer *parentSizer;

	parentWnd		= this; 
	parentSizer		= parentWnd->GetSizer();

	entitySubPanel = new ReflectedClassPropertyPanel<Entity>(this, parentWnd, parentSizer, entity);
	entitySubPanel->Connect(wxEVT_COMMAND_REFLECTED_CLASS_PROPERTY_PANEL_COLLAPSED_CHANGED	, wxReflectedClassPropertyPanelEventHandler(EntityPanel::onCollapsePanelChanged), 0, this);
	entitySubPanel->Connect(wxEVT_COMMAND_REFLECTED_CLASS_PROPERTY_PANEL_SIZE_CHANGED		, wxReflectedClassPropertyPanelEventHandler(EntityPanel::onSize), 0, this);
	entitySubPanel->Connect(wxEVT_COMMAND_REFLECTED_CLASS_PROPERTY_PANEL_NAME_CHANGED		, wxReflectedClassPropertyPanelEventHandler(EntityPanel::onNameChanged), 0, this);
	entitySubPanel->Connect(wxEVT_COMMAND_REFLECTED_CLASS_PROPERTY_PANEL_TRANSFORM_CHANGED	, wxReflectedClassPropertyPanelEventHandler(EntityPanel::onTransformChanged), 0, this);
	entitySubPanel->Connect(wxEVT_COMMAND_REFLECTED_CLASS_PROPERTY_PANEL_VALUE_CHANGED		, wxReflectedClassPropertyPanelEventHandler(EntityPanel::onValueChanged), 0, this);

	wxStaticLine *staticLine = new wxStaticLine(this, wxID_ANY);
	staticLine->SetForegroundColour(wxColor(32, 32, 32, 255));
	this->GetSizer()->Add(staticLine, 1, wxEXPAND);

	componentSubPanels.resize(entity->getNumComponents());
	for(int i=0; i<entity->getNumComponents(); i++)
	{
		parentWnd		= this; 
		parentSizer		= parentWnd->GetSizer();

		componentSubPanels[i] = new ReflectedClassPropertyPanel<Component>(this, parentWnd, parentSizer, entity->getComponent(i));
		componentSubPanels[i]->Connect(wxEVT_COMMAND_REFLECTED_CLASS_PROPERTY_PANEL_COLLAPSED_CHANGED, wxReflectedClassPropertyPanelEventHandler(EntityPanel::onCollapsePanelChanged), 0, this);
		componentSubPanels[i]->Connect(wxEVT_COMMAND_REFLECTED_CLASS_PROPERTY_PANEL_SIZE_CHANGED, wxReflectedClassPropertyPanelEventHandler(EntityPanel::onSize), 0, this);
		componentSubPanels[i]->Connect(wxEVT_COMMAND_REFLECTED_CLASS_PROPERTY_PANEL_VALUE_CHANGED, wxReflectedClassPropertyPanelEventHandler(EntityPanel::onValueChanged), 0, this);

		wxStaticLine *staticLine = new wxStaticLine(this, wxID_ANY);
		staticLine->SetForegroundColour(wxColor(32, 32, 32, 255));
		this->GetSizer()->Add(staticLine, 1, wxEXPAND);
	}
}

void EntityPanel::destroyUI()
{
	if(entitySubPanel)
	{
		delete entitySubPanel;
		entitySubPanel = 0;
	}

	for(int i=0; i<componentSubPanels.length(); i++)
	{
		delete componentSubPanels[i];
		componentSubPanels[i] = 0;
	}
}

void EntityPanel::updateUI()
{
	if(componentSubPanels.length()==entity->getNumComponents())
	{
		if(entitySubPanel)
			entitySubPanel->update();

		for(int i=0; i<componentSubPanels.length(); i++)
		{
			if(componentSubPanels[i])
				componentSubPanels[i]->update();
		}
	}
	else
	{
		destroyUI();
		createUI();
	}
}

void EntityPanel::updateEntityNameUI()
{
	if(entitySubPanel)
	{
		Entity *entity = getModel().getSelectedEntity();

		entitySubPanel->update("Name", entity->getName());
	}
}

void EntityPanel::updateEntityTransformUI()
{
	if(entitySubPanel)
	{
		Entity *entity = getModel().getSelectedEntity();

		entitySubPanel->update("Transform", entity->getLocalTransform());
	}
}

void EntityPanel::diableUI(unsigned int flags)
{
}

void EntityPanel::enableUI(unsigned int flags)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////
// View request update Model
void EntityPanel::onSize(ReflectedClassPropertyPanelEvent &evt)
{
	parent->FitInside();
	parent->SetScrollRate(20, 20);
	Refresh();
}

void EntityPanel::onCollapsePanelChanged(ReflectedClassPropertyPanelEvent &evt)
{
	parent->FitInside();
	parent->SetScrollRate(20, 20);
	Refresh();
}

void EntityPanel::onNameChanged(ReflectedClassPropertyPanelEvent &evt)
{
	if(evt.GetNameChanged())
		getModel().updateSelectedEntityName();
}

void EntityPanel::onTransformChanged(ReflectedClassPropertyPanelEvent &evt)
{
	if(evt.GetTransformChanged())
		getModel().updateSelectedEntityTransform();
}

void EntityPanel::onValueChanged(ReflectedClassPropertyPanelEvent &evt)
{
	if(evt.GetValueChanged())
		getModel().updateSelectedEntityValue();
}

////////////////////////////////////////////////////////////////////////////////////////////////
// Model request update View
void EntityPanel::notify(int flags, ProjectModelBase &projectModel, const Vector<unsigned char> &buffer)
{
	if(flags & ProjectModelBase::SELECTED_ENTITY_NAME_CHANGED)
	{
		updateEntityNameUI();
	}
	else if(flags & ProjectModelBase::SELECTED_ENTITY_TRANSFORM_CHANGED)
	{
		updateEntityTransformUI();
	}
	/*
	else if(flags & ProjectModelBase::SELECTED_ENTITY_PROPERTIES_CHANGED)
	{
		updateUI();
	}
	*/
}

void EntityPanel::disableUIEvent()
{
}

void EntityPanel::enableUIEvent()
{
}