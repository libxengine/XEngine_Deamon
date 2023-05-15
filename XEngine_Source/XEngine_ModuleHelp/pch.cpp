#include "pch.h"
#include "ModuleHelp_APISystem/ModuleHelp_APISystem.h"
/********************************************************************
//    Created:     2023/05/15  09:58:56
//    File Name:   D:\XEngine_Deamon\XEngine_Source\XEngine_ModuleHelp\pch.cpp
//    File Path:   D:\XEngine_Deamon\XEngine_Source\XEngine_ModuleHelp
//    File Base:   pch
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     导出数显
//    History:
*********************************************************************/
bool ModuleHelp_IsErrorOccur = false;
XLONG ModuleHelp_dwErrorCode = 0;
//////////////////////////////////////////////////////////////////////////
CModuleHelp_APISystem m_HelpSystem;
//////////////////////////////////////////////////////////////////////////
//                        导出函数定义
//////////////////////////////////////////////////////////////////////////
extern "C" XLONG ModuleHelp_GetLastError(int* pInt_ErrorCode)
{
	if (NULL != pInt_ErrorCode)
	{
		*pInt_ErrorCode = errno;
	}
	return ModuleHelp_dwErrorCode;
}
/************************************************************************/
/*                        系统函数库                                    */
/************************************************************************/
extern "C" bool ModuleHelp_APISystem_AutoStart(LPCXSTR lpszDesName, bool bIsAuto /* = true */)
{
	return m_HelpSystem.ModuleHelp_APISystem_AutoStart(lpszDesName, bIsAuto);
}