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
	// �����Ȃ�
}

void FrustumCullingGeometryShader::UpdateBuffer(uint8_t _dataID)
{
	std::shared_ptr<Camera> mainCamera = SceneManager::GetInstance().GetCurrentScene().lock()->GetCameraManager()->GetMainCamera();

	// �r���[�v���W�F�N�V�����s�����������
	DirectX::SimpleMath::Matrix frustum = (mainCamera->GetViewMatrix() * mainCamera->GetProjectionMatrix()).Transpose();
	WriteBuffer(0, &frustum);
}
