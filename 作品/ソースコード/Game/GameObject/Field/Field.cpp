#include "Field.h"
#include "../../../System/RendererSystem/Shader/ShaderStruct.h"
#include "../../Component/TransformComponent/TransformComponent.h"
#include "../../Component/PlaneComponent/PlaneComponent.h"
#include "../../GameObject/StaticMeshObject/StaticMeshObject.h"

using namespace DirectX::SimpleMath;

Field::Field()
	: mPlaneSize(50,0,50)
{
}

/*----------
 初期化処理 
-----------*/
void Field::Init()
{	
	// 地面配置のオブジェクト
	std::shared_ptr<StaticMeshObject> debri = AddChildObject<StaticMeshObject>();
	debri->Init("assets/Field/Field.fbx");
	debri->SetScale(0.1f);
	debri->SetPosition({ 100.f,0.f,100.f });
}

/*---------
 終了処理
----------*/
void Field::Draw()
{	

}


