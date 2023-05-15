#pragma once
/********************************************************************
//    Created:     2023/05/15  09:55:10
//    File Name:   D:\XEngine_Deamon\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_APISystem\ModuleHelp_APISystem.h
//    File Path:   D:\XEngine_Deamon\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_APISystem
//    File Base:   ModuleHelp_APISystem
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     系统API函数帮助库
//    History:
*********************************************************************/

class CModuleHelp_APISystem
{
public:
	CModuleHelp_APISystem();
	~CModuleHelp_APISystem();
public:
	bool ModuleHelp_APISystem_AutoStart(LPCXSTR lpszDesName, bool bIsAuto = true);
protected:
private:
};