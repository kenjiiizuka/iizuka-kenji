/**
* @file AssetHandle.h
* @brief AssetHandle�N���X�̒�`
*/

#pragma once

//-------- INCLUDES ---------
#include <memory>


//-------- �O���錾 ---------
class IAsset;
class IAssetProvider;

/**
* @class AssetHandle
* @brief �A�Z�b�g�̃|�C���^�����b�v����
*/
class AssetHandle
{
	/**--------------------------------------------------------------------------------------
	* �A�Z�b�g�v���o�C�_�[����̂݃n���h���ɃA�Z�b�g�̃|�C���^�������������̂Ńt�����h�w��
	* �Q�b�^�[��p�ӂ���ƁA�n���h���ɐV�����|�C���^���Z�b�g����Ă��܂�
	*/
	friend IAssetProvider;

public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	AssetHandle();

	/**
	* �f�t�H���g�f�X�g���N�^
	*/
	~AssetHandle();
	
private:
	/** �A�Z�b�g�ւ̃|�C���^ */
	std::weak_ptr<IAsset> mAsset;

	/** �A�Z�b�g�����[�h�����v���o�C�_�[ */
	IAssetProvider* mOwnerProvider;

public:
	/**
	* @fn IsValid
	* @brief ���̃n���h�����w���Ă���A�Z�b�g���g�p�\���Ԃ�
	* @return bool true �g�p�\�@false : �g�p�s��
	*/
	inline bool IsValid() const;

	/**
	* @fn Get
	* @brief �A�Z�b�g�ւ̎Q�Ƃ�Ԃ�
	*/
	template<class AssetType>
	inline AssetType& Get();
	
	/**
	* @fn Get
	* @brief �A�Z�b�g�ւ̎Q�Ƃ�Ԃ�
	*/
	inline IAsset& Get();

};

//----------- INLINES -----------

inline bool AssetHandle::IsValid() const
{
	if (mAsset.lock())
	{
		return true;
	}
	return false;
}

template<class AssetType>
inline AssetType& AssetHandle::Get()
{
	AssetType& asset = *std::dynamic_pointer_cast<AssetType>(mAsset.lock());
	return asset;
}

inline IAsset& AssetHandle::Get()
{
	return *mAsset.lock();
}
