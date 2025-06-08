/**
 * @file Inline.hpp
 * @brief インライン定義
 */
#ifndef MIRAGE_ENGINE_INLINE_HPP
#define MIRAGE_ENGINE_INLINE_HPP


#ifdef _MSC_VER
    /**
     * @def INLINE
     * @brief 関数をインライン化するように指示します。（Microsoftコンパイラ）
     *
     * @attention インライン化されるかはコンパイラ次第
     */
    #define INLINE __inline

#elif defined(__GNUC__) || defined(__clang__)
     /**
      * @def INLINE
      * @brief 関数をインライン化するように指示します。（gcc, clangコンパイラ）
      *
      * @attention インライン化されるかはコンパイラ次第
      */
    #define INLINE inline

#endif  // _MSC_VER


#ifdef _MSC_VER
    /**
     * @def FORCEINLINE
     * @brief 関数を強制的にインライン化するように指示します。（Microsoftコンパイラ）
     *
     * @attention インライン化されるかはコンパイラ次第
     */
    #define FORCEINLINE __forceinline

#elif defined(__GNUC__) || defined(__clang__)
    /**
     * @def FORCEINLINE
     * @brief 関数を強制的にインライン化するように指示します。（gcc, clangコンパイラ）
     *
     * @attention インライン化されるかはコンパイラ次第
     */
    #define FORCEINLINE __attribute__((always_inline)) inline

#endif  // _MSC_VER


#endif  // MIRAGE_ENGINE_INLINE_HPP
