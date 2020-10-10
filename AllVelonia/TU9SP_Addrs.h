#ifndef TU9SP_ADDRS_H
#define TU9SP_ADDRS_H

namespace TU9SP
{
	bool(*Dvar_GetBool)(const char* dvarName) = reinterpret_cast<bool(*)(const char*)>(0x822E03B0);
	float(*Dvar_GetFloat)(const char* dvarName) = reinterpret_cast<float(*)(const char*)>(0x822E0480);
	int(*Dvar_GetInt)(const char* dvarName) = reinterpret_cast<int(*)(const char*)>(0x822E0418);
	int(*CL_IsLocalClientInGame)(int localClientNum) = reinterpret_cast<int(*)(int)>(0x82131F68);
	void(*CG_GameMessage)(int localClientNum, const char* msg) = reinterpret_cast<void(*)(int, const char*)>(0x820F7EE8);
	void(*CG_GameMessageBold)(int localClientNum, const char* msg) = reinterpret_cast<void(*)(int, const char*)>(0x820F7F08);
	char* (__cdecl* CL_GetConfigString)(int index) = reinterpret_cast<char* (*)(int)>(0x821201A0);
	PCHAR(*va)(PCHAR format, ...) = reinterpret_cast<PCHAR(*)(PCHAR, ...)>(0x822E8568);
	void* (*Cbuf_AddText)(int localClientNum, const char* text) = reinterpret_cast<void* (*)(int, const char*)>(0x8227CF90);

	void* (*Material_RegisterHandle)(const char* r3, int r4) = reinterpret_cast<void* (*)(const char*, int)>(0x8238BE08);
	void* (*R_RegisterFont)(const char* r3, int r4) = reinterpret_cast<void* (*)(const char*, int)>(0x82133898);
	void* (*R_AddCmdDrawStretchPic)(float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, const float* color, void* material) = reinterpret_cast<void* (*)(float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, const float* color, void* material)>(0x82391620);
	void* (*R_AddCmdDrawText)(const char* r3, int r4, void* r5, float f1, float f2, float f3, float f4, float f5, const float* color, int something) = reinterpret_cast<void* (*)(const char* r3, int r4, void* r5, float f1, float f2, float f3, float f4, float f5, const float* color, int something)>(0x82391F00);

	int(__cdecl* R_TextHeight)(void* font) = reinterpret_cast<int(__cdecl*)(void*)>(0x8238B710);
	int(__cdecl* R_TextWidth)(const char* text, int maxchars, void* font) = reinterpret_cast<int(__cdecl*)(const char*, int, void*)>(0x8238B618);
	void(__cdecl* CG_DrawRotatedPicPhysical)(int, float, float, float, float, float, float*, void*) = reinterpret_cast<void(__cdecl*)(int, float, float, float, float, float, float*, void*)>(0x820EA140);
	bool(*CL_IsPauseMenuOpen)() = reinterpret_cast<bool(*)()>(0x82130DB0);
	
	inline void iprintln(char* msg)
	{
		CG_GameMessage(0, msg);
	}

	inline void iprintlnbold(char* msg)
	{
		CG_GameMessageBold(0, msg);
	}

	inline int TextWidth(const char* text, const char* font) {
		return R_TextWidth(text, 0x7FFFFFFF, R_RegisterFont(font, 0));
	}

	inline int TextHeight(const char* font) {
		return R_TextHeight(R_RegisterFont(font, 0));
	}

	inline bool checkLocalClient(int i) {
		return i == cg.clientNum;
	}
}
#endif // TU9SP_ADDRS_H
