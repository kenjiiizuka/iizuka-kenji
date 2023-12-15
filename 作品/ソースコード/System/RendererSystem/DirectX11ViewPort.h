/**
* @file DirectX11ViewPort.h
* @brief DirectX11ViewPort
*/

#pragma once

//-------- INCLUDES --------
#include <d3d11.h>

/**
* @class DirectX11ViewPort
* @brief �r���[�|�[�g�N���X
*/
class DirectX11ViewPort
{
public:	
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	DirectX11ViewPort();

	/**
	* �f�X�g���N�^
	*/
	~DirectX11ViewPort();

private:
	/** �r���[�|�[�g */
	D3D11_VIEWPORT mViewPort;

public:
	/**
	* @fn SetupViewPort
	* @brief �r���[�|�[�g�̐ݒ������֐�
	* @param const FLOAT (_width)
	* @param const FLAOT (_height)
	* @param const FLAOT (_maxDepth)
	* @param const FLAOT (_minDepth)
	* @param const FLAOT (_topLeftX)
	* @param const FLAOT (_topLeftY)
	* @return void
	*/
	void SetupViewPort(const FLOAT _width, const FLOAT _height, const FLOAT _maxDepth, const FLOAT _minDepth, const FLOAT _topLeftX, const FLOAT _topLeftY);	

	/**
	* @fn GetViewPort
	* @brief �r���[�|�[�g�̃Q�b�^�[
	* @return D3D11_VIEWPORT
	*/
	inline D3D11_VIEWPORT GetViewPort() const;
};

//-------- INLINES ---------

inline D3D11_VIEWPORT DirectX11ViewPort::GetViewPort() const
{
	return mViewPort;
}
