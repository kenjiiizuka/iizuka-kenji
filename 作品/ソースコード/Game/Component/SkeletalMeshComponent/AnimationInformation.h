#pragma once
#include <stdint.h>

namespace AnimationInf
{
	/** アニメーションの再生の仕方 */
	enum AnimationPlayType : uint32_t
	{
		PlayType_None = 0,                  /**< 通常再生 */
		PlayType_Loop = 0x01,               /**< ループ再生 */
		PlayType_PositionSynchro = 0x02,    /**< 座標同期 */
		PlayType_RotationSynchro = 0x04,    /**< 回転同期 */
		PlayType_LastFrameFreesze = 0x08    /**< 最後のフレームで固定 */
	};

	/** アニメーション再生時のブレンドの種類 */
	enum AnimationBlendType : uint16_t
	{
		BlendType_None = 0,                     /**< 通常再生 */
		BlendType_InterpStartPosition = 1,   /**< 次のアニメーションの開始まで補間 */
	};
}

using AnimationPlaySetting = uint32_t;