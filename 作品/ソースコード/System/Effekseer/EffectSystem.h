/**
* @file EffectSystem.h
* @brief EffectSystemクラスの定義
*/
#pragma once

//--------- INCLUDES ---------
#include "../Singleton.h"
#include <EffekseerRendererDX11.h>
#include <Effekseer.h>
#include <SimpleMath.h>
#include "../../System/AssetSystem/Effect/EffekseerEffect.h"


/**
* @class EffectSystem
* @brief エフェクトシステムクラス
* @detail Effekseerを使用し、エフェクトのシステムを提供する
*         Effekseerの初期化、エフェクトの再生をする
*/
class EffectSystem : public Singleton<EffectSystem>
{
	/**-----------------------------------------------------------------------------
	* Singleton<EffectSystem>からのみ生成、破棄ができるようにするためにフレンド指定
	------------------------------------------------------------------------------ */
	friend class Singleton<EffectSystem>;

private:
	/**
	* デフォルトコンストラクタ
	*/
	EffectSystem() {};

	/**
	* コピーコンストラクタ
	*/
	EffectSystem(const EffectSystem&) = delete;

	/**
	* デストラクタ
	*/
	~EffectSystem() {};

	/**
	* 代入演算子のオーバーロード
	*/
	void operator=(const EffectSystem&) = delete;

private:
	/** エフェクシアレンダラー */
	::EffekseerRendererDX11::RendererRef mEffekseerRenderer;

	/** エフェクトマネージャー */
	::Effekseer::ManagerRef mEffekseerManager;

public:
	/**
	* @fn 初期化処理
	* @brief Effekseerを初期化する
	* @return void
	*/
	void Initialize();

	/**
	* @fn Draw
	* @brief 描画処理
	* @return void
	*/
	void Draw();

private:
	/**
	* @fn ConvertEffekseerMatrix
	* @brief DirectX::SimpleMath::MatrixをEffekseer::Matrix44に変換する
	* @param const DirectX::SimpleMath::Matrix& (_matrix)
	* @return Effekseer::Matrix44
	*/
	Effekseer::Matrix44 ConvertEffekseerMatrix(const DirectX::SimpleMath::Matrix& _matrix);

public:
	/**
	* @fn GetEffekseerManager
	* @brief エフェクシアマネージャーを返す
	* @return Effekseer::ManagerRef
	*/
	inline Effekseer::ManagerRef GetEffekseerManager() const noexcept;
};

//------------ INLINES ------------

inline Effekseer::ManagerRef EffectSystem::GetEffekseerManager() const noexcept
{
	return mEffekseerManager;
}
