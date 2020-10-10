namespace TU9
{
	float* isVisible(int i) {
		if (AimTarget_IsTargetValid(cg, Entities[i]))
		{
			if (i == wallClient && !Aimtarget_isTargetVisible(0, Entities[i], 0))
				return wallBlue;
			if (Aimtarget_isTargetVisible(0, Entities[i], 0))
				return mellowYellow;
		}
		return redEnemy;
	}

	void DrawBarrel(int i, bool drawBox = false)
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


	void drawExternalRadar() {
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
			CG_CompassDrawPlayer(0, COMPASS_TYPE_PARTIAL, nullptr, &radarPosition, Material_RegisterHandle("compassping_player", 0), mellowYellow);
			CG_CompassDrawFriendlies(0, COMPASS_TYPE_PARTIAL, nullptr, &radarPosition, Friendlies);
			CG_CompassDrawEnemies(0, COMPASS_TYPE_PARTIAL, nullptr, &radarPosition, Enemies);
			CG_CompassDrawPlanes(0, COMPASS_TYPE_PARTIAL, nullptr, &radarPosition, white);
			//CG_CompassDrawSentry(0, COMPASS_TYPE_PARTIAL, nullptr, &radarPosition, white);
			for (auto i = 18; i < 2046; i++) {
				auto entity = getCEntitybyIDx(i);
				if (entity->Valid) {
					Vector2 compass;
					Vector2 widthHeight;
					widthHeight.x = 6;
					widthHeight.y = 6;
					WorldPosToCompassPos(&radarPosition, size, entity->mPos, &compass, widthHeight);
					const auto angle = Entities[cg->cNum]->Angle.y - entity->Angle.y;
					if (entity->EntityType == TYPE_ITEM || entity->EntityType == TYPE_MISSLE) {
						auto shader = GetWeaponShader(entity->WeaponNum);
						if (shader) {
							CG_DrawRotatedPicInt(0x82690f40, compass.x - (10 / 2), compass.y - (10 / 2), 10, 10, 8, 8, angle, white, shader);
						}
					}
				}
			}
			canRenderRadar = false;
		}
		InitializeOnceInGame(&hasPatchedRadar, RadarPatch);
	}
	
	void drawESPTypes() {
		for (auto i = 18; i < 2048; i++) {
			auto pent = getCEntitybyIDx(i);
			auto distance = GetDistance(pent->mPos, cg->refdef.EyePos);
			if (pent->EntityType == TYPE_ITEM && pent->Valid) {
				Vector2 Screen;
				if (WorldToScreen(pent->mPos, Screen))
				{
					int x = Screen.x;
					int y = Screen.y;
					if (distance < 200)
					{
						int WeaponID = pent->WeaponNum;
						if (WeaponID <= 0) continue;
						auto Shader = GetWeaponShader(WeaponID);
						if (Shader == -1) continue;
						if (strcmp(GetRawWeaponName(WeaponID), "scavenger_bag_mp")) {
							if (Shader) CG_DrawRotatedPicPhysicalInt(0x82690f40, x - 15, y, 20, 20, (i == cg->cNum || pent->EntityType == TYPE_ITEM) ? 0 : (cg->ViewAngle.y - pent->Angle.y), white, Shader);
						}
						else CG_DrawRotatedPicPhysicalInt(0x82690f40, x - 15, y, 20, 20, (i == cg->cNum || pent->EntityType == TYPE_ITEM) ? 0 : (cg->ViewAngle.y - pent->Angle.y), white, Material_RegisterHandleInt("specialty_scavenger", 0));
						auto fWidth = (25.0f) / distance;
						auto fHeight = (15.0f) / distance;
						Make3DBox(pent->mPos, fWidth, fHeight, Orangade);
					}
				}
			}
			if (pent->EntityType == TYPE_MISSLE && pent->Valid) {
				Vector2 Screen;
				int WeaponID = pent->WeaponNum;
				if (WorldToScreen(pent->mPos, Screen))
				{
					int x = Screen.x;
					int y = Screen.y;
					if (distance < 200)
					{
						if (strcmp(GetRawWeaponName(WeaponID), "flash_grenade_mp")) {
							if (WeaponID <= 0) continue;
							auto dwTempShader = GetWeaponShader(WeaponID);
							if (dwTempShader == -1) continue;
							if (dwTempShader) CG_DrawRotatedPicPhysicalInt(0x82690f40, x - 15, y, 20, 20, (i == cg->cNum || pent->EntityType == TYPE_MISSLE) ? 0 : (cg->ViewAngle.y - pent->Angle.y), white, dwTempShader);
						}
						else if (!strcmp(GetRawWeaponName(WeaponID), "flash_grenade_mp")) CG_DrawRotatedPicPhysicalInt(0x82690f40, x - 15, y, 20, 20, (i == cg->cNum || pent->EntityType == TYPE_MISSLE) ? 0 : (cg->ViewAngle.y - pent->Angle.y), white, Material_RegisterHandleInt("weapon_flashbang", 0));
						auto fWidth = (15.0f) / distance;
						auto fHeight = (15.0f) / distance;
						Make3DBox(pent->mPos, fWidth, fHeight, lilac);
					}
				}
			}
			if (pent->EntityType == TYPE_TURRET && pent->Valid)
			{
				Vector2 Screen;
				int WeaponID = pent->WeaponNum;
				auto dwTempShader = GetWeaponShader(WeaponID);
				if (dwTempShader == -1) continue;
				int x = Screen.x; int y = Screen.y;
				if (!strcmp(GetRawWeaponName(WeaponID), "sentry_minigun_mp")) {
					if (WorldToScreen(pent->mPos, Screen)) {
						if (dwTempShader) CG_DrawRotatedPicPhysicalInt(0x82690f40, x - 15, y - 15, 20, 20, (i == cg->cNum || pent->EntityType == TYPE_TURRET) ? 0 : (cg->ViewAngle.y - pent->Angle.y), white, dwTempShader);
						Make3DBox(pent->mPos, 20, 45, dirtyGreen);
					}
				}
			}
		}
	}

	void drawESP() {
		if (!cg->ClientInfo[cg->cNum].Valid) return;
		auto CenterX = cg->refdef.iWidth / 2;
		auto CenterY = cg->refdef.iHeight / 2;
		for (DWORD i = 0; i < 18; i++)
		{
			if (i == cg->cNum) continue;
			if (!Entities[i]->Valid) continue;
			Vector2 Screen;
			Vector2 entHead2D;
			if (drawPointers) CG_DrawGrenadePointer(0, CenterX, CenterY, GetPlayerOrigin(i) - Entities[cg->cNum]->mPos, notTeam(i) ? isVisible(i) : Friendly, 2, 1.1f);
			if (drawBarrelESP) DrawBarrel(i, true);
			if (WorldToScreen(GetPlayerOrigin(i), Screen))
			{
				int x = Screen.x; int y = Screen.y;
				auto entHead3D = GetTagPos(i, "j_head");
				entHead3D.z += 8;
				if (WorldToScreen(entHead3D, entHead2D)) {
					if (esp2D) Draw2DBox(Screen, entHead2D, 2, notTeam(i) ? isVisible(i) : Friendly);
					if (esp3D) draw3DBounded(entHead3D, Entities[i]->mPos, Entities[i]->mPos.y, 25, 2, notTeam(i) ? isVisible(i) : Friendly);
				}
				if (espTri) drawPyramid(GetPlayerOrigin(i), GetBoxWidth(Entities[i]), GetBoxHeight(Entities[i]), notTeam(i) ? isVisible(i) : Friendly);
				if (snaplines) drawLine(CenterX, snaplinepos, x, y, 1, notTeam(i) ? isVisible(i) : Friendly);
				if (espdist) drawTextWithBG(va("[%.fm]", GetDistance(cg->refdef.EyePos, Entities[i]->mPos)), x - 5 / 2, y - 20, "fonts/smallFont", .5, white, 16, nullptr);
				if (espname) {
					const auto client = cg->ClientInfo[i];
					Material* rankIcon;
					CG_GetRankIcon(client.Rank, client.Prestige, &rankIcon);
					drawTextWithBG(va("%s", cg->ClientInfo[i].mName), x - 15 / 2, Screen.y - 36, "fonts/smallFont", .5, white, 16, (cg->ClientInfo[i].Prestige <= 10) ? rankIcon->info.name : nullptr);
					rankIcon = nullptr;
				}
			}
		}
	}
	
}