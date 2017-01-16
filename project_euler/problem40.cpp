#include "euler.h"
#include "level2.h"
#include <boost/range/algorithm/lower_bound.hpp>

namespace {

int get_digit( int digit, const std::vector< int >& sizes )
{
	const auto bucket = --boost::lower_bound( sizes, digit + 1 );
	const auto distance = digit - *bucket;
	const auto numberSize = std::distance( sizes.begin(), bucket ) + 1;

	const auto whichNumber = distance / numberSize;
	const auto whichDigitInNumber = numberSize - 1 - distance % numberSize;

	return static_cast< int >( ( whichNumber % static_cast< int >( std::pow( 10, whichDigitInNumber + 1 ) ) ) / std::pow( 10, whichDigitInNumber ) ) + ( whichDigitInNumber == numberSize - 1 ? 1 : 0 );
}

}

size_t euler::problem40()
{
	std::vector< int > sizes( 1, 0 );
	for( auto i : boost::irange( 0, 7 ) )
		sizes.push_back( ( std::pow( 10, i + 1 ) - std::pow( 10, i ) ) * ( i + 1 ) + sizes.back() );

	assert( sizes.back() >= 1000000 );

	using namespace std::string_literals;
	const auto str = "123456789101112131415161718192021"s;
	for( auto n : boost::irange( 0, static_cast< int >( str.size() ) ) )
		assert( get_digit( n, sizes ) == str[ n ] - '0' );

	using namespace boost::adaptors;
	const auto values = boost::irange( 0, 7 ) | transformed( []( int p ) { return static_cast< int >( std::pow( 10, p ) ); } ) | transformed( [ &sizes ]( int digit ) { return get_digit( digit - 1, sizes ); } ) | to_vector;
	return boost::accumulate( values, 1, []( int total, int value ) { return total * value; } );
}