﻿#include "XDeamon_Hdr.h"

bool XDeamon_Parament(int argc, char **argv)
{
    LPCXSTR lpszBaseCfg = "./XEngine_Config/XEngine_Config.json";
    LPCXSTR lpszListCfg = "./XEngine_Config/XEngine_ConfigList.json";

    if (!ModuleConfigure_Json_File(lpszBaseCfg, &st_ServiceConfig))
    {
        return false;
    }
    if (!ModuleConfigure_Json_LoadList(lpszListCfg, &st_ConfigList))
    {
        return false;
    }

    for (int i = 0;i < argc;i++)
    {
        if ((0 == strcmp("-h", argv[i])) || (0 == strcmp("-H", argv[i])))
        {
            XDeamon_ParamentHelp();
            return false;
        }
        if ((0 == strcmp("-v", argv[i])) || (0 == strcmp("-V", argv[i])))
        {
            printf("Version：%s\n", st_ServiceConfig.st_XVer.pStl_ListVer->front().c_str());
            return false;
        }
        else if (0 == strcmp("-a", argv[i]))
        {
            st_ServiceConfig.bAutoStart = true;
        }
        else if (0 == strcmp("-w", argv[i]))
        {
            st_ServiceConfig.bHideWnd = true;
        }
    }
    return true;
}
void XDeamon_ParamentHelp()
{
    printf("--------------------------启动参数帮助开始--------------------------\n");
    printf("后台管理服务启动参数：程序 参数 参数值，参数是区分大小写的。如果不指定将会加载默认的json配置文件里面的参数\n");
    printf("-h or -H：启动参数帮助提示信息\n");
    printf("-a：设置服务跟随机器一起启动\n");
    printf("-w：设置窗口隐藏启动\n");
    printf("--------------------------启动参数帮助结束--------------------------\n");
}
