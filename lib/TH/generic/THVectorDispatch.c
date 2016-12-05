#ifndef TH_GENERIC_FILE
#define TH_GENERIC_FILE "generic/THVectorDispatch.c"
#else

/* For now there are only SIMD implementations for FLOAT and DOUBLE.
 * Hopefully in the future this can be made totally generic (e.g, there are SIMD implementations
 * for a lot of functions */
/* Each function with multiple implementations has:
 * 1. A DISPATCHPTR which will be initialized to point to the best available implementation for the host
 * 2. A DISPATCHTABLE which holds pointers to each implementation of a function, and a value indicating
 *    which SIMD extension a given implementation uses
 * 3. A dispatch stub, which is what is actually called by clients, that simply wraps the dispatch pointer.
 */

static void (*THVector_(fill_DISPATCHPTR))(real *, const real, const ptrdiff_t) = &THVector_(fill_DEFAULT);
static FunctionDescription THVector_(fill_DISPATCHTABLE)[] = {
  #if defined(__NEON__)
    #if defined(TH_REAL_IS_FLOAT)
      FUNCTION_IMPL(THVector_(fill_NEON), SIMDExtension_NEON),
    #endif
  #endif

  #if defined(__PPC64__)
    #if defined(TH_REAL_IS_DOUBLE) || defined(TH_REAL_IS_FLOAT)
      FUNCTION_IMPL(THVector_(fill_VSX), SIMDExtension_VSX),
    #endif
  #endif

  #if defined(USE_SSE2) || defined(USE_SSE3) || defined(USE_SSSE3) \
          || defined(USE_SSE4_1) || defined(USE_SSE4_2)
    #if defined(TH_REAL_IS_DOUBLE) || defined(TH_REAL_IS_FLOAT)
      FUNCTION_IMPL(THVector_(fill_SSE), SIMDExtension_SSE),
    #endif
  #endif
  FUNCTION_IMPL(THVector_(fill_DEFAULT), SIMDExtension_DEFAULT)
};
void THVector_(fill)(real *x, const real c, const ptrdiff_t n) {
  THVector_(fill_DISPATCHPTR)(x, c, n);
}

static void (*THVector_(cadd_DISPATCHPTR))(real *, const real *, const real *, const real, const ptrdiff_t) = &THVector_(cadd_DEFAULT);
static FunctionDescription THVector_(cadd_DISPATCHTABLE)[] = {
  #if defined(__NEON__)
    #if defined(TH_REAL_IS_FLOAT)
      FUNCTION_IMPL(THVector_(cadd_NEON), SIMDExtension_NEON),
    #endif
  #endif

  #if defined(__PPC64__)
    #if defined(TH_REAL_IS_DOUBLE) || defined(TH_REAL_IS_FLOAT)
      FUNCTION_IMPL(THVector_(add_VSX), SIMDExtension_VSX),
    #endif
  #endif

  #if defined(USE_SSE2) || defined(USE_SSE3) || defined(USE_SSSE3) \
          || defined(USE_SSE4_1) || defined(USE_SSE4_2)
    #if defined(TH_REAL_IS_DOUBLE) || defined(TH_REAL_IS_FLOAT)
      FUNCTION_IMPL(THVector_(cadd_SSE), SIMDExtension_SSE),
    #endif
  #endif

  FUNCTION_IMPL(THVector_(cadd_DEFAULT), SIMDExtension_DEFAULT)
};
void THVector_(cadd)(real *z, const real *x, const real *y, const real c, const ptrdiff_t n) {
  THVector_(cadd_DISPATCHPTR)(z, x, y, c, n);
}

static void (*THVector_(add_DISPATCHPTR))(real *, const real *, const real, const ptrdiff_t) = &THVector_(add_DEFAULT);
static FunctionDescription THVector_(add_DISPATCHTABLE)[] = {
  #if defined(USE_AVX)
    #if defined(TH_REAL_IS_DOUBLE) || defined(TH_REAL_IS_FLOAT)
      FUNCTION_IMPL(THVector_(add_AVX), SIMDExtension_AVX),
    #endif
  #endif

  FUNCTION_IMPL(THVector_(add_DEFAULT), SIMDExtension_DEFAULT)
};
// Dispatch stubs that just call the pointers
TH_API void THVector_(add)(real *r_, const real *t, const real value, const ptrdiff_t n) {
  THVector_(add_DISPATCHPTR)(r_, t, value, n);
}

static void (*THVector_(diff_DISPATCHPTR))(real *, const real *, const real *, const ptrdiff_t) = &THVector_(diff_DEFAULT);
static FunctionDescription THVector_(diff_DISPATCHTABLE)[] = {
  #if defined(__NEON__)
    #if defined(TH_REAL_IS_FLOAT)
      FUNCTION_IMPL(THVector_(diff_NEON), SIMDExtension_NEON),
    #endif
  #endif

  #if defined(__PPC64__)
    #if defined(TH_REAL_IS_DOUBLE) || defined(TH_REAL_IS_FLOAT)
      FUNCTION_IMPL(THVector_(diff_VSX), SIMDExtension_VSX),
    #endif
  #endif

  #if defined(USE_SSE2) || defined(USE_SSE3) || defined(USE_SSSE3) \
          || defined(USE_SSE4_1) || defined(USE_SSE4_2)
    #if defined(TH_REAL_IS_DOUBLE) || defined(TH_REAL_IS_FLOAT)
      FUNCTION_IMPL(THVector_(diff_SSE), SIMDExtension_SSE),
    #endif
  #endif

  FUNCTION_IMPL(THVector_(diff_DEFAULT), SIMDExtension_DEFAULT)
};
void THVector_(diff)(real *z, const real *x, const real *y, const ptrdiff_t n) {
  THVector_(diff_DISPATCHPTR)(z, x, y, n);
}


static void (*THVector_(scale_DISPATCHPTR))(real *, const real, const ptrdiff_t) = &THVector_(scale_DEFAULT);
static FunctionDescription THVector_(scale_DISPATCHTABLE)[] = {
  #if defined(__NEON__)
    #if defined(TH_REAL_IS_FLOAT)
      FUNCTION_IMPL(THVector_(scale_NEON), SIMDExtension_NEON),
    #endif
  #endif

  #if defined(__PPC64__)
    #if defined(TH_REAL_IS_DOUBLE) || defined(TH_REAL_IS_FLOAT)
      FUNCTION_IMPL(THVector_(scale_VSX), SIMDExtension_VSX),
    #endif
  #endif

  #if defined(USE_SSE2) || defined(USE_SSE3) || defined(USE_SSSE3) \
          || defined(USE_SSE4_1) || defined(USE_SSE4_2)
    #if defined(TH_REAL_IS_DOUBLE) || defined(TH_REAL_IS_FLOAT)
      FUNCTION_IMPL(THVector_(scale_SSE), SIMDExtension_SSE),
    #endif
  #endif

  FUNCTION_IMPL(THVector_(scale_DEFAULT), SIMDExtension_DEFAULT)
};
TH_API void THVector_(scale)(real *y, const real c, const ptrdiff_t n) {
  THVector_(scale_DISPATCHPTR)(y, c, n);
}


static void (*THVector_(cmul_DISPATCHPTR))(real *, const real *, const ptrdiff_t) = &THVector_(cmul_DEFAULT);
static FunctionDescription THVector_(cmul_DISPATCHTABLE)[] = {
  #if defined(__NEON__)
    #if defined(TH_REAL_IS_FLOAT)
      FUNCTION_IMPL(THVector_(cmul_NEON), SIMDExtension_NEON),
    #endif
  #endif

  #if defined(__PPC64__)
    #if defined(TH_REAL_IS_DOUBLE) || defined(TH_REAL_IS_FLOAT)
      FUNCTION_IMPL(THVector_(mul_VSX), SIMDExtension_VSX),
    #endif
  #endif

  #if defined(USE_SSE2) || defined(USE_SSE3) || defined(USE_SSSE3) \
          || defined(USE_SSE4_1) || defined(USE_SSE4_2)
    #if defined(TH_REAL_IS_DOUBLE) || defined(TH_REAL_IS_FLOAT)
      FUNCTION_IMPL(THVector_(cmul_SSE), SIMDExtension_SSE),
    #endif
  #endif

  FUNCTION_IMPL(THVector_(cmul_DEFAULT), SIMDExtension_DEFAULT)
};
void THVector_(cmul)(real *y, const real *x, const ptrdiff_t n) {
  THVector_(cmul_DISPATCHPTR);
}

/* This needs to be called in order to initialize the dispatch pointers at runtime.
 * This function simply checks what SIMD extensions are available, and then walks the dispatch table
 * to choose the best function.
 * NOTE: As implemented, it will initialize the dispatch pointer to the first supported function.
 *       This means that in the dispatch tables, implementations supporting more recent extensions
 *       need to come first
 */
void THVector_(vectorDispatchInit)(void)
{
  uint32_t hostSimdExts = detectHostSIMDExtensions();
  INIT_VECTOR_DISPATCH_PTR(fill);
  INIT_VECTOR_DISPATCH_PTR(cadd);
  INIT_VECTOR_DISPATCH_PTR(add);
  INIT_VECTOR_DISPATCH_PTR(diff);
  INIT_VECTOR_DISPATCH_PTR(scale);
  INIT_VECTOR_DISPATCH_PTR(cmul);
}

#endif
