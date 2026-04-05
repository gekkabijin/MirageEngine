/**
 * @file LiearColorDetail.hpp
 * @brief 各チャンネルが単精度浮動小数点数の色を表現します
 */
#ifndef MIRAGE_ENGINE_GRAPHICS_LINEAR_COLOR_DETAIL_HPP
#define MIRAGE_ENGINE_GRAPHICS_LINEAR_COLOR_DETAIL_HPP


namespace mirage_engine {
namespace graphics {

    namespace color_detail
    {
        // 色変換時のclamp用関数（0 ～ 255）
        // 外部公開はしないのでdoxygenコメントは不要
        inline constexpr uint8_t Clamp(float value)
        {
            if (value < 0.0f) { value = 0.0f; }
            if (value > 1.0f) { value = 1.0f; }

            return static_cast<uint8_t>(value * 255 + 0.5f);
        }
    }   // namespace color_detail

    /**
     * @brief コンストラクタ
     *
     * @param[in] color ARGB形式の色（各チャンネルが8bit）
     */
    constexpr LinearColor::LinearColor(uint32_t color) noexcept
        : LinearColor(((color >> 16) & 0xFF) / 255.0f, ((color >> 8) & 0xFF) /255.0f, (color & 0xFF) / 255.0f, ((color >> 24) & 0xFF) / 255.0f)
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
    constexpr LinearColor::LinearColor(float red, float green, float blue, float alpha) noexcept
        : Red(red), Green(green), Blue(blue), Alpha(alpha)
    {
    }

    /**
     * @brief ARGB値を取得する
     *
     * @return ARGB値
     */
    [[nodiscard]]
    constexpr uint32_t LinearColor::ToARGB() const noexcept
    {
        return (static_cast<uint32_t>(color_detail::Clamp(Alpha)) << 24) |
               (static_cast<uint32_t>(color_detail::Clamp(Red)) << 16) |
               (static_cast<uint32_t>(color_detail::Clamp(Green)) << 8) |
               (static_cast<uint32_t>(color_detail::Clamp(Blue)));
    }

    /**
     * @brief ABGR値を取得する
     *
     * @return ABGR値
     */
    [[nodiscard]]
    constexpr uint32_t LinearColor::ToABGR() const noexcept
    {
        return (static_cast<uint32_t>(color_detail::Clamp(Alpha)) << 24) |
               (static_cast<uint32_t>(color_detail::Clamp(Blue)) << 16) |
               (static_cast<uint32_t>(color_detail::Clamp(Green)) << 8) |
               (static_cast<uint32_t>(color_detail::Clamp(Red)));
    }

    /**
     * @brief RGBA値を取得する
     *
     * @return RGBA値
     */
    [[nodiscard]]
    constexpr uint32_t LinearColor::ToRGBA() const noexcept
    {
        return (static_cast<uint32_t>(color_detail::Clamp(Red)) << 24) |
                (static_cast<uint32_t>(color_detail::Clamp(Green)) << 16) |
                (static_cast<uint32_t>(color_detail::Clamp(Blue)) << 8) |
                (static_cast<uint32_t>(color_detail::Clamp(Alpha)));
    }

    /**
     * @brief BGRA値を取得する
     *
     * @return BGRA値
     */
    [[nodiscard]]
    constexpr uint32_t LinearColor::ToBGRA() const noexcept
    {
        return (static_cast<uint32_t>(color_detail::Clamp(Blue)) << 24) |
               (static_cast<uint32_t>(color_detail::Clamp(Green)) << 16) |
               (static_cast<uint32_t>(color_detail::Clamp(Red)) << 8) |
               (static_cast<uint32_t>(color_detail::Clamp(Alpha)));
    }

    /**
     * @brief 透過率のみ変更した色を取得する
     *
     * @param[in] alpha 透過率
     * @return 透過率を変更した色
     */
    [[nodiscard]]
    constexpr LinearColor LinearColor::WithAlpha(float alpha) const noexcept
    {
        return LinearColor(Red, Green, Blue, alpha);
    }

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
    constexpr bool LinearColor::IsOpaque() const noexcept
    {
        return Alpha >= 1.0f;
    }

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
    constexpr bool LinearColor::IsTransparent() const noexcept
    {
        return Alpha <= 0.0f;
    }

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
    constexpr LinearColor& LinearColor::operator += (const LinearColor& color) noexcept
    {
        Red += color.Red;
        Green += color.Green;
        Blue += color.Blue;
        Alpha += color.Alpha;

        return *this;
    }

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
    constexpr LinearColor& LinearColor::operator *= (float scalar) noexcept
    {
        Red *= scalar;
        Green *= scalar;
        Blue *= scalar;
        Alpha *= scalar;

        return *this;
    }

    /**
     * @brief 同色か比較する
     *
     * @param[in] color 色
     * @retval true 同色である
     * @retval false 同色でない
     * 
     * @note 各チャンネルの値はε（イプシロン）を用いた近似比較を行います。
     */
    constexpr bool LinearColor::operator == (const LinearColor& color) const noexcept
    {
        // ε：許容誤差
        const float EPSILON = 1.0e-5f;

        // @todo std::fabsがconstexprに対応していないためここでconstexpr版を定義
        constexpr auto fabs = [](float value) constexpr
        {
            return value < 0.0f ? -value : value;
        };

        return fabs(Red - color.Red) <= EPSILON &&
                fabs(Green - color.Green) <= EPSILON &&
                fabs(Blue - color.Blue) <= EPSILON &&
                fabs(Alpha - color.Alpha) <= EPSILON;
    }

    /**
     * @brief 同色でないか比較する
     *
     * @param[in] color 色
     * @retval true 同色でない
     * @retval false 同色である
     *
     * @note 各チャンネルの値はε（イプシロン）を用いた近似比較を行います。
     */
    constexpr bool LinearColor::operator != (const LinearColor& color) const noexcept
    {
        return !(*this == color);
    }

    /**
     * @brief 2つの色を線形補間する
     *
     * @param[in] from_color 補間する色
     * @param[in] to_color 補間する色
     * @param[in] progress 補間係数
     * @return 線形補間した色
     */
    constexpr LinearColor LinearColor::Lerp(const LinearColor& from_color, const LinearColor& to_color, float progress) noexcept
    {
        constexpr auto lerp = [](float value1, float value2, float progress) constexpr
        {
            return value1 + (value2 - value1) * progress;
        };

        float red = lerp(from_color.Red, to_color.Red, progress);
        float green = lerp(from_color.Green, to_color.Green, progress);
        float blue = lerp(from_color.Blue, to_color.Blue, progress);
        float alpha = lerp(from_color.Alpha, to_color.Alpha, progress);

        return LinearColor(red, green, blue, alpha);
    }

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
    constexpr LinearColor operator + (LinearColor color1, const LinearColor& color2)
    {
        color1 += color2;

        return LinearColor(color1);
    }

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
    constexpr LinearColor operator * (LinearColor color, float scalar)
    {
        color *= scalar;

        return LinearColor(color);
    }

}   // namespace graphics
}   // namespace mirage_engine

#endif  // MIRAGE_ENGINE_GRAPHICS_LINEAR_COLOR_DETAIL_HPP
