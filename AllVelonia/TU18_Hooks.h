#ifndef TU18_HOOKS_H
#define TU18_HOOKS_H

namespace TU18
{
	detour<void> VMHook;

    const char* SL_ConvertToString(int stringValue)
    {
        const char* (*SL_ConvertToString)(int stringValue) = (const char* (*)(int))0x82532A18;
        return SL_ConvertToString(stringValue);
    }

    void Scr_AddString(const char* value)
    {
        void(*Scr_AddString)(int instance, const char* value) = (void(*)(int, const char*))0x8253D9C8;
        Scr_AddString(1, value);
    }
    void(*Scr_NotifyNum)(int entIndex, int classNum, int stringValue, int paramCount) = (void(*)(int, int, int, int))0x8253CF78;
    void(*Scr_ClearOutParams)() = (void(*)())0x8253BA98;
    void(*SetDvar)() = (void(*)())0x8234C9C0;
    void(*MakeDvarServerInfo)() = (void(*)())0x8234CB68;
    void GScr_SetDvar(const char* dvarName, const char* value)
    {
        Scr_AddString(value);
        Scr_AddString(dvarName);
        SetDvar();
        Scr_ClearOutParams();
    }
    void GScr_MakeDvarServerInfo(const char* dvarName, const char* value)
    {
        Scr_AddString(value);
        Scr_AddString(dvarName);
        MakeDvarServerInfo();
        Scr_ClearOutParams();
    }


	inline void iniTU18()
	{
		
	}
}
#endif // TU18_HOOKS_H
