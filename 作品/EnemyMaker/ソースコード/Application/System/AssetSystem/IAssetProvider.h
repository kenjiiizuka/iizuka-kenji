#pragma once

/**
* @file IAssetProvider.h
* @brief IAssetProvider�N���X�̒�`
*/

//---------- INCLUDES ---------
#include <string>
#include <memory>
#include <unordered_map>
#include <iostream>
#include "IAsset.h"

//----------- �O���錾 --------
class AssetHandle;


/**
* @class IAssetProvider
* @brief �A�Z�b�g�v���o�C�_�[�̃C���^�[�t�F�[�X�N���X
*/
class IAssetProvider
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	IAssetProvider()
	{
		// �����Ȃ�
	}

	/**
	* �f�t�H���g�f�X�g���N�^
	*/
	virtual ~IAssetProvider()
	{
		// �����Ȃ�
	}

private:
	/** �L���b�V���}�b�v <�t�@�C���p�X, �A�Z�b�g> */
	std::unordered_map<std::string, std::shared_ptr<IAsset>> mCacheMap;

protected:
	/** �ǂݍ��ݎ��̐ݒ� */
	std::vector<char> mLoadSetting;

public:
	/**
	* @fn GetProviderType
	* @brief �v���o�C�^�[��Type��Ԃ�
	* @detail typeid���g�p���ăv���o�C�^�[�̌^��Ԃ��Ă���
	* @return std::type_info �v���o�C�_�[�̌^
	*/
	inline virtual const std::type_info& GetProviderType() const = 0;

	/**
	* @fn Provide
	* @brief �A�Z�b�g��ǂݍ��݊֐�
	* @param const std::string& (_filePath)
	* @return std::shared_ptr<AssetHandle>
	*/
	virtual std::shared_ptr<AssetHandle> Provide(const std::string& _filePath);

	/**
	 * @fn SettingBase
	 * @brief �ǂݍ��ݎ��̃Z�b�e�B���O������
	 * @detail �ϒ������œn���ꂽ�l���R�s�[���Ă���
	 *         ���ۂɐݒ��l���Ƃ��Ď��̂͊e�v���o�C�_�[���s���Ă���
	 * @param const SettingParam... (_setting)
	 * @return void
	*/
	template<class... SettingParam>
	inline void SettingBase(const SettingParam... _setting);

protected:
	/**
	* @fn Setting
	* @brief �Z�b�e�B���O�̃f�[�^�����ۂɎg�p�ł���l�ɕϊ����Ă���
	* @return void
	*/
	virtual void Setting() = 0;

	/**
	* @fn LoadBase
	* @brief �A�Z�b�g�ǂݍ��݂����ۂɎ��s���鏈��
	* @detail �ǂݍ��݂���������ƃL���b�V���}�b�v�ɓo�^����
	* @param const std::string& _filePath
	*/
	virtual std::shared_ptr<IAsset> LoadBase(const std::string& _filePath);

	/**
	* @fn LoadBase
	* @brief �A�Z�b�g�ǂݍ��݂����ۂɎ��s���鏈��
	* @detail �ǂݍ��݂���������ƃL���b�V���}�b�v�ɓo�^����
	* @param const std::string& _filePath
	*/
	virtual std::shared_ptr<IAsset> Load(const std::string& _filePath) const = 0;

private:
	/**
	* @fn AddCacheMap
	* @brief �ǂݍ��񂾃A�Z�b�g���L���b�V���}�b�v�ɓo�^
	* @detail �L�[�̏d��������Γo�^���Ȃ�
	* @param const std::string& (_filePath) �L�[�Ƃ��Ĉ���
	* @param std::shared_ptr<IAsset> (_asset)
	*/
	inline void AddCacheMap(const std::string& _filePath, std::shared_ptr<IAsset> _asset);

	/**
	* @fn GetAssetFromCacheMap
	* @brief �L���b�V���}�b�v����A�Z�b�g�擾����
	* @param const std::string& (_cacheKey) 
	* @param std::shared_ptr<IAsset>
	*/
	inline std::shared_ptr<IAsset> GetAssetFromCacheMap(const std::string& _cacheKey);
};

//----------- INLINES ------------

inline void IAssetProvider::AddCacheMap(const std::string& _filePath, std::shared_ptr<IAsset> _asset)
{
	// �L���b�V���}�b�v�ɓo�^
	bool success = mCacheMap.try_emplace(_filePath, _asset).second;

	if (!success)
	{
		std::cout << _filePath << "�͂��łɃL���b�X�ɓo�^�ς݂ł�" << std::endl;
	}
}

inline std::shared_ptr<IAsset> IAssetProvider::GetAssetFromCacheMap(const std::string& _cacheKey)
{
	// �L���b�V���}�b�v�Ɏw�肳�ꂽ�L�[�����邩
	if (mCacheMap.contains(_cacheKey))
	{
		return mCacheMap.at(_cacheKey);
	}

	std::cout << _cacheKey << "�̓L���b�V���}�b�v�ɓo�^����Ă��܂���" << std::endl;

	return nullptr;
}

template<class ...SettingParam>
inline void IAssetProvider::SettingBase(SettingParam ..._setting)
{
	// �ǂݍ��ݐݒ���R�s�[����
	size_t settingSize = sizeof...(_setting);
	mLoadSetting.resize(settingSize);
	std::memcpy(mLoadSetting.data(), &_setting..., settingSize);

	// ���ۂɎg����l�ɕϊ�����
	Setting();
}
