/**
* @file SkeletalMeshAnimationData.h
* @brief SkeletalMeshAnimationDataクラスの定義とアニメーションデータに必要な構造体の定義
*/

#pragma once

//--------------- INCUDES ------------
#include <vector>
#include <string>
#include <SimpleMath.h>
#include "../../../System/AssetSystem/IAsset.h"

/**
* @struct VectorKey
* @brief Vector3で表せるキーフレームの情報を持つ
*/
struct VectorKey
{
	double mTime;                         /**< このキーの時間 */
	DirectX::SimpleMath::Vector3 mValue;  /**< キー値 */
	size_t mIndex;                        /**< このキーが先頭から何番目かを表す添え字 */

	/** 
	 * デフォルトコンストラクタ 
	*/
	VectorKey();
};

/**
* @struct QuaternionKey
* @brief キーフレームアニメーションの回転の情報を持つキーフレーム構造体
*/
struct QuaternionKey
{
	double mTime;                           /**< このキーの時間 */
	DirectX::SimpleMath::Quaternion mValue;	/**< キー値 */
	size_t mIndex;							/**< このキーが先頭から何番目かを表す添え字 */

	/**
	 * デフォルトコンストラクタ
	*/
	QuaternionKey();
};

/** ボーンのキーフレームの情報を持つ */
/**
* @struct Channel
* @brief キーフレームアニメーションの情報を持ち、取得しやすくするための関数を持つ
*/
struct Channel
{	
	bool bRoot;                                 /**< ルートボーンのキー情報なのか */
	std::string mBoneName;                      /**< 対応するボーン名前 */
	size_t mNumPositionKey;                     /**< 座標キーの数 */
	size_t mNumRotationKey;                     /**< 回転キーの数 */
	size_t mNumScaleKey;                        /**< スケールキーの数 */
	std::vector<VectorKey> mPositionKeys;       /**< 座標キー */
	std::vector<VectorKey> mScaleKeys;          /**< スケールキー */
	std::vector<QuaternionKey> mRotationKeys;   /**< 回転キー */

	/**
	* デフォルトコンストラクタ
	*/
	Channel();

	/**
	 * @fn　GetCurrentPositionKey
	 * @brief 現在の再生箇所のPositionKeyを取得する関数
	 * @param (_nextPlayTime) アニメーションの現在の再生箇所
	 * @param (_nextScaleKey) 次の再生箇所のPositionKeyの参照
	*/
	void GetCurrentPositionKey(double _currnetPlayTime, VectorKey& _currentKey);

	/**
     * @fn　GetCurrentRotationKey
     * @brief 現在の再生箇所のRotationKeyを取得する関数
     * @param (_nextPlayTime) アニメーションの現在の再生箇所
     * @param (_nextScaleKey) 次の再生箇所のRotationKeyの参照
    */
	void GetCurrentRotationKey(double _currnetPlayTime, QuaternionKey& _currentKey);

	/**
	 * @fn　GetCurrentScaleKey
	 * @brief 現在の再生箇所のScaleKeyを取得する関数
	 * @param (_nextPlayTime) アニメーションの現在の再生箇所
	 * @param (_nextScaleKey) 次の再生箇所のScaleKeyの参照
	*/
	void GetCurrentScaleKey(double _currnetPlayTime, VectorKey& _currentKey);

	/**
	 * @fn　GetNextPositionKey
	 * @brief 次の再生箇所のPositionKeyを取得する関数
	 * @param (_nextPlayTime) アニメーション次の再生箇所
	 * @param (_nextScaleKey) 次の再生箇所のPositionKeyの参照
	*/
	bool GetNextPositionKey(VectorKey& _currentKey, VectorKey& _nextPositionKey);

	/**
	 * @fn　GetNextScaleKey
	 * @brief 次の再生箇所のScaleKeyを取得する関数
	 * @param (_nextPlayTime) アニメーション次の再生箇所
	 * @param (_nextScaleKey) 次の再生箇所のScaleKeyの参照
	*/
	bool GetNextScaleKey(VectorKey& _currentKey, VectorKey& _nextScaleKey);

	/**
	 * @fn　GetNextRotationKey
	 * @brief 指定した再生箇所のRotationKeyを取得する関数
	 * @param (_nextPlayTime) アニメーション次の再生箇所
	 * @param (_nextRotationKey)次の再生箇所のRotationKeyの参照
	*/
	bool GetNextRotationKey(QuaternionKey& _currentKey, QuaternionKey& _nextRotationKey);
};

/**
* @class SkeletalMeshAnimationData
* @brief アニメーションデータクラス 
* @detail アニメーションの再生の設定などの情報も持つ
*/
class SkeletalMeshAnimationData : public IAsset
{
	/**-------------------------------------------
	 * アニメーションデータに対してセットできるクラスをSkeletalMeshProviderクラスに
	 * 限定するためfriend指定をしている 
	*/
	friend class SkeletalMeshAnimationProvider;

public:
	/**
	 * デフォルトコンストラクタ
	*/
	SkeletalMeshAnimationData();
	
	/**
	 * デフォルトデストラクタ
	*/
	~SkeletalMeshAnimationData();

private:	
	/** アニメーションのチャンネルデータ */
	std::vector<Channel> mChannels;

	/** アニメーションの長さ */
	float mDuration;

	/** 一秒間に進むアニメーションの長さ */
	float mTickPerSecond;

public:
	/**
	 * @fn GetChannel
	 * @brief チャンネルデータの取得
	 * @return std::vector<Channel> チャンネルデータ
	*/
	inline std::vector<Channel> GetChannels() const noexcept;

	/**
     * @fn GetAssetType
     * @brief アセットのタイプを返す
     * @detail typeidを使用して型判別をしている
     * @return const std::type_info&
    */
	inline virtual const std::type_info& GetAssetType() const noexcept;

	/**
	* @fn GetDuration
	* @brief アニメーションの長さを返す
	* @return float
	*/
	inline float GetDuration() const noexcept;

	/**
	* @fn GetTickPerSecond
	* @brief 一秒間に進むアニメーションの長さを返す
	* @return float
	*/
	inline float GetTickPerSecond() const noexcept;

};

//----------- INLINES ----------

inline std::vector<Channel> SkeletalMeshAnimationData::GetChannels() const noexcept
{
	return mChannels;
}

inline const std::type_info& SkeletalMeshAnimationData::GetAssetType() const noexcept
{
	return typeid(SkeletalMeshAnimationData);
}

inline float SkeletalMeshAnimationData::GetDuration() const noexcept
{
	return mDuration;
}

inline float SkeletalMeshAnimationData::GetTickPerSecond() const noexcept
{
	return mTickPerSecond;
}