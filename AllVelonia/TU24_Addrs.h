#ifndef TU24_ADDRS_H
#define TU24_ADDRS_H

namespace TU24
{
    void* (*R_RegisterFont)(const char* r3, int r4) = reinterpret_cast<void* (*)(const char*, int)>(0x82407A90);
    void* (*R_AddCmdDrawText)(const char* r3, int r4, void* r5, float f1, float f2, float f3, float f4, float f5, const float* color, int something) = reinterpret_cast<void* (*)(const char* r3, int r4, void* r5, float f1, float f2, float f3, float f4, float f5, const float* color, int something)>(0x8241F9E0);
    int(__cdecl* R_TextWidth)(const char* text, int maxchars, void* font) = reinterpret_cast<int(__cdecl*)(const char*, int, void*)>(0x82407B00);
    int(__cdecl* R_TextHeight)(void* font) = reinterpret_cast<int(__cdecl*)(void*)>(0x82407C80);
    void* (*Material_RegisterHandle)(const char* r3, int r4) = reinterpret_cast<void* (*)(const char*, int)>(0x82413F48);
    int(*Material_RegisterHandleInt)(const char* r3, int r4) = reinterpret_cast<int(*)(const char*, int)>(0x82413F48);
    void* (*R_AddCmdDrawStretchPic)(float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, const float* color, void* material) = reinterpret_cast<void* (*)(float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, const float* color, void* material)>(0x82164AF8);
	void(__cdecl* CG_DrawRotatedPicPhysical)(int, float, float, float, float, float, float*, int) = reinterpret_cast<void(__cdecl*)(int, float, float, float, float, float, float*, int)>(0x82117668);
    void(*Cbuf_AddText)(int localClientNum, const char* text) = reinterpret_cast<void(*)(int, const char*)>(0x82287F68);
    bool(*Dvar_GetBool)(const char* dvarName) = reinterpret_cast<bool(*)(const char*)>(0x8232E2C8);
    int(*Dvar_GetInt)(const char* dvarName) = reinterpret_cast<int(*)(const char*)>(0x8232E330);
    const char* (*Dvar_GetString)(const char* dvarName) = reinterpret_cast<const char* (*)(const char*)>(0x8232E488);
    float (*Dvar_GetFloat)(const char* dvarName) = reinterpret_cast<float (*)(const char*)>(0x8232E398);
    void(*CG_GameMessage)(int localClientNum, const char* msg) = reinterpret_cast<void(*)(int, const char*)>(0x82127BF8);
    void(*CG_GameMessageBold)(int localClientNum, const char* msg) = reinterpret_cast<void(*)(int, const char*)>(0x82127C18);
    int(__cdecl* SL_GetString)(char*, int usr) = reinterpret_cast<int(__cdecl*)(char*, int)>(0x822B5CC8);
    unsigned int(__cdecl* GScr_AllocString)(const char*) = reinterpret_cast<unsigned int(__cdecl*)(const char*)>(0x822513A0);
    int(*Com_GetClientDObj)(int r3, int r4) = reinterpret_cast<int(*)(int, int)>(0x822A28D0);
    bool(*CG_DObjGetWorldTagPos)(CEntity* r3, int r4, int r5, Vector3& r6) = reinterpret_cast<bool(*)(CEntity*, int, int, Vector3&)>(0x8211BCB8);
    int(*Key_isDown)(int ClientNum, int ButtonEnum) = reinterpret_cast<int(*)(int, int)>(0x8216ED28);
    bool(__cdecl* AimTarget_IsTargetVisible)(int localClientNum, CEntity* targetEnt, unsigned int visBone) = reinterpret_cast<bool(*)(int, CEntity*, unsigned int)>(0x820D5010);
    bool(__cdecl* AimTarget_IsTargetValid)(cg_t* cgameGlob, CEntity* targetEnt) = reinterpret_cast<bool(*)(cg_t*, CEntity*)>(0x820D4E88);
    int(__cdecl* BG_GetWeaponDef)(unsigned int weaponIndex) = reinterpret_cast<int(__cdecl*)(unsigned int)>(0x820D5A10);
    float(__cdecl* CG_GoodRandomFloat)(int* seed) = reinterpret_cast<float(__cdecl*)(int*)>(0x820E7E20);
    void(__cdecl* BG_GetSpreadForWeapon)(cg_t* LocalClient, int Weapon, float* min, float* max) = reinterpret_cast<void(*)(cg_t*, int, float*, float*)>(0x82101B08);
    void(__cdecl* CG_GetPlayerViewOrigin)(int localClientNum, cg_t* cg, Vector3& origin) = reinterpret_cast<void(__cdecl*)(int, cg_t*, Vector3&)>(0x82159240);
    void(__cdecl* FireBulletPenetrate)(int LocalClient, BulletFireParams* bullet, int Weapon, int r3, CEntity* localEntity, int r4, float* viewOrg, int r5) = reinterpret_cast<void(__cdecl*)(int LocalClient, BulletFireParams * bullet, int Weapon, int fuckKnows, CEntity * MyCentity, int fuckKnows2, float* viewOrg, int fuckKnows3)>(0x8215FB08);
    void(*CG_LocationalTrace)(trace_t* results, Vector3* start, Vector3* end, int passEntityNum, int contentMask) = reinterpret_cast<void(*)(trace_t * results, Vector3 * start, Vector3 * end, int passEntityNum, int contentMask)>(0x821631B8);
    void(*CG_DrawGrenadePointer)(int localClientNum, float centerX, float centerY, Vector3& grenadeOffset, float* color, float radiusOffset, float scaleFactor) = reinterpret_cast<void(*)(int, float, float, Vector3&, float*, float, float)>(0x82111B88);
    char* (__cdecl* UI_GetMapDisplayName)(const char* mapname) = reinterpret_cast<char* (*)(const char*)>(0x822F2580);
    char* (__cdecl* UI_GetGameTypeDisplayName)(const char* gametype) = reinterpret_cast<char* (*)(const char*)>(0x822F27A8);
    int(__cdecl* irand)(int min, int max) = reinterpret_cast<int(*)(int, int)>(0x82319B98);
    PCHAR(*va)(PCHAR format, ...) = reinterpret_cast<PCHAR(*)(PCHAR, ...)>(0x823365F0);
    void(__cdecl* CG_DrawRotatedPic)(int scrPlace, float x, float y, float width, float height, int horzAlign, int vertAlign, float angle, const float* color, void* material) = reinterpret_cast<void(__cdecl*)(int, float, float, float, float, int, int, float, const float*, void*)>(0x82117810);
    void(__cdecl* CG_DrawRotatedPicInt)(int scrPlace, float x, float y, float width, float height, int horzAlign, int vertAlign, float angle, const float* color, int material) = reinterpret_cast<void(__cdecl*)(int, float, float, float, float, int, int, float, const float*, int)>(0x82117810);
    int(__cdecl* SND_PlayLocalSoundAliasByName)(int localClientNum, const char* aliasname, int system) = reinterpret_cast<int(*)(int, const char*, int)>(0x824E19D0);
    void(__cdecl* CG_DrawNightVisionOverlay)(int localClientNum) = reinterpret_cast<void(__cdecl*)(int)>(0x82115C40);
    void(__cdecl* R_AddDObjToScene)(int obj, int pose, unsigned int entnum, unsigned int renderFxFlags, float* lightingOrigin, float materialTime) = reinterpret_cast<void(__cdecl*)(int, int, unsigned int, unsigned int, float*, float)>(0x82423018);
    float(__cdecl* BG_GetSpeed)(cg_t* ps, int time) = reinterpret_cast<float(*)(cg_t*, int)>(0x820E7D20);
    float(__cdecl* R_NormalizedTextScale)(void* font, float scale) = reinterpret_cast<float(*)(void*, float)>(0x82407AA0);
    void(__cdecl* DrawIconDistanceText)(int localClientNum, float distance, float iconX, float iconY, float iconH, rectDef_s* rect, const float* color, void* textFont, float textScale, int textStyle) = reinterpret_cast<void(*)(int, float, float, float, float, rectDef_s*, const float*, void*, float, int)>(0x8210BD00);
    void(__cdecl* UI_DrawTextNoSnap)(int scrPlace, const char* text, int maxChars, void* font, float x, float y, int horzAlign, int vertAlign, float scale, const float* color, int style) = reinterpret_cast<void(*)(int, const char*, int, void*, float, float, int, int, float, const float*, int)>(0x822EC6A0);
    void(__cdecl* CG_CheckHudSprintDisplay)(int localClientNum) = reinterpret_cast<void(*)(int)>(0x82114CF0);
    void(__cdecl* CL_SetADS)(int localClient, bool ads) = reinterpret_cast<void(__cdecl*)(int, bool)>(0x82165FC0);
    void(__cdecl* CG_DrawIntermission)(int localClient) = reinterpret_cast<void(__cdecl*)(int)>(0x82115088);
    void(__cdecl* UI_DrawConnectScreen)(int localClient) = reinterpret_cast<void(__cdecl*)(int)>(0x822F7FF8);
    void(__cdecl* CG_Trace)(trace_t* results, Vector3 start, const float* mins, const float* maxs, const float* end, int passEntityNum, int contentMask, bool locational, bool staticModels) = reinterpret_cast<void(__cdecl*)(trace_t*, Vector3, const float*, const float*, const float*, int, int, bool, bool)>(0x82162FA0);
    void(__cdecl* CG_GetRankIcon)(int rank, int prestige, Material** material) = reinterpret_cast<void(__cdecl*)(int, int, Material**)>(0x8217C4C8);
    void(__cdecl* CL_DeathMessagePrint)(int localClientNum, const char* attackerName, char attackerColorIndex, const char* victimName, char victimColorIndex, void* iconShader, float iconWidth, float iconHeight, bool horzFlipIcon) = reinterpret_cast<void(__cdecl*)(int, const char*, char, const char*, char, void*, float, float, bool)>(0x82168E60);
    void(__cdecl* CG_DrawClientPing)(int localClientNum, int ping, float x, float y, float maxWidth, float maxHeight) = reinterpret_cast<void(__cdecl*)(int, int, float, float, float, float)>(0x8213AEF8);
    void(__cdecl* CL_AddReliableCommand)(int localClientNum, const char* cmd) = reinterpret_cast<void(__cdecl*)(int, const char*)>(0x821708B0);
    int(__cdecl* DObjGetBoneIndex)(int obj, unsigned int name, char* index) = reinterpret_cast<int(__cdecl*)(int, unsigned int, char*)>(0x8233EBE0);
    void(__cdecl* CG_AddHudGrenade)(cg_t* cgameGlob, CEntity* grenadeEnt) = reinterpret_cast<void(__cdecl*)(cg_t*, CEntity*)>(0x82112080);
    void(__cdecl* CG_PlayBoltedEffect)(int localClientNum, FxEffectDef* fxDef, int dobjHandle, unsigned int boneName) = reinterpret_cast<void(__cdecl*)(int, FxEffectDef*, int, unsigned int)>(0x8211D260);
    void(__cdecl* UI_DrawLoggedInUser)(rectDef_s* rect, void* font, float scale, float* color, int textStyle) = reinterpret_cast<void(__cdecl*)(rectDef_s*, void*, float, float*, int)>(0x822F2A68);
    int(__cdecl* UI_GetClientInfo)(int localClientNum) = reinterpret_cast<int(__cdecl*)(int)>(0x822EB080);
    void(__cdecl* __UI_DrawWrappedText)(int scrPlace, const char* text, rectDef_s* rect, void* font, float x, float y, float scale, const float* color, int style, int textAlignMode, rectDef_s* textRect) = reinterpret_cast<void(__cdecl*)(int scrPlace, const char* text, rectDef_s * rect, void* font, float x, float y,
        float scale, const float* color, int style, int textAlignMode,
        rectDef_s * textRect)>(0x82306CC0);
    void(__cdecl* CG_TeamColor)(int team, const char* prefix, float* color) = reinterpret_cast<void(__cdecl*)(int, const char*, float*)>(0x821185A8);
    void(__cdecl* CL_SetLocalClientActive)(int localClient, bool active) = reinterpret_cast<void(__cdecl*)(int, bool)>(0x821A7D28);
    void(__cdecl* CG_PlayTestFx)(int localClientNum) = reinterpret_cast<void(__cdecl*)(int)>(0x8214AE58);
    void(__cdecl* CG_PlayFxOnTag)(int localClientNum, CEntity* cent, int eventParm) = reinterpret_cast<void(*)(int, CEntity*, int)>(0x8211D4B0);
    void(__cdecl* Con_DrawGameMessageWindow)(int localClientNum, int windowIndex, int xPos, int yPos, int horzAlign, int vertAlign, void* font, float fontScale, float* color, int textStyle, int textAlignMode, int mode) = reinterpret_cast<void(*)(int, int, int, int, int, int, void*, float, float*, int, int, int)>(0x82169F90);
    bool(__cdecl* Key_IsCatcherActive)(int r1, int r2) = reinterpret_cast<bool(*)(int, int)>(0x8216FA08);
    int(__cdecl* Menus_OpenByName)(UIContext_s* dc, const char* p) = reinterpret_cast<int(*)(UIContext_s*, const char*)>(0x8230D148);
    void(__cdecl* CG_Laser_Add)(CEntity* ent, int dobj, int cpose, Vector3 viewerPos, int laserOwner) = reinterpret_cast<void(*)(CEntity*, int, int, Vector3, int)>(0x821250E0);
    void(*CG_CompassDrawPlayerMap)(int localClientNum, CompassType compassType, Vector2& size, rectDef_s* rect, void* material, float* color) = reinterpret_cast<void(*)(int, CompassType, Vector2&, rectDef_s*, void*, float*)>(0x8210AC98);
    void(__cdecl* CG_CompassDrawPlayer)(int localClientNum, CompassType compassType, rectDef_s* parentRect, rectDef_s* rect, float* color) = reinterpret_cast<void(*)(int, CompassType, rectDef_s*, rectDef_s*, float*)>(0x8210B540);
    bool(__cdecl* CG_WorldPosToCompass)(CompassType compassType, cg_t* cgameGlob, rectDef_s* mapRect, Vector2& yaw, Vector3& playerWorldPos, Vector3& in, Vector2& out, Vector2& outClipped) = reinterpret_cast<bool(__cdecl*)(CompassType, cg_t*, rectDef_s*, Vector2&, Vector3&, Vector3&, Vector2&, Vector2&)>(0x82109C50);
    void(__cdecl* CG_CompassDrawCrates)(int localClientNum, CompassType compassType, rectDef_s* parent, rectDef_s* rect, void* Material, float* color) = reinterpret_cast<void(*)(int, CompassType, rectDef_s*, rectDef_s*, void*, float*)>(0x8210C328);
    void(__cdecl* CG_CompassDrawBorder)(int localClientNum, CompassType compassType, rectDef_s* parent, rectDef_s* rect, void* Material, float* color) = reinterpret_cast<void(*)(int, CompassType, rectDef_s*, rectDef_s*, void*, float*)>(0x8210B818);
    void(__cdecl* CG_CompassDrawFriendlies)(int localClientNum, CompassType compassType, rectDef_s* parent, rectDef_s* rect, float* color) = reinterpret_cast<void(*)(int, CompassType, rectDef_s*, rectDef_s*, float*)>(0x8210DB68);
    void(__cdecl* CG_CompassDrawEnemies)(int localClientNum, CompassType compassType, rectDef_s* parent, rectDef_s* rect, float* color) = reinterpret_cast<void(*)(int, CompassType, rectDef_s*, rectDef_s*, float*)>(0x8210E3E0);
    void(__cdecl* CG_CompassDrawTurrets)(int localClientNum, CompassType compassType, rectDef_s* parent, rectDef_s* rect, float* color) = reinterpret_cast<void(*)(int, CompassType, rectDef_s*, rectDef_s*, float*)>(0x8210E9A8);
    void(__cdecl* CG_CompassDrawMissiles)(int localClientNum, CompassType compassType, rectDef_s* parent, rectDef_s* rect, float* color) = reinterpret_cast<void(*)(int, CompassType, rectDef_s*, rectDef_s*, float*)>(0x8210FE10);
    void(__cdecl* CG_CompassDrawHelicopter)(int localClientNum, CompassType compassType, rectDef_s* parent, rectDef_s* rect, float* color) = reinterpret_cast<void(*)(int, CompassType, rectDef_s*, rectDef_s*, float*)>(0x823AD678);
    void(__cdecl* CG_CompassCalcDimensions)(CompassType compassType, cg_t* cgameGlob, Vector2& size, rectDef_s* rect, float* x, float* y, float* w, float* h) = reinterpret_cast<void(*)(CompassType, cg_t*, Vector2&, rectDef_s*, float*, float*, float*, float*)>(0x82109E28);
    void(__cdecl* CG_CompassUpYawVector)(cg_t* cg, Vector2& yaw) = reinterpret_cast<void(*)(cg_t*, Vector2&)>(0x8210BB08);
    const char* (__cdecl* SEH_SafeTranslateString)(const char* r1) = reinterpret_cast<const char* (*)(const char*)>(0x822D8C60);
    void* (__cdecl* UI_GetFontHandle)(int r1, int r2, float r3) = reinterpret_cast<void* (*)(int, int, float)>(0x822EC810);
    void(__cdecl* CL_DrawTextWithCursor)(int scrPlace, const char* text, int maxChars, void* font, float x, float y, int horzAlign, int vertAlign, float xScale, float yScale, const float* color, int style, int cursorPos, char cursor) = reinterpret_cast<void(*)(int, const char*, int, void*, float, float, int, int, float, float, const float*, int, int, char)>(0x82174E78);
    void(__cdecl* Field_DrawTextOverride)(int localClientNum, field_t* edit, int x, int y, int horzAlign, int vertAlign, const char* str, int drawLen, int cursorPos) = reinterpret_cast<void(*)(int, field_t*, int, int, int, int, const char*, int, int)>(0x8216FAD8);
    void(__cdecl* Field_Draw)(int localClientNum, field_t* edit, int x, int y, int horzAlign, int vertAlign) = reinterpret_cast<void(*)(int, field_t*, int, int, int, int)>(0x8216FCA8);
    void(__cdecl* AimTarget_GetClientTargetList)(int localClientNum, AimTarget** targetList, int* targetCount) = reinterpret_cast<void(*)(int, AimTarget**, int*)>(0x820D5938);
    void(__cdecl* AnglesToAxis)(Vector3 angles, float(*axis)[3]) = reinterpret_cast<void(*)(Vector3, float(*)[3])>(0x822654C0);
    bool(__cdecl* AimAssist_ConvertToClipBounds)(cg_t* aaGlob, const float(*bounds)[3], const float(*mtx)[3], float(*clipBounds)[3]) = reinterpret_cast<bool(*)(cg_t*, const float(*)[3], const float(*)[3], float(*)[3])>(0x820D33E0);
    void(__cdecl* AimAssist_AddToTargetList)(cg_t* aaGlob, AimScreenTarget* screenTarget) = reinterpret_cast<void(*)(cg_t*, AimScreenTarget*)>(0x820D3798);
    int(__cdecl* AimAssist_CalcAimPos)(int localClientNum, CEntity* targetEnt, AimTarget* target, Vector3 aimPos) = reinterpret_cast<int(*)(int, CEntity*, AimTarget*, Vector3)>(0x820D3860);
    void(__cdecl* UI_DrawHandlePic)(int scrPlace, float x, float y, float w, float h, int horzAlign, int vertAlign, const float* color, void* material) = reinterpret_cast<void(*)(int, float, float, float, float, int, int, const float*, void*)>(0x822D9FF8);
    void(__cdecl* CL_DrawStretchPic)(int scrPlace, float x, float y, float w, float h, int horzAlign, int vertAlign, float s1, float t1, float s2, float t2, const float* color, void* material) = reinterpret_cast<void(*)(int, float, float, float, float, int, int, float, float, float, float, const float*, void*)>(0x82164CE0);
    void(__cdecl* CG_DrawDisconnect)(int localClientNum) = reinterpret_cast<void(*)(int)>(0x821156B0);
    void(__cdecl* ScrPlace_ApplyRect)(int scrPlace, float* x, float* y, float* w, float* h, int horzAlign, int vertAlign) = reinterpret_cast<void(*)(int, float*, float*, float*, float*, int, int)>(0x821A6428);
    void(__cdecl* CG_DrawPlayerStance)(int localClientNum, rectDef_s* rect, const float* color, void* font, float scale, int textStyle) = reinterpret_cast<void(*)(int, rectDef_s*, const float*, void*, float, int)>(0x82130460);
    void(__cdecl* CG_ItemPickup)(int localClientNum, int weapIndex) = reinterpret_cast<void(*)(int, int)>(0x8211CFA8);
    unsigned __int16(__cdecl* Trace_GetEntityHitId)(trace_t* trace) = reinterpret_cast<unsigned __int16(*)(trace_t*)>(0x82280720);
    int(__cdecl* Lobby_GetPartyData)() = reinterpret_cast<int(*)()>(0x82186A30);
    char* (__cdecl* CL_GetConfigString)(int index) = reinterpret_cast<char* (*)(int)>(0x82164958);

    inline bool Aimtarget_GetTagPos(pCentity_t cen, unsigned int tag, Vector3& v1) {
        auto var = Com_GetClientDObj(*reinterpret_cast<int*>(reinterpret_cast<int>(cen) + 0xC4), 0);
        if (var == 0) return false;
        return CG_DObjGetWorldTagPos(cen, var, tag, v1);
    }
	
    inline bool Aimtarget_isTargetVisible(int clientnum, pCentity_t cen, int tag) {
        trace_t trace;
        ZeroMemory(&trace, sizeof(trace));
        Vector3 tagpos;
        if (Aimtarget_GetTagPos(cen, tag, tagpos)) {
            CG_LocationalTrace(&trace, &cg->refdef.viewOrigin, &tagpos, cg->clientNum, 0x803003);
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

    inline char* getIpAsString(int i) {
        if (i == cg->clientNum) partydata.partyMembers[i].ExternalIP.ip1 = 0x00, partydata.partyMembers[i].ExternalIP.ip2 = 0x00, partydata.partyMembers[i].ExternalIP.ip3 = 0x00, partydata.partyMembers[i].ExternalIP.ip4 = 0x00;
        return va("%d.%d.%d.%d", partydata.partyMembers[i].ExternalIP.ip1, partydata.partyMembers[i].ExternalIP.ip2, partydata.partyMembers[i].ExternalIP.ip3, partydata.partyMembers[i].ExternalIP.ip4);
    }
}
#endif // TU24_ADDRS_H
