#pragma once

// Do not include this file manually, include UniversalTypes.h instead

#pragma push_macro("setbit")
#undef setbit
#include <universal/number/lns/lns.hpp>
#pragma pop_macro("setbit")
#include <c10/util/UniversalTypes/cuda_noinline.h>

namespace sw {
namespace universal {

using LNS16 = lns<16, 8, uint16_t>;
using LNS17 = lns<17, 9, uint16_t>; // Used in convert_ieee754
using LNS16BlockBinary = blockbinary<16, uint16_t, BinaryNumberType::Signed>;
using LNS16ExponentBlockBinary = blockbinary<15, uint16_t, BinaryNumberType::Signed>;
using LNS17BlockBinary = blockbinary<17, uint16_t, BinaryNumberType::Signed>;
using LNS17ExponentBlockBinary = LNS16BlockBinary;

}
}
