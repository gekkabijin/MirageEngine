/**
 * @file MessageEvent.hpp
 * @brief ウィンドウのメッセージイベントを管理します。
 */
#ifndef MIRAGE_ENGINE_SYSTEM_MESSAGE_EVENT_HPP
#define MIRAGE_ENGINE_SYSTEM_MESSAGE_EVENT_HPP


// インクルード
#include <Windows.h>
#include <functional>

#include "MirageEngine/System/Window/WindowEventType.hpp"
#include "MirageEngine/Utility/CharacterCode/CharacterCode.hpp"

// 前方宣言
namespace mirage_engine {
namespace system {
    class Window;
}   // namespace system
}   // namespace mirage_engine

namespace mirage_engine {
namespace system {

    /**
     * @enum MessageEventResult
     * @brief メッセージイベント処理結果
     * 
     * @note 独自処理を行ったかを示し、デフォルトのイベント処理を後続実行するかの判断に使用します。
     */
    enum class MessageEventResult : uint32_t
    {
        /**
         * @brief 未処理状態
         * 
         * @note デフォルトのイベント処理が後続実行されます。
         */
        Unhandled = 0,

        /**
         * @brief 処理済状態
         *
         * @note デフォルトのイベント処理が後続実行されません。
         */
        Handled = 1,

    };  // enum class MessageEventResult

    /**
     * @class MessageEventContext
     * @brief メッセージイベント情報
     */
    class MessageEventContext
    {
    public:

        /**
         * @brief イベントが発生したウィンドウのハンドル
         * 
         * @note 読み取り専用
         */
        HWND Hwnd = nullptr;

        /**
         * @brief 追加情報その1
         *
         * @note
         * - イベントによって込められる内容が異なります。
         * - 読み取り専用
         */
        WPARAM PrimaryParameter = 0;

        /**
         * @brief 追加情報その2
         * 
         * @note
         * - イベントによって込められる内容が異なります。
         * - 読み取り専用
         */
        LPARAM SecondaryParameter = 0;

    };  // class MessageEventContext

    /**
     * @class MessageEvents
     * @brief ウィンドウのメッセージイベントを登録・実行します。
     */
    template<typename... HundlerFunctionArgs>
    class MessageEvents
    {
    private:

        // ハンドラ関数用定義
        using HandlerFunction = std::function<MessageEventResult(HundlerFunctionArgs...)>;

    public:

        /**
         * @brief イベントハンドラを登録します。
         * 
         * @param[in] handler イベントハンドラ
         */
        void operator += (HandlerFunction handler);

        /**
         * @brief 登録されている全てのイベントハンドラを実行します。
         * 
         * @param[in] args メッセージイベント情報
         * @return メッセージイベント処理結果
         * 
         * @note 複数イベントハンドラを実行した際の処理結果は論理和になっています。
         */
        template<typename... Args>
        MessageEventResult Invoke(Args&&... args) const;

    private:

        /**
         * @brief イベントハンドラ
         */
        std::vector<HandlerFunction> Handlers;

    };  // class MessageEvents

    /**
     * @class MessageEventProxy
     * @brief ウィンドウイベントアクセス用プロキシ
     * 
     * @note ウィンドウに紐付くイベントハンドラを取得します。
     */
    class MessageEventProxy
    {
    public:

        /**
         * @brief コンストラクタ
         * 
         * @param[in] owner オーナーウィンドウ
         */
        explicit MessageEventProxy(Window& owner);

        /**
         * @brief イベント種別に対応するイベントハンドラリストを取得します。
         * 
         * @param[in] event_type ウィンドウイベント種別
         * @return イベントハンドラリスト
         */
        MessageEvents<const MessageEventContext&>& operator[] (WindowEventType event_type);

    private:

        /**
         * @brief オーナーウィンドウ
         */
        Window& Owner;

    };  // class MessageEventProxy

}   // namespace system
}   // namespace mirage_engine

// インクルード
#include "MirageEngine/System/Window/MessageEvent/Detail/MessageEventDetail.hpp"


#endif  // MIRAGE_ENGINE_SYSTEM_MESSAGE_EVENT_HPP
