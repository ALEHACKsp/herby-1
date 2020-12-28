#pragma once

#include <windows.h>

#include <string>
#include <vector>

#include "shared/imgui/imgui.hpp"
#include "shared/memory/procedure.hpp"

namespace shared::option
{
	struct VisualData
	{
		// core
		int m_box = 0;				    // 0 - 3 | off, normal, corners, 3d

		bool m_drop = false;            //
		bool m_drop_weapons = false;    //
		bool m_drop_cases = false;      //
		bool m_drop_medkit = false;     //
		bool m_drop_armor = false;      //
		bool m_drop_bags = false;       //
		bool m_drop_ammo = false;       //

		bool m_outlined = false;		//
		bool m_colored = false;         //

		bool m_spot = false;            //
		bool m_backtrack = false;       //
		bool m_fov = false;             //

		// target
		bool m_friendly = false;	    //
		bool m_visible_check = false;   //
		bool m_smoke_check = false;     //
		bool m_bomb = false;            //
		bool m_bomb_timer = false;      //

		// information
		bool m_name = false;			// 
		bool m_weapon = false;			// 
		bool m_skeleton = false;		// 
		bool m_defusing = false;		// 

		int m_health = 0;				// 0 - 2 | off, text, bar
		int m_armor = 0;				// 0 - 2 | off, text, bar

		static std::vector< std::string > m_box_mode_array;
		static std::vector< std::string > m_style_array;

		void Clamp()
		{
			memory::Clamp(&m_box, 0, 3);
			memory::Clamp(&m_health, 0, 2);
			memory::Clamp(&m_armor, 0, 2);
		}
	};

	struct ColorData
	{
		// main
		ImColor color_esp_ct_normal = { 0.f, 0.5f, 1.f, 1.f };
		ImColor	color_esp_t_normal = { 1.f, 0.f, 0.f, 1.f };
		ImColor color_esp_ct_colored = { 0, 237, 180, 255 };
		ImColor color_esp_t_colored = { 237, 200, 0, 255 };

		// reset
		ImColor color_esp_ct_normal_r = { 0.f, 0.5f, 1.f, 1.f };
		ImColor	color_esp_t_normal_r = { 1.f, 0.f, 0.f, 1.f };
		ImColor color_esp_ct_colored_r = { 0, 237, 180, 255 };
		ImColor color_esp_t_colored_r = { 237, 200, 0, 255 };
	};

	extern VisualData m_visual;
	extern ColorData m_colors;

	bool Create();
	void Destroy();

	void Load(const std::string& name);
	void Save(const std::string& name);
	void Delete(const std::string& name);
}