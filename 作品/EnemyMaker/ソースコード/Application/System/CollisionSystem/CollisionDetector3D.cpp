//---------- INCLUDES -----------
#include "CollisionDetector3D.h"
#include "../../Game/Component/CollisionComponent/PrimitiveComponent.h"
#include "../../Game/Component/CollisionComponent/CapsuleCollisionComponent.h"
#include "../../Game/Component/CollisionComponent/CircleCollisionComponent.h"
#include "../../Utility/MathLibrary.h"
#include "../../Game/GameObject/GameObject.h"

//--------------- 名前空間エイリアス ---------------
namespace DXSimpleMath = DirectX::SimpleMath;


void CollisionDetector3D::DetectorOverlap(PrimitiveComponent* _subject1, PrimitiveComponent* _subject2)
{
	// 重なり検出をする必要がないなら早期リターン
	if (!CheckExecuteDetector(_subject1, _subject2))
	{
		return;
	}
	
	// 形状の判定
	Collision::PrimitiveType subject1PrimitiveType = _subject1->GetPrimitiveType();
	Collision::PrimitiveType subject2PrimitiveType = _subject2->GetPrimitiveType();

	// 重なり検出をする 
	DXSimpleMath::Vector3 overlap; // 重なっている量

	if (subject1PrimitiveType == Collision::PrimitiveType_Capsule && subject2PrimitiveType == Collision::PrimitiveType_Capsule)
	{	
		if (DetectorCapsuleAndCapsuleOverlap(static_cast<CapsuleCollisionComponent*>(_subject1), static_cast<CapsuleCollisionComponent*>(_subject2), overlap))
		{
			_subject1->AddCurrentHitCollisions(_subject2);
			_subject2->AddCurrentHitCollisions(_subject1);
			FixOverlap(_subject1, _subject2, overlap);
		}
	}

	else if(subject1PrimitiveType == Collision::PrimitiveType_Capsule && subject2PrimitiveType == Collision::PrimitiveType_Ring)
	{
		if (DetectorPointAndRingOverlap(static_cast<RingCollisionComponent*>(_subject2), static_cast<CapsuleCollisionComponent*>(_subject1), overlap))
		{
			_subject1->AddCurrentHitCollisions(_subject2);
			_subject2->AddCurrentHitCollisions(_subject1);
			FixOverlap(_subject1, _subject2, overlap);
		}
	}
}

bool CollisionDetector3D::CheckExecuteDetector(PrimitiveComponent* _subject1, PrimitiveComponent* _subject2)
{
	// コンポーネントが有効なのかを判断する
	if (!(_subject1->IsActiveCollision() && _subject2->IsActiveCollision()))
	{
		return false;
	}

	// subject1がsubject2に対してのコリジョンのタイプがNoneならfalseを返す
	// ※ コリジョンタイプはそのコリジョンチャンネル対してどのような対応をするのかを表す
	if (_subject1->GetCollisionType(_subject2->GetCollisionChannel()) == Collision::Type_None)
	{
		return false;
	}

	// subject2がsubject1に対してのコリジョンのタイプがNone以外なら重なり検出をする Noneならしない
	return _subject2->GetCollisionType(_subject1->GetCollisionChannel()) != Collision::Type_None;
}

bool CollisionDetector3D::DetectorCapsuleAndCapsuleOverlap(CapsuleCollisionComponent* _capsule1, CapsuleCollisionComponent* _capsule2, DirectX::SimpleMath::Vector3& _depth)
{
	const float height_1 = _capsule1->GetHeight();
	const float height_2 = _capsule2->GetHeight();
	const float radius_1 = _capsule1->GetRadius();
	const float radius_2 = _capsule2->GetRadius();

	const Transform transform_1 = _capsule1->GetTransform();
	const Transform transform_2 = _capsule2->GetTransform();

	// カプセルを線分として表す(半径を含まない)	
	// カプセル１
	PrimitiveShape::Segment3D segment_1;
	DXSimpleMath::Vector3 up_1 = MathLibrary::GetUpVector(transform_1.mRotation);
	segment_1.mStartPosition = transform_1.mPosition + (up_1 * height_1);
	segment_1.mEndPosition = transform_1.mPosition - (up_1 * height_1);
	// カプセル２
	PrimitiveShape::Segment3D segment_2;
	DXSimpleMath::Vector3 up_2 = MathLibrary::GetUpVector(transform_2.mRotation);
	segment_2.mStartPosition = transform_2.mPosition + (up_2 * height_2);
	segment_2.mEndPosition = transform_2.mPosition - (up_2 * height_2);

	// 重なっている方向
	DXSimpleMath::Vector3 collisionDepth;

	// 線分と線分の最短距離を求め、その最短距離の方向を取得する
	float intersection_1, intersection_2;
	float lineDistance = CalucSegment3DToSegment3DDistance(segment_1, segment_2, collisionDepth, intersection_1, intersection_2);

	if ((lineDistance < (radius_1 + radius_2)))
	{
		DXSimpleMath::Vector3 normalizedDepth = collisionDepth;
		normalizedDepth.Normalize();
		float depthLength = lineDistance - (radius_1 + radius_2);
		_depth = normalizedDepth * depthLength;

		// 当たっている位置を計算
		// 線分上の位置を求める
		DXSimpleMath::Vector3 segmentPos = segment_1.mStartPosition + segment_1.GetVector() * intersection_1;
		// めり込まれている方向に半径分をずらす
		DXSimpleMath::Vector3 hitPosition = segmentPos + (normalizedDepth * _depth);
		_capsule1->SetImpactPosition(hitPosition);
		_capsule2->SetImpactPosition(hitPosition);
		return true;
	}

	return false;
}

bool CollisionDetector3D::DetectorPointAndRingOverlap(RingCollisionComponent* _ring, PrimitiveComponent* _point, DirectX::SimpleMath::Vector3& _outputOverlaped)
{
	float ringRadius = _ring->GetRadius();
	DXSimpleMath::Vector3 ringCenter = _ring->GetTransform().mPosition;
	DXSimpleMath::Vector3 point = _point->GetTransform().mPosition;

	if ((ringCenter - point).Length() > ringRadius)
	{
		// 重なっている量を検出する
		DXSimpleMath::Vector3 overlapVector = ringCenter - point;
		overlapVector.Normalize();
		float overlapDepth = (ringCenter - point).Length() - ringRadius;
		_outputOverlaped = overlapVector * overlapDepth;
		return true;
	}

	return false;
}

void CollisionDetector3D::FixOverlap(PrimitiveComponent* _subject1, PrimitiveComponent* _subject2, const DirectX::SimpleMath::Vector3& _overlapedVetor)
{
	Collision::Channel primitive1Channel = _subject1->GetCollisionChannel();
	Collision::Channel primitive2Channel = _subject2->GetCollisionChannel();

	if (_subject1->GetCollisionType(primitive2Channel) != Collision::Type_Block ||
		_subject2->GetCollisionType(primitive1Channel) != Collision::Type_Block)
	{
		return;
	}

	// このCollisionが動いているかを判断する
	bool primitive1Moved = _subject1->IsCurrentFrameMoved();
	bool primitive2Moved = _subject2->IsCurrentFrameMoved();

	// どちらも動いている場合
	if (primitive1Moved && primitive2Moved)
	{
		DXSimpleMath::Vector3 halfFixOverlapedVector = _overlapedVetor / 2;
		_subject1->FixOverlap(halfFixOverlapedVector);
		_subject2->FixOverlap(halfFixOverlapedVector);
		return;
	}

	// １は移動していて、２は静止
	if (primitive1Moved && !primitive2Moved)
	{
		_subject1->FixOverlap(_overlapedVetor);
		return;
	}

	// １静止、２移動
	if (!primitive1Moved && primitive2Moved)
	{
		_subject2->FixOverlap(_overlapedVetor);
		return;
	}

	_subject1->FixOverlap(_overlapedVetor);
	return;
}

float CollisionDetector3D::CalucSegment3DToSegment3DDistance(const PrimitiveShape::Segment3D& _segment1, const PrimitiveShape::Segment3D& _segment2, DirectX::SimpleMath::Vector3& _outputVector, float& _t1, float& _t2)
{
	// 線分のベクトルを求める
	DXSimpleMath::Vector3 segment1Vector = _segment1.mEndPosition - _segment1.mStartPosition;
	DXSimpleMath::Vector3 segment2Vector = _segment2.mEndPosition - _segment2.mStartPosition;

	// ベクトルが平行の場合
	DXSimpleMath::Vector3 segment1NormalVec = segment1Vector;
	DXSimpleMath::Vector3 segment2NormalVec = segment2Vector;
	segment1NormalVec.Normalize();
	segment2NormalVec.Normalize();
	double dot = segment1NormalVec.Dot(segment2NormalVec);

	if (dot == 1.0f || dot == -1.0f)
	{
		float min = (_segment1.mStartPosition - _segment2.mStartPosition).Length();
		min = min < (_segment1.mStartPosition - _segment2.mEndPosition).Length() ? min : (_segment1.mStartPosition - _segment2.mEndPosition).Length();
		min = min < (_segment1.mEndPosition - _segment2.mStartPosition).Length() ? min : (_segment1.mEndPosition - _segment2.mStartPosition).Length();
		min = min < (_segment1.mEndPosition - _segment2.mEndPosition).Length() ? min : (_segment1.mEndPosition - _segment2.mEndPosition).Length();
		_outputVector = _segment2.mEndPosition - _segment1.mEndPosition;
		return min;
	}

	float t1 = 0;
	float t2 = 0;
	DXSimpleMath::Vector3 minPoint1;
	DXSimpleMath::Vector3 minPoint2;

	// 二つの直線間の最短距離を求める
	float distance = CalucLineLineDistance(_segment1, _segment2, minPoint1, minPoint2, t1, t2);
	if (0.0f <= t1 && t1 <= 1.0f &&
		0.0f <= t2 && t2 <= 1.0f)
	{
		// 最短距離が線分内にあった
		_outputVector = minPoint2 - minPoint1;
		_t1 = t1;
		_t2 = t2;
		return distance;
	}

	// minPoint1,t1を求めなおす
	t2 = MathLibrary::Clamp01(t2);
	minPoint2 = _segment2.mStartPosition + _segment2.GetVector() * t2;
	distance = CalucPointLineDistance(minPoint2, _segment1, minPoint1, t1);
	if (0.0f <= t1 && t1 <= 1.0f)
	{
		_outputVector = minPoint2 - minPoint1;
		_t1 = t1;
		_t2 = t2;
		return distance;
	}

	// minPoint2, t2を求めなおす
	t1 = MathLibrary::Clamp01(t1);
	minPoint1 = _segment1.mStartPosition + _segment1.GetVector() * t1;
	distance = CalucPointLineDistance(minPoint1, _segment2, minPoint2, t2);
	if (0.0f <= t2 && t2 <= 1.0f)
	{
		_outputVector = minPoint2 - minPoint1;
		_t1 = t1;
		_t2 = t2;
		return distance;
	}

	t2 = MathLibrary::Clamp01(t2);
	minPoint2 = _segment2.mStartPosition + _segment2.GetVector() * t2;
	_outputVector = minPoint2 - minPoint1;
	_t1 = t1;
	_t2 = t2;
	return _outputVector.Length();
}

float CollisionDetector3D::CalucLineLineDistance(const PrimitiveShape::Segment3D& _segment1, const PrimitiveShape::Segment3D& _segment2, DirectX::SimpleMath::Vector3& _minPoint1, DirectX::SimpleMath::Vector3 _minPoint2, float& _t1, float& _t2)
{
	// 二つの線が平行
	if (_segment1.GetVector().Cross(_segment2.GetVector()).Length() < 0.000001f)
	{
		_t1 = 0.0f;
		_minPoint1 = _segment1.mStartPosition;
		DXSimpleMath::Vector3 intersection;
		float distance = CalucPointLineDistance(_minPoint1, _segment2, intersection, _t2);
		return distance;
	}

	DXSimpleMath::Vector3 v1 = _segment1.GetVector();
	DXSimpleMath::Vector3 v2 = _segment2.GetVector();

	float dv1v2 = v1.Dot(v2);
	float dv1v1 = v1.Dot(v1);
	float dv2v2 = v2.Dot(v2);

	DXSimpleMath::Vector3 vs2sps2sp = _segment1.mStartPosition - _segment2.mStartPosition;
	_t1 = (dv1v2 * v2.Dot(vs2sps2sp)) - dv2v2 * v1.Dot(vs2sps2sp) / (dv1v1 * dv2v2 - dv1v2 * dv1v2);
	_minPoint1 = _segment1.mStartPosition + v1 * _t1;
	_t2 = v2.Dot(_minPoint1 - _segment2.mStartPosition) / dv2v2;
	_minPoint2 = _segment2.mStartPosition + v2 * _t2;

	return (_minPoint2 - _minPoint1).Length();
}

float CollisionDetector3D::CalucPointLineDistance(const DirectX::SimpleMath::Vector3& _point, const PrimitiveShape::Segment3D& _segment, DirectX::SimpleMath::Vector3& _outputIntersection, float& _t)
{
	// セグメントの長さを求める
	DXSimpleMath::Vector3 segmentVec = _segment.mEndPosition - _segment.mStartPosition;
	float segmentLength = segmentVec.Length();

	_t = 0.0f;
	// 二倍の長さを求める　0なら直行しているベクトル
	float dvv = segmentVec.Dot(segmentVec);
	if (dvv > 0.0f)
	{
		_t = segmentVec.Dot(_point - _segment.mStartPosition) / dvv;
	}
	_outputIntersection = _segment.mStartPosition + segmentVec * _t;
	return (_point - _outputIntersection).Length();
}
