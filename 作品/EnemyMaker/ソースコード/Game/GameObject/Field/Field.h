#pragma once
#include "../GameObject.h"


/**
* @file  Field.h
* @brief Fieldクラスの定義
*/

class VertexShaderComponent;
class PixelShaderComponent;
class TextureComponent;

class Field :
    public GameObject
{
public:
    /**
    *
    * 値の初期化
    *
    */
    Field();

private:
    /** 頂点シェーダーコンポーネント */
    std::shared_ptr<VertexShaderComponent> mpVertexShader;

    /** ピクセルシェーダーコンポーネント */
    std::shared_ptr <PixelShaderComponent>  mpPixelShader;

    /** テクスチャ */
    std::shared_ptr <TextureComponent>      mpTexture;
   
    /** 頂点の数 */
    const int mVertexNum = 4;

    /** プレーンの数 奥行 */
    const int mNumDepth = 15;

    /** プレーンの数 横 */
    const int mNumWidth = 15;

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
     * @fn Draw
     * @brief 描画処理
     * @return void
    */
    void Draw() override;
};

