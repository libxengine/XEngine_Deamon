#include "XDeamon_Hdr.h"

bool bIsRun = false;
XHANDLE xhLog = NULL;
unique_ptr<thread> pSTDThread = NULL;
XENGINE_SERVICECONFIG st_ServiceConfig;
XENGINE_CONFIGAPP st_ConfigList;

void ServiceApp_Stop(int signo)
{
	if (bIsRun)
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, "服务器退出...");
		bIsRun = false;

		if (NULL != pSTDThread)
		{
			pSTDThread->join();
			pSTDThread = NULL;
		}
		HelpComponents_XLog_Destroy(xhLog);
		exit(0);
	}
}
int main(int argc, char** argv)
{
#ifdef _MSC_BUILD
	WSADATA st_WSAData;
	WSAStartup(MAKEWORD(2, 2), &st_WSAData);
#endif

	bIsRun = true;
	HELPCOMPONENTS_XLOG_CONFIGURE st_XLogConfig;
	LPCXSTR lpszWndName = _X("XEngine_DeamonApp");

	memset(&st_XLogConfig, '\0', sizeof(HELPCOMPONENTS_XLOG_CONFIGURE));
	memset(&st_ServiceConfig, '\0', sizeof(XENGINE_SERVICECONFIG));

	if (!XDeamon_Parament(argc, argv))
	{
		printf("初始化参数失败,错误:%lX!\n", ModuleConfigure_GetLastError());
		goto NETSERVICE_APPEXIT;
	}
	st_XLogConfig.XLog_MaxBackupFile = st_ServiceConfig.st_XLog.nMaxCount;
	st_XLogConfig.XLog_MaxSize = st_ServiceConfig.st_XLog.nMaxSize;
	strcpy(st_XLogConfig.tszFileName, st_ServiceConfig.st_XLog.tszLogFile);
	xhLog = HelpComponents_XLog_Init(HELPCOMPONENTS_XLOG_OUTTYPE_FILE | HELPCOMPONENTS_XLOG_OUTTYPE_STD, &st_XLogConfig);
	if (NULL == xhLog)
	{
		printf("初始化日志服务失败,无法继续!\n");
		goto NETSERVICE_APPEXIT;
	}
	HelpComponents_XLog_SetLogPriority(xhLog, st_ServiceConfig.st_XLog.nLogLeave);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, "启动服务中，初始化日志系统成功");

	signal(SIGINT, ServiceApp_Stop);
	signal(SIGTERM, ServiceApp_Stop);
	signal(SIGABRT, ServiceApp_Stop);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, "启动服务中，初始化信号处理成功");

	if (!ModuleHelp_APISystem_AutoStart(lpszWndName, st_ServiceConfig.bAutoStart))
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, "启动服务中，注册软件开机启动失败!错误:%lX", ModuleHelp_GetLastError());
		goto NETSERVICE_APPEXIT;
	}
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中，设置软件开机启动标志成功,标志位:%d"), st_ServiceConfig.bAutoStart);

	if (st_ServiceConfig.bHideWnd)
	{
#ifdef _MSC_BUILD
		SetConsoleTitleA(lpszWndName);
		HWND hWnd = FindWindowA(NULL, lpszWndName);

		if (NULL == hWnd)
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中，设置窗口隐藏失败,没有找到句柄"));
		}
		else
		{
			ShowWindow(hWnd, SW_HIDE);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中，设置窗口隐藏成功"));
		}
#endif
	}
	
	pSTDThread = make_unique<thread>(APPManage_Thread_Process);
	if (NULL == pSTDThread)
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, "启动服务中，启动进程管理线程失败");
		goto NETSERVICE_APPEXIT;
	}
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, "启动服务中，启动进程管理线程成功");

	for (auto stl_ListIterator = st_ConfigList.pStl_ListApp->begin(); stl_ListIterator != st_ConfigList.pStl_ListApp->end(); stl_ListIterator++)
	{
		if (stl_ListIterator->bEnable)
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中，加载守护进程:%s,成功,开始守护进程"), stl_ListIterator->tszAPPName);
		}
		else
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("启动服务中，加载守护进程:%s,成功,此项目未启用"), stl_ListIterator->tszAPPName);
		}
	}
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中，加载守护进程列表成功,加载的列表个数:%d"), st_ConfigList.pStl_ListApp->size());
	
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, "启动服务中，所有服务已经启动完毕,程序运行中,XEngine版本:%s%s,服务器发行次数:%d,版本;%s", BaseLib_OperatorVer_XNumberStr(), BaseLib_OperatorVer_XTypeStr(), st_ServiceConfig.st_XVer.pStl_ListVer->size(), st_ServiceConfig.st_XVer.pStl_ListVer->front().c_str());

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
NETSERVICE_APPEXIT:
	if (bIsRun)
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, "后台控制服务关闭，服务器退出...");
		bIsRun = false;

		if (NULL != pSTDThread)
		{
			pSTDThread->join();
			pSTDThread = NULL;
		}
		HelpComponents_XLog_Destroy(xhLog);
	}

#ifdef _MSC_BUILD
	WSACleanup();
#endif
	return 0;
}
