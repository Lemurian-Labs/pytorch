#include <universal/native/ieee754.hpp>
#include <c10/macros/Macros.h>

// Redeclare operators as __host__ __device__
namespace sw {
namespace universal {

// Suppress the warnings that __host__ functions were redeclared as __host__ __device__
#pragma diag_suppress 20040

// extractFields and necessary functions (required for conversion from float and from double)
inline C10_HOST_DEVICE void extractFields(float value, bool& s, uint64_t& rawExponentBits, uint64_t& rawFractionBits);
inline C10_HOST_DEVICE void extractFields(double value, bool& s, uint64_t& rawExponentBits, uint64_t& rawFractionBits);


#pragma diag_default 20040

}
}
