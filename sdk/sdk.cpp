#include "sdk/sdk.hpp"

#include "csgo/engine.hpp"

KeyValues::KeyValues(const char* setName)
{
	using Fn = void(__thiscall*)(void*, const char*);
	static auto procedure = memory::scan<Fn>("client.dll", "8B 0E 33 4D FC 81 E1 ? ? ? ? 31 0E 88 46 03 C1 F8 08 66 89 46 12 8B C6", -0x0045);
	procedure(this, setName);
}

bool KeyValues::LoadBuffer(const char* resourceName, const char* pBuffer, void* pSomething /*= nullptr*/, void* pAnother /*= nullptr*/, void* pLast /*= nullptr*/)
{
	using Fn = bool(__thiscall*)(KeyValues*, const char*, const char*, void*, void*, void*);
	static auto procedure = memory::scan<Fn>("client.dll", "55 8B EC 83 E4 F8 83 EC 34 53 8B 5D 0C 89");
	return procedure(this, resourceName, pBuffer, pSomething, pAnother, pLast);
}

bool WorldToScreen( const Vector& world, ImVec2& screen )
{
	auto mat = csgo::m_engine_client->WorldToScreenMatrix();

	auto z = mat[ 3 ][ 0 ] * world[ 0 ] + mat[ 3 ][ 1 ] * world[ 1 ] + mat[ 3 ][ 2 ] * world[ 2 ] + mat[ 3 ][ 3 ];

	if( z < 0.01f )
		return false;

	auto inverse = 1.f / z;

	screen[ 0 ] = ( mat[ 0 ][ 0 ] * world[ 0 ] + mat[ 0 ][ 1 ] * world[ 1 ] + mat[ 0 ][ 2 ] * world[ 2 ] + mat[ 0 ][ 3 ] ) * inverse;
	screen[ 1 ] = ( mat[ 1 ][ 0 ] * world[ 0 ] + mat[ 1 ][ 1 ] * world[ 1 ] + mat[ 1 ][ 2 ] * world[ 2 ] + mat[ 1 ][ 3 ] ) * inverse;

	auto w = 0, h = 0;
	csgo::m_engine_client->GetScreenSize(w, h);

	auto x = static_cast< float >( w ) / 2.f;
	auto y = static_cast< float >( h ) / 2.f;

	x += 0.5f * screen[ 0 ] * static_cast< float >( w ) + 0.5f;
	y -= 0.5f * screen[ 1 ] * static_cast< float >( h ) + 0.5f;

	screen[ 0 ] = x;
	screen[ 1 ] = y;

	return true;
}

bool SmokeTraceLine(Vector start, Vector end)
{
	using Fn = bool(__cdecl*) (Vector, Vector);
	static auto procedure = memory::scan<Fn>("client.dll", "55 8B EC 83 EC 08 8B 15 ? ? ? ? 0F 57 C0");
	return procedure(start, end);
}