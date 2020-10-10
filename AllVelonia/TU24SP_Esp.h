#ifndef TU24SP_ESP_H
#define TU24SP_ESP_H

namespace TU24SP
{
	inline float* isVisible(int i) {
		if (Centity_s[i].nextState.eType & 1)
		{
			if (i == wallClient && !Aimtarget_isTargetVisible(i, &Centity_s[i], SL_GetString("j_head", 0)))
				return wallBlue;
			if (Aimtarget_isTargetVisible(i, &Centity_s[i], SL_GetString("j_head", 0)))
				return mellowYellow;
		}
		return redEnemy;
	}
	
	inline void drawAIESP()
	{
		const auto CenterX = cg.refdef.Width / 2;
		const auto CenterY = cg.refdef.Height / 2;
		for (auto i = 2; i < 2046; i++)
		{
			if (i == cg.clientNum) continue;
			if (Centity_s[i].pose.eType != ET_ACTOR) continue;
			Vector2 Screen, entHead2D;
			auto Origin = GetPlayerOrigin(i);
			if (drawPointers) CG_DrawGrenadePointer(0, CenterX, CenterY, Centity_s[i].pose.origin - Centity_s[cg.clientNum].pose.origin, isVisible(i), 2, 1.1f);
			//if (drawBarrelESP) DrawBarrel(i, drawEndBox);
			if (WorldToScreen(Origin, Screen))
			{
				const int x = Screen.x;
				const int y = Screen.y;
				auto entHead3D = GetTagPos(i, "j_head");
				entHead3D.z += 8;
				if (WorldToScreen(entHead3D, entHead2D)) {
					if (esp2D) Draw2DBox(Screen, entHead2D, 2, isVisible(i));
					if (esp3D) draw3DBounded(entHead3D, Centity_s[i].pose.origin, Centity_s[i].pose.origin.y, 25, 2, isVisible(i));
				}
				if (espTri) drawPyramid(Centity_s[i].pose.origin, GetBoxWidth(Centity_s[i]), GetBoxHeight(Centity_s[i]), isVisible(i));
				if (snaplines) drawLine(CenterX, snaplinepos, x, y, 1, isVisible(i));
				if (espdist) drawTextWithBG(va("[%.fm]", GetDistance(cg.ps->Origin, Centity_s[i].pose.origin)), x - 5 / 2, y - 20, smallFont, .5, white, 16, nullptr);
			}
		}
	}
	
	inline void drawESP()
	{
		if (static_cast<int>(0x825564D0) != 0 && static_cast<int>(0x825569F0) != 0 && static_cast<int>(0x825CC068) != 0) {
			if (!bgs.clientinfo[cg.clientNum].valid) return;
			drawAIESP();
		}
	}
}
#endif // TU24SP_ESP_H
