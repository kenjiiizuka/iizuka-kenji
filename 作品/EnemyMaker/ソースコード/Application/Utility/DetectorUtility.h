/**
* @file  DetectorUtility.h
* @brief DetectorUtilityクラスの定義をしている
*/

#pragma once

//------------- INCLUDES ---------------
#include <SimpleMath.h>
#include "../Game/Component/CollisionComponent/PrimitiveShapes.h"

/**
* @class DetectorUtility
* @brief 重なり検出などゲームアルゴリズムの中で使用したい機能をもったクラス
*/
class DetectorUtility final
{
public:
    /**
	* デフォルトコンストラクタ
	* Staticなクラスなので = delete 指定
	*/
	DetectorUtility() = delete;

	/**
	 * @fn IsPositionIn2DCircle
	 * @brief 渡された値が指定された円の中に入っているかを返す関数
	 * @param DirectX::SimpleMath::Vector2 (_position)
	 * @param DirectX::SimpleMath::Vector2 (_center)
	 * @param DirectX::SimpleMath::Vector2 (_radius)
	 * @param DirectX::SimpleMath::Vector4 (_color)    デフォルトは赤 {1,0,0,1}
	 * @return void
	*/
	static bool IsPositionInCircle2D(DirectX::SimpleMath::Vector2 _position, DirectX::SimpleMath::Vector2 _center, float _radius, DirectX::SimpleMath::Vector4 _color = { 1,0,0,1 });

	/**
	 * @fn IsPositionInSector2D
	 * @brief 渡された座標が指定されたサイズの扇形の中に入っているかを返す関数
	 * @param const DirectX::SimpleMath::Vector2& (_position)
	 * @param const DirectX::SimpleMath::Vector2& (_sectorCenter)
	 * @param const DirectX::SimpleMath::Vector2& (_sectorEndPoint)
	 * @param const float&                        (_sectorDegree)
	 * @param const DirectX::SimpleMath::Vector4& (_color)    デフォルトは赤 {1,0,0,1}
	 * @return void
	*/
	static bool IsPositionInSector2D(DirectX::SimpleMath::Vector2 _position, DirectX::SimpleMath::Vector2 _sectorCenter, DirectX::SimpleMath::Vector2 _sectorEndPoint, float _sectorDegree, DirectX::SimpleMath::Vector4 _color);

private:
	/**
	 * @fn InSectorCheckXZ
	 * @brief 渡された座標が指定されたサイズの扇形の中に入っているかを返す関数
	 * @param const DirectX::SimpleMath::Vector2& (_sectorCenter)
	 * @param const DirectX::SimpleMath::Vector2& (_sectorEndPoint)
	 * @param const float&                        (_sectorAngle)
	 * @param const DirectX::SimpleMath::Vector2& (_position)
	 * @param const float&                        (length)
	 * @return void
	*/
	static bool InSectorCheckXZ(const DirectX::SimpleMath::Vector2& _sectorCenter, const DirectX::SimpleMath::Vector2& _sectorEndPoint, const float& _sectorAngle, const DirectX::SimpleMath::Vector2& _position, const float& length);

	/**
	 * @fn CalucPointSegmentDistance
	 * @brief 渡された座標が指定されたサイズの扇形の中に入っているかを返す関数
	 * @param const DirectX::SimpleMath::Vector3& (_position)
	 * @param const PrimitiveShape::Segment3D& (_segment)
	 * @param DirectX::SimpleMath::Vector3& (_interSectionPoint)
	 * @param float& (_t) 交点の位置がその線分どの位置にあるかの比率
	 * @return void
	*/
	static float CalucPointSegmentDistance(const DirectX::SimpleMath::Vector3& _position, const PrimitiveShape::Segment3D& _segment, DirectX::SimpleMath::Vector3& _interSectionPoint, float& _t);

	/**
	 * @fn CalucPointLineDist
	 * @brief 点と線分距離を求める
	 * @param const DirectX::SimpleMath::Vector3& (_position)
	 * @param const PrimitiveShape::Segment3D& (_segment)
	 * @param DirectX::SimpleMath::Vector3& (_interSectionPoint)
	 * @param float& (_t) 交点の位置がその線分どの位置にあるかの比率
	 * @return void
	*/
	static float CalucPointLineDist(const DirectX::SimpleMath::Vector3& _position, const PrimitiveShape::Segment3D& _segment, DirectX::SimpleMath::Vector3& _intersectionPoint, float& _t);
};

