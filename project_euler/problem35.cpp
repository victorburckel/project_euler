#include "euler.h"
#include "level2.h"
#include "primes.h"
#include <boost/range/size.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/range/algorithm/lower_bound.hpp>
#include <set>

namespace {

bool isCircularPrime( size_t prime, const std::set< size_t >& primes )
{
	auto str = std::to_string( prime );
	for( auto i : boost::irange( 0_u, str.size() - 1 ) )
	{
		( void ) i;
		std::rotate( str.begin(), std::next( str.begin() ), str.end() );
		if( primes.find( boost::lexical_cast< size_t >( str ) ) == primes.end() )
			return false;
	}

	return true;
}

}

size_t euler::problem35()
{
	const auto limit = 1e6_u;
	std::set< size_t > primes;
	generate_primes( [ limit, &primes ]( size_t prime ) { if( prime < limit ) primes.insert( prime ); }, limit, { 2, 3 } );

	assert( isCircularPrime( 197, primes ) );
	assert( boost::size( boost::make_iterator_range( primes.begin(), boost::lower_bound( primes, 1e2_u ) ) | boost::adaptors::filtered( [ &primes ]( size_t prime ) { return isCircularPrime( prime, primes ); } ) ) + 2 == 13 );
	return boost::size( primes | boost::adaptors::filtered( [ &primes ]( size_t prime ) { return isCircularPrime( prime, primes ); } ) ) + 2;
}