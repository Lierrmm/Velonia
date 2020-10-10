namespace TU7
{
	struct _CE {
		int Scroller;
		int curScroll;
		int maxScroll;
		int curMenu;
		int maxWait;
		bool menuOpen;
		float centerX;
		float centerY;
		float menuW;
	};

	_CE CE;

	void addOption(int i, const char* text, float fontSize = .57) {
		if (i == CE.curScroll) drawShader(960, ((i + 1) * 28 + 24), 278, 20.0f, mainColorAlpha, "white");
		drawText(text, CE.centerX + 7, ((i + 1) * 28 + 44), normalFont, fontSize, colorWhite);
		CE.maxScroll = i;
	}

	void addBool(int i, const char* text, bool toggle) {
		drawShaderOutlined(1225, ((i + 1) * 28 + 29), 10, 10, toggle ? MenuSelectedColor : colorBlackTrans, colorWhite, 1);
		addOption(i, text);
		CE.maxScroll = i;
	}

	void addiSlider(int i, const char* text, int var, int min, int max) {
		const int X = ((var - min) * 85) / (max - min);
		addOption(i, text);
		CG_DrawRotatedPicPhysical(0x8274F580, 1114 + 1, 29 + ((i + 1) * 28) + 2, X, 8, 0, Smoke, Material_RegisterHandle("white", 0));
		drawBoxWithOutline(1114 + 1, 29 + ((i + 1) * 28) + 1, 85, 8, MenuSelectedColor);
		drawText(va("%i", var), 1236 - (R_TextWidth(va("%i", var), 0x7FFFFFFF, R_RegisterFont("fonts/normalfont", 0)) * .57), ((i + 1) * 28) + 29 + 15, "fonts/normalfont", .57, white);
		CE.maxScroll = i;
	}

	void drawMenuOption(int i, char* option) {
		addOption(i, option);
		drawShader(1225, ((i + 1) * 28 + 28), 15, 15, white, "ui_scrollbar_arrow_right");
		CE.maxScroll = i;
	}

	void addiSliderOption(int i, const char* text, int var, int min, int max, bool selected)
	{
		const int X = ((var - min) * 105) / (max - min);
		drawShaderOutlined(1225, ((i + 1) * 28 + 29), 10, 10, selected ? MenuSelectedColor : colorBlackTrans, colorWhite, 1);
		addOption(i, text);
		CG_DrawRotatedPicPhysical(0x8274F580, 1115, 29 + ((i + 1) * 28) + 2, X, 8, 0, Smoke, Material_RegisterHandle("white", 0));
		drawBoxWithOutline(1115, 29 + ((i + 1) * 28) + 1, 105, 8, MenuSelectedColor);
		CE.maxScroll = i;
	}

	void DrawBoneOption(int i, char* option, int bone) {
		addOption(i, option);
		auto bonePicker = va("\x0016 %s \x0017", Bones[bone]);
		if (bone == 0) bonePicker = va("%s \x0017", Bones[bone]);
		if (bone == 19) bonePicker = va("\x0016 %s", Bones[bone]);
		drawText(bonePicker, 1236 - (R_TextWidth(bonePicker, 0x7FFFFFFF, R_RegisterFont("fonts/normalfont", 0)) * .57), ((i + 1) * 28 + 44), "fonts/normalfont", .57, white);
	}

	int calcMenuSize() {
		int originalSize;
		originalSize = ((CE.maxScroll + 1) * 28 + 44);
		return originalSize;
	}

	void MenuStructure() {
		drawShader(958, 28, 280, 2, MenuSelectedColor, "white"); //TOP2
		drawShader(960, 30, 278, calcMenuSize() - 8, black, "white"); //BACKGROUND
		drawShader(958, 28, 2, 4 + calcMenuSize() - 8, MenuSelectedColor, "white"); //LEFT
		drawShader(1238, 28, 2, 4 + calcMenuSize() - 8, MenuSelectedColor, "white"); //RIGHT
		drawShader(960, 48, 278, 2, MenuSelectedColor, "white"); //TOP
		drawShader(958, 2 + calcMenuSize(), 282, 2, MenuSelectedColor, "white"); //BOTTOM
		drawShader(958, 22 + calcMenuSize(), 282, 2, MenuSelectedColor, "white"); //BOTTOM2
		drawText("Velonia", 965, 48, normalFont, .5, white);
		drawRightText("TU7", 1235, 48, normalFont, .5, white);
		drawText(getCurMenu(CE.curMenu), 965, 21 + calcMenuSize(), normalFont, .5, white);
		drawRightText(va("[%d/%d]", (CE.curScroll + 1), (CE.maxScroll + 1)), 1235, 21 + calcMenuSize(), normalFont, .5, white);
		switch (CE.curMenu) {
		case MAIN:
			addOption(0, "Self Menu");
			addOption(1, "ESP Menu");
			addOption(2, "Aimbot Menu");
			addOption(3, "Dvar Menu");
			addOption(4, "Misc Menu");
			addOption(5, "Player Menu");
			addOption(6, "End Game");
			addOption(7, "Menu Settings");
			addOption(8, "^:DEBUG");
			break;
		case SELF:
			addiSlider(0, "Change Team", customTeam, 1, 3);
			addiSlider(1, "Change Class", customClass, 1, 10);
			addBool(2, "God Mode", godmode);
			addBool(3, "No Clip", noclip);
			addBool(4, "Unlimited Radar", radar);
			addBool(5, "No Recoil", recoil);
			addBool(6, "No Sway", sway);
			addBool(7, "No Flinch", noflinch);
			addBool(8, "No Flash", flashing);
			addOption(9, "Disconnect");
			break;
		case ESP:
			drawMenuOption(0, "ESP");
			addBool(1, "Barrel ESP", drawBarrelESP);
			addBool(2, "ESP Types", esptypes);
			addBool(3, "Pointers", drawPointers);
			addiSliderOption(4, "SnapLines", snaplinepos, 10, 700, snaplines);
			addBool(5, "ESP Names", espname);
			addBool(6, "ESP Distance", espdist);
			addBool(7, "External Radar", renderRadar);
			break;
		case AIMBOT:
			addBool(0, "Aimbot", aimbot);
			DrawBoneOption(1, "Target Bone", targetBone);
			addBool(2, "Snap", snapbot);
			addBool(3, "Smooth Snap", smoothAim);
			addBool(4, "AimKey", AimKey);
			addBool(5, "Silent", silentaim);
			addBool(6, "Auto Wall", autowall);
			addBool(7, "No Spread", nospread);
			addBool(8, "Auto Shoot", autoshoot);
			drawMenuOption(9, "Anti Aim");
			addBool(10, "Fake Lag", fakelag);
			break;
		case DVARS:
			addBool(0, "Third Person", thirdperson);
			addiSlider(1, "Third Person Range", tpRange, 0, 359);
			addiSlider(2, "Third Person Range", tpAngle, 0, 359);
			addiSlider(3, "Color Map", colorMap, 0, 3);
			addBool(4, "Chrome Vision", toggleFB);
			addiSlider(5, "Field Of View", cg_fov, 65, 120);
			drawMenuOption(6, "Gun Position");
			addBool(7, "Debug Mode", debugmode);
			break;
		case MISC:
			addBool(0, "Name Stealer", stealName);
			addBool(1, "Draw Info", drawinfo);
			break;
		case ANTIAIM:
			addBool(0, "Spin", _antispin);
			addBool(1, "Flip", _antiflip);
			addBool(2, "Jitter", _antiy);
			addBool(3, "Down", _antix);
			addBool(4, "Shield", _antishield);
			break;
		case GUNPOS:
			addiSlider(0, "Gun X", cg_gun_x, -2, 2);
			addiSlider(1, "Gun Y", cg_gun_y, -2, 2);
			addiSlider(2, "Gun Z", cg_gun_z, -2, 2);
			break;
		case MENUSETTINGS:
			drawMenuOption(0, "Theme Settings");
			addBool(1, "Draw Console Info", _drawConsoleInfo);
			addBool(2, "News Bar", _showNewsbar);
			break;
		case ESPTYPE:
			addBool(0, "2D Box", esp2D);
			addBool(1, "3D Box", esp3D);
			addBool(2, "3D Triangle", espTri);
			break;
		case THEME:
			addOption(0, "Default");
			addOption(1, "Red");
			addOption(2, "Yellow");
			addOption(3, "Green");
			addOption(4, "Orange");
			addOption(5, "Pink");
			addOption(6, "White");
			addOption(7, "Purple");
			addOption(8, "Grey");
			break;
		case PLAYERS:
			auto p = 0;
			for (auto i = 0; i < 18; i++) {
				if (cg->ClientInfo[i].mValid & 1) {
					addOption(p, va("[%s] %s - %s", checkLocalClient(i) ? "^3YOU^7" : checkFFAMode() ? "^1E^7" : notTeam(i) ? "^1E^7" : "^2F^7", cg->ClientInfo[i].szPlayerName, getIpAsString(i)), .46);
					p++;
				}
			}
			break;
		}
	}

	void SelectMonitor() {
		switch (CE.curMenu) {
		case MAIN:
			switch (CE.curScroll) {
			case 0: CE.curMenu = SELF; CE.curScroll = 0; break;
			case 1: CE.curMenu = ESP; CE.curScroll = 0; break;
			case 2: CE.curMenu = AIMBOT; CE.curScroll = 0; break;
			case 3: CE.curMenu = DVARS; CE.curScroll = 0; break;
			case 4: CE.curMenu = MISC; CE.curScroll = 0; break;
			case 5: CE.curMenu = PLAYERS; CE.curScroll = 0; break;
			case 6: endgame(); break;
			case 7: CE.curMenu = MENUSETTINGS; CE.curScroll = 0; break;
			case 8: addBots(); break;
			}
			break;
		case SELF:
			switch (CE.curScroll) {
			case 0: togteam(); break;
			case 1: changeClass(); break;
			case 2: godMode(); break;
			case 3: noClip(); break;
			//case 4: giveRadar(); break;
			//case 5: Recoil(); break;
			//case 6: weaponSway(); break;
			//case 7: noFlinch(); break;
			//case 8: stopFlash(); break;
			case 9: disconnect(); break;
			}
			break;
		case ESP:
			switch (CE.curScroll) {
			case 0: CE.curMenu = ESPTYPE; CE.curScroll = 0; break;
			case 1: drawBarrelESP = !drawBarrelESP; break;
			case 2: esptypes = !esptypes; break;
			case 3: drawPointers = !drawPointers; break;
			case 4: snaplines = !snaplines; break;
			case 5: espname = !espname; break;
			case 6: espdist = !espdist; break;
			case 7: renderRadar = !renderRadar; /*RadarPatch();	*/ break;
			}
			break;
		case AIMBOT:
			switch (CE.curScroll) {
			case 0: aimbot = !aimbot; break;
			case 2: snapbot = !snapbot; if (snapbot) autowall = false; break;
			case 3: smoothAim = !smoothAim; if (smoothAim) autowall = false; break;
			case 4: AimKey = !AimKey; break;
			case 5: silentaim = !silentaim; break;
			case 6: autowall = !autowall; if (autowall) snapbot = false, AimKey = false; silentaim = true; break;
			case 7: nospread = !nospread; break;
			case 8: autoshoot = !autoshoot; break;
			case 9: CE.curMenu = ANTIAIM; CE.curScroll = 0; break;
			case 10: fakelag = !fakelag; break;
			}
			break;
		case DVARS:
			switch (CE.curScroll) {
			case 0: thirdPerson(); break;
			case 1: break; case 2: break;
			case 3: Cbuf_AddText(0, va("r_colorMap %d;", colorMap)); break;
			case 4: toggleChrome(); break;
			case 6: CE.curMenu = GUNPOS; CE.curScroll = 0; break;
			case 7: toggleDebugMode(); break;
			}
			break;
		case MISC:
			switch (CE.curScroll) {
			case 0: stealNames(); break;
			case 1: drawinfo = !drawinfo; break;
			}
			break;
		case THEME:
			switch (CE.curScroll) {
			case 0: updateColorInfo(mainColor); break;
			case 1: updateColorInfo(RedMenu); break;
			case 2: updateColorInfo(YellowMenu); break;
			case 3: updateColorInfo(GreenMenu); break;
			case 4: updateColorInfo(OrangeMenu); break;
			case 5: updateColorInfo(PinkMenu); break;
			case 6: updateColorInfo(WhiteMenu); break;
			case 7: updateColorInfo(PurpleMenu); break;
			case 8: updateColorInfo(GreyMenu); break;
			}
			break;
		case ANTIAIM:
			switch (CE.curScroll) {
			case 0:
				if (!aimbot) aimbot = true;
				_antispin = !_antispin;
				_antiflip = false; _antix = false; _antiy = false; _antishield = false;
				break;
			case 1:
				if (!aimbot) aimbot = true;
				_antiflip = !_antiflip;
				_antispin = false; _antix = false; _antiy = false; _antishield = false;
				break;
			case 2:
				if (!aimbot) aimbot = true;
				_antiy = !_antiy;
				_antispin = false; _antix = false; _antiflip = false; _antishield = false;
				break;
			case 3:
				if (!aimbot) aimbot = true;
				_antix = !_antix;
				_antispin = false; _antiy = false; _antiflip = false; _antishield = false;
				break;
			case 4:
				if (!aimbot) aimbot = true;
				_antishield = !_antishield;
				_antispin = false; _antiy = false; _antiflip = false; _antix = false;
				break;
			}
			break;
		case GUNPOS: break;
		case MENUSETTINGS:
			switch (CE.curScroll) {
			case 0: CE.curMenu = THEME; CE.curScroll = 0; break;
			case 1: _drawConsoleInfo = !_drawConsoleInfo; break;
			case 2: newsBar(); break;
			}
			break;
		case ESPTYPE:
			switch (CE.curScroll) {
			case 0:
				esp2D = !esp2D;
				esp3D = false; espTri = false;
				break;
			case 1:
				esp3D = !esp3D;
				esp2D = false; espTri = false;
				break;
			case 2:
				espTri = !espTri;
				esp3D = false; esp2D = false;
				break;
			}
			break;
		case PLAYERS:
			break;
		}
	}

	void GoBack() {
		switch (CE.curMenu) {
		case MAIN: CE.menuOpen = false; break;
		case SELF: CE.curMenu = MAIN; CE.curScroll = 0; break;
		case ESP: CE.curMenu = MAIN; CE.curScroll = 0; break;
		case AIMBOT: CE.curMenu = MAIN; CE.curScroll = 0; break;
		case DVARS: CE.curMenu = MAIN; CE.curScroll = 0; break;
		case MENUSETTINGS: CE.curMenu = MAIN; CE.curScroll = 0; break;
		case MISC: CE.curMenu = MAIN; CE.curScroll = 0; break;
		case PLAYERS: CE.curMenu = MAIN; CE.curScroll = 0; break;
		case ANTIAIM: CE.curMenu = AIMBOT; CE.curScroll = 0; break;
		case THEME: CE.curMenu = MENUSETTINGS; CE.curScroll = 0; break;
		case GUNPOS: CE.curMenu = DVARS; CE.curScroll = 0; break;
		case ESPTYPE: CE.curMenu = ESP; CE.curScroll = 0; break;
		}
	}

	void IntChanger(int way)
	{
		switch (CE.curMenu)
		{
		case SELF:
			switch (CE.curScroll) {
			case 0:
				switch (way) {
				case 0:
					customTeam--;
					if (customTeam < 1) customTeam = 1;
					break;
				case 1:
					customTeam++;
					if (customTeam > 3) customTeam = 3;
					break;
				}
				break;
			case 1:
				switch (way)
				{
				case 0:
					customClass--;
					if (customClass < 1) customClass = 1;
					break;
				case 1:
					customClass++;
					if (customClass > 10) customClass = 10;
					break;
				}
				break;
			}
			break;
		case ESP:
			switch (CE.curScroll) {
			case 4:
				switch (way) {
				case 0:
					snaplinepos -= 30;
					if (snaplinepos < 10) snaplinepos = 10;
					break;
				case 1:
					snaplinepos += 30;
					if (snaplinepos > 700) snaplinepos = 700;
					break;
				}
				break;
			}
			break;
		case DVARS:
			switch (CE.curScroll)
			{
			case 3:
				switch (way)
				{
				case 0:
					colorMap--;
					if (colorMap < 0)
						colorMap = 0;
					break;
				case 1:
					colorMap++;
					if (colorMap > 3)
						colorMap = 3;
					break;
				}
				break;
			case 5:
				switch (way)
				{
				case 0:
					cg_fov--;
					if (cg_fov < 65)
						cg_fov = 65;
					break;
				case 1:
					cg_fov++;
					if (cg_fov > 120)
						cg_fov = 120;
					break;
				}
				break;
			case 1:
				switch (way)
				{
				case 0:
					tpRange -= 15;
					if (tpRange < 0)
						tpRange = 0;
					break;
				case 1:
					tpRange += 15;
					if (tpRange > 360)
						tpRange = 360;
					break;
				}
				break;
			case 2:
				switch (way)
				{
				case 0:
					tpAngle -= 15;
					if (tpAngle < 0)
						tpAngle = 0;
					break;
				case 1:
					tpAngle += 15;
					if (tpAngle > 360)
						tpAngle = 360;
					break;
				}
				break;
			}
			break;
		case GUNPOS:
			switch (CE.curScroll)
			{
			case 0:
				switch (way)
				{
				case 0:
					cg_gun_x--;
					if (cg_gun_x < -2) cg_gun_x = -2;
					break;
				case 1:
					cg_gun_x++;
					if (cg_gun_x > 2) cg_gun_x = 2;
					break;
				}
				break;
			case 1:
				switch (way)
				{
				case 0:
					cg_gun_y--;
					if (cg_gun_y < -2) cg_gun_y = -2;
					break;
				case 1:
					cg_gun_y++;
					if (cg_gun_y > 2) cg_gun_y = 2;
					break;
				}
				break;
			case 2:
				switch (way)
				{
				case 0:
					cg_gun_z--;
					if (cg_gun_z < -2) cg_gun_z = -2;
					break;
				case 1:
					cg_gun_z++;
					if (cg_gun_z > 2) cg_gun_z = 2;
					break;
				}
				break;
			}
			break;
		}
	}

	void BoneSelector(int dir) {
		if (CE.curMenu == AIMBOT) {
			if (CE.curScroll == 1) {
				switch (dir) {
				case 0:
					targetBone--;
					if (targetBone < 0) targetBone = 0;
					break;
				case 1:
					targetBone++;
					if (targetBone > 18) targetBone = 18;
					break;
				}
			}
		}
	}

	XINPUT_STATE Input;
	void ButtonMonitor() {
		ZeroMemory(&Input, sizeof(XINPUT_STATE));
		XInputGetState(0, &Input);
		CE.maxWait++;
		if (CE.maxWait > 10) {
			if (!CE.menuOpen) {
				if (XINPUT_GAMEPAD_LEFT_TRIGGER && Input.Gamepad.wButtons & (XINPUT_GAMEPAD_DPAD_UP)) {
					CE.menuOpen = true;
					CE.curScroll = 0;
					CE.curMenu = MAIN;
					CE.maxWait = 0;
				}
			}
			else {
				if (XINPUT_GAMEPAD_LEFT_TRIGGER && Input.Gamepad.wButtons & (XINPUT_GAMEPAD_DPAD_UP)) {
					CE.menuOpen = false; CE.maxWait = 0;
				}
				if (Input.Gamepad.wButtons == (XINPUT_GAMEPAD_DPAD_UP) && CE.menuOpen) {
					CE.curScroll--;
					if (CE.curScroll < 0) CE.curScroll = CE.maxScroll;
					CE.maxWait = 0;
				}
				if (Input.Gamepad.wButtons == (XINPUT_GAMEPAD_DPAD_DOWN) && CE.menuOpen) {
					CE.curScroll++;
					if (CE.curScroll > CE.maxScroll) CE.curScroll = 0;
					CE.maxWait = 0;
				}
				if (Input.Gamepad.wButtons == (XINPUT_GAMEPAD_X) && CE.menuOpen) {
					SelectMonitor(); CE.maxWait = 0;
				}
				if (Input.Gamepad.wButtons == (XINPUT_GAMEPAD_B) && CE.menuOpen) {
					GoBack(); CE.maxWait = 0;
				}
				if (Input.Gamepad.wButtons == (XINPUT_GAMEPAD_DPAD_RIGHT))
				{
					IntChanger(1);
					BoneSelector(1);
					CE.maxWait = 0;
				}
				if (Input.Gamepad.wButtons == (XINPUT_GAMEPAD_DPAD_LEFT)) {
					IntChanger(0);
					BoneSelector(0);
					CE.maxWait = 0;
				}
			}
		}
	}

	void setupConst() {
		Cbuf_AddText(0, va("set cg_fov %.f;\n", cg_fov));
		thirdperson ? Cbuf_AddText(0, "set cg_thirdPerson 1;\n") : Cbuf_AddText(0, "set cg_thirdPerson 0;\n");
	}

	void RunMenu() {
		CE.menuW = 39;
		CE.centerX = 958;
		CE.centerY = 30;
		setupConst();
		ButtonMonitor();
		if (CE.menuOpen) {
			MenuStructure();
		}
	}
}