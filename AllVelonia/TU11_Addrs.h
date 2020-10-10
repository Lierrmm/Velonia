#ifndef TU11_ADDRS_H
#define TU11_ADDRS_H

namespace TU11
{
	
    int(__cdecl* R_TextHeight)(void* font) = reinterpret_cast<int(__cdecl*)(void*)>(0x82455880);
	int(__cdecl* R_TextWidth)(const char* text, int maxchars, void* font) = reinterpret_cast<int(__cdecl*)(const char*, int, void*)>(0x82584A90);
	int(__cdecl* SL_GetString)(char* str, int user, int inst) = reinterpret_cast<int(__cdecl*)(char*, int, int)>(0x8242A158);
	void(*Cbuf_AddText)(int localClientNum, const char* text) = reinterpret_cast<void(*)(int, const char*)>(0x8230FD58);
	int(__cdecl* BG_GetWeaponDef)(unsigned int weaponIndex) = reinterpret_cast<int(__cdecl*)(unsigned int)>(0x82144C48);
	int(*Com_GetClientDObj)(int r3, int r4) = reinterpret_cast<int(*)(int, int)>(0x82317D10);
    bool(*CG_DObjGetWorldTagPos)(Centity_t* r3, int r4, int r5, Vector3& r6) = reinterpret_cast<bool(*)(Centity_t*, int, int, Vector3&)>(0x82172E88);

	char* (__cdecl* UI_GetMapDisplayName)(const char* mapname) = reinterpret_cast<char* (*)(const char*)>(0x8233AFC0);
    char* (__cdecl* UI_GetGameTypeDisplayName)(const char* gametype) = reinterpret_cast<char* (*)(const char*)>(0x82337060);

	PCHAR(*va)(PCHAR format, ...) = reinterpret_cast<PCHAR(*)(PCHAR, ...)>(0x82385D30);
    int(*Dvar_GetInt)(const char* dvarName) = reinterpret_cast<int(*)(const char*)>(0x82379860);
    void(*CG_GameMessage)(int localClientNum, const char* msg) = reinterpret_cast<void(*)(int, const char*)>(0x823FBED0);
    void(*CG_GameMessageBold)(int localClientNum, const char* msg) = reinterpret_cast<void(*)(int, const char*)>(0x823FBFF0);
    bool(*Dvar_GetBool)(const char* dvarName) = reinterpret_cast<bool(*)(const char*)>(0x823797D8);


	//float(__cdecl* CG_GoodRandomFloat)(int* seed) = reinterpret_cast<float(__cdecl*)(int*)>(0x822AC660);
    const char* (*Dvar_GetString)(const char* dvarName) = reinterpret_cast<const char* (*)(const char*)>(0x82379CF8);
    void* (*Material_RegisterHandle)(const char* r3, int r4) = reinterpret_cast<void* (*)(const char*, int)>(0x82585308);
    void* (*R_RegisterFont)(const char* r3, int r4) = reinterpret_cast<void* (*)(const char*, int)>(0x82584A48);
    void* (*R_AddCmdDrawText)(const char* r3, int r4, void* r5, float f1, float f2, float f3, float f4, float f5, const float* color, int style) = reinterpret_cast<void* (*)(const char* r3, int r4, void* r5, float f1, float f2, float f3, float f4, float f5, const float* color, int style)>(0x82586DC0);
    void* (*R_AddCmdDrawStretchPic)(float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, const float* color, void* material) = reinterpret_cast<void* (*)(float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, const float* color, void* material)>(0x82586928);
    void(__cdecl* CG_DrawRotatedPicPhysical)(int, float, float, float, float, float, float*, void*) = reinterpret_cast<void(__cdecl*)(int, float, float, float, float, float, float*, void*)>(0x8216CD58);
    void(__cdecl* CG_GetRankIcon)(int rank, int prestige, Material** material) = reinterpret_cast<void(__cdecl*)(int, int, Material**)>(0x823DF2C8);
    int(__cdecl* String_Parse)(const char** p, char* out, int len) = reinterpret_cast<int(*)(const char**, char*, int)>(0x82341268);
    char* (__cdecl* Dvar_GetVariantString)(const char* dvarName) = reinterpret_cast<char* (*)(const char*)>(0x82379D90);
    char* (__cdecl* CL_GetConfigString)(int r1) = reinterpret_cast<char* (*)(int)>(0x823CB000);
    int(__cdecl* I_stricmp)(const char* s0, const char* s1) = reinterpret_cast<int(*)(const char*, const char*)>(0x823857B8);
    //int(__cdecl* CG_irand)(int min, int max) = reinterpret_cast<int(*)(int, int)>(0x821C9470);
    //bool(__cdecl* AimTarget_IsTargetVisible)(int localClientNum, Centity_t* targetEnt, unsigned int visBone) = reinterpret_cast<bool(*)(int, Centity_t*, unsigned int)>(0x82158490);
    //bool(__cdecl* AimTarget_IsTargetValid)(cgArray_t* cgameGlob, Centity_t* targetEnt) = reinterpret_cast<bool(*)(cgArray_t*, Centity_t*)>(0x82158028);
    void(__cdecl* BG_GetSpreadForWeapon)(cgArray_t* LocalClient, int Weapon, float* min, float* max) = reinterpret_cast<void(*)(cgArray_t*, int, float*, float*)>(0x8213AB60);

	//TODO
	/*
	void(*CG_DrawWarningPointer)(int localClientNum, float centerX, float centerY, Vector3& grenadeOffset, float* color, float radiusOffset) = reinterpret_cast<void(*)(int, float, float, Vector3&, float*, float)>(0x821AFD58);
    void(*CG_DrawWarningIcon)(int localClientNum, float centerX, float centerY, Vector3& grenadeOffset, float* color, void* material, float radiusOffset) = reinterpret_cast<void(*)(int, float, float, Vector3&, float*, void*, float)>(0x821AFF40);
	int(*Key_isDown)(int ClientNum, int ButtonEnum) = reinterpret_cast<int(*)(int, int)>(0x82141300);
    
    void(__cdecl* FireBulletPenetrate)(int LocalClient, BulletFireParams* bullet, int Weapon, CEntity* MyCentity, int minus_1_param, float* tracerStart, bool drawTracer) = reinterpret_cast<void(__cdecl*)(int LocalClient, BulletFireParams * bullet, int Weapon, CEntity * MyCentity, int minus_1_param, float* tracerStart, bool drawTracer)>(0x82134648);
    void(__cdecl* CG_GetPlayerViewOrigin)(int localClientNum, cg_t* cg, Vector3& origin) = reinterpret_cast<void(__cdecl*)(int, cg_t*, Vector3&)>(0x8212E670);
    void(*CG_LocationalTrace)(trace_t* results, Vector3* start, Vector3* end, int passEntityNum, int contentMask) = reinterpret_cast<void(*)(trace_t * results, Vector3 * start, Vector3 * end, int passEntityNum, int contentMask)>(0x82136E88);
    void(__cdecl* CG_CompassCalcDimensions)(CompassType compassType, cg_t* cgameGlob, Vector2& size, rectDef_s* rect, float* x, float* y, float* w, float* h) = reinterpret_cast<void(*)(CompassType, cg_t*, Vector2&, rectDef_s*, float*, float*, float*, float*)>(0x820EB278);
    void(__cdecl* CG_CompassUpYawVector)(cg_t* cg, Vector2& yaw) = reinterpret_cast<void(*)(cg_t*, Vector2&)>(0x820ECD00);
    bool(__cdecl* CG_WorldPosToCompass)(CompassType compassType, cg_t* cgameGlob, rectDef_s* mapRect, Vector2& yaw, Vector3& playerWorldPos, Vector3& in, Vector2& out, Vector2& outClipped) = reinterpret_cast<bool(__cdecl*)(CompassType, cg_t*, rectDef_s*, Vector2&, Vector3&, Vector3&, Vector2&, Vector2&)>(0x820EB0A0);
    void(*CG_CompassDrawPlayerMap)(int localClientNum, CompassType compassType, Vector2& size, rectDef_s* rect, void* material, float* color) = reinterpret_cast<void(*)(int, CompassType, Vector2&, rectDef_s*, void*, float*)>(0x820EC0C8);
    void(__cdecl* CG_CompassDrawPlayer)(int localClientNum, CompassType compassType, rectDef_s* parentRect, rectDef_s* rect, void* material, float* color) = reinterpret_cast<void(*)(int, CompassType, rectDef_s*, rectDef_s*, void*, float*)>(0x820EC7A0);
    void(__cdecl* CG_CompassDrawFriendlies)(int localClientNum, CompassType compassType, rectDef_s* parent, rectDef_s* rect, float* color) = reinterpret_cast<void(*)(int, CompassType, rectDef_s*, rectDef_s*, float*)>(0x820EE938);
    void(__cdecl* CG_CompassDrawEnemies)(int localClientNum, CompassType compassType, rectDef_s* parent, rectDef_s* rect, float* color) = reinterpret_cast<void(*)(int, CompassType, rectDef_s*, rectDef_s*, float*)>(0x820EEFA8);
    void(__cdecl* CG_CompassDrawPlanes)(int localClientNum, CompassType compassType, rectDef_s* parent, rectDef_s* rect, float* color) = reinterpret_cast<void(*)(int, CompassType, rectDef_s*, rectDef_s*, float*)>(0x820EFEA0);
    void(__cdecl* CG_CompassDrawSentry)(int localClientNum, CompassType compassType, rectDef_s* parent, rectDef_s* rect, float* color) = reinterpret_cast<void(*)(int, CompassType, rectDef_s*, rectDef_s*, float*)>(0x820EF3B8);
    
    */


    inline int TextWidth(const char* text, const char* font) {
        return R_TextWidth(text, 0x7FFFFFFF, R_RegisterFont(font, 0));
    }

    inline int TextHeight(const char* font) {
        return R_TextHeight(R_RegisterFont(font, 0));
    }

    inline bool checkLocalClient(int i) {
        return i == cg->ClientNumber;
    }

    inline bool checkFFAMode() {
        return false;
    }

    inline bool notTeam(int i) {
        return (cg->ClientInfo[cg->ClientNumber].team != cg->ClientInfo[i].team || cg->ClientInfo[i].team == 0);
    }

    inline int ValidPlayerCount() {
        auto count = 0;
        for (auto i = 0; i < cgs->maxclients; i++) {
            if (cg->ClientInfo[i].infoValid) count++;
        }
        return count;
    };

    /*char* getIpAsString(int i) {
        if (i == cg->ClientNumber) clientIps[i]->ip1 = 0x00, clientIps[i]->ip2 = 0x00, clientIps[i]->ip3 = 0x00, clientIps[i]->ip4 = 0x00;
        return va("%d.%d.%d.%d", clientIps[i]->ip1, clientIps[i]->ip2, clientIps[i]->ip3, clientIps[i]->ip4);
    }*/
}
#endif // TU11_ADDRS_H
