#pragma once
//------------- INCLUDES ------------
#include <SimpleMath.h>
#include <memory>
#include <string>
#include "../../../System/RendererSystem/Renderer.h"
#include "../../../System/RendererSystem/VisualEntity/VisualEntityData.h"
#include "../../../System/RendererSystem/VisualEntity/VisualEntity.h"
#include "../../../System/RendererSystem/Shader/VertexShader/Object3DVertexShader.h"
#include "../../../System/RendererSystem/Shader/PixelShader/LightPixelShader.h"
#include "../../../System/AssetSystem/AssetHandle.h"
#include "../TransformComponent/Transform.h"


class GameObject;

/**
* @class StaticMesh
* @brief スタティックメッシュクラス
* @detail スタティックメッシュのアセットデータから描画用オブジェクトを作成し、Transformを持っている
*/
class StaticMesh
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	StaticMesh();

	/**
	* デストラクタ
	*/
	~StaticMesh();

private:
	/** StaticMeshAssetへのハンドル */
	std::shared_ptr<AssetHandle> mAssetHandle;
	
	/** オーナー */
	GameObject* mOwnerGameObject;

protected:
	/** トランスフォーム */
	Transform mTransform;

	/** ワールド空間のトランスフォーム */
	Transform mWorldTransform;

	/** ワールド行列 */
	DirectX::SimpleMath::Matrix mWorldMatrix;

	/** 描画の実体 */
	std::shared_ptr<VisualEntity> mVisualEntity;

public:
	/**
	* @fn Initialize
	* @brief 初期化処理
	* @param const std::string& (_filePath)
	* @return void
	*/
	void Initialize(const std::string& _filePath);

	/**
	 * @fn　Draw
	 * @brief 描画処理
	 * @return void
	*/
	virtual void Draw();

private:
	/**
	* @fn CreateVisualEntity
	* @brief 描画オブジェクトの作成
	* @return void
	*/
	virtual void CreateVisualEntity();

public:
	/**
	* @fn SetMaterialDiffuse
	* @brief マテリアルカラーをセットする
	* @param const DirectX::SimpleMath::Vector4 (_diffuse)
	* @return void
	*/
	void SetMaterialDiffuse(const DirectX::SimpleMath::Vector4 _diffuse);

	/**
	* @fn CalucWorldMatrix
	* @brief ワールド行列を計算する
	* @detail 何かに親子付けしたければ,引数に親子付けしたい行列を渡すせば親子付けされる
	* @param const DirectX::SimpleMath::Matrix& _worldMatrix
	* @return void
	*/
	void CalucWorldMatrix(const DirectX::SimpleMath::Matrix& _worldMatrix);

	/**
	 * @fn　GetVisualEntity
	 * @brief VisualEntityの取得
	 * @return std::shared_ptr<VisualEntity>
	*/
	inline std::shared_ptr<VisualEntity> GetVisualEntity();

	/**
	 * @fn　SetOwnerObject
	 * @brief オーナーのオブジェクトセッター
	 * @param GameObject* (_owner)
	 * @return void
	*/
	inline void SetOwnerObject(GameObject* _owner);

	/**
	* @fn SetWorldMatrix
	* @brief ワールド行列のセッター
	* @param DirectX::SimpleMath::Matrix _worldMatrix
	* @return void
	*/
	inline void SetWorldMatrix(DirectX::SimpleMath::Matrix _worldMatrix);

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
	* @fn AddGeometryShader
	* @brief ジオメトリシェーダー追加関数
	* @detail 描画用オブジェクトにジオメトリシェーダーを作成し追加する
	* @return std::shared_ptr<GShader>
	*/
	template<DerivedGeometryShader GShader>
	inline std::shared_ptr<GShader> AddGeometryShader();

	/**
	* @fn SetDrawType
	* @brief 描画タイプを設定
	* @param const DrawType (_drawType) 描画の種類
	* @param const size_t   (_id)      描画の種類を設定したいシェーダーID
	* @return void
	*/
	inline void SetDrawType(const CullType _drawType, const size_t _id);

	/**
	* @fn SetVisible
	* @brief 描画するかしないかを切り替える関数
	* @param const bool (_visible) true 描画する false 描画しない
	* @return void
	*/
	inline void SetVisible(const bool _visible);

};

//---------------- INLINES ------------------------------

inline std::shared_ptr<VisualEntity> StaticMesh::GetVisualEntity()
{
	return mVisualEntity;
}

inline void StaticMesh::SetWorldMatrix(DirectX::SimpleMath::Matrix _worldMatrix)
{
	mWorldMatrix = _worldMatrix;
}

inline void StaticMesh::SetOwnerObject(GameObject* _owner)
{
	mOwnerGameObject = _owner;
}

inline void StaticMesh::SwapShader()
{
	mVisualEntity->SwapShader();
}

inline void StaticMesh::SetDrawType(const CullType _drawType, const size_t _id)
{
	mVisualEntity->SetCullType(_drawType, _id);
}

inline void StaticMesh::SetVisible(const bool _visible)
{
	mVisualEntity->SetVisible(_visible);
}

template<DerivedVertexShader VShader>
inline std::shared_ptr<VShader> StaticMesh::AddVertexShader()
{
	return mVisualEntity->MakeVertexShader<VShader>();
}

template<DerivedPixelShader PShader>
inline std::shared_ptr<PShader> StaticMesh::AddPixelShader()
{
	return mVisualEntity->MakePixelShader<PShader>();
}

template<DerivedGeometryShader GShader>
inline std::shared_ptr<GShader> StaticMesh::AddGeometryShader()
{
	return mVisualEntity->MakeGeometryShader<GShader>();
}
