#pragma once

#include "sdk/sdk.hpp"

namespace csgo::engine
{

class Factory : public detail::Singleton< Factory >
{
	using factory_map_t = std::unordered_map< std::string, void* >;
public:
	Factory( const std::string& image_name );
public:
	template< typename T >
	inline T Get( const std::string& name )
	{
		auto factory = m_factory_map[name];
		return reinterpret_cast<T>(factory);
	}
private:
	void CreateFactoryMap();
private:
	HMODULE m_image = nullptr;
	InterfaceReg* m_interface_array = nullptr;
	factory_map_t m_factory_map = { };
};

}
