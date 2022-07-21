#pragma once

#include <c10/util/UniversalTypes/LNS16/aliases.h>
#include <c10/macros/Macros.h>

// Redeclare operators as __host__ __device__
namespace sw {
namespace universal {

// Suppress the warnings that __host__ functions were redeclared as __host__ __device__
#pragma diag_suppress 20040

// Type conversion
template C10_HOST_DEVICE LNS16::operator float() const noexcept;
template C10_HOST_DEVICE float LNS16::to_ieee754<float>() const noexcept;
template C10_HOST_DEVICE LNS16::operator double() const noexcept;
template C10_HOST_DEVICE double LNS16::to_ieee754<double>() const noexcept;
template C10_HOST_DEVICE LNS16::operator int() const noexcept;
template C10_HOST_DEVICE int LNS16::to_signed<int>() const;
template C10_HOST_DEVICE LNS16::operator long() const noexcept;
template C10_HOST_DEVICE long LNS16::to_signed<long>() const;
template C10_HOST_DEVICE LNS16::operator long long() const noexcept;
template C10_HOST_DEVICE long long LNS16::to_signed<long long>() const;
template C10_HOST_DEVICE LNS16::lns(float initial_value) noexcept;
template C10_HOST_DEVICE LNS16& LNS16::operator=(float rhs) noexcept;
template C10_HOST_DEVICE LNS16& LNS16::convert_ieee754<float>(float v) noexcept;
template C10_HOST_DEVICE LNS16::lns(double initial_value) noexcept;
template C10_HOST_DEVICE LNS16& LNS16::operator=(double rhs) noexcept;
template C10_HOST_DEVICE LNS16& LNS16::convert_ieee754<double>(double v) noexcept;
template C10_HOST_DEVICE LNS16::lns(signed char initial_value) noexcept;
template C10_HOST_DEVICE LNS16& LNS16::operator=(signed char rhs) noexcept;
template C10_HOST_DEVICE LNS16& LNS16::convert_signed<signed char>(signed char v) noexcept;
template C10_HOST_DEVICE LNS16::lns(short initial_value) noexcept;
template C10_HOST_DEVICE LNS16& LNS16::operator=(short rhs) noexcept;
template C10_HOST_DEVICE LNS16& LNS16::convert_signed<short>(short v) noexcept;
template C10_HOST_DEVICE LNS16::lns(int initial_value) noexcept;
template C10_HOST_DEVICE LNS16& LNS16::operator=(int rhs) noexcept;
template C10_HOST_DEVICE LNS16& LNS16::convert_signed<int>(int v) noexcept;
template C10_HOST_DEVICE LNS16::lns(long long initial_value) noexcept;
template C10_HOST_DEVICE LNS16& LNS16::operator=(long long rhs) noexcept;
template C10_HOST_DEVICE LNS16& LNS16::convert_signed<long long>(long long v) noexcept;
// Type conversion for additional types
template C10_HOST_DEVICE LNS16& LNS16::convert_unsigned<unsigned char>(unsigned char v) noexcept;
template C10_HOST_DEVICE LNS16& LNS16::convert_unsigned<bool>(bool v) noexcept;
template C10_HOST_DEVICE LNS16& LNS16::convert_signed<long>(long v) noexcept;
template C10_HOST_DEVICE LNS16& LNS16::convert_unsigned<uint64_t>(uint64_t v) noexcept;

// Methods
template C10_HOST_DEVICE bool LNS16::isnan() const noexcept;
template C10_HOST_DEVICE void LNS16::setnan() noexcept;
template C10_HOST_DEVICE bool LNS16::sign() const noexcept;
template C10_HOST_DEVICE void LNS16::setsign(bool s) noexcept;
template C10_HOST_DEVICE bool LNS16::iszero() const noexcept;
template C10_HOST_DEVICE void LNS16::setzero() noexcept;
template C10_HOST_DEVICE void LNS16::setbits(uint64_t value) noexcept;
template C10_HOST_DEVICE void LNS16::setinf(bool sign) noexcept;
template C10_HOST_DEVICE LNS16& LNS16::maxneg() noexcept;
template C10_HOST_DEVICE LNS16& LNS16::maxpos() noexcept;
template C10_HOST_DEVICE void LNS16::clear() noexcept;
template C10_HOST_DEVICE LNS16& LNS16::flip() noexcept;
template C10_HOST_DEVICE bool LNS16::at(size_t bitIndex) const noexcept;

// Comparison operators
template<size_t nnbits, size_t rrbits, typename nbt>
inline C10_HOST_DEVICE bool operator==(const lns<nnbits, rrbits, nbt>& lhs, const lns<nnbits, rrbits, nbt>& rhs);
template<size_t nnbits, size_t rrbits, typename nbt>
inline C10_HOST_DEVICE bool operator!=(const lns<nnbits, rrbits, nbt>& lhs, const lns<nnbits, rrbits, nbt>& rhs);
template<size_t nnbits, size_t rrbits, typename nbt>
inline C10_HOST_DEVICE bool operator<(const lns<nnbits, rrbits, nbt>& lhs, const lns<nnbits, rrbits, nbt>& rhs);
template<size_t nnbits, size_t rrbits, typename nbt>
inline C10_HOST_DEVICE bool operator>(const lns<nnbits, rrbits, nbt>& lhs, const lns<nnbits, rrbits, nbt>& rhs);
template<size_t nnbits, size_t rrbits, typename nbt>
inline C10_HOST_DEVICE bool operator<=(const lns<nnbits, rrbits, nbt>& lhs, const lns<nnbits, rrbits, nbt>& rhs);
template<size_t nnbits, size_t rrbits, typename nbt>
inline C10_HOST_DEVICE bool operator>=(const lns<nnbits, rrbits, nbt>& lhs, const lns<nnbits, rrbits, nbt>& rhs);
template<size_t nnbits, size_t rrbits, typename nbt>
inline C10_HOST_DEVICE bool operator==(const lns<nnbits, rrbits, nbt>& lhs, double rhs);
template<size_t nnbits, size_t rrbits, typename nbt>
inline C10_HOST_DEVICE bool operator!=(const lns<nnbits, rrbits, nbt>& lhs, double rhs);
template<size_t nnbits, size_t rrbits, typename nbt>
inline C10_HOST_DEVICE bool operator<(const lns<nnbits, rrbits, nbt>& lhs, double rhs);
template<size_t nnbits, size_t rrbits, typename nbt>
inline C10_HOST_DEVICE bool operator>(const lns<nnbits, rrbits, nbt>& lhs, double rhs);
template<size_t nnbits, size_t rrbits, typename nbt>
inline C10_HOST_DEVICE bool operator<=(const lns<nnbits, rrbits, nbt>& lhs, double rhs);
template<size_t nnbits, size_t rrbits, typename nbt>
inline C10_HOST_DEVICE bool operator>=(const lns<nnbits, rrbits, nbt>& lhs, double rhs);


#pragma diag_default 20040

}
}
