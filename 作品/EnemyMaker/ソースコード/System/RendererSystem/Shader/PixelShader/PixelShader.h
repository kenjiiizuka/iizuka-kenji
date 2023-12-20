/**
* @file PixelShader.h
* @brief PixelShaderクラスの定義
*/

#pragma once

//---------- INCLUDES ---------
#include "../Shader.h"

//--------- 前方宣言 -----------
class Texture;
class AssetHandle;

/**
* @class PixelShader
* @brief ピクセルシェーダーの読み込み、バッファーのセットなどをする
* @detail GPUへのピクセルシェーダーのセット
*         各バッファーのセットなどを行う
*/
class PixelShader : public Shader
{
public:
    /**
    * 値の初期化
    */
    PixelShader(VisualEntity* _entity);

private:
    /** 読み込んだピクセルシェーダーを管理するためのMap */
    static std::unordered_map<std::string, ID3D11PixelShader*> mpPixelShaders;

    /** 現在割り当てられているシェーダーの名前 */
    static std::string mCurrentBindShaderName;

    /** 自身が扱うシェーダーのポインタ */
    ID3D11PixelShader* mPixelShaderRef;  

protected:
    /** テクスチャなしオブジェクト用のテクスチャ */
    static std::shared_ptr<AssetHandle> mWhiteTexture;

protected:
    /**
　　 * @fn MakeShader
     * @brief シェーダーの作成
     * @param void* (_pData)
     * @param UINT (_fileSize)
     * @param std::string (_shaderName)
　　 * @return HRESULT
　　*/
    HRESULT MakeShader(void* _pData, UINT _fileSize, std::string _shaderName) override;

    /**
　　 * @fn MakeBuffer
     * @brief 定数バッファの作成
     * @param void* (_pData)
     * @param UINT (_fileSize)
　　 * @return HRESULT
　　*/
    HRESULT MakeBuffer(void* _pData, UINT _fileSize) override;

    /**
　　 * @fn CheckDuplication
     * @brief 二重読み込みチェック
     * @param std::string (_shaderName)
　　 * @return bool
　　*/
    bool CheckDuplication(std::string _shaderName) override; 

public:
    /**
　　 * @fn Uninit
     * @brief 終了処理 シェーダーの解放
　　 * @return void
　　*/
    void Uninit() override;

    /**
　　 * @fn UpdateBuffer
     * @brief 定数バッファの更新
     * @param uint8_t (_dataID)
　　 * @return void
　　*/
    virtual void UpdateBuffer(uint8_t _dataID);

    /**
　　 * @fn BindShader
     * @brief シェーダーの割り当て
　　 * @return void
　　*/
    void BindShader() override;           
    
    /**
　　 * @fn SetTexture
     * @brief 指定したスロットにテクスチャをセットする
　　 * @return void
　　*/
    void SetTexture(UINT _slot, ID3D11ShaderResourceView* _texture) override;

    /**
　　 * @fn SetSampler
     * @brief 指定したスロットにサンプラーステートをセットする
     * @param UINT (_slot)
     * @param ID3D11SamplerState* (_samplerState)
　　 * @return void
　　*/
    void SetSampler(UINT _slot, ID3D11SamplerState* _samplerState) override;

    /**
　　 * @fn GetPixelShader
     * @brief シェーダーのポインタを返す
　　 * @return ID3D11PixelShader* 
　　*/
    inline ID3D11PixelShader* GetPixelShader() const; 
};

//------------------- INLINES -----------------

inline ID3D11PixelShader* PixelShader::GetPixelShader() const
{
    return mPixelShaderRef;
}

