#include "stdafx.h"
#include "../res/resource.h"

#include "msg.h"

static char* __THIS_FILE__ = __FILE__;

Common::CComConfig* comcfg;

#ifdef ETW_LOGGER

// {A561E523-8690-4F8D-8768-15302DB93BAC}
static const GUID providerGuid = 
{ 0xa561e523, 0x8690, 0x4f8d, { 0x87, 0x68, 0x15, 0x30, 0x2d, 0xb9, 0x3b, 0xac } };

ETWLogger g_etwLogger(providerGuid);

#endif

void com_load_config(void)
{
	char mp[MAX_PATH]={0};
	GetModuleFileName(NULL, mp, __ARRAY_SIZE(mp));
	strcpy(strrchr(mp, '\\')+1, "common.ini");
	comcfg = new Common::CComConfig;
	comcfg->LoadFile(mp);
}

void com_unload_config(void)
{
	comcfg->SaveFile();
	delete comcfg;
}

Common::c_the_app theApp;

int CALLBACK WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{
	//InitCommonControls();
	LoadLibrary("RichEd20.dll");

	EtwLog("程序已运行");

	com_load_config();

	Common::CComWnd maindlg;
	maindlg.Create(nullptr, MAKEINTRESOURCE(IDD_DLG_MAIN));
	maindlg.CenterWindow();
	maindlg.ShowWindow();

	Common::CWindowManager::MessageLoop();
	
	com_unload_config();

	EtwLog("程序已结束");

#ifdef _DEBUG
	Sleep(500);
#endif
	MessageBeep(MB_OK);
	return 0;
}

