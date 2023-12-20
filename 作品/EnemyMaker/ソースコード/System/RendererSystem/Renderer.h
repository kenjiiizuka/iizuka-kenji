/**
* @file Renderer.h
* @brief Rendererクラスの定義
*/


#pragma once

//------------ INCLUDES ------------
#include <d3d11.h>
#include <SimpleMath.h>
#include <memory>
#include "../Singleton.h"


#define SAFE_RELEASE(p) if(p){p->Release(); p = nullptr;}

//-------- 前方宣言 ----------
class Application;
class DirectX11Device;
class DirectX11DeviceContext;
class SwapChain;
class RenderTarget;
class DepthStencil;
class DirectX11DepthStencilState;
class DirectX11BlendState;
class DirectX11RasterizerState;
class DirectX11SamplerState;
class DirectX11ViewPort;

/**
* @fn Renderer
* @brief レンダリングクラス
* @detail DirectX11APIを使用し描画しています
*/
class Renderer final : public Singleton<Renderer>
{
	/**----------------------------------------------------------------------------------------------
    * 基底クラスのSingletonクラスからコンストラクタと、デストラクタにアクセスするために必要であり
    * クラス外から生成、破棄できないようにするためにフレンド指定する
    ------------------------------------------------------------------------------------------------*/
	friend class Singleton<Renderer>;

private:

	/**
	* デフォルトコンストラクタ
	*/
	Renderer();

	/**
	* デストラクタ
	*/
	~Renderer();

	/**
	* コピーコンストラクタ
	* コピー禁止のために delete指定
	*/
	Renderer(const Renderer&) = delete;

	/**
	* 代入演算子のオーバーロード
	* 代入禁止のため delete指定
	*/
	void operator=(const Renderer&) = delete;

private:	
	/** このレンダラーを使うApplication */
	Application*             mApplication;
	
	/** 機能レベル */
	D3D_FEATURE_LEVEL        mFeatureLevel;

	/** デバイス */
	std::shared_ptr<DirectX11Device> mDevice;

	/** デバイスコンテキスト */
	std::shared_ptr<DirectX11DeviceContext> mDeviceContext;

	/** スワップチェイン */
	std::shared_ptr<SwapChain> mSwapChain;

	/** レンダーターゲット */
	std::shared_ptr<RenderTarget> mRenderTargetView;

	/** デプスステンシル */
	std::shared_ptr<DepthStencil> mDepthStencilView;

	/** デプスステンシル有効ステート */
	std::shared_ptr<DirectX11DepthStencilState> mDepthStencilEnable;

	/** デプスステンシル無効ステート */
	std::shared_ptr<DirectX11DepthStencilState> mDepthStencilDisable;

	/** ブレンドステート */
	std::shared_ptr<DirectX11BlendState> mBlendState;

	/** ラスタライザ-ステート ぬりつぶし Back */
	std::shared_ptr<DirectX11RasterizerState> mRasterizerSolidBack;

	/** ラスタライザーステート　ぬりつぶし Front */
	std::shared_ptr<DirectX11RasterizerState> mRasterizerSolidFront;

	/** ラスタライザーステート ワイヤフレーム表示 */
	std::shared_ptr<DirectX11RasterizerState> mRasterizerFrame;

	/** サンプラーステート */
	std::shared_ptr<DirectX11SamplerState> mSamplerState;

	/** ビューポート */
	std::shared_ptr<DirectX11ViewPort> mViewPort;

public:
	/**
	* @fn Init
	* @brief レンダラーの初期化処理
	* @param Application* (_app)
	* @return void
	*/
	void Initialize(Application* _app);

	/**
	* @fn Uninitialize
	* @brief 終了処理
	*/
	void Uninitialize();

	/**
	* @fn Begin
	* @brief レンダリング開始処理
	* @return void
	*/
	void BeginRenderer();

	/**
	* @fn EndRenderer
	* @brief レンダリング終了処理
	* @return void
	*/
	void EndRenderer();

	/**
	* @fn GetDevice
	* @brief D3D11Deviceのゲッター
	* @return ID3D11Device*
	*/
	ID3D11Device* GetDevice();

	/**
	* @fn GetDeviceContext
	* @brief デバイスコンテキストのゲッター
	* @return ID3D11DeviceContext*
	*/
	ID3D11DeviceContext* GetDeviceContext();

	/**
	* @fn GetSamplerState
	* @brief サンプラーステートのゲッター
	* @return ID3D11SamplerState*
	*/
	ID3D11SamplerState* GetSamplerState();

	/**
	* @fn GetSwapChain
	* @brief スワップチェインのゲッター
	* @return IDXGISwapChain*
	*/
 	IDXGISwapChain* GetSwapChain();

	/**
	* @fn SetRenderTarget
	* @brief レンダーターゲットのセッター
	* @param std::shared_ptr<RenderTarget> (_targetTarget)
	* @param std::shared_ptr<DepthStencil> (_depthStencil)
	* @return void
	*/
	void SetRenderTarget(std::shared_ptr<RenderTarget> _targetTarget, std::shared_ptr<DepthStencil> _depthStencil);

	/**
	* @fn ResetRenderTarget
	* @brief レンダーターゲットをデフォルトのレンダーターゲットにリセットする
	* @return void
	*/
	void ResetRenderTarget();

	/**
	* @fn SetRasterizerSolidBack
	* @brief ぬりつぶしの背面カリングのラスタライザーをセットする
	* @return void
	*/
	void SetRasterizerSolidBack();

	/**
	* @fn SetRasterizerSolidFront
	* @brief ぬりつぶしの前面カリングのラスタライザーをセットする関数
	* @return void
	*/
	void SetRasterizerSolidFront();

	/**
	* @fn SetRasterizerWireFrame
	* @brief ワイヤーフレーム設定のラスタライザーをセットする
	* @return void
	*/
	void SetRasterizerWireFrame();

	/**
	* @fn GetWidth
	* @brief 画面の横幅を取得
	* @return uint16_t
	*/
	float GetWidth();

	/**
	* @fn GetHeight
	* @brief 画面の縦幅を取得
	* @return uint16_t
	*/
	float GetHeight();
	
	/**
	* @fn Draw
	* @brief DrawCall関数のラッパー
	* @param D3D_PRIMITIVE_TOPOLOGY (_topology)
	* @param UINT (_numVertex)
	* @param UINT (_startVertexLocation)
	* @return void
	*/
	void Draw(D3D_PRIMITIVE_TOPOLOGY _topology, UINT _numVertex, UINT _startVertexLocation);
};

//--------- INLINES ----------

//inline 


