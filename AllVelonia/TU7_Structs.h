#ifndef TU7_STRUCTS_H
#define TU7_STRUCTS_H

namespace TU7
{
	struct cgs_t {
		char _0x0000[8];
		int screenX; //0x0008 
		int screenY; //0x000C 
		char _0x0010[24];
		int GameTime; //0x0028 
		BYTE N004984D9; //0x002C 
		BYTE N004BE784; //0x002D 
		BYTE N004C10ED; //0x002E 
		BYTE Local; //0x002F 
		char GameType[4]; //0x0030 
		char _0x0034[28];
		char Host[64]; //0x0050 
		char _0x0090[192];
		int maxClients; //0x0150 
		char _0x0154[4];
		char mapName[64]; //0x0158 
	};

	typedef struct {
		int time;
		int buttons;
		int viewAngles[3];
		short WeaponID;
		char fDir;
		char rDir;
		char padding[0x14];
	} Usercmd_t;

	typedef struct
	{
		char padding00[0xA4];			//0x00
		Vector3 baseAngle;				//0xA4
		char padding02[0x269D0];		//0xAC
		Vector3 viewAngle;				//0x26A80
		char padding03[0x40014];		//0x26A88
		Usercmd_t Usercmd[128];			//0x66AA0
		int CurrentCmdNumber;
		Usercmd_t* getCmd(int id) {
			return &Usercmd[(id & 0x7F)];
		}
		Usercmd_t* getCmd() {
			return getCmd(CurrentCmdNumber);
		}
		Usercmd_t* getLastCmd() {
			return getCmd(CurrentCmdNumber - 1);
		}
	}clientActive;

	struct playerName_t
	{
		char playerName[32]; //0x0000 
		char _0x0020[28]; //0x0020 
		char clanTag[4]; //0x003C 
		char _0x0040[88]; //0x0040 
	}; //diff 0x98

	struct CClient {
		int mValid; //0x0000 
		char _0x0004[4]; //0x0004 
		int clientID;
		char szPlayerName[32]; //0x000C 
		int mTeam; //0x002C 
		char _0x0030[12]; //char _0x0030[48]; //0x0030 
		int Rank;
		int Prestige;
		char _0x0044[8];
		char clantag[4];
		char _0x0050[16]; //0x0044 
		char szBodyModel[32]; //0x0060 
		char _0x0080[32]; //0x0080 
		char szHeadModel[32]; //0x00A0 
		char _0x00C0[32]; //0x00C0 
		char szWeapModel[32]; //0x00E0
		char padding[0x308];			//0x100
		Vector3 viewAngle;				//0x408
		char padding04[0x148];				//0x414
		//char _0x0102[924]; //0x0100 
		//int m_Pose; //0x049C 
		//char _0x4A0[20]; //0x04A0 
		//int m_Shooting; //0x04B4 
		//char _0x04B8[4]; //0x04B8 
		//int m_Zoomed; //0x04BC 
		//char _0x4C0[80]; //0x04C0 
		//int m_WeaponID; //0x0510
		//char _0x0514[72];
	};//Size=0x0570 -- diff = 0x055C

	// b0b50e98 + 53D00 - B0B39E98 + 53D00

	struct RefDef {
		int x; //0x0000 
		int y; //0x0004 
		int width; //0x0008 
		int height; //0x000C 
		//char _0x0010[8];
		//float tanHalfFovX; //0x0018 
		//float tanHalfFovY; //0x001C 
		//float tanHalfFovZ; //0x0020 
		//Vector2 fov; //0x0024
		char _0x0010[16];
		float tanHalfFovX;
		float tanHalfFovY;
		float fov;
		Vector3 viewOrigin; //0x002C 
		char _0x0038[4];
		Vector3 viewAxis[3]; //0x003C 
		char _0x0048[56];
	};//Size=0x0098

	struct cg_t {
		int clientNum; //0x0000 
		char _0x0004[84];
		Vector3 origin; //0x0058 
		char _0x0064[216];//char _0x0064[244];
		int Weapon;
		char _0x0140[92];//char _0x0158[68];
		int Health; //0x019C 
		char _0x01A0[4];
		int MaxHealth; //0x01A4 
		char _0x1A8[331336];
		float SpreadMultiplier; //50FF0
		//char _0x01A8[342872];
		char _0x01A8[11532];
		RefDef refdef; // 53D00
		char _unknown[80];
		Vector3 ViewAngle;
		char _0x53D98[588096];
		CClient ClientInfo[18]; // E3734
	};//Size=0x0440

	//struct playerstate_s {
	//	char _0x0000[2700]; //0x0000 
	//	int SecondaryAmmo; //0x0A8C 
	//	char _0x0A90[208]; //0x0A90 
	//	int weaponClip; //0x0B60 
	//	char _0xB64[11988]; //0x0B64 
	//	char Gamertag[32]; //0x3A38 
	//	char _0x3A58[536]; //0x3A58 
	//};//Size=0x3C6C


	struct xenonuserdata {
		int signInState; //0x0000 
		char name[32]; //0x0004 
		char N0BFD927F[4]; //0x0024 
		__int64 xuid; //0x0028 
		char XuidString[16]; //0x0030
	};//Size=0x0040

	struct playerstate_s {
		int commandTime; //0x0000 
		char _0x0004[4];
		int bobCycle; //0x0008 
		char _0x000C[20];
		Vector3 origin; //0x0020 
		char _0x002C[20];
		int weaponTime; //0x0040 
		char _0x0044[8];
		int N0BA41DD1; //0x004C 
		char _0x0050[32];
		int gravity; //0x0070 
		char _0x0074[4];
		int speed; //0x0078 
		Vector3 delta_angles; //0x007C 
		int groundEntityNum; //0x0088 
		Vector3 vLaderVec; //0x008C 
		int jumpTime; //0x0098 
		float jumpOriginZ; //0x009C 
		char _0x00A0[4];
		int legsAnim; //0x00A4 
		char _0x00A8[8];
		int N0BA41E09; //0x00B0 
		int N0BA41E0A; //0x00B4 
		int damageTimer; //0x00B8 
		int damageDuration; //0x00BC 
		char _0x00C0[8];
		int N0BA41E0F; //0x00C8 
		char _0x00CC[40];
		int weaponShotCount; //0x00F4 
		char _0x00F8[40];
		int viewModelIndex; //0x0120 
		Vector3 viewAngles; //0x0124 
		int viewHeightTarget; //0x0130 
		float viewHeightCurrent; //0x0134 
		char _0x0138[60];
		int N0BA41E59; //0x0174 
		char _0x0178[28];
		int ammoClip; //0x0194 
	};

	//struct cg_t {
	//	int clientNum;
	//	char _0x0004[0x18];
	//	int NewServerTime;
	//	char _0x0020[0xC];
	//	int Ping;
	//	int ServerTime;
	//	int OldServerTime;
	//	char _0x0038[0x20];
	//	Vector3 origin;
	//	char padding02[0xD8];
	//	int WeaponID;
	//	char padding03[0x5C];
	//	int Health;
	//	char padding04[0x4FEB4];
	//	playerstate_s playerState;
	//	char padding05[0x120];
	//	Vector3 ViewAngle;
	//	char padding06[0x3B7C];
	//	RefDef refdef;
	//	char padding07[0x8F9D4];
	//	CClient ClientInfo[18];
	//	char padding08[0x37B0];
	//	float SpreadMultiplier;
	//};

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

	typedef struct {
		char _0x0000[2]; //0x0000 
		BYTE valid; //0x0002 
		char _0x003[37]; //0x0003 
		Vector3 origin; //0x0028 
		Vector3 viewAngle; //0x0034 
		char _0x0040[148]; //0x0040 
		int Flags; //0x00D4 
		char _0x00D8[8]; //0x00D8 
		Vector3 oldOrigin; //0x00E0 
		char _0x0EC[24]; //0x00EC 
		Vector3 ViewAngles1; //0x0104 
		char _0x0110[76]; //0x0110 
		int clientId; //0x015C 
		int Type; //0x0160 
		int Pose; //0x0164 
		char _0x0168[12]; //0x0168 
		Vector3 NewOrigin; //0x0174 
		char _0x0180[24]; //0x0180 
		Vector3 ViewAngles2; //0x0198 
		char _0x1A4[160]; //0x01A4 
		int Weapon; //0x0244 
		char _0x248[100]; //0x0248 
		BYTE State; //0x02AC 
		//char _0x0110[84]; //0x0110 
		//int ClientId; //0x0164 
		//int Type; //0x0168 
		//char _0x016C[8]; //0x016C 
		//Vector3 NewOrigin; //0x0174 
		//char _0x0180[24]; //0x0180 
		//Vector3 ViewAngles2; //0x0198 
		//char _0x1A4[160]; //0x01A4 
		//int Weapon; //0x0244 
		//char N00970092[100]; //0x0248 
		//BYTE State; //0x02AC 
		/*char _0x0000[0x2];
		char alive;
		char _0x003[37];
		Vector3 origin;
		char _0x0034[304];
		int stance;
		char _0x0168[232];
		int weapon;
		char _0x0254[0x5C];*/
	}Centity_t, * pCentity_t;//Size=0x02B0

	struct CSnapshot {
		char _000[8]; //0x0000
		int Ping; //0x0008  
	};

	struct gEntity_t {
		char _0x0000[24];
		float Pos1; //0x0018 
		float Pos2; //0x001C 
		float Pos3; //0x0020 
		char _0x0024[24];
		float Angle1; //0x003C 
		float Angle2; //0x0040 
		char _0x0044[92];
		int Jump; //0x00A0 
	};//Size=0x00A4

	struct CTrace {
		char _000[16];
		float m_Fraction;
		char _001[110];
		int m_SurfaceFlags;
	};

	//struct CompassStyle {
	//	float            x1, y1;
	//	float            y2, x2;
	//};

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
		char horzAlign; /*personally dont utilize this*/
		char vertAlign; /*personally dont utilize this*/
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
		char _0x0000[28]; //0x0000 
		int screenWidth; //0x001C 
		int screenHeight; //0x0020 
		char _0x0024[4]; //0x0024 
		float fps; //0x0028 
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

	typedef enum {
		CA_UNINITIALIZED,
		CA_DISCONNECTED,
		CA_AUTHORIZING,
		CA_CONNECTING,
		CA_CHALLENGING,
		CA_CONNECTED,
		CA_LOADING,
		CA_PRIMED,
		CA_ACTIVE,
		CA_CINEMATIC
	} connstate_t;

	typedef struct {
		char _0x0000[8]; // we dont need connection state
		char servername[256];
	} clientStatic_t;

	struct __declspec(align(8)) MaterialInfo
	{
		char* name;
	};

	struct Material {
		MaterialInfo info;
	};

	struct RawFile
	{
		const char* name;
		int len;
		const char* buffer;
	};

	enum aimtags
	{
		HITLOC_NONE = 0,
		HITLOC_HELMET = 1,
		HITLOC_HEAD = 2,
		HITLOC_NECK = 3,
		HITLOC_TORSO_UPR = 4,
		HITLOC_TORSO_LWR = 5,
		HITLOC_R_ARM_UPR = 6,
		HITLOC_L_ARM_UPR = 7,
		HITLOC_R_ARM_LWR = 8,
		HITLOC_L_ARM_LWR = 9,
		HITLOC_R_HAND = 0xA,
		HITLOC_L_HAND = 0xB,
		HITLOC_R_LEG_UPR = 0xC,
		HITLOC_L_LEG_UPR = 0xD,
		HITLOC_R_LEG_LWR = 0xE,
		HITLOC_L_LEG_LWR = 0xF,
		HITLOC_R_FOOT = 0x10,
		HITLOC_L_FOOT = 0x11,
		HITLOC_GUN = 0x12,
		HITLOC_NUM = 0x13
	};

	struct level_locals {
		playerstate_s* ps;
		gEntity_t* gentities;
		char _0x0008[4];
		int numEntities;
		char _0x0010[548];
		int maxClients; //0x0234 
		int framenum; //0x0238 
		int time; //0x023C 
		int previousTime; //0x0240 
		int frametime; //0x0244 
		int startTime; //0x0248 
		int teamScores[4];
		int lastTeammateHealthTime; //0x025C 
		int bUpdateScoresForIntermission; //0x0260 
		char _0x0264[8];
		int numConnectedClients; //0x026C
	};//Size=0x0270

	struct BulletFireParams {
		int weaponEntIndex;
		int ignoreEntIndex;
		float damageMultiplier;
		int methodOfDeath;
		Vector3 origStart;
		Vector3 start;
		Vector3 end;
		Vector3 dir;
	};

	struct ipInfo {
		byte ip1;
		byte ip2;
		byte ip3;
		byte ip4;
	};

	struct partymember
	{
		char _0x0000[8];
		char Gamertag[32]; //0x0008 
		char Clantag[4]; //0x0028 
		char _0x002C[40];
		ipInfo InternalIP; //0x0054 
		ipInfo ExternalIP; //0x0058 
		char _0x005C[108];
	};

	struct partyData
	{
		int session; //0x0000 
		char _0x0004[5300];
		partymember partyMembers[18];
	};

	DWORD WAW_Cl_ReadyToSendPacket = 0x821B0DF8;
	DWORD WAW_Cl_DrawText = 0x821BF5B0;
	DWORD WAW_clientActive_t = 0x826E8BD8;
	DWORD WAW_centity_t = 0x82510478;
	DWORD WAW_cg_t = 0x8268CD98;
	DWORD WAW_cgs_t = 0x8268CD78;
	DWORD WAW_AddCmdDrawText_t = 0x82401C30;
	DWORD WAW_AddCmdDrawStretchPic_t = 0x82401410;
	DWORD WAW_DrawRotatedPicPhysical_t = 0x8215CEC0;
	DWORD WAW_DrawRotated_R3 = 0x8274F580;
	DWORD WAW_DvarGetBool = 0x822BE0E8;
	DWORD WAW_KeyIsDown = 0x821B2908;
	DWORD WAW_GetPos = 0x82123C08;
	DWORD WAW_j_head = 0x82DD4746;
	DWORD WAW_j_neck = 0x82DD4748;
	DWORD WAW_NoRecoil = 0x821A0BFC;
	DWORD WAW_NoSpread1 = 0x8215C7E4;
	DWORD WAW_NoSpread2 = 0x821A00C0;
	DWORD WAW_WeaponSway = 0x8214789C;
	DWORD WAW_ZommingSway = 0x8214804C;
	DWORD WAW_Radar = 0x821548A4;
	DWORD level_locals_t = 0x82D6A440;
	DWORD playerState_s = 0x82D0FA18;
	DWORD gEntity_s = 0x82BAD1B0;
	DWORD cClient = 0xB0C345CC;
	DWORD cgEntities = 0x8268FC30;
	DWORD weaponDef = 0x8268C47C;
	DWORD GetUserCMD = 0x821A3F20;
	DWORD getCurrCMDNum = 0x821A4108;
	DWORD clientStatic = 0x826E3478;
	DWORD _xenonuserdata = 0x852336B0;
	DWORD _partymember = 0x82736D68;
	DWORD _partyData = 0x827358B0;
	cgs_t* cgs;
	cg_t* cg;
	UIContext_s* uiContext;
	playerstate_s* player_s;
	pCentity_t Centity_s;
	gEntity_t* gentity;
	CClient* Client_s;
	clientStatic_t* staticClient;
	clientActive* activeClient;
	xenonuserdata* xenonUserData;
	level_locals* _level_locals;
	clientActive* ca;
	CSnapshot snapshot;
	partyData partydata;

	CClient* getClientbyIDx(int id)
	{
		return reinterpret_cast<CClient*>(0xB0C345CC + (static_cast<int>(0x55C) * id));
	}

	clientActive* getCA()
	{
		auto ca_ptr = *reinterpret_cast<DWORD*>(0x826E8BD8);
		return reinterpret_cast<clientActive*>(ca_ptr);
	}

	CSnapshot getSnapShot() {
		return *reinterpret_cast<CSnapshot*>(reinterpret_cast<int>(getCA()) + 0x18);
	}

	partymember getPartyMember(int i)
	{
		return *reinterpret_cast<partymember*>(*reinterpret_cast<int*>(_partymember) + (0xC4 * i));
	}
	
	bool done = false;

	inline void getStructs() {
		cgs = *reinterpret_cast<cgs_t**>(WAW_cgs_t);
		gentity = *reinterpret_cast<gEntity_t**>(gEntity_s);
		uiContext = reinterpret_cast<UIContext_s*>(0x84FAA578);
		Client_s = reinterpret_cast<CClient*>(cClient);
		cg = *reinterpret_cast<cg_t**>(WAW_cg_t);
		staticClient = reinterpret_cast<clientStatic_t*>(clientStatic);
		player_s = reinterpret_cast<playerstate_s*>(playerState_s);
		activeClient = *reinterpret_cast<clientActive**>(WAW_clientActive_t);
		xenonUserData = reinterpret_cast<xenonuserdata*>(_xenonuserdata);
		_level_locals = reinterpret_cast<level_locals*>(level_locals_t);
		ca = static_cast<clientActive*>(getCA());
		Centity_s = *reinterpret_cast<pCentity_t*>(0x8268FC30);
		partydata = *reinterpret_cast<partyData*>(_partyData);
		snapshot = getSnapShot();
		
		if(!done)
		{
			done = !done;
			printf("> %d\n", cg->clientNum);
		}
		
	}
}
#endif // TU7_STRUCTS_H
