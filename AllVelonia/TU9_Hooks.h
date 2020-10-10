namespace TU9
{
	void playerDvars() {
		Cbuf_AddText(0, va(";cg_gun_x %i;", cg_gun_x));
		Cbuf_AddText(0, va(";cg_gun_y %i;", cg_gun_y));
		Cbuf_AddText(0, va(";cg_gun_z %i;", cg_gun_z));
		Cbuf_AddText(0, va(";cg_fov %i;", cg_fov));
		Cbuf_AddText(0, va(";cg_thirdpersonrange %i;", tpRange));
		Cbuf_AddText(0, va(";cg_thirdpersonangle %i;", tpAngle));
	}

	bool gotName = false;
	detour<void> Menu_PaintAll;
	void Menu_PaintAll_Hook(int r3)
	{
		if (VE.bDetachModule) return Menu_PaintAll.callOriginal(r3);
		Menu_PaintAll.callOriginal(r3);
		pgStructs();
		if(!gotName)
		{
			gotName = true;
			clientName = reinterpret_cast<char*>(0x838BA824);
			_clanTag = reinterpret_cast<char*>(0x8268FADB);
		}
		if(Dvar_GetBool("cl_ingame"))
		{
			getStructs(); RunMenu();
			playerDvars();
			nameStealer();
			drawESP();
			if (_showNewsbar) drawNewsBar();
			if (esptypes) drawESPTypes();
			if (drawinfo) drawInfo();
			if (_drawConsoleInfo) drawConsoleInfo();
			if (renderRadar) drawExternalRadar();
		}
	}

	detour<DWORD> XamInputGetState;
	DWORD XamInputGetState_Hook(DWORD r3, DWORD r4, PXINPUT_STATE r5) {
		DWORD XInput = XamInputGetState.callOriginal(r3, r4, r5);
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
	void texthook(const char* r3, int r4, void* r5, float f1, float f2, float f3, float f4, float f5, const float* color, int something) {
		if (VE.bDetachModule) return textList.callOriginal(r3, r4, r5, f1, f2, f3, f4, f5, color, something);
		auto txt = const_cast<char*>(r3);
		if (!strcmp(txt, "Searching")) r3 = "Finding Cunt";
		if (!strcmp(txt, "Searching.")) r3 = "Finding Cunt.";
		if (!strcmp(txt, "Searching..")) r3 = "Finding Cunt..";
		if (!strcmp(txt, "Searching...")) r3 = "Finding Cunt...";
		if (!strcmp(txt, "Matched Player")) r3 = "Found Cunt";
		if (!strcmp(txt, "1.4.163842")) r3 = va("[VELONIA] %s", _version);
		if (!strcmp(txt, "Online interactions not rated by the ESRB.")) r3 = "";
		textList.callOriginal(r3, r4, r5, f1, f2, f3, f4, f5, color, something);
	}

	detour<void> MatList;
	void zoneHook(float f1, float f2, float f3, float f4, float f5, int f6, int f7, float f8, float* color, int material) {
		if (VE.bDetachModule) return MatList.callOriginal(f1, f2, f3, f4, f5, f6, f7, f8, color, material);
		auto mat = *reinterpret_cast<char**>(material);
		if (!strcmp(mat, "mw2_main_cloud_overlay") || !strcmp(mat, "mw2_main_cloud_overlay_write_dest_alpha") || !strcmp(mat, "mw2_main_cloud_overlay_dest_alpha_masked") || !strcmp(mat, "mw2_popup_bg_fogscroll") || !strcmp(mat, "mockup_popup_bg_stencilfill") || !strcmp(mat, "mw2_popup_bg_fogstencil"))
			color = wallBlue;
		if (!strcmp(mat, "mockup_bg_glow") || !strcmp(mat, "mw2_main_background") || !strcmp(mat, "mw2_main_mp_image"))
			color = darkPink;
		if (!strcmp(mat, "specialty_new") || !strcmp(mat, "mw2_main_mp_image") || !strcmp(mat, "logo_cod2"))
			color = hideWithAlpha;

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

	detour<void> writePacket;
	void CL_WritePacket(int r3) {
		packetTimer++;
		if (Dvar_GetBool("cl_ingame"))
		{
			getStructs();
			auto currentCmd = ca->getCmd();
			auto oldCmd = ca->getLastCmd();
			auto cmd = ca->getCmd(ca->CurrentCmdNumber);
			*oldCmd = *currentCmd;
			oldCmd->serverTime -= 1;
			if (aimbot) {
				auto closestClient = getClosestClient(cg->cNum);
				if (closestClient != -1)
				{
					auto head = GetTagPos(closestClient, Bones[targetBone]);
					auto newAngles = VectorToAngles(head - GetPlayerViewOrigin()) - ca->baseAngle;
					if (silentaim) {
						snapbot = false;
						AimSilent(oldCmd, newAngles);
					}
					if (snapbot) {
						silentaim = false;
						if (!AimKey) {
							ca->viewAngle = newAngles;
							SHORT2ANGLE(oldCmd->ViewAngles[1]);
						}
						else {
							if (Key_isDown(0, 0x12)) {
								ca->viewAngle = newAngles;
								SHORT2ANGLE(oldCmd->ViewAngles[1]);
							}
						}
					}
					if (smoothAim) {
						silentaim = false; snapbot = false;
						if (!AimKey) {
							_SmoothAngle(newAngles, ca->viewAngle, 30);
						}
						else {
							if (Key_isDown(0, 0x12)) {
								_SmoothAngle(newAngles, ca->viewAngle, 30);
							}
						}
					}
					if (nospread) noSpread(oldCmd);
					if (autoshoot) {
						cmd->buttons &= ~1;
						oldCmd->buttons |= 1;
					}
				}
				if (_antispin) {
					static float spin;
					spin += 5.f;
					if (spin > 70.f) spin = -70.f;
					cmd->ViewAngles[0] = ANGLE2SHORT(spin - ca->baseAngle.x);
				}
				if (_antiflip) {
					static bool flip;
					flip ^= true;
					cmd->ViewAngles[0] = ANGLE2SHORT((flip ? 70 : -70) - ca->baseAngle.x);
				}
				if (_antiy) {
					cmd->ViewAngles[1] = ANGLE2SHORT(rand() % 2 ? (69 - 135) : (69 - 225.0f));
				}
				if (_antix) {
					cmd->ViewAngles[0] = ANGLE2SHORT(70 - ca->baseAngle.x);
				}
				if (_antishield) {
					cmd->ViewAngles[0] = ANGLE2SHORTFLOAT(FloatMinMax(-69.99f, 69.99f) - ca->baseAngle.x);
				}
			}
			if (fakelag && cg->ClientInfo[cg->cNum].Valid & 1 && Dvar_GetBool("cl_ingame")) {
				if (oldCmd->buttons != 0x80800 && oldCmd->buttons != 0x1) {
					_mFakeLag = true;
				}
				else {
					_mFakeLag = false;
				}
			}
		}
		if (fakelag && cg->ClientInfo[cg->cNum].Valid & 1 && Dvar_GetBool("cl_ingame") && _mFakeLag) {
			if (packetTimer >= 15) {
				packetTimer = 0;
				writePacket.callOriginal(r3);
			}
		}
		else {
			writePacket.callOriginal(r3);
		}
	}

	void setupHooks() {
		Menu_PaintAll.setupDetour(0x82285E98, Menu_PaintAll_Hook);
		textList.setupDetour(0x82350278, texthook);
		MatList.setupDetour(0x8234F9B8, zoneHook);
		writePacket.setupDetour(0x821402E0, CL_WritePacket);
		XamInputGetState.setupDetour(0x823B64A4, XamInputGetState_Hook);
	}
	
	void fixSearches()
	{
		Cbuf_AddText(0, "ping_default_min 250;");
	}

	//Patch RCE
	detour<int> _svECC;
	detour<int> _CLPSM;
	detour<int> _svCRS;
	detour<long> _AAPL;
	int MsgReadBitsCompressCheckSV(const char* from, char* to, int size)
	{
		if (VE.bDetachModule) return _svECC.callOriginal(from, to, size);
		static char buffer[0x8000];

		if (size > 0x800) return 0;
		size = MSG_ReadBitsCompress(from, buffer, size);

		if (size > 0x800) return 0;
		std::memcpy(to, buffer, size);

		return size;
	}
	
	int MsgReadBitsCompressCheckCL(const char* from, char* to, int size)
	{
		if (VE.bDetachModule) return _CLPSM.callOriginal(from, to, size);
		
		static char buffer[0x100000];

		if (size > 0x20000) return 0;
		size = MSG_ReadBitsCompress(from, buffer, size);

		if (size > 0x20000) return 0;
		std::memcpy(to, buffer, size);

		return size;
	}

	int SVCanReplaceServerCommand(int client, const char* cmd)
	{
		if (VE.bDetachModule) return _svCRS.callOriginal(client, cmd);
		// This is a fix copied from V2. As I don't have time to investigate, let's simply trust them
		return -1;
	}

	long AtolAdjustPlayerLimit(const char* string)
	{
		if (VE.bDetachModule) return _AAPL.callOriginal(string);
		return min(atol(string), 18l);
	}
	
	void patchBytes()
	{
		//*reinterpret_cast<int*>(0x821442B0) = 0x4E800020; //CL_HandleRelayPacket
		//_svECC.setupDetour(0x822537D8, MsgReadBitsCompressCheckSV); //SV_ExecuteClientCommands
		//_CLPSM.setupDetour(0x8214B70C, MsgReadBitsCompressCheckCL); // CL_ParseServerMessage
		//_svCRS.setupDetour(0x82257848, SVCanReplaceServerCommand); // SV_CanReplaceServerCommand
		//_AAPL.callOriginal(0x82161068, AtolAdjustPlayerLimit); // PartyHost_HandleJoinPartyRequest
		*reinterpret_cast<short*>(0x82273B98) = *reinterpret_cast<short*>(0x82273AE0) = 0x4800; //Clantag Patch
	}

	void iniTU9() {
		preGamePatch();
		patchBytes();
		setupHooks();
		fixSearches();
	}
}