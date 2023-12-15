#include "SpriteComponent.h"
#include "../../../System/RendererSystem/Shader/VertexShader/VertexObject2DShader.h"
#include "../../../System/RendererSystem/VisualEntity/VisualEntity.h"
#include "../../../System/RendererSystem/VisualEntity/VisualEntityData.h"
#include "../../../System/RendererSystem/Shader/PixelShader/TexturePixelShader.h"
#include "../../../System/RendererSystem/RendererInformation.h"
#include "../../../System/RendererSystem/RendererManager.h"
#include "../../../ImGui/ImGuiUtility.h"

using namespace DirectX::SimpleMath;

SpriteComponent::SpriteComponent()
	: mVertex(nullptr)
{
	// 処理なし
}

SpriteComponent::~SpriteComponent()
{
	// 処理なし
}

void SpriteComponent::Init(DirectX::SimpleMath::Vector2 _pos, DirectX::SimpleMath::Vector2 _size, DirectX::SimpleMath::Vector4 _diffuse)
{
	// 左上頂点を設定
	mTransform.mPosition = { _pos.x, _pos.y, 0.0f };
	mSize = { _size.x, _size.y };
	mDiffuse = { 1.0f,1.0f,1.0f,0.2f };

	mVertex = new Vertex[4];
	mVertex[0].mPosition = mTransform.mPosition;
	mVertex[0].mTexCoord = Vector2(0.0f, 0.f);

	mVertex[1].mPosition = { mTransform.mPosition.x + mSize.x, mTransform.mPosition.y, 0.0f};
	mVertex[1].mTexCoord = Vector2(1.0f, 0.f);

	mVertex[2].mPosition = { mTransform.mPosition.x, mTransform.mPosition.y + mSize.y, 0.0f };
	mVertex[2].mTexCoord = Vector2(0.0f, 1.f);

	mVertex[3].mPosition = mTransform.mPosition + mSize;
	mVertex[3].mTexCoord = Vector2(1.0f, 1.f);

	for (size_t vertex_i = 0; vertex_i < 4; vertex_i++)
	{
		mVertex[vertex_i].mDiffuse = mDiffuse;
		mVertex[vertex_i].mNormal = {0.0f, 1.0f, 0.0f};
	}

	std::shared_ptr<void> vertexData
	(
		mVertex,
		[](void* data) {delete[] static_cast<Vertex*>(data); }
	);

	VisualEntityData::Description desc{};
	desc.mbAbleMap = true;
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
	mEntity = std::make_shared<VisualEntity>(visualData);

	std::shared_ptr<TexturePixelShader> pixelShader = mEntity->MakePixelShader<TexturePixelShader>();
	mEntity->MakeVertexShader<VertexObject2DShader>();

	Matrix world;
	world = Matrix::Identity;			// 単位行列にする
	mEntity->SetWorldMatrix(world);
	mEntity->SetOwnerObject(mOwner);
	RendererManager::GetInstance().RegisterEntity(mEntity, RendererInf::Layer_Overlay);
}

void SpriteComponent::Uninit()
{
	mEntity.reset();
}

void SpriteComponent::SetupTransform(const std::string& _id)
{
	ImGui::Begin("Transform");
	ImGui::PushID(_id.c_str());
	ImGui::SliderFloat("PosX", &mTransform.mPosition.x, 0, 1280);
	ImGui::SliderFloat("PosY", &mTransform.mPosition.y, 0, 720);
	ImGui::SliderFloat("SizeX", &mSize.x, 0, 1280);
	ImGui::SliderFloat("SizeY", &mSize.y, 0, 1280);
	ImGui::SliderFloat("RotationX", &mTransform.mRotation.z, -6.28f, 6.28f);
	ImGui::PopID();
	ImGui::End();
	
	mVertex[0].mPosition = { mTransform.mPosition };
	mVertex[1].mPosition = { mTransform.mPosition.x + mSize.x, mTransform.mPosition.y , 0.0f};
	mVertex[2].mPosition = { mTransform.mPosition.x, mTransform.mPosition.y + mSize.y , 0.0f};
	mVertex[3].mPosition = { mTransform.mPosition + mSize };
	HRESULT hr = mEntity->GetVisualEntityData(0)->MapVertexBuffer(mVertex);
}

void SpriteComponent::ReSize(const DirectX::SimpleMath::Vector2 _size)
{
	mSize = { _size.x, _size.y,0.0f };
	mVertex[0].mPosition = { mTransform.mPosition };
	mVertex[1].mPosition = { mTransform.mPosition.x + mSize.x, mTransform.mPosition.y , 0.0f };
	mVertex[2].mPosition = { mTransform.mPosition.x, mTransform.mPosition.y + mSize.y , 0.0f };
	mVertex[3].mPosition = { mTransform.mPosition + mSize };
	MapVertices();
}

bool SpriteComponent::MapVertices(Vertex* _vertices)
{
	mVertex = _vertices;
	HRESULT hr = mEntity->GetVisualEntityData(0)->MapVertexBuffer(mVertex);
	return (SUCCEEDED(hr));
}

bool SpriteComponent::MapVertices()
{
	mVertex[0].mPosition = { mTransform.mPosition };
	mVertex[1].mPosition = { mTransform.mPosition.x + mSize.x, mTransform.mPosition.y , 0.0f };
	mVertex[2].mPosition = { mTransform.mPosition.x, mTransform.mPosition.y + mSize.y , 0.0f };
	mVertex[3].mPosition = { mTransform.mPosition + mSize };
	HRESULT hr = mEntity->GetVisualEntityData(0)->MapVertexBuffer(mVertex);
	return (SUCCEEDED(hr));
}

void SpriteComponent::SetMaterialTexture(const Texture& _texture)
{
	// テクスチャの設定
	VisualEntityData::Material material = mEntity->GetVisualEntityData(0)->GetMaterial();
	material.mTexture = _texture;
	mEntity->GetVisualEntityData(0)->SetMaterial(material);
}

void SpriteComponent::SetMaterialDiffuse(const DirectX::SimpleMath::Vector4& _diffuse) noexcept
{
	// マテリアルディフューズの設定
	mDiffuse = _diffuse;
	VisualEntityData::Material material = mEntity->GetVisualEntityData(0)->GetMaterial();
	material.mDiffuse = mDiffuse;
	mEntity->GetVisualEntityData(0)->SetMaterial(material);
}

void SpriteComponent::SetMaterialEmission(const DirectX::SimpleMath::Color& _emission) noexcept
{		
	VisualEntityData::Material material = mEntity->GetVisualEntityData(0)->GetMaterial();
	material.Emission = _emission;
	mEntity->GetVisualEntityData(0)->SetMaterial(material);
}

void SpriteComponent::SetMaterialShininess(const float _shininess) noexcept
{
	VisualEntityData::Material material = mEntity->GetVisualEntityData(0)->GetMaterial();
	material.mShininess = _shininess;
	mEntity->GetVisualEntityData(0)->SetMaterial(material);
}

DirectX::SimpleMath::Vector2 SpriteComponent::GetPosition() const noexcept
{
	Vector2 position;
	position.x = mVertex[0].mPosition.x + mSize.x / 2.0f;
	position.y = mVertex[0].mPosition.y + mSize.y / 2.0f;
	return position;
}

void SpriteComponent::SetPositionAndMapVertices(const DirectX::SimpleMath::Vector2 _position) noexcept
{
	Vector2 halfSize = mSize / 2.0f;
	mVertex[0].mPosition = { _position.x - halfSize.x, _position.y - halfSize.y, 0.0f };
	mVertex[1].mPosition = { _position.x + halfSize.x, _position.y - halfSize.y, 0.0f };
	mVertex[2].mPosition = { _position.x - halfSize.x, _position.y + halfSize.y, 0.0f };
	mVertex[3].mPosition = { _position.x + halfSize.x, _position.y + halfSize.y, 0.0f };
	MapVertices(mVertex);
}

void SpriteComponent::SetVisible(const bool _visible) noexcept
{
	Component::SetVisible(_visible);
	mEntity->SetVisible(_visible);
}



