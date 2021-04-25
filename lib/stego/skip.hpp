
#ifndef CONST_SKIP_ITERATOR_HPP
#define CONST_SKIP_ITERATOR_HPP

#include <iterator>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/assert.hpp>

namespace Stg
{
    template<typename _InputIterator,
        typename __T = typename std::iterator_traits<_InputIterator>::value_type>
    struct ConstSkipIterator : public boost::iterator_facade<ConstSkipIterator<_InputIterator>, __T const, boost::forward_traversal_tag>
    {
        using It = _InputIterator;

        constexpr ConstSkipIterator(It i) : _i(i), _s(SIZE_MAX) { }

        ConstSkipIterator(size_t s, It i) : _i(i), _s(s)
        {
            BOOST_ASSERT_MSG(_s, "Infinite cycle detected");
        }

        void increment()
        {
            std::advance(_i, _s);
        }

        __T const& dereference() const
        {
            return *_i;
        }

        bool equal(ConstSkipIterator o) const
        {
            if(std::distance(_i, o._i) < 0) return true;
            return _i == o._i;
        }

    private:
        size_t _s;
        It _i;
    };
} // namespace Stg

#endif //CONST_SKIP_ITERATOR_HPP
