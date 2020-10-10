namespace TU17
{
	enum entityType_t {
		ET_GENERAL = 0x0,
		ET_PLAYER = 0x1,
		ET_PLAYER_CORPSE = 0x2,
		ET_ITEM = 0x3,
		ET_MISSLE = 0x4,
		ET_INVISIBLE = 0x5,
		ET_SCRIPTMOVER = 0x6,
		ET_SOUND_BLEND = 0x7,
		ET_FX = 0x8,
		ET_LOOP_FX = 0x9,
		ET_PRIMARY_LIGHT = 0xA,
		ET_TURRET = 0xB,
		ET_HELICOPTER = 0xC,
		ET_PLANE = 0xD,
		ET_VEHICLE = 0xE,
		ET_VEHICLE_COLLMAP = 0xF,
		ET_VEHICLE_CORPSE = 0x10,
		ET_VEHICLE_SPAWNER = 0x11,
		ET_AGENT = 0x12,
		ET_AGENT_CORPSE = 0x13,
		ET_EVENTS = 0x14,
	};
	struct rectDef_s {
		float x;
		float y;
		float w;
		float h;
		DWORD unk;
	};

	enum CompassType {
		COMPASS_TYPE_PARTIAL = 0x0,
		COMPASS_TYPE_FULL = 0x1,
	};
	
	typedef struct Usercmd_t {
		int time;
		int buttons;
		int viewAngles[3];
		int weapon;
		int offHand;
		char fDir;
		char rDir;
		char padding[0x1E];
	} Usercmd_t;
	typedef struct {
		unsigned char _0x0000[0x80];
		int ServerTime;
		unsigned char _0x0084[0x18];
		Vector3 Orign;
		unsigned char _0x00A8[0x3C];
		Vector3 baseAngle;
		unsigned char _0x00F0[0x31E0];
		Vector3 viewAngle;
		Usercmd_t Usercmd[128];
		int CurrentCmdNumber;
		unsigned char _0x32DC[0xAAA4];
		bool ADS;
		Usercmd_t* getCmd(int id) {
			return &Usercmd[id & 0x7F];
		}
		Usercmd_t* getCmd() {
			return getCmd(CurrentCmdNumber);
		}
		Usercmd_t* getLastCmd() {
			return getCmd(CurrentCmdNumber - 1);
		}
	} ClientActive_t;
#pragma pack(push, 2)
	typedef struct {
		unsigned char _0x0000[2];
		unsigned char Alive;
		unsigned char _0x0003[17];
		Vector3 Origin;
		unsigned char _0x0020[60];
		int Flags;
		unsigned char _0x0060[12];
		Vector3 NewOrigin;
		unsigned char _0x0078[24];
		Vector3 viewAngle;
		unsigned char _0x009C[44];
		int Type;
		unsigned char _0x00CC[16];
		Vector3 OldOrigin;
		unsigned char _0x00E8[24];
		Vector3 OldAngles;
		unsigned char _0x010C[32];
		int PreviousWeaponIndex;
		unsigned char _0x0130[88];
		int WeaponID;
		unsigned char _0x018C[59];
		unsigned char State;
		unsigned char _0x01C8[0x24];
	}Centity_t, * pCentity_t;
#pragma pack(pop)
	enum CommandMask {
		CMD_MASK_FIRE = 0x00000001,
		CMD_MASK_MELEE = 0x00000004,
		CMD_MASK_SPRINT = 0x00002002,
		CMD_MASK_RELOAD = 0x00000020,
		CMD_MASK_AIM = 0x00080800,
		CMD_MASK_JUMP = 0x00000400,
		CMD_MASK_CROUCH = 0x00000200,
		CMD_MASK_PRONE = 0x00000100
	};
	typedef struct refdef_s {
		char _0x0000[0x08];
		unsigned long Width;
		unsigned long Height;
		Vector2 Fov;
		Vector3 viewOrigin;
		Vector3 viewAxis[3];
		unsigned char _0x0048[12];
		unsigned long Ping;
	} RefDef_t;
	typedef struct clientInfo_t {
		unsigned long Team;
		char padding01[0xC];
		char Model[0x25];
		char padding02[0x1B];
		char HeadModel[32];
		char padding03[0x52C];
	} clientinfo_t;
	typedef struct playerName_t {
		char Name[32];
		char padding00[0xD0];
	}playerName_t, * pplayerName_t;


	struct FxFloatRange// Size=0x8
	{
		float base;// Offset=0x0 Size=0x4
		float amplitude;// Offset=0x4 Size=0x4
	};

	typedef struct {
		char* name;
		int flags;
		int totalSize;
		int msecLoopingLife;
		int elemDefCountLooping;
		int elemDefCountOneShot;
		int elemDefCountEmission;
		float occlusionQueryDepthBias;// Offset=0x1c Size=0x4
		int occlusionQueryFadeIn;// Offset=0x20 Size=0x4
		int occlusionQueryFadeOut;// Offset=0x24 Size=0x4
		FxFloatRange occlusionQueryScaleRange;// Offset=0x28 Size=0x8
		int elemDefs;// Offset=0x30 Size=0x4
	}FxEffectDef;

	struct Bounds// Size=0x18
	{
		float midPoint[3];// Offset=0x0 Size=0xc
		float halfSize[3];// Offset=0xc Size=0xc
	};

	struct XModelSurfs// Size=0x24
	{
		char* name;// Offset=0x0 Size=0x4
		int surfs;// Offset=0x4 Size=0x4
		unsigned int numsurfs;// Offset=0x8 Size=0x2
		unsigned char __align0[2];// Offset=0xa Size=0x2
		int partBits[6];// Offset=0xc Size=0x18
	};

	struct XModelCollSurf_s// Size=0x24
	{
		Bounds bounds;// Offset=0x0 Size=0x18
		int boneIdx;// Offset=0x18 Size=0x4
		int contents;// Offset=0x1c Size=0x4
		int surfFlags;// Offset=0x20 Size=0x4
	};

	struct XModelLodInfo// Size=0x28
	{
		float dist;// Offset=0x0 Size=0x4
		unsigned int numsurfs;// Offset=0x4 Size=0x2
		unsigned int surfIndex;// Offset=0x6 Size=0x2
		XModelSurfs* modelSurfs;// Offset=0x8 Size=0x4
		int partBits[6];// Offset=0xc Size=0x18
		int surfs;// Offset=0x24 Size=0x4
	};

	struct DObjAnimMat// Size=0x20
	{
		float quat[4];// Offset=0x0 Size=0x10
		float trans[3];// Offset=0x10 Size=0xc
		float transWeight;// Offset=0x1c Size=0x4
	};

	typedef struct {
		char _bf0[8];
	}GfxDrawSurfFields;

	typedef struct {
		GfxDrawSurfFields fields;
	}GfxDrawSurf;

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


	struct XModel// Size=0x124
	{
		char* name;// Offset=0x0 Size=0x4
		unsigned int numBones;// Offset=0x4 Size=0x1
		unsigned int numRootBones;// Offset=0x5 Size=0x1
		unsigned int numsurfs;// Offset=0x6 Size=0x1
		unsigned char __align0[1];// Offset=0x7 Size=0x1
		float scale;// Offset=0x8 Size=0x4
		unsigned int noScalePartBits[6];// Offset=0xc Size=0x18
		unsigned int* boneNames;// Offset=0x24 Size=0x4
		unsigned int* parentList;// Offset=0x28 Size=0x4
		int* quats;// Offset=0x2c Size=0x4
		float* trans;// Offset=0x30 Size=0x4
		unsigned int* partClassification;// Offset=0x34 Size=0x4
		DObjAnimMat* baseMat;// Offset=0x38 Size=0x4
		Material** materialHandles;// Offset=0x3c Size=0x4
		XModelLodInfo lodInfo[4];// Offset=0x40 Size=0xa0
		char maxLoadedLod;// Offset=0xe0 Size=0x1
		char numLods;// Offset=0xe1 Size=0x1
		char collLod;// Offset=0xe2 Size=0x1
		unsigned int flags;// Offset=0xe3 Size=0x1
		XModelCollSurf_s* collSurfs;// Offset=0xe4 Size=0x4
		int numCollSurfs;// Offset=0xe8 Size=0x4
		int contents;// Offset=0xec Size=0x4
		struct XBoneInfo* boneInfo;// Offset=0xf0 Size=0x4
		float radius;// Offset=0xf4 Size=0x4
		Bounds bounds;// Offset=0xf8 Size=0x18
		unsigned int* invHighMipRadius;// Offset=0x110 Size=0x4
		int memUsage;// Offset=0x114 Size=0x4
		struct PhysPreset* physPreset;// Offset=0x118 Size=0x4
		struct PhysCollmap* physCollmap;// Offset=0x11c Size=0x4
		float quantization;// Offset=0x120 Size=0x4
	};
	
	struct cgs_t
	{
		char _0x0000[8];
		__int32 screenX; //0x0008 
		__int32 screenY; //0x000C 
		float viewAspect; //0x0010 
		float viewMult; //0x0014 
		__int32 serverCommandSequence; //0x0018 
		__int32 processedSnapshotNum; //0x001C 
		__int32 Local; //0x0020 
		char GameType[32]; //0x0024 
		char Host[256]; //0x0044 
		BYTE hardcore; //0x0144 
		char _align[3]; //0x0145 
		__int32 maxClients; //0x0148 
		__int32 privateClients; //0x014C 
		char MapName[64]; //0x0150 
		__int32 N00A906A9; //0x0190 
		__int32 redCrosshair; //0x0194 
		XModel* gameModels[1024]; //0x0198 
		FxEffectDef* smokeGrenadeFx; //0x1198 
	};
	
	typedef struct {
		unsigned long Servertime;
		unsigned char _0x0004[8];
		unsigned long Stance;
		unsigned char _0x0010[12];
		Vector3 Origin;
		unsigned char _0x0028[340];
		unsigned long ClientNumber;
		unsigned char _0x0180[0x4];
		Vector3 ViewAngle;
		unsigned char _0x0190[0x38];
		unsigned long Health;
		unsigned char _0x01CC[4];
		unsigned long MaxHealth;
		unsigned char _0x01D4[0x254];
		float SpreadMultiplier;
		char padding01[0x36488];
		playerName_t Names[18];
		char padding02[0x35BA8];
		refdef_s RefDef;
		char padding03[0x4BEA8];
		clientInfo_t ClientInfo[18];
	} cgArray_t;

	struct BulletFireParams {
		int MaxEntNum;
		int ignoreEntIndex;
		float damageMultiplier;
		int methodOfDeath;
		int crackCocaine;
		Vector3 origStart;
		Vector3 start;
		Vector3 end;
		Vector3 dir;
	};
	struct trace_t {
		float fraction;
		char Buf04[0x60];
	};
	struct uiContext {
		char _0x0000[0x20];
		int screenWidth;//0x20
		int screenHeight;//0x24
		char _0x0028[0x4];
		float FPS;
	};

	struct CSnapshot {
		int snapFlags;
		char _0x0000[4];
		int ping;
		char _0x000C[4];
		int entityCount;
		int connectedClients;
	};

	struct ipInfo {
		byte ip1;
		byte ip2;
		byte ip3;
		byte ip4;
	};

	typedef struct {
		char _0x0000[8];
		char servername[256];
	} clientStatic_t;

	struct CClient
	{
		int clientNum; //0x0000  
		char name[32]; //0x0004 
		int rank_mp; //0x0024 
		int prestige_mp; //0x0028 
		int rank_alien; //0x002C 
		int prestige_alien; //0x0030 
		char clanAbbrev[8]; //0x0034 
		char _0x003C[48];
		int rankIconHandle; //0x006C 
		int rankDisplayLevel; //0x0070 
	};

	struct partyMember
	{
		BYTE status; //0x0160 
		char _0x0161[15];
		int rank_mp; //0x0170 
		int prestige_mp; //0x0174 
		char _0x0178[8];
		int availableMapPackFlags; //0x0180 
		int playerCardIcon; //0x0184 
		int playerCardTitle; //0x0188 
		char _0x018C[40];
		char gamertag[32]; //0x01B4 
		char clanAbbrev[5]; //0x01D4 
		char _0x01D9[151];
		__int32 nattype; //0x0270 
		char _0x0274[36];
		ipInfo localIP;
		ipInfo ExternalIP;
		char _0x02A0[128];
	};

	struct PartyInfo
	{
		BYTE active; //0x0000 
		char _0x0001[12];
		ipInfo hostIP;
		char _0x0011[55];
		int numPublicSlots; //0x0048 
	};

	struct partyData
	{
		int session; //0x0000 
		int searchSession; //0x0004 
		char _0x0008[336];
		PartyInfo* partyList; //0x0158 
		int partyListSize; //0x015C
		partyMember partyMembers[12];
	};
	
	uiContext UI;
	ClientActive_t* ClientActive;
	pCentity_t Centity_s;
	cgArray_t* cg;
	clientStatic_t clientStatic;
	CSnapshot snapshot;
	cgs_t* cgs;
	CClient* clientInfo[12];
	partyData partydata;
	
	ClientActive_t* getCA()
	{
		auto ca_ptr = *reinterpret_cast<DWORD*>(0x82BAC404);
		return reinterpret_cast<ClientActive_t*>(ca_ptr);
	}
	
	CSnapshot getSnapShot() {
		return *reinterpret_cast<CSnapshot*>(reinterpret_cast<int>(getCA()) + 0x30EC);
	}

	CClient* getClientbyIDx(int id)
	{
		return reinterpret_cast<CClient*>(cg + (static_cast<int>(0xC5E20) * id));
	}

	bool getStructs() {
		if (((*reinterpret_cast<int*>(0x82AD56FC)) == 0) || ((*reinterpret_cast<int*>(0x82BAC404)) == 0) || ((*reinterpret_cast<int*>(0x82AD11AC)) == 0)) return false;
		cg = *reinterpret_cast<cgArray_t**>(0x82AD56FC);
		ClientActive = static_cast<ClientActive_t*>(getCA());
		Centity_s = *reinterpret_cast<pCentity_t*>(0x82AD11AC);
		clientStatic = *reinterpret_cast<clientStatic_t*>(0x82B14200);
		cgs = *reinterpret_cast<cgs_t**>(0x82AD56F8);
		partydata = *reinterpret_cast<partyData*>(0x82BBD480);
		snapshot = getSnapShot();
		for (auto i = 0; i < 11; i++) clientInfo[i] = getClientbyIDx(i);
		return true;
	}
	void pgStructs() {
		UI = *reinterpret_cast<uiContext*>(0x83D51E20);
	}
}