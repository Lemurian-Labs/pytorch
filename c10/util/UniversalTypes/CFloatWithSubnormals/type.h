#pragma once

#pragma push_macro("setbit")
#undef setbit
#include <universal/number/cfloat/cfloat.hpp>
#pragma pop_macro("setbit")

#include <c10/util/UniversalTypes/CFloatWithSubnormals/add.h>
#include <c10/util/UniversalTypes/CFloatWithSubnormals/div.h>
#include <c10/util/UniversalTypes/CFloatWithSubnormals/mul.h>
#include <c10/util/UniversalTypes/CFloatWithSubnormals/misc.h>
#include <c10/util/BFloat16.h>
#include <c10/util/Half.h>

#include <type_traits>

// Private macro (it is removed with #undef below)
#define FORALL_SUPPORTED_TYPES(_) \
  _(int)                          \
  _(long)                         \
  _(long long)                    \
  _(float)                        \
  _(double)

// Private macro (it is removed with #undef below)
// (argument type, return type)
#define FORALL_SUPPORTED_TYPES_IN_OPERATORS(_) \
  _(int, CFloatWithSubnormals)                 \
  _(float, CFloatWithSubnormals)               \
  _(double, double) // ATen requires returning double if the argument type is double

// Private macro (it is removed with #undef below)
#define FORALL_ADDITIONAL_TYPES(_) \
  _(unsigned char)                 \
  _(uint64_t)


namespace c10 {


class alignas(4) CFloatWithSubnormals : public sw::universal::cfloat<32, 8, uint32_t, true, false, false>
{
public:
  using Base = sw::universal::cfloat<32, 8, uint32_t, true, false, false>;

  CFloatWithSubnormals() = default;
  C10_HOST_DEVICE CFloatWithSubnormals(float value) : Base()
  {
    convert_ieee754<float>(value);
  }

  constexpr C10_HOST_DEVICE CFloatWithSubnormals(Base value) : Base(value) {}

  // A way to construct CFloatWithSubnormals from bits similar to Half and BFloat16
  struct from_bits_t {};
  static constexpr C10_HOST_DEVICE from_bits_t from_bits()
  {
    return from_bits_t();
  }

  constexpr C10_HOST_DEVICE CFloatWithSubnormals(uint32_t bits, from_bits_t) :
    Base()
  {
    setblock(0, bits);
  }

  C10_HOST_DEVICE operator float() const noexcept
  {
    return Base::operator float();
  }

  // Define operator < to avoid ambiguity
  C10_HOST_DEVICE bool operator<(const CFloatWithSubnormals& right) const
  {
    return sw::universal::operator<(
      static_cast<Base>(*this),
      static_cast<Base>(right));
  }
  C10_HOST_DEVICE bool operator<=(const CFloatWithSubnormals& right) const
  {
    return sw::universal::operator<=(
      static_cast<Base>(*this),
      static_cast<Base>(right));
  }
  #define OP(T)                                    \
    C10_HOST_DEVICE bool operator<(T right) const  \
    {                                              \
      return sw::universal::operator<(             \
        static_cast<Base>(*this),                  \
        static_cast<Base>(right));                 \
    }                                              \
    C10_HOST_DEVICE bool operator<=(T right) const \
    {                                              \
      return sw::universal::operator<=(            \
        static_cast<Base>(*this),                  \
        static_cast<Base>(right));                 \
    }
  FORALL_SUPPORTED_TYPES(OP)
  FORALL_ADDITIONAL_TYPES(OP)
  #undef OP

  // Define operator > to avoid ambiguity
  C10_HOST_DEVICE bool operator>(const CFloatWithSubnormals& right) const
  {
    return sw::universal::operator>(
      static_cast<Base>(*this),
      static_cast<Base>(right));
  }
  C10_HOST_DEVICE bool operator>=(const CFloatWithSubnormals& right) const
  {
    return sw::universal::operator>=(
      static_cast<Base>(*this),
      static_cast<Base>(right));
  }
  #define OP(T)                                    \
    C10_HOST_DEVICE bool operator>(T right) const  \
    {                                              \
      return sw::universal::operator>(             \
        static_cast<Base>(*this),                  \
        static_cast<Base>(right));                 \
    }                                              \
    C10_HOST_DEVICE bool operator>=(T right) const \
    {                                              \
      return sw::universal::operator>=(            \
        static_cast<Base>(*this),                  \
        static_cast<Base>(right));                 \
    }
  FORALL_SUPPORTED_TYPES(OP)
  FORALL_ADDITIONAL_TYPES(OP)
  #undef OP

  // Assignment operators
  #define OP(T)                                              \
    C10_HOST_DEVICE CFloatWithSubnormals& operator=(T value) \
    {                                                        \
      Base::operator=(value);                                \
      return *this;                                          \
    }
  FORALL_SUPPORTED_TYPES(OP)
  #undef OP
  C10_HOST_DEVICE CFloatWithSubnormals& operator=(signed char value)
  {
    convert_signed_integer(value);
    return *this;
  }
  C10_HOST_DEVICE CFloatWithSubnormals& operator=(unsigned char value)
  {
    convert_unsigned_integer(value);
    return *this;
  }
  C10_HOST_DEVICE CFloatWithSubnormals& operator=(short value)
  {
    convert_signed_integer(value);
    return *this;
  }
  C10_HOST_DEVICE CFloatWithSubnormals& operator=(bool value)
  {
    convert_signed_integer(value);
    return *this;
  }
  C10_HOST_DEVICE CFloatWithSubnormals& operator=(c10::BFloat16 value)
  {
    Base::operator=(static_cast<float>(value));
    return *this;
  }
  C10_HOST_DEVICE CFloatWithSubnormals& operator=(c10::Half value)
  {
    Base::operator=(static_cast<float>(value));
    return *this;
  }

  // Arithmetic operators
  // ATen requires unary minus to be constexpr
  constexpr C10_HOST_DEVICE CFloatWithSubnormals operator-() const
  {
    cfloat tmp(*this);
    tmp.setblock(Base::MSU, tmp.block(Base::MSU) ^ Base::SIGN_BIT_MASK);
    return static_cast<CFloatWithSubnormals>(tmp);
  }
  C10_HOST_DEVICE CFloatWithSubnormals& operator+=(const CFloatWithSubnormals& right)
  {
    return static_cast<CFloatWithSubnormals&>(Base::operator+=(right));
  }
  C10_HOST_DEVICE CFloatWithSubnormals& operator-=(const CFloatWithSubnormals& right)
  {
    return static_cast<CFloatWithSubnormals&>(Base::operator-=(right));
  }
  C10_HOST_DEVICE CFloatWithSubnormals& operator*=(const CFloatWithSubnormals& right)
  {
    return static_cast<CFloatWithSubnormals&>(Base::operator*=(right));
  }
  C10_HOST_DEVICE CFloatWithSubnormals& operator/=(const CFloatWithSubnormals& right)
  {
    return static_cast<CFloatWithSubnormals&>(Base::operator/=(right));
  }
};

// Nonmember comparison operators
#define OP(T)                                                                       \
  inline C10_HOST_DEVICE bool operator<(T left, const CFloatWithSubnormals& right)  \
  {                                                                                 \
    return sw::universal::operator<(                                                \
      static_cast<CFloatWithSubnormals::Base>(left),                                \
      static_cast<CFloatWithSubnormals::Base>(right));                              \
  }                                                                                 \
  inline C10_HOST_DEVICE bool operator<=(T left, const CFloatWithSubnormals& right) \
  {                                                                                 \
    return sw::universal::operator<=(                                               \
      static_cast<CFloatWithSubnormals::Base>(left),                                \
      static_cast<CFloatWithSubnormals::Base>(right));                              \
  }
FORALL_SUPPORTED_TYPES(OP)
FORALL_ADDITIONAL_TYPES(OP)
#undef OP

#define OP(T)                                                                       \
  inline C10_HOST_DEVICE bool operator>(T left, const CFloatWithSubnormals& right)  \
  {                                                                                 \
    return sw::universal::operator>(                                                \
      static_cast<CFloatWithSubnormals::Base>(left),                                \
      static_cast<CFloatWithSubnormals::Base>(right));                              \
  }                                                                                 \
  inline C10_HOST_DEVICE bool operator>=(T left, const CFloatWithSubnormals& right) \
  {                                                                                 \
    return sw::universal::operator>=(                                               \
      static_cast<CFloatWithSubnormals::Base>(left),                                \
      static_cast<CFloatWithSubnormals::Base>(right));                              \
  }
FORALL_SUPPORTED_TYPES(OP)
FORALL_ADDITIONAL_TYPES(OP)
#undef OP

// Nonmember arithmetic operators
inline C10_HOST_DEVICE CFloatWithSubnormals operator+(const CFloatWithSubnormals& left, const CFloatWithSubnormals& right)
{
  return static_cast<CFloatWithSubnormals>(sw::universal::operator+(
    static_cast<CFloatWithSubnormals::Base>(left),
    static_cast<CFloatWithSubnormals::Base>(right)));
}
inline C10_HOST_DEVICE CFloatWithSubnormals operator-(const CFloatWithSubnormals& left, const CFloatWithSubnormals& right)
{
  return static_cast<CFloatWithSubnormals>(sw::universal::operator-(
    static_cast<CFloatWithSubnormals::Base>(left),
    static_cast<CFloatWithSubnormals::Base>(right)));
}
inline C10_HOST_DEVICE CFloatWithSubnormals operator*(const CFloatWithSubnormals& left, const CFloatWithSubnormals& right)
{
  return static_cast<CFloatWithSubnormals>(sw::universal::operator*(
    static_cast<CFloatWithSubnormals::Base>(left),
    static_cast<CFloatWithSubnormals::Base>(right)));
}
inline C10_HOST_DEVICE CFloatWithSubnormals operator/(const CFloatWithSubnormals& left, const CFloatWithSubnormals& right)
{
  return static_cast<CFloatWithSubnormals>(sw::universal::operator/(
    static_cast<CFloatWithSubnormals::Base>(left),
    static_cast<CFloatWithSubnormals::Base>(right)));
}

#define OP(T, R)                                                                                                                 \
  inline C10_HOST_DEVICE R operator+(const CFloatWithSubnormals& left, T right)                            \
  {                                                                                                                           \
    return static_cast<R>(sw::universal::operator+(static_cast<CFloatWithSubnormals::Base>(left), right)); \
  }                                                                                                                           \
  inline C10_HOST_DEVICE R operator-(const CFloatWithSubnormals& left, T right)                            \
  {                                                                                                                           \
    return static_cast<R>(sw::universal::operator-(static_cast<CFloatWithSubnormals::Base>(left), right)); \
  }                                                                                                                           \
  inline C10_HOST_DEVICE R operator*(const CFloatWithSubnormals& left, T right)                            \
  {                                                                                                                           \
    return static_cast<R>(sw::universal::operator*(static_cast<CFloatWithSubnormals::Base>(left), right)); \
  }                                                                                                                           \
  inline C10_HOST_DEVICE R operator/(const CFloatWithSubnormals& left, T right)                            \
  {                                                                                                                           \
    return static_cast<R>(sw::universal::operator/(static_cast<CFloatWithSubnormals::Base>(left), right)); \
  }                                                                                                                           \
  inline C10_HOST_DEVICE R operator+(T left, const CFloatWithSubnormals& right)                            \
  {                                                                                                                           \
    return static_cast<R>(sw::universal::operator+(left, static_cast<CFloatWithSubnormals::Base>(right))); \
  }                                                                                                                           \
  inline C10_HOST_DEVICE R operator-(T left, const CFloatWithSubnormals& right)                            \
  {                                                                                                                           \
    return static_cast<R>(sw::universal::operator-(left, static_cast<CFloatWithSubnormals::Base>(right))); \
  }                                                                                                                           \
  inline C10_HOST_DEVICE R operator*(T left, const CFloatWithSubnormals& right)                            \
  {                                                                                                                           \
    return static_cast<R>(sw::universal::operator*(left, static_cast<CFloatWithSubnormals::Base>(right))); \
  }                                                                                                                           \
  inline C10_HOST_DEVICE R operator/(T left, const CFloatWithSubnormals& right)                            \
  {                                                                                                                           \
    return static_cast<R>(sw::universal::operator/(left, static_cast<CFloatWithSubnormals::Base>(right))); \
  }
FORALL_SUPPORTED_TYPES_IN_OPERATORS(OP)
#undef OP

#define OP(T)                                                                      \
  inline C10_HOST_DEVICE T& operator+=(T& left, const CFloatWithSubnormals& right) \
  {                                                                                \
    return left += static_cast<T>(right);                                          \
  }                                                                                \
  inline C10_HOST_DEVICE T& operator-=(T& left, const CFloatWithSubnormals& right) \
  {                                                                                \
    return left -= static_cast<T>(right);                                          \
  }                                                                                \
  inline C10_HOST_DEVICE T& operator*=(T& left, const CFloatWithSubnormals& right) \
  {                                                                                \
    return left *= static_cast<T>(right);                                          \
  }                                                                                \
  inline C10_HOST_DEVICE T& operator/=(T& left, const CFloatWithSubnormals& right) \
  {                                                                                \
    return left /= static_cast<T>(right);                                          \
  }
FORALL_SUPPORTED_TYPES(OP)
#undef OP

inline C10_HOST_DEVICE CFloatWithSubnormals operator+(const CFloatWithSubnormals& left, int64_t right)
{
  CFloatWithSubnormals result(left);
  result += right;
  return result;
}
inline C10_HOST_DEVICE CFloatWithSubnormals operator-(const CFloatWithSubnormals& left, int64_t right)
{
  CFloatWithSubnormals result(left);
  result -= right;
  return result;
}
inline C10_HOST_DEVICE CFloatWithSubnormals operator*(const CFloatWithSubnormals& left, int64_t right)
{
  CFloatWithSubnormals result(left);
  result *= right;
  return result;
}
inline C10_HOST_DEVICE CFloatWithSubnormals operator/(const CFloatWithSubnormals& left, int64_t right)
{
  CFloatWithSubnormals result(left);
  result /= right;
  return result;
}
inline C10_HOST_DEVICE CFloatWithSubnormals operator+(int64_t left, const CFloatWithSubnormals& right)
{
  CFloatWithSubnormals result(left);
  result += right;
  return result;
}
inline C10_HOST_DEVICE CFloatWithSubnormals operator-(int64_t left, const CFloatWithSubnormals& right)
{
  CFloatWithSubnormals result(left);
  result -= right;
  return result;
}
inline C10_HOST_DEVICE CFloatWithSubnormals operator*(int64_t left, const CFloatWithSubnormals& right)
{
  CFloatWithSubnormals result(left);
  result *= right;
  return result;
}
inline C10_HOST_DEVICE CFloatWithSubnormals operator/(int64_t left, const CFloatWithSubnormals& right)
{
  CFloatWithSubnormals result(left);
  result /= right;
  return result;
}

#undef FORALL_SUPPORTED_TYPES
#undef FORALL_SUPPORTED_TYPES_IN_OPERATORS
#undef FORALL_ADDITIONAL_TYPES

}

namespace std {

template<>
struct hash<c10::CFloatWithSubnormals> {
  size_t operator()(const c10::CFloatWithSubnormals& value) const noexcept {
    return hash<uint32_t>()(value.block(0));
  }
};

template<> class numeric_limits<c10::CFloatWithSubnormals>
{
public:
  static constexpr bool is_specialized = true;
  static constexpr c10::CFloatWithSubnormals min() { // return minimum value
    return c10::CFloatWithSubnormals(numeric_limits<c10::CFloatWithSubnormals::Base>::min());
  }
  static constexpr c10::CFloatWithSubnormals max() { // return maximum value
    return c10::CFloatWithSubnormals(numeric_limits<c10::CFloatWithSubnormals::Base>::max());
  }
  static constexpr c10::CFloatWithSubnormals lowest() { // return most negative value
    return c10::CFloatWithSubnormals(numeric_limits<c10::CFloatWithSubnormals::Base>::lowest());
  }
  static CONSTEXPRESSION c10::CFloatWithSubnormals epsilon() { // return smallest effective increment from 1.0
    return c10::CFloatWithSubnormals(numeric_limits<c10::CFloatWithSubnormals::Base>::epsilon());
  }
  static CONSTEXPRESSION c10::CFloatWithSubnormals round_error() { // return largest rounding error
    return c10::CFloatWithSubnormals(numeric_limits<c10::CFloatWithSubnormals::Base>::round_error());
  }
  static constexpr c10::CFloatWithSubnormals denorm_min() {  // return minimum denormalized value
    return c10::CFloatWithSubnormals(numeric_limits<c10::CFloatWithSubnormals::Base>::denorm_min());
  }
  static constexpr c10::CFloatWithSubnormals infinity() { // return positive infinity
    return c10::CFloatWithSubnormals(numeric_limits<c10::CFloatWithSubnormals::Base>::infinity());
  }
  static constexpr c10::CFloatWithSubnormals quiet_NaN() { // return non-signaling NaN
    return c10::CFloatWithSubnormals(numeric_limits<c10::CFloatWithSubnormals::Base>::quiet_NaN());
  }
  static constexpr c10::CFloatWithSubnormals signaling_NaN() { // return signaling NaN
    return c10::CFloatWithSubnormals(numeric_limits<c10::CFloatWithSubnormals::Base>::signaling_NaN());
  }

  static constexpr int digits       = numeric_limits<c10::CFloatWithSubnormals::Base>::digits;
  static constexpr int digits10     = numeric_limits<c10::CFloatWithSubnormals::Base>::digits10;
  static constexpr int max_digits10 = numeric_limits<c10::CFloatWithSubnormals::Base>::max_digits10;
  static constexpr bool is_signed   = numeric_limits<c10::CFloatWithSubnormals::Base>::is_signed;
  static constexpr bool is_integer  = numeric_limits<c10::CFloatWithSubnormals::Base>::is_integer;
  static constexpr bool is_exact    = numeric_limits<c10::CFloatWithSubnormals::Base>::is_exact;
  static constexpr int radix        = numeric_limits<c10::CFloatWithSubnormals::Base>::radix;

  static constexpr int min_exponent   = numeric_limits<c10::CFloatWithSubnormals::Base>::min_exponent;
  static constexpr int min_exponent10 = numeric_limits<c10::CFloatWithSubnormals::Base>::min_exponent10;
  static constexpr int max_exponent   = numeric_limits<c10::CFloatWithSubnormals::Base>::max_exponent;
  static constexpr int max_exponent10 = numeric_limits<c10::CFloatWithSubnormals::Base>::max_exponent10;
  static constexpr bool has_infinity  = numeric_limits<c10::CFloatWithSubnormals::Base>::has_infinity;
  static constexpr bool has_quiet_NaN = numeric_limits<c10::CFloatWithSubnormals::Base>::has_quiet_NaN;
  static constexpr bool has_signaling_NaN = numeric_limits<c10::CFloatWithSubnormals::Base>::has_signaling_NaN;
  static constexpr float_denorm_style has_denorm = numeric_limits<c10::CFloatWithSubnormals::Base>::has_denorm;
  static constexpr bool has_denorm_loss = numeric_limits<c10::CFloatWithSubnormals::Base>::has_denorm_loss;

  static constexpr bool is_iec559 = numeric_limits<c10::CFloatWithSubnormals::Base>::is_iec559;
  static constexpr bool is_bounded = numeric_limits<c10::CFloatWithSubnormals::Base>::is_bounded;
  static constexpr bool is_modulo = numeric_limits<c10::CFloatWithSubnormals::Base>::is_modulo;
  static constexpr bool traps = numeric_limits<c10::CFloatWithSubnormals::Base>::traps;
  static constexpr bool tinyness_before = numeric_limits<c10::CFloatWithSubnormals::Base>::tinyness_before;
  static constexpr float_round_style round_style = numeric_limits<c10::CFloatWithSubnormals::Base>::round_style;
};

}
