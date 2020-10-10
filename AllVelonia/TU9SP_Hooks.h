#ifndef TU9SP_HOOKS_H
#define TU9SP_HOOKS_H

namespace TU9SP
{
	inline void playerDvars() {
		Cbuf_AddText(0, va(";cg_gun_x %i;", cg_gun_x));
		Cbuf_AddText(0, va(";cg_gun_y %i;", cg_gun_y));
		Cbuf_AddText(0, va(";cg_gun_z %i;", cg_gun_z));
		Cbuf_AddText(0, va(";cg_fov %i;", cg_fov));
	}

	bool done = false;
	detour<void> menu_paintviewport;
	inline void _menu_paintviewport(int dc)
	{
		if (VE.bDetachModule) return menu_paintviewport.callOriginal(dc);
		menu_paintviewport.callOriginal(dc);
		if (CL_IsLocalClientInGame(0) && !CL_IsPauseMenuOpen())
		{
			getStructs();
			RunMenu();
			//playerDvars();
			if (_showNewsbar) drawNewsBar();
			if (drawinfo) drawInfo();
			if (_drawConsoleInfo) drawConsoleInfo();
			drawESP();
		}
	}

	detour<DWORD> XamInputGetState;
	inline DWORD XamInputGetState_Hook(DWORD r3, DWORD r4, PXINPUT_STATE r5) {
		auto XInput = XamInputGetState.callOriginal(r3, r4, r5);
		if (VE.bDetachModule) return XInput;
		if (r3 != 0 || XInput != 0) return XInput;
		if (CE.menuOpen) {
			r5->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_UP;
			r5->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_DOWN;
			r5->Gamepad.wButtons &= ~XINPUT_GAMEPAD_LEFT_SHOULDER;
			r5->Gamepad.wButtons &= ~XINPUT_GAMEPAD_RIGHT_SHOULDER;
			r5->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_LEFT;
			r5->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_RIGHT;
			r5->Gamepad.wButtons &= ~XINPUT_GAMEPAD_B;
			r5->Gamepad.wButtons &= ~XINPUT_GAMEPAD_X;
			r5->Gamepad.wButtons &= ~XINPUT_GAMEPAD_A;
		}
		return XInput;
	}
	
	inline void iniTU9()
	{
		menu_paintviewport.setupDetour(0x822D15A8, _menu_paintviewport);
		XamInputGetState.setupDetour(0x823F12E4, XamInputGetState_Hook);
		if (CL_IsLocalClientInGame(0)) iprintlnbold("BU9™ Injected.");
	}
}
#endif // TU9SP_HOOKS_H
