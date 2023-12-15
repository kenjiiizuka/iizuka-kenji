/**
* @file LightingSystem.h
* @brief LightingSystemクラスの定義
*/

#pragma once


//--------- INCLUEDES ----------
#include "ILightingSystem.h"

//-------- 前方宣言 ----------
class RenderTarget;
class DepthStencil;
class VisualEntity;
class DepthWritePixelShader;

/**
* @class LightingSystem
* @brief シャドウマップを作成し、描画をする
*/
class LightingSystem final : public ILightingSystem
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	LightingSystem();

	/**
    * デストラクタ
    */
	~LightingSystem();
	
private:
	/** ライティング用のレンダーターゲット */
	std::shared_ptr<RenderTarget> mDepthRenderTarget;

	/** ライティング用のデプスステンシルビュ- */
	std::shared_ptr<DepthStencil> mDepthStencil;

	/** 影描画用オブジェクト */
	std::shared_ptr<VisualEntity> mShadowEntity;

	/** シャドウマップ描画用オブジェクト */
	std::shared_ptr<VisualEntity> mShadowMapEntity;

	/** シャドウ書き込み用シェーダー */
	std::shared_ptr<DepthWritePixelShader> mWriteShadowShader;

	/** ライティング品質 */
	uint8_t mLightingLevel;

public:
	/**
　　 * @fn Init
	 * @brief 初期化処理 ライティングに必要な,レンダーターゲット、デプスステンシル、シェーダーなどを作成する
　　 * @return void
　　*/
	void Init() override;

	/**
　　 * @fn Lighting
	 * @brief シャドウマップを作成渡されたオブジェクトの影を反映したシャドウマップを作成し、影描画オブジェクトにセットする
	 * @param std::vector<std::weak_ptr<VisualEntity>> (_entitys)
	 * @param std::weak_ptr<VisualEntity> (_lightingEntity)
　　 * @return void
　　*/
	void Lighting(std::vector<std::weak_ptr<VisualEntity>> _entitys, std::weak_ptr<VisualEntity> _lightingEntity) override;

private:
	/**
　　 * @fn CreateShadowMapSprite_debug
	 * @brief デバッグ用のシャドウマップを描画するオブジェクト
　　 * @return void
　　*/
	void CreateShadowMapSprite_debug();
};
