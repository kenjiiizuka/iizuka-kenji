#include "Object3DVertexShader.h"
#include "../ShaderStruct.h"
#include "../../VisualEntity/VisualEntity.h"
#include "../../VisualEntity/VisualEntityData.h"
#include "../../../../Utility/Debug.h"
#include "../../../../Game/Scene/Scene.h"
#include "../../../../Game/GameObject/Light/LightBase.h"
#include "../../../../Game/Scene/SceneManager.h"


using namespace DirectX::SimpleMath;

Object3DVertexShader::Object3DVertexShader(VisualEntity* _entity)
	: VertexShader(_entity)
{
	LoadWithShaderReflection("VS_Lighting.cso");
	mbIsDropShadow = true;
}

void Object3DVertexShader::UpdateBuffer(uint8_t _dataID)
{
	VertexShader::UpdateBuffer(_dataID);
	Matrix world = mVisualEntity->GetWorldMatrix();

	VisualEntityData::Material mat = mVisualEntity->GetVisualEntityData(_dataID)->GetMaterial();

	MATERIAL material;
	material.Ambient = mat.mAmbient;
	material.Diffuse = mat.mDiffuse;
	material.Emission = mat.Emission;
	material.Shininess = mat.mShininess;
	material.Specular = mat.mSpecular;
	WriteBuffer(2, &material);

	// ライトのセット
	std::shared_ptr<LightBase> light = SceneManager::GetInstance().GetCurrentScene().lock()->GetGameObject<LightBase>(ELayer::BaseLayer);
	Vector4 lightBuffer[3] = {
		{0.0f,-1.0f,0.0f,0.0f},
		{1.0f,1.0f,1.0f,1.0f},
		{0.3f,0.3f,0.3f,0.3f}
	};
	if (light)
	{
		GameObject* owner = mVisualEntity->GetOwnerObject();
		Vector3 direction = owner ? -owner->GetComponent<TransformComponent>()->GetPosition() - light->GetPosition() : light->GetDirection();
		lightBuffer[0] = { direction.x, direction.y, direction.z, 0.0f };
		lightBuffer[1] = light->GetDiffuse();
		lightBuffer[2] = light->GetAmbient();
	}
	WriteBuffer(3, &lightBuffer);

}
