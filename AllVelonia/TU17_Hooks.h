namespace TU17
{
	void playerDvars() {
		Cbuf_AddText(0, va(";cg_gun_x %i;", cg_gun_x));
		Cbuf_AddText(0, va(";cg_gun_y %i;", cg_gun_y));
		Cbuf_AddText(0, va(";cg_gun_z %i;", cg_gun_z));
		Cbuf_AddText(0, va(";cg_fov %i;", cg_fov));
	}

	bool gotName = false;
	detour<void> Menu_PaintAll;
	void Menu_PaintAll_Hook(int r3, int r4) {
		if (VE.bDetachModule) return Menu_PaintAll.callOriginal(r3, r4);
		Menu_PaintAll.callOriginal(r3, r4);
		pgStructs();
		if (Dvar_GetBool("cl_ingame")) {
			getStructs(); RunMenu();
			playerDvars();
			drawESP();
			if (drawinfo) drawInfo();
			if (_showNewsbar) drawNewsBar();
			if (renderRadar) drawExternalRadar();
		}
		else CE.menuOpen = false;
	}

	bool canshoot = false;
	detour<DWORD> XamInputGetState;
	DWORD XamInputGetState_Hook(DWORD r3, DWORD r4, PXINPUT_STATE r5) {
		auto XInput = XamInputGetState.callOriginal(r3, r4, r5);
		if (VE.bDetachModule) return XInput;
		if (r3 != 0 || XInput != 0) return XInput;
		if (CE.menuOpen && Dvar_GetBool("cl_ingame")) {
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
	void texthook(const char* r3, int r4, void* r5, float f1, float f2, float f3, float f4, float f5, const float* color, int something) {
		if (VE.bDetachModule) return textList.callOriginal(r3, r4, r5, f1, f2, f3, f4, f5, color, something);
		auto* const txt = const_cast<char*>(r3);
		if (!strcmp(txt, "Matched Player")) r3 = "Found Cunt";
		if (!strcmp(txt, "3.15.146")) r3 = va("[VELONIA] %s", "BETA 0.0.1");
		textList.callOriginal(r3, r4, r5, f1, f2, f3, f4, f5, color, something);
	}
	
	detour<void> matList;
	void matHook(float x, float y, float w, float h, float s0, float t0, float s1, float t1, const float* color, void* material)
	{
		if(VE.bDetachModule) return matList.callOriginal(x, y, w, h, s0, t0, s1, t1, color, material);
		const auto mat = *static_cast<char**>(material);
		
		if (!strcmp(mat, "minimap_tickertape_mp")) {
			m_radarXY = Vector2(x, y);
			canRenderRadar = true;
		}

		/*if ((!strcmp(mat, "minimap_tickertape_mp") || !strcmp(mat, "scanlines_stencil"))) {
			if (renderRadar) {
				return;
			}
		}*/
		
		matList.callOriginal(x, y, w, h, s0, t0, s1, t1, color, material);
	}

	detour<void> writePacket;
	void CL_WritePacket(int r3) {
		if (VE.bDetachModule) return writePacket.callOriginal(r3);
		packetTimer++;
		if (Dvar_GetBool("cl_ingame"))
		{
			getStructs();
			auto* ca = ClientActive;
			auto* const currentCmd = ca->getCmd();
			auto* oldCmd = ca->getLastCmd();
			auto* cmd = ca->getCmd(ca->CurrentCmdNumber);
			*oldCmd = *currentCmd;
			oldCmd->time -= 1;
			if (aimbot) {
				const auto closestClient = getClosestClient(cg->ClientNumber);
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
							ca->viewAngle = newAngles;
							SHORT2ANGLE(oldCmd->viewAngles[1]);
						}
						else {
							if (Key_isDown(0, 0x12)) {
								ca->viewAngle = newAngles;
								SHORT2ANGLE(oldCmd->viewAngles[1]);
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
						canshoot = true;
					}
				}
				if (_antispin) {
					static float spin;
					spin += 5.f;
					if (spin > 70.f) spin = -70.f;
					cmd->viewAngles[0] = ANGLE2SHORT(spin - ca->baseAngle.x);
				}
				if (_antiflip) {
					static bool flip;
					flip ^= true;
					cmd->viewAngles[0] = ANGLE2SHORT((flip ? 70 : -70) - ca->baseAngle.x);
				}
				if (_antiy) {
					cmd->viewAngles[1] = ANGLE2SHORT(rand() % 2 ? (69 - 135) : (69 - 225.0f));
				}
				if (_antix) {
					cmd->viewAngles[0] = ANGLE2SHORT(70 - ca->baseAngle.x);
				}
				if (_antishield) {
					cmd->viewAngles[0] = ANGLE2SHORTFLOAT(FloatMinMax(-69.99f, 69.99f) - ca->baseAngle.x);
				}
			}
			if (fakelag && Centity_s[cg->ClientNumber].Alive & 1 && Dvar_GetBool("cl_ingame")) {
				if (oldCmd->buttons != 0x80800 && oldCmd->buttons != 0x1) {
					_mFakeLag = true;
				}
				else {
					_mFakeLag = false;
				}
			}
		}
		if (fakelag && Centity_s[cg->ClientNumber].Alive & 1 && Dvar_GetBool("cl_ingame") && _mFakeLag) {
			if (packetTimer >= 15) {
				packetTimer = 0;
				writePacket.callOriginal(r3);
			}
		}
		else {
			writePacket.callOriginal(r3);
		}
	}
	
	void patchBytes()
	{
		*reinterpret_cast<int*>(0x822E0CE0) = 0x60000000;
		*reinterpret_cast<int*>(0x8256F9E8) = 0x60000000;
		*reinterpret_cast<short*>(0x8253EA58) = *reinterpret_cast<short*>(0x8253E9E4) = *reinterpret_cast<int*>(0x82546090) = 0x4800; //Clantag Patch
		//82BB6896 clantag address
	}

	inline void iniTU17()
	{
		Menu_PaintAll.setupDetour(0x8253E140, Menu_PaintAll_Hook);
		XamInputGetState.setupDetour(0x828103EC, XamInputGetState_Hook);
		textList.setupDetour(0x8266CEB8, texthook);
		matList.setupDetour(0x8266AF28, matHook);
		writePacket.setupDetour(0x822D68C0, CL_WritePacket);
		patchBytes();
	}
}