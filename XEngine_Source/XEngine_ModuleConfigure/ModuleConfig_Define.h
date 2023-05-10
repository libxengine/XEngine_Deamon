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
	CHAR tszIPAddr[128];                      //本机IP地址,根据需要配置
	BOOL bDeamon;                             //是否以守护进程启动,LINUX有效
	int nPort;                                //服务
	struct
	{
		int nMaxClient;                       //最大客户端个数
		int nMaxQueue;                        //最大队列个数
		int nIOThread;                        //网络IO线程数
		int nThread;                          //业务任务处理线程数
	}st_XMax;
	struct
	{
		int nTimeCheck;                       //检测次数
		int nTimeOut;                         //业务超时时间
	}st_XTime;                                //次数*时间=超时
	struct
	{
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
	CHAR tszAPPName[MAX_PATH];         //应用程序名称
	CHAR tszAPPPath[MAX_PATH];         //应用程序路径
	BOOL bShow;                        //显示还是隐藏 
	BOOL bAutoStart;                   //是否自动启动
	BOOL bEnable;                      //是否启用
	BOOL bService;                     //是否为服务启动
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
extern "C" DWORD ModuleConfigure_GetLastError(int* pInt_ErrorCode = NULL);
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
extern "C" BOOL ModuleConfigure_Json_File(LPCSTR lpszConfigFile, XENGINE_SERVICECONFIG* pSt_ServerConfig);
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
extern "C" BOOL ModuleConfigure_Json_LoadList(LPCSTR lpszConfigFile, XENGINE_CONFIGAPP * pSt_AppConfig);