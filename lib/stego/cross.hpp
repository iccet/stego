
#ifndef CONST_CROSS_ITERATOR_HPP
#define CONST_CROSS_ITERATOR_HPP

#include <iterator>
#include <tuple>
#include <iostream>
#include <array>
#include <utility>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/range/irange.hpp>
#include <boost/log/trivial.hpp>

#include "meta.hpp"

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

template<int Size, typename InputIterator, int ... Position>
struct CrossIterator : public boost::iterator_facade<
        CrossIterator<Size, InputIterator, Position...>,
        int const,
        boost::forward_traversal_tag>
{
    using It = InputIterator;
    using Index = decltype(std::make_tuple(Position...));
    using Range = std::vector<Index>;

    using _T = typename std::iterator_traits<InputIterator>::value_type::value_type;

    CrossIterator(It i) : _i(i) { }

    CrossIterator(It i, std::integer_sequence<int, Position...>) : _i(i)
    {
        BOOST_ASSERT(sizeof...(Position));

        std::array<int, 2 * Size + 1> indexes { };
        std::iota(indexes.begin(), indexes.end(), -Size);

        for (auto i : indexes)
        {
            std::array<int, sizeof...(Position)> permutation{Position...};
            permutation.front() += i;
            std::reverse(permutation.begin(), permutation.end());

            for (int j = 0; j < sizeof...(Position); ++j)
            {
                auto tuple = to_tuple(permutation, std::make_index_sequence<sizeof...(Position)>());
                _range.push_back(tuple);
                std::rotate(permutation.begin(), permutation.begin() + j, permutation.end());
            }
        }
    }

    void increment()
    {
        _range.pop_back();
    }

    _T const& dereference() const
    {
        auto x = _range.back();
        auto i = indexing<It, Position...>(_i, x);
        BOOST_LOG_TRIVIAL(debug) << i;
        return i;
    }

    bool equal(CrossIterator) const
    {
        return _range.empty();
    }

private:
    It _i;
    Range _range;
};
#endif //CONST_CROSS_ITERATOR_HPP

