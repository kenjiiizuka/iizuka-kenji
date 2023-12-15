/**
* @file Manager.h
* @brief Managerクラスの定義
*/

#pragma once

//--------- 前方宣言 ----------
class Application;

/**
* @class Manager
* @brief アプリケーションに必要なシステムの初期化、メインループ内の処理、終了処理をする
*/
class Manager
{	
private:
	/** 処理をするかしないかを判断するフラグ falseになればアプリケーションが終了する */
	static bool mbActive;

public:
	/**
	* @fn Initialize
	* @brief 初期化処理
	* @param Application* (_app) アプリケーション
	* @return 
	*/
	static void Initialize(Application* _app);

	/**
	* @fn Uninitialize
	* @brief 終了処理
	* @return void
	*/
	static void Uninitialize();

	/**
	* @fn Update
	* @brief 更新処理
	* @return void
	*/
	static void Update();

	/**
	* @fn Draw
	* @brief 描画処理
	* @return void
	*/
	static void Draw();

	/**
	* @fn EndMainLoop
	* @brief 処理終了関数
	* @detail アプリケーションのメインループを終了することをアプリケーションに伝える関数
	* @return void
	*/
	static inline void Inactive();

	/**
	* @fn IsActive
	* @brief アクティブかを返す
	* @return bool true アクティブ false 非アクティブ
	*/
	static inline bool IsActive() noexcept;
};

//---------- INLINES -----------


inline void Manager::Inactive()
{
	mbActive = false;
}

inline bool Manager::IsActive() noexcept
{
	return mbActive;
}
