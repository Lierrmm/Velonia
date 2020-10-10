namespace TU11
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

	/*void drawNewsBar() {
		drawShader(0, 680, 1280, 40, black, "white");
		drawShader(0, 679, 1280, 1, MenuSelectedColor, "white");
		drawText(va("%s", _newsbarTxt), _newsbarxPos, 714, smallFont, 1, white);
		if (_showNewsbar && !_newsbarPause) _newsbarxPos -= 1;
		if (_newsbarxPos == 250) { _newsbarPause = true; _pauseTimer++; }
		if (_pauseTimer == 400) { _pauseTimer = 0; _newsbarPause = false; }
		if (_newsbarxPos <= -1000) _newsbarxPos = 1500;
	}*/

	void drawLine(float X1, float Y1, float X2, float Y2, float Width, float* Colors) {
		float X, Y, Angle, L1, L2, H1;
		H1 = Y2 - Y1;
		L1 = X2 - X1;
		L2 = sqrt(L1 * L1 + H1 * H1);
		X = X1 + ((L1 - L2) / 2);
		Y = Y1 + (H1 / 2);
		Angle = static_cast<float>(atan(H1 / L1)) * (180 / 3.14159265358979323846);
		CG_DrawRotatedPicPhysical(0x828398F8, X, Y, L2, Width, Angle, Colors, Material_RegisterHandle("white", 0));
	}

	void drawLine(Vector2 src, Vector2 dst, int thickness, float* color)
	{
		drawLine(src.x, src.y, dst.x, dst.y, thickness, color);
	}

	VOID MakeESPLine(Vector3 Center, FLOAT X1, FLOAT Y1, FLOAT Z1, FLOAT X2, FLOAT Y2, FLOAT Z2, float* Color, int Width)
	{
		Vector2 XY1, XY2;
		if (WorldToScreen(Vector3(Center.x + X1, Center.y + Y1, Center.z + Z1), XY1) &&
			WorldToScreen(Vector3(Center.x + X2, Center.y + Y2, Center.z + Z2), XY2))
		{
			drawLine(XY1.x, XY1.y, XY2.x, XY2.y, Width, Color);
		}
	}

	VOID Make3DBox(Vector3 Center, FLOAT W, FLOAT H, float* Color)
	{
		MakeESPLine(Center, -W, -W, 0, W, -W, 0, Color, 1);
		MakeESPLine(Center, -W, -W, 0, -W, W, 0, Color, 1);
		MakeESPLine(Center, W, W, 0, W, -W, 0, Color, 1);
		MakeESPLine(Center, W, W, 0, -W, W, 0, Color, 1);
		MakeESPLine(Center, -W, -W, 0, -W, -W, H, Color, 1);
		MakeESPLine(Center, -W, W, 0, -W, W, H, Color, 1);
		MakeESPLine(Center, W, -W, 0, W, -W, H, Color, 1);
		MakeESPLine(Center, W, W, 0, W, W, H, Color, 1);
		MakeESPLine(Center, -W, -W, H, W, -W, H, Color, 1);
		MakeESPLine(Center, -W, -W, H, -W, W, H, Color, 1);
		MakeESPLine(Center, W, W, H, W, -W, H, Color, 1);
		MakeESPLine(Center, W, W, H, -W, W, H, Color, 1);
	}

	void draw3DBounded(Vector3 top, Vector3 bot, float a, int width, int thickness, float* color)
	{
		int height = abs(top.z - bot.z);
		Vector3 b1, b2, b3, b4, t1, t2, t3, t4;
		b1.z = b2.z = b3.z = b4.z = bot.z;

		b1.x = bot.x + (cos(TORAD(a + 45)) * width);
		b1.y = bot.y + (sin(TORAD(a + 45)) * width);
		b2.x = bot.x + (cos(TORAD(a + 135)) * width);
		b2.y = bot.y + (sin(TORAD(a + 135)) * width);
		b3.x = bot.x + (cos(TORAD(a + 225)) * width);
		b3.y = bot.y + (sin(TORAD(a + 225)) * width);
		b4.x = bot.x + (cos(TORAD(a + 315)) * width);
		b4.y = bot.y + (sin(TORAD(a + 315)) * width);

		t1.x = b1.x;
		t1.y = b1.y;
		t1.z = b1.z + height;
		t2.x = b2.x;
		t2.y = b2.y;
		t2.z = b2.z + height;
		t3.x = b3.x;
		t3.y = b3.y;
		t3.z = b3.z + height;
		t4.x = b4.x;
		t4.y = b4.y;
		t4.z = b4.z + height;

		Vector2 b1_2, b2_2, b3_2, b4_2, t1_2, t2_2, t3_2, t4_2;

		if (WorldToScreen(b1, b1_2) && WorldToScreen(b2, b2_2) && WorldToScreen(b3, b3_2) && WorldToScreen(b4, b4_2)
			&& WorldToScreen(t1, t1_2) && WorldToScreen(t2, t2_2) && WorldToScreen(t3, t3_2)
			&& WorldToScreen(t4, t4_2))
		{
			drawLine(t1_2, b1_2, thickness, color);
			drawLine(t2_2, b2_2, thickness, color);
			drawLine(t3_2, b3_2, thickness, color);
			drawLine(t4_2, b4_2, thickness, color);

			drawLine(t1_2, t2_2, thickness, color);
			drawLine(t2_2, t3_2, thickness, color);
			drawLine(t3_2, t4_2, thickness, color);
			drawLine(t4_2, t1_2, thickness, color);

			drawLine(b1_2, b2_2, thickness, color);
			drawLine(b2_2, b3_2, thickness, color);
			drawLine(b3_2, b4_2, thickness, color);
			drawLine(b4_2, b1_2, thickness, color);
		}
	}

	void Draw2DBox(Vector2 top, Vector2 bot, int thickness, float* color)
	{
		int height = abs(top.y - bot.y);
		Vector2 tl, tr;
		tl.x = top.x - height / 4;
		tr.x = top.x + height / 4;
		tl.y = tr.y = top.y;

		Vector2 bl, br;
		bl.x = bot.x - height / 4;
		br.x = bot.x + height / 4;
		bl.y = br.y = bot.y;

		drawLine(tl, tr, thickness, color);
		drawLine(bl, br, thickness, color);
		drawLine(tl, bl, thickness, color);
		drawLine(tr, br, thickness, color);
	}

	void drawPyramid(Vector3 center, float w, float h, float* color)
	{
		MakeESPLine(center, -w, -w, 0, w, -w, 0, color, 1);
		MakeESPLine(center, -w, -w, 0, -w, w, 0, color, 1);
		MakeESPLine(center, w, w, 0, w, -w, 0, color, 1);
		MakeESPLine(center, w, w, 0, -w, w, 0, color, 1);
		MakeESPLine(center, -w, -w, 0, 0, 0, h, color, 1);
		MakeESPLine(center, -w, w, 0, 0, 0, h, color, 1);
		MakeESPLine(center, w, -w, 0, 0, 0, h, color, 1);
		MakeESPLine(center, w, w, 0, 0, 0, h, color, 1);
	}

	void drawLines(Vector3 Origin, float X1, float Y1, float Z1, float X2, float Y2, float Z2, float* Color, int Size) {
		Vector2 Screen1, Screen2;
		Vector3 Origin1(Origin.x + X1, Origin.y + Y1, (Origin.z + Z1) - 5);
		Vector3 Origin2(Origin.x + X2, Origin.y + Y2, (Origin.z + Z2) - 5);
		if (WorldToScreen(Origin1, Screen1) && WorldToScreen(Origin2, Screen2)) {
			drawLine(Screen1.x, Screen1.y, Screen2.x, Screen2.y, Size, Color);
		}
	}

	void drawBoneLine(pCentity_t entity, int ent, char* tagname1, char* tagname2, float* color) {
		Vector3 Origin1 = GetTagPos(ent, tagname1), Origin2 = GetTagPos(ent, tagname2);
		Vector2 Loc1, Loc2;
		if (WorldToScreen(Origin1, Loc1) && WorldToScreen(Origin2, Loc2)) {
			drawLine(Loc1.x, Loc1.y, Loc2.x, Loc2.y, 1.25, color);
		}
	}

	void doAllBones(int Client, float* boneESPCol) {
		pCentity_t ent = &Centity_s[Client];
		int entNum = Client;
		drawBoneLine(ent, entNum, "j_head", "j_neck", boneESPCol);
		drawBoneLine(ent, entNum, "j_neck", "j_shoulder_le", boneESPCol);
		drawBoneLine(ent, entNum, "j_shoulder_le", "j_elbow_le", boneESPCol);
		drawBoneLine(ent, entNum, "j_elbow_le", "j_wrist_le", boneESPCol);
		drawBoneLine(ent, entNum, "j_neck", "j_shoulder_ri", boneESPCol);
		drawBoneLine(ent, entNum, "j_shoulder_ri", "j_elbow_ri", boneESPCol);
		drawBoneLine(ent, entNum, "j_elbow_ri", "j_wrist_ri", boneESPCol);
		drawBoneLine(ent, entNum, "j_neck", "j_mainroot", boneESPCol);
		drawBoneLine(ent, entNum, "j_mainroot", "j_hip_le", boneESPCol);
		drawBoneLine(ent, entNum, "j_hip_le", "j_knee_le", boneESPCol);
		drawBoneLine(ent, entNum, "j_knee_le", "j_ankle_le", boneESPCol);
		drawBoneLine(ent, entNum, "j_mainroot", "j_hip_ri", boneESPCol);
		drawBoneLine(ent, entNum, "j_hip_ri", "j_knee_ri", boneESPCol);
		drawBoneLine(ent, entNum, "j_knee_ri", "j_ankle_ri", boneESPCol);
	}

	void draw3DBox(int client, float* sColor) {
		Vector3 Center = Centity_s[client].Origin;
		float W = GetBoxWidth(&Centity_s[client]), H = GetBoxHeight(&Centity_s[client]);
		drawLines(Center, -W, -W, 0, -W + (W / 2), -W, 0, sColor, 1);
		drawLines(Center, W / 2, -W, 0, W, -W, 0, sColor, 1);
		drawLines(Center, -W, -W, 0, -W, -W + (W / 2), 0, sColor, 1);
		drawLines(Center, -W, W - (W / 2), 0, -W, W, 0, sColor, 1);
		drawLines(Center, W, -W + (W / 2), 0, W, -W, 0, sColor, 1);
		drawLines(Center, W, W - (W / 2), 0, W, W, 0, sColor, 1);
		drawLines(Center, -W + (W / 2), W, 0, -W, W, 0, sColor, 1);
		drawLines(Center, W, W, 0, W - (W / 2), W, 0, sColor, 1);
		drawLines(Center, -W, -W, 0, -W, -W, H / 6, sColor, 1);
		drawLines(Center, -W, -W, H, -W, -W, H - (H / 6), sColor, 1);
		drawLines(Center, -W, W, 0, -W, W, H / 6, sColor, 1);
		drawLines(Center, -W, W, H, -W, W, H - (H / 6), sColor, 1);
		drawLines(Center, W, -W, 0, W, -W, H / 6, sColor, 1);
		drawLines(Center, W, -W, H, W, -W, H - (H / 6), sColor, 1);
		drawLines(Center, W, W, 0, W, W, H / 6, sColor, 1);
		drawLines(Center, W, W, H, W, W, H - (H / 6), sColor, 1);
		drawLines(Center, -W, -W, H, -W + (W / 2), -W, H, sColor, 1);
		drawLines(Center, W / 2, -W, H, W, -W, H, sColor, 1);
		drawLines(Center, -W, -W, H, -W, -W + (W / 2), H, sColor, 1);
		drawLines(Center, -W, W - (W / 2), H, -W, W, H, sColor, 1);
		drawLines(Center, W, -W + (W / 2), H, W, -W, H, sColor, 1);
		drawLines(Center, W, W - (W / 2), H, W, W, H, sColor, 1);
		drawLines(Center, -W + (W / 2), W, H, -W, W, H, sColor, 1);
		drawLines(Center, W, W, H, W - (W / 2), W, H, sColor, 1);
	}

	void drawTriBox(int client, float* sColor) {
		Vector3 Center = Centity_s[client].Origin;
		float W = GetBoxWidth(&Centity_s[client]), H = GetBoxHeight(&Centity_s[client]);
		W *= 1.5; H *= 1.25;
		drawLines(Center, -W, -W, 0, W, -W, 0, sColor, 1);
		drawLines(Center, -W, -W, 0, -W, W, 0, sColor, 1);
		drawLines(Center, W, W, 0, W, -W, 0, sColor, 1);
		drawLines(Center, W, W, 0, -W, W, 0, sColor, 1);
		drawLines(Center, -W, -W, 0, 0, 0, H, sColor, 1);
		drawLines(Center, -W, W, 0, 0, 0, H, sColor, 1);
		drawLines(Center, W, -W, 0, 0, 0, H, sColor, 1);
		drawLines(Center, W, W, 0, 0, 0, H, sColor, 1);
	}

	void drawBoundingBox(Vector3 HeadOrigin, float W, float H, float* sColor) {
		drawLines(HeadOrigin, -W, W, 0, W, W, 0, sColor, 1);
		drawLines(HeadOrigin, -W, W, 0, -W, W, H, sColor, 1);
		drawLines(HeadOrigin, W, W, 0, W, W, H, sColor, 1);
		drawLines(HeadOrigin, -W, W, H, W, W, H, sColor, 1);
		drawLines(HeadOrigin, -W, W, 0, -W, -W, 0, sColor, 1);
		drawLines(HeadOrigin, W, -W, 0, W, W, 0, sColor, 1);
		drawLines(HeadOrigin, W, -W, 0, -W, -W, 0, sColor, 1);
		drawLines(HeadOrigin, -W, -W, 0, -W, -W, H, sColor, 1);
		drawLines(HeadOrigin, W, -W, 0, W, -W, H, sColor, 1);
		drawLines(HeadOrigin, -W, W, H, -W, -W, H, sColor, 1);
		drawLines(HeadOrigin, W, -W, H, W, W, H, sColor, 1);
		drawLines(HeadOrigin, W, -W, H, -W, -W, H, sColor, 1);
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
		GameInfo(va("Map: %s", UI_GetMapDisplayName(Dvar_GetString("ui_mapname"))), 5, pos + (27 * 0), "fonts/bigFont", .3f, white);
		GameInfo(va("Game: %s", UI_GetGameTypeDisplayName(cgs->GameType)), 5, pos + (27 * 1), "fonts/bigFont", .3f, white);
		GameInfo(va("FPS: %.0f", (uicontext.fps / 2)), 5, pos + (27 * 2), "fonts/bigFont", .3f, white);
		GameInfo(va("Host: %s", cgs->Host), 5, pos + (27 * 3), "fonts/bigFont", .3f, white);
		GameInfo(va("Ping: %d", snapshot.ping), 5, pos + (27 * 4), "fonts/bigFont", .3f, white);
		GameInfo(va("Health: %d", cg->Health), 5, pos + (27 * 5), "fonts/bigFont", .3f, white);
		GameInfo(va("Connected Clients: %d", snapshot.connectedClients), 5, pos + (27 * 6), "fonts/bigFont", .3f, white);
		GameInfo(va("Entity Count: %d", snapshot.entityCount), 5, pos + (27 * 7), "fonts/bigFont", .3f, white);
	}

	void drawConsoleInfo() {
		GameInfo(va("Input: %s", Console.GetAVPackName()), 99, 13 + (27 * 0), "fonts/bigFont", .3f, white);
		GameInfo(va("CPU: %.1f", Console.GetTemperature(CPU, true)), 172, 13, "fonts/bigFont", .3f, white);
		GameInfo(va("GPU: %.1f", Console.GetTemperature(GPU, true)), 233, 13, "fonts/bigFont", .3f, white);
		GameInfo(va("Mem: %.1f", Console.GetTemperature(MEM, true)), 295, 13, "fonts/bigFont", .3f, white);
		GameInfo(va("Case: %.1f", Console.GetTemperature(BRD, true)), 359, 13, "fonts/bigFont", .3f, white);
	}
}