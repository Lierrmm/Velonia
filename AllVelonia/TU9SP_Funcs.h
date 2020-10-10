#ifndef TU9SP_FUNCS_H
#define TU9SP_FUNCS_H

namespace TU9SP
{
	#define spreadMultiplier 0.00392156862f
	char* _version = "BETA 0.0.1";

	bool renderRadar, teamnow, thirdperson, radar, sway, recoil, noflinch, toggleFB, vmColor,
		debugmode, drawPointers, drawBarrelESP, drawEndBox, flashing, _noinfect, esp, esptypes, espname, espdist,
		snaplines, drawinfo, walls;
	bool aimbot, snapbot, smoothAim, AimKey, silentaim, autowall, nospread, autoshoot, fakelag;
	bool stealName, eliteClanTag, _showNewsbar;
	bool _antispin, _antiflip, _antix, _antiy, _antishield;
	bool _drawConsoleInfo;
	bool esp2D, esp3D, espTri;

	int packetTimer;

	Vector2 m_radarXY;
	bool canRenderRadar;
	bool hasPatchedRadar;

	bool _mFakeLag = false;

	int cg_fov = 65;
	int cg_gun_x = 0;
	int cg_gun_y = 0;
	int cg_gun_z = 0;
	int customClass = 1;
	int customTeam = 1;
	int chromeVal = 0;
	int colorMap = 1;
	int tpRange = 120;
	int tpAngle = 120;
	int snaplinepos = (740 / 2);
	int targetBone = 0;
	int wallClient = -1;

	char* Bones[20] = {
		"j_helmet", "j_head", "j_neck", "j_shoulder_le", "j_shoulder_ri", "j_elbow_le",
		"j_elbow_ri", "j_wrist_le", "j_wrist_ri", "j_gun",
		"j_mainroot", "j_spineupper", "j_spinelower", "j_spine4",
		"j_hip_ri", "j_hip_le", "j_knee_le", "j_knee_ri", "j_ankle_ri", "j_ankle_le"
	};

	inline const char* boolToStr(bool val) {
		return val ? "[^2ON^7]" : "[^1OFF^7]";
	}

	inline void thirdPerson() {
		thirdperson = !thirdperson;
		Cbuf_AddText(0, va("god %d;", thirdperson));
		iprintln(va("Godmode: %s", boolToStr(thirdperson)));
	}

	inline void toggleChrome() {
		toggleFB = !toggleFB;
		toggleFB ? chromeVal = 2 : chromeVal = 0;
		Cbuf_AddText(0, va("r_specularMap %d;", chromeVal));
		iprintln(va("Chrome Vision: %s", boolToStr(toggleFB)));
	}

	inline void toggleDebugMode() {
		debugmode = !debugmode;
		Cbuf_AddText(0, va("ui_debugmode  %d;", debugmode));
		iprintln(va("Debug Mode: %s", boolToStr(debugmode)));
	}

	inline void toggleWalls() {
		walls = !walls;
		walls ? Cbuf_AddText(0, ";r_znear 45;") : Cbuf_AddText(0, ";r_znear 1;");
		iprintln(va("Wall Hack: %s", boolToStr(walls)));
	}
	
	char* _newsbarTxt = "Welcome to Velonia TU9 | \x14/\x15 to Scroll - \x3 to Select - \x2 to Go Back | Developed By Liam";
	float _newsbarxPos = 1500;
	bool _newsbarPause = false;
	int _pauseTimer, stealTimer, rainTimer = 0;

	inline void newsBar() {
		_showNewsbar = !_showNewsbar;
		iprintln(va("News Bar: %s", boolToStr(_showNewsbar)));
	}

	bool WorldToScreen(Vector3& WorldLocation, Vector2& Screen)
	{
		Vector3 Position = SubstractVector(WorldLocation, cg.refdef.view.Origin);
		Vector3 Transform;
		Transform.x = DotProduct(Position, cg.refdef.view.viewAxis[1]);
		Transform.y = DotProduct(Position, cg.refdef.view.viewAxis[2]);
		Transform.z = DotProduct(Position, cg.refdef.view.viewAxis[0]);
		if (Transform.z < 0.1f) return FALSE;
		Vector2 Center;
		Center.x = cg.refdef.width / 2;
		Center.y = cg.refdef.height / 2;
		Screen.x = Center.x * (1 - (Transform.x / cg.refdef.view.tanHalfFovX / Transform.z));
		Screen.y = Center.y * (1 - (Transform.y / cg.refdef.view.tanHalfFovX / Transform.z));
		return TRUE;
	}
}
#endif // TU9SP_FUNCS_H