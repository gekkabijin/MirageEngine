/**
 * @file WindowStyle.hpp
 * @brief ウィンドウスタイルの定義
 */
#ifndef MIRAGE_ENGINE_SYSTEM_WINDOW_STYLE_HPP
#define MIRAGE_ENGINE_SYSTEM_WINDOW_STYLE_HPP


 // インクルード
#include <Windows.h>

namespace mirage_engine {
namespace system {

    /**
     * @enum WindowStyle
     * @brief ウィンドウスタイル
     *
     * @attention
     * - Windowスタイル（WS_*）のうち、使用頻度の高いもののみを定義しています。
     * - 必要に応じて他のスタイルも追加してください。
     */
    enum class WindowStyle : DWORD
    {
        /**
         * @brief デフォルトのスタイルです。
         * 
         * @note タイトルバー、最大化ボタン、最小化ボタン、システムメニューを追加します。
         */
        Default = WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU,

        /**
         * @brief 境界線を追加します。
         */
        Border = WS_BORDER,

        /**
         * @brief タイトルバーを追加します。
         * 
         * @note 細い境界線を含みます。（スタイルにBorderが含まれます）
         */
        Caption = WS_CAPTION,

        /**
         * @brief 最大化ボタンを追加します。
         */
        MaximizeButton = WS_MAXIMIZEBOX,

        /**
         * @brief 最小化ボタンを追加します。
         */
        MinimizeButton = WS_MINIMIZEBOX,

        /**
         * @brief タイトルバーにシステムメニューを追加します。
         */
        SystemMenu = WS_SYSMENU,

        /**
         * @brief サイズ変更が可能になります。
         */
        Resizable = WS_THICKFRAME,

        /**
         * @brief 水平スクロールバーを追加します。
         */
        HorizontalScroll = WS_HSCROLL,

        /**
         * @brief 垂直スクロールバーを追加します。
         */
        VerticalScroll = WS_VSCROLL,

        /**
         * @brief 装飾なしのポップアップスタイルです。
         */
        Popup = WS_POPUP,

        /**
         * @brief ウィンドウ作成時にウィンドウを表示します。
         * 
         * @note Visibleを使用しない場合は明示的に表示用のメソッドを使用する必要があります。
         */
        Visible = WS_VISIBLE,

    };  // enum class WindowStyle

    /**
     * @enum WindowExtraStyle
     * @brief ウィンドウ拡張スタイル
     * 
     * @attention
     * - Window拡張スタイル（WS_EX_*）のうち、使用頻度の高いもののみを定義しています。
     * - 必要に応じて他のスタイルも追加してください。
     */
    enum class WindowExtraStyle : DWORD
    {
        /**
         * @brief 拡張なし
         */
        None = 0,

        /**
         * @brief MDI子ウィンドウを作成します。
         */
        MDI = WS_EX_MDICHILD,

    };  // enum class WindowExtraStyle

    /**
     * @brief ウィンドウスタイルを結合します。
     * 
     * @param[in] style1 ウィンドウスタイル1
     * @param[in] style2 ウィンドウスタイル2
     * @return 結合したウィンドウスタイル
     */
    constexpr WindowStyle operator | (WindowStyle style1, WindowStyle style2)
    {
        return static_cast<WindowStyle>(static_cast<DWORD>(style1) | static_cast<DWORD>(style2));
    }

    /**
     * @brief 指定したウィンドウスタイルが含まれているか判定します。
     *
     * @param[in] style 基準となるウィンドウスタイル
     * @param[in] target 判定するウィンドウスタイル
     * @retval true 含まれている
     * @retval false 含まれていない
     */
    constexpr bool operator & (WindowStyle style, WindowStyle target)
    {
        return static_cast<bool>(static_cast<DWORD>(style) & static_cast<DWORD>(target));
    }

    /**
     * @brief ウィンドウ拡張スタイルを結合します。
     *
     * @param[in] style1 ウィンドウ拡張スタイル1
     * @param[in] style2 ウィンドウ拡張スタイル2
     * @return 結合したウィンドウ拡張スタイル
     */
    constexpr WindowExtraStyle operator | (WindowExtraStyle style1, WindowExtraStyle style2)
    {
        return static_cast<WindowExtraStyle>(static_cast<DWORD>(style1) | static_cast<DWORD>(style2));
    }

    /**
     * @brief 指定したウィンドウ拡張スタイルが含まれているか判定します。
     *
     * @param[in] style 基準となるウィンドウ拡張スタイル
     * @param[in] target 判定するウィンドウ拡張スタイル
     * @retval true 含まれている
     * @retval false 含まれていない
     */
    constexpr bool operator & (WindowExtraStyle style, WindowExtraStyle target)
    {
        return static_cast<bool>(static_cast<DWORD>(style) & static_cast<DWORD>(target));
    }

}   // namespace system
}   // namespace mirage_engine


#endif  // MIRAGE_ENGINE_SYSTEM_WINDOW_STYLE_HPP
