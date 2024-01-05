/**
* @file  SceneManager.h
* @brief SceneManagerクラスの定義
*/

#pragma once

//---------- INCLUDES ------------
#include "../../System/Singleton.h"
#include "Scene.h"

/**
* @class SceneManager
* @brief シーンを管理するクラス
* @detail シーンの遷移とシーンの状態を管理するクラス
*/
class SceneManager final : public Singleton<SceneManager>
{
	/**----------------------------------------------------------------------------------------------
	  * 基底クラスのSingletonクラスからコンストラクタと、デストラクタにアクセスするために必要であり
	  * クラス外から生成、破棄できないようにするためにフレンド指定する
	  ------------------------------------------------------------------------------------------------*/
	friend class Singleton<SceneManager>;

private:
	/**
	* デフォルトコンストラクタ
	*/
	SceneManager();

	/**
	* デストラクタ
	*/
	~SceneManager();

	/**
	* コピーコンストラクタ
	* コピー禁止のために delete指定
	*/
	SceneManager(const SceneManager&) = delete;

	/**
	* 代入演算子のオーバーロード
	* 代入禁止のため delete指定
	*/
	void operator=(const SceneManager&) = delete;

private:
	/** 現在実行中のシーン */
	std::shared_ptr<Scene> mCurrentScene;

	/** 次の遷移先のシーン */
	std::shared_ptr<Scene> mNextScene;

	/** シーンの遷移が必要なことを示すフラグ */
	bool mbNeedTransition;

	/** シーンの更新処理を実行するかしないか */
	bool mbUpdateActive;

	/** シーンの描画処理を実行するかしないか*/
	bool mbDrawActive;

public:
	/**
　　 * @fn Init
	 * @brief 初期化処理
　　 * @return void
　　*/
	void Init();

	/**
　　 * @fn Uninit
	 * @brief 初期化処理
　　 * @return void
　　*/
	void Uninit();

	/**
　　 * @fn Update
	 * @brief 初期化処理
　　 * @return void
　　*/
	void Update();

	/**
　　 * @fn Draw
	 * @brief 初期化処理
　　 * @return void
　　*/
	void Draw();

	/**
　　 * @fn SceneEntry
	 * @brief シーンの開始の処理
　　 * @return void
　　*/
	template<typename EntryScene>
	void SceneEntry();

	/**
　　 * @fn GetCurrentScene
	 * @brief 現在のシーンを返す
　　 * @return void
　　*/
	inline std::weak_ptr<Scene> GetCurrentScene() const;
};

//---------------- INLINES ---------------------

template<typename EntryScene>
inline void SceneManager::SceneEntry()
{
	// 次のシーンを生成する
	mNextScene = std::make_shared<EntryScene>();
	mbNeedTransition = true;
}

inline std::weak_ptr<Scene> SceneManager::GetCurrentScene() const
{
	return mCurrentScene;
}