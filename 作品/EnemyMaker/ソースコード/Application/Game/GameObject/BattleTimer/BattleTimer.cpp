//--------- INCLUDES ---------
#include "BattleTimer.h"
#include "../../Component/SpriteComponent/SpriteComponent.h"
#include "../../../System/AssetSystem/Texture/TextureAssetInclude.h"
#include "../../../Utility/MathLibrary.h"
#include "../../../Utility/CurveFloat.h"
#include "../../../System/RendererSystem/Shader/VertexShader/VertexShader.h"

BattleTimer::BattleTimer()
	: mTimeLimitSec(60 * 5) // ５分
	, mState(TimerState::Stop)
	, mFlashElapsedTime(0.0f)
	, mInitialPosition(530,5)
	, mSize(55.0f * 0.6f, 75.0f * 0.6f)
	, mElapsedTimeSec(0.0f)
{
	// 処理なし
}

BattleTimer::~BattleTimer()
{
	// 処理なし
}

void BattleTimer::Init(const double _timeLimit, const DirectX::SimpleMath::Vector2 _pos)
{
	mTimeLimitSec = _timeLimit;
	mInitialPosition = _pos;

	// 点滅用カーブ
	mFlashCurve = std::make_shared<CurveFloat>();
	mFlashCurve->Initialize("assets/Battle/TimerCurve/FlashCurve.json");

	// テクスチャ読み込み
	for (uint8_t tex_i = 0; std::shared_ptr<AssetHandle>& asset : mNumberTextures)
	{
		std::string textureFilePath = "assets/UI/" + std::to_string(tex_i) + ".png";
		asset = AssetManager::GetInstance().Load<TextureProvider>(textureFilePath);
		tex_i++;
	}
	
	// : テクスチャの読み込み
	mKoronTexture = AssetManager::GetInstance().Load<TextureProvider>("assets/UI/Koron.png");

	// . テクスチャの読み込み
	mCommaTexture = AssetManager::GetInstance().Load<TextureProvider>("assets/UI/..png");

	// スプライトコンポーネントの追加
	for (uint8_t sp_i = 0; std::weak_ptr<SpriteComponent>& sp : mSprites) 
	{
		std::shared_ptr<SpriteComponent> sprite = AddComponent<SpriteComponent>();
		
		// 位置
		DirectX::SimpleMath::Vector2 pos =
		{
			mInitialPosition.x + (mSize.x * sp_i), // 400 左端の位置、サイズ＋余白ずらす
			mInitialPosition.y,                    // y軸の位置
		};

		// スプライト初期化処理
		sprite->Init(pos, mSize);
	
		// テクスチャは全て0に設定する	
		sprite->SetMaterialTexture(mNumberTextures[0]->Get<Texture>());
		
		sp = sprite;
		sp_i++;
	}

	// コロン テクスチャの設定
	mSprites[1].lock()->SetMaterialTexture(mKoronTexture->Get<Texture>());
	mSprites[4].lock()->SetMaterialTexture(mCommaTexture->Get<Texture>());

	// 残り時間に合わせてテクスチャを設定する
	SetupTexture();
}

void BattleTimer::Update(const double _deltaTime)
{
	// 計測中なら制限時間を減らす
	if (mState == TimerState::Count)
	{	
		mTimeLimitSec -= _deltaTime;
		mElapsedTimeSec += _deltaTime;

		// 残り時間がなくなっていたら終了ステートにいく
		if (mTimeLimitSec <= 0.0)
		{
			mTimeLimitSec = 0.0;
			mState = TimerState::End;
		}

		// 残り時間に合わせてテクスチャを設定する
		SetupTexture();

		// 60秒以下になったら赤く点滅させ,振動させる
		if (mTimeLimitSec <= 60.0f)
		{
			TimerFlash(_deltaTime);
			TimerVibration(_deltaTime);
		}
	}
}

void BattleTimer::SetupTexture()
{	
	// 残り時間を表示できる形式に変換する
	uint16_t time = ConvertTimeToDrawFormat(mTimeLimitSec);

	// テクスチャの設定 
	// 分
	{
		uint8_t digit = MathLibrary::GetDigitValue(time, 4);
		mSprites[0].lock()->SetMaterialTexture(mNumberTextures[digit]->Get<Texture>());
	}

	// 秒 2桁目
	{
		uint8_t digit = MathLibrary::GetDigitValue(time,3);
		mSprites[2].lock()->SetMaterialTexture(mNumberTextures[digit]->Get<Texture>());
	}

	// 秒 1桁目
	{
		uint8_t digit = MathLibrary::GetDigitValue(time, 2);
		mSprites[3].lock()->SetMaterialTexture(mNumberTextures[digit]->Get<Texture>());
	}

	// 秒　小数点第1位
	{
		uint8_t digit = MathLibrary::GetDigitValue(time, 1);
		mSprites[5].lock()->SetMaterialTexture(mNumberTextures[digit]->Get<Texture>());
	}

	// 秒　小数点第2位
	{
		uint8_t digit = MathLibrary::GetDigitValue(time, 0);
		mSprites[6].lock()->SetMaterialTexture(mNumberTextures[digit]->Get<Texture>());
	}
}

uint16_t BattleTimer::ConvertTimeToDrawFormat(const double _second)
{
	// 分
	uint8_t minutes = static_cast<uint8_t>(mTimeLimitSec / 60.0);

	// 秒 桁ごとの値を取り出しやすいように整数にする 例 16.05 → 1605
	uint16_t seconds = static_cast<uint16_t>((mTimeLimitSec - minutes * 60.0f) * 100);

	// 分を先頭の桁に移動 + 秒
	return minutes * 10000 + seconds;
}

void BattleTimer::TimerVibration(const double _deltaTime)
{
	// 振動させる
	DirectX::SimpleMath::Vector2 randomVector =
	{
		MathLibrary::RandomFloatInRange(-1.0f, 1.0f),
		MathLibrary::RandomFloatInRange(-1.0f,1.0f)
	};

	for (uint8_t sp_i = 0; std::weak_ptr<SpriteComponent>& sp : mSprites)
	{
		sp.lock()->AddPosition(randomVector);

		// 範囲がに出ないようにする

		// 位置
		DirectX::SimpleMath::Vector2 pos =
		{
			mInitialPosition.x + (mSize.x * sp_i), // 400 左端の位置、サイズ＋余白ずらす
			mInitialPosition.y,                           // y軸の位置
		};

		float range = 5.0f;
		// xが初期位置から +- rangeの範囲いるか、範囲外ならもとの位置に戻す
		DirectX::SimpleMath::Vector3 vertexPos = sp.lock()->GetVertices()[0].mPosition;
		if (MathLibrary::Abs(pos.x - vertexPos.x) >= range)
		{
			sp.lock()->SetPositionAndMapVertices(pos + mSize / 2.0f);
		}
		else if (MathLibrary::Abs(pos.y - vertexPos.y) >= range)
		{
			sp.lock()->SetPositionAndMapVertices(pos + mSize / 2.0f);
		}
		sp_i++;
	}
}

void BattleTimer::TimerFlash(const double _deltaTime)
{
	// サインカーブに合わせて点滅させる
	float t = static_cast<float>(mFlashElapsedTime / 0.5);

	// カーブから値を取得する
	float red = mFlashCurve->GetValueByTime(t);

	// 色をセットする
	for (std::weak_ptr<SpriteComponent>& sp : mSprites)
	{
		sp.lock()->SetMaterialDiffuse({1, red,red,1});
	}

	// tが1を超えたら経過時間を0に戻す
	mFlashElapsedTime = (t >= 1.0) ? 0.0 : mFlashElapsedTime + _deltaTime;
}