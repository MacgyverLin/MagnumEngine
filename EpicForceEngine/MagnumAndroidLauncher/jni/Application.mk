APP_STL					:= gnustl_static
APP_OPTIM				:= release
APP_CPPFLAGS			+= -frtti 
APP_CPPFLAGS			+= -fexceptions
APP_CPPFLAGS			+= -fpermissive
APP_CPPFLAGS			+= -DANDROID

STLPORT_FORCE_REBUILD	:= true 