//----------- INCLUDES ----------
#include "AudioEmitter.h"
#include "../../System/AudioSystem/AudioSource.h"
#include "../../System/RendererSystem/DebugRenderer/DebugRendererManager.h"
#include "../../Utility/MathLibrary.h"

AudioEmitter::AudioEmitter()
	: mEmitter()
	, mbDestroy(false)
{
	// �����Ȃ�
}

AudioEmitter::~AudioEmitter()
{
	// �����Ȃ�
}

void AudioEmitter::Initialize(const std::shared_ptr<AudioClip> _audioClip, const UINT32 _channelCount, const DirectX::SimpleMath::Vector3 _rotation, const DirectX::SimpleMath::Vector3 _position, const float _innerRadius)
{
	// �G�~�b�^�[�̐ݒ�
	mEmitter.pCone = NULL;
	mEmitter.ChannelCount = _channelCount;
	mEmitter.ChannelRadius = 1.0f;
	mEmitter.InnerRadius = _innerRadius;
	mEmitter.InnerRadiusAngle = X3DAUDIO_PI / 4.0f;
	FLOAT32 azimuths = X3DAUDIO_2PI;
	mEmitter.pChannelAzimuths = &azimuths;
	mEmitter.CurveDistanceScaler = 1.0f;
	mEmitter.DopplerScaler = 1.0f;

	mEmitter.Position = _position;
	mEmitter.OrientTop = MathLibrary::GetUpVector(_rotation);
	mEmitter.OrientFront = MathLibrary::GetForwardVector(_rotation);

	// �I�[�f�B�I�Đ�
	mAudioClip = _audioClip;
	mAudioClip.lock()->Play();
	mAudioSource = mAudioClip.lock()->GetAudioSource();
}

void AudioEmitter::Update()
{
	// �Đ����I�����Ă��邩���m�F����
	CheckFinish();

#ifdef _DEBUG
	// DebugRendererManager::GetInstance().DrawSphere(mEmitter.Position, mEmitter.InnerRadius);
#endif
}

void AudioEmitter::CheckFinish()
{
	if(!mAudioSource.lock())
	{
		mbDestroy = true;
		return;
	}

	if (mAudioSource.lock()->IsFinish())
	{
		// �Đ����~�߂�
		mAudioSource.lock()->Stop();
		mbDestroy = true;
		return;
	}
}