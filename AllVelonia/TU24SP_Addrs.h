#ifndef TU24SP_ADDRS_H
#define TU24SP_ADDRS_H

namespace TU24SP
{
	bool(*Dvar_GetBool)(const char* dvarName) = reinterpret_cast<bool(*)(const char*)>(0x82304420);
	float(*Dvar_GetFloat)(const char* dvarName) = reinterpret_cast<float(*)(const char*)>(0x823044F0);
	int(*Dvar_GetInt)(const char* dvarName) = reinterpret_cast<int(*)(const char*)>(0x82304488);
	int(*CL_IsLocalClientInGame)(int localClientNum) = reinterpret_cast<int(*)(int)>(0x821233B8);

	void(*CG_GameMessage)(int localClientNum, const char* msg) = reinterpret_cast<void(*)(int, const char*)>(0x820E37D8);
	void(*CG_GameMessageBold)(int localClientNum, const char* msg) = reinterpret_cast<void(*)(int, const char*)>(0x820E37F8);
	void(*CL_SubtitlePrint)(int localClientNum, const char* text, int duration, int pixelWidth) = reinterpret_cast<void(*)(int, const char*, int, int)>(0x82118628);

	int(__cdecl* R_TextWidth)(const char* text, int maxchars, void* font) = reinterpret_cast<int(__cdecl*)(const char*, int, void*)>(0x823DD318	);
	int(__cdecl* R_TextHeight)(void* font) = reinterpret_cast<int(__cdecl*)(void*)>(0x823DD320);
	void* (*R_RegisterFont)(const char* r3, int r4) = reinterpret_cast<void* (*)(const char*, int)>(0X823DD130);
	void* (*R_AddCmdDrawText)(const char* text, int maxChars, void* font, float x, float y, float xScale, float yScale, float rotation, const float* color, int style) = reinterpret_cast<void* (*)(const char* r3, int r4, void* r5, float f1, float f2, float f3, float f4, float f5, const float* color, int something)>(0x823F5158);
	PCHAR(*va)(PCHAR format, ...) = reinterpret_cast<PCHAR(*)(PCHAR, ...)>(0x8230C428);
	void* (*R_AddCmdDrawStretchPic)(float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, const float* color, void* material) = reinterpret_cast<void* (*)(float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, const float* color, void* material)>(0x823F4878);
	void* (*Material_RegisterHandle)(const char* r3, int r4) = reinterpret_cast<void* (*)(const char*, int)>(0x823E95E8);
	int (*Material_RegisterHandleInt)(const char* r3, int r4) = reinterpret_cast<int(*)(const char*, int)>(0x823E95E8);

	bool (*CG_WorldPosToScreenPosReal)(int localClientNumber, int scr, Vector3& worldPos, Vector2& outScreenPos) = reinterpret_cast<bool(*)(int, int, Vector3&, Vector2&)>(0x820D6828);
	void(*Cbuf_AddText)(int localClientNum, const char* text) = reinterpret_cast<void(*)(int, const char*)>(0x8228E1F8);
	void(__cdecl* CG_GetPlayerViewOrigin)(int localClientNum, playerstate_s* cg, Vector3& origin) = reinterpret_cast<void(__cdecl*)(int, playerstate_s*, Vector3&)>(0x82110710);
	void(__cdecl* CG_DrawRotatedPicPhysical)(int, float, float, float, float, float, float*, int) = reinterpret_cast<void(__cdecl*)(int, float, float, float, float, float, float*, int)>(0x820D5A18);
	void(*CG_LocationalTrace)(trace_t* results, Vector3* start, Vector3* end, int passEntityNum, int contentMask) = reinterpret_cast<void(*)(trace_t * results, Vector3 * start, Vector3 * end, int passEntityNum, int contentMask)>(0x821172F0);
	short(__cdecl* SL_GetString)(char*, int usr) = reinterpret_cast<short(__cdecl*)(char*, int)>(0x822B2E80);
	void(*CG_DrawGrenadePointer)(int localClientNum, float centerX, float centerY, Vector3& grenadeOffset, float* color, float radiusOffset, float scaleFactor) = reinterpret_cast<void(*)(int, float, float, Vector3&, float*, float, float)>(0x820D30E0);
	char* (__cdecl* Lobby_GetName)(int clientNum) = reinterpret_cast<char* (*)(int)>(0x8212B280);
	int(*Com_GetClientDObj)(int r3, int r4) = reinterpret_cast<int(*)(int, int)>(0x822A00B8);
	bool(*CG_DObjGetWorldTagPos)(CEntity* r3, int r4, int r5, Vector3& r6) = reinterpret_cast<bool(*)(CEntity*, int, int, Vector3&)>(0x820D9578);
	void(__cdecl* BG_GetSpreadForWeapon)(playerstate_s* LocalClient, int Weapon, float* min, float* max) = reinterpret_cast<void(*)(playerstate_s*, int, float*, float*)>(0x82366FD0);
	int(__cdecl* BG_GetWeaponDef)(unsigned int weaponIndex) = reinterpret_cast<int(__cdecl*)(unsigned int)>(0x8235C4D8);
	void(__cdecl* FireBulletPenetrate)(int LocalClient, BulletFireParams* bullet, int Weapon, int r3, CEntity* localEntity, int r4, float* viewOrg, int r5) = reinterpret_cast<void(__cdecl*)(int, BulletFireParams*, int, int, CEntity*, int, float*, int)>(0x821F0978);
	float(__cdecl* CG_GoodRandomFloat)(int* seed) = reinterpret_cast<float(__cdecl*)(int*)>(0x82350110);
	int(*Key_isDown)(int ClientNum, int ButtonEnum) = reinterpret_cast<int(*)(int, int)>(0x82120D38);
	
	inline bool Aimtarget_GetTagPos(int entNum, CEntity* cen, unsigned int tag, Vector3& v1) {
		auto var = Com_GetClientDObj(entNum, 0);
		if (var == 0) return false;
		return CG_DObjGetWorldTagPos(cen, var, tag, v1);
	}
	
	inline bool Aimtarget_isTargetVisible(int entNum, CEntity* cen, int tag) {
        trace_t trace;
        ZeroMemory(&trace, sizeof(trace));
        Vector3 tagpos;
        if (Aimtarget_GetTagPos(entNum, cen, tag, tagpos)) {
            CG_LocationalTrace(&trace, &cg.refdef.Origin, &tagpos, cg.clientNum, 0x803003);
            return trace.fraction >= 0.95f;
		}
        return false;
    }
	
	inline int TextWidth(const char* text, const char* font) {
		return R_TextWidth(text, 0x7FFFFFFF, R_RegisterFont(font, 0));
	}

	inline int TextHeight(const char* font) {
		return R_TextHeight(R_RegisterFont(font, 0));
	}

	inline bool checkLocalClient(int i) {
		return i == cg.clientNum;
	}

	inline char* getIpAsString(int i)
	{
		return "0";
	}

	/*inline char* getIpAsString(int i) {
		if (i == cg->clientNum) partydata.partyMembers[i].ExternalIP.ip1 = 0x00, partydata.partyMembers[i].ExternalIP.ip2 = 0x00, partydata.partyMembers[i].ExternalIP.ip3 = 0x00, partydata.partyMembers[i].ExternalIP.ip4 = 0x00;
		return va("%d.%d.%d.%d", partydata.partyMembers[i].ExternalIP.ip1, partydata.partyMembers[i].ExternalIP.ip2, partydata.partyMembers[i].ExternalIP.ip3, partydata.partyMembers[i].ExternalIP.ip4);
	}*/
}
#endif // TU24SP_ADDRS_H
