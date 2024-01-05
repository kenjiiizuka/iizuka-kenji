/**
* @file  AnimationInstance.h
* @brief SkeletalMeshのアニメーションを管理するクラス
*/


#pragma once

//---------- INCLUDES ---------
#include <map>
#include <string>
#include <memory>
#include <functional>
#include "../../../System/AnimationSystem/AnimationPlayer.h"


//----------- 前方宣言 -----------
class SkeletalMeshOld;
class SkeletalMeshAnimation;
class SkeletalMeshAnimationClip;
class GameObject;
class AnimationStateContext;
class AnimationPlayer;

template<typename Derived, typename Base>
concept DerivedFromAnimationStateContext = std::is_base_of<Base, Derived>::value;

/**
* @class AnimationInstance
* @brief スケルタルメッシュのアニメーションに関連する処理を行うためのユーザー向けのクラス
* @detail 継承し、それぞれのアニメーションインスタンスを作成し、独自の処理をする
*/
class AnimationInstance
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	AnimationInstance();

	/**
	* デストラクタ
	*/
	virtual ~AnimationInstance() {};

private:
	/** このアニメーションインスタンスを持つゲームオブジェクト */
	GameObject* mOwner;

protected:
	/** アニメーション再生するクラス  */
	std::weak_ptr<AnimationPlayer> mAnimPlayer;
	
	/** このアニメーションインスタンスを持つスケルタルメッシュ */
	std::weak_ptr<SkeletalMesh> mSkeletalMesh;

	/** アニメーションクリップ */
	std::unordered_map<std::string, std::shared_ptr<SkeletalMeshAnimationClip>> mAnimationClips;

	/** 現在アニメーションが再生されているか */
	bool bPlayAnimation;

	/** 現在のステートコンテキスト */
	std::shared_ptr<AnimationStateContext> mStateContext;

public:
	/**
	 * @fn　AnimationInit
	 * @brief 初期化処理
	 * @return void
	*/
	virtual void AnimationInit() {}

	/**
	 * @fn　AnimationUninit
	 * @brief 終了処理
	 * @return void
	*/
	virtual void AnimationUninit() {};

	/**
     * @fn　AnimationUpdate
     * @brief Animationの更新処理
     * @return void
    */
	virtual void AnimationUpdate();

protected:	
	/**
	 * @fn　MainStateMachine
	 * @brief ステートマシン
	 * @return void
	*/
	virtual void MainStateMachine() {};
 
	/**
	 * @fn　TransitionStateAndPlay
	 * @brief ステートの遷移と遷移時にアニメーションの再生をする
	 * @param EnumType& (_state) アニメーションの現在ステートを持つ変数の参照
	 * @param EnumType  (_nextState) 遷移先のステート
	 * @param std::string (_animationName) 再生するアニメーションの名前
	 * @param bool (_loop) ループ再生するか
	 * @return void
	*/
	template<typename EnumType, typename = std::enable_if_t<std::is_enum_v<EnumType>>>
	inline void TransitionStateAndPlay(EnumType& _state, EnumType _nextState, const std::string _animationName, bool _loop = false);

	/**
     * @fn　TransitionStateContext
     * @brief ステートコンテキストの遷移関数
     * @return std::shared_ptr<T> 遷移先のステートコンテキスト
    */
	template<typename T>
	requires DerivedFromAnimationStateContext<T, AnimationStateContext>
	inline std::shared_ptr<T> TransitionContext();
	
public:
	/**
	 * @fn　LoadAnimationClip
	 * @brief アニメーションの読み込み関数
	 * @param std::string (_filePath) 読み込むアニメーションのファイルパス
	 * @param std::string (_animationName) アニメーションの名前
	 * @return std::weak_ptr<SkeletalMeshAnimationClip> 読み込んだアニメーションクリップ
	*/
	std::weak_ptr<SkeletalMeshAnimationClip> LoadAnimationClip(const std::string& _filePath, const std::string& _animationName);

	/**
	 * @fn　PlayAnimationClip
	 * @brief アニメーションクリップの再生
	 * @param const std::string& (_animationName)
	 * @param const float        (_playRate)
	 * @param const float        (_interpTime)
	 * @param const float        (_toInterpAnimationClipTime)
	 * @return void
	*/
	void PlayAnimationClip(const std::string& _animationName, const float _playRate = 1.0f, const float _interpTime = 0.0f, const float _toInterpAnimationClipTime = 0.0f);
	
	/**
	 * @fn　SetOwnerSkeletalMesh
	 * @brief このアニメーションインスタンスが対応しているスケルタルメッシュのセッター
	 * @param std::shared_ptr<SkeletalMesh> (_skeletalMesh) 対応するスケルタルメッシュ
	 * @return void
	*/
	void SetOwnerSkeletalMesh(std::shared_ptr<SkeletalMesh> _skeletalMesh);

	/**
	 * @fn　SetOwner
	 * @brief オーナーになるゲームオブジェクトのセッター
	 * @param GameObject* (_owner) オーナーになるゲームオブジェクト
	 * @return void
	*/
	void SetOwner(GameObject* _owner);

	/**
	 * @fn　GetOwner
	 * @brief オーナーのゲームオブジェクトを返す
	 * @return GameObject* オーナーのゲームオブジェクト
	*/
	GameObject* GetOwner();

	/**
	 * @fn　GetCurrnetAnimation
	 * @brief 現在再生しているアニメーションのゲッター
	 * @return std::shared_ptr<SkeletalMeshAnimation> 現在再生しているアニメーション
	*/
	std::shared_ptr<AnimationPlayer> GetAnimationPlayer();

	/**
	 * @fn　GetAnimationByName
	 * @brief アニメーションを名前で取得する
	 * @return std::shared_ptr<SkeletalMeshAnimationClip>
	 */
	inline std::shared_ptr<SkeletalMeshAnimationClip> GetAnimationClipByName(const std::string& _animName);

	/**
	* @fn SetAnimationPlayer
	* @brief アニメーションプレイヤーのセッター
	* @param const std::shared_ptr<AnimationPlayer> (_animPlayer)
	* @return void
	*/
	inline void SetAnimationPlayer(const std::shared_ptr<AnimationPlayer> _animPlayer);
};

//-------------------- INLINES --------------------

inline std::shared_ptr<SkeletalMeshAnimationClip> AnimationInstance::GetAnimationClipByName(const std::string& _animName)
{
	if (mAnimationClips.contains(_animName))
	{
		return mAnimationClips[_animName];
	}

	return nullptr;
}

inline void AnimationInstance::SetAnimationPlayer(const std::shared_ptr<AnimationPlayer> _animPlayer)
{
	mAnimPlayer = _animPlayer;
}

template<typename EnumType, typename T>
inline void AnimationInstance::TransitionStateAndPlay(EnumType& _state, EnumType _nextState, const std::string _animationName, bool _loop)
{
	_state = _nextState;
}

template<typename T>
requires DerivedFromAnimationStateContext<T, AnimationStateContext>
inline std::shared_ptr<T> AnimationInstance::TransitionContext()
{
	mStateContext.reset();
	return std::make_shared<T>(this);
}

