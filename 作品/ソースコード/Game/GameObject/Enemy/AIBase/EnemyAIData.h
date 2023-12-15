#pragma once

/** エネミーの行動の結果を表す列挙型 */
enum class EnemyActionResult
{
	Succeeded, /**< 成功 */
	Failed,    /**< 失敗 */
	InProgress, /**< 実行中 */
	CanChange,  /**< 変更可能 */
	// Aborted,    /**< 中止 */
};

