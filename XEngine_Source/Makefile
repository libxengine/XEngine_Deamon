RELEASE = 0
UNICODE = 0
PLATFORM=linux
FLAGS= 

#要编译的模块
THIRDPART_MODULE_JSONCPP = ./XEngine_ThirdPart/jsoncpp

MODULE_CONFIGURE_PATH = ./XEngine_ModuleConfigure
APP_DEAMON_PATH = ./XEngine_ServiceApp/XEngine_DeamonApp

XENGINE_MODULES = libjsoncpp.so                                   \
                  libXEngine_ModuleConfigure.so                   \
				  XEngine_DeamonApp.exe 
.PHONY:MakeAll 
MakeAll:$(XENGINE_MODULES)

libjsoncpp.so:
	make -C $(THIRDPART_MODULE_JSONCPP) PLATFORM=$(PLATFORM) $(FLAGS)

libXEngine_ModuleConfigure.so:
	make -C $(MODULE_CONFIGURE_PATH) PLATFORM=$(PLATFORM) $(FLAGS)

XEngine_DeamonApp.exe:
	make -C $(APP_DEAMON_PATH) PLATFORM=$(PLATFORM) $(FLAGS)