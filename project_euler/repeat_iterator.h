#pragma once

#include <boost/iterator/iterator_facade.hpp>
#include <boost/range/iterator_range_core.hpp>

namespace detail {

template< typename Iterator >
class repeat_iterator : public boost::iterator_facade< repeat_iterator< Iterator >, typename Iterator::value_type, boost::forward_traversal_tag >
{
public:
	repeat_iterator()
		: _count( 0 )
	{}

	repeat_iterator( Iterator begin, Iterator end, size_t n )
		: _begin( begin )
		, _end( end )
		, _n( n )
		, _current( begin )
		, _count( 0 )
	{}

	repeat_iterator( Iterator end, size_t n )
		: _begin()
		, _end()
		, _n( n )
		, _current( end )
		, _count( n )
	{}

private:
	friend class boost::iterator_core_access;

	bool equal( const repeat_iterator< Iterator >& other ) const
	{
		return
			_current == other._current &&
			_count == other._count;
	}

	void increment()
	{
		if( ++_current == _end )
		{
			if( ++_count != _n )
				_current = _begin;
		}
	}

	typename Iterator::reference dereference() const
	{
		return *_current;
	}

	const Iterator _begin;
	const Iterator _end;
	const size_t _n;

	Iterator _current;
	size_t _count;
};

template< typename Iterator >
repeat_iterator< Iterator > make_repeat_iterator( Iterator begin, Iterator end, size_t n )
{
	return repeat_iterator< Iterator >( begin, end, n );
}

template< typename Iterator >
repeat_iterator< Iterator > make_repeat_iterator( Iterator end, size_t n )
{
	return repeat_iterator< Iterator >( end, n );
}

struct repeated_adaptor
{
	size_t n;
};

template< typename Range >
inline auto operator|( Range&& range, const repeated_adaptor& r )
{
	return boost::make_iterator_range(
		detail::make_repeat_iterator( range.begin(), range.end(), r.n ),
		detail::make_repeat_iterator( range.end(), r.n )
	);
}

}

inline auto repeated( size_t n )
{
	return detail::repeated_adaptor{ n };
}

template< typename Range >
inline auto repeat( Range&& range, size_t n )
{
	return range | repeated( n );
}

