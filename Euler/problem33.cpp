#include "euler.h"
#include "level2.h"
#include "combinations.h"
#include "vector_adaptor.h"
#include "cross_product_iterator.h"
#include <boost/range/combine.hpp>
#include <boost/range/adaptor/reversed.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/algorithm/set_algorithm.hpp>
#include <boost/range/size.hpp>
#include <boost/math/common_factor_rt.hpp>
#include <algorithm>
#include <set>

namespace {

template< typename Range >
int compute( const Range& values )
{
	int power = 0;
	return boost::accumulate( values | boost::adaptors::reversed, 0, [ &power ]( int total, int digit ) { return total + static_cast< int >( std::pow( 10, power++ ) ) * digit; } );
}

bool isDigitCancellingFraction( std::vector< int > numerator, std::vector< int > denominator )
{
	const auto num = compute( numerator );
	const auto den = compute( denominator );

	for( auto itNumerator = numerator.begin(); itNumerator != numerator.end(); ++itNumerator )
	{
		const auto findNext = [ end = denominator.end(), value = *itNumerator ]( auto it ) { return std::find( it, end, value ); };
		for( auto itDenomiator = findNext( denominator.begin() ); itDenomiator != denominator.end(); itDenomiator = findNext( ++itDenomiator ) )
		{
			const auto computeSimplifiedResult = []( std::vector< int >& values, std::vector< int >::iterator it ) {
				const auto pivot = std::rotate( it, std::next( it ), values.end() );
				const auto result = compute( boost::make_iterator_range( values.begin(), --values.end() ) );
				std::rotate( pivot, --values.end(), values.end() );
				return result;
			};

			const auto simplifiedNum = computeSimplifiedResult( numerator, itNumerator );
			const auto simplifiedDen = computeSimplifiedResult( denominator, itDenomiator );

			if( simplifiedDen != 0 && simplifiedNum != 0 )
			{
				const auto gcd = boost::math::gcd( num, den );
				const auto simplifiedGcd = boost::math::gcd( simplifiedNum, simplifiedDen );

				if( num / gcd == simplifiedNum / simplifiedGcd && den / gcd == simplifiedDen / simplifiedGcd )
					return true;
			}
		}
	}
	
	return false;
}

bool isSimpleDigitCancellingFraction( std::vector< int > numerator, std::vector< int > denominator )
{
	const auto num = compute( numerator );
	const auto den = compute( denominator );

	return num == den || ( numerator.back() == 0 && denominator.back() == 0 );
}

}

size_t euler::problem33()
{
	assert( isDigitCancellingFraction( { 4,9 }, { 9,8 } ) );
	assert( isDigitCancellingFraction( { 3,0 }, { 5,0 } ) );

	const auto twoDigitNumbers = coro_t< int >::pull_type( []( coro_t< int >::push_type& sink ) { arragements_generator( sink, boost::irange( 0, 10 ) | to_vector, 2 );	} )
		| boost::adaptors::filtered( []( const auto& digits ) { return digits[ 0 ] != 0; } )
		| to_vector;

	const auto& digitCancellingFractions = cross_product( twoDigitNumbers, twoDigitNumbers )
		| boost::adaptors::filtered( []( const auto& fraction ) { return isDigitCancellingFraction( std::get< 0 >( fraction ), std::get< 1 >( fraction ) ); } )
		| boost::adaptors::filtered( []( const auto& fraction ) { return !isSimpleDigitCancellingFraction( std::get< 0 >( fraction ), std::get< 1 >( fraction ) ); } )
		| boost::adaptors::transformed( []( const auto& fraction ) { return std::make_pair( compute( std::get< 0 >( fraction ) ), compute( std::get< 1 >( fraction ) ) ); } )
		| boost::adaptors::filtered( []( const auto& fraction ) { return fraction.first < fraction.second; } );

	assert( boost::size( digitCancellingFractions ) == 4 );

	const auto product = boost::accumulate( digitCancellingFractions, std::make_pair( 1, 1 ), []( const std::pair< int, int >& total, const std::pair< int, int >& fraction ) { 
		return std::make_pair( total.first * fraction.first, total.second * fraction.second ); 
	} );
	
	return product.second / boost::math::gcd( product.first, product.second );
}