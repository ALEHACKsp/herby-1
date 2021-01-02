#pragma once

#include "sdk/sdk.hpp"

namespace csgo::engine
{

class NetPropSystem : public detail::Singleton< NetPropSystem >
{
public:
	bool Create();
	void Destroy();

	int Get( const std::string& array_name, const std::string& prop_name, RecvProp** prop_out = nullptr) const;

private:
	int Get( RecvTable* recv_entry, const std::string& prop_name, RecvProp** prop_out = nullptr) const;

	RecvTable* GetArrayEntry( const std::string& array_name ) const;

private:
	std::vector< RecvTable* > m_recv_array = { };
};

}

#define NET_PROP( return_type, name, recv_table_name, recv_prop_name ) \
	return_type& name ## () const \
	{ \
		const auto& net_prop_system = csgo::engine::NetPropSystem::Instance(); \
		static auto displacement = 0; \
        if( !displacement ) \
             displacement = net_prop_system.Get(  XorStr(recv_table_name),  XorStr(recv_prop_name) ); \
		return *( return_type* )( this + displacement ); \
	}

#define NET_PROP_EX( return_type, name, recv_table_name, recv_prop_name, extra ) \
	return_type& name ## () const \
	{ \
		const auto& net_prop_system = csgo::engine::NetPropSystem::Instance(); \
		static auto displacement = 0; \
        if( !displacement ) \
             displacement = ( net_prop_system.Get(  XorStr(recv_table_name),  XorStr(recv_prop_name) ) + extra ); \
		return *( return_type* )( this + displacement ); \
	}
