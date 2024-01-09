/**
* @file Camera.h
* @class Cameraクラスの定義
*/

#pragma once

//---------- INCLUDES ----------
#include "../GameObject.h"

/**
* @class Camera
* @brief View行列とProjection行列を計算
*/
class Camera :  public GameObject
{
public:
    /**
    * コンストラクタ
    */
    Camera();

    /**
    * デストラクタ
    */
    ~Camera();

protected:
    /** カメラの名前 */
    std::string mName;

    /** 注視点 */
    DirectX::SimpleMath::Vector3 mFocusPosition;

    /** 上向きベクトル */
    DirectX::SimpleMath::Vector3 mUpVector;

    /** ビュー変換行列 */
    DirectX::SimpleMath::Matrix mViewMatrix;

    /** プロジェクション変換行列 */
    DirectX::SimpleMath::Matrix mProjectionMatrix;

    /** 振動ベクトル */
    DirectX::SimpleMath::Vector3 mShakeVector;

    /** ビュー、プロジェクション変換行列 */
    static DirectX::SimpleMath::Matrix mViewProjection[2];

    /** 視野 */
    float mFieldOfView;

    /** ニアクリップ */
    float mNearClip;

    /** ファークリップ */
    float mFarClip;

    /** アスペクト比 */
    float mAspectRatio;

    /** 振動レベル */
    uint8_t mShakeLevel;

    /** 振動中なのか */
    bool mbShake;

    /** カメラ振動の時間 */
    double mShakeTime;

    /** 振動開始してからの経過時間 */
    double mElapsedShakeTime;

    /** 振動の最大値 */
    DirectX::SimpleMath::Vector2 mMaxShakeVector;

public:
    /**
　　* @fn Init
    * @brief 初期化処理
　　* @return void
　　*/
    void Init() override;

    /**
    * @fn Update
    * @brief 更新処理
    * @param const double (_deltaTime)
    * @return void
    */
    void Update(const double _deltaTime) override;

    /**
　　* @fn Draw
    * @brief 描画処理 ビューとプロジェクション行列の計算
　　* @return void
　　*/
    void Draw() override;

    /**
    * @fn CameraShake
    * @brief カメラ振動関数
    * @param const uint8_t (_shakeLevel) カメラ振動のレベル 
    * @param const DirectX::SimpleMath::Vector2 (_maxShakeVector) 最大の振動値
    * @param const double  (_shakeTime)  カメラ振動時間
    * @return void
    */
    void CameraShake(const uint8_t _shakeLevel, const DirectX::SimpleMath::Vector2 _maxShakeVector = {1.0f,1.0f}, const double _shakeTime = 1.0f);

protected:
    /**
    * @fn CalcuFocusPosition
    * @brief 注視点を計算する
    * @return void
    */
    virtual void CalcuFocusPosition();

    /**
    * @fn CameraShakeBase
    * @brief 実際に振動の処理をする関数
    * @parm 
    */
    virtual void CameraShakeBase();

public:
    /**
　　* @fn GetName
    * @brief カメラの名前を返す
　　* @return std::string
　　*/
    inline std::string GetName();

    /**
　　* @fn SetName
    * @brief カメラの名前をセットする関数
　　* @return void
　　*/
    inline void SetName(const std::string& _name);

    /**
    * @fn GetFieldOfView
    * @brief 視野を返す
    * @return float 
    */
    inline float GetFieldOfView() const noexcept;

    /**
    * @fn GetNearClip
    * @brief ニアクリップを返す
    * @return float
    */
    inline float GetNearClip() const noexcept;

    /**
    * @fn GetFarClip
    * @brief ファークリップを返す
    * @return float
    */
    inline float GetFarClip() const noexcept;

    /**
    * @fn GetAspectRatio
    * @brief アスペクト比を返す
    * @return float 
    */
    inline float GetAspectRatio() const noexcept;

    /**
    * @fn GetFocusPosition
    * @brief 注視点を返す
    * @return DirectX::SimpleMath::Vector3
    */
    inline DirectX::SimpleMath::Vector3 GetFocusPosition() const noexcept;

    /**
    * @fn GetUp
    * @brief カメラの上方向を返す
    * @return DirectX::SimpleMath::Vector3
    */
    inline DirectX::SimpleMath::Vector3 GetUp() const noexcept; 

    /**
    * @fn GetCameraPosition
    * @brief カメラの座標を返す
    * @return DirectX::SimpleMath::Vector3
    */
    inline DirectX::SimpleMath::Vector3 GetCameraPosition() const noexcept;

    /**
    * @fn GetProjectionMatrix
    * @brief プロジェクションマトリックスを返す
    * @return void
    */
    inline DirectX::SimpleMath::Matrix GetProjectionMatrix() const noexcept;

    /**
    * @fn GetViewMatrix
    * @brief ビュー行列を返す
    * @return DirectX::SimpleMath::Matrix
    */
    inline DirectX::SimpleMath::Matrix GetViewMatrix() const noexcept;

};

//---------------- INLINSE ------------------

inline std::string Camera::GetName()
{
    return mName;
}

inline void Camera::SetName(const std::string& _name)
{
    mName = _name;
}

inline float Camera::GetFieldOfView() const noexcept
{
    return mFieldOfView;
}

inline float Camera::GetNearClip() const noexcept
{
    return mNearClip;
}

inline float Camera::GetFarClip() const noexcept
{
    return mFarClip;
}

inline float Camera::GetAspectRatio() const noexcept
{
    return mAspectRatio;
}

inline DirectX::SimpleMath::Vector3 Camera::GetFocusPosition() const noexcept
{
    return mFocusPosition;
}

inline DirectX::SimpleMath::Vector3 Camera::GetUp() const noexcept
{
    return mUpVector;
}

inline DirectX::SimpleMath::Vector3 Camera::GetCameraPosition() const noexcept
{
    return mTransform.lock()->GetPosition();
}

inline DirectX::SimpleMath::Matrix Camera::GetProjectionMatrix() const noexcept
{
    return mProjectionMatrix;
}

inline DirectX::SimpleMath::Matrix Camera::GetViewMatrix() const noexcept
{
    return mViewMatrix;
}
