/**
* @file DirectX11DepthStencilState.h
* @brief DirectX11DepthStencilState�N���X�̒�`
*/

#pragma once

//--------- INCLUDES ----------
#include <d3d11.h>
#include <memory>

//---------- INCLUDES ---------
class DirectX11Device;

/**
* @class DirectX11DepthStencilState
* @brief DepthStencilState�����b�v�����N���X
*/
class DirectX11DepthStencilState
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	DirectX11DepthStencilState();

	/**
	* �f�X�g���N�^
	*/
	~DirectX11DepthStencilState();

private:
	/** �f�v�X�X�e���V���X�e�[�g */
	ID3D11DepthStencilState* mDepthStencilState;

	/** �f�v�X�X�e���V���f�X�N */
	D3D11_DEPTH_STENCIL_DESC mDepthStencilDesc;

public:
	/**
	* @fn SetupDepthStencilStateDesc
	* @brief �f�v�X�X�e���V���X�e�[�g�f�X�N�̐ݒ�֐�
	* @param const D3D11_DEPTH_WRITE_MASK& (_depthWriteMask)
	* @param const D3D11_COMPARISON_FUNC&  (_depthFunc)
	* @param const BOOL                    (_depthEnable)
	* @param const BOOL                    (_stencilEnable)
	* @return void
	*/
	void SetupDepthStencilStateDesc(const D3D11_DEPTH_WRITE_MASK& _depthWriteMask, const D3D11_COMPARISON_FUNC& _depthFunc, const BOOL _depthEnable = TRUE, const BOOL _stencilEnable = FALSE);

	/**
	* @fn CreateDepthStencilState
	* @brief �f�v�X�X�e���V���쐬
	* @param const std::shared_ptr<DirectX11Device> (_device)
	* @return void
	*/
	void CreateDepthStencilState(const std::shared_ptr<DirectX11Device> _device);

	/**
	* @fn GetDepthStencilState
	* @brief �f�v�X�X�e���V���X�e�[�g��Ԃ�
	* @return ID3D11DepthStencilState*
	*/
	inline ID3D11DepthStencilState* GetDepthStencilState() const;

};

//-------------- INLINES -----------

inline ID3D11DepthStencilState* DirectX11DepthStencilState::GetDepthStencilState() const
{
	return mDepthStencilState;
}
