//------------ INCLUDES -----------
#include "AudioTestScene.h"
#include "../../../System/Audio/audio.h"
#include "../../../ImGui/ImGuiUtility.h"
#include "../../../System/AssetSystem/Audio/AudioProvider.h"
#include "../../../System/AssetSystem/AssetManager.h"
#include "../../Resource/AudioClip.h"
#include "../../../System/Logger/Logger.h"
#include "../../../System/AudioSystem/AudioSystem.h"

std::shared_ptr<AudioClip> audioClip;

AudioTestScene::AudioTestScene()
{
}

void AudioTestScene::Initialize()
{
	audioClip = std::make_shared<AudioClip>();
	audioClip->Initialize("assets/audio/bgm.wav");
	audioClip->SetLoop(false);

}

void AudioTestScene::Uninitialize()
{

}

void AudioTestScene::Update()
{
	ImGui::Begin("SoundPlay");
	if (ImGui::Button("Play"))
	{
		AudioSystem::GetInstance().SpawnAudioEmitterAndPlay(audioClip, { 0,0,0 }, { 0,0,0 });
	}
	else if (ImGui::Button("Stop"))
	{
		audioClip->Stop();
	}
	else if (ImGui::Button("Resume"))
	{
		
	}
	ImGui::End();
}
