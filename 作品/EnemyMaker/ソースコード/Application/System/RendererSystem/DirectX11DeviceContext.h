/**
* @file DirectX11DeviceContext.h
* @brief DirectX11DeviceContext�N���X�̒�`
*/

#pragma once


//--------- INCLUDES ----------
#include <d3d11.h>
#include <memory>

//------- �O���錾 --------
class DirectX11BlendState;
class DirectX11RasterizerState;
class DirectX11SamplerState;
class DirectX11ViewPort;

/**
* @class DirectX11DeviceContext
* @brief ID3D11DeviceContext�����b�v�����N���X
*/
class DirectX11DeviceContext final
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	DirectX11DeviceContext();

	/**
	* �f�X�g���N�^
	*/
	~DirectX11DeviceContext();

private:
	/** �f�o�C�X�R���e�L�X�g */
	ID3D11DeviceContext* mDeviceContext;

public:
	/**
	* @fn Release
	* @brief DeviceContext�̉��
	* @return void
	*/
	void Release();

	/**
	* @fn SetBlendState
	* @brief �u�����h�X�e�[�g�̃Z�b�g
	* @param const std::shared_ptr<DirectX11BlendState> (_blendState)
	* @param const float (_blendFactor[4])
	* @return void
	*/
	void SetBlendState(const std::shared_ptr<DirectX11BlendState> _blendState, const float _blendFactor[4]);

	/**
	* @fn SetRasterizerState
	* @brief ���X�^���C�U�[�X�e�[�g�̃Z�b�g
	* @param const std::shared_ptr<DirectX11RasterizerState> (_rasterizerState)
	* @return void
	*/
	void SetRasterizerState(const std::shared_ptr<DirectX11RasterizerState> _rasterizerState);

	/**
	* @fn SetSamplerState
	* @brief �T���v���[�X�e�[�g�̃Z�b�g
	* @param const UINT (_slot)
	* @param const UINT (_numSampler)
	* @param const std::shared_ptr<DirectX11SamplerState> (_samplerState)
	* @return void
	*/
	void SetSamplerState(const UINT _slot, const UINT _numSampler,const std::shared_ptr<DirectX11SamplerState> _samplerState);

	/**
	* @fn SetViewPort
	* @brief �r���[�|�[�g�̃Z�b�^�[
	* @param const std::shared_ptr<DirectX11ViewPort> (_viewPort)
	* @return void
	*/
	void SetViewPort(const std::shared_ptr<DirectX11ViewPort> _viewPort);

public:
	/**
	* @fn GetContext
	* @brief �f�o�C�X�R���e�L�X�g��Ԃ�
	* @return ID3D11DeviceContext*
	*/
	inline ID3D11DeviceContext* GetContext() const;

	/**
	* @fn GetContextWPtr
	* @brief �f�o�C�X�R���e�L�X�g�Ƃ̃_�u���|�C���^��Ԃ�
	* @return ID3D11DeviceContext**
	*/
	inline ID3D11DeviceContext** GetContextWPtr();

};

//--------- INLINES ----------

inline ID3D11DeviceContext* DirectX11DeviceContext::GetContext() const
{
	return mDeviceContext;
}

inline ID3D11DeviceContext** DirectX11DeviceContext::GetContextWPtr()
{
	return &mDeviceContext;
}
