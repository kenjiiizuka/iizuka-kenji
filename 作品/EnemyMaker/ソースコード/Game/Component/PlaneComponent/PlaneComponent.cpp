#include "PlaneComponent.h"
#include "../../GameObject/GameObject.h"
#include "../../../System/RendererSystem/Renderer.h"
#include "../../../System/AssetSystem/Texture/TextureAssetInclude.h"
#include "../../../System/RendererSystem/VisualEntity/VisualEntity.h"
#include "../../../System/RendererSystem/VisualEntity/VisualEntityData.h"
#include "../../../System/RendererSystem/Shader/PixelShader/LightPixelShader.h"
#include "../../../System/RendererSystem/Shader/VertexShader/Object3DVertexShader.h"
#include "../../../System/RendererSystem/RendererManager.h"
#include "../../../System/RendererSystem/Shader/PixelShader/TexturePixelShader.h"

using namespace DirectX::SimpleMath;

PlaneComponent::PlaneComponent()
{
}

void PlaneComponent::Init(Vector3 _size, Vector3 _offset, const std::string& _textureFilePath, bool _isLighting)
{
	struct Vertex
	{
		Vector3 mPosition;
		Vector3 Normal;
		Vector2 TexCoord;
		Vector4 Color;
	};

	// テクスチャ読み込み
	std::shared_ptr<AssetHandle> textureHandle = AssetManager::GetInstance().Load<TextureProvider>(_textureFilePath);

	std::weak_ptr<TransformComponent> trans = mOwner->GetComponent<TransformComponent>();
	Vector3 ownerPos = trans.lock()->GetPosition() +_offset;
	_size *= trans.lock()->GetScale();

	Vertex* vertex = new Vertex[4];
	vertex[0].mPosition = Vector3(ownerPos.x - _size.x, ownerPos.y + _size.y , ownerPos.z + _size.z );
	vertex[0].Normal = Vector3(0.0, 1.0f, 0.0f);
	vertex[0].TexCoord = Vector2(0.0f, 0.f);
	vertex[0].Color = { 1.0f,1.0f,1.0f,1.0f };

	vertex[1].mPosition = Vector3(ownerPos.x + _size.x, ownerPos.y + _size.y , ownerPos.z + _size.z );
	vertex[1].Normal = Vector3(0.0, 1.0f, 0.0f);
	vertex[1].TexCoord = Vector2(1.0f, 0.f);
	vertex[1].Color = { 1.0f,1.0f,1.0f,1.0f };

	vertex[2].mPosition = Vector3(ownerPos.x - _size.x, ownerPos.y - _size.y , ownerPos.z - _size.z );
	vertex[2].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[2].TexCoord = Vector2(0.0f, 1.f);
	vertex[2].Color = { 1.0f,1.0f,1.0f,1.0f };

	vertex[3].mPosition = Vector3(ownerPos.x + _size.x, ownerPos.y - _size.y , ownerPos.z - _size.z );
	vertex[3].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[3].TexCoord = Vector2(1.0f, 1.f);
	vertex[3].Color = { 1.0f,1.0f,1.0f,1.0f };

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

	mVisualEntity = std::make_shared<VisualEntity>(visualData);

	VisualEntityData::Material material;
	material.mDiffuse = { 1,1,1,1 };
	material.mAmbient = { 0.3f,0.3f,0.3f,1.0f };
	material.mShininess = 1.0f;
	material.mSpecular = { 1.0f,1.0f,1.0f,0.0f };
	
	if (textureHandle->IsValid())
	{
		material.mTexture = textureHandle->Get<Texture>();
	}


	mVisualEntity->GetVisualEntityData(0)->SetMaterial(material);	
	mVisualEntity->MakeVertexShader<Object3DVertexShader>();
	mVisualEntity->SetWorldMatrix(mOwner->GetComponent<TransformComponent>()->GetWorldMatrix());
	mVisualEntity->SetOwnerObject(mOwner);
	
	if (_isLighting)
	{
		mVisualEntity->MakePixelShader<LightPixelShader>();
		RendererManager::GetInstance().RegisterEntity(mVisualEntity, RendererInf::Layer_Object);
	}
	else
	{
		mVisualEntity->MakePixelShader<TexturePixelShader>();
		RendererManager::GetInstance().RegisterEntity(mVisualEntity, RendererInf::Layer_BackGround);
	}	
}

void PlaneComponent::Draw()
{
	mVisualEntity->SetWorldMatrix(mOwner->GetComponent<TransformComponent>()->GetWorldMatrix());
}



void PlaneComponent::Uninit()
{

}





