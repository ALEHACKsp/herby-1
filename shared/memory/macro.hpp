#pragma once

#define CONCATENATE_DETAIL( left, right ) left ## right
#define CONCATENATE( left, right ) CONCATENATE_DETAIL( left, right )

#define PAD( size ) \
	private: \
		std::uint8_t CONCATENATE( __pad, __COUNTER__ )[ size ] = { }; \
	public:

#ifdef NDEBUG
#define d_print( data )
#define d_print_value( data )
#else
#define d_print( data ) MessageBoxA( GetActiveWindow(), std::string( data ).c_str(), "", 0u )
#define d_print_value( data ) MessageBoxA( GetActiveWindow(), std::to_string( ( unsigned long )data ).c_str(), "", 0u )
#endif

