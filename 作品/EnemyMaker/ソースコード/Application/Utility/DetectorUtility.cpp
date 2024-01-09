//------------ INCLUDES -----------
#include "DetectorUtility.h"
#include "../System/RendererSystem/DebugRenderer/DebugRendererManager.h"
#include "MathLibrary.h"

bool DetectorUtility::IsPositionInCircle2D(DirectX::SimpleMath::Vector2 _position, DirectX::SimpleMath::Vector2 _center, float _radius, DirectX::SimpleMath::Vector4 _color)
{
#ifdef _DEBUG
	DebugRendererManager::GetInstance().DrawHalfCircle(
		_radius,
		{ _center.x, 0, _center.y },        /* 半球描画位置 yは0固定 */
		1,                                 /* 描画フレーム */
		_color
	);
#endif // _DEBUG

	float distance = (_position - _center).Length();
	return distance < _radius;
}

bool DetectorUtility::IsPositionInSector2D(DirectX::SimpleMath::Vector2 _position, DirectX::SimpleMath::Vector2 _sectorCenter, DirectX::SimpleMath::Vector2 _sectorEndPoint, float _sectorDegree, DirectX::SimpleMath::Vector4 _color)
{
#ifdef _DEBUG
	{
		DebugRendererManager& debugRenderer = DebugRendererManager::GetInstance();

		DirectX::SimpleMath::Vector2 startToEndVector = _sectorEndPoint - _sectorCenter;

		{
			debugRenderer.DrawSegment
			(
				{ _sectorCenter.x,1.0f, _sectorCenter.y },
				{ _sectorEndPoint.x, 1.0f, _sectorEndPoint.y },
				1,
				_color
			);
		}

		// セクターの上
		{
			float upRadian = MathLibrary::FloatDegreeToRadian(_sectorDegree / 2.0f);
			DirectX::SimpleMath::Matrix rotationMatrix = DirectX::SimpleMath::Matrix::CreateRotationZ(upRadian);
			DirectX::SimpleMath::Vector2 sectorUp = DirectX::SimpleMath::Vector2::Transform(startToEndVector, rotationMatrix);
			sectorUp += _sectorCenter;

			debugRenderer.DrawSegment
			(
				{ _sectorCenter.x, 1.0f, _sectorCenter.y },
				{ sectorUp.x, 1.0f, sectorUp.y },
				1,
				_color
			);
		}

		// セクターの下
		{
			float DownRadian = MathLibrary::FloatDegreeToRadian(-_sectorDegree / 2.0f);
			DirectX::SimpleMath::Matrix rotationMatrix = DirectX::SimpleMath::Matrix::CreateRotationZ(DownRadian);
			DirectX::SimpleMath::Vector2 sectorDown = DirectX::SimpleMath::Vector2::Transform(startToEndVector, rotationMatrix);
			sectorDown += _sectorCenter;

			debugRenderer.DrawSegment
			(
				{ _sectorCenter.x, 1.0f, _sectorCenter.y },
				{ sectorDown.x, 1.0f, sectorDown.y },
				1,
				_color
			);
		}

	}
#endif // _DEBUG

	bool sts = false;

	// チェック対象と視点を結ぶベクトル
	DirectX::SimpleMath::Vector2 vecobj;
	vecobj = _position - _sectorCenter;

	// オブジェクトとの距離を求める
	float objlength = vecobj.Length();

	// 扇の長さ
	float sectorLength = (_sectorEndPoint - _sectorCenter).Length();
	// 距離範囲外？
	if (objlength > sectorLength)
	{
		return false;
	}

	// 視線ベクトルの上限と下限を求める
	DirectX::SimpleMath::Vector2 pulsViewVec;
	DirectX::SimpleMath::Vector2 muinasViewVec;

	// 視線ベクトル
	DirectX::SimpleMath::Vector2 viewvec = _sectorEndPoint - _sectorCenter;

	// 上限
	float upRadian = MathLibrary::FloatDegreeToRadian(_sectorDegree / 2.0f);
	DirectX::SimpleMath::Matrix mtx;
	mtx = mtx.CreateRotationZ(upRadian);	// 視野角の半分を指定して行列を作成（Z軸回転）	
	pulsViewVec = pulsViewVec.Transform(viewvec, mtx);	// 視線ベクトルを視野角の半分　回転させる
	pulsViewVec += _sectorEndPoint;

	PrimitiveShape::Segment3D segment;
	segment.mStartPosition = { _sectorCenter.x, 0.0f, _sectorCenter.y };
	segment.mEndPosition = { pulsViewVec.x, 0.0f, pulsViewVec.y };
	float t;

	DirectX::SimpleMath::Vector3 intersection;
	float distance = CalucPosintSegmentDistance({_position.x, 0.0f, _position.y}, segment, intersection, t);
	
	// 下限
	float downRadian = MathLibrary::FloatDegreeToRadian(-_sectorDegree / 2.0f);
	mtx = mtx.CreateRotationZ(downRadian);	  // 視野角の半分を指定して行列を作成（Z軸回転）	
	muinasViewVec = pulsViewVec.Transform(viewvec, mtx);  // 視線ベクトルを視野角の半分　回転させる
	muinasViewVec += _sectorCenter;
	segment.mStartPosition = { _sectorCenter.x, 0.0f, _sectorCenter.y };
	segment.mEndPosition = { muinasViewVec.x, 0.0f, muinasViewVec.y };
	distance = CalucPosintSegmentDistance({ _position.x, 0.0f, _position.y }, segment, intersection, t);

	sts = InSectorCheackXZ(_sectorCenter, _sectorEndPoint, upRadian, _position, sectorLength);

	return sts;
}

bool DetectorUtility::InSectorCheackXZ(const DirectX::SimpleMath::Vector2& _sectorCenter, const DirectX::SimpleMath::Vector2& _sectorEndPoint, const float& _sectorAngle, const DirectX::SimpleMath::Vector2& _position, const float& _length)
{
	// チェック対象と視点を結ぶベクトル
	DirectX::SimpleMath::Vector2 vecobj;
	vecobj = _position - _sectorCenter;

	// オブジェクトとの距離を求める
	float objlength = vecobj.Length();

	// 距離範囲外？
	if (objlength > _length)
	{
		return false;
	}

	// 視線ベクトル
	DirectX::SimpleMath::Vector2 vecview;
	vecview = _sectorEndPoint - _sectorCenter;

	// 正規化
	vecview.Normalize();				// 視線ベクトルの正規化
	vecobj.Normalize();					// 判定対象オブジェクトへのベクトルを正規化

	// 内積を計算（視線ベクトルとターゲットベクトル）
	float dotobj = vecview.Dot(vecobj);

	// 回転
	DirectX::SimpleMath::Matrix mtx;
	mtx = mtx.CreateRotationZ(_sectorAngle);	// 視野角の半分を指定して行列を作成（Z軸回転）
	DirectX::SimpleMath::Vector2 vecrotview;
	vecrotview = vecview.Transform(vecview, mtx);	// 視線ベクトルを視野角の半分　回転させる

	// 内積を計算
	float dotrotview = vecview.Dot(vecrotview);     // 回転させた視線ベクトル（上限）との内積を計算

	// 視野角範囲内？
	if (dotrotview <= dotobj) 
	{
		return true;
	}

	return false;
}

float DetectorUtility::CalucPosintSegmentDistance(const DirectX::SimpleMath::Vector3& _position, const PrimitiveShape::Segment3D& _segment, DirectX::SimpleMath::Vector3& _interSectionPoint, float& _t)
{
	float distance = CalucPointLineDist(_position, _segment, _interSectionPoint, _t);

	// 交点が線分の外にある（始点に近い）
	if (_t < 0.0f) 
	{
		_interSectionPoint = _segment.mStartPosition;		// 開始点が交点

		float toIntersectionlength = (_position - _interSectionPoint).Length();	// 交点との距離を求める

		return toIntersectionlength;
	}

	// 交点が線分の外にある（終点に近い)
	if (_t > 1.0f) 
	{
		_interSectionPoint = _segment.mEndPosition;		// 終点が交点

		float toIntersectionlength = (_position - _interSectionPoint).Length();	// 交点との距離を求める

		return toIntersectionlength;
	}

	// 交点が線分上にある（０＜ｔ＜１）
	return distance;
}

float DetectorUtility::CalucPointLineDist(const DirectX::SimpleMath::Vector3& _position, const PrimitiveShape::Segment3D& _segment, DirectX::SimpleMath::Vector3& _intersectionPoint, float& _t)
{
	float distance = 0.0f;

	// ここからコーディング開始
	_t = 0.0f;
	// 線分のベクトルを求める
	float ABx = _segment.mEndPosition.x - _segment.mStartPosition.x;
	float ABy = _segment.mEndPosition.y - _segment.mStartPosition.y;
	float ABz = _segment.mEndPosition.z - _segment.mStartPosition.z;

	// 線分の始点と点を結ぶベクトルを求める
	float APx = _position.x - _segment.mStartPosition.x;
	float APy = _position.y - _segment.mStartPosition.y;
	float APz = _position.z - _segment.mStartPosition.z;

	// 線分ABの長さを求める
	float AB2 = ABx * ABx + ABy * ABy + ABz * ABz; // ベクトルの長さを求める

	// ABベクトルとAPベクトルの内積を計算する（射影した長さを求める）
	float ABdotAP = ABx * APx + ABy * APy + ABz * APz;

	// ttを計算
	float tt = ABdotAP / AB2;

	// 垂線の足
	_intersectionPoint.x = static_cast<float>(_segment.mStartPosition.x + ABx * tt);
	_intersectionPoint.y = static_cast<float>(_segment.mStartPosition.y + ABy * tt);
	_intersectionPoint.z = static_cast<float>(_segment.mStartPosition.z + ABz * tt);

	_t = static_cast<float>(tt);
	// 垂線の足の長さ
	distance = (_intersectionPoint - _position).Length();

	// ここまでコーディング
	return distance;
}
