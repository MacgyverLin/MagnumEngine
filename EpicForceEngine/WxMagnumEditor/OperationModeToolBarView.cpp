#include "OperationModeToolBarView.h"
#include "ProjectView.h"

#include "selection_png.h"
#include "moveselected_png.h"
#include "rotateselected_png.h"
#include "scaleselected_png.h"
#include "zoom_png.h"
#include "zoomExtents_png.h"
#include "zoomExtentSelected_png.h"
#include "zoomregion_png.h"
#include "fov_png.h"
#include "pan_png.h"
#include "orbit_png.h"
#include "orbitselected_png.h"
//#include "updateasset_png.h"
#include "BitmapCreater.h"
#include "Localization.h"

OperationModeToolBarView::OperationModeToolBarView(ProjectView *projectView_)
: wxAuiToolBar(projectView_, wxID_ANY, 
			   wxPoint(0, 0), wxSize(960, 16), 
			   wxAUI_TB_DEFAULT_STYLE /*| wxAUI_TB_OVERFLOW/* | wxAUI_TB_VERTICAL*/)
, coordSysComboBox(0)
{
	this->SetForegroundColour(projectView_->GetForegroundColour());
    this->SetBackgroundColour(projectView_->GetBackgroundColour());

	wxBitmap selectionBitmap				= BitmapCreater::getBitmapFromMemory(selection_png				, sizeof(selection_png			));
	wxBitmap moveselectedBitmap				= BitmapCreater::getBitmapFromMemory(moveselected_png			, sizeof(moveselected_png		));
	wxBitmap rotateselectedBitmap			= BitmapCreater::getBitmapFromMemory(rotateselected_png			, sizeof(rotateselected_png		));
	wxBitmap scaleselectedBitmap			= BitmapCreater::getBitmapFromMemory(scaleselected_png			, sizeof(scaleselected_png		));
	wxBitmap zoomBitmap						= BitmapCreater::getBitmapFromMemory(zoom_png					, sizeof(zoom_png				));
	wxBitmap zoomExtentsBitmap				= BitmapCreater::getBitmapFromMemory(zoomExtents_png			, sizeof(zoomExtents_png		));
	wxBitmap zoomExtentSelectedBitmap		= BitmapCreater::getBitmapFromMemory(zoomExtentSelected_png		, sizeof(zoomExtentSelected_png	));
	wxBitmap zoomregionBitmap				= BitmapCreater::getBitmapFromMemory(zoomregion_png				, sizeof(zoomregion_png			));
	wxBitmap fovBitmap						= BitmapCreater::getBitmapFromMemory(fov_png					, sizeof(fov_png				));
	wxBitmap panBitmap						= BitmapCreater::getBitmapFromMemory(pan_png					, sizeof(pan_png				));
	wxBitmap orbitBitmap					= BitmapCreater::getBitmapFromMemory(orbit_png					, sizeof(orbit_png				));
	wxBitmap orbitselectedBitmap			= BitmapCreater::getBitmapFromMemory(orbitselected_png			, sizeof(orbitselected_png		));
	//wxBitmap updateAssetsBitmap				= BitmapCreater::getBitmapFromMemory(updateasset_png			, sizeof(updateasset_png		));
	
	this->SetToolBitmapSize(wxSize(16,16));
	wxString choices[] =
	{
		Localization::getCoordSysLocal(),
		Localization::getCoordSysParent(),
		Localization::getCoordSysWorld(),
		Localization::getCoordSysView(),
	};
	coordSysComboBox = new wxComboBox(this, wxID_ANY, choices[0], wxDefaultPosition, wxSize(96, 24), sizeof(choices)/sizeof(choices[0]), choices, wxCB_READONLY);
	this->AddControl(coordSysComboBox, "");
	this->AddSeparator();
	this->AddTool(MenuCommand::MENU_OPERATION_SELECTION					, Localization::getOperationSelection()			, selectionBitmap			, Localization::getOperationSelection()			, wxITEM_RADIO);
	this->AddSeparator();																															  			
	this->AddTool(MenuCommand::MENU_OPERATION_MOVE_SELECTED				, Localization::getOperationMoveSelected()		, moveselectedBitmap		, Localization::getOperationMoveSelected()		, wxITEM_RADIO);
	this->AddTool(MenuCommand::MENU_OPERATION_ROTATE_SELECTED			, Localization::getOperationRotateSelected()	, rotateselectedBitmap		, Localization::getOperationRotateSelected()	, wxITEM_RADIO);
	this->AddTool(MenuCommand::MENU_OPERATION_SCALE_SELECTED			, Localization::getOperationScaleSelected()		, scaleselectedBitmap		, Localization::getOperationScaleSelected()		, wxITEM_RADIO);
	this->AddSeparator();																															  			
	this->AddTool(MenuCommand::MENU_OPERATION_ZOOM						, Localization::getOperationZoom()				, zoomBitmap				, Localization::getOperationZoom()				, wxITEM_RADIO);
	this->AddTool(MenuCommand::MENU_OPERATION_ZOOM_EXTENT				, Localization::getOperationZoomExtent()		, zoomExtentsBitmap			, Localization::getOperationZoomExtent()		, wxITEM_RADIO);
	this->AddTool(MenuCommand::MENU_OPERATION_ZOOM_EXTENT_SELECTED		, Localization::getOperationZoomExtentSelected(), zoomExtentSelectedBitmap	, Localization::getOperationZoomExtentSelected(), wxITEM_RADIO);
	this->AddTool(MenuCommand::MENU_OPERATION_FOV						, Localization::getOperationFov()				, fovBitmap					, Localization::getOperationFov()				, wxITEM_RADIO);
	this->AddTool(MenuCommand::MENU_OPERATION_PAN						, Localization::getOperationPan()				, panBitmap					, Localization::getOperationPan()				, wxITEM_RADIO);
	this->AddTool(MenuCommand::MENU_OPERATION_ORBIT						, Localization::getOperationOrbit()				, orbitBitmap				, Localization::getOperationOrbit()				, wxITEM_RADIO);
	this->AddTool(MenuCommand::MENU_OPERATION_ORBIT_SELECTED			, Localization::getOperationOrbitSelected()		, orbitselectedBitmap		, Localization::getOperationOrbitSelected()		, wxITEM_RADIO);
	this->Realize();

	enableUIEvent();
}

OperationModeToolBarView::~OperationModeToolBarView()
{
}

void OperationModeToolBarView::diableUI(unsigned int flags)
{
}

void OperationModeToolBarView::enableUI(unsigned int flags)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////
// View request update Model
void OperationModeToolBarView::onComboBoxDropDown(wxCommandEvent &evt)
{
	int value = ProjectModelBase::LOCAL;
	value += evt.GetSelection();

	Vector<unsigned char> buffer;
	MemOutputStream os(buffer);
	os << String("ChangeCoordSys") << value;
	GameDescriptor::instance().onGUIEvent(&buffer[0], buffer.length());
	/*
	int value = ProjectModelBase::LOCAL;
	value += evt.GetSelection();
	getModel().setCoordinateSystem((ProjectModelBase::CoordSys)value);
	*/
}

////////////////////////////////////////////////////////////////////////////////////////////////
// Model request update View
void OperationModeToolBarView::notify(int flags, ProjectModelBase &projectModel, const Vector<unsigned char> &buffer)
{
	if(flags & ProjectModelBase::COORDSYS_CHANGED)
	{
		ProjectModelBase::CoordSys coordsys = projectModel.getCoordinateSystem();

		coordSysComboBox->SetSelection(coordsys);
	}
	if(flags & ProjectModelBase::STATE_CHANGED)
	{
		if(projectModel.getCurrentState()=="DebugRun")
		{
			EnableTool(MenuCommand::MENU_OPERATION_SELECTION			, false);
			EnableTool(MenuCommand::MENU_OPERATION_MOVE_SELECTED		, false);
			EnableTool(MenuCommand::MENU_OPERATION_ROTATE_SELECTED		, false);
			EnableTool(MenuCommand::MENU_OPERATION_SCALE_SELECTED		, false);

			EnableTool(MenuCommand::MENU_OPERATION_ZOOM					, false);
			EnableTool(MenuCommand::MENU_OPERATION_ZOOM_EXTENT			, false);
			EnableTool(MenuCommand::MENU_OPERATION_ZOOM_EXTENT_SELECTED	, false);
			EnableTool(MenuCommand::MENU_OPERATION_FOV					, false);
			EnableTool(MenuCommand::MENU_OPERATION_PAN					, false);
			EnableTool(MenuCommand::MENU_OPERATION_ORBIT				, false);
			EnableTool(MenuCommand::MENU_OPERATION_ORBIT_SELECTED		, false);

			coordSysComboBox->Disable();

			Refresh();
		}
		else if(projectModel.getCurrentState()=="OperationScaleSelected")
		{
			EnableTool(MenuCommand::MENU_OPERATION_SELECTION			, true);
			EnableTool(MenuCommand::MENU_OPERATION_MOVE_SELECTED		, true);
			EnableTool(MenuCommand::MENU_OPERATION_ROTATE_SELECTED		, true);
			EnableTool(MenuCommand::MENU_OPERATION_SCALE_SELECTED		, true);

			EnableTool(MenuCommand::MENU_OPERATION_ZOOM					, true);
			EnableTool(MenuCommand::MENU_OPERATION_ZOOM_EXTENT			, false); // true);
			EnableTool(MenuCommand::MENU_OPERATION_ZOOM_EXTENT_SELECTED	, false); // true);
			EnableTool(MenuCommand::MENU_OPERATION_FOV					, true);
			EnableTool(MenuCommand::MENU_OPERATION_PAN					, true);
			EnableTool(MenuCommand::MENU_OPERATION_ORBIT				, true);
			EnableTool(MenuCommand::MENU_OPERATION_ORBIT_SELECTED		, true);

			coordSysComboBox->SetSelection(0);
			coordSysComboBox->Disable();

			Refresh();
		}
		else
		{
			EnableTool(MenuCommand::MENU_OPERATION_SELECTION			, true);
			EnableTool(MenuCommand::MENU_OPERATION_MOVE_SELECTED		, true);
			EnableTool(MenuCommand::MENU_OPERATION_ROTATE_SELECTED		, true);
			EnableTool(MenuCommand::MENU_OPERATION_SCALE_SELECTED		, true);

			EnableTool(MenuCommand::MENU_OPERATION_ZOOM					, true);
			EnableTool(MenuCommand::MENU_OPERATION_ZOOM_EXTENT			, false); // true);
			EnableTool(MenuCommand::MENU_OPERATION_ZOOM_EXTENT_SELECTED	, false); // true);
			EnableTool(MenuCommand::MENU_OPERATION_FOV					, true);
			EnableTool(MenuCommand::MENU_OPERATION_PAN					, true);
			EnableTool(MenuCommand::MENU_OPERATION_ORBIT				, true);
			EnableTool(MenuCommand::MENU_OPERATION_ORBIT_SELECTED		, true);

			coordSysComboBox->Enable();

			Refresh();
		}
	}
}

void OperationModeToolBarView::disableUIEvent()
{
	this->Disconnect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(OperationModeToolBarView::onComboBoxDropDown), 0, this);
}

void OperationModeToolBarView::enableUIEvent()
{
	this->Connect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(OperationModeToolBarView::onComboBoxDropDown), 0, this);
}