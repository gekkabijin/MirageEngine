/**
 * @file Inline.hpp
 * @brief インライン定義
 */
#ifndef MIRAGE_ENGINE_SYSTEM_INLINE_HPP
#define MIRAGE_ENGINE_SYSTEM_INLINE_HPP


#ifdef _MSC_VER // Microsoftコンパイラ
    /**
     * @def INLINE
     * @brief 関数をインライン化するように指示します。
     *
     * @attention インライン化されるかはコンパイラ次第
     */
    #define MIRAGE_ENGINE_INLINE __inline

#elif defined(__GNUC__) || defined(__clang__)   // gcc, clangコンパイラ
     /**
      * @def INLINE
      * @brief 関数をインライン化するように指示します。
      *
      * @attention インライン化されるかはコンパイラ次第
      */
    #define MIRAGE_ENGINE_INLINE inline

#endif  // _MSC_VER


#ifdef _MSC_VER // Microsoftコンパイラ
    /**
     * @def FORCEINLINE
     * @brief 関数を強制的にインライン化するように指示します。
     *
     * @attention インライン化されるかはコンパイラ次第
     */
    #define MIRAGE_ENGINE_FORCEINLINE __forceinline

#elif defined(__GNUC__) || defined(__clang__)   // gcc, clangコンパイラ
    /**
     * @def FORCEINLINE
     * @brief 関数を強制的にインライン化するように指示します。
     *
     * @attention インライン化されるかはコンパイラ次第
     */
    #define MIRAGE_ENGINE_FORCEINLINE __attribute__((always_inline)) inline

#endif  // _MSC_VER


#endif  // MIRAGE_ENGINE_SYSTEM_INLINE_HPP
