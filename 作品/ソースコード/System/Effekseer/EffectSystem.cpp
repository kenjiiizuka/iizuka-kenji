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

	// エフェクシアの描画デバイスを作成
	::Effekseer::Backend::GraphicsDeviceRef graphicsDevice = ::EffekseerRendererDX11::CreateGraphicsDevice(renderer.GetDevice() , renderer.GetDeviceContext());
	
	// エフェクトマネージャーの作成
	mEffekseerManager = ::Effekseer::Manager::Create(8000);

	// エフェクトレンダラーの作成
	mEffekseerRenderer = ::EffekseerRendererDX11::Renderer::Create(graphicsDevice, 8000);

	//描画モジュールの設定
	mEffekseerManager->SetSpriteRenderer(mEffekseerRenderer->CreateSpriteRenderer());
	mEffekseerManager->SetRibbonRenderer(mEffekseerRenderer->CreateRibbonRenderer());
	mEffekseerManager->SetRingRenderer(mEffekseerRenderer->CreateRingRenderer());
	mEffekseerManager->SetTrackRenderer(mEffekseerRenderer->CreateTrackRenderer());
	mEffekseerManager->SetModelRenderer(mEffekseerRenderer->CreateModelRenderer());

	// テクスチャ、モデル、カーブ、マテリアルローダーの設定する。
	mEffekseerManager->SetTextureLoader(mEffekseerRenderer->CreateTextureLoader());
	mEffekseerManager->SetModelLoader(mEffekseerRenderer->CreateModelLoader());
	mEffekseerManager->SetMaterialLoader(mEffekseerRenderer->CreateMaterialLoader());
 	mEffekseerManager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());
}

void EffectSystem::Draw()
{
	// メインカメラを取得する
	std::shared_ptr<CameraManager> cameraManager = SceneManager::GetInstance().GetCurrentScene().lock()->GetCameraManager();
	std::shared_ptr<Camera> mainCamera = cameraManager->GetMainCamera();

	// プロジェクション行列の作成
	::Effekseer::Matrix44 projection = ConvertEffekseerMatrix(mainCamera->GetProjectionMatrix());

	// ビュー行列の作成
	::Effekseer::Matrix44 view = ConvertEffekseerMatrix(mainCamera->GetViewMatrix());

	// カメラ位置を取得
	DirectX::SimpleMath::Vector3 position = mainCamera->GetCameraPosition();

	// レイヤーパラメータの設定
	Effekseer::Manager::LayerParameter layerParameter;
	layerParameter.ViewerPosition = { position.x,position.y, position.z };
	mEffekseerManager->SetLayerParameter(0, layerParameter);

	// マネージャーの更新
	Effekseer::Manager::UpdateParameter updateParameter;
	mEffekseerManager->Update(updateParameter);

	// プロジェクション,ビューの設定
	mEffekseerRenderer->SetProjectionMatrix(projection);
	mEffekseerRenderer->SetCameraMatrix(view);

	// エフェクトの描画開始処理を行う。
	mEffekseerRenderer->BeginRendering();

	// エフェクトの描画を行う。
	Effekseer::Manager::DrawParameter drawParameter;
	drawParameter.ZNear = 0.0f;
	drawParameter.ZFar = 1.0f;
	drawParameter.ViewProjectionMatrix = mEffekseerRenderer->GetCameraProjectionMatrix();
	mEffekseerManager->Draw(drawParameter);

	// エフェクトの描画終了処理を行う。
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
