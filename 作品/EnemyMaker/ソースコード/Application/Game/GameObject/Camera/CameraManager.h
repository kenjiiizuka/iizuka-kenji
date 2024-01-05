/**
* @file CameraManager.h
* @brief CameraManagerクラスの定義
*/
#pragma once

//---------- INCLUDES ------------
#include <unordered_map>
#include <string>
#include "Camera.h"

//--------- INCLUDES ----------
class Camera2D;

/**
* @class CameraManager
* @brief カメラを生成、管理、破棄するクラス
* @detail シーン内に必ず一つCameraManagerを生成し、CameraManagerから必要なカメラを生成するようにする
*/
class CameraManager
{
private:
	/** 3D空間上のメインカメラ */
	std::shared_ptr<Camera> mMainCamera;

	/** メインカメラの名前 */
	std::string mMainCameraName;

	/** ２Dカメラ */
	std::shared_ptr<Camera2D> m2DCamera;

	/** カメラのリスト */
	std::unordered_map<std::string, std::shared_ptr<Camera>> mpCameraList;

	std::string mOldCameraName; // デバッグカメラに切り替える前に使用していたカメラ
	bool bDebug = false; // デバッグカメラモード

public:
	/**
	* @fn Init
	* @brief 初期化処理
	* @detail デフォルトの2D用のカメラと3Dカメラを生成している
	* @return void
	*/
	void Init();

	/**
	* @fn Update
	* @brief 更新処理
	* @detail 生成されたカメラの更新処理を行っている
	* @return void
	*/
	void Update(const double _deltaTime);

	/**
	* @fn Draw
	* @brief 描画処理
	* @detail カメラの描画処理(カメラに移っているオブジェクト描画ために必要な処理をしている)
	* @return void
	*/
	void Draw();

	/**
	* @fn Uninit
	* @brief 終了処理
	* @detail リストにあるカメラの解放をしている
	* @return void
	*/
	void Uninit();

public:
	/**
	* @fn ShakeMainCamera
	* @brief メインカメラのカメラ振動関数を実行する
	* @param const DirectX::SimpleMath::Vector2 (_maxShakeVector) 
	* @param const double (_shakeTime)
	* @param const uint8_t (_shakeLevel)
	* @return void
	*/
	void ShakeMainCamera(const DirectX::SimpleMath::Vector2 _maxShakeVector = { 1.0f,1.0f }, const double _shakeTime = 1.0f ,const uint8_t _shakeLevel = 1);

	/**
	* @fn CreateCamera
	* @brief カメラ作成関数
	* @param std::string_view (_cameraName)　作成するカメラに付ける名前
	* @return std::shared_ptr<T> 作成したカメラ
	*/
	template<typename T>
	inline std::shared_ptr<T> CreateCamera(std::string_view _cameraName);

	/**
	* @fn GetCameraByName
	* @brief 指定された名前のカメラを返す
	* @param std::string_view (_cameraName)
	* @return std::shared_ptr<T>
	*/
	template<typename T>
	inline std::shared_ptr<T> GetCameraByName(std::string_view _cameraName);
	
	/**
	* @fn SetMainCameraByName
	* @param std::string_view _cameraName
	* @return void
	*/
	inline void SetMainCameraByName(std::string_view _cameraName);

	/**
	* @fn GetMainCamera
	* @brief メインカメラを返す
	* @return std::shared_ptr<Camera>
	*/
	inline std::shared_ptr<Camera> GetMainCamera() const noexcept;

	/**
　　 * @fn　Get2DCamera
　　 * @brief 2Dカメラの取得
　　 * @return std::shared_ptr<Camera2D>
　　*/
	inline std::shared_ptr<Camera2D> Get2DCamera();

private:
	void Debug();
};

//----------------- INLINES ---------------------

inline void CameraManager::SetMainCameraByName(std::string_view _cameraName)
{
	if (!mpCameraList.contains(_cameraName.data()))
	{
		return;
	}
	mMainCamera = mpCameraList[_cameraName.data()];
	mMainCameraName = _cameraName;
}

inline std::shared_ptr<Camera> CameraManager::GetMainCamera() const noexcept
{
	return mMainCamera ? mMainCamera : nullptr;
}

inline std::shared_ptr<Camera2D> CameraManager::Get2DCamera()
{
	return m2DCamera;
}

template<typename T>
inline std::shared_ptr<T> CameraManager::CreateCamera(std::string_view _cameraName)
{
	// 同名のカメラがすでにあればそれを返す
	if (mpCameraList.contains(_cameraName.data()))
	{
		return std::static_pointer_cast<T>(mpCameraList[_cameraName.data()]);
	}

	// カメラの作成
	std::shared_ptr<T> camera = std::make_shared<T>();
	std::static_pointer_cast<Camera>(camera)->InitBase();
	std::static_pointer_cast<Camera>(camera)->SetName(_cameraName.data());
	mpCameraList[_cameraName.data()] = camera;

	return camera;
}

template<typename T>
inline std::shared_ptr<T> CameraManager::GetCameraByName(std::string_view _cameraName)
{
	// 名前が一致するカメラがあれば返す
	if (mpCameraList.contains(_cameraName.data()))
	{
		return std::static_pointer_cast<T>(mpCameraList[_cameraName.data()]);
	}
	return std::shared_ptr<T>();
}
