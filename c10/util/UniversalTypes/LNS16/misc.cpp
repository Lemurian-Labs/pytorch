#include <c10/util/UniversalTypes/LNS16/misc.h>


// Redeclare operators as __host__ __device__
namespace sw {
namespace universal {

// Suppress the warnings that __host__ functions were redeclared as __host__ __device__
#pragma diag_suppress 20040

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
