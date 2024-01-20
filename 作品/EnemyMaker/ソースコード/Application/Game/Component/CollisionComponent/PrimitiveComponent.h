/**
* @file  PrimitiveComponent.h
* @brief 各形状の情報を持つクラスの基底クラス
*/

#pragma once

//---------- INCLUDES ------------
#include <array>
#include <memory>
#include "../Component.h"
#include "../TransformComponent/Transform.h"
#include "../../../System/CollisionSystem/Collision.h"

//------------前方宣言 --------------
class TransformComponent;
class Bone;
class SkeletalMesh;

using CollisionTypes = std::array<Collision::Type, Collision::Channel_Max>;

/**
* @class PrimitiveComponent.h
* @brief 当たり判定の機能を持つクラスの基底クラス
* @detail ゲームオブジェクトの位置を参照し座標を合わせている
*         ボーンにアタッチする機能がある
*         現在のフレームでコリジョンに当たっていれば、GameObjectのBeginHit関数を実行している
*/
class PrimitiveComponent : public Component
{
public:
    /**
    * 値の初期化
    */
    PrimitiveComponent(Collision::PrimitiveType _primitiveType);

private:
    /** コリジョンが有効なのか */
    bool mbActiveCollision;

    /** 現在当たっている */
    bool bCurrentHit;

    /** 現フレームで重なりを修正したか */
    bool bCurrentFrameFixOverlap;

    /** 重なって修正した量 */
    DirectX::SimpleMath::Vector3 mFixOverlap;


protected:
    /** 現フレームで当たっているコリジョン */
    std::vector<PrimitiveComponent*> mCurrentHitCollisions; 

    /** 新規で当たったコリジョン */
    std::vector<PrimitiveComponent*> mBeginHitCollisions;

    /** 前フレームで当たっていたコリジョン */
    std::vector<PrimitiveComponent*> mPrevHitCollisions;
 
    /** 衝突が発生した位置 */
    DirectX::SimpleMath::Vector3 mImpactPosition;

    /** このコリジョンの形状 */
    Collision::PrimitiveType mPrimitiveType;

    /** このコリジョンのチャンネル */
    Collision::Channel mChannel;

    /** ほかのコリジョンチャンネルとの当たり判定の取り方を種類 */
    CollisionTypes mCollisionTypes;
    
    /** このコリジョンは動くのか */
    bool bMoveable;

    /** トランスフォーム */
    Transform mTransform;

    /** オフセットトランスフォーム */
    Transform mOffSetTransform;

    /** このコリジョンコンポーネントのオーナーのトランスフォームコンポーネント */
    std::weak_ptr<TransformComponent> mOwnerTransform; 

    /**スケール */
    DirectX::SimpleMath::Vector3 mScale;

    /** 前回の座標 */
    DirectX::SimpleMath::Vector3 mOldPos;

    /** アタッチされているボーン */
    std::weak_ptr<Bone> mAttachedBone;

    /** アタッチされているボーンを持っているスケルタルメッシュ */
    std::weak_ptr<SkeletalMesh> mSkeletalMesh;

    /** ボーン行列 */
    DirectX::SimpleMath::Matrix mBoneMatrix;

    /** コリジョンの描画色 */
    DirectX::SimpleMath::Vector4 mColor;

    /** コリジョンヒット時の色 */
    DirectX::SimpleMath::Vector4 mHitColor;

    /** コリジョン未ヒット時の色 */
    DirectX::SimpleMath::Vector4 mDefaultColor;

    /** このコリジョンワールド行列 */
    DirectX::SimpleMath::Matrix mWorldMatrix;

public:
    /**
　　 * @fn　Init
　　 * @brief 初期化処理
　　 * @return void
　　*/
    void Init() override;

    /**
　　 * @fn　Uninit
　　 * @brief 終了処理
　　 * @return void
　　*/
    void Uninit() override;

    /**
　　 * @fn　Update
　　 * @brief 更新処理
　　 * @return void
　　*/
    void Update(const double _deltaTime) override;
 
    /**
　　 * @fn　LastUpdate
　　 * @brief 最終更新処理
　　 * @return void
　　*/
    void LastUpdate() override;

private:
    /**
　　 * @fn　CalucCollisionTransform
　　 * @brief コリジョンの位置を求める
　　 * @return void
　　*/
    virtual void CalucCollisionTransform();

    /**
    * @fn ExecuteBeginHit
    * @brief オーナーのBeginHitを実際に実行する関数
    * @return void
    */
    virtual void ExecuteBeginHit();

public:
    /**
　　 * @fn　FixOverlap
　　 * @brief 重なりを修正する関数
     * @param DirectX::SimpleMath::Vector3 (_depth) 重なり 
　　 * @return void
　　*/
    void FixOverlap(DirectX::SimpleMath::Vector3 _depth);

    /**
　　 * @fn　GetAttachedBone
　　 * @brief アタッチされているボーンのゲッター
　　 * @return std::weak_ptr<Bone> アタッチされているボーン
　　*/
    std::weak_ptr<Bone> GetAttachedBone();

    /**
　　 * @fn　AttachBone
　　 * @brief ボーンをアタッチする関数
　　 * @param const std::shared_ptr<Bone>          (_attachBone) アタッチするボーン
     * @param  const std::shared_ptr<SkeletalMesh> (_skeletalMesh) アタッチするボーンを持っているスケルタルメッシュ
     * @return void 
　　*/
    void AttachBone(const std::shared_ptr<Bone> _attachBone, const std::shared_ptr<SkeletalMesh> _skeletalMesh);

    /**
　　 * @fn　AttachBone
　　 * @brief ボーンをアタッチする関数
　　 * @param BoneData* (_attachBone) アタッチするボーン
     * @return void
　　*/
    void AddCurrentHitCollisions(PrimitiveComponent* _currnetHitCollision);

    /**
　　 * @fn　GetOwnerTransform
　　 * @brief オーナーのトランスフォームを返す
　　 * @return std::weak_ptr<TransformComponent> オーナーのトランスフォームコンポーネント
　　*/
    inline std::weak_ptr<TransformComponent> GetOwnerTransform();

    /**
　　 * @fn　
   　* GetScale
　　 * @brief この形状のスケールを返す
　　 * @return DirectX::SimpleMath::Vector3 スケール
　　*/
    inline DirectX::SimpleMath::Vector3 GetScale();

    /**
　　 * @fn　IsMoveable
　　 * @brief このコリジョンが動くかを返す
　　 * @return bool 動くか
　　*/
    inline bool IsMoveable();

    /**
　　 * @fn　SetMovable
　　 * @brief このコリジョンが動くかどうかをセットする
     *        true 動く : false 動かない
　　 * @return void
　　*/
    inline void SetMovable(bool _able);

    /**
　　 * @fn　GetOldPos
　　 * @brief このコリジョンの前回の座標を返す
　　 * @return DirectX::SimpleMath::Vector3 前回の座標
　　*/
    inline DirectX::SimpleMath::Vector3 GetOldPos();

    /**
　　 * @fn　SetOffSetTransform
　　 * @brief コリジョンのオフセットトランスフォームのセッター
     * @param Transform (_transform) オフセットトランスフォーム 
　　 * @return void
　　*/
    inline void SetOffSetTransform(Transform _transform);

    /**
　　 * @fn　SetOffSetTransform
　　 * @brief コリジョンのオフセットトランスフォームのゲッター
　　 * @return void
　　*/
    inline Transform GetOffSetTransform();

    /**
　　 * @fn　SetOffSetPosition
　　 * @brief コリジョンのオフセットポジションのｓセッター
     * @param DirectX::SimpleMath::Vector3 (_offsetPosition) オフセット位置
　　 * @return void
　　*/
    inline void SetOffSetPosition(DirectX::SimpleMath::Vector3 _offsetPosition);

    /**
　　 * @fn　GetTransform
　　 * @brief コリジョンのトランスフォームのゲッター
　　 * @return Transform
　　*/
    inline Transform GetTransform();

    /**
　　 * @fn　GetHit
　　 * @brief 当たっているかを返す
　　 * @return bool 当たっているか true : 当たっている false : 当たっていない
　　*/
    inline bool IsCurrentHit();
 
    /**
　　 * @fn　SetCollisionChannel
　　 * @brief コリジョンチャンネルのセッター
     * @param Collision::Channel (_channel) チャンネル
　　 * @return void
　　*/
    inline void SetCollisionChannel(Collision::Channel _channel);

    /**
　　 * @fn　SetCollisionTypes
　　 * @brief コリジョンタイプのセッター
     * @param CollisionTypes (_collisionTypes) コリジョンタイプ
　　 * @return void
　　*/
    inline void SetCollisionTypes(CollisionTypes _collisionTypes);

    /**
　　 * @fn　SetCollisionTypes
　　 * @brief コリジョンタイプのセッター
     * @param Collision::Channel (_channel) コリジョンタイプを新たにセットするチャンネル
     * @param Collision::Type (_collisionType) コリジョンタイプ
　　 * @return void
　　*/
    inline void SetCollisionTypes(Collision::Channel _channel, Collision::Type _collisionType);

    /**
　　 * @fn　GetCollisionChannel
　　 * @brief コリジョンチャンネルのゲッター
　　 * @return Collision::Channel コリジョンチャンネル
　　*/
    inline Collision::Channel GetCollisionChannel();

    /**
　　 * @fn　GetCollisionTypes
　　 * @brief コリジョンタイプのゲッター
　　 * @return CollisionTypes
　　*/
    inline CollisionTypes GetCollisionTypes();

    /**
　　 * @fn　GetCollisionType
　　 * @brief 引数で指定されたチャネルのコリジョンタイプのゲッター
　　 * @return Collision::Type コリジョンタイプ
　　*/
    inline Collision::Type GetCollisionType(Collision::Channel _channel);

    /**
　　 * @fn　SetDefaultColor
　　 * @brief 通常時のカラーのセッター
     * @param DirectX::SimpleMath::Vector4 (_color) 色
　　 * @return CollisionTypes
　　*/
    inline void SetDefaultColor(DirectX::SimpleMath::Vector4 _color);

    /**
　　 * @fn　SetHitColor
　　 * @brief ヒット時のカラーのセッター
     * @param DirectX::SimpleMath::Vector4 (_color) 色
　　 * @return CollisionTypes
　　*/
    inline void SetHitColor(DirectX::SimpleMath::Vector4 _color);

    /**
    * @fn SetImpactPosition
    * @brief 衝突が発生した位置のセッター
    * @param const DirectX::SimpleMath::Vector3 (_pos)
    * @return void
    */
    inline void SetImpactPosition(const DirectX::SimpleMath::Vector3 _pos) noexcept;

    /**
    * @fn GetImpactPosition
    * @brief 衝突が発生した位置を返す
    * @return DirectX::SimpleMath::Vector3 
    */
    inline DirectX::SimpleMath::Vector3 GetImpactPosition() const noexcept;

    /**
　　 * @fn　IsCurrentFrameFixOverlap
　　 * @brief 現在のフレームで重なりを修正したか
　　 * @return bool true 修正した false してない
　　*/
    inline bool IsCurrentFrameFixOverlap() const;

    /**
　　 * @fn　GetFixOverlap
　　 * @brief 重なりを修正した量を返す
　　 * @return DirectX::SimpleMath::Vector3
　　*/
    inline DirectX::SimpleMath::Vector3 GetFixOverlap() const;

    /**
　　 * @fn　IsCurrentFrameMoved
　　 * @brief 現フレームで移動したか
　　 * @return bool true 移動した false 移動していない
　　*/
     bool IsCurrentFrameMoved() const;

     /**
     * @fn GetCurrentHitCollision
     * @brief 現在あ立っているコリジョンを返す
     * @return std::vector<PrimitiveComponent*> 
     */
     inline std::vector<PrimitiveComponent*> GetCurrentHitCollisions() const;

     /**
　　 * @fn IsActiveCollision
　　 * @brief このコリジョンが有効なのかを返す
　　 * @return bool true コリジョンが有効  false コリジョンが無効
　　*/
     inline bool IsActiveCollision() const noexcept;

     /**
 　　 * @fn SetActiveCollision
 　　 * @brief コリジョンの有効無効の切り替え
      * @param bool (_active)
 　　 * @return void
 　　*/
     inline void SetActiveCollision(bool _active) noexcept;

     /**
     * @fn GetPrimitiveType
     * @brief プリミティブタイプを返す
     * @return Collision::PrimitiveType
     */
     inline Collision::PrimitiveType GetPrimitiveType() const noexcept;
};


// -------------------- INLINES -------------------------------

inline std::weak_ptr<TransformComponent> PrimitiveComponent::GetOwnerTransform()
{
    return mOwnerTransform;
}

inline DirectX::SimpleMath::Vector3 PrimitiveComponent::GetScale()
{
    return mScale;
}

inline bool PrimitiveComponent::IsMoveable()
{
    return bMoveable;
}

inline void PrimitiveComponent::SetMovable(bool _moveable)
{
    bMoveable = _moveable;
}

inline DirectX::SimpleMath::Vector3 PrimitiveComponent::GetOldPos()
{
    return mOldPos;
}

inline void PrimitiveComponent::SetOffSetTransform(Transform _transform)
{
    mOffSetTransform = _transform;
}

inline Transform PrimitiveComponent::GetOffSetTransform()
{
    return mOffSetTransform;
}

inline void PrimitiveComponent::SetOffSetPosition(DirectX::SimpleMath::Vector3 _offsetPosition)
{
    mOffSetTransform.mPosition = _offsetPosition;
}

inline Transform PrimitiveComponent::GetTransform()
{
    return mTransform;
}

inline bool PrimitiveComponent::IsCurrentHit()
{
    return bCurrentHit;
}

inline void PrimitiveComponent::SetCollisionChannel(Collision::Channel _channel)
{
    mChannel = _channel;
}

inline void PrimitiveComponent::SetCollisionTypes(CollisionTypes _collisionTypes)
{
    mCollisionTypes = _collisionTypes;
}

inline void PrimitiveComponent::SetCollisionTypes(Collision::Channel _channel, Collision::Type _collisionType)
{
    if (_channel < mCollisionTypes.size())
    {
        mCollisionTypes[_channel] = _collisionType;
    } 
}

inline Collision::Channel PrimitiveComponent::GetCollisionChannel()
{
    return mChannel;
}

inline CollisionTypes PrimitiveComponent::GetCollisionTypes()
{
    return mCollisionTypes;
}

inline Collision::Type PrimitiveComponent::GetCollisionType(Collision::Channel _channel)
{
    return mCollisionTypes[_channel];
}

inline void PrimitiveComponent::SetDefaultColor(DirectX::SimpleMath::Vector4 _color)
{
    mDefaultColor = _color;
}

inline void PrimitiveComponent::SetHitColor(DirectX::SimpleMath::Vector4 _color)
{
    mHitColor = _color;
}

inline void PrimitiveComponent::SetImpactPosition(const DirectX::SimpleMath::Vector3 _pos) noexcept
{
    mImpactPosition = _pos;
}

inline DirectX::SimpleMath::Vector3 PrimitiveComponent::GetImpactPosition() const noexcept
{
    return mImpactPosition;
}

inline bool PrimitiveComponent::IsCurrentFrameFixOverlap() const
{
    return bCurrentFrameFixOverlap;
}

inline DirectX::SimpleMath::Vector3 PrimitiveComponent::GetFixOverlap() const
{
    return mFixOverlap;
}

inline std::vector<PrimitiveComponent*> PrimitiveComponent::GetCurrentHitCollisions() const
{
    return mCurrentHitCollisions;
}

inline bool PrimitiveComponent::IsActiveCollision() const noexcept
{
    return mbActiveCollision;
}

inline void PrimitiveComponent::SetActiveCollision(bool _active) noexcept
{
    mbActiveCollision = _active;
}

inline Collision::PrimitiveType PrimitiveComponent::GetPrimitiveType() const noexcept
{
    return mPrimitiveType;
}

