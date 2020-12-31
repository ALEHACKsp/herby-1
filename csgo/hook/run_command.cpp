#include "csgo/hook/procedure.hpp"

#include "csgo/engine.hpp"

#include "sdk/object/entity.hpp"
#include "sdk/object/player.hpp"
#include "sdk/object/weapon.hpp"

namespace csgo::hook
{
	VOID API_FASTCALL RunCommand(C_BasePlayer* player, CUserCmd* ucmd, IMoveHelper* moveHelper)
	{
		auto& prediction = engine::Prediction::Instance();

		m_run_command_hook->Restore();
		m_run_command_hook->FastCall< VOID >(player, ucmd, moveHelper);
		m_run_command_hook->Replace();

		prediction.RunCommand(player);
	}
}