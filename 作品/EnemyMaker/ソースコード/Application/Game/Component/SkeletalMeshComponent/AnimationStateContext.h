/**
* @file  AnimationStateContext.h
* @brief AnimationStateContextクラスの定義
*/

#pragma once

//-------- INCLUDES ---------
#include <string>
#include <memory>
#include "../../../System/AnimationSystem/AnimationPlayer.h"


//----------- 前方宣言 ------------
class AnimationInstance;

/**
* @class AnimationStateContext
* @brief アニメステートコンテキストの基底クラス
*/
class AnimationStateContext
{
public:
	AnimationStateContext() = delete;

	/**
	* コンストラクタ
	* 
	* @param AnimationInstance* (_animInstance) 
	*/
	AnimationStateContext(AnimationInstance* _animInstance);

	/**
	* デストラクタ
	*/
	virtual ~AnimationStateContext() {};

protected:
	/** このステートの名前 */
	std::string mStateName;

	/** このステート使用するオーナーのAnimationInstance */
	AnimationInstance* mOwnerAnimationInstance;

	/** 遷移が必要であることを示す */
	bool mbNeedTransition;
public:
	/**
     * @fn Entry
     * @brief ステートの開始処理
     * @return void
    */
	virtual void Entry() {};

	/**
	 * @fn Entry
	 * @brief 再度のこのステートを開始する処理
	 * @return void
	*/
	virtual void ReEntry() {};

	/**
	 * @fn StateMachine
	 * @brief ステートマシン
	 * @return void
	*/
	virtual void StateMachine() {};

	/**
	 * @fn Update
	 * @brief ステートの更新処理
	 * @return void
	*/
	virtual void Update(){}

protected:
	/**
	 * @fn PlayAnimationClip
	 * @brief アニメーション再生のラッパー関数
	 * @param std::string (_animationName) 再生するアニメーションの名前
	 * @param const float (_playRate)
	 * @param const float (_interpTime)
	 * @param const float (_toInterpAnimationClipTime)
	 * @return void
	*/
	void PlayAnimationClip(const std::string& _animationName, const float _playRate = 1.0f, const float _interpTime = 0.0f, const float _toInterpAnimationClipTime = 0.0f);

	/**
	 * @fn TransitionStateAndPlay
	 * @brief ステートの遷移とそれに伴うアニメーションを再生する
	 * @param EnumType&          (_state)         遷移するステート変数
	 * @param const EnumType     (_nextState)     遷移先のステート
	 * @param const std::string& (_animationName) 再生するアニメーションの名前
	 * @param const float        (_playRate)      再生速度
	 * @param const float        (_interpTime)    補間する時間
	 * @return void
	*/
	template<typename EnumType, typename = std::enable_if_t<std::is_enum_v<EnumType>>>
	inline void TransitionStateAndPlay(EnumType& _state, const EnumType _nextState,const std::string& _animationName, const float _playRate = 1.0f, const float _interpTime = 0.0f)
	{
		_state = _nextState;
		PlayAnimationClip(_animationName, _playRate, _interpTime);
	}

public:

	/**
	 * @fn GetStateName
	 * @brief ステートの名前を返す
	 * @return std::string mStateName
	*/
	std::string GetStateName() { return mStateName; }	

	/**
	 * @fn GetNeedTransition
	 * @brief bNeedTransitionを返す
	 * @return bool bNeedTransition
	*/
	bool IsNeedTransition() { return mbNeedTransition; }
};
