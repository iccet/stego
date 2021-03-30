#ifndef STEGO_META_HPP
#define STEGO_META_HPP

#include <array>

template<typename T, std::size_t... I>
constexpr auto create_array_impl(std::index_sequence<I...>)
{
    return std::array<T, sizeof...(I)>{I...};
}

template<typename T, std::size_t N>
constexpr auto create_array()
{
    return create_array_impl<T>(std::make_index_sequence<N>{});
}

template<typename Array, std::size_t... I>
auto a2t_impl(const Array& a, std::index_sequence<I...>)
{
    return std::make_tuple(a[I]...);
}

template<int ... J>
auto slice(decltype(std::make_tuple(int(), J ...)) t, std::integer_sequence<int, J...>)
{
    return std::make_tuple(std::get<J>(t) ...);
}

template<typename Array, int I, int ... J>
auto indexing(const Array& a, decltype(std::make_tuple(I, J ...)) t)
{
    auto r = slice(t, std::make_integer_sequence<int, sizeof...(J)>());

    const auto &d = a[std::get<0>(t)];
    return indexing<decltype(d), J...>(d, r);
}

#endif //STEGO_META_HPP
