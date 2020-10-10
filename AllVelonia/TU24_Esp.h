#ifndef TU24_ESP_H
#define TU24_ESP_H

namespace TU24
{
	inline float* isVisible(int i) {
		if (AimTarget_IsTargetValid(cg, Entities[i]))
		{
			if (i == wallClient && !AimTarget_IsTargetVisible(0, Entities[i], 0))
				return wallBlue;
			if (AimTarget_IsTargetVisible(0, Entities[i], 0))
				return mellowYellow;
		}
		return redEnemy;
	}

	inline void DrawBarrel(int i, bool drawBox = false)
	{
		trace_t results;
		Vector2 startOut, endOut;
		Vector3 start, end, endPos, forward;
		AngleForwardVectors(Entities[i]->Angle, &forward);
		start = GetTagPos(i, "tag_flash");
		end = start + (forward * 100.0f);
		CG_LocationalTrace(&results, &start, &end, i, 0x803003);
		endPos = start + (forward * (100.0f * results.fraction));
		auto boxPos = endPos;
		boxPos.z -= .5;
		if (WorldToScreen(start, startOut) && WorldToScreen(endPos, endOut))
		{
			drawLine(startOut.x, startOut.y, endOut.x, endOut.y, 1, notTeam(i) ? isVisible(i) : Friendly);
			if (drawBox) Make3DBox(boxPos, 0.5, 1, notTeam(i) ? isVisible(i) : Friendly);
		}
	}

	inline void drawESPTypes() {
		for (auto i = 19; i < 2048; i++) {
			auto pent = getCEntitybyIDx(i);
			const auto distance = GetDistance(pent->origin, cg->refdef.viewOrigin);
			if (pent->Type == TYPE_ITEM && pent->valid) {
				Vector2 Screen;
				if (WorldToScreen(pent->origin, Screen))
				{
					const int x = Screen.x;
					const int y = Screen.y;
					if (distance < 200)
					{
						const int WeaponID = pent->WeaponID;
						if (strcmp(GetRawWeaponName(WeaponID), "scavenger_bag_mp")) {
							if (WeaponID <= 0) continue;
							const auto TempShader = GetWeaponShader(WeaponID);
							if (TempShader) CG_DrawRotatedPicPhysical(0x82732100, x - 15, y, 20, 20, (i == cg->clientNum || pent->Type == TYPE_ITEM) ? 0 : (cg->ViewAngle.y - pent->Angle.y), white, TempShader);
						}
						else
						{
							CG_DrawRotatedPicPhysical(0x82732100, x - 15, y, 20, 20, (i == cg->clientNum || pent->Type == TYPE_ITEM) ? 0 : (cg->ViewAngle.y - pent->Angle.y), white, Material_RegisterHandleInt("specialty_scavenger", 0));
						}
						const auto fWidth = (25.0f) / distance;
						const auto fHeight = (15.0f) / distance;
						Make3DBox(pent->origin, fWidth, fHeight, Orangade);
					}
				}
			}
			if (pent->Type == TYPE_MISSLE && pent->valid) {
				Vector2 Screen;
				if (WorldToScreen(pent->origin, Screen))
				{
					const int x = Screen.x;
					const int y = Screen.y;
					if (distance < 200)
					{
						const int WeaponID = pent->WeaponID;
						if (strcmp(GetRawWeaponName(WeaponID), "flash_grenade_mp") && strcmp(GetRawWeaponName(WeaponID), "iw5_smaw_mp")) {
							if (WeaponID <= 0) continue;
							const auto dwTempShader = GetWeaponShader(WeaponID);
							if (dwTempShader) CG_DrawRotatedPicPhysical(0x82732100, x - 15, y, 20, 20, (i == cg->clientNum || pent->Type == TYPE_MISSLE) ? 0 : (cg->ViewAngle.y - pent->Angle.y), white, dwTempShader);
						}
						else if (!strcmp(GetRawWeaponName(WeaponID), "flash_grenade_mp")) {
							CG_DrawRotatedPicPhysical(0x82732100, x - 15, y, 20, 20, (i == cg->clientNum || pent->Type == TYPE_MISSLE) ? 0 : (cg->ViewAngle.y - pent->Angle.y), white, Material_RegisterHandleInt("weapon_flashbang", 0));
						}
						const auto fWidth = (15.0f) / distance;
						const auto fHeight = (15.0f) / distance;
						Make3DBox(pent->origin, fWidth, fHeight, lilac);
					}
				}
			}
			if (pent->Type == TYPE_TURRET && pent->valid)
			{
				Vector2 Screen;
				const int WeaponID = pent->WeaponID;
				if (!strcmp(GetRawWeaponName(WeaponID), "sentry_minigun_mp")) {
					if (WorldToScreen(pent->origin, Screen)) {
						const int x = Screen.x;
						const int y = Screen.y;
						const auto dwTempShader = GetWeaponShader(WeaponID);
						if (dwTempShader) CG_DrawRotatedPicPhysical(0x82732100, x - 15, y - 15, 20, 20, (i == cg->clientNum || pent->Type == TYPE_TURRET) ? 0 : (cg->ViewAngle.y - pent->Angle.y), white, dwTempShader);
						Make3DBox(pent->origin, 20, 45, dirtyGreen);
					}
				}
			}
		}
	}

	inline void drawExternalRadar() {
		if (canRenderRadar) {
			rectDef_s radarPosition;
			radarPosition.x = 6.f;
			radarPosition.y = 6.f;
			radarPosition.w = 100.f;
			radarPosition.h = 100.f;
			radarPosition.unk = 0x08084000;
			Vector2 size;
			size.x = 6, size.y = 6;

			CG_CompassDrawPlayerMap(0, COMPASS_TYPE_PARTIAL, size, &radarPosition, Material_RegisterHandle("white", 0), white);
			CG_CompassDrawCrates(0, COMPASS_TYPE_PARTIAL, nullptr, &radarPosition, Material_RegisterHandle("white", 0), white);
			CG_CompassDrawPlayer(0, COMPASS_TYPE_PARTIAL, nullptr, &radarPosition, mellowYellow);
			CG_CompassDrawFriendlies(0, COMPASS_TYPE_PARTIAL, nullptr, &radarPosition, Friendlies);
			CG_CompassDrawEnemies(0, COMPASS_TYPE_PARTIAL, nullptr, &radarPosition, Enemies);
			CG_CompassDrawTurrets(0, COMPASS_TYPE_PARTIAL, nullptr, &radarPosition, white);
			CG_CompassDrawMissiles(0, COMPASS_TYPE_PARTIAL, nullptr, &radarPosition, white);
			CG_CompassDrawHelicopter(0, COMPASS_TYPE_PARTIAL, nullptr, &radarPosition, white);
			for (auto i = 0; i < 2048; i++) {
				auto entity = getCEntitybyIDx(i);
				if (entity->valid) {
					Vector2 compass;
					Vector2 widthHeight;
					widthHeight.x = 6;
					widthHeight.y = 6;
					WorldPosToCompassPos(&radarPosition, size, entity->origin, &compass, widthHeight);
					const auto angle = Entities[cg->clientNum]->Angle.y - entity->Angle.y;
					if (entity->Type == TYPE_ITEM || entity->Type == TYPE_MISSLE) {
						const auto shader = GetWeaponShader(entity->WeaponID);
						if (shader) {
							CG_DrawRotatedPicInt(0x827322C0, compass.x - (10 / 2), compass.y - (10 / 2), 10, 10, 8, 8, angle, white, shader);
						}
					}
				}
			}
			canRenderRadar = false;
		}
		InitializeOnceInGame(&hasPatchedRadar, RadarPatch);
	}

	inline void drawESP()
	{
		if (!cg->ClientInfo[cg->clientNum].mValid) return;
		const auto CenterX = cg->refdef.width / 2;
		const auto CenterY = cg->refdef.height / 2;
		for (DWORD i = 0; i < 18; i++)
		{
			if (i == cg->clientNum) continue;
			if (!Entities[i]->valid) continue;
			Vector2 Screen, entHead2D;
			auto Origin = GetPlayerOrigin(i);
			if (drawPointers) CG_DrawGrenadePointer(0, CenterX, CenterY, Entities[i]->origin - Entities[cg->clientNum]->origin, notTeam(i) ? isVisible(i) : Friendly, 2, 1.1f);
			if (drawBarrelESP) DrawBarrel(i, drawEndBox);
			if (WorldToScreen(Origin, Screen))
			{
				const int x = Screen.x;
				const int y = Screen.y;
				auto entHead3D = GetTagPos(i, "j_head");
				entHead3D.z += 8;
				if (WorldToScreen(entHead3D, entHead2D)) {
					if (esp2D) Draw2DBox(Screen, entHead2D, 2, notTeam(i) ? isVisible(i) : Friendly);
					if (esp3D) draw3DBounded(entHead3D, Entities[i]->origin, Entities[i]->origin.y, 25, 2, notTeam(i) ? isVisible(i) : Friendly);
				}
				if (espTri) drawPyramid(Entities[i]->origin, GetBoxWidth(Entities[i]), GetBoxHeight(Entities[i]), notTeam(i) ? isVisible(i) : Friendly);
				if (snaplines) drawLine(CenterX, snaplinepos, x, y, 1, notTeam(i) ? isVisible(i) : Friendly);
				if (espname) {
					const auto client = cg->ClientInfo[i];
					Material* rankIcon;
					CG_GetRankIcon(client.Rank, client.Prestige, &rankIcon);
					drawTextWithBG(va("%s", cg->ClientInfo[i].szPlayerName), x - 15 / 2, Screen.y - 36, "fonts/smallFont", .5, white, 16, (cg->ClientInfo[i].Prestige <= 20) ? rankIcon->info.name : nullptr);
				}
				if (espdist) drawTextWithBG(va("[%.fm]", GetDistance(cg->refdef.viewOrigin, Entities[i]->origin)), x - 5 / 2, y - 20, "fonts/smallFont", .5, white, 16, nullptr);
			}
		}
	}
}
#endif // TU24_ESP_H