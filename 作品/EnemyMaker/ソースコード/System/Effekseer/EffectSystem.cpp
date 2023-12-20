//--------- INCLUDES -----------
#include "EffectSystem.h"
#include "../RendererSystem/Renderer.h"
#include "../../Game/Scene/SceneManager.h"
#include "../../Game/Scene/Scene.h"
#include "../../Game/GameObject/Camera/Camera.h"
#include "../../Game/GameObject/Camera/CameraManager.h"
#include <filesystem>
#include "../../System/InputSystem/Input.h"
#include "../../System/RendererSystem/DebugRenderer/DebugRendererManager.h"

//----------- LIBRARY ----------
#ifdef _DEBUG
#pragma comment(lib, "Effekseerd.lib")
#pragma comment(lib, "EffekseerRendererDX11d.lib")
#else 
#pragma comment(lib, "Effekseer.lib")
#pragma comment(lib, "EffekseerRendererDX11.lib")
#endif

void EffectSystem::Initialize()
{
	Renderer& renderer = Renderer::GetInstance();

	// �G�t�F�N�V�A�̕`��f�o�C�X���쐬
	::Effekseer::Backend::GraphicsDeviceRef graphicsDevice = ::EffekseerRendererDX11::CreateGraphicsDevice(renderer.GetDevice() , renderer.GetDeviceContext());
	
	// �G�t�F�N�g�}�l�[�W���[�̍쐬
	mEffekseerManager = ::Effekseer::Manager::Create(8000);

	// �G�t�F�N�g�����_���[�̍쐬
	mEffekseerRenderer = ::EffekseerRendererDX11::Renderer::Create(graphicsDevice, 8000);

	//�`�惂�W���[���̐ݒ�
	mEffekseerManager->SetSpriteRenderer(mEffekseerRenderer->CreateSpriteRenderer());
	mEffekseerManager->SetRibbonRenderer(mEffekseerRenderer->CreateRibbonRenderer());
	mEffekseerManager->SetRingRenderer(mEffekseerRenderer->CreateRingRenderer());
	mEffekseerManager->SetTrackRenderer(mEffekseerRenderer->CreateTrackRenderer());
	mEffekseerManager->SetModelRenderer(mEffekseerRenderer->CreateModelRenderer());

	// �e�N�X�`���A���f���A�J�[�u�A�}�e���A�����[�_�[�̐ݒ肷��B
	mEffekseerManager->SetTextureLoader(mEffekseerRenderer->CreateTextureLoader());
	mEffekseerManager->SetModelLoader(mEffekseerRenderer->CreateModelLoader());
	mEffekseerManager->SetMaterialLoader(mEffekseerRenderer->CreateMaterialLoader());
 	mEffekseerManager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());
}

void EffectSystem::Draw()
{
	// ���C���J�������擾����
	std::shared_ptr<CameraManager> cameraManager = SceneManager::GetInstance().GetCurrentScene().lock()->GetCameraManager();
	std::shared_ptr<Camera> mainCamera = cameraManager->GetMainCamera();

	// �v���W�F�N�V�����s��̍쐬
	::Effekseer::Matrix44 projection = ConvertEffekseerMatrix(mainCamera->GetProjectionMatrix());

	// �r���[�s��̍쐬
	::Effekseer::Matrix44 view = ConvertEffekseerMatrix(mainCamera->GetViewMatrix());

	// �J�����ʒu���擾
	DirectX::SimpleMath::Vector3 position = mainCamera->GetCameraPosition();

	// ���C���[�p�����[�^�̐ݒ�
	Effekseer::Manager::LayerParameter layerParameter;
	layerParameter.ViewerPosition = { position.x,position.y, position.z };
	mEffekseerManager->SetLayerParameter(0, layerParameter);

	// �}�l�[�W���[�̍X�V
	Effekseer::Manager::UpdateParameter updateParameter;
	mEffekseerManager->Update(updateParameter);

	// �v���W�F�N�V����,�r���[�̐ݒ�
	mEffekseerRenderer->SetProjectionMatrix(projection);
	mEffekseerRenderer->SetCameraMatrix(view);

	// �G�t�F�N�g�̕`��J�n�������s���B
	mEffekseerRenderer->BeginRendering();

	// �G�t�F�N�g�̕`����s���B
	Effekseer::Manager::DrawParameter drawParameter;
	drawParameter.ZNear = 0.0f;
	drawParameter.ZFar = 1.0f;
	drawParameter.ViewProjectionMatrix = mEffekseerRenderer->GetCameraProjectionMatrix();
	mEffekseerManager->Draw(drawParameter);

	// �G�t�F�N�g�̕`��I���������s���B
	mEffekseerRenderer->EndRendering();
}

Effekseer::Matrix44 EffectSystem::ConvertEffekseerMatrix(const DirectX::SimpleMath::Matrix& _matrix)
{
	Effekseer::Matrix44 matrix;

	for (size_t x = 0; x < 4; x++)
	{
		for (size_t y = 0; y < 4; y++)
		{
			matrix.Values[x][y] = _matrix.m[x][y];
		}
	}
	return matrix;
}
