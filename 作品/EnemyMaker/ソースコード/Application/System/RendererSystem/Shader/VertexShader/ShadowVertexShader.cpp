#include "ShadowVertexShader.h"
#include "../../../../Game/GameObject/Light/LightBase.h"
#include "../../../../Game/Scene/SceneManager.h"
#include "../../../../Game/Scene/Scene.h"

using namespace DirectX::SimpleMath;

ShadowVertexShader::ShadowVertexShader(VisualEntity* _entity)
	: VertexShader(_entity)
{
	LoadWithShaderReflection("VS_Shadow.cso");
}

void ShadowVertexShader::UpdateBuffer(uint8_t _dataID)
{
	VertexShader::UpdateBuffer(_dataID);

	std::weak_ptr<Scene> currentScene = SceneManager::GetInstance().GetCurrentScene();
	std::shared_ptr<LightBase> light = currentScene.lock()->GetGameObject<LightBase>();
	if (!light)
	{
		return;
	}

	// ƒ‰ƒCƒgs—ñ‚ðì¬‚·‚é
	Matrix lView_lProj[2];
	light->CalucLightViewMatrix(lView_lProj[0], { 0,0,0 });
	light->CalucLightProjectionMatrix(lView_lProj[1]);
	lView_lProj[0] = lView_lProj[0].Transpose();
	lView_lProj[1] = lView_lProj[1].Transpose();
	WriteBuffer(2, &lView_lProj);
}


