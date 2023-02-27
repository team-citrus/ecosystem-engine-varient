/*
*   name: include/core/simd.h
*   origin: Citrus Engine
*   purpose: Provide SIMD abstractions
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: CC0-1.0 OR LGPL-3.0-ONLY
*/

#ifndef CITRUS_ENGINE_SINGLE_INSRUCTION_MULTIPLE_DATA_H__
#define CITRUS_ENGINE_SINGLE_INSRUCTION_MULTIPLE_DATA_H__

#include <x86intrin.h>

// Create a shuffle mask for shuffling an xmmreg packed with 32 bit integers
// a is xmmreg_i32[3], b is xmmreg_i32[2], etc.
#define XMM_I32_CREATE_SHUFFLE_MASK(a, b, c, d) ((a & 3) << 6) | ((b & 3) << 4) | ((c & 3) << 2) | (d & 3)

// Create a shuffle mask for shuffling an xmmreg packed with 32 bit floats
// a is xmmreg_f32[3], b is xmmreg_f32[2], etc.
#define XMM_F32_CREATE_SHUFFLE_MASK(a, b, c, d) ((a & 3) << 6) | ((b & 3) << 4) | ((c & 3) << 2) | (d & 3)

// Create a shuffle mask for shuffling a 64 bit value packed with 16 bit integers
// a is val[3], b is val[2], etc.
#define XMM_I16_CREATE_SHUFFLE_MASK(a, b, c, d) XMM_I32_CREATE_SHUFFLE_MASK(a, b, c, d)

// Create a shuffle mask for shuffling an xmmreg packed with 64 bit floats
// a is xmmreg_f64[1] = a ? xmmreg_f64[0] : xmmreg_f64[1], b is xmmreg_f64[0] = a ? xmmreg_f64[0] : xmmreg_f64[1]
#define XMM_F64_CREATE_SHUFFLE_MASK(a, b) ((a & 1) << 1) | (b & 1)

// Create a blend mask for blending an xmmreg packed with 16 bit integers
// a is xmmdest_i16[7] = a ? xmmsrc1_i16[7] : xmmsrc0_i16[7], etc.
#define XMM_I16_CREATE_BLEND_MASK(a, b, c, d, e, f, g, h) ((a & 1) << 7) | ((b & 1) << 6) | ((c & 1) << 5) | ((d & 1) << 4) | ((e & 1) << 3) | ((f & 1) << 2) | ((g & 1) << 1) | (h & 1)

// Create a blend mask for blending an xmmreg packed with 32 bit floats
// a is xmmdest_f32[3] = a ? xmmsrc1_f32[3] : xmmsrc0_f32[3], etc.
#define XMM_F32_CREATE_BLEND_MASK(a, b, c, d) ((a & 1) << 3) | ((b & 1) << 2) | ((c & 1) << 1) | (d & 1)

// Create a blend mask for blending an xmmreg packed with 64 bit floats
// a is xmmdest_f64[1] = a ? xmmsrc1_f64[1] : xmmsrc0_f64[1], b is xmmdest_f64[0] = b ? xmmsrc1_f64[0] : xmmsrc0_f64[0]
#define XMM_F64_CREATE_BLEND_MASK(a, b) ((a & 1) << 1) | (b & 1)

typedef __m128 m128f_t;
typedef __m128d m128d_t;
typedef __m128i m128i_t;

#ifdef _MAVX_

// Create a shuffle mask for shufflng an ymmreg packed with 64 bit floats
// a is ymmreg_f64[3] = a ? ymmreg_f64[3] : ymmreg_f64[2], b is ymmreg_f64[2] = b ? ymmreg_f64[3] : ymmreg_f64[2], c is ymmreg_f64[1] = c ? ymmreg_f64[1] : ymmreg_f64[0], d is ymmreg_f64[1] = d ? ymmreg_f64[1] : ymmreg_f64[0] 
#define YMM_F64_CREATE_SHUFFLE_MASK(a, b, c, d) ((a & 1) << 3) | ((b & 1) << 2) | ((c & 1) << 1) | (d & 1)

// Create a shuffle mask for shuffling each 128 bit half of a ymmreg packed with 32 bit floats
#define YMM_F32_CREATE_SHUFFLE_MASK(a, b, c, d) XMM_F32_CREATE_SHUFFLE_MASK(a, b, c, d)

// Create a blend mask for blending an ymmreg packed with 64 bit floats
// a is ymmdest_f64[3] = a ? ymmsrc1_f64[3] : ymmsrc0_f64[3], etc.
#define YMM_F64_CREATE_BLEND_MASK(a, b, c, d) XMM_F32_CREATE_BLEND_MASK(a, b, c, d)

// Create a blend mask for blending an ymmreg packed with 32 bit floats
// a is ymmdest_f32[7] = a ? ymmsrc1_f32[7] : ymmsrc0_f32[7], etc.
#define YMM_F32_CREATE_BLEND_MASK(a, b, c, d, e, f, g, h) XMM_I16_CREATE_BLEND_MASK(a, b, c, d, e, f, g, h)

#if _MAVX_ >= 2

// Create a blend mask for blending an xmmreg packed with 32 bit integers
// a is xmmdest_i32[3] = a ? xmmsrc1_i32[3] : xmmsrc0_i32[3], etc.
#define XMM_I32_CREATE_BLEND_MASK(a, b, c, d) XMM_F32_CREATE_BLEND_MASK(a, b, c, d)

// Create a blend mask for blending each 128 bit half of a ymmreg packed with 16 bit ints
// a is ymmhhdest_i16[7] = a ? ymmhhsrc1_i16[7] : ymmhhsrc0_i16[7], etc.
#define YMM_I16_CREATE_BLEND_MASK(a, b, c, d, e, f, g, h) XMM_I16_CREATE_BLEND_MASK(a, b, c, d, e, f, g, h)

// Create a blend mask for blending an ymmreg packed with 32 bit integers
// a is ymmdest_i32[7] = a ? ymmsrc1_i32[7] : ymmsrc0_i32[7], etc.
#define YMM_I32_CREATE_BLEND_MASK(a, b, c, d, e, f, g, h) XMM_I16_CREATE_BLEND_MASK(a, b, c, d, e, f, g, h)

#endif

// Create a permutate mask for shuffling 2 ymmregs
// a is higher half of the dest, b is the lower half
// If bit 3 is set, the selected 128 bits will be zeroed
// If bit 1 is set, it will select from source 1, if bit 1 is clear, it will select from source 0
// If bit 0 is set, it will select the high half of the reg, if bit 0 is clear, it will select the lower half of the right
#define YMM_CREATE_PERMUTATE_MASK(a, b) ((a & 013) << 4) | (b & 013)

typedef __m256 m256f_t;
typedef __m256d m256d_t;
typedef __m256i m256i_t;

#endif

// xmm/SSE intrinsics

#define abs_i16(a) _mm_abs_epi16(a)
#define abs_i32(a) _mm_abs_epi32(a)
#define abs_i8(a) _mm_abs_epi8(a)

#define add_i8(a, b) _mm_add_epi8(a, b)
#define add_i16(a, b) _mm_add_epi16(a, b)
#define add_i32(a, b) _mm_add_epi32(a, b)
#define add_i64(a, b) _mm_add_epi64(a, b)
#define add_mf64(a, b) _mm_add_pd(a, b)
#define add_mf32(a, b) _mm_add_ps(a, b)
#define add_f64(a, b) _mm_add_sd(a, b)
#define add_f32(a, b) _mm_add_ss(a, b)

#define adds_i8(a, b) _mm_adds_epi8(a, b)
#define adds_i16(a, b) _mm_adds_epi16(a, b)
#define adds_i32(a, b) _mm_adds_epi32(a, b)
#define adds_i64(a, b) _mm_adds_epi64(a, b)

#define addsub_mf64(a, b) _mm_addsub_pd(a, b)
#define addsub_mf32(a, b) _mm_addsub_ps(a, b)
#define addsub_f64(a, b) _mm_addsub_sd(a, b)

#define and_f64(a, b) _mm_and_pd(a, b)
#define and_f32(a, b) _mm_and_ps(a, b)
#define and_i128(a, b) _mm_and_si128(a, b)

#define andnot_f64(a, b) _mm_andnot_pd(a, b)
#define andnot_f32(a, b) _mm_andnot_ps(a, b)
#define andnot_i128(a, b) _mm_andnot_si128(a, b)

#define average_u8(a, b) _mm_avg_epu8(a, b)
#define average_u16(a, b) _mm_avg_epu16(a, b)

#define raverage_u8(a, b) _mm_avg_pu8(a, b)
#define raverage_u16(a, b) _mm_avg_pu16(a, b)

#define blend_i16(a, b, i) _mm_blend_epi16(a, b, i)
#define blend_f64(a, b, i) _mm_blend_pd(a, b, i)
#define blend_f32(a, b, i) _mm_blend_ps(a, b, i)

#define blendv_i8(a, b, m) _mm_blendv_epi8(a, b, m)
#define blendv_f64(a, b, m) _mm_blendv_pd(a, b, m)
#define blendv_f32(a, b, m) _mm_blendv_ps(a, b, m)

#define bshl_i128(a, i) _mm_bslli_si128(a, i)
#define bshr_i128(a, i) _mm_bsrli_si128(a, i)

#define shl_i128(a, i) _mm_slli_si128(a, i)
#define shr_i128(a, i) _mm_srli_si128(a, i)
#define shl_i16(a, i) _mm_slli_epi16(a, i)
#define shr_i16(a, i) _mm_srli_epi16(a, i)
#define shl_i32(a, i) _mm_slli_epi32(a, i)
#define shr_i32(a, i) _mm_srli_epi32(a, i)
#define shl_i64(a, i) _mm_slli_epi64(a, i)
#define shr_i64(a, i) _mm_srli_epi64(a, i)

#define ceil_pd(a) _mm_ceil_pd(a)
#define ceil_ps(a) _mm_ceil_ps(a)
#define ceil_sd(a, b) _mm_ceil_sd(a, b)
#define ceil_ss(a, b) _mm_ceil_ss(a, b)

#define extract_i8(a, i) _mm_extract_epi8(a, i)
#define extract_i16(a, i) _mm_extract_epi16(a, i)
#define extract_i32(a, i) _mm_extract_epi32(a, i)
#define extract_i64(a, i) _mm_extract_epi64(a, i)

#define shuffle_i8(a, xm) _mm_shuffle_epi8(a, xm)
#define shuffle64_i8(a, m) _mm_shuffle_pi8(a, m)
#define shuffleh_i16(a, m) _mm_shufflehi_epi16(a, m)
#define shufflel_i16(a, m) _mm_shufflelo_epi16(a, m)
#define shuffle64_i16(a, m) _mm_shuffle_pi16(a, m)
#define shuffle_i32(a, m) _mm_shuffle_epi32(a, m)

#ifndef _MAVX_

#define shuffle_f32(a, m) _mm_shuffle_ps(a, a, m)
#define shuffle_f64(a, m) _mm_shuffle_pd(a, a, m)

#else 

#define shuffle_f32(a, m) _mm_permute_ps(a, a, m)
#define shuffle_f64(a, m) _mm_permute_pd(a, m)

#endif

#define shufflem_f64(a, b, m) _mm_shuffle_pd(a, b, m)
#define shufflem_f32(a, b, m) _mm_shuffle_ps(a, b, m)

#define broadcast_i8(a) _mm_set1_epi8(a)
#define broadcast_i16(a) _mm_set1_epi16(a)
#define broadcast_i32(a) _mm_set1_epi32(a)
#define broadcast_i64(a) _mm_set1_epi64x(a)
#define broadcast_f64(a) _mm_set1_pd(a)
#define broadcast_f32(a) _mm_set1_ps(a)

#define sub_i8(a, b) _mm_sub_epi8(a, b)
#define sub_i16(a, b) _mm_sub_epi16(a, b)
#define sub_i32(a, b) _mm_sub_epi32(a, b)
#define sub_i64(a, b) _mm_sub_epi64(a, b)
#define sub_mf64(a, b) _mm_sub_pd(a, b)
#define sub_mf32(a, b) _mm_sub_ps(a, b)
#define sub_f64(a, b) _mm_sub_sd(a, b)

#define mul_mf64(a, b) _mm_mul_pd(a, b)
#define mul_mf32(a, b) _mm_mul_ps(a, b)
#define mul_f64(a, b) _mm_mul_sd(a, b)

#define div_mf64(a, b) _mm_div_pd(a, b)
#define div_mf32(a, b) _mm_div_ps(a, b)
#define div_f64(a, b) _mm_div_sd(a, b)

#define or_f64(a, b) _mm_or_pd(a, b)
#define or_f32(a, b) _mm_or_ps(a, b)
#define or_i128(a, b) _mm_or_si128(a, b)

#define xor_f64(a, b) _mm_xor_pd(a, b)
#define xor_f32(a, b) _mm_xor_ps(a, b)
#define xor_i128(a, b) _mm_xor_si128(a, b)

#define load_mf64(ptr) _mm_load_pd(ptr)
#define load_mf32(ptr) _mm_load_ps(ptr)
#define load_f64(ptr) _mm_load_sd(ptr)
#define load_f32(ptr) _mm_load_ss(ptr)
#define load_i128(ptr) _mm_load_si128(ptr)

#define uload_mf64(ptr) _mm_loadu_pd(ptr)
#define uload_mf32(ptr) _mm_loadu_ps(ptr)
#define uload_f64(ptr) load_sd(ptr)
#define uload_f32(ptr) load_ss(ptr)
#define uload_i128(ptr) _mm_lddqu_si128(ptr)

#define store_mf64(dest, src) _mm_store_pd(dest, src)
#define store_mf32(dest, src) _mm_store_ps(dest, src)
#define store_f64(dest, src) _mm_store_sd(dest, src)
#define store_f32(dest, src) _mm_store_ss(dest, src)
#define store_i128(dest, src) _mm_store_si128(dest, src)

#define ustore_mf64(dest, src) _mm_storeu_pd(dest, src)
#define ustore_mf32(dest, src) _mm_storeu_ps(dest, src)
#define ustore_f64(dest, src) store_sd(dest, src)
#define ustore_f32(dest, src) store_ss(dest, src)
#define ustore_i128(dest, src) _mm_storeu_si128(dest, src)

// ymm/AVX intrinsics

#ifdef _MAVX_

#define add256_f64(a, b) _mm256_add_pd(a, b)
#define add256_f32(a, b) _mm256_add_ps(a, b)

#define sub256_f64(a, b) _mm256_sub_pd(a, b)
#define sub256_f32(a, b) _mm256_sub_ps(a, b)

#define mul256_f64(a, b) _mm256_mul_pd(a, b)
#define mul256_f32(a, b) _mm256_mul_ps(a, b)

#define div256_f64(a, b) _mm256_div_pd(a, b)
#define div256_f32(a, b) _mm256_div_ps(a, b)

#define and256_f64(a, b) _mm256_and_pd(a, b)
#define and256_f32(a, b) _mm256_and_ps(a, b)

#define andnot256_f64(a, b) _mm256_andnot_pd(a, b)
#define andnot256_f32(a, b) _mm256_andnot_ps(a, b)

#define or256_f64(a, b) _mm256_or_pd(a, b)
#define or256_f32(a, b) _mm256_or_ps(a, b)

#define xor256_f64(a, b) _mm256_xor_pd(a, b)
#define xor256_f32(a, b) _mm256_xor_ps(a, b)

#define blend256_f64(a, b, m) _mm256_blend_pd(a, b, m)
#define blend256_f32(a, b, m) _mm256_blend_ps(a, b, m)

#define blendv256_f64(a, b, mv) _mm256_blendv_pd(a, b, mv)
#define blendv256_f32(a, b, mv) _mm256_blendv_ps(a, b, mv)

#if _MAVX_ >= 2

#define add256_i8(a, b) _mm256_add_epi8(a, b)
#define add256_i16(a, b) _mm256_add_epi16(a, b)
#define add256_i32(a, b) _mm256_add_epi32(a, b)
#define add256_i64(a, b) _mm256_add_epi64(a, b)

#define sub256_i8(a, b) _mm256_sub_epi8(a, b)
#define sub256_i16(a, b) _mm256_sub_epi16(a, b)
#define sub256_i32(a, b) _mm256_sub_epi32(a, b)
#define sub256_i64(a, b) _mm256_sub_epi64(a, b)

#define mul256_i8(a, b) _mm256_mul_epi8(a, b)
#define mul256_i16(a, b) _mm256_mul_epi16(a, b)
#define mul256_i32(a, b) _mm256_mul_epi32(a, b)
#define mul256_i64(a, b) _mm256_mul_epi64(a, b)

#define shl256_i128(a, i) _mm256_bslli_epi128(a, i)
#define shr256_i128(a, i) _mm256_bsrli_epi128(a, i)

#define shl256_i16(a, i) _mm256_slli_epi16(a, i)
#define shr256_i16(a, i) _mm256_srli_epi16(a, i)
#define shl256_i32(a, i) _mm256_slli_epi32(a, i)
#define shr256_i32(a, i) _mm256_srli_epi32(a, i)
#define shl256_i64(a, i) _mm256_slli_epi64(a, i)
#define shr256_i64(a, i) _mm256_srli_epi64(a, i)

#define shlv256_i16(a, iv) _mm256_sll_epi16(a, iv)
#define shrv256_i16(a, iv) _mm256_srl_epi16(a, iv)
#define shlv256_i32(a, iv) _mm256_sll_epi32(a, iv)
#define shrv256_i32(a, iv) _mm256_srl_epi32(a, iv)
#define shlv256_i64(a, iv) _mm256_sll_epi64(a, iv)
#define shrv256_i64(a, iv) _mm256_srl_epi64(a, iv)

#define and_i256(a, b) _mm256_and_si256(a, b)
#define andnot_i256(a, b) _mm256_andnot_si256(a, b)
#define or_i256(a, b) _mm256_or_si256(a, b)
#define xor_i256(a, b) _mm256_xor_si256(a, b)

#define blend256_i16(a, b, i) _mm256_blend_epi16(a, b, i)
#define blend256_i32(a, b, i) _mm256_blend_epi32(a, b, i) 
#define blendv256_i8(a, b, mv) _mm256_blendv_epi8(a, b, mv)

#endif

#define shuffle256_f64(a, m) _mm256_permute_pd(a, m)
#define shufflem256_f64(a, b, m) _mm256_shuffle_pd(a, b, m)
#define shuffle256_f32(a, m) _mm256_permute_ps(a, m)
#define shufflem256_f32(a, b, m) _mm256_shuffle_ps(a, b, m)

#define permute256_f64(a, b, m) _mm256_permute2f128_pd(a, b, m)
#define permute256_f32(a, b, m) _mm256_permute2f128_ps(a, b, m)
#define permute_i256(a, b, m) _mm256_permute2f128_si256(a, b, m)

#define load256_f64(ptr) _mm256_load_pd(ptr)
#define load256_f32(ptr) _mm256_load_ps(ptr)
#define load_i256(src) _mm256_load_si256(src)

#define uload256_f64(ptr) _mm256_loadu_pd(ptr)
#define uload256_f32(ptr) _mm256_loadu_ps(ptr)
#define uload_i256(ptr) _mm256_lddqu_si256(ptr)

#define store256_f64(dest, src) _mm256_store_pd(dest, src)
#define store256_f32(dest, src) _mm256_store_ps(dest, src)
#define store_i256(dest, src) _mm256_store_si256(dest, src)

#define ustore256_f64(dest, src) _mm256_storeu_pd(dest, src)
#define ustore256_f32(dest, src) _mm256_storeu_ps(dest, src)
#define ustore_i256(dest, src) _mm256_storeu_si256(dest, src)

#endif

// Non-SIMD intrinsics

#define spinlock_pause() _mm_pause()

#define crc32_u8(crc, u8) _mm_crc32_u8(crc, u8)
#define crc32_u16(crc, u16) _mm_crc32_u16(crc, u16)
#define crc32_u32(crc, u32) _mm_crc32_u32(crc, u32)
#define crc32_u64(crc, u64) _mm_crc32_u64(crc, u64)

// TODO: Add more stuff

#endif
