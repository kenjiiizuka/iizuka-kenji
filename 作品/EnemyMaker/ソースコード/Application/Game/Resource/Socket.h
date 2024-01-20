/**
* @file Socket.h
* @brief Socketクラスの定義
*/

#pragma once

//------------ INCLUDES ------------
#include <string>
#include "Bone.h"


/**
* @class Socket
* @brief アタッチポイントとして使用するSkeletonに追加する物
*/
class Socket : public Bone
{
public:
	/**
	 * デフォルトコンストラクタ
	*/
	Socket();

	/**
	 * デストラクタ
	*/
	~Socket();

private:
	/** トランスフォーメーション行列 親ボーンからの位置を示す */
	DirectX::SimpleMath::Matrix mTransformation;

public:
	/**
	* @fn Initialize
	* @brief 初期化処理
	* @param const Transform&      (_transform)
	* @param const std::string&    (_socketName)
	* @param const std::shared_ptr (_parentBone)
	* @return void
	*/
	void Initialize(const Transform& _transform, const std::string& _socketName, const std::shared_ptr<Bone> _parentBone);
	
	/**
	 * @fn CalucBoneMatrix
	 * @brief ボーン行列を計算する関数
	 * @param DirectX::SimpleMath::Matrix (_parentBoneMatrix)
	 * @return void
	*/
	void CalcuBindPoseBoneMatrix(DirectX::SimpleMath::Matrix _parentBoneMatrix = DirectX::SimpleMath::Matrix::Identity) override;

	/**
	* @fn CalucAnimatedBoneMatrix
	* @brief アニメーションを適応したボーン行列を計算する
	* @param DirectX::SimpleMath::Matrix (_parentBoneMatrix)
	* @return void
	*/
	void CalcuAnimatedBoneMatrix(DirectX::SimpleMath::Matrix _parentBoneMatrix = DirectX::SimpleMath::Matrix::Identity) override;

public:
	/** 
	* @fn SetTransform
	* @brief トランスフォームのセッター
	* @param const Transform& (_transform)
	* @return void
	*/
	inline void SetTransform(const Transform& _transform) noexcept;

	/**
	* @fn GetTransform
	* @brief トランスフォームのゲッター
	* @return Transform 
	*/
	inline Transform GetTransform() const noexcept;
};

//-------------- INLINES --------------

inline void Socket::SetTransform(const Transform& _transform) noexcept
{
	mTransform = _transform;
}

inline Transform Socket::GetTransform() const noexcept
{
	return mTransform;
}


