//------- INCLUDES ----------
#include <string>
#include "Number.h"
#include "../../../System/AssetSystem/Texture/TextureAssetInclude.h"
#include "../../../Utility/MathLibrary.h"
#include "../Billboard/BillboardObject.h"

Number::Number()
	: mNumber(0)
{
	// 処理なし
}

Number::~Number()
{
	// 処理なし
}

void Number::Init()
{
	// テクスチャの準備
	mNumberTextures.resize(10);	
	std::string filePath = "assets/UI/";
	for (size_t texture_i = 0; std::shared_ptr<AssetHandle>& texture : mNumberTextures)
	{
		texture = AssetManager::GetInstance().Load<TextureProvider>(filePath + std::to_string(texture_i) + ".png");
		texture_i++;
	}

	// 最大３桁まで表示する
	mNumberBillboard.resize(3);
	float xPos = 0.0f;
	for (std::weak_ptr<BillboardObject>& number : mNumberBillboard)
	{
		number = AddChildObject<BillboardObject>();
		number.lock()->Init();
		number.lock()->SetPosition({ xPos,0.0f,0.0f });
		Texture texture = mNumberTextures[0]->Get<Texture>();
		number.lock()->SetMaterialDiffuse({ 1,1,1,0 });
		number.lock()->SetTexture(texture);
		xPos -= 1.5f;
	}
}

void Number::SetNumber(const uint8_t _number)
{
	mNumber = _number;
	for (uint8_t i = 0; std::weak_ptr<BillboardObject>& billboard : mNumberBillboard)
	{
		uint8_t num = MathLibrary::GetDigitValue(mNumber, i);
		billboard.lock()->SetMaterialDiffuse({ 1,1,1,1 });

		if (num <= 0 && i > 0)
		{
			billboard.lock()->SetMaterialDiffuse({ 1,1,1,0 });
		}
		billboard.lock()->SetTexture(mNumberTextures[num]->Get<Texture>());	
		i++;
	}
}

void Number::SetDiffuse(const DirectX::SimpleMath::Color _color)
{
	for (uint8_t i = 0; std::weak_ptr<BillboardObject>&billboard : mNumberBillboard)
	{
		uint8_t num = MathLibrary::GetDigitValue(mNumber, i);
		billboard.lock()->SetMaterialDiffuse(_color);

		if (num <= 0 && i > 0)
		{
			billboard.lock()->SetMaterialDiffuse({ 1,1,1,0 });
		}
		billboard.lock()->SetTexture(mNumberTextures[num]->Get<Texture>());
		i++;
	}
}

void Number::SetPosition(DirectX::SimpleMath::Vector3 _position)
{
	mTransform.lock()->SetPosition(_position);
	Transform trans = mTransform.lock()->GetTransform();
	DirectX::SimpleMath::Matrix matrix = MathLibrary::MakeWorldMatrix(trans);
	for (std::weak_ptr<BillboardObject>& billboard : mNumberBillboard)
	{
		billboard.lock()->CalcuWorldMatrix(matrix);
	}
}

