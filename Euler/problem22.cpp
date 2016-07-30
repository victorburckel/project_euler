#include "problems.h"
#include "literals.h"
#include "skip_adaptor.h"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/range/numeric.hpp>
#include <boost/range/algorithm/equal_range.hpp>
#include <boost/range/irange.hpp>
#include <boost/range/combine.hpp>
#include <fstream>
#include <vector>

namespace {

unsigned getScore( const std::string& name )
{
	return boost::accumulate( name, 0u, []( unsigned total, char c ) { return total + c - 'A' + 1; } );
}

size_t getPosition( const std::vector< std::string >& names, const std::string& name )
{
	const auto range = boost::equal_range( names, name );
	return std::distance( names.begin(), range.first );
}

}

size_t euler::problem22()
{
	std::ifstream f( "p022_names.txt" );
	std::string content;
	std::getline( f, content );

	std::vector< std::string > names;
	boost::split( names, content, boost::is_any_of( "\"," ), boost::algorithm::token_compress_on );
	names.pop_back();
	std::sort( names.begin(), names.end() );

	assert( getPosition( names, "COLIN" ) == 938 );
	assert( getScore( "COLIN" ) == 53);

	return boost::accumulate( boost::combine( names | euler::skip( 1 ), boost::irange( 1_u, names.size() ) ), 0_u, []( size_t total, const auto& element ) { return total + getScore( boost::get< 0 >( element ) ) * boost::get< 1 >( element ); } );
}