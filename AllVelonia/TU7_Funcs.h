namespace TU7
{
#define spreadMultiplier 0.00392156862f
	char* _version = "BETA 0.0.3";
	bool renderRadar, teamnow, thirdperson, radar, sway, recoil, noflinch, toggleFB, vmColor,
		debugmode, drawPointers, drawBarrelESP, drawEndBox, flashing, _noinfect, esp, esptypes, espname, espdist,
		snaplines, drawinfo;
	bool aimbot, snapbot, smoothAim, AimKey, silentaim, autowall, nospread, autoshoot, fakelag;
	bool stealName, eliteClanTag, _showNewsbar;
	bool _antispin, _antiflip, _antix, _antiy, _antishield;
	bool _drawConsoleInfo;
	bool esp2D, esp3D, espTri;
	bool godmode, noclip;
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

	char* Bones[19] = {
		"j_helmet", "j_head", "j_neck", "j_shoulder_le", "j_shoulder_ri", "j_elbow_le",
		"j_elbow_ri", "j_wrist_le", "j_wrist_ri",
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
	
	void godMode()
	{
		godmode = !godmode;
		Cbuf_AddText(0, va("god %d;", godmode));
	}

	void noClip()
	{
		noclip = !noclip;
		Cbuf_AddText(0, va("noclip %d;", noclip));
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
		Cbuf_AddText(0, va("cmd mr %i %i %s", Dvar_GetInt("sv_serverId"), -1, "endround;"));
	}

	void disconnect()
	{
		Cbuf_AddText(0, "disconnect;");
	}

	void Changeteam(char* team)
	{
		Cbuf_AddText(0, va("cmd mr %i 4 %s;", Dvar_GetInt("sv_serverId"), team));
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

	//TODO: Find Class Value
	void changeClass() {
		Cbuf_AddText(0, va("cmd mr %i 3 custom%i;", Dvar_GetInt("sv_serverId"), customClass));
		iprintln(va("Changed to Class %i", customClass));
	}
	
	void stealNames() {
		stealName = !stealName;
		iprintln(va("Steal Names: %s", boolToStr(stealName)));
	}

	void newsBar() {
		_showNewsbar = !_showNewsbar;
		iprintln(va("News Bar: %s", boolToStr(_showNewsbar)));
	}

	void addBots()
	{
		Cbuf_AddText(0, "developer 1;developer_script 1;set scr_testclients 6;fast_restart;");
	}
	
	bool hasReset = true;
	bool validClient = true;
	char* clientName = "";
	char* _clanTag = "";

	char* _newsbarTxt = "Welcome to Velonia TU7 | \x14/\x15 to Scroll - \x3 to Select - \x2 to Go Back | Developed By Liam";
	float _newsbarxPos = 1500;
	bool _newsbarPause = false;
	int _pauseTimer, stealTimer, rainTimer = 0;
	int stealClient = 0;

	void updateUserInfo(char* name, char* clanTag, int rank = 0, int prestige = 0) {
		auto txt = va("userinfo \"\\name\\%s\\rank\\%d\\prestige\\%d\"", name, rank, prestige);
		if (*clanTag != 0)  txt = va("userinfo \"\\name\\%s\\clanAbbrev\\%s\\ec_usingTag\\%d\\ec_TagText\\%s\\rank\\%d\\prestige\\%d\"", name, clanTag, static_cast<int>(eliteClanTag), clanTag, rank, prestige);
		Cbuf_AddText(0, txt);
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
		auto tagShort = SL_GetString(tagName, 0);
		Aimtarget_GetTagPos(i, tagShort, Pos);
		return Pos;
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

	float(__cdecl* CG_GoodRandomFloat)(int* seed) = reinterpret_cast<float(__cdecl*)(int*)>(0x822046D0);
	
	int BG_GetWeaponDef(int WeaponID) {
		return *reinterpret_cast<int*>(0x824C6CF8 + (WeaponID << 2));
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