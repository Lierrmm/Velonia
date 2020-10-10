namespace TU17
{
	void(__cdecl* CG_CompassDrawPlayerMap)(int localClientNum, CompassType compassType, Vector2& size, rectDef_s* r6, int material, const float* color) = reinterpret_cast<void(__cdecl*)(int, CompassType, Vector2&, rectDef_s*, int, const float*)>(0x82260B50);
	void(__cdecl* CG_CompassDrawPlayer)(int localClientNum, CompassType compassType, rectDef_s* parentRect, rectDef_s* rect, float* color) = reinterpret_cast<void(*)(int, CompassType, rectDef_s*, rectDef_s*, float*)>(0x82260E40);
	void(__cdecl* CG_CompassDrawFriendlies)(int localClientNum, CompassType compassType, rectDef_s* parent, rectDef_s* rect, const float* color) = reinterpret_cast<void(__cdecl*)(int, CompassType, rectDef_s*, rectDef_s*, const float*)>(0x82264A38);
	void(__cdecl* CG_CompassDrawEnemies)(int localClientNum, CompassType compassType, rectDef_s* parent, rectDef_s* rect, const float* color) = reinterpret_cast<void(__cdecl*)(int, CompassType, rectDef_s*, rectDef_s*, const float*)>(0x82265248);
	void(__cdecl* CG_CompassDrawCrates)(int localClientNum, CompassType compassType, rectDef_s* parent, rectDef_s* rect, int Material, float* color) = reinterpret_cast<void(*)(int, CompassType, rectDef_s*, rectDef_s*, int, float*)>(0x82261A60);
	void(__cdecl* CG_CompassDrawBorder)(int localClientNum, CompassType compassType, rectDef_s* parent, rectDef_s* rect, int Material, float* color) = reinterpret_cast<void(*)(int, CompassType, rectDef_s*, rectDef_s*, int, float*)>(0x82261138);
	void(__cdecl* CG_CompassDrawTurrets)(int localClientNum, CompassType compassType, rectDef_s* parent, rectDef_s* rect, float* color) = reinterpret_cast<void(*)(int, CompassType, rectDef_s*, rectDef_s*, float*)>(0x82265AF8);
	void(__cdecl* CG_CompassDrawMissiles)(int localClientNum, CompassType compassType, rectDef_s* parent, rectDef_s* rect, float* color) = reinterpret_cast<void(*)(int, CompassType, rectDef_s*, rectDef_s*, float*)>(0x82266D70);
	void(__cdecl* CG_CompassDrawHelicopter)(int localClientNum, CompassType compassType, rectDef_s* parent, rectDef_s* rect, float* color) = reinterpret_cast<void(*)(int, CompassType, rectDef_s*, rectDef_s*, float*)>(0x825ED198);
	bool(__cdecl* CG_WorldPosToCompass)(CompassType compassType, cgArray_t* cgameGlob, rectDef_s* mapRect, Vector2& yaw, Vector3& playerWorldPos, Vector3& in, Vector2& out, Vector2& outClipped) = reinterpret_cast<bool(__cdecl*)(CompassType, cgArray_t*, rectDef_s*, Vector2&, Vector3&, Vector3&, Vector2&, Vector2&)>(0x8225FD18);
	void(__cdecl* CG_CompassCalcDimensions)(CompassType compassType, cgArray_t* cGameBlob, Vector2& size, rectDef_s* rect, float* x, float* y, float* w, float* h) = reinterpret_cast<void(*)(CompassType, cgArray_t*, Vector2&, rectDef_s*, float*, float*, float*, float*)>(0x8225F3D8);
	void(__cdecl* CG_CompassUpYawVector)(cgArray_t* cg, Vector2& yaw) = reinterpret_cast<void(*)(cgArray_t*, Vector2&)>(0x82261428);

	void(*R_AddCmdDrawText)(const char* text, int maxChars, void* font, float x, float y, float xScale, float yScale, float rotation, const float* Color, int style) = reinterpret_cast<void(*)(const char*, int, void*, float, float, float, float, float, const float*, int)>(0x8266CEB8);
	void(*R_AddCmdDrawStretchPic)(float x, float y, float w, float h, float s0, float t0, float s1, float t1, const float* Color, void* material) = reinterpret_cast<void(*)(float, float, float, float, float, float, float, float, const float*, void*)>(0x8266AF28);
	int(*R_RegisterFont)(const char* font, int imageTrack) = reinterpret_cast<int(*)(const char*, int)>(0x8264DBF0);
	int(*Material_RegisterHandle)(const char* name, int imageTrack) = reinterpret_cast<int(*)(const char*, int)>(0x8265A470);
	bool(*Dvar_GetBool)(const char* dvarName) = reinterpret_cast<bool(*)(const char*)>(0x825639B0);
	int(*Dvar_GetInt)(const char* dvarName) = reinterpret_cast<int(*)(const char*)>(0x82563A18);
	void* (*Cbuf_AddText)(int localClientNum, const char* text) = reinterpret_cast<void* (*)(int, const char*)>(0x8244C738);
	const char* (__cdecl* Dvar_GetString)(const char* Text) = reinterpret_cast<const char* (__cdecl*)(const char*)>(0x82563AF0);
	void(__cdecl* FireBulletPenetrate)(int localClientNum, BulletFireParams* bp, int weaponIndex, int unk, Centity_t* attacker, int unk2, float* tracerStart, bool drawTracer) = reinterpret_cast<void(__cdecl*)(int localClientNum, BulletFireParams* bp, int weaponIndex, int unk,                                                                                                                                                                               Centity_t* attacker, int unk2, float* tracerStart, bool drawTracer)>(0x822C7518);
	void(__cdecl* BG_GetSpreadForWeapon)(cgArray_t* LocalClient, int Weapon, float* min, float* max) = reinterpret_cast<void(__cdecl*)(cgArray_t* LocalClient, int Weapon, float* min, float* max)>(0x82254700);
	bool(__cdecl* Aimtarget_isTargetVisible)(int localclient, pCentity_t centity, unsigned int visBone) = reinterpret_cast<bool(__cdecl*)(int, pCentity_t, unsigned int)>(0x8213A168);
	int(__cdecl* SL_GetString)(const char*, int usr) = reinterpret_cast<int(__cdecl*)(const char*, int)>(0x824934A8);
	void(__cdecl* CG_DrawRotatedPicPhysical)(int, float, float, float, float, float, float*, int) = reinterpret_cast<void(__cdecl*)(int, float, float, float, float, float, float*, int)>(0x82270138);
	void(__cdecl* CG_GetPlayerViewOrigin)(int localClientNum, cgArray_t* cg, Vector3& origin) = reinterpret_cast<void(__cdecl*)(int, cgArray_t*, Vector3&)>(0x822BC078);
	int(*Aimtarget_GetTagPos)(int localClientNum, pCentity_t TheEnt, short tag, Vector3& out) = reinterpret_cast<int(*)(int unknown, pCentity_t, short, Vector3&)>(0x821379E0);
	int(__cdecl* R_TextWidth)(const char* text, int maxchars, int font) = reinterpret_cast<int(__cdecl*)(const char*, int, int)>(0x8264DC78);
	int(*R_TextHeight)(int font) = reinterpret_cast<int(*)(int)>(0x8264DD70);
	float(__cdecl* CG_GoodRandomFloat)(int* seed) = reinterpret_cast<float(__cdecl*)(int*)>(0x8222EC70);
	int(__cdecl* BG_GetWeaponDef)(unsigned int weaponIndex) = reinterpret_cast<int(__cdecl*)(unsigned int)>(0x826BF988);
	char* (*va)(char* format, ...) = reinterpret_cast<char* (*)(char*, ...)>(0x8256E970);
	void(*CG_GameMessage)(int localClientNum, const char* msg) = reinterpret_cast<void(*)(int, const char*)>(0x82282090);
	void(*CG_GameMessageBold)(int localClientNum, const char* msg) = reinterpret_cast<void(*)(int, const char*)>(0x822820F0);
	void(*CL_SubtitlePrint)(int localClientNum, const char* msg, int duration, int lineWidth) = reinterpret_cast<void(*)(int, const char*, int, int)>(0x822CCCC8);
	bool(__cdecl* AimTarget_IsTargetValid)(cgArray_t* cgameGlob, pCentity_t targetEnt) = reinterpret_cast<bool(*)(cgArray_t*, pCentity_t)>(0x82139F18);
	void(*CG_LocationalTrace)(trace_t* results, Vector3* start, Vector3* end, int passEntityNum, int contentMask) = reinterpret_cast<void(*)(trace_t * results, Vector3 * start, Vector3 * end, int passEntityNum, int contentMask)>(0x822CB3B0);
	void(*CG_DrawGrenadePointer)(int localClientNum, float centerX, float centerY, Vector3& grenadeOffset, float* color, float radiusOffset, float scaleFactor) = reinterpret_cast<void(*)(int, float, float, Vector3&, float*, float, float)>(0x822679A8);
	int(*Key_isDown)(int ClientNum, int ButtonEnum) = reinterpret_cast<int(*)(int, int)>(0x822D6E90);
	char* (__cdecl* UI_GetMapDisplayName)(const char* mapname) = reinterpret_cast<char* (*)(const char*)>(0x82527AD0);
	char* (__cdecl* UI_GetGameTypeDisplayName)(const char* gametype) = reinterpret_cast<char* (*)(const char*)>(0x82527CF8);
	void(__cdecl* CG_GetRankIcon)(int rank, int prestige, Material** material) = reinterpret_cast<void(__cdecl*)(int, int, Material**)>(0x822E6670);
	void(__cdecl* CG_DrawRotatedPicInt)(int scrPlace, float x, float y, float width, float height, int horzAlign, int vertAlign, float angle, const float* color, int material) = reinterpret_cast<void(__cdecl*)(int, float, float, float, float, int, int, float, const float*, int)>(0x822702F0);
	bool(__cdecl* ShowPopupGettingData)(int localClientNum) = reinterpret_cast<bool(*)(int)>(0x82456710);
	char* (__cdecl* CL_GetConfigString)(int r1) = reinterpret_cast<char* (*)(int)>(0x822CCD48);
	int(__cdecl* sub_82217CF0)(int a1, __int64 a2, DWORD* a3) = reinterpret_cast<int(*)(int, __int64, DWORD*)>(0x82217CF0);

	inline int TextWidth(const char* text, const char* font) {
		return R_TextWidth(text, 0x7FFFFFFF, R_RegisterFont(font, 0));
	}

	inline int TextHeight(const char* font) {
		return R_TextHeight(R_RegisterFont(font, 0));
	}

	inline bool checkLocalClient(int i) {
		return i == cg->ClientNumber;
	}

	inline bool isAliens()
	{
		return !strcmp(cgs->GameType, "aliens");
	}

	inline bool checkFFAMode() {
		if (cgs->GameType == "oic" || cgs->GameType == "dm") return true;
		return false;
	}

	inline bool notTeam(int i) {
		return (cg->ClientInfo[cg->ClientNumber].Team != cg->ClientInfo[i].Team || cg->ClientInfo[i].Team == 0);
	}

	inline int ValidPlayerCount() {
		auto count = 0;
		for (auto i = 0; i < cgs->maxClients; i++) {
			if (Centity_s[i].State & 0x40) count++;
		}
		return count;
	};

	inline char* getIpAsString(int i) {
		if (i == cg->ClientNumber) partydata.partyMembers[i].ExternalIP.ip1 = 0x00, partydata.partyMembers[i].ExternalIP.ip2 = 0x00, partydata.partyMembers[i].ExternalIP.ip3 = 0x00, partydata.partyMembers[i].ExternalIP.ip4 = 0x00;
		return va("%d.%d.%d.%d", partydata.partyMembers[i].ExternalIP.ip1, partydata.partyMembers[i].ExternalIP.ip2, partydata.partyMembers[i].ExternalIP.ip3, partydata.partyMembers[i].ExternalIP.ip4);
	}

	inline bool bypassEntAliens(int type)
	{
		switch (type)
		{
		case ET_GENERAL:
		case ET_PLAYER:
		case ET_PLAYER_CORPSE:
		case ET_ITEM:
		case ET_MISSLE:
		case ET_INVISIBLE:
		case ET_SCRIPTMOVER:
		case ET_SOUND_BLEND:
		case ET_FX:
		case ET_LOOP_FX:
		case ET_PRIMARY_LIGHT:
		case ET_TURRET:
		case ET_HELICOPTER:
		case ET_PLANE:
		case ET_VEHICLE:
		case ET_VEHICLE_COLLMAP:
		case ET_VEHICLE_CORPSE:
		case ET_VEHICLE_SPAWNER:
		case ET_EVENTS:
			return true;
		default:
			return false;
		}
	}
}