#pragma once
#include <stdint.h>

/** レンダリング関係使用するものを定義した名前空間 */
namespace RendererInf
{
	/** 描画オブジェクトのレイヤー */
	enum Layer : uint8_t
	{
		Layer_BackGround = 0, /**< バックグラウンド 背景オブジェクト */
		Layer_Object = 1,     /**< オブジェクト ゲーム内に存在する3Dオブジェクト */
		Layer_PerticleEffect, /**< エフェクト */
		Layer_Lithing,        /**< ライティングに必要な物を描画するレイヤー */
		Layer_Overlay,        /**< 2DのUI等 */
		Layer_Max,            /**< 最大数 */
	};
};

