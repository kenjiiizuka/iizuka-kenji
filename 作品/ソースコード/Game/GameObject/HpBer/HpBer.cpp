#include "HpBer.h"
#include "../../Component/SpriteComponent/SpriteComponent.h"
#include "../../../System/RendererSystem/Shader/VertexShader/VertexShader.h"
#include "../../../Utility/MathLibrary.h"
#include "../../../System/AssetSystem/Texture/TextureAssetInclude.h"
#include "../../../System/InputSystem/Input.h"
#include "../../../System/FPSController/FPSController.h"

using namespace DirectX::SimpleMath;

HpBer::HpBer()
	: mCurrentHp(100.f)
	, mMaxHp(100.f)
	, mGageSize(905.f, 40.f)
	, mGagePosition(33.f, 33.f)
	, mFramePosition(30.f,30.f)
	, mFrameSize(911, 46)
	, mDecreaseDamage(0.f)
	, mbLostGageDecreasing(false)
	, mLostElapsedTime(0)
	, mDelayTimeToGageLost(0.7f)
	, mGageLostSpeedPerSec(1.0f)
	, mElapsedDelayTimeToGageLost(0.0f)
	, mLostGageInitialLength(0.0f)
	, mPrevHp(100.0f)
{
}

void HpBer::InitSprite()
{
	// 枠設定
	{
		std::shared_ptr<SpriteComponent> sprite = AddComponent<SpriteComponent>();
		sprite->Init(mFramePosition, mFrameSize, { 1.0f,1.0f,1.0f,1.0f });
		
		std::shared_ptr<AssetHandle> texture = AssetManager::GetInstance().Load<TextureProvider>("assets/UI/Frame_a.png");
		if (texture->IsValid())
		{
			sprite->SetMaterialTexture(texture->Get<Texture>());
		}
		
		mFrameSprite = sprite;
	}

	// ゲージ設定
	{
		mGageSprite = AddComponent<SpriteComponent>();
		mGageSprite.lock()->Init(mGagePosition, mGageSize);
		
		std::shared_ptr<AssetHandle> texture = AssetManager::GetInstance().Load<TextureProvider>("assets/UI/Gage_a.png");
		if (texture->IsValid())
		{
			mGageSprite.lock()->SetMaterialTexture(texture->Get<Texture>());
		}

		mGageSprite.lock()->SetMaterialDiffuse({ 0.4f,0.0f,1.0f,1.0f });
	}

	// ゲージ消失時のゲージ
	{
		// 常にゲージの右端におく
		Vector2 lostGagePos = mGagePosition + mGageSize;
		mGageLostSprite = AddComponent<SpriteComponent>();
		mGageLostSprite.lock()->Init(lostGagePos, { 0.0,0.0 });
		
		std::shared_ptr<AssetHandle> texture = AssetManager::GetInstance().Load<TextureProvider>("assets/UI/Gage_a.png");
		if (texture->IsValid())
		{
			mGageLostSprite.lock()->SetMaterialTexture(texture->Get<Texture>());
		}

		mGageLostSprite.lock()->SetMaterialDiffuse({ 0.1f,0.5f,1.0f,1.0f });
	}
}

void HpBer::Init(float _maxHp, float _currentHp, DirectX::SimpleMath::Vector2 _position, DirectX::SimpleMath::Vector2 _size, float _offset)
{
	mFramePosition = _position;
	mGagePosition = { _position.x + _offset, _position.y + _offset }; // 3.0fは枠の内側に描画するための位置調整
	mFrameSize = _size;
	mGageSize = { _size.x - _offset * 2.0f, _size.y - _offset * 2.0f };
	mMaxHp = _maxHp;
	mCurrentHp = _currentHp;
	InitSprite();
}

void HpBer::Update(const double _deltaTime)
{
	// HPが減っていたら
	if (mDecreaseDamage != 0)
	{
		DecreaseGage();
	}

	// Lostゲージを消していく
	if (mbLostGageDecreasing)
	{
		GageLost();
	}
	
	// 前フレームのHpとして保存する
	mPrevHp = mCurrentHp;
}

void HpBer::DecreaseGage()
{
	// ダメージを受ける前のHPの割合を計算
	float prevHpT = MathLibrary::Clamp01(mPrevHp / mMaxHp);
	// 現在のHpの割合を計算
	float currentHpT = MathLibrary::Clamp01(mCurrentHp / mMaxHp);

	// LostGageの設定
	{
		// LoatGageの設定
		Vertex* lostGageVertex = mGageLostSprite.lock()->GetVertices();
		// 右端 ゲージ消失中は右端の位置は変えない
		if (!mbLostGageDecreasing)
		{
			float rightLostGagePos = mGageSize.x * prevHpT + mGagePosition.x;
			lostGageVertex[1].mPosition = { rightLostGagePos, mGagePosition.y , 0.0f };
			lostGageVertex[3].mPosition = { rightLostGagePos, mGagePosition.y + mGageSize.y,0.0f };

			// UV設定
			float rightU = 1.0f * prevHpT;
			lostGageVertex[1].mTexCoord = { rightU,0.0f };
			lostGageVertex[3].mTexCoord = { rightU,1.0f };
		}
		// 左端
		float leftLostPosition = mGageSize.x * currentHpT + mGagePosition.x;
		lostGageVertex[0].mPosition = { leftLostPosition, mGagePosition.y, 0.0f };
		lostGageVertex[2].mPosition = { leftLostPosition,mGagePosition.y + mGageSize.y,0.0f };

		// UV設定
		float leftU = 1.0f * currentHpT;
		lostGageVertex[0].mTexCoord = { leftU,0.0f };
		lostGageVertex[2].mTexCoord = { leftU,1.0f };

		// 水平なので、X方向の長さを取得する
		mLostGageInitialLength = lostGageVertex[1].mPosition.x - lostGageVertex[0].mPosition.x;

		mGageLostSprite.lock()->MapVertices(lostGageVertex);
	}

	// Gageの設定
	{
		Vertex* gageVertex = mGageSprite.lock()->GetVertices();
		// 右端
		float rightPos = mGageSize.x * currentHpT + mGagePosition.x;
		gageVertex[1].mPosition = { rightPos, mGagePosition.y , 0.0f };
		gageVertex[3].mPosition = { rightPos, mGagePosition.y + mGageSize.y,0.0f };

		//UVの設定
		float u = 1.0f * currentHpT;
		gageVertex[1].mTexCoord = { u,0.0f };
		gageVertex[3].mTexCoord = { u, 1.0f };

		mGageSprite.lock()->MapVertices(gageVertex);
	}

	// 消失用ゲージの値の設定
	mDecreaseDamage = 0;
	mLostElapsedTime = 0;
	mElapsedDelayTimeToGageLost = 0;
	mbLostGageDecreasing = true;
}

void HpBer::GageLost()
{
	// Delay中ならDelay経過時間を加算する
	if (mElapsedDelayTimeToGageLost <= mDelayTimeToGageLost)
	{
		mElapsedDelayTimeToGageLost += static_cast<float>(FPSController::GetDeltaTime());
		return;
	}

	// １秒で消す
	Vertex* lostGageVertex = mGageLostSprite.lock()->GetVertices();
	// 消失の割合を求める
	float lostGageUVT = MathLibrary::Clamp01(mLostElapsedTime / mGageLostSpeedPerSec);
	float lostGageT = 1.0f - lostGageUVT;

	// 右端
	float rightLostGagePos = mLostGageInitialLength * lostGageT + lostGageVertex[0].mPosition.x;
	lostGageVertex[1].mPosition = { rightLostGagePos, mGagePosition.y , 0.0f };
	lostGageVertex[3].mPosition = { rightLostGagePos, mGagePosition.y + mGageSize.y,0.0f };

	// UVの設定
	float u = 1.0f * ((rightLostGagePos - mGagePosition.x) / mGageSize.x);

	u = u <= 0 ? 0.1f : u;
	lostGageVertex[1].mTexCoord = { u, 0.0f };
	lostGageVertex[3].mTexCoord = { u, 1.0f };

	mGageLostSprite.lock()->MapVertices(lostGageVertex);

	// 経過時間の加算
	mLostElapsedTime += static_cast<float>(FPSController::GetDeltaTime());

	// ゲージが減り切ったら
	if (lostGageT <= 0.0)
	{
		mbLostGageDecreasing = false;
		mElapsedDelayTimeToGageLost = 0.0f;
	}
}
