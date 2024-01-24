#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cmath>
#include <concepts>
#include <cstddef> // std::size_t
#include <type_traits>

template<typename D, std::size_t N>
struct array
{
    using dtype = D;
    D data[N];

    constexpr auto& operator[](std::size_t i) { return data[i]; }
    constexpr const auto& operator[](std::size_t i) const { return data[i]; }

    static constexpr std::size_t size() { return N; }
};

template<typename D> using array2 = array<D, 2>;
template<typename D> using array3 = array<D, 3>;
template<typename D> using array4 = array<D, 4>;

template<typename A> using dtype = typename A::dtype;

template<typename A> concept Array2 = std::derived_from< A, array2<dtype<A>> >;
template<typename A> concept Array3 = std::derived_from< A, array3<dtype<A>> >;
template<typename A> concept Array4 = std::derived_from< A, array4<dtype<A>> >;

template<typename A> concept Array  = Array2<A> || Array3<A> || Array4<A>;

////////////////////
template<Array2 A> constexpr auto& operator+=(A& x, const A& y) { x[0] += y[0]; x[1] += y[1]; return x; }
template<Array3 A> constexpr auto& operator+=(A& x, const A& y) { x[0] += y[0]; x[1] += y[1]; x[2] += y[2]; return x; }
template<Array4 A> constexpr auto& operator+=(A& x, const A& y) { x[0] += y[0]; x[1] += y[1]; x[2] += y[2]; x[3] += y[3]; return x; }

template<Array2 A> constexpr auto& operator-=(A& x, const A& y) { x[0] -= y[0]; x[1] -= y[1]; return x; }
template<Array3 A> constexpr auto& operator-=(A& x, const A& y) { x[0] -= y[0]; x[1] -= y[1]; x[2] -= y[2]; return x; }
template<Array4 A> constexpr auto& operator-=(A& x, const A& y) { x[0] -= y[0]; x[1] -= y[1]; x[2] -= y[2]; x[3] -= y[3]; return x; }

template<Array2 A> constexpr auto& operator*=(A& x, dtype<A> q) { x[0] *= q; x[1] *= q; return x; }
template<Array3 A> constexpr auto& operator*=(A& x, dtype<A> q) { x[0] *= q; x[1] *= q; x[2] *= q; return x; }
template<Array4 A> constexpr auto& operator*=(A& x, dtype<A> q) { x[0] *= q; x[1] *= q; x[2] *= q; x[3] *= q; return x; }

template<Array2 A> constexpr auto& operator/=(A& x, dtype<A> q) { x[0] /= q; x[1] /= q; return x; }
template<Array3 A> constexpr auto& operator/=(A& x, dtype<A> q) { x[0] /= q; x[1] /= q; x[2] /= q; return x; }
template<Array4 A> constexpr auto& operator/=(A& x, dtype<A> q) { x[0] /= q; x[1] /= q; x[2] /= q; x[3] /= q; return x; }

// unary +
template<Array2 A> constexpr auto  operator+ (const A& x) { return A{+x[0], +x[1]}; }
template<Array3 A> constexpr auto  operator+ (const A& x) { return A{+x[0], +x[1], +x[2]}; }
template<Array4 A> constexpr auto  operator+ (const A& x) { return A{+x[0], +x[1], +x[2], +x[3]}; }

// unary -
template<Array2 A> constexpr auto  operator- (const A& x) { return A{-x[0], -x[1]}; }
template<Array3 A> constexpr auto  operator- (const A& x) { return A{-x[0], -x[1], -x[2]}; }
template<Array4 A> constexpr auto  operator- (const A& x) { return A{-x[0], -x[1], -x[2], -x[3]}; }

template<Array2 A> constexpr auto  operator+ (const A& x, const A& y) { return A{x[0] + y[0], x[1] + y[1]}; }
template<Array3 A> constexpr auto  operator+ (const A& x, const A& y) { return A{x[0] + y[0], x[1] + y[1], x[2] + y[2]}; }
template<Array4 A> constexpr auto  operator+ (const A& x, const A& y) { return A{x[0] + y[0], x[1] + y[1], x[2] + y[2], x[3] + y[3]}; }

template<Array2 A> constexpr auto  operator- (const A& x, const A& y) { return A{x[0] - y[0], x[1] - y[1]}; }
template<Array3 A> constexpr auto  operator- (const A& x, const A& y) { return A{x[0] - y[0], x[1] - y[1], x[2] - y[2]}; }
template<Array4 A> constexpr auto  operator- (const A& x, const A& y) { return A{x[0] - y[0], x[1] - y[1], x[2] - y[2], x[3] - y[3]}; }

template<Array2 A> constexpr auto  operator* (const A& x, dtype<A> q) { return A{x[0] * q, x[1] * q}; }
template<Array3 A> constexpr auto  operator* (const A& x, dtype<A> q) { return A{x[0] * q, x[1] * q, x[2] * q}; }
template<Array4 A> constexpr auto  operator* (const A& x, dtype<A> q) { return A{x[0] * q, x[1] * q, x[2] * q, x[3] * q}; }

template<Array2 A> constexpr auto  operator* (dtype<A> q, const A& x) { return A{q * x[0], q * x[1]}; }
template<Array3 A> constexpr auto  operator* (dtype<A> q, const A& x) { return A{q * x[0], q * x[1], q * x[2]}; }
template<Array4 A> constexpr auto  operator* (dtype<A> q, const A& x) { return A{q * x[0], q * x[1], q * x[2], q * x[3]}; }

template<Array2 A> constexpr auto  operator/ (const A& x, dtype<A> q) { return A{x[0] / q, x[1] / q}; }
template<Array3 A> constexpr auto  operator/ (const A& x, dtype<A> q) { return A{x[0] / q, x[1] / q, x[2] / q}; }
template<Array4 A> constexpr auto  operator/ (const A& x, dtype<A> q) { return A{x[0] / q, x[1] / q, x[2] / q, x[3] / q}; }

template<Array2 A> constexpr auto  operator/ (dtype<A> q, const A& x) { return A{q / x[0], q / x[1]}; }
template<Array3 A> constexpr auto  operator/ (dtype<A> q, const A& x) { return A{q / x[0], q / x[1], q / x[2]}; }
template<Array4 A> constexpr auto  operator/ (dtype<A> q, const A& x) { return A{q / x[0], q / x[1], q / x[2], q / x[3]}; }

template<Array3 A>
constexpr auto cross(const A& x, const A& y)
{
    return A{x[1] * y[2] - y[1] * x[2], x[2] * y[0] - y[2] * x[0], x[0] * y[1] - y[0] * x[1]};
}

template<Array2 A> constexpr auto dot(const A& x, const A& y) { return x[0] * y[0] + x[1] * y[1]; }
template<Array3 A> constexpr auto dot(const A& x, const A& y) { return x[0] * y[0] + x[1] * y[1] + x[2] * y[2]; }
template<Array4 A> constexpr auto dot(const A& x, const A& y) { return x[0] * y[0] + x[1] * y[1] + x[2] * y[2] + x[3] * y[3]; }

template<Array  A> constexpr auto len(const A& x) { return std::sqrt(len_2(x)); }
template<Array  A> constexpr auto len_2(const A& x) { return dot(x, x); }

template<Array2 A> constexpr auto sqrt(const A& x) { return A{std::sqrt(x[0]), std::sqrt(x[1])}; }
template<Array3 A> constexpr auto sqrt(const A& x) { return A{std::sqrt(x[0]), std::sqrt(x[1]), std::sqrt(x[2])}; }
template<Array4 A> constexpr auto sqrt(const A& x) { return A{std::sqrt(x[0]), std::sqrt(x[1]), std::sqrt(x[2]), std::sqrt(x[3])}; }

template<Array  A> constexpr auto unit(const A& x) { return x / len(x); }

#endif
