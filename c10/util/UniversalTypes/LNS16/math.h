#pragma once

#include <c10/util/math_compat.h>

C10_CLANG_DIAGNOSTIC_PUSH()
#if C10_CLANG_HAS_WARNING("-Wimplicit-float-conversion")
C10_CLANG_DIAGNOSTIC_IGNORE("-Wimplicit-float-conversion")
#endif

// Math functions like in BFloat16-math.h
namespace std {

/// Used by vec256<c10::LNS16>::map
inline c10::LNS16 acos(c10::LNS16 a) {
  return std::acos(static_cast<float>(a));
}
inline c10::LNS16 asin(c10::LNS16 a) {
  return std::asin(static_cast<float>(a));
}
inline c10::LNS16 atan(c10::LNS16 a) {
  return std::atan(static_cast<float>(a));
}
inline c10::LNS16 erf(c10::LNS16 a) {
  return std::erf(static_cast<float>(a));
}
inline c10::LNS16 erfc(c10::LNS16 a) {
  return std::erfc(static_cast<float>(a));
}
inline c10::LNS16 exp(c10::LNS16 a) {
  return std::exp(static_cast<float>(a));
}
inline c10::LNS16 expm1(c10::LNS16 a) {
  return std::expm1(static_cast<float>(a));
}
inline c10::LNS16 log(c10::LNS16 a) {
  return std::log(static_cast<float>(a));
}
inline c10::LNS16 log10(c10::LNS16 a) {
  return std::log10(static_cast<float>(a));
}
inline c10::LNS16 log1p(c10::LNS16 a) {
  return std::log1p(static_cast<float>(a));
}
inline c10::LNS16 log2(c10::LNS16 a) {
  return std::log2(static_cast<float>(a));
}
inline c10::LNS16 ceil(c10::LNS16 a) {
  return std::ceil(static_cast<float>(a));
}
inline c10::LNS16 cos(c10::LNS16 a) {
  return std::cos(static_cast<float>(a));
}
inline c10::LNS16 floor(c10::LNS16 a) {
  return std::floor(static_cast<float>(a));
}
inline c10::LNS16 nearbyint(c10::LNS16 a) {
  return std::nearbyint(static_cast<float>(a));
}
inline c10::LNS16 sin(c10::LNS16 a) {
  return std::sin(static_cast<float>(a));
}
inline c10::LNS16 tan(c10::LNS16 a) {
  return std::tan(static_cast<float>(a));
}
inline c10::LNS16 sinh(c10::LNS16 a) {
  return std::sinh(static_cast<float>(a));
}
inline c10::LNS16 cosh(c10::LNS16 a) {
  return std::cosh(static_cast<float>(a));
}
inline c10::LNS16 tanh(c10::LNS16 a) {
  return std::tanh(static_cast<float>(a));
}
inline c10::LNS16 trunc(c10::LNS16 a) {
  return std::trunc(static_cast<float>(a));
}
inline c10::LNS16 lgamma(c10::LNS16 a) {
  return std::lgamma(static_cast<float>(a));
}
inline c10::LNS16 sqrt(c10::LNS16 a) {
  return std::sqrt(static_cast<float>(a));
}
inline c10::LNS16 rsqrt(c10::LNS16 a) {
  return 1.0 / std::sqrt(static_cast<float>(a));
}
inline c10::LNS16 abs(c10::LNS16 a) {
  return std::abs(static_cast<float>(a));
}
inline c10::LNS16 pow(double a, c10::LNS16 b) {
  return std::pow(a, static_cast<double>(b));
}
inline c10::LNS16 pow(c10::LNS16 a, double b) {
  return std::pow(static_cast<double>(a), b);
}
inline c10::LNS16 pow(c10::LNS16 a, c10::LNS16 b) {
  return std::pow(static_cast<float>(a), static_cast<float>(b));
}
inline c10::LNS16 fmod(c10::LNS16 a, c10::LNS16 b) {
  return std::fmod(static_cast<float>(a), static_cast<float>(b));
}
inline c10::LNS16 fabs(c10::LNS16 a) {
  return std::fabs(static_cast<float>(a));
}

C10_HOST_DEVICE inline c10::LNS16 nextafter(
    c10::LNS16 from,
    c10::LNS16 to) {
  return std::nextafter(static_cast<float>(from), static_cast<float>(to));
}

C10_HOST_DEVICE inline c10::LNS16 nexttoward(
    c10::LNS16 from,
    long double to) {
  return std::nexttoward(static_cast<float>(from), to);
}

} // namespace std

C10_CLANG_DIAGNOSTIC_POP()
