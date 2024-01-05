/**
* @file DirectX11RasterizerState
* @brief DirectX11RasterizerState�N���X�̒�`
*/

#pragma once

//----------- INCLUDES ---------
#include <d3d11.h>

/**
* @class DirectX11RasterizerState
* @brief ID3D11RasterizerState�����b�v�����N���X
*/
class DirectX11RasterizerState
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	DirectX11RasterizerState();

	/**
	* �f�X�g���N�^
	*/
	~DirectX11RasterizerState();

private:
	/** ���X�^���C�U�[�X�e�[�g */
	ID3D11RasterizerState* mRasterizerState;

	/** ���X�^���C�U�[�f�X�N */
	D3D11_RASTERIZER_DESC mRasterizerDesc;

public:
	/**
	* @fn SetupRasterizerDesc
	* @brief ���X�^���C�U�[�f�X�N�̐ݒ�
	* @param const D3D11_FILL_MODE& (_fillMode)
	* @param const D3D11_CULL_MODE& (_cullMode)
	* @return void
	*/
	void SetupRasterizerDesc(const D3D11_FILL_MODE& _fillMode, const D3D11_CULL_MODE& _cullMode);

	/**
	* @fn GetRasterizerState
	* @brief ���X�^���C�U�[�X�e�[�g���擾����֐�
	* @return ID3D11RasterizerState*
	*/
	inline ID3D11RasterizerState* GetRasterizerState() const;

	/**
	* @fn ID3D11RasterizerState**
	* @brief ���X�^���C�U�[�X�e�[�g�̃_�u���|�C���^��Ԃ�
	* @return ID3D11RasterizerState**
	*/
	inline ID3D11RasterizerState** GetRasterizerStateWPtr();

	/**
	* @fn GetRasterizerDesc
	* @brief ���X�^���C�U�[�X�e�[�g�̃Q�b�^�[
	* @return D3D11_RASTERIZER_DESC
	*/
	inline D3D11_RASTERIZER_DESC GetRasterizerDesc() const;

};

//--------- INLINES -----------

inline ID3D11RasterizerState* DirectX11RasterizerState::GetRasterizerState() const
{
	return mRasterizerState;
}

inline ID3D11RasterizerState** DirectX11RasterizerState::GetRasterizerStateWPtr()
{
	return &mRasterizerState;
}

inline D3D11_RASTERIZER_DESC DirectX11RasterizerState::GetRasterizerDesc() const
{
	return mRasterizerDesc;
}
