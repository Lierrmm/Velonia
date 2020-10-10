namespace TU17
{
#define spreadMultiplier 0.00392156862f
	char* _version = "BETA 0.0.1";
	bool renderRadar, teamnow, thirdperson, radar, sway, recoil, noflinch, toggleFB, vmColor,
		debugmode, drawPointers, drawBarrelESP, drawEndBox, flashing, _noinfect, esp, esptypes, espname, espdist,
		snaplines, drawinfo;
	bool aimbot, snapbot, smoothAim, AimKey, silentaim, autowall, nospread, autoshoot, fakelag;
	bool stealName, eliteClanTag, _showNewsbar;
	bool _antispin, _antiflip, _antix, _antiy, _antishield;
	bool _drawConsoleInfo;
	bool esp2D, esp3D, espTri;

	bool UIMode, drawSnap;

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

	int serverId = 0x82B55908;

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
		Cbuf_AddText(0, va("camera_thirdPerson %d;", thirdperson));
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

	void toggleUIMode()
	{
		UIMode = !UIMode;
		Cbuf_AddText(0, va("ui_showlist  %d;", UIMode));
		iprintln(va("ShowList: %s", boolToStr(UIMode)));
	}
	
	void endgame()
	{
		Cbuf_AddText(0, va("cmd lui %i %i %i;", 9, 1, *reinterpret_cast<int*>(serverId)));
	}

	void switchTeam(int team)
	{
		Cbuf_AddText(0, va("cmd lui %i %i %i;", 68, team, *reinterpret_cast<int*>(serverId)));
	}

	void togteam() {
		switchTeam(customTeam);
		iprintln("Switched Teams");
	}

	void changeClass() {
		Cbuf_AddText(0, va("cmd lui %i %i %i;", 5, (customClass - 1), *reinterpret_cast<int*>(serverId)));
		iprintln(va("Changed to Class %i", customClass));
	}

	void disconnect()
	{
		Cbuf_AddText(0, "disconnect;");
	}

	void giveRadar() {
		radar = !radar;
		*reinterpret_cast<byte*>(0x8226539B) = radar ? 0x01 : 0x00;
		*reinterpret_cast<byte*>(0x82265793) = radar ? 0x01 : 0x00;
		*reinterpret_cast<byte*>(0x822657FF) = radar ? 0x01 : 0x00;
		iprintln(va("Unlimited Radar: %s", boolToStr(radar)));
	}

	void weaponSway() {
		sway = !sway;
		*reinterpret_cast<int*>(0x82103CD8) = sway ? 0x60000000 : 0x4BFFEA61;
		*reinterpret_cast<int*>(0x8210468C) = sway ? 0x60000000 : 0x4BFFFB9D;
		iprintln(va("No Sway: %s", boolToStr(sway)));
	}
	
	void Recoil() {
		recoil = !recoil;
		*reinterpret_cast<int*>(0x822C9344) = recoil ? 0x60000000 : 0x4BF8AE4D;
		iprintln(va("No Recoil: %s", boolToStr(recoil)));
	}

	void ToggleRCS(int)
	{
		//*reinterpret_cast<int*>(0x822542B0) = bRCS ? 0x60000000 : 0x40990028;
	}
	
	//TODO: This shit
	void noFlinch() {
		noflinch = !noflinch;
		*reinterpret_cast<int*>(0x82258BE0) = noflinch ? 0x60000000 : 0x4BFFDED9;
		*reinterpret_cast<int*>(0x822B512C) = noflinch ? 0x60000000 : 0x4BF9F39C;
		iprintln(va("No Flinch: %s", boolToStr(noflinch)));
	}

	void newsBar() {
		_showNewsbar = !_showNewsbar;
		iprintln(va("News Bar: %s", boolToStr(_showNewsbar)));
	}

	
	char* _newsbarTxt = "Welcome to Velonia TU17 | \x14/\x15 to Scroll - \x3 to Select - \x2 to Go Back | Developed By Liam";
	float _newsbarxPos = 1500;
	bool _newsbarPause = false;
	int _pauseTimer = 0;
		
	
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
		auto Position = SubstractVector(WorldLocation, cg->RefDef.viewOrigin);
		Vector3 Transform;
		Transform.x = DotProduct(Position, cg->RefDef.viewAxis[1]);
		Transform.y = DotProduct(Position, cg->RefDef.viewAxis[2]);
		Transform.z = DotProduct(Position, cg->RefDef.viewAxis[0]);
		if (Transform.z < 0.1f) return FALSE;
		Vector2 Center;
		Center.x = cg->RefDef.Width / 2;
		Center.y = cg->RefDef.Height / 2;
		Screen.x = Center.x * (1 - (Transform.x / cg->RefDef.Fov.x / Transform.z));
		Screen.y = Center.y * (1 - (Transform.y / cg->RefDef.Fov.y / Transform.z));
		return TRUE;
	}

	Vector3 GetPlayerOrigin(int i) {
		return Centity_s[i].Origin;
	}

	Vector3 GetPlayerViewOrigin() {
		Vector3 Pos;
		CG_GetPlayerViewOrigin(0, cg, Pos);
		return Pos;
	}

	Vector3 GetTagPos(int i, const char* tagName) {
		Vector3 Pos;
		Aimtarget_GetTagPos(0, &Centity_s[i], SL_GetString(tagName, 0), Pos);
		return Pos;
	}

	int GetWeaponShader(int Weapon)
	{
		return *reinterpret_cast<int*>(*reinterpret_cast<int*>(0x82A96FD0 + ((Weapon * 4) & 0x3FC)) + 0x84);
	}

	int RawWeaponDef(int WeaponID)
	{
		const int WeaponDef = (0x82A96FD0 + (WeaponID << 2));
		if (MmIsAddressValid(reinterpret_cast<PVOID>(WeaponDef)))
			return *reinterpret_cast<int*>(WeaponDef);
		return 0;
	}

	const char* GetRawWeaponName(char Weapon)
	{
		const auto dwWeapon = RawWeaponDef(Weapon);
		if (dwWeapon) {
			auto* const szRawName = reinterpret_cast<char*>(*reinterpret_cast<int*>(dwWeapon));
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
	
	int transformSeed(int* seed) {
		return (0x343FD * (0x343FD * (0x343FD * (0x343FD * *seed + 0x269EC3) + 0x269EC3) + 0x269EC3) + 0x269EC3);
	}

	void RandomBulletDir(int randSeed, float* x, float* y) {
		float f26 = (CG_GoodRandomFloat(&randSeed) * 360.0f) * (M_PI / 180.0f);
		float f28 = CG_GoodRandomFloat(&randSeed);
		*x = f28 * cosf(f26); // sin
		*y = f28 * sinf(f26); // cos
	}

	void preGamePatch() {
		*reinterpret_cast<int*>(0x8225F484) = 0x48211E35; // Compass ownerdraw had width or height of 0
		*reinterpret_cast<int*>(0x8220D854) = 0x48053DDD; // CG_CompassDrawTickertape
		*reinterpret_cast<int*>(0x8220D964) = 0x480531ED; // CG_CompassDrawPlayerMap
		*reinterpret_cast<int*>(0x8220DE04) = 0x4805303D; // CG_CompassDrawPlayer
		*reinterpret_cast<int*>(0x8220DD68) = 0x48053CF9; // CG_CompassDrawPlayerPointers_MP
		*reinterpret_cast<int*>(0x8220DD98) = 0x48056CA1; // CG_CompassDrawFriendlies
		*reinterpret_cast<int*>(0x8220DDB0) = 0x48057499; // CG_CompassDrawEnemies
		*reinterpret_cast<int*>(0x8220DD80) = 0x48057D79; // CG_CompassDrawTurrets
		*reinterpret_cast<int*>(0x8220DDC8) = 0x48058FA9; // CG_CompassDrawMissiles
		*reinterpret_cast<int*>(0x8220DDE0) = 0x483DF3B9; // CG_CompassDrawHelicopter
	}

	void RadarPatch() {
		if (!renderRadar) {
			preGamePatch();
		}
		else {
			*reinterpret_cast<int*>(0x8225F484) = 0x60000000; // Compass ownerdraw had width or height of 0
			//*reinterpret_cast<int*>(0x8220D854) = 0x60000000; // CG_CompassDrawTickertape
			*reinterpret_cast<int*>(0x8220D964) = 0x60000000; // CG_CompassDrawPlayerMap
			*reinterpret_cast<int*>(0x8220DE04) = 0x60000000; // CG_CompassDrawPlayer
			*reinterpret_cast<int*>(0x8220DD68) = 0x60000000; // CG_CompassDrawPlayerPointers_MP
			*reinterpret_cast<int*>(0x8220DD98) = 0x60000000; // CG_CompassDrawFriendlies
			*reinterpret_cast<int*>(0x8220DDB0) = 0x60000000; // CG_CompassDrawEnemies
			*reinterpret_cast<int*>(0x8220DD80) = 0x60000000; // CG_CompassDrawTurrets
			*reinterpret_cast<int*>(0x8220DDC8) = 0x60000000; // CG_CompassDrawMissiles
			*reinterpret_cast<int*>(0x8220DDE0) = 0x60000000; // CG_CompassDrawHelicopter
		}
	}
	
	void WorldPosToCompassPos(rectDef_s* rect, Vector2 size, Vector3& world, Vector2* compass, Vector2 widthHeight) {
		rectDef_s radarStruct;
		CG_CompassCalcDimensions(COMPASS_TYPE_PARTIAL, cg, size, rect, &radarStruct.x, &radarStruct.y, &radarStruct.w, &radarStruct.h);
		const float x2 = (radarStruct.w * 0.5) + radarStruct.x;
		const float y2 = (radarStruct.h * 0.5) + radarStruct.y;
		Vector2 yaw, out, outClipped;
		CG_CompassUpYawVector(cg, yaw);
		CG_WorldPosToCompass(COMPASS_TYPE_PARTIAL, cg, &radarStruct, yaw, Centity_s[cg->ClientNumber].Origin, world, out, outClipped);
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