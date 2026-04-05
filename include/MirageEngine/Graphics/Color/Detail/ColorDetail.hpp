/**
 * @file ColorDetail.hpp
 * @brief 各チャンネルが8bitの色を表現します
 */
#ifndef MIRAGE_ENGINE_GRAPHICS_COLOR_DETAIL_HPP
#define MIRAGE_ENGINE_GRAPHICS_COLOR_DETAIL_HPP


namespace mirage_engine {
namespace graphics {


    /**
     * @brief コンストラクタ
     *
     * @param[in] color ARGB形式の色（各チャンネルが8bit）
     */
    constexpr Color::Color(uint32_t color) noexcept
        : Color((color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF, (color >> 24) & 0xFF)
    {
    }

    /**
     * @brief コンストラクタ
     *
     * @param[in] red 赤
     * @param[in] green 緑
     * @param[in] blue 青
     * @param[in] alpha 透過率
     */
    constexpr Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) noexcept
        : Red(red), Green(green), Blue(blue), Alpha(alpha)
    {
    }

    /**
     * @brief ARGB値を取得する
     *
     * @return ARGB値
     */
    [[nodiscard]]
    constexpr uint32_t Color::ToARGB() const noexcept
    {
        return (static_cast<uint32_t>(Alpha) << 24) |
               (static_cast<uint32_t>(Red) << 16) |
               (static_cast<uint32_t>(Green) << 8) |
               (static_cast<uint32_t>(Blue));
    }

    /**
     * @brief ABGR値を取得する
     *
     * @return ABGR値
     */
    [[nodiscard]]
    constexpr uint32_t Color::ToABGR() const noexcept
    {
        return (static_cast<uint32_t>(Alpha) << 24) |
               (static_cast<uint32_t>(Blue) << 16) |
               (static_cast<uint32_t>(Green) << 8) |
               (static_cast<uint32_t>(Red));
    }

    /**
     * @brief RGBA値を取得する
     *
     * @return RGBA値
     */
    [[nodiscard]]
    constexpr uint32_t Color::ToRGBA() const noexcept
    {
        return (static_cast<uint32_t>(Red) << 24) |
               (static_cast<uint32_t>(Green) << 16) |
               (static_cast<uint32_t>(Blue) << 8) |
               (static_cast<uint32_t>(Alpha));
    }

    /**
     * @brief BGRA値を取得する
     *
     * @return BGRA値
     */
    [[nodiscard]]
    constexpr uint32_t Color::ToBGRA() const noexcept
    {
        return (static_cast<uint32_t>(Blue) << 24) |
               (static_cast<uint32_t>(Green) << 16) |
               (static_cast<uint32_t>(Red) << 8) |
               (static_cast<uint32_t>(Alpha));
    }

    /**
     * @brief 透過率のみ変更した色を取得する
     *
     * @param[in] alpha 透過率
     * @return 透過率を変更した色
     */
    [[nodiscard]]
    constexpr Color Color::WithAlpha(uint8_t alpha) const noexcept
    {
        return Color(Red, Green, Blue, alpha);
    }

    /**
     * @brief 不透明かチェックする
     *
     * @retval true 不透明である
     * @retval false 不透明でない
     */
    [[nodiscard]]
    constexpr bool Color::IsOpaque() const noexcept
    {
        return Alpha == 255;
    }

    /**
     * @brief 透明かチェックする
     *
     * @retval true 透明である
     * @retval false 透明でない
     *
     * @note Alpha == 0 の場合のみtrue
     */
    [[nodiscard]]
    constexpr bool Color::IsTransparent() const noexcept
    {
        return Alpha == 0;
    }

    /**
     * @brief 色を加算合成する
     *
     * @param[in] color 色
     * @return 加算合成した色
     *
     * @note 各チャンネル最大255で飽和します。
     */
    constexpr Color& Color::operator += (const Color& color) noexcept
    {
        constexpr auto saturation_addition = [](uint8_t value1, uint8_t value2) constexpr
        {
            uint16_t sum = value1 + value2;

            return sum > 255 ? 255 : static_cast<uint8_t>(sum);
        };

        Red = saturation_addition(Red, color.Red);
        Green = saturation_addition(Green, color.Green);
        Blue = saturation_addition(Blue, color.Blue);
        Alpha = saturation_addition(Alpha, color.Alpha);

        return *this;
    }

    /**
     * @brief 色をスカラー倍する
     *
     * @param[in] scalar 倍率（0.0 ～ 1.0）
     * @return スカラー倍した色
     */
    constexpr Color& Color::operator *= (float scalar) noexcept
    {
        if (scalar < 0.0f) { scalar = 0.0f; }
        if (scalar > 1.0f) { scalar = 1.0f; }

        constexpr auto scalar_multiplication = [](uint8_t value, float scalar) constexpr
        {
            return static_cast<uint8_t>(value * scalar + 0.5f);
        };

        Red = scalar_multiplication(Red, scalar);
        Green = scalar_multiplication(Green, scalar);
        Blue = scalar_multiplication(Blue, scalar);
        Alpha = scalar_multiplication(Alpha, scalar);

        return *this;
    }

    /**
     * @brief 同色か比較する
     *
     * @param[in] color 色
     * @retval true 同色である
     * @retval false 同色でない
     */
    constexpr bool Color::operator == (const Color& color) const noexcept
    {
        return Red == color.Red && Green == color.Green && Blue == color.Blue && Alpha == color.Alpha;
    }

    /**
     * @brief 同色でないか比較する
     *
     * @param[in] color 色
     * @retval true 同色でない
     * @retval false 同色である
     */
    constexpr bool Color::operator != (const Color& color) const noexcept
    {
        return !(*this == color);
    }

    /**
     * @brief 2つの色を線形補間する
     *
     * @param[in] from_color 補間する色
     * @param[in] to_color 補間する色
     * @param[in] progress 補間係数（0.0 ～ 1.0）
     * @return 線形補間した色
     */
    constexpr Color Color::Lerp(const Color& from_color, const Color& to_color, float progress) noexcept
    {
        if (progress < 0.0f) { progress = 0.0f; }
        if (progress > 1.0f) { progress = 1.0f; }

        constexpr auto lerp = [](uint8_t value1, uint8_t value2, float progress) constexpr
        {
            return static_cast<uint8_t>(value1 + (value2 - value1) * progress + 0.5f);
        };

        uint8_t red = lerp(from_color.Red, to_color.Red, progress);
        uint8_t green = lerp(from_color.Green, to_color.Green, progress);
        uint8_t blue = lerp(from_color.Blue, to_color.Blue, progress);
        uint8_t alpha = lerp(from_color.Alpha, to_color.Alpha, progress);

        return Color(red, green, blue, alpha);
    }

    /**
     * @brief 色を加算する
     *
     * @param[in] color1 色
     * @param[in] color2 色
     * @return 加算した色
     *
     * @note 各チャンネル最大255で飽和します。
     */
    constexpr Color operator + (Color color1, const Color& color2)
    {
        color1 += color2;

        return Color(color1);
    }

    /**
     * @brief 色をスカラー倍する
     *
     * @param[in] color 色
     * @param[in] scalar 倍率（0.0 ～ 1.0）
     * @return スカラー倍した色
     */
    constexpr Color operator * (Color color, float scalar)
    {
        color *= scalar;

        return Color(color);
    }

}   // namespace graphics
}   // namespace mirage_engine

#endif  // MIRAGE_ENGINE_GRAPHICS_COLOR_DETAIL_HPP
