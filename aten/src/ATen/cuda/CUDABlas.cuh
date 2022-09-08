#pragma once

#include <ATen/cuda/Exceptions.h>

#define CUTLASS_GEMM_ARGTYPES(Dtype)                                                     \
  cublasOperation_t opa, cublasOperation_t opb,                                          \
  int64_t m, int64_t n, int64_t k, at::opmath_type<Dtype> alpha,                         \
  const Dtype *a, int64_t lda, const Dtype *b, int64_t ldb, at::opmath_type<Dtype> beta, \
  Dtype *c, int64_t ldc

namespace at {
namespace cuda {
namespace blas {

#define OP(T, _) \
  void cutlassGemm(CUTLASS_GEMM_ARGTYPES(T));
AT_FORALL_UNIVERSAL_TYPES(OP)
#undef OP

}
}
}
