namespace TU11
{
	float* isVisible(int i) {
		/*if (AimTarget_IsTargetValid(cg, &Centity_s[i]))
		{
			if (i == wallClient && !AimTarget_IsTargetVisible(0, &Centity_s[i], 0))
				return wallBlue;
			if (AimTarget_IsTargetVisible(0, &Centity_s[i], 0))
				return mellowYellow;
		}*/
		return redEnemy;
	}

	//void DrawBarrel(int i, bool drawBox = false)
	//{
	//	trace_t results;
	//	Vector2 startOut, endOut;
	//	Vector3 start, end, endPos, forward;
	//	AngleForwardVectors(Centity_s[i].Angle, &forward);
	//	start = GetTagPos(i, "tag_flash");
	//	end = start + (forward * 100.0f);
	//	//CG_LocationalTrace(&results, &start, &end, i, 0x803003);
	//	endPos = start + (forward * (100.0f * results.fraction));
	//	auto boxPos = endPos;
	//	boxPos.z -= .5;
	//	if (WorldToScreen(start, startOut) && WorldToScreen(endPos, endOut))
	//	{
	//		drawLine(startOut.x, startOut.y, endOut.x, endOut.y, 1, notTeam(i) ? isVisible(i) : Friendly);
	//		if (drawBox) Make3DBox(boxPos, 0.5, 1, notTeam(i) ? isVisible(i) : Friendly);
	//	}
	//}

	//void drawESPTypes() {
	//	for (auto i = 19; i < 2048; i++) {
	//		auto pent = Centity_s[i];
	//		const auto distance = GetDistance(pent.Origin, cg->RefDef.viewOrigin);
	//		if (pent.Type == ET_ITEM && pent.Valid) {
	//			Vector2 Screen;
	//			if (WorldToScreen(pent.Origin, Screen))
	//			{
	//				const int x = Screen.x;
	//				const int y = Screen.y;
	//				if (distance < 200)
	//				{
	//					/*const int WeaponID = pent.WeaponID;
	//					if (strcmp(GetRawWeaponName(WeaponID), "scavenger_bag_mp")) {
	//						if (WeaponID <= 0) continue;
	//						const auto TempShader = GetWeaponShader(WeaponID);
	//						if (TempShader) CG_DrawRotatedPicPhysical(0x82732100, x - 15, y, 20, 20, (i == cg->ClientNumber || pent.Type == ET_ITEM) ? 0 : (cg->ViewAngle.y - pent.Angle.y), white, TempShader);
	//					}
	//					else
	//					{
	//						CG_DrawRotatedPicPhysical(0x82732100, x - 15, y, 20, 20, (i == cg->ClientNumber || pent.Type == ET_ITEM) ? 0 : (cg->ViewAngle.y - pent.Angle.y), white, Material_RegisterHandle("specialty_scavenger", 0));
	//					}*/
	//					const auto fWidth = (25.0f) / distance;
	//					const auto fHeight = (15.0f) / distance;
	//					Make3DBox(pent.Origin, fWidth, fHeight, Orangade);
	//					drawText(va("%p ET_ITEM", &Centity_s[i]), x, y, normalFont, 1.0, white);
	//				}
	//			}
	//		}
	//		if (pent.Type == ET_MISSILE && pent.Valid) {
	//			Vector2 Screen;
	//			if (WorldToScreen(pent.Origin, Screen))
	//			{
	//				const int x = Screen.x;
	//				const int y = Screen.y;
	//				if (distance < 200)
	//				{
	//					/*const int WeaponID = pent.WeaponID;
	//					if (strcmp(GetRawWeaponName(WeaponID), "flash_grenade_mp") && strcmp(GetRawWeaponName(WeaponID), "iw5_smaw_mp")) {
	//						if (WeaponID <= 0) continue;
	//						const auto dwTempShader = GetWeaponShader(WeaponID);
	//						if (dwTempShader) CG_DrawRotatedPicPhysical(0x82732100, x - 15, y, 20, 20, (i == cg->ClientNumber || pent.Type == ET_MISSILE) ? 0 : (cg->ViewAngle.y - pent.Angle.y), white, dwTempShader);
	//					}
	//					else if (!strcmp(GetRawWeaponName(WeaponID), "flash_grenade_mp")) {
	//						CG_DrawRotatedPicPhysical(0x82732100, x - 15, y, 20, 20, (i == cg->ClientNumber || pent.Type == ET_MISSILE) ? 0 : (cg->ViewAngle.y - pent.Angle.y), white, Material_RegisterHandle("weapon_flashbang", 0));
	//					}*/
	//					const auto fWidth = (15.0f) / distance;
	//					const auto fHeight = (15.0f) / distance;
	//					Make3DBox(pent.Origin, fWidth, fHeight, lilac);
	//					drawText(va("%p ET_MISSILE", &Centity_s[i]), x, y, normalFont, 1.0, white);
	//				}
	//			}
	//		}
	//		if (pent.Type == ET_TURRET && pent.Valid)
	//		{
	//			Vector2 Screen;
	//			const int WeaponID = pent.WeaponID;
	//			/*if (!strcmp(GetRawWeaponName(WeaponID), "sentry_minigun_mp")) {
	//				if (WorldToScreen(pent.Origin, Screen)) {
	//					const int x = Screen.x;
	//					const int y = Screen.y;
	//					const auto dwTempShader = GetWeaponShader(WeaponID);
	//					if (dwTempShader) CG_DrawRotatedPicPhysical(0x82732100, x - 15, y - 15, 20, 20, (i == cg->ClientNumber || pent.Type == ET_TURRET) ? 0 : (cg->ViewAngle.y - pent.Angle.y), white, dwTempShader);
	//					Make3DBox(pent.Origin, 20, 45, dirtyGreen);
	//				}
	//			}*/
	//		}
	//	}
	//}
	/*
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
			CG_CompassDrawCrates(0, COMPASS_TYPE_PARTIAL, nullptr, &radarPosition, Material_RegisterHandle("white", 0), white);
			CG_CompassDrawPlayer(0, COMPASS_TYPE_PARTIAL, nullptr, &radarPosition, mellowYellow);
			CG_CompassDrawFriendlies(0, COMPASS_TYPE_PARTIAL, nullptr, &radarPosition, Friendlies);
			CG_CompassDrawEnemies(0, COMPASS_TYPE_PARTIAL, nullptr, &radarPosition, Enemies);
			CG_CompassDrawTurrets(0, COMPASS_TYPE_PARTIAL, nullptr, &radarPosition, white);
			CG_CompassDrawMissiles(0, COMPASS_TYPE_PARTIAL, nullptr, &radarPosition, white);
			CG_CompassDrawHelicopter(0, COMPASS_TYPE_PARTIAL, nullptr, &radarPosition, white);
			for (auto i = 0; i < 2048; i++) {
				auto entity = Centity_s[i];
				if (entity.Valid) {
					Vector2 compass;
					Vector2 widthHeight;
					widthHeight.x = 6;
					widthHeight.y = 6;
					WorldPosToCompassPos(&radarPosition, size, entity.Origin, &compass, widthHeight);
					const auto angle = Centity_s[cg->ClientNumber].Angle.y - entity->Angle.y;
					if (entity->Type == TYPE_ITEM || entity->Type == TYPE_MISSLE) {
						const auto shader = GetWeaponShader(entity.WeaponID);
						if (shader) {
							CG_DrawRotatedPic(0x82A06718, compass.x - (10 / 2), compass.y - (10 / 2), 10, 10, 8, 8, angle, white, shader);
						}
					}
				}
			}
			canRenderRadar = false;
		}
		InitializeOnceInGame(&hasPatchedRadar, RadarPatch);
	}
	*/

	inline void drawZM()
	{
		getStructs();
		const auto CenterX = cg->RefDef.Width / 2;
		for (auto i = 0; i < 2048; i++)
		{
			if (i == cg->ClientNumber) continue;
						
			if (!Centity_s[i].Valid & 1) continue;
			if (!Centity_s[i].eType == ET_ACTOR) continue;
			//printf("ZM Pointer %p\n", &Centity_s[i]);
			Vector2 Screen, entHead2D;
			auto Origin = GetPlayerOrigin(i);
			if (WorldToScreen(Origin, Screen)) 
			{
				const int x = Screen.x;
				const int y = Screen.y;
				auto entHead3D = GetTagPos(i, "j_neck");
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
		if (!cg->ClientInfo[cg->ClientNumber].infoValid) return;
		drawZM();
		const auto CenterX = cg->RefDef.Width / 2;
		const auto CenterY = cg->RefDef.Height / 2;
		for (auto i = 0; i < 4; i++)
		{
			if (i == cg->ClientNumber) continue;
			if (!Centity_s[i].Valid) continue;
			Vector2 Screen, entHead2D;
			auto Origin = GetPlayerOrigin(i);
			//if (drawPointers) CG_DrawWarningPointer(0, CenterX, CenterY, Centity_s[i].Origin - Centity_s[cg->ClientNumber].Origin, notTeam(i) ? isVisible(i) : Friendly, 2);
			//if (drawBarrelESP) DrawBarrel(i, drawEndBox);
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
				if (espname) drawTextWithBG(va("%s", cg->ClientInfo[i].name), x - 15 / 2, Screen.y - 36, "fonts/smallFont", .5, white, 16, nullptr);
				if (espdist) drawTextWithBG(va("[%.fm]", GetDistance(cg->RefDef.viewOrigin, Centity_s[i].Origin)), x - 5 / 2, y - 20, "fonts/smallFont", .5, white, 16, nullptr);
			}
		}
	}
}