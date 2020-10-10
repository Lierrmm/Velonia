#pragma once
#define normalFont					"fonts/normalFont"
#define consoleFont					"fonts/consoleFont"
#define hudBigFont					"fonts/hudBigFont"
#define hudSmallFont				"fonts/hudSmallFont"
#define extraBigFont				"fonts/extraBigFont"
#define smallFont					"fonts/smallFont"
#define bigFont						"fonts/bigFont"
#define objectiveFont				"fonts/objectiveFont"
#define boldFont					"fonts/boldFont"
#define smallDevFont				"fonts/smallDevFont"
#define bigDevFont					"fonts/bigDevFont"

#define BO2normalFont				"fonts/720/normalFont"
#define BO2consoleFont				"fonts/720/consoleFont"
#define BO2hudBigFont				"fonts/720/hudBigFont"
#define BO2hudSmallFont				"fonts/720/hudSmallFont"
#define BO2extraBigFont				"fonts/720/extraBigFont"
#define BO2smallFont				"fonts/720/smallFont"
#define BO2bigFont					"fonts/720/bigFont"
#define BO2objectiveFont			"fonts/720/objectiveFont"
#define BO2boldFont					"fonts/720/boldFont"
#define BO2smallDevFont				"fonts/720/smallDevFont"
#define BO2bigDevFont				"fonts/720/bigDevFont"

float colorWhiteTrans[4] = { 1.0f, 1.0f, 1.0f, 0.6f };
float colorBlackTrans[4] = { 0.0f, 0.0f, 0.0f, 0.6f };
float colorRedTrans[4] = { 1.0f, 0.0f, 0.0f, 0.6f };
float colorGreenTrans[4] = { 0.0f, 1.0f, 0.0f, 0.6f };
float colorBlueTrans[4] = { 0.0f, 0.0f, 1.0f, 0.6f };
float colorOrangeTrans[4] = { 1.0f, 0.4f, 0.0f, 0.6f };
float colorYellowTrans[4] = { 1.0f, 1.0f, 0.0f, 0.6f };

float colorBlack[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
float colorWhite[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
float colorRed[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
float colorGreen[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
float colorBlue[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
float colorOrange[4] = { 1.0f, 0.4f, 0.0f, 1.0f };
float colorYellow[4] = { 1.0f, 1.0f, 0.0f, 1.0f };

float colorMenu[4] = { 0.0f, 0.482f, 0.655f, 0.55f };


float white[4] = { 1, 1, 1, 1 };
float whiteTrans[4] = { 1, 1, 1, 0.5 };
float black[4] = { 0, 0, 0, 0.4 };
float emptyColor[4] = { 0, 0, 0, 0 };
float mainColor[4] = { 0.259, 0.957, 0.608, 1 };
float redEnemy[4] = { 0.776, 0.122, 0.122, 1 };
float mainColorAlpha[4] = { 0.259, 0.957, 0.608, .4 };
float mellowYellow[4] = { 1, 0.949, 0.459, 1 };
float Friendly[4] = { 0.271, 0.8, 0.271, 1 };
float wallBlue[4] = { 0.192, 0.647, 0.737, 1 };
float lilac[4] = { 0.714, 0.4, 0.824, 1 };
float hideWithAlpha[4] = { 0, 0, 0, 0 };
float darkPink[4] = { 0.827, 0.149, 0.6, 1 };
float Orangade[4] = { 1, 0.549, 0.259, 1 };
float Smoke[4] = { 0.5, 0.5, 0.5, 1 };
float dirtyGreen[4] = { 0.655, 0.831, 0.608, 1 };

float RedMenu[4] = { 0.8, 0.169, 0.2, 1 };
float YellowMenu[4] = { 0.886, 0.91, 0.18, 1 };
float GreenMenu[4] = { 0.192, 0.741, 0.165, 1 };
float OrangeMenu[4] = { 0.82, 0.616, 0, 1 };
float PinkMenu[4] = { 0.851, 0.212, 0.627, 1 };
float GreyMenu[4] = { 0.322, 0.29, 0.31, 1 };
float WhiteMenu[4] = { 1, 1, 1, 1 };
float PurpleMenu[4] = { 0.522, 0.224, 0.749, 1 };
float MenuSelectedColor[4] = { 0.259, 0.957, 0.608, 1 };
float primaryColor[4] = { 0.827, 0.149, 0.6, 1 };
float secondaryColor[4] = { 0.192, 0.647, 0.737, 1 };
float playerColor[4] = { 0.090, 0.780, 0.459, 1 };
float Friendlies[4] = { 0.216, 0.780, 0.459, 1 };
float Enemies[4] = { 0.780, 0.216, 0.216, 1 };

float* defaultMenuColor = colorMenu;
float* defaultText = colorWhite;
float* defaultBackground = colorBlackTrans;
float* defaultScroller = defaultMenuColor;
float* defaultVisible = colorOrangeTrans;
float* defaultHittable = colorYellowTrans;
float* defaultPriority = colorWhiteTrans;
float* defaultFriendly = colorGreenTrans;
float* defaultEnemy = colorRed;

void updateScrollerColor(const float* color) {
	mainColorAlpha[0] = color[0];
	mainColorAlpha[1] = color[1];
	mainColorAlpha[2] = color[2];
}

void updateColorInfo(float* color) {
	MenuSelectedColor[0] = color[0];
	MenuSelectedColor[1] = color[1];
	MenuSelectedColor[2] = color[2];
	MenuSelectedColor[3] = color[3];
	updateScrollerColor(color);
}

enum MENUS {
	MAIN,
	SELF,
	ESP,
	AIMBOT,
	DVARS,
	THEME,
	MISC,
	PLAYERS,
	ANTIAIM,
	GUNPOS,
	MENUSETTINGS,
	ESPTYPE,
	DEBUG
};

const char* getCurMenu(int a) {
	switch (a) {
	case MAIN: return "Main Menu";
	case SELF: return "Self Menu";
	case ESP: return "ESP Menu";
	case AIMBOT: return "Aimbot Menu";
	case DVARS: return "Dvar Menu";
	case THEME: return "Theme Settings";
	case MISC: return "Misc Menu";
	case PLAYERS: return "Player Menu";
	case ANTIAIM: return "Anti Aim";
	case GUNPOS: return "Gun Position";
	case MENUSETTINGS: return "Menu Settings";
	default: return "Main Menu";
	}
}

#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}

smc Console;