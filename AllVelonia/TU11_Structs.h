namespace TU11
{
	enum entityType_t
	{
		ET_GENERAL = 0,
		ET_PLAYER = 1,
		ET_PLAYER_CORPSE = 2,
		ET_ITEM = 3,
		ET_MISSILE = 4,
		ET_INVISIBLE = 5,
		ET_SCRIPTMOVER = 6,
		ET_SOUND_BLEND = 7,
		ET_FX = 8,
		ET_LOOP_FX = 9,
		ET_PRIMARY_LIGHT = 10,
		ET_MG42 = 11,
		ET_PLANE = 12,
		ET_VEHICLE = 13,
		ET_VEHICLE_CORPSE = 14,
		ET_VEHICLE_COLLMAP = 15,
		ET_ACTOR = 16,
		ET_ACTOR_SPAWNER = 17,
		ET_ACTOR_CORPSE = 18,
		ET_STREAMER_HINT = 19
	};

	struct __declspec(align(8)) MaterialInfo
	{
		char* name;
	};

	struct Material {
		MaterialInfo info;
	};
	
	struct UIContext_s {
		char _0x0000[28];
		__int32 screenWidth;
		__int32 screenHeight;
		char _0x0024[0x4];
		float fps;
	};


	typedef struct {
		char _0x0000[4];
		char servername[256];
	} clientStatic_t;
	
	typedef struct
	{
		char padding00[0x8];			//0x0
		int Width;						//0x8
		int Height;						//0xC
		char padding01[0x14];			//0x10
		Vector2 Fov;					//0x24
		float Fov_f;					//0x2C
		Vector3 viewOrigin;				//0x30
		char padding02[0x4];			//0x3C
		Vector3 viewAxis[3];			//0x40
	}RefDef_t;

	struct score_s// Size=0x2c
	{
		int ping;// Offset=0x0 Size=0x4
		int status_icon;// Offset=0x4 Size=0x4
		int place;// Offset=0x8 Size=0x4
		int score;// Offset=0xc Size=0x4
		int kills;// Offset=0x10 Size=0x4
		int assists;// Offset=0x14 Size=0x4
		int deaths;// Offset=0x18 Size=0x4
		int scoreboardColumns[5];// Offset=0x1c Size=0x14
	};


	struct cgs_t
	{
		char _0x0000[8];
		int viewWidth; //0x0008 
		int viewHeight; //0x000C 
		float viewAspect; //0x0010 
		char _0x0014[28];
		char GameType[32]; //0x0030 
		char Host[256]; //0x0050 
		int maxclients; //0x0150 
		char _0x0154[4];
		char Map[64]; //0x0158 
		int gameEndTime; //0x0198 
	};
	
	//struct clientInfo
	//{
	//	int infoValid; //0x0000 
	//	char _0x0004[4];
	//	int clientNum; //0x0008 
	//	char name[32]; //0x000C 
	//	int team; //0x002C 
	//	char _0x0030[8];
	//	int Rank; //0x0038 
	//	int Prestige; //0x003C 
	//	char _0x0040[24];
	//	char clanAbbrev[4]; //0x0058 
	//	char _0x005C[1012];
	//	Vector3 playerAngles; //0x0450 
	//	char _0x045C[372]; //0x045C
	//};//Size=0x0514

	struct clientInfo
	{
		int infoValid; //0x0000 
		char _0x0004[4];
		int clientNum; //0x0008 
		char name[32]; //0x000C 
		int team; //0x002C 
		char _0x0030[32];
		char ClanTag[4]; //0x0050 
		char _0x0054[1020];
		Vector3 playerAngles; //0x0450 
		char _0x045C[420];
	}; //Size=0x0600
	
	typedef struct
	{
		unsigned char _0x0000[28];
		unsigned long  InGame; //0x001C 
		unsigned char _0x0020[100];
		unsigned long  Ping; //0x0084 
		unsigned long  iNewTime; //0x0088 
		unsigned long  Servertime; //0x008C 
		unsigned long  iOldTime; //0x0090 
		unsigned char _0x0094[32];
		Vector3 Origin; //0x00B4 
		unsigned char _0x00C0[256];
		unsigned char ClientNumber; //0x01C0 
		unsigned char _0x01C1[19];
		short WeaponID; //0x01D4 
		unsigned char _0x01D6[34];
		float fZoomProgress; //0x01F8 
		unsigned char _0x01FC[88];
		int Health; //0x0254 
		unsigned char _0x0258[4];
		int MaxHealth; //0x025C 
		unsigned char _0x0260[432];
		int iSecondaryAmmo; //0x0410 
		unsigned char _0x0414[4];
		int iPrimaryAmmo; //0x0418 
		unsigned char _0x041C[108];
		int iSecondaryClip; //0x0488 
		unsigned char _0x048C[4];
		int iPrimaryClip; //0x0490 
		unsigned char _0x0494[0x15C];	//0x0840
		float SpreadMultiplier;			//0x05F0
		unsigned char _0x05F4[0x3EB28];
		Vector3 ViewAngle;				//0x3F11C
		char padding03[0x28D8];			//0x3F128
		RefDef_t RefDef;				//0x41A00
		char padding04[0x1C094];		//0x41A64
		clientInfo ClientInfo[18];		//0x5DAF8
		char padding05[0x4ECC];			//0x64398
		float SpreadMultiplier2;		//0x69264
	} cgArray_t;

	typedef struct
	{
		int ClientNumber;
		char _0x0000[100];
		Vector3 Origin; //0x0068 
		Vector3 velocity; //0x0074 
		int weaponTime; //0x0080 
		char _0x0084[56];
		int gravity; //0x00BC 
		char _0x00C0[4];
		int speed; //0x00C4 
		Vector3 delta_angles; //0x00C8 
		int groundEntityNum; //0x00D4 
		char _0x00D8[4];
		Vector3 vLadderVec; //0x00DC 
		int jumpTime; //0x00E8 
		float jumpOriginZ; //0x00EC 
		int slideTime; //0x00F0 
		int moveType; //0x00F4 
		int legsTimer; //0x00F8 
		int torsoTimer; //0x00FC 
		int legsAnim; //0x0100 
		int torsoAnim; //0x0104 
		int legsAnimDuration; //0x0108 
		int torsoAnimDuration; //0x010C 
		int damageTimer; //0x0110 
		int damageDuration; //0x0114 
		int dmgDirection; //0x0118 
		char _0x011C[92];
		int crap1; //0x0178 
		char _0x017C[4];
		int crap; //0x0180 
		int crap2; //0x0184 
		short weapon; //0x0188 
		char _0x018A[14];
		int N004E9045; //0x0198 
		int N004E9046; //0x019C 
		char _0x01A0[12];
		float adsDelayTime; //0x01AC 
		char _0x01B0[88];
		int Health; //0x0208 
		char _0x020C[4];
		int MaxHealth; //0x0210 
		char _0x0214[496];
		int iPrimaryAmmo; //0x0404 
		char _0x0408[360];
		float SpreadMultiplier; //0x0570 
		char N006EE366[572284]; //0x0574 
		RefDef_t RefDef;  //_0x8C0F0
		char _unknown[193836];
		clientInfo ClientInfo[4];
	} cgArray;//Size=0x8C130

	typedef struct // size 0x34
	{
		int time;		// 0x00-0x04
		int buttons;		// 0x04-0x08
		char Buf8[4];		// 0x08-0x0C
		int viewAngles[3];		// 0x0C-0x18
		short weapon;		// 0x18-0x1A
		short offHandIndex;	// 0x1A-0x1C
		char padding[0x2];
		char fDir;	// 0x1C-0x1D
		char rDir;		// 0x1D-0x1E
		char Buf1E[0x14];	// 0x1E-0x34
	}Usercmd_t;

	typedef struct
	{
		char padding00[0xAC];			//0x00
		Vector3 baseAngle;				//0xAC
		char padding01[0x2788];			//0xB4
		Vector3 viewAngle;				//0x2840
		char padding02[0x40010];		//0x2848
		Usercmd_t Usercmd[128];			//0x4285C
		int CurrentCmdNumber;			//0x4425C
		Usercmd_t* getCmd(int id) {
			return &Usercmd[(id & 0x7F)];
		}
		Usercmd_t* getCmd() {
			return getCmd(CurrentCmdNumber);
		}
		Usercmd_t* getLastCmd() {
			return getCmd(CurrentCmdNumber - 1);
		}
	}ClientActive_t;

	typedef struct
	{
		int number; // 0x0
		int eType; // 0x4
		int eFlags; // 0x8
		char pad1[176]; // 0xC
		__int16 mod; // 0xBC; MethodOfDeath enum
		char pad2[6]; // 0xBE
		__int16 victim; // 0xC4
		__int16 attacker; // 0xC6
	} entityState_s;
	
	//typedef struct
	//{
	//	unsigned char _0x0000[48];
	//	Vector3 Origin; //0x0030
	//	Vector3 Angle;
	//	unsigned char _0x003C[288];
	//	int Flags; //0x0168 
	//	unsigned char _0x016C[4];
	//	unsigned char Valid; //0x0170 
	//	unsigned char _0x0171[11];
	//	Vector3 OldOrigin; //0x017C
	//	unsigned char _0x0188[0x54];
	//	int Handle; // 0x01DC
	//	unsigned char _0x01E0[0x14];
	//	Vector3 NewOrigin; //0x01F4 
	//	/*unsigned char _0x0200[164];*/
	//	char _0x0200[154];
	//	short Type; //0x029A
	//	char _0x029C[8];
	//	int WeaponID; //0x02A4 
	//	unsigned char _0x02A8[0x74]; // 0x2A8
	//}Centity_t, * pCentity_t;
	//
	typedef struct
	{
		char _0x0000[2];
		BYTE eType; //0x0002 
		BYTE localClientNum; //0x0003 
		char _0x0004[32];
		Vector3 Origin; //0x0024 
		char _0x0030[300];
		int Flags; //0x015C 
		char _0x0160[4];
		BYTE Valid; //0x0164 
		char _0x0165[11];
		Vector3 oldOrigin; //0x0170 
		char _0x017C[132];
		short N00DBBEC4; //0x0200 
		char _0x0202[42];
		short N00DBBECF; //0x022C 
		char _0x022E[22];
		Vector3 newOrigin; //0x0244 
		char _0x0250[60];
		short WeaponID; //0x028C 
		char _0x028E[130];
	}Centity_t, * pCentity_t;

	struct CSnapshot {
		int valid; //0x0000 
		int snapFlags; //0x0004 
		char _0x0008[16];
		int ping; //0x0018 
		char _0x001C[9964];
		int entityCount; //0x2708 
		int connectedClients; //0x270C 
	};


	struct rectDef_s
	{
		float x;// Offset=0x0 Size=0x4
		float y;// Offset=0x4 Size=0x4
		float w;// Offset=0x8 Size=0x4
		float h;// Offset=0xc Size=0x4
		DWORD unk;
	};
	
	struct windowDef_t// Size=0xa4
	{
		char* name;// Offset=0x0 Size=0x4
		rectDef_s rect;// Offset=0x4 Size=0x18
		rectDef_s rectClient;// Offset=0x1c Size=0x18
		char* group;// Offset=0x34 Size=0x4
		unsigned char style;// Offset=0x38 Size=0x1
		unsigned char border;// Offset=0x39 Size=0x1
		unsigned char modal;// Offset=0x3a Size=0x1
		unsigned char frameSides;// Offset=0x3b Size=0x1
		float frameTexSize;// Offset=0x3c Size=0x4
		float frameSize;// Offset=0x40 Size=0x4
		int ownerDraw;// Offset=0x44 Size=0x4
		int ownerDrawFlags;// Offset=0x48 Size=0x4
		float borderSize;// Offset=0x4c Size=0x4
		int staticFlags;// Offset=0x50 Size=0x4
		int dynamicFlags[1];// Offset=0x54 Size=0x4
		int nextTime;// Offset=0x58 Size=0x4
		float foreColor[4];// Offset=0x5c Size=0x10
		float backColor[4];// Offset=0x6c Size=0x10
		float borderColor[4];// Offset=0x7c Size=0x10
		float outlineColor[4];// Offset=0x8c Size=0x10
		float rotation;// Offset=0x9c Size=0x4
		int background;// Offset=0xa0 Size=0x4
	};

	union itemDefData_t// Size=0x4
	{
		int textDef;// Offset=0x0 Size=0x4
		int imageDef;// Offset=0x0 Size=0x4
		int blankButtonDef;// Offset=0x0 Size=0x4
		int ownerDrawDef;// Offset=0x0 Size=0x4
		void* data;// Offset=0x0 Size=0x4
	};


	struct menuDef_t// Size=0x190
	{
		struct windowDef_t window;// Offset=0x0 Size=0xa4
		char* font;// Offset=0xa4 Size=0x4
	};
	
	struct itemDef_s// Size=0x110
	{
		windowDef_t window;// Offset=0x0 Size=0xa4
		int type;// Offset=0xa4 Size=0x4
		int dataType;// Offset=0xa8 Size=0x4
		int imageTrack;// Offset=0xac Size=0x4
		char* dvar;// Offset=0xb0 Size=0x4
		char* dvarTest;// Offset=0xb4 Size=0x4
		char* enableDvar;// Offset=0xb8 Size=0x4
		int dvarFlags;// Offset=0xbc Size=0x4
		itemDefData_t typeData;// Offset=0xc0 Size=0x4
		menuDef_t* parent;// Offset=0xc4 Size=0x4
	};


	typedef enum
	{
		M_KNIFE = 7,
		M_HEADSHOT = 9,
		M_CRUSHED = 10,
		M_FALL = 12,
		M_SUICIDE = 14,
		M_GRENADE = 16
	} MethodOfDeath;

	//829F8E58
	struct ipInfo
	{
		char name[32];
		char clantag[4];
		
	};

	enum TraceHitType
	{
		TRACE_HITTYPE_NONE = 0,
		TRACE_HITTYPE_ENTITY = 1,
		TRACE_HITTYPE_DYNENT_MODEL = 2,
		TRACE_HITTYPE_DYNENT_BRUSH = 3,
		TRACE_HITTYPE_GLASS = 4
	};
	
	struct trace_t// Size=0x38
	{
		char crap[4];// Offset=0x0 Size=0x10
		float fraction;// Offset=0x10 Size=0x4
		int sflags;// Offset=0x14 Size=0x4
		int cflags;// Offset=0x18 Size=0x4
		TraceHitType hitType;// Offset=0x1c Size=0x4
		unsigned short hitId;// Offset=0x20 Size=0x2
		unsigned short modelIndex;// Offset=0x22 Size=0x2
		unsigned short partName;// Offset=0x24 Size=0x2
		unsigned short boneIndex;// Offset=0x26 Size=0x2
		unsigned short partGroup;// Offset=0x28 Size=0x2
		bool allsolid;// Offset=0x2a Size=0x1
		bool startsolid;// Offset=0x2b Size=0x1
		bool walkable;// Offset=0x2c Size=0x1
	};
	
	cgArray* cg;
	cgs_t* cgs;
	pCentity_t Centity_s;
	ClientActive_t* ClientActive;
	UIContext_s uicontext;
	CSnapshot snapshot;

	ipInfo clientIps[18];
	
	bool done = false;

	inline void pgStructs()
	{
		uicontext = *reinterpret_cast<UIContext_s*>(0x832D4000);
	}

	inline ipInfo clientIPPointer(int i)
	{
		return *reinterpret_cast<ipInfo*>(0x829F8E58 + (static_cast<int>(0x1C0) * i));
	}

	inline void getStructs()
	{
		cg = *reinterpret_cast<cgArray**>(0x836DBAAC);
		Centity_s = *reinterpret_cast<pCentity_t*>(0x836DCDDC);
		ClientActive = *reinterpret_cast<ClientActive_t**>(0x8363338C);
		cgs = *reinterpret_cast<cgs_t**>(0x836DBA7C);
		//snapshot = *reinterpret_cast<CSnapshot*>(reinterpret_cast<int>(ClientActive) + 8);
		//clientStatic 83618710
		if (!done)
		{
			for (auto i = 0; i < cgs->maxclients; i++)
			{
				printf("LocalClientNum: %d\n", cg->ClientNumber);
				printf("Pointer %p - Ent Pointer %p\n", &cg->ClientInfo[i], &Centity_s[i]);
				if (*cg->ClientInfo[i].name != 0)
					printf("Client %d > %s\n", cg->ClientInfo[i].clientNum, cg->ClientInfo[i].name);
			}
			done = !done;
		}
	}
}