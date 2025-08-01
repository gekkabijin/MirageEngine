/**
 * @file MessageEventDetail.hpp
 * @brief ウィンドウのメッセージイベントを管理します。
 */
#ifndef MIRAGE_ENGINE_SYSTEM_MESSAGE_EVENT_DETAIL_HPP
#define MIRAGE_ENGINE_SYSTEM_MESSAGE_EVENT_DETAIL_HPP


namespace mirage_engine {
namespace system {

/**
 * @brief イベントハンドラを登録します。
 *
 * @param[in] handler イベントハンドラ
 */
template<typename... HundlerFunctionArgs>
void MessageEvents<HundlerFunctionArgs...>::operator += (HandlerFunction handler)
{
    Handlers.emplace_back(std::move(handler));
}

/**
* @brief 登録されている全てのイベントハンドラを実行します。
*
* @param[in] args メッセージイベント情報
* @return メッセージイベント処理結果
*
* @note 複数イベントハンドラを実行した際の処理結果は論理和になっています。
*/
template<typename... HundlerFunctionArgs>
template<typename... Args>
MessageEventResult MessageEvents<HundlerFunctionArgs...>::Invoke(Args&&... args) const
{
    uint32_t result = 0;

    for (const auto& handler : Handlers)
    {
        result |= static_cast<uint32_t>(handler(std::forward<Args>(args)...));
    }

    return static_cast<MessageEventResult>(result);
}

}   // namespace system
}   // namespace mirage_engine


#endif  // MIRAGE_ENGINE_SYSTEM_MESSAGE_EVENT_DETAIL_HPP
