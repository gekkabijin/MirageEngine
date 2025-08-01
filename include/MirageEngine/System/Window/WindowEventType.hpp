/**
 * @file WindowEventType.hpp
 * @brief ウィンドウイベント種別の定義
 */
#ifndef MIRAGE_ENGINE_SYSTEM_WINDOW_EVENT_TYPE_HPP
#define MIRAGE_ENGINE_SYSTEM_WINDOW_EVENT_TYPE_HPP


// インクルード
#include <Windows.h>

namespace mirage_engine {
namespace system {

    /**
     * @enum WindowEventType
     * @brief ウィンドウイベント種別
     * 
     * @attention
     * - Windowメッセージ（WM_*）のうち、使用頻度の高いもののみを定義しています。
     * - 必要に応じて他のメッセージも追加してください。
     */
    enum class WindowEventType
    {
        /**
         * @brief ウィンドウのクライアント領域の再描画要求
         */
        Paint = WM_PAINT,

        /**
         * @brief ウィンドウの破棄
         */
        Destroy = WM_DESTROY,

    };  // enum class WindowEventType

}   // namespace system
}   // namespace mirage_engine


#endif  // MIRAGE_ENGINE_SYSTEM_WINDOW_EVENT_TYPE_HPP
