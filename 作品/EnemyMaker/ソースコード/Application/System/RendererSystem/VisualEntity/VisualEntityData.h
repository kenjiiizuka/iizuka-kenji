/**
* @file VisualEntityData.h
* @brief VisualEntityDataクラスの定義
*/

#pragma once

//---------- INCLUDES ----------
#include <d3d11.h>
#include <memory>
#include <functional>
#include <SimpleMath.h>
#include "../../AssetSystem/Texture/Texture.h"


/**
 * @class VisualEntityData
 * @brief 3Dビジュアルエンティティのデータを管理するクラス
 */
class VisualEntityData final
{
public:
	/**
	* @struct Material
	* @brief マテリアルの情報を保持する構造体
	*/
	struct Material
	{
		DirectX::SimpleMath::Vector4 mDiffuse; ///< ディフューズ色
		DirectX::SimpleMath::Vector4 mAmbient; ///< アンビエント色
		DirectX::SimpleMath::Vector4 mSpecular; ///< スペキュラ色	
		DirectX::SimpleMath::Color	Emission;	
		float mShininess;
		BOOL		TextureEnable;
		float		mDummy[2];	
		Texture mTexture; ///< マテリアルに関連するテクスチャ
		Material();
	};

	/**
  　 * @struct Description
  　 * @brief VisualEntityの作成時に必要な情報を保持する構造体
  　*/
	struct Description
	{
		std::shared_ptr<void> mpVertex;
		uint32_t mVertexTypeByteSize;  ///< 1頂点のデータサイズ
		uint32_t mVertexCount;         ///< 頂点の数
		bool mbAbleMap;         ///< 頂点バッファが書き込み可能かどうか
		bool mbUseIndex;      ///< インデックスバッファを使用するか
		std::shared_ptr<void> mpIndex;
		uint32_t mIndexTypeByteSize;   ///< 1インデックスのデータサイズ
		uint32_t mIndexCount;  ///< インデックスの数
		D3D11_PRIMITIVE_TOPOLOGY mTopology; ///< プリミティブのトポロジー

		Description();
		Description(const Description& _desc);
	};

public:
	/**
	* コンストラクタ
	* 
	* @param const Description& (_desc)
	*/
	VisualEntityData(const Description& _desc);

	/**
	* コンストラクタ
	* 
	* @param const std::shared_ptr<VisualEntityData>& (_entity)
	*/
	VisualEntityData(const std::shared_ptr<VisualEntityData>& _entity);

	/**
	* デストラクタ
	*/
	~VisualEntityData();
private:
	/** 頂点バッファ */
	ID3D11Buffer* mVertexBuffer;

	/** インデックスバッファ */
	ID3D11Buffer* mIndexBuffer;

	/** マテリアル */
	Material mMaterial;

	/** VisualEntity作成時のデータ */
	Description mDesc;

public:
	/**
　　 * @fn Draw
　　 * @brief 描画処理
　　 * @return void
　　*/
	void Draw();

private:
	/**
　　 * @fn CreateVertexBuffer
　　 * @brief 頂点バッファの作成関数
	 * @param const void* (_pVertexData) 頂点データ
	 * @param uint32_t (_size) 1頂点のデータサイズ
	 * @param uint32_t (_count) 頂点の数
	 * @param bool (_isWrite) 書き込み可能か
　　 * @return HRESULT
　　*/
	HRESULT CreateVertexBuffer(const void* _pVertexData, uint32_t _size, uint32_t _count, bool _isWrite);

	/**
　　 * @fn　CreateIndexBuffer
　　 * @brief 頂点バッファの作成関数
	 * @param const void* (_pIndexData) 頂点データ
	 * @param uint32_t (_size) 1インデックスのデータサイズ
	 * @param uint32_t (_count) インデックスの数
　　 * @return HRESULT
　　*/
	HRESULT CreateIndexBuffer(const void* _pIndexData, uint32_t _size, uint32_t _count);

public:
	/**
　　 * @fn ReMakeVertexBuffer
　　 * @brief 頂点バッファの作り直し関数
	 * @param const void* (_pVertexData) 頂点データ
	 * @param uint32_t (_size) 1頂点のデータサイズ
	 * @param uint32_t (_count) 頂点の数
	 * @param bool (_isWrite) 書き込み可能か
　　 * @return HRESULT
　　*/
	HRESULT ReMakeVertexBuffer(void* _pVertexData, uint32_t _size, uint32_t _count, bool _isWrite);

	/**
　　 * @fn ReMakeVertexBuffer
     * @brief 頂点バッファの作り直し関数
　　 * @param std::function<Description(const Description&)> (_reDesc)
　　 * @return HRESULT
　　*/
	HRESULT ReMakeVertexBuffer(std::function<void(const Description&, Description*)> _reDesc);

	/**
　　 * @fn MapVertexBuffer
     * @brief 頂点データをMapしてデータを書き込む
　　 * @param void* (_vertexData)
　　 * @return HRESULT
　　*/
	HRESULT MapVertexBuffer(void* _vertexData);

	/**
　　 * @fn　MakeMaterial
　　 * @brief マテリアル作成関数
	 * @param Material (_material)
　　 * @return void
　　*/
	void SetMaterial(Material _material);

	/**
	* @fn SetMaterialTexture
	* @brief マテリアルにテクスチャをセットする
	* @param ID3D11ShaderResourceView* (_texture)
	* @return void
	*/
	inline void SetMaterialTexture(ID3D11ShaderResourceView* _texture);

	/**
	* @fn SetMaterialTexture
	* @brief マテリアルにテクスチャをセットする
	* @param const Texture& (_texture)
	* @return void
	*/
	inline void SetMaterialTexture(const Texture& _texture);

	/**
　　 * @fn　GetDescription
　　 * @brief デスクリプションの取得
　　 * @return Description
　　*/
	inline Description GetDescription() const;

	/**
　　 * @fn　GetMaterial
　　 * @brief マテリアルのゲッター
　　 * @return Description
　　*/
	inline Material GetMaterial() const;

	/**
　　 * @fn　SetMaterialDiffuse
　　 * @brief マテリアルのディフューズのセット
     * @param DirectX::SimpleMath::Vector4 (_diffuse)
　　 * @return void
　　*/
	inline void SetMaterialDiffuse(DirectX::SimpleMath::Vector4 _diffuse);

};

//------------- INLINES ------------------

inline void VisualEntityData::SetMaterialTexture(ID3D11ShaderResourceView* _texture)
{
	mMaterial.mTexture.SetResource(_texture);
}

inline void VisualEntityData::SetMaterialTexture(const Texture& _texture)
{
	mMaterial.mTexture = _texture;
}

inline VisualEntityData::Description VisualEntityData::GetDescription() const
{
	return mDesc;
}

inline VisualEntityData::Material VisualEntityData::GetMaterial() const
{
	return mMaterial;
}

inline void VisualEntityData::SetMaterialDiffuse(DirectX::SimpleMath::Vector4 _diffuse)
{
	mMaterial.mDiffuse = _diffuse;
}
