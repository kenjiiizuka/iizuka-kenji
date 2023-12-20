//--------- INCLUDES ----------
#include "SliderSpriteComponent.h"
#include "../../../ImGui/ImGuiUtility.h"
#include "../../../System/RendererSystem/Shader/VertexShader/VertexObject2DShader.h"


SliderSpriteComponent::SliderSpriteComponent()
	: mMaxSize()
{
	// èàóùÇ»Çµ
}

SliderSpriteComponent::~SliderSpriteComponent()
{
	// èàóùÇ»Çµ
}

void SliderSpriteComponent::Init(DirectX::SimpleMath::Vector2 _pos, DirectX::SimpleMath::Vector2 _maxSize, DirectX::SimpleMath::Vector4 _vertexColor)
{
	mCurrentSliderSize = mMaxSize = _maxSize;
	mMaxUV = mCurrentUV = { 1.0f,1.0f };
	SpriteComponent::Init(_pos, mCurrentSliderSize, _vertexColor);

	//std::shared_ptr<Texture> texture = std::make_shared<Texture>();
	//texture->Load("assets/texture/Title/TitleLayer1.png");
	//SetMaterialTexture(texture);

}

void SliderSpriteComponent::Update(const double _deltaTime)
{
	SpriteComponent::Update(_deltaTime);

	static float t = 1.0f;

	ImGui::Begin("slider");
	ImGui::SliderFloat("t", &t, 0, 1.0f);
	ImGui::End();

	SetSliderSize(t);
}

void SliderSpriteComponent::SetSliderSize(const float _sliderSize_t)
{
	mCurrentSliderSize.x = mMaxSize.x * _sliderSize_t;
	ReSize(mCurrentSliderSize);

	// UVÇÃà íuÇí≤êÆ
	Vertex* vertices = GetVertices();
	mCurrentUV.x = mMaxUV.x * _sliderSize_t;

	vertices[1].mTexCoord.x = mCurrentUV.x;
	vertices[3].mTexCoord.x = mCurrentUV.x;

	MapVertices(vertices);	
}
