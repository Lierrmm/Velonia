#ifndef TU24_STRUCTS_H
#define TU24_STRUCTS_H

namespace TU24
{
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

	//struct cgs_t {
	//	int viewX;
	//	int viewY;
	//	__int32 screenX; //0x0008 
	//	__int32 screenY; //0x000C 
	//	char _0x0010[12]; //0x0010 
	//	__int32 GameTime; //0x001C 
	//	char _0x0020[3]; //0x0020 
	//	BYTE Local; //0x0023 
	//	char GameType[4]; //0x0024 
	//	char _0x0028[28]; //0x0028 
	//	char Host[64]; //0x0044 
	//	char _0x0084[196]; //0x0084 
	//	__int32 maxClients; //0x0148 
	//	char _0x014C[4]; //0x014C 
	//	char MapName[64]; //0x0150 
	//};//Size=0x0190
	//

	struct GfxImageStreamData// Size=0x8
	{
		unsigned short width;// Offset=0x0 Size=0x2
		unsigned short height;// Offset=0x2 Size=0x2
		unsigned int pixelSize;// Offset=0x4 Size=0x4
	};
	
	struct CardMemory// Size=0x4
	{
		int platform[1];// Offset=0x0 Size=0x4
	};
	
	union GfxTexture// Size=0x34
	{
		struct D3DBaseTexture basemap;// Offset=0x0 Size=0x34
		struct D3DLineTexture linemap;// Offset=0x0 Size=0x34
		struct D3DTexture map;// Offset=0x0 Size=0x34
		struct D3DVolumeTexture volmap;// Offset=0x0 Size=0x34
		struct D3DCubeTexture cubemap;// Offset=0x0 Size=0x34
	};
	
	struct GfxImage// Size=0x70
	{
		GfxTexture texture;// Offset=0x0 Size=0x34
		int format;// Offset=0x34 Size=0x4
		unsigned char mapType;// Offset=0x38 Size=0x1
		unsigned char semantic;// Offset=0x39 Size=0x1
		unsigned char category;// Offset=0x3a Size=0x1
		unsigned char flags;// Offset=0x3b Size=0x1
		CardMemory cardMemory;// Offset=0x3c Size=0x4
		unsigned short width;// Offset=0x40 Size=0x2
		unsigned short height;// Offset=0x42 Size=0x2
		unsigned short depth;// Offset=0x44 Size=0x2
		unsigned char levelCount;// Offset=0x46 Size=0x1
		unsigned char cached;// Offset=0x47 Size=0x1
		unsigned char* pixels;// Offset=0x48 Size=0x4
		GfxImageStreamData streams[4];// Offset=0x4c Size=0x20
		char* name;// Offset=0x6c Size=0x4
	};

	union MaterialTextureDefInfo// Size=0x4
	{
		struct GfxImage* image;// Offset=0x0 Size=0x4
		struct water_t* water;// Offset=0x0 Size=0x4
	};

	struct MaterialTextureDef// Size=0xc
	{
		unsigned int nameHash;// Offset=0x0 Size=0x4
		char nameStart;// Offset=0x4 Size=0x1
		char nameEnd;// Offset=0x5 Size=0x1
		unsigned char samplerState;// Offset=0x6 Size=0x1
		unsigned char semantic;// Offset=0x7 Size=0x1
		MaterialTextureDefInfo u;// Offset=0x8 Size=0x4
	};

	struct MaterialArgumentCodeConst// Size=0x4
	{
		unsigned short index;// Offset=0x0 Size=0x2
		unsigned char firstRow;// Offset=0x2 Size=0x1
		unsigned char rowCount;// Offset=0x3 Size=0x1
	};
	
	union MaterialArgumentDef// Size=0x4
	{
		float* literalConst;// Offset=0x0 Size=0x4
		MaterialArgumentCodeConst codeConst;// Offset=0x0 Size=0x4
		unsigned int codeSampler;// Offset=0x0 Size=0x4
		unsigned int nameHash;// Offset=0x0 Size=0x4
	};

	struct MaterialShaderArgument// Size=0x8
	{
		unsigned short type;// Offset=0x0 Size=0x2
		unsigned short dest;// Offset=0x2 Size=0x2
		MaterialArgumentDef u;// Offset=0x4 Size=0x4
	};

	enum SamplerType
	{
		VERTEX_SAMPLER = 0,
		PIXEL_SAMPLER = 1
	};

	struct cgs_t {
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
	};//Size=0x119C

	typedef struct {
		int servertime;
		int buttons;
		int viewangles[3];
		int Weapon;
		int offHand;
		char fDir;
		char rDir;
		char uDir;
		char yDir;
		char padding[0xC];
	} Usercmd_t;

	typedef struct {
		bool ADS;
		char padding00[0xDF];
		Vector3 baseAngle;
		char paddig00[0x34C4];
		Vector3 ViewAngles;
		Usercmd_t cmds[128]; //0x35BC
		int CmdNum; //0x4BBC 
		Usercmd_t* GetCmd(int Index)
		{
			return &cmds[(Index & 0x7F)];
		}
		Usercmd_t* getCmd() {
			return GetCmd(CmdNum);
		}
		Usercmd_t* getLastCmd() {
			return GetCmd(CmdNum - 1);
		}
	} clientActive;

	union float4 {
		float v[4];
		float u[4];
	};

	struct hybrid_vector {
		float4 vec;
	};

	struct trace_t {
		float fraction;
		hybrid_vector normal;
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

	struct BulletFireParams {
		int weaponEntIndex;
		int ignoreEntIndex;
		float damageMultiplier;
		int methodOfDeath;
		bool noRicochet;
		unsigned char _align[3];
		Vector3 origStart;
		Vector3 start;
		Vector3 end;
		Vector3 dir;
	};

	struct CClient {
		int mValid;
		char _0x0004[0x8];
		char szPlayerName[32];
		int mTeam;
		char _0x0030[0x4];
		int Rank;
		int Prestige;
		char _0x003C[0x10];
		char clanTag[4];
		char _0x004C[0x10];
		char szBodyModel[0x40];
		char szHeadModel[0x40];
		char _0x00E0[0x3D0];
		int mShooting;
		char _0x04B4[0x4];
		int mZooming;
		char _0x04BC[0x60];
		int Weapon;
		char _0x0520[14];
		BYTE usingKnife;
		char _0x0013[1];
		__int32 dualWielding;
		char _0x0018[8];
		__int32 cardIcon;
		__int32 CardTitle;
		__int32 CardNamePlate;
		BYTE use_elite_clan_tag;
		BYTE use_elite_clan_title;
		char elite_clan_title_text[24];
		char _align[2];
		__int32 elite_clan_title_bg;
		char elit_clan_tag_text[5];
		char _align1[3];
		__int32 prestige_black_ops;
		__int32 rank_black_ops;
		__int32 prestige_mw2;
		__int32 rank_mw2;
		__int32 prestige_waw;
		__int32 rank_waw;
		__int32 prestige_mw;
		__int32 rank_mw;
		char _align2[4];
		//char _0x0520[0x74];  
	};//Size=0x0594

	struct RefDef {
		__int32 x; //0x0000 
		__int32 y; //0x0004 
		__int32 width; //0x0008 
		__int32 height; //0x000C 
		float tanHalfFovX; //0x0010 
		float tanHalfFovY; //0x0014 
		Vector3 viewOrigin; //0x0018 
		Vector3 viewAxis[3]; //0x0024 
		//NEW
		char _0x0048[0x24];
		float m_zoomProgress;
		char _0x0070[0x4AC0];
	};

	typedef struct
	{
		__int32 _0x0000; //0x0000 
		__int32 Type; //0x0004 
		__int32 eventParam; //0x0008 
		char _0x000C[12]; //0x000C 
		Vector3 NewOrigin; //0x0018 
		char _0X0024[28]; //0x0024 
		Vector3 NewAngles; //0x0040 
		char _0x004C[44]; //0x004C 
		__int32 VictimEntNum; //0x0078 
		__int32 KillerEntNum; //0x007C 
		char _0x0080[88]; //0x0080 
		__int32 eventParam2; //0x00D8 
	}entityState_t;


	struct cg_t {
		int serverTime;
		char padding00[0xA]; //10
		short Stance; //12
		char padding01[0xC]; //24
		Vector3 origin; //
		char padding02[0x128];
		int clientNum;
		char padding03[0x4];
		Vector3 ViewAngle;
		char padding04[0x38];
		int Health;
		char padding05[0xDC];
		int WeaponPrimary;
		char padding06[0xF0];
		int Weapon;
		char padding07[0x8];
		float SpreadMultiplier;
		char padding08[0x6B72C];
		RefDef refdef;
		Vector3 refdefViewAngles;
		//char padding09[0x92490]; //0x92494
		//NEW
		char _0x705E8[0x746C];
		float m_compassNorth[2];
		char _0x77A54[0x8652C];
		CClient ClientInfo[18];
	};//Size=0xFDF8C

	struct AimScreenTarget {
		int entIndex;
		Vector2 clipMins;
		Vector2 clipMaxs;
		Vector3 aimPos;
		Vector3 velocity;
		float distSqr;
		float crosshairDistSqr;
	};

	struct playerstate_s {
		char _0x0000[2700]; //0x0000 
		__int32 SecondaryAmmo; //0x0A8C 
		char _0x0A90[208]; //0x0A90 
		__int32 weaponClip; //0x0B60 
		char _0xB64[11988]; //0x0B64 
		char Gamertag[32]; //0x3A38 
		char _0x3A58[536]; //0x3A58 
	};//Size=0x3C6C

	typedef struct {
		char _0x0000[2]; //0x0000 
		BYTE valid; //0x0002 
		char _0x0003[17];
		Vector3 origin; //0x0014 
		Vector3 Angle; //0x0020 
		char _0x002C[48];
		int Flags;
		char _0x0060[12];
		Vector3 oldOrigin; //0x006C 
		char _0x0078[24];
		Vector3 ViewAngles1; //0x0090 
		char padding00[0x28];
		//char _0x0078[76];
		__int32 clientId; //0x00C4 
		__int32 Type; //0x00C8 
		__int32 Pose; //0x00CC 
		char _0x00D0[12];
		Vector3 NewOrigin; //0x00DC 
		char _0x00E8[24];
		Vector3 ViewAngles2; //0x0100 
		char _0x010C[131];
		char WeaponID; //0x018F 
		char _0x0190[55];
		char State; //0x01C7 
		char _0x01C8[0x24];
	} CEntity, * pCentity_t;//Size=0x01EC


	struct CSnapshot {
		int snapFlags;
		char _0x0000[4]; //0x0000 - somewhere here - snapFlags
		int ping; //0x0008
		char _0x000C[4];
		int entityCount;
		int connectedClients;
	};

	struct field_t {
		int cursor;
		int scroll;
		int drawWidth;
		int widthInPixels;
		int charHeight;
		int fixedSize;
		char buffer[256];
	};

	struct AimTarget {
		int entIndex;
		int worldDistSqr;
		int heightChange;
		Vector3 mins;
		Vector3 maxs;
		Vector3 velocity;
	};

	enum CompassType
	{
		COMPASS_TYPE_PARTIAL = 0x0, /*Will draw the radar how it normally looks.*/
		COMPASS_TYPE_FULL = 0x1, /*Will draw the radar how it looks in the pause screen*/
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

	struct Weaponinfo_t
	{
		char pad0[9]; // 0x0
		int SurfacePenetrateType; // 0x9
		char pad1[1344]; // 0xD
		bool LargePenetrate; // 0x54D
		char pad2[378]; // 0x54E
		float spreadmultiplier; // 0x6C8
	};


	struct ipInfo {
		byte ip1;
		byte ip2;
		byte ip3;
		byte ip4;
	};//0x82720EEC + 0xB8 + (0x158 * i)

	typedef struct
	{
		char* IconName;
	} icon_t;

	//typedef struct {
	//	unsigned long    client;
	//	unsigned long    score;
	//	unsigned long    ping;
	//	unsigned long    deaths;
	//	unsigned long    team;
	//	unsigned long    kills;
	//	unsigned long    Level;
	//	unsigned long    assists;
	//	unsigned long	 int_unk;
	//	icon_t* Dead;
	//	icon_t* Rank;
	//} score_t;

	struct score_t// Size=0x2c
	{
		int client;// Offset=0x0 Size=0x4
		int score;// Offset=0x4 Size=0x4
		int ping;// Offset=0x8 Size=0x4
		int deaths;// Offset=0xc Size=0x4
		int team;// Offset=0x10 Size=0x4
		int kills;// Offset=0x14 Size=0x4
		int rank_mp;// Offset=0x18 Size=0x4
		int assists;// Offset=0x1c Size=0x4
		Material* hPartyIcon;// Offset=0x20 Size=0x4
		Material* hStatusIcon;// Offset=0x24 Size=0x4
		Material* hRankIcon;// Offset=0x28 Size=0x4
	};

	enum entityevents_t
	{
		EV_NONE = 0,
		EV_FOLIAGE_SOUND,
		EV_STOP_WEAPON_SOUND,
		EV_SOUND_ALIAS,
		EV_SOUND_ALIAS_AS_MASTER,
		EV_STOPSOUNDS,
		EV_STANCE_FORCE_STAND,
		EV_STANCE_FORCE_CROUCH,
		EV_STANCE_FORCE_PRONE,
		EV_STANCE_INVALID,
		EV_ITEM_PICKUP,
		EV_AMMO_PICKUP,
		EV_NOAMMO,
		EV_EMPTYCLIP,
		EV_EMPTY_OFFHAND_PRIMARY,
		EV_EMPTY_OFFHAND_SECONDARY,
		EV_OFFHAND_END_NOTIFY,
		EV_RESET_ADS,
		EV_RELOAD,
		EV_RELOAD_FROM_EMPTY,
		EV_RELOAD_START,
		EV_RELOAD_END,
		EV_RELOAD_START_NOTIFY,
		EV_RELOAD_ADDAMMO,
		EV_RAISE_WEAPON,
		EV_FIRST_RAISE_WEAPON,
		EV_PUTAWAY_WEAPON,
		EV_WEAPON_ALT,
		EV_WEAPON_SWITCH_STARTED,
		EV_PULLBACK_WEAPON,
		EV_FIRE_WEAPON,
		EV_FIRE_WEAPON_LASTSHOT,
		EV_FIRE_RICOCHET,
		EV_RECHAMBER_WEAPON,
		EV_EJECT_BRASS,
		EV_FIRE_WEAPON_LEFT,
		EV_FIRE_WEAPON_LASTSHOT_LEFT,
		EV_EJECT_BRASS_LEFT,
		EV_HITCLIENT_FIRE_WEAPON,
		EV_HITCLIENT_FIRE_WEAPON_LASTSHOT,
		EV_HITCLIENT_FIRE_WEAPON_LEFT,
		EV_HITCLIENT_FIRE_WEAPON_LASTSHOT_LEFT,
		EV_SV_FIRE_WEAPON,
		EV_SV_FIRE_WEAPON_LASTSHOT,
		EV_SV_FIRE_WEAPON_LEFT,
		EV_SV_FIRE_WEAPON_LASTSHOT_LEFT,
		EV_MELEE_SWIPE,
		EV_FIRE_MELEE,
		EV_PREP_OFFHAND,
		EV_USE_OFFHAND,
		EV_SWITCH_OFFHAND,
		EV_MELEE_HIT,
		EV_MELEE_MISS,
		EV_MELEE_BLOOD,
		EV_FIRE_TURRET,
		EV_FIRE_SENTRY,
		EV_FIRE_QUADBARREL_1,
		EV_FIRE_QUADBARREL_2,
		EV_BULLET_HIT,
		EV_BULLET_HIT_SHIELD,
		EV_BULLET_HIT_EXPLODE,
		EV_BULLET_HIT_CLIENT_SMALL,
		EV_BULLET_HIT_CLIENT_LARGE,
		EV_BULLET_HIT_CLIENT_EXPLODE,
		EV_BULLET_HIT_CLIENT_SHIELD,
		EV_EXPLOSIVE_IMPACT_ON_SHIELD,
		EV_EXPLOSIVE_SPLASH_ON_SHIELD,
		EV_GRENADE_BOUNCE,
		EV_GRENADE_STICK,
		EV_GRENADE_REST,
		EV_GRENADE_EXPLODE,
		EV_GRENADE_PICKUP,
		EV_GRENADE_LETGO,
		EV_ROCKET_EXPLODE,
		EV_ROCKET_EXPLODE_NOMARKS,
		EV_FLASHBANG_EXPLODE,
		EV_CUSTOM_EXPLODE,
		EV_CUSTOM_EXPLODE_NOMARKS,
		EV_CHANGE_TO_DUD,
		EV_DUD_EXPLODE,
		EV_DUD_IMPACT,
		EV_TROPHY_EXPLODE,
		EV_BULLET,
		EV_PLAY_FX,
		EV_PLAY_FX_ON_TAG,
		EV_STOP_FX_ON_TAG,
		EV_PLAY_FX_ON_TAG_FOR_CLIENTS,
		EV_PHYS_EXPLOSION_SPHERE,
		EV_PHYS_EXPLOSION_CYLINDER,
		EV_PHYS_EXPLOSION_JOLT,
		EV_RADIUSDAMAGE,
		EV_PHYS_JITTER,
		EV_EARTHQUAKE,
		EV_GRENADE_SUICIDE,
		EV_DETONATE,
		EV_NIGHTVISION_WEAR,
		EV_NIGHTVISION_REMOVE,
		EV_MISSILE_REMOTE_BOOST,
		EV_OBITUARY,
		EV_NO_PRIMARY_GRENADE_HINT,
		EV_NO_SECONDARY_GRENADE_HINT,
		EV_TARGET_TOO_CLOSE_HINT,
		EV_TARGET_NOT_ENOUGH_CLEARANCE_HINT,
		EV_LOCKON_REQUIRED_HINT,
		EV_VEHICLE_COLLISION,
		EV_VEHICLE_SUSPENSION_SOFT,
		EV_VEHICLE_SUSPENSION_HARD,
		EV_FOOTSTEP_SPRINT,
		EV_FOOTSTEP_RUN,
		EV_FOOTSTEP_WALK,
		EV_FOOTSTEP_PRONE,
		EV_JUMP,
		EV_LANDING_DEFAULT,
		EV_LANDING_BARK,
		EV_LANDING_BRICK,
		EV_LANDING_CARPET,
		EV_LANDING_CLOTH,
		EV_LANDING_CONCRETE,
		EV_LANDING_DIRT,
		EV_LANDING_FLESH,
		EV_LANDING_FOLIAGE,
		EV_LANDING_GLASS,
		EV_LANDING_GRASS,
		EV_LANDING_GRAVEL,
		EV_LANDING_ICE,
		EV_LANDING_METAL,
		EV_LANDING_MUD,
		EV_LANDING_PAPER,
		EV_LANDING_PLASTER,
		EV_LANDING_ROCK,
		EV_LANDING_SAND,
		EV_LANDING_SNOW,
		EV_LANDING_WATER,
		EV_LANDING_WOOD,
		EV_LANDING_ASPHALT,
		EV_LANDING_CERAMIC,
		EV_LANDING_PLASTIC,
		EV_LANDING_RUBBER,
		EV_LANDING_CUSHION,
		EV_LANDING_FRUIT,
		EV_LANDING_PAINTEDMETAL,
		EV_LANDING_RIOTSHIELD,
		EV_LANDING_SLUSH,
		EV_LANDING_PAIN_DEFAULT,
		EV_LANDING_PAIN_BARK,
		EV_LANDING_PAIN_BRICK,
		EV_LANDING_PAIN_CARPET,
		EV_LANDING_PAIN_CLOTH,
		EV_LANDING_PAIN_CONCRETE,
		EV_LANDING_PAIN_DIRT,
		EV_LANDING_PAIN_FLESH,
		EV_LANDING_PAIN_FOLIAGE,
		EV_LANDING_PAIN_GLASS,
		EV_LANDING_PAIN_GRASS,
		EV_LANDING_PAIN_GRAVEL,
		EV_LANDING_PAIN_ICE,
		EV_LANDING_PAIN_METAL,
		EV_LANDING_PAIN_MUD,
		EV_LANDING_PAIN_PAPER,
		EV_LANDING_PAIN_PLASTER,
		EV_LANDING_PAIN_ROCK,
		EV_LANDING_PAIN_SAND,
		EV_LANDING_PAIN_SNOW,
		EV_LANDING_PAIN_WATER,
		EV_LANDING_PAIN_WOOD,
		EV_LANDING_PAIN_ASPHALT,
		EV_LANDING_PAIN_CERAMIC,
		EV_LANDING_PAIN_PLASTIC,
		EV_LANDING_PAIN_RUBBER,
		EV_LANDING_PAIN_CUSHION,
		EV_LANDING_PAIN_FRUIT,
		EV_LANDING_PAIN_PAINTEDMETAL,
		EV_LANDING_PAIN_RIOTSHIELD,
		EV_LANDING_PAIN_SLUSH,
		EV_MANTLE
	};

	typedef struct {
		char _0x0000[8];
		char servername[256];
	} clientStatic_t;

	struct clientLogo_t// Size=0x18
	{
		int startTime;// Offset=0x0 Size=0x4
		int duration;// Offset=0x4 Size=0x4
		int fadein;// Offset=0x8 Size=0x4
		int fadeout;// Offset=0xc Size=0x4
		Material* material[2];// Offset=0x10 Size=0x8
	};

	struct serverInfo_t// Size=0xd0
	{
		XNADDR xnaddr;// Offset=0x0 Size=0x24
		XNKEY xnkey;// Offset=0x24 Size=0x10
		XNKID xnkid;// Offset=0x34 Size=0x8
		int publicSlots;// Offset=0x3c Size=0x4
		int publicSlotsUsed;// Offset=0x40 Size=0x4
		int privateSlots;// Offset=0x44 Size=0x4
		int privateSlotsUsed;// Offset=0x48 Size=0x4
		unsigned char __align0[4];// Offset=0x4c Size=0x4
		unsigned int nonce;// Offset=0x50 Size=0x8
		unsigned int netType;// Offset=0x58 Size=0x1
		unsigned int clients;// Offset=0x59 Size=0x1
		unsigned int maxClients;// Offset=0x5a Size=0x1
		unsigned int dirty;// Offset=0x5b Size=0x1
		char friendlyfire;// Offset=0x5c Size=0x1
		char killcam;// Offset=0x5d Size=0x1
		char onlineStatsOffline;// Offset=0x5e Size=0x1
		unsigned int hardware;// Offset=0x5f Size=0x1
		unsigned int mod;// Offset=0x60 Size=0x1
		unsigned int requestCount;// Offset=0x61 Size=0x1
		int minPing;// Offset=0x62 Size=0x2
		int maxPing;// Offset=0x64 Size=0x2
		int ping;// Offset=0x66 Size=0x2
		char hostName[32];// Offset=0x68 Size=0x20
		char mapName[32];// Offset=0x88 Size=0x20
		char game[24];// Offset=0xa8 Size=0x18
		char gameType[16];// Offset=0xc0 Size=0x10
	};

	struct vidConfig_t// Size=0x30
	{
		unsigned int sceneWidth;// Offset=0x0 Size=0x4
		unsigned int sceneHeight;// Offset=0x4 Size=0x4
		unsigned int displayWidth;// Offset=0x8 Size=0x4
		unsigned int displayHeight;// Offset=0xc Size=0x4
		char _align[4];
		float displayFrequency;// Offset=0x10 Size=0x4
		int isHiDef;// Offset=0x14 Size=0x4
		int isFullscreen;// Offset=0x18 Size=0x4
		float aspectRatioWindow;// Offset=0x1c Size=0x4
		float aspectRatioScenePixel;// Offset=0x20 Size=0x4
		float aspectRatioDisplayPixel;// Offset=0x24 Size=0x4
		unsigned int maxTextureSize;// Offset=0x28 Size=0x4
		bool deviceSupportsGamma;// Offset=0x2c Size=0x1
	};


	union GfxColor// Size=0x4
	{
		unsigned int array[4];// Offset=0x0 Size=0x4
		unsigned int packed;// Offset=0x0 Size=0x4
	};

	struct trDebugLine_t// Size=0x20
	{
		float start[3];// Offset=0x0 Size=0xc
		float end[3];// Offset=0xc Size=0xc
		GfxColor color;// Offset=0x18 Size=0x4
		int depthTest;// Offset=0x1c Size=0x4
	};

	struct clientDebugLineInfo_t// Size=0x10
	{
		int max;// Offset=0x0 Size=0x4
		int num;// Offset=0x4 Size=0x4
		trDebugLine_t* lines;// Offset=0x8 Size=0x4
		int* durations;// Offset=0xc Size=0x4
	};

	struct trDebugString_t// Size=0x60
	{
		float xyz[3];// Offset=0x0 Size=0xc
		GfxColor color;// Offset=0xc Size=0x4
		float scale;// Offset=0x10 Size=0x4
		char text[76];// Offset=0x14 Size=0x4c
	};

	struct clientDebugStringInfo_t// Size=0x10
	{
		int max;// Offset=0x0 Size=0x4
		int num;// Offset=0x4 Size=0x4
		trDebugString_t* strings;// Offset=0x8 Size=0x4
		int* durations;// Offset=0xc Size=0x4
	};

	struct clientDebug_t// Size=0x68
	{
		int prevFromServer;// Offset=0x0 Size=0x4
		int fromServer;// Offset=0x4 Size=0x4
		clientDebugStringInfo_t clStrings;// Offset=0x8 Size=0x10
		clientDebugStringInfo_t svStringsBuffer;// Offset=0x18 Size=0x10
		clientDebugStringInfo_t svStrings;// Offset=0x28 Size=0x10
		clientDebugLineInfo_t clLines;// Offset=0x38 Size=0x10
		clientDebugLineInfo_t svLinesBuffer;// Offset=0x48 Size=0x10
		clientDebugLineInfo_t svLines;// Offset=0x58 Size=0x10
	};

	struct ClientMatchData// Size=0x440
	{
		char def[64];// Offset=0x0 Size=0x40
		unsigned int data[1024];// Offset=0x40 Size=0x400
	};

	struct gameState_t// Size=0x13bb0
	{
		int stringOffsets[3819];// Offset=0x0 Size=0x3bac
		char stringData[65536];// Offset=0x3bac Size=0x10000
		int dataCount;// Offset=0x13bac Size=0x4
	};

	typedef struct
	{
		int blurBlendFadeTime; //0x0000 
		int blurBlendTime; //0x0004 
		int whiteFadeTime; //0x0008 
		int shotFadeTime; //0x000C 
		int screenType; //0x0010 
		int screenType2; //0x0014 
		float viewKickPeriod; //0x0018 
		float viewKickRadius; //0x001C 
		BYTE _0x0020; //0x0020 
		BYTE _0x0021; //0x0021 
		BYTE _0x0022; //0x0022 
		BYTE shockSound; //0x0023 
		//char sfString[30]; //0x0024 
	}stunflashdata_t;//Size=0x0043

	typedef struct
	{
		char unknown0[43];
		__int32 soundFadeInTime;
		__int32 soundFadeOutTime;
		float soundDryLevel;
		float soundWetLevel;
		char soundRoomType[16];
		char unknown1[256];
		__int32 soundModEndDelay;
		__int32 soundLoopFadeTime;
		__int32 soundLoopEndDelay;
		DWORD lookControl;
		__int32 lookControlFadeTime;
		float lcMouseSensitivityScale;
		float lcMaxPitchSpeed;
		float lcMaxYawSpeed;
		DWORD shockMovement;
	}stunflash_t;

	enum team_t {
		TEAM_FREE,
		TEAM_AXIS,
		TEAM_ALLIES,
		TEAM_SPECTATOR,
		TEAM_NUM_TEAMS,
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

	typedef struct {
		int down[2];// Offset=0x0 Size=0x8
		unsigned int downtime;// Offset=0x8 Size=0x4
		unsigned int msec;// Offset=0xc Size=0x4
		bool active;// Offset=0x10 Size=0x1
		bool wasPressed;// Offset=0x11 Size=0x1
	}kbutton_t;

	enum handleCall_t {
		CALL_START = 0x1,
		CALL_EXECUTE = 0x2,
		CALL_TEMP = 0x3,
		CALL_STOP = 0x4,
		CALL_FREE = 0x5,
	};

	#define HANDLE_COUNT		0x100
	#define INVALID_HANDLE		((handle_t)-1)

	#define TIME_NOW			clock()
	#define TIME_NOW_OFF(x)		(clock() + (x * (CLOCKS_PER_SEC / 1000)))

	struct GfxDrawPrimArgs
	{
		int vertexCount;
		int triCount;
		int baseIndex;
	};

	struct GfxCmdBufPrimState {
		IDirect3DDevice9* device;
	};

	struct PartyInfo
	{
		BYTE active; //0x0000 
		char _0x0001[12];
		ipInfo hostIP;
		//BYTE hostIP1; //0x000D 
		//BYTE hostIP2; //0x000E 
		//BYTE hostIP3; //0x000F 
		//BYTE hostIP4; //0x0010 
		char _0x0011[47];
		__int32 occupiedPublicSlots; //0x0040 
		__int32 occupiedPrivateSlots; //0x0044 
		__int32 numPublicSlots; //0x0048 
	};

	struct SubpartyInfo// Size=0x58
	{
		int members[18];// Offset=0x0 Size=0x48
		int count;// Offset=0x48 Size=0x4
		int skill;// Offset=0x4c Size=0x4
		int score;// Offset=0x50 Size=0x4
		int team;// Offset=0x54 Size=0x4
	};

	struct partyMember
	{
		BYTE status; //0x0130 
		char _0x0131[3];
		char ab[8]; //0x0134 
		int rank_mp; //0x013C 
		int prestige_mp; //0x0140 
		int rank_so; //0x0144 
		int prestige_so; //0x0148 
		int availableMapPackFlags; //0x014C 
		int playerCardIcon; //0x0150 
		int playerCardTitle; //0x0154 
		char _0x0158[4];
		char Gamertag[32]; //0x015C 
		char clantag[4]; //0x017C 
		char _0x0180[4];
		int vote; //0x0184 
		BYTE use_elite_clan_tag; //0x0188 
		BYTE use_elite_clan_title; //0x0189 
		char elite_clan_title_text[24]; //0x018A 
		char _0x01A2[2];
		int elite_clan_title_bg; //0x01A4 
		char elite_clan_tag_text[5]; //0x01A8 
		char _0x01AD[7];
		int prestige_black_ops; //0x01B4 
		int rank_black_ops; //0x01B8 
		int prestige_mw2; //0x01BC 
		int rank_mw2; //0x01C0 
		int prestige_world_at_war; //0x01C4 
		int rank_world_at_war; //0x01C8 
		int prestige_mw; //0x01CC 
		int rank_mw; //0x01D0 
		char _0x01D4[60];
		ipInfo localIP;
		ipInfo ExternalIP;
		char _0x0218[52];
		int canUsePrivateSlot; //0x024C 
		int natType; //0x0250 
		char _0x0254[52];
	}; // 0x288

	struct partyData
	{
		int session; //0x0000 
		int searchSession; //0x0004 
		int presenceSession; //0x0008 
		char _0x000C[284];
		PartyInfo* partyList; //0x0128 
		int partyListSize; //0x012C
		partyMember partyMembers[18];
		SubpartyInfo subparties[18];
		unsigned int subpartyCount;
	};
	
	DWORD _cg_t = 0x8263EE60;
	DWORD _cgs_t = 0x8263EE44;
	DWORD cClient = 0xBB6A8508;
	DWORD cgEntities = 0x826436B8;
	DWORD uiContext = 0x836E5AF8;
	DWORD ipAddress = 0x82720FA4;
	DWORD ClientStatic = 0x82676C00;
	DWORD _concGrenade = 0x825DDD65;
	DWORD _flashGrenade = 0x825DDFCD;
	DWORD _playersKb = 0x826708E0;
	DWORD _partyData = 0x82720D90;
	
	cgs_t* cgs;
	cg_t* cg;
	CEntity* cent;
	CClient* Clients[18];
	CEntity* Entities[18];
	UIContext_s uicontext;
	clientActive* ca;
	pCentity_t Centity_s;
	CSnapshot snapshot;
	score_t* score;
	clientStatic_t clientStatic;
	partyData partydata;
	
	inline CClient* getClientbyIDx(int id)
	{
		return reinterpret_cast<CClient*>(cClient + (static_cast<int>(0x594) * id));
	}
	
	inline CEntity* getCEntitybyIDx(int id)
	{
		auto cent_ptr = *reinterpret_cast<DWORD*>(cgEntities);
		return reinterpret_cast<CEntity*>(cent_ptr + (static_cast<int>(0x01EC) * id));
	}

	inline clientActive* getCA()
	{
		auto ca_ptr = *reinterpret_cast<DWORD*>(0x82713DC4);
		return reinterpret_cast<clientActive*>(ca_ptr);
	}

	inline ipInfo* getClientIpByID(int id) {
		return reinterpret_cast<ipInfo*>(ipAddress + (static_cast<int>(0x158) * id));
	}

	inline CSnapshot getSnapShot() {
		return *reinterpret_cast<CSnapshot*>(reinterpret_cast<int>(getCA()) + 0x338C);
	}

	inline void pgStructs() {
		uicontext = *reinterpret_cast<UIContext_s*>(uiContext);
	}
	
	inline void getStructs() {
		cgs = *reinterpret_cast<cgs_t**>(_cgs_t);
		cg = *reinterpret_cast<cg_t**>(_cg_t);
		ca = static_cast<clientActive*>(getCA());
		Centity_s = *reinterpret_cast<pCentity_t*>(cgEntities);
		clientStatic = *reinterpret_cast<clientStatic_t*>(ClientStatic);
		partydata = *reinterpret_cast<partyData*>(_partyData);
		snapshot = getSnapShot();
		for (auto i = 0; i < 18; i++) Entities[i] = static_cast<CEntity*>(getCEntitybyIDx(i));
		for (auto i = 0; i < 18; i++) Clients[i] = static_cast<CClient*>(getClientbyIDx(i));		
	}
}
#endif // TU24_STRUCTS_H
