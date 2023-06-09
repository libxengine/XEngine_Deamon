﻿#include "XDeamon_Hdr.h"

bool APPManage_CreateService(XENGINE_APPINFO *pSt_APPInfo)
{
	XCHAR tszCmdExe[1024];
	memset(tszCmdExe, '\0', sizeof(tszCmdExe));

#ifdef _MSC_BUILD
	sprintf(tszCmdExe, "sc stop %s", pSt_APPInfo->tszAPPName);
#else
	sprintf(tszCmdExe, "systemctl restart %s", pSt_APPInfo->tszAPPName);
#endif
	if (-1 == system(tszCmdExe))
	{
		return false;
	}
#ifdef _MSC_BUILD
	memset(tszCmdExe, '\0', sizeof(tszCmdExe));
	sprintf(tszCmdExe, "sc start %s", pSt_APPInfo->tszAPPName);
	if (-1 == system(tszCmdExe))
	{
		return false;
	}
#endif
	return true;
}
bool APPManage_CreateProcess(XENGINE_APPINFO* pSt_APPInfo, XLONG* pdwProcessID)
{
	XCHAR tszCmdExe[1024];
	memset(tszCmdExe, '\0', sizeof(tszCmdExe));

	sprintf(tszCmdExe, "%s%s", pSt_APPInfo->tszAPPPath, pSt_APPInfo->tszAPPName);
	if (!SystemApi_Process_CreateProcess(pdwProcessID, tszCmdExe))
	{
		return false;
	}
	return true;
}

bool APPManage_Thread_Process()
{
	while (bIsRun)
	{
		//轮询检测进程列表
		list<XENGINE_APPINFO>::iterator stl_ListIterator = st_ConfigList.pStl_ListApp->begin();
		for (; stl_ListIterator != st_ConfigList.pStl_ListApp->end(); stl_ListIterator++)
		{
			//是否启用
			if (!stl_ListIterator->bEnable)
			{
				continue;
			}
			//重试次数判断
			if (stl_ListIterator->nErrorTime > st_ServiceConfig.st_XTime.nTimeError)
			{
				stl_ListIterator->bEnable = false;
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, "服务名：%s，由于超过指定启动失败次数：%d，这个服务检测功能被关闭...", stl_ListIterator->tszAPPName, st_ServiceConfig.st_XTime.nTimeError);
				continue;
			}
			XENGINE_APPINFO st_APPInfo = *stl_ListIterator;

			if (stl_ListIterator->nReTime > 0)
			{
				//进程自动重启
				__int64x nNowTime = time(NULL);
				if ((nNowTime - stl_ListIterator->nStartTime) > stl_ListIterator->nReTime)
				{
					if (stl_ListIterator->bService)
					{
						if (APPManage_CreateService(&st_APPInfo))
						{
							XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, "自动重启,重启服务：%s 成功...", stl_ListIterator->tszAPPName);
						}
						else
						{
							stl_ListIterator->nErrorTime++;
							XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, "自动重启,重启服务：%s 失败，错误码：%d...", stl_ListIterator->tszAPPName, errno);
						}
					}
					else
					{
						XLONG dwProcessId = 0;
						SystemApi_Process_Stop(stl_ListIterator->tszAPPName);
						if (APPManage_CreateProcess(&st_APPInfo, &dwProcessId))
						{
							XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, "自动重启,重启进程：%s 成功，进程ID：%d...", stl_ListIterator->tszAPPName, dwProcessId);
						}
						else
						{
							stl_ListIterator->nErrorTime++;
							XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, "自动重启,重启进程：%s 失败，错误码：%lX...", stl_ListIterator->tszAPPName, SystemApi_GetLastError());
						}
					}
					stl_ListIterator->nStartTime = time(NULL);
				}
			}
			else 
			{
				//进程不存在才启动
				SYSTEMAPI_PROCESS_INFOMATION st_ProcessInfo;
				memset(&st_ProcessInfo, '\0', sizeof(SYSTEMAPI_PROCESS_INFOMATION));
				if (SystemApi_Process_GetProcessInfo(&st_ProcessInfo, stl_ListIterator->tszAPPName))
				{
					if (ENUM_SYSTEMSDK_PROCFILE_PROCFILE_PROCESS_STATE_ZOMBIE == st_ProcessInfo.en_ProcessState)
					{
#ifndef _MSC_BUILD
						//僵尸进程必须使用waitpid退出
						int nStatus = 0;
						waitpid(st_ProcessInfo.nPid, &nStatus, 0);
#endif
					}
					else
					{
						continue;
					}
				}

				if (stl_ListIterator->bService)
				{
					if (APPManage_CreateService(&st_APPInfo))
					{
						XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, "崩溃重启,检查到服务不存在,启动服务：%s 成功...", stl_ListIterator->tszAPPName);
					}
					else
					{
						stl_ListIterator->nErrorTime++;
						XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, "崩溃重启,检查到服务不存在,启动服务：%s 失败，错误码：%d...", stl_ListIterator->tszAPPName, errno);
					}
				}
				else
				{
					XLONG dwProcessId = 0;
					if (APPManage_CreateProcess(&st_APPInfo, &dwProcessId))
					{
						XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, "崩溃重启,检查到进程不存在,启动进程：%s 成功，进程ID：%d...", stl_ListIterator->tszAPPName, dwProcessId);
					}
					else
					{
						stl_ListIterator->nErrorTime++;
						XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, "崩溃重启,检查到进程不存在,启动进程：%s 失败，错误码：%lX...", stl_ListIterator->tszAPPName, SystemApi_GetLastError());
					}
				}
			}
		}
		//休眠用户配置的时间
		std::this_thread::sleep_for(std::chrono::seconds(st_ServiceConfig.st_XTime.nTimeCheck));
	}
	return 0;
}
