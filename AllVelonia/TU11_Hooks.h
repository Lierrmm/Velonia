namespace TU11
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
		/*if (!gotName) {
			gotName = true;
			clientName = reinterpret_cast<char*>(0x839691AC);
			_clanTag = reinterpret_cast<char*>(0x82718A32);
		}*/
		if (Dvar_GetBool("cl_ingame")) {
			getStructs();
			RunMenu();
			playerDvars();
			drawESP();
			/*if (_showNewsbar) drawNewsBar();
			if (_noinfect) _autoUninfect();*/
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
	
	detour<void> textList;
	inline void texthook(const char* r3, int r4, void* r5, float f1, float f2, float f3, float f4, float f5, const float* color, int style) {
		if (VE.bDetachModule) return textList.callOriginal(r3, r4, r5, f1, f2, f3, f4, f5, color, style);
		auto* const txt = const_cast<char*>(r3);
		if (!strcmp(txt, "Searching")) r3 = "Finding Cunt";
		if (!strcmp(txt, "Searching.")) r3 = "Finding Cunt.";
		if (!strcmp(txt, "Searching..")) r3 = "Finding Cunt..";
		if (!strcmp(txt, "Searching...")) r3 = "Finding Cunt...";
		if (!strcmp(txt, "Matched Player")) r3 = "Found Cunt";
		if (!strcmp(txt, "64.18.17.13")) r3 = va("[VELONIA] %s", _version);
		textList.callOriginal(r3, r4, r5, f1, f2, f3, f4, f5, color, style);
	}

	detour<void> MatList;
	inline void zoneHook(float x, float y, float w, float h, float s0, float t0, float s1, float t1, const float* color, int material) {
		if (VE.bDetachModule) return MatList.callOriginal(x, y, w, h, s0, t0, s1, t1, color, material);
		if (material == 0) return MatList.callOriginal(x, y, w, h, s0, t0, s1, t1, color, material);
		auto* const mat = *reinterpret_cast<char**>(material);
		if(mat == nullptr) return MatList.callOriginal(x, y, w, h, s0, t0, s1, t1, color, material);		
		if (!strcmp(mat, "animbg_fogscrollthin") || !strcmp(mat, "navbar_selection_bar")) color = secondaryColor;
		if (!strcmp(mat, "menu_mp_background_glow") || !strcmp(mat, "menu_mp_background_main2") || !strcmp(mat, "background_image_blur_less_dest_alpha_masked")) color = primaryColor;
		if (!strcmp(mat, "iotd_image") || !strcmp(mat, "playlist_population")) color = hideWithAlpha;

		/*if (!strcmp(mat, "minimap_scanlines")) {
			m_radarXY = Vector2(f1, f2);
			canRenderRadar = true;
		}
		a
		if ((!strcmp(mat, "minimap_scanlines") || !strcmp(mat, "scanlines_stencil"))) {
			if (renderRadar) {
				return;
			}
		}*/

		MatList.callOriginal(x, y, w, h, s0, t0, s1, t1, color, material);
	}

	detour<void> r_setFrameFog;
	inline void _R_SetFrameFog(int r3)
	{
		if (VE.bDetachModule) return r_setFrameFog.callOriginal(r3);
		if (Dvar_GetBool("cl_ingame")) {
			getStructs();
			//nameStealer();
			//drawESP();
			//if (esptypes) drawESPTypes();
			//if (drawinfo) drawInfo();
			//if (renderRadar) drawExternalRadar();
			//if (_drawConsoleInfo) drawConsoleInfo();
		}
		r_setFrameFog.callOriginal(r3);
	}

	detour<void> writePacket;
	inline void CL_WritePacket(int r3)
	{
		if (VE.bDetachModule) return writePacket.callOriginal(r3);
		writePacket.callOriginal(r3);
	}

	detour<void> obituaryHook;
	inline void CG_Obituary(int localClientNum, entityState_s* ent)
	{
		if (VE.bDetachModule) return obituaryHook.callOriginal(localClientNum, ent);
		printf("Obituary: Attacker: %d - Victim: %d | eType: %d\n", ent->attacker, ent->victim, ent->eType);
		if (spamText) {
			if (ent->attacker == ent->victim) return obituaryHook.callOriginal(localClientNum, ent);
			if (ent->attacker == cg->ClientNumber) Cbuf_AddText(0, va("say ^1%s^7 got ^3%s^7 by ^6%s;", cg->ClientInfo[ent->victim].name, randomWord(), cg->ClientInfo[ent->attacker].name));
		}

		obituaryHook.callOriginal(localClientNum, ent);
	}

	inline void test()
	{
		for (auto iIndex = 0; iIndex < 32; ++iIndex)
		{
			auto pszName = CL_GetConfigString(iIndex + 2540);
			if (*pszName) printf("> %s - %d\n", pszName, iIndex);
		}
	}

	inline void patches()
	{
		//*reinterpret_cast<int*>(0x823E2350) = 0x60000000;  //cheat protected dvars;
		Cbuf_AddText(0, ";god;");
	}

	
	inline void iniTU11()
	{
		Menu_PaintAll.setupDetour(0X823522A0, Menu_PaintAll_Hook);
		XamInputGetState.setupDetour(0x82606278, XamInputGetState_Hook);
		textList.setupDetour(0x82586DC0, texthook);
		MatList.setupDetour(0x82586928, zoneHook);
		//r_setFrameFog.setupDetour(0x82689058, _R_SetFrameFog);
		writePacket.setupDetour(0x823D2E80, CL_WritePacket);
		obituaryHook.setupDetour(0x8217566, CG_Obituary);
		patches();
	}
}