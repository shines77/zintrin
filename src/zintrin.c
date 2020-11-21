
#include <stdio.h>
#include <stdlib.h>

//
// v 1.00: https://www.cnblogs.com/zyl910/archive/2012/09/23/zintrin.html
// v 1.01: https://www.cnblogs.com/zyl910/archive/2012/10/01/zintrin_v101.html
// v 1.02: https://www.cnblogs.com/zyl910/archive/2012/11/07/zintrin_v102.html
//
#include "zintrin.h"

#define MAKE_MARCO_STR_ESCAPE(x)    #x
#define MAKE_MARCO_STR(x)           { #x, MAKE_MARCO_STR_ESCAPE(x) }

#if !defined(INTRIN_WORD_SIZE) || (INTRIN_WORD_SIZE == 64)
  #if defined(_MSC_VER)
    typedef __int64             ssize_t;
    typedef unsigned __int64    size_t;
  #else
    typedef long long           ssize_t;
    typedef unsigned long long  size_t;
  #endif
#else
    typedef int                 ssize_t;
    typedef unsigned int        size_t;
#endif

typedef struct tagMarcoInfo {
    const char * name;
    const char * value;
} marco_info_t;

/* Intrinsics */
static const marco_info_t g_intrins[] = {
    // { "[Intrinsics]", "" },

#ifdef INTRIN_MMX
    MAKE_MARCO_STR(INTRIN_MMX),
#endif

#ifdef INTRIN_3dNOW
    MAKE_MARCO_STR(INTRIN_3dNOW),
#endif

#ifdef INTRIN_SSE
    MAKE_MARCO_STR(INTRIN_SSE),
#endif

#ifdef INTRIN_SSE2
    MAKE_MARCO_STR(INTRIN_SSE2),
#endif

#ifdef INTRIN_SSE3
    MAKE_MARCO_STR(INTRIN_SSE3),
#endif

#ifdef INTRIN_SSSE3
    MAKE_MARCO_STR(INTRIN_SSSE3),
#endif

#ifdef INTRIN_SSE4_1
    MAKE_MARCO_STR(INTRIN_SSE4_1),
#endif

#ifdef INTRIN_SSE4_2
    MAKE_MARCO_STR(INTRIN_SSE4_2),
#endif

#ifdef INTRIN_SSE4A
    MAKE_MARCO_STR(INTRIN_SSE4A),
#endif

#ifdef INTRIN_AES
    MAKE_MARCO_STR(INTRIN_AES),
#endif

#ifdef INTRIN_PCLMUL
    MAKE_MARCO_STR(INTRIN_PCLMUL),
#endif

#ifdef INTRIN_AVX
    MAKE_MARCO_STR(INTRIN_AVX),
#endif

#ifdef INTRIN_AVX2
    MAKE_MARCO_STR(INTRIN_AVX2),
#endif

#ifdef INTRIN_F16C
    MAKE_MARCO_STR(INTRIN_F16C),
#endif

#ifdef INTRIN_FMA
    MAKE_MARCO_STR(INTRIN_FMA),
#endif

#ifdef INTRIN_FMA4
    MAKE_MARCO_STR(INTRIN_FMA4),
#endif

#ifdef INTRIN_XOP
    MAKE_MARCO_STR(INTRIN_XOP),
#endif

#ifdef INTRIN_LWP
    MAKE_MARCO_STR(INTRIN_LWP),
#endif

#ifdef INTRIN_RDRND
    MAKE_MARCO_STR(INTRIN_RDRND),
#endif

#ifdef INTRIN_FSGSBASE
    MAKE_MARCO_STR(INTRIN_FSGSBASE),
#endif

#ifdef INTRIN_LZCNT
    MAKE_MARCO_STR(INTRIN_LZCNT),
#endif

#ifdef INTRIN_POPCNT
    MAKE_MARCO_STR(INTRIN_POPCNT),
#endif

#ifdef INTRIN_BMI
    MAKE_MARCO_STR(INTRIN_BMI),
#endif

#ifdef INTRIN_BMI2
    MAKE_MARCO_STR(INTRIN_BMI2),
#endif

#ifdef INTRIN_TBM
    MAKE_MARCO_STR(INTRIN_TBM),
#endif

#ifdef INTRIN_INVPCID
    MAKE_MARCO_STR(INTRIN_INVPCID),
#endif

#ifdef INTRIN_HLE
    MAKE_MARCO_STR(INTRIN_HLE),
#endif

#ifdef INTRIN_RTM
    MAKE_MARCO_STR(INTRIN_RTM),
#endif
};

static const size_t kIntrinsSize = sizeof(g_intrins) / sizeof(g_intrins[0]);

int GetWordSize(void)
{
    return sizeof(int *) * 8;
}

void print_marco_info(const marco_info_t * pArray, size_t cnt)
{
    printf("[Intrinsics]\n\n");
    size_t i;
    for (i = 0; i < cnt; ++i) {
        printf("%-24s%s\n", pArray[i].name, pArray[i].value);
    }
    printf("\n");
}

int main(int argc, char * argv[])
{
    printf("test_zintrin v1.01 (%d-bit)\n\n", GetWordSize());
    printf("Compiler: %s\n\n", INTRIN_COMPILER_NAME);

    print_marco_info(g_intrins, kIntrinsSize);

    // _mm_malloc
#ifdef INTRIN_SSE
    if (1)
    {
        void * p;
        p = _mm_malloc(0x10, 0x10);
        printf("_mm_malloc:             %ph\n", p);
        _mm_free(p);
    }
#endif

    // mmx
#ifdef INTRIN_MMX
    _mm_empty();
#endif

    // 3DNow!
#ifdef INTRIN_3dNOW
    //_m_femms();    // AMD cpu only.
#endif

    // sse
#ifdef INTRIN_SSE
    if (1)
    {
        __m128 xmm1;
        float f;
        printf("&xmm1:                  %ph\n", &xmm1);
        xmm1 = _mm_setzero_ps();        // SSE instruction: xorps
        f = _mm_cvtss_f32(xmm1);
        printf("_mm_cvtss_f32:          %f\n", f);
    }
#endif

    // popcnt
#ifdef INTRIN_POPCNT
    printf("popcnt(0xffffffffu):    %d\n", _mm_popcnt_u32(0xffffffffu));
    #if INTRIN_WORD_SIZE >= 64
        printf("popcnt(0xffffffffffffffffull): %d\n", (int)_mm_popcnt_u64(0xffffffffffffffffull));
    #endif
#endif

    // avx2: only Haswell+
#ifdef INTRIN_AVX2
    if (1)
    {
        INTRIN_ALIGN(32) unsigned short buf[16];
        volatile __m256i ymm1;                      // Use "volatile" to avoid the compiler optimization.
        printf("&ymm1:                  %ph\n", &ymm1);
        ymm1 = _mm256_setzero_si256();              // [AVX2] VPXOR. Compiler maybe optimized become to [AVX] VXORPS
        ymm1 = _mm256_add_epi16(ymm1, ymm1);        // [AVX2] VPADDW
        _mm256_store_si256((__m256i *)buf, ymm1);   // [AVX] VMOVDQA
        printf("ymm1[0]:                %d\n", (int)buf[0]);
    }
#endif

    printf("\n");

    return 0;
}
