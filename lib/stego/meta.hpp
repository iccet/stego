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
auto to_tuple(const Array& a, std::index_sequence<I...>)
{
    return std::make_tuple(a[I]...);
}

template<int I, int ... J>
auto slice_tuple(decltype(std::make_tuple(I, J ...)) t, std::integer_sequence<int, J...>)
{
    return std::make_tuple(std::get<J + 1>(t) ...);
}

template<typename Array, typename T>
auto indexing(const Array& array, std::tuple<T> tuple)
{
    auto i = std::get<0>(tuple);
    return array[i];
}

template<typename Array, int I, int ... Index>
auto indexing(const Array& array, decltype(std::make_tuple(I, Index ...)) tuple)
{
    auto index = slice_tuple<Index ...>(tuple, std::make_integer_sequence<int, sizeof...(Index)>());
    auto sub_array = array[std::get<0>(tuple)];
    return indexing(sub_array, index);
}

#endif //STEGO_META_HPP
