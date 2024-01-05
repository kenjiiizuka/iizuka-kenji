/**
* @file TitleScene.h
* @brief TitleSceneクラスの定義
*/

#pragma once

//-------- INCLUDES -----------
#include "../Scene.h"
#include <vector>

//-------- 前方宣言 --------
class Fade;
class CommandSelector;
class StaticMeshObject;
class AudioComponent;

/**
* @class TitleScene
* @brief タイトルシーン
*/
class TitleScene : public Scene
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	TitleScene();

	/**
	* デストラクタ
	*/
	~TitleScene();

	/**
	* @fn Initialize
	* @brief 初期化処理
	* @detail タイトルに必要なオブジェクトを生成しています
	* @return void
	*/
	void Initialize() override;

	/**
	* @fn Update
	* @brief 更新処理
	* @return void
	*/
	void Update() override;

private:
	/** フェード用のオブジェクト */
	std::weak_ptr<Fade> mFade;

	/** コマンドセレクター */
	std::weak_ptr<CommandSelector> mCommandSelector;

	/** シーン遷移の入力があったか */
	bool mbTransitionScene;

	/** 終了コマンドが選択されたか */
	bool mbEnd;

	/** フェードの速度 */
	float mFadeSpeed;

	/** 小物オブジェクト */
	std::vector<std::weak_ptr<StaticMeshObject>> mProps;

	/** BGM再生用コンポーネント */
	std::weak_ptr<AudioComponent> mBGM;

};

