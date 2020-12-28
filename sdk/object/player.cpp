#include "sdk/object/player.hpp"

#include "csgo/engine.hpp"


void C_BasePlayer::SetAbsOrigin(const Vector& origin)
{
	using Fn = void(__thiscall*)(void*, const Vector&);
	static auto procedure = memory::scan<Fn>("client.dll", "55 8B EC 83 E4 F8 51 53 56 57 8B F1 E8");
	return procedure(this, origin);
}

void C_BasePlayer::SetAbsAngles(const QAngle& angles)
{
	using Fn = void(__thiscall*)(void*, const QAngle&);
	static auto procedure = memory::scan<Fn>("client.dll", "55 8B EC 83 E4 F8 83 EC 64 53 56 57 8B F1 E8");
	return procedure(this, angles);
}

C_BasePlayer* C_BasePlayer::GetBasePlayer(int index)
{
	auto base_entity = C_BaseEntity::GetBaseEntity(index);
	return ToBasePlayer(base_entity);
}

const Vector& C_BasePlayer::EyePosition() const
{
	return ( m_vecOrigin() + m_vecViewOffset() );
}

C_CSPlayer* C_CSPlayer::GetLocalCSPlayer()
{
	const auto base_entity = C_BaseEntity::GetBaseEntity( csgo::m_engine_client->GetLocalPlayer() );
	return ToCSPlayer( base_entity );
}

C_CSPlayer* C_CSPlayer::GetCSPlayer( const int index )
{
	const auto base_entity = C_BaseEntity::GetBaseEntity( index );
	return ToCSPlayer( base_entity );
}

bool C_CSPlayer::IsLocal()
{
	if (!IsGood())
		return false;

	return (GetIndex() == csgo::m_engine_client->GetLocalPlayer());
}

bool C_CSPlayer::IsGood()
{
	return (m_iHealth() && m_lifeState() == LIFE_ALIVE && !IsDormant());
}

bool C_CSPlayer::IsVisible(const Vector& end)
{
	auto player = C_CSPlayer::GetLocalCSPlayer();

	if (!player)
		return false;

	CTraceFilterSimple trace(player);

	Ray_t ray = { };
	ray.Init(player->EyePosition(), end);

	CGameTrace tr = { };
	csgo::m_engine_trace->TraceRay(ray, 0x46004003, &trace, &tr);

	if (this)
		return (tr.fraction == 1.0f || tr.m_pEnt == this);

	return (tr.fraction == 1.0f);
}