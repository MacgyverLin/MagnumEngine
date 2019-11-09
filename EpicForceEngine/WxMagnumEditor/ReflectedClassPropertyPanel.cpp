///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "ReflectedClassPropertyPanel.h"
using namespace Magnum;

////////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC_CLASS( ReflectedClassPropertyPanelEvent, wxNotifyEvent )
DEFINE_EVENT_TYPE( wxEVT_COMMAND_REFLECTED_CLASS_PROPERTY_PANEL_COLLAPSED_CHANGED	)
DEFINE_EVENT_TYPE( wxEVT_COMMAND_REFLECTED_CLASS_PROPERTY_PANEL_SIZE_CHANGED		)
DEFINE_EVENT_TYPE( wxEVT_COMMAND_REFLECTED_CLASS_PROPERTY_PANEL_NAME_CHANGED		)
DEFINE_EVENT_TYPE( wxEVT_COMMAND_REFLECTED_CLASS_PROPERTY_PANEL_TRANSFORM_CHANGED	)
DEFINE_EVENT_TYPE( wxEVT_COMMAND_REFLECTED_CLASS_PROPERTY_PANEL_VALUE_CHANGED		)