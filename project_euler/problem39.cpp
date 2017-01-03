#include "euler.h"
#include "level2.h"

size_t euler::problem39()
{
	// a² + b² = c²
	// a + b + c = p
	// a <= b <= c
	// a, b, c in N+

	auto result = std::make_pair( 0, 0 );
	for( auto p : boost::irange( 3, 1000 ) )
	{
		int n = 0;
		for( auto a : boost::irange( 1, p / 3 + 1 ) )
		{
			for( auto b : boost::irange( a, ( p - a ) / 2 ) )
			{
				const auto c = p - b - a;
				if( a * a + b * b == c * c )
					++n;
			}
		}

		if( n > result.second )
			result = std::make_pair( p, n );
	}

	return result.first;
}