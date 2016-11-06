#include "euler.h"
#include "level2.h"
#include "divisors.h"
#include "cross_product_iterator.h"
#include "sorted_adaptor.h"
#include <boost/range/adaptor/uniqued.hpp>

namespace {

size_t getDistinctPowers( unsigned max )
{
	const auto range = boost::irange( 2u, max + 1 );
	const auto factors = range | boost::adaptors::transformed( &euler::getPrimeFactors );

	typedef decltype( cross_product( factors, range ) )::value_type element_t;
	const auto poweredFactors = cross_product( factors, range )
		| boost::adaptors::transformed( []( const element_t& element ) { return std::get< 0 >( element ) | boost::adaptors::transformed( [ power = std::get< 1 >( element ) ]( const euler::prime_factor& f ) { return euler::prime_factor{ f.prime, f.factor * power };  } ) | euler::to_vector; } )
		| euler::sorted()
		| boost::adaptors::uniqued
		| euler::to_vector;

	return poweredFactors.size();
}

}

size_t euler::problem29()
{
	assert( getDistinctPowers( 5 ) == 15 );
	return getDistinctPowers( 100 );
}