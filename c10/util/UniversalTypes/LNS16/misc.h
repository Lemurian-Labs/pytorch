#pragma once

#include <c10/util/UniversalTypes/LNS16/aliases.h>
#include <c10/macros/Macros.h>

// Redeclare operators as __host__ __device__
namespace sw {
namespace universal {

// Suppress the warnings that __host__ functions were redeclared as __host__ __device__
#pragma diag_suppress 20040

// Specific value constructor
template CUDA_NOINLINE C10_HOST_DEVICE LNS16::lns(const SpecificValue code) noexcept;
// Type conversion
template CUDA_NOINLINE C10_HOST_DEVICE LNS16::operator float() const noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE float LNS16::to_ieee754<float>() const noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16::operator double() const noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE double LNS16::to_ieee754<double>() const noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16::operator int() const noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE int LNS16::to_signed<int>() const;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16::operator long() const noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE long LNS16::to_signed<long>() const;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16::operator long long() const noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE long long LNS16::to_signed<long long>() const;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16::lns(float initial_value) noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16& LNS16::operator=(float rhs) noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16& LNS16::convert_ieee754<float>(float v) noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16::lns(double initial_value) noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16& LNS16::operator=(double rhs) noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16& LNS16::convert_ieee754<double>(double v) noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16::lns(signed char initial_value) noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16& LNS16::operator=(signed char rhs) noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16& LNS16::convert_signed<signed char>(signed char v) noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16::lns(short initial_value) noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16& LNS16::operator=(short rhs) noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16& LNS16::convert_signed<short>(short v) noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16::lns(int initial_value) noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16& LNS16::operator=(int rhs) noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16& LNS16::convert_signed<int>(int v) noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16::lns(long long initial_value) noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16& LNS16::operator=(long long rhs) noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16& LNS16::convert_signed<long long>(long long v) noexcept;
// Type conversion for additional types
template CUDA_NOINLINE C10_HOST_DEVICE LNS16& LNS16::convert_unsigned<unsigned char>(unsigned char v) noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16& LNS16::convert_unsigned<bool>(bool v) noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16& LNS16::convert_signed<long>(long v) noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16& LNS16::convert_unsigned<uint64_t>(uint64_t v) noexcept;

// Methods
template CUDA_NOINLINE C10_HOST_DEVICE bool LNS16::isnan() const noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE void LNS16::setnan() noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE bool LNS16::sign() const noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE void LNS16::setsign(bool s) noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE bool LNS16::iszero() const noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE void LNS16::setzero() noexcept;
#pragma push_macro("setbit")
#undef setbit
template CUDA_NOINLINE C10_HOST_DEVICE void LNS16::setbit(size_t i, bool v) noexcept;
#pragma pop_macro("setbit")
template CUDA_NOINLINE C10_HOST_DEVICE void LNS16::setbits(uint64_t value) noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE void LNS16::setinf(bool sign) noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16& LNS16::minneg() noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16& LNS16::maxneg() noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16& LNS16::minpos() noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16& LNS16::maxpos() noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16& LNS16::zero() noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE void LNS16::clear() noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16& LNS16::flip() noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE bool LNS16::at(size_t bitIndex) const noexcept;

// Comparison operators
constexpr C10_HOST_DEVICE bool operator==(const LNS16& lhs, const LNS16& rhs);
constexpr C10_HOST_DEVICE bool operator!=(const LNS16& lhs, const LNS16& rhs);
constexpr C10_HOST_DEVICE bool operator<(const LNS16& lhs, const LNS16& rhs);
constexpr C10_HOST_DEVICE bool operator>(const LNS16& lhs, const LNS16& rhs);
constexpr C10_HOST_DEVICE bool operator<=(const LNS16& lhs, const LNS16& rhs);
constexpr C10_HOST_DEVICE bool operator>=(const LNS16& lhs, const LNS16& rhs);
constexpr C10_HOST_DEVICE bool operator==(const LNS16& lhs, double rhs);
constexpr C10_HOST_DEVICE bool operator!=(const LNS16& lhs, double rhs);
constexpr C10_HOST_DEVICE bool operator<(const LNS16& lhs, double rhs);
constexpr C10_HOST_DEVICE bool operator>(const LNS16& lhs, double rhs);
constexpr C10_HOST_DEVICE bool operator<=(const LNS16& lhs, double rhs);
constexpr C10_HOST_DEVICE bool operator>=(const LNS16& lhs, double rhs);

template<size_t nbits, size_t rbits, typename bt, auto... xtra>
C10_HOST_DEVICE lns<nbits, rbits, bt, xtra...> min(lns<nbits, rbits, bt, xtra...> x, lns<nbits, rbits, bt, xtra...> y);
template<size_t nbits, size_t rbits, typename bt, auto... xtra>
C10_HOST_DEVICE lns<nbits, rbits, bt, xtra...> max(lns<nbits, rbits, bt, xtra...> x, lns<nbits, rbits, bt, xtra...> y);

template<size_t nbits, size_t rbits, typename bt, auto... xtra>
inline C10_HOST_DEVICE bool isinf(const lns<nbits, rbits, bt, xtra...>& a);
template<size_t nbits, size_t rbits, typename bt, auto... xtra>
inline C10_HOST_DEVICE bool isnan(const lns<nbits, rbits, bt, xtra...>& a);

// LNS17 type conversion for convert_ieee754
template CUDA_NOINLINE C10_HOST_DEVICE LNS17::operator float() const noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE float LNS17::to_ieee754<float>() const noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS17::operator double() const noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE double LNS17::to_ieee754<double>() const noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE bool LNS17::isnan() const noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE bool LNS17::iszero() const noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE bool LNS17::sign() const noexcept;


#pragma diag_default 20040

}
}
