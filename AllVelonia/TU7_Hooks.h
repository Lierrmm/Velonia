#ifndef TU7_HOOKS_H
#define TU7_HOOKS_H

namespace TU7
{
	inline void playerDvars() {
		Cbuf_AddText(0, va("cg_gun_x %i;", cg_gun_x));
		Cbuf_AddText(0, va("cg_gun_y %i;", cg_gun_y));
		Cbuf_AddText(0, va("cg_gun_z %i;", cg_gun_z));
		Cbuf_AddText(0, va("cg_fov %i;", cg_fov));
		Cbuf_AddText(0, va("cg_thirdpersonrange %i;", tpRange));
		Cbuf_AddText(0, va("cg_thirdpersonangle %i;", tpAngle));
		Cbuf_AddText(0, "unbind DPAD_UP;");
	}

	/*inline void test()
	{
		for (auto i = 0; i < sizeof(Bones)-1; i++)
			printf("> %s %X\n", Bones[i], SL_GetStringOfSize(0, Bones[i], 2, strlen(Bones[i])));
	}*/
	
	detour<void> Menu_PaintAll;
	inline void Menu_PaintAll_Hook(int r3, int r4) {
		if (VE.bDetachModule) return Menu_PaintAll.callOriginal(r3, r4);
		Menu_PaintAll.callOriginal(r3, r4);
		if (Dvar_GetBool("cl_ingame")) {
			getStructs();
			RunMenu();
			drawESP();
			playerDvars();
			//nameStealer();
			if (_showNewsbar) drawNewsBar();
			//if (esptypes) drawESPTypes();
			if (drawinfo) drawInfo();
			//if (renderRadar) drawExternalRadar();
			if (_drawConsoleInfo) drawConsoleInfo();
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
		textList.callOriginal(r3, r4, r5, f1, f2, f3, f4, f5, color, something);
	}

	
	detour<void> MatList;
	inline void zoneHook(float f1, float f2, float f3, float f4, float f5, int f6, int f7, float f8, float* color, int material) {
		if (VE.bDetachModule) return MatList.callOriginal(f1, f2, f3, f4, f5, f6, f7, f8, color, material);
		auto* const mat = *reinterpret_cast<char**>(material);

		if (!strcmp(mat, "menu_background_mp_tank") || !strcmp(mat, "menu_background_mp_tank_blurred")) color = primaryColor;
		if (!strcmp(mat, "animbg_fogscrollthin")) color = secondaryColor;
		
		/*if (!strcmp(mat, "minimap_scanlines")) {
			m_radarXY = Vector2(f1, f2);
			canRenderRadar = true;
		}

		if ((!strcmp(mat, "minimap_scanlines") || !strcmp(mat, "scanlines_stencil"))) {
			if (renderRadar) {
				return;
			}
		}*/

		MatList.callOriginal(f1, f2, f3, f4, f5, f6, f7, f8, color, material);
	}


	detour<void> writePacket;
	inline void CL_WritePacket(int r3) {
		if (VE.bDetachModule) return writePacket.callOriginal(r3);
		packetTimer++;
		if (Dvar_GetBool("cl_ingame"))
		{
			getStructs();
			auto* const cmd = ca->getCmd();
			auto* oldCmd = ca->getLastCmd();
			*oldCmd = *cmd;
			oldCmd->time -= 1;
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
							ca->viewAngle = newAngles;
							SHORT2ANGLE(oldCmd->viewAngles[1]);
						}
						else {
							/*if (Key_isDown(0, 0x12)) {
								ca->viewAngle = newAngles;
								SHORT2ANGLE(oldCmd->viewAngles[1]);
							}*/
						}
					}
					if (smoothAim) {
						silentaim = false; snapbot = false;
						if (!AimKey) {
							_SmoothAngle(newAngles, ca->viewAngle, 30);
						}
						else {
							/*if (Key_isDown(0, 0x12)) {
								_SmoothAngle(newAngles, ca->ViewAngles, 30);
							}*/
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
	char* (__cdecl* CL_GetConfigString)(int r1) = reinterpret_cast<char* (*)(int)>(0x821A4EC0);

	inline void test1()
	{
		int iIndex; // [sp+0h] [bp-C10h]@5
		char* pszName; // [sp+4h] [bp-C0Ch]@8
		char* v5;

		for (iIndex = 0; iIndex < 32; ++iIndex)
		{
			printf("> Trying\n");
			pszName = CL_GetConfigString(iIndex + 2196);
			printf("> Hit\n");
			if (*pszName) 
				if(strlen(pszName) > 0)
					printf("> %s - %d\n", pszName, iIndex);
			/*{
				if (!I_stricmp(item->parent->window.name, pszName))
					break;
			}*/
		}
		if (iIndex == 32) iIndex = -1;
		//v5 = va("cmd mr %i %i %s;", Dvar_GetInt("sv_serverId"), iIndex, "axis;");
		//printf("iIndex > %d\n", iIndex);
		//Cbuf_AddText(0, v5);
	}


	int(*__cdecl String_Parse)(const char** p, char* out, int len) = reinterpret_cast<int(*)(const char**, char*, int)>(0x822A8680);
	//822AACE8 Script_ConditionalResponseHandler
	void Script_ConditionalResponseHandler(int localClientNum, int dc, int item, const char** args, bool(__cdecl* shouldRespond)(const char*, const char*))
	{
		if (VE.bDetachModule) return writePacket.callOriginal(localClientNum, dc, item, args, shouldRespond);

		printf("> Begin\n");

		char command[1024];
		if(String_Parse(args, command, 1024))
		{
			printf("> command: %s\n", command);
		}
		
		printf("> End\n");

		writePacket.callOriginal(localClientNum, dc, item, args, shouldRespond);
	}

	inline void configstringhook(int index)
	{
		if (VE.bDetachModule || index == 0) return writePacket.callOriginal(index);
		printf("> Begin\n");
		printf("> index: %d\n", index);
		printf("> End\n");

		return writePacket.callOriginal(index);
	}

	inline void resetBuffs()
	{
		godmode = false;
		Cbuf_AddText(0, va("god %d;", godmode));
		noclip = false;
		Cbuf_AddText(0, va("noclip %d;", noclip));
	}
	
	inline void iniTU7()
	{
		Menu_PaintAll.setupDetour(0x822B2F38, Menu_PaintAll_Hook);
		MatList.setupDetour(0x82401410, zoneHook);
		XamInputGetState.setupDetour(0x82463714, XamInputGetState_Hook);
		resetBuffs();
		//writePacket.setupDetour(0x821B0F30, CL_WritePacket);
		//writePacket.setupDetour(0x821A4EC0, configstringhook);
		//test1();
	}
	
}
#endif // TU7_HOOKS_H
