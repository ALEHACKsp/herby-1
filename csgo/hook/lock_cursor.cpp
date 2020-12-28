#include "csgo/hook/procedure.hpp"

#include "csgo/engine.hpp"

namespace csgo::hook
{
	VOID API_STDCALL LockCursor()
	{
		auto& system = win32::System::Instance();

		if (system.Gui())
		{
			m_surface->UnlockCursor();
			return;
		}
		
		m_lock_cursor_hook->Restore();
		m_lock_cursor_hook->Win32Call< VOID >(m_surface);
		m_lock_cursor_hook->Replace();
	}
}