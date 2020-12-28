#include "csgo/hook/procedure.hpp"

#include "csgo/engine.hpp"

#include "sdk/object/entity.hpp"
#include "sdk/object/player.hpp"
#include "sdk/object/weapon.hpp"

namespace csgo::hook
{
	bool API_STDCALL CreateMove(float input_time, CUserCmd* cmd)
	{
		m_create_move_hook->Restore();
		const auto result = m_create_move_hook->Win32Call< bool >( input_time, cmd);
		m_create_move_hook->Replace();

		if (!cmd->command_number)
			return false;


		/*features call
		* example:
		* auto& aimbot = feature::Aimbot::Instance();
		* aimbot.CreateMove( cmd );
		*/

		auto& system = win32::System::Instance();

		if (system.Gui())
		{
			cmd->buttons &= ~IN_ATTACK;
			cmd->buttons &= ~IN_ATTACK2;
			cmd->buttons &= ~IN_SCORE;
			cmd->buttons &= ~IN_RUN;
		}

		return result;
	}
}