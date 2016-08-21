#include "euler.h"
#include "level2.h"
#include "cross_product_iterator.h"
#include "sorted_adaptor.h"

namespace {

std::vector< size_t > getDigitPowers( size_t power )
{
	// Given a number n with d digits
	// Maximum value of Sigma ai ^ power is d * 9 ^ power
	// Minimum value of n is 10 ^ ( d - 1 )
	// If power < 10 if d >= power + 1 with known for sure that Sigma ai ^ power < n so d <= power

	struct element { size_t n; size_t digitPowers; };
	std::vector< element > elements{ { 0, 0 } };
	for( auto i : boost::irange( 0_u, power + 1 ) )
	{
		typedef decltype( cross_product( elements, boost::irange( 0, 10 ) ) )::value_type valut_type;
		elements = cross_product( elements, boost::irange( 0, 10 ) )
			| boost::adaptors::transformed( [ i, power ]( const valut_type& v ) { return element{ std::get< 0 >( v ).n + static_cast< size_t >( std::pow( 10, i ) ) * std::get< 1 >( v ), std::get< 0 >( v ).digitPowers + static_cast< size_t >( std::pow( std::get< 1 >( v ), power ) ) }; } )
			| euler::to_vector;
	}

	return elements
		| boost::adaptors::filtered( []( const element& e ) { return e.n == e.digitPowers; } )
		| boost::adaptors::transformed( []( const element& e ) { return e.n; } )
		| euler::to_vector;
}

}

size_t euler::problem30()
{
	assert( ( getDigitPowers( 4_u ) | sorted() ) == std::vector< size_t >( { 0, 1, 1634, 8208, 9474 } ) );

	return boost::accumulate( getDigitPowers( 5 ), 0_u ) - 1;
}