/**
* @file StaticMeshComponent.h
* @brief StaticMeshComponentクラスの定義
*/

#pragma once
//----------- INCLUDES ---------
#include <string>
#include "../Component.h"
#include "../TransformComponent/Transform.h"

//------------ 前方宣言 -------------
class StaticMesh;

/**
* @class StaticMeshComponent
* @brief StaticMeshをラップして持ち、ゲームオブジェクト側で使いやすいようにしたComponent
*/
class StaticMeshComponent : public Component
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	StaticMeshComponent();

	/**
	* デストラクタ
	*/
	~StaticMeshComponent();

private:
	/** スタティックメッシュ */
	std::shared_ptr<StaticMesh> mStaticMesh;
	
	/** トランスフォーム */
	Transform mTransform;

public:
	/**
　　 * @fn Load
	 * @brief モデルの読み込み処理
	 * @param const std::string& (_filePath)
　　 * @return void
　　*/
	void Load(const std::string& _filepath);

	/**
	* @fn Update
	* @brief 更新処理
	* @return void
	*/
	void Update(const double _deltaTime) override;

	/**
　　 * @fn Draw
	 * @brief 描画処理
　　 * @return void
　　*/
	void Draw() override;

private:
	/**
	* @fn CalucStaticMeshWorldMatrix
	* @brief スタティックメッシュのワールド行列を計算する
	* @return void
	*/
	void CalucStaticMeshWorldMatrix();

public:
	/**
	* @fn GetStaticMesh
	* @brief スタティックメッシュを返す
	* @return std::shared_ptr<StaticMesh>
	*/
	inline std::shared_ptr<StaticMesh> GetStaticMesh();
};

//------------- INLINES --------------

inline std::shared_ptr<StaticMesh> StaticMeshComponent::GetStaticMesh()
{
	return mStaticMesh;
}