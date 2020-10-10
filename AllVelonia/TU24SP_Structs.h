#ifndef TU24SP_STRUCTS_H
#define TU24SP_STRUCTS_H

namespace TU24SP
{
	enum entityType_t
	{
		ET_GENERAL = 0,
		ET_PLAYER = 1,
		ET_ITEM = 2,
		ET_MISSILE = 3,
		ET_INVISIBLE = 4,
		ET_SCRIPTMOVER = 5,
		ET_SOUND_BLEND = 6,
		ET_PRIMARY_LIGHT = 7,
		ET_TURRET = 8,
		ET_VEHICLE = 9,
		ET_VEHICLE_COLLMAP = 10,
		ET_VEHICLE_CORPSE = 11,
		ET_VEHICLE_SPAWNER = 12,
		ET_ACTOR = 13,
		ET_ACTOR_SPAWNER = 14,
		ET_ACTOR_CORPSE = 15,
		ET_EVENTS = 16
	};	
	struct cgs_t
	{
		int viewX;
		int viewY;
		int viewWidth;
		int viewHeight;
		float viewAspect;
		float viewMult;
		bool started;
	};

	struct snapshot
	{
		int snapFlags; //0x0000 
		int serverTime; //0x0004 
		int numEntities; //0x0008 
		char entityNums[4096]; //0x000C 
		int numFxEntities; //0x100C 
		char fxEntityNums[2048]; //0x1010 
		int numSounds; //0x1810 
		char soundInfoNums[2048]; //0x1814 
	};

	struct playerstate_s
	{
		int commandTime; //0x0000 
		char _0x0004[4];
		int pm_time; //0x0008 
		int pm_flags; //0x000C 
		char _0x0010[12];
		Vector3 Origin; //0x001C 
		Vector3 Velocity; //0x0028 
		char _0x0034[36];
		int Gravity; //0x0058 
		int Speed; //0x005C 
		Vector3 delta_angles; //0x0060 
		int groundEntityNum; //0x006C 
		char _0x0070[60];
		int eFlags; //0x00AC 
		char _0x00B0[84];
		int clientNum; //0x0104 
		char _0x0108[4];
		Vector3 viewAngles; //0x010C 
		char _0x0118[208];
		float moveSpeedScaleMultiplier; //0x01E8 
		char _0x01EC[824];
		float viewKickScale; //0x0524 
		char _0x0528[32];
		char Huds[43008]; //0x0548 
		char _0xAD48[12];
	};//Size=0xAD54
	
	struct refdef
	{
		int x;// Offset=0x0 Size=0x4
		int y;// Offset=0x4 Size=0x4
		int Width;// Offset=0x8 Size=0x4
		int Height;// Offset=0xc Size=0x4
		float tanHalfFovX;// Offset=0x0 Size=0x4
		float tanHalfFovY;// Offset=0x4 Size=0x4
		Vector3 Origin;// Offset=0x8 Size=0xc
		Vector3 viewAxis[3];// Offset=0x14 Size=0x24
	};

	struct cpose_t// Size=0x54
	{
		short lightingHandle;// Offset=0x0 Size=0x2
		char eType;// Offset=0x2 Size=0x1
		char cullIn[2];// Offset=0x3 Size=0x2
		bool isRagdoll;// Offset=0x5 Size=0x1
		char __align0[2];// Offset=0x6 Size=0x2
		int ragdollHandle;// Offset=0x8 Size=0x4
		int physObjId;// Offset=0xc Size=0x4
		Vector3 origin;// Offset=0x10 Size=0xc
		Vector3 angles;// Offset=0x1c Size=0xc
		char _crap[0x2c];
	};

	enum trType_t
	{
		TR_STATIONARY = 0,
		TR_INTERPOLATE = 1,
		TR_LINEAR = 2,
		TR_LINEAR_STOP = 3,
		TR_SINE = 4,
		TR_GRAVITY = 5,
		TR_LOW_GRAVITY = 6,
		TR_ACCELERATE = 7,
		TR_DECELERATE = 8,
		TR_PHYSICS = 9,
		TR_FIRST_RAGDOLL = 10,
		TR_RAGDOLL = 10,
		TR_RAGDOLL_GRAVITY = 11,
		TR_RAGDOLL_INTERPOLATE = 12,
		TR_LAST_RAGDOLL = 12,
		NUM_TRTYPES = 13
	};

	struct trajectory_t// Size=0x24
	{
		trType_t trType;// Offset=0x0 Size=0x4
		int trTime;// Offset=0x4 Size=0x4
		int trDuration;// Offset=0x8 Size=0x4
		float trBase[3];// Offset=0xc Size=0xc
		float trDelta[3];// Offset=0x18 Size=0xc
	};

	struct LerpEntityState// Size=0x6c
	{
		int eFlags;// Offset=0x0 Size=0x4
		trajectory_t pos;// Offset=0x4 Size=0x24
		trajectory_t apos;// Offset=0x28 Size=0x24
		char _0x004C[0x1C];// Offset=0x4c Size=0x1c
		int useCount;// Offset=0x68 Size=0x4
	};
	struct entityState_s// Size=0xb0
	{
		BYTE eType;// Offset=0x0 Size=0x1
		BYTE surfType;// Offset=0x1 Size=0x1
		char __align0[2];// Offset=0x1 Size=0x2
		unsigned short loopSound;// Offset=0x4 Size=0x2
		char __align2[2];// Offset=0x6 Size=0x2
		int eventParm;// Offset=0x8 Size=0x4
		LerpEntityState lerp;// Offset=0xc Size=0x6c
		char staticState[4];// Offset=0x78 Size=0x4
		//char _weapon[4];
		short weapon;
		char _carp[2];
		int inAltWeaponMode;// Offset=0x80 Size=0x4
		short number;// Offset=0x84 Size=0x2
		short otherEntityNum;// Offset=0x86 Size=0x2
		short groundEntityNum;// Offset=0x88 Size=0x2
		char __align3[0x24];
	};

	enum meansOfDeath_t
	{
		MOD_UNKNOWN = 0,
		MOD_PISTOL_BULLET = 1,
		MOD_RIFLE_BULLET = 2,
		MOD_EXPLOSIVE_BULLET = 3,
		MOD_GRENADE = 4,
		MOD_GRENADE_SPLASH = 5,
		MOD_PROJECTILE = 6,
		MOD_PROJECTILE_SPLASH = 7,
		MOD_MELEE = 8,
		MOD_HEAD_SHOT = 9,
		MOD_CRUSH = 10,
		MOD_FALLING = 11,
		MOD_SUICIDE = 12,
		MOD_TRIGGER_HURT = 13,
		MOD_EXPLOSIVE = 14,
		MOD_IMPACT = 15,
		MOD_NUM = 16
	};

	struct BulletFireParams// Size=0x44
	{
		int weaponEntIndex;// Offset=0x0 Size=0x4
		int ignoreEntIndex;// Offset=0x4 Size=0x4
		float damageMultiplier;// Offset=0x8 Size=0x4
		meansOfDeath_t methodOfDeath;// Offset=0xc Size=0x4
		bool noRicochet;// Offset=0x10 Size=0x1
		unsigned char __align0[3];// Offset=0x11 Size=0x3
		Vector3 origStart;// Offset=0x14 Size=0xc
		Vector3 start;// Offset=0x20 Size=0xc
		Vector3 end;// Offset=0x2c Size=0xc
		Vector3 dir;// Offset=0x38 Size=0xc
	};

	struct CEntity// Size=0x188
	{
		cpose_t pose;// Offset=0x0 Size=0x54
		LerpEntityState prevState;// Offset=0x54 Size=0x6c
		entityState_s nextState;// Offset=0xc0 Size=0xb0
		int _unknown;// Offset=0x170 Size=0x4
		char tracerDrawRateCounter;// Offset=0x174 Size=0x1
		char prevEType;// Offset=0x175 Size=0x1
		char __align0[2];// Offset=0x176 Size=0x2
		int previousEventSequence;// Offset=0x178 Size=0x4
		Vector3 lightingOrigin;// Offset=0x17c Size=0xc
	};

	struct cg_t
	{
		int clientNum; //0x0000 
		int localClientNum; //0x0004 
		char _0x0008[16];
		int loaded; //0x0018 
		snapshot* snap; //0x001C 
		snapshot* nextsnap; //0x0020 
		playerstate_s* ps; //0x0024 
		playerstate_s* nextPs; //0x0028 
		char _0x002C[133144]; //0x002C 
		CEntity* predictedPlayerEntity; //0x20844 
		char _0x20848[104];
		refdef refdef; //0x208B0 
	};

	struct cgCommon_t
	{
		char _0x0000[4];
		snapshot* snap; //0x0004 
		snapshot* nextSnap; //0x0008 
		char _0x000C[16424]; //0x000C 
		int time; //0x4034 
		char _0x4038[4];
		float frameInterpolation; //0x403C 
		char _0x4040[452];
		char mapname[64]; //0x4204 
	};// Size=0x4244

	typedef struct {
		char _0x0000[8];
		char servername[256];
	} clientStatic_t;


	struct clientInfo_t
	{
		int valid; //0x0000 
		int clientNum; //0x0004 
		char _0x0008[100];
		Vector3 Angles; //0x006C 
		char _0x0078[260];
		int playerCardIcon; //0x017C 
		int playerCardTitle; //0x0180 
		int playerCardNameplate; //0x0184 
		BYTE use_elite_clan_tag; //0x0188 
		BYTE use_elite_clan_title; //0x0189 
		char elite_clan_title_text[24]; //0x018A 
		char _0x01A2[2];
		int elite_clan_title_bg; //0x01A4 
		char elite_clan_tag_text[5]; //0x01A8 
		char _0x01AD[3];
		int prestige_black_ops; //0x01B0 
		int rank_black_ops; //0x01B4 
		int prestige_mw2; //0x01B8 
		int rank_mw2; //0x01BC 
		int prestige_world_at_war; //0x01C0 
		int rank_world_at_war; //0x01C4 
		int prestige_mw; //0x01C8 
		int rank_mw; //0x01CC
	};	//Size=0x01D0


	struct bgs_t
	{
		char _0x0000[549852];
		clientInfo_t clientinfo[2];// Offset=0x863dc Size=0x3a0
	};

	enum TraceHitType
	{
		TRACE_HITTYPE_NONE = 0,
		TRACE_HITTYPE_ENTITY = 1,
		TRACE_HITTYPE_DYNENT_MODEL = 2,
		TRACE_HITTYPE_DYNENT_BRUSH = 3,
		TRACE_HITTYPE_GLASS = 4
	};

	struct trace_t// Size=0x2c
	{
		float fraction;// Offset=0x0 Size=0x4
		float normal[3];// Offset=0x4 Size=0xc
		int surfaceFlags;// Offset=0x10 Size=0x4
		int contents;// Offset=0x14 Size=0x4
		char* material;// Offset=0x18 Size=0x4
		TraceHitType hitType;// Offset=0x1c Size=0x4
		short hitId;// Offset=0x20 Size=0x2
		short modelIndex;// Offset=0x22 Size=0x2
		short partName;// Offset=0x24 Size=0x2
		short partGroup;// Offset=0x26 Size=0x2
		bool allsolid;// Offset=0x28 Size=0x1
		bool startsolid;// Offset=0x29 Size=0x1
		bool walkable;// Offset=0x2a Size=0x1
	};

	struct usercmd_s// Size=0x40
	{
		int serverTime;// Offset=0x0 Size=0x4
		int buttons;// Offset=0x4 Size=0x4
		int angles[3];// Offset=0x8 Size=0xc
		char weapon[4];// Offset=0x14 Size=0x4
		char offHand[4];// Offset=0x18 Size=0x4
		int forwardmove;// Offset=0x1c Size=0x1
		int rightmove;// Offset=0x1d Size=0x1
		unsigned char upmove;// Offset=0x1e Size=0x1
		unsigned char downmove;// Offset=0x1f Size=0x1
		int pitchmove;// Offset=0x20 Size=0x1
		int yawmove;// Offset=0x21 Size=0x1
		unsigned char __align0[2];// Offset=0x22 Size=0x2
		float gunPitch;// Offset=0x24 Size=0x4
		float gunYaw;// Offset=0x28 Size=0x4
		float gunXOfs;// Offset=0x2c Size=0x4
		float gunYOfs;// Offset=0x30 Size=0x4
		float gunZOfs;// Offset=0x34 Size=0x4
		int meleeChargeYaw;// Offset=0x38 Size=0x2
		unsigned char meleeChargeDist;// Offset=0x3a Size=0x1
		int selectedLoc[2];// Offset=0x3b Size=0x2
		unsigned char selectedLocAngle;// Offset=0x3d Size=0x1
		int remoteControlAngles[2];// Offset=0x3e Size=0x2
	};

	enum StanceState
	{
		CL_STANCE_STAND = 0,
		CL_STANCE_CROUCH = 1,
		CL_STANCE_PRONE = 2
	};

	union Weapon// Size=0x4
	{
		unsigned int padding : 8;// Offset=0x0 Size=0x4 BitOffset=0x18 BitSize=0x8
		unsigned int scopeVariation : 3;// Offset=0x0 Size=0x4 BitOffset=0x15 BitSize=0x3
		unsigned int weaponOthers : 4;// Offset=0x0 Size=0x4 BitOffset=0x11 BitSize=0x4
		unsigned int weaponUnderBarrels : 2;// Offset=0x0 Size=0x4 BitOffset=0xf BitSize=0x2
		unsigned int weaponScopes : 3;// Offset=0x0 Size=0x4 BitOffset=0xc BitSize=0x3
		unsigned int weaponVariation : 4;// Offset=0x0 Size=0x4 BitOffset=0x8 BitSize=0x4
		unsigned int weaponIdx : 8;// Offset=0x0 Size=0x4 BitOffset=0x0 BitSize=0x8
		unsigned int data;// Offset=0x0 Size=0x4
	};

	struct outPacket_t// Size=0xc
	{
		int p_cmdNumber;// Offset=0x0 Size=0x4
		int p_serverTime;// Offset=0x4 Size=0x4
		int p_realtime;// Offset=0x8 Size=0x4
	};
	
	struct clientActive_t// Size=0xbe90
	{
		bool usingAds;// Offset=0x0 Size=0x1
		unsigned char __align0[3];// Offset=0x1 Size=0x3
		int mouseDx[2];// Offset=0x4 Size=0x8
		int mouseDy[2];// Offset=0xc Size=0x8
		int mouseIndex;// Offset=0x14 Size=0x4
		bool stanceHeld;// Offset=0x18 Size=0x1
		unsigned char __align1[3];// Offset=0x19 Size=0x3
		StanceState stance;// Offset=0x1c Size=0x4
		StanceState stancePosition;// Offset=0x20 Size=0x4
		int stanceTime;// Offset=0x24 Size=0x4
		Weapon cgameUserCmdWeapon;// Offset=0x28 Size=0x4
		Weapon cgameUserCmdOffHand;// Offset=0x2c Size=0x4
		bool cgameUserCmdAlternate;// Offset=0x30 Size=0x1
		unsigned char __align2[3];// Offset=0x31 Size=0x3
		float cgameUserCmdGunPitch;// Offset=0x34 Size=0x4
		float cgameUserCmdGunYaw;// Offset=0x38 Size=0x4
		float cgameUserCmdGunXOfs;// Offset=0x3c Size=0x4
		float cgameUserCmdGunYOfs;// Offset=0x40 Size=0x4
		float cgameUserCmdGunZOfs;// Offset=0x44 Size=0x4
		float cgameFOVSensitivityScale;// Offset=0x48 Size=0x4
		float cgameMaxPitchSpeed;// Offset=0x4c Size=0x4
		float cgameMaxYawSpeed;// Offset=0x50 Size=0x4
		int cgameExtraButtons;// Offset=0x54 Size=0x4
		Vector3 viewangles;// Offset=0x58 Size=0xc
		usercmd_s cmds[64];// Offset=0x64 Size=0x1000
		int cmdNumber;// Offset=0x1064 Size=0x4
		int cmdNumberAcknowledge;// Offset=0x1068 Size=0x4
		int bCmdForceValues;// Offset=0x106c Size=0x4
		int iForceButtons;// Offset=0x1070 Size=0x4
		Weapon iForceWeapon;// Offset=0x1074 Size=0x4
		Weapon forceOffhand;// Offset=0x1078 Size=0x4
		playerstate_s ps;// Offset=0x107c Size=0xad54
		outPacket_t outPackets[16];// Offset=0xbdd0 Size=0xc0
		usercmd_s GetCmd(int Index)
		{
			return cmds[(Index & 0x3F)];
		}
		usercmd_s getCmd() {
			return GetCmd(cmdNumber);
		}
		usercmd_s getLastCmd() {
			return GetCmd(cmdNumber - 1);
		}
	};
	
	struct client_t// Size=0x3a88
	{
		int state;// Offset=0x0 Size=0x4
		char _ignorereliableCommands[0x120c];
		char _ignoreHeader[8];// Offset=0x1210 Size=0x8
		int lastClientCommand;// Offset=0x1218 Size=0x4
		char lastClientCommandString[1024];// Offset=0x121c Size=0x400
		char name[32];// Offset=0x161c Size=0x20
		int lastPacketTime;// Offset=0x163c Size=0x4
		unsigned char stats[8192];// Offset=0x1640 Size=0x2000
		unsigned char statsModifiedFlags[1024];// Offset=0x3640 Size=0x400
		bool statsModified;// Offset=0x3a40 Size=0x1
		unsigned char statPacketsReceived;// Offset=0x3a41 Size=0x1
		unsigned char __align0[2];// Offset=0x3a42 Size=0x2
		usercmd_s lastUsercmd;// Offset=0x3a44 Size=0x40
		int gentity;// Offset=0x3a84 Size=0x4
	};

	enum netadrtype_t
	{
		NA_BOT = 0,
		NA_BAD = 1,
		NA_LOOPBACK = 2,
		NA_BROADCAST = 3,
		NA_IP = 4
	};
	
	struct netadr_t// Size=0xc
	{
		netadrtype_t type;// Offset=0x0 Size=0x4
		unsigned char ip[4];// Offset=0x4 Size=0x4
		unsigned short port;// Offset=0x8 Size=0x2
	};

	struct serverStatic_t// Size=0x7534
	{
		int snapFlagServerBit;// Offset=0x0 Size=0x4
		client_t clients[2];// Offset=0x4 Size=0x7510
		int numSnapshotEntities;// Offset=0x7514 Size=0x4
		int nextSnapshotEntities;// Offset=0x7518 Size=0x4
		netadr_t authorizeAddress;// Offset=0x751c Size=0xc
		int playerDeaths;// Offset=0x7528 Size=0x4
		int playerScore;// Offset=0x752c Size=0x4
		int outgoingSequence;// Offset=0x7530 Size=0x4
	};
	
	cgs_t cgs;
	cg_t cg;
	cgCommon_t cgameCommonGlob;
	clientStatic_t cs;
	CEntity Centity_s[2046];
	bgs_t bgs;
	serverStatic_t sStatic;
	clientActive_t ca;
	
	bool done = false;

	inline CEntity getCent(int clientNum)
	{
		return *reinterpret_cast<CEntity*>(0x825CC068 + (0x188 * clientNum));
	}

	inline clientActive_t getCA()
	{
		return *reinterpret_cast<clientActive_t*>(0x8275E8A0);
	}
	
	inline void getStructs()
	{
		cgs = *reinterpret_cast<cgs_t*>(0x825564D0);
		cg = *reinterpret_cast<cg_t*>(0x825569F0);
		cgameCommonGlob = *reinterpret_cast<cgCommon_t*>(0x8269C1D8);
		cs = *reinterpret_cast<clientStatic_t*>(0x826CC3A8);
		bgs = *reinterpret_cast<bgs_t*>(0x8309E690);
		sStatic = *reinterpret_cast<serverStatic_t*>(0x83E50688);
		ca = getCA();
		for (auto i = 0; i < 2046; i++) Centity_s[i] = getCent(i);
		
		if (!done)
		{
			done = !done;
		}
	}
}
#endif // TU24SP_STRUCTS_H
