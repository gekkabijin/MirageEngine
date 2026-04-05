/**
 * @file Color.hpp
 * @brief 各チャンネルが8bitの色を表現します
 */
#ifndef MIRAGE_ENGINE_GRAPHICS_COLOR_HPP
#define MIRAGE_ENGINE_GRAPHICS_COLOR_HPP

// インクルード
#include <cstdint>
#include <type_traits>
#include "MirageEngine/Utility/Property/Property.hpp"


// 前方宣言
namespace mirage_engine {
namespace graphics {
    class PackedColor;
    class LinearColor;
}   // namespace graphics
}   // namespace mirage_engine

namespace mirage_engine {
namespace graphics {

    /**
     * @class Color
     * @brief 各チャンネルが8bitの色を表現します。
     */
    class alignas(4) Color final
    {
    public:

        /**
         * @brief コンストラクタ
         * 
         * @note 不透明な黒で初期化します。(Red = 0, Green = 0, Blue = 0, Alpha = 255)
         */
        constexpr Color() noexcept = default;

        /**
         * @brief コンストラクタ
         * 
         * @param[in] color ARGB形式の色（各チャンネルが8bit）
         */
        constexpr explicit Color(uint32_t color) noexcept;

        /**
         * @brief コンストラクタ
         * 
         * @param[in] red 赤
         * @param[in] green 緑
         * @param[in] blue 青
         * @param[in] alpha 透過率
         */
        constexpr Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) noexcept;

        /**
         * @brief コンストラクタ
         * 
         * @param[in] color 色
         */
        constexpr explicit Color(const Color& color) noexcept = default;

        /**
         * @brief コンストラクタ
         *
         * @param[in] color 色
         */
        constexpr explicit Color(Color&& color) noexcept = default;

        /**
         * @brief コンストラクタ
         *
         * @param[in] color 色
         */
        explicit Color(const PackedColor& color) noexcept;

        /**
         * @brief コンストラクタ
         *
         * @param[in] color 色
         *
         * @note 各チャンネルは 0.0 ～ 1.0 にclampされた後 0 ～ 255 に変換されます。
         */
        explicit Color(const LinearColor& color) noexcept;

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
        constexpr Color WithAlpha(uint8_t alpha) const noexcept;

        /**
         * @brief 不透明かチェックする
         * 
         * @retval true 不透明である
         * @retval false 不透明でない
         */
        [[nodiscard]]
        constexpr bool IsOpaque() const noexcept;

        /**
         * @brief 透明かチェックする
         *
         * @retval true 透明である
         * @retval false 透明でない
         *
         * @note Alpha == 0 の場合のみtrue
         */
        [[nodiscard]]
        constexpr bool IsTransparent() const noexcept;

        /**
         * @brief 色をコピーする
         *
         * @param[in] color 色
         * @return コピーした色
         */
        constexpr Color& operator = (const Color& color) noexcept = default;

        /**
         * @brief 色をコピーする
         *
         * @param[in] color 色
         * @return コピーした色
         */
        constexpr Color& operator = (Color&& color) noexcept = default;

        /**
         * @brief 色を加算合成する
         * 
         * @param[in] color 色
         * @return 加算合成した色
         * 
         * @note 各チャンネル最大255で飽和します。
         */
        constexpr Color& operator += (const Color& color) noexcept;

        /**
         * @brief 色をスカラー倍する
         *
         * @param[in] scalar 倍率（0.0 ～ 1.0）
         * @return スカラー倍した色
         */
        constexpr Color& operator *= (float scalar) noexcept;

        /**
         * @brief 同色か比較する
         * 
         * @param[in] color 色
         * @retval true 同色である
         * @retval false 同色でない
         */
        constexpr bool operator == (const Color& color) const noexcept;

        /**
         * @brief 同色でないか比較する
         *
         * @param[in] color 色
         * @retval true 同色でない
         * @retval false 同色である
         */
        constexpr bool operator != (const Color& color) const noexcept;

        /**
         * @brief 2つの色を線形補間する
         * 
         * @param[in] from_color 補間する色
         * @param[in] to_color 補間する色
         * @param[in] progress 補間係数（0.0 ～ 1.0）
         * @return 線形補間した色
         */
        constexpr static Color Lerp(const Color& from_color, const Color& to_color, float progress) noexcept;

        /**
         * @brief 赤
         * 
         * @note 読み取り専用
         */
        utility::ReadOnlyProperty<Color, uint8_t> Red = 0;

        /**
         * @brief 緑
         *
         * @note 読み取り専用
         */
        utility::ReadOnlyProperty<Color, uint8_t> Green = 0;

        /**
         * @brief 青
         *
         * @note 読み取り専用
         */
        utility::ReadOnlyProperty<Color, uint8_t> Blue = 0;

        /**
         * @brief 透過率
         *
         * @note 読み取り専用
         */
        utility::ReadOnlyProperty<Color, uint8_t> Alpha = 255;

    };  // class Color

    /**
     * @brief 色を加算する
     *
     * @param[in] color1 色
     * @param[in] color2 色
     * @return 加算した色
     *
     * @note 各チャンネル最大255で飽和します。
     */
    constexpr Color operator + (Color color1, const Color& color2);

    /**
     * @brief 色をスカラー倍する
     *
     * @param[in] color 色
     * @param[in] scalar 倍率（0.0 ～ 1.0）
     * @return スカラー倍した色
     */
    constexpr Color operator * (Color color, float scalar);


    // コンパイル時検証

    // メモリサイズの検証
    // 各チャンネルがReadOnlyPropertyで値を保持しているため、合計で4byteになっているかチェックします。
    static_assert(sizeof(Color) == 4, "Colorクラスのサイズが4byteではありません。パディングが入っている可能性があります。");

    // メモリ配置の検証
    // 各チャンネルがReadOnlyPropertyで値を保持しているため、Red、Green、Blue、Alphaの順番でメモリ配置されているかチェックします。
    static_assert(offsetof(Color, Red) == 0 && offsetof(Color, Green) == 1 && offsetof(Color, Blue) == 2 && offsetof(Color, Alpha) == 3, "Colorクラスの各チャンネルのオフセットが不正です。Red、Green、Blue、Alphaの順に1byteずつ並んでいるか確認してください。");

    // 標準レイアウト型か検証
    // C言語の構造体と互換性があり、多言語（C#など）とのデータの受け渡しが安全かチェックします。
    static_assert(std::is_standard_layout_v<Color>, "Colorクラスは標準レイアウト型である必要があります。");

}   // namespace graphics
}   // namespace mirage_engine

// インクルード
#include "MirageEngine/Graphics/Color/Detail/ColorDetail.hpp"


#endif  // MIRAGE_ENGINE_GRAPHICS_COLOR_HPP
