/**
 * @file LinearColor.hpp
 * @brief 各チャンネルが単精度浮動小数点数の色を表現します
 */
#ifndef MIRAGE_ENGINE_GRAPHICS_LINEAR_COLOR_HPP
#define MIRAGE_ENGINE_GRAPHICS_LINEAR_COLOR_HPP

 // インクルード
#include <cstdint>
#include <type_traits>
#include "MirageEngine/Utility/Property/Property.hpp"


// 前方宣言
namespace mirage_engine {
namespace graphics {
    class Color;
    class PackedColor;
}   // namespace graphics
}   // namespace mirage_engine

namespace mirage_engine {
namespace graphics {

    /**
     * @class LinearColor
     * @brief 各チャンネルが単精度浮動小数点数の色を表現します。
     * 
     * @note
     * - 各チャンネルの値は 0.0 ～ 1.0 の範囲で制限されません。
     * - HDRなどで負の値や1.0を超える値を使用可能にできる仕様です。
     */
    class LinearColor final
    {
    public:

        /**
         * @brief コンストラクタ
         *
         * @note 不透明な黒で初期化します。(Red = 0.0f, Green = 0.0f, Blue = 0.0f, Alpha = 1.0f)
         */
        constexpr LinearColor() noexcept = default;

        /**
         * @brief コンストラクタ
         *
         * @param[in] color ARGB形式の色（各チャンネルが8bit）
         */
        constexpr explicit LinearColor(uint32_t color) noexcept;

        /**
         * @brief コンストラクタ
         *
         * @param[in] red 赤
         * @param[in] green 緑
         * @param[in] blue 青
         * @param[in] alpha 透過率
         */
        constexpr LinearColor(float red, float green, float blue, float alpha) noexcept;

        /**
         * @brief コンストラクタ
         *
         * @param[in] color 色
         */
        constexpr explicit LinearColor(const LinearColor& color) noexcept = default;

        /**
         * @brief コンストラクタ
         *
         * @param[in] color 色
         */
        constexpr explicit LinearColor(LinearColor&& color) noexcept = default;

        /**
         * @brief コンストラクタ
         *
         * @param[in] color 色
         */
        explicit LinearColor(const Color& color) noexcept;

        /**
         * @brief コンストラクタ
         *
         * @param[in] color 色
         */
        explicit LinearColor(const PackedColor& color) noexcept;

        /**
         * @brief ARGB値を取得する
         *
         * @return ARGB値
         */
        [[nodiscard]]
        constexpr uint32_t ToARGB() const noexcept;

        /**
         * @brief ABGR値を取得する
         *
         * @return ABGR値
         */
        [[nodiscard]]
        constexpr uint32_t ToABGR() const noexcept;

        /**
         * @brief RGBA値を取得する
         *
         * @return RGBA値
         */
        [[nodiscard]]
        constexpr uint32_t ToRGBA() const noexcept;

        /**
         * @brief BGRA値を取得する
         *
         * @return BGRA値
         */
        [[nodiscard]]
        constexpr uint32_t ToBGRA() const noexcept;

        /**
         * @brief 透過率のみ変更した色を取得する
         *
         * @param[in] alpha 透過率
         * @return 透過率を変更した色
         */
        [[nodiscard]]
        constexpr LinearColor WithAlpha(float alpha) const noexcept;

        /**
         * @brief 不透明かチェックする
         *
         * @retval true 不透明である
         * @retval false 不透明でない
         *
         * @note
         * - 各チャンネルの値は 0.0 ～ 1.0 の範囲で制限されません。
         * - そのため Alpha >= 1.0f の場合はtrue
         */
        [[nodiscard]]
        constexpr bool IsOpaque() const noexcept;

        /**
         * @brief 透明かチェックする
         *
         * @retval true 透明である
         * @retval false 透明でない
         *
         * @note
         * - 各チャンネルの値は 0.0 ～ 1.0 の範囲で制限されません。
         * - そのため Alpha <= 0.0f の場合はtrue
         */
        [[nodiscard]]
        constexpr bool IsTransparent() const noexcept;

        /**
         * @brief 色をコピーする
         *
         * @param[in] color 色
         * @return コピーした色
         */
        constexpr LinearColor& operator = (const LinearColor& color) noexcept = default;

        /**
         * @brief 色をコピーする
         *
         * @param[in] color 色
         * @return コピーした色
         */
        constexpr LinearColor& operator = (LinearColor&& color) noexcept = default;

        /**
         * @brief 色を加算合成する
         *
         * @param[in] color 色
         * @return 加算合成した色
         *
         * @note
         * - 各チャンネルはclampされません。
         * - 負の値や1.0を超える値がそのまま保持されます。
         */
        constexpr LinearColor& operator += (const LinearColor& color) noexcept;

        /**
         * @brief 色をスカラー倍する
         *
         * @param[in] scalar 倍率
         * @return スカラー倍した色
         *
         * @note
         * - 各チャンネルはclampされません。
         * - 負の値や1.0を超える値がそのまま保持されます。
         */
        constexpr LinearColor& operator *= (float scalar) noexcept;

        /**
         * @brief 同色か比較する
         *
         * @param[in] color 色
         * @retval true 同色である
         * @retval false 同色でない
         *
         * @note 各チャンネルの値はε（イプシロン）を用いた近似比較を行います。
         */
        constexpr bool operator == (const LinearColor& color) const noexcept;

        /**
         * @brief 同色でないか比較する
         *
         * @param[in] color 色
         * @retval true 同色でない
         * @retval false 同色である
         *
         * @note 各チャンネルの値はε（イプシロン）を用いた近似比較を行います。
         */
        constexpr bool operator != (const LinearColor& color) const noexcept;

        /**
         * @brief 2つの色を線形補間する
         *
         * @param[in] from_color 補間する色
         * @param[in] to_color 補間する色
         * @param[in] progress 補間係数
         * @return 線形補間した色
         */
        constexpr static LinearColor Lerp(const LinearColor& from_color, const LinearColor& to_color, float progress) noexcept;

        /**
         * @brief 赤
         *
         * @note 読み取り専用
         */
        utility::ReadOnlyProperty<LinearColor, float> Red = 0.0f;

        /**
         * @brief 緑
         *
         * @note 読み取り専用
         */
        utility::ReadOnlyProperty<LinearColor, float> Green = 0.0f;

        /**
         * @brief 青
         *
         * @note 読み取り専用
         */
        utility::ReadOnlyProperty<LinearColor, float> Blue = 0.0f;

        /**
         * @brief 透過率
         *
         * @note 読み取り専用
         */
        utility::ReadOnlyProperty<LinearColor, float> Alpha = 1.0f;

    };  // class LinearColor

    /**
     * @brief 色を加算する
     *
     * @param[in] color1 色
     * @param[in] color2 色
     * @return 加算した色
     *
     * @note
     * - 各チャンネルはclampされません。
     * - 負の値や1.0を超える値がそのまま保持されます。
     */
    constexpr LinearColor operator + (LinearColor color1, const LinearColor& color2);

    /**
     * @brief 色をスカラー倍する
     *
     * @param[in] color 色
     * @param[in] scalar 倍率
     * @return スカラー倍した色
     *
     * @note
     * - 各チャンネルはclampされません。
     * - 負の値や1.0を超える値がそのまま保持されます。
     */
    constexpr LinearColor operator * (LinearColor color, float scalar);


    // コンパイル時検証

    // メモリサイズの検証
    // 各チャンネルがReadOnlyPropertyで値を保持しているため、合計で16byteになっているかチェックします。
    static_assert(sizeof(LinearColor) == 16, "LinearColorクラスのサイズが16byteではありません。パディングが入っている可能性があります。");

    // メモリ配置の検証
    // 各チャンネルがReadOnlyPropertyで値を保持しているため、Red、Green、Blue、Alphaの順番でメモリ配置されているかチェックします。
    static_assert(offsetof(LinearColor, Red) == 0 && offsetof(LinearColor, Green) == 4 && offsetof(LinearColor, Blue) == 8 && offsetof(LinearColor, Alpha) == 12, "LinearColorクラスの各チャンネルのオフセットが不正です。Red、Green、Blue、Alphaの順に1byteずつ並んでいるか確認してください。");

    // 標準レイアウト型か検証
    // C言語の構造体と互換性があり、多言語（C#など）とのデータの受け渡しが安全かチェックします。
    static_assert(std::is_standard_layout_v<LinearColor>, "LinearColorクラスは標準レイアウト型である必要があります。");

}   // namespace graphics
}   // namespace mirage_engine

// インクルード
#include "MirageEngine/Graphics/Color/Detail/LinearColorDetail.hpp"


#endif  // MIRAGE_ENGINE_GRAPHICS_LINEAR_COLOR_HPP
