/**
 * @file MessageEvent.cpp
 * @brief ウィンドウのメッセージイベントを管理します。
 */

// インクルード
#include "MirageEngine/System/Window/MessageEvent/MessageEvent.hpp"
#include "MirageEngine/System/Window/Window.hpp"

// usingディレクティブ
using namespace mirage_engine::system;


/**
 * @brief コンストラクタ
 *
 * @param[in] owner オーナーウィンドウ
 */
MessageEventProxy::MessageEventProxy(Window& owner)
    : Owner(owner)
{
}

/**
 * @brief イベント種別に対応するイベントハンドラリストを取得します。
 *
 * @param[in] event_type ウィンドウイベント種別
 * @return ウィンドハンドラリスト
 */
MessageEvents<const MessageEventContext&>& MessageEventProxy::operator[] (WindowEventType event_type)
{
    return Owner.Handlers[event_type];
}
