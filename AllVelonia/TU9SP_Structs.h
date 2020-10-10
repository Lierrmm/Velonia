#ifndef TU9SP_STRUCTS_H
#define TU9SP_STRUCTS_H

namespace TU9SP
{
	#pragma region enums
    enum CubemapShot
    {
        CUBEMAPSHOT_NONE = 0,
        CUBEMAPSHOT_RIGHT = 1,
        CUBEMAPSHOT_LEFT = 2,
        CUBEMAPSHOT_BACK = 3,
        CUBEMAPSHOT_FRONT = 4,
        CUBEMAPSHOT_UP = 5,
        CUBEMAPSHOT_DOWN = 6,
        CUBEMAPSHOT_COUNT = 7
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
    enum InvalidCmdHintType
    {
        INVALID_CMD_NONE = 0,
        INVALID_CMD_NO_AMMO_BULLETS = 1,
        INVALID_CMD_NO_AMMO_GRENADE = 2,
        INVALID_CMD_STAND_BLOCKED = 3,
        INVALID_CMD_CROUCH_BLOCKED = 4,
        INVALID_CMD_PRONE_BLOCKED = 5,
        INVALID_CMD_TARGET_TOO_CLOSE = 6,
        INVALID_CMD_LOCKON_REQUIRED = 7,
        INVALID_CMD_NOT_ENOUGH_CLEARANCE = 8
    };
    enum clientConnected_t
    {
        CON_DISCONNECTED = 0,
        CON_CONNECTING = 1,
        CON_CONNECTED = 2
    };
    enum team_t
    {
        TEAM_FREE = 0,
        TEAM_BAD = 0,
        TEAM_AXIS = 1,
        TEAM_ALLIES = 2,
        TEAM_THREE = 3,
        TEAM_NEUTRAL = 4,
        TEAM_DEAD = 5,
        TEAM_NUM_TEAMS = 6
    };
    enum AISpecies
    {
        AI_SPECIES_HUMAN = 0,
        AI_SPECIES_DOG = 1,
        AI_SPECIES_CIVILIAN = 2,
        MAX_AI_SPECIES = 3,
        AI_SPECIES_ALL = 3
    };
	#pragma endregion 
	
	struct cgs_t// Size=0x280
	{
		int viewX;// Offset=0x0 Size=0x4
		int viewY;// Offset=0x4 Size=0x4
		int viewWidth;// Offset=0x8 Size=0x4
		int viewHeight;// Offset=0xc Size=0x4
		float viewAspect;// Offset=0x10 Size=0x4
		bool started;// Offset=0x14 Size=0x1
		unsigned char __align0[3];// Offset=0x15 Size=0
	};
	
	struct clientStatic_t
	{
		char _0x0000[4];
		char mapname[64]; //0x0004 
		char servername[256]; //0x0044 
	};

    struct MaterialInfo// Size=0x18
    {
        char* name;// Offset=0x0 Size=0x4
    };

    struct Material// Size=0x58
    {
        MaterialInfo info;// Offset=0x0 Size=0x18
    };

    struct playerState_s// Size=0xaca4
    {
        int commandTime;// Offset=0x0 Size=0x4
        int pm_type;// Offset=0x4 Size=0x4
        int pm_time;// Offset=0x8 Size=0x4
        int pm_flags;// Offset=0xc Size=0x4
        int otherFlags;// Offset=0x10 Size=0x4
        int linkFlags;// Offset=0x14 Size=0x4
        int bobCycle;// Offset=0x18 Size=0x4
        Vector3 origin;// Offset=0x1c Size=0xc
        Vector3 velocity;// Offset=0x28 Size=0xc
        int grenadeTimeLeft;// Offset=0x34 Size=0x4
        int throwbackGrenadeOwner;// Offset=0x38 Size=0x4
        int throwbackGrenadeTimeLeft;// Offset=0x3c Size=0x4
        unsigned int throwbackWeaponIndex;// Offset=0x40 Size=0x4
        int remoteEyesEnt;// Offset=0x44 Size=0x4
        int remoteEyesTagname;// Offset=0x48 Size=0x4
        int remoteControlEnt;// Offset=0x4c Size=0x4
        int foliageSoundTime;// Offset=0x50 Size=0x4
        int gravity;// Offset=0x54 Size=0x4
        float leanf;// Offset=0x58 Size=0x4
        int speed;// Offset=0x5c Size=0x4
        float delta_angles[3];// Offset=0x60 Size=0xc
        int groundEntityNum;// Offset=0x6c Size=0x4
        float vLadderVec[3];// Offset=0x70 Size=0xc
        int jumpTime;// Offset=0x7c Size=0x4
        float jumpOriginZ;// Offset=0x80 Size=0x4
        int legsTimer;// Offset=0x84 Size=0x4
        int legsAnim;// Offset=0x88 Size=0x4
        int torsoTimer;// Offset=0x8c Size=0x4
        int torsoAnim;// Offset=0x90 Size=0x4
        int legsAnimDuration;// Offset=0x94 Size=0x4
        int torsoAnimDuration;// Offset=0x98 Size=0x4
        int damageTimer;// Offset=0x9c Size=0x4
        int damageDuration;// Offset=0xa0 Size=0x4
        int flinchYawAnim;// Offset=0xa4 Size=0x4
        int movementDir;// Offset=0xa8 Size=0x4
        int eFlags;// Offset=0xac Size=0x4
        int eventSequence;// Offset=0xb0 Size=0x4
        int events[4];// Offset=0xb4 Size=0x10
        unsigned int eventParms[4];// Offset=0xc4 Size=0x10
        int oldEventSequence;// Offset=0xd4 Size=0x4
        int unpredictableEventSequence;// Offset=0xd8 Size=0x4
        int unpredictableEventSequenceOld;// Offset=0xdc Size=0x4
        int unpredictableEvents[4];// Offset=0xe0 Size=0x10
        unsigned int unpredictableEventParms[4];// Offset=0xf0 Size=0x10
        int clientNum;// Offset=0x100 Size=0x4
        int viewmodelIndex;// Offset=0x104 Size=0x4
        float viewangles[3];// Offset=0x108 Size=0xc
        int viewHeightTarget;// Offset=0x114 Size=0x4
        float viewHeightCurrent;// Offset=0x118 Size=0x4
        int viewHeightLerpTime;// Offset=0x11c Size=0x4
        int viewHeightLerpTarget;// Offset=0x120 Size=0x4
        int viewHeightLerpDown;// Offset=0x124 Size=0x4
        float viewAngleClampBase[2];// Offset=0x128 Size=0x8
        float viewAngleClampRange[2];// Offset=0x130 Size=0x8
        int damageEvent;// Offset=0x138 Size=0x4
        int damageYaw;// Offset=0x13c Size=0x4
        int damagePitch;// Offset=0x140 Size=0x4
        int damageCount;// Offset=0x144 Size=0x4
        int damageFlags;// Offset=0x148 Size=0x4
        int stats[4];// Offset=0x14c Size=0x10
        float proneDirection;// Offset=0x15c Size=0x4
        float proneDirectionPitch;// Offset=0x160 Size=0x4
        float proneTorsoPitch;// Offset=0x164 Size=0x4
        char _viewLocked[0x4];
        int viewlocked_entNum;// Offset=0x16c Size=0x4
        float linkAngles[3];// Offset=0x170 Size=0xc
        float linkWeaponAngles[3];// Offset=0x17c Size=0xc
        int linkWeaponEnt;// Offset=0x188 Size=0x4
        int loopSound;// Offset=0x18c Size=0x4
        int vehicleType;// Offset=0x190 Size=0x4
        float groundTiltAngles[3];// Offset=0x194 Size=0xc
        int cursorHint;// Offset=0x1a0 Size=0x4
        int cursorHintString;// Offset=0x1a4 Size=0x4
        int cursorHintEntIndex;// Offset=0x1a8 Size=0x4
        int cursorHintDualWield;// Offset=0x1ac Size=0x4
        int motionTrackerEnabled;// Offset=0x1b0 Size=0x4
        int locationSelectionInfo;// Offset=0x1b4 Size=0x4
        char sprintState[0x14];
        float holdBreathScale;// Offset=0x1cc Size=0x4
        int holdBreathTimer;// Offset=0x1d0 Size=0x4
        float moveSpeedScaleMultiplier;// Offset=0x1d4 Size=0x4
        char mantleState[0x10];
        char weapState[0x38];
        unsigned int weaponsEquipped[15];// Offset=0x220 Size=0x3c
        char weapEquipedCrap[0x4b];
        unsigned char __align0[1];// Offset=0x2a7 Size=0x1
        char _weapCommonCrap[0x17C];
        float meleeChargeYaw;// Offset=0x424 Size=0x4
        int meleeChargeDist;// Offset=0x428 Size=0x4
        int meleeChargeTime;// Offset=0x42c Size=0x4
        char actionSlotType[0x10];
        char actionSlotCrap[0x10];
        int weaponHudIconOverrides[6];// Offset=0x450 Size=0x18
        int animScriptedType;// Offset=0x468 Size=0x4
        int shellshockIndex;// Offset=0x46c Size=0x4
        int shellshockTime;// Offset=0x470 Size=0x4
        int shellshockDuration;// Offset=0x474 Size=0x4
        float dofNearStart;// Offset=0x478 Size=0x4
        float dofNearEnd;// Offset=0x47c Size=0x4
        float dofFarStart;// Offset=0x480 Size=0x4
        float dofFarEnd;// Offset=0x484 Size=0x4
        float dofNearBlur;// Offset=0x488 Size=0x4
        float dofFarBlur;// Offset=0x48c Size=0x4
        float dofViewmodelStart;// Offset=0x490 Size=0x4
        float dofViewmodelEnd;// Offset=0x494 Size=0x4
        char _hudCrap[0xa800];// Offset=0x498 Size=0xa800
        int recoilScale;// Offset=0xac98 Size=0x4
        int diveDirection;// Offset=0xac9c Size=0x4
        int stunTime;// Offset=0xaca0 Size=0x4
    };

    struct snapshot_s// Size=0x1610
    {
        int snapFlags;// Offset=0x0 Size=0x4
        int serverTime;// Offset=0x4 Size=0x4
        int numEntities;// Offset=0x8 Size=0x4
        unsigned short entityNums[2048];// Offset=0xc Size=0x1000
        int numFxEntities;// Offset=0x100c Size=0x4
        unsigned short fxEntityNums[768];// Offset=0x1010 Size=0x600
    };

    struct cpose_t// Size=0x60
    {
        unsigned short lightingHandle;// Offset=0x0 Size=0x2
        unsigned char eType;// Offset=0x2 Size=0x1
        unsigned char cullIn[2];// Offset=0x3 Size=0x2
        unsigned char __align0[3];// Offset=0x5 Size=0x3
        unsigned int usedInScene[2];// Offset=0x8 Size=0x8
        bool isRagdoll;// Offset=0x10 Size=0x1
        unsigned char __align1[3];// Offset=0x11 Size=0x3
        int ragdollHandle;// Offset=0x14 Size=0x4
        int physObjId;// Offset=0x18 Size=0x4
        float origin[3];// Offset=0x1c Size=0xc
        float angles[3];// Offset=0x28 Size=0xc
        char crap[0x2C];
    };

    struct trajectory_t// Size=0x24
    {
        trType_t trType;// Offset=0x0 Size=0x4
        int trTime;// Offset=0x4 Size=0x4
        int trDuration;// Offset=0x8 Size=0x4
        float trBase[3];// Offset=0xc Size=0xc
        float trDelta[3];// Offset=0x18 Size=0xc
    };

    struct LerpEntityState// Size=0x70
    {
        int eFlags;// Offset=0x0 Size=0x4
        trajectory_t pos;// Offset=0x4 Size=0x24
        trajectory_t apos;// Offset=0x28 Size=0x24
        char entLerpState[0x20];
        int useCount;// Offset=0x6c Size=0x4
    };

    struct entityState_s// Size=0xac
    {
        unsigned char eType;// Offset=0x0 Size=0x1
        unsigned char surfType;// Offset=0x1 Size=0x1
        char _0x0003[4];
        unsigned int eventParm;// Offset=0x8 Size=0x4
        struct LerpEntityState lerp;// Offset=0xc Size=0x70
        char _0x007C[2];
        unsigned short number;// Offset=0x7e Size=0x2
        unsigned short otherEntityNum;// Offset=0x80 Size=0x2
        unsigned short groundEntityNum;// Offset=0x82 Size=0x2
        char _0x0084[2];
        unsigned char __align5[2];// Offset=0x86 Size=0x2
        int time2;// Offset=0x88 Size=0x4
        int solid;// Offset=0x8c Size=0x4
        int eventSequence;// Offset=0x90 Size=0x4
        unsigned char events[4];// Offset=0x94 Size=0x4
        unsigned int eventParms[4];// Offset=0x98 Size=0x10
        char _0x00A8[4];// Offset=0xa8 Size=0x4
    };

    struct centity_s// Size=0x194
    {
        cpose_t pose;// Offset=0x0 Size=0x60
        LerpEntityState prevState;// Offset=0x60 Size=0x70
        entityState_s nextState;// Offset=0xd0 Size=0xac
        int flags;// Offset=0x17c Size=0x4
        unsigned char tracerDrawRateCounter;// Offset=0x180 Size=0x1
        unsigned char prevEType;// Offset=0x181 Size=0x1
        unsigned char __align0[2];// Offset=0x182 Size=0x2
        int previousEventSequence;// Offset=0x184 Size=0x4
        float lightingOrigin[3];// Offset=0x188 Size=0xc
    };

    struct playerEntity_t// Size=0x48
    {
        int bPositionToADS;// Offset=0x0 Size=0x4
        float fOOPositionBlendTime;// Offset=0x4 Size=0x4
        float vPositionBlendOrg[3];// Offset=0x8 Size=0xc
        float vPositionBlendAng[3];// Offset=0x14 Size=0xc
        float vPositionLastAng[3];// Offset=0x20 Size=0xc
        float fLastIdleFactor;// Offset=0x2c Size=0x4
        float baseMoveOrigin[3];// Offset=0x30 Size=0xc
        float baseMoveAngles[3];// Offset=0x3c Size=0xc
    };

    struct RefdefView// Size=0x3c
    {
        float tanHalfFovX;// Offset=0x0 Size=0x4
        float tanHalfFovY;// Offset=0x4 Size=0x4
        Vector3 Origin;// Offset=0x8 Size=0xc
        Vector3 viewAxis[3]; // Offset=0x14 Size=0x24
        float zNear;// Offset=0x38 Size=0x4
    };

    struct GfxDepthOfField// Size=0x20
    {
        float viewModelStart;// Offset=0x0 Size=0x4
        float viewModelEnd;// Offset=0x4 Size=0x4
        float nearStart;// Offset=0x8 Size=0x4
        float nearEnd;// Offset=0xc Size=0x4
        float farStart;// Offset=0x10 Size=0x4
        float farEnd;// Offset=0x14 Size=0x4
        float nearBlur;// Offset=0x18 Size=0x4
        float farBlur;// Offset=0x1c Size=0x4
    };

    struct GfxFilm// Size=0x3c
    {
        bool enabled;// Offset=0x0 Size=0x1
        unsigned char __align0[3];// Offset=0x1 Size=0x3
        float brightness;// Offset=0x4 Size=0x4
        float contrast;// Offset=0x8 Size=0x4
        float desaturation;// Offset=0xc Size=0x4
        float desaturationDark;// Offset=0x10 Size=0x4
        bool invert;// Offset=0x14 Size=0x1
        unsigned char __align1[3];// Offset=0x15 Size=0x3
        float tintDark[3];// Offset=0x18 Size=0xc
        float tintMedium[3];// Offset=0x24 Size=0xc
        float tintLight[3];// Offset=0x30 Size=0xc
    };

    struct GfxGlow// Size=0x14
    {
        bool enabled;// Offset=0x0 Size=0x1
        unsigned char __align0[3];// Offset=0x1 Size=0x3
        float bloomCutoff;// Offset=0x4 Size=0x4
        float bloomDesaturation;// Offset=0x8 Size=0x4
        float bloomIntensity;// Offset=0xc Size=0x4
        float radius;// Offset=0x10 Size=0x4
    };

    struct GfxLightScale// Size=0x8
    {
        float diffuseScale;// Offset=0x0 Size=0x4
        float specularScale;// Offset=0x4 Size=0x4
    };

    struct GfxCompositeFx// Size=0x6c
    {
        GfxFilm film;// Offset=0x0 Size=0x3c
        float distortionScale[3];// Offset=0x3c Size=0xc
        float blurRadius;// Offset=0x48 Size=0x4
        float distortionMagnitude;// Offset=0x4c Size=0x4
        float frameRate;// Offset=0x50 Size=0x4
        int lastUpdate;// Offset=0x54 Size=0x4
        int frame;// Offset=0x58 Size=0x4
        int startMSec;// Offset=0x5c Size=0x4
        int currentTime;// Offset=0x60 Size=0x4
        int duration;// Offset=0x64 Size=0x4
        bool enabled;// Offset=0x68 Size=0x1
        bool scriptEnabled;// Offset=0x69 Size=0x1
    };
	
    struct GfxLight// Size=0x40
    {
        unsigned char type;// Offset=0x0 Size=0x1
        unsigned char canUseShadowMap;// Offset=0x1 Size=0x1
        unsigned char unused[2];// Offset=0x2 Size=0x2
        float color[3];// Offset=0x4 Size=0xc
        float dir[3];// Offset=0x10 Size=0xc
        float origin[3];// Offset=0x1c Size=0xc
        float radius;// Offset=0x28 Size=0x4
        float cosHalfFovOuter;// Offset=0x2c Size=0x4
        float cosHalfFovInner;// Offset=0x30 Size=0x4
        int exponent;// Offset=0x34 Size=0x4
        unsigned int spotShadowIndex;// Offset=0x38 Size=0x4
        int def;// Offset=0x3c Size=0x4
    };

    struct GfxViewport// Size=0x10
    {
        int x;// Offset=0x0 Size=0x4
        int y;// Offset=0x4 Size=0x4
        int width;// Offset=0x8 Size=0x4
        int height;// Offset=0xc Size=0x4
    };
	
    struct refdef_t// Size=0x3f60
    {
        unsigned int x;// Offset=0x0 Size=0x4
        unsigned int y;// Offset=0x4 Size=0x4
        unsigned int width;// Offset=0x8 Size=0x4
        unsigned int height;// Offset=0xc Size=0x4
        RefdefView view;// Offset=0x10 Size=0x3c
        float viewOffset[3];// Offset=0x4c Size=0xc
        int time;// Offset=0x58 Size=0x4
        float blurRadius;// Offset=0x5c Size=0x4
        GfxDepthOfField dof;// Offset=0x60 Size=0x20
        GfxFilm film;// Offset=0x80 Size=0x3c
        GfxGlow glow;// Offset=0xbc Size=0x14
        GfxLightScale charPrimaryLightScale;// Offset=0xd0 Size=0x8
        GfxCompositeFx waterSheetingFx;// Offset=0xd8 Size=0x6c
        GfxLight primaryLights[248];// Offset=0x144 Size=0x3e00
        GfxViewport scissorViewport;// Offset=0x3f44 Size=0x10
        bool useScissorViewport;// Offset=0x3f54 Size=0x1
        bool viewModelHasDistortion;// Offset=0x3f55 Size=0x1
        unsigned char forceSunShadowsGenerate;// Offset=0x3f56 Size=0x1
        bool halfResParticles;// Offset=0x3f57 Size=0x1
        bool playerTeleported;// Offset=0x3f58 Size=0x1
        unsigned char __align0[3];// Offset=0x3f59 Size=0x3
        int localClientNum;// Offset=0x3f5c Size=0x4
    };

    struct viewDamage_t// Size=0x44
    {
        int time;// Offset=0x0 Size=0x4
        int duration;// Offset=0x4 Size=0x4
        float dir[3];// Offset=0x8 Size=0xc
        float yaw;// Offset=0x14 Size=0x4
        float playerYaw;// Offset=0x18 Size=0x4
        float playerDir[3][3];// Offset=0x1c Size=0x24
        bool stun;// Offset=0x40 Size=0x1
    };
	
    struct cg_s// Size=0x2f1b0
    {
        int clientNum;// Offset=0x0 Size=0x4
        int localClientNum;// Offset=0x4 Size=0x4
        CubemapShot cubemapShot;// Offset=0x8 Size=0x4
        int cubemapSize;// Offset=0xc Size=0x4
        int serverCommandSequence;// Offset=0x10 Size=0x4
        int serverLatestCommandSequence;// Offset=0x14 Size=0x4
        int loaded;// Offset=0x18 Size=0x4
        snapshot_s* snap;// Offset=0x1c Size=0x4
        snapshot_s* nextSnap;// Offset=0x20 Size=0x4
        playerState_s* ps;// Offset=0x24 Size=0x4
        playerState_s* nextPs;// Offset=0x28 Size=0x4
        playerState_s activePs[2];// Offset=0x2c Size=0x15948
        int createdNextSnap;// Offset=0x15974 Size=0x4
        float frameInterpolation;// Offset=0x15978 Size=0x4
        int frametime;// Offset=0x1597c Size=0x4
        int time;// Offset=0x15980 Size=0x4
        int oldTime;// Offset=0x15984 Size=0x4
        int physicsTime;// Offset=0x15988 Size=0x4
        playerState_s predictedPlayerState;// Offset=0x1598c Size=0xaca4
        centity_s predictedPlayerEntity;// Offset=0x20630 Size=0x194
        playerEntity_t playerEntity;// Offset=0x207c4 Size=0x48
        int validPPS;// Offset=0x2080c Size=0x4
        int predictedErrorTime;// Offset=0x20810 Size=0x4
        float predictedError[3];// Offset=0x20814 Size=0xc
        float landChange;// Offset=0x20820 Size=0x4
        int landTime;// Offset=0x20824 Size=0x4
        float heightToCeiling;// Offset=0x20828 Size=0x4
        refdef_t refdef;// Offset=0x2082c Size=0x3f60
        float refdefViewAngles[3];// Offset=0x2478c Size=0xc
        float baseGunAngles[3];// Offset=0x24798 Size=0xc
        float aimAssistEyeOrigin[3];// Offset=0x247a4 Size=0xc
        float aimAssistViewOrigin[3];// Offset=0x247b0 Size=0xc
        float aimAssistViewAngles[3];// Offset=0x247bc Size=0xc
        float swayViewAngles[3];// Offset=0x247c8 Size=0xc
        float swayAngles[3];// Offset=0x247d4 Size=0xc
        float swayOffset[3];// Offset=0x247e0 Size=0xc
        float recoilAngles[3];// Offset=0x247ec Size=0xc
        float recoilSpeed[3];// Offset=0x247f8 Size=0xc
        float zoomSensitivity;// Offset=0x24804 Size=0x4
        int vehicleInitView;// Offset=0x24808 Size=0x4
        float prevVehicleInvAxis[3][3];// Offset=0x2480c Size=0x24
        bool vehicleViewLocked;// Offset=0x24830 Size=0x1
        unsigned char __align0[3];// Offset=0x24831 Size=0x3
        float vehicleViewLockedAngles[3];// Offset=0x24834 Size=0xc
        int showScores;// Offset=0x24840 Size=0x4
        int scoreFadeTime;// Offset=0x24844 Size=0x4
        int timeScaleTimeStart;// Offset=0x24848 Size=0x4
        int timeScaleTimeEnd;// Offset=0x2484c Size=0x4
        float timeScaleStart;// Offset=0x24850 Size=0x4
        float timeScaleEnd;// Offset=0x24854 Size=0x4
        int deadquoteStartTime;// Offset=0x24858 Size=0x4
        int cursorHintIcon;// Offset=0x2485c Size=0x4
        int cursorHintEntType;// Offset=0x24860 Size=0x4
        int cursorHintTime;// Offset=0x24864 Size=0x4
        int cursorHintFade;// Offset=0x24868 Size=0x4
        int cursorHintString;// Offset=0x2486c Size=0x4
        int cursorHintDualWield;// Offset=0x24870 Size=0x4
        int lastClipFlashTime;// Offset=0x24874 Size=0x4
        InvalidCmdHintType invalidCmdHintType;// Offset=0x24878 Size=0x4
        int invalidCmdHintWeapon;// Offset=0x2487c Size=0x4
        int invalidCmdHintTime;// Offset=0x24880 Size=0x4
        int lastHealthPulseTime;// Offset=0x24884 Size=0x4
        int lastHealthLerpDelay;// Offset=0x24888 Size=0x4
        int lastHealthClient;// Offset=0x2488c Size=0x4
        float lastHealth;// Offset=0x24890 Size=0x4
        int showHud;// Offset=0x24894 Size=0x4
        float bloodOverlayAlpha;// Offset=0x24898 Size=0x4
        int lastStance;// Offset=0x2489c Size=0x4
        int lastStanceChangeTime;// Offset=0x248a0 Size=0x4
        int lastStanceFlashTime;// Offset=0x248a4 Size=0x4
        int voiceTime;// Offset=0x248a8 Size=0x4
        unsigned int weaponSelect;// Offset=0x248ac Size=0x4
        int weaponSelectTime;// Offset=0x248b0 Size=0x4
        unsigned int weaponLatestPrimaryIdx;// Offset=0x248b4 Size=0x4
        unsigned short primaryWeaponForAlt[200];// Offset=0x248b8 Size=0x190
        unsigned int prevViewmodelWeapon;// Offset=0x24a48 Size=0x4
        int prevDualWielding;// Offset=0x24a4c Size=0x4
        int equippedOffHand;// Offset=0x24a50 Size=0x4
        viewDamage_t viewDamage[12];// Offset=0x24a54 Size=0x330
        int damageTime;// Offset=0x24d84 Size=0x4
        float damageX;// Offset=0x24d88 Size=0x4
        float damageY;// Offset=0x24d8c Size=0x4
        float damageValue;// Offset=0x24d90 Size=0x4
        int weapIdleTime;// Offset=0x24d94 Size=0x4
        int v_dmg_time;// Offset=0x24d98 Size=0x4
        int v_dmg_stun_time;// Offset=0x24d9c Size=0x4
        float v_dmg_pitch;// Offset=0x24da0 Size=0x4
        float v_dmg_roll;// Offset=0x24da4 Size=0x4
        float xyspeed;// Offset=0x24da8 Size=0x4
        float kickAVel[3];// Offset=0x24dac Size=0xc
        float kickAngles[3];// Offset=0x24db8 Size=0xc
        float gunPitch;// Offset=0x24dc4 Size=0x4
        float gunYaw;// Offset=0x24dc8 Size=0x4
        float gunXOfs;// Offset=0x24dcc Size=0x4
        float gunYOfs;// Offset=0x24dd0 Size=0x4
        float gunZOfs;// Offset=0x24dd4 Size=0x4
        float viewModelAxis[4][3];// Offset=0x24dd8 Size=0x30
        bool hideViewModel;// Offset=0x24e08 Size=0x1
        unsigned char __align1[3];// Offset=0x24e09 Size=0x3
        float rumbleScale;// Offset=0x24e0c Size=0x4
        float selectedLocation[2];// Offset=0x24e10 Size=0x8
        float selectedLocationAngle;// Offset=0x24e18 Size=0x4
        float compassNorthYaw;// Offset=0x24e1c Size=0x4
        float compassNorth[2];// Offset=0x24e20 Size=0x8
        Material* compassMapMaterial;// Offset=0x24e28 Size=0x4
        float compassMapUpperLeft[2];// Offset=0x24e2c Size=0x8
        float compassMapWorldSize[2];// Offset=0x24e34 Size=0x8
        float motionTrackerPrevCenter[2];// Offset=0x24e3c Size=0x8
        float motionTrackerProgress;// Offset=0x24e44 Size=0x4
        int compassFadeTime;// Offset=0x24e48 Size=0x4
        int healthFadeTime;// Offset=0x24e4c Size=0x4
        int ammoFadeTime;// Offset=0x24e50 Size=0x4
        int stanceFadeTime;// Offset=0x24e54 Size=0x4
        int sprintFadeTime;// Offset=0x24e58 Size=0x4
        int offhandFadeTime;// Offset=0x24e5c Size=0x4
        int offhandFlashTime;// Offset=0x24e60 Size=0x4
    };


    struct usercmd_s// Size=0x40
    {
        int serverTime;// Offset=0x0 Size=0x4
        int buttons;// Offset=0x4 Size=0x4
        Vector3 Angles;// Offset=0x8 Size=0xc
        unsigned short weapon;// Offset=0x14 Size=0x2
        unsigned short primaryWeaponForAltMode;// Offset=0x16 Size=0x2
        unsigned short offHandIndex;// Offset=0x18 Size=0x2
        int forwardmove;// Offset=0x1a Size=0x1
        int rightmove;// Offset=0x1b Size=0x1
        unsigned char upmove;// Offset=0x1c Size=0x1
        unsigned char downmove;// Offset=0x1d Size=0x1
        int pitchmove;// Offset=0x1e Size=0x1
        int yawmove;// Offset=0x1f Size=0x1
        float gunPitch;// Offset=0x20 Size=0x4
        float gunYaw;// Offset=0x24 Size=0x4
        float gunXOfs;// Offset=0x28 Size=0x4
        float gunYOfs;// Offset=0x2c Size=0x4
        float gunZOfs;// Offset=0x30 Size=0x4
        float meleeChargeYaw;// Offset=0x34 Size=0x4
        unsigned char meleeChargeDist;// Offset=0x38 Size=0x1
        int selectedLoc[2];// Offset=0x39 Size=0x2
        unsigned char selectedLocAngle;// Offset=0x3b Size=0x1
        int remoteControlAngles[2];// Offset=0x3c Size=0x2
    };

    struct clientPersistent_t// Size=0xb0
    {
        clientConnected_t connected;// Offset=0x0 Size=0x4
        usercmd_s cmd;// Offset=0x4 Size=0x40
        usercmd_s oldcmd;// Offset=0x44 Size=0x40
        int maxHealth;// Offset=0x84 Size=0x4
        float moveSpeedScaleMultiplier;// Offset=0x88 Size=0x4
        int motionTrackerEnabled;// Offset=0x8c Size=0x4
        char playerName[32];// Offset=0x90 Size=0x20
    };

    struct gclient_s// Size=0xafd4
    {
        playerState_s ps;// Offset=0x0 Size=0xaca4
        clientPersistent_t pers;// Offset=0xaca4 Size=0xb0
        int flags;// Offset=0xad54 Size=0x4
        int buttons;// Offset=0xad58 Size=0x4
        int oldbuttons;// Offset=0xad5c Size=0x4
        int latched_buttons;// Offset=0xad60 Size=0x4
        int buttonsSinceLastFrame;// Offset=0xad64 Size=0x4
        float fGunPitch;// Offset=0xad68 Size=0x4
        float fGunYaw;// Offset=0xad6c Size=0x4
        float fGunXOfs;// Offset=0xad70 Size=0x4
        float fGunYOfs;// Offset=0xad74 Size=0x4
        float fGunZOfs;// Offset=0xad78 Size=0x4
        int damage_blood;// Offset=0xad7c Size=0x4
        int damage_stun;// Offset=0xad80 Size=0x4
        Vector3 damage_from;// Offset=0xad84 Size=0xc
        int damage_fromWorld;// Offset=0xad90 Size=0x4
        float currentAimSpreadScale;// Offset=0xad94 Size=0x4
    };

    struct sentient_s// Size=0x70
    {
        int ent;// Offset=0x0 Size=0x4
        team_t eTeam;// Offset=0x4 Size=0x4
        int iThreatBias;// Offset=0x8 Size=0x4
        int iThreatBiasGroupIndex;// Offset=0xc Size=0x4
        bool bIgnoreMe;// Offset=0x10 Size=0x1
        bool bIgnoreAll;// Offset=0x11 Size=0x1
        bool originChanged;// Offset=0x12 Size=0x1
        unsigned char __align0[1];// Offset=0x13 Size=0x1
        Vector3 oldOrigin;// Offset=0x14 Size=0xc
        float maxVisibleDist;// Offset=0x20 Size=0x4
        float surprisedByMeDistSq;// Offset=0x24 Size=0x4
        int iEnemyNotifyTime;// Offset=0x28 Size=0x4
        int attackerCount;// Offset=0x2c Size=0x4
        int lastAttacker;// Offset=0x30 Size=0x4
        char _crap[0xC];
        float entityTargetThreat;// Offset=0x40 Size=0x4
        int meleeAttackerSpot[4];// Offset=0x44 Size=0x10
        float attackerAccuracy;// Offset=0x54 Size=0x4
        bool ignoreRandomBulletDamage;// Offset=0x58 Size=0x1
        bool doDamageToAll;// Offset=0x59 Size=0x1
        bool turretInvulnerability;// Offset=0x5a Size=0x1
        bool scriptTargetHasTagEye;// Offset=0x5b Size=0x1
        int pClaimedNode;// Offset=0x5c Size=0x4
        int pPrevClaimedNode;// Offset=0x60 Size=0x4
        int pNearestNode;// Offset=0x64 Size=0x4
        unsigned char bNearestNodeValid;// Offset=0x68 Size=0x1
        unsigned char bNearestNodeBad;// Offset=0x69 Size=0x1
        bool inuse;// Offset=0x6a Size=0x1
        unsigned char __align1[1];// Offset=0x6b Size=0x1
        int banNodeTime;// Offset=0x6c Size=0x4
    };
	
    struct actor_s// Size=0x1408
    {
        int ent;// Offset=0x0 Size=0x4
        sentient_s* sentient;// Offset=0x4 Size=0x4
        AISpecies species;// Offset=0x8 Size=0x4
        int talkToSpecies;// Offset=0xc Size=0x4
        char eState[0x18];
        char eSubState[0x18];
        unsigned int stateLevel;// Offset=0x40 Size=0x4
        int iStateTime;// Offset=0x44 Size=0x4
        int preThinkTime;// Offset=0x48 Size=0x4
        char stateTransitions[0x68];
        unsigned int transitionCount;// Offset=0xb4 Size=0x4
        char eSimulatedState[0x18];
        unsigned int simulatedStateLevel;// Offset=0xd0 Size=0x4
        unsigned short properName;// Offset=0xd4 Size=0x2
        unsigned short weaponName;// Offset=0xd6 Size=0x2
    };
	
    struct gentity_s// Size=0x270
    {
        entityState_s s;// Offset=0x0 Size=0xac
        char _0x00AC[0x5C];
        gclient_s* client;// Offset=0x108 Size=0x4
        actor_s* actor;// Offset=0x10c Size=0x4
        sentient_s* sentient;// Offset=0x110 Size=0x4
        int vehicle;// Offset=0x114 Size=0x4
        int turret;// Offset=0x118 Size=0x4
        int physObjId;// Offset=0x11c Size=0x4
        unsigned char physicsObject;// Offset=0x120 Size=0x1
        unsigned char takedamage;// Offset=0x121 Size=0x1
        unsigned char active;// Offset=0x122 Size=0x1
        unsigned char handler;// Offset=0x123 Size=0x1
        unsigned short classname;// Offset=0x124 Size=0x2
        unsigned short script_classname;// Offset=0x126 Size=0x2
        unsigned short script_linkName;// Offset=0x128 Size=0x2
        unsigned short script_noteworthy;// Offset=0x12a Size=0x2
        unsigned short target;// Offset=0x12c Size=0x2
        unsigned short targetname;// Offset=0x12e Size=0x2
        unsigned int attachIgnoreCollision;// Offset=0x130 Size=0x4
        int spawnflags;// Offset=0x134 Size=0x4
        int flags;// Offset=0x138 Size=0x4
        int clipmask;// Offset=0x13c Size=0x4
        int processedFrame;// Offset=0x140 Size=0x4
        int crap;
        int nextthink;// Offset=0x148 Size=0x4
        int health;// Offset=0x14c Size=0x4
        int maxHealth;// Offset=0x150 Size=0x4
        int nexteq;// Offset=0x154 Size=0x4
        int damage;// Offset=0x158 Size=0x4
    };

    struct level_locals_t// Size=0x3ffc
    {
        gclient_s* clients;// Offset=0x0 Size=0x4
        gentity_s* gentities;// Offset=0x4 Size=0x4
        int num_entities;// Offset=0x8 Size=0x4
        gentity_s* firstFreeEnt;// Offset=0xc Size=0x4
        gentity_s* lastFreeEnt;// Offset=0x10 Size=0x4
        sentient_s* sentients;// Offset=0x14 Size=0x4
        actor_s* actors;// Offset=0x18 Size=0x4
        int vehicles;// Offset=0x1c Size=0x4
        int turrets;// Offset=0x20 Size=0x4
        int initializing;// Offset=0x24 Size=0x4
        int clientIsSpawning;// Offset=0x28 Size=0x4
        int maxclients;// Offset=0x2c Size=0x4
        int framenum;// Offset=0x30 Size=0x4
        int time;// Offset=0x34 Size=0x4
        int previousTime;// Offset=0x38 Size=0x4
        int timeAtLastPause;// Offset=0x3c Size=0x4
        int respawnTime;// Offset=0x40 Size=0x4
        int newSession;// Offset=0x44 Size=0x4
        int actorCorpseCount;// Offset=0x48 Size=0x4
        int actorCount;// Offset=0x4c Size=0x4
    };
	
	cgs_t cgs;
	cg_s cg;
	clientStatic_t cs;
    level_locals_t level;
	int srcPlacement = 0x8266BCA8;
	
	inline void getStructs()
	{
		cgs = *reinterpret_cast<cgs_t*>(0x8244BDA8);
		cs = *reinterpret_cast<clientStatic_t*>(0x825B70A0);
        cg = *reinterpret_cast<cg_s*>(0x8244C2C0);
        level = *reinterpret_cast<level_locals_t*>(0x82EC2598);
	}
}
#endif // TU9SP_STRUCTS_H