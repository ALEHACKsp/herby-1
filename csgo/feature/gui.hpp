#pragma once

#include "csgo/engine/renderer.hpp"

namespace csgo::feature
{
enum gui_tab
{
	tab_aimbot,
	tab_triggerbot,
	tab_esp,
	tab_removal,
	tab_misc,
	tab_config,
};

struct gui_tab_t
{
	bool m_render = false;
	int m_index = -1;
	std::string m_name = { };

	gui_tab_t() = default;

	gui_tab_t(bool render, int index, const std::string & name)
		: m_render(render)
		, m_index(index)
		, m_name(name)
	{ }
};

class Gui : public detail::Singleton< Gui >
{
public:
	bool Create();
	void Destroy();
	
	void Present();

	void CreateTab(const std::string& name, bool render = false);

public:
	static bool MessageProcedure( HWND window, UINT message, WPARAM wparam, LPARAM lparam );
private:
	bool m_render_mouse = false;
	std::vector< gui_tab_t > m_tab_array = { };
	int m_directory = -1;
	char m_directory_input[MAX_PATH] = { };
};

}