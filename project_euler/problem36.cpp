#include "euler.h"
#include "level2.h"
#include <bitset>

namespace {

bool is_palindrome( const std::string& s )
{
	return std::equal( s.begin(), s.end(), s.rbegin() );
}

bool is_palindrome( size_t i ) 
{ 
	return is_palindrome( std::to_string( i ) );
}

std::string base2( size_t i )
{
	std::bitset< 8 * sizeof( size_t ) > bits = i;
	const auto str = bits.to_string();
	const auto result = str.substr( str.find_first_not_of( '0' ) );
	return result;
}

bool is_double_base_palindrome( size_t i )
{
	return is_palindrome( i ) && is_palindrome( base2( i ) );
}


}

size_t euler::problem36()
{
	assert( base2( 585 ) == "1001001001" );
	assert( is_double_base_palindrome( 585 ) );
	return boost::accumulate( boost::irange( 1_u, 1e6_u ) | boost::adaptors::filtered( &is_double_base_palindrome ), 0_u );
}