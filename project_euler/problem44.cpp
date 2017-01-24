#include "euler.h"
#include "level2.h"
#include <boost/unordered_set.hpp>
#include <vector>

namespace {

auto generatePentagonalNumbers( int count )
{
	boost::unordered_set< int > searcher;
	std::vector< int > accessor;
	searcher.reserve( count );
	accessor.reserve( count );

	const auto p = []( int n ) { return n * ( 3 * n - 1 ) / 2;  };
	for( auto n : boost::irange( 1, 10000 ) )
	{
		const auto value = p( n );
		searcher.insert( value );
		accessor.push_back( value );
	}

	return std::make_pair( [ searcher = std::move( searcher ) ]( int value ){ return searcher.find( value ) != searcher.end(); }, [ accessor = std::move( accessor ) ]( int n ) { return accessor[ n - 1 ]; } );
}

}

size_t euler::problem44()
{
	// We have D = Pk - Pj = n( 3n - 1 ) / 2 = ( k( 3k - 1 ) - j( 3j - 1 ) ) / 2
	// With k > j and k > n
	// The minimum value for Pk - Pj for a given k is 
	// Pk - Pk-1 = ( k( 3k - 1 ) - ( k - 1 )( 3( k - 1 ) - 1 ) ) /2
	// = ( 3k² - k - ( k - 1 )( 3k - 4 ) ) / 2
	// = ( 3k² - k - 3k² + 4k + 3k - 4 ) / 2
	// = ( 6k - 4 ) / 2
	// For a given n, we have Pk - Pj > Pn
	// <=> 6k - 4 / 2 > Pn
	// <=> 3k - 2 > Pn
	// <=> k > ( Pn + 2 ) / 3
	const auto count = 10000;
	const auto ps = generatePentagonalNumbers( count );

	for( auto n = 1;; ++n )
	{
		const auto pn = ps.second( n );
		const auto limit = ( pn + 2 ) / 3 + 1;
		for( auto k : boost::irange( n + 1, std::min( limit, count ) ) )
		{
			const auto pk = ps.second( k );
			const auto pj = pk - pn;
			if( ps.first( pj ) )
			{
				const auto pm = pj + pk;
				if( ps.first( pm ) )
					return pn;
			}
		}
	}
}