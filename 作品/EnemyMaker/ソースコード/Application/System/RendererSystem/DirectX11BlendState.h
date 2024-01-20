/**
* @file DirectX11BlendState.h
* @brief DirectX11BlendState�N���X�̒�`
*/

#pragma once

//--------- INCLUDES ----------
#include <d3d11.h>
#include <memory>

//--------- �O���錾 --------
class DirectX11Device;

/**
* @class DirectX11BlendState
* @brief ID3D11BlendState�����b�v�����N���X
*/
class DirectX11BlendState final
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	DirectX11BlendState();

	/**
	* �f�X�g���N�^
	*/
	~DirectX11BlendState();

private:
	/** �u�����h�f�X�N */
	D3D11_BLEND_DESC mBlendDesc;

	/** �u�����h�X�e�[�g */
	ID3D11BlendState* mBlendState;

public:
	/**
	* @fn Release
	* @brief �������
	* @return void
	*/
	void Release();

	/**
	* @fn SetupBlendDesc
	* @brief �u�����h�f�X�N�̐ݒ�
	* @param const BOOL (_alphaToCoverageEnable)
	* @return void
	*/
	void SetupBlendDesc(const BOOL _alphaToCoverageEnable = FALSE);

	/**
	* @fn CreateBlendState
	* @brief �u�����h�X�e�[�g�쐬�֐�
	* @param const std::shared_ptr<DirectX11Device> (_device)
	* @return HRESULT
	*/
	HRESULT CreateBlendState(const std::shared_ptr<DirectX11Device> _device);

	/**
	* @fn GetBlendState
	* @brief �u�����h�X�e�[�g�̃Q�b�g
	* @return ID3D11BlendState*
	*/
	inline ID3D11BlendState* GetBlendState() const;
};

//---------- INLINES ---------

inline ID3D11BlendState* DirectX11BlendState::GetBlendState() const
{
	return mBlendState;
}