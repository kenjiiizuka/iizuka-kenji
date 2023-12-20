/**
* @file StaticMeshObject.h
* @brief StaticMeshObjectクラスの定義
*/

#pragma once

//---------- INCLUDES ----------
#include "../GameObject.h"

/**
* @class StaticMeshObject
* @brief スティックメッシュオブジェクトの表示をするクラス
* @detail デフォルトでアウトラインが付き
*/
class StaticMeshObject : public GameObject
{
public:
    /**
    * デフォルトコンストラクタ
    */
    StaticMeshObject();

    /**
    * デストラクタ
    */
    ~StaticMeshObject();


    /**
    * @fn Init
    * @brief 初期化処理
    * @detail メッシュの読み込み、シェーダーのセットをしている
    * @param std::string_view (_filePath)
    * @return void
    */
    void Init(std::string_view _filePath);

    /**
    * @fn Update
    * @brief 更新処理
    * @detail StaticMeshのワールドマトリックスを設定している
    * @param const double (_deltaTime)
    * @return void
    */
    void Update(const double _deltaTime) override;
};