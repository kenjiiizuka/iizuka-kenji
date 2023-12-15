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
	* @fn PlaySound2D
	* @brief AudioClipの2D再生をする
	* @param const float (_volume)
	* @return void
	*/
	void PlaySound2D(const float _volume = 1.0f);

	/**
	* @fn PlaySound3D
	* @brief AudioClipの3Dサウンドを再生する
	* @param const DirectX::SimpleMath::Vector3 (_position)
	* @param const DirectX::SimpleMath::Vector3 (_rotation)
	* @param const const float                  (_volume)
	* @return void
	*/
	void PlaySound3D(const DirectX::SimpleMath::Vector3 _position, const DirectX::SimpleMath::Vector3 _rotation, const float _volume = 1.0f);
};

