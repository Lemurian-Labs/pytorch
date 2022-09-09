#include <ATen/cuda/CUDABlas.h>
#include <ATen/cuda/CUDABlas.cuh>
#include <cutlass/gemm/device/gemm.h>
#include <c10/util/UniversalTypes.h>

namespace at {
namespace cuda {
namespace blas {

template <typename T, typename LayoutA, typename LayoutB>
void _cutlassGemm(CUTLASS_GEMM_ARGTYPES(T)) {
  using Gemm = cutlass::gemm::device::Gemm<
    T,
    LayoutA,
    T,
    LayoutB,
    T,
    cutlass::layout::RowMajor,
    T
  >;
  Gemm gemm_op;
  typename Gemm::Arguments args(
    // at::cuda::blas::gemm checks that m, n, and k are less than INT_MAX,
    // so this cast is valid
    {static_cast<int>(m), static_cast<int>(n), static_cast<int>(k)},
    {a, lda},
    {b, ldb},
    {c, ldc},
    {c, ldc},
    {alpha, beta}
  );
  TORCH_CUTLASS_CHECK(gemm_op(args));
}

#define OP(T, _)                                                                    \
  void cutlassGemm(CUTLASS_GEMM_ARGTYPES(T)) {                                      \
    if (opa == CUBLAS_OP_N && opb == CUBLAS_OP_N)                                   \
      _cutlassGemm<T, cutlass::layout::RowMajor, cutlass::layout::RowMajor>(        \
        opa, opb, m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);                    \
    else if (opa == CUBLAS_OP_N)                                                    \
      _cutlassGemm<T, cutlass::layout::RowMajor, cutlass::layout::ColumnMajor>(     \
        opa, opb, m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);                    \
    else if (opb == CUBLAS_OP_N)                                                    \
      _cutlassGemm<T, cutlass::layout::ColumnMajor, cutlass::layout::RowMajor>(     \
        opa, opb, m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);                    \
    else                                                                            \
      _cutlassGemm<T, cutlass::layout::ColumnMajor, cutlass::layout::ColumnMajor>(  \
        opa, opb, m, n, k, alpha, a, lda, b, ldb, beta, c, ldc);                    \
  }
AT_FORALL_UNIVERSAL_TYPES(OP)
#undef OP

}
}
}
