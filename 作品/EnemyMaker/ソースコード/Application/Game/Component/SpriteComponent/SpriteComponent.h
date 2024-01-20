/**
* @file SpriteComponent.h
* @brief SpriteComponentクラスの定義
*/

#pragma once

//---------- INCLUDES ------------
#include <SimpleMath.h>
#include <string>
#include "../Component.h"
#include "../TransformComponent/Transform.h"

//--------- 前方宣言 ----------
class Texture;
class VisualEntity;
struct Vertex;

/**
* @class SpriteComponent
* @brief 2Dポリゴンを表示するコンポーネント テクスチャのセットもできる
*        左上頂点を基準に４頂点の位置が決まる
*/
class SpriteComponent : public Component
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	SpriteComponent();

	/**
	* デストラクタ
	*/
	~SpriteComponent();

private:		
	/** テクスチャ */
	std::shared_ptr<Texture> mTexture;

	/** 描画の実体 */
	std::shared_ptr<VisualEntity> mEntity;

	/** 頂点データ */
	Vertex* mVertex;

	/** ディフューズ */
	DirectX::SimpleMath::Vector4 mDiffuse;

	/** トランスフォーム */
	Transform mTransform;

	/** サイズ */
	DirectX::SimpleMath::Vector2 mSize;

public:
	/**
　　 * @fn Init
	 * @brief 初期化処理
	 * @param DirectX::SimpleMath::Vector2 (_pos)
	 * @param DirectX::SimpleMath::Vector2 (_size)
	 * @param DirectX::SimpleMath::Vector4 (_diffuse)
　　 * @return void
　　*/
	virtual void Init(DirectX::SimpleMath::Vector2 _pos, DirectX::SimpleMath::Vector2 _size, DirectX::SimpleMath::Vector4 _vertexColor = { 1.0f,1.0f,1.0f,1.0f });

	/**
　　 * @fn Uninit
	 * @brief 終了処理
　　 * @return void
　　*/
	void Uninit() override;

public:
	/**
	* 
	*/
	void SetupTransform(const std::string& _id);

	/**
	* @fn ReSize
	* @brief サイズを変更し、Mapして頂点の位置を変更する
	* @param const DirectX::SimpleMath::Vector2 (_size)
	* @return void
	*/
	void ReSize(const DirectX::SimpleMath::Vector2 _size);

	/**
　　 * @fn MapVertices
	 * @brief 頂点データのマップ
	 * @param @param Vertex* (_vertices)
　　 * @return bool true Mapに成功しているか  false Map失敗
　　*/
	bool MapVertices(Vertex* _vertices);

	/**
　　 * @fn MapVertices
	 * @brief 頂点データのマップ
　　 * @return bool true Mapに成功しているか  false Map失敗
　　*/
	bool MapVertices();

	/**
　　 * @fn SetTexture
	 * @brief テクスチャのセッター
	 * @param const Texture& (_texture)
　　 * @return void
　　*/
	void SetMaterialTexture(const Texture& _texture);

	/**
	* @fn　SetVisible
	* @brief 可視性のセッター
	* @param bool (_visible) true : 可視  false : 不可視
	* @return void
	*/
	void SetVisible(const bool _visible) noexcept;

	/**
　　 * @fn GetVertices
	 * @brief 頂点データの取得
　　 * @return void
　　*/
	inline Vertex* GetVertices();

	/**
　　 * @fn SetMaterialDiffuse
	 * @brief マテリアルディフューズのセッター
	 * @param DirectX::SimpleMath::Vector4 (_diffuse)
　　 * @return void
　　*/
	void SetMaterialDiffuse(const DirectX::SimpleMath::Vector4& _diffuse) noexcept;

	/**
	* @fn SetMaterialEmission
	* @brief マテリアルのエミッションのセッター
	* @param const DirectX::SimpleMath::Color& (_emission)
	* @return void
	*/
	void SetMaterialEmission(const DirectX::SimpleMath::Color& _emission) noexcept;

	/**
	* @fn SetMaterialShininess
	* @brief マテリアルの輝度のセッター
	* @param const float (_shininess)
	* @return void 
	*/
	void SetMaterialShininess(const float _shininess) noexcept;

	/**
	* @fn GetPosition
	* @brief スプライトの中心座標を取得する
	* @detail ４頂点の中心位置を返しています
	* @return DirectX::SimpleMath::Vector2
	*/
	DirectX::SimpleMath::Vector2 GetPosition() const noexcept;

	/**
	* @fn SetPositionAndMapVertices
	* @brief 渡された座標を中心にスプライトの4頂点をリマップする
	* @param const DirectX::SimpleMath::Vector2 (_position)
	* @return void
	*/
	void SetPositionAndMapVertices(const DirectX::SimpleMath::Vector2 _position) noexcept;

	/**
	* @fn GetDiffuse
	* @brief ディフューズ取得関数
	* @return DirectX::SimpleMath::Vector4
	*/
	inline DirectX::SimpleMath::Vector4 GetDiffuse() const noexcept;
};

//------------------- INLINES -----------------

inline Vertex* SpriteComponent::GetVertices()
{
	return mVertex;
}

inline DirectX::SimpleMath::Vector4 SpriteComponent::GetDiffuse() const noexcept
{
	return mDiffuse;
}
