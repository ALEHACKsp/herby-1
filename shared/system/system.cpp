#include "shared/system/system.hpp"

#include "shared/auto.hpp"

namespace shared::win32
{

System::~System()
{
	Destroy();
}

bool System::Create()
{
	auto& input = win32::Input::Instance();

	if( !input.AddEvent( &MessageProcedure ) )
		return false;

	return true;
}

void System::Destroy()
{
	
}

const std::string& System::GetExecuteDirectory() const
{
	return m_execute_directory;
}

void System::SetExecuteDirectory(const std::string& execute_directory)
{
	m_execute_directory = execute_directory;
}

ExecuteState System::GetExecuteState() const
{
	return m_execute_state;
}

void System::SetExecuteState( const ExecuteState execute_state )
{
	m_execute_state = execute_state;
}

bool System::Gui() const
{
	return m_gui;
}

void System::Gui( bool value )
{
	m_gui = value;
}

bool System::Quit() const
{
	return m_quit;
}

void System::Quit(bool value)
{
	m_quit = value;
	m_gui = !value;
}

bool System::MessageProcedure( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
	auto& system = System::Instance();

	auto execute = false;

	switch( message )
	{
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		{
			if( wparam == VK_DELETE )
			{
				execute = true;
				system.Quit(true);
			}
			else if( wparam == VK_INSERT )
			{
				execute = true;
				system.Gui(!system.Gui());
			}

			break;
		}
	}

	return execute;
}

}