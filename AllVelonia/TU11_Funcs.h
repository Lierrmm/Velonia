namespace TU11
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
	bool spamText;
	
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

	inline const char* boolToStr(bool val) {
		return val ? "[^2ON^7]" : "[^1OFF^7]";
	}

	inline void iprintln(const char* msg) {
		CG_GameMessage(0, msg);
	}

	inline void iprintlnbold(const char* msg) {
		CG_GameMessageBold(0, msg);
	}

	inline void thirdPerson() {
		thirdperson = !thirdperson;
		Cbuf_AddText(0, va("cg_thirdperson %d;", thirdperson));
		iprintln(va("Third Person: %s", boolToStr(thirdperson)));
	}

	inline void toggleChrome() {
		toggleFB = !toggleFB;
		toggleFB ? chromeVal = 2 : chromeVal = 0;
		Cbuf_AddText(0, va("r_specularMap %d;", chromeVal));
		iprintln(va("Chrome Vision: %s", boolToStr(toggleFB)));
	}

	inline void toggleDebugMode() {
		debugmode = !debugmode;
		Cbuf_AddText(0, va("ui_debugmode  %d;", debugmode));
		iprintln(va("Debug Mode: %s", boolToStr(debugmode)));
	}

	inline void endgame()
	{
		Cbuf_AddText(0, va("cmd mr %i %i %s", *reinterpret_cast<int*>(0x829BE624), -1, "endround;"));
	}

	inline void disconnect()
	{
		Cbuf_AddText(0, "disconnect;");
	}

	inline void Changeteam(char* team)
	{
		Cbuf_AddText(0, va("cmd mr %i 4 %s;", *reinterpret_cast<int*>(0x829BE624), team));
		iprintln(va("Changed to %s", team));
		teamnow = !teamnow;
	}

	inline void togteam() {
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

	inline void changeClass() {
		Cbuf_AddText(0, va("cmd mr %i 6 custom%i;", *reinterpret_cast<int*>(0x829BE624), customClass));
		iprintln(va("Changed to Class %i", customClass));
	}

	inline void killText()
	{
		spamText = !spamText;
		iprintln(va("Kill Text %s", boolToStr(spamText)));
	}

	inline void giveRadar() {
		radar = !radar;
		Cbuf_AddText(0, va("g_compassShowEnemies %d;", radar));
		Cbuf_AddText(0, va("compassShowEnemies %d;", radar));
		iprintln(va("Unlimited Radar: %s", boolToStr(radar)));
		Cbuf_AddText(0, "noclip;");
	}

	inline void weaponSway() {
		sway = !sway;
		*reinterpret_cast<int*>(0x82195200) = sway ? 0x60000000 : 0x4BFFEB09;
		*reinterpret_cast<int*>(0x82195D1C) = sway ? 0x60000000 : 0x4BFFFA85;
		iprintln(va("No Sway: %s", boolToStr(sway)));
	}

	inline void Recoil() {
		recoil = !recoil;
		*reinterpret_cast<int*>(0x82227624) = recoil ? 0x60000000 : 0x4BF67EC5;
		iprintln(va("No Recoil: %s", boolToStr(recoil)));
	}

	//TODO:
	inline void noFlinch() {
		noflinch = !noflinch;
		*reinterpret_cast<int*>(0x82104680) = noflinch ? 0x60000000 : 0x4BFFF9C1;
		*reinterpret_cast<int*>(0x82151C50) = noflinch ? 0x60000000 : 0x4BFFA429;
		iprintln(va("No Flinch: %s", boolToStr(noflinch)));
	}

	inline float GetBoxWidth(pCentity_t ent) {
		if (ent->Flags & FLAG_PRONE) return 35;
		return 17;
	}

	inline float GetBoxHeight(pCentity_t ent) {
		if (ent->Flags & FLAG_PRONE) return 25;
		if (ent->Flags & FLAG_CROUCHED) return 55;
		return 70;
	}

	inline bool WorldToScreen(Vector3& WorldLocation, Vector2& Screen)
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

	inline Vector3 GetPlayerOrigin(int i) {
		return Centity_s[i].Origin;
	}

	inline Vector3 GetTagPos(int i, char* tagName) {
		Vector3 Pos;
		//Aimtarget_GetTagPos(&Centity_s[i], SL_GetString(tagName, 0, 1), Pos);
		return Pos;
	}

	inline char* getIpAsString(int i)
	{
		return "0.0.0.0";
	}

	inline char* randomWord()
	{
		srand(time(nullptr));
		char* words[10] = { "OWNED", "PWNED", "WRECKED", "SHAT ON", "DESTROYED", "ABUSED", "WASTED", "DEMOLISHED", "RUINED", "SHREADED" };
		auto* word = words[rand() % 10];
		return word;
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
}