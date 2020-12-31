#include "csgo/hook/procedure.hpp"

#include "csgo/engine.hpp"

#include "sdk/object/entity.hpp"
#include "sdk/object/player.hpp"
#include "sdk/object/weapon.hpp"

namespace csgo::hook
{
	auto m_send_packet = false;

	VOID CreateMoveCall(int sequence_number, float input_sample_frametime, bool active)
	{
		auto& prediction = engine::Prediction::Instance();
		auto& system = win32::System::Instance();

		auto cmd = m_input->GetUserCmd(sequence_number);
		auto verified = m_input->GetVerifiedCmd(sequence_number);

		if (!cmd || !cmd->command_number)
			return;

		if (system.Gui())
		{
			cmd->buttons &= ~IN_ATTACK;
			cmd->buttons &= ~IN_ATTACK2;
			cmd->buttons &= ~IN_SCORE;
			cmd->buttons &= ~IN_RUN;
		}

		if (prediction.Begin(cmd, &m_send_packet))
		{
			//engine prediction stuff
		}
		prediction.End();

		verified->m_cmd = *cmd;
		verified->m_crc = cmd->GetChecksum();
	}

	std::uintptr_t m_create_move = 0u;
	std::uintptr_t m_create_move_ret = 0u;

	VOID API_FASTCALL CreateMove( int sequence_number, float input_sample_frametime, bool active )
	{
		m_create_move_hook->Restore();
		m_create_move = m_create_move_hook->FastCall< std::uintptr_t >( sequence_number, input_sample_frametime, active);
		m_create_move_hook->Replace();

		__asm
		{
			push eax
			mov eax, [esp + 4]
			mov m_create_move_ret, eax
			pop eax
			add esp, 4
			call m_create_move
			mov m_send_packet, bl
			pushad
		}

		CreateMoveCall(sequence_number, input_sample_frametime, active);

		__asm
		{
			popad
			mov bl, m_send_packet
			jmp m_create_move_ret
		}
	}
}