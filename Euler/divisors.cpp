#include "divisors.h"
#include "literals.h"
#include <boost/math/special_functions/prime.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <boost/range/numeric.hpp>
#include <boost/range/irange.hpp>

namespace {

struct prime_factor
{
	unsigned prime;
	unsigned factor;
};

std::vector< prime_factor > getPrimeFactors( size_t n )
{
	std::vector< prime_factor > result;
	for( unsigned count = 0u, prime = boost::math::prime( count ); prime <= n; prime = boost::math::prime( ++count ) )
	{
		unsigned pow = 0u;
		while( n % prime == 0u )
		{
			n /= prime;
			++pow;
		}

		if( pow )
			result.push_back( { prime, pow } );
	}

	return result;
}

size_t sigma( prime_factor factor )
{
	return ( static_cast< size_t >( std::pow( factor.prime, factor.factor + 1 ) ) - 1 ) / ( factor.prime - 1 );
}

}

size_t euler::getSumOfProperDivisorsAlt( size_t n )
{
	const auto factors = getPrimeFactors( n );
	return boost::accumulate( factors, 1_u, []( size_t total, const prime_factor& factor ) { return total * sigma( factor ); } ) - n;
}

std::vector< size_t > euler::getDivisors( size_t n )
{
	const auto factors = getPrimeFactors( n );

	const auto size = boost::accumulate( factors, 1_u, []( size_t total, const prime_factor& factor ) { return total * ( factor.factor + 1 ); } );
	std::vector< size_t > result;
	result.reserve( size - 1 );

	result.push_back( 1_u );
	for( const auto& factor : factors )
	{
		const auto current = result.size();
		auto divisor = 1u;
		for( auto i : boost::irange( 0u, factor.factor ) )
		{
			( void ) i;
			divisor *= factor.prime;
			boost::transform( boost::make_iterator_range( result.begin(), std::next( result.begin(), current ) ), std::back_inserter( result ), [ divisor ]( size_t p ) { return p * divisor; } );
		}
	}

	return result;
}

std::vector< size_t > euler::getProperDivisors( size_t n )
{
	auto result = getDivisors( n );
	result.pop_back();
	return result;
}

size_t euler::getSumOfProperDivisors( size_t n )
{
	return boost::accumulate( getProperDivisors( n ), 0_u );
}
