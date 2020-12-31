#pragma once

#include "csgo/engine/net_prop_system.hpp"

class C_BaseEntity : public IClientEntity
{
public:
	static C_BaseEntity* GetBaseEntity( const int index );
	static C_BaseEntity* GetBaseEntityFromHandle( const CBaseHandle base_handle );
	
	static void SetPredictionSeed(CUserCmd* cmd);
public:
	VFUNC(bool, IsPlayer, 157, (), (this))
	VFUNC(bool, IsWeapon, 165, (), (this))
public:
	NET_PROP( int, m_iTeamNum, "DT_BaseEntity", "m_iTeamNum" );

	NET_PROP( int, m_nModelIndex, "DT_BaseEntity", "m_nModelIndex" );

	NET_PROP(float, m_flC4Blow ,"DT_PlantedC4", "m_flC4Blow");

	NET_PROP( float, m_flSimulationTime, "DT_BaseEntity", "m_flSimulationTime" );

	NET_PROP( Vector, m_vecOrigin, "DT_BaseEntity", "m_vecOrigin" );

	NET_PROP( QAngle, m_angRotation, "DT_BaseEntity", "m_angRotation" );

	NET_PROP( CBaseHandle, m_hWeapon, "DT_BaseEntity", "m_hWeapon" );
	NET_PROP( CBaseHandle, m_hOwner, "DT_BaseEntity", "m_hOwner" );

public:
	NET_PROP_EX( const matrix3x4_t, m_rgflCoordinateFrame, "DT_BaseEntity", "m_CollisionGroup", -0x0030 );
};

class C_BaseAnimating : public C_BaseEntity
{
public:
	bool GetBoneTransform(matrix3x4_t* output, float time = 0.f);
	bool GetBoneWorld(int index, matrix3x4_t* transform, Vector& output);
	bool GetBoxBoundWorld(int index, matrix3x4_t* transform, Vector& min, Vector& max);
	bool GetBoxWorld(int index, matrix3x4_t* transform, Vector& output);
	bool GetHitboxVector(int hitbox, Vector& out);
	bool GetBonePosition(matrix3x4_t* bone_transform, const int bone, Vector& output);

	Vector GetHitboxPosition(int index);

public:
	NET_PROP(bool, m_bClientSideAnimation, "DT_BaseAnimating", "m_bClientSideAnimation");
	NET_PROP(bool, m_bClientSideFrameReset, "DT_BaseAnimating", "m_bClientSideFrameReset");

	NET_PROP(int, m_nSequence, "DT_BaseAnimating", "m_nSequence");
	NET_PROP(int, m_nForceBone, "DT_BaseAnimating", "m_nForceBone");
	NET_PROP(int, m_nSkin, "DT_BaseAnimating", "m_nSkin");
	NET_PROP(int, m_nBody, "DT_BaseAnimating", "m_nBody");
	NET_PROP(int, m_nHitboxSet, "DT_BaseAnimating", "m_nHitboxSet");

	NET_PROP(float, m_flCycle, "DT_BaseAnimating", "m_flCycle");
	NET_PROP(float, m_flPlaybackRate, "DT_BaseAnimating", "m_flPlaybackRate");

	NET_PROP(Vector, m_vecForce, "DT_BaseAnimating", "m_vecForce");
};

class C_BaseAnimatingOverlay : public C_BaseAnimating
{
public:
};

class C_BaseViewModel : public C_BaseAnimatingOverlay
{
public:
	VFUNC(void, SetModelIndex, 75, (int index), (this, index))
	VFUNC(void, SetWeaponModel, 243, (const char* name, void* weapon), (this, name, weapon))
};

class C_BaseAttributeItem : public C_BaseViewModel
{
public:
	C_BaseViewModel* GetBaseModel();
public:
	NET_PROP(short, m_iItemDefinitionIndex, "DT_BaseAttributableItem", "m_iItemDefinitionIndex");

	NET_PROP(int, m_iItemIDHigh, "DT_BaseAttributableItem", "m_iItemIDHigh");
	NET_PROP(int, m_iAccountID, "DT_BaseAttributableItem", "m_iAccountID");
	NET_PROP(int, m_iEntityQuality, "DT_BaseAttributableItem", "m_iEntityQuality");
	NET_PROP(int, m_OriginalOwnerXuidLow, "DT_BaseAttributableItem", "m_OriginalOwnerXuidLow");
	NET_PROP(int, m_OriginalOwnerXuidHigh, "DT_BaseAttributableItem", "m_OriginalOwnerXuidHigh");
	NET_PROP(int, m_nFallbackPaintKit, "DT_BaseAttributableItem", "m_nFallbackPaintKit");
	NET_PROP(int, m_nFallbackSeed, "DT_BaseAttributableItem", "m_nFallbackSeed");
	NET_PROP(int, m_nFallbackStatTrak, "DT_BaseAttributableItem", "m_nFallbackStatTrak");

	NET_PROP(float, m_flFallbackWear, "DT_BaseAttributableItem", "m_flFallbackWear");

};
