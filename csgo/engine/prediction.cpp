#include "csgo/engine/prediction.hpp"
#include "csgo/engine.hpp"

namespace csgo::engine
{
	bool Prediction::Begin(CUserCmd* cmd, bool* send_packet)
	{
		m_cmd = cmd;
		m_send_packet = send_packet;

		m_player = C_CSPlayer::GetLocalCSPlayer();

		if (!m_player)
			return false;

		if (m_player->m_lifeState() != LIFE_ALIVE)
			return false;

		m_weapon = m_player->GetActiveWeapon();

		if (!m_weapon)
			return false;

		m_weapon->UpdateAccuracyPenalty();

		m_time_current = m_globals->curtime;
		m_time_frame = m_globals->frametime;

		m_flags = m_player->m_fFlags();

		if (m_cmd_previous)
		{
			if (m_cmd_previous->hasbeenpredicted)
				m_server_command = m_player->m_nTickBase();
			else
				m_server_command++;
		}
		else
		{
			m_server_command = m_player->m_nTickBase();
		}

		m_server_time = static_cast<float>(m_server_command) * m_globals->interval_per_tick;

		m_globals->curtime = static_cast<float>(m_player->m_nTickBase()) * m_globals->interval_per_tick;
		m_globals->frametime = m_globals->interval_per_tick;

		m_move_helper->SetHost(m_player);

		m_player->m_pCurrentCommand() = m_cmd;

		C_BaseEntity::SetPredictionSeed(m_cmd);

		CMoveData move = { };

		m_game_movement->StartTrackPredictionErrors(m_player);
		m_prediction->SetupMove(m_player, m_cmd, m_move_helper, &move);
		m_game_movement->ProcessMovement(m_player, &move);
		m_prediction->FinishMove(m_player, m_cmd, &move);
		m_game_movement->FinishTrackPredictionErrors(m_player);

		C_BaseEntity::SetPredictionSeed(nullptr);

		m_player->m_pCurrentCommand() = nullptr;

		m_move_helper->SetHost(nullptr);

		return true;
	}

	void Prediction::End()
	{
		m_globals->curtime = m_time_current;
		m_globals->frametime = m_time_frame;

		m_cmd_previous = m_cmd;
	}

	void Prediction::FrameStageNotify(ClientFrameStage_t stage)
	{
		if (stage != FRAME_NET_UPDATE_POSTDATAUPDATE_START)
			return;

		auto player = C_CSPlayer::GetLocalCSPlayer();

		if (!player)
			return;

		auto entry_index = (player->m_nTickBase() % 128);
		auto entry = GetPlayerCacheEntry(entry_index);

		if (!entry)
			return;

		player->m_aimPunchAngle() = entry->m_aimPunchAngle;
		player->m_viewPunchAngle() = entry->m_viewPunchAngle;
	}

	void Prediction::RunCommand(C_BasePlayer* base_player)
	{
		auto player = C_CSPlayer::GetLocalCSPlayer();

		if (!player)
			return;

		if (player != base_player)
			return;

		auto entry_index = (player->m_nTickBase() % 128);
		auto entry = GetPlayerCacheEntry(entry_index);

		if (!entry)
			return;

		entry->m_aimPunchAngle = player->m_aimPunchAngle();
		entry->m_viewPunchAngle = player->m_viewPunchAngle();
	}

	CUserCmd* Prediction::GetUserCmd() const
	{
		return m_cmd;
	}

	C_CSPlayer* Prediction::GetPlayer() const
	{
		return m_player;
	}

	C_WeaponCSBase* Prediction::GetWeapon() const
	{
		return m_weapon;
	}

	int Prediction::GetFlags() const
	{
		return m_flags;
	}

	int Prediction::GetServerCommand() const
	{
		return m_server_command;
	}

	float Prediction::GetServerTime() const
	{
		return m_server_time;
	}

	player_cache_entry_t* Prediction::GetPlayerCacheEntry(int index)
	{
		if (index < 0 || index >= 128)
			return nullptr;

		return &m_player_cache[index];
	}
}