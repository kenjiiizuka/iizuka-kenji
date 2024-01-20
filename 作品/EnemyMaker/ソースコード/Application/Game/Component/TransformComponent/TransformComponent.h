/**
* @file  TransformComponent.h
* @brief トランスフォームコンポーネントクラス
*/

#pragma once

//---------- INCLUDES -----------
#include "../Component.h"
#include <SimpleMath.h>
#include <DirectXMath.h>
#include "../../../Utility/Debug.h"
#include "Transform.h"

/**
* @class TransformComponent
* @brief オーナーのトランスフォームを管理する
*/
class TransformComponent : public Component
{
public:
	/**
   　* 値の初期化 
    */
	TransformComponent();

private:
	/** トランスフォーム */
	Transform mTransform;

	/** ワールド行列 */
	DirectX::SimpleMath::Matrix mWorldMatrix;

	/** 回転行列 */
	DirectX::SimpleMath::Matrix mRotationMatrix;

	/** 平行移動行列 */
	DirectX::SimpleMath::Matrix mTranslationMatrix;

	/** スケール行列 */
	DirectX::SimpleMath::Matrix mScaleMatrix;

	/** 親の位置の影響を受けるか */
	bool bPositionParentInfluence;

	/** 親の回転の影響を受けるか */
	bool bRotationParentInfluence;

	/** 親のスケールの影響を受けるか */
	bool bScaleParentInfluence;

public:
	/**
　　 * @fn　SetPositionParentInfluence
　　 * @brief 親の位置の影響を受けるかのセッター
     * @param bool (_influence) true : 影響を受ける false : 影響を受けない 
　　 * @return void
　　*/
	inline void SetPositionParentInfluence(bool _influence);

	/**
　　 * @fn　SetRotationParentInfluence
　　 * @brief 親の回転の影響を受けるかのセッター
	 * @param bool (_influence) true : 影響を受ける false : 影響を受けない
　　 * @return void
　　*/
	inline void SetRotationParentInfluence(bool _influence);

	/**
　　 * @fn　SetScaleParentInfluence
　　 * @brief 親のスケールの影響を受けるかのセッター
	 * @param bool (_influence) true : 影響を受ける false : 影響を受けない
　　 * @return void
　　*/
	inline void SetScaleParentInfluence(bool _influence);

	/**
　　 * @fn　SetParentTransformInfluence
　　 * @brief 親のトランスフォームの影響を受けるかのセッター
	 * @param bool (_influence) true : 影響を受ける false : 影響を受けない
　　 * @return void
　　*/
	inline void SetParentTransformInfluence(bool _influence);

	/**
　　 * @fn　GetTranslationMatrix
　　 * @brief 平行移動行列のゲッター
　　 * @return DirectX::SimpleMath::Matrix 平行移動行列
　　*/
	inline DirectX::SimpleMath::Matrix GetTranslationMatrix();

	/**
　　 * @fn　GetScaleMatrix
　　 * @brief スケール行列のゲッター
　　 * @return DirectX::SimpleMath::Matrix スケール行列
　　*/
	inline DirectX::SimpleMath::Matrix GetScaleMatrix();

	/**
	* @fn GetPosition
	* @brief 座標を返す
	* @return DirectX::SimpleMath::Vector3
	*/
	inline DirectX::SimpleMath::Vector3 GetPosition() const;

	/**
	* @fn GetRotation
	* @brief 回転を返す
	* @return DirectX::SimpleMath::Vector3
	*/
	inline DirectX::SimpleMath::Vector3 GetRotation() const;

	/**
	* @fn GetScale
	* @brief スケールを返す
	* @return DirectX::SimpleMath::Vector3
	*/
	inline DirectX::SimpleMath::Vector3 GetScale() const ;
	
	/**
	* @fn GetTransform
	* @brief トランスフォームを返す
	* @return void
	*/
	inline Transform GetTransform() const;

	/**
	* @fn SetPosition
	* @brief 座標のセッター
	* @param  const DirectX::SimpleMath::Vector3 (_pos)
	* @return void
	*/
	inline void SetPosition(const DirectX::SimpleMath::Vector3 _pos);
	
	/**
	* @fn SetScale
	* @brief 座標のスケール
	* @param  const DirectX::SimpleMath::Vector3 (_scale)
	* @return void
	*/
	inline void SetScale(const DirectX::SimpleMath::Vector3 _scale);

	/**
	* @fn SetScale
	* @brief 座標のスケール
	* @param  const float (_scale)
	* @return void
	*/
	inline void SetScale(const float _scale);
		
	/**
	* @fn SetRotation
	* @brief 回転のセッター
	* @param const DirectX::SimpleMath::Vector3 (_rotation)
	* @return void
	*/
	inline void SetRotation(const DirectX::SimpleMath::Vector3 _rotation);

	/**
	* @fn AddRotation
	* @brief 回転の追加
	* @param const DirectX::SimpleMath::Vector3 (_rotation)
	* @return void
	*/
	inline void AddRotation(const DirectX::SimpleMath::Vector3 _rotation);

	/**
	* @fn AddPosition
	* @brief 座標加算
	* @param const DirectX::SimpleMath::Vector3 (_vector)
	* @return void
	*/
	inline void AddPosition(const DirectX::SimpleMath::Vector3 _vector);
	
	/**
	* @fn CalucWorldMatrix
	* @brief ワールド行列の計算処理
	* @param DirectX::SimpleMath::Matrix (_parent) 親行列
	* @return DirectX::SimpleMath::Matrix
	*/
	DirectX::SimpleMath::Matrix CalucWorldMatrix(DirectX::SimpleMath::Matrix _parent);
	
	/**
　　 * @fn　GetWorldMatrix
　　 * @brief ワールド行列のゲッター
　　 * @return DirectX::SimpleMath::Matrix ワールド行列
　　*/
	inline DirectX::SimpleMath::Matrix GetWorldMatrix();

	/**
　　 * @fn　SetWorldMatrix
　　 * @brief ワールド行列のセッター
　　 * @param DirectX::SimpleMath::Matrix ワールド行列
    　* @return void
　　*/
	void SetWorldMatrix(DirectX::SimpleMath::Matrix _worldMatrix);

	/**
　　 * @fn　SetTransform
　　 * @brief トランスフォームのセッター
　　 * @param Transform (_transform) トランスフォーム
	 * @return void
　　*/
	inline void SetTransform(Transform _transform);

	/**
	* @fn GetTransposedWorldMatrix
	* @brief 転置したワールド行列を返す
	* @return DirectX::SimpleMath::Matrix
	*/
	inline DirectX::SimpleMath::Matrix GetTransposedWorldMatrix();
	
	/**
	* @fn GetRotationMatrix
	* @brief 回転行列を返す
	* @return DirectX::SimpleMath::Matrix
	*/
	DirectX::SimpleMath::Matrix GetRotationMatrix();

	/**
	* @fn GetForwardVector
	* @brief 前向きベクトルを返す
	* @return DirectX::SimpleMath::Vector3
	*/
	DirectX::SimpleMath::Vector3 GetForwardVector()
	{
		GetRotationMatrix();
		DirectX::SimpleMath::Vector3 forward;
		forward.x = mRotationMatrix._31;
		forward.y = mRotationMatrix._32;
		forward.z = mRotationMatrix._33;
		forward.Normalize();
		return forward;
	}

	/**
	* @fn GetRightVector
	* @brief 右向きベクトルを返す
	* @return DirectX::SimpleMath::Vector3
	*/
	DirectX::SimpleMath::Vector3 GetRightVector()
	{
		DirectX::SimpleMath::Matrix rot = GetRotationMatrix();
		DirectX::SimpleMath::Vector3 right;
		right.x = rot._11;
		right.y = rot._12;
		right.z = rot._13;
		return right;
	}

	/**
	* @fn GetUpVector
	* @brief 上向きベクトル
	* @return DirectX::SimpleMath::Vector3
	*/
	DirectX::SimpleMath::Vector3 GetUpVector()
	{
		DirectX::SimpleMath::Matrix rot = GetRotationMatrix();
		DirectX::SimpleMath::Vector3 Up;
		Up.x = rot._21;
		Up.y = rot._22;
		Up.z = rot._23;
		return Up;
	}
};

//------------------- INLINES -------------------------

inline DirectX::SimpleMath::Vector3 TransformComponent::GetScale() const
{
	return mTransform.mScale;
}

inline Transform TransformComponent::GetTransform() const
{
	return mTransform;
}

inline void TransformComponent::SetPosition(const DirectX::SimpleMath::Vector3 _pos)
{	
	mTransform.mPosition = _pos;
}

inline void TransformComponent::SetScale(const DirectX::SimpleMath::Vector3 _scale)
{
	mTransform.mScale = _scale;
}

inline void TransformComponent::SetScale(const float _scale)
{
	mTransform.mScale = { _scale,_scale,_scale };
}

inline void TransformComponent::SetRotation(const DirectX::SimpleMath::Vector3 _rotation)
{
	mTransform.mRotation = _rotation;
}

inline void TransformComponent::AddRotation(const DirectX::SimpleMath::Vector3 _rotation)
{
	mTransform.mRotation += _rotation;
}

inline void TransformComponent::AddPosition(const DirectX::SimpleMath::Vector3 _vector)
{
	mTransform.mPosition += _vector;
}

inline void TransformComponent::SetTransform(Transform _transform)
{
	mTransform = _transform;
}

inline DirectX::SimpleMath::Matrix TransformComponent::GetTransposedWorldMatrix()
{
	return mWorldMatrix.Transpose();
}

inline DirectX::SimpleMath::Matrix TransformComponent::GetRotationMatrix()
{
	mRotationMatrix = DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(mTransform.mRotation.y, mTransform.mRotation.x, mTransform.mRotation.z);
	return mRotationMatrix;
}

inline void TransformComponent::SetPositionParentInfluence(bool _influence)
{
	bPositionParentInfluence = _influence;
}

inline void TransformComponent::SetRotationParentInfluence(bool _influence)
{
	bRotationParentInfluence = _influence;
}

inline void TransformComponent::SetScaleParentInfluence(bool _influence)
{
	bScaleParentInfluence = _influence;
}

inline void TransformComponent::SetParentTransformInfluence(bool _influence)
{
	bScaleParentInfluence = _influence;
	bRotationParentInfluence = _influence;
	bPositionParentInfluence = _influence;
}

inline DirectX::SimpleMath::Matrix TransformComponent::GetTranslationMatrix()
{
	return DirectX::SimpleMath::Matrix::CreateTranslation(mTransform.mPosition.x, mTransform.mPosition.y, mTransform.mPosition.z);
}

inline DirectX::SimpleMath::Matrix TransformComponent::GetScaleMatrix()
{
	return DirectX::SimpleMath::Matrix::CreateScale(mTransform.mScale.x, mTransform.mScale.y, mTransform.mScale.z);
}

inline DirectX::SimpleMath::Vector3 TransformComponent::GetPosition() const
{
	return mTransform.mPosition;
}

inline DirectX::SimpleMath::Vector3 TransformComponent::GetRotation() const
{
	return mTransform.mRotation;
}

inline DirectX::SimpleMath::Matrix TransformComponent::GetWorldMatrix()
{
	return mWorldMatrix;
}
