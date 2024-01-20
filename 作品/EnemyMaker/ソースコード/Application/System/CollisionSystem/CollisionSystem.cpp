//------------ INCLUDES -----------
#include "CollisionSystem.h"
#include "../../Utility/Debug.h"
#include "CollisionDetector3D.h"
#include "../RendererSystem/RendererManager.h"

//----------- NAMESPACEAILIAS ------------
using namespace DirectX::SimpleMath;

CollisionSystem::CollisionSystem()
	: mbSystemActive(false)
{
	// 処理なし
}

CollisionSystem::~CollisionSystem()
{
	// 処理なし
}

void CollisionSystem::Init()
{
	// 検出クラスの生成 3D用
	mCollisionDetector = std::make_unique<CollisionDetector3D>();
}

void CollisionSystem::Update()
{
	// コリジョンシステムが無効なら早期リターン
	if (!mbSystemActive)
	{
		return;
	}

	// コリジョンの種類が増えてきたら関数を二次元配列に格納して、enumでPrimitivetypeを宣言して紐づけるようにする	
	for (uint16_t i = 0; i < mRegisterdCollisions.size(); i++)
	{
		for (uint16_t j = i + 1; j < mRegisterdCollisions.size(); j++)
		{
			mCollisionDetector->DetectorOverlap(mRegisterdCollisions[i], mRegisterdCollisions[j]);
		}
	}
}
