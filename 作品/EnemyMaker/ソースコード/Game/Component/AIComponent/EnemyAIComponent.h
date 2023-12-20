/**
* @file EnemyAIComponent.h
* @brief EnemyAIComponentクラスの定義
*/

#pragma once

//--------- INCLUDES ---------
#include "../Component.h"

//--------- 前方宣言 ---------
class EnemyAIController;
class EnemyBase;

//--------- コンセプト ----------
template<class AIController>
concept DerivedAIController = std::derived_from<AIController, EnemyAIController>;

/**
* @class EnemyAIComponent
* @brief Enemyを制御するEnemy専用のクラス
*/
class EnemyAIComponent : public Component
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	EnemyAIComponent();

	/**
	* デストラクタ
	*/
	~EnemyAIComponent();

private:
	/** AIコントローラー*/
	std::shared_ptr<EnemyAIController> mAIController;

	/** AIを実行するか */
	bool mbRunAI;

public:
	/**
	* @fn ControllerInitialize
	* @brief AIControllerの初期化
	* @return void
	*/
	void ControllerInitialize();

	/**
	* @fn Update
	* @brief 更新処理
	* @return void
	*/
	void Update(const double _deltaTime) override;

	/**
	* @fn CreateAIController
	* @brief AIController作成関数
	*/
	template<DerivedAIController AIController>
	inline void CreateAIController(EnemyBase* _controlledeEnemy);

	/**
	* @fn StopAI
	* @brief AIによる制御を止める
	* @return void
	*/
	void StopAI();

	/**
	* @fn RunAI
	* @brief AI制御を開始する
	* @return void 
	*/
	void RunAI();

	/**
	* @fn SetTakenDamage
	* @brief くらったダメージをセットする
	* @param const float (_takenDamage)
	* @return void
	*/
	void SetTakenDamage(const float _takenDamage);

	/**
	* @fn GetAIController
	* @brief AIControllerを返す
	* @return std::weak_ptr<EnemyAIController>
	*/
	inline std::weak_ptr<EnemyAIController> GetAIController() const noexcept;
};

//-------- INLINES -----------

template<DerivedAIController AIController>
inline void EnemyAIComponent::CreateAIController(EnemyBase* _controlledEnemy)
{
	mAIController = std::make_shared<AIController>(_controlledEnemy);
}

inline std::weak_ptr<EnemyAIController> EnemyAIComponent::GetAIController() const noexcept
{
	return mAIController;
}
