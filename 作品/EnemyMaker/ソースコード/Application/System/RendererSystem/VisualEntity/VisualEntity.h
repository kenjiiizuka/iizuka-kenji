#pragma once
#include <d3d11.h>
#include <memory>
#include <SimpleMath.h>
#include <array>
#include <string>
#include "VisualEntityData.h"
/**
* @file  VisualEntity.h
* @brief VisualEntityクラスの定義
*/

//--------- 前方宣言 -----------
class GameObject;
class VisualEntityData;
class VertexShader;
class PixelShader;
class GeometryShader;

//------- コンセプト ---------
template<class VShader>
concept DerivedVertexShader = std::derived_from<VShader, VertexShader>;

template<class PShader>
concept DerivedPixelShader = std::derived_from<PShader, PixelShader>;

template<class GShader>
concept DerivedGeometryShader = std::derived_from<GShader, GeometryShader>;

/**
* @enum CullType
* @brief カリングタイプ
*/
enum class CullType : uint8_t
{
	Draw_SolidBack,  /**< ぬりつぶしの背面 */
	Draw_SolidFront, /**< ぬりつぶしの前面 */
	Draw_WireFrame,  /**< ワイヤーフレームのなし */
};

/**
 * @class VisualEntity
 * @brief 描画される物体の基底となるクラス
 * @detail シェーダーは二つまで使用可能
 */
class VisualEntity
{
public:
	/**
	 * コンストラクタ
	 *
	 * @param const Description& (_desc) 
	*/
	VisualEntity(const std::vector<std::shared_ptr<VisualEntityData>>& _entityData);

	/**
	* コンストラクタ
	* 
	* @param const std::shared_ptr<VisualEntityData> (_entityData)
	*/
	VisualEntity(const std::shared_ptr<VisualEntityData>& _entityData);
	
	/**
	* デフォルトコンストラクタ
	*/
	VisualEntity();

	/**
	 * デストラクタ
	*/
	virtual ~VisualEntity();

private:
	/** 描画データ */
	std::vector<std::shared_ptr<VisualEntityData>> mEntityData;

	/** 頂点シェーダー */
	std::vector<std::shared_ptr<VertexShader>> mVertexShader;

	/** ピクセルシェーダー */
	std::vector<std::shared_ptr<PixelShader>> mPixelShader;

	/** ジオメトリシェーダー */
	std::vector<std::shared_ptr<GeometryShader>> mGeometryShader;

	/** このEntityのワールド行列 */
	DirectX::SimpleMath::Matrix mWorldMatrix;

	/** オーナーのゲームオブジェクト */
	GameObject* mOwnerObject;

	/** 描画の種類 シェーダーごとに設定する */
	std::vector<CullType> mDrawType;

	/** 自身を破棄するか */
	bool mbDestroy;

	/** 描画するかしないか */
	bool mbVisible;

public:
	/**
　　 * @fn Draw
　　 * @brief 描画処理
　　 * @return void
　　*/
	void Draw();

	/**
	* @fn DrawDropShadow
	* @brief 落ち影描画
	* @return void
	*/
	void DrawDropShadow();

private:
	/**
	* @fn SetRasterizerState
	* @brief ラスタライザ―の設定
	* @param const size_t (entity_i)
	* @return void
	*/
	void SetRasterizerState(const size_t entity_i);

	/**
	* @fn SetupGeometryShader
	* @brief ジオメトリシェーダーを更新、割り当てる
	* @param const size_t (shader_i) 使用するジオメトリシェーダーの添え字
	* @return void
	*/
	void SetupGeometryShader(const size_t shader_i);

public:
	/**
　　 * @fn　Copy
　　 * @brief VisualEntityのコピー関数
	 * @param const std::shared_ptr<VisualEntity> (_entity)
　　 * @return void
　　*/
	void Copy(const std::shared_ptr<VisualEntity> _entity);

	/**
　　 * @fn　SetOwnerObject
　　 * @brief オーナーオブジェクトのセッター
     * @param GameObject* (_owner) 
　　 * @return void
　　*/
	inline void SetOwnerObject(GameObject* _owner);

	/**
　　 * @fn　GetOwnerObject
　　 * @brief オーナーオブジェクトの取得
　　 * @return GameObject
　　*/
	inline GameObject* GetOwnerObject();

	/**
　　 * @fn　MakeVertexShader
　　 * @brief 頂点シェーダーの作成関数
　　 * @return void
　　*/
	template<DerivedVertexShader VShader>
	inline std::shared_ptr<VShader> MakeVertexShader();

	/**
　　 * @fn　MakePixelShader
　　 * @brief ピクセルシェーダーの作成関数
　　 * @return void
　　*/
	template<DerivedPixelShader PShader>
	inline std::shared_ptr<PShader> MakePixelShader();
	
	/**
	* @fn MakeGeometryShader
	* @brief ジオメトリシェーダー作成関数
	* @return void
	*/
	template<DerivedGeometryShader GSahder>
	inline std::shared_ptr<GSahder> MakeGeometryShader();

	/**
　　 * @fn　GetVisualEntityData
　　 * @brief 指定したヴィジュアルデータを取得する関数
     * @param uint8_t (_dataID) 
　　 * @return std::shared_ptr<VisualEntityData>
　　*/
	inline std::shared_ptr<VisualEntityData> GetVisualEntityData(uint8_t _dataID) const;

	/**
　　 * @fn　GetAllVisualEntityData
　　 * @brief ヴィジュアルデータを取得する関数
　　 * @return std::vector<std::shared_ptr<VisualEntityData>>
　　*/
	inline std::vector<std::shared_ptr<VisualEntityData>> GetAllVisualEntityData();

	/**
　　 * @fn　GetVertexShader
　　 * @brief 頂点シェーダーの取得関数
	 * @param const size_t (_shaderID)
　　 * @return std::shared_ptr<VertexShader> 
　　*/
	inline std::shared_ptr<VertexShader> GetVertexShader(const size_t _shaderID = 0) const;

	/**
　　 * @fn　GetPixelShader
　　 * @brief ピクセルシェーダーの取得関数
	 * @param const size_t (_shaderID)
　　 * @return std::shared_ptr<PixelShader>
　　*/
	inline std::shared_ptr<PixelShader> GetPixelShader(const size_t _shaderID = 0) const;

	/**
　　 * @fn　SetPixelShader
　　 * @brief ピクセルシェーダーのセット関数
     * @param const std::shared_ptr<PixelShader> (_shader)
	 * @param const size_t (_shaderID)
　　 * @return void
　　*/
	inline void SetPixelShader(const std::shared_ptr<PixelShader> _shader, const size_t _shaderID = 0);

	/**
	 * @fn SwapShader
	 * @brief 頂点シェーダー、ピクセルシェーダーの順番を入れ替える
	 * @return void
	*/
	inline void SwapShader();

	/**
	 * @fn SwapVertexShader
	 * @brief 頂点シェーダーの順番を入れ替える
	 * @return void
	*/
	inline void SwapVertexShader();

	/**
	 * @fn SwapPixelShader
	 * @brief ピクセルシェーダーの順番を入れ替える
	 * @return void
	*/
	inline void SwapPixelShader();

	/**
　　 * @fn　GetWorldMatrix
　　 * @brief ワールド行列の取得関数
　　 * @return DirectX::SimpleMath::Matrix
　　*/
	inline DirectX::SimpleMath::Matrix GetWorldMatrix() const;

	/**
　　 * @fn　SetWorldMatrix
　　 * @brief ワールド行列セット関数
　　 * @return void
　　*/
	inline void SetWorldMatrix(DirectX::SimpleMath::Matrix _worldMatrix);

	/**
　　 * @fn　SetDrawType
　　 * @brief 描画の種類のセット
     * @param CullType (_type) 
	 * @param const size_t (_shaderID)
　　 * @return void
　　*/
	inline void SetCullType(CullType _type, const size_t _shaderID = 0);

	/**
　　 * @fn　GetNumData
　　 * @brief データの数
　　 * @return size_t
　　*/
	inline size_t GetNumData() const;

	/**
　　 * @fn　Destroy
　　 * @brief 破棄を関数
　　 * @return void
　　*/
	inline void Destroy();

	/**
　　 * @fn　IsDestroy
　　 * @brief 破棄されるかを返す
　　 * @return bool true 破棄 : false 破棄しない
　　*/
	inline bool IsDestroy();

	/**
　　 * @fn　SetVisible
　　 * @brief 描画するかしないかのセッター
     * @param bool (_visible)
　　 * @return void
　　*/
	inline void SetVisible(bool _visible);
};

//----------------- INLINES --------------------

inline void VisualEntity::SetOwnerObject(GameObject* _owner)
{
	mOwnerObject = _owner;
}

inline GameObject* VisualEntity::GetOwnerObject()
{
	return mOwnerObject;
}

inline std::shared_ptr<VisualEntityData> VisualEntity::GetVisualEntityData(uint8_t _dataID) const
{
	return  (_dataID < mEntityData.size()) ? mEntityData[_dataID] : nullptr;
}

inline std::vector<std::shared_ptr<VisualEntityData>> VisualEntity::GetAllVisualEntityData()
{
	return mEntityData;
}

inline std::shared_ptr<VertexShader> VisualEntity::GetVertexShader(const size_t _shaderID) const
{
	return mVertexShader[_shaderID] ? mVertexShader[_shaderID] : nullptr;
}

inline std::shared_ptr<PixelShader> VisualEntity::GetPixelShader(const size_t _shaderID) const
{
	return mPixelShader[_shaderID] ? mPixelShader[_shaderID] : nullptr;
}

inline void VisualEntity::SetPixelShader(const std::shared_ptr<PixelShader> _shader, const size_t _shaderID)
{
	mPixelShader[_shaderID] = _shader;
}

inline void VisualEntity::SwapShader()
{
	SwapVertexShader();
	SwapPixelShader();
}

inline void VisualEntity::SwapVertexShader()
{
	if (mVertexShader.size() < 2)
	{
		return;
	}
	std::shared_ptr<VertexShader> shader = mVertexShader[0];
	mVertexShader[0] = mVertexShader[1];
	mVertexShader[1] = shader;
}

inline void VisualEntity::SwapPixelShader()
{
	if (mPixelShader.size() < 2)
	{
		return;
	}

	std::shared_ptr<PixelShader> shader = mPixelShader[0];
	mPixelShader[0] = mPixelShader[1];
	mPixelShader[1] = shader;
}

inline DirectX::SimpleMath::Matrix VisualEntity::GetWorldMatrix() const
{
	return mWorldMatrix;
}

inline void VisualEntity::SetWorldMatrix(DirectX::SimpleMath::Matrix _worldMatrix)
{
	mWorldMatrix = _worldMatrix;
}

inline void VisualEntity::SetCullType(CullType _type, const size_t _shaderID)
{
	mDrawType[_shaderID] = _type;
}

inline size_t VisualEntity::GetNumData() const
{
	return mEntityData.size();
}

inline void VisualEntity::Destroy()
{
	mbDestroy = true;
}

inline bool VisualEntity::IsDestroy()
{
	return mbDestroy;
}

inline void VisualEntity::SetVisible(bool _visible)
{
	mbVisible = _visible;
}

template<DerivedVertexShader VShader>
inline std::shared_ptr<VShader> VisualEntity::MakeVertexShader()
{
	// すでにシェーダーが二つ以上あれば追加しない
	if (mVertexShader.size() > 2)
	{
		return nullptr;
	}

	std::shared_ptr<VShader> shader = std::make_shared<VShader>(this);
	mVertexShader.emplace_back(shader);
	return shader;
}

template<DerivedPixelShader PShader>
inline std::shared_ptr<PShader> VisualEntity::MakePixelShader()
{
	// すでにシェーダーが二つ以上あれば追加しない
	if (mPixelShader.size() > 2)
	{
		return nullptr;
	}

	std::shared_ptr<PShader> shader = std::make_shared<PShader>(this);
	mPixelShader.emplace_back(shader);
	return shader;
}

template<DerivedGeometryShader GSahder>
inline std::shared_ptr<GSahder> VisualEntity::MakeGeometryShader()
{
	// すでにシェーダーが二つ以上あれば追加しない
	if (mGeometryShader.size() > 2)
	{
		return nullptr;
	}

	// 作成
	std::shared_ptr<GSahder> shader = std::make_shared<GSahder>(this);
	mGeometryShader.emplace_back(shader);
	return shader;
}
