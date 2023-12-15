/**
* @file  DebugRendererManager.h
* @brief DebugRendererManagerの定義をしている
* @details デバッグ機能なので、DebugBuildのみ使用可能
*/
#ifdef _DEBUG

#pragma once


//--------------- includes ---------------
#include <vector>
#include <SimpleMath.h>
#include "../../Singleton.h"
#include "../../../Game/Component/TransformComponent/Transform.h"

//-------------- 前方宣言 ----------------
class StaticMesh; // スタティックメッシュではなく、ジオメトリーで描画できるようにしたい
class VisualEntity;

/**
* @class DebugRendererManager
* @brief デバッグ描画用のレンダラーマネージャークラス  
* @details デバッグ用オブジェクトなどを描画する
*          同時に複数を描画するために、Meshの元データをコピーし、コピーを配列に格納し描画する
*/
class DebugRendererManager final : public Singleton<DebugRendererManager>
{
    /**
    * @struct DebugDrawHalfCircle
    * @brief HalfCircleをデバッグ表示する際に必要な情報を持つ
    */
    struct DebugDrawHalfCircle
    {
        /**
        * デフォルトコンストラクタ
        * 必ず引数ありコンストラクタで生成するために = delete 指定
        */
        DebugDrawHalfCircle() = delete;

        /**
        * 引数ありコンストラクタ
        * 
        * @param const uint16_t (_drawFrame)
        * @param const float (_radius)
        */
        DebugDrawHalfCircle(const uint16_t _drawFrame, const float _radius);

        std::shared_ptr<StaticMesh> mMesh;                 /**< 半球メッシュ */
        uint16_t mDrawFrame;                               /**< 描画するフレーム数 */
        uint16_t mCurrentDrewFrameCount;                   /**< 描画したフレーム数 */
        float mRadius;                                     /**< 半径 */
    };

    /**
    * @struct DebugDrawPlane
    * @brief Planeをデバッグ表示する際に必要な情報を持つ
    */
    struct DebugDrawPlane
    {
        /**
         * デフォルトコンストラクタ
         * 必ず引数ありコンストラクタで生成するために = delete 指定
        */
        DebugDrawPlane() = delete;

        /**
         * 引数ありコンストラクタ
         *
         * @param const uint16_t (_drawFrame)
        */
        DebugDrawPlane(const uint16_t _drawFrame);

        std::shared_ptr<StaticMesh> mMesh;                 /**< 板メッシュ */
        uint16_t mDrawFrame;                               /**< 描画するフレーム数 */
        uint16_t mCurrentDrewFrameCount;                   /**< 描画したフレーム数 */
        
        DirectX::SimpleMath::Vector3 mPosition;            /**< 描画位置 */
    };

    /**
    * @struct DebugDrawLine
    * @brief Lineをデバッグ表示する際に必要な情報を持つ
    */
    struct DebugDrawLine
    {
        /**
         * デフォルトコンストラクタ
         * 必ず引数ありコンストラクタで生成するために = delete 指定
        */
        DebugDrawLine() = delete;

        /**
         * 引数ありコンストラクタ
         *
         * @param const uint16_t (_drawFrame)
        */
        DebugDrawLine(const uint16_t _drawFrame);

        std::shared_ptr<VisualEntity> mMesh;               /**< ラインメッシュ */
        uint16_t mDrawFrame;                               /**< 描画するフレーム数 */
        uint16_t mCurrentDrewFrameCount;                   /**< 描画したフレーム数 */
    };

    /**
    * @struct DebugDrawSphere
    * @brief Sphereをデバッグ表示する際に必要な情報を持つ
    */
    struct DebugDrawSphere
    {
        /**
        * デフォルトコンストラクタ
        * 必ず引数ありコンストラクタで生成するために = delete 指定
       */
        DebugDrawSphere() = delete;

        /**
        * 引数ありコンストラクタ
        * 
        * @param const uint16_t (_drawFrame)
        */
        DebugDrawSphere(const uint16_t _drawFrame, const float _radius);

        std::shared_ptr<StaticMesh> mMesh;          /**< スフィアメッシュ */
        uint16_t mDrawFrame;                          /**< 描画するフレーム */
        uint16_t mCurrentDrawFrameCount;              /**< 現在描画したフレーム数 */
        float mRadius;                                /**< 半径 */
    };

private:
    /**----------------------------------------------------------------------------------------------
    * 基底クラスのSingletonクラスからコンストラクタと、デストラクタにアクセスするために必要であり
    * クラス外から生成、破棄できないようにするためにフレンド指定する
    ------------------------------------------------------------------------------------------------*/
    friend Singleton<DebugRendererManager>;

    /**
    * デフォルトコンストラクタ
    */
    DebugRendererManager();

    /**
    * デフォルトデストラクタ
    */
    ~DebugRendererManager();

    /**
    * コピーコンストラクタ
    * コピー禁止のため = delete 指定
    */
    DebugRendererManager(const DebugRendererManager& _from) = delete;

    /**
    * 代入演算子のオーバーロード
    * 代入禁止のため = delete 指定
    */
    void operator=(const DebugRendererManager& _from) = delete;

private:
    /** デバッグ表示用半球オブジェクト */
    std::shared_ptr<StaticMesh> mHalfCircleMesh;

    /** デバッグ表示する半球の配列 */
    std::vector<DebugDrawHalfCircle> mDrawHalfCircels;

    /** デバッグ表示用板オブジェクト */
    std::shared_ptr<StaticMesh> mPlaneMesh;

    /** デバッグ表示する板の配列 */
    std::vector<DebugDrawPlane> mDrawPlanes;

    /** デバッグ描画用のライン */
    std::vector<DebugDrawLine> mDrawLines;

    /** デバッグ表示用球メッシュ */
    std::shared_ptr<StaticMesh> mSphereMesh;

    /** デバッグ表示する球の配列 */
    std::vector<DebugDrawSphere> mDrawSpheres;
public:
    /**
     * @fn Init
     * @brief 初期化処理
   　* @details デバッグ表示用メッシュの読み込みをしている
     * @return void
    */
    void Init();
  
    /**
     * @fn Update
     * @brief 更新処理
　   * @details デバッグ表示オブジェクトが指定されたフレーム数描画されていたら配列から削除する
     * @return void
    */
    void Update();

    /**
     * @fn Draw
     * @brief 描画に関連する処理
　   * @details デバッグ表示オブジェクトが何フレーム描画されたかをカウントする
     * @return void
    */
    void Draw();

private:
    /**
     * @fn DrawSetup
     * @brief 描画のセットアップ
　   * @details ワールド変換行列のセットとマテリアルの設定
     * @param const Transform& (_trans)
     * @param const std::shared_ptr<VisualEntity> (_visualEntity)
     * @param const DirectX::SimpleMath::Vector4& (_diffuse)
     * @return void
    */
    void DrawSetup(const Transform& _trans, std::shared_ptr<VisualEntity> _visualEntity, const DirectX::SimpleMath::Vector4& _diffuse);

public:
    /**
     * @fn DrawHalfCircle
     * @brief 指定された半径でサークルを指定されたフレーム間表示
     * @param const float                        (_radius)
     * @param const DirectX::SimpleMath::Vector3 (_position)
     * @param const uint16_t                     (_drawFrame) デフォルトは1フレーム
     * @param consr DirectX::SimpleMath::Vector4 (_color)     デフォルトは {1,0,0,1} 赤
     * @return void
    */
    void DrawHalfCircle(const float _radius, const DirectX::SimpleMath::Vector3 _position, const uint16_t _drawFrame = 1, const DirectX::SimpleMath::Vector4 _color = {1,0,0,1});

    /**
     * @fn DrawPlane
     * @brief 指定された位置と大きさと回転で指定されたフレーム間表示する
     * @param const DirectX::SimpleMath::Vector3 (_position)
     * @param const DirectX::SimpleMath::Vector3 (_scale)
     * @param const DirectX::SimpleMath::Vector3 (_rotation)
     * @param const uint16_t                     (_drawFrame) デフォルトは1フレーム
     * @param consr DirectX::SimpleMath::Vector4 (_color)     デフォルトは {1,0,0,1} 赤
     * @return void
    */
    void DrawPlane(const DirectX::SimpleMath::Vector3 _position, const DirectX::SimpleMath::Vector3 _scale, const DirectX::SimpleMath::Vector3 _rotation, const uint16_t _drawFrame = 1, const DirectX::SimpleMath::Vector4 _color = { 1,0,0,1 });


    /**
     * @fn DrawSegment
     * @brief 指定された位置と大きさと回転で指定されたフレーム間表示する
     * @param const DirectX::SimpleMath::Vector3 (_startPosition)
     * @param const DirectX::SimpleMath::Vector3 (_endPosition)
     * @param const uint16_t                     (_drawFrame) デフォルトは1フレーム
     * @param const DirectX::SimpleMath::Vector4 (_color)     デフォルトは {1,0,0,1} 赤
     * @return void
    */
    void DrawSegment(const DirectX::SimpleMath::Vector3 _startPosition, const DirectX::SimpleMath::Vector3 _endPosition, const uint16_t _drawFrame = 1, const DirectX::SimpleMath::Vector4 _color = { 1,0,0,1 });

    /**
    * @fn DrawSphere
    * @brief 球を表示する
    * @param const DirectX::SimpleMath::Vector3 (_centerPosition)
    * @param const float                        (_radius)
    * @param const uint16_t                     (_drawFrame)
    * @param const DirectX::SimpleMath::Vector4 (_color)
    * @return void
    */
    void DrawSphere(const DirectX::SimpleMath::Vector3 _centerPosition, const float _radius, const uint16_t _drawFrame = 1, const DirectX::SimpleMath::Vector4 _color = { 1,0,0,1 });
};

#endif // _DEBUG