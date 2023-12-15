﻿#pragma once
#include <SimpleMath.h>
#include <string>
#include "../Component.h"
#include "../../../System/RendererSystem/Shader/Shader.h"
#include "../../../System/RendererSystem/Renderer.h"

/**
* @file  PlaneComponent.h
* @brief 板ポリを描画する機能を持つコンポーネントのクラスの定義
*/

class VertexShader;
class PixelShader;
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

public:
	/**
	 * @fn Init
	 * @brief 初期化処理
	 * @param DirectX::SimpleMath::Vector3 (_size) プレーン一つ一つの大きさ
	 * @param DirectX::SimpleMath::Vector3 (_offset) オフセット
	 * @param const std::string& (_textureFilePath) テクスチャのファイルパス
	 * @param const bool (_isLighting) ライティングするかどうか 
	 * @return void
	*/
	void Init(DirectX::SimpleMath::Vector3 _size, DirectX::SimpleMath::Vector3 _offset, const std::string& _textureFilePath, const bool _isLighting = true);

	/**
	 * @fn Uninit
	 * @brief 終了処理
	 * @return void
	*/
	void Uninit() override;

	/**
	 * @fn Draw
	 * @brief 描画処理
	 * @return void
	*/
	void Draw() override;


	inline std::shared_ptr<VisualEntity> GetVisualEntity() const;
};

//----------------- INLINES --------------

inline std::shared_ptr<VisualEntity> PlaneComponent::GetVisualEntity() const
{
	return mVisualEntity;
}