/**
* @file EffectSystem.h
* @brief EffectSystem�N���X�̒�`
*/
#pragma once

//--------- INCLUDES ---------
#include "../Singleton.h"
#include <EffekseerRendererDX11.h>
#include <Effekseer.h>
#include <SimpleMath.h>
#include "../../System/AssetSystem/Effect/EffekseerEffect.h"


/**
* @class EffectSystem
* @brief �G�t�F�N�g�V�X�e���N���X
* @detail Effekseer���g�p���A�G�t�F�N�g�̃V�X�e����񋟂���
*         Effekseer�̏������A�G�t�F�N�g�̍Đ�������
*/
class EffectSystem : public Singleton<EffectSystem>
{
	/**-----------------------------------------------------------------------------
	* Singleton<EffectSystem>����̂ݐ����A�j�����ł���悤�ɂ��邽�߂Ƀt�����h�w��
	------------------------------------------------------------------------------ */
	friend class Singleton<EffectSystem>;

private:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	EffectSystem() {};

	/**
	* �R�s�[�R���X�g���N�^
	*/
	EffectSystem(const EffectSystem&) = delete;

	/**
	* �f�X�g���N�^
	*/
	~EffectSystem() {};

	/**
	* ������Z�q�̃I�[�o�[���[�h
	*/
	void operator=(const EffectSystem&) = delete;

private:
	/** �G�t�F�N�V�A�����_���[ */
	::EffekseerRendererDX11::RendererRef mEffekseerRenderer;

	/** �G�t�F�N�g�}�l�[�W���[ */
	::Effekseer::ManagerRef mEffekseerManager;

public:
	/**
	* @fn ����������
	* @brief Effekseer������������
	* @return void
	*/
	void Initialize();

	/**
	* @fn Draw
	* @brief �`�揈��
	* @return void
	*/
	void Draw();

private:
	/**
	* @fn ConvertEffekseerMatrix
	* @brief DirectX::SimpleMath::Matrix��Effekseer::Matrix44�ɕϊ�����
	* @param const DirectX::SimpleMath::Matrix& (_matrix)
	* @return Effekseer::Matrix44
	*/
	Effekseer::Matrix44 ConvertEffekseerMatrix(const DirectX::SimpleMath::Matrix& _matrix);

public:
	/**
	* @fn GetEffekseerManager
	* @brief �G�t�F�N�V�A�}�l�[�W���[��Ԃ�
	* @return Effekseer::ManagerRef
	*/
	inline Effekseer::ManagerRef GetEffekseerManager() const noexcept;
};

//------------ INLINES ------------

inline Effekseer::ManagerRef EffectSystem::GetEffekseerManager() const noexcept
{
	return mEffekseerManager;
}
