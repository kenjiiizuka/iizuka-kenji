/**
* @file  Field.h
* @brief Fieldクラスの定義
*/

#pragma once

//--------- INCLUDES ----------
#include "../GameObject.h"


//--------- 前方宣言 ---------
class StaticMeshObject;

/**
* @class Field 
* @brief フィールドオブジェクト
*/
class Field : public GameObject
{
public:
    /**
    * コンストラクタ
    */
    Field();

private:  
    /** フィールド配置オブジェクト */
    std::vector<std::weak_ptr<StaticMeshObject>> mProps;

    /** 頂点の数 */
    const int mVertexNum = 4;

    /** プレーンの数 奥行 */
    const int mNumDepth = 30;

    /** プレーンの数 横 */
    const int mNumWidth = 30;

    /** プレーンのサイズ */
    DirectX::SimpleMath::Vector3 mPlaneSize;

public:
    /**
     * @fn Init
     * @brief 初期化処理
     * @return void
    */
    void Init() override;

    /**
    * @fn Update
    * @brief 更新処理
    * @param const double (_deltaTime)
    * @return void
    */
    void Update(const double _deltaTime) override;
};
