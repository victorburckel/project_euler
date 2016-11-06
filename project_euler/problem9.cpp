#include "euler.h"
#include "level1.h"
#include <boost/range/algorithm/find_if.hpp>

size_t euler::problem9()
{
	size_t result;
	*boost::find_if( boost::irange( 0_u, 1000_u ), [ &result ]( auto a ) {
		const auto numerator = 1000_u * 1000_u - 2000_u  * a;
		const auto denominator = 2000_u - 2_u * a;
		if( numerator % denominator == 0_u )
		{
			const auto b = numerator / denominator;
			const auto c = 1000_u - a - b;
			if( a != b && a != c && b != c )
			{
				result = a * b * c;
				return true;
			}
		}
		return false;
	} );

	return result;
}