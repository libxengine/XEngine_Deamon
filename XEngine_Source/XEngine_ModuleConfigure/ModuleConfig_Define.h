﻿#pragma once
/********************************************************************
//    Created:     2021/12/02  16:09:03
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ModuleConfigure\ModuleConfig_Define.h
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ModuleConfigure
//    File Base:   ModuleConfig_Define
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     配置模块导出定义
//    History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////
//                        导出的数据结构
//////////////////////////////////////////////////////////////////////////
typedef struct tag_XEngine_ServiceConfig
{
	bool bDeamon;                             //是否以守护进程启动,LINUX有效
	bool bAutoStart;                          //是否自动启动
	bool bHideWnd;                            //是否隐藏
	struct  
	{
		int nTimeError;                       //最大错误次数
		int nTimeCheck;                       //检测等待时间
	}st_XTime;
	struct
	{
		XCHAR tszLogFile[MAX_PATH];           //日志保存位置
		int nMaxSize;                         //最大日志大小
		int nMaxCount;                        //最大日志个数
		int nLogLeave;                        //日志等级
	}st_XLog;
	struct  
	{
		list<string> *pStl_ListVer;           //版本列表
	}st_XVer;
}XENGINE_SERVICECONFIG;
//用户进程列表
typedef struct
{
	bool bEnable;                      //是否启用
	XCHAR tszAPPName[MAX_PATH];         //应用程序名称
	XCHAR tszAPPPath[MAX_PATH];         //应用程序路径
	bool bService;                     //是否为服务启动
	int nReTime;                       //是否自动重启
	//自定义
	int nErrorTime;
	__int64x nStartTime;
}XENGINE_APPINFO;
typedef struct
{
	list<XENGINE_APPINFO>* pStl_ListApp;
}XENGINE_CONFIGAPP;
//////////////////////////////////////////////////////////////////////////
//                        导出函数定义
//////////////////////////////////////////////////////////////////////////
extern "C" XLONG ModuleConfigure_GetLastError(int* pInt_ErrorCode = NULL);
/************************************************************************/
/*                        文件配置读取                                  */
/************************************************************************/
/********************************************************************
函数名称：ModuleConfigure_Json_File
函数功能：读取JSON配置文件
 参数.一：lpszConfigFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要读取的配置文件
 参数.二：pSt_ServerConfig
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出服务配置信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleConfigure_Json_File(LPCXSTR lpszConfigFile, XENGINE_SERVICECONFIG* pSt_ServerConfig);
/********************************************************************
函数名称：ModuleConfigure_Json_LoadList
函数功能：JSON APP列表配置读取
 参数.一：lpszConfigFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入文件地址
 参数.二：pSt_FileConfig
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出获取到的配置信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleConfigure_Json_LoadList(LPCXSTR lpszConfigFile, XENGINE_CONFIGAPP * pSt_AppConfig);