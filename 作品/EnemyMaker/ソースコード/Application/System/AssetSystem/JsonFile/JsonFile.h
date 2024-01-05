/**
* @file JsonFile.h
* @brief JsonFileクラスの定義
*/
#pragma once

//---------- INCLUDES -----------
#include "../IAsset.h"
#include <nlohmann/json.hpp>
#include <fstream>

/**
* @class JsonFile
* @brief Jsonをラップしたクラス
* @detail Jsonの機能が十分に便利なので単純にラップだけして、参照を取得できるようにしている
*         読み込み時などにAssetとして管理するためにクラス化している
*/
class JsonFile : public IAsset
{
    /**-----------------------------------------------------------
    * JsonFileProviderからのみデータをセットするためにフレンド指定
    -------------------------------------------------------------*/
    friend class JsonFileProvider;

public:
    /**
    * デフォルトコンストラクタ
    */
    JsonFile();

    /**
    * デストラクタ
    */
    ~JsonFile();

private:
    /** Jsonオブジェクト */
    nlohmann::json mJson;

    /** ファイルパス */
    std::string mFilePath;

public:
    /**
    * @fn WriteFile
    * @brief jsonオブジェクトの内容をファイルに書き込み
    * @return void
    */
    void WriteFile() const;

    /**
    * @fn GetAssetType
    * @brief アセットのタイプを返す
    * @detail typeidを使用して型判別をしている
    * @return const std::type_info&
    */
    inline virtual const std::type_info& GetAssetType() const noexcept;

    /**
    * @fn GetJson
    * @brief Jsonオブジェクトの参照を返す
    * @return void
    */
    inline nlohmann::json& GetJson() noexcept;

};

//--------- INLINES ----------

inline const std::type_info& JsonFile::GetAssetType() const noexcept
{
    return typeid(JsonFile);
}

inline nlohmann::json& JsonFile::GetJson() noexcept
{
    return mJson;
}
