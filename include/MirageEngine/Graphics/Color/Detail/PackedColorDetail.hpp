/**
 * @file PackedColorDetail.hpp
 * @brief 各チャンネルを32bitにパックした色を表現します
 */
#ifndef MIRAGE_ENGINE_GRAPHICS_PACKED_COLOR_DETAIL_HPP
#define MIRAGE_ENGINE_GRAPHICS_PACKED_COLOR_DETAIL_HPP


namespace mirage_engine {
namespace graphics {

    namespace color_detail
    {
        // 赤取得用関数
        // 外部公開はしないのでdoxygenコメントは不要
        inline constexpr uint8_t Red(uint32_t color)
        {
            return (color >> 16) & 0xFF;
        }

        // 緑取得用関数
        // 外部公開はしないのでdoxygenコメントは不要
        inline constexpr uint8_t Green(uint32_t color)
        {
            return (color >> 8) & 0xFF;
        }

        // 青取得用関数
        // 外部公開はしないのでdoxygenコメントは不要
        inline constexpr uint8_t Blue(uint32_t color)
        {
            return color & 0xFF;
        }

        // 透過率取得用関数
        // 外部公開はしないのでdoxygenコメントは不要
        inline constexpr uint8_t Alpha(uint32_t color)
        {
            return (color >> 24) & 0xFF;
        }
    }   // namespace color_detail

    /**
     * @brief コンストラクタ
     *
     * @param[in] color ARGB形式の色（各チャンネルが8bit）
     */
    constexpr PackedColor::PackedColor(uint32_t color) noexcept
        : Value(color)
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
    constexpr PackedColor::PackedColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) noexcept
        : PackedColor((static_cast<uint32_t>(alpha) << 24) | (static_cast<uint32_t>(red) << 16) | (static_cast<uint32_t>(green) << 8) | (static_cast<uint32_t>(blue)))
    {
    }

    /**
     * @brief ARGB値を取得する
     *
     * @return ARGB値
     */
    [[nodiscard]]
    constexpr uint32_t PackedColor::ToARGB() const noexcept
    {
        return Value;
    }

    /**
     * @brief ABGR値を取得する
     *
     * @return ABGR値
     */
    [[nodiscard]]
    constexpr uint32_t PackedColor::ToABGR() const noexcept
    {
        return (static_cast<uint32_t>(color_detail::Alpha(Value)) << 24) |
               (static_cast<uint32_t>(color_detail::Blue(Value)) << 16) |
               (static_cast<uint32_t>(color_detail::Green(Value)) << 8) |
               (static_cast<uint32_t>(color_detail::Red(Value)));
    }

    /**
     * @brief RGBA値を取得する
     *
     * @return RGBA値
     */
    [[nodiscard]]
    constexpr uint32_t PackedColor::ToRGBA() const noexcept
    {
        return (static_cast<uint32_t>(color_detail::Red(Value)) << 24) |
               (static_cast<uint32_t>(color_detail::Green(Value)) << 16) |
               (static_cast<uint32_t>(color_detail::Blue(Value)) << 8) |
               (static_cast<uint32_t>(color_detail::Alpha(Value)));
    }

    /**
     * @brief BGRA値を取得する
     *
     * @return BGRA値
     */
    [[nodiscard]]
    constexpr uint32_t PackedColor::ToBGRA() const noexcept
    {
        return (static_cast<uint32_t>(color_detail::Blue(Value)) << 24) |
               (static_cast<uint32_t>(color_detail::Green(Value)) << 16) |
               (static_cast<uint32_t>(color_detail::Red(Value)) << 8) |
               (static_cast<uint32_t>(color_detail::Alpha(Value)));
    }

    /**
     * @brief 透過率のみ変更した色を取得する
     *
     * @param[in] alpha 透過率
     * @return 透過率を変更した色
     */
    [[nodiscard]]
    constexpr PackedColor PackedColor::WithAlpha(uint8_t alpha) const noexcept
    {
        return PackedColor(color_detail::Red(Value), color_detail::Green(Value), color_detail::Blue(Value), alpha);
    }

    /**
     * @brief 不透明かチェックする
     *
     * @retval true 不透明である
     * @retval false 不透明でない
     */
    [[nodiscard]]
    constexpr bool PackedColor::IsOpaque() const noexcept
    {
        return color_detail::Alpha(Value) == 255;
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
    constexpr bool PackedColor::IsTransparent() const noexcept
    {
        return color_detail::Alpha(Value) == 0;
    }

    /**
     * @brief 色を加算合成する
     *
     * @param[in] color 色
     * @return 加算合成した色
     *
     * @note 各チャンネル最大255で飽和します。
     */
    constexpr PackedColor& PackedColor::operator += (const PackedColor& color) noexcept
    {
        constexpr auto saturation_addition = [](uint8_t value1, uint8_t value2) constexpr
        {
            uint16_t sum = value1 + value2;

            return sum > 255 ? 255 : static_cast<uint8_t>(sum);
        };

        uint8_t red = saturation_addition(color_detail::Red(Value), color_detail::Red(color.Value));
        uint8_t green = saturation_addition(color_detail::Green(Value), color_detail::Green(color.Value));
        uint8_t blue = saturation_addition(color_detail::Blue(Value), color_detail::Blue(color.Value));
        uint8_t alpha = saturation_addition(color_detail::Alpha(Value), color_detail::Alpha(color.Value));

        Value = (static_cast<uint32_t>(alpha) << 24) | (static_cast<uint32_t>(red) << 16) | (static_cast<uint32_t>(green) << 8) | (static_cast<uint32_t>(blue));

        return *this;
    }

    /**
     * @brief 色をスカラー倍する
     *
     * @param[in] scalar 倍率（0.0 ～ 1.0）
     * @return スカラー倍した色
     */
    constexpr PackedColor& PackedColor::operator *= (float scalar) noexcept
    {
        if (scalar < 0.0f) { scalar = 0.0f; }
        if (scalar > 1.0f) { scalar = 1.0f; }

        constexpr auto scalar_multiplication = [](uint8_t value, float scalar) constexpr
        {
            return static_cast<uint8_t>(value * scalar + 0.5f);
        };

        uint8_t red = scalar_multiplication(color_detail::Red(Value), scalar);
        uint8_t green = scalar_multiplication(color_detail::Green(Value), scalar);
        uint8_t blue = scalar_multiplication(color_detail::Blue(Value), scalar);
        uint8_t alpha = scalar_multiplication(color_detail::Alpha(Value), scalar);

        Value = (static_cast<uint32_t>(alpha) << 24) | (static_cast<uint32_t>(red) << 16) | (static_cast<uint32_t>(green) << 8) | (static_cast<uint32_t>(blue));

        return *this;
    }

    /**
     * @brief 同色か比較する
     *
     * @param[in] color 色
     * @retval true 同色である
     * @retval false 同色でない
     */
    constexpr bool PackedColor::operator == (const PackedColor& color) const noexcept
    {
        return Value == color.Value;
    }

    /**
     * @brief 同色でないか比較する
     *
     * @param[in] color 色
     * @retval true 同色でない
     * @retval false 同色である
     */
    constexpr bool PackedColor::operator != (const PackedColor& color) const noexcept
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
    constexpr PackedColor PackedColor::Lerp(const PackedColor& from_color, const PackedColor& to_color, float progress) noexcept
    {
        if (progress < 0.0f) { progress = 0.0f; }
        if (progress > 1.0f) { progress = 1.0f; }

        constexpr auto lerp = [](uint8_t value1, uint8_t value2, float progress) constexpr
        {
            return static_cast<uint8_t>(value1 + (value2 - value1) * progress + 0.5f);
        };

        uint8_t red = lerp(color_detail::Red(from_color.Value), color_detail::Red(to_color.Value), progress);
        uint8_t green = lerp(color_detail::Green(from_color.Value), color_detail::Green(to_color.Value), progress);
        uint8_t blue = lerp(color_detail::Blue(from_color.Value), color_detail::Blue(to_color.Value), progress);
        uint8_t alpha = lerp(color_detail::Alpha(from_color.Value), color_detail::Alpha(to_color.Value), progress);

        return PackedColor(red, green, blue, alpha);
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
    constexpr PackedColor operator + (PackedColor color1, const PackedColor& color2)
    {
        color1 += color2;

        return PackedColor(color1);
    }

    /**
     * @brief 色をスカラー倍する
     *
     * @param[in] color 色
     * @param[in] scalar 倍率（0.0 ～ 1.0）
     * @return スカラー倍した色
     */
    constexpr PackedColor operator * (PackedColor color, float scalar)
    {
        color *= scalar;

        return PackedColor(color);
    }

}   // namespace graphics
}   // namespace mirage_engine

#endif  // MIRAGE_ENGINE_GRAPHICS_PACKED_COLOR_DETAIL_HPP
