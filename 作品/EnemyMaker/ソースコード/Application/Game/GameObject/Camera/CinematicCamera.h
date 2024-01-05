/**
* @file CinematicCamera.h
* @brief CinematicCameraクラスの定義
*/

#pragma once

//------- INCLUDES --------
#include "Camera.h"

//------- 前方宣言 ---------
class Bone;

/**
* @class CinematicCamera
* @brief シネマティックカメラ、カメラ演出などをするためのクラス
*        設定されたキーに沿ってカメラアニメーションさせる
*        キーの保存先としてファイルパスを指定する必要があります
*		 キーの位置情報は移す対象からローカル位置
*/
class CinematicCamera : public Camera
{
	/**
	* @struct CameraAnimationKey 
	* @brief カメラアニメーションのための情報
	*        移動位置、秒数をもつ
	*/
	struct CameraAnimationKey
	{
		DirectX::SimpleMath::Vector3 mPosition;  /**< カメラの移動位置 */
		double mTime;                            /**< 時間 */
		bool mbCut;                              /**< 次のキーまで補間なしで切り替える */

		/**
		* デフォルトコンストラクタ
		*/
		CameraAnimationKey();

	};

public:
	/**
	* デフォルトコンストラクタ
	*/
	CinematicCamera();

	/**
	* デストラクタ
	*/
	~CinematicCamera();

private:
	/** カメラアニメーションキー ローカル空間上の値を持つ */
	std::vector<CameraAnimationKey> mLocalAnimKeys;

	/** カメラアニメーションキー ワールド空間上の値を持つ　実際にアニメーションに使用 */
	std::vector<CameraAnimationKey> mWorldAnimKeys;

	/** データを保存するためのファイルパス */
	std::string mSaveFilePath;

	/** カメラアニメーションを再生しているか */
	bool mbPlay;

	/** 現在の再生時間 */
	double mCurrentPlayTime;

	/** 再生時間 */
	double mDuration;

	/** 映す対象 */
	std::weak_ptr<GameObject> mTargetObject;

	/** 映し対象のボーン 設定されていない場合はTargetObjectを使用する */
	std::weak_ptr<Bone> mTargetBone;

public:
	/**
	* @fn Init
	* @brief 初期化処理
	* @detail 指定されたファイルからデータを読み込む。データがなければ読み込みは行わない
	*         ここで渡されたファイルパスにデータを保存する
	* @param std::string_view (_filepath)
	* @return void
	*/
	void Init(std::string_view _filepath);

	/**
	* @fn Update
	* @brief 更新処理
	* @param const double (_deltaTime)
	* @return void
	*/
	void Update(const double _deltaTime) override;

private:
	/**
	* @fn CameraAnimation
	* @brief カメラアニメーション
	* @param const double (_deltaTime)
	* @return void
	*/
	void CameraAnimation(const double _deltaTime);

	/**
	* @fn InterpCameraAnimationKeyPosition
	* @brief 補完してポジションを求める
	* @param CameraAnimationKey& (_keyBase) 補間元キー
	* @param CameraAnimationKey& (_keyTo)   補間先キー
	* @param DirectX::SimpleMath::Vector3& (_position) 補間結果
	* @return void
	*/
	void InterpCameraAnimationKeyPosition(CameraAnimationKey& _keyBase, CameraAnimationKey& _keyTo, DirectX::SimpleMath::Vector3& _position);

	/**
	* @fn GetKey
	* @brief 現在の再生時間から、補完するために必要なキーを取得する
	* @detail 現在の再生時間の直前のキーと、次のキーを取得する
	* @param CameraAnimationKey& (_key1)
	* @param CameraAnimationKey& (_key2)
	* @return void
	*/
	void GetKey(CameraAnimationKey& _key1, CameraAnimationKey& _key2);

	/**
	* @fn CalcuFocusPosition
	* @brief 注視点を計算する
	* @return void
	*/
	void CalcuFocusPosition() override;

	/**
	* @fn ConvertTargetWorldPosition
	* @brief 設定されたキーの位置情報をワールド空間に変換する
	* @return void
	*/
	void ConvertTargetWorldPosition();

	/**
	* @fn Save
	* @brief キーデータをセーブする
	* @return void
	*/
	void Save();

	/**
	* @fn Load
	* @brief データ読み込み
	* @return bool
	*/
	bool Load();

public:
	/**
	* @fn Edit
	* @brief カメラアニメーションを編集する関数
	* @param std::string_view (_label)
	* @return void
	*/
	void EditAnimation(std::string_view _label);

	/**
	* @fn Play
	* @brief カメラアニメーション再生
	* @detail データがなければ再生しない
	*         データがあれば最初のキーの位置にカメラを設定し、再生
	* @return void
	*/
	void Play();

	/**
	* @fn SetTargetObject
	* @brief ターゲットのゲームオブジェクトをセットする
	* @param std::shared_ptr<GameObject> (_targetObject)
	* @return void
	*/
	inline void SetTargetObject(std::shared_ptr<GameObject> _targetObject) noexcept;

	/**
	* @fn SetTargetBone
	* @brief ターゲットとなるボーンをセットする
	* @param std::shared_ptr<Bone> (_targetBone)
	* @return void
	*/
	inline void SetTargetBone(std::shared_ptr<Bone> _targetBone) noexcept;

	/**
	* @fn GetCurrentPlayTime
	* @brief 現在の再生時間を返す
	* @return double 
	*/
	inline double GetCurrentPlayTime() const noexcept;

	/**
	* @fn GetDuration
	* @brief アニメーションの長さを返す
	* @return double 
	*/
	inline double GetDuration() const noexcept;

};

//---------- INLINES ----------

inline void CinematicCamera::SetTargetObject(std::shared_ptr<GameObject>_targetObject) noexcept
{
	mTargetObject = _targetObject;
	mTargetBone.reset();
}

inline void CinematicCamera::SetTargetBone(std::shared_ptr<Bone> _targetBone) noexcept
{
	mTargetBone = _targetBone;
	mTargetObject.reset();
}

inline double CinematicCamera::GetCurrentPlayTime() const noexcept
{
	return mCurrentPlayTime;
}

inline double CinematicCamera::GetDuration() const noexcept
{
	return mDuration;
}
