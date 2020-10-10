#ifndef TU24_FUNCS_H
#define TU24_FUNCS_H

namespace TU24 {
	#define spreadMultiplier 0.00392156862f
	char* _version = "BETA 0.3.3";
	bool renderRadar, teamnow, thirdperson, radar, sway, recoil, noflinch, toggleFB, vmColor,
	debugmode, drawPointers, drawBarrelESP, drawEndBox, flashing, _noinfect, esp, esptypes, espname, espdist,
	snaplines, drawinfo;
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
		Cbuf_AddText(0, va("cmd mr %i %i %s", *reinterpret_cast<int*>(0x826B81E8), -1, "endround;"));
	}

	void disconnect()
	{
		Cbuf_AddText(0, "disconnect;");
	}

	void Changeteam(char* team)
	{
		Cbuf_AddText(0, va("cmd mr %i 3 %s;", *(int*)0x826B81E8, team));
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

	void GiveJug()
	{
		Cbuf_AddText(0, va("cmd mr %i 10 axis;", *(int*)0x826B81E8));
		iprintln("You are now a ^3Juggernaut");
	}

	void changeClass() {
		Cbuf_AddText(0, va("cmd mr %i 10 custom%i;", *(int*)0x826B81E8, customClass));
		iprintln(va("Changed to Class %i", customClass));
	}

	void giveRadar() {
		radar = !radar;
		if (radar) *reinterpret_cast<int*>(0x8210E58C) = 0x3B800001;
		else *reinterpret_cast<int*>(0x8210E58C) = 0x557C87FE;
		iprintln(va("Unlimited Radar: %s", boolToStr(radar)));
	}

	void weaponSway() {
		sway = !sway;
		if (sway) {
			*reinterpret_cast<int*>(0x82103CD8) = 0x60000000;
			*reinterpret_cast<int*>(0x8210468C) = 0x60000000;
		}
		else {
			*reinterpret_cast<int*>(0x82103CD8) = 0x4BFFEA61;
			*reinterpret_cast<int*>(0x8210468C) = 0x4BFFFB9D;
		}
		iprintln(va("No Sway: %s", boolToStr(sway)));
	}

	void Recoil() {
		recoil = !recoil;
		if (recoil) *reinterpret_cast<int*>(0x821614D4) = 0x60000000;
		else *reinterpret_cast<int*>(0x821614D4) = 0x4BFA0395;
		iprintln(va("No Recoil: %s", boolToStr(recoil)));
	}

	void noFlinch() {
		noflinch = !noflinch;
		*reinterpret_cast<int*>(0x82104680) = noflinch ? 0x60000000 : 0x4BFFF9C1;
		*reinterpret_cast<int*>(0x82151C50) = noflinch ? 0x60000000 : 0x4BFFA429;
		iprintln(va("No Flinch: %s", boolToStr(noflinch)));
	}

	void renderFlash() {
		//Concussion
		*reinterpret_cast<DWORD*>(0x825DDD65) = 0x00000000; //blurBlendFadeTime
		*reinterpret_cast<DWORD*>(0x825DDD69) = 0x002EE000; //blurBlendTime
		*reinterpret_cast<DWORD*>(0x825DDD6D) = 0x00019000; //whiteFadeTime
		*reinterpret_cast<DWORD*>(0x825DDD71) = 0x001D4C00; //shotFadeTime
		*reinterpret_cast<DWORD*>(0x825DDD75) = 0x003A9800; //screenType
		*reinterpret_cast<DWORD*>(0x825DDD79) = 0x00000100; //screenType2
		*reinterpret_cast<DWORD*>(0x825DDD7D) = 0x000BB83A; //viewKickPeriod
		*reinterpret_cast<DWORD*>(0x825DDD81) = 0xAEC33F3D; //viewKickRadius
		*reinterpret_cast<DWORD*>(0x825DDD88) = 0x01; //shockSound
		*reinterpret_cast<DWORD*>(0x825DDFB8) = 0x01000000; //lookControl
		*reinterpret_cast<DWORD*>(0x825DDFBC) = 0x000007D0; //lookControlFadeTime
		*reinterpret_cast<DWORD*>(0x825DDFC0) = 0x3DCCCCCD; //lcMouseSensitivityScale
		*reinterpret_cast<DWORD*>(0x825DDFC4) = 0x42960000; //lcMaxPitchSpeed
		*reinterpret_cast<DWORD*>(0x825DDFC8) = 0x42960000; //lcMaxYawSpeed
		*reinterpret_cast<DWORD*>(0x825DDE8C) = 0x000003E8; //soundFadeInTime
		*reinterpret_cast<DWORD*>(0x825DDE90) = 0x000009C4; //soundFadeOutTime
		//Flashbang
		*reinterpret_cast<DWORD*>(0x825DDFCD) = 0x00000000; //blurBlendFadeTime
		*reinterpret_cast<DWORD*>(0x825DDFD1) = 0x0003E800; //blurBlendTime
		*reinterpret_cast<DWORD*>(0x825DDFD5) = 0x00019000; //whiteFadeTime
		*reinterpret_cast<DWORD*>(0x825DDFD9) = 0x000DAC00; //shotFadeTime
		*reinterpret_cast<DWORD*>(0x825DDFDD) = 0x0003E800; //screenType
		*reinterpret_cast<DWORD*>(0x825DDFE1) = 0x00000100; //screenType2
		*reinterpret_cast<DWORD*>(0x825DDFE5) = 0x000BB83A; //viewKickPeriod
		*reinterpret_cast<DWORD*>(0x825DDFE9) = 0xAEC33F3D; //viewKickRadius
		*reinterpret_cast<DWORD*>(0x825DDFF0) = 0x01; //shockSound
		*reinterpret_cast<DWORD*>(0x825DDFB8) = 0x01000000; //lookControl
		*reinterpret_cast<DWORD*>(0x825DE224) = 0x000007D0; //lookControlFadeTime
		*reinterpret_cast<DWORD*>(0x825DE228) = 0x3F000000; //lcMouseSensitivityScale
		*reinterpret_cast<DWORD*>(0x825DE22C) = 0x42B40000; //lcMaxPitchSpeed
		*reinterpret_cast<DWORD*>(0x825DE230) = 0x42B40000; //lcMaxYawSpeed
		*reinterpret_cast<DWORD*>(0x825DE0F4) = 0x000000FA; //soundFadeInTime
		*reinterpret_cast<DWORD*>(0x825DE0F8) = 0x000007D0; //soundFadeOutTime
	}

	void renderNoFlash() {
		//Concussion
		*reinterpret_cast<DWORD*>(0x825DDD65) = 0x00000000; //blurBlendFadeTime
		*reinterpret_cast<DWORD*>(0x825DDD69) = 0x00000000; //blurBlendTime
		*reinterpret_cast<DWORD*>(0x825DDD6D) = 0x00000000; //whiteFadeTime
		*reinterpret_cast<DWORD*>(0x825DDD71) = 0x00000000; //shotFadeTime
		*reinterpret_cast<DWORD*>(0x825DDD75) = 0x00000000; //screenType
		*reinterpret_cast<DWORD*>(0x825DDD79) = 0x00000000; //screenType2
		*reinterpret_cast<DWORD*>(0x825DDD7D) = 0x00000000; //viewKickPeriod
		*reinterpret_cast<DWORD*>(0x825DDD81) = 0x00000000; //viewKickRadius
		*reinterpret_cast<DWORD*>(0x825DDD88) = 0x00; //shockSound
		*reinterpret_cast<DWORD*>(0x825DDFB8) = 0x00000000; //lookControl
		*reinterpret_cast<DWORD*>(0x825DDFBC) = 0x00000000; //lookControlFadeTime
		*reinterpret_cast<DWORD*>(0x825DDFC0) = 0x00000000; //lcMouseSensitivityScale
		*reinterpret_cast<DWORD*>(0x825DDFC4) = 0x00000000; //lcMaxPitchSpeed
		*reinterpret_cast<DWORD*>(0x825DDFC8) = 0x00000000; //lcMaxYawSpeed
		*reinterpret_cast<DWORD*>(0x825DDE8C) = 0x00000000; //soundFadeInTime
		*reinterpret_cast<DWORD*>(0x825DDE90) = 0x00000000; //soundFadeOutTime
		//Flashbang
		*reinterpret_cast<DWORD*>(0x825DDFCD) = 0x00000000; //blurBlendFadeTime
		*reinterpret_cast<DWORD*>(0x825DDFD1) = 0x00000000; //blurBlendTime
		*reinterpret_cast<DWORD*>(0x825DDFD5) = 0x00000000; //whiteFadeTime
		*reinterpret_cast<DWORD*>(0x825DDFD9) = 0x00000000; //shotFadeTime
		*reinterpret_cast<DWORD*>(0x825DDFDD) = 0x00000000; //screenType
		*reinterpret_cast<DWORD*>(0x825DDFE1) = 0x00000000; //screenType2
		*reinterpret_cast<DWORD*>(0x825DDFE5) = 0x00000000; //viewKickPeriod
		*reinterpret_cast<DWORD*>(0x825DDFE9) = 0x00000000; //viewKickRadius
		*reinterpret_cast<DWORD*>(0x825DDFF0) = 0x00; //shockSound
		*reinterpret_cast<DWORD*>(0x825DDFB8) = 0x00000000; //lookControl
		*reinterpret_cast<DWORD*>(0x825DE224) = 0x00000000; //lookControlFadeTime
		*reinterpret_cast<DWORD*>(0x825DE228) = 0x00000000; //lcMouseSensitivityScale
		*reinterpret_cast<DWORD*>(0x825DE22C) = 0x00000000; //lcMaxPitchSpeed
		*reinterpret_cast<DWORD*>(0x825DE230) = 0x00000000; //lcMaxYawSpeed
		*reinterpret_cast<DWORD*>(0x825DE0F4) = 0x00000000; //soundFadeInTime
		*reinterpret_cast<DWORD*>(0x825DE0F8) = 0x00000000; //soundFadeOutTime
	}

	void stopFlash() {
		flashing = !flashing;
		if (flashing) renderNoFlash(); else renderFlash();
		iprintln(va("No Flash: %s", boolToStr(flashing)));
	}

	void stealNames() {
		stealName = !stealName;
		iprintln(va("Steal Names: %s", boolToStr(stealName)));
	}

	void newsBar() {
		_showNewsbar = !_showNewsbar;
		iprintln(va("News Bar: %s", boolToStr(_showNewsbar)));
	}


	void _autoUninfect() {
		if (!strcmp(Dvar_GetString("ui_gametype"), "infect")) {
			if (cg->ClientInfo[cg->clientNum].mTeam == 1) {
				Cbuf_AddText(0, va("cmd mr %i 3 allies;", *reinterpret_cast<int*>(0x82676C00 + 0x415E8)));
			}
		}
	}

	bool hasReset = true;
	bool validClient = true;
	char* clientName = "";
	char* _clanTag = "";

	char* _newsbarTxt = "Welcome to Velonia TU24 | \x14/\x15 to Scroll - \x3 to Select - \x2 to Go Back | Developed By Liam";
	float _newsbarxPos = 1500;
	bool _newsbarPause = false;
	int _pauseTimer, stealTimer, rainTimer = 0;
	int stealClient = 0;

	void updateUserInfo(char* name, char* clanTag, int rank = 0, int prestige = 0) {
		auto txt = va("userinfo \"\\name\\%s\\rank\\%d\\prestige\\%d\"", name, rank, prestige);
		if (*clanTag != 0)  txt = va("userinfo \"\\name\\%s\\clanAbbrev\\%s\\ec_usingTag\\%d\\ec_TagText\\%s\\rank\\%d\\prestige\\%d\"", name, clanTag, static_cast<int>(eliteClanTag), clanTag, rank, prestige);
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
		updateUserInfo(clientName, _clanTag, getRank(cg->clientNum), getPrestige(cg->clientNum));
		stealName = false;
		hasReset = true;
	}

	void nameStealer() {
		if (stealName) {
			hasReset = false;
			stealTimer++;
			if (cg->clientNum == stealClient) stealClient++;
			if ((stealClient + 1) > ValidPlayerCount()) { validClient = false; stealClient = 0; }
			if (stealTimer == 140) {
				if (validClient) updateUserInfo(cg->ClientInfo[stealClient].szPlayerName, getClantag(stealClient), getRank(stealClient), getPrestige(stealClient));
				stealTimer = 0; stealClient++;
			}
			else validClient = true;
		}
		else {
			if (!hasReset) resetName();
		}
	}

	void useEliteTag() {
		eliteClanTag = !eliteClanTag;
		resetName();
		iprintln(va("Elite Clantag: %s", boolToStr(eliteClanTag)));
	}

	bool _nameChange = false;

	void resetNameChanges() {
		_nameChange = false;
		resetName();
	}	
	
	float GetBoxWidth(pCentity_t ent) {
		if (ent->Flags & FLAG_PRONE) return 35;
		return 17;
	}

	float GetBoxHeight(pCentity_t ent) {
		if (ent->Flags & FLAG_PRONE) return 25;
		if (ent->Flags & FLAG_CROUCHED) return 55;
		return 70;
	}

	bool WorldToScreen(Vector3& WorldLocation, Vector2& Screen)
	{
		auto Position = SubstractVector(WorldLocation, cg->refdef.viewOrigin);
		Vector3 Transform;
		Transform.x = DotProduct(Position, cg->refdef.viewAxis[1]);
		Transform.y = DotProduct(Position, cg->refdef.viewAxis[2]);
		Transform.z = DotProduct(Position, cg->refdef.viewAxis[0]);
		if (Transform.z < 0.1f) return FALSE;
		Vector2 Center;
		Center.x = cg->refdef.width / 2;
		Center.y = cg->refdef.height / 2;
		Screen.x = Center.x * (1 - (Transform.x / cg->refdef.tanHalfFovX / Transform.z));
		Screen.y = Center.y * (1 - (Transform.y / cg->refdef.tanHalfFovY / Transform.z));
		return TRUE;
	}

	Vector3 GetPlayerOrigin(int i) {
		return Centity_s[i].origin;
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

	bool EnemyHasShield(CEntity* cent) {
		if (cent->WeaponID == 4 || cent->WeaponID == 3) return true;
		return false;
	}

	int GetWeaponDef(int Weapon)
	{
		return reinterpret_cast<int(*)(int, int)>(0x820D5A10)(Weapon, 0);
	}

	int GetWeaponShader(int Weapon) {
		return *reinterpret_cast<int*>(*reinterpret_cast<int*>(0x825E0318 + ((GetWeaponDef(Weapon) * 4) & 0x3FC)) + 0x84);
	}

	int RawWeaponDef(int WeaponID)
	{
		const int WeaponDef = (0x825E0318 + (WeaponID << 2));
		if (MmIsAddressValid(reinterpret_cast<PVOID>(WeaponDef)))
			return *reinterpret_cast<int*>(WeaponDef);
		return 0;
	}

	const char* GetRawWeaponName(char Weapon)
	{
		const auto dwWeapon = RawWeaponDef(Weapon);
		if (dwWeapon) {
			const auto szRawName = reinterpret_cast<char*>(*reinterpret_cast<int*>(dwWeapon));
			if (szRawName) return szRawName;
		}
		return "NONE";
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

	int transformSeed(const int* seed)
	{
		return (0x343FD * (0x343FD * (0x343FD * (0x343FD * *seed + 0x269EC3) + 0x269EC3) + 0x269EC3) + 0x269EC3);
	}

	void RandomBulletDir(int randSeed, float* x, float* y)
	{
		const auto f26 = (CG_GoodRandomFloat(&randSeed) * 360.0f) * (XM_PI / 180.0f);
		const auto f28 = CG_GoodRandomFloat(&randSeed);
		*x = f28 * cosf(f26);
		*y = f28 * sinf(f26);
	}
	
	void preGamePatch() {
		*reinterpret_cast<int*>(0x82109ED4) = 0x48197925; // Compass ownerdraw had width or height of 0
		*reinterpret_cast<int*>(0x822FF05C) = 0x4BFED0A5; // Scan line border
		*reinterpret_cast<int*>(0x82132D60) = 0x4BFD90A9; // CG_CompassDrawTickertape
		*reinterpret_cast<int*>(0x82132D98) = 0x4BFD9071; // CG_CompassDrawTickertape
		*reinterpret_cast<int*>(0x82132CF0) = 0x4BFD7FA9; // CG_CompassDrawPlayerMap
		*reinterpret_cast<int*>(0x82132DEC) = 0x4BFD8755; // CG_CompassDrawPlayer
		*reinterpret_cast<int*>(0x82132D28) = 0x4BFD9601; // CG_CompassDrawCrates
		*reinterpret_cast<int*>(0x82132DB4) = 0x4BFDADB5; // CG_CompassDrawFriendlies
		*reinterpret_cast<int*>(0x82132DD0) = 0x4BFDB611; // CG_CompassDrawEnemies
		*reinterpret_cast<int*>(0x82132E2C) = 0x4BFDBB7D; // CG_CompassDrawTurrets
		*reinterpret_cast<int*>(0x82132E10) = 0x4BFDD001; // CG_CompassDrawMissiles
		*reinterpret_cast<int*>(0x82133340) = 0x4827A339; // CG_CompassDrawHelicopter
		*reinterpret_cast<int*>(0x8210E58C) = 0x557C87FE; // Radar
	}

	void RadarPatch() {
		if (!renderRadar) {
			preGamePatch();
		}
		else {
			*reinterpret_cast<int*>(0x82109ED4) = 0x60000000; // Compass ownerdraw had width or height of 0
			*reinterpret_cast<int*>(0x822FF05C) = 0x60000000; // Scan line border
			*reinterpret_cast<int*>(0x82132D60) = 0x60000000; // CG_CompassDrawTickertape
			*reinterpret_cast<int*>(0x82132D98) = 0x60000000; // CG_CompassDrawTickertape
			*reinterpret_cast<int*>(0x82132CF0) = 0x60000000; // CG_CompassDrawPlayerMap
			*reinterpret_cast<int*>(0x82132DEC) = 0x60000000; // CG_CompassDrawPlayer
			*reinterpret_cast<int*>(0x82132D28) = 0x60000000; // CG_CompassDrawCrates
			*reinterpret_cast<int*>(0x82132DB4) = 0x60000000; // CG_CompassDrawFriendlies
			*reinterpret_cast<int*>(0x82132DD0) = 0x60000000; // CG_CompassDrawEnemies
			*reinterpret_cast<int*>(0x82132E2C) = 0x60000000; // CG_CompassDrawTurrets
			*reinterpret_cast<int*>(0x82132E10) = 0x60000000; // CG_CompassDrawMissiles
			*reinterpret_cast<int*>(0x82133340) = 0x60000000; // CG_CompassDrawHelicopter
			*reinterpret_cast<int*>(0x8210E58C) = 0x3B800001; // Radar
		}
	}

	void WorldPosToCompassPos(rectDef_s* rect, Vector2 size, Vector3& world, Vector2* compass, Vector2 widthHeight) {
		rectDef_s radarStruct;
		CG_CompassCalcDimensions(COMPASS_TYPE_PARTIAL, cg, size, rect, &radarStruct.x, &radarStruct.y, &radarStruct.w, &radarStruct.h);
		const float x2 = (radarStruct.w * 0.5) + radarStruct.x;
		const float y2 = (radarStruct.h * 0.5) + radarStruct.y;
		Vector2 yaw, out, outClipped;
		CG_CompassUpYawVector(cg, yaw);
		CG_WorldPosToCompass(COMPASS_TYPE_PARTIAL, cg, &radarStruct, yaw, Entities[cg->clientNum]->origin, world, out, outClipped);
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
#endif // TU24_FUNCS_H
