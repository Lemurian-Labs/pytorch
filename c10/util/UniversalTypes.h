#pragma once

#include <c10/util/UniversalTypes/common.h>
#include <c10/util/UniversalTypes/CFloatWithSubnormals/type.h>
#include <c10/util/UniversalTypes/LNS16/type.h>

namespace c10 {

// Checks whether T is one of the new floating point types
template <typename T>
struct is_universal_floating_point :
  std::integral_constant<bool,
    std::is_same<T, CFloatWithSubnormals>::value ||
    std::is_same<T, LNS16>::value> {
};

// Checks whether T is one of the new double precision floating point types
template <typename T>
struct is_universal_double_precision :
  std::integral_constant<bool, false> {
};

// In case we want to add complex or integral types later
template <typename T>
struct is_universal_type :
  std::integral_constant<bool,
    is_universal_floating_point<T>::value> {
};

// Checks whether the type behaves correcly if we memset it to 0
// (For example, if we memset LNS16 to 0, the result will be 1, and not 0)
template <typename T>
struct supports_memset_0 :
  std::integral_constant<bool,
    !std::is_same<T, LNS16>::value> {
};

template <typename T>
void memset_0_if_supported(T* ptr, size_t n_elements)
{
  if constexpr (supports_memset_0<T>::value) {
    std::memset(ptr, 0, n_elements * sizeof(T));
  } else {
    std::fill_n(ptr, n_elements, 0);
  }
}

}
