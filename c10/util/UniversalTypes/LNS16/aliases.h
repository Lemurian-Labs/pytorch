#pragma once

// Do not include this file manually, include UniversalTypes.h instead

#pragma push_macro("setbit")
#undef setbit
#include <universal/number/lns/lns.hpp>
#pragma pop_macro("setbit")

namespace sw {
namespace universal {

using LNS16 = lns<16, 8, uint16_t>;
using LNS16BlockBinary = blockbinary<16, uint16_t, BinaryNumberType::Signed>;
using LNS16ExponentBlockBinary = blockbinary<15, uint16_t, BinaryNumberType::Signed>;

}
}
