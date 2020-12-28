#include "csgo/feature/gui.hpp"
#include "csgo/engine.hpp"

namespace csgo::feature
{

bool Gui::Create()
{
	auto& input = win32::Input::Instance();

	if( !input.AddEvent( &Gui::MessageProcedure ) )
		return false;

	auto& style = ImGui::GetStyle();

	ImGui::StyleColorsDark();

	style.WindowPadding = { 8.f, 8.f };
	style.WindowRounding = 0.f;
	style.WindowBorderSize = 0.f;
	style.ChildRounding = 0.f;
	style.ChildBorderSize = 1.f;
	style.PopupRounding = 0.f;
	style.PopupBorderSize = 0.f;
	style.FramePadding = { 4.f, 2.f };
	style.FrameRounding = 0.f;
	style.FrameBorderSize = 0.f;
	style.IndentSpacing = 20.f;
	style.ScrollbarSize = 14.f;
	style.ScrollbarRounding = 0.f;
	style.GrabMinSize = 10.f;
	style.GrabRounding = 0.f;

	CreateTab("aimbot", false);
	CreateTab("triggerbot", false);
	CreateTab("esp", false);
	CreateTab("removal", false);
	CreateTab("misc", false);
	CreateTab("config", false);

	return true;
}

void Gui::Destroy()
{

}

std::string get_extension(const std::string& data)
{
	auto dot = data.find_last_of('.');

	std::string extension = { };

	if (dot != std::string::npos)
		extension = data.substr(dot + 1u, data.size());

	return extension;
}

void Gui::Present()
{
	auto& system = win32::System::Instance();

	if (m_render_mouse != system.Gui())
		m_render_mouse = system.Gui();

	auto& io = ImGui::GetIO();
	io.MouseDrawCursor = m_render_mouse;

	if( !system.Gui() )
		return;

	auto render_style = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;

	auto frame_height = 0.f;

	D3DVIEWPORT9 viewport = { };
	if (SUCCEEDED(csgo::m_direct_device->GetViewport(&viewport)))
		frame_height = static_cast<float>(viewport.Height);

	auto frame_pos = ImVec2{ 0.f, 0.f };
	auto frame_size = ImVec2{ 156.f, frame_height };

	ImGui::SetNextWindowPos(frame_pos, ImGuiCond_Always);
	ImGui::SetNextWindowSize(frame_size, ImGuiCond_Always);

	auto frame_render_style = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse;

	if (ImGui::Begin("frame", nullptr, frame_render_style))
	{
		auto& gui_style = ImGui::GetStyle();

		auto tab_size = ImVec2{ 140.f, 30.f };
		auto tab_array_size = ((30.f * (static_cast<float>(m_tab_array.size()) + gui_style.ItemSpacing.y)) - gui_style.ItemSpacing.y) * 0.5f;

		auto frame_tab_center_y = frame_height * 0.5f;
		auto frame_tab_start_y = (frame_tab_center_y - tab_array_size) * 0.5f;

		ImGui::Dummy({ 0.f, frame_tab_start_y });
		ImGui::Dummy({ 0.f, 0.f });

		auto frame_name = "herby"s;
		auto frame_name_size = ImGui::CalcTextSize(frame_name.c_str(), nullptr, true);

		ImGui::SameLine(0.f, (frame_size.x * 0.5f) - (frame_name_size.x * 0.5f) - gui_style.ItemSpacing.x);
		ImGui::Text(frame_name.c_str());
		ImGui::Dummy({ 0.f, frame_tab_start_y });

		ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, { 0.f, 0.5f });
		ImGui::PushStyleColor(ImGuiCol_Text, { 1.f, 1.f, 1.f, 1.f });
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.1f, 0.1f, 0.1f, 1.f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.12f, 0.12f, 0.12f, 1.f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.15f, 0.15f, 0.15f, 1.f });

		for (auto& tab : m_tab_array)
		{
			if (ImGui::Button(tab.m_name.c_str(), tab_size))
				tab.m_render = !tab.m_render;
		}

		ImGui::PopStyleColor(4);
		ImGui::PopStyleVar(1);
	}
	ImGui::End();

	if (m_tab_array.at(tab_aimbot).m_render)
	{

	}
	if (m_tab_array.at(tab_triggerbot).m_render)
	{

	}
	if (m_tab_array.at(tab_esp).m_render)
	{
		if (ImGui::Begin("esp", nullptr, render_style))
		{
			auto& style = ImGui::GetStyle();
			auto& esp = option::m_visual;

			ImGui::Dummy({ 140.f, 0.f });

			ImGui::PushItemWidth(160.f);
			if (ImGui::CollapsingHeader("core"))
			{
				ImGui::Combo("box", &esp.m_box, esp.m_box_mode_array);

				if (esp.m_box)
				{
					ImGui::Checkbox("outline", &esp.m_outlined);
					ImGui::Checkbox("colored", &esp.m_colored);
				}
			}

			if (ImGui::CollapsingHeader("information"))
			{
				ImGui::Combo("health", &esp.m_health, esp.m_style_array);
				ImGui::Combo("armor", &esp.m_armor, esp.m_style_array);
				ImGui::Checkbox("name", &esp.m_name);
				ImGui::Checkbox("skeleton", &esp.m_skeleton);
				ImGui::Checkbox("weapon", &esp.m_weapon);
				ImGui::Checkbox("defusing", &esp.m_defusing);
				ImGui::Checkbox("aim spot", &esp.m_spot);
				ImGui::Checkbox("aim fov", &esp.m_fov);
				ImGui::Checkbox("bactrack", &esp.m_backtrack);
				ImGui::Checkbox("c4", &esp.m_bomb);
				ImGui::Checkbox("c4 timer", &esp.m_bomb_timer);
				ImGui::Checkbox("drop", &esp.m_drop);

				if (esp.m_drop)
				{
					ImGui::ListBoxHeader("");
					ImGui::Selectable("weapons", &esp.m_drop_weapons);
					ImGui::Selectable("ammo", &esp.m_drop_ammo);
					ImGui::Selectable("armor", &esp.m_drop_armor);
					ImGui::Selectable("medkit", &esp.m_drop_medkit);
					ImGui::Selectable("bags", &esp.m_drop_bags);
					ImGui::Selectable("cases", &esp.m_drop_cases);
					ImGui::ListBoxFooter();
				}
			}

			if (ImGui::CollapsingHeader("target"))
			{
				ImGui::Checkbox("smoke check", &esp.m_smoke_check);
				ImGui::Checkbox("visible check", &esp.m_visible_check);
				ImGui::Checkbox("friendly", &esp.m_friendly);
			}
			ImGui::PopItemWidth();
		}
		ImGui::End();
	}
	if (m_tab_array.at(tab_removal).m_render)
	{

	}
	if (m_tab_array.at(tab_misc).m_render)
	{

	}
	if (m_tab_array.at(tab_config).m_render)
	{
		if (ImGui::Begin("config", nullptr, render_style))
		{
			ImGui::ListBoxHeader("");

			WIN32_FIND_DATAA search_data = { };
			LARGE_INTEGER search_data_size = { };

			auto directory = std::string(core::m_data.m_loader_directory);
			directory.append("\\csgo\\*");

			auto search_object = FindFirstFileA(directory.c_str(), &search_data);

			std::vector< std::string > search_data_array = { };
			if (search_object != INVALID_HANDLE_VALUE)
			{
				auto search_index = 0;

				do
				{
					auto extension = get_extension(search_data.cFileName);

					if (!(search_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !extension.compare("ini"))
					{
						const auto is_selected = (search_index == m_directory);

						search_data_size.LowPart = search_data.nFileSizeLow;
						search_data_size.HighPart = search_data.nFileSizeHigh;

						char search_data_name[MAX_PATH] = { };
						sprintf_s(search_data_name, "%s [%lld bytes]", search_data.cFileName, search_data_size.QuadPart);

						ImGui::PushID(search_index);
						if (ImGui::Selectable(search_data_name, is_selected))
						{
							m_directory = search_index;
							strncpy_s(m_directory_input, search_data.cFileName, sizeof(m_directory_input));
						}
						ImGui::PopID();

						search_index++;
						search_data_array.emplace_back(search_data.cFileName);
					}
				}
				while (FindNextFileA(search_object, &search_data));

				FindClose(search_object);
			}
			ImGui::ListBoxFooter();

			ImGui::InputText("", m_directory_input, sizeof(m_directory_input));

			if (ImGui::Button("load") && m_directory != -1)
			{
				system.SetExecuteDirectory(search_data_array[m_directory]);
				system.SetExecuteState(win32::Load);
			}

			ImGui::SameLine();

			if (ImGui::Button("save") && std::strlen(m_directory_input))
			{
				system.SetExecuteDirectory(m_directory_input);
				system.SetExecuteState(win32::Save);
			}

			ImGui::SameLine();

			if (ImGui::Button("delete"))
				ImGui::OpenPopup("delete?");

			if (ImGui::BeginPopupModal("delete?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
			{
				ImGui::Text("you are going to delete \"%s\"!\nare you sure?\n\n", m_directory_input);
				ImGui::Separator();

				if (ImGui::Button("yes", { 120.f, 0.f }))
				{
					option::Delete(m_directory_input);
					ImGui::CloseCurrentPopup();
				}

				ImGui::SameLine();

				if (ImGui::Button("no", { 120.f, 0.f }))
					ImGui::CloseCurrentPopup();

				ImGui::EndPopup();
			}
		}

		ImGui::End();
	}
}

void Gui::CreateTab(const std::string& name, bool selected /*= false*/)
{
	auto index = static_cast<int>(m_tab_array.size());
	m_tab_array.emplace_back(selected, index, name);
}

bool Gui::MessageProcedure( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
	auto& system = win32::System::Instance();

	if (!system.Gui())
		return false;

	return !!ImGui_ImplWin32_WndProcHandler(window, message, wparam, lparam);
}

}