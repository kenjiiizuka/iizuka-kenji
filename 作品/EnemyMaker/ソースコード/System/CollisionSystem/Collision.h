#pragma once

/**
* @file Collision.h
* @brief 当たり判定に関する名前空間、列挙型が定義されている
*/

/** 当たり判定に関するenumを定義してある名前空間 */
namespace Collision 
{
    /** 当たり判定の形状の種類 */
    enum PrimitiveType : uint16_t
    {
        PrimitiveType_Box,            /**< ボックス */
        PrimitiveType_Cylinder,       /**< シリンダー */
        PrimitiveType_Capsule,        /**< カプセル */
        PrimitiveType_Ring,           /**< リング */
        PrimitiveType_BoundingSphere, /** バウンディングスフィア */
        PrimitiveType_Max             /**< 最大数 */
    };

    /** 当たり判定の種類 */
    enum Type : uint16_t
    {
        Type_None,     /**< 当たり判定を取らない */
        Type_Overlap,  /**< 重なり判定のみ検知  */
        Type_Block,    /**< 衝突応答あり    */
        Type_Max       /**< 最大数 */
    };

    /** 当たり判定チャンネル */
    enum Channel : uint16_t
    {
        Channel_Static,          /**< 移動しないオブジェクト */
        Channel_Movable,         /**< 移動するオブジェクト */
        Channel_Player,          /**< プレイヤー */
        Channel_Enemy,           /**< エネミー */
        Channel_PlayerAttack,    /**< 攻撃 */
        Channel_EnemyAttack ,    /**< エネミーの攻撃 */
        Channel_Max,             /**< 最大数 */
    };
}