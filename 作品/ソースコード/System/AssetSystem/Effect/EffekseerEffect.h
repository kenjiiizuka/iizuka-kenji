/**
* @file EffekseerEffect.h
* @brief EffekseerEffect�N���X�̒�`
*/

#pragma once

//-------- INCLUDES ----------
#include "../IAsset.h"
#include <Effekseer.h>

/**
* @class EffekseerEffect
* @brief �G�t�F�N�V�A�̃G�t�F�N�g�����b�v�����N���X
*/
class EffekseerEffect : public IAsset
{
	/**-----------------------------------------------------------------------------
	* EffekseerEffectProvider����݂̂��ϐ��ɑ���ł���悤�ɂ��邽�߂Ƀt�����h�w��
	----------------------------------------------------------------------------- */
	friend class EffekseerEffectProvider;

public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	EffekseerEffect();

	/**
	* �f�X�g���N�^
	*/
	~EffekseerEffect();

private:
	/** �G�t�F�N�g�ւ̎Q�ƂƃG�t�F�N�g�n���h��  */
	Effekseer::EffectRef mEffect;

public:
	/**
	* @fn GetEffect
	* @brief �G�t�F�N�g��Ԃ�
	* @return std::pair<Effekseer::EffectRef, Effekseer::Handle>
	*/
	inline Effekseer::EffectRef GetEffect() const noexcept;

	/**
	* @fn GetAssetType
	* @brief �A�Z�b�g�̃^�C�v��Ԃ�
	* @detail typeid���g�p���Č^���ʂ����Ă���
	* @return const std::type_info&
	*/
	inline virtual const std::type_info& GetAssetType() const noexcept;

};

//------------ INLINES ----------

inline Effekseer::EffectRef EffekseerEffect::GetEffect() const noexcept
{
	return mEffect;
}

inline const std::type_info& EffekseerEffect::GetAssetType() const noexcept
{
	return typeid(EffekseerEffect);
}
