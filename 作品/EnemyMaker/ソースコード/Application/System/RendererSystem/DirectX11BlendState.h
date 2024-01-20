/**
* @file DirectX11BlendState.h
* @brief DirectX11BlendStateクラスの定義
*/

#pragma once

//--------- INCLUDES ----------
#include <d3d11.h>
#include <memory>

//--------- 前方宣言 --------
class DirectX11Device;

/**
* @class DirectX11BlendState
* @brief ID3D11BlendStateをラップしたクラス
*/
class DirectX11BlendState final
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	DirectX11BlendState();

	/**
	* デストラクタ
	*/
	~DirectX11BlendState();

private:
	/** ブレンドデスク */
	D3D11_BLEND_DESC mBlendDesc;

	/** ブレンドステート */
	ID3D11BlendState* mBlendState;

public:
	/**
	* @fn Release
	* @brief 解放処理
	* @return void
	*/
	void Release();

	/**
	* @fn SetupBlendDesc
	* @brief ブレンドデスクの設定
	* @param const BOOL (_alphaToCoverageEnable)
	* @return void
	*/
	void SetupBlendDesc(const BOOL _alphaToCoverageEnable = FALSE);

	/**
	* @fn CreateBlendState
	* @brief ブレンドステート作成関数
	* @param const std::shared_ptr<DirectX11Device> (_device)
	* @return HRESULT
	*/
	HRESULT CreateBlendState(const std::shared_ptr<DirectX11Device> _device);

	/**
	* @fn GetBlendState
	* @brief ブレンドステートのゲット
	* @return ID3D11BlendState*
	*/
	inline ID3D11BlendState* GetBlendState() const;
};

//---------- INLINES ---------

inline ID3D11BlendState* DirectX11BlendState::GetBlendState() const
{
	return mBlendState;
}