#pragma once

#include <c10/util/UniversalTypes/LNS16/aliases.h>
#include <c10/macros/Macros.h>

// Redeclare operators as __host__ __device__
namespace sw {
namespace universal {

// Suppress the warnings that __host__ functions were redeclared as __host__ __device__
#pragma diag_suppress 20040

// blockbinary
template CUDA_NOINLINE C10_HOST_DEVICE LNS16BlockBinary::blockbinary<LNS16BlockBinary::nbits>(const LNS16BlockBinary& rhs);
template CUDA_NOINLINE C10_HOST_DEVICE LNS16BlockBinary& LNS16BlockBinary::assign<LNS16BlockBinary::nbits>(const LNS16BlockBinary& rhs);
template CUDA_NOINLINE C10_HOST_DEVICE LNS16BlockBinary::blockbinary<LNS16ExponentBlockBinary::nbits>(const LNS16ExponentBlockBinary& rhs);
template CUDA_NOINLINE C10_HOST_DEVICE LNS16BlockBinary& LNS16BlockBinary::assign<LNS16ExponentBlockBinary::nbits>(const LNS16ExponentBlockBinary& rhs);
template CUDA_NOINLINE C10_HOST_DEVICE LNS16BlockBinary::blockbinary<LNS17BlockBinary::nbits>(const LNS17BlockBinary& rhs);
template CUDA_NOINLINE C10_HOST_DEVICE LNS16BlockBinary& LNS16BlockBinary::assign<LNS17BlockBinary::nbits>(const LNS17BlockBinary& rhs);
template CUDA_NOINLINE C10_HOST_DEVICE LNS16BlockBinary::blockbinary(long long initial_value) noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16BlockBinary& LNS16BlockBinary::operator+=(const LNS16BlockBinary& rhs);
template CUDA_NOINLINE C10_HOST_DEVICE LNS16BlockBinary& LNS16BlockBinary::operator-=(const LNS16BlockBinary& rhs);
template CUDA_NOINLINE C10_HOST_DEVICE LNS16BlockBinary& LNS16BlockBinary::operator=(long long rhs) noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16BlockBinary::bt& LNS16BlockBinary::operator[](size_t index);
template CUDA_NOINLINE C10_HOST_DEVICE LNS16BlockBinary::bt LNS16BlockBinary::operator[](size_t index) const;
#pragma push_macro("setbit")
#undef setbit
template CUDA_NOINLINE C10_HOST_DEVICE void LNS16BlockBinary::setbit(size_t index, bool v) noexcept;
#pragma pop_macro("setbit")
template CUDA_NOINLINE C10_HOST_DEVICE LNS16BlockBinary::bt LNS16BlockBinary::block(size_t b) const noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE bool LNS16BlockBinary::sign() const noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE bool LNS16BlockBinary::ispos() const noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE bool LNS16BlockBinary::isneg() const noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE void LNS16BlockBinary::setzero() noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE void LNS16BlockBinary::clear() noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16BlockBinary& LNS16BlockBinary::twosComplement() noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16BlockBinary& LNS16BlockBinary::flip() noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16BlockBinary& LNS16BlockBinary::operator<<=(int bitsToShift);
template CUDA_NOINLINE C10_HOST_DEVICE LNS16BlockBinary& LNS16BlockBinary::operator>>=(int bitsToShift);

// exponentblockbinary
template CUDA_NOINLINE C10_HOST_DEVICE LNS16ExponentBlockBinary::blockbinary<LNS16ExponentBlockBinary::nbits>(const LNS16ExponentBlockBinary& rhs);
template CUDA_NOINLINE C10_HOST_DEVICE LNS16ExponentBlockBinary& LNS16ExponentBlockBinary::assign<LNS16ExponentBlockBinary::nbits>(const LNS16ExponentBlockBinary& rhs);
template CUDA_NOINLINE C10_HOST_DEVICE LNS16ExponentBlockBinary::blockbinary(const SpecificValue code);
template CUDA_NOINLINE C10_HOST_DEVICE LNS16ExponentBlockBinary::blockbinary<LNS16BlockBinary::nbits>(const LNS16BlockBinary& rhs);
template CUDA_NOINLINE C10_HOST_DEVICE LNS16ExponentBlockBinary& LNS16ExponentBlockBinary::assign(const LNS16BlockBinary& rhs);
template CUDA_NOINLINE C10_HOST_DEVICE LNS16ExponentBlockBinary::blockbinary(long long initial_value) noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16ExponentBlockBinary& LNS16ExponentBlockBinary::operator=(long long rhs) noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16ExponentBlockBinary::bt& LNS16ExponentBlockBinary::operator[](size_t index);
template CUDA_NOINLINE C10_HOST_DEVICE LNS16ExponentBlockBinary::bt LNS16ExponentBlockBinary::operator[](size_t index) const;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16ExponentBlockBinary& LNS16ExponentBlockBinary::operator+=(const LNS16ExponentBlockBinary& rhs);
template CUDA_NOINLINE C10_HOST_DEVICE LNS16ExponentBlockBinary& LNS16ExponentBlockBinary::operator-=(const LNS16ExponentBlockBinary& rhs);
template CUDA_NOINLINE C10_HOST_DEVICE LNS16ExponentBlockBinary::bt LNS16ExponentBlockBinary::block(size_t b) const noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE bool LNS16ExponentBlockBinary::sign() const noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE bool LNS16ExponentBlockBinary::ispos() const noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE bool LNS16ExponentBlockBinary::isneg() const noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE void LNS16ExponentBlockBinary::setzero() noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE void LNS16ExponentBlockBinary::clear() noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16ExponentBlockBinary& LNS16ExponentBlockBinary::minpos() noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16ExponentBlockBinary& LNS16ExponentBlockBinary::maxpos() noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16ExponentBlockBinary& LNS16ExponentBlockBinary::minneg() noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16ExponentBlockBinary& LNS16ExponentBlockBinary::maxneg() noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16ExponentBlockBinary& LNS16ExponentBlockBinary::zero() noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16ExponentBlockBinary& LNS16ExponentBlockBinary::twosComplement() noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16ExponentBlockBinary& LNS16ExponentBlockBinary::flip() noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS16ExponentBlockBinary& LNS16ExponentBlockBinary::operator<<=(int bitsToShift);
template CUDA_NOINLINE C10_HOST_DEVICE LNS16ExponentBlockBinary& LNS16ExponentBlockBinary::operator>>=(int bitsToShift);
#pragma push_macro("setbit")
#undef setbit
template CUDA_NOINLINE C10_HOST_DEVICE void LNS16ExponentBlockBinary::setbit(size_t index, bool v) noexcept;
#pragma pop_macro("setbit")
template CUDA_NOINLINE C10_HOST_DEVICE void LNS16ExponentBlockBinary::setbits(uint64_t value) noexcept;

// blockbinary for LNS17
template CUDA_NOINLINE C10_HOST_DEVICE LNS17BlockBinary::blockbinary<LNS17ExponentBlockBinary::nbits>(const LNS17ExponentBlockBinary& rhs);
template CUDA_NOINLINE C10_HOST_DEVICE LNS17BlockBinary& LNS17BlockBinary::assign(const LNS17ExponentBlockBinary& rhs);
template CUDA_NOINLINE C10_HOST_DEVICE LNS17BlockBinary::blockbinary<LNS17BlockBinary::nbits>(const LNS17BlockBinary& rhs);
template CUDA_NOINLINE C10_HOST_DEVICE LNS17BlockBinary& LNS17BlockBinary::assign(const LNS17BlockBinary& rhs);
template CUDA_NOINLINE C10_HOST_DEVICE LNS17BlockBinary::blockbinary(long long initial_value) noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS17BlockBinary& LNS17BlockBinary::operator=(long long rhs) noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS17BlockBinary::bt& LNS17BlockBinary::operator[](size_t index);
// template CUDA_NOINLINE C10_HOST_DEVICE LNS17BlockBinary::bt LNS17BlockBinary::operator[](size_t index) const;
template CUDA_NOINLINE C10_HOST_DEVICE LNS17BlockBinary& LNS17BlockBinary::operator+=(const LNS17BlockBinary& rhs);
template CUDA_NOINLINE C10_HOST_DEVICE LNS17BlockBinary& LNS17BlockBinary::operator-=(const LNS17BlockBinary& rhs);
template CUDA_NOINLINE C10_HOST_DEVICE LNS17BlockBinary::bt LNS17BlockBinary::block(size_t b) const noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE bool LNS17BlockBinary::sign() const noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE bool LNS17BlockBinary::ispos() const noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE bool LNS17BlockBinary::isneg() const noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE void LNS17BlockBinary::setzero() noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE void LNS17BlockBinary::clear() noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS17BlockBinary& LNS17BlockBinary::twosComplement() noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS17BlockBinary& LNS17BlockBinary::flip() noexcept;
template CUDA_NOINLINE C10_HOST_DEVICE LNS17BlockBinary& LNS17BlockBinary::operator<<=(int bitsToShift);
template CUDA_NOINLINE C10_HOST_DEVICE LNS17BlockBinary& LNS17BlockBinary::operator>>=(int bitsToShift);
#pragma push_macro("setbit")
#undef setbit
template CUDA_NOINLINE C10_HOST_DEVICE void LNS17BlockBinary::setbit(size_t index, bool v) noexcept;
#pragma pop_macro("setbit")
template CUDA_NOINLINE C10_HOST_DEVICE void LNS17BlockBinary::setbits(uint64_t value) noexcept;

template<size_t N, typename B, BinaryNumberType T>
inline C10_HOST_DEVICE bool operator==(const blockbinary<N, B, T>& lhs, const blockbinary<N, B, T>& rhs);
template<size_t N, typename B, BinaryNumberType T>
inline C10_HOST_DEVICE bool operator!=(const blockbinary<N, B, T>& lhs, const blockbinary<N, B, T>& rhs);
template<size_t N, typename B, BinaryNumberType T>
inline C10_HOST_DEVICE bool operator<(const blockbinary<N, B, T>& lhs, const blockbinary<N, B, T>& rhs);
template<size_t N, typename B, BinaryNumberType T>
inline C10_HOST_DEVICE bool operator<=(const blockbinary<N, B, T>& lhs, const blockbinary<N, B, T>& rhs);
template<size_t N, typename B, BinaryNumberType T>
inline C10_HOST_DEVICE bool operator>(const blockbinary<N, B, T>& lhs, const blockbinary<N, B, T>& rhs);
template<size_t N, typename B, BinaryNumberType T>
inline C10_HOST_DEVICE bool operator>=(const blockbinary<N, B, T>& lhs, const blockbinary<N, B, T>& rhs);

template<size_t N, typename B, BinaryNumberType T>
inline C10_HOST_DEVICE blockbinary<N, B, T> operator+(const blockbinary<N, B, T>& a, const blockbinary<N, B, T>& b);
template<size_t N, typename B, BinaryNumberType T >
inline C10_HOST_DEVICE blockbinary<N, B, T> operator-(const blockbinary<N, B, T>& a, const blockbinary<N, B, T>& b);
template<size_t N, typename B, BinaryNumberType T>
inline C10_HOST_DEVICE blockbinary<N, B, T> operator*(const blockbinary<N, B, T>& a, const blockbinary<N, B, T>& b);
template<size_t N, typename B, BinaryNumberType T>
inline C10_HOST_DEVICE blockbinary<N, B, T> operator/(const blockbinary<N, B, T>& a, const blockbinary<N, B, T>& b);

template<size_t nbits, typename BlockType, BinaryNumberType NumberType>
constexpr C10_HOST_DEVICE blockbinary<nbits, BlockType, NumberType>& maxneg(blockbinary<nbits, BlockType, NumberType>& a);

template<size_t nbits, typename BlockType, BinaryNumberType NumberType>
C10_HOST_DEVICE blockbinary<nbits, BlockType, NumberType> twosComplement(const blockbinary<nbits, BlockType, NumberType>&);

// uradd, ursub
template<size_t N, typename B, BinaryNumberType T>
inline C10_HOST_DEVICE blockbinary<N + 1, B, T> uradd(const blockbinary<N, B, T>& a, const blockbinary<N, B, T>& b);
template<size_t N, typename B, BinaryNumberType T>
inline C10_HOST_DEVICE blockbinary<N + 1, B, T> ursub(const blockbinary<N, B, T>& a, const blockbinary<N, B, T>& b);

#pragma diag_default 20040

}
}
