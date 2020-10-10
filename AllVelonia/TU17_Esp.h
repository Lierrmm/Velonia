#ifndef TU17_ESP_H
#define TU17_ESP_H
namespace TU17
{
	inline float* isVisible(int i) {
		if (AimTarget_IsTargetValid(cg, &Centity_s[i]))
		{
			if (i == wallClient && !Aimtarget_isTargetVisible(0, &Centity_s[i], 0))
				return GhostsWall;
			if (Aimtarget_isTargetVisible(0, &Centity_s[i], 0))
				return GhostsVisible;
		}
		return redEnemy;
	}

	inline void DrawBarrel(int i, bool drawBox = false)
	{
		if (Centity_s[i].Type == ET_PLAYER) {
			trace_t results;
			Vector2 startOut, endOut;
			Vector3 start, end, endPos, forward;
			AngleForwardVectors(Centity_s[i].viewAngle, &forward);
			start = GetTagPos(i, "j_neck");
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
	}

	inline void drawExternalRadar() {
		if (canRenderRadar) {
			rectDef_s radarPosition;
			radarPosition.x = 8.f;
			radarPosition.y = 8.f;
			radarPosition.w = 200.f;
			radarPosition.h = 100.f;
			radarPosition.unk = 0x08084000;
			Vector2 size;
			size.x = 8, size.y = 8;

			CG_CompassDrawPlayerMap(0, COMPASS_TYPE_PARTIAL, size, &radarPosition, Material_RegisterHandle("white", 0), white);
			CG_CompassDrawCrates(0, COMPASS_TYPE_PARTIAL, nullptr, &radarPosition, Material_RegisterHandle("white", 0), white);
			CG_CompassDrawPlayer(0, COMPASS_TYPE_PARTIAL, nullptr, &radarPosition, mellowYellow);
			CG_CompassDrawFriendlies(0, COMPASS_TYPE_PARTIAL, nullptr, &radarPosition, Friendlies);
			CG_CompassDrawEnemies(0, COMPASS_TYPE_PARTIAL, nullptr, &radarPosition, Enemies);
			CG_CompassDrawTurrets(0, COMPASS_TYPE_PARTIAL, nullptr, &radarPosition, white);
			CG_CompassDrawMissiles(0, COMPASS_TYPE_PARTIAL, nullptr, &radarPosition, white);
			CG_CompassDrawHelicopter(0, COMPASS_TYPE_PARTIAL, nullptr, &radarPosition, white);
			for (auto i = 0; i < 2048; i++) {
				auto entity = Centity_s[i];
				if (entity.Alive) {
					Vector2 compass;
					Vector2 widthHeight;
					widthHeight.x = 8;
					widthHeight.y = 8;
					WorldPosToCompassPos(&radarPosition, size, entity.Origin, &compass, widthHeight);
					const auto angle = Centity_s[cg->ClientNumber].viewAngle.y - entity.viewAngle.y;
					if (entity.Type == ET_ITEM || entity.Type == ET_MISSLE) {
						const auto shader = GetWeaponShader(entity.WeaponID);
						if (shader) CG_DrawRotatedPicInt(0x82BCDD10, compass.x - (10 / 2), compass.y - (10 / 2), 10, 10, 8, 8, angle, white, shader);
					}
				}
			}
			canRenderRadar = false;
		}
		InitializeOnceInGame(&hasPatchedRadar, RadarPatch);
	}

	inline void drawAliensESP()
	{
		getStructs();
		const auto CenterX = cg->RefDef.Width / 2;
		const auto CenterY = cg->RefDef.Height / 2;
		for (auto i = 0; i < snapshot.entityCount; i++)
		{
			if (i == cg->ClientNumber) continue;
			if (bypassEntAliens(Centity_s[i].Type)) continue;
			if (Centity_s[i].Type != ET_AGENT) continue;
			if (!Centity_s[i].Alive) continue;
			Vector2 Screen, entHead2D;
			auto Origin = GetPlayerOrigin(i);
			if (drawPointers) CG_DrawGrenadePointer(0, CenterX, CenterY, Centity_s[i].Origin - Centity_s[cg->ClientNumber].Origin, isVisible(i), 2, 1.1f);
			if (WorldToScreen(Origin, Screen))
			{
				const int x = Screen.x;
				const int y = Screen.y;
				auto entHead3D = GetTagPos(i, "j_head");
				entHead3D.z += 8;
				if (WorldToScreen(entHead3D, entHead2D)) {
					if (esp2D) Draw2DBox(Screen, entHead2D, 2, isVisible(i));
					if (esp3D) draw3DBounded(entHead3D, Centity_s[i].Origin, Centity_s[i].Origin.y, 25, 2, isVisible(i));
				}
				if (espTri) drawPyramid(Centity_s[i].Origin, GetBoxWidth(&Centity_s[i]), GetBoxHeight(&Centity_s[i]), isVisible(i));
				if (snaplines) drawLine(CenterX, snaplinepos, x, y, 1, isVisible(i));
				if (espdist) drawTextWithBG(va("[%.fm]", GetDistance(cg->RefDef.viewOrigin, Centity_s[i].Origin)), x - 5 / 2, y - 20, smallFont, .5, white, 16, nullptr);
			}
		}
	}

	inline void drawESP()
	{
		if (isAliens()) return drawAliensESP();
		const auto CenterX = cg->RefDef.Width / 2;
		const auto CenterY = cg->RefDef.Height / 2;
		for (auto i = 0; i < 18; i++)
		{
			if (i == cg->ClientNumber) continue;
			if (!Centity_s[i].Alive) continue;
			if (Centity_s[i].Type != ET_PLAYER) continue;
			Vector2 Screen, entHead2D;
			auto Origin = GetPlayerOrigin(i);
			if (drawPointers) CG_DrawGrenadePointer(0, CenterX, CenterY, Centity_s[i].Origin - Centity_s[cg->ClientNumber].Origin, notTeam(i) ? isVisible(i) : Friendly, 2, 1.1f);
			if (drawBarrelESP) DrawBarrel(i, drawEndBox);
			if (WorldToScreen(Origin, Screen))
			{
				const int x = Screen.x;
				const int y = Screen.y;
				auto entHead3D = GetTagPos(i, "j_head");
				entHead3D.z += 8;
				if (WorldToScreen(entHead3D, entHead2D)) {
					if (esp2D) Draw2DBox(Screen, entHead2D, 2, notTeam(i) ? isVisible(i) : Friendly);
					if (esp3D) draw3DBounded(entHead3D, Centity_s[i].Origin, Centity_s[i].Origin.y, 25, 2, notTeam(i) ? isVisible(i) : Friendly);
				}
				if (espTri) drawPyramid(Centity_s[i].Origin, GetBoxWidth(&Centity_s[i]), GetBoxHeight(&Centity_s[i]), notTeam(i) ? isVisible(i) : Friendly);
				if (snaplines) drawLine(CenterX, snaplinepos, x, y, 1, notTeam(i) ? isVisible(i) : Friendly);
				if (espdist) drawTextWithBG(va("[%.fm]", GetDistance(cg->RefDef.viewOrigin, Centity_s[i].Origin)), x - 5 / 2, y - 20, smallFont, .5, white, 16, nullptr);
				if (espname) drawTextWithBG(va("%s", partydata.partyMembers[i].gamertag), x - 15 / 2, Screen.y - 36, smallFont, .5, white, 16, nullptr);
			}
		}
	}
}
#endif // TU17_ESP_H