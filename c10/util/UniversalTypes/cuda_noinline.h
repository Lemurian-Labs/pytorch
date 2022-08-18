#pragma once

#if defined(__CUDACC__) || defined(__HIPCC__)
// Designates functions callable from the host (CPU) and the device (GPU)
#define CUDA_NOINLINE __noinline__
#else
#define CUDA_NOINLINE
#endif
