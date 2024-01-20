/**
* @file AssetManager.h
* @brief AssetManager�N���X�̒�`
*/

#pragma once

//---------- INCLUDES -----------
#include <memory>
#include <vector>
#include <iostream>
#include "../Singleton.h"
#include "IAssetProvider.h"

//--------- �O���錾 ------------
class AssetHandle;

//--------- �R���Z�v�g ----------
template<class Provider>
concept DerivedProvider = std::derived_from<Provider, IAssetProvider>;

/**
* @class AssetManager
* @brief �A�Z�b�g�Ɋւ���C���^�[�t�F�[�X���V�X�e���ƃ��[�U�[�ɒ񋟂���N���X 
*/
class AssetManager final : public Singleton<AssetManager>
{
	/**----------------------------------------------------------------------------------------------
	* ���N���X��Singleton�N���X����R���X�g���N�^�ƁA�f�X�g���N�^�ɃA�N�Z�X���邽�߂ɕK�v�ł���
	* �N���X�O���琶���A�j���ł��Ȃ��悤�ɂ��邽�߂Ƀt�����h�w�肷��
	------------------------------------------------------------------------------------------------*/
	friend class Singleton<AssetManager>;

private:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	AssetManager()
	{
		// �����Ȃ�
	}

	/**
	* �f�t�H���g�f�X�g���N�^
	*/
	~AssetManager()
	{
		// �����Ȃ�
	}

	/**
	* �R�s�[�R���X�g���N�^
	* �R�s�[�֎~�̂���delete�w��
	*/
	AssetManager(const AssetManager&) = delete;

	/**
	* = ���Z�q�̃I�[�o�[���[�h
	* ����֎~�̂���delete�w��
	*/
	void operator=(const AssetManager&) = delete;

	/** �o�^���ꂽ�A�Z�b�g�v���o�C�_�[ */
	std::vector<std::shared_ptr<IAssetProvider>> mProviders;

public:
	/**
	* @fn �A�Z�b�g�v���o�C�_�[�̓o�^
	* @brief �^�Ŏw�肳�ꂽ�v���o�C�_�[�̓o�^������
	* @detail �o�^�̑O�ɂ��łɓo�^����Ă��Ȃ����`�F�b�N������A��d�o�^�͋N���Ȃ�
	* @return void
	*/
	template<DerivedProvider Provider>
	inline void RegisterAssetProvider();

	/**
	* @fn Load
	* @brief �A�Z�b�g�ǂݍ��݊֐�
	* @param const std::string& (_filePath)
	* @param const Setting... (_setting)
	*/
	template<DerivedProvider Provider>
	inline std::shared_ptr<AssetHandle> Load(const std::string& _filePath);

	template<DerivedProvider Provider, class... Setting>
	inline void ProviderSetting(const Setting... _setting);
private:
	/**
	* @fn GetProvider
	* @brief �v���o�C�_�[�̎擾�֐�
	* @return std::shared_ptr<Provider>
	*/
	template<DerivedProvider Provider>
	inline std::shared_ptr<Provider> GetProvider() const;

};

//----------- INLINES --------------
template<DerivedProvider Provider>
inline void AssetManager::RegisterAssetProvider()
{
	// ���ݓo�^����Ă���v���o�C�_�[�d�����Ă��Ȃ����m�F
	for (std::shared_ptr<IAssetProvider> provider : mProviders)
	{	
		if (provider->GetProviderType() == typeid(Provider))
		{
			std::cout << "���̃v���o�C�_�[�͂��łɓo�^����Ă��܂��B" << typeid(Provider).name() << std::endl;
			return;
		}
	}

	// �v���o�C�_�[�̍쐬
	mProviders.emplace_back(std::make_shared<Provider>());
}

template<DerivedProvider Provider>
inline  std::shared_ptr<AssetHandle> AssetManager::Load(const std::string& _filePath)
{
	// �v���o�C�_�[�̎擾
	std::shared_ptr<Provider> provider = GetProvider<Provider>();

	// �v���o�C�_�[���擾�ł��Ă��邩�m�F
	if (!provider)
	{
		return nullptr;
	}

	// �v���o�C�_�[����A�Z�b�g�ǂݍ���
	std::shared_ptr<AssetHandle> newHandle = provider->Provide(_filePath);

	return newHandle;
}

template<DerivedProvider Provider, class ...Setting>
inline void AssetManager::ProviderSetting(const Setting... _setting)
{
	// �v���o�C�_�[���擾
	std::shared_ptr<Provider> provider = GetProvider<Provider>();

	// �v���o�C�_�[�����݂��邩
	if (!provider)
	{
		return;
	}
	provider->SettingBase(_setting...);
}

template<DerivedProvider Provider>
inline std::shared_ptr<Provider> AssetManager::GetProvider() const
{
	// �w�肳�ꂽ�v���o�C�_�[��T��
	for (std::shared_ptr<IAssetProvider> provider : mProviders)
	{
		if (provider->GetProviderType() == typeid(Provider))
		{
			return std::static_pointer_cast<Provider>(provider);
		}
	}

	std::cout << "�w�肳�ꂽ�v���o�C�_�[�͓o�^����Ă��܂���" << typeid(Provider).name() << std::endl;
	return nullptr;
}
