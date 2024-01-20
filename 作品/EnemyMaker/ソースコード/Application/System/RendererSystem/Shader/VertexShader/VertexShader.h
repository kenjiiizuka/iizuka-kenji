/**
* @file VertexShader.h
* @brief VertexShaderクラスの定義
*/

#pragma once

//----------- INCLUDES -------------
#include "../Shader.h"

/** 頂点データ */
struct Vertex
{
    DirectX::SimpleMath::Vector3 mPosition; /**< 頂点座標 */
    DirectX::SimpleMath::Vector3 mNormal;   /**< 法線 */
    DirectX::SimpleMath::Vector2 mTexCoord; /**< UV座標 */
    DirectX::SimpleMath::Vector4 mDiffuse;  /**< 頂点カラー */
};

/**
* @class VertexShader
* @brief 頂点シェーダークラス
*/
class VertexShader : public Shader
{
public:
    /**
    * 値の初期化
    */
    VertexShader(VisualEntity* _entity);
private:
    /** すべての頂点シェーダーを管理するMap */
    static std::unordered_map<std::string, ID3D11VertexShader*> mpVertexShaders;

    /** すべてのインプットレイアウトを管理するMap */
    static std::unordered_map<std::string, ID3D11InputLayout*>  mpInputLayouts;

    /** 現在割り当てられている頂点シェーダーの名前 */
    static std::string mCurrentBindShaderName;

    /** このシェーダーの参照 */
    ID3D11VertexShader* mpVertexShaderRef;

    /** このシェーダーのインプットレイアウト */
    ID3D11InputLayout* mpInputLayoutRef;
 
protected:
    /**
　　 * @fn MakeShader
     * @brief シェーダーの作成
     * @param void* (_pData)
     * @param UINT (_fileSize)
     * @param std::string (_shaderName)
　　 * @return HRESULT
　　*/
    HRESULT MakeShader(void* _pData, UINT _fileSize, std::string _shaderName) override;     // シェーダーの作成

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
     * @brief 定数バッファの更新(書き込み)
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
　　 * @fn GetVertexShader
     * @brief シェーダーのポインタを返す
　　 * @return ID3D11VertexShader*
　　*/
    inline ID3D11VertexShader* GetVertexShader() const;
};


//----------------------------- INLINES ---------------------------

inline ID3D11VertexShader* VertexShader::GetVertexShader() const
{ 
     return mpVertexShaderRef; 
}
