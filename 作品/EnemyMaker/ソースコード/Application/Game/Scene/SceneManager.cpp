#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager()
	: mbNeedTransition(false)
	, mbUpdateActive(true)
	, mbDrawActive(true)
{
	// 処理なし
}

SceneManager::~SceneManager()
{
	// 処理なし
}

void SceneManager::Init()
{
}

void SceneManager::Uninit()
{
	if (mCurrentScene)
	{
		mCurrentScene->UninitBase();
	}
}

void SceneManager::Update()
{
	// 遷移が必要なら次のシーンの初期化処理をする
	if (mbNeedTransition)
	{		
		if (mCurrentScene)
		{
			// 今のシーンの終了処理をする
			mCurrentScene->UninitBase();

			// 現在のシーンの解放
			mCurrentScene.reset();
		}

		// 今のシーンに代入(遷移)
		mCurrentScene = mNextScene;

		// 次のシーンの初期化処理をする
		mNextScene->InitBase();

		// 遷移が完了したのでfalseにする
		mbNeedTransition = false;
	}

	// 現在のシーンの更新処理
	if (mbUpdateActive)
	{
		mCurrentScene->UpdateBase();
		mCurrentScene->LastUpdateBase();
	}
}

void SceneManager::Draw()
{
	// 現在のシーンの描画処理
	if (mbDrawActive)
	{
		mCurrentScene->DrawBase();
	}
}
