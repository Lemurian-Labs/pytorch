#include <c10/util/UniversalTypes/LNS16/misc.h>


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
template C10_HOST_DEVICE LNS16& LNS16::convert_ieee754<float>(float v) noexcept;
template C10_HOST_DEVICE LNS16& LNS16::convert_ieee754<double>(double v) noexcept;

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

// Comparison operators
template C10_HOST_DEVICE bool operator==(const LNS16& lhs, const LNS16& rhs);
template C10_HOST_DEVICE bool operator!=(const LNS16& lhs, const LNS16& rhs);
template C10_HOST_DEVICE bool operator<(const LNS16& lhs, const LNS16& rhs);
template C10_HOST_DEVICE bool operator>(const LNS16& lhs, const LNS16& rhs);
template C10_HOST_DEVICE bool operator<=(const LNS16& lhs, const LNS16& rhs);
template C10_HOST_DEVICE bool operator>=(const LNS16& lhs, const LNS16& rhs);
template C10_HOST_DEVICE bool operator==(const LNS16& lhs, double rhs);
template C10_HOST_DEVICE bool operator!=(const LNS16& lhs, double rhs);
template C10_HOST_DEVICE bool operator<(const LNS16& lhs, double rhs);
template C10_HOST_DEVICE bool operator>(const LNS16& lhs, double rhs);
template C10_HOST_DEVICE bool operator<=(const LNS16& lhs, double rhs);
template C10_HOST_DEVICE bool operator>=(const LNS16& lhs, double rhs);

#pragma diag_default 20040

}
}
