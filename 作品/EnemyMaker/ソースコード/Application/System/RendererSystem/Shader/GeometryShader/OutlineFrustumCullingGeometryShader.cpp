//--------- INCLUDES ---------
#include "OutlineFrustumCullingGeometryShader.h"
#include "../../../../Game/GameObject/Camera/CameraIncludes.h"

OutlineFrustumCullingGeometryShader::OutlineFrustumCullingGeometryShader(VisualEntity* _entity)
	: GeometryShader(_entity)
{
	LoadWithShaderReflection("GS_FrustumCullingOutline.cso");
}

OutlineFrustumCullingGeometryShader::~OutlineFrustumCullingGeometryShader()
{
	// 処理なし
}


void OutlineFrustumCullingGeometryShader::UpdateBuffer(uint8_t _dataID)
{
	std::shared_ptr<Camera> mainCamera = SceneManager::GetInstance().GetCurrentScene().lock()->GetCameraManager()->GetMainCamera();

	// ビュープロジェクション行列を書き込む
	DirectX::SimpleMath::Matrix frustum = (mainCamera->GetViewMatrix() * mainCamera->GetProjectionMatrix()).Transpose();
	WriteBuffer(0, &frustum);
}
