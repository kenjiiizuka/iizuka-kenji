/**
* @file AudioComponent.h
* @brief AudioComponentクラスの定義
*/

#pragma once

//--------- INCLUDES ----------
#include "../Component.h"
#include <string>
#include <SimpleMath.h>

//--------- 前方宣言 --------
class AudioClip;


/**
* @class AudioComponent
* @brief AudioClipを持ち、Audioの2D再生、3D再生をしやすいようにしたクラス
*/
class AudioComponent : public Component
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	AudioComponent();

	/**
	* デストラクタ
	*/
	~AudioComponent();

private:
	/** オーディオクリップ */
	std::shared_ptr<AudioClip> mAudioClip;

	/** フェード再生するか */
	bool mbIsFadeIn;

	/** 音量 */
	float mVolume;

	/** フェードイン開始してからの経過時間 */
	double mFadeInElapsedTime;

	/** フェードインにかける時間 */
	double mFadeInTime;

	/** フェードアウトをするか */
	bool mbIsFadeOut;

	/** フェードアウトにかける時間 */
	double mFadeOutTime;

	/** フェードアウト開始してからの経過時間 */
	double mFadeOutElapsedTime;

public:
	/**
	* @fn Init
	* @brief 初期化処理
	* @param std::string_view (_filePath)
	* @param const bool       (_loop)
	* @detail AudioClipの生成をする
	* @return void
	*/
	void Init(std::string_view _filePath, const bool _loop = false);

	/**
	* @fn Update
	* @brief 更新処理
	* @param const double (_deltaTime)
	* @return void
	*/
	void Update(const double _deltaTime) override;

private:
	/**
	* @fn  FadeIn
	* @brief フェードイン処理
	* @param const double (_deltaTime)
	* @return void 
	*/
	void FadeIn(const double _deltaTime);

	/**
	* @fn  FadeOut
	* @brief フェードアウト処理
	* @param const double (_deltaTime)
	* @return void
	*/
	void FadeOut(const double _deltaTime);

public:
	/**
	* @fn PlaySound2D
	* @brief AudioClipの2D再生をする
	* @param const float  (_volume)     音量
	* @param const bool   (_isFade)     フェード再生するか
	* @param const double (_fadeInTime) フェードインにかける時間
	* @return void
	*/
	void PlaySound2D(const float _volume = 1.0f, const bool _isFade = false, const double _fadeInTime = 10.0f);

	/**
	* @fn PlaySound3D
	* @brief AudioClipの3Dサウンドを再生する
	* @param const DirectX::SimpleMath::Vector3 (_position)
	* @param const DirectX::SimpleMath::Vector3 (_rotation)
	* @param const const float                  (_volume)
	* @return void
	*/
	void PlaySound3D(const DirectX::SimpleMath::Vector3 _position, const DirectX::SimpleMath::Vector3 _rotation, const float _volume = 1.0f);

	/**
	* @fn Stop
	* @brief 再生を停止する処理
	* @param const bool (_isFadeOut)
	* @param cont double (_fadeOutTime)
	* @return void
	*/
	void Stop(const bool _isFadeOut = false, const double _fadeOutTime = 2.0f);
};

