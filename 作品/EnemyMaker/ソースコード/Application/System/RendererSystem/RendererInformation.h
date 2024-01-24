#pragma once
#include <stdint.h>

/** レンダリング関係使用するものを定義した名前空間 */
namespace RendererInf
{
	/** 描画オブジェクトのレイヤー */
	enum Layer : uint8_t
	{
		Layer_Lithing  = 0,   /**< ライティングに必要な物を描画するレイヤー */
		Layer_BackGround,     /**< バックグラウンド 背景オブジェクト */	
		Layer_Object,         /**< オブジェクト ゲーム内に存在する3Dオブジェクト */
		// Layer_PerticleEffect, /**< エフェクト */	
		Layer_Overlay,        /**< 2DのUI等 */
		Layer_Max,            /**< 最大数 */
	};
};

