#pragma once

#include <c10/util/UniversalTypes/CFloatWithSubnormals/aliases.h>
#include <c10/macros/Macros.h>

// Private macro (it is removed with #undef below)
// (argument type, return type)
#define FORALL_SUPPORTED_TYPES_IN_OPERATORS(_) \
  _(int, CFloatWithSubnormals)                 \
  _(float, CFloatWithSubnormals)               \
  _(double, double) // ATen requires returning double if the argument type is double

// Redeclare operators as __host__ __device__
namespace sw {
namespace universal {

// Suppress the warnings that __host__ functions were redeclared as __host__ __device__
#pragma diag_suppress 20040

// Comparison
template<size_t nnbits, size_t nes, typename nbt, bool nsub, bool nsup, bool nsat>
inline C10_HOST_DEVICE bool operator==(
  const cfloat<nnbits,nes,nbt,nsub,nsup,nsat>& lhs,
  const cfloat<nnbits,nes,nbt,nsub,nsup,nsat>& rhs);
template<size_t nnbits, size_t nes, typename nbt, bool nsub, bool nsup, bool nsat>
inline C10_HOST_DEVICE bool operator!=(
  const cfloat<nnbits,nes,nbt,nsub,nsup,nsat>& lhs,
  const cfloat<nnbits,nes,nbt,nsub,nsup,nsat>& rhs);

#define OP(T, _)                                                                                               \
  template<size_t nbits, size_t es, typename bt, bool hasSubnormals, bool hasSupernormals, bool isSaturating>  \
  inline C10_HOST_DEVICE bool operator==(                                                                      \
    const cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating>& lhs,                            \
    T rhs);                                                                                                    \
  template<size_t nbits, size_t es, typename bt, bool hasSubnormals, bool hasSupernormals, bool isSaturating>  \
  inline C10_HOST_DEVICE bool operator!=(                                                                      \
    const cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating>& lhs,                            \
    T rhs);
FORALL_SUPPORTED_TYPES_IN_OPERATORS(OP)
#undef OP

template<size_t nnbits, size_t nes, typename nbt, bool nsub, bool nsup, bool nsat>
inline C10_HOST_DEVICE bool operator<(
  const cfloat<nnbits, nes, nbt, nsub, nsup, nsat>& lhs,
  const cfloat<nnbits, nes, nbt, nsub, nsup, nsat>& rhs);

template<size_t nnbits, size_t nes, typename nbt, bool nsub, bool nsup, bool nsat>
inline C10_HOST_DEVICE bool operator<=(
  const cfloat<nnbits, nes, nbt, nsub, nsup, nsat>& lhs,
  const cfloat<nnbits, nes, nbt, nsub, nsup, nsat>& rhs);

template<size_t nnbits, size_t nes, typename nbt, bool nsub, bool nsup, bool nsat>
inline C10_HOST_DEVICE bool operator>(
  const cfloat<nnbits, nes, nbt, nsub, nsup, nsat>& lhs,
  const cfloat<nnbits, nes, nbt, nsub, nsup, nsat>& rhs);

template<size_t nnbits, size_t nes, typename nbt, bool nsub, bool nsup, bool nsat>
inline C10_HOST_DEVICE bool operator>=(
  const cfloat<nnbits, nes, nbt, nsub, nsup, nsat>& lhs,
  const cfloat<nnbits, nes, nbt, nsub, nsup, nsat>& rhs);

// Arithmetic
template<size_t nbits, size_t es, typename bt, bool hasSubnormals, bool hasSupernormals, bool isSaturating>
inline C10_HOST_DEVICE cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> operator+(
  const cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating>& lhs,
  const cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating>& rhs);

template<size_t nbits, size_t es, typename bt, bool hasSubnormals, bool hasSupernormals, bool isSaturating>
inline C10_HOST_DEVICE cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> operator-(
  const cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating>& lhs,
  const cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating>& rhs);

template<size_t nbits, size_t es, typename bt, bool hasSubnormals, bool hasSupernormals, bool isSaturating>
inline C10_HOST_DEVICE cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> operator*(
  const cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating>& lhs,
  const cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating>& rhs);

template<size_t nbits, size_t es, typename bt, bool hasSubnormals, bool hasSupernormals, bool isSaturating>
inline C10_HOST_DEVICE cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> operator/(
  const cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating>& lhs,
  const cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating>& rhs);

// Other math functions
template<size_t nbits, size_t es, typename bt, bool hasSubnormals, bool hasSupernormals, bool isSaturating>
C10_HOST_DEVICE cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> exp(
  cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> x);

template<size_t nbits, size_t es, typename bt, bool hasSubnormals, bool hasSupernormals, bool isSaturating>
C10_HOST_DEVICE cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> log(
  cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> x);

template<size_t nbits, size_t es, typename bt, bool hasSubnormals, bool hasSupernormals, bool isSaturating>
C10_HOST_DEVICE cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> pow(
  cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> x,
  cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> y);

template<size_t nbits, size_t es, typename bt, bool hasSubnormals, bool hasSupernormals, bool isSaturating>
C10_HOST_DEVICE cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> pow(
  cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> x,
  int y);

template<size_t nbits, size_t es, typename bt, bool hasSubnormals, bool hasSupernormals, bool isSaturating>
C10_HOST_DEVICE cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> pow(
  cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> x,
  double y);


#define OP(T, _)                                                                                              \
  template<size_t nbits, size_t es, typename bt, bool hasSubnormals, bool hasSupernormals, bool isSaturating> \
  inline C10_HOST_DEVICE cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> operator+(       \
    T lhs,                                                                                                    \
    const cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating>& rhs);                          \
                                                                                                              \
  template<size_t nbits, size_t es, typename bt, bool hasSubnormals, bool hasSupernormals, bool isSaturating> \
  inline C10_HOST_DEVICE cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> operator-(       \
    T lhs,                                                                                                    \
    const cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating>& rhs);                          \
                                                                                                              \
  template<size_t nbits, size_t es, typename bt, bool hasSubnormals, bool hasSupernormals, bool isSaturating> \
  inline C10_HOST_DEVICE cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> operator*(       \
    T lhs,                                                                                                    \
    const cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating>& rhs);                          \
                                                                                                              \
  template<size_t nbits, size_t es, typename bt, bool hasSubnormals, bool hasSupernormals, bool isSaturating> \
  inline C10_HOST_DEVICE cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> operator/(       \
    T lhs,                                                                                                    \
    const cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating>& rhs);                          \
                                                                                                              \
  template<size_t nbits, size_t es, typename bt, bool hasSubnormals, bool hasSupernormals, bool isSaturating> \
  inline C10_HOST_DEVICE cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> operator+(       \
    const cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating>& lhs,                           \
    T rhs);                                                                                                   \
                                                                                                              \
  template<size_t nbits, size_t es, typename bt, bool hasSubnormals, bool hasSupernormals, bool isSaturating> \
  inline C10_HOST_DEVICE cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> operator-(       \
    const cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating>& lhs,                           \
    T rhs);                                                                                                   \
                                                                                                              \
  template<size_t nbits, size_t es, typename bt, bool hasSubnormals, bool hasSupernormals, bool isSaturating> \
  inline C10_HOST_DEVICE cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> operator*(       \
    const cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating>& lhs,                           \
    T rhs);                                                                                                   \
                                                                                                              \
  template<size_t nbits, size_t es, typename bt, bool hasSubnormals, bool hasSupernormals, bool isSaturating> \
  inline C10_HOST_DEVICE cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> operator/(       \
    const cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating>& lhs,                           \
    T rhs);
FORALL_SUPPORTED_TYPES_IN_OPERATORS(OP)
#undef OP

// min and max
template<size_t nbits, size_t es, typename bt, bool hasSubnormals, bool hasSupernormals, bool isSaturating>
C10_HOST_DEVICE cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> min(
  cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> x,
  cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> y);

template<size_t nbits, size_t es, typename bt, bool hasSubnormals, bool hasSupernormals, bool isSaturating>
C10_HOST_DEVICE cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> max(
  cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> x,
  cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> y);

// cfloat constructors
extern template C10_HOST_DEVICE CFloat::cfloat(float) noexcept;
extern template C10_HOST_DEVICE CFloat::cfloat(double) noexcept;
extern template C10_HOST_DEVICE void CFloat::setblock(size_t b, uint32_t data) noexcept;

// blockbinary constructor and methods
extern template C10_HOST_DEVICE bool BlockBinary::isallones() const noexcept;
extern template C10_HOST_DEVICE bool BlockBinary::iszero() const noexcept;
extern template C10_HOST_DEVICE void BlockBinary::clear() noexcept;
extern template C10_HOST_DEVICE void BlockBinary::setbits(uint64_t value) noexcept;
#pragma push_macro("setbit")
#undef setbit
extern template C10_HOST_DEVICE void BlockBinary::setbit(size_t i, bool v) noexcept;
#pragma pop_macro("setbit")

// cfloat methods that handle blockbinary
extern template C10_HOST_DEVICE void CFloat::exponent(
  BlockBinary& e) const;

// isnan, isinf, and necessary methods
template<size_t nbits, size_t es, typename bt, bool hasSubnormals, bool hasSupernormals, bool isSaturating>
inline C10_HOST_DEVICE bool isnan(const cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating>& a);

template<size_t nbits, size_t es, typename bt, bool hasSubnormals, bool hasSupernormals, bool isSaturating>
inline C10_HOST_DEVICE bool isinf(const cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating>& a);

extern template C10_HOST_DEVICE bool CFloat::isnan(int NaNType) const noexcept;
extern template C10_HOST_DEVICE bool CFloat::isnanencoding(int NaNType) const noexcept;
extern template C10_HOST_DEVICE bool CFloat::issupernormal() const noexcept;
extern template C10_HOST_DEVICE bool CFloat::isinf(int InfType) const noexcept;
extern template C10_HOST_DEVICE bool CFloat::ispos() const noexcept;
extern template C10_HOST_DEVICE bool CFloat::isneg() const noexcept;
extern template C10_HOST_DEVICE bool CFloat::sign() const noexcept;

// Conversion to float and necessary methods
extern template C10_HOST_DEVICE CFloat::operator float() const noexcept;
extern template C10_HOST_DEVICE bool CFloat::iszero() const noexcept;
extern template C10_HOST_DEVICE bool CFloat::iszeroencoding() const noexcept;
extern template C10_HOST_DEVICE bool CFloat::at(size_t bitIndex) const noexcept;

// Conversion from float and necessary methods
template C10_HOST_DEVICE CFloat&
  CFloat::convert_ieee754<float>(float rhs) noexcept;
extern template C10_HOST_DEVICE void CFloat::setnan(int NaNType) noexcept;
extern template C10_HOST_DEVICE void CFloat::setinf(bool sign) noexcept;
extern template C10_HOST_DEVICE void CFloat::clear() noexcept;
extern template C10_HOST_DEVICE CFloat& CFloat::flip() noexcept;
extern template C10_HOST_DEVICE CFloat& CFloat::maxneg() noexcept;
extern template C10_HOST_DEVICE CFloat& CFloat::maxpos() noexcept;
extern template C10_HOST_DEVICE void CFloat::setsign(bool sign);
extern template C10_HOST_DEVICE void CFloat::shiftLeft(int leftShift);
extern template C10_HOST_DEVICE void CFloat::shiftRight(int rightShift);

// Explicit type casts to types other than float
extern template C10_HOST_DEVICE CFloat::operator int() const noexcept;
extern template C10_HOST_DEVICE CFloat::operator long() const noexcept;
extern template C10_HOST_DEVICE CFloat::operator long long() const noexcept;
extern template C10_HOST_DEVICE CFloat::operator double() const noexcept;
extern template C10_HOST_DEVICE int CFloat::to_int() const;
extern template C10_HOST_DEVICE long CFloat::to_long() const;
extern template C10_HOST_DEVICE long long CFloat::to_long_long() const;

// extractFields and necessary functions (required for conversion from float and from double)
inline C10_HOST_DEVICE void extractFields(float value, bool& s, uint64_t& rawExponentBits, uint64_t& rawFractionBits);

// operator=
extern template C10_HOST_DEVICE CFloat& CFloat::operator=(
  float rhs) noexcept;

// to_native
// FIXME extern template causes "Undefined reference" error. Fix it and move instantiation to UniversalTypes.cpp
template C10_HOST_DEVICE float CFloat::to_native<float>() const;
template C10_HOST_DEVICE double CFloat::to_native<double>() const;

#pragma diag_default 20040

}
}

#undef FORALL_SUPPORTED_TYPES_IN_OPERATORS
