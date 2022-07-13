#pragma once

#pragma push_macro("setbit")
#undef setbit
#include <universal/number/lns/lns.hpp>
#pragma pop_macro("setbit")

#include <c10/util/BFloat16.h>
#include <c10/util/Half.h>

#include <type_traits>

// Private macro (it is removed with #undef below)
#define FORALL_SUPPORTED_TYPES(_) \
  _(signed char)                  \
  _(short)                        \
  _(int)                          \
  _(long long)                    \
  _(float)                        \
  _(double)

// Private macro (it is removed with #undef below)
// (argument type, return type, left operand type, right operand type)
#define FORALL_SUPPORTED_TYPES_IN_OPERATORS(_) \
  _(int, LNS16, LNS16::Base, LNS16::Base)      \
  _(float, float, float, float)                \
  _(double, double, double, double)

// Private macro (it is removed with #undef below)
#define FORALL_ADDITIONAL_TYPES(_) \
  _(unsigned char)                 \
  _(long)                          \
  _(uint64_t)

namespace c10 {


class alignas(2) LNS16 : public sw::universal::lns<16, 8, uint16_t>
{
public:
  using Base = sw::universal::lns<16, 8, uint16_t>;

  LNS16() = default;

  C10_HOST_DEVICE LNS16(float value) : Base(value) {}
  constexpr C10_HOST_DEVICE LNS16(Base value) : Base(value) {}

  // A way to construct LNS16 from bits similar to Half and BFloat16
  struct from_bits_t {};
  static constexpr C10_HOST_DEVICE from_bits_t from_bits()
  {
    return from_bits_t();
  }

  constexpr C10_HOST_DEVICE LNS16(uint16_t bits, from_bits_t) :
    Base()
  {
    // FIXME
  }

  C10_HOST_DEVICE operator float() const noexcept
  {
    return Base::operator float();
  }

  // Define operator < to avoid ambiguity
  C10_HOST_DEVICE bool operator<(const LNS16& right) const
  {
    return sw::universal::operator<(
      static_cast<Base>(*this),
      static_cast<Base>(right));
  }
  C10_HOST_DEVICE bool operator<=(const LNS16& right) const
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
  #undef OP
  #define OP(T)                                        \
    C10_HOST_DEVICE bool operator<(T right) const      \
    {                                                  \
      return sw::universal::operator<(                 \
        static_cast<Base>(*this),                      \
        static_cast<Base>(static_cast<LNS16>(right))); \
    }                                                  \
    C10_HOST_DEVICE bool operator<=(T right) const     \
    {                                                  \
      return sw::universal::operator<=(                \
        static_cast<Base>(*this),                      \
        static_cast<Base>(static_cast<LNS16>(right))); \
    }
  FORALL_ADDITIONAL_TYPES(OP)
  #undef OP

  // Define operator > to avoid ambiguity
  C10_HOST_DEVICE bool operator>(const LNS16& right) const
  {
    return sw::universal::operator>(
      static_cast<Base>(*this),
      static_cast<Base>(right));
  }
  C10_HOST_DEVICE bool operator>=(const LNS16& right) const
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
  #undef OP
  #define OP(T)                                        \
    C10_HOST_DEVICE bool operator>(T right) const      \
    {                                                  \
      return sw::universal::operator>(                 \
        static_cast<Base>(*this),                      \
        static_cast<Base>(static_cast<LNS16>(right))); \
    }                                                  \
    C10_HOST_DEVICE bool operator>=(T right) const     \
    {                                                  \
      return sw::universal::operator>=(                \
        static_cast<Base>(*this),                      \
        static_cast<Base>(static_cast<LNS16>(right))); \
    }
  FORALL_ADDITIONAL_TYPES(OP)
  #undef OP

  // Assignment operators
  #define OP(T)                               \
    C10_HOST_DEVICE LNS16& operator=(T value) \
    {                                         \
      Base::operator=(value);                 \
      return *this;                           \
    }
  FORALL_SUPPORTED_TYPES(OP)
  #undef OP
  C10_HOST_DEVICE LNS16& operator=(unsigned char value)
  {
    convert_unsigned(value);
    return *this;
  }
  C10_HOST_DEVICE LNS16& operator=(bool value)
  {
    convert_signed(value);
    return *this;
  }
  C10_HOST_DEVICE LNS16& operator=(long value)
  {
    convert_signed(value);
    return *this;
  }
  C10_HOST_DEVICE LNS16& operator=(uint64_t value)
  {
    convert_unsigned(value);
    return *this;
  }
  C10_HOST_DEVICE LNS16& operator=(c10::BFloat16 value)
  {
    Base::operator=(static_cast<float>(value));
    return *this;
  }
  C10_HOST_DEVICE LNS16& operator=(c10::Half value)
  {
    Base::operator=(static_cast<float>(value));
    return *this;
  }

  // Arithmetic operators
  // ATen requires unary minus to be constexpr
  constexpr C10_HOST_DEVICE LNS16 operator-() const
  {
    return *this; // FIXME
  }
  C10_HOST_DEVICE LNS16& operator+=(const LNS16& right)
  {
    return static_cast<LNS16&>(Base::operator+=(right));
  }
  C10_HOST_DEVICE LNS16& operator-=(const LNS16& right)
  {
    return static_cast<LNS16&>(Base::operator-=(right));
  }
  C10_HOST_DEVICE LNS16& operator*=(const LNS16& right)
  {
    return static_cast<LNS16&>(Base::operator*=(right));
  }
  C10_HOST_DEVICE LNS16& operator/=(const LNS16& right)
  {
    return static_cast<LNS16&>(Base::operator/=(right));
  }
};

// Nonmember comparison operators
#define OP(T)                                                        \
  inline C10_HOST_DEVICE bool operator<(T left, const LNS16& right)  \
  {                                                                  \
    return sw::universal::operator<(                                 \
      static_cast<LNS16::Base>(left),                                \
      static_cast<LNS16::Base>(right));                              \
  }                                                                  \
  inline C10_HOST_DEVICE bool operator<=(T left, const LNS16& right) \
  {                                                                  \
    return sw::universal::operator<=(                                \
      static_cast<LNS16::Base>(left),                                \
      static_cast<LNS16::Base>(right));                              \
  }
FORALL_SUPPORTED_TYPES(OP)
#undef OP
#define OP(T)                                                        \
  inline C10_HOST_DEVICE bool operator<(T left, const LNS16& right)  \
  {                                                                  \
    return sw::universal::operator<(                                 \
      static_cast<LNS16::Base>(static_cast<LNS16>(left)),            \
      static_cast<LNS16::Base>(right));                              \
  }                                                                  \
  inline C10_HOST_DEVICE bool operator<=(T left, const LNS16& right) \
  {                                                                  \
    return sw::universal::operator<=(                                \
      static_cast<LNS16::Base>(static_cast<LNS16>(left)),            \
      static_cast<LNS16::Base>(right));                              \
  }
FORALL_ADDITIONAL_TYPES(OP)
#undef OP

#define OP(T)                                                        \
  inline C10_HOST_DEVICE bool operator>(T left, const LNS16& right)  \
  {                                                                  \
    return sw::universal::operator>(                                 \
      static_cast<LNS16::Base>(left),                                \
      static_cast<LNS16::Base>(right));                              \
  }                                                                  \
  inline C10_HOST_DEVICE bool operator>=(T left, const LNS16& right) \
  {                                                                  \
    return sw::universal::operator>=(                                \
      static_cast<LNS16::Base>(left),                                \
      static_cast<LNS16::Base>(right));                              \
  }
FORALL_SUPPORTED_TYPES(OP)
#undef OP
#define OP(T)                                                        \
  inline C10_HOST_DEVICE bool operator>(T left, const LNS16& right)  \
  {                                                                  \
    return sw::universal::operator>(                                 \
      static_cast<LNS16::Base>(static_cast<LNS16>(left)),            \
      static_cast<LNS16::Base>(right));                              \
  }                                                                  \
  inline C10_HOST_DEVICE bool operator>=(T left, const LNS16& right) \
  {                                                                  \
    return sw::universal::operator>=(                                \
      static_cast<LNS16::Base>(static_cast<LNS16>(left)),            \
      static_cast<LNS16::Base>(right));                              \
  }
FORALL_ADDITIONAL_TYPES(OP)
#undef OP

// Nonmember arithmetic operators
inline C10_HOST_DEVICE LNS16 operator+(const LNS16& left, const LNS16& right)
{
  return static_cast<LNS16>(sw::universal::operator+(
    static_cast<LNS16::Base>(left),
    static_cast<LNS16::Base>(right)));
}
inline C10_HOST_DEVICE LNS16 operator-(const LNS16& left, const LNS16& right)
{
  return static_cast<LNS16>(sw::universal::operator-(
    static_cast<LNS16::Base>(left),
    static_cast<LNS16::Base>(right)));
}
inline C10_HOST_DEVICE LNS16 operator*(const LNS16& left, const LNS16& right)
{
  return static_cast<LNS16>(sw::universal::operator*(
    static_cast<LNS16::Base>(left),
    static_cast<LNS16::Base>(right)));
}
inline C10_HOST_DEVICE LNS16 operator/(const LNS16& left, const LNS16& right)
{
  return static_cast<LNS16>(sw::universal::operator/(
    static_cast<LNS16::Base>(left),
    static_cast<LNS16::Base>(right)));
}

#define OP(T, R, Left, Right)                                                   \
  inline C10_HOST_DEVICE R operator+(const LNS16& left, T right)                \
  {                                                                             \
    return static_cast<R>(static_cast<Left>(left) + static_cast<Right>(right)); \
  }                                                                             \
  inline C10_HOST_DEVICE R operator-(const LNS16& left, T right)                \
  {                                                                             \
    return static_cast<R>(static_cast<Left>(left) + static_cast<Right>(right)); \
  }                                                                             \
  inline C10_HOST_DEVICE R operator*(const LNS16& left, T right)                \
  {                                                                             \
    return static_cast<R>(static_cast<Left>(left) + static_cast<Right>(right)); \
  }                                                                             \
  inline C10_HOST_DEVICE R operator/(const LNS16& left, T right)                \
  {                                                                             \
    return static_cast<R>(static_cast<Left>(left) + static_cast<Right>(right)); \
  }                                                                             \
  inline C10_HOST_DEVICE R operator+(T left, const LNS16& right)                \
  {                                                                             \
    return static_cast<R>(static_cast<Left>(left) + static_cast<Right>(right)); \
  }                                                                             \
  inline C10_HOST_DEVICE R operator-(T left, const LNS16& right)                \
  {                                                                             \
    return static_cast<R>(static_cast<Left>(left) + static_cast<Right>(right)); \
  }                                                                             \
  inline C10_HOST_DEVICE R operator*(T left, const LNS16& right)                \
  {                                                                             \
    return static_cast<R>(static_cast<Left>(left) + static_cast<Right>(right)); \
  }                                                                             \
  inline C10_HOST_DEVICE R operator/(T left, const LNS16& right)                \
  {                                                                             \
    return static_cast<R>(static_cast<Left>(left) + static_cast<Right>(right)); \
  }
FORALL_SUPPORTED_TYPES_IN_OPERATORS(OP)
#undef OP

#define OP(T)                                                       \
  inline C10_HOST_DEVICE T& operator+=(T& left, const LNS16& right) \
  {                                                                 \
    return left += static_cast<T>(right);                           \
  }                                                                 \
  inline C10_HOST_DEVICE T& operator-=(T& left, const LNS16& right) \
  {                                                                 \
    return left -= static_cast<T>(right);                           \
  }                                                                 \
  inline C10_HOST_DEVICE T& operator*=(T& left, const LNS16& right) \
  {                                                                 \
    return left *= static_cast<T>(right);                           \
  }                                                                 \
  inline C10_HOST_DEVICE T& operator/=(T& left, const LNS16& right) \
  {                                                                 \
    return left /= static_cast<T>(right);                           \
  }
FORALL_SUPPORTED_TYPES(OP)
#undef OP

inline C10_HOST_DEVICE LNS16 operator+(const LNS16& left, int64_t right)
{
  LNS16 result(left);
  result += right;
  return result;
}
inline C10_HOST_DEVICE LNS16 operator-(const LNS16& left, int64_t right)
{
  LNS16 result(left);
  result -= right;
  return result;
}
inline C10_HOST_DEVICE LNS16 operator*(const LNS16& left, int64_t right)
{
  LNS16 result(left);
  result *= right;
  return result;
}
inline C10_HOST_DEVICE LNS16 operator/(const LNS16& left, int64_t right)
{
  LNS16 result(left);
  result /= right;
  return result;
}
inline C10_HOST_DEVICE LNS16 operator+(int64_t left, const LNS16& right)
{
  LNS16 result(left);
  result += right;
  return result;
}
inline C10_HOST_DEVICE LNS16 operator-(int64_t left, const LNS16& right)
{
  LNS16 result(left);
  result -= right;
  return result;
}
inline C10_HOST_DEVICE LNS16 operator*(int64_t left, const LNS16& right)
{
  LNS16 result(left);
  result *= right;
  return result;
}
inline C10_HOST_DEVICE LNS16 operator/(int64_t left, const LNS16& right)
{
  LNS16 result(left);
  result /= right;
  return result;
}

#undef FORALL_SUPPORTED_TYPES
#undef FORALL_SUPPORTED_TYPES_IN_OPERATORS
#undef FORALL_ADDITIONAL_TYPES

}

namespace std {

template<>
struct hash<c10::LNS16> {
size_t operator()(const c10::LNS16& value) const noexcept {
  return hash<uint16_t>()(value.block(0));
}
};

template<> class numeric_limits<c10::LNS16>
{
public:
  static constexpr bool is_specialized = true;
  static constexpr c10::LNS16 min() { // return minimum value
    return c10::LNS16(numeric_limits<c10::LNS16::Base>::min());
  }
  static constexpr c10::LNS16 max() { // return maximum value
    return c10::LNS16(numeric_limits<c10::LNS16::Base>::max());
  }
  static constexpr c10::LNS16 lowest() { // return most negative value
    return c10::LNS16(numeric_limits<c10::LNS16::Base>::lowest());
  }
  static CONSTEXPRESSION c10::LNS16 epsilon() { // return smallest effective increment from 1.0
    return c10::LNS16(numeric_limits<c10::LNS16::Base>::epsilon());
  }
  static CONSTEXPRESSION c10::LNS16 round_error() { // return largest rounding error
    return c10::LNS16(numeric_limits<c10::LNS16::Base>::round_error());
  }
  static constexpr c10::LNS16 denorm_min() {  // return minimum denormalized value
    return c10::LNS16(numeric_limits<c10::LNS16::Base>::denorm_min());
  }
  static constexpr c10::LNS16 infinity() { // return positive infinity
    return c10::LNS16(); // FIXME
    // return c10::LNS16(numeric_limits<c10::LNS16::Base>::infinity());
  }
  static constexpr c10::LNS16 quiet_NaN() { // return non-signaling NaN
    return c10::LNS16(numeric_limits<c10::LNS16::Base>::quiet_NaN());
  }
  static constexpr c10::LNS16 signaling_NaN() { // return signaling NaN
    return c10::LNS16(numeric_limits<c10::LNS16::Base>::signaling_NaN());
  }

  static constexpr int digits       = numeric_limits<c10::LNS16::Base>::digits;
  static constexpr int digits10     = numeric_limits<c10::LNS16::Base>::digits10;
  static constexpr int max_digits10 = numeric_limits<c10::LNS16::Base>::max_digits10;
  static constexpr bool is_signed   = numeric_limits<c10::LNS16::Base>::is_signed;
  static constexpr bool is_integer  = numeric_limits<c10::LNS16::Base>::is_integer;
  static constexpr bool is_exact    = numeric_limits<c10::LNS16::Base>::is_exact;
  static constexpr int radix        = numeric_limits<c10::LNS16::Base>::radix;

  static constexpr int min_exponent   = numeric_limits<c10::LNS16::Base>::min_exponent;
  static constexpr int min_exponent10 = numeric_limits<c10::LNS16::Base>::min_exponent10;
  static constexpr int max_exponent   = numeric_limits<c10::LNS16::Base>::max_exponent;
  static constexpr int max_exponent10 = numeric_limits<c10::LNS16::Base>::max_exponent10;
  static constexpr bool has_infinity  = numeric_limits<c10::LNS16::Base>::has_infinity;
  static constexpr bool has_quiet_NaN = numeric_limits<c10::LNS16::Base>::has_quiet_NaN;
  static constexpr bool has_signaling_NaN = numeric_limits<c10::LNS16::Base>::has_signaling_NaN;
  static constexpr float_denorm_style has_denorm = numeric_limits<c10::LNS16::Base>::has_denorm;
  static constexpr bool has_denorm_loss = numeric_limits<c10::LNS16::Base>::has_denorm_loss;

  static constexpr bool is_iec559 = numeric_limits<c10::LNS16::Base>::is_iec559;
  static constexpr bool is_bounded = numeric_limits<c10::LNS16::Base>::is_bounded;
  static constexpr bool is_modulo = numeric_limits<c10::LNS16::Base>::is_modulo;
  static constexpr bool traps = numeric_limits<c10::LNS16::Base>::traps;
  static constexpr bool tinyness_before = numeric_limits<c10::LNS16::Base>::tinyness_before;
  static constexpr float_round_style round_style = numeric_limits<c10::LNS16::Base>::round_style;
};

}
