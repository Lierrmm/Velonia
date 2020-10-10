#ifndef TU7_ADDRS_H
#define TU7_ADDRS_H

namespace TU7
{
	void* (*R_RegisterFont)(const char* r3, int r4) = reinterpret_cast<void* (*)(const char*, int)>(0x821B7E40);
	void* (*R_AddCmdDrawText)(const char* r3, int r4, void* r5, float f1, float f2, float f3, float f4, float f5, const float* color, int something) = reinterpret_cast<void* (*)(const char* r3, int r4, void* r5, float f1, float f2, float f3, float f4, float f5, const float* color, int something)>(0x82401C30);
	int(__cdecl* UI_TextWidth)(const char* text, int maxChars, int* font, float scale) = reinterpret_cast<int(__cdecl*)(const char* text, int maxChars, int* font, float scale)>(0x8229B6E0);
	int(__cdecl* UI_TextHeight)(int* font, float scale) = reinterpret_cast<int(__cdecl*)(int* font, float scale)>(0x8229B748);
	int(__cdecl* R_TextWidth)(const char* text, int maxchars, void* font) = reinterpret_cast<int(__cdecl*)(const char*, int, void*)>(0x823FFF28);
	int(__cdecl* R_TextHeight)(void* font) = reinterpret_cast<int(__cdecl*)(void* font)>(0x82400018);
	void(*R_AddCmdDrawTextWithEffects)(const char* text, int maxChars, void* font, float x, float y, float xScale, float yScale, float rotation, const float* color, int style, const float* glowColor, void* fxMaterial, void* fxMaterialGlow, int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int fxDecayDuration) = reinterpret_cast<void(*)(const char* text, int maxChars, void* font, float x, float y, float xScale, float yScale, float rotation, const float* color, int style, const float* glowColor, void* fxMaterial, void* fxMaterialGlow, int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int fxDecayDuration)>(0x82401F48);
	void(*DrawText2D)(const char* text, float x, float y, void* font, float xScale, float yScale, float sinAngle, float cosAngle, float* color, int maxLength, int renderFlags, int cursorPos, char cursorLetter, float padding, float* glowForcedColor, int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int fxDecayDuration, void* fxMaterial, void* fxMaterialGlow) = reinterpret_cast<void(*)(const char*, float, float, void*, float, float, float, float, float*, int, int, int, char, float, float*, int, int, int, int, void*, void*)>(0x82414E28);
	void* (*Material_RegisterHandle)(const char* r3, int r4) = reinterpret_cast<void* (*)(const char*, int)>(0x824006F0);
	int(*Material_RegisterHandleInt)(const char* r3, int r4) = reinterpret_cast<int(*)(const char*, int)>(0x824006F0);
	void* (*R_AddCmdDrawStretchPic)(float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, const float* color, void* material) = reinterpret_cast<void* (*)(float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, const float* color, void* material)>(0x82401410);
	void(*CG_GameMessage)(int localClientNum, const char* msg) = reinterpret_cast<void(*)(int, const char*)>(0x8216EC68);
	void(*CG_GameMessageBold)(int localClientNum, const char* msg) = reinterpret_cast<void(*)(int, const char*)>(0x8216EC88);
	void(*Cbuf_AddText)(int localClientNum, const char* text) = reinterpret_cast<void(*)(int, const char*)>(0x8226FF08);
	int(*Dvar_GetInt)(const char* dvarName) = reinterpret_cast<int(*)(const char*)>(0x822BE158);
	bool(*Dvar_GetBool)(const char* dvarName) = reinterpret_cast<bool(*)(const char*)>(0x822BE0E8);
	const char* (*Dvar_GetString)(const char* dvarName) = reinterpret_cast<const char* (*)(const char*)>(0x822BE230);
	float (*Dvar_GetFloat)(char const* dvarName) = reinterpret_cast<float(*)(const char*)>(0x822BE1C0);
	void(*CL_Disconnect)(int localClientNum) = reinterpret_cast<void(*)(int)>(0x821B5088);
	void(*CG_DrawClientPing)(int localClientNum, int ping, float x, float y, float maxWidth, float maxHeight) = reinterpret_cast<void(*)(int, int, float, float, float, float)>(0x82180698);
	void(*CG_DrawOverheadNames)(int localClientNum, Centity_t* ent, float alpha) = reinterpret_cast<void(*)(int, Centity_t*, float)>(0x82159B48);
	void(*ClientUserInfoChanged)(int localClientNum) = reinterpret_cast<void(*)(int)>(0x8220A8E0);
	void(*toggleConsole)() = reinterpret_cast<void(*)()>(0x821A99F0);
	void(*Sys_ShowIP)() = reinterpret_cast<void(*)()>(0x822E5AE8);
	void(*SendCommandToConsole)(int localClientNum, const char* text) = reinterpret_cast<void(*)(int, const char*)>(0x82270D68);
	//int(__cdecl* SL_GetString)(char*, int usr) = reinterpret_cast<int(__cdecl*)(char*, int)>(0x8233B7A0);
	int(*Com_GetClientDObj)(int r3, int r4) = reinterpret_cast<int(*)(int, int)>(0x822758E8);
	bool(*CG_DObjGetWorldTagPos)(Centity_t* r3, int r4, int r5, Vector3& r6) = reinterpret_cast<bool(*)(Centity_t*, int, int, Vector3&)>(0x82161EA8);
	//int(*AimTarget_GetTagPos)(int localClientNum, Centity_t* cent, short tagName, Vector3& pos) = reinterpret_cast<int(*)(int, Centity_t*, short, Vector3&)>(0x82123C08);
	static void(__cdecl* CG_DrawRotatedPicPhysical)(int, float, float, float, float, float, float*, void*) = reinterpret_cast<void(__cdecl*)(int, float, float, float, float, float, float*, void*)>(0x8215CEC0);
	void(*BG_GetSpreadForWeapon)(cg_t* pps, int weaponinfo, float* minspread, float* maxspread) = reinterpret_cast<void(*)(cg_t*, int, float*, float*)>(0x82141650);
	void(*Bullet_RandomDir)(int seed, float* x, float* y) = reinterpret_cast<void(*)(int, float*, float*)>(0x822046D0);
	static void(*CG_DrawGrenadePointer)(int localClientNum, float centerX, float centerY, Vector3& grenadeOffset, float* color, const float radiusOffset, const float scaleFactor) = reinterpret_cast<void(*)(int, float, float, Vector3&, float*, float, float)>(0x82156838);
	static void(*CG_CompassDrawPlayerMap)(int localClientNum, CompassType compassType, rectDef_s* parentRect, rectDef_s* rect, void* material, float* color) = reinterpret_cast<void(*)(int, CompassType, rectDef_s*, rectDef_s*, void*, float*)>(0x82150B48);
	void(__cdecl* CG_CompassDrawFriendlies)(int localClientNum, CompassType compassType, rectDef_s* parentRect, rectDef_s* rect, float* color) = reinterpret_cast<void(*)(int, CompassType, rectDef_s*, rectDef_s*, float*)>(0x82153828);
	void(__cdecl* CG_CompassDrawEnemies)(int localClientNum, CompassType compassType, rectDef_s* parentRect, rectDef_s* rect, float* color) = reinterpret_cast<void(*)(int, CompassType, rectDef_s*, rectDef_s*, float*)>(0x82154680);
	void(__cdecl* CG_CompassDrawVehicles)(int localClientNum, CompassType compassType, int eType, rectDef_s* parentRect, rectDef_s* rect, void* enemyMaterial, void* friendlyMaterial, const float* color) = reinterpret_cast<void(*)(int, CompassType, int, rectDef_s*, rectDef_s*, void*, void*, const float*)>(0x82154DD8);
	void(__cdecl* CG_CompassDrawVehicles_0)(int localClientNum, CompassType compassType, int eType, rectDef_s* parentRect, rectDef_s* rect, void* enemyMaterial, void* friendlyMaterial, const float* color) = reinterpret_cast<void(*)(int, CompassType, int, rectDef_s*, rectDef_s*, void*, void*, const float*)>(0x821553A0);
	void(__cdecl* CG_CompassDrawPlayer)(int localClientNum, CompassType compassType, rectDef_s* parentRect, rectDef_s* rect, void* material, float* color) = reinterpret_cast<void(*)(int, CompassType, rectDef_s*, rectDef_s*, void*, float*)>(0x821510A0);
	void(__cdecl* CG_CompassDrawBorder)(int localClientNum, CompassType compassType, rectDef_s* parentRect, rectDef_s* rect, void* material, float* color) = reinterpret_cast<void(*)(int, CompassType, rectDef_s*, rectDef_s*, void*, float*)>(0x82151300);
	int (*CG_GetWeaponIndexForName)(const char* name) = reinterpret_cast<int(*)(const char*)>(0x82144FF8);
	int (*Key_Down)(int localClientNum, int buttonEnum) = reinterpret_cast<int(*)(int, int)>(0x821B2908);
	int(__cdecl* CL_GetCurrentCmdNumber)(int localClientNum) = reinterpret_cast<int(*)(int)>(0x821A4108);
	unsigned int(__cdecl* GScr_AllocString)(const char*) = reinterpret_cast<unsigned int(__cdecl*)(const char*)>(0x8222D368);
	const char* (__cdecl* Con_GetVersionString)() = reinterpret_cast<const char* (*)()>(0x821AB0A8);
	char* (__cdecl* getBuildNumber)() = reinterpret_cast<char* (*)()>(0x82264298);
	void(__cdecl* CG_GetRankIcon)(int rank, int prestige, Material** mat) = reinterpret_cast<void(*)(int, int, Material**)>(0x821BE9F8);
	bool(*CG_WorldPosToCompass)(CompassType compassType, cg_t* cgameGlob, rectDef_s* mapRect, const float* north, const float* playerWorldPos, const float* in, float* out, float* outClipped) = reinterpret_cast<bool(*)(CompassType, cg_t*, rectDef_s*, const float*, const float*, const float*, float*, float*)>(0x8214FB20);
	Vector3(*CL_GetMapCenter)() = reinterpret_cast<Vector3(*)()>(0x821B7E70);
	char* (__cdecl* UI_GetMapDisplayName)(const char* mapname) = reinterpret_cast<char* (*)(const char*)>(0x8229F7A0);
	char* (__cdecl* UI_GetGameTypeDisplayName)(const char* gametype) = reinterpret_cast<char* (*)(const char*)>(0x8229FA18);
	int(__cdecl* irand)(int min, int max) = reinterpret_cast<int(*)(int, int)>(0x822B8290);
	int(__cdecl* RandWithSeed)(int*) = reinterpret_cast<int(*)(int*)>(0x822B5160);
	bool(__cdecl* AimTarget_IsTargetVisible)(int localClientNum, Centity_t* targetEnt, unsigned int visBone) = reinterpret_cast<bool(*)(int, Centity_t*, unsigned int)>(0x82125E70);
	bool(__cdecl* AimTarget_IsTargetValid)(cg_t* cgameGlob, Centity_t* targetEnt) = reinterpret_cast<bool(*)(cg_t*, Centity_t*)>(0x82125960);
	static void(__cdecl* CG_GetPlayerViewOrigin)(int localClientNum, cg_t* cg, Vector3& origin) = reinterpret_cast<void(__cdecl*)(int, cg_t* cg, Vector3&)>(0x8219BD50);
	static void(*CG_LocationalTrace)(trace_t* results, Vector3* start, Vector3* end, int passEntityNum, int contentMask) = reinterpret_cast<void(*)(trace_t* results, Vector3* start, Vector3* end, int passEntityNum, int contentMask)>(0x821A2C58);
	int(__cdecl* CG_PlayClientSoundAliasByName)(int localClientNum, const char* aliasname) = reinterpret_cast<int(*)(int, const char*)>(0x821717B0);
	PCHAR(*va)(PCHAR format, ...) = reinterpret_cast<PCHAR(*)(PCHAR, ...)>(0x822C38D8);
	unsigned int(*__cdecl SL_FindLowercaseString)(const char* tagName) = reinterpret_cast<unsigned int(*)(const char*)>(0x8233B1C8);
	char* (*SL_ConvertToString)(unsigned int stringValue) = reinterpret_cast<char* (*)(unsigned int)>(0x8233AD40);
	int(*SL_GetStringOfSize)(int localClientNum, char* txt, int type, unsigned int len) = reinterpret_cast<int(*)(int, char*, int, unsigned int)>(0x8233B2D8);
	void(__cdecl* FireBulletPenetrate)(int LocalClient, BulletFireParams* bullet, int Weapon, Centity_t* MyCentity, float* viewOrg, bool drawTracer) = reinterpret_cast<void(__cdecl*)(int LocalClient, BulletFireParams* bullet, int Weapon, Centity_t* MyCentity, float* viewOrg, bool drawTracer)>(0x8219F6D0);

	inline int SL_GetString(char* tag, int localClientNum)
	{
		return SL_GetStringOfSize(localClientNum, tag, 2, strlen(tag) + 1);
	}
	
	inline bool Aimtarget_GetTagPos(int cen, int tag, Vector3& tagpos) {
		auto meh = Com_GetClientDObj(cen, 0);

		if (meh == 0) {
			return false;
		}

		return CG_DObjGetWorldTagPos(&Centity_s[cen], meh, tag, tagpos);
	}

	inline int TextWidth(const char* text, const char* font) {
		return R_TextWidth(text, 0x7FFFFFFF, R_RegisterFont(font, 0));
	}

	inline int TextHeight(const char* font) {
		return R_TextHeight(R_RegisterFont(font, 0));
	}

	inline bool checkLocalClient(int i) {
		return i == cg->clientNum;
	}

	inline bool checkFFAMode() {
		if (cgs->GameType == "oic" || cgs->GameType == "dm") return true;
		return false;
	}

	inline bool notTeam(int i) {
		return (cg->ClientInfo[cg->clientNum].mTeam != cg->ClientInfo[i].mTeam || cg->ClientInfo[i].mTeam == 0);
	}

	inline int ValidPlayerCount() {
		auto count = 0;
		for (auto i = 0; i < cgs->maxClients; i++) {
			if (cg->ClientInfo[i].mValid) count++;
		}
		return count;
	};

	/*inline char* getIpAsString(int i) {
		if (i == cg->clientNum) partydata.partyMembers[i].ExternalIP.ip1 = 0x00, partydata.partyMembers[i].ExternalIP.ip2 = 0x00, partydata.partyMembers[i].ExternalIP.ip3 = 0x00, partydata.partyMembers[i].ExternalIP.ip4 = 0x00;
		return va("%d.%d.%d.%d", partydata.partyMembers[i].ExternalIP.ip1, partydata.partyMembers[i].ExternalIP.ip2, partydata.partyMembers[i].ExternalIP.ip3, partydata.partyMembers[i].ExternalIP.ip4);
	}*/

	inline char* getIpAsString(int i)
	{
		return va("%d.%d.%d.%d", partydata.partyMembers[i].ExternalIP.ip1, partydata.partyMembers[i].ExternalIP.ip2, partydata.partyMembers[i].ExternalIP.ip3, partydata.partyMembers[i].ExternalIP.ip4);
	}
}
#endif // TU7_ADDRS_H
