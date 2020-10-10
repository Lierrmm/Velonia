namespace TU9
{
	struct BulletFireParams
	{
		int MaxEntNum;
		int ignoreEntIndex;
		float damageMultiplier;
		int methodOfDeath;
		Vector3 origStart;
		Vector3 start;
		Vector3 end;
		Vector3 dir;
	};

	class cgs_t
	{
	public:
		/*union
		{
			DEFINE_MEMBER_N(__int32, screenX, 0x08);
			DEFINE_MEMBER_N(__int32, screenY, 0x0C);
			DEFINE_MEMBER_N(__int32, GameTime, 0x1C);
			DEFINE_MEMBER_N(bool, Local, 0x23);
			DEFINE_MEMBER_N(bool, Local, 0x23);
			DEFINE_MEMBER_N(char, GameType, 0x24);
			DEFINE_MEMBER_N(char, Host, 0x44);
			DEFINE_MEMBER_N(__int32, maxClients, 0x0148);
			DEFINE_MEMBER_N(char, MapName, 0x0150);
		};*/
		char _0x0000[8];
		__int32 screenX; //0x0008 
		__int32 screenY; //0x000C 
		char _0x0010[0x8];
		__int32 GameTime; //0x001C 
		char _0x0020[3]; //0x0020 
		BYTE Local; //0x0023 
		char GameType[4]; //0x0024 
		char _0x0028[28]; //0x0028 
		char Host[64]; //0x0044 
		char _0x0084[196]; //0x0084 
		__int32 maxClients; //0x0148 
		char _0x014C[4]; //0x014C 
		char MapName[64]; //0x0150 
	};

	class PlayerState_sMW2
	{
	public:
		int GameTime; // 0x0
		int ServerTime; // 0x4
		char _0x0008[0x18];
		Vector3 Origin; // 0x20
		Vector3 Velocity; // 0x2C
		char _0x0038[0xE8];
		float weaponPosFraction; // 0x124
	}; // size 0x128 or 0x4B4

	class cRefdef
	{
	public:
		char _0x0000[8];
		__int32 iWidth; //0x0008 
		__int32 iHeight; //0x000C 
		float fov_X; //0x0010 
		float fov_Y; //0x0014 
		Vector3 EyePos; //0x0018 
		Vector3 ViewAxis[3]; //0x0024 
	};


	class CClient
	{
	public:
		__int32 Valid; //0x0000 
		char _0x0004[4];
		__int32 mNum; //0x0008 
		char mName[32]; //0x000C 
		__int32 mTeam; //0x002C 
		char _0x0030[4];
		__int32 Rank; //0x0034 
		__int32 Prestige; //0x0038 
		char _0x003C[8];
		char clanTag[4];
		char _0x0048[16];
		char szBodyModel[64]; //0x0058 
		char szHeadModel[64]; //0x0098 
		char N0AFB4B1A[64]; //0x00D8 
		char szWeapModel[64]; //0x0118 
		char _0x0158[852];
		__int32 mShooting; //0x04AC 
		char _0x04B0[4];
		__int32 mZooming; //0x04B4 
		char N0AFE4D2B[96]; //0x04B8 
		__int32 Weapon; //0x0518 
		char _0x051C[40];
	}; //544

	class cg_t
	{
	public:
		int ServerTime; // 0x00
		char _0x0004[0x18];
		Vector3 Origin; // 0x1C
		char _0x0028[0x88];
		int Stance;
		char _0x00B4[0x50];
		__int32 cNum; //0x0104
		char _0x0108[4];
		Vector3 ViewAngle;
		char _0x0118[56];
		__int32 Health; //0x0150 
		char _0x0154[4];
		__int32 Health2; //0x0158 
		char _0x015C[0x168];
		float aimSpreadScale; // 0x2C4
		char _0x02C8[0x36D34];
		PlayerState_sMW2 ps; // 0x36FFC
		char _padding[211720];
		cRefdef refdef; //CG + 6AC28
		char _padding2[573968];
		CClient ClientInfo[18];
	};

	typedef struct {
		char _0x0000[2]; //0x0000 
		BYTE Valid; //0x0002
		char _0x0003[21];
		Vector3 mPos; //0x0018 
		Vector3 Angle; //0x0024
		char N0B4867E0[48]; //0x0030
		__int32 Flags; //0x0060  
		char N0B4D8B96[20]; //0x0064 
		Vector3 mPos2; //0x0078 
		char N0B4B45DC[76]; //0x0084 
		__int32 ClientNumber; //0x00D0 
		__int32 EntityType; //0x00D4
		char _0x00D8[4];
		BYTE N0B4B4612; //0x00DC 
		BYTE Zoomed; //0x00DD 
		BYTE Shooting; //0x00DE 
		BYTE PlayerPose; //0x00DF 
		char _0x00E0[20];
		Vector3 mPos3; //0x00F4 
		char _0x0100[88];
		int scavWeaponID; //0x0158 
		char _0x015C[64];
		short WeaponNum; //0x019C 
		char N0B4B4662[50]; //0x01A0 
		__int32 isAlive; //0x01D0
		char _0x01D4[36];
	}CEntity, *pCentity_t;; //Size=0x01F8

	struct trace_t {
		float fraction;
		Vector3 normal;
		int surfaceFlags;
		int contents;
		const char* material;
		int hitType;
		unsigned short hitId;
		unsigned short modelIndex;
		unsigned short partName;
		unsigned short partGroup;
		bool allsolid;
		bool startsolid;
		bool walkable;
		char _0x002B[5];
		Vector3 endpos;
		char _0x003C[4];
		unsigned long materialType;
		char _0x0044[0x20];
	};

	struct UserCmd_t {
		int serverTime;
		int buttons;
		int ViewAngles[3];
		short weapon;
		short offHandIndex;
		char Buf[0x02];
		char fDir;
		char rDir;
		char Buf2[0x0C];
	};

	typedef struct {
		bool ADS;
		char padding00[0xDF];
		Vector3 baseAngle;
		char padding01[0x31B7];
		char MapName[0x40];
		char padding02[0x21];
		int Stance;
		char padding03[0x28];
		Vector3 Origin;
		char padding04[0x1C];
		Vector3 viewAngle;
		UserCmd_t Usercmd[128];
		int CurrentCmdNumber;
		UserCmd_t* getCmd(int id) {
			return &Usercmd[id & 0x7F];
		}
		UserCmd_t* getCmd() {
			return getCmd(CurrentCmdNumber);
		}
		UserCmd_t* getLastCmd() {
			return getCmd(CurrentCmdNumber - 1);
		}
	}clientActive;

	struct CSnapshot {
		int snapFlags;
		char _0x0000[4];
		int ping;
		char _0x000C[4];
		int entityCount;
		int connectedClients;
	};

	enum CompassType
	{
		COMPASS_TYPE_PARTIAL = 0x0,
		COMPASS_TYPE_FULL = 0x1,
	};


	struct rectDef_s
	{
		float x;
		float y;
		float w;
		float h;
		DWORD unk;
	};

	struct Radar_Angle {
		float Pos_X;
		float Pos_Y;
		float Size_W;
		float Size_H;
		float style1;
		float style2;
	};

	struct UIContext_s {
		char _0x0000[0x20];
		__int32 screenWidth;
		__int32 screenHeight;
		char _0x0024[0x4];
		float fps;
	};


	struct ipInfo {
		byte ip1;
		byte ip2;
		byte ip3;
		byte ip4;
	};

	struct GfxDrawPrimArgs
	{
		int vertexCount;
		int triCount;
		int baseIndex;
	};

	struct GfxCmdBufPrimState {
		IDirect3DDevice9* device;
	};

	struct GfxDrawSurfFields
	{
		__int64 _bf0;
	};

	union GfxDrawSurf
	{
		GfxDrawSurfFields fields;
		unsigned __int64 packed;
	};

	struct __declspec(align(8)) MaterialInfo
	{
		char* name;
		BYTE gameFlags;
		BYTE sortKey;
		BYTE textureAtlasRowCount;
		BYTE textureAtlasColumnCount;
		GfxDrawSurf drawSurf;
		int surfaceTypeBits;
		char _padding[4];
	};

	struct Material {
		MaterialInfo info;
		BYTE stateBitsEntry[26];
		BYTE textureCount;
		BYTE constantCount;
		BYTE stateBitsCount;
		BYTE stateFlags;
		BYTE cameraRegion;
		BYTE _Unknown;
		char* techniqueSet;
		char* textureTable;
		char* constantTable;
		char* stateBitsTable;
	};

	typedef struct {
		char _0x0000[8];
		char servername[256];
	} clientStatic_t;


	struct nWeapon
	{
		char WeaponName[64]; //Weapon Name
	};
	struct sWeapon
	{
		char WeaponShader[64];//Weapon Shader
	};
	struct sWeapon_t
	{
		sWeapon* sWeapon;
	};
	struct CWeapon
	{
		char unknown0[8];
		nWeapon* nWeapon; // Name Esp
		char unknown1[60];
		sWeapon_t* sWeapon_t;//Shader Esp
	};
	struct CWeapon_t
	{
		CWeapon* CWeapon;
	};

	enum EntTypes
	{
		TYPE_GENERAL = 0,
		TYPE_PLAYER = 1,
		TYPE_DEAD = 2,
		TYPE_ITEM = 3,
		TYPE_MISSLE = 4,
		TYPE_INVISIBLE_ENTITY = 5,
		TYPE_SCRIPTMOVER = 6,
		TYPE_TURRET = 11,
		TYPE_HELICOPTER = 12,
		TYPE_PLANE = 13,
		TYPE_VEHICLE = 14
	};

	DWORD _cg_t = 0x825B8638;
	DWORD _cgs_t = 0x825B861C;
	DWORD cgEntities = 0x825BE150;
	DWORD ipAddress = 0x8268EF04;
	DWORD uiContext = 0x83647860;
	DWORD ClientStatic = 0x825E2200;
	DWORD refdef = 0x82553764;
	DWORD FlashConc = 0x8255595C;
	DWORD StunConc = 0x825556F4;

	cgs_t* cgs;
	cg_t* cg;
	CEntity* Entities[18];
	UIContext_s uicontext;
	clientActive* ca;
	pCentity_t Centity_s;
	ipInfo* clientIps[18];
	clientStatic_t clientStatic;
	cRefdef* Refdef;
	CClient* Clients[18];
	CSnapshot snapshot;

	CEntity* getCEntitybyIDx(int id)
	{
		DWORD cent_ptr = *(DWORD*)cgEntities;
		return (CEntity*)(cent_ptr + ((int)0x01F8 * id));
	}
	clientActive* getCA()
	{
		DWORD ca_ptr = *(DWORD*)0x82682350;
		return (clientActive*)ca_ptr;
	}

	ipInfo* getClientIpByID(int id) {
		return (ipInfo*)(ipAddress + ((int)0xC0 * id));
	}

	cRefdef* getRefdef() {
		DWORD ptr = *(DWORD*)refdef;
		return (cRefdef*)(ptr - 0x98D0);
	}

	CClient* getClientbyIDx(int id)
	{
		DWORD ClientInfo = ((DWORD)getRefdef() + 0x8C258);

		return (CClient*)(ClientInfo + ((int)0x544 * id));
	}

	CSnapshot getSnapShot() {
		return *(CSnapshot*)((int)getCA() + 0x320C);
	}

	void pgStructs()
	{
		uicontext = *(UIContext_s*)uiContext;
	}
	

	void getStructs() {
		cgs = *(cgs_t**)(_cgs_t);
		cg = *(cg_t**)(_cg_t);
		ca = (clientActive*)getCA();
		clientStatic = *(clientStatic_t*)ClientStatic;
		Centity_s = *reinterpret_cast<pCentity_t*>(cgEntities);
		Refdef = getRefdef();
		snapshot = getSnapShot();
		for (int i = 0; i < 18; i++) Entities[i] = (CEntity*)getCEntitybyIDx(i);
		for (int i = 0; i < 18; i++) clientIps[i] = (ipInfo*)getClientIpByID(i);
		for (int i = 0; i < 18; i++) Clients[i] = (CClient*)getClientbyIDx(i);
	}
}