/**
* @file SwapChain.h
* @brief SwapChain�N���X�̒�`
*/

#pragma once

//----------- INCLUDES ----------
#include <d3d11.h>

/**
* @class SwapChain
* @brief DX11��SwapChain�����b�v�����N���X
*/
class SwapChain
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	SwapChain();

	/**
	* �f�X�g���N�^
	*/
	~SwapChain();

private:
	/** �X���b�v�`�F�[�� */
	IDXGISwapChain* mSwapChain;

	/** �X���b�v�`�F�[���f�X�N */
	DXGI_SWAP_CHAIN_DESC mSwapChainDesc;

public:
	/**
	* @fn CreateSwapChainDesc
	* @brief �X���b�v�`�F�[���f�X�N�̍쐬�֐�
	* @param const HWND& (_outPutWindow)
	* @param const UINT& (_bufferWidth)
	* @param const UINT& (_bufferHeight)
	* @param const BOOL& (_windowMode)
	* @return void
	*/
	void SetupSwapChainDesc(const HWND& _outPutWindow, const UINT& _bufferWidth, const UINT& _bufferHeight, const BOOL& _windowMode);

	/**
	* @fn Release
	* @brief ����֐�
	* @return void
	*/
	void Release();

	/**
	* @fn Present
	* @brief ��ʕ\��
	* @return void
	*/
	void Present();

	/**
	* @fn GetSwapChainDesc
	* @brief �X���b�v�`�F�[���f�X�N�̍쐬
	* @return DXGI_SWAP_CHAIN_DESC
	*/
	inline DXGI_SWAP_CHAIN_DESC GetSwapChainDesc() const noexcept;

	/**
	* @fn GetSwapChainWPtr
	* @brief SwapChain�̃_�u���|�C���^��Ԃ�
	* @return IDXGISwapChain**
	*/
	inline IDXGISwapChain** GetSwapChainWPtr();
};

//--------- INLINES ----------

inline DXGI_SWAP_CHAIN_DESC SwapChain::GetSwapChainDesc() const noexcept
{
	return mSwapChainDesc;
}

inline IDXGISwapChain** SwapChain::GetSwapChainWPtr()
{
	return &mSwapChain;
}

