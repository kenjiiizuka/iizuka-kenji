//------------- INCLUDES ----------
#include "Field.h"
#include "../../../System/RendererSystem/Shader/ShaderStruct.h"
#include "../../Component/TransformComponent/TransformComponent.h"
#include "../../Component/PlaneComponent/PlaneComponent.h"
#include "../../GameObject/StaticMeshObject/StaticMeshObject.h"
#include "../../../ImGui/ImGuiUtility.h"
#include "../../../Utility/MathLibrary.h"

using namespace DirectX::SimpleMath;

Field::Field()
	: mPlaneSize(50,0,50)
{
	// 処理なし
}

void Field::Init()
{	
	// 地面配置のオブジェクト
	// 0
	{
		// 地面配置のオブジェクト
		std::shared_ptr<StaticMeshObject> Prop = AddChildObject<StaticMeshObject>();
		Prop->Init("assets/Field/Gate.fbx");
		Prop->SetScale(0.1f);
		Prop->SetPosition({ 100.f,0.f,27.f });
		mProps.emplace_back(Prop);
	}

	// 1
	{
		// 地面配置のオブジェクト
		std::shared_ptr<StaticMeshObject> Prop = AddChildObject<StaticMeshObject>();
		Prop->Init("assets/Field/Rock_3.fbx");
		Prop->SetScale(0.1f);
		Prop->SetPosition({ 33.0f,0.f,100.f });
		Prop->SetRotation(
			{
				MathLibrary::FloatDegreeToRadian(14.0),
				MathLibrary::FloatDegreeToRadian(86.0),
				MathLibrary::FloatDegreeToRadian(0.0)
			});
		mProps.emplace_back(Prop);
	}

	// 2
	{
		// 地面配置のオブジェクト
		std::shared_ptr<StaticMeshObject> Prop = AddChildObject<StaticMeshObject>();
		Prop->Init("assets/Field/Rock_3.fbx");
		Prop->SetScale(0.1f);
		Prop->SetPosition({ 139.f,0.f,44.0f });
		Prop->SetRotation(
			{
				MathLibrary::FloatDegreeToRadian(0.0),
				MathLibrary::FloatDegreeToRadian(-30.0),
				MathLibrary::FloatDegreeToRadian(2.0)
			});
		mProps.emplace_back(Prop);
	}

	// 3
	{
		// 地面配置のオブジェクト
		std::shared_ptr<StaticMeshObject> Prop = AddChildObject<StaticMeshObject>();
		Prop->Init("assets/Field/Rock_3.fbx");
		Prop->SetScale(0.1f);
		Prop->SetPosition({ 62.f,0.f,167.f });
		Prop->SetRotation(
			{
				MathLibrary::FloatDegreeToRadian(0.0),
				MathLibrary::FloatDegreeToRadian(-218.0),
				MathLibrary::FloatDegreeToRadian(0.0)
			});
		mProps.emplace_back(Prop);
	}

	// 4
	{
		// 地面配置のオブジェクト
		std::shared_ptr<StaticMeshObject> Prop = AddChildObject<StaticMeshObject>();
		Prop->Init("assets/Field/Rock_3.fbx");
		Prop->SetScale({0.2f,0.15f,0.15f});
		Prop->SetPosition({ 166.f,5.f,68.f });
		Prop->SetRotation(
			{
				MathLibrary::FloatDegreeToRadian(39.0),
				MathLibrary::FloatDegreeToRadian(297.0),
				MathLibrary::FloatDegreeToRadian(186.0)
			});
		mProps.emplace_back(Prop);
	}

	// 5
	{
		// 地面配置のオブジェクト
		std::shared_ptr<StaticMeshObject> Prop = AddChildObject<StaticMeshObject>();
		Prop->Init("assets/Field/Rock_w_4.fbx");
		Prop->SetScale(0.1f);
		Prop->SetPosition({ 47.f,0.f,50.f });
		Prop->SetRotation(
			{
				MathLibrary::FloatDegreeToRadian(0.0),
				MathLibrary::FloatDegreeToRadian(-100.0),
				MathLibrary::FloatDegreeToRadian(0.0)
			});
		mProps.emplace_back(Prop);
	}

	// 6
	{
		// 地面配置のオブジェクト
		std::shared_ptr<StaticMeshObject> Prop = AddChildObject<StaticMeshObject>();
		Prop->Init("assets/Field/Rock_w_4.fbx");
		Prop->SetScale(0.05f);
		Prop->SetPosition({ 166.0f,5.0f,111.f });
		Prop->SetRotation(
			{
				MathLibrary::FloatDegreeToRadian(-227.0),
				MathLibrary::FloatDegreeToRadian(46.0),
				MathLibrary::FloatDegreeToRadian(96.0)
			});
		mProps.emplace_back(Prop);
	}

	// 7
	{
		// 地面配置のオブジェクト
		std::shared_ptr<StaticMeshObject> Prop = AddChildObject<StaticMeshObject>();
		Prop->Init("assets/Field/Rock_w_4.fbx");
		Prop->SetScale(0.1f);
		Prop->SetPosition({ 151.0f,0.f,155.f });
		Prop->SetRotation(
			{
				MathLibrary::FloatDegreeToRadian(0.0),
				MathLibrary::FloatDegreeToRadian(66.0),
				MathLibrary::FloatDegreeToRadian(0.0)
			});
		mProps.emplace_back(Prop);
	}

	// 8
	{
		// 地面配置のオブジェクト
		std::shared_ptr<StaticMeshObject> Prop = AddChildObject<StaticMeshObject>();
		Prop->Init("assets/Field/Rock_w_4.fbx");
		Prop->SetScale(0.1f);
		Prop->SetPosition({ 1,0.f,116.f });
		Prop->SetRotation(
			{
				MathLibrary::FloatDegreeToRadian(0.0),
				MathLibrary::FloatDegreeToRadian(0.0),
				MathLibrary::FloatDegreeToRadian(0.0)
			});
		mProps.emplace_back(Prop);
	}

	// 9
	{
		// 地面配置のオブジェクト
		std::shared_ptr<StaticMeshObject> Prop = AddChildObject<StaticMeshObject>();
		Prop->Init("assets/Field/Rock_w_4.fbx");
		Prop->SetScale(0.2f);
		Prop->SetPosition({ 211.0f,0.f,33.0f });
		Prop->SetRotation(
			{
				MathLibrary::FloatDegreeToRadian(0.0),
				MathLibrary::FloatDegreeToRadian(29.0),
				MathLibrary::FloatDegreeToRadian(0.0)
			});
		mProps.emplace_back(Prop);
	}

	// 10
	{
		// 地面配置のオブジェクト
		std::shared_ptr<StaticMeshObject> Prop = AddChildObject<StaticMeshObject>();
		Prop->Init("assets/Field/Rock_w.fbx");
		Prop->SetScale(0.15f);
		Prop->SetPosition({ 38.0f,-10.f,16.0f });
		Prop->SetRotation(
			{
				MathLibrary::FloatDegreeToRadian(0.0),
				MathLibrary::FloatDegreeToRadian(163.0),
				MathLibrary::FloatDegreeToRadian(0.0)
			});
		mProps.emplace_back(Prop);
	}

	// 11
	{
		// 地面配置のオブジェクト
		std::shared_ptr<StaticMeshObject> Prop = AddChildObject<StaticMeshObject>();
		Prop->Init("assets/Field/Rock_w.fbx");
		Prop->SetScale(0.2f);
		Prop->SetPosition({ 117,0.f,-32.f });
		Prop->SetRotation(
			{
				MathLibrary::FloatDegreeToRadian(0.0),
				MathLibrary::FloatDegreeToRadian(-12.0),
				MathLibrary::FloatDegreeToRadian(-69.0)
			});
		mProps.emplace_back(Prop);
	}

	// 12
	{
		// 地面配置のオブジェクト
		std::shared_ptr<StaticMeshObject> Prop = AddChildObject<StaticMeshObject>();
		Prop->Init("assets/Field/Rock_w.fbx");
		Prop->SetScale(0.1f);
		Prop->SetPosition({ 204,0.f,111.f });
		Prop->SetRotation(
			{
				MathLibrary::FloatDegreeToRadian(0.0),
				MathLibrary::FloatDegreeToRadian(0.0),
				MathLibrary::FloatDegreeToRadian(0.0)
			});
		mProps.emplace_back(Prop);
	}

	// 13
	{
		// 地面配置のオブジェクト
		std::shared_ptr<StaticMeshObject> Prop = AddChildObject<StaticMeshObject>();
		Prop->Init("assets/Field/Rock_w.fbx");
		Prop->SetScale(0.1f);
		Prop->SetPosition({ 144.0f,0.f,185.0f });
		Prop->SetRotation(
			{
				MathLibrary::FloatDegreeToRadian(0.0),
				MathLibrary::FloatDegreeToRadian(-217.0),
				MathLibrary::FloatDegreeToRadian(0.0)
			});
		mProps.emplace_back(Prop);
	}

	// 14
	{
		// 地面配置のオブジェクト
		std::shared_ptr<StaticMeshObject> Prop = AddChildObject<StaticMeshObject>();
		Prop->Init("assets/Field/Rock_w.fbx");
		Prop->SetScale(0.1f);
		Prop->SetPosition({ 101.0f,-12.f,202.f });
		Prop->SetRotation(
			{
				MathLibrary::FloatDegreeToRadian(0.0),
				MathLibrary::FloatDegreeToRadian(-19.0),
				MathLibrary::FloatDegreeToRadian(0.0)
			});
		mProps.emplace_back(Prop);
	}

	// 15
	{
		// 地面配置のオブジェクト
		std::shared_ptr<StaticMeshObject> Prop = AddChildObject<StaticMeshObject>();
		Prop->Init("assets/Field/Rock_w.fbx");
		Prop->SetScale(0.2f);
		Prop->SetPosition({ 10,0.f,211.f });
		Prop->SetRotation(
			{
				MathLibrary::FloatDegreeToRadian(0.0),
				MathLibrary::FloatDegreeToRadian(-12.0),
				MathLibrary::FloatDegreeToRadian(-69.0)
			});
		mProps.emplace_back(Prop);
	}
}

void Field::Update(const double _deltaTime)
{
	/*ImGui::Begin("Field");
	for (size_t trans_i = 0; std::weak_ptr<StaticMeshObject>& prop : mProps)
	{
		std::shared_ptr<StaticMeshObject> valid = prop.lock();
		if (!valid)
		{
			continue;
		}

		std::shared_ptr<TransformComponent> trans = valid->GetComponent<TransformComponent>();
		Transform transform = trans->GetTransform();
		std::string label = "Transform " + std::to_string(trans_i);
		ImGui::Text(("Prop" + std::to_string(trans_i)).c_str());
		ImGuiUtility::GetInstance().DragTransform(label, transform);
		trans->SetTransform(transform);
		trans_i++;
	}
	ImGui::End();*/
}