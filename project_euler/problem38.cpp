#include "euler.h"
#include "level2.h"

namespace {

std::string concatenated_product( int number, int n )
{
	std::ostringstream str;
	for( auto i : boost::irange( 1, n + 1 ) )
		str << i * number;

	return str.str();
}

boost::optional< int > get_pandigital_concatenated_product( int number, int n )
{
	static const auto range = boost::irange( '1', static_cast< char >( '9' + 1 ) );
	auto result = concatenated_product( number, n );

	if( result.size() == range.size() && std::is_permutation( result.begin(), result.end(), range.begin() ) )
		return boost::lexical_cast< int >( result );

	return boost::none;
}

}

size_t euler::problem38()
{
	assert( get_pandigital_concatenated_product( 192, 3 ) == 192384576 );
	assert( get_pandigital_concatenated_product( 9, 5 ) == 918273645 );

	int result = 0;
	for( auto n : boost::irange( 2, 4 ) )
	{
		for( auto number : boost::irange( 1, static_cast< int >( std::pow( 10, 9 / n ) ) ) )
		{
			if( const auto r = get_pandigital_concatenated_product( number, n ) )
				result = std::max( result, *r );
		}
	}

	return result;
}