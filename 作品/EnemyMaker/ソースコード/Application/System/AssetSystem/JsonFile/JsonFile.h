/**
* @file JsonFile.h
* @brief JsonFile�N���X�̒�`
*/
#pragma once

//---------- INCLUDES -----------
#include "../IAsset.h"
#include <nlohmann/json.hpp>
#include <fstream>

/**
* @class JsonFile
* @brief Json�����b�v�����N���X
* @detail Json�̋@�\���\���ɕ֗��Ȃ̂ŒP���Ƀ��b�v�������āA�Q�Ƃ��擾�ł���悤�ɂ��Ă���
*         �ǂݍ��ݎ��Ȃǂ�Asset�Ƃ��ĊǗ����邽�߂ɃN���X�����Ă���
*/
class JsonFile : public IAsset
{
    /**-----------------------------------------------------------
    * JsonFileProvider����̂݃f�[�^���Z�b�g���邽�߂Ƀt�����h�w��
    -------------------------------------------------------------*/
    friend class JsonFileProvider;

public:
    /**
    * �f�t�H���g�R���X�g���N�^
    */
    JsonFile();

    /**
    * �f�X�g���N�^
    */
    ~JsonFile();

private:
    /** Json�I�u�W�F�N�g */
    nlohmann::json mJson;

    /** �t�@�C���p�X */
    std::string mFilePath;

public:
    /**
    * @fn WriteFile
    * @brief json�I�u�W�F�N�g�̓��e���t�@�C���ɏ�������
    * @return void
    */
    void WriteFile() const;

    /**
    * @fn GetAssetType
    * @brief �A�Z�b�g�̃^�C�v��Ԃ�
    * @detail typeid���g�p���Č^���ʂ����Ă���
    * @return const std::type_info&
    */
    inline virtual const std::type_info& GetAssetType() const noexcept;

    /**
    * @fn GetJson
    * @brief Json�I�u�W�F�N�g�̎Q�Ƃ�Ԃ�
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
