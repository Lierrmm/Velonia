#ifndef TU9SP_ESP_H
#define TU9SP_ESP_H

namespace TU9SP
{
	inline float* isVisible(int i) {
		return redEnemy;
	}

	inline void drawESP() {
		//if (!cg->ClientInfo[cg->cNum].Valid) return;
		auto CenterX = cg.refdef.width / 2;
		for (DWORD i = 0; i < 18; i++)
		{
			if (i == cg.clientNum) continue;
			if (!level.gentities[i].s.lerp.eFlags & 1) continue;
			Vector2 Screen;
		
			if (WorldToScreen(level.gentities[i].sentient->oldOrigin, Screen))
			{
				int x = Screen.x; int y = Screen.y;
				if (snaplines) drawLine(CenterX, snaplinepos, x, y, 1, isVisible(i));
				if (espdist) drawTextWithBG(va("[%.fm]", GetDistance(cg.refdef.view.Origin, level.gentities[i].sentient->oldOrigin)), x - 5 / 2, y - 20, "fonts/smallFont", .5, white, 16, nullptr);
				if (espname) drawTextWithBG(va("%s", level.clients[i].pers.playerName), x - 15 / 2, Screen.y - 36, "fonts/smallFont", .5, white, 16, nullptr);
			}
		}
	}
}
#endif // TU9SP_ESP_H