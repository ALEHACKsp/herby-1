#pragma once

#include "csgo/engine/renderer.hpp"
#include "csgo/engine.hpp"
#include "sdk/object/entity.hpp"
#include "sdk/object/player.hpp"
#include "sdk/object/weapon.hpp"

namespace csgo::feature
{
	class Esp : public detail::Singleton< Esp >
	{
	public:
		void Present();
	private:
		void DrawBorderBox(const ImVec2& begin, const ImVec2& size, float t, const ImColor& color);
		void DrawBorderBoxOut(const ImVec2& begin, const ImVec2& size, float t, const ImColor& color, const ImColor& out = { 0.f, 0.f, 0.f, 1.f });
		void PaintEntity(int index, C_CSPlayer* player);
		void PaintDrop(int index);
		void PaintGround(C_BaseEntity* ent);
		bool IsDangerZoneLoot(C_CSPlayer* ent);
		float ScaleDamage(float damage, int armor);
	};
}