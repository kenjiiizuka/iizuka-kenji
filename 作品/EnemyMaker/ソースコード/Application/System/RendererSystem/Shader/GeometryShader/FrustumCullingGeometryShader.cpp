//---------- INCLUDES ----------
#include "FrustumCullingGeometryShader.h"
#include "../../../../Game/GameObject/Camera/CameraIncludes.h"


FrustumCullingGeometryShader::FrustumCullingGeometryShader(VisualEntity* _entity)
	: GeometryShader(_entity)
{
	LoadWithShaderReflection("GS_FrustumCulling.cso");
}

FrustumCullingGeometryShader::~FrustumCullingGeometryShader()
{
	// 処理なし
}

void FrustumCullingGeometryShader::UpdateBuffer(uint8_t _dataID)
{
	std::shared_ptr<Camera> mainCamera = SceneManager::GetInstance().GetCurrentScene().lock()->GetCameraManager()->GetMainCamera();

	// ビュープロジェクション行列を書き込む
	DirectX::SimpleMath::Matrix frustum = (mainCamera->GetViewMatrix() * mainCamera->GetProjectionMatrix()).Transpose();
	WriteBuffer(0, &frustum);
}
