#include "csgo/hook/procedure.hpp"

#include "csgo/engine.hpp"

#include "sdk/object/entity.hpp"
#include "sdk/object/player.hpp"
#include "sdk/object/weapon.hpp"

namespace csgo::hook
{

INT API_FASTCALL FrameStageNotify( ClientFrameStage_t stage )
{
	m_frame_stage_notify_hook->Restore();
	const auto result = m_frame_stage_notify_hook->FastCall< INT >( stage );
	m_frame_stage_notify_hook->Replace();

	auto& prediction = engine::Prediction::Instance();

	prediction.FrameStageNotify(stage);

	return result;

}

}