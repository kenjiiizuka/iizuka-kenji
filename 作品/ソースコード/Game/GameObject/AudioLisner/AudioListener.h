#pragma once

#include <Windows.h>
#include <x3daudio.h>
#include "../GameObject.h"



/**
* @class AudioListener
* @brief オーディオリスナー
* @detail 3D空間上で音を聞くオブジェクト
*/
class AudioListener : public GameObject
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	AudioListener();

	/**
	* デストラクタ
	*/
	~AudioListener();

private:
	/** リスナーにするオブジェクト */
	std::weak_ptr<GameObject> mListenerObject;

	/** リスナーオブジェクトのトランスフォーム */
	std::weak_ptr<TransformComponent> mListenerTransformComponent;

	/** リスナ- */
	X3DAUDIO_LISTENER mListener;

public:
	/**
	* @fn Init
	* @brief 初期化処理
	* @return void
	*/
	void Init() override;

	/**
	* @fn Update
	* @brief 更新処理
	* @param const double _deltaTime
	* @return void
	*/
	void Update(const double _deltaTime) override;

	/**
	* @fn GetListener
	* @brief リスナーを返す
	* @return X3DAUDIO_LISTENER
	*/
	inline X3DAUDIO_LISTENER GetListener() const noexcept;

	/**
	* @fn SetListenerObject
	* @brief リスナーオブジェクトをセットする
	* @param std::shared_ptr<GameObject> (_listenerObject)
	* @return void
	*/
	void SwitchListenerObject(std::shared_ptr<GameObject> _listenerObject) noexcept;

};

//---------- INLINES ---------

inline X3DAUDIO_LISTENER AudioListener::GetListener() const noexcept
{
	return mListener;
}
