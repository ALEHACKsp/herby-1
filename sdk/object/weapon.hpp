#pragma once

#include "sdk/object/entity.hpp"


class CCSWeaponInfo
{
public:
	PAD( 0x0088 );
	const char* m_hud_name = nullptr;
	const char* m_weapon_name = nullptr;
	PAD( 0x0038 );
	CSWeaponType m_type = WEAPONTYPE_UNKNOWN;
	PAD( 0x0020 );
	int m_damage = 0;
	float m_armor_ratio = 0.f;
	int m_bullets = 0;
	float m_penetration = 0.f;
	PAD( 0x0008 );
	float m_range = 0.f;
	float m_range_modifier = 0.f;
	PAD( 0x0030 );
	float m_inaccuracy_crouch = 0.f;
	PAD( 0x0030 );
	float m_inaccuracy_move = 0.f;
};

class C_BaseCombatWeapon : public C_BaseAttributeItem
{
public:
	NET_PROP( int, m_iClip1, "DT_BaseCombatWeapon", "m_iClip1" );
	NET_PROP( int, m_iClip2, "DT_BaseCombatWeapon", "m_iClip2" );
	NET_PROP( int, m_iPrimaryAmmoType, "DT_BaseCombatWeapon", "m_iPrimaryAmmoType" );
	NET_PROP( int, m_iSecondaryAmmoType, "DT_BaseCombatWeapon", "m_iSecondaryAmmoType" );

	NET_PROP( float, m_flNextPrimaryAttack, "DT_BaseCombatWeapon", "m_flNextPrimaryAttack" );
	NET_PROP( float, m_flNextSecondaryAttack, "DT_BaseCombatWeapon", "m_flNextSecondaryAttack" );
};

class C_WeaponCSBase : public C_BaseCombatWeapon
{
public:
	bool IsFireTime();
	bool IsSecondaryFireTime();

	bool IsGun();
	bool IsPistol();
	bool IsSniper();

	CCSWeaponInfo* GetCSWeaponData();

public:
	NET_PROP( float, m_fAccuracyPenalty, "DT_WeaponCSBase", "m_fAccuracyPenalty" );
	NET_PROP( float, m_flRecoilIndex, "DT_WeaponCSBase", "m_flRecoilIndex" );
};

class C_BaseCombatCharacter : public C_BaseAnimatingOverlay
{
public:
	C_WeaponCSBase* GetActiveWeapon()
	{
		const auto base_entity = C_BaseEntity::GetBaseEntityFromHandle( m_hActiveWeapon() );

		if( !base_entity )
			return nullptr;

		return reinterpret_cast< C_WeaponCSBase* >( base_entity );
	}

public:
	NET_PROP( CBaseHandle, m_hActiveWeapon, "DT_BaseCombatCharacter", "m_hActiveWeapon" );
	NET_PROP( float, m_flNextAttack, "DT_BaseCombatCharacter", "m_flNextAttack" );
};