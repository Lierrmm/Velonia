namespace TU9
{
    int(__cdecl* R_TextHeight)(void* font) = reinterpret_cast<int(__cdecl*)(void*)>(0x8234DDF0);
    int(__cdecl* R_TextWidth)(const char* text, int maxchars, void* font) = reinterpret_cast<int(__cdecl*)(const char*, int, void*)>(0x8234DD20);
    int(__cdecl* SL_GetString)(char*, int) = reinterpret_cast<int(__cdecl*)(char*, int)>(0x82242250);
    void(*Cbuf_AddText)(int localClientNum, const char* text) = reinterpret_cast<void(*)(int, const char*)>(0x82224990);
    int(__cdecl* BG_GetWeaponDef)(unsigned int weaponIndex) = reinterpret_cast<int(__cdecl*)(unsigned int)>(0x820E22C0);
    int(*Com_GetClientDObj)(int r3, int r4) = reinterpret_cast<int(*)(int, int)>(0x8222FCC0);
    bool(*CG_DObjGetWorldTagPos)(CEntity* r3, int r4, int r5, Vector3& r6) = reinterpret_cast<bool(*)(CEntity*, int, int, Vector3&)>(0x820FB9E8);
    int(*AimTarget_GetTagPos)(int localClientNum, CEntity* cent, short tagName, Vector3& pos) = reinterpret_cast<int(*)(int, CEntity*, short, Vector3&)>(0x820C4458);
    void(*CG_DrawGrenadePointer)(int localClientNum, float centerX, float centerY, Vector3& grenadeOffset, float* color, const float radiusOffset, const float scaleFactor) = reinterpret_cast<void(*)(int, float, float, Vector3&, float*, const float, const float)>(0x820F17F0);
    char* (__cdecl* UI_GetMapDisplayName)(const char* mapname) = reinterpret_cast<char* (*)(const char*)>(0x822729A0);
    PCHAR(*va)(PCHAR format, ...) = reinterpret_cast<PCHAR(*)(PCHAR, ...)>(0x822A7028);
    int(*Dvar_GetInt)(const char* dvarName) = reinterpret_cast<int(*)(const char*)>(0x8229EF50);
    void(*CG_GameMessage)(int localClientNum, const char* msg) = reinterpret_cast<void(*)(int, const char*)>(0x821071D0);
    void(*CG_GameMessageBold)(int localClientNum, const char* msg) = reinterpret_cast<void(*)(int, const char*)>(0x821071F0);
    bool(*Dvar_GetBool)(const char* dvarName) = reinterpret_cast<bool(*)(const char*)>(0x8229EEE8);
    int(*Key_isDown)(int ClientNum, int ButtonEnum) = reinterpret_cast<int(*)(int, int)>(0x82141300);
    void(__cdecl* BG_GetSpreadForWeapon)(cg_t* LocalClient, int Weapon, float* min, float* max) = reinterpret_cast<void(*)(cg_t*, int, float*, float*)>(0x820E33F0);
    void(__cdecl* FireBulletPenetrate)(int LocalClient, BulletFireParams* bullet, int Weapon, CEntity* MyCentity, int minus_1_param, float* tracerStart, bool drawTracer) = reinterpret_cast<void(__cdecl*)(int LocalClient, BulletFireParams * bullet, int Weapon, CEntity * MyCentity,
        int minus_1_param, float* tracerStart, bool drawTracer)>(0x82134648);
    float(__cdecl* CG_GoodRandomFloat)(int* seed) = reinterpret_cast<float(__cdecl*)(int*)>(0x820D76F0);
    void(__cdecl* CG_GetPlayerViewOrigin)(int localClientNum, cg_t* cg, Vector3& origin) = reinterpret_cast<void(__cdecl*)(int, cg_t*, Vector3&)>(0x8212E670);
    const char* (*Dvar_GetString)(const char* dvarName) = reinterpret_cast<const char* (*)(const char*)>(0x8229F0A8);
    void* (*Material_RegisterHandle)(const char* r3, int r4) = reinterpret_cast<void* (*)(const char*, int)>(0x8234E510);
    int(*Material_RegisterHandleInt)(const char* r3, int r4) = reinterpret_cast<int(*)(const char*, int)>(0x8234E510);
    void* (*R_RegisterFont)(const char* r3, int r4) = reinterpret_cast<void* (*)(const char*, int)>(0x8234DCB0);
    void* (*R_AddCmdDrawText)(const char* r3, int r4, void* r5, float f1, float f2, float f3, float f4, float f5, const float* color, int something) = reinterpret_cast<void* (*)(const char* r3, int r4, void* r5, float f1, float f2, float f3, float f4, float f5,
        const float* color, int something)>(0x82350278);
    void* (*R_AddCmdDrawStretchPic)(float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, const float* color, void* material) = reinterpret_cast<void* (*)(float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8,
        const float* color, void* material)>(0x8234F9B8);
    void(*CG_LocationalTrace)(trace_t* results, Vector3* start, Vector3* end, int passEntityNum, int contentMask) = reinterpret_cast<void(*)(trace_t * results, Vector3 * start, Vector3 * end, int passEntityNum, int contentMask)>(
        0x82136E88);
    void(__cdecl* CG_DrawRotatedPicPhysical)(int, float, float, float, float, float, float*, void*) = reinterpret_cast<void(__cdecl*)(int, float, float, float, float, float, float*, void*)>(0x820F7900);
    void(__cdecl* CG_DrawRotatedPicPhysicalInt)(int, float, float, float, float, float, float*, int) = reinterpret_cast<void(__cdecl*)(int, float, float, float, float, float, float*, int)>(0x820F7900);
    void(__cdecl* CG_DrawRotatedPic)(int scrPlace, float x, float y, float width, float height, int horzAlign, int vertAlign, float angle, const float* color, void* material) = reinterpret_cast<void(__cdecl*)(int, float, float, float, float, int, int, float, const float*, void*)>(0x820F7AB0);
    void(__cdecl* CG_DrawRotatedPicInt)(int scrPlace, float x, float y, float width, float height, int horzAlign, int vertAlign, float angle, const float* color, int material) = reinterpret_cast<void(__cdecl*)(int, float, float, float, float, int, int, float, const float*, int)>(0x820F7AB0);
    int(__cdecl* SND_PlayLocalSoundAliasByName)(int localClientNum, const char* aliasname, int system) = reinterpret_cast<int(*)(int, const char*, int)>(0x8232B660);
    char* (__cdecl* UI_GetGameTypeDisplayName)(const char* gametype) = reinterpret_cast<char* (*)(const char*)>(0x82272BD0);
    void(__cdecl* CG_CompassCalcDimensions)(CompassType compassType, cg_t* cgameGlob, Vector2& size, rectDef_s* rect, float* x, float* y, float* w, float* h) = reinterpret_cast<void(*)(CompassType, cg_t*, Vector2&, rectDef_s*, float*, float*, float*, float*)>(0x820EB278);
    void(__cdecl* CG_CompassUpYawVector)(cg_t* cg, Vector2& yaw) = reinterpret_cast<void(*)(cg_t*, Vector2&)>(0x820ECD00);
    bool(__cdecl* CG_WorldPosToCompass)(CompassType compassType, cg_t* cgameGlob, rectDef_s* mapRect, Vector2& yaw, Vector3& playerWorldPos, Vector3& in, Vector2& out, Vector2& outClipped) = reinterpret_cast<bool(__cdecl*)(CompassType, cg_t*, rectDef_s*, Vector2&, Vector3&, Vector3&, Vector2&, Vector2&)>(0x820EB0A0);
    void(*CG_CompassDrawPlayerMap)(int localClientNum, CompassType compassType, Vector2& size, rectDef_s* rect, void* material, float* color) = reinterpret_cast<void(*)(int, CompassType, Vector2&, rectDef_s*, void*, float*)>(0x820EC0C8);
    void(__cdecl* CG_CompassDrawPlayer)(int localClientNum, CompassType compassType, rectDef_s* parentRect, rectDef_s* rect, void* material, float* color) = reinterpret_cast<void(*)(int, CompassType, rectDef_s*, rectDef_s*, void*, float*)>(0x820EC7A0);
    void(__cdecl* CG_CompassDrawFriendlies)(int localClientNum, CompassType compassType, rectDef_s* parent, rectDef_s* rect, float* color) = reinterpret_cast<void(*)(int, CompassType, rectDef_s*, rectDef_s*, float*)>(0x820EE938);
    void(__cdecl* CG_CompassDrawEnemies)(int localClientNum, CompassType compassType, rectDef_s* parent, rectDef_s* rect, float* color) = reinterpret_cast<void(*)(int, CompassType, rectDef_s*, rectDef_s*, float*)>(0x820EEFA8);
    void(__cdecl* CG_CompassDrawPlanes)(int localClientNum, CompassType compassType, rectDef_s* parent, rectDef_s* rect, float* color) = reinterpret_cast<void(*)(int, CompassType, rectDef_s*, rectDef_s*, float*)>(0x820EFEA0);
    void(__cdecl* CG_CompassDrawSentry)(int localClientNum, CompassType compassType, rectDef_s* parent, rectDef_s* rect, float* color) = reinterpret_cast<void(*)(int, CompassType, rectDef_s*, rectDef_s*, float*)>(0x820EF3B8);
    void(__cdecl* R_DrawXModelSkinnedCached)(int context, int xsurf, int skinnedCachedOffset) = reinterpret_cast<void(*)(int, int, int)>(0x823982E0);
    void(__cdecl* CG_GetRankIcon)(int rank, int prestige, Material** material) = reinterpret_cast<void(__cdecl*)(int, int, Material**)>(0x8214BB50);
    bool(__cdecl* AimTarget_IsTargetValid)(cg_t* cgameGlob, CEntity* targetEnt) = reinterpret_cast<bool(*)(cg_t*, CEntity*)>(0x820C5A50);
    int(__cdecl* MSG_ReadBitsCompress)(const char* from, char* to, int size) = reinterpret_cast<int(*)(const char*, char*, int)>(0x822348E8);
    void(__cdecl* CL_DrawStretchPicPhysical)(float x, float y, float w, float h, float s1, float t1, float s2, float t2, const float* color, Material* material) = reinterpret_cast<void(*)(float, float, float, float, float, float, float, float, const float*, Material*)>(0x821384D8);

	
	bool Aimtarget_GetTagPos(pCentity_t cen, unsigned int tag, Vector3& v1) {
        auto var = Com_GetClientDObj(*reinterpret_cast<int*>(reinterpret_cast<int>(cen) + 0xD0), 0);
        if (var == 0) return false;
        return CG_DObjGetWorldTagPos(cen, var, tag, v1);
    }

    bool Aimtarget_isTargetVisible(int clientnum, pCentity_t cen, int tag) {
        trace_t trace;
        ZeroMemory(&trace, sizeof(trace));
        Vector3 tagpos;
        if (Aimtarget_GetTagPos(cen, tag, tagpos)) {
            CG_LocationalTrace(&trace, &cg->refdef.EyePos, &tagpos, cg->cNum, 0x803003);
            return trace.fraction >= 0.95f;
        }
        return false;
    }

    int TextWidth(const char* text, const char* font) {
        return R_TextWidth(text, 0x7FFFFFFF, R_RegisterFont(font, 0));
    }

    int TextHeight(const char* font) {
        return R_TextHeight(R_RegisterFont(font, 0));
    }

    bool checkLocalClient(int i) {
        return i == cg->cNum;
    }

    bool checkFFAMode() {
        if (cgs->GameType == "oic" || cgs->GameType == "dm") return true;
        return false;
    }

    bool notTeam(int i) {
        return (cg->ClientInfo[cg->cNum].mTeam != cg->ClientInfo[i].mTeam || cg->ClientInfo[i].mTeam == 0);
    }

    int ValidPlayerCount() {
        auto count = 0;
        for (auto i = 0; i < cgs->maxClients; i++) {
            if (cg->ClientInfo[i].Valid) count++;
        }
        return count;
    };

    char* getIpAsString(int i) {
        if (i == cg->cNum) clientIps[i]->ip1 = 0x00, clientIps[i]->ip2 = 0x00, clientIps[i]->ip3 = 0x00, clientIps[i]->ip4 = 0x00;
        return va("%d.%d.%d.%d", clientIps[i]->ip1, clientIps[i]->ip2, clientIps[i]->ip3, clientIps[i]->ip4);
    }
}
