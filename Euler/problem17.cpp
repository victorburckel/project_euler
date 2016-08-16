#include "euler.h"
#include <array>

size_t euler::problem17()
{
	const std::array< std::string, 9 > units = {
		"one", "two", "three", "four", "five", "six", "seven", "height", "nine"
	};

	const std::array< std::string, 10 > iregulars = {
		"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"
	};

	const std::array< std::string, 8 > tens = {
		"twenty", "thirty", "fourty", "fifty", "sixty", "seventy", "eighty", "ninety"
	};

	const std::string hundred = "hundred";
	const std::string and = "and";

	const auto op = []( size_t total, const std::string& s ) { return total + s.size(); };

	const auto units_size = boost::accumulate( units, 0_u, op );
	const auto iregular_size = boost::accumulate( iregulars, 0_u, op );
	const auto tens_size = boost::accumulate( tens, 0_u, op );

	const auto sum_to_hundred = iregular_size + ( units_size + 1 ) * tens.size() + tens_size * ( units.size() + 1 );
	const auto sum_to_thousand = boost::accumulate( units, 0_u, [ &hundred, &and ]( size_t total, const std::string& s ) { return total + 100 * ( hundred.size() + s.size() ) + 99 * and.size(); } );
	const auto total = sum_to_thousand + sum_to_hundred * 10_u;

	assert( boost::accumulate( boost::make_iterator_range( units.begin(), std::next( units.begin(), 5 ) ), 0_u, op ) == 19 );


	return total + std::string( "onethousand" ).size();
}