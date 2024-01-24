#ifndef VEC_HPP
#define VEC_HPP

#include <cmath>
#include <concepts>
#include <cstddef> // std::size_t
#include <type_traits>

template<typename D, std::size_t N>
struct vec
{
    using dtype = D;
    D data[N];

    constexpr auto& operator[](std::size_t i) { return data[i]; }
    constexpr const auto& operator[](std::size_t i) const { return data[i]; }

    static constexpr std::size_t size() { return N; }
};

template<typename D> using vec2 = vec<D, 2>;
template<typename D> using vec3 = vec<D, 3>;
template<typename D> using vec4 = vec<D, 4>;

template<typename V> using dtype = typename V::dtype;

template<typename V> concept Vec2 = std::derived_from< V, vec2<dtype<V>> >;
template<typename V> concept Vec3 = std::derived_from< V, vec3<dtype<V>> >;
template<typename V> concept Vec4 = std::derived_from< V, vec4<dtype<V>> >;

template<typename V> concept Vec  = Vec2<V> || Vec3<V> || Vec4<V>;

////////////////////
template<Vec2 V> constexpr auto& operator+=(V& v, const V& w) { v[0] += w[0]; v[1] += w[1]; return v; }
template<Vec3 V> constexpr auto& operator+=(V& v, const V& w) { v[0] += w[0]; v[1] += w[1]; v[2] += w[2]; return v; }
template<Vec4 V> constexpr auto& operator+=(V& v, const V& w) { v[0] += w[0]; v[1] += w[1]; v[2] += w[2]; v[3] += w[3]; return v; }

template<Vec2 V> constexpr auto& operator-=(V& v, const V& w) { v[0] -= w[0]; v[1] -= w[1]; return v; }
template<Vec3 V> constexpr auto& operator-=(V& v, const V& w) { v[0] -= w[0]; v[1] -= w[1]; v[2] -= w[2]; return v; }
template<Vec4 V> constexpr auto& operator-=(V& v, const V& w) { v[0] -= w[0]; v[1] -= w[1]; v[2] -= w[2]; v[3] -= w[3]; return v; }

template<Vec2 V> constexpr auto& operator*=(V& v, dtype<V> q) { v[0] *= q; v[1] *= q; return v; }
template<Vec3 V> constexpr auto& operator*=(V& v, dtype<V> q) { v[0] *= q; v[1] *= q; v[2] *= q; return v; }
template<Vec4 V> constexpr auto& operator*=(V& v, dtype<V> q) { v[0] *= q; v[1] *= q; v[2] *= q; v[3] *= q; return v; }

template<Vec2 V> constexpr auto& operator/=(V& v, dtype<V> q) { v[0] /= q; v[1] /= q; return v; }
template<Vec3 V> constexpr auto& operator/=(V& v, dtype<V> q) { v[0] /= q; v[1] /= q; v[2] /= q; return v; }
template<Vec4 V> constexpr auto& operator/=(V& v, dtype<V> q) { v[0] /= q; v[1] /= q; v[2] /= q; v[3] /= q; return v; }

// unary +
template<Vec2 V> constexpr auto  operator+ (const V& v) { return V{+v[0], +v[1]}; }
template<Vec3 V> constexpr auto  operator+ (const V& v) { return V{+v[0], +v[1], +v[2]}; }
template<Vec4 V> constexpr auto  operator+ (const V& v) { return V{+v[0], +v[1], +v[2], +v[3]}; }

// unary -
template<Vec2 V> constexpr auto  operator- (const V& v) { return V{-v[0], -v[1]}; }
template<Vec3 V> constexpr auto  operator- (const V& v) { return V{-v[0], -v[1], -v[2]}; }
template<Vec4 V> constexpr auto  operator- (const V& v) { return V{-v[0], -v[1], -v[2], -v[3]}; }

template<Vec2 V> constexpr auto  operator+ (const V& v, const V& w) { return V{v[0] + w[0], v[1] + w[1]}; }
template<Vec3 V> constexpr auto  operator+ (const V& v, const V& w) { return V{v[0] + w[0], v[1] + w[1], v[2] + w[2]}; }
template<Vec4 V> constexpr auto  operator+ (const V& v, const V& w) { return V{v[0] + w[0], v[1] + w[1], v[2] + w[2], v[3] + w[3]}; }

template<Vec2 V> constexpr auto  operator- (const V& v, const V& w) { return V{v[0] - w[0], v[1] - w[1]}; }
template<Vec3 V> constexpr auto  operator- (const V& v, const V& w) { return V{v[0] - w[0], v[1] - w[1], v[2] - w[2]}; }
template<Vec4 V> constexpr auto  operator- (const V& v, const V& w) { return V{v[0] - w[0], v[1] - w[1], v[2] - w[2], v[3] - w[3]}; }

template<Vec2 V> constexpr auto  operator* (const V& v, dtype<V> q) { return V{v[0] * q, v[1] * q}; }
template<Vec3 V> constexpr auto  operator* (const V& v, dtype<V> q) { return V{v[0] * q, v[1] * q, v[2] * q}; }
template<Vec4 V> constexpr auto  operator* (const V& v, dtype<V> q) { return V{v[0] * q, v[1] * q, v[2] * q, v[3] * q}; }

template<Vec2 V> constexpr auto  operator* (dtype<V> q, const V& v) { return V{q * v[0], q * v[1]}; }
template<Vec3 V> constexpr auto  operator* (dtype<V> q, const V& v) { return V{q * v[0], q * v[1], q * v[2]}; }
template<Vec4 V> constexpr auto  operator* (dtype<V> q, const V& v) { return V{q * v[0], q * v[1], q * v[2], q * v[3]}; }

template<Vec2 V> constexpr auto  operator/ (const V& v, dtype<V> q) { return V{v[0] / q, v[1] / q}; }
template<Vec3 V> constexpr auto  operator/ (const V& v, dtype<V> q) { return V{v[0] / q, v[1] / q, v[2] / q}; }
template<Vec4 V> constexpr auto  operator/ (const V& v, dtype<V> q) { return V{v[0] / q, v[1] / q, v[2] / q, v[3] / q}; }

template<Vec2 V> constexpr auto  operator/ (dtype<V> q, const V& v) { return V{q / v[0], q / v[1]}; }
template<Vec3 V> constexpr auto  operator/ (dtype<V> q, const V& v) { return V{q / v[0], q / v[1], q / v[2]}; }
template<Vec4 V> constexpr auto  operator/ (dtype<V> q, const V& v) { return V{q / v[0], q / v[1], q / v[2], q / v[3]}; }

template<Vec3 V>
constexpr auto cross(const V& v, const V& w)
{
    return V{v[1] * w[2] - w[1] * v[2], v[2] * w[0] - w[2] * v[0], v[0] * w[1] - w[0] * v[1]};
}

template<Vec2 V> constexpr auto dot(const V& v, const V& w) { return v[0] * w[0] + v[1] * w[1]; }
template<Vec3 V> constexpr auto dot(const V& v, const V& w) { return v[0] * w[0] + v[1] * w[1] + v[2] * w[2]; }
template<Vec4 V> constexpr auto dot(const V& v, const V& w) { return v[0] * w[0] + v[1] * w[1] + v[2] * w[2] + v[3] * w[3]; }

template<Vec  V> constexpr auto len(const V& v) { return std::sqrt(len_2(v)); }
template<Vec  V> constexpr auto len_2(const V& v) { return dot(v, v); }

template<Vec2 V> constexpr auto sqrt(const V& v) { return V{std::sqrt(v[0]), std::sqrt(v[1])}; }
template<Vec3 V> constexpr auto sqrt(const V& v) { return V{std::sqrt(v[0]), std::sqrt(v[1]), std::sqrt(v[2])}; }
template<Vec4 V> constexpr auto sqrt(const V& v) { return V{std::sqrt(v[0]), std::sqrt(v[1]), std::sqrt(v[2]), std::sqrt(v[3])}; }

template<Vec  V> constexpr auto unit(const V& v) { return v / len(v); }

#endif
