/**
* @file LightBase.h
* @brief LightBaseクラスの定義
*/

#pragma once

//--------- INCLUDES -----------
#include "../GameObject.h"
#include <SimpleMath.h>

/**
* @class LightBase
* @brief ライトのベースクラス
*/
class LightBase : public GameObject
{
public:
	LightBase();

private:
	/** 座標 */
	DirectX::SimpleMath::Vector3 mPosition;

	/** 光の方向 */
	DirectX::SimpleMath::Vector3 mDirection;

	/** 光の色 */
	DirectX::SimpleMath::Vector4 mDiffuse;

	/** 環境光 */
	DirectX::SimpleMath::Vector4 mAmbient;

	/** この光が向いている位置 */
	DirectX::SimpleMath::Vector3 mTargetPosition;

public:
#ifdef  _DEBUG
	virtual void Update(const double _deltaTime) override;
#else 
	virtual void Update(const double _deltaTime) override {};
#endif //  _DEBUG

private:
	void CalucDirection();

public:
	/**
	 * @fn SetPosition
	 * @brief 座標のセット
	 * @param const DirectX::SimpleMath::Vector3 (_position)
	 * @return void
	*/
	inline void SetPosition(const DirectX::SimpleMath::Vector3 _position);

	/**
	 * @fn SetDirection
	 * @brief 光の方向のセット
	 * @param const DirectX::SimpleMath::Vector3 (_direction)
	 * @return void
	*/
	inline void SetDirection(const DirectX::SimpleMath::Vector3 _direction);

	/**
	 * @fn SetDiffuse
	 * @brief 光の色のセット
	 * @param const DirectX::SimpleMath::Vector4 (_diffuse)
	 * @return void
	*/
	inline void SetDiffuse(const DirectX::SimpleMath::Vector4 _diffuse);

	/**
	 * @fn SetAmbient
	 * @brief 環境光のセット
	 * @param const DirectX::SimpleMath::Vector4 (_ambient)
	 * @return void
	*/
	inline void SetAmbient(const DirectX::SimpleMath::Vector4 _ambient);

	/**
	 * @fn GetPosition
	 * @brief 座標の取得
	 * @return DirectX::SimpleMath::Vector3
	*/
	inline DirectX::SimpleMath::Vector3 GetPosition() const;

	/**
	 * @fn GetDirection
	 * @brief 光の方向の取得
	 * @return DirectX::SimpleMath::Vector3
	*/
	inline DirectX::SimpleMath::Vector3 GetDirection() const;

	/**
	 * @fn GetDiffuse
	 * @brief 光の色の取得
	 * @return DirectX::SimpleMath::Vector4
	*/
	inline DirectX::SimpleMath::Vector4 GetDiffuse() const;


	/**
	 * @fn GetAmbient
	 * @brief 環境光の取得
	 * @return DirectX::SimpleMath::Vector4
	*/
	inline DirectX::SimpleMath::Vector4 GetAmbient() const;

	/**
	 * @fn CalucLightViewMatrix
	 * @brief 光源からみたビュー行列を計算し、引数に代入する
	 * @param DirectX::SimpleMath::Matrix& (_lightMatrix) 
	 * @param DirectX::SimpleMath::Vector3 (_targetPos)
	 * @return void
	*/
	void CalucLightViewMatrix(DirectX::SimpleMath::Matrix& _lightMatrix, DirectX::SimpleMath::Vector3 _targetPos);

	/**
	 * @fn CalucLightProjectionMatrix
	 * @brief 光源からみたプロジェクション行列を計算し、引数に代入する
	 * @param DirectX::SimpleMath::Matrix& (_lightMatrix)
	 * @return void
	*/
	void CalucLightProjectionMatrix(DirectX::SimpleMath::Matrix& _lightMatrix);

};


//-------------------- INLINES --------------------

inline void LightBase::SetPosition(const DirectX::SimpleMath::Vector3 _position)
{
	mPosition = _position;
}

inline void LightBase::SetDirection(const DirectX::SimpleMath::Vector3 _direction)
{
	mDirection = _direction;
}

inline void LightBase::SetDiffuse(const DirectX::SimpleMath::Vector4 _diffuse)
{
	mDiffuse = _diffuse;
}

inline void LightBase::SetAmbient(const DirectX::SimpleMath::Vector4 _ambient)
{
	mAmbient = _ambient;
}

inline DirectX::SimpleMath::Vector3 LightBase::GetPosition() const
{
	return mPosition;
}

inline DirectX::SimpleMath::Vector3 LightBase::GetDirection() const
{
	return mDirection;
}

inline DirectX::SimpleMath::Vector4 LightBase::GetDiffuse() const
{
	return mDiffuse;
}

inline DirectX::SimpleMath::Vector4 LightBase::GetAmbient() const
{
	return mAmbient;
}


