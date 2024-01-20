/**
* @file DirectX11Device.h
* @brief DirectX11Device�N���X�̒�`
*/

#pragma once
//------------ INCLUDES ----------
#include <d3d11.h>
#include <memory>

//----------- �O���錾 ---------
class DirectX11RasterizerState;
class DirectX11SamplerState;

/**
* @fn DirectX11Device
* @brief ID3D11Device�����b�v�����N���X
*/
class DirectX11Device final
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	DirectX11Device();

	/**
	* �f�X�g���N�^
	*/
	~DirectX11Device();

private:
	/** �f�o�C�X */
	ID3D11Device* mDevice;

public:
	/**
	* @fn CreateRasterizerState
	* @brief ���X�^���C�U�[�X�e�[�g�쐬�֐�
	* @param const std::shared_ptr<DirectX11RasterizerState>& (_rasterizer)
	* @return HRESULT
	*/
	HRESULT CreateRasterizerState(const std::shared_ptr<DirectX11RasterizerState>& _rasterizer);

	/**
	* @fn CreateSamplerState
	* @brief �T���v���[�X�e�[�g�쐬�֐�
	* @param const std::shared_ptr<DirectX11SamplerState>& (_samplerState)
	* @return HRESULT
	*/
	HRESULT CreateSamplerState(const std::shared_ptr<DirectX11SamplerState>& _samplerState);

public:
	/**
	* @fn GetDevice
	* @brief �f�o�C�X�̃Q�b�^�[
	* @return ID3D11Device*
	*/
	inline ID3D11Device* GetDevice();

	/**
	* @fn GetDevice
	* @brief Device�̃_�u���|�C���^�̃Q�b�^�[
	* @return ID3D11Device**
	*/
	inline ID3D11Device** GetDeviceWPtr();
};

//----------- INLINES -----------

inline ID3D11Device* DirectX11Device::GetDevice()
{
	return mDevice;
}

inline ID3D11Device** DirectX11Device::GetDeviceWPtr()
{
	return &mDevice;
}