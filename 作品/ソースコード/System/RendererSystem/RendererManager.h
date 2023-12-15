#pragma once
#include <list>
#include <vector>
#include <memory>
#include "RendererInformation.h"
#include "../Singleton.h"

//------------------ 前方宣言 -------------------
class VisualEntity;
class ILightingSystem;

using EntityLayer = std::vector<std::vector<std::weak_ptr<VisualEntity>>>;

/** オブジェクトのレンダリング、ライティングをする */
class RendererManager final : public Singleton<RendererManager>
{
	/**----------------------------------------------------------------------------------------------
	* 基底クラスのSingletonクラスからコンストラクタと、デストラクタにアクセスするために必要であり
	* クラス外から生成、破棄できないようにするためにフレンド指定する
	------------------------------------------------------------------------------------------------*/
	friend Singleton<RendererManager>; 

private:	
	/**
	* 隠しコンストラクタ
	*/
	RendererManager();

	/**
	* 隠しデストラクタ
	*/
	~RendererManager();

	/**
	* コピーコンストラクタ 
	* コピー禁止のために = delete 指定
	* 
	* @param const RendererManager& (_from) コピー元インスタンス
	*/
	RendererManager(const RendererManager&) = delete;

	/**
	* コピー代入演算子のオーバーロード
	* 代入禁止のために = delete 指定
	*
	* @param const RendererManager& (_from) コピー元インスタンス
	*/
	void operator=(const RendererManager&) = delete;

private:
	/** 描画オブジェクトリスト */
	EntityLayer mEntityLayer;

	/** ライティングをするか */
	bool mbLighting;
	
	/** ライティングシステム */
	std::shared_ptr<ILightingSystem> mLightingSystem;

public:
	/**
　　 * @fn Init
	 * @brief 初期化処理
　　 * @return void
　　*/
	void Init();

	/**
　　 * @fn UnInit
	 * @brief 終了処理
　　 * @return void
　　*/
	void Uninit();

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

	/**
　　 * @fn　RegisterEntity
　　 * @brief 描画オブジェクトの登録
	 * @param std::shared_ptr<VisualEntity> (_entity) 描画オブジェクト
	 * @param RendererInf::Layer (_layer) 登録するレイヤー
　　 * @return bool true 登録 false 登録失敗
　　*/
	bool RegisterEntity(std::shared_ptr<VisualEntity> _entity, RendererInf::Layer _layer);

public:
	/**
　　 * @fn SwitchLighting
	 * @brief ライティングをするかしないか切り替える
	 * @param bool (_active)
　　 * @return void
　　*/
	inline void SwitchLighting(bool _active);

};

//------------- INLINES -----------------

inline void RendererManager::SwitchLighting(bool _active)
{
	mbLighting = _active;
}