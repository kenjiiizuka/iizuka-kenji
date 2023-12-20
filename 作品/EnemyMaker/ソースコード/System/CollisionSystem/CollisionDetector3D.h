#pragma once
#include <SimpleMath.h>
#include "ICollisionDetector.h"
#include "../../Game/Component/CollisionComponent/PrimitiveShapes.h"

/**
* @file  CollisionDetector3D.h
* @brief CollisionDetector3Dクラスの定義とコリジョン検出に使用する構造体の定義
*/


//------------ 前方宣言 ------------
class CapsuleCollisionComponent;
class RingCollisionComponent;

/**
* @class CollisionDetector3D
* @brief 3Dコリジョンの重なりを検出する機能をもつクラス
*/
class CollisionDetector3D final : public ICollisionDetector
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	CollisionDetector3D() { /* 処理なし */ }

	/**
	* デストラクタ
	*/
	~CollisionDetector3D() {/* 処理なし */ }

public:
	/**
　　 * @fn DetectorOverlap
	 * @brief 渡されたコリジョン同士で重なりを検出する
	 * @dettails 渡されコリジョンの形状を判別し、組み合わせにあった重なり検出用の関数実行
	 *           これ以上のオーバーライドを禁止するために final 指定
	 * @param PrimitiveComponent* (_subject1)
	 * @param PrimitiveComponent* (_subject2)
　　 * @return bool true 重なり検出　false 重なり無し
　　*/
	void DetectorOverlap(PrimitiveComponent* _subject1, PrimitiveComponent* _subject2) final override;

private:
	/**
	 * @fn CheckExecuteDetector
	 * @brief 重なり検出をすうか判断する関数
	 * @details 対象のコリジョンのコリジョンタイプとコリジョンチャンネルを確認し、重なり検出をする必要があるかをチェックする
	 * @param PrimitiveComponent* (_subject1)
	 * @param PrimitiveComponent* (_subject2)
	 * @return bool  true 検出する : false 検出しない
	*/
	bool CheckExecuteDetector(PrimitiveComponent* _subject1, PrimitiveComponent* _subject2);

	/**
     * @fn DetectorCapsuleAndCapsuleOverlap
     * @brief カプセルとカプセルの重なり検出
	 * @details カプセル同氏の重なり検出を行い,第三引数に重なっているベクトルを返す
     * @param CapsuleCollisionComponent* (_capsule1) カプセル1
     * @param CapsuleCollisionComponent* (_capsule2) カプセル2
	 * @param DirectX::SimpleMath::Vector3& (_outputOverlapped) 重なっている量
     * @return bool  true 当たり : false 当たっていない
    */
	bool DetectorCapsuleAndCapsuleOverlap(CapsuleCollisionComponent* _capsule1, CapsuleCollisionComponent* _capsule2, DirectX::SimpleMath::Vector3& _outputOverlaped);

	/**
	* @class DetectorPointAndRingOverlap
	* @brief 点とリングの重なり検出
	* @param RingCollisionComponent*       (_ring)
	* @param PrimitiveComponent*           (_point)
	* @param DirectX::SimpleMath::Vector3& (_outputOverlapped)
	* @return bool  true 当たり : false 当たっていない
	*/
	bool DetectorPointAndRingOverlap(RingCollisionComponent* _ring, PrimitiveComponent* _point, DirectX::SimpleMath::Vector3& _outputOverlaped);

	/**
	 * @fn FixOverlap
	 * @brief Blockの処理
	 * @details 重なりを修正する処理
	 *          お互い動いていたら重なり量の半分ずつどちらも修正する
	 *          片方のみ動いていたなら動いていた方を重なり量分修正する
	 * @param PrimitiveComponent* (_subject1)
	 * @param PrimitiveComponent* (_subject2)
	 * @param const DirectX::SimpleMath::Vector3& (_overlapedVetor)
	 * @return void
	*/
	void FixOverlap(PrimitiveComponent* _subject1, PrimitiveComponent* _subject2, const DirectX::SimpleMath::Vector3& _overlapedVetor);

	/**
	 * @fn CalucSegment3DToSegment3DDistance
	 * @brief　直線と直線の最短距離を求める関数
	 * @param const PrimitiveShape::Segment3D& (_segment1) 直線1
	 * @param const PrimitiveShape::Segment3D& (_segment2) 直線2
	 * @param DirectX::SimpleMath::Vector3& (_outputVector) 最短距離がどの方向に伸びているか
	 * @return float 最短距離 
	*/
	float CalucSegment3DToSegment3DDistance(const PrimitiveShape::Segment3D& _segment1, const PrimitiveShape::Segment3D& _segment2, DirectX::SimpleMath::Vector3& _outputVector);

	/**
	 * @fn CalucLineLineDistance
	 * @brief　直線と直線の最短距離を求める関数
	 * @param const PrimitiveShape::Segment3D& (_segment1) 線分1
	 * @param const PrimitiveShape::Segment3D& (_segment1) 線分2
	 * @param DirectX::SimpleMath::Vector3& (_minPoint1) 最短の垂線の端点1
	 * @param DirectX::SimpleMath::Vector3& (_minPoint2) 最短の垂線の端点2
	 * @param float& (_t1) segment1の開始地点からminPoint1までの比率
	 * @param float& (_t2) segment2の開始地点からminPoint2までの比率
	 * @return float 直線と直線の最短距離
	*/
	float CalucLineLineDistance(const PrimitiveShape::Segment3D& _segment1, const PrimitiveShape::Segment3D& _segment2, DirectX::SimpleMath::Vector3& _minPoint1, DirectX::SimpleMath::Vector3 _minPoint2, float& _t1, float& _t2);


	/**
	 * @fn CalucPointLineDistance
	 * @brief　直線と点の最短距離を求める関数
	 * @param const DirectX::SimpleMath::Vector3& (_point) 
	 * @param const PrimitiveShape::Segment3D& (_segment)
	 * @param DirectX::SimpleMath::Vector3& (_outputIntersection) 点から線分へ最短距離で線を引いた時の交差点
	 * @param float& (_t) 点から線分に対して最短距離で線を引いたときの交わる点の線分上の比率
	 * @return float 点から線分への最短距離
	*/
	float CalucPointLineDistance(const DirectX::SimpleMath::Vector3& _point, const PrimitiveShape::Segment3D& _segment, DirectX::SimpleMath::Vector3& _outputIntersection, float& _t);

};

