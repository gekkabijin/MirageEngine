/**
 * @file Window.hpp
 * @brief ウィンドウの生成・破棄・表示を管理します。
 */
#ifndef MIRAGE_ENGINE_SYSTEM_WINDOW_HPP
#define MIRAGE_ENGINE_SYSTEM_WINDOW_HPP


// インクルード
#include "MirageEngine/System/Inline/Inline.hpp"
#include "MirageEngine/System/ResultCode/ResultCode.hpp"
#include "MirageEngine/System/Window/MessageEvent/MessageEvent.hpp"
#include "MirageEngine/System/Window/WindowStyle.hpp"
#include "MirageEngine/Utility/CharacterCode/CharacterCode.hpp"

// 前方宣言
namespace mirage_engine {
namespace system {
    class Menu;
}   // namespace system
}   // namespace mirage_engine

namespace mirage_engine {
namespace system {

    /**
     * @class WindowInfo
     * @brief ウィンドウの生成に必要な情報を管理します。
     */
    class WindowInfo
    {
    public:

        /**
         * @brief ウィンドウのタイトルバーに表示するテキスト
         */
        utility::tstring CaptionName = _T("");

        /**
         * @brief ウィンドウクラス名
         */
        utility::tstring ClassName = _T("ApplicationWindow");

        /**
         * @brief 親ウィンドウ
         */
        Window* Parent = nullptr;

        /**
         * @brief メニュー
         */
        Menu* Menu = nullptr;

        /**
         * @brief ウィンドウスタイル
         */
        WindowStyle Style = WindowStyle::Default;

        /**
         * @brief 拡張ウィンドウスタイル
         */
        WindowExtraStyle ExtraStyle = WindowExtraStyle::None;

        /**
         * @brief ウィンドウ左上のX座標
         */
        int32_t X = 0;

        /**
         * @brief ウィンドウ左上のY座標
         */
        int32_t Y = 0;

        /**
         * @brief ウィンドウの幅
         *
         * @attention クライアント領域の幅と高さの両方が0の場合はこの値を使用します。
         */
        uint32_t Width = 0;

        /**
         * @brief ウィンドウの高さ
         *
         * @attention クライアント領域の幅と高さの両方が0の場合はこの値を使用します。
         */
        uint32_t Height = 0;

        /**
         * @brief クライアント領域の幅
         * 
         * @attention クライアント領域の幅と高さの両方が0でない場合はこの値を使用します。
         */
        uint32_t ClientWidth = 0;

        /**
         * @brief クライアント領域の高さ
         *
         * @attention クライアント領域の幅と高さの両方が0でない場合はこの値を使用します。
         */
        uint32_t ClientHeight = 0;

        /**
         * @brief ダブルクリックを認識するか
         */
        bool IsDoubleClick = true;

        /**
         * @brief ウィンドウを画面中央に表示するか
         */
        bool IsCentering = true;

        /**
         * @brief ウィンドウクラス名の重複を許可するか
         * 
         * @attention 
         * - 同一のウィンドウクラス名が登録済で重複を許可した場合は新しい設定を作成せずに登録済の情報を使用します。
         */
        bool AllowDuplicateClass = true;

    };  // class WindowInfo

    /**
     * @class Window
     * @brief ウィンドウの生成・破棄・表示を管理します。
     */
    class Window
    {
    public:

        /**
         * @brief コンストラクタ
         */
        Window();

        /**
         * @brief ウィンドウを作成します。
         *
         * @param[in] info ウィンドウ情報
         * @return 作成結果
         *
         * @attention 既にウィンドウが作成済の場合は再作成しません。
         * @note ウィンドウクラスの登録も内部の処理で行います。
         */
        [[nodiscard]] MirageEngineResultCode Create(const WindowInfo& info);

        /**
         * @brief ウィンドウを作成します。
         *
         * @param[in] caption_name ウィンドウのタイトルバーに表示するテキスト
         * @param[in] client_width クライアント領域の幅
         * @param[in] client_height クライアント領域の高さ
         * @return 作成結果
         *
         * @attention 既にウィンドウが作成済の場合は再作成しません。
         * @note ウィンドウクラスの登録も内部の処理で行います。
         */
        [[nodiscard]] MirageEngineResultCode Create(utility::tstring caption_name, uint32_t client_width, uint32_t client_height);

        /**
         * @brief ウィンドウを破棄します。
         */
        void Destroy();

        /**
         * @brief ウィンドウが作成済か確認します。
         *
         * @retval true ウィンドウが作成済です。
         * @retval false ウィンドウが未作成です。
         */
        [[nodiscard]] bool IsCreated() const;

        /**
         * @brief ウィンドウを表示します。
         */
        void Show() const;


    private:

        /**
         * @brief 受信したメッセージを処理します。
         * 
         * @param[in] hwnd ウィンドウハンドル
         * @param[in] msg メッセージの種類
         * @param[in] wparam メッセージの追加情報
         * @param[in] lparam メッセージの追加情報
         * @return メッセージの処理結果
         */
        static LRESULT CALLBACK Procedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

        /**
         * @brief ウィンドウクラスを登録します。
         *
         * @param[in] hInstance インスタンスハンドル
         * @param[in] info ウィンドウ情報
         * @return 登録結果
         *
         * @attention
         * - ウィンドウクラスが登録済の場合は新しい設定を作成せずに登録済の情報を使用します。
         * - ウィンドウクラス名の重複を許可しない場合は登録に失敗します。
         * - ウィンドウクラス名の重複を許可していてもプロシージャが異なる場合は登録に失敗します。
         */
        [[nodiscard]] static MirageEngineResultCode RegisterWindowClass(HINSTANCE hinstance, const WindowInfo& info);

        /**
         * @brief インスタンスキー用の参照カウンタ
         * 
         * @note SetProp、GetProp、RemovePropで使用する参照カウンタ。
         */
        inline static std::atomic<int> InstanceKeyRefCount;

        /**
         * @brief インスタンスキー用のアトム
         *
         * @note SetProp、GetProp、RemovePropで使用するアトム。
         */
        inline static ATOM InstanceKeyAtom = 0;

    protected:

        /**
         * @brief ウィンドウハンドル
         * 
         * @note 読み取り専用
         */
        HWND Hwnd = nullptr;

        /**
         * @brief イベントハンドラ
         */
        std::unordered_map<WindowEventType, MessageEvents<const MessageEventContext&>> Handlers;

    public:

        /**
         * @brief ウィンドウイベント登録用プロキシ
         * 
         * @note Event += 形式でイベントハンドラを追加できます。
         */
        MessageEventProxy Event;

        // ウィンドウイベントを登録するためにHandlersなどにアクセスできる必要がある。
        friend MessageEventProxy;

    };  // class Window

}   // namespace system
}   // namespace mirage_engine


#endif  // MIRAGE_ENGINE_SYSTEM_WINDOW_HPP
