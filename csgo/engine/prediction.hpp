#pragma once

#include "sdk/object/entity.hpp"
#include "sdk/object/player.hpp"
#include "sdk/object/weapon.hpp"

namespace csgo::engine
{
	struct player_cache_entry_t
	{
		QAngle m_aimPunchAngle = { };
		QAngle m_viewPunchAngle = { };
	};

	class Prediction : public detail::Singleton< Prediction >
	{
	public:
		bool Begin(CUserCmd* cmd, bool* send_packet);
		void End();

		void FrameStageNotify(ClientFrameStage_t stage);
		void RunCommand(C_BasePlayer* base_player);

		CUserCmd* GetUserCmd() const;
		C_CSPlayer* GetPlayer() const;
		C_WeaponCSBase* GetWeapon() const;

		int GetFlags() const;

		int GetServerCommand() const;
		float GetServerTime() const;
	private:
		player_cache_entry_t* GetPlayerCacheEntry(int index);
	private:
		CUserCmd* m_cmd = nullptr;
		CUserCmd* m_cmd_previous = nullptr;
		bool* m_send_packet = nullptr;
		C_CSPlayer* m_player = nullptr;
		C_WeaponCSBase* m_weapon = nullptr;

		float m_time_current = 0.f;
		float m_time_frame = 0.f;

		int m_flags = 0;

		int m_server_command = 0;
		float m_server_time = 0.f;

		player_cache_entry_t m_player_cache[128] = { };
	};
}