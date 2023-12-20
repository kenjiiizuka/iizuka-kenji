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
	void SetMainCamera(const std::string _cameraName) 
	{
		if (mpCameraList.count(_cameraName) > 0)
		{
			mMainCamera = mpCameraList[_cameraName];
			mMainCameraName = _cameraName;
		}
	}
	
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

	template<typename T>
	std::shared_ptr<T> CreateCamera(std::string _cameraName) 
	{
		if (mpCameraList.count(_cameraName) > 0) 
		{
			return nullptr;
		}
		std::shared_ptr<T> camera = std::make_shared<T>();
	    std::static_pointer_cast<Camera>(camera)->InitBase();
		std::static_pointer_cast<Camera>(camera)->SetName(_cameraName);
		mpCameraList[_cameraName] = camera;
	
		return camera;
	}

	template<typename T>
	std::shared_ptr<T> GetCamera(std::string _cameraName) 
	{
		if (mpCameraList.count(_cameraName) > 0) 
		{
			return std::static_pointer_cast<T>(mpCameraList[_cameraName]);
		}
		return nullptr;
	}

	std::shared_ptr<Camera> GetMainCamera()
	{
		return mMainCamera ? mMainCamera : nullptr;
	}

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

inline std::shared_ptr<Camera2D> CameraManager::Get2DCamera()
{
	return m2DCamera;
}
