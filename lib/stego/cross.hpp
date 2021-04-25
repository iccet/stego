
#ifndef CONST_CROSS_ITERATOR_HPP
#define CONST_CROSS_ITERATOR_HPP

#include <iterator>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/range/irange.hpp>
#include <boost/log/trivial.hpp>

namespace Stg
{
    template<typename _InputIterator,
            typename __T = typename std::iterator_traits<_InputIterator>::value_type::value_type>
    struct ConstCrossIterator : public boost::iterator_facade<
            ConstCrossIterator<_InputIterator>,
            __T const,
            boost::forward_traversal_tag>
    {
        using It = _InputIterator;
        using Range = std::vector<std::tuple<int, int>>;

        ConstCrossIterator(It i) : _i(i) { }

        ConstCrossIterator(It i, size_t s, int x, int y) : _i(i)
        {
            std::vector<int> v(2 * s + 1);
            std::iota(v.begin(), v.end(), -s);

            for (auto i : v)
            {
                std::vector<int> t {0, i};
                std::sort(t.begin(), t.end());
                do {
                    _range.push_back(std::make_tuple(x - t.front(), y - t.back()));
                }
                while(std::next_permutation(t.begin(), t.end()));
            }
        }

        void increment()
        {
            _range.pop_back();
        }

        __T const& dereference() const
        {
            auto [x, y] = _range.back();
            return _i[x][y];
        }

        bool equal(ConstCrossIterator) const
        {
            return _range.empty();
        }

    private:
        It _i;
        Range _range;
    };
} // namespace Stg

#endif //CONST_CROSS_ITERATOR_HPP
