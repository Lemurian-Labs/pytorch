#pragma once

#include <c10/util/UniversalTypes/LNS16/aliases.h>
#include <c10/macros/Macros.h>

// Redeclare operators as __host__ __device__
namespace sw {
namespace universal {

// Suppress the warnings that __host__ functions were redeclared as __host__ __device__
#pragma diag_suppress 20040

// blockbinary
template C10_HOST_DEVICE LNS16BlockBinary::bt& LNS16BlockBinary::operator[](size_t index);
template C10_HOST_DEVICE LNS16BlockBinary::bt LNS16BlockBinary::operator[](size_t index) const;
template C10_HOST_DEVICE void LNS16BlockBinary::clear() noexcept;
#pragma push_macro("setbit")
#undef setbit
template C10_HOST_DEVICE void LNS16BlockBinary::setbit(size_t index, bool v) noexcept;
#pragma pop_macro("setbit")

// exponentblockbinary
template C10_HOST_DEVICE LNS16ExponentBlockBinary::blockbinary<LNS16BlockBinary::nbits>(const LNS16BlockBinary& rhs);
template C10_HOST_DEVICE LNS16ExponentBlockBinary::blockbinary(long long initial_value) noexcept;
template C10_HOST_DEVICE LNS16ExponentBlockBinary& LNS16ExponentBlockBinary::operator=(long long rhs) noexcept;
template C10_HOST_DEVICE LNS16ExponentBlockBinary::bt& LNS16ExponentBlockBinary::operator[](size_t index);
template C10_HOST_DEVICE LNS16ExponentBlockBinary::bt LNS16ExponentBlockBinary::operator[](size_t index) const;
template C10_HOST_DEVICE LNS16ExponentBlockBinary& LNS16ExponentBlockBinary::operator+=(const LNS16ExponentBlockBinary& rhs);
template C10_HOST_DEVICE LNS16ExponentBlockBinary& LNS16ExponentBlockBinary::operator-=(const LNS16ExponentBlockBinary& rhs);
template C10_HOST_DEVICE LNS16ExponentBlockBinary::bt LNS16ExponentBlockBinary::block(size_t b) const noexcept;
template C10_HOST_DEVICE bool LNS16ExponentBlockBinary::sign() const noexcept;
template C10_HOST_DEVICE void LNS16ExponentBlockBinary::setzero() noexcept;
template C10_HOST_DEVICE void LNS16ExponentBlockBinary::clear() noexcept;
template C10_HOST_DEVICE LNS16ExponentBlockBinary& LNS16ExponentBlockBinary::twosComplement() noexcept;
template C10_HOST_DEVICE LNS16ExponentBlockBinary& LNS16ExponentBlockBinary::flip() noexcept;
template C10_HOST_DEVICE LNS16ExponentBlockBinary& LNS16ExponentBlockBinary::operator<<=(int bitsToShift);
template C10_HOST_DEVICE LNS16ExponentBlockBinary& LNS16ExponentBlockBinary::operator>>=(int bitsToShift);
#pragma push_macro("setbit")
#undef setbit
template C10_HOST_DEVICE void LNS16ExponentBlockBinary::setbit(size_t index, bool v) noexcept;
#pragma pop_macro("setbit")
template C10_HOST_DEVICE void LNS16ExponentBlockBinary::setbits(uint64_t value) noexcept;

// mixed
template C10_HOST_DEVICE LNS16ExponentBlockBinary& LNS16ExponentBlockBinary::assign(const LNS16BlockBinary& rhs);
template C10_HOST_DEVICE LNS16BlockBinary& LNS16BlockBinary::assign(const LNS16ExponentBlockBinary& rhs);

#pragma diag_default 20040

}
}
