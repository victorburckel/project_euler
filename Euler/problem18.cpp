#include "euler.h"
#include "skip_adaptor.h"
#include <boost/range/adaptor/reversed.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <fstream>

using namespace boost::adaptors;

namespace {

auto parser( const std::vector< std::string >& content )
{
	return content
		| transformed( []( const std::string& s ) { std::vector< std::string > r; boost::split( r, s, boost::is_space() ); return r; } )
		| transformed( []( const std::vector< std::string >& s ) { return s | transformed( []( const std::string& s ) { return boost::lexical_cast< size_t >( s ); } ) | euler::to_vector; } )
		| euler::to_vector;
}

auto maximum_path_sum( const std::vector< std::string >& content )
{
	const auto tree = parser( content );

	auto result = tree.back();
	for( auto row : tree | reversed | euler::skip( 1_u ) )
	{
		for( auto i = 0_u, size = row.size(); i < size; ++i )
			result[ i ] = row[ i ] + std::max( result[ i ], result[ i + 1 ] );
	}

	return result[ 0_u ];
}

}

size_t euler::problem18()
{
	const std::vector< std::string > tester = {
		{ "3" },
		{ "7 4" },
		{ "2 4 6" },
		{ "8 5 9 3" }
	};

	assert( maximum_path_sum( tester ) == 23 );

	const std::vector< std::string > content = {
		{ "75" },
		{ "95 64" },
		{ "17 47 82" },
		{ "18 35 87 10" },
		{ "20 04 82 47 65" },
		{ "19 01 23 75 03 34" },
		{ "88 02 77 73 07 63 67" },
		{ "99 65 04 28 06 16 70 92" },
		{ "41 41 26 56 83 40 80 70 33" },
		{ "41 48 72 33 47 32 37 16 94 29" },
		{ "53 71 44 65 25 43 91 52 97 51 14" },
		{ "70 11 33 28 77 73 17 78 39 68 17 57" },
		{ "91 71 52 38 17 14 91 43 58 50 27 29 48" },
		{ "63 66 04 68 89 53 67 30 73 16 69 87 40 31" },
		{ "04 62 98 27 23 09 70 98 73 93 38 53 60 04 23" }
	};

	return maximum_path_sum( content );
}

size_t euler::problem67()
{
	std::ifstream ifs( "p067_triangle.txt" );
	std::vector< std::string > content;
	std::string line;
	while( std::getline( ifs, line ) )
		content.push_back( line );

	return maximum_path_sum( content );
}