#include "RendererManager.h"
#include "Renderer.h"
#include "VisualEntity/VisualEntity.h"
#include "Shader/VertexShader/VertexShader.h"
#include "Shader/PixelShader/PixelShader.h"
#include "Lighting/LightingSystem.h"
#include "../../Game/GameObject/Camera/Camera.h"
#include "../../Game/GameObject/Camera/CameraManager.h"
#include "../../Manager.h"
#include "../../Game/Scene/Scene.h"
#include "../../Game/GameObject/Camera/Camera2D.h"
#include "../../Game/Scene/SceneManager.h"

using namespace DirectX::SimpleMath;

RendererManager::RendererManager()
	: mbLighting(true)
{
	// 処理なし
}

RendererManager::~RendererManager()
{
	// 処理なし
}

void RendererManager::Init()
{
	mEntityLayer.resize(RendererInf::Layer_Max);

	// ライティングシステム生成、初期化
	mLightingSystem = std::make_shared<LightingSystem>();
	mLightingSystem->Init();
}

void RendererManager::Uninit()
{
	mEntityLayer.clear();
}

void RendererManager::Update()
{
	// 破棄するか判断するEntityがあるか判断する
	for (std::vector<std::weak_ptr<VisualEntity>>& entities : mEntityLayer)
	{
		for (auto it = entities.begin(); it != entities.end();)
		{
			if (!it->lock())
			{
				// 参照がなかったら配列から除外する
				it = entities.erase(it);
				continue;
			}

			if (it->lock().get()->IsDestroy())
			{
				// 破棄フラグがあれば配列から除外
				it = entities.erase(it);		
			}
			else
			{
				it++;
			}
		}
	}	
}

void RendererManager::Draw()
{
	ID3D11DeviceContext* device = Renderer::GetInstance().GetDeviceContext();
	// フレームごとに一回だけで良い情報を先に書き込む
	
	// 3Dカメラ
	std::shared_ptr<CameraManager> cameraManager = SceneManager::GetInstance().GetCurrentScene().lock()->GetCameraManager();
	cameraManager->GetMainCamera()->Draw();

	// Objectごとに必要な情報を書き込む
	uint8_t layer = 0;

	for (std::vector<std::weak_ptr<VisualEntity>> entitys : mEntityLayer)
	{
		// ライティング層なら専用の処理をする
		if (layer == RendererInf::Layer_Lithing && mbLighting)
		{	
			mLightingSystem->Lighting(mEntityLayer[RendererInf::Layer_Object], entitys.front());
			cameraManager->GetMainCamera()->Draw();
		}

		// オーバーレイ層用の処理をする
		else if(layer == RendererInf::Layer_Overlay)
		{
			cameraManager->Get2DCamera()->Draw();
		}

		for (std::weak_ptr<VisualEntity> entity : entitys)
		{
			if (!entity.lock())
			{
				continue;
			}
			entity.lock()->Draw();
		}
		layer++;
	}
}

bool RendererManager::RegisterEntity(std::shared_ptr<VisualEntity> _entity, RendererInf::Layer _layer)
{	
	// 二重登録チェック
	for (std::vector<std::weak_ptr<VisualEntity>> entity : mEntityLayer) 
	{
	/*	auto end = entity.end();
		if (std::find(entity.begin(), end, _entity) != end)
		{
			return false;
		}*/
	}

	mEntityLayer[_layer].push_back(_entity);
	return true;
}



//bool RendererManager::SwitchRegisterLayerEntity(std::shared_ptr<VisualEntity> _entity, uint8_t _switchLayer)
//{
//	// レイヤーチェック
//	if (_switchLayer >= mLayerNum)
//	{
//		return false;
//	}
//
//	for (std::list<std::shared_ptr<VisualEntity>> list : mEntitys)
//	{
//		auto end = list.end();
//		auto findIt = std::find(list.begin(), end, _entity);		
//		if (findIt != end)
//		{
//			mEntitys[_switchLayer].push_back(_entity);
//			list.erase(findIt);
//			return true;
//		}
//	}	
//	return false;
//}
