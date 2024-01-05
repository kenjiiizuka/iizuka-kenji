/**
* @file Application.h
* @brief Applicationクラス
*/

#pragma once

//---------- INCLUDES -----------
#include <Windows.h>
#include <cstdint>

/**
* @class Application
* @brief ウィンドウの作成、メインループ処理をしているクラス
* @detail エントリポイントのみで必ず作成してください。
*/
class Application
{
public:
    /**
    * コンストラクタ
    *
    * @param const float (_width) 画面の横幅
    * @param const float (_height) 画面の縦幅
    */
    Application(const float _width, const float _height);

    /**
    * デストラクタ
    */
    ~Application();

private:
    /** インスタンスハンドル */
    HINSTANCE   mHInstance;

    /** ウィンドウハンドル */
    HWND        mhWnd;

    /** ウィンドウの横幅 */
    float    mWidth;

    /** ウィンドウの縦幅 */
    float    mHeight;

public:
    /**
    * @fn Run
    * @brief アプリケーション実行関数
    * @detail アプリケーションの初期化をし、メインループ、終了処理を行う
    */
    void Run();

private:
    /**
    * @fn Initialize
    * @brief アプリケーション初期化処理
    * @return bool true 初期化成功 false 失敗
    */
    bool Initialize();

    /**
    * @fn Uninitialize
    * @brief アプリケーション終了処理
    * @return void
    */
    void Uninitialize();

    /**
    * @fn WindowInitialize
    * @brief ウィンドウの初期化処理
    * @return bool true 成功 false 失敗
    */
    bool WindowInitialize();

    /**
    * @fn WindowUninitialize
    * @brief ウィンドウ終了処理
    * @return void
    */
    void WindowUninitialize();

    /**
    * @fn MainLoop
    * @brief メインループ処理
    * @return void
    */
    void MainLoop();

    /**
    * @fn WndProc
    * @brief ウィンドウプロシージャ関数
    * @param HWND   (_hWnd)
    * @param UINT   (_msg)
    * @param WPARAM (_wp)
    * @param LPARAM (_lp)
    * @return LRESULT
    */
    static LRESULT CALLBACK WndProc(HWND _hWnd, UINT _msg, WPARAM _wp, LPARAM _lp);   // ウィンドウプロシージャ

    /**
    * @fn CtrlHandler
    * @brief ConsoleWindowのHandler関数
    * @detail コンソールから閉じたらメモリリークすることを防ぐためにハンドラーを作り対策している
    * @param DWORD _ctrlType
    * @return  BOOL
    */
    static BOOL WINAPI CtrlHandler(DWORD _ctrlType);                               // ConsoleWindowのHandler関数

public:
    /**
    * @fn GetWidth
    * @brief 画面の横幅を返す
    * @return uint32_t 画面の横幅
    */
    inline float GetWidth() const noexcept;

    /**
    * @fn GetHeight
    * @brief 画面の縦幅を返す
    * @return uint32_t 画面の縦幅
    */
    inline float GetHeight() const noexcept;

    /**
    * @fn GetWindow
    * @brief ウィンドウハンドルを返す
    * @return HWND&
    */
    inline HWND& GetWindow() noexcept;
};

//-------- INLINES -----------

inline float Application::GetWidth() const noexcept
{
    return mWidth;
}

inline float Application::GetHeight() const noexcept
{
    return mHeight;
}

inline HWND& Application::GetWindow() noexcept
{
    return mhWnd;
}
