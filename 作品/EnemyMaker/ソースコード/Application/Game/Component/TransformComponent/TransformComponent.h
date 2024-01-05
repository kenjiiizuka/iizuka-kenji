#pragma once
#include "../Component.h"
#include <SimpleMath.h>
#include <DirectXMath.h>
#include "../../../Utility/Debug.h"
#include "Transform.h"

/**
* @file  TransformComponent.h
* @brief トランスフォームコンポーネントクラス
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
	DirectX::SimpleMath::Matrix mTraslationMatrix;

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


	DirectX::SimpleMath::Vector3 GetPosition() { return mTransform.mPosition; }
	DirectX::SimpleMath::Vector3 GetRotation() { return mTransform.mRotation; }
	DirectX::SimpleMath::Vector3 GetScale() { return mTransform.mScale; }
	
	inline Transform GetTransform();

	void SetPosition(DirectX::SimpleMath::Vector3 _pos) 
	{
		mTransform.mPosition = _pos;
	}

	void SetScale(DirectX::SimpleMath::Vector3 _scale) 
	{
		mTransform.mScale = _scale;
	}

	void SetScale(float _scale)
	{
		mTransform.mScale = { _scale,_scale,_scale };
	}

	void SetRotation(DirectX::SimpleMath::Vector3 _rotation) 
	{
		mTransform.mRotation = _rotation;
	}

	void AddRotation(DirectX::SimpleMath::Vector3 _rotation) 
	{
		mTransform.mRotation += _rotation;
	}

	void AddPosition(DirectX::SimpleMath::Vector3 _vector) 
	{
		mTransform.mPosition += _vector;
	}


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


	DirectX::SimpleMath::Matrix GetTransposedWorldMatrix() 
	{
		return mWorldMatrix.Transpose();
	}

	/*--------------- 
	  回転行列の取得
	---------------*/
	DirectX::SimpleMath::Matrix GetRotationMatrix() 
	{	
		mRotationMatrix = DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(mTransform.mRotation.y, mTransform.mRotation.x, mTransform.mRotation.z);
		return mRotationMatrix;
	}

	/*---------------------
      前向きベクトルの取得
    ---------------------*/
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

	/*--------------------
	 右向きベクトルの取得
	--------------------*/
	DirectX::SimpleMath::Vector3 GetRightVector()
	{
		DirectX::SimpleMath::Matrix rot = GetRotationMatrix();
		DirectX::SimpleMath::Vector3 right;
		right.x = rot._11;
		right.y = rot._12;
		right.z = rot._13;
		return right;
	}

	/*-------------------
	 上向きベクトルの取得
	--------------------*/
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

inline Transform TransformComponent::GetTransform()
{
	return mTransform;
}

inline void TransformComponent::SetTransform(Transform _transform)
{
	mTransform = _transform;
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

inline DirectX::SimpleMath::Matrix TransformComponent::GetWorldMatrix()
{
	return mWorldMatrix;
}
