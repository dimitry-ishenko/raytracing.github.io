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

template<typename A> using dtype = typename A::dtype;

template<typename A> concept Array2 = std::derived_from< A, array<dtype<A>, 2> >;
template<typename A> concept Array3 = std::derived_from< A, array<dtype<A>, 3> >;
template<typename A> concept Array4 = std::derived_from< A, array<dtype<A>, 4> >;

template<typename A> concept Array  = Array2<A> || Array3<A> || Array4<A>;

////////////////////
template<Array2 A> constexpr auto& operator+=(A& x, const A& y) { x[0] += y[0]; x[1] += y[1]; return x; }
template<Array3 A> constexpr auto& operator+=(A& x, const A& y) { x[0] += y[0]; x[1] += y[1]; x[2] += y[2]; return x; }
template<Array4 A> constexpr auto& operator+=(A& x, const A& y) { x[0] += y[0]; x[1] += y[1]; x[2] += y[2]; x[3] += y[3]; return x; }

template<Array2 A> constexpr auto& operator+=(A& x, dtype<A> q) { x[0] += q; x[1] += q; return x; }
template<Array3 A> constexpr auto& operator+=(A& x, dtype<A> q) { x[0] += q; x[1] += q; x[2] += q; return x; }
template<Array4 A> constexpr auto& operator+=(A& x, dtype<A> q) { x[0] += q; x[1] += q; x[2] += q; x[3] += q; return x; }

template<Array2 A> constexpr auto& operator-=(A& x, const A& y) { x[0] -= y[0]; x[1] -= y[1]; return x; }
template<Array3 A> constexpr auto& operator-=(A& x, const A& y) { x[0] -= y[0]; x[1] -= y[1]; x[2] -= y[2]; return x; }
template<Array4 A> constexpr auto& operator-=(A& x, const A& y) { x[0] -= y[0]; x[1] -= y[1]; x[2] -= y[2]; x[3] -= y[3]; return x; }

template<Array2 A> constexpr auto& operator-=(A& x, dtype<A> q) { x[0] -= q; x[1] -= q; return x; }
template<Array3 A> constexpr auto& operator-=(A& x, dtype<A> q) { x[0] -= q; x[1] -= q; x[2] -= q; return x; }
template<Array4 A> constexpr auto& operator-=(A& x, dtype<A> q) { x[0] -= q; x[1] -= q; x[2] -= q; x[3] -= q; return x; }

template<Array2 A> constexpr auto& operator*=(A& x, const A& y) { x[0] *= y[0]; x[1] *= y[1]; return x; }
template<Array3 A> constexpr auto& operator*=(A& x, const A& y) { x[0] *= y[0]; x[1] *= y[1]; x[2] *= y[2]; return x; }
template<Array4 A> constexpr auto& operator*=(A& x, const A& y) { x[0] *= y[0]; x[1] *= y[1]; x[2] *= y[2]; x[3] *= y[3]; return x; }

template<Array2 A> constexpr auto& operator*=(A& x, dtype<A> q) { x[0] *= q; x[1] *= q; return x; }
template<Array3 A> constexpr auto& operator*=(A& x, dtype<A> q) { x[0] *= q; x[1] *= q; x[2] *= q; return x; }
template<Array4 A> constexpr auto& operator*=(A& x, dtype<A> q) { x[0] *= q; x[1] *= q; x[2] *= q; x[3] *= q; return x; }

template<Array2 A> constexpr auto& operator/=(A& x, const A& y) { x[0] /= y[0]; x[1] /= y[1]; return x; }
template<Array3 A> constexpr auto& operator/=(A& x, const A& y) { x[0] /= y[0]; x[1] /= y[1]; x[2] /= y[2]; return x; }
template<Array4 A> constexpr auto& operator/=(A& x, const A& y) { x[0] /= y[0]; x[1] /= y[1]; x[2] /= y[2]; x[3] /= y[3]; return x; }

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

template<Array2 A> constexpr auto  operator+ (const A& x, dtype<A> q) { return A{x[0] + q, x[1] + q}; }
template<Array3 A> constexpr auto  operator+ (const A& x, dtype<A> q) { return A{x[0] + q, x[1] + q, x[2] + q}; }
template<Array4 A> constexpr auto  operator+ (const A& x, dtype<A> q) { return A{x[0] + q, x[1] + q, x[2] + q, x[3] + q}; }

template<Array2 A> constexpr auto  operator+ (dtype<A> q, const A& x) { return A{q + x[0], q + x[1]}; }
template<Array3 A> constexpr auto  operator+ (dtype<A> q, const A& x) { return A{q + x[0], q + x[1], q + x[2]}; }
template<Array4 A> constexpr auto  operator+ (dtype<A> q, const A& x) { return A{q + x[0], q + x[1], q + x[2], q + x[3]}; }

template<Array2 A> constexpr auto  operator- (const A& x, const A& y) { return A{x[0] - y[0], x[1] - y[1]}; }
template<Array3 A> constexpr auto  operator- (const A& x, const A& y) { return A{x[0] - y[0], x[1] - y[1], x[2] - y[2]}; }
template<Array4 A> constexpr auto  operator- (const A& x, const A& y) { return A{x[0] - y[0], x[1] - y[1], x[2] - y[2], x[3] - y[3]}; }

template<Array2 A> constexpr auto  operator- (const A& x, dtype<A> q) { return A{x[0] - q, x[1] - q}; }
template<Array3 A> constexpr auto  operator- (const A& x, dtype<A> q) { return A{x[0] - q, x[1] - q, x[2] - q}; }
template<Array4 A> constexpr auto  operator- (const A& x, dtype<A> q) { return A{x[0] - q, x[1] - q, x[2] - q, x[3] - q}; }

template<Array2 A> constexpr auto  operator- (dtype<A> q, const A& x) { return A{q - x[0], q - x[1]}; }
template<Array3 A> constexpr auto  operator- (dtype<A> q, const A& x) { return A{q - x[0], q - x[1], q - x[2]}; }
template<Array4 A> constexpr auto  operator- (dtype<A> q, const A& x) { return A{q - x[0], q - x[1], q - x[2], q - x[3]}; }

template<Array2 A> constexpr auto  operator* (const A& x, const A& y) { return A{x[0] * y[0], x[1] * y[1]}; }
template<Array3 A> constexpr auto  operator* (const A& x, const A& y) { return A{x[0] * y[0], x[1] * y[1], x[2] * y[2]}; }
template<Array4 A> constexpr auto  operator* (const A& x, const A& y) { return A{x[0] * y[0], x[1] * y[1], x[2] * y[2], x[3] * y[3]}; }

template<Array2 A> constexpr auto  operator* (const A& x, dtype<A> q) { return A{x[0] * q, x[1] * q}; }
template<Array3 A> constexpr auto  operator* (const A& x, dtype<A> q) { return A{x[0] * q, x[1] * q, x[2] * q}; }
template<Array4 A> constexpr auto  operator* (const A& x, dtype<A> q) { return A{x[0] * q, x[1] * q, x[2] * q, x[3] * q}; }

template<Array2 A> constexpr auto  operator* (dtype<A> q, const A& x) { return A{q * x[0], q * x[1]}; }
template<Array3 A> constexpr auto  operator* (dtype<A> q, const A& x) { return A{q * x[0], q * x[1], q * x[2]}; }
template<Array4 A> constexpr auto  operator* (dtype<A> q, const A& x) { return A{q * x[0], q * x[1], q * x[2], q * x[3]}; }

template<Array2 A> constexpr auto  operator/ (const A& x, const A& y) { return A{x[0] / y[0], x[1] / y[1]}; }
template<Array3 A> constexpr auto  operator/ (const A& x, const A& y) { return A{x[0] / y[0], x[1] / y[1], x[2] / y[2]}; }
template<Array4 A> constexpr auto  operator/ (const A& x, const A& y) { return A{x[0] / y[0], x[1] / y[1], x[2] / y[2], x[3] / y[3]}; }

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

template<Array  A> constexpr auto dist(const A& x, const A& y) { return std::sqrt(dist_2(x, y)); }
template<Array  A> constexpr auto dist_2(const A& x, const A& y) { return len_2(x - y); }

template<Array2 A> constexpr auto dot(const A& x, const A& y) { return x[0] * y[0] + x[1] * y[1]; }
template<Array3 A> constexpr auto dot(const A& x, const A& y) { return x[0] * y[0] + x[1] * y[1] + x[2] * y[2]; }
template<Array4 A> constexpr auto dot(const A& x, const A& y) { return x[0] * y[0] + x[1] * y[1] + x[2] * y[2] + x[3] * y[3]; }

template<Array  A> constexpr auto len(const A& x) { return std::sqrt(len_2(x)); }
template<Array  A> constexpr auto len_2(const A& x) { return dot(x, x); }

template<Array  A> constexpr auto lerp(const A& x, const A& y, dtype<A> t) { return x + t * (y - x); }

template<Array2 A> constexpr auto sqrt(const A& x) { return A{std::sqrt(x[0]), std::sqrt(x[1])}; }
template<Array3 A> constexpr auto sqrt(const A& x) { return A{std::sqrt(x[0]), std::sqrt(x[1]), std::sqrt(x[2])}; }
template<Array4 A> constexpr auto sqrt(const A& x) { return A{std::sqrt(x[0]), std::sqrt(x[1]), std::sqrt(x[2]), std::sqrt(x[3])}; }

////////////////////
struct adopt_unit_t { explicit adopt_unit_t() = default; };
inline constexpr adopt_unit_t adopt_unit{ };

template<Array A> struct unit : A
{
    explicit unit(const A& x) : A{ x / len(x) } { }
    unit(const A& x, adopt_unit_t) : A{x} { }
};

template<Array A> const A& to_array(const unit<A>& x) { return x; } 
template<Array A> A&& to_array(unit<A>&& x) { return x; } 

template<Array  A> constexpr auto& operator+=(unit<A>& x, const unit<A>& y) = delete;
template<Array  A> constexpr auto& operator+=(unit<A>& x, dtype<A> q) = delete;
template<Array  A> constexpr auto& operator-=(unit<A>& x, const unit<A>& y) = delete;
template<Array  A> constexpr auto& operator-=(unit<A>& x, dtype<A> q) = delete;
template<Array  A> constexpr auto& operator*=(unit<A>& x, const unit<A>& y) = delete;
template<Array  A> constexpr auto& operator*=(unit<A>& x, dtype<A> q) = delete;
template<Array  A> constexpr auto& operator/=(unit<A>& x, const unit<A>& y) = delete;
template<Array  A> constexpr auto& operator/=(unit<A>& x, dtype<A> q) = delete;

// unary +/-
template<Array  A> constexpr auto  operator+ (const unit<A>& x) { return unit{+to_array(x), adopt_unit}; }
template<Array  A> constexpr auto  operator- (const unit<A>& x) { return unit{-to_array(x), adopt_unit}; }

template<Array  A> constexpr auto  operator+ (const unit<A>& x, const unit<A>& y) { return to_array(x) + to_array(y); }
template<Array  A> constexpr auto  operator+ (const unit<A>& x, const A& y) { return to_array(x) + y; }
template<Array  A> constexpr auto  operator+ (const A& x, const unit<A>& y) { return x + to_array(y); }

template<Array  A> constexpr auto  operator+ (const unit<A>& x, dtype<A> q) { return to_array(x) + q; }
template<Array  A> constexpr auto  operator+ (dtype<A> q, const unit<A>& x) { return q + to_array(x); }

template<Array  A> constexpr auto  operator- (const unit<A>& x, const unit<A>& y) { return to_array(x) - to_array(y); }
template<Array  A> constexpr auto  operator- (const unit<A>& x, const A& y) { return to_array(x) - y; }
template<Array  A> constexpr auto  operator- (const A& x, const unit<A>& y) { return x - to_array(y); }

template<Array  A> constexpr auto  operator- (const unit<A>& x, dtype<A> q) { return to_array(x) - q; }
template<Array  A> constexpr auto  operator- (dtype<A> q, const unit<A>& x) { return q - to_array(x); }

template<Array  A> constexpr auto  operator* (const unit<A>& x, const unit<A>& y) { return to_array(x) * to_array(y); }
template<Array  A> constexpr auto  operator* (const unit<A>& x, const A& y) { return to_array(x) * y; }
template<Array  A> constexpr auto  operator* (const A& x, const unit<A>& y) { return x * to_array(y); }

template<Array  A> constexpr auto  operator* (const unit<A>& x, dtype<A> q) { return to_array(x) * q; }
template<Array  A> constexpr auto  operator* (dtype<A> q, const unit<A>& x) { return q * to_array(x); }

template<Array  A> constexpr auto  operator/ (const unit<A>& x, const unit<A>& y) { return to_array(x) / to_array(y); }
template<Array  A> constexpr auto  operator/ (const unit<A>& x, const A& y) { return to_array(x) / y; }
template<Array  A> constexpr auto  operator/ (const A& x, const unit<A>& y) { return x / to_array(y); }

template<Array  A> constexpr auto  operator/ (const unit<A>& x, dtype<A> q) { return to_array(x) / q; }
template<Array  A> constexpr auto  operator/ (dtype<A> q, const unit<A>& x) { return q / to_array(x); }

template<Array  A> constexpr auto  cross(const unit<A>& x, const unit<A>& y) { return unit{cross(to_array(x), to_array(y)), adopt_unit}; }
template<Array  A> constexpr auto  cross(const unit<A>& x, const A& y) { return cross(to_array(x), y); }
template<Array  A> constexpr auto  cross(const A& x, const unit<A>& y) { return cross(x, to_array(y)); }

template<Array  A> constexpr auto  dist(const unit<A>& x, const A& y) { return dist(to_array(x), y); }
template<Array  A> constexpr auto  dist(const A& x, const unit<A>& y) { return dist(x, to_array(y)); }

template<Array  A> constexpr auto  dist_2(const unit<A>& x, const A& y) { return dist_2(to_array(x), y); }
template<Array  A> constexpr auto  dist_2(const A& x, const unit<A>& y) { return dist_2(x, to_array(y)); }

template<Array  A> constexpr auto  dot(const unit<A>& x, const A& y) { return dot(to_array(x), y); }
template<Array  A> constexpr auto  dot(const A& x, const unit<A>& y) { return dot(x, to_array(y)); }

template<Array  A> constexpr auto  lerp(const unit<A>& x, const A& y, dtype<A> t) { return lerp(to_array(x), y, t); }
template<Array  A> constexpr auto  lerp(const A& x, const unit<A>& y, dtype<A> t) { return lerp(x, to_array(y), t); }

#endif