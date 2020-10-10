#ifndef TU24SP_HOOKS_H
#define TU24SP_HOOKS_H

namespace TU24SP
{
	detour<void> debugtext;
	inline void DrawMenuDebugText(int dc)
	{
		if (VE.bDetachModule) return debugtext.callOriginal(dc);
		debugtext.callOriginal(dc);
		if(CL_IsLocalClientInGame(0))
		{
			getStructs();
			RunMenu();
			drawESP();
		}
	}

	bool canshoot = false;
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

		if (autoshoot && canshoot) {
			r5->Gamepad.bRightTrigger = 100;
			canshoot = false;
		}
		return XInput;
	}

	detour<void> textList;
	inline void texthook(const char* r3, int r4, void* r5, float f1, float f2, float f3, float f4, float f5, const float* color, int something) {
		if (VE.bDetachModule) return textList.callOriginal(r3, r4, r5, f1, f2, f3, f4, f5, color, something);
		auto* const txt = const_cast<char*>(r3);
		if (!strcmp(txt, "SPECIAL OPS")) r3 = va("%s", "Velonia SP");
		if (!strcmp(txt, "CAMPAIGN")) r3 = va("%s", "Velonia CP");
		if (!strcmp(txt, "MULTIPLAYER")) r3 = va("%s", "Velonia MP");

		textList.callOriginal(r3, r4, r5, f1, f2, f3, f4, f5, color, something);
	}

	detour<void> MatList;
	inline void zoneHook(float f1, float f2, float f3, float f4, float f5, int f6, int f7, float f8, float* color, int material) {
		if (VE.bDetachModule) return MatList.callOriginal(f1, f2, f3, f4, f5, f6, f7, f8, color, material);
		auto* const mat = *reinterpret_cast<char**>(material);
		if (!strcmp(mat, "mw2_main_cloud_overlay") || !strcmp(mat, "mw2_main_cloud_overlay_write_dest_alpha") || !strcmp(mat, "mw2_main_cloud_overlay_dest_alpha_masked") || !strcmp(mat, "navbar_selection_bar")) color = secondaryColor;
		if (!strcmp(mat, "background_image_blur_less") || !strcmp(mat, "background_image") || !strcmp(mat, "background_image_blur_less_dest_alpha_masked")) color = primaryColor;
		if (!strcmp(mat, "iotd_image") || !strcmp(mat, "playlist_population")) color = hideWithAlpha;

		MatList.callOriginal(f1, f2, f3, f4, f5, f6, f7, f8, color, material);
	}

	detour<void> writePacket;
	inline void CL_WritePacket(int r3) {
		if (VE.bDetachModule) return writePacket.callOriginal(r3);
		packetTimer++;
		if (CL_IsLocalClientInGame(0))
		{
			getStructs();
			auto const currentCmd = ca.getCmd();
			auto oldCmd = ca.getLastCmd();
			auto cmd = ca.GetCmd(ca.cmdNumber);
			oldCmd = currentCmd;
			oldCmd.serverTime -= 1;
			if (aimbot) {
				const auto closestClient = getClosestClient(cg.clientNum);
				if (closestClient != -1)
				{
					auto head = GetTagPos(closestClient, Bones[targetBone]);
					const auto newAngles = VectorToAngles(head - cg.refdef.Origin) - cg.ps->viewAngles;
					if (silentaim) {
						snapbot = false;
						AimSilent(oldCmd, newAngles);
					}
					if (snapbot) {
						silentaim = false;
						if (!AimKey) {
							ca.viewangles = newAngles;
							SHORT2ANGLE(oldCmd.angles[1]);
						}
						else {
							if (Key_isDown(0, 0x12)) {
								ca.viewangles = newAngles;
								SHORT2ANGLE(oldCmd.angles[1]);
							}
						}
					}
					if (smoothAim) {
						silentaim = false; snapbot = false;
						if (!AimKey) {
							_SmoothAngle(newAngles, ca.viewangles, 30);
						}
						else {
							if (Key_isDown(0, 0x12)) {
								_SmoothAngle(newAngles, ca.viewangles, 30);
							}
						}
					}
					if (nospread) noSpread(oldCmd);
					if (autoshoot) {
						cmd.buttons &= ~1;
						oldCmd.buttons |= 1;
						canshoot = true;
					}
				}
				if (_antispin) {
					static float spin;
					spin += 5.f;
					if (spin > 70.f) spin = -70.f;
					cmd.angles[0] = ANGLE2SHORT(spin - cg.ps->viewAngles.x);
				}
				if (_antiflip) {
					static bool flip;
					flip ^= true;
					cmd.angles[0] = ANGLE2SHORT((flip ? 70 : -70) - cg.ps->viewAngles.x);
				}
				if (_antiy) {
					cmd.angles[1] = ANGLE2SHORT(rand() % 2 ? (69 - 135) : (69 - 225.0f));
				}
				if (_antix) {
					cmd.angles[0] = ANGLE2SHORT(70 - cg.ps->viewAngles.x);
				}
				if (_antishield) {
					cmd.angles[0] = ANGLE2SHORTFLOAT(FloatMinMax(-69.99f, 69.99f) - cg.ps->viewAngles.x);
				}
			}
			if (fakelag && Centity_s[cg.clientNum].pose.eType & 1 && CL_IsLocalClientInGame(0)) {
				if (oldCmd.buttons != 0x80800 && oldCmd.buttons != 0x1) {
					_mFakeLag = true;
				}
				else {
					_mFakeLag = false;
				}
			}
		}
		if (fakelag && Centity_s[cg.clientNum].pose.eType & 1 && CL_IsLocalClientInGame(0) && _mFakeLag) {
			if (packetTimer >= 15) {
				packetTimer = 0;
				writePacket.callOriginal(r3);
			}
		}
		else {
			writePacket.callOriginal(r3);
		}
	}
	
	inline void iniTU24()
	{
		debugtext.setupDetour(0x822E0488, DrawMenuDebugText);
		textList.setupDetour(0x823F5158, texthook);
		XamInputGetState.setupDetour(0x824F0934, XamInputGetState_Hook);
		MatList.setupDetour(0x823F4878, zoneHook);
		//writePacket.setupDetour(0x8211FF20, CL_WritePacket);
		aimbot = true;
		snapbot = true;
		AimKey = true;
	}

	inline void takeDownTU24()
	{
		debugtext.takeDownDetour();
		textList.takeDownDetour();
		XamInputGetState.takeDownDetour();
		MatList.takeDownDetour();
		writePacket.takeDownDetour();
	}
}
#endif // TU24SP_HOOKS_H
