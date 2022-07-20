#pragma once

#include <c10/util/UniversalTypes/LNS16/aliases.h>
#include <c10/macros/Macros.h>

// Redeclare operators as __host__ __device__
namespace sw {
namespace universal {

// Suppress the warnings that __host__ functions were redeclared as __host__ __device__
#pragma diag_suppress 20040

// Type conversion
extern template C10_HOST_DEVICE LNS16::operator float() const noexcept;
extern template C10_HOST_DEVICE float LNS16::to_ieee754<float>() const noexcept;
extern template C10_HOST_DEVICE LNS16::operator double() const noexcept;
extern template C10_HOST_DEVICE double LNS16::to_ieee754<double>() const noexcept;
extern template C10_HOST_DEVICE LNS16::operator int() const noexcept;
extern template C10_HOST_DEVICE LNS16& LNS16::convert_ieee754<float>(float v) noexcept;
extern template C10_HOST_DEVICE LNS16& LNS16::convert_ieee754<double>(double v) noexcept;

// Methods
extern template C10_HOST_DEVICE bool LNS16::isnan() const noexcept;
extern template C10_HOST_DEVICE void LNS16::setnan() noexcept;
extern template C10_HOST_DEVICE bool LNS16::sign() const noexcept;
extern template C10_HOST_DEVICE void LNS16::setsign(bool s) noexcept;
extern template C10_HOST_DEVICE bool LNS16::iszero() const noexcept;
extern template C10_HOST_DEVICE void LNS16::setzero() noexcept;
extern template C10_HOST_DEVICE void LNS16::setbits(uint64_t value) noexcept;
extern template C10_HOST_DEVICE void LNS16::setinf(bool sign) noexcept;
extern template C10_HOST_DEVICE LNS16& LNS16::maxneg() noexcept;
extern template C10_HOST_DEVICE LNS16& LNS16::maxpos() noexcept;
extern template C10_HOST_DEVICE void LNS16::clear() noexcept;
extern template C10_HOST_DEVICE LNS16& LNS16::flip() noexcept;

// Comparison operators
extern template C10_HOST_DEVICE bool operator==(const LNS16& lhs, const LNS16& rhs);
extern template C10_HOST_DEVICE bool operator!=(const LNS16& lhs, const LNS16& rhs);
extern template C10_HOST_DEVICE bool operator<(const LNS16& lhs, const LNS16& rhs);
extern template C10_HOST_DEVICE bool operator>(const LNS16& lhs, const LNS16& rhs);
extern template C10_HOST_DEVICE bool operator<=(const LNS16& lhs, const LNS16& rhs);
extern template C10_HOST_DEVICE bool operator>=(const LNS16& lhs, const LNS16& rhs);
extern template C10_HOST_DEVICE bool operator==(const LNS16& lhs, double rhs);
extern template C10_HOST_DEVICE bool operator!=(const LNS16& lhs, double rhs);
extern template C10_HOST_DEVICE bool operator<(const LNS16& lhs, double rhs);
extern template C10_HOST_DEVICE bool operator>(const LNS16& lhs, double rhs);
extern template C10_HOST_DEVICE bool operator<=(const LNS16& lhs, double rhs);
extern template C10_HOST_DEVICE bool operator>=(const LNS16& lhs, double rhs);

template<size_t nnbits, size_t rrbits, typename nbt>
bool C10_HOST_DEVICE operator==(const lns<nnbits, rrbits, nbt>& lhs, const lns<nnbits, rrbits, nbt>& rhs);
template<size_t nnbits, size_t rrbits, typename nbt>
bool C10_HOST_DEVICE operator!=(const lns<nnbits, rrbits, nbt>& lhs, const lns<nnbits, rrbits, nbt>& rhs);
template<size_t nnbits, size_t rrbits, typename nbt>
bool C10_HOST_DEVICE operator<(const lns<nnbits, rrbits, nbt>& lhs, const lns<nnbits, rrbits, nbt>& rhs);
template<size_t nnbits, size_t rrbits, typename nbt>
bool C10_HOST_DEVICE operator>(const lns<nnbits, rrbits, nbt>& lhs, const lns<nnbits, rrbits, nbt>& rhs);
template<size_t nnbits, size_t rrbits, typename nbt>
bool C10_HOST_DEVICE operator<=(const lns<nnbits, rrbits, nbt>& lhs, const lns<nnbits, rrbits, nbt>& rhs);
template<size_t nnbits, size_t rrbits, typename nbt>
bool C10_HOST_DEVICE operator>=(const lns<nnbits, rrbits, nbt>& lhs, const lns<nnbits, rrbits, nbt>& rhs);
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
