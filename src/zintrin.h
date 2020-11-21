
//
// v 1.00: https://www.cnblogs.com/zyl910/archive/2012/09/23/zintrin.html
// v 1.01: https://www.cnblogs.com/zyl910/archive/2012/10/01/zintrin_v101.html
// v 1.02: https://www.cnblogs.com/zyl910/archive/2012/11/07/zintrin_v102.html
//

#ifndef ZINTRIN_H_INCLUDED
#define ZINTRIN_H_INCLUDED

#if defined(WIN64) || defined(_WIN64) || defined(_M_X64) || defined(_M_AMD64) \
 || defined(_M_IA64) || defined(__amd64__) || defined(__x86_64__)
  #define INTRIN_IS_X86         1
  #define INTRIN_IS_X86_64      1
  #define INTRIN_WORD_SIZE      64
#else
  #if defined(WIN32) || defined(_WIN32) || defined (_M_IX86) || defined(__i386__)
    #define INTRIN_IS_X86       1
    #define INTRIN_IS_X86_32    1
  #endif
  #define INTRIN_WORD_SIZE      32
#endif

#define INTRIN_MARCO_TOSTR(x)       #x
#define INTRIN_MARCO_VALUE(x)       INTRIN_MARCO_TOSTR(x)

#if defined(__ICL)          // Intel C++ compiler
#  if defined(__VERSION__)
#    define INTRIN_COMPILER_NAME    "Intel C++ " __VERSION__
#  elif defined(__INTEL_COMPILER_BUILD_DATE)
#    define INTRIN_COMPILER_NAME    "Intel C++ (" INTRIN_MARCO_VALUE(__INTEL_COMPILER_BUILD_DATE) ")"
#  else
#    define INTRIN_COMPILER_NAME    "Intel C++"
#  endif // __VERSION__
#elif defined(_MSC_VER)     // Microsoft VC++
#  if defined(_MSC_FULL_VER)
#    define INTRIN_COMPILER_NAME    "Microsoft VC++ (" INTRIN_MARCO_VALUE(_MSC_FULL_VER) ")"
#  elif defined(_MSC_VER)
#    define INTRIN_COMPILER_NAME    "Microsoft VC++ (" INTRIN_MARCO_VALUE(_MSC_VER) ")"
#  else
#    define INTRIN_COMPILER_NAME    "Microsoft VC++"
#  endif // _MSC_FULL_VER
#elif defined(__GNUC__)     // GCC
#  if defined(__CYGWIN__)
#    define INTRIN_COMPILER_NAME    "GCC(Cygmin) " __VERSION__
#  elif defined(__MINGW32__)
#    define INTRIN_COMPILER_NAME    "GCC(MinGW) " __VERSION__
#  else
#    define INTRIN_COMPILER_NAME    "GCC " __VERSION__
#  endif // _MSC_FULL_VER
#elif defined(__clang__)    // clang
#  if defined(__VERSION__)
#    define INTRIN_COMPILER_NAME    "clang " __VERSION__
#else
#    define INTRIN_COMPILER_NAME    "clang"
#  endif // __VERSION__
#else
#  define INTRIN_COMPILER_NAME      "Unknown Compiler"
#endif // __ICL

#if defined(__GNUC__)    // GCC
    #define INTRIN_ALIGN(n)     __attribute__((aligned(n)))
#elif defined(_MSC_VER)
    #define INTRIN_ALIGN(n)     __declspec(align(n))
#else
    #define INTRIN_ALIGN(n)     n
#endif // __GNUC__

#if defined(__GNUC__)    // GCC
    // The gcc-llvm not support intrin function on Mac OS X.
    #if (defined(__i386__) || defined(__x86_64__))
        // header files
        #if defined(__llvm__)
            #include "x86_intrin.h"
        #else
            #include <x86intrin.h>
            #include <cpuid.h>
        #endif // __llvm__

        // macros
        #ifdef __MMX__
            #define INTRIN_MMX      1
        #endif
        #ifdef __3dNOW__
            #define INTRIN_3dNOW    1
        #endif
        #ifdef __SSE__
            #define INTRIN_SSE      1
        #endif
        #ifdef __SSE2__
            #define INTRIN_SSE2     1
        #endif
        #ifdef __SSE3__
            #define INTRIN_SSE3     1
        #endif
        #ifdef __SSSE3__
            #define INTRIN_SSSE3    1
        #endif
        #ifdef __SSE4_1__
            #define INTRIN_SSE4_1   1
        #endif
        #ifdef __SSE4_2__
            #define INTRIN_SSE4_2   1
        #endif
        #if defined(__SSE4A__) || defined(__SSE4a__)
            #define INTRIN_SSE4A    1
        #endif
        #ifdef __AES__
            #define INTRIN_AES      1
        #endif
        #ifdef __PCLMUL__
            #define INTRIN_PCLMUL   1
        #endif
        #ifdef __AVX__
            #define INTRIN_AVX      1
        #endif
        #ifdef __AVX2__
            #define INTRIN_AVX2     1
        #endif
        #ifdef __F16C__
            #define INTRIN_F16C     1
        #endif
        #ifdef __FMA__
            #define INTRIN_FMA      1
        #endif
        #ifdef __FMA4__
            #define INTRIN_FMA4     1
        #endif
        #ifdef __XOP__
            #define INTRIN_XOP      1
        #endif
        #ifdef __LWP__
            #define INTRIN_LWP      1
        #endif
        #ifdef __RDRND__
            #define INTRIN_RDRND    1
        #endif
        #ifdef __FSGSBASE__
            #define INTRIN_FSGSBASE 1
        #endif
        #ifdef __LZCNT__
            #define INTRIN_LZCNT    1
        #endif
        #ifdef __POPCNT__
            #define INTRIN_POPCNT   1
        #endif
        #ifdef __BMI__
            #define INTRIN_BMI      1
        #endif
        #ifdef __BMI2__
            #define INTRIN_BMI2     1
        #endif
        #ifdef __TBM__
            #define INTRIN_TBM      1
        #endif

    #endif // __i386__ || __x86_64__

#elif defined(_MSC_VER)         // MSVC
    // header files
    #if (_MSC_VER >= 1400)      // VC2005
        #include <intrin.h>
    #elif (_MSC_VER >= 1200)    // VC6
        #if (defined(_M_IX86) || defined(_M_X64))
            #include <emmintrin.h>      // MMX, SSE, SSE2
            #include <mm3dnow.h>        // 3DNow!
        #endif
    #endif // (_MSC_VER >= 1400)
    #include <malloc.h>         // For _mm_malloc(), _mm_free().

    // macros
    #if (defined(_M_IX86) || defined(_M_X64))
        #if (_MSC_VER >= 1200)  // VC6
            #if defined(_M_X64) && !defined(__INTEL_COMPILER)
                // VC 6.0 compiler not support 64 bit MMX intrin.
            #else
                #define INTRIN_MMX      1    // mmintrin.h
                #define INTRIN_3dNOW    1    // mm3dnow.h
            #endif
            #define INTRIN_SSE          1    // xmmintrin.h
            #define INTRIN_SSE2         1    // emmintrin.h
        #endif
        #if (_MSC_VER >= 1300)  // VC2003
        #endif
        #if (_MSC_VER >= 1400)  // VC2005
        #endif
        #if (_MSC_VER >= 1500)  // VC2008
            #define INTRIN_SSE3         1    // pmmintrin.h
            #define INTRIN_SSSE3        1    // tmmintrin.h
            #define INTRIN_SSE4_1       1    // smmintrin.h
            #define INTRIN_SSE4_2       1    // nmmintrin.h
            #define INTRIN_SSE4A        1    // intrin.h
            #define INTRIN_POPCNT       1    // nmmintrin.h
        #endif
        #if (_MSC_VER >= 1600)  // VC2010
            #define INTRIN_AES          1    // wmmintrin.h
            #define INTRIN_PCLMUL       1    // wmmintrin.h
            #define INTRIN_AVX          1    // immintrin.h
            #define INTRIN_FMA4         1    // ammintrin.h
            #define INTRIN_XOP          1    // ammintrin.h
            #define INTRIN_LWP          1    // ammintrin.h
        #endif
        #if (_MSC_VER >= 1700)  // VC2012
            #define INTRIN_AVX2         1    // immintrin.h
            #define INTRIN_FMA          1    // immintrin.h
            #define INTRIN_F16C         1    // immintrin.h
            #define INTRIN_RDRND        1    // immintrin.h
            #define INTRIN_FSGSBASE     1    // immintrin.h
            #define INTRIN_LZCNT        1    // immintrin.h
            #define INTRIN_TBM          1    // ammintrin.h
            #define INTRIN_BMI          1    // immintrin.h
            #define INTRIN_BMI2         1    // immintrin.h
            #define INTRIN_INVPCID      1    // immintrin.h
            #define INTRIN_HLE          1    // immintrin.h
            #define INTRIN_RTM          1    // immintrin.h
        #endif
    #elif (defined(_M_ARM) || defined(_M_ARM64))
        // VC2012 have added below header files: armintr.h, arm_neon.h
        // And armintr.h have be automatically included by intrin.h
    #endif // _M_IX86 || _M_X64

    // TODO: To be verified, the feature about support Intel C++ compiler intrin function on Visual Studio.

    // Have no _mm_cvtss_f32 before VC2008
    #if (_MSC_VER < 1500)       // VC2008
        // float _mm_cvtss_f32(__m128 _A);
        #ifndef _mm_cvtss_f32
            #define _mm_cvtss_f32(__m128_A)     (*(float *)(void *)&(__m128_A))
        #endif
    #endif

#else
    #error "Only supports GCC or MSVC."
#endif // __GNUC__

#endif // ZINTRIN_H_INCLUDED
