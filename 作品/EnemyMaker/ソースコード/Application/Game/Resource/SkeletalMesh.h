/**
* @file SkeletalMesh.h
* @brief SkeletalMeshクラスの定義
*/

#pragma once

//---------- INCLUDES ------------
#include <memory>
#include <string>
#include "../Component/TransformComponent/Transform.h"
#include "../../System/RendererSystem/VisualEntity/VisualEntity.h"
#include "../../System/AssetSystem/AssetHandle.h"
#include "../../System/AssetSystem/SkeletalMesh/SkeletalMeshAsset.h"

//---------- 前方宣言 ------------
class Skeleton;
class GameObject;

/**
* @class SkeletalMesh
* @brief スケルタルメッシュクラス
*/
class SkeletalMesh
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	SkeletalMesh();
	
	/**
	* デストラクタ
	*/
	~SkeletalMesh();

private:
	/** SkeletalMeshAssetへのハンドル */
	std::shared_ptr<AssetHandle> mAssetHandle;
	
	/** スケルトン */
	std::shared_ptr<Skeleton> mSkeleton;

	/** 描画用オブジェクト */
	std::shared_ptr<VisualEntity> mVisualEntity;

	/** アニメーションしているか */
	bool mbAnimate;

	/** トランスフォーム */
	Transform mTransform;

	/** ワールド空間のトランスフォーム */
	Transform mWorldTransform;

	/** ワールド行列 */
	DirectX::SimpleMath::Matrix mWorldMatrix;

	/** オーナーのゲームオブジェクト */
	GameObject* mOwnerGameObject;

public:
	/**
	* @fn Initialize
	* @brief 初期化処理
	* @param const std::string& (_filePath)
	* @return void
	*/
	void Initialize(const std::string& _filePath);

	/**
	* @fn Update
	* @brief 更新処理
	* @return void
	*/
	void Update();

	/**
	* @fn Draw
	* @brief 描画処理
	* @return void
	*/
	void Draw();
	
private:
	/**
	* @fn CreateVisualEntity
	* @brief 描画用オブジェクトの生成関数
	* @return void
	*/
	void CreateVisualEntity();

public:
	/**
	* @fn GetSkeletalMeshAsset
	* @brief スケルタルメッシュアセットを返す
	* @return SkeletalMeshAsset
	*/
	inline SkeletalMeshAsset GetSkeletalMeshAsset() const noexcept;

	/**
	* @fn GetSkeleton
	* @brief Skeletonの弱参照を返す
	* @return std::weak_ptr<Skeleton>
	*/
	inline std::weak_ptr<Skeleton> GetSkeleton() const;

	/**
	* @fn SetAnimate
	* @brief アニメーションしているかをセットする
	* @param const bool (_animate)
	* @return void
	*/
	inline void SetAnimate(bool _animate) noexcept;
	
	/**
	* @fn SetTransform
	* @brief トランスフォームのセット
	* @param Transform (_trans)
	* @return void
	*/
	inline void SetTransform(Transform _trans);

	/**
	* @fn CalucWorldMatrix
	* @brief ワールド行列を計算する
	* @detail 何かに親子付けしたければ,引数に親子付けしたい行列を渡すせば親子付けされる
	* @param const DirectX::SimpleMath::Matrix& (_parentMatrix)
	* @return void
	*/
	void CalucWorldMatrix(const DirectX::SimpleMath::Matrix& _parentMatrix);

	/**
	* @fn SetWorldMatrix
	* @brief ワールド行列にセッター
	* @param const DirectX::SimpleMath::Matrix& (_worldMatrix)
	* @return void
	*/
	inline void SetWorldMatrix(const DirectX::SimpleMath::Matrix& _worldMatrix);

	/**
	* @fn GetWorldMatrix
	* @brief ワールド行列を返す
	* @return DirectX::SimpleMath::Matrix
	*/
	inline DirectX::SimpleMath::Matrix GetWorldMatrix() const noexcept;

	/**
	* @fn SetGameObject
	* @brief オーナーのゲームオブジェクトのセッター
	* @param GameObject* (_owner)
	* @return void
	*/
	inline void SetOwnerObject(GameObject* _owner) noexcept;

	/**
	* @fn GetOwnerOjbect
	* @brief オーナーのゲームオブジェクトのゲッター
	* @return GameObject*
	*/
	inline GameObject* GetOwnerObject() const noexcept;

	/**
	* @fn GetTransform
	* @brief トランスフォームのゲッター
	* @return Transform
	*/
	inline Transform GetWorldTransform() const noexcept;

	/**
	* @fn SwapShader
	* @brief シェーダーの使用順番を入れ替える
	* @return void
	*/
	inline void SwapShader();

	/**
	* @fn AddVertexShader
	* @brief 頂点シェーダーの追加関数
	* @detail 描画用オブジェクトに頂点シェーダーを作成し追加する
	* @return std::shared_ptr<VShader>
	*/
	template<DerivedVertexShader VShader>
	inline std::shared_ptr<VShader> AddVertexShader();

	/**
	* @fn AddPixelShader
	* @brief ピクセルシェーダーの追加関数
	* @detail 描画用オブジェクトにピクセルシェーダーを作成し追加する
	* @return std::shared_ptr<PShader>
	*/
	template<DerivedPixelShader PShader>
	inline std::shared_ptr<PShader> AddPixelShader();

	/**
	* @fn SetDrawType
	* @brief 描画タイプを設定
	* @param const DrawType (_drawType) 描画の種類
	* @param const size_t   (_id)      描画の種類を設定したいシェーダーID
	* @return void
	*/
	inline void SetDrawType(const CullType _drawType, const size_t _id);

	/**
	* @fn SetMaterialDiffuse
	* @brief マテリアルディフューズのセッター
	* @detail 複数メッシュの場合でもすべてのメッシュにディフューズを設定する
	* @param const DirectX::SimpleMath::Color (_diffuse)
	* @return void
	*/
	inline void SetMaterialDiffuse(const DirectX::SimpleMath::Color _diffuse);

};

//------------ INLINES ----------

inline void SkeletalMesh::SetWorldMatrix(const DirectX::SimpleMath::Matrix& _worldMatrix)
{
	mWorldMatrix = _worldMatrix;
}

inline DirectX::SimpleMath::Matrix SkeletalMesh::GetWorldMatrix() const noexcept
{
	return mWorldMatrix;
}

inline SkeletalMeshAsset SkeletalMesh::GetSkeletalMeshAsset() const noexcept
{
	return mAssetHandle->Get<SkeletalMeshAsset>();
}

inline std::weak_ptr<Skeleton> SkeletalMesh::GetSkeleton() const
{
	return mSkeleton;
}

inline void SkeletalMesh::SetAnimate(bool _animate) noexcept
{
	mbAnimate = _animate;
}

inline void SkeletalMesh::SetTransform(Transform _trans)
{
	mTransform = _trans;
}

inline void SkeletalMesh::SetOwnerObject(GameObject* _owner) noexcept
{
	mOwnerGameObject = _owner;
}

inline GameObject* SkeletalMesh::GetOwnerObject() const noexcept
{
	return mOwnerGameObject;
}

inline Transform SkeletalMesh::GetWorldTransform() const noexcept
{
	return mWorldTransform;
}

inline void SkeletalMesh::SwapShader()
{
	mVisualEntity->SwapShader();
}

inline void SkeletalMesh::SetDrawType(const CullType _drawType, const size_t _id)
{
	mVisualEntity->SetCullType(_drawType, _id);
}

inline void SkeletalMesh::SetMaterialDiffuse(const DirectX::SimpleMath::Color _diffuse)
{
	for (std::shared_ptr<VisualEntityData> entity : mVisualEntity->GetAllVisualEntityData())
	{
		entity->SetMaterialDiffuse(_diffuse);
	}
}

template<DerivedVertexShader VShader>
inline std::shared_ptr<VShader> SkeletalMesh::AddVertexShader()
{
	return mVisualEntity->MakeVertexShader<VShader>();
}

template<DerivedPixelShader PShader>
inline std::shared_ptr<PShader> SkeletalMesh::AddPixelShader()
{
	return mVisualEntity->MakePixelShader<PShader>();
}
