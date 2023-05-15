CC = g++ -Wall -std=c++17
PLATFORM = linux
PLATVER = 
PLATDIR = 
RELEASE = 0
UNICODE = 0
LOADHDR = -I ./ -I ../XEngine_ThirdPart/jsoncpp
LOADSO = -L /usr/local/lib/XEngine_Release/XEngine_BaseLib -L /usr/local/lib/XEngine_Release/XEngine_HelpComponents -L /usr/local/lib/XEngine_Release/XEngine_SystemSdk \
         -L ../../XEngine_ModuleConfigure -L ../../XEngine_ModuleHelp \
         -L ../../XEngine_ThirdPart/jsoncpp 
LIB = -lXEngine_BaseLib -lHelpComponents_XLog -lXEngine_SystemApi \
      -lXEngine_ModuleConfigure -lXEngine_ModuleHelp \
      -ljsoncpp 
LIBEX = 
OBJECTS = XDeamon_Config.o XDeamon_Process.o XDeamon_DeamonApp.o

ifeq ($(RELEASE),1)
FLAGS = -c 
DEBUG = 
else
FLAGS = -c -lc_p
DEBUG = -g -pg 
endif

ifeq ($(UNICODE),1)
UNICODE = -D _UNICODE
else
UNICODE = 
endif

ifeq ($(PLATFORM),linux)
	ifeq (/etc/redhat-release,$(wildcard /etc/redhat-release))
		PLATVER = -D __CENTOS__
		PLATDIR = XEngine_Linux/Centos
	else
		PLATVER = -D __UBUNTU__
		PLATDIR = XEngine_Linux/Ubuntu
	endif
	LIBEX = -lpthread -lrt -ldl
	LOADBIN = -Wl,-rpath=./,--disable-new-dtags
else ifeq ($(PLATFORM),mac)
	CC += -Wno-deprecated-declarations
	PLATVER = -D __MACOS__
	PLATDIR = XEngine_Mac
	LIBEX = -lpthread -ldl
	LOADBIN = -Wl,-rpath,@loader_path/./
endif

all:$(OBJECTS)
	$(CC) $(DEBUG) $(OBJECTS) -o XEngine_DeamonApp $(LIB) $(LIBEX) $(LOADSO) $(LOADBIN)
  
XDeamon_Config.o:./XDeamon_Config.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XDeamon_Config.cpp
XDeamon_Process.o:./XDeamon_Process.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XDeamon_Process.cpp 
		
XDeamon_DeamonApp.o:./XDeamon_DeamonApp.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XDeamon_DeamonApp.cpp   


InstallAll:InstallApp
InstallApp:./XEngine_DeamonApp
	cp -f ./XEngine_DeamonApp ../../../XEngine_Release/XEngine_DeamonApp

CleanAll:CleanObj CleanMk
CleanObj:                                              
	rm *.o
CleanMk:                                  
	rm XEngine_DeamonApp     
	       
