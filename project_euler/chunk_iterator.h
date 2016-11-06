#pragma once

#include <boost/iterator/iterator_facade.hpp>
#include <boost/range/iterator_range_core.hpp>

namespace detail {

template< typename Iterator >
Iterator safe_next( Iterator it, Iterator end, size_t size )
{
	std::advance( it, std::min( static_cast< size_t >( std::distance( it, end ) ), size ) );
	return it;
}

}

template< typename Iterator >
class chunk_iterator: public boost::iterator_facade< chunk_iterator< Iterator >, const boost::iterator_range< Iterator >, boost::forward_traversal_tag >
{
public:
	chunk_iterator()
		: _size( 0 )
	{ /* no-op */ }

	explicit chunk_iterator( Iterator it, Iterator end, size_t size )
		: _current( it, detail::safe_next( it, end, size ) )
		, _end( end )
		, _size( size )
	{ /* no-op */ }

private:
	friend class boost::iterator_core_access;

	bool equal( const chunk_iterator< Iterator >& other ) const
	{
		return
			_current.begin() == other._current.begin() &&
			_end == other._end &&
			_size == other._size;
	}

	void increment()
	{
		_current = boost::make_iterator_range( _current.end(), detail::safe_next( _current.end(), _end, _size ) );
	}

	const boost::iterator_range< Iterator >& dereference() const
	{
		return _current;
	}

	boost::iterator_range< Iterator > _current;
	Iterator _end;
	size_t _size;
};

template< typename Iterator >
auto make_chunk_iterator( Iterator it, Iterator end, size_t size )
{
	return chunk_iterator< Iterator >( it, end, size );
}

template< typename Sequence >
auto chunk( Sequence&& sequence, size_t size )
{
	return boost::make_iterator_range( make_chunk_iterator( sequence.begin(), sequence.end(), size ), make_chunk_iterator( sequence.end(), sequence.end(), size ) );
}
