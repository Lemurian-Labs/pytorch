#include <ATen/cuda/CUDABlas.h>
#include <ATen/cuda/CUDABlas.cuh>
#include <cutlass/gemm/device/gemm.h>

namespace at {
namespace cuda {
namespace blas {

template <typename T, bool tA, bool tB>
void _cutlassGemm(CUTLASS_GEMM_ARGTYPES(T)) {
  cutlass::gemm::device::Gemm<
    T,
    tA ? cutlass::layout::ColumnMajor : cutlass::layout::RowMajor,
    T,
    tB ? cutlass::layout::ColumnMajor : cutlass::layout::RowMajor,
    T,
    cutlass::layout::RowMajor,
    at::opmath_type<T>,
    cutlass::arch::OpClassTensorOp,
    cutlass::arch::Sm70
  > gemm_op;
  TORCH_CUTLASS_CHECK(gemm_op(
    {m, n, k},
    {a, lda},
    {b, ldb},
    {c, ldc},
    {c, ldc},
    {alpha, beta}
  ));
}

#define OP(T, _)                                                                   \
  void cutlassGemm(CUTLASS_GEMM_ARGTYPES(T)) {                                     \
    if (opa == CUBLAS_OP_N && opb == CUBLAS_OP_N)                                  \
      _cutlassGemm<T, false, false>(m, n, k, alpha, a, lda, b, ldb, beta, c, ldc); \
    else if (opa == CUBLAS_OP_N)                                                   \
      _cutlassGemm<T, false, true>(m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);  \
    else if (opb == CUBLAS_OP_N)                                                   \
      _cutlassGemm<T, true, false>(m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);  \
    else                                                                           \
      _cutlassGemm<T, true, true>(m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);   \
  }
AT_FORALL_UNIVERSAL_TYPES(OP)
#undef OP

}
}
}
