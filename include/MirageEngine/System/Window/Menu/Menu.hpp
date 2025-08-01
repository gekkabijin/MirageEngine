/**
 * @file Menu.hpp
 * @brief ウィンドウメニューの生成・破棄を管理します。
 */
#ifndef MIRAGE_ENGINE_SYSTEM_MENU_HPP
#define MIRAGE_ENGINE_SYSTEM_MENU_HPP


// インクルード
#include <Windows.h>

namespace mirage_engine {
namespace system {

    /**
     * @class Menu
     * @brief ウィンドウメニューの生成・破棄を管理します。
     */
    class Menu
    {
    private:

        /**
         * @brief メニューハンドル
         * 
         * @note 読み取り専用
         */
        HMENU Hmenu = nullptr;

        // ウィンドウと関連付けするためにHmenuなどにアクセスできる必要がある。
        friend class Window;

    };  // class Menu

}   // namespace system
}   // namespace mirage_engine


#endif  // MIRAGE_ENGINE_SYSTEM_MENU_HPP
