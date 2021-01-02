#pragma once

#include "shared/include/auto.hpp"

#include "shared/detail/singleton.hpp"
#include "shared/hash/xorstr.hpp"

namespace shared::win32
{

enum ExecuteState
{
	None,
	Load,
	Save
};

class System : public detail::Singleton< System >
{
public:
	~System();

public:
	bool Create();
	void Destroy();

	const std::string& GetExecuteDirectory() const;
	void SetExecuteDirectory(const std::string& execute_directory);

	ExecuteState GetExecuteState() const;
	void SetExecuteState( const ExecuteState execute_state );

public:
	bool Gui() const;
	void Gui( bool value );

	bool Quit() const;
	void Quit(bool value);

private:
	static bool MessageProcedure( HWND window, UINT message, WPARAM wparam, LPARAM lparam );
private:
	bool m_quit = false;
	bool m_gui = false;

	std::string m_execute_directory = { "configs" };
	ExecuteState m_execute_state;
};

}