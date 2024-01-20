/**
* file DebugScene.h
* @brief DebugSceneクラスの定義
*/

#pragma once

//----------- INCLUDES ------------
#include "../Scene.h"

/**
* @class DebugScene 
* @brief デバッグ用のシーン
*/
class DebugScene : public Scene
{
public:
    /**
    * @fn Initialize
    * @brief 初期化処理
    * @return void
    */
    void Initialize() override;

    /**
    * @fn Update
    * @brief 更新処理
    * @return void
    */
    void Update() override;

    /**
    * @fn Uninitialize
    * @brief 終了処理
    * @return void
    */
    void Uninitialize() override; 
};

