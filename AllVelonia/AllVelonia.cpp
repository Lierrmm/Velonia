#include "stdafx.h"
#include "Globals.h"
#include "Invoker.h"
#include "Detour.h"
#include "Vectors.h"
#include "Utilities.h"

#define m_ModuleName "Velonia.xex"
//#define _debug // uncomment this if you want to test with a module loader.

struct Velonia
{
	HANDLE m_Module;
	BOOL bDashboard;
	BOOL bInitialized;
	BOOL bDetachModule;
	BOOL bBannedClient;
};

Velonia VE;
PCHAR PATH_XEX = nullptr;
PCHAR PATH_INI = nullptr;
BYTE CPUKey[0x10] = {0};
BOOL DashLoaded = FALSE;
#pragma region TU9
#include "TU9_Structs.h"
#include "TU9_Addrs.h"
#include "TU9_Funcs.h"
#include "TU9_Draw.h"
#include "TU9_Menu.h"
#include "TU9_Aim.h"
#include "TU9_Esp.h"
#include "TU9_Hooks.h"
#pragma endregion
#pragma region TU17
#include "TU17_Structs.h"
#include "TU17_Addrs.h"
#include "TU17_Funcs.h"
#include "TU17_Draw.h"
#include "TU17_Menu.h"
#include "TU17_Aim.h"
#include "TU17_Esp.h"
#include "TU17_Hooks.h"
#pragma endregion
#pragma region TU24
#include "TU24_Structs.h"
#include "TU24_Addrs.h"
#include "TU24_Funcs.h"
#include "TU24_Draw.h"
#include "TU24_Menu.h"
#include "TU24_Aim.h"
#include "TU24_Esp.h"
#include "TU24_Hooks.h"
#pragma endregion
#if defined(_debug)
#pragma region TU7
//#include "TU7_Structs.h"
//#include "TU7_Addrs.h"
//#include "TU7_Funcs.h"
//#include "TU7_Draw.h"
//#include "TU7_Menu.h"
//#include "TU7_Aim.h"
//#include "TU7_Esp.h"
//#include "TU7_Hooks.h"
#pragma endregion
#pragma region TU11
//#include "TU11_Structs.h"
//#include "TU11_Addrs.h"
//#include "TU11_Funcs.h"
//#include "TU11_Draw.h"
//#include "TU11_Menu.h"
//#include "TU11_Aim.h"
//#include "TU11_Esp.h"
//#include "TU11_Hooks.h"
#pragma endregion
#endif

DWORD (__cdecl* XamGetCurrentTitleID)() = reinterpret_cast<DWORD(__cdecl*)()>(Utils::ResolveFunction("xam.xex", 0x1CF));

HRESULT GetIntegrity()
{
	VE.m_Module = GetModuleHandle(m_ModuleName);
	if (!VE.m_Module)
	{
		printf("m_ModuleName != %s\n", m_ModuleName);
		Utils::XNotifyUI(L"Tamper Error!");
	}
	return ERROR_SUCCESS;
}

wchar_t final[0x37];
char XamGT[0x16], msg[0x37];

void setupClient()
{
	while (!VE.bDetachModule)
	{
		Sleep(10);
		if (XamGetCurrentTitleID() == 0xFFFE07D1)
		{
			if (!VE.bDashboard)
			{
				VE.bDashboard = TRUE;
				Sleep(100);
			}
		}
		else
		{
			switch (XamGetCurrentTitleID())
			{
			case 0x41560817:
				if (!VE.bInitialized && !strcmp(reinterpret_cast<CONST PCHAR>(0x82001270), "multiplayer") == TRUE)
				{
					VE.bInitialized = TRUE;
					Sleep(8500);
					Utils::XexThread(reinterpret_cast<LPTHREAD_START_ROUTINE>(TU9::iniTU9));
					Utils::XNotifyUI(L"[Velonia] TU9 Loaded");
				}
				break;
			case 0x415608CB:
				if (!VE.bInitialized && !strcmp(reinterpret_cast<CONST PCHAR>(0x82001458), "multiplayer") == TRUE)
				{
					VE.bInitialized = TRUE;
					Sleep(8500);
					Utils::XexThread(reinterpret_cast<LPTHREAD_START_ROUTINE>(TU24::iniTU24));
					Utils::XNotifyUI(L"[Velonia] TU24 Loaded");
				}
				break;
			case 0x415608FC:
				if (!VE.bInitialized && !strcmp(reinterpret_cast<CONST PCHAR>(0x82000C9C), "multiplayer") == TRUE)
				{
					VE.bInitialized = TRUE;
					Sleep(8500);
					Utils::XexThread(reinterpret_cast<LPTHREAD_START_ROUTINE>(TU17::iniTU17));
					Utils::XNotifyUI(L"[Velonia] TU17 Loaded");
				}
				break;
			case 0x415607FF:
				if (!VE.bInitialized && !strcmp(reinterpret_cast<CONST PCHAR>(0x8200236C), "multiplayer") == TRUE)
				{
					VE.bInitialized = TRUE;
					Sleep(8500);
					/*Utils::XexThread(reinterpret_cast<LPTHREAD_START_ROUTINE>(TU17::iniTU17));*/
					Utils::XNotifyUI(L"[Velonia] TU2 Coming Soon");
				}
				break;
			default: VE.bInitialized = FALSE;
				break;
			}
		}
	}
}

#if defined(_debug)
void debug()
{
	if (XamGetCurrentTitleID() == 0x415608CB)
	{
		VE.bInitialized = TRUE;
		Sleep(3500);
		if (!strcmp(reinterpret_cast<CONST PCHAR>(0x82001458), "multiplayer") == TRUE) TU24::iniTU24();
		Utils::XNotifyUI(L"[Velonia] TU24 Loaded");
	}
	else if (XamGetCurrentTitleID() == 0x41560817)
	{
		VE.bInitialized = TRUE;
		Sleep(3500);
		if (!strcmp(reinterpret_cast<CONST PCHAR>(0x82001270), "multiplayer") == TRUE) TU9::iniTU9();
		Utils::XNotifyUI(L"[Velonia] TU9 Loaded");
	}
	else if (XamGetCurrentTitleID() == 0x415608FC)
	{
		VE.bInitialized = TRUE;
		Sleep(3500);
		TU17::iniTU17();
		Utils::XNotifyUI(L"[Velonia] TU17 Loaded");
	}
	/*else if (XamGetCurrentTitleID() == 0x41560855)
	{
		VE.bInitialized = TRUE;
		Sleep(3500);
		TU11::iniTU11();
		Utils::XNotifyUI(L"[Velonia] TU11 Loaded");
	}*/
	/*else if (XamGetCurrentTitleID() == 0x4156081C)
	{
		VE.bInitialized = TRUE;
		Sleep(3500);
		TU7::iniTU7();
		Utils::XNotifyUI(L"[Velonia] TU7 Loaded");
	}*/
	else
	{
		Utils::XNotifyUI(L"Can't Find Valid Game");
	}
}
#endif

BOOL Initialize()
{
	if (!InitializeHvxPeekPoke()) return FALSE;
	return TRUE;
}

BOOL WINAPI DllMain(HANDLE h, DWORD r, LPVOID lp) {
	switch (r) {
	case DLL_PROCESS_ATTACH:
	#if defined(_debug)
		debug();
	#else
		if (Initialize()) {
			Utils::XexThread(reinterpret_cast<LPTHREAD_START_ROUTINE>(setupClient));
		}
	#endif
		break;
	case DLL_PROCESS_DETACH:
		VE.bDetachModule = true;
		#pragma region TU9
		TU9::Menu_PaintAll.takeDownDetour();
		TU9::XamInputGetState.takeDownDetour();
		TU9::MatList.takeDownDetour();
		TU9::textList.takeDownDetour();
		TU9::writePacket.takeDownDetour();
		TU9::_svECC.takeDownDetour();
		TU9::_CLPSM.takeDownDetour();
		TU9::_svCRS.takeDownDetour();
		TU9::_AAPL.takeDownDetour();
		#pragma endregion
		#pragma region TU17
		TU17::Menu_PaintAll.takeDownDetour();
		TU17::XamInputGetState.takeDownDetour();
		TU17::textList.takeDownDetour();
		TU17::matList.takeDownDetour();
		TU17::writePacket.takeDownDetour();
		#pragma endregion
		#pragma region TU24
		TU24::takeDownDetours();
		#pragma endregion
		#if defined(_debug)
		#endif
		break;
	}
	return true;
}
