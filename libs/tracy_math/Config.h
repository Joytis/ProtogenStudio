
#if defined(__EMSCRIPTEN__)
#define CPU_CAN_DO_SIMD 0
#define CPU_CAN_DO_THREADS 0
#else
#define CPU_CAN_DO_SIMD 1
#define CPU_CAN_DO_THREADS 1
#endif


// Should float3 struct use SSE/NEON?
#define DO_FLOAT3_WITH_SIMD (CPU_CAN_DO_SIMD)
