/**
* @file SkeletalMeshAnimationClip.h
* @brief SkeletalMeshAnimationClipクラスの定義
*/

#pragma once

//------------ INCLUDES -----------
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include "../../System/AssetSystem/SkeletalMesh/SkeletalMeshAnimationData.h"
#include "../Component/SkeletalMeshComponent/AnimationNotifyState.h"

//------------ 前方宣言 -----------
class AssetHandle;
class SkeletalMesh;


//--------- TEMPLATE ------------
template<typename Derived, typename Base>
concept DerivedAnimationNotify = std::is_base_of<Base, Derived>::value;

template<typename Derived, typename Base>
concept DerivedAnimationNotifyState = std::is_base_of<Base, Derived>::value;


/**
* @class SkeletalMeshAnimationClip
* @brief アニメーションを制御、再生するために必要なデータへのアクセスをしやすくする為に
*        SkeletalMeshAnimationAssetをラップしたクラス
*/
class SkeletalMeshAnimationClip
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	SkeletalMeshAnimationClip();

	/**
	* デストラクタ
	*/
	virtual ~SkeletalMeshAnimationClip();

private:
	/** アニメーションアセットのハンドル */
	std::shared_ptr<AssetHandle> mAnimationAssetHandle;

	/** アニメーション通知の配列 通知とその通知がアタッチされるフレーム数 */
	std::vector<std::pair<std::shared_ptr<AnimationNotify>, float>> mAnimNotifies;

	/** アタッチされているアニメーション通知ステートの配列 */
	std::vector<std::shared_ptr<AnimationNotifyState>> mAnimNotifyStates;

	/** アニメーションの名前 */
	std::string mAnimationName;

protected:
	/** キーフレームデータを持つチャンネル */
	std::vector<Channel> mChannels;

	/** アニメーションの長さ */
	float mDuration;

	/** アニメーションの終了フレーム */
	float mEndFrame;

	/** 一秒間に進むアニメーションの長さ */
	float mTickPerSeconds;

	/** ループ再生するか */
	bool mbLoop;

	/** 位置を同期をするか */
	bool mbSynchroPosition;

	/** 回転を同期する */
	bool mbSynchroRotation;

	/** 開始がルートからずれた位置であることを示す */
	bool mbDisplacedStartAnimation;

	/** 通知処理を実行したか */
	std::vector<bool> mbNotifyExecuted;

	/** 通知の開始処理をしたか 各通知ステートごとにフラグを管理する */
	std::vector<bool> mbNotifyStateBeginExecuted;

	/** 通知の終了処理をしたか 各通知ステートごとにフラグを管理する */
	std::vector<bool> mbNotifyStateEndExecuted;

	/** アニメーションが適応されるスケルタルメッシュ */
	std::weak_ptr<SkeletalMesh> mSkeletalMesh;

	/** 現在の再生時間 */
	float mCurrentPlayTime;

	/** 現在のセクション */
	std::string mCurrentSection;

	/** アニメーションに設定されているセクション デフォルトでは "Default" セクション設定されている */
	std::vector<std::pair<uint16_t, std::string>> mSections;

public:
	/**
	* @fn Initialize
	* @brief 初期化処理
	* @detail 指定されたアニメーションデータを読み込みをし読み込んだアセットのハンドルを取得
	* @param const std::string&     (_filePath)
	* @return void
	*/
	virtual void Initialize(const std::string& _filePath);

	/**
	* @fn Begin 
	* @brief アニメーションの開始処理
	* @return void
	*/
	virtual void Begin();

	/**
	* @fn Update
	* @brief 更新処理
	* @param const float (_currentPlayTime)
	* @return void
	*/
	virtual void Update(const float _currentPlayTime);

private:
	/**
	* @fn PositionKeyLerp
	* @brief 渡されたチャンネルの指定された時間に対応する座標をキーフレーム間で補完して返す
	* @param const float                   (_time)
	* @param DirectX::SimpleMath::Vector3& (_outPutPosition)
	* @param Channel&                      (_channel)
	* @return void
	*/
	void PositionKeyLerp(const double& _time, DirectX::SimpleMath::Vector3& _outPutPosition, Channel& _channel);

	/**
	* @fn RotationKeyLerp
	* @brief 渡されたチャンネルの指定された時間に対応する回転をキーフレーム間で補完して返す
	* @param const double                      (_time)
	* @param DirectX::SimpleMath::Quaternion&  (_outPutQuaternion)
	* @param Channel&                          (_channel)
	* @return void
	*/
	void RotationKeyLerp(const double& _time, DirectX::SimpleMath::Quaternion& _outPutQuaternion, Channel& _channel);

	/**
	* @fn ScaleKeyLerp
	* @brief 渡されたチャンネルの指定された時間に対応するスケールをキーフレーム間で補完して返す
	* @param const double                   (_time)
	* @param DirectX::SimpleMath::Vector3&  (_outPutScale)
	* @param Channel&                       (_channel)
	* @return void
	*/
	void ScaleKeyLerp(const double& _time, DirectX::SimpleMath::Vector3& _outPutScale, Channel& _channel);

	/**
	* @fn CheckCurrentSection
	* @brief 現在のセクションがどれかを判断して設定する
	* @return void
	*/
	void CheckCurrentSection();

public:

	/**
　　 * @fn　AddAnimationNotify
　　 * @brief アニメーション通知の追加関数
	 * @param float (_attachFrame) アタッチするフレーム
　　 * @return std::shared_ptr<T> 追加したアニメーション通知クラスの参照
　　*/
	template<typename T>
	requires DerivedAnimationNotify<T, AnimationNotify>
	std::shared_ptr<T> AddAnimationNotify(float _attachFrame)
	{
		std::pair<std::shared_ptr<AnimationNotify>, float> animNotify;
		animNotify.first = std::make_shared<T>(this, _attachFrame);
		animNotify.second = _attachFrame;
		animNotify.first->SetAttachFrame(_attachFrame);
		mAnimNotifies.emplace_back(animNotify);	
		mbNotifyExecuted.emplace_back(false);
		return std::static_pointer_cast<T>(animNotify.first);
	}

	/**
　　 * @fn　AddAnimationNotifyState
　　 * @brief アニメーション通知ステートの追加関数
	 * @param float (_attachStartFrame) アタッチする開始フレーム
	 * @param float (_attachEndFrame) アタッチする終了フレーム
　　 * @return std::shared_ptr<T> 追加したアニメーション通知ステートクラスの参照
　　*/
	template<typename T>
	requires DerivedAnimationNotifyState<T, AnimationNotifyState>
	std::shared_ptr<T> AddAnimationNotifyState(uint16_t _attachStartFrame, uint16_t _attachEndFrame)
	{
		std::shared_ptr<AnimationNotifyState> notifyState;
		notifyState = std::make_shared<T>(this, _attachStartFrame, _attachEndFrame);
		mAnimNotifyStates.emplace_back(notifyState);
		mbNotifyStateBeginExecuted.emplace_back(false);
		mbNotifyStateEndExecuted.emplace_back(false);
		return std::static_pointer_cast<T>(notifyState);
	}

	/**
　　 * @fn　GetAnimationNotify
　　 * @brief アニメーション通知の取得関数
　　 * @return std::shared_ptr<T> 指定したアニメーション通知
　　*/
	template<typename T>
	requires DerivedAnimationNotify<T, AnimationNotify>
	std::shared_ptr<T> GetAnimnotify()
	{
		for (std::pair<std::shared_ptr<AnimationNotify>, float>& notify : mAnimNotifies)
		{
			if (typeid(*notify.first.get()) == typeid(T))
			{
				return std::static_pointer_cast<T>(notify.first);
			}
		}
		return nullptr;
	}

	/**
	* @fn GetAllAnimationNotify
	* @brief アタッチされている指定された型のアニメーションステートをすべて返す
	* @return std::vector<std::shared_ptr<T>>
	*/
	template<typename T>
	requires DerivedAnimationNotify<T, AnimationNotify>
	inline std::vector<std::shared_ptr<T>> GetAllAnimationNotify();

	/**
　　 * @fn　GetAnimationNotifyState
　　 * @brief アニメーション通知のステート取得関数
　　 * @return std::shared_ptr<T> 指定したアニメーション通知ステート
　　*/
	template<typename T>
	requires DerivedAnimationNotifyState<T, AnimationNotifyState>
	std::shared_ptr<T> GetAnimnotifyState()
	{
		for (std::shared_ptr<AnimationNotifyState> notifyState : mAnimNotifyStates)
		{
			if (typeid(*notifyState.get()) == typeid(T))
			{
				return std::static_pointer_cast<T>(notifyState);
			}
		}
		return nullptr;
	}

	/**
	* @fn GetAllAnimNotifyState
	* @brief 指定された通知ステートをすべて返す
	* @detail 指定された通知ステートがなければサイズが0の配列を変えす 
	* @return std::vector<std::shared_ptr<T>>
	*/
	template<typename T>
	requires DerivedAnimationNotifyState<T, AnimationNotifyState>
	inline std::vector<std::shared_ptr<T>> GetAllAnimNotifyState();

	/**
	* @fn AddSection
	* @brief セクション追加
	* @detail 複数のセクションを追加する際はフレームが昇順になるように追加してください
	* @param const uint16_t (_frame)
	* @param std::string_view (_sectionName)
	* @return void
	*/
	inline void AddSection(const uint16_t _frame, std::string_view _sectionName);

public:
	/**
	* @fn CalucAnimationMatrix
	* @brief チャンネルの指定された時間のアニメーションマトリックスを返す関数
	* @param Channel& (_channel)
	* @param const double (_time)
	* @param DirectX::SimpleMath::Matrix& (_animationMatrix)
	* @return void
	*/
	virtual void CalucAnimationMatrix(Channel& _channel, const double _time, DirectX::SimpleMath::Matrix& _animationMatrix);

	/**
	* @fn CalucAnimationKey
	* @brief チャンネルの指定された時間のアニメーションキー情報を返す
	* @param Channel& (_channel)
	* @param const double (_time)
	* @param DirectX::SimpleMath::Vector3&    (_position)
	* @param DirectX::SimpleMath::Vector3&    (_scale)
	* @param DirectX::SimpleMath::Quaternion& (_quaternion)
	* @return void
	*/
	virtual void CalucAnimationKey(Channel& _channel, const double _time, DirectX::SimpleMath::Vector3& _position, DirectX::SimpleMath::Vector3& _scale, DirectX::SimpleMath::Quaternion& _quaternion);

	/**
	* @fn GetChannels
	* @brief チャンネルデータを返す
	* @return std::vector<Channel>
	*/
	inline std::vector<Channel> GetChannels() const;

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

	/**
	* @fn SetLoop
	* @brief ループ再生するかセットする
	* @param const bool (_loop)
	* @return void
	*/
	inline void SetLoop(const bool _loop) noexcept;

	/**
	* @fn IsLoop
	* @brief ループ再生なのかを返す
	* @return bool true ループ false ループではない
	*/
	inline bool IsLoop() const noexcept;

	/**
	* @fn SetEndFrame
	* @brief アニメーションの終了フレームを設定する関数
	* @param const float (_endFrame)
	* @return void
	*/
	inline void SetEndFrame(const float _endFrame) noexcept;

	/**
	* @fn GetEndFrame
	* @brief アニメーション終了フレームの取得
	* @return float 
	*/
	inline float GetEndFrame() const noexcept;

	/**
	* @fn SetSynchro
	* @brief アニメーションとゲームオブジェクトを同期するかをセットする
	* @param const bool (_synchro) true 同期する false 同期しない
	* @return void
	*/
	inline void SetSynchroPosition(const bool _synchroPosition) noexcept;

	/**
	* @fn IsSynchroPosition
	* @brief 同期するかを返す
	* @return bool true 同期する false 同期しない
	*/
	inline bool IsSynchroPosition() const noexcept;

	/**
	* @fn SetSynchroRotation
	* @brief 回転を同期させるのセッター
	* @param const bool 
	* @return void
	*/
	inline void SetSynchroRotation(const bool _synchroRotation) noexcept;

	/**
	* @fn IsSynchroRotation
	* @brief 回転を同期するか返す
	* @return bool true 同期する false 同期しない
	*/
	inline bool IsSynchroRotation() const noexcept;

	/**
	* @fn GetSkeletalMesh
	* @brief このアニメーションが適応されるスケルタルメッシュを返す
	* @return std::weak_ptr<SkeletalMesh>
	*/
	inline std::weak_ptr<SkeletalMesh> GetSkeletalMesh() const;

	/**
	* @fn SetSkeletalMesh
	* @brief アニメーションが適応されるスケルタルメッシュをセット関数
	* @param const std::shared_ptr<SkeletalMesh> _skeletalMesh
	* @return void
	*/
	inline void SetSkeletalMesh(const std::shared_ptr<SkeletalMesh> _skeletalMesh);

	/**
	* @fn GetAnimationName
	* @brief アニメーション名を返す
	* @return std::string
	*/
	inline std::string GetAnimationName() const noexcept;

	/**
	* @fn SetDisplaced
	* @brief 開始がルートからずれた位置であるかをセットする
	* @param const bool (_isDisplaced)
	* @return void
	*/
	inline void SetDisplaced(const bool _isDisplaced) noexcept;

	/**
	* @fn IsDisplaced
	* @brief 開始位置がルートからずれたアニメーションかを返す
	* @return bool 
	*/
	inline bool IsDisplaced() const noexcept;

	/**
	* @fn GetCurrentPlayTime
	* @brief 現在の再生時間
	* @return float
	*/
	inline float GetCurrentPlayTime() const noexcept;

	/**
	* @fn GetCurrentSection
	* @brief 現在のセクションを返す
	* @return std::string
	*/
	inline std::string GetCurrentSection() const noexcept;

};

//----------- INLINES ------------

inline std::vector<Channel> SkeletalMeshAnimationClip::GetChannels() const
{
	return mChannels;
}

inline float SkeletalMeshAnimationClip::GetDuration() const noexcept
{
	return mDuration;
}

inline float SkeletalMeshAnimationClip::GetTickPerSecond() const noexcept
{
	return mTickPerSeconds;
}

inline void SkeletalMeshAnimationClip::SetLoop(const bool _loop) noexcept
{
	mbLoop = _loop;
}

inline bool SkeletalMeshAnimationClip::IsLoop() const noexcept
{
	return mbLoop;
}

inline void SkeletalMeshAnimationClip::SetEndFrame(const float _endFrame) noexcept
{
	mEndFrame = _endFrame;
}

inline float SkeletalMeshAnimationClip::GetEndFrame() const noexcept
{
	return mEndFrame;
}

inline void SkeletalMeshAnimationClip::SetSynchroPosition(const bool _synchroPosition) noexcept
{
	mbSynchroPosition = _synchroPosition;
}

inline bool SkeletalMeshAnimationClip::IsSynchroPosition() const noexcept
{
	return mbSynchroPosition;
}

inline void SkeletalMeshAnimationClip::SetSynchroRotation(const bool _synchroRotation) noexcept
{
	mbSynchroRotation = _synchroRotation;
}

inline bool SkeletalMeshAnimationClip::IsSynchroRotation() const noexcept
{
	return mbSynchroRotation;
}

inline std::weak_ptr<SkeletalMesh> SkeletalMeshAnimationClip::GetSkeletalMesh() const
{
	return mSkeletalMesh;
}

inline void SkeletalMeshAnimationClip::SetSkeletalMesh(const std::shared_ptr<SkeletalMesh> _skeletalMesh)
{
	mSkeletalMesh = _skeletalMesh;
}

inline std::string SkeletalMeshAnimationClip::GetAnimationName() const noexcept
{
	return mAnimationName;
}

inline void SkeletalMeshAnimationClip::SetDisplaced(const bool _isDisplaced) noexcept
{
	mbDisplacedStartAnimation = _isDisplaced;
}

inline bool SkeletalMeshAnimationClip::IsDisplaced() const noexcept
{
	return mbDisplacedStartAnimation;
}

inline float SkeletalMeshAnimationClip::GetCurrentPlayTime() const noexcept
{
	return mCurrentPlayTime;
}

inline std::string SkeletalMeshAnimationClip::GetCurrentSection() const noexcept
{
	return mCurrentSection;
}

inline void SkeletalMeshAnimationClip::AddSection(const uint16_t _frame, std::string_view _sectionName)
{
	// アニメーションの長さをこえていれば追加しない
	if (_frame > mDuration)
	{
		std::cout << "Animationの長さを超えた位置にセクションを追加しようとしています。" << std::endl
			<< "AnimationName  : " << mAnimationName << std::endl
			<< "Duration       : " << mDuration << std::endl
			<< "AddFrame       : " << _frame << std::endl
			<< "AddSectionName : " << _sectionName << std::endl;
		return;
	}

	// 追加
	mSections.emplace_back(std::pair<uint16_t, std::string>(_frame, _sectionName));
}

template<typename T>
requires DerivedAnimationNotify<T, AnimationNotify>
inline std::vector<std::shared_ptr<T>> SkeletalMeshAnimationClip::GetAllAnimationNotify()
{
	std::vector<std::shared_ptr<T>> notifies;
	for (std::pair<std::shared_ptr<AnimationNotify>, float> notify : mAnimNotifies)
	{
		if (typeid(*notify.first.get()) == typeid(T))
		{
			notifies.emplace_back(std::static_pointer_cast<T>(notify.first));
		}
	}
	return notifies;
}

template<typename T>
requires DerivedAnimationNotifyState<T, AnimationNotifyState>
inline std::vector<std::shared_ptr<T>> SkeletalMeshAnimationClip::GetAllAnimNotifyState()
{
	std::vector<std::shared_ptr<T>> notifies;
	for (std::shared_ptr<AnimationNotifyState> notifyState : mAnimNotifyStates)
	{
		if (typeid(*notifyState.get()) == typeid(T))
		{
			notifies.emplace_back(std::static_pointer_cast<T>(notifyState));
		}
	}
	return notifies;
}
