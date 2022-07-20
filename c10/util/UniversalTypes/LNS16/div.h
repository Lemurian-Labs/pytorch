#pragma once

#include <c10/util/UniversalTypes/LNS16/aliases.h>
#include <c10/macros/Macros.h>

// Redeclare operators as __host__ __device__
namespace sw {
namespace universal {

// Suppress the warnings that __host__ functions were redeclared as __host__ __device__
#pragma diag_suppress 20040

template C10_HOST_DEVICE LNS16& LNS16::operator/=(const LNS16& rhs);
template C10_HOST_DEVICE LNS16& LNS16::operator/=(double rhs);

#pragma diag_default 20040

}
}
