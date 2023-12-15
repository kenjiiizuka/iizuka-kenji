#pragma once
#include "../../../System/RendererSystem/Renderer.h"
#include <string>
#include <unordered_map>
#include "../../../System/AssetSystem/IAsset.h"

/**
 * @class Texture
 * @brief ID3D11ShaderResourceViewをラップしたクラス
 */
class Texture : public IAsset
{
    /**--------------------------------------------------------------------------------------
    * テクスチャデータに対してプロバイダーのみがアクセスができるようにするためにフレンド申請
    --------------------------------------------------------------------------------------- */
    friend class TextureProvider;

public:
    /**
     * デフォルトコンストラクタ
     */
    Texture();

private:
   
    /**
     * @brief テクスチャリソースへのポインタです。
     */
    ID3D11ShaderResourceView* mResource;

public:
 
    /**
     * @brief テクスチャのシェーダーリソースビューを取得します。
     * @return テクスチャのシェーダーリソースビューへのポインタ。利用不可の場合はnullptr。
     */
    ID3D11ShaderResourceView* GetResource() { return mResource ? mResource : nullptr; }

    inline void SetResource(ID3D11ShaderResourceView* _resource);

    /**
    * @fn IsValid
    * @brief シェーダーリソースビューがあるかを返す
    * @bool true ある false なし
    */
    inline bool IsValid() const noexcept;

    /**
    * @fn GetAssetType
    * @brief アセットのタイプを返す
    * @detail typeidを使用して型判別をしている
    * @return const std::type_info&
    */
    inline virtual const std::type_info& GetAssetType() const noexcept;

private:
    /**
     * @brief 指定したファイル名のテクスチャが既に読み込まれているかをチェックします。
     * @param _fileName チェックするテクスチャのファイル名。
     * @return テクスチャが重複していない場合はtrue、重複している場合はfalse。
     */
    bool CheckDuplication(const std::string& _fileName);
  
};

//---------------- INLINES -------------

inline void Texture::SetResource(ID3D11ShaderResourceView* _resource)
{
    mResource = _resource;
}

inline bool Texture::IsValid() const noexcept
{
    return mResource;
}

inline const std::type_info& Texture::GetAssetType() const noexcept
{
    return typeid(Texture);
}
