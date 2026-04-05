/**
 * @file LinearColor.cpp
 * @brief 各チャンネルが単精度浮動小数点数の色を表現します
 */

// インクルード
#include "MirageEngine/Graphics/Color/LinearColor.hpp"
#include "MirageEngine/Graphics/Color/Color.hpp"
#include "MirageEngine/Graphics/Color/PackedColor.hpp"

// usingディレクティブ
using namespace mirage_engine::graphics;


/**
 * @brief コンストラクタ
 *
 * @param[in] color 色
 */
LinearColor::LinearColor(const Color& color) noexcept
    : LinearColor(color.Red / 255.0f, color.Green / 255.0f, color.Blue / 255.0f, color.Alpha / 255.0f)
{
}

/**
 * @brief コンストラクタ
 *
 * @param[in] color 色
 */
LinearColor::LinearColor(const PackedColor& color) noexcept
    : LinearColor(color.Value)
{
}
