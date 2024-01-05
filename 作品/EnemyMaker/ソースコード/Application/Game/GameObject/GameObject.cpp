//--------- INCLUDES ---------
#include "GameObject.h"

//--------- NAMESPACEALIAS ------------
using namespace DirectX::SimpleMath;

GameObject::GameObject()
	: bDestroy(false)
	, bActive(true)
	, mParent(nullptr)
	, bIsVisible(true)
	, mTimeDilation(1.0)
{
	// 処理なし
}

GameObject::~GameObject()
{
	// 処理なし
}

void GameObject::UninitBase()
{
	Uninit();
	for (std::shared_ptr<Component>& comp : mComponent)
	{
		comp->UninitBase();
		comp.reset();
	}
	for (std::shared_ptr<GameObject>& obj : mChildObject)
	{
		obj->UninitBase();
		obj.reset();
	}
	mComponent.clear();
	mChildObject.clear();
}

void GameObject::UpdateBase(const double _deltaTime)
{
	mCustomDeltaTime = _deltaTime * mTimeDilation;

	// コンポーネントが破棄されるか判断する
	if (!bActive)
	{
		return;
	}
	
	for (auto it = mComponent.begin(); it != mComponent.end();)
	{
		if (it->get()->IsDestroy())
		{
			it->get()->UninitBase();
			it = mComponent.erase(it);
		}	
		else
		{
			it++;
		}	
	}

	for (auto it = mChildObject.begin(); it != mChildObject.end();)
	{
		if (it->get()->bDestroy)
		{
			it->get()->UninitBase();
			it = mChildObject.erase(it);
		}
		else
		{
			it++;
		}
	}

	// 持っているコンポ-ネントのUpdate
	for (std::shared_ptr<Component> comp : mComponent)
	{
		comp->UpdateBase(mCustomDeltaTime);
	}
	for (std::shared_ptr<GameObject> obj : mChildObject)
	{
		obj->UpdateBase(mCustomDeltaTime);
	}
	Update(mCustomDeltaTime);
}

void GameObject::LastUpdateBase()
{
	if (!bActive)
	{
		return;
	}
	for (std::shared_ptr<Component> comp : mComponent)
	{
		comp->LastUpdateBase();
	}
	for (std::shared_ptr<GameObject> obj : mChildObject)
	{
		obj->LastUpdateBase();
	}
	LastUpdate();
	
}

void GameObject::DrawBase(Matrix _parentMatrix)
{		
	if (!bActive)
	{
		return;
	}
	
	DirectX::SimpleMath::Matrix world = mTransform.lock()->CalucWorldMatrix(_parentMatrix);
	
	for (std::shared_ptr<Component> comp : mComponent)
	{
		comp->DrawBase();
	}
	for (std::shared_ptr<GameObject> obj : mChildObject)
	{
		obj->DrawBase(world);
	}
	Draw();
}