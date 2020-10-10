namespace TU7
{
	float* isVisible(int i) {
		if (AimTarget_IsTargetValid(cg, &Centity_s[i]))
		{
			if (i == wallClient && !AimTarget_IsTargetVisible(0, &Centity_s[i], 0))
				return wallBlue;
			if (AimTarget_IsTargetVisible(0, &Centity_s[i], 0))
				return mellowYellow;
		}
		return redEnemy;
	}

	void DrawBarrel(int i, bool drawBox = false)
	{
		trace_t results;
		Vector2 startOut, endOut;
		Vector3 start, end, endPos, forward;
		AngleForwardVectors(Centity_s[i].viewAngle, &forward);
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
	
	void drawESP()
	{
		if (!cg->ClientInfo[cg->clientNum].mValid) return;
		const auto CenterX = cg->refdef.width / 2;
		const auto CenterY = cg->refdef.height / 2;
		for (DWORD i = 0; i < 18; i++)
		{
			if (i == cg->clientNum) continue;
			if (!Centity_s[i].valid) continue;
			if (!Centity_s[i].State & 1) continue;
			Vector2 Screen, entHead2D;
			auto Origin = GetPlayerOrigin(i);
			if (drawPointers) CG_DrawGrenadePointer(0, CenterX, CenterY, Centity_s[i].origin - Centity_s[cg->clientNum].origin, notTeam(i) ? isVisible(i) : Friendly, 2, 1.1f);
			if (drawBarrelESP) DrawBarrel(i, drawEndBox);
			if (WorldToScreen(Origin, Screen))
			{
				const int x = Screen.x;
				const int y = Screen.y;
				auto entHead3D = GetTagPos(i, "j_head");
				entHead3D.z += 8;
				if (WorldToScreen(entHead3D, entHead2D)) {
					if (esp2D) Draw2DBox(Screen, entHead2D, 2, notTeam(i) ? isVisible(i) : Friendly);
					if (esp3D) draw3DBounded(entHead3D, Centity_s[i].origin, Centity_s[i].origin.y, 25, 2, notTeam(i) ? isVisible(i) : Friendly);
				}
				if (espTri) drawPyramid(Centity_s[i].origin, GetBoxWidth(&Centity_s[i]), GetBoxHeight(&Centity_s[i]), notTeam(i) ? isVisible(i) : Friendly);
				if (snaplines) drawLine(CenterX, snaplinepos, x, y, 1, notTeam(i) ? isVisible(i) : Friendly);
				if (espname) {
					Material* rankIcon;
					CG_GetRankIcon(cg->ClientInfo[i].Rank, cg->ClientInfo[i].Prestige, &rankIcon);
					drawTextWithBG(va("%s", cg->ClientInfo[i].szPlayerName), x - 15 / 2, Screen.y - 36, "fonts/smallFont", .5, white, 16, (cg->ClientInfo[i].Prestige <= 10) ? rankIcon->info.name : nullptr);
				}
				if (espdist) drawTextWithBG(va("[%.fm]", GetDistance(cg->refdef.viewOrigin, Centity_s[i].origin)), x - 5 / 2, y - 20, "fonts/smallFont", .5, white, 16, nullptr);
			}
		}
	}
}