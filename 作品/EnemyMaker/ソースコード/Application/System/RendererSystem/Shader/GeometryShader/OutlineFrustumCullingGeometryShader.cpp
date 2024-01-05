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
	// �����Ȃ�
}


void OutlineFrustumCullingGeometryShader::UpdateBuffer(uint8_t _dataID)
{
	std::shared_ptr<Camera> mainCamera = SceneManager::GetInstance().GetCurrentScene().lock()->GetCameraManager()->GetMainCamera();

	// �r���[�v���W�F�N�V�����s�����������
	DirectX::SimpleMath::Matrix frustum = (mainCamera->GetViewMatrix() * mainCamera->GetProjectionMatrix()).Transpose();
	WriteBuffer(0, &frustum);
}
