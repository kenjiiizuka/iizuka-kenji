/**
* @file  PlaneComponent.h
* @brief 板ポリを描画する機能を持つコンポーネントのクラスの定義
*/

#pragma once

//---------- INCLUDES -----------
#include <SimpleMath.h>
#include <string>
#include "../../../System/RendererSystem/RendererInformation.h"
#include "../Component.h"
#include "../../../System/AssetSystem/Texture/TextureAssetInclude.h"


//------- 前方宣言 ---------
class VisualEntity;


class PlaneComponent : public Component
{
public:
	/**
	* 値の初期化
	*/
	PlaneComponent();

private:
	/** オフセット */
	DirectX::SimpleMath::Vector3 mOffSet;

	/** 描画の実体 */
	std::shared_ptr<VisualEntity> mVisualEntity;

	/** ワールド行列 */
	DirectX::SimpleMath::Matrix mWorldMatrix;


public:
	/**
	 * @fn Init
	 * @brief 初期化処理
	 * @param DirectX::SimpleMath::Vector3 (_size) プレーン一つ一つの大きさ
	 * @param DirectX::SimpleMath::Vector3 (_offset) オフセット
	 * @param const std::string& (_textureFilePath) テクスチャのファイルパス
	 * @param const RendererInf::Layer (_registerLayer)
	 * @param const bool (_isLighting )
	 * @return void
	*/
	void Init(DirectX::SimpleMath::Vector3 _size, DirectX::SimpleMath::Vector3 _offset, const std::string& _textureFilePath, const RendererInf::Layer _registerLayer = RendererInf::Layer_Object, const bool _isLighting = false);

	/**
	 * @fn Draw
	 * @brief 描画処理
	 * @return void
	*/
	void Draw() override;

	/**
	* @fn SetTexture
	* @brief テクスチャのセッター
	* @param const Texture (_texture)
	* @return void
	*/
	void SetTexture(const Texture _texture);

	/**
	* @fn SetWorldMatrix
	* @brief ワールド行列のセッター
	* @param const DirectX::SimpleMath::Matrix& (_matrix)
	* @return void
	*/
	void SetWorldMatrix(const DirectX::SimpleMath::Matrix& _matrix) noexcept;

	inline std::shared_ptr<VisualEntity> GetVisualEntity() const;

};

//----------------- INLINES --------------

inline std::shared_ptr<VisualEntity> PlaneComponent::GetVisualEntity() const
{
	return mVisualEntity;
}