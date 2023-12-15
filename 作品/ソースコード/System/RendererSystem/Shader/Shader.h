/**
* @file Shader.h
* @brief Shaderクラス
*/

#pragma once

//------- INCLUDES ---------
#include <unordered_map>
#include <string>
#include <vector>
#include "../Renderer.h"

//------- 前方宣言 ---------
class VisualEntity;

/** シェーダーの基底クラス リフレクション機能を使いシェーダーの読み込み、定数バッファの作成をする */
class Shader
{
public:
    /**
    * 値の初期化
    */
    Shader(VisualEntity* _entity);

protected:
    /** このシェーダーが使用する定数バッファ */
    static std::unordered_map<std::string, std::vector<ID3D11Buffer*>> mBuffers;

    /** このシェーダーが何個の描画オブジェクトから使用されているかのカウント */
    static std::unordered_map<std::string, int>  mRefCounts;

    /** ビュープロジェクション変換行列の定数バッファ */ 
    static ID3D11Buffer* mpView_ProjectionBuffer; 

    /** ワールド変換行列の定数バッファ */
    static ID3D11Buffer* mpWorldBuffer;


protected:
    /** このシェーダーを描画のオブジェクト */
    VisualEntity* mVisualEntity;

    /** シェーダーの名前 (ファイルパスと同じにしています) */
    std::string mShaderName = "None";

    /** このシェーダが使う定数バッファへのポインタ */
    std::vector<ID3D11Buffer*>      mpBufferRef;              // このシェーダーが使う定数バッファへのポインタ

    /** シャドウマップに影を書き込むか */
    bool mbIsDropShadow;

protected:
    /**
　　 * @fn MakeBuffer
     * @brief 定数バッファ作成関数 リフレクションで読み取ったデータから定数バッファを作成する
     * @param void* (_pData) 
     * @param UINT (_fileSize)
　　 * @return HRESULT 
　　*/
    virtual HRESULT MakeBuffer(void* _pData, UINT _fileSize);

    /**
　　 * @fn MakeShader
     * @brief シェーダーを作成する
     * @param void* (_pData)
     * @param UINT (_fileSize)
     * @param std::string (_shaderName)
　　 * @return HRESULT
　　*/
    virtual HRESULT MakeShader(void* _pData, UINT _fileSize, std::string _shaderName) = 0;

    /**
　　 * @fn CheckDuplication
     * @brief 二重読み込みチェック
     * @param std::string (_shaderName)
　　 * @return bool
　　*/
    virtual bool CheckDuplication(std::string _shaderName) = 0;      

public:
    /**
　　 * @fn LoadWithShaderReflection
     * @brief リフレクション機能を使用してシェーダー読み込み
     * @param std::string (_shaderName)
　　 * @return bool
　　*/
    bool LoadWithShaderReflection(std::string _shaderName);                                                  

    /**
　　 * @fn Uninit
     * @brief 終了処理 定数バッファの解放 参照カウントの減算
　　 * @return void
　　*/
    virtual void Uninit(); 

    /**
　　 * @fn WriteBuffer
     * @brief 指定したSlotの定数バッファに値を書き込む
     * @param UINT (_slot) 書き込みたい定数バッファのスロット
     * @param void* (_pData) 書き込むデータ
　　 * @return void
　　*/
    virtual void WriteBuffer(UINT _slot, void* _pData);

    /**
　　 * @fn BindShader
     * @brief シェーダー割り当て
　　 * @return void
　　*/
    virtual void BindShader() = 0;

    /**
　　 * @fn SetTexture
     * @brief 指定されたスロットにテクスチャをセットする
     * @param UINT (_slot)
     * @param ID3D11ShaderResourceView* (_resourceView)
　　 * @return void
　　*/
    virtual void SetTexture(UINT _slot, ID3D11ShaderResourceView* _resourceView) = 0;

    /**
　　 * @fn SetSampler
     * @brief 指定されたスロットにサンプラーステートをセットする
     * @param UINT (_slot)
     * @param ID3D11SamplerState* (_smaplerState)
　　 * @return void
　　*/
    virtual void SetSampler(UINT _slot, ID3D11SamplerState* _smaplerState) = 0;                 // サンプラーステートセット

    /**
　　 * @fn SetVisualEntity
     * @brief このシェーダーを使用するVisualEntityのセット関数
     * @param VisualEntity* (_entity)
　　 * @return void
　　*/
    inline void SetVisualEntity(VisualEntity* _entity);

    /**
    * @fn IsDropShadow
    * @brief 落ち影を出すかださないかを返す関数
    * @return bool true 影を出す false 出さない
    */
    inline bool IsDropShadow() const noexcept;

    /**
　　 * @fn WriteView_ProjectionMatrix
     * @brief ViewとProjection行列の値を定数バッファに書き込む
     * @param void* (_view_ProjectionMatrix)
　　 * @return void
　　*/
    static void WriteView_ProjectionMatrix(void* _view_ProjectionMatrix);

    /**
　　 * @fn WriteWorldMatrix
     * @brief World行列を定数バッファに書き込む関数
     * @param void* (_view_ProjectionMatrix)
　　 * @return void
　　*/
    static void WriteWorldMatrix(void* _worldMatrix);
};

//----------- INLINES -----------------

inline void Shader::SetVisualEntity(VisualEntity* _entity)
{
    mVisualEntity = _entity;
}

inline bool Shader::IsDropShadow() const noexcept
{
    return mbIsDropShadow;
}
