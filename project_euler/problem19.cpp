#include "euler.h"
#include "level1.h"
#include <functional>

size_t euler::problem19()
{
	const std::function< size_t( size_t ) > thirty = []( size_t ) { return 30_u; };
	const std::function< size_t( size_t ) > thirty_one = []( size_t ) { return 31_u; };
	const std::function< size_t( size_t ) > february = []( size_t y ) { return y % 4_u == 0 && ( y % 100_u != 0_u || y % 400_u == 0_u ) ? 29_u : 28_u; };

	const auto days_in_months = {
		thirty_one, february, thirty_one, thirty, thirty_one, thirty, thirty_one, thirty_one, thirty, thirty_one, thirty, thirty_one
	};

	// 1_u is monday
	auto days_since_1900 = 1_u, result = 0_u;
	for( auto year : boost::irange( 1900_u, 2001_u ) )
	{
		for( const auto& days_in_month : days_in_months )
		{
			if( days_since_1900 % 7_u == 0_u && year != 1900_u )
				++result;

			days_since_1900 += days_in_month( year );
		}
	}

	return result;
}