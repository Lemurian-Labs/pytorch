#pragma once

#include <c10/util/UniversalTypes/LNS16/aliases.h>
#include <c10/macros/Macros.h>

// Redeclare operators as __host__ __device__
namespace std {

// Suppress the warnings that __host__ functions were redeclared as __host__ __device__
#pragma diag_suppress 20040

template C10_HOST_DEVICE sw::universal::LNS16 numeric_limits<sw::universal::LNS16>::max();
template C10_HOST_DEVICE sw::universal::LNS16 numeric_limits<sw::universal::LNS16>::epsilon();

#pragma diag_default 20040

}
