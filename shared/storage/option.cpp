#include "shared/storage/option.hpp"
#include "shared/include/auto.hpp"
#include "shared/system/system.hpp"
#include "shared/core/data.hpp"

namespace shared::option
{
	VisualData m_visual = { };
	ColorData m_colors = { };

	std::string m_directory = { };
	std::string m_directory_current = { };

	bool Create()
	{
		auto& system = win32::System::Instance();

		m_directory = core::m_data.m_loader_directory;
		m_directory.append("\\csgo\\");

		system.SetExecuteDirectory("configs");
		system.SetExecuteState(win32::Load);

		return true;
	}

	void Destroy()
	{

	}

	bool get_bool(const std::string& app_name, const std::string& key_name)
	{
		char key_data[128] = { };
		GetPrivateProfileStringA(app_name.c_str(), key_name.c_str(), "false", key_data, 128, m_directory.c_str());

		auto data = std::string(key_data);

		return (!data.compare("true") ||
			!data.compare("on") ||
			!data.compare("1"));
	}

	int get_int(const std::string& app_name, const std::string& key_name)
	{
		char result[128] = { };
		GetPrivateProfileStringA(app_name.c_str(), key_name.c_str(), "0", result, 128, m_directory.c_str());

		auto data = std::string(result);
		return (data.empty() ? 0 : std::stoi(data));
	}

	float get_float(const std::string& app_name, const std::string& key_name)
	{
		char key_data[128] = { };
		GetPrivateProfileStringA(app_name.c_str(), key_name.c_str(), "0.0000", key_data, 128, m_directory.c_str());

		auto data = std::string(key_data);

		return (data.empty() ? 0.f : std::stof(data));
	}

	ImColor get_color(const std::string& app_name, const std::string& key_name)
	{
		char key_data[128] = { };
		GetPrivateProfileStringA(app_name.c_str(), key_name.c_str(), "0.0.0.0", key_data, 128, m_directory.c_str());

		auto data = std::string(key_data);

		return (data.empty() ? 0.f : std::stof(data));
	}

	void set_bool(const std::string& app_name, const std::string& key_name, bool value)
	{
		char key_data[128] = { };
		sprintf_s(key_data, "%s", value ? "true" : "false");

		WritePrivateProfileStringA(app_name.c_str(), key_name.c_str(), key_data, m_directory.c_str());
	}

	void set_int(const std::string& app_name, const std::string& key_name, int value)
	{
		char key_data[128] = { };
		sprintf_s(key_data, "%i", value);

		WritePrivateProfileStringA(app_name.c_str(), key_name.c_str(), key_data, m_directory.c_str());
	}

	void set_float(const std::string& app_name, const std::string& key_name, float value)
	{
		char key_data[128] = { };
		sprintf_s(key_data, "%f", value);

		WritePrivateProfileStringA(app_name.c_str(), key_name.c_str(), key_data, m_directory.c_str());
	}

	void set_color(const std::string& app_name, const std::string& key_name, ImColor value)
	{
		char key_data[128] = { };
		sprintf_s(key_data, "%f", value.Value.x);
		sprintf_s(key_data, "%f", value.Value.y);
		sprintf_s(key_data, "%f", value.Value.z);
		sprintf_s(key_data, "%f", value.Value.w);

		WritePrivateProfileStringA(app_name.c_str(), key_name.c_str(), key_data, m_directory.c_str());
	}

	bool IsGood(const std::string& name)
	{
		std::ifstream stream(name);
		return stream.good();
	}

	bool Create(const std::string& name)
	{
		auto directory = name.substr(0u, name.find_last_of('\\'));

		if (CreateDirectoryA(directory.c_str(), nullptr) || GetLastError() == ERROR_ALREADY_EXISTS)
		{
			std::ofstream stream(name);
			return stream.good();
		}
		
		return false;
	}

	void Load(const std::string& name)
	{
		auto& system = win32::System::Instance();

		auto current = name;

		if (current.find(".ini") == std::string::npos)
			current.append(".ini");

		m_directory_current = m_directory + current;

		if (!IsGood(m_directory_current))
			Save(name);

		auto app_name = "esp"s;

		m_visual.m_box = get_int(app_name, "esp.box");
		m_visual.m_outlined = get_bool(app_name, "esp.outline");
		m_visual.m_colored = get_bool(app_name, "esp.colored");
		m_visual.m_health = get_int(app_name, "esp.health");
		m_visual.m_armor = get_int(app_name, "esp.armor");
		m_visual.m_weapon = get_bool(app_name, "esp.weapon");
		m_visual.m_name = get_bool(app_name, "esp.name");
		m_visual.m_backtrack = get_bool(app_name, "esp.backtrack");
		m_visual.m_fov = get_bool(app_name, "esp.fov");
		m_visual.m_spot = get_bool(app_name, "esp.spot");
		m_visual.m_bomb = get_bool(app_name, "esp.bomb");
		m_visual.m_bomb_timer = get_bool(app_name, "esp.timer");
		m_visual.m_defusing = get_bool(app_name, "esp.defusing");
		m_visual.m_friendly = get_bool(app_name, "esp.friendly");

		m_visual.Clamp();

		app_name = "colors"s;

		m_colors.color_esp_ct_colored = get_color(app_name, "color.esp.ct.colored");
		m_colors.color_esp_ct_colored_r = get_color(app_name, "color.esp.ct.colored.reset");
		m_colors.color_esp_ct_normal = get_color(app_name, "color.esp.ct.normal");
		m_colors.color_esp_ct_normal_r = get_color(app_name, "color.esp.ct.normal.reset");
		m_colors.color_esp_t_colored = get_color(app_name, "color.esp.t.colored");
		m_colors.color_esp_t_colored_r = get_color(app_name, "color.esp.t.colored.reset");
		m_colors.color_esp_t_normal = get_color(app_name, "color.esp.t.colored.normal");
		m_colors.color_esp_t_normal_r = get_color(app_name, "color.esp.t.colored.normal.reset");

		system.SetExecuteState(win32::None);

	}

	void Save(const std::string& name)
	{
		auto& system = win32::System::Instance();

		auto current = name;

		if (current.find(".ini") == std::string::npos)
			current.append(".ini");

		m_directory_current = m_directory + current;

		if (!IsGood(m_directory_current))
			Create(m_directory_current);

		auto app_name = "esp"s;

		m_visual.Clamp();
		set_int(app_name, "esp.box", m_visual.m_box);
		set_bool(app_name, "esp.outline", m_visual.m_outlined);
		set_bool(app_name, "esp.colored", m_visual.m_colored);
		set_int(app_name, "esp.health", m_visual.m_health);
		set_int(app_name, "esp.armor", m_visual.m_armor);
		set_bool(app_name, "esp.weapon", m_visual.m_weapon);
		set_bool(app_name, "esp.name", m_visual.m_name);
		set_bool(app_name, "esp.backtrack", m_visual.m_backtrack);
		set_bool(app_name, "esp.fov", m_visual.m_fov);
		set_bool(app_name, "esp.spot", m_visual.m_spot);
		set_bool(app_name, "esp.bomb", m_visual.m_bomb);
		set_bool(app_name, "esp.timer", m_visual.m_bomb_timer);
		set_bool(app_name, "esp.defusing", m_visual.m_defusing);
		set_bool(app_name, "esp.friendly", m_visual.m_friendly);

		app_name = "colors"s;
		set_color(app_name, "color.esp.ct.colored", m_colors.color_esp_ct_colored);
		set_color(app_name, "color.esp.ct.colored.reset", m_colors.color_esp_ct_colored_r);
		set_color(app_name, "color.esp.ct.normal", m_colors.color_esp_ct_normal);
		set_color(app_name, "color.esp.ct.normal.reset", m_colors.color_esp_ct_normal_r);
		set_color(app_name, "color.esp.t.colored", m_colors.color_esp_t_colored);
		set_color(app_name, "color.esp.t.colored.reset", m_colors.color_esp_t_colored_r);
		set_color(app_name, "color.esp.t.normal", m_colors.color_esp_t_normal);
		set_color(app_name, "color.esp.t.normal.reset", m_colors.color_esp_t_normal_r);

		system.SetExecuteState(win32::None);
	}

	void Delete(const std::string& name)
	{
		auto current = name;

		if (current.find(".ini") == std::string::npos)
			current.append(".ini");

		m_directory_current = m_directory + current;

		DeleteFileA(m_directory_current.c_str());
	}

	std::vector< std::string > VisualData::m_box_mode_array =
	{
		"off",
		"normal",
		"corners",
		"3d"
	};

	std::vector< std::string > VisualData::m_style_array =
	{
		"off",
		"text",
		"bar",
	};
}