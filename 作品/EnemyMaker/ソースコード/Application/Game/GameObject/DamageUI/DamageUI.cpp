//--------- INCLUDES ----------
#include "DamageUI.h"
#include "../UI/Number.h"
#include "../../../Utility/CurveFloat.h"
#include "../../../Utility/MathLibrary.h"

DamageUI::DamageUI()
	: mBillboardLifeTime(1.0f)
	, mbEditCurve(true)
{
	// 処理なし
}

DamageUI::~DamageUI()
{
	// 処理なし
}

void DamageUI::Init()
{
	mCurve = std::make_shared<CurveFloat>();
	mCurve->Initialize("assets/Player/Config/DamageMove.json");

	// 親のトランスフォームの影響を受けない
	mTransform.lock()->SetParentTransformInfluence(false);
}

void DamageUI::Update(const double _deltaTime)
{
	for (auto it = mDamageBillboard.begin(); it != mDamageBillboard.end();)
	{
		if (it->mElapsedTime > mBillboardLifeTime)
		{
			it->mBillboard.lock()->Destroy();
			it = mDamageBillboard.erase(it);
			continue;
		}	
		MoveBillboard(*it);
		InterpAlpha(*it);
		it->mElapsedTime += static_cast<float>(_deltaTime);
		it++;
	}

	if (mbEditCurve)
	{
		mCurve->Edit("MoveCurve");
	}
}

void DamageUI::MoveBillboard(DamageBillboard& _billboard)
{
	float t = MathLibrary::Clamp01(static_cast<float>(_billboard.mElapsedTime / mBillboardLifeTime));
	DirectX::SimpleMath::Vector3 movement = _billboard.mDirection* mCurve->GetValueByTime(t);
	_billboard.mBillboard.lock()->GetComponent<TransformComponent>()->AddPosition(movement);
}

void DamageUI::InterpAlpha(DamageBillboard& _billboard)
{
	float t = static_cast<float>(MathLibrary::Clamp01(_billboard.mElapsedTime / mBillboardLifeTime));
	DirectX::SimpleMath::Color diffuse = { 1,1,1,1.0f - t };
	_billboard.mBillboard.lock()->SetDiffuse(diffuse);
}

void DamageUI::DisplayDamage(const float _damage, const DirectX::SimpleMath::Vector3 _position)
{
	DamageBillboard damageBillboard;
	damageBillboard.mBillboard = AddChildObject<Number>();
	damageBillboard.mBillboard.lock()->SetNumber(static_cast<uint8_t>(_damage));
	damageBillboard.mBillboard.lock()->GetComponent<TransformComponent>()->SetParentTransformInfluence(false);
	damageBillboard.mBillboard.lock()->SetPosition(_position);
	damageBillboard.mDirection = { 0,1,0 };
	mDamageBillboard.emplace_back(damageBillboard);
}

DamageUI::DamageBillboard::DamageBillboard()
	: mElapsedTime(0.0f)
{
	// 処理なし
}
