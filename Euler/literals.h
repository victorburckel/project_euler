#pragma once

inline size_t operator "" _u( unsigned long long int v ) { return static_cast< size_t >( v ); }
inline size_t operator "" _u( long double v ) { return static_cast< size_t >( v ); }