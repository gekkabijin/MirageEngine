/**
 * @file PackedColor.cpp
 * @brief 各チャンネルを32bitにパックした色を表現します
 */

// インクルード
#include <algorithm>
#include "MirageEngine/Graphics/Color/PackedColor.hpp"
#include "MirageEngine/Graphics/Color/Color.hpp"
#include "MirageEngine/Graphics/Color/LinearColor.hpp"

// usingディレクティブ
using namespace mirage_engine::graphics;


/**
 * @brief コンストラクタ
 *
 * @param[in] color 色
 */
PackedColor::PackedColor(const Color& color) noexcept
    : PackedColor(color.Red, color.Green, color.Blue, color.Alpha)
{
}

/**
 * @brief コンストラクタ
 *
 * @param[in] color 色
 * 
 * @note 各チャンネルは 0.0 ～ 1.0 にclampされた後 0 ～ 255 に変換されます。
 */
PackedColor::PackedColor(const LinearColor& color) noexcept
    : PackedColor(static_cast<uint8_t>(std::clamp(color.Red.Value(), 0.0f, 1.0f) * 255.0f + 0.5f),
                  static_cast<uint8_t>(std::clamp(color.Green.Value(), 0.0f, 1.0f) * 255.0f + 0.5f),
                  static_cast<uint8_t>(std::clamp(color.Blue.Value(), 0.0f, 1.0f) * 255.0f + 0.5f),
                  static_cast<uint8_t>(std::clamp(color.Alpha.Value(), 0.0f, 1.0f) * 255.0f + 0.5f))
{
}
