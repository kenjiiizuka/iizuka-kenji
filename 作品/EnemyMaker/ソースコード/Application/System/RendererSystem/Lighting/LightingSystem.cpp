#include "LightingSystem.h"
#include "../VisualEntity/VisualEntity.h"
#include "../VisualEntity/VisualEntityData.h"
#include "../../../Game/GameObject/Light/LightBase.h"
#include "../../../Manager.h"
#include "../../../Game/Scene/Scene.h"
#include "../View/RenderTarget.h"
#include "../View/DepthStencil.h"
#include "../Shader/PixelShader/DepthWritePixelShader.h"
#include "../RendererInformation.h"
#include "../Shader/PixelShader/ShadowPixelShader.h"
#include "../Shader/VertexShader/ShadowVertexShader.h"
#include "../RendererManager.h"
#include "../Shader/PixelShader/TexturePixelShader.h"
#include "../Shader/VertexShader/VertexObject2DShader.h"
#include "../../AssetSystem/Texture/TextureAssetInclude.h"
#include "../../../Game/Scene/SceneManager.h"

namespace DXSimpleMath = DirectX::SimpleMath;

LightingSystem::LightingSystem()
	: mLightingLevel(4)
{
	// 処理なし
}

LightingSystem::~LightingSystem()
{
	// 処理なし
}

void LightingSystem::Init()
{
	// レンダーターゲットの作成
	mDepthRenderTarget = std::make_shared<RenderTarget>();
	mDepthStencil = std::make_shared<DepthStencil>();

	// シャドウマップ書き込み用のレンダーターゲット、デプスステンシルの作成
	uint16_t shadowMapSize[2] = 
	{
		static_cast<uint16_t>(Renderer::GetInstance().GetWidth() * mLightingLevel),
		static_cast<uint16_t>(Renderer::GetInstance().GetHeight() * mLightingLevel)
	};
	mDepthRenderTarget->Create(DXGI_FORMAT_R32_FLOAT, shadowMapSize[0], shadowMapSize[1]);
	mDepthStencil->Create(shadowMapSize[0], shadowMapSize[1], false);

	struct Vertex
	{
		DXSimpleMath::Vector3 mPosition;
		DXSimpleMath::Vector3 Normal;
		DXSimpleMath::Vector2 TexCoord;
	};

	Vertex* vertex = new Vertex[4];
	vertex[0].mPosition = { 0.0f, 0.0f, 250.0f };
	vertex[0].Normal = { 0.0, 1.0f, 0.0f };
	vertex[0].TexCoord = { 0.0f, 0.0f };

	vertex[1].mPosition = { 250.0f, 0, 250.0f };
	vertex[1].Normal = { 0.0, 1.0f, 0.0f };
	vertex[1].TexCoord = { 1.0f, 0.f };

	vertex[2].mPosition = { 0.0f, 0, 0.0f };
	vertex[2].Normal = { 0.0f, 1.0f, 0.0f };
	vertex[2].TexCoord = { 0.0f, 1.f };

	vertex[3].mPosition = { 250.0f, 0, 0.0f };
	vertex[3].Normal = { 0.0f, 1.0f, 0.0f };
	vertex[3].TexCoord = {1.0f, 1.f};

	VisualEntityData::Description desc{};

	std::shared_ptr<void> vertexData(
		vertex,
		[](void* _data) {delete[] _data; }
	);

	desc.mpVertex = vertexData;
	desc.mTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
	desc.mVertexCount = 4;
	desc.mVertexTypeByteSize = sizeof(Vertex);
	desc.mpIndex = nullptr;
	desc.mbAbleMap = false;
	desc.mbUseIndex = false;
	std::shared_ptr<VisualEntityData> visualData = std::make_shared<VisualEntityData>(desc);

	mShadowEntity = std::make_shared<VisualEntity>(visualData);
	mShadowEntity->MakeVertexShader<ShadowVertexShader>();
	mShadowEntity->SetWorldMatrix(DXSimpleMath::Matrix::Identity);
	mShadowEntity->MakePixelShader<ShadowPixelShader>();
	RendererManager::GetInstance().RegisterEntity(mShadowEntity, RendererInf::Layer_Lithing);

	// 影書き込み用のピクセルシェーダー作成
	mWriteShadowShader = std::make_shared<DepthWritePixelShader>();

#ifdef _DEBUG
	// CreateShadowMapSprite_debug();
#endif // DEBUG
}

void LightingSystem::Lighting(std::vector<std::weak_ptr<VisualEntity>> _entitys, std::weak_ptr<VisualEntity> _lightingEntity)
{
	std::weak_ptr<Scene> currentScene = SceneManager::GetInstance().GetCurrentScene();
	std::shared_ptr<LightBase> light = currentScene.lock()->GetGameObject<LightBase>(ELayer::BaseLayer);
	if (!light)
	{
		return;
	}

	// ライト行列を作成する
	DXSimpleMath::Matrix lView_lProj[2];
	light->CalucLightViewMatrix(lView_lProj[0], { 0,0,0 });
	light->CalucLightProjectionMatrix(lView_lProj[1]);
	lView_lProj[0] = lView_lProj[0].Transpose();
	lView_lProj[1] = lView_lProj[1].Transpose();

	// ライト行列の書き込み
	Shader::WriteView_ProjectionMatrix(&lView_lProj);

	// オブジェクトに影を付ける
	mDepthRenderTarget->Clear({ 1.0f,1.0f,0.0f,1.0f });
	mDepthStencil->Clear();
	Renderer::GetInstance().SetRenderTarget(mDepthRenderTarget, mDepthStencil);

	for (std::weak_ptr<VisualEntity> entity : _entitys)
	{
		if (!entity.lock())
		{
			continue;
		}

		// 落ち影ありのシェーダーのみ書き込み
		std::shared_ptr<PixelShader> tmpPixelShader = entity.lock()->GetPixelShader();
		entity.lock()->SetPixelShader(mWriteShadowShader);
		entity.lock()->DrawDropShadow();
		entity.lock()->SetPixelShader(tmpPixelShader);
	}

	Renderer::GetInstance().ResetRenderTarget();

	// シャドウマップのセット
	std::static_pointer_cast<ShadowPixelShader>(_lightingEntity.lock()->GetPixelShader())->SetShadowMap(mDepthRenderTarget->GetResource());

#ifdef _DEBUG
	// デバッグ用　ShadowMap表示
	// mShadowMapEntity->GetVisualEntityData(0)->SetMaterialTexture(mDepthRenderTarget->GetResource());
#endif // DEBUG
}

void LightingSystem::CreateShadowMapSprite_debug()
{
	Vertex* vertex = new Vertex[4];
	vertex[0].mPosition = { 0, 0, 0 };
	vertex[0].mNormal = {0.0, 1.0f, 0.0f};
	vertex[0].mTexCoord = { 0.0f, 0.f };
	vertex[0].mDiffuse = { 1.0f,1.0f,1.0f,1.0f };

	vertex[1].mPosition = { 1280 / 4, 0, 0 };
	vertex[1].mNormal = { 0.0, 1.0f, 0.0f };
	vertex[1].mTexCoord = { 1.0f, 0.f };
	vertex[1].mDiffuse = { 1.0f,1.0f,1.0f,1.0f };

	vertex[2].mPosition = { 0, 720 / 4, 0 };
	vertex[2].mNormal = { 0.0f, 1.0f, 0.0f };
	vertex[2].mTexCoord = { 0.0f, 1.f };
	vertex[2].mDiffuse = { 1.0f,1.0f,1.0f,1.0f };

	vertex[3].mPosition = { 1280 / 4, 720 / 4, 0 };
	vertex[3].mNormal = { 0.0f, 1.0f, 0.0f };
	vertex[3].mTexCoord = { 1.0f, 1.f };
	vertex[3].mDiffuse = { 1.0f,1.0f,1.0f,1.0f };

	std::shared_ptr<void> vertexData(
		vertex,
		[](void* data) {delete[] static_cast<Vertex*>(data); }
	);

	VisualEntityData::Description desc{};
	desc.mbAbleMap = false;
	desc.mbUseIndex = false;
	desc.mIndexCount = 0;
	desc.mIndexTypeByteSize = 0;
	desc.mpIndex = nullptr;
	desc.mpVertex = vertexData;
	desc.mVertexCount = 4;
	desc.mVertexTypeByteSize = sizeof(Vertex);
	desc.mTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;

	std::shared_ptr<VisualEntityData> visualData = std::make_shared<VisualEntityData>(desc);
	VisualEntityData::Material material;

	visualData->SetMaterial(material);
	mShadowMapEntity = std::make_shared<VisualEntity>(visualData);

	std::shared_ptr<TexturePixelShader> pixelShader = mShadowMapEntity->MakePixelShader<TexturePixelShader>();
	mShadowMapEntity->MakeVertexShader<VertexObject2DShader>();

	DXSimpleMath::Matrix world;
	world = DXSimpleMath::Matrix::Identity;			// 単位行列にする
	
	mShadowMapEntity->SetWorldMatrix(world);
	
	RendererManager::GetInstance().RegisterEntity(mShadowMapEntity, RendererInf::Layer_Overlay);
}
