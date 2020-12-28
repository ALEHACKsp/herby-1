#include "csgo/hook/procedure.hpp"

#include "csgo/engine.hpp"

#include "sdk/object/entity.hpp"
#include "sdk/object/player.hpp"
#include "sdk/object/weapon.hpp"

namespace csgo::hook
{

INT API_FASTCALL FrameStageNotify( void* ecx, void* edx, int stage )
{
	m_frame_stage_notify_hook->Restore();
	const auto result = m_frame_stage_notify_hook->Call< INT >( ecx, stage );
	m_frame_stage_notify_hook->Replace();

	return result;

}

}