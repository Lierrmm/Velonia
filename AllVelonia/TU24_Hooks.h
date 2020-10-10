#ifndef TU24_HOOKS_H
#define TU24_HOOKS_H

namespace TU24
{
	inline void playerDvars() {
		Cbuf_AddText(0, va("cg_gun_x %i;", cg_gun_x));
		Cbuf_AddText(0, va("cg_gun_y %i;", cg_gun_y));
		Cbuf_AddText(0, va("cg_gun_z %i;", cg_gun_z));
		Cbuf_AddText(0, va("cg_fov %i;", cg_fov));
		Cbuf_AddText(0, va("cg_thirdpersonrange %i;", tpRange));
		Cbuf_AddText(0, va("cg_thirdpersonangle %i;", tpAngle));
	}

	bool gotName = false;
	detour<void> Menu_PaintAll;
	inline void Menu_PaintAll_Hook(int r3, int r4) {
		if (VE.bDetachModule) return Menu_PaintAll.callOriginal(r3, r4);
		Menu_PaintAll.callOriginal(r3, r4);
		pgStructs();
		
		if (!gotName) {
			gotName = true;
			clientName = reinterpret_cast<char*>(0x839691AC);
			_clanTag = reinterpret_cast<char*>(0x82718A32);
		}
		
		if (Dvar_GetBool("cl_ingame")) {
			getStructs(); RunMenu();
			playerDvars();
			if (_showNewsbar) drawNewsBar();
			if (_noinfect) _autoUninfect();
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
		if (!strcmp(txt, "Searching")) r3 = "Finding Cunt";
		if (!strcmp(txt, "Searching.")) r3 = "Finding Cunt.";
		if (!strcmp(txt, "Searching..")) r3 = "Finding Cunt..";
		if (!strcmp(txt, "Searching...")) r3 = "Finding Cunt...";
		if (!strcmp(txt, "Matched Player")) r3 = "Found Cunt";
		if (!strcmp(txt, "1.8.388110")) r3 = va("[VELONIA] %s", _version);
		textList.callOriginal(r3, r4, r5, f1, f2, f3, f4, f5, color, something);
	}

	detour<void> MatList;
	inline void zoneHook(float f1, float f2, float f3, float f4, float f5, int f6, int f7, float f8, float* color, int material) {
		if (VE.bDetachModule) return MatList.callOriginal(f1, f2, f3, f4, f5, f6, f7, f8, color, material);
		auto* const mat = *reinterpret_cast<char**>(material);
		if (!strcmp(mat, "mw2_main_cloud_overlay") || !strcmp(mat, "mw2_main_cloud_overlay_write_dest_alpha") || !strcmp(mat, "mw2_main_cloud_overlay_dest_alpha_masked") || !strcmp(mat, "navbar_selection_bar")) color = secondaryColor;
		if (!strcmp(mat, "background_image_blur_less") || !strcmp(mat, "background_image") || !strcmp(mat, "background_image_blur_less_dest_alpha_masked")) color = primaryColor;
		if (!strcmp(mat, "iotd_image") || !strcmp(mat, "playlist_population")) color = hideWithAlpha;

		if (!strcmp(mat, "minimap_scanlines")) {
			m_radarXY = Vector2(f1, f2);
			canRenderRadar = true;
		}

		if ((!strcmp(mat, "minimap_scanlines") || !strcmp(mat, "scanlines_stencil"))) {
			if (renderRadar) {
				return;
			}
		}

		MatList.callOriginal(f1, f2, f3, f4, f5, f6, f7, f8, color, material);
	}

	detour<void> r_setFrameFog;
	inline void _R_SetFrameFog(int r3)
	{
		if (VE.bDetachModule) return r_setFrameFog.callOriginal(r3);
		if (Dvar_GetBool("cl_ingame")) {
			getStructs();
			nameStealer();
			drawESP();
			if (esptypes) drawESPTypes();
			if (drawinfo) drawInfo();
			if (renderRadar) drawExternalRadar();
			if (_drawConsoleInfo) drawConsoleInfo();
		}
		r_setFrameFog.callOriginal(r3);
	}

	detour<void> writePacket;
	inline void CL_WritePacket(int r3) {
		if (VE.bDetachModule) return writePacket.callOriginal(r3);
		packetTimer++;
		if (Dvar_GetBool("cl_ingame"))
		{
			getStructs();
			auto const currentCmd = ca->getCmd();
			auto* oldCmd = ca->getLastCmd();
			auto* cmd = ca->GetCmd(ca->CmdNum);
			*oldCmd = *currentCmd;
			oldCmd->servertime -= 1;
			if (aimbot) {
				const auto closestClient = getClosestClient(cg->clientNum);
				if (closestClient != -1)
				{
					auto head = GetTagPos(closestClient, Bones[targetBone]);
					const auto newAngles = VectorToAngles(head - GetPlayerViewOrigin()) - ca->baseAngle;
					if (silentaim) {
						snapbot = false;
						AimSilent(oldCmd, newAngles);
					}
					if (snapbot) {
						silentaim = false;
						if (!AimKey) {
							ca->ViewAngles = newAngles;
							SHORT2ANGLE(oldCmd->viewangles[1]);
						}
						else {
							if (Key_isDown(0, 0x12)) {
								ca->ViewAngles = newAngles;
								SHORT2ANGLE(oldCmd->viewangles[1]);
							}
						}
					}
					if (smoothAim) {
						silentaim = false; snapbot = false;
						if (!AimKey) {
							_SmoothAngle(newAngles, ca->ViewAngles, 30);
						}
						else {
							if (Key_isDown(0, 0x12)) {
								_SmoothAngle(newAngles, ca->ViewAngles, 30);
							}
						}
					}
					if (nospread) noSpread(oldCmd);
					if (autoshoot) {
						cmd->buttons &= ~1;
						oldCmd->buttons |= 1;
						canshoot = true;
					}
				}
				if (_antispin) {
					static float spin;
					spin += 5.f;
					if (spin > 70.f) spin = -70.f;
					cmd->viewangles[0] = ANGLE2SHORT(spin - ca->baseAngle.x);
				}
				if (_antiflip) {
					static bool flip;
					flip ^= true;
					cmd->viewangles[0] = ANGLE2SHORT((flip ? 70 : -70) - ca->baseAngle.x);
				}
				if (_antiy) {
					cmd->viewangles[1] = ANGLE2SHORT(rand() % 2 ? (69 - 135) : (69 - 225.0f));
				}
				if (_antix) {
					cmd->viewangles[0] = ANGLE2SHORT(70 - ca->baseAngle.x);
				}
				if (_antishield) {
					cmd->viewangles[0] = ANGLE2SHORTFLOAT(FloatMinMax(-69.99f, 69.99f) - ca->baseAngle.x);
				}
			}
			if (fakelag && cg->ClientInfo[cg->clientNum].mValid & 1 && Dvar_GetBool("cl_ingame")) {
				if (oldCmd->buttons != 0x80800 && oldCmd->buttons != 0x1) {
					_mFakeLag = true;
				}
				else {
					_mFakeLag = false;
				}
			}
		}
		if (fakelag && cg->ClientInfo[cg->clientNum].mValid & 1 && Dvar_GetBool("cl_ingame") && _mFakeLag) {
			if (packetTimer >= 15) {
				packetTimer = 0;
				writePacket.callOriginal(r3);
			}
		}
		else {
			writePacket.callOriginal(r3);
		}
	}


	detour<int> getSkillsHook;
	inline int Live_GetSkills(int a1, int a2)
	{
		if (VE.bDetachModule) return getSkillsHook.callOriginal(a1, a2);
		return 0;
	}
	
	inline void setupHooks() {
		Menu_PaintAll.setupDetour(0x823091D0, Menu_PaintAll_Hook);
		XamInputGetState.setupDetour(0x8257FF4C, XamInputGetState_Hook);
		textList.setupDetour(0x8241F9E0, texthook);
		MatList.setupDetour(0x82164AF8, zoneHook);
		r_setFrameFog.setupDetour(0x82444510, _R_SetFrameFog);
		writePacket.setupDetour(0x8216DAF0, CL_WritePacket);
		getSkillsHook.setupDetour(0x823E8AE0, Live_GetSkills);
	}

	inline void takeDownDetours()
	{
		Menu_PaintAll.takeDownDetour();
		XamInputGetState.takeDownDetour();
		MatList.takeDownDetour();
		textList.takeDownDetour();
		r_setFrameFog.takeDownDetour();
		writePacket.takeDownDetour();
	}

	inline void EnableBounces() {
		*reinterpret_cast<int*>(0x820EB474) = 0x6060FFB0;// 0x60000000;
	}
	
	inline void ResetVars() {
		teamnow = false;
		thirdperson = false;
		preGamePatch();
	}

	inline void patchBytes() {
		*reinterpret_cast<int*>(0x8217601C) = 0x60000000; //userinfochanged
		*reinterpret_cast<int*>(0x82338880) = 0x60000000; //clientCleanName
		*reinterpret_cast<short*>(0x82309AA8) = *reinterpret_cast<short*>(0x82309A3C) = 0x4800; //Clantag Patch
		*reinterpret_cast<int*>(0x82309598) = 0x2F0B00FF; //Change 0x5E to FF
		*reinterpret_cast<int*>(0x820D4C98) = 0x60000000; //AimTarget Godmode Class - Prevent Kick
		*reinterpret_cast<int*>(0x820D4D18) = 0x60000000; //AimTarget Godmode Class - Prevent Kick
		*reinterpret_cast<int*>(0x820D5070) = 0x60000000; //AimTarget Godmode Class - Prevent Kick
		*reinterpret_cast<short*>(0x8218769C) = 0x4100;  //Bypass MOTD Feed
	}

	inline void fixSearches()
	{
		Cbuf_AddText(0, "ping_default_min 200;");
	}

	inline void iniTU24()
	{
		ResetVars();
		EnableBounces();
		preGamePatch();
		patchBytes();
		setupHooks();
		fixSearches();
	}
}
#endif // TU24_HOOKS_H
