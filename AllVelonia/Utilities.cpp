#include "stdafx.h"

pDmSetMemory DevSetMemory = NULL;
BYTE HvxPeekBYTE(QWORD Address) { return (BYTE)HvxExpansionCall(HvxPeekPokeExpID, PEEK_BYTE, Address); }
WORD HvxPeekWORD(QWORD Address) { return (WORD)HvxExpansionCall(HvxPeekPokeExpID, PEEK_WORD, Address); }
DWORD HvxPeekDWORD(QWORD Address) { return (DWORD)HvxExpansionCall(HvxPeekPokeExpID, PEEK_DWORD, Address); }
QWORD HvxPeekQWORD(QWORD Address) { return HvxExpansionCall(HvxPeekPokeExpID, PEEK_QWORD, Address); }

enum DL_ORDINAL : DWORD {
	DL_ORDINAL_LDAT = 1,
	DL_ORDINAL_STARTSYSMOD = 2,
	DL_ORDINAL_SHUTDOWN = 3,
	DL_ORDINAL_FORCEINILOAD = 4,
	DL_ORDINAL_GETNUMOPTS = 5,
	DL_ORDINAL_GETOPTINFO = 6,
	DL_ORDINAL_GETOPTVAL = 7,
	DL_ORDINAL_SETOPTVAL = 8,
	DL_ORDINAL_GETOPTVALBYNAME = 9,
	DL_ORDINAL_SETOPTVALBYNAME = 0xA,
	DL_ORDINAL_GETDRIVELIST = 0xB,
	DL_ORDINAL_GETDRIVEINFO = 0xC
};


#define GetPointer(X) *(PDWORD)(X)
#define CSleep(X) Sleep(X * 1000)

PWCHAR Utils::charToWChar(__in LPCSTR c_buffer) {
	INT wchars_num = MultiByteToWideChar(CP_ACP, 0, c_buffer, -1, NULL, 0);
	PWCHAR c_wbuffer = new WCHAR[wchars_num];
	MultiByteToWideChar(CP_ACP, 0, c_buffer, -1, (LPWSTR)c_wbuffer, wchars_num);
	return c_wbuffer;
}

INT Utils::toWCHAR(char* input, WCHAR* output) {
	if (!input || !output) return 0;
	INT len = strlen(input);
	memset(output, 0, (len * 2) + 2);
	for (INT i = 1, b = 0; b < len; i += 2) {
		((char*)output)[i] = input[b];
		b++;
	}
	return len;
}

VOID __declspec(naked) GLPR(VOID) {
	__asm {
		std     r14, -0x98(sp)
		std     r15, -0x90(sp)
		std     r16, -0x88(sp)
		std     r17, -0x80(sp)
		std     r18, -0x78(sp)
		std     r19, -0x70(sp)
		std     r20, -0x68(sp)
		std     r21, -0x60(sp)
		std     r22, -0x58(sp)
		std     r23, -0x50(sp)
		std     r24, -0x48(sp)
		std     r25, -0x40(sp)
		std     r26, -0x38(sp)
		std     r27, -0x30(sp)
		std     r28, -0x28(sp)
		std     r29, -0x20(sp)
		std     r30, -0x18(sp)
		std     r31, -0x10(sp)
		stw     r12, -0x8(sp)
		blr
	}
}

DWORD RelinkGPLR(DWORD SFSOffset, PDWORD SaveStubAddress, PDWORD OriginalAddress) {
	DWORD Instruction = 0, Replacing;
	PDWORD Saver = (PDWORD)GLPR;
	if (SFSOffset & 0x2000000)
		SFSOffset = SFSOffset | 0xFC000000;
	Replacing = OriginalAddress[SFSOffset / 4];
	for (INT i = 0; i < 20; i++) {
		if (Replacing == Saver[i]) {
			DWORD NewOffset = (DWORD)&Saver[i] - (DWORD)SaveStubAddress;
			Instruction = 0x48000001 | (NewOffset & 0x3FFFFFC);
		}
	}
	return Instruction;
}

VOID Utils::HookFunctionStart(PDWORD Address, PDWORD SaveStub, DWORD Destination) {
	if ((SaveStub != NULL) && (Address != NULL)) {
		DWORD AddressRelocation = (DWORD)(&Address[4]);
		if (AddressRelocation & 0x8000)
			SaveStub[0] = 0x3D600000 + (((AddressRelocation >> 16) & 0xFFFF) + 1);
		else
			SaveStub[0] = 0x3D600000 + ((AddressRelocation >> 16) & 0xFFFF);
		SaveStub[1] = 0x396B0000 + (AddressRelocation & 0xFFFF);
		SaveStub[2] = 0x7D6903A6;
		for (INT i = 0; i < 4; i++)
		{
			if ((Address[i] & 0x48000003) == 0x48000001)
				SaveStub[i + 3] = RelinkGPLR((Address[i] & ~0x48000003), &SaveStub[i + 3], &Address[i]);
			else
				SaveStub[i + 3] = Address[i];
		}
		SaveStub[7] = 0x4E800420;
		__dcbst(0, SaveStub);
		__sync();
		__isync();
		PatchInJump(Address, Destination, FALSE);
	}
}

VOID Utils::PatchInJump(DWORD* Address, DWORD Destination, BOOL Linked) {
	Address[0] = 0x3D600000 + ((Destination >> 16) & 0xFFFF);
	if (Destination & 0x8000) Address[0] += 1;
	Address[1] = 0x396B0000 + (Destination & 0xFFFF);
	Address[2] = 0x7D6903A6;
	Address[3] = Linked ? 0x4E800421 : 0x4E800420;
}

VOID Utils::PatchInBranch(DWORD* Address, DWORD Destination, BOOL Linked) {
	Address[0] = (0x48000000 + ((Destination - (DWORD)Address) & 0x3FFFFFF));
	if (Linked) Address[0] += 1;
}

FARPROC Utils::ResolveFunction(CHAR* ModuleName, DWORD Ordinal) {
	HMODULE mHandle = GetModuleHandle(ModuleName);
	return (mHandle == NULL) ? NULL : GetProcAddress(mHandle, (LPCSTR)Ordinal);
}

DWORD Utils::PatchModuleImport(CHAR* Module, CHAR* ImportedModuleName, DWORD Ordinal, DWORD PatchAddress) {
	LDR_DATA_TABLE_ENTRY* moduleHandle = (LDR_DATA_TABLE_ENTRY*)GetModuleHandle(Module);
	return (moduleHandle == NULL) ? S_FALSE : PatchModuleImport(moduleHandle, ImportedModuleName, Ordinal, PatchAddress);
}

DWORD Utils::PatchModuleImport(PLDR_DATA_TABLE_ENTRY Module, CHAR* ImportedModuleName, DWORD Ordinal, DWORD PatchAddress) {
	DWORD address = (DWORD)Utils::ResolveFunction(ImportedModuleName, Ordinal);
	if (address == NULL)
		return S_FALSE;
	VOID* headerBase = Module->XexHeaderBase;
	PXEX_IMPORT_DESCRIPTOR importDesc = (PXEX_IMPORT_DESCRIPTOR)RtlImageXexHeaderField(headerBase, 0x000103FF);
	if (importDesc == NULL)
		return S_FALSE;
	DWORD result = 2;
	CHAR* stringTable = (CHAR*)(importDesc + 1);
	XEX_IMPORT_TABLE_ORG* importTable = (XEX_IMPORT_TABLE_ORG*)(stringTable + importDesc->NameTableSize);
	for (DWORD x = 0; x < importDesc->ModuleCount; x++) {
		DWORD* importAdd = (DWORD*)(importTable + 1);
		for (DWORD y = 0; y < importTable->ImportTable.ImportCount; y++) {
			DWORD value = *((DWORD*)importAdd[y]);
			if (value == address) {
				SetMemory((DWORD*)importAdd[y], &PatchAddress, 4);
				DWORD newCode[4];
				PatchInJump(newCode, PatchAddress, FALSE);
				SetMemory((DWORD*)importAdd[y + 1], newCode, 16);
				result = S_OK;
			}
		}
		importTable = (XEX_IMPORT_TABLE_ORG*)(((BYTE*)importTable) + importTable->TableSize);
	}
	return result;
}

BOOL Utils::IsTrayOpen() {
	unsigned char msg[0x10];
	unsigned char resp[0x10];
	memset(msg, 0x0, 0x10);
	msg[0] = 0xa;
	HalSendSMCMessage(msg, resp);
	if (resp[1] == 0x60)
		return true;
	else
		return false;
}

HRESULT Utils::GetMemory(VOID* Destination, VOID* Source, DWORD Length) {
	memcpy(Destination, Source, Length);
	return E_FAIL;
}

HRESULT Utils::SetMemory(VOID* Destination, VOID* Source, DWORD Length) {
	if (DevSetMemory == NULL)
		DevSetMemory = (pDmSetMemory)Utils::ResolveFunction("xbdm.xex", 40);
	if (DevSetMemory == NULL) {
		Utils::GetMemory(Destination, Source, Length);
		return ERROR_SUCCESS;
	}
	else {
		if (DevSetMemory(Destination, Length, Source, NULL) == MAKE_HRESULT(0, 0x2da, 0))
			return ERROR_SUCCESS;
	}
	return E_FAIL;
}

BOOL pfShow = (BOOL)0xDEADBEEF, pfShowMovie, pfPlaySound, pfShowIPTV;
VOID toggleNotify(BOOL on) {
	if ((INT)pfShow == 0xDEADBEEF)
		XNotifyUIGetOptions(&pfShow, &pfShowMovie, &pfPlaySound, &pfShowIPTV);
	if (!on)
		XNotifyUISetOptions(pfShow, pfShowMovie, pfPlaySound, pfShowIPTV);
	else
		XNotifyUISetOptions(true, true, true, true);
	Sleep(500);
}

VOID Utils::XNotifyDoQueueUI(PWCHAR pwszStringParam) {
	toggleNotify(true);
	XNotifyQueueUI(XNOTIFYUI_TYPE_CONSOLEMESSAGE, XUSER_INDEX_ANY, XNOTIFYUI_PRIORITY_HIGH, pwszStringParam, NULL);
	toggleNotify(false);
}

VOID Utils::XNotifyUI(PWCHAR pwszStringParam) {
	if (KeGetCurrentProcessType() != PROC_USER) {
		HANDLE th = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Utils::XNotifyDoQueueUI, (LPVOID)pwszStringParam, CREATE_SUSPENDED, NULL);
		if (th == NULL) return;
		ResumeThread(th);
	}
	else
		Utils::XNotifyDoQueueUI(pwszStringParam);
}

VOID Utils::XexThread(LPTHREAD_START_ROUTINE Thread) {
	HANDLE hThread; DWORD hThreadID;
	ExCreateThread(&hThread, 0, &hThreadID, (PVOID)XapiThreadStartup, (LPTHREAD_START_ROUTINE)Thread, NULL, 0x2);
	XSetThreadProcessor(hThread, 4); ResumeThread(hThread); CloseHandle(hThread);
	SetThreadPriority(hThread, THREAD_PRIORITY_ABOVE_NORMAL);
	ResumeThread(hThread);
	CloseHandle(hThread);
}

INT Utils::snprintf(char* buffer, size_t len, const char* fmt, ...) {
	va_list args;
	int i;
	va_start(args, fmt);
	i = vsnprintf(buffer, len, fmt, args);
	va_end(args);
	return i;
}

DWORD BytesRead, BytesWritten;

BOOL FileExists(CONST PCHAR FilePath)
{
	if (GetFileAttributes(FilePath) == INVALID_FILE_ATTRIBUTES)
	{
		DWORD LastError = GetLastError();
		if ((LastError == ERROR_PATH_NOT_FOUND) || (LastError == ERROR_FILE_NOT_FOUND)) return FALSE;
	}
	return TRUE;
}

BOOL CReadFile(CONST PCHAR FilePath, MemoryBuffer& Buffer)
{
	HANDLE Handle = CreateFile(FilePath, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (Handle == INVALID_HANDLE_VALUE) return FALSE;
	DWORD FileSize = GetFileSize(Handle, 0);
	PBYTE FileBuffer = (PBYTE)malloc(FileSize);
	if (FileBuffer == 0)
	{
		CloseHandle(Handle);
		return FALSE;
	}
	DWORD ReadSize = 0;
	if (!ReadFile(Handle, FileBuffer, FileSize, &ReadSize, 0))
	{
		free(FileBuffer);
		CloseHandle(Handle);
		return FALSE;
	}
	else if (ReadSize != FileSize)
	{
		free(FileBuffer);
		CloseHandle(Handle);
		return FALSE;
	}
	Buffer.Add(FileBuffer, FileSize);
	free(FileBuffer);
	CloseHandle(Handle);
	return TRUE;
}

BOOL CWriteFile(CONST PCHAR FilePath, CONST PVOID Buffer, DWORD Size)
{
	DWORD WriteSize = Size;
	HANDLE Handle = CreateFile(FilePath, GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	if (Handle == INVALID_HANDLE_VALUE) return FALSE;
	if (!WriteFile(Handle, Buffer, WriteSize, &WriteSize, 0))
	{
		CloseHandle(Handle);
		return FALSE;
	}
	CloseHandle(Handle);
	return (WriteSize == Size);
}


BOOL CReadFile(const CHAR* FileName, MemoryBuffer& pBuffer) {

	HANDLE hFile; DWORD dwFileSize, dwNumberOfBytesRead;
	hFile = CreateFile(FileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		DbgPrint("CReadFile - CreateFile failed");
		return FALSE;
	}
	dwFileSize = GetFileSize(hFile, NULL);
	PBYTE lpBuffer = (BYTE*)malloc(dwFileSize);
	if (lpBuffer == NULL) {
		CloseHandle(hFile);
		DbgPrint("CReadFile - malloc failed");
		return FALSE;
	}
	if (ReadFile(hFile, lpBuffer, dwFileSize, &dwNumberOfBytesRead, NULL) == FALSE) {
		free(lpBuffer);
		CloseHandle(hFile);
		DbgPrint("CReadFile - ReadFile failed");
		return FALSE;
	}
	else if (dwNumberOfBytesRead != dwFileSize) {
		free(lpBuffer);
		CloseHandle(hFile);
		DbgPrint("CReadFile - Failed to read all the bytes");
		return FALSE;
	}
	CloseHandle(hFile);
	pBuffer.Add(lpBuffer, dwFileSize);
	free(lpBuffer);
	return TRUE;
}

BOOL CWriteFile(const CHAR* FilePath, const VOID* Data, DWORD Size)
{
	// Open our file
	HANDLE fHandle = CreateFile(FilePath, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (fHandle == INVALID_HANDLE_VALUE)
	{
		DbgPrint("CWriteFile - CreateFile failed");
		return FALSE;
	}

	// Write our data and close
	DWORD writeSize = Size;
	if (WriteFile(fHandle, Data, writeSize, &writeSize, NULL) != TRUE)
	{
		DbgPrint("CWriteFile - WriteFile failed");
		return FALSE;
	}
	CloseHandle(fHandle);

	// All done
	return TRUE;
}
BOOL ReadFileAlt(PCHAR Path, LPVOID Buffer, DWORD dwBytesToRead)
{
	HANDLE hFile = CreateFile(Path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile); return FALSE;
	}
	ReadFile(hFile, Buffer, dwBytesToRead, &BytesRead, NULL);
	CloseHandle(hFile);
	return TRUE;
}
BOOL WriteFileAlt(PCHAR Path, LPCVOID Buffer, DWORD dwBytesToWrite)
{
	HANDLE hFile = CreateFile(Path, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile); return FALSE;
	}
	WriteFile(hFile, Buffer, dwBytesToWrite, &BytesRead, NULL);
	CloseHandle(hFile);
	return TRUE;
}

#pragma warning(push)
#pragma warning(disable:4826)

BOOL InitializeHvxPeekPoke()
{
	PVOID pBuffer = XPhysicalAlloc(0x1000, MAXULONG_PTR, 0, PAGE_READWRITE);
	DWORD Address = (DWORD)MmGetPhysicalAddress(pBuffer);
	memset(pBuffer, 0, 0x1000);
	memcpy(pBuffer, HvxPeekPokeExp, sizeof(HvxPeekPokeExp));
	DWORD Result = (DWORD)HvxExpansionInstall(Address, 0x1000);
	XPhysicalFree(pBuffer);
	return (Result == S_OK);
}


DWORD HvxPeekBytes(QWORD Address, PVOID Buffer, DWORD Size)
{
	PVOID pBuffer = XPhysicalAlloc(Size, MAXULONG_PTR, 0, PAGE_READWRITE);
	memset(pBuffer, 0, Size);
	DWORD Result = (DWORD)HvxExpansionCall(HvxPeekPokeExpID, PEEK_BYTES, Address, (QWORD)MmGetPhysicalAddress(pBuffer), Size);
	if (Result == S_OK) memcpy(Buffer, pBuffer, Size);
	XPhysicalFree(pBuffer);
	return Result;
}

DWORD MountPath(PCHAR Drive, PCHAR Device)
{
	CHAR Destination[MAX_PATH] = { 0 };
	sprintf_s(Destination, MAX_PATH, (KeGetCurrentProcessType() == PROC_SYSTEM) ? OBJ_SYS_STRING : OBJ_USR_STRING, Drive);
	ANSI_STRING LinkName, DeviceName;
	RtlInitAnsiString(&LinkName, Destination);
	RtlInitAnsiString(&DeviceName, Device);
	ObDeleteSymbolicLink(&LinkName);
	return (DWORD)ObCreateSymbolicLink(&LinkName, &DeviceName);
}