/**
* @file DirectX11SamplerState.h
* @brief DirectX11SamplerState�N���X�̒�`
*/

#pragma once

//---------- INCLUDES ---------
#include <d3d11.h>


/**
* @class DirectX11SamplerState
* @brief ID3D11SamplerState�����b�v�����N���X
*/
class DirectX11SamplerState final
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	DirectX11SamplerState();

	/**
	* �f�X�g���N�^
	*/
	~DirectX11SamplerState();

private:
	/** �T���v���[�X�e�[�g */
	ID3D11SamplerState* mSamplerState;

	/** �T���v���[�X�e�[�g�f�X�N */
	D3D11_SAMPLER_DESC mSamplerStateDesc;

public:
	/**
	* @fn Release
	* @brief �T���v���[�X�e�[�g�̉������
	* @return void
	*/
	void Release();

	/**
	* @fn SetupSamplerStateDesc
	* @brief SamplerStateDesc�̐ݒ������
	* @return void
	*/
	void SetupSamplerStateDesc();

	/**
	* @fn GetSamplerState
	* @brief �T���v���[�X�e�[�g�̃Q�b�^�[
	* @return void
	*/
	inline ID3D11SamplerState* GetSamplerState() const;

	/**
	* @fn GetSamplerStateWPtr
	* @brief �T���v���[�X�e�[�g�̃_�u���|�C���^��Ԃ�
	* @return ID3D11SamplerState**
	*/
	inline ID3D11SamplerState** GetSamplerStateWPtr();

	/**
	* @fn GetSamplerStateDesc
	* @brief �T���v���[�X�e�[�g�f�X�N��Ԃ�
	* @return D3D11_SAMPLER_DESC
	*/
	inline D3D11_SAMPLER_DESC GetSamplerStateDesc();


};

//-------- INLINES --------

inline ID3D11SamplerState* DirectX11SamplerState::GetSamplerState() const
{
	return mSamplerState;
}

inline ID3D11SamplerState** DirectX11SamplerState::GetSamplerStateWPtr()
{
	return &mSamplerState;
}

inline D3D11_SAMPLER_DESC DirectX11SamplerState::GetSamplerStateDesc()
{
	return mSamplerStateDesc;
}
