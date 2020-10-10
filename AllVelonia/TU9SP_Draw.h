#ifndef TU9SP_DRAW_H
#define TU9SP_DRAW_H

namespace TU9SP
{
	void drawShader(float x, float y, float w, float h, char* material, float* Color) {
		R_AddCmdDrawStretchPic(x, y, w, h, 0, 0, 1, 1, Color, static_cast<void*>(Material_RegisterHandle(material, 0)));
	}

	void drawShader(float x, float y, float w, float h, float* Color, char* material) {
		R_AddCmdDrawStretchPic(x, y, w, h, 0, 0, 1, 1, Color, static_cast<void*>(Material_RegisterHandle(material, 0)));
	}

	void drawShaderOutlined(float x, float y, float w, float h, float* backgroundColor, float* outlineColor, float lineWidth) {
		drawShader(x + lineWidth, y + lineWidth, w - (lineWidth * 2), h - (lineWidth * 2), "white", backgroundColor);
		drawShader(x, y, lineWidth, h, "white", outlineColor);
		drawShader(x + lineWidth, y, w - lineWidth, lineWidth, "white", outlineColor);
		drawShader(x + lineWidth, y + h - lineWidth, w - (lineWidth * 2), lineWidth, "white", outlineColor);
		drawShader(x + w - lineWidth, y + lineWidth, lineWidth, h - lineWidth, "white", outlineColor);
	}

	void drawText(const char* text, float x, float y, char* font, float fontSize, float* Color) {
		R_AddCmdDrawText(text, 0x7FFFFFFF, static_cast<void*>(R_RegisterFont(font, 0)), x, y, fontSize, fontSize, 0, Color, 0);
	}

	void drawTextWithBG(const char* text, float x, float y, char* font, float fontSize, float* color, float h, char* shader)
	{
		drawText(text, x - (R_TextWidth(text, 0x7FFFFFFF, R_RegisterFont(font, 0)) * fontSize / 3.5f) + 2, y + h, font, fontSize, color);
		if (shader != nullptr) drawShader(x - (R_TextWidth(text, 0x7FFFFFFF, R_RegisterFont(font, 0)) * fontSize / 2) - 20, y + h - 15, 20, 20, white, shader);
	}

	void drawRightText(const char* text, float x, float y, char* font, float fontSize, float* Color) {
		R_AddCmdDrawText(text, 0x7FFFFFFF, static_cast<void*>(R_RegisterFont(font, 0)), (x - (TextWidth(text, font) / 1) * fontSize), y, fontSize, fontSize, 0, Color, 0);
	}

	void drawCenterText(const char* text, float x, float y, char* font, float fontSize, float* Color) {
		R_AddCmdDrawText(text, 0x7FFFFFFF, static_cast<void*>(R_RegisterFont(font, 0)), (x - (TextWidth(text, font) / 2) * fontSize), y, fontSize, fontSize, 0, Color, 0);
	}

	void drawShadowText(const char* text, float x, float y, char* font, float fontSize, float* Color, float* sColor) {
		R_AddCmdDrawText(text, 0x7FFFFFFF, static_cast<void*>(R_RegisterFont(font, 0)), x + 1, y + 1, fontSize, fontSize, 0, sColor, 0);
		R_AddCmdDrawText(text, 0x7FFFFFFF, static_cast<void*>(R_RegisterFont(font, 0)), x, y, fontSize, fontSize, 0, Color, 0);
	}

	void drawRightShadowText(const char* text, float x, float y, char* font, float fontSize, float* Color, float* sColor) {
		R_AddCmdDrawText(text, 0x7FFFFFFF, static_cast<void*>(R_RegisterFont(font, 0)), (x - (TextWidth(text, font) / 1) * fontSize) + 1, y + 1, fontSize, fontSize, 0, sColor, 0);
		R_AddCmdDrawText(text, 0x7FFFFFFF, static_cast<void*>(R_RegisterFont(font, 0)), (x - (TextWidth(text, font) / 1) * fontSize), y, fontSize, fontSize, 0, Color, 0);
	}

	void drawCenterShadowText(const char* text, float x, float y, char* font, float fontSize, float* Color, float* sColor) {
		R_AddCmdDrawText(text, 0x7FFFFFFF, static_cast<void*>(R_RegisterFont(font, 0)), (x - (TextWidth(text, font) / 2) * fontSize) + 1, y + 1, fontSize, fontSize, 0, sColor, 0);
		R_AddCmdDrawText(text, 0x7FFFFFFF, static_cast<void*>(R_RegisterFont(font, 0)), (x - (TextWidth(text, font) / 2) * fontSize), y, fontSize, fontSize, 0, Color, 0);
	}

	void drawTextWithShader(const char* text, const char* font, float x, float y, float fontSize, float* color, float* bcolor) {
		drawShader((x - 2), (y - (TextHeight(font) * fontSize)), ((TextWidth(text, font) * fontSize) + 4), TextHeight(font) * fontSize, "white", bcolor);
		R_AddCmdDrawText(text, 0x7FFFFFFF, static_cast<void*>(R_RegisterFont(font, 0)), x, y, fontSize, fontSize, 0, color, 0);
	}

	void drawRightTextWithShader(const char* text, const char* font, float x, float y, float fontSize, float* color, float* bcolor) {
		drawShader(((x - 2) - (TextWidth(text, font) / 1) * fontSize), (y - (TextHeight(font) * fontSize)), ((TextWidth(text, font) * fontSize) + 4), TextHeight(font) * fontSize, "white", bcolor);
		R_AddCmdDrawText(text, 0x7FFFFFFF, static_cast<void*>(R_RegisterFont(font, 0)), (x - (TextWidth(text, font) / 1) * fontSize), y, fontSize, fontSize, 0, color, 0);
	}

	void drawCenterTextWithShader(const char* text, const char* font, float x, float y, float fontSize, float* color, float* bcolor) {
		drawShader(((x - 2) - (TextWidth(text, font) / 2) * fontSize), (y - (TextHeight(font) * fontSize)), ((TextWidth(text, font) * fontSize) + 4), TextHeight(font) * fontSize, "white", bcolor);
		R_AddCmdDrawText(text, 0x7FFFFFFF, static_cast<void*>(R_RegisterFont(font, 0)), (x - (TextWidth(text, font) / 2) * fontSize), y, fontSize, fontSize, 0, color, 0);
	}

	void drawBoxWithOutline(float x, float y, float w, float h, float* color)
	{
		drawShader(x, y, 1, h, color, "white");
		drawShader(x + w, y, 1, h, color, "white");
		drawShader(x, y, w, 1, color, "white");
		drawShader(x, y + h, w + 1, 1, color, "white");
	}

	void drawNewsBar() {
		drawShader(0, 680, 1280, 40, black, "white");
		drawShader(0, 679, 1280, 1, MenuSelectedColor, "white");
		drawText(va("%s", _newsbarTxt), _newsbarxPos, 714, smallFont, 1, white);
		if (_showNewsbar && !_newsbarPause) _newsbarxPos -= 1;
		if (_newsbarxPos == 250) { _newsbarPause = true; _pauseTimer++; }
		if (_pauseTimer == 400) { _pauseTimer = 0; _newsbarPause = false; }
		if (_newsbarxPos <= -1000) _newsbarxPos = 1500;
	}

	void drawLine(float X1, float Y1, float X2, float Y2, float Width, float* Colors) {
		float X, Y, Angle, L1, L2, H1;
		H1 = Y2 - Y1;
		L1 = X2 - X1;
		L2 = sqrt(L1 * L1 + H1 * H1);
		X = X1 + ((L1 - L2) / 2);
		Y = Y1 + (H1 / 2);
		Angle = static_cast<float>(atan(H1 / L1)) * (180 / 3.14159265358979323846);
		CG_DrawRotatedPicPhysical(srcPlacement, X, Y, L2, Width, Angle, Colors, Material_RegisterHandle("white", 0));
	}

	void drawLine(Vector2 src, Vector2 dst, int thickness, float* color)
	{
		drawLine(src.x, src.y, dst.x, dst.y, thickness, color);
	}

	void GameInfo(char* text, float x, float y, char* font, float fontSize, float* color)
	{
		const auto textWid = R_TextWidth(text, 0x7FFFFFFF, R_RegisterFont("fonts/bigFont", 0)) * fontSize;
		drawBoxWithOutline(x, y - 17, textWid + 10, 22, MenuSelectedColor);
		drawShader(x, y - 17, textWid + 10, 22, black, "white");
		drawText(text, x + 5, y + 2, font, fontSize, color);
	}

	void GameInfoNoPadding(char* text, float x, float y, char* font, float fontSize, float* color) {
		const auto textWid = R_TextWidth(text, 0x7FFFFFFF, R_RegisterFont("fonts/bigFont", 0)) * fontSize;
		drawBoxWithOutline(x, y - 17, textWid, 32, MenuSelectedColor);
		drawShader(x, y - 17, textWid, 32, black, "white");
		drawText(text, x + 15, y + 10, font, fontSize, color);
	}

	void drawInfo() {
		const auto pos = 210;
		GameInfo(va("Server: %s", cs.servername), 5, pos + (27 * 0), "fonts/bigFont", .3f, white);
		//GameInfo(va("Health: %d", cg->Health), 5, pos + (27 * 1), "fonts/bigFont", .3f, white);
		GameInfo(va("Entity Count: %d", cg.snap->numEntities), 5, pos + (27 * 1), "fonts/bigFont", .3f, white);
	}

	void drawConsoleInfo() {
		GameInfo(va("Input: %s", Console.GetAVPackName()), 99, 13 + (27 * 0), "fonts/bigFont", .3f, white);
		GameInfo(va("CPU: %.1f", Console.GetTemperature(CPU, true)), 172, 13, "fonts/bigFont", .3f, white);
		GameInfo(va("GPU: %.1f", Console.GetTemperature(GPU, true)), 233, 13, "fonts/bigFont", .3f, white);
		GameInfo(va("Mem: %.1f", Console.GetTemperature(MEM, true)), 295, 13, "fonts/bigFont", .3f, white);
		GameInfo(va("Case: %.1f", Console.GetTemperature(BRD, true)), 359, 13, "fonts/bigFont", .3f, white);
	}
}
#endif // TU9SP_DRAW_H
