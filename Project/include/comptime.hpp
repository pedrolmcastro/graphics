#pragma once

#include <utility>
#include <array>

// source: https://stackoverflow.com/questions/37602057/why-isnt-a-for-loop-a-compile-time-expression

// Singleton type for natural numbers. A singleton type has a single inhabitant. In
// this template, `snat<N>` has only one inhabitant, where `snat<N>::value` equals
// `N`, but can be used both at compile and runtime. This type is usefull when you need
// a runtime-type to represent a compile-time number in a way that can be converted back
// and forth.
template<std::size_t N>
struct snat { static const constexpr auto value = N; };

template<typename F, std::size_t... Is>
static inline void comptime_for(F func, std::index_sequence<Is...>) {
    (func(snat<Is>{}), ...);
}

// Iterate from 0 to `N` and call `func<snat<I>>(snat<I>{})` for every iteration.
// This makes it possible to access the compile-time number `I` through the singleton
// type `snat<I>`.
template<std::size_t N, typename F>
static inline void comptime_for(F func) {
    comptime_for(func, std::make_index_sequence<N>());
}

template<typename A>
struct array_size { };

template<typename T, std::size_t N>
struct array_size<std::array<T, N>> { static const constexpr auto value = N; };

// Get the size of the array at compile time.
template<typename A>
inline constexpr std::size_t array_size_v = array_size<A>::value;
