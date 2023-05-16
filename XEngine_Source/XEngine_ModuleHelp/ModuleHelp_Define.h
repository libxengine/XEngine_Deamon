#pragma once
/********************************************************************
//    Created:     2023/05/15  09:58:20
//    File Name:   D:\XEngine_Deamon\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_Define.h
//    File Path:   D:\XEngine_Deamon\XEngine_Source\XEngine_ModuleHelp
//    File Base:   ModuleHelp_Define
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     帮助模块导出定义
//    History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////
//                        导出函数定义
//////////////////////////////////////////////////////////////////////////
extern "C" XLONG ModuleHelp_GetLastError(int* pInt_ErrorCode = NULL);
/************************************************************************/
/*                        系统函数库                                    */
/************************************************************************/
/********************************************************************
函数名称：ModuleHelp_APISystem_AutoStart
函数功能：注册自动启动与服务函数
 参数.一：lpszDesName
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：描述名称
 参数.二：bIsAuto
  In/Out：In
  类型：逻辑型
  可空：Y
  意思：是否让其自动启动，默认为真，自动启动
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleHelp_APISystem_AutoStart(LPCXSTR lpszDesName, bool bIsAuto = true);