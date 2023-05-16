#include "pch.h"
#include "ModuleHelp_APISystem.h"
/********************************************************************
//    Created:     2023/05/15  09:55:23
//    File Name:   D:\XEngine_Deamon\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_APISystem\ModuleHelp_APISystem.cpp
//    File Path:   D:\XEngine_Deamon\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_APISystem
//    File Base:   ModuleHelp_APISystem
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     系统API函数帮助库
//    History:
*********************************************************************/
CModuleHelp_APISystem::CModuleHelp_APISystem()
{

}
CModuleHelp_APISystem::~CModuleHelp_APISystem()
{

}
//////////////////////////////////////////////////////////////////////////
//                        公用函数
//////////////////////////////////////////////////////////////////////////
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
bool CModuleHelp_APISystem::ModuleHelp_APISystem_AutoStart(LPCXSTR lpszDesName, bool bIsAuto /* = true */)
{
	ModuleHelp_IsErrorOccur = false;

#ifdef _MSC_BUILD
	if (bIsAuto)
	{
		IShellLinkA* pSt_ILink = NULL;      //IShellLink对象指针
		IPersistFile* pSt_IFile = NULL;    //IPersisFil对象指针
		//创建IShellLink对象
		CoInitializeEx(NULL, COINIT_MULTITHREADED);
		HRESULT hResult = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&pSt_ILink);
		if (FAILED(hResult))
		{
			ModuleHelp_IsErrorOccur = true;
			ModuleHelp_dwErrorCode = ERROR_MODULE_HELP_SYSTEMAPI_COINIT;
			return false;
		}
		//从IShellLink对象中获取IPersistFile接口
		hResult = pSt_ILink->QueryInterface(IID_IPersistFile, (void**)&pSt_IFile);
		if (FAILED(hResult))
		{
			ModuleHelp_IsErrorOccur = true;
			ModuleHelp_dwErrorCode = ERROR_MODULE_HELP_SYSTEMAPI_QUERY;
			return false;
		}

		XCHAR tszFilePath[MAX_PATH];
		XCHAR tszFileName[MAX_PATH];

		memset(tszFilePath, '\0', MAX_PATH);
		memset(tszFileName, '\0', MAX_PATH);

		GetCurrentDirectoryA(MAX_PATH, tszFilePath);
		GetModuleFileNameA(NULL, tszFileName, MAX_PATH);
		//目标
		pSt_ILink->SetPath(tszFileName);
		//工作目录
		pSt_ILink->SetWorkingDirectory(tszFilePath);
		//备注
		pSt_ILink->SetDescription(lpszDesName);
		//显示方式
		pSt_ILink->SetShowCmd(SW_SHOW);
		//保存快捷方式到指定目录下

		XCHAR tszAFile[MAX_PATH];
		WCHAR tszUFile[MAX_PATH];

		memset(tszAFile, '\0', sizeof(tszAFile));
		memset(tszUFile, '\0', sizeof(tszUFile));

		if (S_OK != SHGetFolderPath(NULL, CSIDL_STARTUP, NULL, 0, tszAFile))
		{
			ModuleHelp_IsErrorOccur = true;
			ModuleHelp_dwErrorCode = ERROR_MODULE_HELP_SYSTEMAPI_GETFILENAME;
			return false;
		}
		_tcsxcat(tszAFile, _T("\\XEngine_DeamonApp.lnk"));
		BaseLib_OperatorCharset_AnsiToUnicode(tszAFile, tszUFile);

		hResult = pSt_IFile->Save(tszUFile, TRUE);
		if (FAILED(hResult))
		{
			ModuleHelp_IsErrorOccur = true;
			ModuleHelp_dwErrorCode = ERROR_MODULE_HELP_SYSTEMAPI_SYSENABLE;
			return false;
		}
		pSt_IFile->Release();
		pSt_ILink->Release();
		CoUninitialize();
	}
	else
	{
		XCHAR tszAFile[MAX_PATH];
		memset(tszAFile, '\0', sizeof(tszAFile));

		if (S_OK != SHGetFolderPath(NULL, CSIDL_STARTUP, NULL, 0, tszAFile))
		{
			ModuleHelp_IsErrorOccur = true;
			ModuleHelp_dwErrorCode = ERROR_MODULE_HELP_SYSTEMAPI_SYSDISABLE;
			return false;
		}
		_tcsxcat(tszAFile, _T("\\XEngine_DeamonApp.lnk"));
		_xtremove(tszAFile);
	}
#elif __linux__

	LPCXSTR lpszStartStr = _X("/usr/lib/systemd/system/xdeamon.service");
	if (bIsAuto)
	{
		if (0 != _xtaccess(lpszStartStr, F_OK))
		{
			system("sudo cp -rf ./xdeamon.service /usr/lib/systemd/system/xdeamon.service");
		}

		XCHAR tszServiceStr[MAX_PATH];
		memset(tszServiceStr, '\0', MAX_PATH);

		_xstprintf(tszServiceStr, _X("sudo systemctl enable xdeamon"));
		if (-1 == system(tszServiceStr))
		{
			ModuleHelp_IsErrorOccur = true;
			ModuleHelp_dwErrorCode = ERROR_MODULE_HELP_SYSTEMAPI_SYSENABLE;
			return false;
		}
	}
	else
	{
		XCHAR tszServiceStr[MAX_PATH];
		memset(tszServiceStr, '\0', MAX_PATH);

		_xstprintf(tszServiceStr, _X("systemctl disable xdeamon"));
		if (-1 == system(tszServiceStr))
		{
			ModuleHelp_IsErrorOccur = true;
			ModuleHelp_dwErrorCode = ERROR_MODULE_HELP_SYSTEMAPI_SYSDISABLE;
			return false;
		}
		_xtremove(lpszStartStr);
	}
#endif
	return true;
}