#pragma once
#include <vector>
#include <memory>

class VisualEntity;

/** ライティングシステムのインターフェースクラス */
class ILightingSystem
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	ILightingSystem();

	/**
	* デストラクタ
	*/
	virtual ~ILightingSystem();

public:
	/**
　　 * @fn Init
	 * @brief 初期化処理 ライティングに必要な,レンダーターゲット、デプスステンシル、シェーダーなどを作成する
　　 * @return void
　　*/
	virtual void Init() = 0;

	/**
　　 * @fn Lighting
	 * @brief シャドウマップを作成渡されたオブジェクトの影を反映したシャドウマップを作成し、影描画オブジェクトにセットする
	 * @param std::vector<std::weak_ptr<VisualEntity>> (_entitys)
	 * @param std::weak_ptr<VisualEntity> (_lightingEntity)
　　 * @return void
　　*/
	virtual void Lighting(std::vector<std::weak_ptr<VisualEntity>> _entitys, std::weak_ptr<VisualEntity> _lightingEntity) = 0;
};

