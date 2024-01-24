//--------- INCLUDES ---------
#include "BattleTimer.h"
#include "../../Component/SpriteComponent/SpriteComponent.h"
#include "../../../System/AssetSystem/Texture/TextureAssetInclude.h"
#include "../../../Utility/MathLibrary.h"
#include "../../../Utility/CurveFloat.h"
#include "../../../System/RendererSystem/Shader/VertexShader/VertexShader.h"

BattleTimer::BattleTimer()
	: mTimeLimitSec(60 * 5) // �T��
	, mState(TimerState::Stop)
	, mFlashElapsedTime(0.0f)
	, mInitialPosition(530,5)
	, mSize(55.0f * 0.6f, 75.0f * 0.6f)
	, mElapsedTimeSec(0.0f)
{
	// �����Ȃ�
}

BattleTimer::~BattleTimer()
{
	// �����Ȃ�
}

void BattleTimer::Init(const double _timeLimit, const DirectX::SimpleMath::Vector2 _pos)
{
	mTimeLimitSec = _timeLimit;
	mInitialPosition = _pos;

	// �_�ŗp�J�[�u
	mFlashCurve = std::make_shared<CurveFloat>();
	mFlashCurve->Initialize("assets/Battle/TimerCurve/FlashCurve.json");

	// �e�N�X�`���ǂݍ���
	for (uint8_t tex_i = 0; std::shared_ptr<AssetHandle>& asset : mNumberTextures)
	{
		std::string textureFilePath = "assets/UI/" + std::to_string(tex_i) + ".png";
		asset = AssetManager::GetInstance().Load<TextureProvider>(textureFilePath);
		tex_i++;
	}
	
	// : �e�N�X�`���̓ǂݍ���
	mKoronTexture = AssetManager::GetInstance().Load<TextureProvider>("assets/UI/Koron.png");

	// . �e�N�X�`���̓ǂݍ���
	mCommaTexture = AssetManager::GetInstance().Load<TextureProvider>("assets/UI/..png");

	// �X�v���C�g�R���|�[�l���g�̒ǉ�
	for (uint8_t sp_i = 0; std::weak_ptr<SpriteComponent>& sp : mSprites) 
	{
		std::shared_ptr<SpriteComponent> sprite = AddComponent<SpriteComponent>();
		
		// �ʒu
		DirectX::SimpleMath::Vector2 pos =
		{
			mInitialPosition.x + (mSize.x * sp_i), // 400 ���[�̈ʒu�A�T�C�Y�{�]�����炷
			mInitialPosition.y,                    // y���̈ʒu
		};

		// �X�v���C�g����������
		sprite->Init(pos, mSize);
	
		// �e�N�X�`���͑S��0�ɐݒ肷��	
		sprite->SetMaterialTexture(mNumberTextures[0]->Get<Texture>());
		
		sp = sprite;
		sp_i++;
	}

	// �R���� �e�N�X�`���̐ݒ�
	mSprites[1].lock()->SetMaterialTexture(mKoronTexture->Get<Texture>());
	mSprites[4].lock()->SetMaterialTexture(mCommaTexture->Get<Texture>());

	// �c�莞�Ԃɍ��킹�ăe�N�X�`����ݒ肷��
	SetupTexture();
}

void BattleTimer::Update(const double _deltaTime)
{
	// �v�����Ȃ琧�����Ԃ����炷
	if (mState == TimerState::Count)
	{	
		mTimeLimitSec -= _deltaTime;
		mElapsedTimeSec += _deltaTime;

		// �c�莞�Ԃ��Ȃ��Ȃ��Ă�����I���X�e�[�g�ɂ���
		if (mTimeLimitSec <= 0.0)
		{
			mTimeLimitSec = 0.0;
			mState = TimerState::End;
		}

		// �c�莞�Ԃɍ��킹�ăe�N�X�`����ݒ肷��
		SetupTexture();

		// 60�b�ȉ��ɂȂ�����Ԃ��_�ł���,�U��������
		if (mTimeLimitSec <= 60.0f)
		{
			TimerFlash(_deltaTime);
			TimerVibration(_deltaTime);
		}
	}
}

void BattleTimer::SetupTexture()
{	
	// �c�莞�Ԃ�\���ł���`���ɕϊ�����
	uint16_t time = ConvertTimeToDrawFormat(mTimeLimitSec);

	// �e�N�X�`���̐ݒ� 
	// ��
	{
		uint8_t digit = MathLibrary::GetDigitValue(time, 4);
		mSprites[0].lock()->SetMaterialTexture(mNumberTextures[digit]->Get<Texture>());
	}

	// �b 2����
	{
		uint8_t digit = MathLibrary::GetDigitValue(time,3);
		mSprites[2].lock()->SetMaterialTexture(mNumberTextures[digit]->Get<Texture>());
	}

	// �b 1����
	{
		uint8_t digit = MathLibrary::GetDigitValue(time, 2);
		mSprites[3].lock()->SetMaterialTexture(mNumberTextures[digit]->Get<Texture>());
	}

	// �b�@�����_��1��
	{
		uint8_t digit = MathLibrary::GetDigitValue(time, 1);
		mSprites[5].lock()->SetMaterialTexture(mNumberTextures[digit]->Get<Texture>());
	}

	// �b�@�����_��2��
	{
		uint8_t digit = MathLibrary::GetDigitValue(time, 0);
		mSprites[6].lock()->SetMaterialTexture(mNumberTextures[digit]->Get<Texture>());
	}
}

uint16_t BattleTimer::ConvertTimeToDrawFormat(const double _second)
{
	// ��
	uint8_t minutes = static_cast<uint8_t>(mTimeLimitSec / 60.0);

	// �b �����Ƃ̒l�����o���₷���悤�ɐ����ɂ��� �� 16.05 �� 1605
	uint16_t seconds = static_cast<uint16_t>((mTimeLimitSec - minutes * 60.0f) * 100);

	// ����擪�̌��Ɉړ� + �b
	return minutes * 10000 + seconds;
}

void BattleTimer::TimerVibration(const double _deltaTime)
{
	// �U��������
	DirectX::SimpleMath::Vector2 randomVector =
	{
		MathLibrary::RandomFloatInRange(-1.0f, 1.0f),
		MathLibrary::RandomFloatInRange(-1.0f,1.0f)
	};

	for (uint8_t sp_i = 0; std::weak_ptr<SpriteComponent>& sp : mSprites)
	{
		sp.lock()->AddPosition(randomVector);

		// �͈͂��ɏo�Ȃ��悤�ɂ���

		// �ʒu
		DirectX::SimpleMath::Vector2 pos =
		{
			mInitialPosition.x + (mSize.x * sp_i), // 400 ���[�̈ʒu�A�T�C�Y�{�]�����炷
			mInitialPosition.y,                           // y���̈ʒu
		};

		float range = 5.0f;
		// x�������ʒu���� +- range�͈̔͂��邩�A�͈͊O�Ȃ���Ƃ̈ʒu�ɖ߂�
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
	// �T�C���J�[�u�ɍ��킹�ē_�ł�����
	float t = static_cast<float>(mFlashElapsedTime / 0.5);

	// �J�[�u����l���擾����
	float red = mFlashCurve->GetValueByTime(t);

	// �F���Z�b�g����
	for (std::weak_ptr<SpriteComponent>& sp : mSprites)
	{
		sp.lock()->SetMaterialDiffuse({1, red,red,1});
	}

	// t��1�𒴂�����o�ߎ��Ԃ�0�ɖ߂�
	mFlashElapsedTime = (t >= 1.0) ? 0.0 : mFlashElapsedTime + _deltaTime;
}