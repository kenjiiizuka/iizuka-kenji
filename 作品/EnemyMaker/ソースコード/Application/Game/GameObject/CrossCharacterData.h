#pragma once
#include <stdint.h>

/**
* @file  CrossCharacterData.h
* @brief キャラクター間で共通したデータを定義したファイル
*/

/** キャラクター間で共通したデータを定義する名前空間 */
namespace CrossCharacter
{
	/** 敵の攻撃がヒットした際のリアクションの種類 */
	enum HitReaction : uint8_t
	{
		HitReaction_Small,  /**< リアクション 小 */
		HitReaction_Big,	/**< リアクション 大 */
		HitReaction_Max,   /**< リアクションの数 */
	};
}
