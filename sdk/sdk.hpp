#pragma once

#include "sdk/math/base.hpp"
#include "shared/imgui/imgui.hpp"
//
// enums
//

enum SendPropType
{
	DPT_Int = 0,
	DPT_Float,
	DPT_Vector,
	DPT_VectorXY,
	DPT_String,
	DPT_Array,
	DPT_DataTable,
	DPT_Int64,
	DPT_NUMSendPropTypes,
};

enum ClientFrameStage_t
{
	FRAME_UNDEFINED = -1,
	FRAME_START,
	FRAME_NET_UPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	FRAME_NET_UPDATE_END,
	FRAME_RENDER_START,
	FRAME_RENDER_END
};

enum TraceType_t
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,
	TRACE_ENTITIES_ONLY,
	TRACE_EVERYTHING_FILTER_PROPS,
};

enum RenderViewInfo_t
{
	RENDERVIEW_UNSPECIFIED = 0,
	RENDERVIEW_DRAWVIEWMODEL = (1 << 0),
	RENDERVIEW_DRAWHUD = (1 << 1),
	RENDERVIEW_SUPPRESSMONITORRENDERING = (1 << 2),
};

enum ECstrike15UserMessages
{
	CS_UM_VGUIMenu = 1,
	CS_UM_Geiger = 2,
	CS_UM_Train = 3,
	CS_UM_HudText = 4,
	CS_UM_SayText = 5,
	CS_UM_SayText2 = 6,
	CS_UM_TextMsg = 7,
	CS_UM_HudMsg = 8,
	CS_UM_ResetHud = 9,
	CS_UM_GameTitle = 10,
	CS_UM_Shake = 12,
	CS_UM_Fade = 13,
	CS_UM_Rumble = 14,
	CS_UM_CloseCaption = 15,
	CS_UM_CloseCaptionDirect = 16,
	CS_UM_SendAudio = 17,
	CS_UM_RawAudio = 18,
	CS_UM_VoiceMask = 19,
	CS_UM_RequestState = 20,
	CS_UM_Damage = 21,
	CS_UM_RadioText = 22,
	CS_UM_HintText = 23,
	CS_UM_KeyHintText = 24,
	CS_UM_ProcessSpottedEntityUpdate = 25,
	CS_UM_ReloadEffect = 26,
	CS_UM_AdjustMoney = 27,
	CS_UM_UpdateTeamMoney = 28,
	CS_UM_StopSpectatorMode = 29,
	CS_UM_KillCam = 30,
	CS_UM_DesiredTimescale = 31,
	CS_UM_CurrentTimescale = 32,
	CS_UM_AchievementEvent = 33,
	CS_UM_MatchEndConditions = 34,
	CS_UM_DisconnectToLobby = 35,
	CS_UM_PlayerStatsUpdate = 36,
	CS_UM_DisplayInventory = 37,
	CS_UM_WarmupHasEnded = 38,
	CS_UM_ClientInfo = 39,
	CS_UM_XRankGet = 40,
	CS_UM_XRankUpd = 41,
	CS_UM_CallVoteFailed = 45,
	CS_UM_VoteStart = 46,
	CS_UM_VotePass = 47,
	CS_UM_VoteFailed = 48,
	CS_UM_VoteSetup = 49,
	CS_UM_ServerRankRevealAll = 50,
	CS_UM_SendLastKillerDamageToClient = 51,
	CS_UM_ServerRankUpdate = 52,
	CS_UM_ItemPickup = 53,
	CS_UM_ShowMenu = 54,
	CS_UM_BarTime = 55,
	CS_UM_AmmoDenied = 56,
	CS_UM_MarkAchievement = 57,
	CS_UM_MatchStatsUpdate = 58,
	CS_UM_ItemDrop = 59,
	CS_UM_GlowPropTurnOff = 60,
	CS_UM_SendPlayerItemDrops = 61,
	CS_UM_RoundBackupFilenames = 62,
	CS_UM_SendPlayerItemFound = 63,
	CS_UM_ReportHit = 64,
	CS_UM_XpUpdate = 65,
	CS_UM_QuestProgress = 66,
	CS_UM_ScoreLeaderboardData = 67,
	CS_UM_PlayerDecalDigitalSignature = 68
};

enum CSWeaponType
{
	WEAPONTYPE_UNKNOWN = -1,
	WEAPONTYPE_KNIFE,
	WEAPONTYPE_PISTOL,
	WEAPONTYPE_SUBMACHINEGUN,
	WEAPONTYPE_RIFLE,
	WEAPONTYPE_SHOTGUN,
	WEAPONTYPE_SNIPER,
	WEAPONTYPE_MACHINEGUN,
	WEAPONTYPE_C4,
	WEAPONTYPE_PLACEHOLDER,
	WEAPONTYPE_GRENADE,
	WEAPONTYPE_HEALTHSHOT,
	WEAPONTYPE_FISTS,
	WEAPONTYPE_BREACHCHARGE,
	WEAPONTYPE_BUMPMINE,
	WEAPONTYPE_TABLET,
	WEAPONTYPE_MELEE
};

enum ItemDefinitionIndex
{
	WEAPON_INVALID = -1,
	WEAPON_DEAGLE = 1,
	WEAPON_ELITE = 2,
	WEAPON_FIVESEVEN = 3,
	WEAPON_GLOCK = 4,
	WEAPON_AK47 = 7,
	WEAPON_AUG = 8,
	WEAPON_AWP = 9,
	WEAPON_FAMAS = 10,
	WEAPON_G3SG1 = 11,
	WEAPON_GALILAR = 13,
	WEAPON_M249 = 14,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10 = 17,
	WEAPON_P90 = 19,
	WEAPON_ZONE_REPULSOR = 20,
	WEAPON_MP5SD = 23,
	WEAPON_UMP45 = 24,
	WEAPON_XM1014 = 25,
	WEAPON_BIZON = 26,
	WEAPON_MAG7 = 27,
	WEAPON_NEGEV = 28,
	WEAPON_SAWEDOFF = 29,
	WEAPON_TEC9 = 30,
	WEAPON_TASER = 31,
	WEAPON_HKP2000 = 32,
	WEAPON_MP7 = 33,
	WEAPON_MP9 = 34,
	WEAPON_NOVA = 35,
	WEAPON_P250 = 36,
	WEAPON_SHIELD = 37,
	WEAPON_SCAR20 = 38,
	WEAPON_SG556 = 39,
	WEAPON_SSG08 = 40,
	WEAPON_KNIFE_GG = 41,
	WEAPON_KNIFE = 42,
	WEAPON_FLASHBANG = 43,
	WEAPON_HEGRENADE = 44,
	WEAPON_SMOKEGRENADE = 45,
	WEAPON_MOLOTOV = 46,
	WEAPON_DECOY = 47,
	WEAPON_INCGRENADE = 48,
	WEAPON_C4 = 49,
	WEAPON_HEALTHSHOT = 57,
	WEAPON_KNIFE_T = 59,
	WEAPON_M4A1_SILENCER = 60,
	WEAPON_USP_SILENCER = 61,
	WEAPON_CZ75A = 63,
	WEAPON_REVOLVER = 64,
	WEAPON_TAGRENADE = 68,
	WEAPON_FISTS = 69,
	WEAPON_BREACHCHARGE = 70,
	WEAPON_TABLET = 72,
	WEAPON_MELEE = 74,
	WEAPON_AXE = 75,
	WEAPON_HAMMER = 76,
	WEAPON_SPANNER = 78,
	WEAPON_KNIFE_GHOST = 80,
	WEAPON_FIREBOMB = 81,
	WEAPON_DIVERSION = 82,
	WEAPON_FRAG_GRENADE = 83,
	WEAPON_SNOWBALL = 84,
	WEAPON_BUMPMINE = 85,
	WEAPON_KNIFE_BAYONET = 500,
	WEAPON_KNIFE_CSS = 503,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT = 506,
	WEAPON_KNIFE_KARAMBIT = 507,
	WEAPON_KNIFE_M9_BAYONET = 508,
	WEAPON_KNIFE_TACTICAL = 509,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
	WEAPON_KNIFE_BUTTERFLY = 515,
	WEAPON_KNIFE_PUSH = 516,
	WEAPON_KNIFE_CORD = 517,
	WEAPON_KNIFE_CANIS = 518,
	WEAPON_KNIFE_URSUS = 519,
	WEAPON_KNIFE_GYPSY_JACKKNIFE = 520,
	WEAPON_KNIFE_OUTDOOR = 521,
	WEAPON_KNIFE_STILETTO = 522,
	WEAPON_KNIFE_WIDOWMAKER = 523,
	WEAPON_KNIFE_SKELETON = 525,
	GLOVE_STUDDED_BLOODHOUND = 5027,
	GLOVE_T = 5028,
	GLOVE_CT = 5029,
	GLOVE_SPORTY = 5030,
	GLOVE_SLICK = 5031,
	GLOVE_LEATHER_HANDWRAPS = 5032,
	GLOVE_MOTORCYCLE = 5033,
	GLOVE_SPECIALIST = 5034,
	GLOVE_HYDRA = 5035
};

enum ClassID
{
	CAI_BaseNPC = 0,
	CAK47,
	CBaseAnimating,
	CBaseAnimatingOverlay,
	CBaseAttributableItem,
	CBaseButton,
	CBaseCombatCharacter,
	CBaseCombatWeapon,
	CBaseCSGrenade,
	CBaseCSGrenadeProjectile,
	CBaseDoor,
	CBaseEntity,
	CBaseFlex,
	CBaseGrenade,
	CBaseParticleEntity,
	CBasePlayer,
	CBasePropDoor,
	CBaseTeamObjectiveResource,
	CBaseTempEntity,
	CBaseToggle,
	CBaseTrigger,
	CBaseViewModel,
	CBaseVPhysicsTrigger,
	CBaseWeaponWorldModel,
	CBeam,
	CBeamSpotlight,
	CBoneFollower,
	CBRC4Target,
	CBreachCharge,
	CBreachChargeProjectile,
	CBreakableProp,
	CBreakableSurface,
	CBumpMine,
	CBumpMineProjectile,
	CC4,
	CCascadeLight,
	CChicken,
	CColorCorrection,
	CColorCorrectionVolume,
	CCSGameRulesProxy,
	CCSPlayer,
	CCSPlayerResource,
	CCSRagdoll,
	CCSTeam,
	CDangerZone,
	CDangerZoneController,
	CDEagle,
	CDecoyGrenade,
	CDecoyProjectile,
	CDrone,
	CDronegun,
	CDynamicLight,
	CDynamicProp,
	CEconEntity,
	CEconWearable,
	CEmbers,
	CEntityDissolve,
	CEntityFlame,
	CEntityFreezing,
	CEntityParticleTrail,
	CEnvAmbientLight,
	CEnvDetailController,
	CEnvDOFController,
	CEnvGasCanister,
	CEnvParticleScript,
	CEnvProjectedTexture,
	CEnvQuadraticBeam,
	CEnvScreenEffect,
	CEnvScreenOverlay,
	CEnvTonemapController,
	CEnvWind,
	CFEPlayerDecal,
	CFireCrackerBlast,
	CFireSmoke,
	CFireTrail,
	CFish,
	CFists,
	CFlashbang,
	CFogController,
	CFootstepControl,
	CFunc_Dust,
	CFunc_LOD,
	CFuncAreaPortalWindow,
	CFuncBrush,
	CFuncConveyor,
	CFuncLadder,
	CFuncMonitor,
	CFuncMoveLinear,
	CFuncOccluder,
	CFuncReflectiveGlass,
	CFuncRotating,
	CFuncSmokeVolume,
	CFuncTrackTrain,
	CGameRulesProxy,
	CGrassBurn,
	CHandleTest,
	CHEGrenade,
	CHostage,
	CHostageCarriableProp,
	CIncendiaryGrenade,
	CInferno,
	CInfoLadderDismount,
	CInfoMapRegion,
	CInfoOverlayAccessor,
	CItem_Healthshot,
	CItemCash,
	CItemDogtags,
	CKnife,
	CKnifeGG,
	CLightGlow,
	CMaterialModifyControl,
	CMelee,
	CMolotovGrenade,
	CMolotovProjectile,
	CMovieDisplay,
	CParadropChopper,
	CParticleFire,
	CParticlePerformanceMonitor,
	CParticleSystem,
	CPhysBox,
	CPhysBoxMultiplayer,
	CPhysicsProp,
	CPhysicsPropMultiplayer,
	CPhysMagnet,
	CPhysPropAmmoBox,
	CPhysPropLootCrate,
	CPhysPropRadarJammer,
	CPhysPropWeaponUpgrade,
	CPlantedC4,
	CPlasma,
	CPlayerPing,
	CPlayerResource,
	CPointCamera,
	CPointCommentaryNode,
	CPointWorldText,
	CPoseController,
	CPostProcessController,
	CPrecipitation,
	CPrecipitationBlocker,
	CPredictedViewModel,
	CProp_Hallucination,
	CPropCounter,
	CPropDoorRotating,
	CPropJeep,
	CPropVehicleDriveable,
	CRagdollManager,
	CRagdollProp,
	CRagdollPropAttached,
	CRopeKeyframe,
	CSCAR17,
	CSceneEntity,
	CSensorGrenade,
	CSensorGrenadeProjectile,
	CShadowControl,
	CSlideshowDisplay,
	CSmokeGrenade,
	CSmokeGrenadeProjectile,
	CSmokeStack,
	CSnowball,
	CSnowballPile,
	CSnowballProjectile,
	CSpatialEntity,
	CSpotlightEnd,
	CSprite,
	CSpriteOriented,
	CSpriteTrail,
	CStatueProp,
	CSteamJet,
	CSun,
	CSunlightShadowControl,
	CSurvivalSpawnChopper,
	CTablet,
	CTeam,
	CTeamplayRoundBasedRulesProxy,
	CTEArmorRicochet,
	CTEBaseBeam,
	CTEBeamEntPoint,
	CTEBeamEnts,
	CTEBeamFollow,
	CTEBeamLaser,
	CTEBeamPoints,
	CTEBeamRing,
	CTEBeamRingPoint,
	CTEBeamSpline,
	CTEBloodSprite,
	CTEBloodStream,
	CTEBreakModel,
	CTEBSPDecal,
	CTEBubbles,
	CTEBubbleTrail,
	CTEClientProjectile,
	CTEDecal,
	CTEDust,
	CTEDynamicLight,
	CTEEffectDispatch,
	CTEEnergySplash,
	CTEExplosion,
	CTEFireBullets,
	CTEFizz,
	CTEFootprintDecal,
	CTEFoundryHelpers,
	CTEGaussExplosion,
	CTEGlowSprite,
	CTEImpact,
	CTEKillPlayerAttachments,
	CTELargeFunnel,
	CTEMetalSparks,
	CTEMuzzleFlash,
	CTEParticleSystem,
	CTEPhysicsProp,
	CTEPlantBomb,
	CTEPlayerAnimEvent,
	CTEPlayerDecal,
	CTEProjectedDecal,
	CTERadioIcon,
	CTEShatterSurface,
	CTEShowLine,
	CTesla,
	CTESmoke,
	CTESparks,
	CTESprite,
	CTESpriteSpray,
	CTest_ProxyToggle_Networkable,
	CTestTraceline,
	CTEWorldDecal,
	CTriggerPlayerMovement,
	CTriggerSoundOperator,
	CVGuiScreen,
	CVoteController,
	CWaterBullet,
	CWaterLODControl,
	CWeaponAug,
	CWeaponAWP,
	CWeaponBaseItem,
	CWeaponBizon,
	CWeaponCSBase,
	CWeaponCSBaseGun,
	CWeaponCycler,
	CWeaponElite,
	CWeaponFamas,
	CWeaponFiveSeven,
	CWeaponG3SG1,
	CWeaponGalil,
	CWeaponGalilAR,
	CWeaponGlock,
	CWeaponHKP2000,
	CWeaponM249,
	CWeaponM3,
	CWeaponM4A1,
	CWeaponMAC10,
	CWeaponMag7,
	CWeaponMP5Navy,
	CWeaponMP7,
	CWeaponMP9,
	CWeaponNegev,
	CWeaponNOVA,
	CWeaponP228,
	CWeaponP250,
	CWeaponP90,
	CWeaponSawedoff,
	CWeaponSCAR20,
	CWeaponScout,
	CWeaponSG550,
	CWeaponSG552,
	CWeaponSG556,
	CWeaponShield,
	CWeaponSSG08,
	CWeaponTaser,
	CWeaponTec9,
	CWeaponTMP,
	CWeaponUMP45,
	CWeaponUSP,
	CWeaponXM1014,
	CWeaponZoneRepulsor,
	CWorld,
	CWorldVguiText,
	DustTrail,
	MovieExplosion,
	ParticleSmokeGrenade,
	RocketTrail,
	SmokeTrail,
	SporeExplosion,
	SporeTrail,
};

enum EntityFlags
{
	FL_ONGROUND = (1 << 0),
	FL_DUCKING = (1 << 1),
	FL_ANIMDUCKING = (1 << 2),
	FL_WATERJUMP = (1 << 3),
	FL_ONTRAIN = (1 << 4),
	FL_INRAIN = (1 << 5),
	FL_FROZEN = (1 << 6),
	FL_ATCONTROLS = (1 << 7),
	FL_CLIENT = (1 << 8),
	FL_FAKECLIENT = (1 << 9),
	FL_INWATER = (1 << 10),
	FL_FLY = (1 << 11),
	FL_SWIM = (1 << 12),
	FL_CONVEYOR = (1 << 13),
	FL_NPC = (1 << 14),
	FL_GODMODE = (1 << 15),
	FL_NOTARGET = (1 << 16),
	FL_AIMTARGET = (1 << 17),
	FL_PARTIALGROUND = (1 << 18),
	FL_STATICPROP = (1 << 19),
	FL_GRAPHED = (1 << 20),
	FL_GRENADE = (1 << 21),
	FL_STEPMOVEMENT = (1 << 22),
	FL_DONTTOUCH = (1 << 23),
	FL_BASEVELOCITY = (1 << 24),
	FL_WORLDBRUSH = (1 << 25),
	FL_OBJECT = (1 << 26),
	FL_KILLME = (1 << 27),
	FL_ONFIRE = (1 << 28),
	FL_DISSOLVING = (1 << 29),
	FL_TRANSRAGDOLL = (1 << 30),
	FL_UNBLOCKABLE_BY_PLAYER = (1 << 31)
};

enum LifeState : unsigned char
{
	LIFE_ALIVE = 0,// alive
	LIFE_DYING = 1, // playing death animation or still falling off of a ledge waiting to hit ground
	LIFE_DEAD = 2, // dead. lying still.
	MAX_LIFESTATE
};

enum WeaponSound_t
{
	EMPTY,
	SINGLE,
	SINGLE_NPC,
	WPN_DOUBLE, // Can't be "DOUBLE" because windows.h uses it.
	DOUBLE_NPC,
	BURST,
	RELOAD,
	RELOAD_NPC,
	MELEE_MISS,
	MELEE_HIT,
	MELEE_HIT_WORLD,
	SPECIAL1,
	SPECIAL2,
	SPECIAL3,
	TAUNT,
	FAST_RELOAD,
	// Add new shoot sound types here
	REVERSE_THE_NEW_SOUND,
	NUM_SHOOT_SOUND_TYPES,
	MAX_WEAPONSOUND
};

enum MoveType_t
{
	MOVETYPE_NONE = 0,
	MOVETYPE_ISOMETRIC,
	MOVETYPE_WALK,
	MOVETYPE_STEP,
	MOVETYPE_FLY,
	MOVETYPE_FLYGRAVITY,
	MOVETYPE_VPHYSICS,
	MOVETYPE_PUSH,
	MOVETYPE_NOCLIP,
	MOVETYPE_LADDER,
	MOVETYPE_OBSERVER,
	MOVETYPE_CUSTOM,
	MOVETYPE_LAST = MOVETYPE_CUSTOM,
	MOVETYPE_MAX_BITS = 4,
	MAX_MOVETYPE
};

enum MaterialType_t
{
	CHAR_TEX_ANTLION = 'A',
	CHAR_TEX_BLOODYFLESH = 'B',
	CHAR_TEX_CONCRETE = 'C',
	CHAR_TEX_DIRT = 'D',
	CHAR_TEX_EGGSHELL = 'E',
	CHAR_TEX_FLESH = 'F',
	CHAR_TEX_GRATE = 'G',
	CHAR_TEX_ALIENFLESH = 'H',
	CHAR_TEX_CLIP = 'I',
	CHAR_TEX_PLASTIC = 'L',
	CHAR_TEX_METAL = 'M',
	CHAR_TEX_SAND = 'N',
	CHAR_TEX_FOLIAGE = 'O',
	CHAR_TEX_COMPUTER = 'P',
	CHAR_TEX_SLOSH = 'S',
	CHAR_TEX_TILE = 'T',
	CHAR_TEX_VENT = 'V',
	CHAR_TEX_WOOD = 'W',
	CHAR_TEX_GLASS = 'Y',
	CHAR_TEX_WARPSHIELD = 'Z'
};

enum OverrideType_t
{
	OVERRIDE_NORMAL = 0,
	OVERRIDE_BUILD_SHADOWS,
	OVERRIDE_DEPTH_WRITE,
};

enum MaterialVarFlags_t
{
	MATERIAL_VAR_DEBUG = (1 << 0),
	MATERIAL_VAR_NO_DEBUG_OVERRIDE = (1 << 1),
	MATERIAL_VAR_NO_DRAW = (1 << 2),
	MATERIAL_VAR_USE_IN_FILLRATE_MODE = (1 << 3),
	MATERIAL_VAR_VERTEXCOLOR = (1 << 4),
	MATERIAL_VAR_VERTEXALPHA = (1 << 5),
	MATERIAL_VAR_SELFILLUM = (1 << 6),
	MATERIAL_VAR_ADDITIVE = (1 << 7),
	MATERIAL_VAR_ALPHATEST = (1 << 8),
	MATERIAL_VAR_ZNEARER = (1 << 10),
	MATERIAL_VAR_MODEL = (1 << 11),
	MATERIAL_VAR_FLAT = (1 << 12),
	MATERIAL_VAR_NOCULL = (1 << 13),
	MATERIAL_VAR_NOFOG = (1 << 14),
	MATERIAL_VAR_IGNOREZ = (1 << 15),
	MATERIAL_VAR_DECAL = (1 << 16),
	MATERIAL_VAR_ENVMAPSPHERE = (1 << 17),
	MATERIAL_VAR_ENVMAPCAMERASPACE = (1 << 19),
	MATERIAL_VAR_BASEALPHAENVMAPMASK = (1 << 20),
	MATERIAL_VAR_TRANSLUCENT = (1 << 21),
	MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = (1 << 22),
	MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING = (1 << 23),
	MATERIAL_VAR_OPAQUETEXTURE = (1 << 24),
	MATERIAL_VAR_ENVMAPMODE = (1 << 25),
	MATERIAL_VAR_SUPPRESS_DECALS = (1 << 26),
	MATERIAL_VAR_HALFLAMBERT = (1 << 27),
	MATERIAL_VAR_WIREFRAME = (1 << 28),
	MATERIAL_VAR_ALLOWALPHATOCOVERAGE = (1 << 29),
	MATERIAL_VAR_ALPHA_MODIFIED_BY_PROXY = (1 << 30),
	MATERIAL_VAR_VERTEXFOG = (1 << 31),
};

enum ImageFormat
{
	IMAGE_FORMAT_UNKNOWN = -1,
	IMAGE_FORMAT_RGBA8888 = 0,
	IMAGE_FORMAT_ABGR8888,
	IMAGE_FORMAT_RGB888,
	IMAGE_FORMAT_BGR888,
	IMAGE_FORMAT_RGB565,
	IMAGE_FORMAT_I8,
	IMAGE_FORMAT_IA88,
	IMAGE_FORMAT_P8,
	IMAGE_FORMAT_A8,
	IMAGE_FORMAT_RGB888_BLUESCREEN,
	IMAGE_FORMAT_BGR888_BLUESCREEN,
	IMAGE_FORMAT_ARGB8888,
	IMAGE_FORMAT_BGRA8888,
	IMAGE_FORMAT_DXT1,
	IMAGE_FORMAT_DXT3,
	IMAGE_FORMAT_DXT5,
	IMAGE_FORMAT_BGRX8888,
	IMAGE_FORMAT_BGR565,
	IMAGE_FORMAT_BGRX5551,
	IMAGE_FORMAT_BGRA4444,
	IMAGE_FORMAT_DXT1_ONEBITALPHA,
	IMAGE_FORMAT_BGRA5551,
	IMAGE_FORMAT_UV88,
	IMAGE_FORMAT_UVWQ8888,
	IMAGE_FORMAT_RGBA16161616F,
	IMAGE_FORMAT_RGBA16161616,
	IMAGE_FORMAT_UVLX8888,
	IMAGE_FORMAT_R32F,			// Single-channel 32-bit floating point
	IMAGE_FORMAT_RGB323232F,
	IMAGE_FORMAT_RGBA32323232F,

	// Depth-stencil texture formats for shadow depth mapping
	IMAGE_FORMAT_NV_DST16,		// 
	IMAGE_FORMAT_NV_DST24,		//
	IMAGE_FORMAT_NV_INTZ,		// Vendor-specific depth-stencil texture
	IMAGE_FORMAT_NV_RAWZ,		// formats for shadow depth mapping 
	IMAGE_FORMAT_ATI_DST16,		// 
	IMAGE_FORMAT_ATI_DST24,		//
	IMAGE_FORMAT_NV_NULL,		// Dummy format which takes no video memory

	// Compressed normal map formats
	IMAGE_FORMAT_ATI2N,			// One-surface ATI2N / DXN format
	IMAGE_FORMAT_ATI1N,			// Two-surface ATI1N format

	NUM_IMAGE_FORMATS
};

enum RenderTargetSizeMode_t
{
	RT_SIZE_NO_CHANGE = 0,			// Only allowed for render targets that don't want a depth buffer
	// (because if they have a depth buffer, the render target must be less than or equal to the size of the framebuffer).
	RT_SIZE_DEFAULT = 1,				// Don't play with the specified width and height other than making sure it fits in the framebuffer.
	RT_SIZE_PICMIP = 2,				// Apply picmip to the render target's width and height.
	RT_SIZE_HDR = 3,					// frame_buffer_width / 4
	RT_SIZE_FULL_FRAME_BUFFER = 4,	// Same size as frame buffer, or next lower power of 2 if we can't do that.
	RT_SIZE_OFFSCREEN = 5,			// Target of specified size, don't mess with dimensions
	RT_SIZE_FULL_FRAME_BUFFER_ROUNDED_UP = 6, // Same size as the frame buffer, rounded up if necessary for systems that can't do non-power of two textures.
	RT_SIZE_REPLAY_SCREENSHOT = 7,	// Rounded down to power of 2, essentially...
	RT_SIZE_LITERAL = 8				// Use the size passed in. Don't clamp it to the frame buffer size. Really.
};

enum MaterialRenderTargetDepth_t
{
	MATERIAL_RT_DEPTH_SHARED = 0x0,
	MATERIAL_RT_DEPTH_SEPARATE = 0x1,
	MATERIAL_RT_DEPTH_NONE = 0x2,
	MATERIAL_RT_DEPTH_ONLY = 0x3,
};

enum TextureFlags
{
	// flags from the *.txt config file
	TEXTUREFLAGS_POINTSAMPLE = 0x00000001,
	TEXTUREFLAGS_TRILINEAR = 0x00000002,
	TEXTUREFLAGS_CLAMPS = 0x00000004,
	TEXTUREFLAGS_CLAMPT = 0x00000008,
	TEXTUREFLAGS_ANISOTROPIC = 0x00000010,
	TEXTUREFLAGS_HINT_DXT5 = 0x00000020,
	TEXTUREFLAGS_SRGB = 0x00000040,
	TEXTUREFLAGS_NORMAL = 0x00000080,
	TEXTUREFLAGS_NOMIP = 0x00000100,
	TEXTUREFLAGS_NOLOD = 0x00000200,
	TEXTUREFLAGS_ALL_MIPS = 0x00000400,
	TEXTUREFLAGS_PROCEDURAL = 0x00000800,

	// These are automatically generated by vtex from the texture data.
	TEXTUREFLAGS_ONEBITALPHA = 0x00001000,
	TEXTUREFLAGS_EIGHTBITALPHA = 0x00002000,

	// newer flags from the *.txt config file
	TEXTUREFLAGS_ENVMAP = 0x00004000,
	TEXTUREFLAGS_RENDERTARGET = 0x00008000,
	TEXTUREFLAGS_DEPTHRENDERTARGET = 0x00010000,
	TEXTUREFLAGS_NODEBUGOVERRIDE = 0x00020000,
	TEXTUREFLAGS_SINGLECOPY = 0x00040000,

	TEXTUREFLAGS_UNUSED_00080000 = 0x00080000,
	TEXTUREFLAGS_UNUSED_00100000 = 0x00100000,
	TEXTUREFLAGS_UNUSED_00200000 = 0x00200000,
	TEXTUREFLAGS_UNUSED_00400000 = 0x00400000,

	TEXTUREFLAGS_NODEPTHBUFFER = 0x00800000,

	TEXTUREFLAGS_UNUSED_01000000 = 0x01000000,

	TEXTUREFLAGS_CLAMPU = 0x02000000,

	TEXTUREFLAGS_VERTEXTEXTURE = 0x04000000,					// Useable as a vertex texture

	TEXTUREFLAGS_SSBUMP = 0x08000000,

	TEXTUREFLAGS_UNUSED_10000000 = 0x10000000,

	// Clamp to border color on all texture coordinates
	TEXTUREFLAGS_BORDER = 0x20000000,

	TEXTUREFLAGS_UNUSED_40000000 = 0x40000000,
	TEXTUREFLAGS_UNUSED_80000000 = 0x80000000,
};

enum ClearFlags_t
{
	VIEW_CLEAR_COLOR = 0x1,
	VIEW_CLEAR_DEPTH = 0x2,
	VIEW_CLEAR_FULL_TARGET = 0x4,
	VIEW_NO_DRAW = 0x8,
	VIEW_CLEAR_OBEY_STENCIL = 0x10, // Draws a quad allowing stencil test to clear through portals
	VIEW_CLEAR_STENCIL = 0x20,
};


enum DataUpdateType_t
{
	DATA_UPDATE_CREATED = 0,
	DATA_UPDATE_DATATABLE_CHANGED,
};

enum CommandButtons
{
	IN_ATTACK = (1 << 0),
	IN_JUMP = (1 << 1),
	IN_DUCK = (1 << 2),
	IN_FORWARD = (1 << 3),
	IN_BACK = (1 << 4),
	IN_USE = (1 << 5),
	IN_CANCEL = (1 << 6),
	IN_LEFT = (1 << 7),
	IN_RIGHT = (1 << 8),
	IN_MOVELEFT = (1 << 9),
	IN_MOVERIGHT = (1 << 10),
	IN_ATTACK2 = (1 << 11),
	IN_RUN = (1 << 12),
	IN_RELOAD = (1 << 13),
	IN_LEFT_ALT = (1 << 14),
	IN_RIGHT_ALT = (1 << 15),
	IN_SCORE = (1 << 16),
	IN_SPEED = (1 << 17),
	IN_WALK = (1 << 18),
	IN_ZOOM = (1 << 19),
	IN_WEAPON = (1 << 20),
	IN_WEAPON2 = (1 << 21),
	IN_BULLRUSH = (1 << 22),
	IN_GRENADE = (1 << 23),
	IN_GRENADE2 = (1 << 24),
	IN_ATTACK3 = (1 << 25)
};

//
// functions
//
bool WorldToScreen( const Vector& world, ImVec2& screen );
bool SmokeTraceLine(Vector start, Vector end);
void RandomSeed(unsigned int seed);
float RandomFloat(float min, float max);

//
// typedefs
//

using Quaternion = Vector4D;
using RadianEuler = QAngle;
using VectorAligned = Vector4D;
using CRC32_t = unsigned int;
using CBaseHandle = unsigned long;

using InstantiateInterfaceFn = void* ( * )( );
using RecvVarProxyFn = void( * )( const void*, void*, void* );
using ArrayLengthRecvProxyFn = void( * )( void*, int, int );
using DataTableRecvVarProxyFn = void( * )( const void*, void**, void*, int );
using CreateClientClassFn = void* ( * )( int, int );
using CreateEventFn = void* ( * )( );
using FnChangeCallback_t = void(*)(void*, const char*, float);
using CreateInterfaceFn = void* (*)(const char*, int*);

//
// crc32 procedure
//
void CRC32_Init(CRC32_t* pulCRC);
void CRC32_ProcessBuffer(CRC32_t* pulCRC, const void* p, int len);
void CRC32_Final(CRC32_t* pulCRC);
CRC32_t CRC32_GetTableEntry(unsigned int slot);

//
// structs
//

struct model_t;
struct player_info_t;
struct mstudiobone_t;
struct mstudiobbox_t;
struct mstudiohitboxset_t;
struct studiohdr_t;
struct cplane_t;
struct csurface_t;
struct Ray_t;
struct surfacephysicsparams_t;
struct surfaceaudioparams_t;
struct surfacesoundnames_t;
struct surfacegameprops_t;
struct surfacedata_t;
struct ModelRenderInfo_t;
struct DrawModelState_t;

class IConVar;
class ISurface;
class CCommand;

class IHandleEntity;
class IClientMode;
class IClientUnknown;
class ICollideable;
class IClientNetworkable;
class IClientRenderable;
class IClientEntity;
class C_BaseEntity;
class C_BaseAnimating;
class C_BaseCombatCharacter;
class C_CSPlayer;
class C_BaseCombatWeapon;
class C_BaseViewModel;
class C_WeaponCSBase;
class C_WeaponCSBaseGun;
class CCSWeaponInfo;

class InterfaceReg;
class InterfaceHelper;
class DVariant;
class CRecvProxyData;
class RecvProp;
class RecvTable;
class ClientClass;
class CMoveData;
class CUserCmd;
class CVerifiedUserCmd;
class CGlobalVarsBase;
class CBaseClientState;
class CBaseTrace;
class CGameTrace;
template< class T, class I = int >
class CUtlMemory;
template< class T, class A = CUtlMemory< T > >
class CUtlVector;
class ConCommandBase;
class ConVar;
class SpoofedConVar;
class KeyValues;
class CViewSetup;

class IMoveHelper;
class IViewRender;
class CInput;
class INetChannelInfo;
class IMaterialVar;
class IMaterial;
class ITexture;
class IMatRenderContext;

class ITraceFilter;
class CTraceFilter;
class CTraceFilterSimple;

class C_GlowObjectManager;

class IBaseClientDLL;
class IClientEntityList;
class IGameMovement;
class IPrediction;
class IVEngineClient;
class IVModelInfoClient;
class IVRenderView;
class IVModelRender;
class IEngineTrace;
class ICvar;
class IMemAlloc;
class IPhysicsSurfaceProps;
class IWeaponSystem;
class IGameUI;
class IInputSystem;
class ILocalize;
class IPhysicsSurfaceProps;

struct player_info_t
{
	PAD( 0x0008 );

	union
	{
		__int64 steamID64;

		struct
		{
			__int32 xuid_low;
			__int32 xuid_high;
		};
	};

	char name[ 128 ] = { };
	int userID = 0;
	char guid[ 20 ] = { };
	PAD( 0x0010 );
	std::uint32_t friendsID = 0;
	char friendsName[ 128 ] = { };
	bool fakeplayer = false;
	bool ishltv = false;
	std::uint32_t customFiles[ 4 ] = { };
	std::uint8_t filesDownloaded = { };
};

struct mstudiobone_t
{
	int sznameindex = 0;
	int parent = 0;
	int bonecontroller[6] = { };
	Vector pos = { };
	Quaternion quat = { };
	RadianEuler rot = { };
	Vector posscale = { };
	Vector rotscale = { };
	matrix3x4_t poseToBone = { };
	Quaternion qAlignment = { };
	int flags = 0;
	int proctype = 0;
	int procindex = 0;
	mutable int physicsbone = 0;
	int surfacepropidx = 0;
	int contents = 0;
	PAD(0x0020);

	inline const char* pszName() const
	{
		return ((char*)this) + sznameindex;
	}
};

struct mstudiobbox_t
{
	int bone = 0;
	int group = 0;
	Vector bbmin = { };
	Vector bbmax = { };
	int szhitboxnameindex = 0;
	PAD(0x000C);
	float radius = 0.f;
	PAD(0x0010);

	const char* pszHitboxName()
	{
		if (szhitboxnameindex == 0)
			return "";

		return ((const char*)this) + szhitboxnameindex;
	}
};

struct mstudiohitboxset_t
{
	int sznameindex = 0;
	int numhitboxes = 0;
	int hitboxindex = 0;

	inline mstudiobbox_t* pHitbox(int i) const
	{
		return (mstudiobbox_t*)(((byte*)this) + hitboxindex) + i;
	};

	inline const char* pszName() const
	{
		return ((char*)this) + sznameindex;
	}
};

struct studiohdr_t
{
	int id = 0;
	int version = 0;
	int checksum = 0;
	char name[64] = { };
	int length = 0;
	Vector eyeposition = { };
	Vector illumposition = { };
	Vector hull_min = { };
	Vector hull_max = { };
	Vector view_bbmin = { };
	Vector view_bbmax = { };
	int flags = 0;
	int numbones = 0;
	int boneindex = 0;
	int numbonecontrollers = 0;
	int bonecontrollerindex = 0;
	int numhitboxsets = 0;
	int hitboxsetindex = 0;

	inline mstudiobone_t* pBone(int index) const
	{
		return (mstudiobone_t*)(((byte*)this) + boneindex) + index;
	}

	mstudiohitboxset_t* pHitboxSet(int i) const
	{
		return (mstudiohitboxset_t*)(((byte*)this) + hitboxsetindex) + i;
	}

	inline mstudiobbox_t* pHitbox(int i, int set) const
	{
		const auto s = pHitboxSet(set);

		if (!s)
			return nullptr;

		return s->pHitbox(i);
	}

	inline int iHitboxCount(int set) const
	{
		const auto s = pHitboxSet(set);

		if (!s)
			return 0;

		return s->numhitboxes;
	}
};

struct cplane_t
{
	Vector normal = { };
	float dist = 0.f;
	std::uint8_t type = 0u;
	std::uint8_t signbits = 0u;
	PAD(0x02);
};

struct csurface_t
{
	const char* name = nullptr;
	short surfaceProps = 0;
	std::uint16_t flags = 0u;
};

struct Ray_t
{
	VectorAligned m_Start = { };
	VectorAligned m_Delta = { };
	VectorAligned m_StartOffset = { };
	VectorAligned m_Extents = { };
	const matrix3x4_t* m_pWorldAxisTransform = nullptr;
	bool m_IsRay = false;
	bool m_IsSwept = false;

	Ray_t()
		: m_pWorldAxisTransform(nullptr)
	{
	}

	void Init(const Vector& start, const Vector& end)
	{
		m_Delta = (end - start).ToVector4();
		m_IsSwept = (m_Delta.LengthSqr() != 0.f);
		m_Extents.Init();
		m_pWorldAxisTransform = nullptr;
		m_IsRay = true;
		m_StartOffset.Init();
		m_Start = start.ToVector4();
	}

	void Init(const Vector& start, const Vector& end, const Vector& mins, const Vector& maxs)
	{
		m_Delta = (end - start).ToVector4();
		m_pWorldAxisTransform = nullptr;
		m_IsSwept = (m_Delta.LengthSqr() != 0.f);
		m_Extents = (maxs - mins).ToVector4();
		m_Extents *= 0.5f;
		m_IsRay = (m_Extents.LengthSqr() < 1e-6f);
		m_StartOffset = (maxs + mins).ToVector4();
		m_StartOffset *= 0.5f;
		m_Start = start.ToVector4() + m_StartOffset;
		m_StartOffset *= -1.f;
	}
};

struct surfacephysicsparams_t
{
	float    friction;
	float    elasticity;
	float    density;
	float    thickness;
	float    dampening;
};

struct surfaceaudioparams_t
{
	float    reflectivity;             // like elasticity, but how much sound should be reflected by this surface
	float    hardnessFactor;           // like elasticity, but only affects impact sound choices
	float    roughnessFactor;          // like friction, but only affects scrape sound choices   
	float    roughThreshold;           // surface roughness > this causes "rough" scrapes, < this causes "smooth" scrapes
	float    hardThreshold;            // surface hardness > this causes "hard" impacts, < this causes "soft" impacts
	float    hardVelocityThreshold;    // collision velocity > this causes "hard" impacts, < this causes "soft" impacts   
	float    highPitchOcclusion;       //a value betweeen 0 and 100 where 0 is not occluded at all and 100 is silent (except for any additional reflected sound)
	float    midPitchOcclusion;
	float    lowPitchOcclusion;
};

struct surfacesoundnames_t
{
	unsigned short    walkStepLeft;
	unsigned short    walkStepRight;
	unsigned short	  runStepLeft;
	unsigned short	  runStepRight;
	unsigned short    impactSoft;
	unsigned short    impactHard;
	unsigned short    scrapeSmooth;
	unsigned short    scrapeRough;
	unsigned short    bulletImpact;
	unsigned short    rolling;
	unsigned short    breakSound;
	unsigned short    strainSound;
};

struct surfacegameprops_t
{
public:
	float max_speed_factor = 0.f;
	float jump_factor = 0.f;
	float penetration_modifier = 0.f;
	float damage_modifier = 0.f;
	unsigned short material = 0u;
	unsigned char climbable = 0u;
	PAD(0x04);
};

struct surfacedata_t
{
	surfacephysicsparams_t	physics;
	surfaceaudioparams_t	audio;
	surfacesoundnames_t		sounds;
	surfacegameprops_t		game;
};

class InterfaceReg
{
public:
	InstantiateInterfaceFn m_CreateFn = nullptr;
	const char* m_pName = nullptr;
	InterfaceReg* m_pNext = nullptr;
};

class InterfaceHelper
{
public:
	std::uintptr_t* ToArray()
	{
		static auto procedure = *reinterpret_cast<std::uintptr_t**>(this);
		return procedure;
	}

	template< typename T >
	T ToArray(int index)
	{
		static auto procedure = *reinterpret_cast<std::uintptr_t**>(this);
		return (T)procedure[index];
	}

	std::uintptr_t ToArray(int index)
	{
		static auto procedure = *reinterpret_cast<std::uintptr_t**>(this);
		return procedure[index];
	}
};

class DVariant
{
public:
	union
	{
		float m_Float;
		int m_Int;
		const char* m_pString;
		void* m_pData;
		float m_Vector[3];
		std::int64_t m_Int64;
	};

	SendPropType m_Type = { };
};

class CRecvProxyData
{
public:
	const RecvProp* m_pRecvProp = nullptr;
	PAD(0x004);
	DVariant m_Value = { };
	int m_iElement = 0;
	int m_ObjectID = 0;
};

class RecvProp
{
public:
	const char* m_pVarName = nullptr;
	SendPropType m_RecvType = { };
	int m_Flags = 0;
	int m_StringBufferSize = 0;
	bool m_bInsideArray = false;
	const void* m_pExtraData = nullptr;
	RecvProp* m_pArrayProp = nullptr;
	ArrayLengthRecvProxyFn m_ArrayLengthProxy = nullptr;
	RecvVarProxyFn m_ProxyFn = nullptr;
	DataTableRecvVarProxyFn m_DataTableProxyFn = nullptr;
	RecvTable* m_pDataTable = nullptr;
	int m_Offset = 0;
	int m_ElementStride = 0;
	int m_nElements = 0;
	const char* m_pParentArrayPropName = nullptr;
};

class RecvTable
{
public:
	RecvProp* m_pProps = nullptr;
	int m_nProps = 0;
	void* m_pDecoder = nullptr;
	const char* m_pNetTableName = nullptr;
	bool m_bInitialized = false;
	bool m_bInMainList = false;
};

class ClientClass
{
public:
	CreateClientClassFn m_pCreateFn = nullptr;
	CreateEventFn m_pCreateEventFn = nullptr;
	char* m_pNetworkName = nullptr;
	RecvTable* m_pRecvTable = nullptr;
	ClientClass* m_pNext = nullptr;
	int m_ClassID = 0;
};

class CMoveData
{
public:
	bool m_bFirstRunOfFunctions : 1;
	bool m_bGameCodeMovedPlayer : 1;
	int m_nPlayerHandle = 0;
	int m_nImpulseCommand = 0;
	QAngle m_vecViewAngles = { };
	QAngle m_vecAbsViewAngles = { };
	int m_nButtons = 0;
	int m_nOldButtons = 0;
	float m_flForwardMove = 0.f;
	float m_flSideMove = 0.f;
	float m_flUpMove = 0.f;
	float m_flMaxSpeed = 0.f;
	float m_flClientMaxSpeed = 0.f;
	Vector m_vecVelocity = { };
	QAngle m_vecAngles = { };
	QAngle m_vecOldAngles = { };
	float m_outStepHeight = 0.f;
	Vector m_outWishVel = { };
	Vector m_outJumpVel = { };
	Vector m_vecConstraintCenter = { };
	float m_flConstraintRadius = 0.f;
	float m_flConstraintWidth = 0.f;
	float m_flConstraintSpeedFactor = 0.f;
	PAD(0x0014);
	Vector m_vecAbsOrigin = { };
};

class CUserCmd
{
public:
	CUserCmd()
	{
		Reset();
	}

	CUserCmd(const CUserCmd& cmd)
	{
		*this = cmd;
	}

	virtual ~CUserCmd() = default;

public:
	void Reset()
	{
		command_number = 0;
		tick_count = 0;
		viewangles.Init();
		aimdirection.Init();
		forwardmove = 0.f;
		sidemove = 0.f;
		upmove = 0.f;
		buttons = 0;
		impulse = 0;
		weaponselect = 0;
		weaponsubtype = 0;
		random_seed = 0;
		mousedx = 0;
		mousedy = 0;
		hasbeenpredicted = false;
		headangles.Init();
		headoffset.Init();
	}

	CRC32_t GetChecksum() const
	{
		CRC32_t crc = 0u;

		CRC32_Init(&crc);
		CRC32_ProcessBuffer(&crc, &command_number, sizeof(command_number));
		CRC32_ProcessBuffer(&crc, &tick_count, sizeof(tick_count));
		CRC32_ProcessBuffer(&crc, &viewangles, sizeof(viewangles));
		CRC32_ProcessBuffer(&crc, &aimdirection, sizeof(aimdirection));
		CRC32_ProcessBuffer(&crc, &forwardmove, sizeof(forwardmove));
		CRC32_ProcessBuffer(&crc, &sidemove, sizeof(sidemove));
		CRC32_ProcessBuffer(&crc, &upmove, sizeof(upmove));
		CRC32_ProcessBuffer(&crc, &buttons, sizeof(buttons));
		CRC32_ProcessBuffer(&crc, &impulse, sizeof(impulse));
		CRC32_ProcessBuffer(&crc, &weaponselect, sizeof(weaponselect));
		CRC32_ProcessBuffer(&crc, &weaponsubtype, sizeof(weaponsubtype));
		CRC32_ProcessBuffer(&crc, &random_seed, sizeof(random_seed));
		CRC32_ProcessBuffer(&crc, &mousedx, sizeof(mousedx));
		CRC32_ProcessBuffer(&crc, &mousedy, sizeof(mousedy));
		CRC32_Final(&crc);

		return crc;
	}

public:
	CUserCmd& operator = (const CUserCmd& cmd)
	{
		if (this == &cmd)
			return *this;

		command_number = cmd.command_number;
		tick_count = cmd.tick_count;
		viewangles = cmd.viewangles;
		aimdirection = cmd.aimdirection;
		forwardmove = cmd.forwardmove;
		sidemove = cmd.sidemove;
		upmove = cmd.upmove;
		buttons = cmd.buttons;
		impulse = cmd.impulse;
		weaponselect = cmd.weaponselect;
		weaponsubtype = cmd.weaponsubtype;
		random_seed = cmd.random_seed;
		mousedx = cmd.mousedx;
		mousedy = cmd.mousedy;
		hasbeenpredicted = cmd.hasbeenpredicted;
		headangles = cmd.headangles;
		headoffset = cmd.headoffset;

		return *this;
	}

public:
	int command_number = 0;
	int tick_count = 0;
	QAngle viewangles = { };
	Vector aimdirection = { };
	float forwardmove = 0.f;
	float sidemove = 0.f;
	float upmove = 0.f;
	int buttons = 0;
	std::uint8_t impulse = 0u;
	int weaponselect = 0;
	int weaponsubtype = 0;
	int random_seed = 0;
	short mousedx = 0;
	short mousedy = 0;
	bool hasbeenpredicted = false;
	QAngle headangles = { };
	Vector headoffset = { };
};

class CVerifiedUserCmd
{
public:
	CUserCmd m_cmd = { };
	CRC32_t m_crc = 0u;
};

class CGlobalVarsBase
{
public:
	float realtime = 0.f;
	int framecount = 0;
	float absoluteframetime = 0.f;
	float absoluteframestarttimestddev = 0.f;
	float curtime = 0.f;
	float frametime = 0.f;
	int maxClients = 0;
	int tickcount = 0;
	float interval_per_tick = 0.f;
	float interpolation_amount = 0.f;
	int simTicksThisFrame = 0;
	int network_protocol = 0;
	void* pSaveData = nullptr;
	bool m_bClient = false;
	int nTimestampNetworkingBase = 0;
	int nTimestampRandomizeWindow = 0;
};

class CBaseTrace
{
public:
	Vector startpos = { };
	Vector endpos = { };
	cplane_t plane = { };
	float fraction = 0.f;
	int contents = 0;
	std::uint16_t dispFlags = 0u;
	bool allsolid = false;
	bool startsolid = false;
};

class CGameTrace : public CBaseTrace
{
public:
	float fractionleftsolid = 0.f;
	csurface_t surface = { };
	int hitgroup = 0;
	short physicsbone = 0;
	std::uint16_t worldSurfaceIndex = 0u;
	C_BaseEntity* m_pEnt = nullptr;
	int hitbox = 0;
};

template< class T, class I >
class CUtlMemory
{
public:
	T* m_pMemory = nullptr;
	int m_nAllocationCount = 0;
	int m_nGrowSize = 0;
};

template< class T, class A >
class CUtlVector
{
	using CAllocator = A;
public:
	CAllocator* m_Memory = { };
	int m_Size = 0;
	T* m_pElements = nullptr;
};

class ConCommandBase
{
public:
	virtual ~ConCommandBase() = default;

public:
	ConCommandBase* m_pNext = nullptr;
	int m_bRegistered = 0;
	const char* m_pszName = nullptr;
	const char* m_pszHelpString = nullptr;
	int m_nFlags = 0;
};

class ConVar : public ConCommandBase
{
public:
	float GetFloat()
	{
		auto xored = *(std::uint32_t*) & m_pParent->m_Value.m_fValue ^ (std::uint32_t)this;
		return *(float*)&xored;
	}

	int GetInt()
	{
		return (int)(m_pParent->m_Value.m_nValue ^ (int)this);
	}

	bool GetBool()
	{
		return !(!(GetInt()));
	}

	void SetValue(float value)
	{
		auto new_value = value;

		*(std::uint32_t*)& m_pParent->m_Value.m_fValue = *(std::uint32_t*) & new_value ^ (std::uint32_t) this;
		*(std::uint32_t*)& m_pParent->m_Value.m_nValue = (std::uint32_t) new_value ^ (std::uint32_t) this;
	}

	void SetValue(int value)
	{
		return SetValue(static_cast<float>(value));
	}

	void SetValue(bool value)
	{
		return SetValue(static_cast<int>(value));
	}
public:
	struct CVValue_t
	{
		char* m_pszString = nullptr;
		int m_StringLength = 0;
		float m_fValue = 0.f;
		int m_nValue = 0;
	};
private:
	PAD(0x04);
	ConVar* m_pParent = nullptr;
	const char* m_pszDefaultValue = nullptr;
	CVValue_t m_Value = { };
	int m_bHasMin = 0;
	float m_fMinVal = 0.f;
	int m_bHasMax = 0;
	float m_fMaxVal = 0.f;
	CUtlVector< FnChangeCallback_t > m_fnChangeCallbacks = { };
};

class IClientMode
{
public:
};

//
// interfaces
//

class IMaterialVar
{
public:
	VFUNC(void, SetValue, 4, (float value), (this, value))
	VFUNC(void, SetVectorValue, 11, (float x, float y, float z), (this, x, y, z))
	VFUNC(void, SetVecComponentValue, 26, (float value, int component), (this, value, component))
};

class IMaterial
{
public:
	VFUNC(const char*, GetName, 0, (), (this))
	VFUNC(const char*, GetTextureGroupName, 1, (), (this))
	VFUNC(IMaterialVar*, FindVar, 11, (const char* name, bool* found = nullptr, bool complain = true), (this, name, found, complain))
	VFUNC(void, IncrementReferenceCount, 12, (), (this))
	VFUNC(void, DecrementReferenceCount, 13, (), (this))
	VFUNC(void, AlphaModulate, 27, (float alpha), (this, alpha))
	VFUNC(void, ColorModulate, 28, (float r, float g, float b), (this, r, g, b))
	VFUNC(void, SetMaterialVarFlag, 29, (MaterialVarFlags_t flag, bool on), (this, flag, on))
	VFUNC(int, GetReferenceCount, 56, (), (this))
	VFUNC(bool, IsPrecached, 70, (), (this))
};

class ISurface
{
public:
	VFUNC(void, LockCursor, 67, (), (this))
	VFUNC(void, UnlockCursor, 66, (), (this))
};

class ITraceFilter
{
public:
	virtual bool ShouldHitEntity(IHandleEntity* pEntity, int contentsMask) = 0;
	virtual TraceType_t GetTraceType() const = 0;
};

class CTraceFilter : public ITraceFilter
{
public:
	virtual TraceType_t GetTraceType() const
	{
		return TRACE_EVERYTHING;
	}
};

class CTraceFilterSimple : public CTraceFilter
{
public:
	CTraceFilterSimple(C_BaseEntity* base_entity = nullptr)
		: m_skip(base_entity)
	{
	}

	virtual bool ShouldHitEntity(IHandleEntity* pEntity, int contentsMask)
	{
		return !(pEntity == (IHandleEntity*)m_skip);
	}

private:
	C_BaseEntity* m_skip = nullptr;
};

class IHandleEntity
{
public:
	VFUNC(void, SetRefEHandle, 1, (const CBaseHandle& handle), (this, handle))
	VFUNC(CBaseHandle&, GetRefEHandle, 2, (), (this))
};

class IClientUnknown : public IHandleEntity
{
public:
	VFUNC(ICollideable*, GetCollideable, 3, (), (this))
	VFUNC(IClientNetworkable*, GetClientNetworkable, 4, (), (this))
	VFUNC(IClientRenderable*, GetClientRenderable, 5, (), (this))
	VFUNC(IClientEntity*, GetIClientEntity, 6, (), (this))
	VFUNC(C_BaseEntity*, GetBaseEntity, 7, (), (this))
};

class ICollideable
{
public:
	VFUNC(const Vector&, OBBMins, 1, (), (this))
	VFUNC(const Vector&, OBBMaxs, 2, (), (this))
};

class IClientNetworkable
{
public:
	VFUNC(void, Release, 1, (), (this))
	VFUNC(ClientClass*, GetClientClass, 2, (), (this))
	VFUNC(void, PreDataUpdate, 6, (DataUpdateType_t type), (this, type))
	VFUNC(bool, IsDormant, 9, (), (this))
	VFUNC(int, GetIndex, 10, (), (this))
	VFUNC(int, SetDestroyedOnRecreateEntities, 13, (), (this))
};

class IClientRenderable
{
public:
	VFUNC(const model_t*, GetModel, 8, (), (this))
	VFUNC(int, DrawModel, 9, (int flags, const int& instasnce), (this, flags, instasnce))
	VFUNC(bool, SetupBones, 13, (matrix3x4_t* pBoneToWorld, int nMaxBones, int boneMask, float currentTime), (this, pBoneToWorld, nMaxBones, boneMask, currentTime))
};

class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable
{
public:
	VFUNC(const Vector&, GetAbsOrigin, 10, (), (this))
	VFUNC(const QAngle&, GetAbsAngles, 11, (), (this))
};

class IBaseClientDLL : public InterfaceHelper
{
public:
	VFUNC(ClientClass*, GetAllClasses, 8, (), (this))
	VFUNC(bool, DispatchUserMessage, 38, (int messageType, int arg, int arg1, void* data), (this, messageType, arg, arg1, data))
};

class IClientEntityList
{
public:
	VFUNC(IClientEntity*, GetClientEntity, 3, (int index), (this, index))
	VFUNC(IClientEntity*, GetClientEntityFromHandle, 4, (CBaseHandle hEnt), (this, hEnt))
	VFUNC(int, GetHighestEntityIndex, 6, (), (this))
};

class IVEngineClient
{
public:
	VFUNC(void, GetScreenSize, 5, (int& width, int& height), (this, std::ref(width), std::ref(height)))
	VFUNC(bool, GetPlayerInfo, 8, (int ent_num, player_info_t* pinfo), (this, ent_num, pinfo))
	VFUNC(int, GetPlayerForUserID, 9, (int userID), (this, userID))
	VFUNC(int, GetLocalPlayer, 12, (), (this))
	VFUNC(void, GetViewAngles, 18, (QAngle& va), (this, std::ref(va)))
	VFUNC(void, SetViewAngles, 19, (QAngle& va), (this, std::ref(va)))
	VFUNC(int, GetMaxClients, 20, (), (this))
	VFUNC(bool, IsInGame, 26, (), (this))
	VFUNC(bool, IsConnected, 27, (), (this))
	VFUNC(bool, CullBox, 34, (const Vector& mins, const Vector& maxs), (this, std::cref(mins), std::cref(maxs)))
	VFUNC(const VMatrix&, WorldToScreenMatrix, 37, (), (this))
	VFUNC(void*, GetBSPTreeQuery, 43, (), (this))
	VFUNC(const char*, GetLevelName, 53, (), (this))
	VFUNC(INetChannelInfo*, GetNetChannelInfo, 78, (), (this))
	VFUNC(void, ExecuteClientCmd, 108, (const char* cmd), (this,cmd))
	VFUNC(void, ClientCmdUnrestricted, 114, (const char* cmd, bool fromConsoleOrKeybind = false), (this, cmd, fromConsoleOrKeybind))
};

class IVModelInfoClient
{
public:
	VFUNC(const model_t*, GetModel, 1, (int index), (this, index))
	VFUNC(int, GetModelIndex, 2, (const char* name), (this, name))
	VFUNC(const char*, GetModelName, 3, (const model_t* model), (this, model))
	VFUNC(studiohdr_t*, GetStudioModel, 32, (const model_t* model), (this, model))
};

class IVRenderView
{
public:
	VFUNC(void, SetBlend, 4, (float blend), (this, blend))
	VFUNC(void, SetColorModulation, 6, (const float* color), (this, color))
};

class IVModelRender
{
public:
	VFUNC(void, ForcedMaterialOverride, 1, (IMaterial* mat, OverrideType_t type = OVERRIDE_NORMAL), (this, mat, type,0))
};

class IEngineTrace
{
public:
	VFUNC(void, TraceRay, 5, (const Ray_t& ray, unsigned int fMask, ITraceFilter* pTraceFilter, CGameTrace* pTrace), (this, ray, fMask, pTraceFilter, pTrace))
};

class ICvar
{
public:
	VFUNC(void, RegisterConCommand, 11, (ConVar* pCommandBase), (this, pCommandBase))
	VFUNC(void, UnregisterConCommand, 12, (ConVar* pCommandBase), (this, pCommandBase))
	VFUNC(ConVar*, FindVar, 14, (const char* var_name), (this, var_name))
};

class IMemAlloc
{
public:
	VFUNC(void*, Alloc, 1, (int nSize), (this, nSize))
	VFUNC(void*, Realloc, 3, (void* pMem, int nSize), (this, pMem, nSize))
	VFUNC(void*, Free, 5, (void* pMem), (this, pMem))
};

class IMaterialSystem
{
public:
	VFUNC(IMaterial*, CreateMaterial, 83, (const char* name, KeyValues* key), (this, name, key))
	VFUNC(IMaterial*, FindMaterial, 84, (const char* name, const char* texture_group_name, bool complain = true, const char* complain_prefix = nullptr), (this, name, texture_group_name, complain, complain_prefix))
};

class IGameEvent
{
public:
	virtual ~IGameEvent() = 0;
	virtual const char* GetName() const = 0;

	virtual bool  IsReliable() const = 0;
	virtual bool  IsLocal() const = 0;
	virtual bool  IsEmpty(const char* keyName = nullptr) = 0;

	virtual bool  GetBool(const char* keyName = nullptr, bool defaultValue = false) = 0;
	virtual int   GetInt(const char* keyName = nullptr, int defaultValue = 0) = 0;
	virtual unsigned long GetUint64(const char* keyName = nullptr, unsigned long defaultValue = 0) = 0;
	virtual float GetFloat(const char* keyName = nullptr, float defaultValue = 0.0f) = 0;
	virtual const char* GetString(const char* keyName = nullptr, const char* defaultValue = "") = 0;
	virtual const wchar_t* GetWString(const char* keyName, const wchar_t* defaultValue = L"") = 0;

	virtual void SetBool(const char* keyName, bool value) = 0;
	virtual void SetInt(const char* keyName, int value) = 0;
	virtual void SetUint64(const char* keyName, unsigned long value) = 0;
	virtual void SetFloat(const char* keyName, float value) = 0;
	virtual void SetString(const char* keyName, const char* value) = 0;
	virtual void SetWString(const char* keyName, const wchar_t* value) = 0;
};

class IGameEventListener2
{
public:
	virtual ~IGameEventListener2() { }

	virtual void FireGameEvent(IGameEvent* event) = 0;
	virtual int GetEventDebugID() = 0;
};

class IGameEventManager
{
public:
	VFUNC(bool, AddListener, 3, (IGameEventListener2* listener, const char* name, bool bServerSide), (this, listener, name, bServerSide))
	VFUNC(int, RemoveListener, 5, (IGameEventListener2* listener), (this, listener))
	VFUNC(bool, FireEventClientSide, 9, (IGameEvent* events), (this, events))
};

class SpoofedConVar
{
public:
	SpoofedConVar() = default;
	SpoofedConVar(const char* var_name);
	SpoofedConVar(ConVar * cvar);

	~SpoofedConVar();

	bool IsSpoofed();
	void Spoof();

	void SetFlags(int flags);
	int GetFlags();

	void SetBool(bool value);
	void SetInt(int value);
	void SetFloat(float value);
private:
	ConVar* m_cvar_restore = nullptr;
	ConVar* m_cvar_replace = nullptr;

	char m_restore_name[128] = { };
	float m_restore_value = 0.f;

	char m_replace_name[128] = { };
	float m_replace_value = 0.f;

	int m_restore_flags = 0;
};

class KeyValues
{
public:
	KeyValues(const char* name);
public:
	bool LoadBuffer(const char* resourceName, const char* pBuffer, void* pSomething = nullptr, void* pAnother = nullptr, void* pLast = nullptr);
public:
	PAD(0x0025);
};

class IWeaponSystem
{
public:
	VFUNC(CCSWeaponInfo*, GetWeaponData, 2, (short index), (this, index))
};

class IGameMovement
{
public:
	VFUNC(void, ProcessMovement, 1, (C_CSPlayer* localPlayer, CMoveData* moveData), (this, localPlayer, moveData))
};

class IGameUI
{
public:
	VFUNC(void, CreateCommandMsgBox, 20, (const char* title, const char* message, bool showOk = true, bool showCancel = false, const char* okCommand = nullptr, const char* cancelCommand = nullptr, const char* closedCommand = nullptr, const char* legend = nullptr, const char* unknown = nullptr), (this, title, message, showOk, showCancel, okCommand, cancelCommand, closedCommand, legend, unknown))
};

class IInputSystem
{
public:
	VFUNC(void, EnableInput, 11, (bool enable), (this, enable))
	VFUNC(bool, IsButtonDown, 15, (int buttonCode), (this, buttonCode))
	VFUNC(void, ResetInputState, 39, (), (this))
	VFUNC(const char*, ButtonCodeToString, 40, (int buttonCode), (this, buttonCode))
};

class ILocalize
{
public:
	VFUNC(const wchar_t*, Find, 12, (const char* tokenName), (this, tokenName))
	VFUNC(int, ConvertAnsiToUnicode, 15, (const char* ansi, wchar_t* unicode, int unicodeBufferSizeInBytes), (this, ansi, unicode, unicodeBufferSizeInBytes))
	VFUNC(int, ConvertUnicodeToAnsi, 16, (const wchar_t* unicode, char* ansi, int ansiBufferSize), (this, unicode, ansi, ansiBufferSize))
	VFUNC(const char*, FindAsUTF8, 47, (const char* tokenName), (this, tokenName))
};

class C_GlowObjectManager
{
public:
	class GlowObjectDefinition_t
	{
	public:
		class C_BaseEntity* m_pEntity = nullptr;

		Vector	m_vGlowColor = { };
		float m_flGlowAlpha = 0.f;

		PAD(0x004);

		float m_flUnknown = 0.f;
		float m_flBloomAmount = 0.f;
		float m_flPointZero = 0.f;

		bool m_bRenderWhenOccluded = false;
		bool m_bRenderWhenUnoccluded = false;
		bool m_bFullBloomRender = false;

		PAD(0x001);

		std::int32_t m_nFullBloomStencilTestValue = 0;
		std::int32_t m_nStyle = 0;
		std::int32_t m_nSplitScreenSlot = 0;
		std::int32_t m_nNextFreeSlot = 0;

		bool IsUnused() const
		{
			return (m_nNextFreeSlot != -2);
		}

		void SetColor(const ImColor& color)
		{
			m_vGlowColor = { color.Value.x, color.Value.y, color.Value.z };
			m_flGlowAlpha = color.Value.w;
		}
	};

	GlowObjectDefinition_t* m_GlowObjectDefinitions = nullptr;
	int max_size = 0;
	int pad = 0;
	int size = 0;
	GlowObjectDefinition_t* m_Unknown = nullptr;
	int	currentObjects = 0;
};


class IPhysicsSurfaceProps
{
public:
	VFUNC(surfacedata_t*, GetSurfaceData, 5, (int dataIndex), (this, dataIndex))
};