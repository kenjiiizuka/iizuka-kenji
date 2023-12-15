/**
* @file AnimationSynchro.h
* @brief AnimationSynchroクラスの定義
*/

#pragma once

//------------- INCLUDES ------------
#include <memory>
#include <SimpleMath.h>
#include "../../Game/Component/TransformComponent/Transform.h"

//---------- 前方宣言 -----------
class SkeletalMesh;
class Bone;
class SkeletalMeshAnimationClip;
class GameObject;

/**
* @class AnimationSynchro
* @brief アニメーションで動くメッシュとGameObjectの座標を同期するクラス
*/
class AnimationSynchronizer
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	AnimationSynchronizer();

	/**
	* デストラクタ
	*/
	~AnimationSynchronizer();

private:
	/** 同期するスケルタルメッシュ */
	std::weak_ptr<SkeletalMesh> mSkeletalMesh;

	/** アニメーションクリップ */
	std::weak_ptr<SkeletalMeshAnimationClip> mAnimationClip;

	/** 同期対象のSkeletalMeshのRootボーン */
	std::weak_ptr<Bone> mBone;

	/** SkeletalMeshのオーナーオブジェクト */
	GameObject* mMeshOwnerObject;

	/** アニメーション開始時のSkeletalMeshのワールド行列 */
	DirectX::SimpleMath::Matrix mSkeletalMeshWorldMatrix;

	/** スケルタルメッシュのトランスフォーム */
	Transform mSkeletalMeshTrans;

	/** ルートボーンのトランスフォーム */
	Transform mRootBoneTrans;

	/** 座標同期 */
	bool mbSynchroPosition;

	/** 回転同期 */
	bool mbSynchroRotation;

	/** 連続して同期処理をしていることを示す */
	bool mbRepeated;

	/** ルートがずれている位置から開始するアニメーションなのか */
	bool mbDisplacedStartAnimation;

	/** 同期開始して最初のフレームを示す */
	bool mbFirstFrame;

public:
	/**
	* @fn SynchroBegin
	* @brief 同期処理開始処理
	* @param std::shared_ptr<SkeletalMesh> (_skeletalMesh)
	* @param const bool                    (_synchroPosition)
	* @param const bool                    (_synchroRotation)
	* @param const bool                    (_repeated)
	* @param const bool                    (_displaced)
	* @return void
	*/
	void SynchroBegin(std::shared_ptr<SkeletalMesh> _skeletalMesh, const bool _synchroPosition, const bool _synchroRotation, const bool _repeated, const bool _displaced);

	/**
	* @fn Synchro
	* @brief 同期更新処理
	* @detail ルートが動くアニメーションに合わせてGameObjectを動かしている
	* @return void
	*/
	void Synchro();

	/**
	* @fn SynchroEnd
	* @brief 同期終了処理
	* @return void
	*/
	void SynchroEnd();

private:
	/**
	* @fn SynchroCollision
	* @brief コリジョンと同期させる処理
	* @param Transform& (_rootBoneTrans)
	* @return void
	*/
	void SynchroCollision(Transform& _rootBoneTrans);

	/**
	* @fn RepeatSynchroSetup
	* @brief 連続して同期処理をするための準備
	* @return void
	*/
	void RepeatSynchroSetup();

public:
	/**
	* @fn RepeatedEnd
	* @brief 連続同期終了をAnimationPlayerから伝える関数
	* @return void
	*/
	inline void RepeatedEnd() noexcept;

};
