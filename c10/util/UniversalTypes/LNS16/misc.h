#pragma once

#include <c10/util/UniversalTypes/LNS16/aliases.h>
#include <c10/macros/Macros.h>

// Redeclare operators as __host__ __device__
namespace sw {
namespace universal {

// Suppress the warnings that __host__ functions were redeclared as __host__ __device__
#pragma diag_suppress 20040

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
