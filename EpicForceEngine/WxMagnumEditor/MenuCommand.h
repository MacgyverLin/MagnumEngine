#ifndef _MenuCommand_h_
#define _MenuCommand_h_

#include "wxdef.h"
#include "Array.h"
#include "EString.h"
using namespace Magnum;

class MenuCommand
{
public:
	enum
	{
		MENU_FILE_PROJECT_NEW					= 0x0,
		MENU_FILE_PROJECT_OPEN					,
		MENU_FILE_PROJECT_SAVE					,

		MENU_FILE_SCENE_NEW						,
		MENU_FILE_SCENE_OPEN					,
		MENU_FILE_SCENE_SAVE					,
		MENU_FILE_SCENE_SAVE_AS					,
		MENU_FILE_SCENE_DELETE					,
		MENU_FILE_OPEN_PREFAB					,
		MENU_FILE_SAVE_PREFAB					,
		MENU_FILE_EXIT							,

		MENU_EDIT_UNDO							,
		MENU_EDIT_REDO							,
		MENU_EDIT_CUT							,
		MENU_EDIT_COPY							,
		MENU_EDIT_PASTE							,
		MENU_EDIT_DUPLICATE						,
		MENU_EDIT_DELETE						,

		MENU_OPERATION_SELECTION				,
		MENU_OPERATION_MOVE_SELECTED			,
		MENU_OPERATION_ROTATE_SELECTED			,
		MENU_OPERATION_SCALE_SELECTED			,
		MENU_OPERATION_FRAME_SELECTED			,
		MENU_OPERATION_FIND						,
		MENU_OPERATION_SELECT_ALL				,
		MENU_OPERATION_ZOOM						,
		MENU_OPERATION_ZOOM_EXTENT				,
		MENU_OPERATION_ZOOM_EXTENT_SELECTED		,
		MENU_OPERATION_ZOOM_REGION				,
		MENU_OPERATION_FOV						,
		MENU_OPERATION_PAN						,
		MENU_OPERATION_ORBIT					,
		MENU_OPERATION_ORBIT_SELECTED			,

		MENU_MISC_A_UPDATE_ASSETS				,
		MENU_MISC_A_0							,
		MENU_MISC_A_1							,
		MENU_MISC_A_2							,
		MENU_MISC_A_3							,
		MENU_MISC_A_4							,
		MENU_MISC_A_5							,
		MENU_MISC_A_6							,
		MENU_MISC_A_7							,
		MENU_MISC_A_8							,
		MENU_MISC_A_9							,

		MENU_MISC_B_0							,
		MENU_MISC_B_1							,
		MENU_MISC_B_2							,
		MENU_MISC_B_3							,
		MENU_MISC_B_4							,
		MENU_MISC_B_5							,
		MENU_MISC_B_6							,
		MENU_MISC_B_7							,
		MENU_MISC_B_8							,
		MENU_MISC_B_9							,
		
		MENU_DEBUG_RUN,
		MENU_DEBUG_STOP,
		MENU_DEBUG_PAUSE,
		MENU_DEBUG_STEP,

		MENU_BUILD,
		MENU_BUILD_PLATFORM_WIN32,
		MENU_BUILD_PLATFORM_IOS,
		MENU_BUILD_PLATFORM_ANDROID,
		MENU_BUILD_PLATFORM_WINMOBILE,
		MENU_BUILD_PLATFORM_PS3,
		MENU_BUILD_PLATFORM_PSP,
		MENU_BUILD_PLATFORM_PSVITA,
		MENU_BUILD_PLATFORM_WII,
		MENU_BUILD_PLATFORM_WIIU,

		MENU_HELP_HELP ,
		MENU_HELP_ABOUT,
	};
};

#endif