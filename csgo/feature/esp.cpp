#include "csgo/feature/esp.hpp"

namespace csgo::feature
{
	void Esp::DrawBorderBox(const ImVec2& begin, const ImVec2& size, float t, const ImColor& color)
	{
		auto& renderer = engine::Renderer::Instance();

		renderer.DrawRect(begin, { size[0], t }, color);
		renderer.DrawRect(begin, { t, size[1] }, color);

		renderer.DrawRect({ begin[0] + size[0], begin[1] }, { t, size[1] }, color);
		renderer.DrawRect({ begin[0], begin[1] + size[1] }, { size[0] + t, t }, color);
	}

	void Esp::DrawBorderBoxOut(const ImVec2& begin, const ImVec2& size, float t, const ImColor& color, const ImColor& out /*= { 0.f, 0.f, 0.f, 1.f }*/)
	{
		DrawBorderBox(begin, size, t, color);
		DrawBorderBox({ begin[0] - t, begin[1] - t }, { size[0] + t * 2.f, size[1] + t * 2.f }, 1.f, out);
		DrawBorderBox({ begin[0] + t, begin[1] + t }, { size[0] - t * 2.f, size[1] - t * 2.f }, 1.f, out);
	}

	void Esp::PaintEntity(int index, C_CSPlayer* player)
	{
		auto& visual = option::m_visual;
		auto& colors = option::m_colors;
		auto& renderer = engine::Renderer::Instance();

		if (player->IsDormant())
			return;

		if (player->m_lifeState() != LIFE_ALIVE)
			return;

		if (!visual.m_friendly)
		{
			if (player->m_iTeamNum() == C_CSPlayer::GetLocalCSPlayer()->m_iTeamNum())
				return;
		}

		matrix3x4_t bone_data[128] = { };

		if (!player->GetBoneTransform(bone_data))
			return;

		Vector head = { };

		if (!player->GetBoxWorld(0, bone_data, head))
			return;

		if (visual.m_visible_check)
		{
			if (!player->IsVisible(head))
				return;
		}

		if (visual.m_smoke_check)
		{
			if (SmokeTraceLine(C_CSPlayer::GetLocalCSPlayer()->EyePosition(), head))
				return;
		}

		ImColor color = { 1.f, 1.f, 1.f, 1.f };

		if (player->m_iTeamNum() == 2)
		{
			color = colors.color_esp_t_normal;

			if (visual.m_colored)
			{
				if (player->IsVisible(head))
					color = colors.color_esp_t_colored;
			}
		}
		else if (player->m_iTeamNum() == 3)
		{
			color = colors.color_esp_ct_normal;

			if (visual.m_colored)
			{
				if (player->IsVisible(head))
					color = colors.color_esp_ct_colored;
			}
		}

		const auto& transform = player->m_rgflCoordinateFrame();

		Vector position(transform[0][3], transform[1][3], transform[2][3]);

		Vector mins = player->GetCollideable()->OBBMins();
		Vector maxs = player->GetCollideable()->OBBMaxs();

		Vector points[] =
		{
			{ mins[0], mins[1], mins[2] },
			{ mins[0], maxs[1], mins[2] },
			{ maxs[0], maxs[1], mins[2] },
			{ maxs[0], mins[1], mins[2] },
			{ maxs[0], maxs[1], maxs[2] },
			{ mins[0], maxs[1], maxs[2] },
			{ mins[0], mins[1], maxs[2] },
			{ maxs[0], mins[1], maxs[2] },
		};

		Vector transformed[8] = { };

		for (auto i = 0; i < 8; i++)
			transformed[i] = points[i].Transform(transform);

		ImVec2 flb, brt, blb, frt, frb, brb, blt, flt;

		if (!WorldToScreen(transformed[3], flb) ||
			!WorldToScreen(transformed[0], blb) ||
			!WorldToScreen(transformed[2], frb) ||
			!WorldToScreen(transformed[6], blt) ||
			!WorldToScreen(transformed[5], brt) ||
			!WorldToScreen(transformed[4], frt) ||
			!WorldToScreen(transformed[1], brb) ||
			!WorldToScreen(transformed[7], flt))
			return;

		ImVec2 screen[] = { flb, brt, blb, frt, frb, brb, blt, flt };

		float left = flb[0];
		float top = flb[1];
		float right = flb[0];
		float bottom = flb[1];

		for (int i = 0; i < 8; i++)
		{
			if (left > screen[i][0])
				left = screen[i][0];
			if (top < screen[i][1])
				top = screen[i][1];
			if (right < screen[i][0])
				right = screen[i][0];
			if (bottom > screen[i][1])
				bottom = screen[i][1];
		}

		auto x = std::round(left);
		auto y = std::round(bottom);

		auto w = std::round(right - left);
		auto h = std::round(top - bottom);

		if (visual.m_box == 1) // normal
		{
			if (visual.m_outlined)
				DrawBorderBoxOut({ x, y }, { w, h }, 1.f, color);
			else
				DrawBorderBox({ x, y }, { w, h }, 1.f, color);
		}

		else if (visual.m_box == 2) // corner
		{
			auto line_w = std::round(w / 4.f);
			auto line_h = std::round(h / 4.f);

			if (visual.m_outlined)
			{
				renderer.DrawRect({ x - 1.f, y - 1.f }, { line_w + 2.f, 3.f }, { 0.f, 0.f, 0.f, 1.f });
				renderer.DrawRect({ x - 1.f, y - 1.f }, { 3.f, line_h + 2.f }, { 0.f, 0.f, 0.f, 1.f });

				renderer.DrawRect({ x - 1.f, y + h - line_h }, { 3.f, line_h + 2.f }, { 0.f, 0.f, 0.f, 1.f });
				renderer.DrawRect({ x - 1.f, y + h - 1.f }, { line_w + 2.f, 3.f }, { 0.f, 0.f, 0.f, 1.f });

				renderer.DrawRect({ x + w - line_w, y - 1.f }, { line_w + 2.f, 3.f }, { 0.f, 0.f, 0.f, 1.f });
				renderer.DrawRect({ x + w - 1.f, y - 1.f }, { 3.f, line_h + 2.f }, { 0.f, 0.f, 0.f, 1.f });

				renderer.DrawRect({ x + w - line_w, y + h - 1.f }, { line_w + 2.f, 3.f }, { 0.f, 0.f, 0.f, 1.f });
				renderer.DrawRect({ x + w - 1.f, y + h - line_h }, { 3.f, line_h + 2 }, { 0.f, 0.f, 0.f, 1.f });
			}

			renderer.DrawRect({ x, y }, { line_w, 1.f }, color);
			renderer.DrawRect({ x, y }, { 1.f, line_h }, color);

			renderer.DrawRect({ x, y + h - line_h + 1.f }, { 1.f, line_h }, color);
			renderer.DrawRect({ x, y + h }, { line_w, 1.f }, color);

			renderer.DrawRect({ x + w - line_w + 1.f, y }, { line_w, 1.f }, color);
			renderer.DrawRect({ x + w, y }, { 1.f, line_h }, color);

			renderer.DrawRect({ x + w - line_w + 1.f, y + h }, { line_w, 1.f }, color);
			renderer.DrawRect({ x + w, y + h - line_h + 1.f }, { 1.f, line_h }, color);
		}
		else if (visual.m_box == 3) // 3d
		{
			auto min = player->GetCollideable()->OBBMins() + player->m_vecOrigin();
			auto max = player->GetCollideable()->OBBMaxs() + player->m_vecOrigin();

			Vector points[] =
			{
				{ min[0], min[1], min[2] },
				{ min[0], max[1], min[2] },
				{ max[0], max[1], min[2] },
				{ max[0], min[1], min[2] },
				{ min[0], min[1], max[2] },
				{ min[0], max[1], max[2] },
				{ max[0], max[1], max[2] },
				{ max[0], min[1], max[2] },
			};

			int edges[12][2] =
			{
				{ 0, 1 },{ 1, 2 },
				{ 2, 3 },{ 3, 0 },
				{ 4, 5 },{ 5, 6 },
				{ 6, 7 },{ 7, 4 },
				{ 0, 4 },{ 1, 5 },
				{ 2, 6 },{ 3, 7 },
			};

			for (auto& edge : edges)
			{
				ImVec2 begin = { };
				ImVec2 end = { };

				if (WorldToScreen(points[edge[0]], begin))
				{
					if (WorldToScreen(points[edge[1]], end))
					{
						if (visual.m_outlined)
						{
							renderer.DrawLine({ begin[0] - 1.f, begin[1] }, end, { 0.f, 0.f, 0.f, 1.f });
							renderer.DrawLine({ begin[0] + 1.f, begin[1] }, end, { 0.f, 0.f, 0.f, 1.f });
						}

						renderer.DrawLine(begin, end, color);
					}
				}
			}
		}

		auto pad_h = 0.f;

		if (visual.m_name)
		{
			player_info_t info = { };

			if (m_engine_client->GetPlayerInfo(index, &info))
				renderer.DrawText({ x + w / 2.f, y - 16.f }, engine::TextCenterH, { 1.f, 1.f, 1.f, 1.f }, "%s", info.name);
		}

		if (visual.m_skeleton)
		{
			matrix3x4_t bone_data[128] = { };

			if (!player->GetBoneTransform(bone_data, m_globals->curtime))
				return;

			auto model = player->GetModel();

			if (model)
			{
				auto studio = m_model_info_client->GetStudioModel(model);

				if (studio)
				{
					for (auto i = 0; i < studio->numbones; i++)
					{
						auto bone = studio->pBone(i);

						if (!bone)
							continue;

						if (!(bone->flags & 0x0100))
							continue;

						if (bone->parent == -1)
							continue;

						Vector bone_world, parent_world;
						ImVec2 bone_screen, parent_screen;

						if (!player->GetBoneWorld(i, bone_data, bone_world))
							continue;

						if (!player->GetBoneWorld(bone->parent, bone_data, parent_world))
							continue;

						if (WorldToScreen(bone_world, bone_screen) && WorldToScreen(parent_world, parent_screen))
							renderer.DrawLine(bone_screen, parent_screen, { 1.f, 1.f, 1.f, 1.f });
					}
				}
			}
		}

		if (visual.m_weapon)
		{
			auto weapon = player->GetActiveWeapon();

			if (weapon)
			{
				auto name = weapon->GetCSWeaponData()->m_weapon_name + 7;

				if (name)
					renderer.DrawText({ x + w / 2.f, y + h + 2.f }, engine::TextCenterH, { 1.f, 1.f, 1.f, 1.f }, "%s", name);
			}
		}

		if (visual.m_spot)
		{
			//TODO
		}

		if (visual.m_backtrack)
		{
			//TODO
		}

		if (visual.m_health == 1) // Text
		{
			auto pad_w = 0.f;

			if (visual.m_armor == 2)
				pad_w += 5.f;

			renderer.DrawText({ x + w + 4.f + pad_w, y }, engine::TextLeft, { 1.f, 1.f, 1.f, 1.f }, "H: %i", player->m_iHealth());

			pad_h += 12.f;
		}
		else if (visual.m_health == 2) // Bar
		{
			auto health = static_cast<float>(player->m_iHealth());

			if (health > 100.f)
				health = 100.f;

			auto size_h = std::round(((h + 1.f) * health) / 100.f);
			auto real_h = (h + 1.f) - size_h;

			renderer.DrawRect({ x - 6.f, y - 1.f }, { 4.f, h + 3.f }, { 0.f, 0.f, 0.f, 0.65f });
			renderer.DrawRect({ x - 5.f, y + real_h }, { 2.f, size_h }, { 1.f - (health * 0.01f), health * 0.01f, 0.f, 1.f });
		}

		if (visual.m_armor == 1) // Text
		{
			renderer.DrawText({ x + w + 4.f, y + pad_h }, engine::TextLeft, { 1.f, 1.f, 1.f, 1.f }, "A: %i", player->m_ArmorValue());

			pad_h += 13.f;
		}
		else if (visual.m_armor == 2) // Bar
		{
			auto armor = static_cast<float>(player->m_ArmorValue());

			if (armor > 100)
				armor = 100;

			auto size_h = std::round(((h + 1.f) * armor) / 100.f);
			auto real_h = (h + 1.f) - size_h;

			renderer.DrawRect({ x + w + 3.f, y - 1.f }, { 4.f, h + 3.f }, { 0.f, 0.f, 0.f, 0.65f });
			renderer.DrawRect({ x + w + 4.f, y + real_h }, { 2.f, size_h }, { 0.7f, 0.7f, 0.7f, 1.f });
		}

		if (visual.m_defusing)
		{
			if (visual.m_name)
				y -= 16.f;

			if (player->m_bIsDefusing())
				renderer.DrawText({ x + w / 2.f, y - 16.f }, engine::TextCenterH, { 1.f, 0.1f, 0.1f, 1.f }, "defusing!");
		}
	}

	void Esp::PaintDrop(int index)
	{
		auto& renderer = engine::Renderer::Instance();
		auto& visual = option::m_visual;

		if (!visual.m_drop)
			return;

		auto ent = reinterpret_cast<C_CSPlayer*>(m_client_entity_list->GetClientEntity(index));

		if (!ent || ent->IsPlayer())
			return;

		const auto model = ent->GetModel();

		if (model)
		{
			auto model_name = m_model_info_client->GetModelName(model);

			if (model_name)
			{
				ImVec2 screen = { };
				ImColor color = { 1.f, 1.f, 1.f, 1.f };

				auto name = ""s;

				if (WorldToScreen(ent->m_vecOrigin(), screen))
				{
					if (visual.m_drop_weapons)
					{
						if (std::strstr(model_name, "models/weapons/w_eq_") == 0 && std::strstr(model_name, "models/weapons/w_ied") == 0)
						{
							if (strstr(model_name, "models/weapons/w_") && strstr(model_name, "_dropped.mdl"))
							{
								name = (model_name + 17u);

								name[name.size() - 12] = '\0';

								if (strstr(model_name, "models/weapons/w_pist_223") && strstr(model_name, "_dropped.mdl"))
									name = "usp";

								else if (strstr(model_name, "models/weapons/w_pist_cz_75") && strstr(model_name, "_dropped.mdl"))
									name = "cz75";

								else if (strstr(model_name, "models/weapons/w_pist_deagle") && strstr(model_name, "_dropped.mdl"))
									name = "deagle";

								else if (strstr(model_name, "models/weapons/w_pist_elite") && strstr(model_name, "_dropped.mdl"))
									name = "duals";

								else if (strstr(model_name, "models/weapons/w_pist_fiveseven") && strstr(model_name, "_dropped.mdl"))
									name = "fiveseven";

								else if (strstr(model_name, "models/weapons/w_pist_glock18") && strstr(model_name, "_dropped.mdl"))
									name = "glock18";

								else if (strstr(model_name, "models/weapons/w_pist_hkp2000") && strstr(model_name, "_dropped.mdl"))
									name = "p2000";

								else if (strstr(model_name, "models/weapons/w_pist_p250") && strstr(model_name, "_dropped.mdl"))
									name = "p250";

								else if (strstr(model_name, "models/weapons/w_pist_revolver") && strstr(model_name, "_dropped.mdl"))
									name = "r8";

								else if (strstr(model_name, "models/weapons/w_pist_tec9") && strstr(model_name, "_dropped.mdl"))
									name = "tec9";

								else if (strstr(model_name, "models/weapons/w_rif_aug") && strstr(model_name, "_dropped.mdl"))
									name = "aug";

								else if (strstr(model_name, "models/weapons/w_rif_ak47") && strstr(model_name, "_dropped.mdl"))
									name = "ak47";

								else if (strstr(model_name, "models/weapons/w_rif_famas") && strstr(model_name, "_dropped.mdl"))
									name = "famas";

								else if (strstr(model_name, "models/weapons/w_rif_galilar") && strstr(model_name, "_dropped.mdl"))
									name = "galil";

								else if (strstr(model_name, "models/weapons/w_rif_m4a1") && strstr(model_name, "_dropped.mdl"))
									name = "m4a4";

								else if (strstr(model_name, "models/weapons/w_rif_m4a1_s") && strstr(model_name, "_dropped.mdl"))
									name = "m4a1s";

								else if (strstr(model_name, "models/weapons/w_rif_sg556") && strstr(model_name, "_dropped.mdl"))
									name = "sg556";

								else if (strstr(model_name, "models/weapons/w_snip_awp") && strstr(model_name, "_dropped.mdl"))
									name = "awp";

								else if (strstr(model_name, "models/weapons/w_snip_g3sg1") && strstr(model_name, "_dropped.mdl"))
									name = "g3sg1";

								else if (strstr(model_name, "models/weapons/w_snip_scar20") && strstr(model_name, "_dropped.mdl"))
									name = "scar20";

								else if (strstr(model_name, "models/weapons/w_snip_ssg08") && strstr(model_name, "_dropped.mdl"))
									name = "ssg08";

								else if (strstr(model_name, "models/weapons/w_shot_mag7") && strstr(model_name, "_dropped.mdl"))
									name = "mag-7";

								else if (strstr(model_name, "models/weapons/w_shot_nova") && strstr(model_name, "_dropped.mdl"))
									name = "nova";

								else if (strstr(model_name, "models/weapons/w_shot_sawedoff") && strstr(model_name, "_dropped.mdl"))
									name = "sawed-off";

								else if (strstr(model_name, "models/weapons/w_shot_xm1014") && strstr(model_name, "_dropped.mdl"))
									name = "xm1014";

								else if (strstr(model_name, "models/weapons/w_smg_bizon") && strstr(model_name, "_dropped.mdl"))
									name = "bizon";

								else if (strstr(model_name, "models/weapons/w_smg_mac10") && strstr(model_name, "_dropped.mdl"))
									name = "mac10";

								else if (strstr(model_name, "models/weapons/w_smg_mp7") && strstr(model_name, "_dropped.mdl"))
									name = "mp7";

								else if (strstr(model_name, "models/weapons/w_smg_mp5sd") && strstr(model_name, "_dropped.mdl"))
									name = "mp5sd";

								else if (strstr(model_name, "models/weapons/w_smg_mp9") && strstr(model_name, "_dropped.mdl"))
									name = "mp9";

								else if (strstr(model_name, "models/weapons/w_smg_p90") && strstr(model_name, "_dropped.mdl"))
									name = "p90";

								else if (strstr(model_name, "models/weapons/w_smg_ump45") && strstr(model_name, "_dropped.mdl"))
									name = "ump45";

								else if (strstr(model_name, "models/weapons/w_mach_m249") && strstr(model_name, "_dropped.mdl"))
									name = "m249";

								else if (strstr(model_name, "models/weapons/w_mach_negev") && strstr(model_name, "_dropped.mdl"))
									name = "negev";
							}
						}
					}

					if (IsDangerZoneLoot(ent))
					{
						auto item = std::string(model_name);

						if (visual.m_drop_cases)
						{
							if (item.find("case_pistol") != std::string::npos)
							{
								name = "pistol case";
								color = { 255, 255, 153 };
							}

							else if (item.find("case_light_weapon") != std::string::npos)
							{
								name = "light case";
								color = { 255, 255, 153 };
							}

							else if (item.find("case_heavy_weapon") != std::string::npos)
							{
								name = "heavy case";
								color = { 255, 255, 153 };
							}

							else if (item.find("case_explosive") != std::string::npos)
							{
								name = "explosive case";
								color = { 255, 255, 153 };
							}

							else if (item.find("case_tools") != std::string::npos)
							{
								name = "tools case";
								color = { 255, 255, 153 };
							}

							else if (item.find("briefcase") != std::string::npos)
							{
								name = "brief case";
								color = { 255, 0, 64 };
							}
						}

						if (visual.m_drop_bags)
						{
							if (item.find("random") != std::string::npos)
							{
								name = "airdrop";
								color = { 153, 153, 255 };
							}
							else if (item.find("parachutepack") != std::string::npos)
							{
								name = "parachute";
								color = { 19, 236, 236 };
							}

							else if (item.find("dufflebag") != std::string::npos)
							{
								name = "duffle bag";
								color = { 19, 236, 236 };
							}
						}

						if (visual.m_drop_armor)
						{
							if (item.find("dz_armor_helmet") != std::string::npos)
							{
								name = "full armor";
								color = { 64, 191, 191 };
							}
							else if (item.find("dz_helmet") != std::string::npos)
							{
								name = "helmet";
								color = { 64, 191, 191 };
							}

							else if (item.find("dz_armor") != std::string::npos)
							{
								name = "armor";
								color = { 64, 191, 191 };
							}
						}

						if (visual.m_drop_medkit)
						{
							if (item.find("upgrade_tablet") != std::string::npos)
							{
								name = "medkit";
								color = { 0, 255, 64 };
							}
						}

						if (visual.m_drop_ammo)
						{
							if (item.find("ammobox") != std::string::npos)
							{
								name = "ammo";
								color = { 102, 153, 153 };
							}
						}
					}

					renderer.DrawText(screen, engine::TextLeft, color, "%s", name.data());
				}
			}
		}
	}

	void Esp::PaintGround(C_BaseEntity* ent)
	{
		auto& renderer = engine::Renderer::Instance();
		auto& visual = option::m_visual;

		if (ent->IsDormant())
			return;

		auto name = ent->GetClientClass()->m_pNetworkName;

		auto player = C_CSPlayer::GetLocalCSPlayer();

		auto world = ent->m_vecOrigin();

		if (world.IsZero())
			return;

		if (std::strcmp(name, "CPlantedC4") == 0)
		{
			ImVec2 screen = { };

			if (WorldToScreen(world, screen))
			{
				if (visual.m_bomb)
				{
					renderer.DrawText(screen, engine::TextLeft, { 1.f, 0.f, 0.f, 1.f }, "[ c4 ]");
				}

				if (visual.m_bomb_timer)
				{
					auto to_explosive = (ent->m_flC4Blow() - player->m_nTickBase() * m_globals->interval_per_tick);
					renderer.DrawText({ screen[0], screen[1] + 15.f }, engine::TextLeft, { 1.f, 0.5f, 0.f, 1.f }, "%.1f", to_explosive);
				}
			}
		}
	}

	bool Esp::IsDangerZoneLoot(C_CSPlayer* ent)
	{
		auto client_class = ent->GetClientClass();

		return (client_class->m_ClassID == CPhysPropAmmoBox ||
			client_class->m_ClassID == CPhysPropLootCrate ||
			client_class->m_ClassID == CPhysPropRadarJammer ||
			client_class->m_ClassID == CPhysPropWeaponUpgrade);
	}

	float Esp::ScaleDamage(float damage, int armor)
	{
		float ratio = 0.5f;
		float bonus = 0.5f;

		if (armor > 0)
		{
			float new_damage = damage * ratio;
			float new_armor = (damage - new_damage) * bonus;

			if (new_armor > static_cast<float>(armor))
			{
				new_armor = static_cast<float>(armor) * (1.0f / bonus);
				new_damage = damage - new_armor;
			}

			damage = new_damage;
		}

		return damage;
	}

	void Esp::Present()
	{
		auto player = C_CSPlayer::GetLocalCSPlayer();

		if (!player)
			return;

		auto size = m_client_entity_list->GetHighestEntityIndex();
		for (auto index = 1; index <= size; index++)
		{
			auto ent = C_CSPlayer::GetCSPlayer(index);

			if (!ent)
				continue;

			PaintGround(ent);
			PaintDrop(index);

			if (!ent->IsPlayer())
				continue;

			if (ent == player)
				continue;

			PaintEntity(index, ent);
		}
	}
}