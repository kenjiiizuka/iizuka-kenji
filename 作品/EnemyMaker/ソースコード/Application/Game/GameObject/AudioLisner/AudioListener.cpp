//----------- INCLUDES ----------
#include "AudioListener.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneManager.h"
#include "../../GameObject/Camera/CameraManager.h"

AudioListener::AudioListener()
	: mListener({})
{
	// �����Ȃ�
}

AudioListener::~AudioListener()
{
	// �����Ȃ�
}

void AudioListener::Init()
{
	std::shared_ptr<Scene> scene = SceneManager::GetInstance().GetCurrentScene().lock();
	mListenerObject = scene->GetCameraManager()->GetMainCamera();

	std::shared_ptr<TransformComponent> transform = mListenerObject.lock()->GetComponent<TransformComponent>();
	mListener.Position = transform->GetPosition();
	mListener.OrientFront = transform->GetForwardVector();
	mListener.OrientTop = transform->GetUpVector();
	mListener.Velocity = DirectX::SimpleMath::Vector3::Zero;

	mListenerTransformComponent = transform;
}

void AudioListener::Update(const double _deltaTime)
{
	DirectX::SimpleMath::Vector3 position = mListenerTransformComponent.lock()->GetPosition();
	mListener.Velocity =  mListener.Position - position;
	mListener.Position = position;
	mListener.OrientFront = mListenerTransformComponent.lock()->GetForwardVector();
	mListener.OrientTop = mListenerTransformComponent.lock()->GetUpVector();	
}

void AudioListener::SwitchListenerObject(std::shared_ptr<GameObject> _listenerObject) noexcept
{
	// �V�������X�i�[�ƂȂ�I�u�W�F�N�g���Z�b�g���A���X�i�[�̏����Z�b�g����
	mListenerObject = _listenerObject;
	std::shared_ptr<TransformComponent> transform = mListenerObject.lock()->GetComponent<TransformComponent>();
	mListener.Position = transform->GetPosition();
	mListener.OrientFront = transform->GetForwardVector();
	mListener.OrientTop = transform->GetUpVector();
	mListener.Velocity = DirectX::SimpleMath::Vector3::Zero;
	mListenerTransformComponent = transform;
}
