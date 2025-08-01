/**
 * @file Window.cpp
 * @brief ウィンドウの生成・破棄・表示を管理します。
 */

// インクルード
#include <type_traits>
#include <Windows.h>
#include "MirageEngine/System/Window/Window.hpp"
#include "MirageEngine/System/Window/Menu/Menu.hpp"

// usingディレクティブ
using namespace std;
using namespace mirage_engine::utility;
using namespace mirage_engine::system;

// const定義
static tstring MirageEngineWindowsInstanceKey = _T("MirageEngineWindowsInstanceKey");


/**
 * @brief コンストラクタ
 */
Window::Window()
    : Hwnd(nullptr), Event(*this)
{
}

/**
 * @brief ウィンドウを作成します。
 *
 * @param[in] info ウィンドウ情報
 * @return 作成結果
 *
 * @attention 既にウィンドウが作成済の場合は再作成しません。
 * @note ウィンドウクラスの登録も内部の処理で行います。
 */
[[nodiscard]]
MirageEngineResultCode Window::Create(const WindowInfo& info)
{
    // 既にウィンドウを作成済の場合は作成しない
    if (IsCreated())
    {
        return MirageEngineResultCode::FailedToCreateWindowAlreadyExists;
    }

    // インスタンスハンドル
    HINSTANCE hinstance = ::GetModuleHandle(nullptr);

    // ウィンドウクラスを登録する
    MirageEngineResultCode register_result = RegisterWindowClass(hinstance, info);
    if (register_result != MirageEngineResultCode::Successful)
    {
        return register_result;
    }

    // ウィンドウの幅、高さ
    int32_t width = info.Width;
    int32_t height = info.Height;

    // 親ウィンドウ
    HWND parent = info.Parent ? info.Parent->Hwnd : nullptr;
    // メニュー
    HMENU menu = info.Menu ? info.Menu->Hmenu : nullptr;
    // ウィンドウスタイル
    underlying_type_t<WindowStyle> style = static_cast<underlying_type_t<WindowStyle>>(info.Style);
    // ウィンドウ拡張スタイル
    underlying_type_t<WindowExtraStyle> extra_style = static_cast<underlying_type_t<WindowExtraStyle>>(info.ExtraStyle);

    // クライアント領域のサイズを指定している場合は、クライアント領域のサイズからウィンドウのサイズを求める
    if (info.ClientWidth > 0 && info.ClientHeight > 0)
    {
        RECT rect = { 0, 0, static_cast<LONG>(info.ClientWidth), static_cast<LONG>(info.ClientHeight) };

        ::AdjustWindowRectEx(&rect, style, menu != nullptr, extra_style);

        width = rect.right - rect.left;
        height = rect.bottom - rect.top;

        // スクロールバーを追加する場合は、スクロールバーのサイズも考慮する
        if (info.Style & WindowStyle::HorizontalScroll) { height += ::GetSystemMetrics(SM_CYVSCROLL); }
        if (info.Style & WindowStyle::VerticalScroll) { width += ::GetSystemMetrics(SM_CYHSCROLL); }
    }

    // ウィンドウの座標
    int32_t x = info.X;
    int32_t y = info.Y;

    // ウィンドウの初期位置を画面の真ん中にする
    if (info.IsCentering)
    {
        x = (::GetSystemMetrics(SM_CXSCREEN) - width) >> 1;
        y = (::GetSystemMetrics(SM_CYSCREEN) - height) >> 1;
    }

    // ウィンドウを作成する
    Hwnd = ::CreateWindowEx(extra_style, info.ClassName.c_str(), info.CaptionName.c_str(), style, x, y, width, height, parent, menu, hinstance, this);
    if (Hwnd == nullptr)
    {
        return MirageEngineResultCode::FailedToCreateWindow;
    }

    // スクロールバーは使用不可にしておく
    if (info.Style & (WindowStyle::HorizontalScroll | WindowStyle::VerticalScroll))
    {
        ::EnableScrollBar(Hwnd, SB_BOTH, ESB_DISABLE_BOTH);
    }

    return MirageEngineResultCode::Successful;
}

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
[[nodiscard]]
MirageEngineResultCode Window::Create(tstring caption_name, uint32_t client_width, uint32_t client_height)
{
    WindowInfo window_info;

    window_info.CaptionName = caption_name;
    window_info.ClientWidth = client_width;
    window_info.ClientHeight = client_height;

    return Create(window_info);
}

/**
 * @brief ウィンドウを破棄します。
 */
void Window::Destroy()
{
    if (Hwnd != nullptr)
    {
        if (::DestroyWindow(Hwnd))
        {
            Hwnd = nullptr;
        }
    }
}

/**
 * @brief ウィンドウが作成済か確認します。
 *
 * @retval true ウィンドウが作成済です。
 * @retval false ウィンドウが未作成です。
 */
[[nodiscard]]
bool Window::IsCreated() const
{
    if (::IsWindow(Hwnd))
    {
        // ウィンドウハンドルに古い値が残っている可能性があるため本当に自分自身が所有するウィンドウか確認する
        // WM_CREATE内でSetPropを行いウィンドウハンドルと自分自身のアドレスを紐付けているのでそれで確認
        Window* window = reinterpret_cast<Window*>(GetProp(Hwnd, reinterpret_cast<TCHAR*>(InstanceKeyAtom)));
        if (window && window == this)
        {
            return true;
        }
    }

    return false;
}

/**
 * @brief 受信したメッセージを処理します。
 *
 * @param[in] hwnd ウィンドウハンドル
 * @param[in] msg メッセージの種類
 * @param[in] wparam メッセージの追加情報
 * @param[in] lparam メッセージの追加情報
 * @return メッセージの処理結果
 */
LRESULT CALLBACK Window::Procedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    uint32_t handled = 0;

    // thisポインタを取得する
    Window* window = reinterpret_cast<Window*>(::GetProp(hwnd, reinterpret_cast<TCHAR*>(InstanceKeyAtom)));

    if (window != nullptr)
    {
        WindowEventType event_type = static_cast<WindowEventType>(msg);

        if (window->Handlers.contains(event_type))
        {
            // 登録したイベントを処理する
            MessageEventContext context = { .Hwnd = hwnd, .PrimaryParameter = wparam, .SecondaryParameter = lparam };

            handled |= static_cast<uint32_t>(window->Handlers[event_type].Invoke(std::forward<MessageEventContext&>(context)));
        }
    }

    switch (msg)
    {
        case WM_CREATE:
        {
            // 最初の1回目のみインスタンスキー用のアトムを作成する
            // （2回目以降は同じアトムが作成されるため処理は不要）
            ++InstanceKeyRefCount;
            if (InstanceKeyRefCount == 1)
            {
                InstanceKeyAtom = ::GlobalAddAtom(MirageEngineWindowsInstanceKey.c_str());
            }

            // ウィンドウ作成時にthisポインタを登録する
            CREATESTRUCT* parameter = reinterpret_cast<CREATESTRUCT*>(lparam);
            Window* window = reinterpret_cast<Window*>(parameter->lpCreateParams);

            if (!::SetProp(hwnd, reinterpret_cast<TCHAR*>(InstanceKeyAtom), window))
            {
            }

            handled |= 1;

            break;
        }
        case WM_DESTROY:
        {
            // ウィンドウ破棄時にthisポインタを解除する
            ::RemoveProp(hwnd, reinterpret_cast<TCHAR*>(InstanceKeyAtom));

            if (window != nullptr)
            {

                window->Handlers.clear();
                window->Hwnd = nullptr;
            }

            // インスタンスキー用のアトムの参照が0になった場合は削除する
            --InstanceKeyRefCount;
            if (InstanceKeyRefCount == 0)
            {
                ::GlobalDeleteAtom(InstanceKeyAtom);
                InstanceKeyAtom = 0;
            }

            handled |= 1;

            break;
        }
    }

    // 何かイベントを処理した場合はデフォルトの処理はしない
    if (handled != 0) { return 0; }

    return ::DefWindowProc(hwnd, msg, wparam, lparam);
}

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
[[nodiscard]]
MirageEngineResultCode Window::RegisterWindowClass(HINSTANCE hInstance, const WindowInfo& info)
{
    // ウィンドウクラス情報
    WNDCLASSEX wndclass = { sizeof(WNDCLASSEX) };

    if (!::GetClassInfoEx(hInstance, info.ClassName.c_str(), &wndclass))
    {
        // ウィンドウクラスが未登録の場合は登録する

        UINT style = CS_HREDRAW | CS_VREDRAW;
        if (info.IsDoubleClick) { style |= CS_DBLCLKS; }

        wndclass.cbClsExtra = 0;
        wndclass.cbWndExtra = 0;
        wndclass.hbrBackground = static_cast<HBRUSH>(::GetStockObject(GRAY_BRUSH));
        wndclass.hInstance = hInstance;
        wndclass.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
        wndclass.hIcon = ::LoadIcon(nullptr, IDI_APPLICATION);
        wndclass.hIconSm = wndclass.hIcon;
        wndclass.lpfnWndProc = reinterpret_cast<WNDPROC>(Procedure);
        wndclass.lpszClassName = info.ClassName.c_str();
        wndclass.lpszMenuName = nullptr;
        wndclass.style = style;

        if (!::RegisterClassEx(&wndclass))
        {
            return MirageEngineResultCode::FailedToRegisterWindowClass;
        }
    }
    else
    {
        // 登録済の場合はオプションで処理を切り替える

        if (!info.AllowDuplicateClass)
        {
            // 重複を許可していないので登録失敗にする
            return MirageEngineResultCode::FailedToRegisterWindowClassAlreadyExists;
        }

        if (wndclass.lpfnWndProc != reinterpret_cast<WNDPROC>(Procedure))
        {
            // プロシージャが異なると意図した動作ではなくなる可能性が高いため登録失敗にする
            return MirageEngineResultCode::ErrorWindowProcedureConflict;
        }
    }

    return MirageEngineResultCode::Successful;
}

/**
 * @brief ウィンドウを表示します。
 */
void Window::Show() const
{
    ShowWindow(Hwnd, SW_SHOW);
}
