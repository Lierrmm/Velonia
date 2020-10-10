namespace TU9
{
	#define spreadMultiplier 0.00392156862f
	char* _version = "BETA 0.2.1";
	
	bool renderRadar, teamnow, thirdperson, radar, sway, recoil, noflinch, toggleFB, vmColor,
		debugmode, drawPointers, drawBarrelESP, drawEndBox, flashing, _noinfect, esp, esptypes, espname, espdist,
		snaplines, drawinfo, walls;
	bool aimbot, snapbot, smoothAim, AimKey, silentaim, autowall, nospread, autoshoot, fakelag;
	bool stealName, eliteClanTag, _showNewsbar;
	bool _antispin, _antiflip, _antix, _antiy, _antishield;
	bool _drawConsoleInfo;
	bool esp2D, esp3D, espTri;

	int packetTimer;

	Vector2 m_radarXY;
	bool canRenderRadar;
	bool hasPatchedRadar;

	bool _mFakeLag = false;

	int cg_fov = 65;
	int cg_gun_x = 0;
	int cg_gun_y = 0;
	int cg_gun_z = 0;
	int customClass = 1;
	int customTeam = 1;
	int chromeVal = 0;
	int colorMap = 1;
	int tpRange = 120;
	int tpAngle = 120;
	int snaplinepos = (740 / 2);
	int targetBone = 0;
	int wallClient = -1;

	DWORD NoRecoil = 0x82135BFC;
	DWORD WeaponSway = 0x820E5B38;
	DWORD ZommingSway = 0x820E657C;

	char* Bones[20] = {
		"j_helmet", "j_head", "j_neck", "j_shoulder_le", "j_shoulder_ri", "j_elbow_le",
		"j_elbow_ri", "j_wrist_le", "j_wrist_ri", "j_gun",
		"j_mainroot", "j_spineupper", "j_spinelower", "j_spine4",
		"j_hip_ri", "j_hip_le", "j_knee_le", "j_knee_ri", "j_ankle_ri", "j_ankle_le"
	};
	
	const char* boolToStr(bool val) {
		return val ? "[^2ON^7]" : "[^1OFF^7]";
	}

	void iprintln(const char* msg) {
		CG_GameMessage(0, msg);
	}

	void iprintlnbold(const char* msg) {
		CG_GameMessageBold(0, msg);
	}

	void thirdPerson() {
		thirdperson = !thirdperson;
		Cbuf_AddText(0, va("cg_thirdperson %d;", thirdperson));
		iprintln(va("Third Person: %s", boolToStr(thirdperson)));
	}

	void toggleChrome() {
		toggleFB = !toggleFB;
		toggleFB ? chromeVal = 2 : chromeVal = 0;
		Cbuf_AddText(0, va("r_specularMap %d;", chromeVal));
		iprintln(va("Chrome Vision: %s", boolToStr(toggleFB)));
	}

	void toggleDebugMode() {
		debugmode = !debugmode;
		Cbuf_AddText(0, va("ui_debugmode  %d;", debugmode));
		iprintln(va("Debug Mode: %s", boolToStr(debugmode)));
	}

	void endgame()
	{
		Cbuf_AddText(0, va(";cmd mr %i %i %s", *reinterpret_cast<int*>(0x826237E0), -1, "endround;"));
	}

	void disconnect()
	{
		Cbuf_AddText(0, "disconnect;");
	}

	void Changeteam(char* team)
	{
		Cbuf_AddText(0, va("cmd mr %i 3 %s;", *reinterpret_cast<int*>(0x826237E0), team));
		iprintln(va("Changed to %s", team));
		teamnow = !teamnow;
	}

	void togteam() {
		switch (customTeam) {
		case 1:
			Changeteam("axis");
			break;
		case 2:
			Changeteam("allies");
			break;
		case 3:
			Changeteam("spectator");
			break;
		}
	}
	void changeClass() {
		Cbuf_AddText(0, va(";cmd mr %i 10 custom%i;", *reinterpret_cast<int*>(0x826237E0), customClass));
		iprintln(va("Changed to Class %i", customClass));
	}

	void giveRadar() {
		radar = !radar;
		if (radar) Cbuf_AddText(0, "g_compassShowEnemies 1;");
		else Cbuf_AddText(0, "g_compassShowEnemies 0;");
		iprintln(va("Unlimited Radar: %s", boolToStr(radar)));
	}
	
	void weaponSway() {
		sway = !sway;
		if (sway) {
			*reinterpret_cast<int*>(WeaponSway) = 0x60000000;
			*reinterpret_cast<int*>(ZommingSway) = 0x60000000;
		}
		else {
			*reinterpret_cast<int*>(WeaponSway) = 0x4BFFEAA9;
			*reinterpret_cast<int*>(ZommingSway) = 0x4BFFFBC5;
		}
		iprintln(va("No Sway: %s", boolToStr(sway)));
	}

	void Recoil() {
		recoil = !recoil;
		if (recoil) *reinterpret_cast<int*>(NoRecoil) = 0x60000000;
		else *reinterpret_cast<int*>(NoRecoil) = 0x4BFAD5FD;
		iprintln(va("No Recoil: %s", boolToStr(recoil)));
	}

	void noFlinch() {
		noflinch = !noflinch;
		*(int*)(0x820E6570) = noflinch ? 0x60000000 : 0x4BFFF989;
		*(int*)(0x82128AA8) = noflinch ? 0x60000000 : 0x4BFFA970;
		iprintln(va("No Flinch: %s", boolToStr(noflinch)));
	}

	void renderFlash() {
		//Concussion
		*(DWORD*)(StunConc) = 0x00000000; //blurBlendFadeTime
		*(DWORD*)(StunConc + 0x4) = 0x000003E8; //blurBlendTime
		*(DWORD*)(StunConc + 0x8) = 0x00000190; //whiteFadeTime
		*(DWORD*)(StunConc + 0xC) = 0x000DAC00; //shotFadeTime
		*(DWORD*)(StunConc + 0x10) = 0x00000000; //screenType
		*(DWORD*)(StunConc + 0x14) = 0x00000000; //screenType2
		*(DWORD*)(StunConc + 0x18) = 0x00000BB8; //viewKickPeriod
		*(DWORD*)(StunConc + 0x1C) = 0x3AAEC33F; //viewKickRadius
		*(DWORD*)(StunConc + 0x23) = 0x01; //shockSound
		*(DWORD*)(StunConc + 0x254) = 0x01000000; //lookControl
		*(DWORD*)(StunConc + 0x258) = 0x000007D0; //lookControlFadeTime
		*(DWORD*)(StunConc + 0x25C) = 0x3F000000; //lcMouseSensitivityScale
		*(DWORD*)(StunConc + 0x260) = 0x42340000; //lcMaxPitchSpeed
		*(DWORD*)(StunConc + 0x264) = 0x42340000; //lcMaxYawSpeed
		*(DWORD*)(StunConc + 0x128) = 0x000000FA; //soundFadeInTime
		*(DWORD*)(StunConc + 0x12C) = 0x000009C4; //soundFadeOutTime
		//Flashbang
		*(DWORD*)(FlashConc) = 0x00000000; //blurBlendFadeTime
		*(DWORD*)(FlashConc + 0x4) = 0x0003E800; //blurBlendTime
		*(DWORD*)(FlashConc + 0x8) = 0x00019000; //whiteFadeTime
		*(DWORD*)(FlashConc + 0xC) = 0x000DAC00; //shotFadeTime
		*(DWORD*)(FlashConc + 0x10) = 0x0003E800; //screenType
		*(DWORD*)(FlashConc + 0x14) = 0x00000100; //screenType2
		*(DWORD*)(FlashConc + 0x18) = 0x000BB83A; //viewKickPeriod
		*(DWORD*)(FlashConc + 0x1C) = 0xAEC33F3D; //viewKickRadius
		*(DWORD*)(FlashConc + 0x23) = 0x01; //shockSound
		*(DWORD*)(FlashConc + 0x254) = 0x01000000; //lookControl
		*(DWORD*)(FlashConc + 0x258) = 0x000007D0; //lookControlFadeTime
		*(DWORD*)(FlashConc + 0x25C) = 0x3F000000; //lcMouseSensitivityScale
		*(DWORD*)(FlashConc + 0x260) = 0x42B40000; //lcMaxPitchSpeed
		*(DWORD*)(FlashConc + 0x264) = 0x42B40000; //lcMaxYawSpeed
		*(DWORD*)(FlashConc + 0x128) = 0x000000FA; //soundFadeInTime
		*(DWORD*)(FlashConc + 0x12C) = 0x000007D0; //soundFadeOutTime
	}

	void renderNoFlash() {
		//Concussion
		*(DWORD*)(StunConc) = 0x00000000; //blurBlendFadeTime
		*(DWORD*)(StunConc + 0x4) = 0x00000000; //blurBlendTime
		*(DWORD*)(StunConc + 0x8) = 0x00000000; //whiteFadeTime
		*(DWORD*)(StunConc + 0xC) = 0x00000000; //shotFadeTime
		*(DWORD*)(StunConc + 0x10) = 0x00000000; //screenType
		*(DWORD*)(StunConc + 0x14) = 0x00000000; //screenType2
		*(DWORD*)(StunConc + 0x18) = 0x00000000; //viewKickPeriod
		*(DWORD*)(StunConc + 0x1C) = 0x00000000; //viewKickRadius
		*(DWORD*)(StunConc + 0x23) = 0x00; //shockSound
		*(DWORD*)(StunConc + 0x254) = 0x00000000; //lookControl
		*(DWORD*)(StunConc + 0x258) = 0x00000000; //lookControlFadeTime
		*(DWORD*)(StunConc + 0x25C) = 0x00000000; //lcMouseSensitivityScale
		*(DWORD*)(StunConc + 0x260) = 0x00000000; //lcMaxPitchSpeed
		*(DWORD*)(StunConc + 0x264) = 0x00000000; //lcMaxYawSpeed
		*(DWORD*)(StunConc + 0x128) = 0x00000000; //soundFadeInTime
		*(DWORD*)(StunConc + 0x12C) = 0x00000000; //soundFadeOutTime
		//Flashbang
		*(DWORD*)(FlashConc) = 0x00000000; //blurBlendFadeTime
		*(DWORD*)(FlashConc + 0x4) = 0x00000000; //blurBlendTime
		*(DWORD*)(FlashConc + 0x8) = 0x00000000; //whiteFadeTime
		*(DWORD*)(FlashConc + 0xC) = 0x00000000; //shotFadeTime
		*(DWORD*)(FlashConc + 0x10) = 0x00000000; //screenType
		*(DWORD*)(FlashConc + 0x14) = 0x00000000; //screenType2
		*(DWORD*)(FlashConc + 0x18) = 0x00000000; //viewKickPeriod
		*(DWORD*)(FlashConc + 0x1C) = 0x00000000; //viewKickRadius
		*(DWORD*)(FlashConc + 0x23) = 0x00; //shockSound
		*(DWORD*)(FlashConc + 0x254) = 0x00000000; //lookControl
		*(DWORD*)(FlashConc + 0x258) = 0x00000000; //lookControlFadeTime
		*(DWORD*)(FlashConc + 0x25C) = 0x00000000; //lcMouseSensitivityScale
		*(DWORD*)(FlashConc + 0x260) = 0x00000000; //lcMaxPitchSpeed
		*(DWORD*)(FlashConc + 0x264) = 0x00000000; //lcMaxYawSpeed
		*(DWORD*)(FlashConc + 0x128) = 0x00000000; //soundFadeInTime
		*(DWORD*)(FlashConc + 0x12C) = 0x00000000; //soundFadeOutTime
	}

	void stopFlash() {
		flashing = !flashing;
		if (flashing) renderNoFlash(); else renderFlash();
		iprintln(va("No Flash: %d", flashing));
	}

	void toggleWalls() {
		walls = !walls;
		walls ? Cbuf_AddText(0, ";r_znear 45;") : Cbuf_AddText(0, ";r_znear 1;");
		iprintln(va("Wall Hack: %s", boolToStr(walls)));
	}

	void stealNames() {
		stealName = !stealName;
		iprintln(va("Steal Names: %s", boolToStr(stealName)));
	}

	void newsBar() {
		_showNewsbar = !_showNewsbar;
		iprintln(va("News Bar: %s", boolToStr(_showNewsbar)));
	}

	bool hasReset = true;
	bool validClient = true;
	char* clientName = "";
	char* _clanTag = "";

	char* _newsbarTxt = "Welcome to Velonia TU9 | \x14/\x15 to Scroll - \x3 to Select - \x2 to Go Back | Developed By Liam";
	float _newsbarxPos = 1500;
	bool _newsbarPause = false;
	int _pauseTimer, stealTimer, rainTimer = 0;
	int stealClient = 0;

	void testColorName(char* name)
	{
		auto txt = va("userinfo \"\\name\\%s\"", name);
		Cbuf_AddText(0, txt);
	}
	
	void updateUserInfo(char* name, char* clanTag, int rank = 0, int prestige = 0) {
		auto txt = va("userinfo \"\\name\\%s\\rank\\%d\\prestige\\%d\"", name, rank, prestige);
		if (*clanTag != 0)  txt = va("userinfo \"\\name\\%s\\clanAbbrev\\%s\\rank\\%d\\prestige\\%d\"", name, clanTag, static_cast<int>(eliteClanTag), clanTag, rank, prestige);
		Cbuf_AddText(0, txt);
	}

	char* getClantag(int i) {
		return *cg->ClientInfo[i].clanTag != 0 ? cg->ClientInfo[i].clanTag : "";
	}

	int getRank(int i) {
		return cg->ClientInfo[i].Rank;
	}

	int getPrestige(int i) {
		return cg->ClientInfo[i].Prestige;
	}

	void resetName() {
		updateUserInfo(clientName, _clanTag, getRank(cg->cNum), getPrestige(cg->cNum));
		stealName = false;
		hasReset = true;
	}

	void nameStealer() {
		if (stealName) {
			hasReset = false;
			stealTimer++;
			if (cg->cNum == stealClient) stealClient++;
			if ((stealClient + 1) > ValidPlayerCount()) { validClient = false; stealClient = 0; }
			if (stealTimer == 140) {
				if (validClient) updateUserInfo(cg->ClientInfo[stealClient].mName, getClantag(stealClient), getRank(stealClient), getPrestige(stealClient));
				stealTimer = 0; stealClient++;
			}
			else validClient = true;
		}
		else {
			if (!hasReset) resetName();
		}
	}

	bool _nameChange = false;

	void resetNameChanges() {
		_nameChange = false;
		resetName();
	}


	float GetBoxWidth(pCentity_t ent) {
		if (ent->Flags & FLAG_PRONE) return 35;
		else return 17;
	}

	float GetBoxHeight(pCentity_t ent) {
		if (ent->Flags & FLAG_PRONE) return 25;
		else if (ent->Flags & FLAG_CROUCHED) return 55;
		else return 70;
	}
	
	bool WorldToScreen(Vector3& WorldLocation, Vector2& Screen)
	{
		Vector3 Position = SubstractVector(WorldLocation, cg->refdef.EyePos);
		Vector3 Transform;
		Transform.x = DotProduct(Position, cg->refdef.ViewAxis[1]);
		Transform.y = DotProduct(Position, cg->refdef.ViewAxis[2]);
		Transform.z = DotProduct(Position, cg->refdef.ViewAxis[0]);
		if (Transform.z < 0.1f) return FALSE;
		Vector2 Center;
		Center.x = cg->refdef.iWidth / 2;
		Center.y = cg->refdef.iHeight / 2;
		Screen.x = Center.x * (1 - (Transform.x / cg->refdef.fov_X / Transform.z));
		Screen.y = Center.y * (1 - (Transform.y / cg->refdef.fov_Y / Transform.z));
		return TRUE;
	}

	Vector3 GetPlayerOrigin(int i) {
		return Centity_s[i].mPos;
	}

	Vector3 GetPlayerViewOrigin() {
		Vector3 Pos;
		CG_GetPlayerViewOrigin(0, cg, Pos);
		return Pos;
	}

	Vector3 GetTagPos(int i, char* tagName) {
		Vector3 Pos;
		Aimtarget_GetTagPos(&Centity_s[i], SL_GetString(tagName, 0), Pos);
		return Pos;
	}
	
	int transformSeed(int* seed) {
		return (0x343FD * (0x343FD * (0x343FD * (0x343FD * *seed + 0x269EC3) + 0x269EC3) + 0x269EC3) + 0x269EC3);
	}

	void RandomBulletDir(int randSeed, float* x, float* y) {
		float f26 = (CG_GoodRandomFloat(&randSeed) * 360.0f) * (XM_PI / 180.0f);
		float f28 = CG_GoodRandomFloat(&randSeed);
		*x = f28 * cosf(f26);
		*y = f28 * sinf(f26);
	}

	unsigned int dwBezierSeed;
	float RandomFloat(float min, float max)
	{
		srand(dwBezierSeed);
		const auto random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
		const auto range = max - min;
		return (random * range) + min;
	}

	float FloatMinMax(float min, float max) {
		const auto random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
		const auto range = max - min;
		return (random * range) + min;
	}

	void AngleForwardVectors(Vector3 angles, Vector3* forward)
	{
		static float sr, sp, sy, cr, cp, cy;
		float angle = angles.y * (M_PI * 2 / 360);
		sy = sin(angle);
		cy = cos(angle);
		angle = angles.x * (M_PI * 2 / 360);
		sp = sin(angle);
		cp = cos(angle);
		angle = angles.z * (M_PI * 2 / 360);
		sr = sin(angle);
		cr = cos(angle);

		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}

	float flBezierTime;
	bool bFirstBezierSet;
	Vector3 vPoint[4];

	void flNormalize(float* x) {
		while (!(*x > -180 && *x < 180))
		{
			if (*x > 180)*x -= 360;
			if (*x < -180)*x += 360;
		}
	}

	Vector3 Lerp(const Vector3& a, const Vector3& b, const float t) {
		Vector3 result;
		result.x = a.x + (b.x - a.x) * t;
		result.y = a.y + (b.y - a.y) * t;
		return result;
	}

	Vector3 CubicBezier(const Vector3& a, const Vector3& b, const Vector3& c, const Vector3& d, const float t) {
		Vector3 ab, bc, cd, abbc, bccd;
		Vector3 result;

		ab = Lerp(a, b, t);
		bc = Lerp(b, c, t);
		cd = Lerp(c, d, t);
		abbc = Lerp(ab, bc, t);
		bccd = Lerp(bc, cd, t);

		result = Lerp(abbc, bccd, t);
		return result;
	}

	int GetWeaponShader(int Weapon) {
		auto Structure = *reinterpret_cast<int*>(0x82557750 + (Weapon * 4));
		return Structure ? *reinterpret_cast<int*>(Structure + 0x48) : -1;
	}

	int CG_GetLocalClientWeaponInfo(int weapon)
	{
		return *reinterpret_cast<int*>(0x825B8524) + weapon * 0x20;
	}

	int RawWeaponDef(int WeaponID)
	{
		int WeaponDef = (0x82557750 + (WeaponID << 2));
		if (MmIsAddressValid(reinterpret_cast<PVOID>(WeaponDef)))
			return *reinterpret_cast<int*>(WeaponDef);
		return 0;
	}

	const char* GetRawWeaponName(char Weapon)
	{
		auto dwWeapon = RawWeaponDef(Weapon);
		if (dwWeapon) {
			auto szRawName = reinterpret_cast<char*>(*reinterpret_cast<int*>(dwWeapon));
			if (szRawName) return szRawName;
		}
		return "NONE";
	}

	void preGamePatch() {
		*reinterpret_cast<int*>(0x820EB324) = 0x48143795; // Compass ownerdraw had width or height of 0
		*reinterpret_cast<int*>(0x821102A8) = 0x4BFDBE21; // CG_CompassDrawPlayerMap
		*reinterpret_cast<int*>(0x821103A8) = 0x4BFDC3F9; // CG_CompassDrawPlayer
		*reinterpret_cast<int*>(0x8211036C) = 0x4BFDE5CD; // CG_CompassDrawFriendlies
		*reinterpret_cast<int*>(0x82110388) = 0x4BFDEC21; // CG_CompassDrawEnemies
		*reinterpret_cast<int*>(0x821103DC) = 0x4BFDFAC5; // CG_CompassDrawPlanes
		//*reinterpret_cast<int*>(0x821103F8) = 0x4BFDEFC1; // CG_CompassDrawSentry
	}

	void RadarPatch() {
		if (!renderRadar) {
			preGamePatch();
		}
		else {
			*reinterpret_cast<int*>(0x820EB324) = 0x60000000; // Compass ownerdraw had width or height of 0
			*reinterpret_cast<int*>(0x821102A8) = 0x60000000; // CG_CompassDrawPlayerMap
			*reinterpret_cast<int*>(0x821103A8) = 0x60000000; // CG_CompassDrawPlayer
			*reinterpret_cast<int*>(0x8211036C) = 0x60000000; // CG_CompassDrawFriendlies
			*reinterpret_cast<int*>(0x82110388) = 0x60000000; // CG_CompassDrawEnemies
			*reinterpret_cast<int*>(0x821103DC) = 0x60000000; // CG_CompassDrawPlanes
			//*reinterpret_cast<int*>(0x821103F8) = 0x60000000; // CG_CompassDrawSentry
		}
	}

	void WorldPosToCompassPos(rectDef_s* rect, Vector2 size, Vector3& world, Vector2* compass, Vector2 widthHeight) {
		rectDef_s radarStruct;
		CG_CompassCalcDimensions(COMPASS_TYPE_PARTIAL, cg, size, rect, &radarStruct.x, &radarStruct.y, &radarStruct.w, &radarStruct.h);
		const float x2 = (radarStruct.w * 0.5) + radarStruct.x;
		const float y2 = (radarStruct.h * 0.5) + radarStruct.y;
		Vector2 yaw, out, outClipped;
		CG_CompassUpYawVector(cg, yaw);
		CG_WorldPosToCompass(COMPASS_TYPE_PARTIAL, cg, &radarStruct, yaw, Entities[cg->cNum]->mPos, world, out, outClipped);
		compass->x = -((widthHeight.x * 0.5) - x2) + outClipped.x;
		compass->y = -((widthHeight.y * 0.5) - y2) + outClipped.y;
	}

	void InitializeOnceInGame(bool* value, void(*function)()) {
		if (Dvar_GetBool("cl_ingame")) {
			if (!*value) {
				*value = true;
				function();
			}
		}
		else {
			if (*value)
				*value = false;
		}
	}	
}
