#pragma once
/********************************************************************
//    Created:     2023/05/15  10:01:38
//    File Name:   D:\XEngine_Deamon\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_Error.h
//    File Path:   D:\XEngine_Deamon\XEngine_Source\XEngine_ModuleHelp
//    File Base:   ModuleHelp_Error
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     配置模块导出错误
//    History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////
//                            系统函数错误表
//////////////////////////////////////////////////////////////////////////
#define ERROR_MODULE_HELP_SYSTEMAPI_PARAMENT 0xB0001                      //参数错误
#define ERROR_MODULE_HELP_SYSTEMAPI_SYSENABLE 0xB0002                     //自动启动服务启用失败
#define ERROR_MODULE_HELP_SYSTEMAPI_SYSDISABLE 0xB0003                    //禁用自动启动服务失败
#define ERROR_MODULE_HELP_SYSTEMAPI_GETFILENAME 0xB0004                   //获取自身文件名失败
#define ERROR_MODULE_HELP_SYSTEMAPI_COINIT 0xB0005                        //打开OLD失败
#define ERROR_MODULE_HELP_SYSTEMAPI_QUERY 0xB0006                         //查询接口失败