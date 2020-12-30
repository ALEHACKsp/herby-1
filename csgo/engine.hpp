#pragma once

#include "sdk/sdk.hpp"

#include "csgo/engine/renderer.hpp"

#include "csgo/feature/triggerbot.hpp"
#include "csgo/feature/aimbot.hpp"
#include "csgo/feature/gui.hpp"
#include "csgo/feature/esp.hpp"

#include "csgo/hook/procedure.hpp"

namespace csgo
{

extern IBaseClientDLL* m_base_client;
extern IClientEntityList* m_client_entity_list;
extern IVEngineClient* m_engine_client;
extern IVModelInfoClient* m_model_info_client;
extern IEngineTrace* m_engine_trace;
extern ISurface* m_surface;
extern ICvar* m_cvar;
extern IMaterialSystem* m_material_system;
extern IVRenderView* m_render_view;
extern IVModelRender* m_model_render;
extern IGameEventManager* m_game_event_manager;
extern IGameUI* m_game_ui;
extern IGameMovement* m_game_movement;
extern IInputSystem* m_input_system;
extern ILocalize* m_localize;
extern IPhysicsSurfaceProps* m_physics_surface_props;

extern CGlobalVarsBase* m_globals;
extern IClientMode* m_client_mode;
extern IWeaponSystem* m_weapon_system;
extern C_GlowObjectManager* m_glow_object;
extern IMemAlloc* m_mem_alloc;

extern IDirect3DDevice9* m_direct_device;

extern memory::ObjectHook::Shared m_present_hook;
extern memory::ObjectHook::Shared m_reset_hook;

extern memory::ObjectHook::Shared m_frame_stage_notify_hook;
extern memory::ObjectHook::Shared m_create_move_hook;
extern memory::ObjectHook::Shared m_lock_cursor_hook;

bool Create();
void Destroy();

}